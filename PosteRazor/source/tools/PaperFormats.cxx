/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PaperFormats.h"
#include <string.h>

typedef struct
{
	enum PaperFormats::ePaperFormats format;
	char *name;
	double width;
	double height;
} paperFormats;

// Needs to have the same order as the ePaperFormats enum!!!
static const paperFormats g_paperFormats[] =
{
	{PaperFormats::ePaperFormatA4, "DIN A4", 21.0, 29.7},
	{PaperFormats::ePaperFormatA3, "DIN A3", 29.7, 42.0},
	{PaperFormats::ePaperFormatLegal, "Legal", 21.6, 35.6},
	{PaperFormats::ePaperFormatLetter, "Letter", 21.6, 27.9},
	{PaperFormats::ePaperFormatTabloid, "Tabloid", 27.9, 43.2}
};

static const int g_paperFormatsCount = sizeof(g_paperFormats)/sizeof(g_paperFormats[0]);

int PaperFormats::GetPaperFormatsCount(void)
{
	return g_paperFormatsCount;
}

enum PaperFormats::ePaperFormats PaperFormats::GetPaperFormatForIndex(int index)
{
	return g_paperFormats[index].format;
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
			paperFormat = GetPaperFormatForIndex(i);
			break;
		}
	}

	return paperFormat;
}

double PaperFormats::GetPaperDimension(enum ePaperFormats format, enum ePaperOrientations orientation, enum eUnitsOfLength unit, bool width)
{
	int paperFormatIndex = GetPaperFormatIndex(format);
	double dimension = ((width && orientation == ePaperOrientationPortrait) || (!width && orientation == ePaperOrientationLandscape))?g_paperFormats[paperFormatIndex].width:g_paperFormats[paperFormatIndex].height;
	return ConvertBetweenUnitsOfLength(dimension, eUnitOfLengthCentimeter, unit);
}

double PaperFormats::GetPaperWidth(enum ePaperFormats format, enum ePaperOrientations orientation, enum eUnitsOfLength unit)
{
	return GetPaperDimension(format, orientation, unit, true);
}

double PaperFormats::GetPaperHeight(enum ePaperFormats format, enum ePaperOrientations orientation, enum eUnitsOfLength unit)
{
	return GetPaperDimension(format, orientation, unit, false);
}
