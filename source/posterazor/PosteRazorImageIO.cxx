#include "FreeImage.h"
#include "PosteRazorImageIO.h"
#include "DistanceUnits.h"
#include <stdio.h>

class FreeImageInitializer
{
public:
	FreeImageInitializer()
	{
		FreeImage_Initialise();
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

	FIBITMAP  *m_bitmap;

	int          m_widthPixels;
	int          m_heightPixels;

	unsigned int m_horizontalDotsPerMeter;
	unsigned int m_verticalDotsPerMeter;

public:
	PosteRazorImageIOImplementation(const char* imgFileName)
	{
		m_bitmap = FreeImage_Load(FreeImage_GetFileType(imgFileName, 0), imgFileName);

		m_widthPixels = 0;
		m_heightPixels = 0;

		m_horizontalDotsPerMeter = 0;
		m_verticalDotsPerMeter = 0;


		if (m_bitmap)
		{
			m_widthPixels = FreeImage_GetWidth(m_bitmap);
			m_heightPixels = FreeImage_GetHeight(m_bitmap);

			m_horizontalDotsPerMeter = FreeImage_GetDotsPerMeterX(m_bitmap);
			m_verticalDotsPerMeter = FreeImage_GetDotsPerMeterY(m_bitmap);

			if (m_horizontalDotsPerMeter == 0)
				m_horizontalDotsPerMeter = 2835; // 72 dpi
			if (m_verticalDotsPerMeter == 0)
				m_verticalDotsPerMeter = 2835;
		}
	}

	~PosteRazorImageIOImplementation()
	{
		if (m_bitmap)
			FreeImage_Unload(m_bitmap);
	}

	FIBITMAP *GetBitmap(void) {return m_bitmap;}

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
};

PosteRazorImageIO* PosteRazorImageIO::CreatePosteRazorImageIO(const char* imgFileName)
{
	PosteRazorImageIOImplementation *impl = new PosteRazorImageIOImplementation(imgFileName);

	if (impl && !impl->GetBitmap())
	{
		delete impl;
		impl = 0;
	}

	return (PosteRazorImageIO*)(impl);
}