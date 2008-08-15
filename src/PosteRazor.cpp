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

#include "PosteRazor.h"
#include "imageiofreeimage.h"
#include <QSettings>
#include <QStringList>
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

PosteRazor::PosteRazor()
    : m_posterSizeMode(PosteRazorEnums::ePosterSizeModePages)
    , m_posterDimension(2.0)
    , m_posterDimensionIsWidth(true)
    , m_posterAlignment(Qt::AlignCenter)

    , m_useCustomPaperSize(false)
    , m_paperFormat(defaultValue_PaperFormat)
    , m_paperOrientation(PaperFormats::ePaperOrientationPortrait)
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
    m_imageIO = ImageIOFreeImage::createImageIOFreeImage();
}

PosteRazor::~PosteRazor()
{
    delete m_imageIO;
}

bool PosteRazor::readSettings(const QSettings *settings)
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
    m_paperOrientation             = (PaperFormats::ePaperOrientations)settings->value(settingsKey_PaperOrientation, (int)m_paperOrientation).toInt();
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

bool PosteRazor::writeSettings(QSettings *settings) const
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

double PosteRazor::convertDistanceToCm(double distance) const
{
    return UnitsOfLength::convertBetweenUnitsOfLength(distance, getUnitOfLength(), UnitsOfLength::eUnitOfLengthCentimeter);
}

double PosteRazor::convertCmToDistance(double cm) const
{
    return UnitsOfLength::convertBetweenUnitsOfLength(cm, UnitsOfLength::eUnitOfLengthCentimeter, getUnitOfLength());
}

bool PosteRazor::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    const bool success = m_imageIO->loadInputImage(imageFileName, errorMessage);
    if (success)
        createPreviewImage(QSize(1024, 768));
    return success;
}

bool PosteRazor::getIsImageLoaded() const
{
    return m_imageIO->isImageLoaded();
}

QSize PosteRazor::getInputImageSizePixels() const
{
    return m_imageIO->getSizePixels();
}

double PosteRazor::getInputImageHorizontalDpi() const
{
    return m_imageIO->getHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
}

double PosteRazor::getInputImageVerticalDpi() const
{
    return m_imageIO->getVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
}

QSizeF PosteRazor::getInputImageSize() const
{
    return m_imageIO->getSize(m_unitOfLength);
}

int PosteRazor::getInputImageBitsPerPixel() const
{
    return m_imageIO->getBitsPerPixel();
}

ColorTypes::eColorTypes PosteRazor::getInputImageColorType() const
{
    return m_imageIO->getColorDataType();
}

void PosteRazor::setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
    m_unitOfLength = unit;
}

UnitsOfLength::eUnitsOfLength PosteRazor::getUnitOfLength() const
{
    return m_unitOfLength;
}

const char* PosteRazor::getUnitOfLengthName() const
{
    return UnitsOfLength::getUnitOfLengthName(m_unitOfLength);
}

void PosteRazor::setPaperFormat(const QString &format)
{
    m_paperFormat = format;
}

void PosteRazor::setPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
    m_paperOrientation = orientation;
}

void PosteRazor::setPaperBorderTop(double border)
{
    m_paperBorderTop = convertDistanceToCm(border);
}

void PosteRazor::setPaperBorderRight(double border)
{
    m_paperBorderRight = convertDistanceToCm(border);
}

void PosteRazor::setPaperBorderBottom(double border)
{
    m_paperBorderBottom = convertDistanceToCm(border);
}

void PosteRazor::setPaperBorderLeft(double border)
{
    m_paperBorderLeft = convertDistanceToCm(border);
}

const QString PosteRazor::getPaperFormat() const
{
    return m_paperFormat;
}

PaperFormats::ePaperOrientations PosteRazor::getPaperOrientation() const
{
    return m_paperOrientation;
}

double PosteRazor::getPaperBorderTop() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderTop), getMaximalHorizontalPaperBorder());
}

double PosteRazor::getPaperBorderRight() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderRight), getMaximalVerticalPaperBorder());
}

double PosteRazor::getPaperBorderBottom() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderBottom), getMaximalHorizontalPaperBorder());
}

double PosteRazor::getPaperBorderLeft() const
{
    return qBound(.0, convertCmToDistance(m_paperBorderLeft), getMaximalVerticalPaperBorder());
}

double PosteRazor::getMaximalVerticalPaperBorder() const
{
    return getPaperWidth() / 2.0 - convertCmToDistance(1.0);
}

double PosteRazor::getMaximalHorizontalPaperBorder() const
{
    return getPaperHeight() / 2.0 - convertCmToDistance(1.0);
}

