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

	static double GetPaperDimension(enum ePaperFormats format, enum ePaperOrientations orientation, enum eDistanceUnits unit, bool width);
	static double GetPaperWidth(enum ePaperFormats format, enum ePaperOrientations orientation, enum eDistanceUnits unit);
	static double GetPaperHeight(enum ePaperFormats format, enum ePaperOrientations orientation, enum eDistanceUnits unit);
};

#endif