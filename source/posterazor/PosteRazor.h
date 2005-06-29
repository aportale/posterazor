#ifndef PosteRazor_h
#define PosteRazor_h

#include "..\tools\PaperFormats.h"

class PosteRazor: public PaperFormats
{
public:
	typedef enum eBorderPositions
	{
		eBorderPositionTopRight,
		eBorderPositionRightBottom,
		eBorderPositionBottomLeft,
		eBorderPositionLeftTop
	};

	typedef enum ePosterSizeModes
	{
		ePosterSizeModeAbsolute,
		ePosterSizeModePercentual,
		ePosterSizeModePages
	};

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
	
	virtual void SetPreserveAspectRatio(bool preserveIt) = 0;
	virtual bool GetPreserveAspectRatio(void) = 0;

	virtual void SetPosterWidth(enum ePosterSizeModes mode, double width) = 0;
	virtual void SetPosterHeight(enum ePosterSizeModes mode, double height) = 0;
	virtual double GetPosterWidth(enum ePosterSizeModes mode) = 0;
	virtual double GetPosterHeight(enum ePosterSizeModes mode) = 0;
	virtual enum ePosterSizeModes GetPosterSizeMode(void) = 0;
};

#endif