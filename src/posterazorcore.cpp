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

#include "posterazorcore.h"
#if defined (FREEIMAGE_LIB)
#    include "imageloaderfreeimage.h"
#else
#    include "imageloaderqt.h"
#endif
#include "pdfwriter.h"
#include <QSettings>
#include <QStringList>
#include <QBrush>
#include <math.h>

const QLatin1String defaultValue_PaperFormat("DIN A4");

const QLatin1String settingsKey_PosterSizeMode("PosterSizeMode");
const QLatin1String settingsKey_PosterDimension("PosterDimension");
const QLatin1String settingsKey_PosterDimensionIsWidth("PosterDimensionIsWidth");
const QLatin1String settingsKey_PosterAlignment("PosterAlignment");
const QLatin1String settingsKey_UseCustomPaperSize("UseCustomPaperSize");
const QLatin1String settingsKey_PaperFormat("paperFormat");
const QLatin1String settingsKey_PaperOrientation("PaperOrientation");
const QLatin1String settingsKey_PaperBorderTop("PaperBorderTop");
const QLatin1String settingsKey_PaperBorderRight("PaperBorderRight");
const QLatin1String settingsKey_PaperBorderBottom("PaperBorderBottom");
const QLatin1String settingsKey_PaperBorderLeft("PaperBorderLeft");
const QLatin1String settingsKey_CustomPaperWidth("CustomPaperWidth");
const QLatin1String settingsKey_CustomPaperHeight("CustomPaperHeight");
const QLatin1String settingsKey_OverlappingWidth("OverlappingWidth");
const QLatin1String settingsKey_OverlappingHeight("OverlappingHeight");
const QLatin1String settingsKey_OverlappingPosition("overlappingPosition");
const QLatin1String settingsKey_UnitOfLength("unitOfLength");

PosteRazorCore::PosteRazorCore(QObject *parent)
    : QObject(parent)
    , m_posterSizeMode(PosteRazorEnums::ePosterSizeModePages)
    , m_posterDimension(2.0)
    , m_posterDimensionIsWidth(true)
    , m_posterAlignment(Qt::AlignCenter)
    , m_useCustomPaperSize(false)
    , m_paperFormat(defaultValue_PaperFormat)
    , m_paperOrientation(QPrinter::Portrait)
    , m_paperBorderTop(1.5)
    , m_paperBorderRight(1.5)
    , m_paperBorderBottom(1.5)
    , m_paperBorderLeft(1.5)
    , m_customPaperWidth(20)
    , m_customPaperHeight(20)
    , m_overlappingWidth(1.0)
    , m_overlappingHeight(1.0)
    , m_overlappingPosition(Qt::AlignBottom | Qt::AlignRight)
    , m_unitOfLength(UnitsOfLength::eUnitOfLengthCentimeter)
{
    m_imageLoader =
#if defined (FREEIMAGE_LIB)
        new ImageLoaderFreeImage(this);
#else
        new ImageLoaderQt(this);
#endif
}

unsigned int PosteRazorCore::getImageBitsPerLineCount(int widthPixels, int bitPerPixel)
{
    return (widthPixels * bitPerPixel);
}

unsigned int PosteRazorCore::getImageBytesPerLineCount(int widthPixels, int bitPerPixel)
{
    return (int)(ceil((double)getImageBitsPerLineCount(widthPixels, bitPerPixel)/8.0f));
}

unsigned int PosteRazorCore::getImageBytesCount(const QSize &size, int bitPerPixel)
{
    return getImageBytesPerLineCount(size.width(), bitPerPixel) * size.height();
}

