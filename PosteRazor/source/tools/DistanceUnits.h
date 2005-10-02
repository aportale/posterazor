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

#ifndef DistanceUnits_h
#define DistanceUnits_h

class DistanceUnits
{
public:
	typedef enum eDistanceUnits
	{
		eDistanceUnitMeter,
		eDistanceUnitMillimeter,
		eDistanceUnitCentimeter,
		eDistanceUnitInch,
		eDistanceUnitFeet,
		eDistanceUnitPoints
	};

	static int GetDistanceUnitsCount(void);

	static double ConvertBetweenDistanceUnits(double distance, enum eDistanceUnits sourceUnit, enum eDistanceUnits targetUnit);
	static int GetDistanceUnitIndex(enum eDistanceUnits unit);
	static const char* GetDistanceUnitName(enum eDistanceUnits unit);
	static enum eDistanceUnits GetDistanceUnitForName(const char* name);
	static enum eDistanceUnits GetDistanceUnitForIndex(int index);
};

#endif