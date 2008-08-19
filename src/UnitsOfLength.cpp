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

#include "UnitsOfLength.h"
#include <string.h>

typedef struct
{
    UnitsOfLength::eUnitsOfLength unit;
    char *name;
    double multipleOfCentimeter;
} UnitsOfLengthStruct;

// Needs to have the same order as the eUnitsOfLength enum!!!
static const UnitsOfLengthStruct g_UnitsOfLength[] =
{
    {UnitsOfLength::eUnitOfLengthMeter, "m", 100},
    {UnitsOfLength::eUnitOfLengthMillimeter, "mm", 0.1},
    {UnitsOfLength::eUnitOfLengthCentimeter, "cm", 1.0},
    {UnitsOfLength::eUnitOfLengthInch, "in", 2.54},
    {UnitsOfLength::eUnitOfLengthFeet, "ft", 2.54 * 12.0},
    {UnitsOfLength::eUnitOfLengthPoints, "pt", 2.54 / 72.0}
};

static const int g_UnitsOfLengthCount = sizeof(g_UnitsOfLength)/sizeof(g_UnitsOfLength[0]);

int UnitsOfLength::getUnitsOfLengthCount()
{
    return g_UnitsOfLengthCount;
}

UnitsOfLength::eUnitsOfLength UnitsOfLength::getUnitOfLengthForIndex(int index)
{
    return g_UnitsOfLength[index].unit;
}

int UnitsOfLength::getUnitOfLengthIndex(eUnitsOfLength unit)
{
    int index = 0;

    for (int i = 0; i < g_UnitsOfLengthCount; i++) {
        if (unit == g_UnitsOfLength[i].unit) {
            index = i;
            break;
        }
    }

    return index;
}

const char* UnitsOfLength::getUnitOfLengthName(eUnitsOfLength unit)
{
    const int UnitOfLengthIndex = getUnitOfLengthIndex(unit);

    return g_UnitsOfLength[UnitOfLengthIndex].name;
}

UnitsOfLength::eUnitsOfLength UnitsOfLength::getUnitOfLengthForName(const char* name)
{
    eUnitsOfLength unitOfLength = eUnitOfLengthCentimeter;

    for (int i = 0; i < g_UnitsOfLengthCount; i++) {
        if (0 == strcmp(name, g_UnitsOfLength[i].name)) {
            unitOfLength = g_UnitsOfLength[i].unit;
            break;
        }
    }

    return unitOfLength;
}

double CentimeterToUnitOfLength(double cm, UnitsOfLength::eUnitsOfLength unit)
{
    cm /= g_UnitsOfLength[UnitsOfLength::getUnitOfLengthIndex(unit)].multipleOfCentimeter;
    return cm;
}

double UnitOfLengthToCentimeter(double distance, UnitsOfLength::eUnitsOfLength unit)
{
    distance *= g_UnitsOfLength[UnitsOfLength::getUnitOfLengthIndex(unit)].multipleOfCentimeter;
    return distance;
}

double UnitsOfLength::convertBetweenUnitsOfLength(double distance, eUnitsOfLength sourceUnit, eUnitsOfLength targetUnit)
{
    double convertedDistance = distance;

    if (sourceUnit != targetUnit) {
        if (sourceUnit != eUnitOfLengthCentimeter)
            convertedDistance = UnitOfLengthToCentimeter(convertedDistance, sourceUnit);

        if (targetUnit != eUnitOfLengthCentimeter)
            convertedDistance = CentimeterToUnitOfLength(convertedDistance, targetUnit);
    }

    return convertedDistance;
}

QSizeF UnitsOfLength::convertBetweenUnitsOfLength(const QSizeF &size, eUnitsOfLength sourceUnit, eUnitsOfLength targetUnit)
{
    return QSizeF(
        convertBetweenUnitsOfLength(size.width(), sourceUnit, targetUnit),
        convertBetweenUnitsOfLength(size.height(), sourceUnit, targetUnit)
    );
}