void PosteRazor::setCustomPaperWidth(double width)
{
    m_customPaperWidth = convertDistanceToCm(width);
}

void PosteRazor::setCustomPaperHeight(double height)
{
    m_customPaperHeight = convertDistanceToCm(height);
}

double PosteRazor::getCustomPaperWidth() const
{
    return qBound(getCustomMinimalPaperWidth(), convertCmToDistance(m_customPaperWidth), getCustomMaximalPaperWidth());
}

double PosteRazor::getCustomPaperHeight() const
{
    return qBound(getCustomMinimalPaperHeight(), convertCmToDistance(m_customPaperHeight), getCustomMaximalPaperHeight());
}

double PosteRazor::getCustomMinimalPaperWidth() const
{
    return convertCmToDistance(4.0);
}

double PosteRazor::getCustomMinimalPaperHeight() const
{
    return convertCmToDistance(4.0);
}

double PosteRazor::getCustomMaximalPaperWidth() const
{
    return convertCmToDistance(500.0); // Maximum of PDF page
}

double PosteRazor::getCustomMaximalPaperHeight() const
{
    return convertCmToDistance(500.0);
}

void PosteRazor::setUseCustomPaperSize(bool useIt)
{
    m_useCustomPaperSize = useIt;
}

bool PosteRazor::getUseCustomPaperSize() const
{
    return m_useCustomPaperSize;
}

double PosteRazor::getPaperWidth() const
{
    return getUseCustomPaperSize()?getCustomPaperWidth():PaperFormats::getPaperWidth(getPaperFormat(), getPaperOrientation(), m_unitOfLength);
}

double PosteRazor::getPaperHeight() const
{
    return getUseCustomPaperSize()?getCustomPaperHeight():PaperFormats::getPaperHeight(getPaperFormat(), getPaperOrientation(), m_unitOfLength);
}

double PosteRazor::getPrintablePaperAreaWidth() const
{
    return getPaperWidth() - getPaperBorderLeft() - getPaperBorderRight();
}

double PosteRazor::getPrintablePaperAreaHeight() const
{
    return getPaperHeight() - getPaperBorderTop() - getPaperBorderBottom();
}

double PosteRazor::convertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width) const
{
    double posterDimension = dimension;

    const double printablePaperAreaWidth = getPrintablePaperAreaWidth();
    const double printablePaperAreaHeight = getPrintablePaperAreaHeight();
    const double printablePaperAreaDimension = convertDistanceToCm(width?printablePaperAreaWidth:printablePaperAreaHeight);
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
double PosteRazor::calculateOtherPosterDimension() const
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

void PosteRazor::setPosterDimension(PosteRazorEnums::ePosterSizeModes mode, double dimension, bool dimensionIsWidth)
{
    setPosterSizeMode(mode);

    if (getPosterSizeMode() == PosteRazorEnums::ePosterSizeModeAbsolute)
        dimension = convertDistanceToCm(dimension);

    m_posterDimension = dimension;
    m_posterDimensionIsWidth = dimensionIsWidth;
}

void PosteRazor::setOverlappingWidth(double width)
{
    m_overlappingWidth = convertDistanceToCm(width);
}

void PosteRazor::setOverlappingHeight(double height)
{
    m_overlappingHeight = convertDistanceToCm(height);
}

double PosteRazor::getOverlappingWidth() const
{
    return qBound(.0, convertCmToDistance(m_overlappingWidth), getMaximalOverLappingWidth());
}

double PosteRazor::getOverlappingHeight() const
{
    return qBound(.0, convertCmToDistance(m_overlappingHeight), getMaximalOverLappingHeight());
}

double PosteRazor::getMaximalOverLappingWidth() const
{
    return getPaperWidth() - getPaperBorderLeft() - getPaperBorderRight() - convertCmToDistance(1.0);
}

double PosteRazor::getMaximalOverLappingHeight() const
{
    return getPaperHeight() - getPaperBorderTop() - getPaperBorderBottom() - convertCmToDistance(1.0);
}

void PosteRazor::setOverlappingPosition(Qt::Alignment position)
{
    m_overlappingPosition = position;
}

Qt::Alignment PosteRazor::getOverlappingPosition() const
{
    return m_overlappingPosition;
}

void PosteRazor::setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
    setPosterDimension(mode, width, true);
}

void PosteRazor::setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
    setPosterDimension(mode, height, false);
}

void PosteRazor::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
    m_posterSizeMode = mode;
}

