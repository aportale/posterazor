#include "FreeImage.h"
#include "PosteRazorImageIO.h"
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

class PosteRazorPDFOutput: public PaintCanvasInterface
{
private:
	FILE *m_outputFile;
	char *m_xref;
	int m_pdfObjectCount;
	int m_contentPagesCount;

public:
	PosteRazorPDFOutput()
	{
		m_outputFile = NULL;
		m_pdfObjectCount = 0;
	}

	void AddOffsetToXref(void)
	{
		char xrefLine[25];
		m_pdfObjectCount++;
		sprintf(xrefLine, "%10d %5d n \012", ftell(m_outputFile), m_pdfObjectCount);
	}

	int StartSaving(const char* fileName, int pages)
	{
		int err = 0;
		m_outputFile = fopen(fileName, "wb");
		if (!m_outputFile)
			err = 1;
		if (!err)
		{
			m_contentPagesCount = pages;
			m_xref = new char[m_contentPagesCount * 20 + 100];
			sprintf(m_xref, "\nxref\n0 %d\n0000000000 65535 f \012", 7 + m_contentPagesCount*2);
		}
		return err;
	}

	int SaveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, bool greyscale, bool cmyk, bool lossy, double lossyQuality)
	{
		AddOffsetToXref();
	}

	int FinishSaving()
	{
		int err = 0;
		err = fputs(m_xref, m_outputFile);
		if (m_xref)
			delete[] m_xref;
		fclose(m_outputFile);
		return err;
	}

	void DrawFilledRect(double x, double y, double width, double heigth, unsigned char red, unsigned char green, unsigned char blue) {}
	void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue) {}
	void GetSize(double &width, double &height) {}
	void SetImage(const unsigned char* rgbData, double width, double height) {}
	void DrawImage(double x, double y, double width, double height)
	{
	}
};

class PosteRazorImageIOImplementation: public PosteRazorImageIO
{
private:

	FIBITMAP*    m_bitmap;

	int          m_widthPixels;
	int          m_heightPixels;

	unsigned int m_horizontalDotsPerMeter;
	unsigned int m_verticalDotsPerMeter;

public:
	PosteRazorImageIOImplementation()
	{
		m_bitmap = NULL;

		m_widthPixels = 0;
		m_heightPixels = 0;

		m_horizontalDotsPerMeter = 0;
		m_verticalDotsPerMeter = 0;
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

	bool LoadImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
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
		}

		strncpy(errorMessage, FreeImageErrorMessage, errorMessageSize);
		errorMessage[errorMessageSize-1] = '\0';

		return result;
	}
	bool IsImageLoaded(void) {return (m_bitmap != NULL);}

	int GetWidthPixels(void) {return m_widthPixels;}
	int GetHeightPixels(void) {return m_heightPixels;}

	double GetHorizontalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit)
	{
		return m_horizontalDotsPerMeter / DistanceUnits::ConvertBetweenDistanceUnits(1, DistanceUnits::eDistanceUnitMeter, unit);
	}

	double GetVerticalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit)
	{
		return m_verticalDotsPerMeter / DistanceUnits::ConvertBetweenDistanceUnits(1, DistanceUnits::eDistanceUnitMeter, unit);
	}

	double GetWidth(enum DistanceUnits::eDistanceUnits unit) {return GetWidthPixels() / GetHorizontalDotsPerDistanceUnit(unit);}
	double GetHeight(enum DistanceUnits::eDistanceUnits unit) {return GetHeightPixels() / GetVerticalDotsPerDistanceUnit(unit);}

	void GetImageAsRGB(unsigned char **buffer, int &widthPixels, int &heightPixels)
	{
		FIBITMAP* originalImage = m_bitmap;
		FIBITMAP* temp24BPPImage = NULL;
		
		if (FreeImage_GetBPP(m_bitmap) != 24)
		{
			temp24BPPImage = FreeImage_ConvertTo24Bits(originalImage);
			originalImage = temp24BPPImage;
		}
		
		unsigned long numberOfPixels = m_widthPixels * m_heightPixels;

		*buffer = new unsigned char[numberOfPixels * 3];
		FreeImage_ConvertToRawBits(*buffer, originalImage, m_widthPixels*3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

		widthPixels = m_widthPixels;
		heightPixels = m_heightPixels;

#ifdef _WIN32
		for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++)
		{
			unsigned char *pixelPtr = *buffer + pixelIndex*3;

			unsigned char temp = pixelPtr[0];
			pixelPtr[0] = pixelPtr[2];
			pixelPtr[2] = temp;
			pixelPtr+=3;
		}
#endif

		if (temp24BPPImage)
			FreeImage_Unload(temp24BPPImage);

	}
	
	int GetBitsPerPixel(void)
	{
		return FreeImage_GetBPP(m_bitmap);
	}
	
	enum eColorTypes GetColorDataType(void)
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

	int SavePoster(const char *fileName, enum ImageIOTypes::eImageFormats format, bool lossy, double lossyQuality, const PainterInterface *painter, int pagesCount)
	{
		int err = 0;

		//unsigned char *imageData = new unsigned char[GetWidthPixels() * GetHeightPixels() * (GetBitsPerPixel()/8)];

		PosteRazorPDFOutput pdfOutput;
		pdfOutput.StartSaving(fileName, pagesCount);
		//pdfOutput.SaveImage(
		pdfOutput.FinishSaving();

		return err;
	}
};

PosteRazorImageIO* PosteRazorImageIO::CreatePosteRazorImageIO(void)
{
	return (PosteRazorImageIO*) new PosteRazorImageIOImplementation();
}