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

const QHash<QString, QSizeF> &PaperFormats::paperFormats()
{
    static QHash<QString, QSizeF> formats;
    if (formats.empty()) {
        static const struct {
            QString name;
            double width;
            double height;
        } paperFormats[] = {
            {QLatin1String("DIN A4"),    21.0, 29.7},
            {QLatin1String("DIN A3"),    29.7, 42.0},
            {QLatin1String("Legal"),     21.6, 35.6},
            {QLatin1String("Letter"),    21.6, 27.9},
            {QLatin1String("Tabloid"),   27.9, 43.2}
        };
        static const int paperFormatsCount = (int)sizeof(paperFormats)/sizeof(paperFormats[0]);
        for (int i = 0; i < paperFormatsCount; i++)
            formats.insert(paperFormats[i].name, QSizeF(paperFormats[i].width, paperFormats[i].height));
    }
    return formats;
}

QSizeF PaperFormats::getPaperSize(const QString &format, QPrinter::Orientation orientation, UnitsOfLength::eUnitsOfLength unit)
{
    QSizeF result = paperFormats().value(format);
    if (orientation == QPrinter::Landscape)
        result.transpose();
    return UnitsOfLength::convertBetweenUnitsOfLength(result, UnitsOfLength::eUnitOfLengthCentimeter, unit);
}
