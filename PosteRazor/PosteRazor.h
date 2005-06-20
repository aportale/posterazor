#ifndef PosteRazor_h
#define PosteRazor_h

#include "PaperFormats.h"

class PosteRazor: public PaperFormats
{
public:
	virtual ~PosteRazor() {};
	static PosteRazor* CreatePosteRazor(const char* imgFileName);

	virtual int GetPixelWidth(void) = 0;
	virtual int GetPixelHeight(void) = 0;

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