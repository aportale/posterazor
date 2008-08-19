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

#include "FreeImage.h"
#include "imageiofreeimage.h"
#include "UnitsOfLength.h"
#include <QStringList>

static QString FreeImageErrorMessage;

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message)
{
    Q_UNUSED(fif)
    FreeImageErrorMessage = message;
}

class FreeImageInitializer
{
public:
    FreeImageInitializer()
    {
        FreeImage_Initialise();
        FreeImage_SetOutputMessage(FreeImageErrorHandler);
    }

    ~FreeImageInitializer()
    {
        FreeImage_DeInitialise();
    }
};

ImageLoaderFreeImage::ImageLoaderFreeImage(QObject *parent)
    : QObject(parent)
    , m_bitmap(NULL)
    , m_widthPixels(0)
    , m_heightPixels(0)
    , m_horizontalDotsPerMeter(0)
    , m_verticalDotsPerMeter(0)
{
    const static FreeImageInitializer initializer;
}

ImageLoaderFreeImage::~ImageLoaderFreeImage()
{
    disposeImage();
}

void ImageLoaderFreeImage::disposeImage()
{
    if (m_bitmap) {
        FreeImage_Unload(m_bitmap);
        m_bitmap = NULL;
    }
}

bool ImageLoaderFreeImage::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    bool result = false;

    FreeImageErrorMessage.clear();

    const FREE_IMAGE_FORMAT fileType = FreeImage_GetFileType(imageFileName.toAscii(), 0);
    FIBITMAP* newImage = FreeImage_Load(fileType, imageFileName.toAscii(), TIFF_CMYK);

    if (newImage) {
        result = true;
        disposeImage();

        m_bitmap = newImage;

        m_widthPixels = FreeImage_GetWidth(m_bitmap);
        m_heightPixels = FreeImage_GetHeight(m_bitmap);

        m_horizontalDotsPerMeter = FreeImage_GetDotsPerMeterX(m_bitmap);
        m_verticalDotsPerMeter = FreeImage_GetDotsPerMeterY(m_bitmap);

        if (m_horizontalDotsPerMeter == 0)
            m_horizontalDotsPerMeter = 2835; // 72 dpi
        if (m_verticalDotsPerMeter == 0)
            m_verticalDotsPerMeter = 2835;

        m_imageFileName = imageFileName;

        if ((getColorDataType() == ColorTypes::eColorTypeRGB && getBitsPerPixel() == 32) // Sometimes, there are strange .PSD images like this (FreeImage bug?)
            || (getColorDataType() == ColorTypes::eColorTypeRGBA)) // We can't export alpha channels to PDF, anyway (yet)
        {
            RGBQUAD white = { 255, 255, 255, 0 };
            FIBITMAP *Image24Bit = FreeImage_Composite(m_bitmap, FALSE, &white);
            FreeImage_Unload(m_bitmap);
            m_bitmap = Image24Bit;
        }
    }

    errorMessage = FreeImageErrorMessage;

    return result;
}

bool ImageLoaderFreeImage::isImageLoaded() const
{
    return (m_bitmap != NULL);
}

bool ImageLoaderFreeImage::isJpeg() const
{
    return FreeImage_GetFileType(m_imageFileName.toAscii(), 0) == FIF_JPEG;
}

QString ImageLoaderFreeImage::getFileName() const
{
    return m_imageFileName;
}

QSize ImageLoaderFreeImage::getSizePixels() const
{
    return QSize(m_widthPixels, m_heightPixels);
}

double ImageLoaderFreeImage::getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
{
    return m_horizontalDotsPerMeter / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthMeter, unit);
}

double ImageLoaderFreeImage::getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitsOfLength unit) const
{
    return m_verticalDotsPerMeter / UnitsOfLength::convertBetweenUnitsOfLength(1, UnitsOfLength::eUnitOfLengthMeter, unit);
}

QSizeF ImageLoaderFreeImage::getSize(UnitsOfLength::eUnitsOfLength unit) const
{
    const QSize sizePixels(getSizePixels());
    return QSizeF(sizePixels.width() / getHorizontalDotsPerUnitOfLength(unit), sizePixels.height() / getVerticalDotsPerUnitOfLength(unit));
}

