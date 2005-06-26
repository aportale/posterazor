#ifndef PosteRazor_h
#define PosteRazor_h

#include "..\tools\PaperFormats.h"

class PosteRazor: public PaperFormats
{
public:
	virtual ~PosteRazor() {};
	static PosteRazor* CreatePosteRazor(const char* imgFileName);

	virtual int GetInputImageWidthPixels(void) = 0;
	virtual int GetInputImageHeightPixels(void) = 0;

	virtual double GetInputImageHorizontalDpi(void) = 0;
	virtual double GetInputImageVerticalDpi(void) = 0;

	virtual double GetInputImageWidth(void) = 0;
	virtual double GetInputImageHeight(void) = 0;

	virtual void SetDistanceUnit(enum eDistanceUnits unit) = 0;
	virtual enum eDistanceUnits GetDistanceUnit(void) = 0;

	virtual void SetPaperFormatAndBorders(enum ePaperFormats, enum ePaperOrientations, double borderTop, double borderRight, double borderBottom, double borderLeft) = 0;
	

	typedef enum eBorderPositions
	{
		eBorderPositionTopRight,
		eBorderPositionRightBottom,
		eBorderPositionBottomLeft,
		eBorderPositionLeftTop
	};
};

#endif