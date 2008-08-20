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

#ifndef IMAGELOADERQT_H
#define IMAGELOADERQT_H

#include "imageloaderinterface.h"
#include <QObject>

class ImageLoaderQt: public QObject, public ImageLoaderInterface
{
public:
    ImageLoaderQt(QObject *parent = 0);

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
    int savePoster(const QString &fileName, const PainterInterface *painter, int pagesCount, const QSizeF &sizeCm) const;
    const QByteArray getBits() const;
    const QVector<QRgb> getColorTable() const;
    const QVector<QPair<QStringList, QString> > &getImageFormats() const;

private:
    QImage m_image;
    QString m_imageFileName;
};

#endif // IMAGELOADERQT_H