double PosteRazor::getPosterDimension(PosteRazorEnums::ePosterSizeModes mode, bool width) const
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
        const double inputImageDimension = convertDistanceToCm(width?inputImageSize.width():inputImageSize.width());

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

double PosteRazor::getPosterWidth(PosteRazorEnums::ePosterSizeModes mode) const
{
    return getPosterDimension(mode, true);
}

double PosteRazor::getPosterHeight(PosteRazorEnums::ePosterSizeModes mode) const
{
    return getPosterDimension(mode, false);
}

PosteRazorEnums::ePosterSizeModes PosteRazor::getPosterSizeMode() const
{
    return m_posterSizeMode;
}

void PosteRazor::setPosterAlignment(Qt::Alignment alignment)
{
    m_posterAlignment = alignment;
}

Qt::Alignment PosteRazor::getPosterAlignment() const
{
    return m_posterAlignment;
}

QSize PosteRazor::getPreviewSize(const QSizeF &imageSize, const QSize &boxSize, bool enlargeToFit) const
{
    QSize result(imageSize.toSize());

    QSize boundedBoxSize(boxSize);
    if (!enlargeToFit)
        boundedBoxSize = boundedBoxSize.boundedTo(imageSize.toSize());

    result.scale(boundedBoxSize, Qt::KeepAspectRatio);
    return result;
}

QSize PosteRazor::getInputImagePreviewSize(const QSize &boxSize) const
{
    return getPreviewSize(getInputImageSizePixels(), boxSize, false);
}

void PosteRazor::createPreviewImage(const QSize &size) const
{
    QImage previewImage = m_imageIO->getImageAsRGB(getInputImagePreviewSize(size));
    emit previewImageChanged(previewImage);
}

void PosteRazor::paintImageOnCanvas(PaintCanvasInterface *paintCanvas) const
{
    if (getIsImageLoaded()) {
        double canvasWidth = 0, canvasHeight = 0;
        paintCanvas->getSize(canvasWidth, canvasHeight);
        double x_offset, y_offset;

        const QSize inputImageSize = getInputImageSizePixels();
        const QSize boxSize = getPreviewSize(inputImageSize, QSize((int)canvasWidth, (int)canvasHeight), false);
        x_offset = (canvasWidth - boxSize.width()) / 2;
        y_offset = (canvasHeight - boxSize.height()) / 2;
        
        // If the image is not downscaled, make sure that the coordinates are integers in order
        // to prevent unneeded blurring (especially in OpenGL)
        if (canvasWidth >= inputImageSize.width() && canvasHeight >= inputImageSize.height()) {
            x_offset = floor(x_offset);
            y_offset = floor(y_offset);
        }

        paintCanvas->drawImage(0 + x_offset, 0 + y_offset, boxSize.width(), boxSize.height());
    }
}

void PosteRazor::paintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const
{
    double canvasWidth = 0, canvasHeight = 0;
    paintCanvas->getSize(canvasWidth, canvasHeight);

    const double paperWidth = getPaperWidth();
    const double paperHeight = getPaperHeight();
    const QSize boxSize = getPreviewSize(QSizeF(paperWidth, paperHeight), QSize((int)canvasWidth, (int)canvasHeight), true);
    const double x_offset = (canvasWidth - (double)boxSize.width()) / 2.0;
    const double y_offset = (canvasHeight - (double)boxSize.height()) / 2.0;
    const double UnitOfLengthToPixelfactor = (double)boxSize.width()/paperWidth;
    const double borderTop = getPaperBorderTop() * UnitOfLengthToPixelfactor;
    const double borderRight = getPaperBorderRight() * UnitOfLengthToPixelfactor;
    const double borderBottom = getPaperBorderBottom() * UnitOfLengthToPixelfactor;
    const double borderLeft = getPaperBorderLeft() * UnitOfLengthToPixelfactor;
    const double printableAreaWidth = boxSize.width() - borderLeft - borderRight;
    const double printableAreaHeight = boxSize.height() - borderTop - borderBottom;
    
    paintCanvas->drawFilledRect(0 + x_offset, 0 + y_offset, boxSize.width(), boxSize.height(), 128, 128, 128, 255);
    paintCanvas->drawFilledRect(0 + borderLeft + x_offset, 0 + borderTop + y_offset, printableAreaWidth, printableAreaHeight, 230, 230, 230, 255);

    if (paintOverlapping) {
        const double overlappingWidth = getOverlappingWidth() * UnitOfLengthToPixelfactor;
        const double overlappingHeight = getOverlappingHeight() * UnitOfLengthToPixelfactor;
        const Qt::Alignment overlappingPosition = getOverlappingPosition();
        const double overlappingTop = (overlappingPosition & Qt::AlignTop)?
            borderTop:boxSize.height() - borderBottom - overlappingHeight;
        const double overlappingLeft = (overlappingPosition & Qt::AlignLeft)?
            borderLeft:boxSize.width() - borderRight - overlappingWidth;

        paintCanvas->drawFilledRect(borderLeft + x_offset, overlappingTop + y_offset, printableAreaWidth, overlappingHeight, 255, 128, 128, 255);
        paintCanvas->drawFilledRect(overlappingLeft + x_offset, borderTop + y_offset, overlappingWidth, printableAreaHeight, 255, 128, 128, 255);
    }
}