bool PosteRazorCore::readSettings(const QSettings *settings)
{
    bool returnValue = true;

    m_posterSizeMode               = (PosteRazorEnums::ePosterSizeModes)settings->value(settingsKey_PosterSizeMode, (int)m_posterSizeMode).toInt();
    m_posterDimension              = settings->value(settingsKey_PosterDimension, m_posterDimension).toDouble();
    m_posterDimensionIsWidth       = settings->value(settingsKey_PosterDimensionIsWidth, m_posterDimensionIsWidth).toBool();
    m_posterAlignment              = (Qt::Alignment)settings->value(settingsKey_PosterAlignment, (int)m_posterAlignment).toInt();
    m_useCustomPaperSize           = settings->value(settingsKey_UseCustomPaperSize, m_useCustomPaperSize).toBool();
    m_paperFormat                  = settings->value(settingsKey_PaperFormat, m_paperFormat).toString();
    if (!PaperFormats::paperFormats().contains(m_paperFormat))
        m_paperFormat = QLatin1String(defaultValue_PaperFormat);
    m_paperOrientation             = (QPrinter::Orientation)settings->value(settingsKey_PaperOrientation, (int)m_paperOrientation).toInt();
    m_paperBorderTop               = settings->value(settingsKey_PaperBorderTop, m_paperBorderTop).toDouble();
    m_paperBorderRight             = settings->value(settingsKey_PaperBorderRight, m_paperBorderRight).toDouble();
    m_paperBorderBottom            = settings->value(settingsKey_PaperBorderBottom, m_paperBorderBottom).toDouble();
    m_paperBorderLeft              = settings->value(settingsKey_PaperBorderLeft, m_paperBorderLeft).toDouble();
    m_customPaperWidth             = settings->value(settingsKey_CustomPaperWidth, m_customPaperWidth).toDouble();
    m_customPaperHeight            = settings->value(settingsKey_CustomPaperHeight, m_customPaperHeight).toDouble();
    m_overlappingWidth             = settings->value(settingsKey_OverlappingWidth, m_overlappingWidth).toDouble();
    m_overlappingHeight            = settings->value(settingsKey_OverlappingHeight, m_overlappingHeight).toDouble();
    m_overlappingPosition          = (Qt::Alignment)settings->value(settingsKey_OverlappingPosition, (int)m_overlappingPosition).toInt();
    m_unitOfLength                 = (UnitsOfLength::eUnitsOfLength)settings->value(settingsKey_UnitOfLength, (int)m_unitOfLength).toInt();

    return returnValue;
}

bool PosteRazorCore::writeSettings(QSettings *settings) const
{
    bool returnValue = true;

    settings->setValue(settingsKey_PosterSizeMode, (int)m_posterSizeMode);
    settings->setValue(settingsKey_PosterDimension, m_posterDimension);
    settings->setValue(settingsKey_PosterDimensionIsWidth, m_posterDimensionIsWidth);
    settings->setValue(settingsKey_PosterAlignment, (int)m_posterAlignment);
    settings->setValue(settingsKey_UseCustomPaperSize, m_useCustomPaperSize);
    settings->setValue(settingsKey_PaperFormat, m_paperFormat);
    settings->setValue(settingsKey_PaperOrientation, (int)m_paperOrientation);
    settings->setValue(settingsKey_PaperBorderTop, m_paperBorderTop);
    settings->setValue(settingsKey_PaperBorderRight, m_paperBorderRight);
    settings->setValue(settingsKey_PaperBorderBottom, m_paperBorderBottom);
    settings->setValue(settingsKey_PaperBorderLeft, m_paperBorderLeft);
    settings->setValue(settingsKey_CustomPaperWidth, m_customPaperWidth);
    settings->setValue(settingsKey_CustomPaperHeight, m_customPaperHeight);
    settings->setValue(settingsKey_OverlappingWidth, m_overlappingWidth);
    settings->setValue(settingsKey_OverlappingHeight, m_overlappingHeight);
    settings->setValue(settingsKey_OverlappingPosition, (int)m_overlappingPosition);
    settings->setValue(settingsKey_UnitOfLength, (int)m_unitOfLength);

    return returnValue;
}

double PosteRazorCore::convertDistanceToCm(double distance) const
{
    return UnitsOfLength::convertBetweenUnitsOfLength(distance, getUnitOfLength(), UnitsOfLength::eUnitOfLengthCentimeter);
}

QSizeF PosteRazorCore::convertSizeToCm(const QSizeF &size) const
{
    return QSizeF(convertDistanceToCm(size.width()), convertDistanceToCm(size.height()));
}

double PosteRazorCore::convertCmToDistance(double cm) const
{
    return UnitsOfLength::convertBetweenUnitsOfLength(cm, UnitsOfLength::eUnitOfLengthCentimeter, getUnitOfLength());
}

QSizeF PosteRazorCore::convertCmToSize(const QSizeF &sizeInCm) const
{
    return QSizeF(convertCmToDistance(sizeInCm.width()), convertCmToDistance(sizeInCm.height()));
}

