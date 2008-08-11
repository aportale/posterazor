/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "FreeImage.h"
#include "PosteRazorImageIO.h"
#include "PosteRazorPDFOutput.h"
#include "UnitsOfLength.h"
#include <stdio.h>
#include <string.h>

static char FreeImageErrorMessage[1024];

void FreeImageErrorHandler(FREE_IMAGE_FORMAT /* fif */, const char *message)
{
	strncpy(FreeImageErrorMessage, message, sizeof(FreeImageErrorMessage));
	FreeImageErrorMessage[sizeof(FreeImageErrorMessage)-1] = '\0';
}

class FreeImageInitializer
{
public:
	FreeImageInitializer()
	{
		FreeImage_Initialise();
		FreeImage_SetOutputMessage(FreeImageErrorHandler);
	}

	~FreeImageInitializer()
	{
		FreeImage_DeInitialise();
	}
};
static FreeImageInitializer initializer;

class PosteRazorImageIOImplementation: public PosteRazorImageIO
{
private:

	FIBITMAP*    m_bitmap;

	int          m_widthPixels;
	int          m_heightPixels;

	unsigned int m_horizontalDotsPerMeter;
	unsigned int m_verticalDotsPerMeter;

	char         m_imageFileName[1024];

	static bool isSystemLittleEndian()
	{
		// Endianness detection lines borrowed from: http://en.wikipedia.org/wiki/Endianness
		const long int i = 1;
		const char *p = (const char *) &i;
		return p[0] == 1;  // Lowest address contains the least significant byte
	}

	// FreeImage_Convert[To|From]RawBits inverted the topdown parameter until v3.10
	static BOOL hasFreeImageVersionCorrectTopDownInConvertBits()
	{
		const char *version = FreeImage_GetVersion();
		int majorVersion;
		int minorVersion;
		const int readCount = sscanf(version, "%d.%d", &majorVersion, &minorVersion);
		return readCount == 2 && majorVersion >= 3 && minorVersion >= 10?TRUE:FALSE;
	}

public:
	PosteRazorImageIOImplementation()
		: m_bitmap(NULL)
		, m_widthPixels(0)
		, m_heightPixels(0)
		, m_horizontalDotsPerMeter(0)
		, m_verticalDotsPerMeter(0)
	{
		m_imageFileName[0] = '\0';
	}

	~PosteRazorImageIOImplementation()
	{
		disposeImage();
	}

	void disposeImage()
	{
		if (m_bitmap) {
			FreeImage_Unload(m_bitmap);
			m_bitmap = NULL;
		}
	}

	bool loadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		bool result = false;

		strcpy(FreeImageErrorMessage, "");

		FIBITMAP* newImage = FreeImage_Load(FreeImage_GetFileType(imageFileName, 0), imageFileName, TIFF_CMYK);

		if (newImage) {
			result = true;
			disposeImage();

			m_bitmap = newImage;

			m_widthPixels = FreeImage_GetWidth(m_bitmap);
			m_heightPixels = FreeImage_GetHeight(m_bitmap);

			m_horizontalDotsPerMeter = FreeImage_GetDotsPerMeterX(m_bitmap);
			m_verticalDotsPerMeter = FreeImage_GetDotsPerMeterY(m_bitmap);

			if (m_horizontalDotsPerMeter == 0)
				m_horizontalDotsPerMeter = 2835; // 72 dpi
			if (m_verticalDotsPerMeter == 0)
				m_verticalDotsPerMeter = 2835;

			strcpy(m_imageFileName, imageFileName);

			if ((getColorDataType() == eColorTypeRGB && getBitsPerPixel() == 32) // Sometimes, there are strange .PSD images like this (FreeImage bug?)
				|| (getColorDataType() == eColorTypeRGBA)) // We can't export alpha channels to PDF, anyway (yet)
			{
				RGBQUAD white = { 255, 255, 255, 0 };
				FIBITMAP *Image24Bit = FreeImage_Composite(m_bitmap, FALSE, &white);
				FreeImage_Unload(m_bitmap);
				m_bitmap = Image24Bit;
			}
		}

