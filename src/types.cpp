/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2018 by Alessandro Portale
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

#include "types.h"

#include <QRegExp>
#include <QtDebug>

const QHash<Types::UnitsOfLength, QPair<QString, qreal> > &Types::unitsOfLength()
{
    static QHash<UnitsOfLength, QPair<QString, qreal> > units;
    if (units.empty()) {
        static const struct {
            UnitsOfLength unit;
            QString name;
            qreal cm;
        } unitsOfLength[] = {
            {UnitOfLengthMeter,      QLatin1String("m"),        100.00},
            {UnitOfLengthMillimeter, QLatin1String("mm"),         0.10},
            {UnitOfLengthCentimeter, QLatin1String("cm"),         1.00},
            {UnitOfLengthInch,       QLatin1String("in"),         2.54},
            {UnitOfLengthFeet,       QLatin1String("ft"), 2.54 * 12.00},
            {UnitOfLengthPoints,     QLatin1String("pt"), 2.54 / 72.00}
        };
        for (auto unit : unitsOfLength)
            units.insert(unit.unit, {unit.name, unit.cm});
    }
    return units;
}

qreal Types::convertBetweenUnitsOfLength(qreal distance, UnitsOfLength sourceUnit, UnitsOfLength targetUnit)
{
    qreal convertedDistance = distance;
    if (sourceUnit != targetUnit) {
        if (sourceUnit != UnitOfLengthCentimeter)
            convertedDistance *= unitsOfLength().value(sourceUnit).second;
        if (targetUnit != UnitOfLengthCentimeter)
            convertedDistance /= unitsOfLength().value(targetUnit).second;
    }
    return convertedDistance;
}

QSizeF Types::convertBetweenUnitsOfLength(const QSizeF &size, UnitsOfLength sourceUnit, UnitsOfLength targetUnit)
{
    return {
        convertBetweenUnitsOfLength(size.width(), sourceUnit, targetUnit),
        convertBetweenUnitsOfLength(size.height(), sourceUnit, targetUnit)
    };
}

Types::UnitsOfLength Types::unitOfLenthFromString(const QString &string)
{
    static QHash<QString, UnitsOfLength> hash;
    if (hash.isEmpty()) {
        const QList<UnitsOfLength> units = unitsOfLength().keys();
        foreach (UnitsOfLength unit, units)
            hash.insert(unitsOfLength().value(unit).first, unit);
    }
    return hash.value(string);
}

const QHash<QString, QSizeF> &Types::paperFormats()
{
    static QHash<QString, QSizeF> formats;
    if (formats.empty()) {
        static const struct {
            QString name;
            qreal width;
            qreal height;
        } paperFormats[] = {
            {QLatin1String("DIN A4"),    21.0, 29.7},
            {QLatin1String("DIN A3"),    29.7, 42.0},
            {QLatin1String("Legal"),     21.6, 35.6},
            {QLatin1String("Letter"),    21.6, 27.9},
            {QLatin1String("Tabloid"),   27.9, 43.2}
        };
        for (auto format : paperFormats)
            formats.insert(format.name, {format.width, format.height});
    }
    return formats;
}

QSizeF Types::paperSize(const QString &format, QPrinter::Orientation orientation, UnitsOfLength unit)
{
    QSizeF result = paperFormats().value(format);
    if (orientation == QPrinter::Landscape)
        result.transpose();
    return convertBetweenUnitsOfLength(result, UnitOfLengthCentimeter, unit);
}

QString Types::cleanString(const QString &dirtyString)
{
    QString result = dirtyString;
    result.replace(QRegExp(QLatin1String("[:&]")), QString());
    result.replace(QRegExp(QLatin1String("\\(.*\\)")), QString());
    result.replace(QLatin1Char('\n'), QLatin1Char(' '));
    return result.trimmed();
}

QString Types::newlineToParagraph(const QString &nlText)
{
    QString result = nlText;
    result.replace(QLatin1Char('\n'), QLatin1String("</p><p>"));
    return QLatin1String("<p>") + result + QLatin1String("</p>");
}
