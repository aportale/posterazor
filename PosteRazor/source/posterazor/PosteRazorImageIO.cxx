/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
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
#include "DistanceUnits.h"
#include <stdio.h>
#include <string.h>

static char FreeImageErrorMessage[1024];
void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message)
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

public:
	PosteRazorImageIOImplementation()
	{
		m_bitmap = NULL;

		m_widthPixels = 0;
		m_heightPixels = 0;

		m_horizontalDotsPerMeter = 0;
		m_verticalDotsPerMeter = 0;

		m_imageFileName[0] = '\0';
	}

	~PosteRazorImageIOImplementation()
	{
		DisposeImage();
	}

	void DisposeImage()
	{
		if (m_bitmap)
		{
			FreeImage_Unload(m_bitmap);
			m_bitmap = NULL;
		}
	}

	bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		bool result = false;

		strcpy(FreeImageErrorMessage, "");

		FIBITMAP* newImage = FreeImage_Load(FreeImage_GetFileType(imageFileName, 0), imageFileName, TIFF_CMYK);

		if (newImage)
		{
			result = true;
			DisposeImage();

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

			if (GetColorDataType() == eColorTypeRGBA) // We can't export alpha channels to PDF, anyway (yet)
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
	bool IsImageLoaded(void) const {return (m_bitmap != NULL);}

	int GetWidthPixels(void) const {return m_widthPixels;}
	int GetHeightPixels(void) const {return m_heightPixels;}

	double GetHorizontalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) const
	{
		return m_horizontalDotsPerMeter / DistanceUnits::ConvertBetweenDistanceUnits(1, DistanceUnits::eDistanceUnitMeter, unit);
	}

	double GetVerticalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) const
	{
		return m_verticalDotsPerMeter / DistanceUnits::ConvertBetweenDistanceUnits(1, DistanceUnits::eDistanceUnitMeter, unit);
	}

	double GetWidth(enum DistanceUnits::eDistanceUnits unit) const {return GetWidthPixels() / GetHorizontalDotsPerDistanceUnit(unit);}
	double GetHeight(enum DistanceUnits::eDistanceUnits unit) const {return GetHeightPixels() / GetVerticalDotsPerDistanceUnit(unit);}