void PosteRazor::paintPosterOnCanvas(PaintCanvasInterface *paintCanvas) const
{
    double canvasWidth = 0, canvasHeight = 0;
    paintCanvas->getSize(canvasWidth, canvasHeight);

    double pagePrintableAreaWidth = getPrintablePaperAreaWidth();
    double pagePrintableAreaHeight = getPrintablePaperAreaHeight();
    const int pagesHorizontal = (int)ceil(getPosterWidth(PosteRazorEnums::ePosterSizeModePages));
    const int pagesVertical = (int)ceil(getPosterHeight(PosteRazorEnums::ePosterSizeModePages));
    const double posterWidth = pagesHorizontal*pagePrintableAreaWidth - (pagesHorizontal-1)*getOverlappingWidth() + getPaperBorderLeft() + getPaperBorderRight();
    const double posterHeight = pagesVertical*pagePrintableAreaHeight - (pagesVertical-1)*getOverlappingHeight() + getPaperBorderTop() + getPaperBorderBottom();
    const QSize boxSize = getPreviewSize(QSizeF(posterWidth, posterHeight), QSize((int)canvasWidth, (int)canvasHeight), true);
    const double x_offset = (canvasWidth - boxSize.width()) / 2;
    const double y_offset = (canvasHeight - boxSize.height()) / 2;
    const double UnitOfLengthToPixelfactor = (double)boxSize.width()/posterWidth;

    const double borderTop = getPaperBorderTop() * UnitOfLengthToPixelfactor;
    const double borderRight = getPaperBorderRight() * UnitOfLengthToPixelfactor;
    const double borderBottom = getPaperBorderBottom() * UnitOfLengthToPixelfactor;
    const double borderLeft = getPaperBorderLeft() * UnitOfLengthToPixelfactor;
    const double posterPrintableAreaWidth = boxSize.width() - borderLeft - borderRight;
    const double posterPrintableAreaHeight = boxSize.height() - borderTop - borderBottom;

    paintCanvas->drawFilledRect(x_offset, y_offset, boxSize.width(), boxSize.height(), 128, 128, 128, 255);
    paintCanvas->drawFilledRect(borderLeft + x_offset, borderTop + y_offset, posterPrintableAreaWidth, posterPrintableAreaHeight, 230, 230, 230, 255);

    const double imageWidth = getPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute) * UnitOfLengthToPixelfactor;
    const double imageHeight = getPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute) * UnitOfLengthToPixelfactor;

    const Qt::Alignment alignment = getPosterAlignment();

    paintCanvas->drawImage(
        (
            alignment & Qt::AlignLeft?borderLeft
            :alignment & Qt::AlignHCenter?qBound(borderLeft, ((double)boxSize.width() - imageWidth) / 2, borderLeft + posterPrintableAreaWidth - imageWidth)
            :(borderLeft + posterPrintableAreaWidth - imageWidth)
        )
        + x_offset,

        (
            alignment & Qt::AlignTop?borderTop
            :alignment & Qt::AlignVCenter?qBound(borderTop, ((double)boxSize.height() - imageHeight) / 2, borderTop + posterPrintableAreaHeight - imageHeight)
            :(borderTop + posterPrintableAreaHeight - imageHeight)
        )
        + y_offset,
        imageWidth, imageHeight
    );

    const double overlappingHeight = getOverlappingHeight() * UnitOfLengthToPixelfactor;
    const double overlappingWidth = getOverlappingWidth() * UnitOfLengthToPixelfactor;
    pagePrintableAreaWidth *= UnitOfLengthToPixelfactor;
    pagePrintableAreaHeight *= UnitOfLengthToPixelfactor;

    double overlappingRectangleYPosition = borderTop;
    for (int pagesRow = 0; pagesRow < pagesVertical - 1; pagesRow++) {
        overlappingRectangleYPosition += pagePrintableAreaHeight - overlappingHeight;
        paintCanvas->drawFilledRect(x_offset, overlappingRectangleYPosition + y_offset, boxSize.width(), overlappingHeight, 255, 128, 128, 128);
    }

    double overlappingRectangleXPosition = borderLeft;
    for (int pagesColumn = 0; pagesColumn < pagesHorizontal - 1; pagesColumn++) {
        overlappingRectangleXPosition += pagePrintableAreaWidth - overlappingWidth;
        paintCanvas->drawFilledRect(overlappingRectangleXPosition + x_offset, y_offset, overlappingWidth, boxSize.height(), 255, 128, 128, 128);
    }
}

