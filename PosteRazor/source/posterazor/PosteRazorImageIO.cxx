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
	FIBITMAP*    m_previewBitmap;

	int          m_widthPixels;
	int          m_heightPixels;

	unsigned int m_horizontalDotsPerMeter;
	unsigned int m_verticalDotsPerMeter;

public:
	PosteRazorImageIOImplementation()
	{
		m_bitmap = NULL;
		m_previewBitmap = NULL;

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
		if (m_previewBitmap)
		{
			FreeImage_Unload(m_previewBitmap);
			m_previewBitmap = NULL;
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

	void GetPreview(unsigned char* buffer, int pixelWidth, int pixelHeight)
	{
		if (!m_previewBitmap || pixelWidth != FreeImage_GetWidth(m_previewBitmap) || pixelHeight != FreeImage_GetHeight(m_previewBitmap))
		{
			FIBITMAP* originalImage = m_bitmap;
			FIBITMAP* temp24BPPImage = NULL;

			if (FreeImage_GetBPP(m_bitmap) != 24)
			{
				temp24BPPImage = FreeImage_ConvertTo24Bits(originalImage);
				originalImage = temp24BPPImage;
			}

			if (m_previewBitmap)
				FreeImage_Unload(m_previewBitmap);

			m_previewBitmap = FreeImage_Rescale(originalImage, pixelWidth, pixelHeight, FILTER_BILINEAR);

			for (unsigned int row = 0; row < pixelHeight; row++)
			{
				unsigned char *pixelPtr = FreeImage_GetScanLine(m_previewBitmap, row);

				for (unsigned int column = 0; column < pixelWidth; column++)
				{
					unsigned char temp = pixelPtr[0];
					pixelPtr[0] = pixelPtr[2];
					pixelPtr[2] = temp;
					pixelPtr+=3;
				}
			}
			

			if (temp24BPPImage)
				FreeImage_Unload(temp24BPPImage);
		}

		FreeImage_ConvertToRawBits(buffer, m_previewBitmap, pixelWidth*3, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);
	}
};

PosteRazorImageIO* PosteRazorImageIO::CreatePosteRazorImageIO(void)
{
	return (PosteRazorImageIO*) new PosteRazorImageIOImplementation();
}