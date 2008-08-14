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
#include <QString>

class PainterInterface;

class ImageIOFreeImage: public ColorTypes
{
public:
    virtual ~ImageIOFreeImage() {}

    static ImageIOFreeImage* createImageIOFreeImage();

    virtual bool loadInputImage(const QString &imageFileName, QString &errorMessage) = 0;
    virtual bool isImageLoaded() const = 0;

    virtual int getWidthPixels() const = 0;
    virtual int getHeightPixels() const = 0;

    virtual double getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const = 0;
    virtual double getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const = 0;

    virtual double getWidth(UnitsOfLength::eUnitsOfLength unit) const = 0;
    virtual double getHeight(UnitsOfLength::eUnitsOfLength unit) const = 0;

    virtual bool getImageAsRGB(unsigned char *buffer) const = 0;
    virtual bool getImageAsRGB(unsigned char *buffer, int width, int height) const = 0;
    
    virtual int getBitsPerPixel() const = 0;
    virtual eColorTypes getColorDataType() const = 0;

    virtual int savePoster(const QString &fileName, const PainterInterface *painter, int pagesCount, double widthCm, double heightCm) const = 0;
};

#endif // IMAGEIOFREEIMAGE_H
