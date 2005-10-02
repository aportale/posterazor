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

#include "DistanceUnits.h"
#include <string.h>

typedef struct
{
	enum DistanceUnits::eDistanceUnits unit;
	char *name;
	double multipleOfCentimeter;
} distanceUnits;

// Needs to have the same order as the eDistanceUnits enum!!!
static const distanceUnits g_distanceUnits[] =
{
	{DistanceUnits::eDistanceUnitMeter, "m", 100},
	{DistanceUnits::eDistanceUnitMillimeter, "mm", 0.1},
	{DistanceUnits::eDistanceUnitCentimeter, "cm", 1.0},
	{DistanceUnits::eDistanceUnitInch, "inch", 2.54},
	{DistanceUnits::eDistanceUnitFeet, "feet", 2.54 * 12.0},
	{DistanceUnits::eDistanceUnitPoints, "points", 2.54 / 72.0}
};

static const int g_distanceUnitsCount = sizeof(g_distanceUnits)/sizeof(g_distanceUnits[0]);

int DistanceUnits::GetDistanceUnitsCount(void)
{
	return g_distanceUnitsCount;
}

enum DistanceUnits::eDistanceUnits DistanceUnits::GetDistanceUnitForIndex(int index)
{
	return g_distanceUnits[index].unit;
}

int DistanceUnits::GetDistanceUnitIndex(enum eDistanceUnits unit)
{
	int index = 0;

	for (int i = 0; i < g_distanceUnitsCount; i++)
	{
		if (unit == g_distanceUnits[i].unit)
		{
			index = i;
			break;
		}
	}

	return index;
}

const char* DistanceUnits::GetDistanceUnitName(enum eDistanceUnits unit)
{
	int distanceUnitIndex = GetDistanceUnitIndex(unit);

	return g_distanceUnits[distanceUnitIndex].name;
}

enum DistanceUnits::eDistanceUnits DistanceUnits::GetDistanceUnitForName(const char* name)
{
	enum eDistanceUnits distanceUnit = eDistanceUnitCentimeter;

	for (int i = 0; i < g_distanceUnitsCount; i++)
	{
		if (0 == strcmp(name, g_distanceUnits[i].name))
		{
			distanceUnit = g_distanceUnits[i].unit;
			break;
		}
	}

	return distanceUnit;
}

double CentimeterToDistanceUnit(double cm, enum DistanceUnits::eDistanceUnits unit)
{
	cm /= g_distanceUnits[DistanceUnits::GetDistanceUnitIndex(unit)].multipleOfCentimeter;
	return cm;
}

double DistanceUnitToCentimeter(double distance, enum DistanceUnits::eDistanceUnits unit)
{
	distance *= g_distanceUnits[DistanceUnits::GetDistanceUnitIndex(unit)].multipleOfCentimeter;
	return distance;
}

double DistanceUnits::ConvertBetweenDistanceUnits(double distance, enum eDistanceUnits sourceUnit, enum eDistanceUnits targetUnit)
{
	double convertedDistance = distance;

	if (sourceUnit != targetUnit)
	{
		if (sourceUnit != eDistanceUnitCentimeter)
			convertedDistance = DistanceUnitToCentimeter(convertedDistance, sourceUnit);

		if (targetUnit != eDistanceUnitCentimeter)
			convertedDistance = CentimeterToDistanceUnit(convertedDistance, targetUnit);
	}

	return convertedDistance;
}
