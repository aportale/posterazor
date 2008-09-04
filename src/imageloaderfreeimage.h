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

#ifndef IMAGELOADERFREEIMAGE_H
#define IMAGELOADERFREEIMAGE_H

#include "imageloaderinterface.h"

struct FIBITMAP;

class ImageLoaderFreeImage: public QObject, public ImageLoaderInterface
{
public:
    ImageLoaderFreeImage(QObject *parent = 0);
    ~ImageLoaderFreeImage();

    bool loadInputImage(const QString &imageFileName, QString &errorMessage);
    bool isImageLoaded() const;
    bool isJpeg() const;
    QString getFileName() const;
    QSize getSizePixels() const;
    double getHorizontalDotsPerUnitOfLength(Types::UnitsOfLength unit) const;
    double getVerticalDotsPerUnitOfLength(Types::UnitsOfLength unit) const;
    QSizeF getSize(Types::UnitsOfLength unit) const;
    const QImage getImageAsRGB(const QSize &size) const;
    int getBitsPerPixel() const;
    Types::ColorTypes getColorDataType() const;
    const QByteArray getBits() const;
    const QVector<QRgb> getColorTable() const;
    const QVector<QPair<QStringList, QString> > &getImageFormats() const;
    QString getLibraryName() const;
    QString getLibraryAboutText() const;

private:
    FIBITMAP*    m_bitmap;
    int          m_widthPixels;
    int          m_heightPixels;
    unsigned int m_horizontalDotsPerMeter;
    unsigned int m_verticalDotsPerMeter;
    QString      m_imageFileName;

    void disposeImage();
    static bool hasFreeImageVersionCorrectTopDownInConvertBits();
};

#endif // IMAGELOADERFREEIMAGE_H
