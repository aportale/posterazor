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

#include "imageioqt.h"
#include <QImageReader>
#include <math.h>

ImageLoaderQt::ImageLoaderQt(QObject *parent)
    : QObject(parent)
{
}

bool ImageLoaderQt::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    bool result = m_image.load(imageFileName);
    if (result)
        m_imageFileName = imageFileName;

    return result;
}

bool ImageLoaderQt::isImageLoaded() const
{
    return !m_image.isNull();
}

bool ImageLoaderQt::isJpeg() const
{
    QImageReader reader(m_imageFileName);
    return reader.format() == "jpg";
}

QString ImageLoaderQt::getFileName() const
{
    return m_imageFileName;
}

QSize ImageLoaderQt::getSizePixels() const
{
    return m_image.size();
}

double ImageLoaderQt::getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
{
    return m_image.logicalDpiX() / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthInch, unit);
}

double ImageLoaderQt::getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
{
    return m_image.logicalDpiY() / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthInch, unit);
}

QSizeF ImageLoaderQt::getSize(UnitsOfLength::eUnitsOfLength unit) const
{
    const QSize sizePixels(getSizePixels());
    return QSizeF(sizePixels.width() / getHorizontalDotsPerUnitOfLength(unit), sizePixels.height() / getVerticalDotsPerUnitOfLength(unit));
}

const QImage ImageLoaderQt::getImageAsRGB(const QSize &size) const
{
    return m_image.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

int ImageLoaderQt::getBitsPerPixel() const
{
    return getColorDataType() == ColorTypes::eColorTypeRGB?24:m_image.depth();
}

ColorTypes::eColorTypes ImageLoaderQt::getColorDataType() const
{
    const QImage::Format format = m_image.format();

    return  format==QImage::Format_Mono?ColorTypes::eColorTypeMonochrome:
            format==QImage::Format_Indexed8?ColorTypes::eColorTypePalette:
            format==QImage::Format_ARGB32?ColorTypes::eColorTypeRGBA:
            /*format==QImage::Format_RGB32?*/ColorTypes::eColorTypeRGB;
}

const QByteArray ImageLoaderQt::getBits() const
{
    const int imageWidth = m_image.width();
    const int imageHeight = m_image.height();
    const unsigned int bitsPerLine = imageWidth * getBitsPerPixel();
    const unsigned int bytesPerLine = (unsigned int)ceil(bitsPerLine/8.0);
    const unsigned int imageBytesCount = bytesPerLine * imageHeight;

    QByteArray result(imageBytesCount, 0);
    char *destination = result.data();

    if (getBitsPerPixel() == 24 && QSysInfo::ByteOrder == QSysInfo::LittleEndian) {
        for (int scanline = 0; scanline < imageHeight; scanline++) {
            const uchar *sourceScanLine = m_image.scanLine(scanline);
            for (int column = 0; column < imageWidth; column++) {
                *destination++ = sourceScanLine[2];
                *destination++ = sourceScanLine[1];
                *destination++ = sourceScanLine[0];
                sourceScanLine += 4;
            }
        }
    }

    return result;
}

const QVector<QRgb> ImageLoaderQt::getColorTable() const
{
    return m_image.colorTable();
}
