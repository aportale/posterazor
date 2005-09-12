#ifndef PosteRazorImageIO_h
#define PosteRazorImageIO_h

#include "DistanceUnits.h"
#include "ColorTypes.h"
#include "PaintCanvasInterface.h"
#include "ImageIOTypes.h"

class PosteRazorImageIO: public ColorTypes
{
public:
	virtual ~PosteRazorImageIO() {};
	static PosteRazorImageIO* CreatePosteRazorImageIO();

	virtual bool LoadImage(const char *imageFileName, char *errorMessage, int errorMessageSize) = 0;
	virtual bool IsImageLoaded(void) = 0;

	virtual int GetWidthPixels(void) = 0;
	virtual int GetHeightPixels(void) = 0;

	virtual double GetHorizontalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) = 0;
	virtual double GetVerticalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) = 0;

	virtual double GetWidth(enum DistanceUnits::eDistanceUnits unit) = 0;
	virtual double GetHeight(enum DistanceUnits::eDistanceUnits unit) = 0;

	virtual void GetImageAsRGB(unsigned char **buffer, int &widthPixels, int &heightPixels) = 0;
	
	virtual int GetBitsPerPixel(void) = 0;
	virtual enum eColorTypes GetColorDataType(void) = 0;

	virtual int SavePoster(const char *fileName, enum ImageIOTypes::eImageFormats format, const PainterInterface *painter, int pagesCount, double widthCm, double heightCm) = 0;
};

#endif