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

#ifndef IMAGEIOFREEIMAGE_H
#define IMAGEIOFREEIMAGE_H

#include "UnitsOfLength.h"
#include "ColorTypes.h"
#include "ImageIOTypes.h"
#include <QObject>
#include <QImage>

class PainterInterface;
struct FIBITMAP;

class ImageIOFreeImage: public QObject
{
public:
    ImageIOFreeImage(QObject *parent = 0);
    ~ImageIOFreeImage();

    void disposeImage();
    bool loadInputImage(const QString &imageFileName, QString &errorMessage);
    bool isImageLoaded() const;
    QSize getSizePixels() const;
    double getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const;
    double getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const;
    QSizeF getSize(UnitsOfLength::eUnitsOfLength unit) const;
    QImage getImageAsRGB(const QSize &size) const;
    int getBitsPerPixel() const;
    ColorTypes::eColorTypes getColorDataType() const;
    int savePoster(const QString &fileName, const PainterInterface *painter, int pagesCount, const QSizeF &sizeCm) const;

private:
    FIBITMAP*    m_bitmap;
    int          m_widthPixels;
    int          m_heightPixels;
    unsigned int m_horizontalDotsPerMeter;
    unsigned int m_verticalDotsPerMeter;
    QString      m_imageFileName;

    static bool hasFreeImageVersionCorrectTopDownInConvertBits();
};

#endif // IMAGEIOFREEIMAGE_H
