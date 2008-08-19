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

const QHash<UnitsOfLength::eUnitsOfLength, QPair<QString, double> > &UnitsOfLength::unitsOfLength()
{
    static QHash<eUnitsOfLength, QPair<QString, double> > units;
    if (units.empty()) {
        static const struct
        {
            UnitsOfLength::eUnitsOfLength unit;
            QString name;
            double cm;
        } unitsOfLength[] = {
            {UnitsOfLength::eUnitOfLengthMeter,      QLatin1String("m"),        100.00},
            {UnitsOfLength::eUnitOfLengthMillimeter, QLatin1String("mm"),         0.10},
            {UnitsOfLength::eUnitOfLengthCentimeter, QLatin1String("cm"),         1.00},
            {UnitsOfLength::eUnitOfLengthInch,       QLatin1String("in"),         2.54},
            {UnitsOfLength::eUnitOfLengthFeet,       QLatin1String("ft"), 2.54 * 12.00},
            {UnitsOfLength::eUnitOfLengthPoints,     QLatin1String("pt"), 2.54 / 72.00}
        };
        static const int unitsOfLengthCount = sizeof(unitsOfLength)/sizeof(unitsOfLength[0]);
        for (int i = 0; i < unitsOfLengthCount; i++)
            units.insert(unitsOfLength[i].unit, QPair<QString, double> (unitsOfLength[i].name, unitsOfLength[i].cm));
    }
    return units;
}

double UnitsOfLength::convertBetweenUnitsOfLength(double distance, eUnitsOfLength sourceUnit, eUnitsOfLength targetUnit)
{
    double convertedDistance = distance;
    if (sourceUnit != targetUnit) {
        if (sourceUnit != eUnitOfLengthCentimeter)
            convertedDistance *= UnitsOfLength::unitsOfLength().value(sourceUnit).second;
        if (targetUnit != eUnitOfLengthCentimeter)
            convertedDistance /= UnitsOfLength::unitsOfLength().value(targetUnit).second;
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