bool PosteRazorCore::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    const bool success = m_imageLoader->loadInputImage(imageFileName, errorMessage);
    if (success)
        createPreviewImage(QSize(1024, 768));
    return success;
}

bool PosteRazorCore::getIsImageLoaded() const
{
    return m_imageLoader->isImageLoaded();
}

QSize PosteRazorCore::getInputImageSizePixels() const
{
    return m_imageLoader->getSizePixels();
}

double PosteRazorCore::getInputImageHorizontalDpi() const
{
    return m_imageLoader->getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
}

double PosteRazorCore::getInputImageVerticalDpi() const
{
    return m_imageLoader->getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
}

QSizeF PosteRazorCore::getInputImageSize() const
{
    return m_imageLoader->getSize(m_unitOfLength);
}

int PosteRazorCore::getInputImageBitsPerPixel() const
{
    return m_imageLoader->getBitsPerPixel();
}

ColorTypes::eColorTypes PosteRazorCore::getInputImageColorType() const
{
    return m_imageLoader->getColorDataType();
}

void PosteRazorCore::setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
    m_unitOfLength = unit;
}

UnitsOfLength::eUnitsOfLength PosteRazorCore::getUnitOfLength() const
{
    return m_unitOfLength;
}

void PosteRazorCore::setPaperFormat(const QString &format)
{
    m_paperFormat = format;
}

void PosteRazorCore::setPaperOrientation(QPrinter::Orientation orientation)
{
    m_paperOrientation = orientation;
}

void PosteRazorCore::setPaperBorderTop(double border)
{
    m_paperBorderTop = convertDistanceToCm(border);
}

void PosteRazorCore::setPaperBorderRight(double border)
{
    m_paperBorderRight = convertDistanceToCm(border);
}

void PosteRazorCore::setPaperBorderBottom(double border)
{
    m_paperBorderBottom = convertDistanceToCm(border);
}

void PosteRazorCore::setPaperBorderLeft(double border)
{
    m_paperBorderLeft = convertDistanceToCm(border);
}

const QString PosteRazorCore::getPaperFormat() const
{
    return m_paperFormat;
}

QPrinter::Orientation PosteRazorCore::getPaperOrientation() const
{
    return m_paperOrientation;
}

double PosteRazorCore::getPaperBorderTop() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderTop), getMaximalHorizontalPaperBorder());
}

double PosteRazorCore::getPaperBorderRight() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderRight), getMaximalVerticalPaperBorder());
}

double PosteRazorCore::getPaperBorderBottom() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderBottom), getMaximalHorizontalPaperBorder());
}

double PosteRazorCore::getPaperBorderLeft() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderLeft), getMaximalVerticalPaperBorder());
}

double PosteRazorCore::getMaximalVerticalPaperBorder() const
{
    return getPaperSize().width() / 2.0 - convertCmToDistance(1.0);
}

double PosteRazorCore::getMaximalHorizontalPaperBorder() const
{
    return getPaperSize().height() / 2.0 - convertCmToDistance(1.0);
}

void PosteRazorCore::setCustomPaperWidth(double width)
{
    m_customPaperWidth = convertDistanceToCm(width);
}

void PosteRazorCore::setCustomPaperHeight(double height)
{
    m_customPaperHeight = convertDistanceToCm(height);
}

QSizeF PosteRazorCore::getCustomPaperSize() const
{
    const double minimalPaperWidth = 4.0;
    const double minimalPaperHeight = minimalPaperWidth;
    const double maximalPaperWidth = 4.0;
    const double maximalPaperHeight = maximalPaperWidth;
    return QSizeF(
        convertCmToDistance(qBound(minimalPaperWidth, m_customPaperWidth, maximalPaperWidth)),
        convertCmToDistance(qBound(minimalPaperHeight, m_customPaperHeight, maximalPaperHeight))
    );
}

void PosteRazorCore::setUseCustomPaperSize(bool useIt)
{
    m_useCustomPaperSize = useIt;
}

bool PosteRazorCore::getUseCustomPaperSize() const
{
    return m_useCustomPaperSize;
}

