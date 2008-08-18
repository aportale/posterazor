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

#ifndef POSTERAZORCORE_H
#define POSTERAZORCORE_H

#include "PaperFormats.h"
#include "ColorTypes.h"
#include "ImageIOTypes.h"
#include "PaintCanvasInterface.h"
#include <QObject>

class QSettings;
class ImageLoaderInterface;

class PosteRazorEnums
{
public:
    enum ePosterSizeModes {
        ePosterSizeModeAbsolute,
        ePosterSizeModePercentual,
        ePosterSizeModePages,
        ePosterSizeModeNone
    };
};

class PosteRazorCore: public QObject
{
    Q_OBJECT

public:
    PosteRazorCore(QObject *parent = 0);

    static unsigned int getImageBitsPerLineCount(int widthPixels, int bitPerPixel);
    static unsigned int getImageBytesPerLineCount(int widthPixels, int bitPerPixel);
    static unsigned int getImageBytesCount(const QSize &size, int bitPerPixel);

    bool readSettings(const QSettings *settings);
    bool writeSettings(QSettings *settings) const;
    bool loadInputImage(const QString &imageFileName, QString &errorMessage);
    int savePoster(const QString &fileName) const;

    QSize getInputImageSizePixels() const;
    double getInputImageHorizontalDpi() const;
    double getInputImageVerticalDpi() const;
    QSizeF getInputImageSize() const;
    int getInputImageBitsPerPixel() const;
    ColorTypes::eColorTypes getInputImageColorType() const;
    UnitsOfLength::eUnitsOfLength getUnitOfLength() const;
    const char* getUnitOfLengthName() const;
    const QString getPaperFormat() const;
    QPrinter::Orientation getPaperOrientation() const;
    double getPaperBorderTop() const;
    double getPaperBorderRight() const;
    double getPaperBorderBottom() const;
    double getPaperBorderLeft() const;
    QSizeF getCustomPaperSize() const;
    bool getUseCustomPaperSize() const;
    QSizeF getPaperSize() const;
    QSizeF getPrintablePaperAreaSize() const;
    double getOverlappingWidth() const;
    double getOverlappingHeight() const;
    Qt::Alignment getOverlappingPosition() const;
    QSizeF getPosterSize(PosteRazorEnums::ePosterSizeModes mode) const;
    PosteRazorEnums::ePosterSizeModes getPosterSizeMode() const;
    Qt::Alignment getPosterAlignment() const;
    bool getIsImageLoaded() const;

    void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit);
    void setPaperFormat(const QString &format);
    void setPaperOrientation(QPrinter::Orientation orientation);
    void setPaperBorderTop(double border);
    void setPaperBorderRight(double border);
    void setPaperBorderBottom(double border);
    void setPaperBorderLeft(double border);
    void setCustomPaperWidth(double width);
    void setCustomPaperHeight(double height);
    void setUseCustomPaperSize(bool useIt);
    void setOverlappingWidth(double width);
    void setOverlappingHeight(double height);
    void setOverlappingPosition(Qt::Alignment position);
    void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width);
    void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height);
    void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
    void setPosterAlignment(Qt::Alignment alignment);

public slots:
    void paintOnCanvas(PaintCanvasInterface *paintCanvas, const QVariant &options) const;

private:
    double convertDistanceToCm(double distance) const;
    QSizeF convertSizeToCm(const QSizeF &size) const;
    double convertCmToDistance(double cm) const;
    QSizeF convertCmToSize(const QSizeF &sizeInCm) const;
    void createPreviewImage(const QSize &boxSize) const;
    double getMaximalVerticalPaperBorder() const;
    double getMaximalHorizontalPaperBorder() const;
    double getCustomMinimalPaperWidth() const;
    double getCustomMinimalPaperHeight() const;
    double getCustomMaximalPaperWidth() const;
    double getCustomMaximalPaperHeight() const;
    double convertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width) const;
    double calculateOtherPosterDimension() const;
    void setPosterDimension(PosteRazorEnums::ePosterSizeModes mode, double dimension, bool dimensionIsWidth);
    double getMaximalOverLappingWidth() const;
    double getMaximalOverLappingHeight() const;
    double getPosterDimension(PosteRazorEnums::ePosterSizeModes mode, bool width) const;
    QSizeF getPreviewSize(const QSizeF &imageSize, const QSize &boxSize, bool enlargeToFit) const;
    QSizeF getInputImagePreviewSize(const QSize &boxSize) const;
    void paintImageOnCanvas(PaintCanvasInterface *paintCanvas) const;
    void paintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const;
    void paintPosterOnCanvas(PaintCanvasInterface *paintCanvas) const;
    void paintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const;

signals:
    void previewImageChanged(const QImage &image) const;

private:
    ImageLoaderInterface*                   m_imageLoader;

    PosteRazorEnums::ePosterSizeModes       m_posterSizeMode;
    double                                  m_posterDimension;
    bool                                    m_posterDimensionIsWidth;
    Qt::Alignment                           m_posterAlignment;

    bool                                    m_useCustomPaperSize;
    QString                                 m_paperFormat;
    QPrinter::Orientation                   m_paperOrientation;
    double                                  m_paperBorderTop;
    double                                  m_paperBorderRight;
    double                                  m_paperBorderBottom;
    double                                  m_paperBorderLeft;
    double                                  m_customPaperWidth;
    double                                  m_customPaperHeight;

    double                                  m_overlappingWidth;
    double                                  m_overlappingHeight;
    Qt::Alignment                           m_overlappingPosition;

    UnitsOfLength::eUnitsOfLength           m_unitOfLength;
};

#endif // POSTERAZORCORE_H
