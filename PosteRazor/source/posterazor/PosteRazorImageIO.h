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
	virtual bool IsImageLoaded(void) const = 0;

	virtual int GetWidthPixels(void) const = 0;
	virtual int GetHeightPixels(void) const = 0;

	virtual double GetHorizontalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) const = 0;
	virtual double GetVerticalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) const = 0;

	virtual double GetWidth(enum DistanceUnits::eDistanceUnits unit) const = 0;
	virtual double GetHeight(enum DistanceUnits::eDistanceUnits unit) const = 0;

	virtual void GetImageAsRGB(unsigned char **buffer, int &widthPixels, int &heightPixels) const = 0;
	
	virtual int GetBitsPerPixel(void) const = 0;
	virtual enum eColorTypes GetColorDataType(void) const = 0;

	virtual int SavePoster(const char *fileName, enum ImageIOTypes::eImageFormats format, const PainterInterface *painter, int pagesCount, double widthCm, double heightCm) const = 0;
};

#endif