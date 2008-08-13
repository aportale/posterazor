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

#ifndef UNITSOFLENGTH_H
#define UNITSOFLENGTH_H

class UnitsOfLength
{
public:
    enum eUnitsOfLength    {
        eUnitOfLengthMeter,
        eUnitOfLengthMillimeter,
        eUnitOfLengthCentimeter,
        eUnitOfLengthInch,
        eUnitOfLengthFeet,
        eUnitOfLengthPoints
    };

    static int getUnitsOfLengthCount();

    static double convertBetweenUnitsOfLength(double distance, eUnitsOfLength sourceUnit, eUnitsOfLength targetUnit);
    static int getUnitOfLengthIndex(eUnitsOfLength unit);
    static const char* getUnitOfLengthName(eUnitsOfLength unit);
    static eUnitsOfLength getUnitOfLengthForName(const char* name);
    static eUnitsOfLength getUnitOfLengthForIndex(int index);
};

#endif // UNITSOFLENGTH_H