const QImage ImageLoaderFreeImage::getImageAsRGB(const QSize &size) const
{
    const QSize resultSize = size.isValid()?size:getSizePixels();
    QImage result(resultSize, QImage::Format_RGB32);

    const int width = resultSize.width();
    const int height = resultSize.height();
    const QSize sizePixels = getSizePixels();

    FIBITMAP* originalImage = m_bitmap;
    FIBITMAP* temp24BPPImage = NULL;
    FIBITMAP* scaledImage = NULL;

    if (getBitsPerPixel() != 24) {
        if (getColorDataType() == ColorTypes::eColorTypeCMYK) {
            temp24BPPImage = FreeImage_Allocate(sizePixels.width(), sizePixels.height(), 24);
            const unsigned int columnsCount = sizePixels.width();
            const unsigned int scanlinesCount = sizePixels.height();
            for (unsigned int scanline = 0; scanline < scanlinesCount; scanline++) {
                const BYTE* const cmykBits = FreeImage_GetScanLine(m_bitmap, scanline);
                BYTE* const rgbBits = FreeImage_GetScanLine(temp24BPPImage, scanline);

                for (unsigned int column = 0; column < columnsCount; column++) {
                    const unsigned int cmykColumn = column * 4;
                    const unsigned int rgbColumn = column * 3;

                    const BYTE cyan = cmykBits[cmykColumn];
                    const BYTE magenta = cmykBits[cmykColumn + 1];
                    const BYTE yellow = cmykBits[cmykColumn + 2];
                    const BYTE black = cmykBits[cmykColumn + 3];

                    const BYTE red = qMax(0, (255 - (unsigned char)((double)yellow/1.5) - (unsigned char)((double)black/1.5)));
                    const BYTE green = qMax(0, (255 - (unsigned char)((double)magenta/1.5) - (unsigned char)((double)black/1.5)));
                    const BYTE blue = qMax(0, (255 - (unsigned char)((double)cyan/1.5) - (unsigned char)((double)black/1.5)));

                    rgbBits[rgbColumn] = red;
                    rgbBits[rgbColumn + 1] = green;
                    rgbBits[rgbColumn + 2] = blue;
                }
            }
        } else {
            temp24BPPImage = FreeImage_ConvertTo24Bits(originalImage);
        }
        originalImage = temp24BPPImage;
    }

    if (resultSize != sizePixels) {
        scaledImage = FreeImage_Rescale(originalImage, width, height, FILTER_BOX);
        originalImage = scaledImage;
    }

    for (int scanline = 0; scanline < height; scanline++) {
        const BYTE *sourceData = FreeImage_GetScanLine(originalImage, height - scanline - 1);
        QRgb *targetData = (QRgb*)result.scanLine(scanline);
        for (int column = 0; column < width; column++) {
            *targetData++ = qRgb(sourceData[2], sourceData[1], *sourceData);
            sourceData += 3;
        }
    }

    if (temp24BPPImage)
        FreeImage_Unload(temp24BPPImage);

    if (scaledImage)
        FreeImage_Unload(scaledImage);

    return result;
}

int ImageLoaderFreeImage::getBitsPerPixel() const
{
    return FreeImage_GetBPP(m_bitmap);
}

ColorTypes::eColorTypes ImageLoaderFreeImage::getColorDataType() const
{
    ColorTypes::eColorTypes colorDatatype = ColorTypes::eColorTypeRGB;
    const FREE_IMAGE_COLOR_TYPE imageColorType = FreeImage_GetColorType(m_bitmap);

    if (imageColorType == FIC_MINISBLACK || imageColorType == FIC_MINISWHITE) {
        colorDatatype = getBitsPerPixel()==1?ColorTypes::eColorTypeMonochrome:ColorTypes::eColorTypeGreyscale;
    } else {
        colorDatatype =
            imageColorType==FIC_PALETTE?ColorTypes::eColorTypePalette:
            imageColorType==FIC_RGB?ColorTypes::eColorTypeRGB:
            imageColorType==FIC_RGBALPHA?ColorTypes::eColorTypeRGBA:
            /*imageColorType==FIC_CMYK?*/ColorTypes::eColorTypeCMYK;
    }

    return colorDatatype;
}

const QByteArray ImageLoaderFreeImage::getBits() const
{
    const unsigned int bitsPerLine = m_widthPixels * getBitsPerPixel();
    const unsigned int bytesPerLine = ceil(bitsPerLine/8.0);
    const unsigned int imageBytesCount = bytesPerLine * m_heightPixels;

    QByteArray result(imageBytesCount, 0);
    char *destination = result.data();
    FreeImage_ConvertToRawBits((BYTE*)destination, m_bitmap, bytesPerLine, getBitsPerPixel(), FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, hasFreeImageVersionCorrectTopDownInConvertBits());

    if (getBitsPerPixel() == 24 && QSysInfo::ByteOrder == QSysInfo::LittleEndian) {
        const unsigned long numberOfPixels = m_widthPixels * m_heightPixels;
        for (unsigned int pixelIndex = 0; pixelIndex < numberOfPixels; pixelIndex++) {
            char *pixelPtr = destination + pixelIndex*3;
            const char temp = pixelPtr[0];
            pixelPtr[0] = pixelPtr[2];
            pixelPtr[2] = temp;
            pixelPtr+=3;
        }
    }

    return result;
}

const QVector<QRgb> ImageLoaderFreeImage::getColorTable() const
{
    QVector<QRgb> result;

    const RGBQUAD* const palette = FreeImage_GetPalette(m_bitmap);
    if (palette) {
        const int count = FreeImage_GetColorsUsed(m_bitmap);
        result.resize(count);
        for (int i = 0; i < count; i++)
            result.replace(i, qRgb(palette[i].rgbRed, palette[i].rgbGreen, palette[i].rgbBlue));
    }

    return result;
}

const QVector<QPair<QStringList, QString> > &ImageLoaderFreeImage::getImageFormats() const
{
    static QVector<QPair<QStringList, QString> > formats;
    if (formats.empty()) {
        QStringList extensions;
        extensions << "Gif";
        formats.append(QPair<QStringList, QString> (extensions, "Graphics interchange format"));
    }
    return formats;
}

bool ImageLoaderFreeImage::hasFreeImageVersionCorrectTopDownInConvertBits()
{
    const QStringList versionDigits = QString(FreeImage_GetVersion()).split('.');
    return versionDigits.count() >= 2
        && versionDigits.at(0).toInt() >= 3
        && versionDigits.at(1).toInt() >= 10;
}
