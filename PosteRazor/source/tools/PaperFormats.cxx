#include "PaperFormats.h"
#include <string.h>

typedef struct
{
	enum PaperFormats::ePaperFormats format;
	char *name;
	double width;
	double height;
} paperFormats;

static const paperFormats g_paperFormats[] =
{
	{PaperFormats::ePaperFormatA4, "DIN A4", 210, 297},
	{PaperFormats::ePaperFormatA3, "DIN A3", 297, 420},
	{PaperFormats::ePaperFormatLegal, "Legal", 216, 356},
	{PaperFormats::ePaperFormatLetter, "Letter", 216, 279},
	{PaperFormats::ePaperFormatTabloid, "Tabloid", 279, 432}
};

static const g_paperFormatsCount = sizeof(g_paperFormats)/sizeof(g_paperFormats[0]);

int PaperFormats::GetPaperFormatsCount(void)
{
	return g_paperFormatsCount;
}

const int GetPaperFormatIndex(enum PaperFormats::ePaperFormats format)
{
	int index = 0;

	for (int i = 0; i < g_paperFormatsCount; i++)
	{
		if (format == g_paperFormats[i].format)
		{
			index = i;
			break;
		}
	}

	return index;
}

const char* PaperFormats::GetPaperFormatName(enum ePaperFormats format)
{
	int paperFormatIndex = GetPaperFormatIndex(format);

	return g_paperFormats[paperFormatIndex].name;
}

enum PaperFormats::ePaperFormats PaperFormats::GetPaperFormatForName(const char* name)
{
	enum ePaperFormats paperFormat = ePaperFormatA4;

	for (int i = 0; i < g_paperFormatsCount; i++)
	{
		if (0 == strcmp(name, g_paperFormats[i].name))
		{
			paperFormat = g_paperFormats[i].format;
			break;
		}
	}

	return paperFormat;
}

void PaperFormats::GetPaperDimensions(enum ePaperFormats format, enum ePaperOrientations orientation, enum eDistanceUnits unit, double &width, double &height)
{
	int paperFormatIndex = GetPaperFormatIndex(format);

	width = ConvertBetweenDistanceUnits(g_paperFormats[paperFormatIndex].width, unit, eDistanceUnitCentimeter);
	height = ConvertBetweenDistanceUnits(g_paperFormats[paperFormatIndex].height, unit, eDistanceUnitCentimeter);

	if (orientation == ePaperOrientationLandscape)
	{
		double temp = width;
		width = height;
		height = temp;
	}
}

void PaperFormats::GetPrintableArea(enum ePaperFormats format, enum ePaperOrientations orientation, enum eDistanceUnits unit, double borderTop, double borderRight, double borderBottom, double borderLeft, double &width, double &height)
{
	GetPaperDimensions(format, orientation, unit, width, height);
	width -= (borderLeft + borderRight);
	height -= (borderTop + borderBottom);
}
