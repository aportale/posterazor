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

#include "imageloaderqt.h"
#include <QImageReader>
#include <math.h>

ImageLoaderQt::ImageLoaderQt(QObject *parent)
    : QObject(parent)
{
}

bool ImageLoaderQt::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    Q_UNUSED(errorMessage);
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
    return reader.format() == "jpeg";
}

QString ImageLoaderQt::getFileName() const
{
    return m_imageFileName;
}

QSize ImageLoaderQt::getSizePixels() const
{
    return m_image.size();
}

double ImageLoaderQt::getHorizontalDotsPerUnitOfLength(Types::UnitsOfLength unit) const
{
    return m_image.logicalDpiX() / Types::convertBetweenUnitsOfLength(1, Types::UnitOfLengthInch, unit);
}

double ImageLoaderQt::getVerticalDotsPerUnitOfLength(Types::UnitsOfLength unit) const
{
    return m_image.logicalDpiY() / Types::convertBetweenUnitsOfLength(1, Types::UnitOfLengthInch, unit);
}

QSizeF ImageLoaderQt::getSize(Types::UnitsOfLength unit) const
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
    return getColorDataType() == Types::ColorTypeRGB?24:m_image.depth();
}

Types::ColorTypes ImageLoaderQt::getColorDataType() const
{
    const QImage::Format format = m_image.format();

    return  format==QImage::Format_Mono?Types::ColorTypeMonochrome:
            format==QImage::Format_Indexed8?Types::ColorTypePalette:
            format==QImage::Format_ARGB32?Types::ColorTypeRGBA:
            /*format==QImage::Format_RGB32?*/Types::ColorTypeRGB;
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

const QVector<QPair<QStringList, QString> > &ImageLoaderQt::getImageFormats() const
{
    static QVector<QPair<QStringList, QString> > formats;
    if (formats.empty()) {
        const struct {
            const QString extensions;
            const QString description;
        } extensionList[] = {
            {QLatin1String("bmp"),      QLatin1String("Windows, OS/2 Bitmap")},
            {QLatin1String("gif"),      QLatin1String("Graphic Interchange Format")},
            {QLatin1String("ico"),      QLatin1String("Windows Icon")},
            {QLatin1String("jpg jpeg"), QLatin1String("Joint Photographic Experts Group")},
            {QLatin1String("mng"),      QLatin1String("Multiple-image Network Graphics")},
            {QLatin1String("pbm"),      QLatin1String("Portable Bitmap")},
            {QLatin1String("pgm"),      QLatin1String("Portable Graymap")},
            {QLatin1String("png"),      QLatin1String("Portable Network Graphics")},
            {QLatin1String("ppm"),      QLatin1String("Portable Pixelmap")},
            {QLatin1String("tif tiff"), QLatin1String("Tagged Image File Format")},
            {QLatin1String("svg"),      QLatin1String("Scalable Vector Graphics")},
            {QLatin1String("xbm"),      QLatin1String("X11 Bitmap")},
            {QLatin1String("xpm"),      QLatin1String("X11 Pixmap")}
        };
        const int extensionListCount = (int)sizeof(extensionList)/sizeof(extensionList[0]);
        const QList<QByteArray> supportedFormats = QImageReader::supportedImageFormats();
        for (int i = 0; i < extensionListCount; i++) {
            QStringList extensions = extensionList[i].extensions.split(' ');
            foreach (const QString &extension, extensions)
                if (supportedFormats.contains(extension.toAscii())) {
                    formats.append(QPair<QStringList, QString> (extensions, extensionList[i].description));
                    break;
                }
        }
    }
    return formats;
}

QString ImageLoaderQt::getLibraryName() const
{
    return QLatin1String("Qt");
}

QString ImageLoaderQt::getLibraryAboutText() const
{
    // Returning an empty string means that this image IO library does not want to be mentioned.
    // Assuming that the host application provides a state-of-the-art "About Qt" message box.
    return QString();
}
