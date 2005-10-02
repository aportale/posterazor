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