		strncpy(errorMessage, FreeImageErrorMessage, errorMessageSize);
		errorMessage[errorMessageSize-1] = '\0';

		return result;
	}
	bool isImageLoaded() const {return (m_bitmap != NULL);}

	int getWidthPixels() const {return m_widthPixels;}
	int getHeightPixels() const {return m_heightPixels;}

	double getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
	{
		return m_horizontalDotsPerMeter / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthMeter, unit);
	}

	double getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
	{
		return m_verticalDotsPerMeter / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthMeter, unit);
	}

	double getWidth(UnitsOfLength::eUnitsOfLength unit) const {return getWidthPixels() / getHorizontalDotsPerUnitOfLength(unit);}
	double getHeight(UnitsOfLength::eUnitsOfLength unit) const {return getHeightPixels() / getVerticalDotsPerUnitOfLength(unit);}

#define MAX(a, b) ((a)>(b)?(a):(b))

	bool getImageAsRGB(unsigned char *buffer) const
	{
		return getImageAsRGB(buffer, getWidthPixels(), getHeightPixels());
	}

	bool getImageAsRGB(unsigned char *buffer, int width, int height) const
	{
		bool success = true;
	
		FIBITMAP* originalImage = m_bitmap;
		FIBITMAP* temp24BPPImage = NULL;
		FIBITMAP* scaledImage = NULL;
		
		if (getBitsPerPixel() != 24) {
			if (getColorDataType() == eColorTypeCMYK) {
				temp24BPPImage = FreeImage_Allocate(getWidthPixels(), getHeightPixels(), 24);
				const unsigned int scanlinesCount = getHeightPixels();
				const unsigned int columnsCount = getWidthPixels();
				for (unsigned int scanline = 0; scanline < scanlinesCount; scanline++) {
					const BYTE* const cmykBits = FreeImage_GetScanLine(m_bitmap, scanline);
					BYTE* const rgbBits = FreeImage_GetScanLine(temp24BPPImage, scanline);

					for (unsigned int column = 0; column < columnsCount; column++) {
						const unsigned int cmykColumn = column * 4;
						const unsigned int rgbColumn = column * 3;

						const BYTE cyan = cmykBits[cmykColumn];
						const BYTE magenta = cmykBits[cmykColumn + 1];
						const BYTE yellow = cmykBits[cmykColumn + 2];
						const BYTE black = cmykBits[cmykColumn + 3];

						const BYTE red = MAX(0, (255 - (unsigned char)((double)yellow/1.5) - (unsigned char)((double)black/1.5)));
						const BYTE green = MAX(0, (255 - (unsigned char)((double)magenta/1.5) - (unsigned char)((double)black/1.5)));
						const BYTE blue = MAX(0, (255 - (unsigned char)((double)cyan/1.5) - (unsigned char)((double)black/1.5)));

						rgbBits[rgbColumn] = red;
						rgbBits[rgbColumn + 1] = green;
						rgbBits[rgbColumn + 2] = blue;
					}
				}
			} else {
				temp24BPPImage = FreeImage_ConvertTo24Bits(originalImage);
			}
			originalImage = temp24BPPImage;
		}

		if (getWidthPixels() != width || getHeightPixels() != height) {
			scaledImage = FreeImage_Rescale(originalImage, width, height, FILTER_BOX);
			originalImage = scaledImage;
		}

		FreeImage_ConvertToRawBits(buffer, originalImage, width*3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, hasFreeImageVersionCorrectTopDownInConvertBits());

		// Swapping RGB data if needed (like on Intel)
		if (isSystemLittleEndian()) {
			const unsigned int numberOfPixels = width * height;

			for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++) {
				unsigned char* pixelPtr = buffer + pixelIndex*3;

				const unsigned char temp = pixelPtr[0];
				pixelPtr[0] = pixelPtr[2];
				pixelPtr[2] = temp;
				pixelPtr+=3;
			}
		}

		if (temp24BPPImage)
			FreeImage_Unload(temp24BPPImage);

		if (scaledImage)
			FreeImage_Unload(scaledImage);

		return success;
	}
	
	int getBitsPerPixel() const
	{
		return FreeImage_GetBPP(m_bitmap);
	}
	
	eColorTypes getColorDataType() const
	{
		eColorTypes colorDatatype = eColorTypeRGB;
		const FREE_IMAGE_COLOR_TYPE imageColorType = FreeImage_GetColorType(m_bitmap);
		
		if (imageColorType == FIC_MINISBLACK || imageColorType == FIC_MINISWHITE) {
			colorDatatype = getBitsPerPixel()==1?eColorTypeMonochrome:eColorTypeGreyscale;
		} else {
			colorDatatype =
				imageColorType==FIC_PALETTE?eColorTypePalette:
				imageColorType==FIC_RGB?eColorTypeRGB:
				imageColorType==FIC_RGBALPHA?eColorTypeRGBA:
				/*imageColorType==FIC_CMYK?*/eColorTypeCMYK;
		}
		
		return colorDatatype;
	}

	int savePoster(const char *fileName, ImageIOTypes::eImageFormats /* format */, const PainterInterface *painter, int pagesCount, double widthCm, double heightCm) const
	{
		int err = 0;

		const unsigned int imageBytesCount = PosteRazorPDFOutput::getImageBytesCount(getWidthPixels(), getHeightPixels(), getBitsPerPixel());
		unsigned char *imageData = new unsigned char[imageBytesCount];

		const unsigned int bytesPerLineCount = PosteRazorPDFOutput::getImageBytesPerLineCount(getWidthPixels(), getBitsPerPixel());

		FreeImage_ConvertToRawBits(imageData, m_bitmap, bytesPerLineCount, getBitsPerPixel(), FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, hasFreeImageVersionCorrectTopDownInConvertBits());

		// Swapping RGB data if needed (like on Intel)
		if (getBitsPerPixel() == 24 && isSystemLittleEndian()) {
			const unsigned long numberOfPixels = getWidthPixels() * getHeightPixels();
			for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++) {
				unsigned char *pixelPtr = imageData + pixelIndex*3;

				const unsigned char temp = pixelPtr[0];
				pixelPtr[0] = pixelPtr[2];
				pixelPtr[2] = temp;
				pixelPtr+=3;
			}
		}

		const RGBQUAD* const palette = FreeImage_GetPalette(m_bitmap);
		unsigned char rgbPalette[768];

		// Compacting the palette
		if (palette) {
			const int count = FreeImage_GetColorsUsed(m_bitmap);
			for (int i = 0; i < count; i++) {
				const int offset = i*3;
				rgbPalette[offset] = palette[i].rgbRed;
				rgbPalette[offset + 1] = palette[i].rgbGreen;
				rgbPalette[offset + 2] = palette[i].rgbBlue;
			}
		}

		PosteRazorPDFOutput *pdfOutput = PosteRazorPDFOutput::createPosteRazorPDFOutput();
		err = pdfOutput->startSaving(fileName, pagesCount, widthCm, heightCm);
		if (!err) {
			if (FreeImage_GetFileType(m_imageFileName, 0) == FIF_JPEG)
				err = pdfOutput->saveImage(m_imageFileName, getWidthPixels(), getHeightPixels(), getColorDataType());
			else
				err = pdfOutput->saveImage(imageData, getWidthPixels(), getHeightPixels(), getBitsPerPixel(), getColorDataType(), rgbPalette, FreeImage_GetColorsUsed(m_bitmap));
		}

		if (!err) {
			for (int page = 0; page < pagesCount; page++) {
				char paintOptions[1024];
				sprintf(paintOptions, "posterpage %d", page);
				pdfOutput->startPage();
				painter->paintOnCanvas(pdfOutput, paintOptions);
				pdfOutput->finishPage();
			}
			err = pdfOutput->finishSaving();
		}

		delete pdfOutput;

		if (imageData)
			delete[] imageData;

		return err;
	}
};

PosteRazorImageIO* PosteRazorImageIO::createPosteRazorImageIO()
{
	return (PosteRazorImageIO*) new PosteRazorImageIOImplementation();
}
