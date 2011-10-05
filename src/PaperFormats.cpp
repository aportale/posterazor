/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
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
	PaperFormats::ePaperFormats format;
	const char *name;
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

int PaperFormats::getPaperFormatsCount(void)
{
	return g_paperFormatsCount;
}

PaperFormats::ePaperFormats PaperFormats::getPaperFormatForIndex(int index)
{
	return g_paperFormats[index].format;
}

const int GetPaperFormatIndex(PaperFormats::ePaperFormats format)
{
	int index = 0;

	for (int i = 0; i < g_paperFormatsCount; i++) {
		if (format == g_paperFormats[i].format) {
			index = i;
			break;
		}
	}

	return index;
}

const char* PaperFormats::getPaperFormatName(ePaperFormats format)
{
	const int paperFormatIndex = GetPaperFormatIndex(format);
	return g_paperFormats[paperFormatIndex].name;
}

PaperFormats::ePaperFormats PaperFormats::getPaperFormatForName(const char* name)
{
	ePaperFormats paperFormat = ePaperFormatA4;

	for (int i = 0; i < g_paperFormatsCount; i++) {
		if (0 == strcmp(name, g_paperFormats[i].name)) {
			paperFormat = getPaperFormatForIndex(i);
			break;
		}
	}

	return paperFormat;
}

double PaperFormats::getPaperDimension(ePaperFormats format, ePaperOrientations orientation, UnitsOfLength::eUnitsOfLength unit, bool width)
{
	const int paperFormatIndex = GetPaperFormatIndex(format);
	const double dimension = ((width && orientation == ePaperOrientationPortrait) || (!width && orientation == ePaperOrientationLandscape))?g_paperFormats[paperFormatIndex].width:g_paperFormats[paperFormatIndex].height;
	return UnitsOfLength::convertBetweenUnitsOfLength(dimension, UnitsOfLength::eUnitOfLengthCentimeter, unit);
}

double PaperFormats::getPaperWidth(ePaperFormats format, ePaperOrientations orientation, UnitsOfLength::eUnitsOfLength unit)
{
	return getPaperDimension(format, orientation, unit, true);
}

double PaperFormats::getPaperHeight(ePaperFormats format, ePaperOrientations orientation, UnitsOfLength::eUnitsOfLength unit)
{
	return getPaperDimension(format, orientation, unit, false);
}