QSizeF PosteRazorCore::getPaperSize() const
{
    return getUseCustomPaperSize()?getCustomPaperSize()
        :PaperFormats::getPaperSize(getPaperFormat(), getPaperOrientation(), m_unitOfLength);
}

QSizeF PosteRazorCore::getPrintablePaperAreaSize() const
{
    return QSizeF(
        getPaperSize().width() - getPaperBorderLeft() - getPaperBorderRight(),
        getPaperSize().height() - getPaperBorderTop() - getPaperBorderBottom()
    );
}

double PosteRazorCore::convertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width) const
{
    double posterDimension = dimension;

    const QSizeF printablePaperAreaSize = getPrintablePaperAreaSize();
    const double printablePaperAreaDimension = convertDistanceToCm(width?printablePaperAreaSize.width():printablePaperAreaSize.height());
    const double overlappingDimension = convertDistanceToCm(width?getOverlappingWidth():getOverlappingHeight());

    if (pagesToAbsolute) {
        double posterDimensionAbsolute = 0;
        if (posterDimension >= 1.0) {
            posterDimension -= 1.0;
            posterDimensionAbsolute += printablePaperAreaDimension;
        } else {
            posterDimensionAbsolute = posterDimension * printablePaperAreaDimension;
            posterDimension = 0;
        }

        if (posterDimension > 0)
            posterDimensionAbsolute += (posterDimension * (printablePaperAreaDimension - overlappingDimension));

        posterDimension = posterDimensionAbsolute;
    } else {
        double posterDimensionPages = 0;
        if (posterDimension >= printablePaperAreaDimension) {
            posterDimension -= printablePaperAreaDimension;
            posterDimensionPages += 1.0;
        } else if (posterDimension < printablePaperAreaDimension) {
            posterDimensionPages = posterDimension / printablePaperAreaDimension;
            posterDimension = 0;
        }

        if (posterDimension > 0)
            posterDimensionPages += (posterDimension / (printablePaperAreaDimension - overlappingDimension));

        posterDimension = posterDimensionPages;
    }

    return posterDimension;
}

// Since m_posterDimension holds only height or width of the poster,
// here we calculate the other dimension considering the aspect ratio.
double PosteRazorCore::calculateOtherPosterDimension() const
{
    double otherDimension = 0;

    if (getPosterSizeMode() != PosteRazorEnums::ePosterSizeModePercentual) {
        const QSizeF inputImageSize = getInputImageSize();
        const double sourceReference = m_posterDimensionIsWidth?inputImageSize.width():inputImageSize.height();
        const double targetReference = m_posterDimensionIsWidth?inputImageSize.height():inputImageSize.width();
        const double aspectRatio = sourceReference/targetReference;

        if (getPosterSizeMode() != PosteRazorEnums::ePosterSizeModePages) {
            otherDimension = m_posterDimension / aspectRatio;
        } else {
            const double sourceAbsolute = convertBetweenAbsoluteAndPagesPosterDimension(m_posterDimension, true, m_posterDimensionIsWidth);
            const double targetAbsolute = sourceAbsolute/aspectRatio;
            otherDimension = convertBetweenAbsoluteAndPagesPosterDimension(targetAbsolute, false, !m_posterDimensionIsWidth);
        }
    }
    else
        otherDimension = m_posterDimension;

    return otherDimension;
}

void PosteRazorCore::setPosterDimension(PosteRazorEnums::ePosterSizeModes mode, double dimension, bool dimensionIsWidth)
{
    setPosterSizeMode(mode);

    if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModeAbsolute)
        dimension = convertDistanceToCm(dimension);

    m_posterDimension = dimension;
    m_posterDimensionIsWidth = dimensionIsWidth;
}

void PosteRazorCore::setOverlappingWidth(double width)
{
    m_overlappingWidth = convertDistanceToCm(width);
}

void PosteRazorCore::setOverlappingHeight(double height)
{
    m_overlappingHeight = convertDistanceToCm(height);
}

double PosteRazorCore::getOverlappingWidth() const
{
    return qBound(.0, convertCmToDistance(m_overlappingWidth), getMaximalOverLappingWidth());
}

double PosteRazorCore::getOverlappingHeight() const
{
    return qBound(.0, convertCmToDistance(m_overlappingHeight), getMaximalOverLappingHeight());
}

