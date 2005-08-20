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

		FIBITMAP* newImage = FreeImage_Load(FreeImage_GetFileType(imageFileName, 0), imageFileName);

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
	double GetHeight(enum DistanceUnits::eDistanceUnits unit) {return GetHeightPixels() / GetHorizontalDotsPerDistanceUnit(unit);}

	void GetImageAsRGB(unsigned char* buffer, int &widthPixels, int &heightPixels)
	{
		FIBITMAP* originalImage = m_bitmap;
		FIBITMAP* temp24BPPImage = NULL;
		
		if (FreeImage_GetBPP(m_bitmap) != 24)
		{
			temp24BPPImage = FreeImage_ConvertTo24Bits(originalImage);
			originalImage = temp24BPPImage;
		}
		
		unsigned long numberOfPixels = m_widthPixels * m_heightPixels;

		buffer = new unsigned char[numberOfPixels * 3];
		FreeImage_ConvertToRawBits(buffer, originalImage, m_widthPixels*3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);

		widthPixels = m_widthPixels;
		heightPixels = m_heightPixels;

#ifdef _WIN32
		for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++)
		{
			unsigned char *pixelPtr = buffer[numberOfPixels*3];

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
};

PosteRazorImageIO* PosteRazorImageIO::CreatePosteRazorImageIO(void)
{
	return (PosteRazorImageIO*) new PosteRazorImageIOImplementation();
}