void PosteRazor::paintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const
{
    const int columsCount = (int)(ceil(getPosterWidth(PosteRazorEnums::ePosterSizeModePages)));
    const int rowsCount = (int)(ceil(getPosterHeight(PosteRazorEnums::ePosterSizeModePages)));
    const int column = page % columsCount;
    const int row = ((int)(floor((double)page / (double)columsCount)));

    const double posterImageWidthCm = convertDistanceToCm(getPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute));
    const double posterImageHeightCm = convertDistanceToCm(getPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute));
    const double printablePaperAreaWidthCm = convertDistanceToCm(getPrintablePaperAreaWidth());
    const double printablePaperAreaHeightCm = convertDistanceToCm(getPrintablePaperAreaHeight());
    const double overlappingWidthCm = convertDistanceToCm(getOverlappingWidth());
    const double overlappingHeightCm = convertDistanceToCm(getOverlappingHeight());
    const double printablePosterAreaWidthCm = columsCount * printablePaperAreaWidthCm - (columsCount - 1) * overlappingWidthCm;
    const double printablePosterAreaHeightCm = rowsCount * printablePaperAreaHeightCm - (rowsCount - 1) * overlappingHeightCm;
    const double borderTopCm = convertDistanceToCm(getPaperBorderTop());
    const double borderRightCm = convertDistanceToCm(getPaperBorderRight());
    const double borderBottomCm = convertDistanceToCm(getPaperBorderBottom());
    const double borderLeftCm = convertDistanceToCm(getPaperBorderLeft());
    const double posterTotalWidthCm = printablePosterAreaWidthCm + borderLeftCm + borderRightCm;
    const double posterTotalHeightCm = printablePosterAreaHeightCm + borderTopCm + borderBottomCm;
    const Qt::Alignment alignment = getPosterAlignment();
    double imageOffsetFromLeftPosterBorderCm = (
        alignment & Qt::AlignRight?posterTotalWidthCm - posterImageWidthCm - borderLeftCm
        :alignment & Qt::AlignHCenter?(posterTotalWidthCm - posterImageWidthCm)/2 - borderLeftCm
        :-borderLeftCm
    );
    imageOffsetFromLeftPosterBorderCm = qBound(.0, imageOffsetFromLeftPosterBorderCm, posterTotalWidthCm - posterImageWidthCm - borderLeftCm - borderRightCm);
    double imageOffsetFromTopPosterBorderCm = (
        alignment & Qt::AlignBottom?posterTotalHeightCm - posterImageHeightCm - borderTopCm
        :alignment & Qt::AlignVCenter?(posterTotalHeightCm - posterImageHeightCm)/2 - borderTopCm
        :-borderTopCm
    );
    imageOffsetFromTopPosterBorderCm = qBound(.0, imageOffsetFromTopPosterBorderCm, posterTotalHeightCm - posterImageHeightCm - borderTopCm - borderBottomCm);
    const double pageOffsetToImageFromLeftCm = column * (printablePaperAreaWidthCm - overlappingWidthCm) - imageOffsetFromLeftPosterBorderCm;
    const double pageOffsetToImageFromTopCm = row * (printablePaperAreaHeightCm - overlappingHeightCm) - imageOffsetFromTopPosterBorderCm;
    
    paintCanvas->drawImage(-pageOffsetToImageFromLeftCm, -pageOffsetToImageFromTopCm, posterImageWidthCm, posterImageHeightCm);
}

void PosteRazor::paintOnCanvas(PaintCanvasInterface *paintCanvas, const QVariant &options) const
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

int PosteRazor::savePoster(const QString &fileName) const
{
    const int pagesCount = (int)(ceil(getPosterWidth(PosteRazorEnums::ePosterSizeModePages))) * (int)(ceil(getPosterHeight(PosteRazorEnums::ePosterSizeModePages)));
    return m_imageIO->savePoster(fileName, this, pagesCount, convertDistanceToCm(getPrintablePaperAreaWidth()), convertDistanceToCm(getPrintablePaperAreaHeight()));
}