double PosteRazorCore::getMaximalOverLappingWidth() const
{
    return getPaperSize().width() - getPaperBorderLeft() - getPaperBorderRight() - convertCmToDistance(1.0);
}

double PosteRazorCore::getMaximalOverLappingHeight() const
{
    return getPaperSize().height() - getPaperBorderTop() - getPaperBorderBottom() - convertCmToDistance(1.0);
}

void PosteRazorCore::setOverlappingPosition(Qt::Alignment position)
{
    m_overlappingPosition = position;
}

Qt::Alignment PosteRazorCore::getOverlappingPosition() const
{
    return m_overlappingPosition;
}

void PosteRazorCore::setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
    setPosterDimension(mode, width, true);
}

void PosteRazorCore::setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
    setPosterDimension(mode, height, false);
}

void PosteRazorCore::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
    m_posterSizeMode = mode;
}

double PosteRazorCore::getPosterDimension(PosteRazorEnums::ePosterSizeModes mode, bool width) const
{
    double posterDimension = (width==m_posterDimensionIsWidth)?m_posterDimension:calculateOtherPosterDimension();

    posterDimension = qMax(
        (mode == PosteRazorEnums::ePosterSizeModeAbsolute)?0.001
        :(mode == PosteRazorEnums::ePosterSizeModePages)?0.001
        :0.001
        , posterDimension
    );

    // anything to convert?
    if (getPosterSizeMode() != mode){
        // These are needed for conversion from and to ePosterSizeModePercentual
        const QSizeF inputImageSize = getInputImageSize();
        const double inputImageDimension = convertDistanceToCm(width?inputImageSize.width():inputImageSize.height());

        // First convert to absolute size mode (cm)
        if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModePages) {
            posterDimension = convertBetweenAbsoluteAndPagesPosterDimension(posterDimension, true, width);
        } else if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModePercentual) {
            posterDimension *= inputImageDimension;
            posterDimension /= 100.0;
        }

        // Then convert to the wanted size mode
        if (mode == PosteRazorEnums::ePosterSizeModePages) {
            posterDimension = convertBetweenAbsoluteAndPagesPosterDimension(posterDimension, false, width);
        } else if (mode == PosteRazorEnums::ePosterSizeModePercentual) {
            posterDimension /= inputImageDimension;
            posterDimension *= 100.0;
        }
    }

    if (mode == PosteRazorEnums::ePosterSizeModeAbsolute)
        posterDimension = convertCmToDistance(posterDimension);

    return posterDimension;
}

QSizeF PosteRazorCore::getPosterSize(PosteRazorEnums::ePosterSizeModes mode) const
{
    return QSizeF(getPosterDimension(mode, true), getPosterDimension(mode, false));
}

PosteRazorEnums::ePosterSizeModes PosteRazorCore::getPosterSizeMode() const
{
    return m_posterSizeMode;
}

void PosteRazorCore::setPosterAlignment(Qt::Alignment alignment)
{
    m_posterAlignment = alignment;
}

Qt::Alignment PosteRazorCore::getPosterAlignment() const
{
    return m_posterAlignment;
}

QSizeF PosteRazorCore::getPreviewSize(const QSizeF &imageSize, const QSize &boxSize, bool enlargeToFit) const
{
    QSizeF result(imageSize);

    QSizeF boundedBoxSize(boxSize);
    if (!enlargeToFit)
        boundedBoxSize = boundedBoxSize.boundedTo(imageSize);

    result.scale(boundedBoxSize, Qt::KeepAspectRatio);
    return result;
}

QSizeF PosteRazorCore::getInputImagePreviewSize(const QSize &boxSize) const
{
    return getPreviewSize(getInputImageSizePixels(), boxSize, false);
}

void PosteRazorCore::createPreviewImage(const QSize &size) const
{
    const QImage previewImage = m_imageLoader->getImageAsRGB(getInputImagePreviewSize(size).toSize());
    emit previewImageChanged(previewImage);
}

