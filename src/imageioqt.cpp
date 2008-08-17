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
#include "PosteRazorPDFOutput.h"

ImageIOQt::ImageIOQt(QObject *parent)
    : QObject(parent)
{
}

bool ImageIOQt::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    bool result = m_image.load(imageFileName);
    if (result)
        m_imageFileName = imageFileName;

    return result;
}

bool ImageIOQt::isImageLoaded() const
{
    return !m_image.isNull();
}

QSize ImageIOQt::getSizePixels() const
{
    return m_image.size();
}

double ImageIOQt::getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
{
    return m_image.logicalDpiX() / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthInch, unit);
}

double ImageIOQt::getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
{
    return m_image.logicalDpiY() / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthInch, unit);
}

QSizeF ImageIOQt::getSize(UnitsOfLength::eUnitsOfLength unit) const
{
    const QSize sizePixels(getSizePixels());
    return QSizeF(sizePixels.width() / getHorizontalDotsPerUnitOfLength(unit), sizePixels.height() / getVerticalDotsPerUnitOfLength(unit));
}

QImage ImageIOQt::getImageAsRGB(const QSize &size) const
{
    return m_image.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

int ImageIOQt::getBitsPerPixel() const
{
    return m_image.depth();
}

ColorTypes::eColorTypes ImageIOQt::getColorDataType() const
{
    const QImage::Format format = m_image.format();

    return  format==QImage::Format_Mono?ColorTypes::eColorTypeMonochrome:
            format==QImage::Format_Indexed8?ColorTypes::eColorTypePalette:
            format==QImage::Format_ARGB32?ColorTypes::eColorTypeRGBA:
            /*format==QImage::Format_RGB32?*/ColorTypes::eColorTypeRGB;
}

int ImageIOQt::savePoster(const QString &fileName, const PainterInterface *painter, int pagesCount, const QSizeF &sizeCm) const
{
    int err = 0;

    const QSize imageSize = getSizePixels();
    const unsigned int imageBytesCount = PosteRazorPDFOutput::getImageBytesCount(imageSize, getBitsPerPixel());
    unsigned char *imageData = new unsigned char[imageBytesCount];

    const unsigned int bytesPerLineCount = PosteRazorPDFOutput::getImageBytesPerLineCount(imageSize.width(), getBitsPerPixel());

    PosteRazorPDFOutput pdfOutput;
    err = pdfOutput.startSaving(fileName, pagesCount, sizeCm.width(), sizeCm.height());
    if (!err) {
//        if (FreeImage_GetFileType(m_imageFileName.toAscii(), 0) == FIF_JPEG)
//            err = pdfOutput.saveImage(m_imageFileName, imageSize, getColorDataType());
//        else
            err = pdfOutput.saveImage(imageData, imageSize, getBitsPerPixel(), getColorDataType(), NULL, m_image.numColors());
    }

    if (!err) {
        for (int page = 0; page < pagesCount; page++) {
            char paintOptions[1024];
            sprintf(paintOptions, "posterpage %d", page);
            pdfOutput.startPage();
            painter->paintOnCanvas(&pdfOutput, paintOptions);
            pdfOutput.finishPage();
        }
        err = pdfOutput.finishSaving();
    }

    return err;
}