#define MAX(a, b) ((a)>(b)?(a):(b))

	void GetImageAsRGB(unsigned char *buffer) const
	{
		GetImageAsRGB(buffer, GetWidthPixels(), GetHeightPixels());
	}

	void GetImageAsRGB(unsigned char *buffer, int width, int height) const
	{
		FIBITMAP* originalImage = m_bitmap;
		FIBITMAP* temp24BPPImage = NULL;
		FIBITMAP* scaledImage = NULL;
		
		if (GetBitsPerPixel() != 24)
		{
			if (GetColorDataType() == eColorTypeCMYK)
			{
				temp24BPPImage = FreeImage_Allocate(GetWidthPixels(), GetHeightPixels(), 24);
				unsigned int scanlinesCount = GetHeightPixels();
				unsigned int columnsCount = GetWidthPixels();
				for (unsigned int scanline = 0; scanline < scanlinesCount; scanline++)
				{
					BYTE *cmykBits = FreeImage_GetScanLine(m_bitmap, scanline);
					BYTE *rgbBits = FreeImage_GetScanLine(temp24BPPImage, scanline);
					for (unsigned int column = 0; column < columnsCount; column++)
					{
						unsigned int cmykColumn = column * 4;
						unsigned int rgbColumn = column * 3;

						BYTE cyan = cmykBits[cmykColumn];
						BYTE magenta = cmykBits[cmykColumn + 1];
						BYTE yellow = cmykBits[cmykColumn + 2];
						BYTE black = cmykBits[cmykColumn + 3];

						BYTE red = MAX(0, (255 - (unsigned char)((double)yellow/1.5) - (unsigned char)((double)black/1.5)));
						BYTE green = MAX(0, (255 - (unsigned char)((double)magenta/1.5) - (unsigned char)((double)black/1.5)));
						BYTE blue = MAX(0, (255 - (unsigned char)((double)cyan/1.5) - (unsigned char)((double)black/1.5)));

						rgbBits[rgbColumn] = red;
						rgbBits[rgbColumn + 1] = green;
						rgbBits[rgbColumn + 2] = blue;
					}
				}
			}
			else
			{
				temp24BPPImage = FreeImage_ConvertTo24Bits(originalImage);
			}
			originalImage = temp24BPPImage;
		}

		if (GetWidthPixels() != width || GetHeightPixels() != height)
		{
			scaledImage = FreeImage_Rescale(originalImage, width, height, FILTER_BOX);
			originalImage = scaledImage;
		}

		FreeImage_ConvertToRawBits(buffer, originalImage, width*3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

#ifdef _WIN32
		unsigned int numberOfPixels = width * height;

		for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++)
		{
			unsigned char *pixelPtr = buffer + pixelIndex*3;

			unsigned char temp = pixelPtr[0];
			pixelPtr[0] = pixelPtr[2];
			pixelPtr[2] = temp;
			pixelPtr+=3;
		}
#endif

		if (temp24BPPImage)
			FreeImage_Unload(temp24BPPImage);

		if (scaledImage)
			FreeImage_Unload(scaledImage);
	}
	
	int GetBitsPerPixel(void) const
	{
		return FreeImage_GetBPP(m_bitmap);
	}
	
	enum eColorTypes GetColorDataType(void) const
	{
		enum eColorTypes colorDatatype = eColorTypeRGB;
		FREE_IMAGE_COLOR_TYPE imageColorType = FreeImage_GetColorType(m_bitmap);
		
		if (imageColorType == FIC_MINISBLACK || imageColorType == FIC_MINISWHITE)
		{
			colorDatatype = GetBitsPerPixel()==1?eColorTypeMonochrome:eColorTypeGreyscale;
		}
		else
		{
			colorDatatype =
				imageColorType==FIC_PALETTE?eColorTypePalette:
				imageColorType==FIC_RGB?eColorTypeRGB:
				imageColorType==FIC_RGBALPHA?eColorTypeRGBA:
				/*imageColorType==FIC_CMYK?*/eColorTypeCMYK;
		}
		
		return colorDatatype;
	}

	int SavePoster(const char *fileName, enum ImageIOTypes::eImageFormats format, const PainterInterface *painter, int pagesCount, double widthCm, double heightCm) const
	{
		int err = 0;

		unsigned int imageBytesCount = PosteRazorPDFOutput::GetImageBytesCount(GetWidthPixels(), GetHeightPixels(), GetBitsPerPixel());
		unsigned char *imageData = new unsigned char[imageBytesCount];

		unsigned int bytesPerLineCount = PosteRazorPDFOutput::GetImageBytesPerLineCount(GetWidthPixels(), GetBitsPerPixel());

		FreeImage_ConvertToRawBits(imageData, m_bitmap, bytesPerLineCount, GetBitsPerPixel(), FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

#ifdef _WIN32
		unsigned long numberOfPixels = GetWidthPixels() * GetHeightPixels();
		
		if (GetBitsPerPixel() == 24)
			for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++)
			{
				unsigned char *pixelPtr = imageData + pixelIndex*3;

				unsigned char temp = pixelPtr[0];
				pixelPtr[0] = pixelPtr[2];
				pixelPtr[2] = temp;
				pixelPtr+=3;
			}
#endif

		RGBQUAD *palette = FreeImage_GetPalette(m_bitmap);
		unsigned char rgbPalette[768];
		if (palette) // Compacting the palette
		{
			int count = FreeImage_GetColorsUsed(m_bitmap);
			for (int i = 0; i < count; i++)
			{
				int offset = i*3;
				rgbPalette[offset] = palette[i].rgbRed;
				rgbPalette[offset + 1] = palette[i].rgbGreen;
				rgbPalette[offset + 2] = palette[i].rgbBlue;
			}
		}

		PosteRazorPDFOutput *pdfOutput = PosteRazorPDFOutput::CreatePosteRazorPDFOutput();
		err = pdfOutput->StartSaving(fileName, pagesCount, widthCm, heightCm);
		if (!err)
		{
			if (FreeImage_GetFileType(m_imageFileName, 0) == FIF_JPEG)
				err = pdfOutput->SaveImage(m_imageFileName, GetWidthPixels(), GetHeightPixels(), GetColorDataType());
			else
				err = pdfOutput->SaveImage(imageData, GetWidthPixels(), GetHeightPixels(), GetBitsPerPixel(), GetColorDataType(), rgbPalette, FreeImage_GetColorsUsed(m_bitmap));
		}

		if (!err)
		{
			for (int page = 0; page < pagesCount; page++)
			{
				char paintOptions[1024];
				sprintf(paintOptions, "posterpage %d", page);
				pdfOutput->StartPage();
				painter->PaintOnCanvas(pdfOutput, paintOptions);
				pdfOutput->FinishPage();
			}
			err = pdfOutput->FinishSaving();
		}

		delete pdfOutput;

		if (imageData)
			delete[] imageData;

		return err;
	}
};

PosteRazorImageIO* PosteRazorImageIO::CreatePosteRazorImageIO(void)
{
	return (PosteRazorImageIO*) new PosteRazorImageIOImplementation();
}