void PosteRazorCore::paintImageOnCanvas(PaintCanvasInterface *paintCanvas) const
{
    if (getIsImageLoaded()) {
        const QSizeF canvasSize = paintCanvas->getSize();
        const QSize inputImageSize = getInputImageSizePixels();
        const QSizeF boxSize = getPreviewSize(inputImageSize, canvasSize.toSize(), false);
        QPointF offset((canvasSize.width() - boxSize.width()) / 2, (canvasSize.height() - boxSize.height()) / 2);

        // If the image is not downscaled, make sure that the coordinates are integers in order
        // to prevent unneeded blurring
        if (canvasSize.width() >= inputImageSize.width() && canvasSize.height() >= inputImageSize.height()) {
            offset.setX(floor(offset.x()));
            offset.setY(floor(offset.y()));
        }

        paintCanvas->drawImage(QRectF(offset, boxSize));
    }
}

void PosteRazorCore::paintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const
{
    const QSizeF canvasSize = paintCanvas->getSize();
    const QSizeF paperSize = getPaperSize();
    const QSizeF boxSize = getPreviewSize(paperSize, canvasSize.toSize(), true);
    const QPointF offset((canvasSize.width() - boxSize.width()) / 2.0, (canvasSize.height() - boxSize.height()) / 2.0);
    const double UnitOfLengthToPixelfactor = boxSize.width()/paperSize.width();
    const double borderTop = getPaperBorderTop() * UnitOfLengthToPixelfactor;
    const double borderRight = getPaperBorderRight() * UnitOfLengthToPixelfactor;
    const double borderBottom = getPaperBorderBottom() * UnitOfLengthToPixelfactor;
    const double borderLeft = getPaperBorderLeft() * UnitOfLengthToPixelfactor;
    const QSizeF printableAreaSize(boxSize.width() - borderLeft - borderRight, boxSize.height() - borderTop - borderBottom);

    paintCanvas->drawFilledRect(QRectF(offset, boxSize), QColor(128, 128, 128));
    paintCanvas->drawFilledRect(QRectF(QPointF(borderLeft, borderTop) + offset, printableAreaSize), QColor(230, 230, 230));

    if (paintOverlapping) {
        const double overlappingWidth = getOverlappingWidth() * UnitOfLengthToPixelfactor;
        const double overlappingHeight = getOverlappingHeight() * UnitOfLengthToPixelfactor;
        const Qt::Alignment overlappingPosition = getOverlappingPosition();
        const double overlappingTop = (overlappingPosition & Qt::AlignTop)?
            borderTop:boxSize.height() - borderBottom - overlappingHeight;
        const double overlappingLeft = (overlappingPosition & Qt::AlignLeft)?
            borderLeft:boxSize.width() - borderRight - overlappingWidth;

        const QColor overlappingBrush(255, 128, 128);
        paintCanvas->drawFilledRect(QRectF(QPointF(borderLeft, overlappingTop) + offset, QSizeF(printableAreaSize.width(), overlappingHeight)), overlappingBrush);
        paintCanvas->drawFilledRect(QRectF(QPointF(overlappingLeft, borderTop) + offset, QSizeF(overlappingWidth, printableAreaSize.height())), overlappingBrush);
    }
}

