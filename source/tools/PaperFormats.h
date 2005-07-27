#ifndef PaperFormats_h
#define PaperFormats_h

#include "DistanceUnits.h"

class PaperFormats: public DistanceUnits
{
public:
	typedef enum ePaperFormats
	{
		ePaperFormatA4,
		ePaperFormatA3,
		ePaperFormatLegal,
		ePaperFormatLetter,
		ePaperFormatTabloid
	};

	typedef enum ePaperOrientations
	{
		ePaperOrientationPortrait,
		ePaperOrientationLandscape
	};

	static int GetPaperFormatsCount(void);
	static enum PaperFormats::ePaperFormats GetPaperFormatForIndex(int index);
	static const char* GetPaperFormatName(enum ePaperFormats format);
	static enum ePaperFormats GetPaperFormatForName(const char* name);
	static void GetPaperDimensions(enum ePaperFormats, enum ePaperOrientations, enum eDistanceUnits, double &width, double &height);
	static void GetPrintableArea(enum ePaperFormats, enum ePaperOrientations, enum eDistanceUnits, double borderTop, double borderRight, double borderBottom, double borderLeft, double &width, double &height);
};

#endif