void PosteRazorCore::paintPosterOnCanvas(PaintCanvasInterface *paintCanvas) const
{
    const QSizeF canvasSize = paintCanvas->getSize();
    QSizeF pagePrintableAreaSize = getPrintablePaperAreaSize();
    const QSizeF posteraSizePages = getPosterSize(PosteRazorEnums::ePosterSizeModePages);
    const int pagesHorizontal = (int)ceil(posteraSizePages.width());
    const int pagesVertical = (int)ceil(posteraSizePages.height());
    const QSizeF posterSize(
        pagesHorizontal*pagePrintableAreaSize.width() - (pagesHorizontal-1)*getOverlappingWidth() + getPaperBorderLeft() + getPaperBorderRight(),
        pagesVertical*pagePrintableAreaSize.height() - (pagesVertical-1)*getOverlappingHeight() + getPaperBorderTop() + getPaperBorderBottom()
    );
    const QSizeF boxSize = getPreviewSize(posterSize, canvasSize.toSize(), true);
    const QPointF offset((canvasSize.width() - boxSize.width()) / 2, (canvasSize.height() - boxSize.height()) / 2);
    const double UnitOfLengthToPixelfactor = boxSize.width()/posterSize.width();

    const double borderTop = getPaperBorderTop() * UnitOfLengthToPixelfactor;
    const double borderRight = getPaperBorderRight() * UnitOfLengthToPixelfactor;
    const double borderBottom = getPaperBorderBottom() * UnitOfLengthToPixelfactor;
    const double borderLeft = getPaperBorderLeft() * UnitOfLengthToPixelfactor;
    const QSizeF posterPrintableAreaSize(boxSize.width() - borderLeft - borderRight, boxSize.height() - borderTop - borderBottom);

    paintCanvas->drawFilledRect(QRectF(offset, boxSize), QColor(128, 128, 128));
    paintCanvas->drawFilledRect(QRectF(QPointF(borderLeft, borderTop) + offset, posterPrintableAreaSize), QColor(230, 230, 230));

    const QSizeF posterSizeAbsolute = getPosterSize(PosteRazorEnums::ePosterSizeModeAbsolute);
    const QSizeF imageSize = posterSizeAbsolute * UnitOfLengthToPixelfactor;
    const Qt::Alignment alignment = getPosterAlignment();

    paintCanvas->drawImage(
        QRectF(
            QPointF(
                (
                    alignment & Qt::AlignLeft?borderLeft
                    :alignment & Qt::AlignHCenter?qBound(borderLeft, (boxSize.width() - imageSize.width()) / 2, borderLeft + posterPrintableAreaSize.width() - imageSize.width())
                    :(borderLeft + posterPrintableAreaSize.width() - imageSize.width())
                ) + offset.x(),
                (
                    alignment & Qt::AlignTop?borderTop
                    :alignment & Qt::AlignVCenter?qBound(borderTop, (boxSize.height() - imageSize.height()) / 2, borderTop + posterPrintableAreaSize.height() - imageSize.height())
                    :(borderTop + posterPrintableAreaSize.height() - imageSize.height())
                ) + offset.y()
            ),
            imageSize
        )
    );

    const double overlappingHeight = getOverlappingHeight() * UnitOfLengthToPixelfactor;
    const double overlappingWidth = getOverlappingWidth() * UnitOfLengthToPixelfactor;
    pagePrintableAreaSize *= UnitOfLengthToPixelfactor;

    const QColor overLappingColor(255, 128, 128, 128);
    double overlappingRectangleYPosition = borderTop;
    for (int pagesRow = 0; pagesRow < pagesVertical - 1; pagesRow++) {
        overlappingRectangleYPosition += pagePrintableAreaSize.height() - overlappingHeight;
        paintCanvas->drawFilledRect(QRectF(QPointF(0, overlappingRectangleYPosition) + offset, QSizeF(boxSize.width(), overlappingHeight)), overLappingColor);
    }

    double overlappingRectangleXPosition = borderLeft;
    for (int pagesColumn = 0; pagesColumn < pagesHorizontal - 1; pagesColumn++) {
        overlappingRectangleXPosition += pagePrintableAreaSize.width() - overlappingWidth;
        paintCanvas->drawFilledRect(QRectF(QPointF(overlappingRectangleXPosition, 0) + offset, QSizeF(overlappingWidth, boxSize.height())), overLappingColor);
    }
}

void PosteRazorCore::paintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const
{
    const QSizeF posterSizePages = getPosterSize(PosteRazorEnums::ePosterSizeModePages);
    const int columsCount = (int)(ceil(posterSizePages.width()));
    const int rowsCount = (int)(ceil(posterSizePages.height()));
    const int column = page % columsCount;
    const int row = ((int)(floor((double)page / (double)columsCount)));

    const QSizeF posterSizeAbsolute = getPosterSize(PosteRazorEnums::ePosterSizeModeAbsolute);
    const QSizeF posterImageSizeCm = convertSizeToCm(posterSizeAbsolute);
    const QSizeF printablePaperAreaSizeCm = convertSizeToCm(getPrintablePaperAreaSize());
    const double overlappingWidthCm = convertDistanceToCm(getOverlappingWidth());
    const double overlappingHeightCm = convertDistanceToCm(getOverlappingHeight());
    const QSizeF printablePosterAreaSizeCm(
        columsCount * printablePaperAreaSizeCm.width() - (columsCount - 1) * overlappingWidthCm,
        rowsCount * printablePaperAreaSizeCm.height() - (rowsCount - 1) * overlappingHeightCm
    );
    const double borderTopCm = convertDistanceToCm(getPaperBorderTop());
    const double borderRightCm = convertDistanceToCm(getPaperBorderRight());
    const double borderBottomCm = convertDistanceToCm(getPaperBorderBottom());
    const double borderLeftCm = convertDistanceToCm(getPaperBorderLeft());
    const QSizeF posterTotalSizeCm(
        printablePosterAreaSizeCm.width() + borderLeftCm + borderRightCm,
        printablePosterAreaSizeCm.height() + borderTopCm + borderBottomCm
    );
    const Qt::Alignment alignment = getPosterAlignment();
    double imageOffsetFromLeftPosterBorderCm = (
        alignment & Qt::AlignRight?posterTotalSizeCm.width() - posterImageSizeCm.width() - borderLeftCm
        :alignment & Qt::AlignHCenter?(posterTotalSizeCm.width() - posterImageSizeCm.width())/2 - borderLeftCm
        :-borderLeftCm
    );
    imageOffsetFromLeftPosterBorderCm = qBound(.0, imageOffsetFromLeftPosterBorderCm, posterTotalSizeCm.width() - posterImageSizeCm.width() - borderLeftCm - borderRightCm);
    double imageOffsetFromTopPosterBorderCm = (
        alignment & Qt::AlignBottom?posterTotalSizeCm.height() - posterImageSizeCm.height() - borderTopCm
        :alignment & Qt::AlignVCenter?(posterTotalSizeCm.height() - posterImageSizeCm.height())/2 - borderTopCm
        :-borderTopCm
    );
    imageOffsetFromTopPosterBorderCm = qBound(.0, imageOffsetFromTopPosterBorderCm, posterTotalSizeCm.height() - posterImageSizeCm.height() - borderTopCm - borderBottomCm);
    const QPointF pageOffsetToImageFromTopLeftCm(
        column * (printablePaperAreaSizeCm.width()- overlappingWidthCm) - imageOffsetFromLeftPosterBorderCm,
        row * (printablePaperAreaSizeCm.height() - overlappingHeightCm) - imageOffsetFromTopPosterBorderCm
    );
    paintCanvas->drawImage(QRectF(-pageOffsetToImageFromTopLeftCm, posterImageSizeCm));
}

void PosteRazorCore::paintOnCanvas(PaintCanvasInterface *paintCanvas, const QVariant &options) const
{
    const QString state = options.toString();

    if (state == QLatin1String("image")) {
        paintImageOnCanvas(paintCanvas);
    } else if (state == QLatin1String("paper") || state == QLatin1String("overlapping")) {
        paintPaperOnCanvas(paintCanvas, state == QLatin1String("overlapping"));
    } else if (state == QLatin1String("poster")) {
        paintPosterOnCanvas(paintCanvas);
    } else if (state.startsWith(QLatin1String("posterpage"))) {
        const int page = state.split(' ').last().toInt();
        paintPosterPageOnCanvas(paintCanvas, page);
    }
}

int PosteRazorCore::savePoster(const QString &fileName) const
{
    int err = 0;

    const QSizeF posterSizePages = getPosterSize(PosteRazorEnums::ePosterSizeModePages);
    const QSizeF sizeCm = convertSizeToCm(getPrintablePaperAreaSize());
    const int pagesCount = (int)(ceil(posterSizePages.width())) * (int)(ceil(posterSizePages.height()));
    const QSize imageSize = m_imageLoader->getSizePixels();
    const QByteArray imageData = m_imageLoader->getBits();

    PDFWriter pdfWriter;
    err = pdfWriter.startSaving(fileName, pagesCount, sizeCm.width(), sizeCm.height());
    if (!err) {
        if (m_imageLoader->isJpeg())
            err = pdfWriter.saveJpegImage(m_imageLoader->getFileName(), imageSize, m_imageLoader->getColorDataType());
        else
            err = pdfWriter.saveImage(imageData, imageSize, m_imageLoader->getBitsPerPixel(), m_imageLoader->getColorDataType(), m_imageLoader->getColorTable());
    }

    if (!err) {
        for (int page = 0; page < pagesCount; page++) {
            char paintOptions[1024];
            sprintf(paintOptions, "posterpage %d", page);
            pdfWriter.startPage();
            paintOnCanvas(&pdfWriter, paintOptions);
            pdfWriter.finishPage();
        }
        err = pdfWriter.finishSaving();
    }

    return err;
}
