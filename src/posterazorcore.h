/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2018 by Alessandro Portale
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

#pragma once

#include "types.h"
#include "paintcanvasinterface.h"
#include <QObject>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

class ImageLoaderInterface;

class PosteRazorCore: public QObject
{
    Q_OBJECT

public:
    PosteRazorCore(ImageLoaderInterface *imageLoader, QObject *parent = nullptr);

    static unsigned int imageBitsPerLineCount(int widthPixels, int bitPerPixel);
    static unsigned int imageBytesPerLineCount(int widthPixels, int bitPerPixel);
    static unsigned int imageBytesCount(const QSize &size, int bitPerPixel);

    void readSettings(const QSettings *settings);
    void writeSettings(QSettings *settings) const;
    bool loadInputImage(const QString &imageFileName, QString &errorMessage);
    int savePoster(QIODevice *outputDevice) const;

    QSize inputImageSizePixels() const;
    qreal inputImageHorizontalDpi() const;
    qreal inputImageVerticalDpi() const;
    QSizeF inputImageSize() const;
    int inputImageBitsPerPixel() const;
    Types::ColorTypes inputImageColorType() const;
    Types::UnitsOfLength unitOfLength() const;
    const QString paperFormat() const;
    QPrinter::Orientation paperOrientation() const;
    qreal paperBorderTop() const;
    qreal paperBorderRight() const;
    qreal paperBorderBottom() const;
    qreal paperBorderLeft() const;
    QSizeF customPaperSize() const;
    bool usesCustomPaperSize() const;
    QSizeF paperSize() const;
    QSizeF printablePaperAreaSize() const;
    qreal overlappingWidth() const;
    qreal overlappingHeight() const;
    Qt::Alignment overlappingPosition() const;
    QSizeF posterSize(Types::PosterSizeModes mode) const;
    Types::PosterSizeModes posterSizeMode() const;
    Qt::Alignment posterAlignment() const;
    QString fileName() const;
    bool isImageLoaded() const;
    const QVector<QPair<QStringList, QString> > &imageFormats() const;
    const QString imageIOLibraryName() const;
    const QString imageIOLibraryAboutText() const;

    void setUnitOfLength(Types::UnitsOfLength unit);
    void setPaperFormat(const QString &format);
    void setPaperOrientation(QPrinter::Orientation orientation);
    void setPaperBorderTop(qreal border);
    void setPaperBorderRight(qreal border);
    void setPaperBorderBottom(qreal border);
    void setPaperBorderLeft(qreal border);
    void setCustomPaperWidth(qreal width);
    void setCustomPaperHeight(qreal height);
    void setUseCustomPaperSize(bool useIt);
    void setOverlappingWidth(qreal width);
    void setOverlappingHeight(qreal height);
    void setOverlappingPosition(Qt::Alignment position);
    void setPosterWidth(Types::PosterSizeModes mode, qreal width);
    void setPosterHeight(Types::PosterSizeModes mode, qreal height);
    void setPosterSizeMode(Types::PosterSizeModes mode);
    void setPosterAlignment(Qt::Alignment alignment);
    void createPreviewImage();

public slots:
    void paintOnCanvas(PaintCanvasInterface *paintCanvas, const QVariant &options) const;

private:
    qreal convertDistanceToCm(qreal distance) const;
    QSizeF convertSizeToCm(const QSizeF &size) const;
    qreal convertCmToDistance(qreal cm) const;
    QSizeF convertCmToSize(const QSizeF &sizeInCm) const;
    void createPreviewImage(const QSize &boxSize) const;
    qreal maximalVerticalPaperBorder() const;
    qreal maximalHorizontalPaperBorder() const;
    qreal convertBetweenAbsoluteAndPagesPosterDimension(qreal dimension, bool pagesToAbsolute, bool width) const;
    qreal calculateOtherPosterDimension() const;
    void setPosterDimension(Types::PosterSizeModes mode, qreal dimension, bool dimensionIsWidth);
    qreal maximalOverLappingWidth() const;
    qreal maximalOverLappingHeight() const;
    qreal posterDimension(Types::PosterSizeModes mode, bool width) const;
    QSizeF previewSize(const QSizeF &imageSize, const QSize &boxSize, bool enlargeToFit) const;
    QSizeF inputImagePreviewSize(const QSize &boxSize) const;
    void paintImageOnCanvas(PaintCanvasInterface *paintCanvas) const;
    void paintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const;
    void paintPosterOnCanvasOverlapped(PaintCanvasInterface *paintCanvas) const;
    void paintPosterOnCanvasDivided(PaintCanvasInterface *paintCanvas) const;
    void paintPosterOnCanvasPageWise(PaintCanvasInterface *paintCanvas, int page) const;
    void paintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const;

signals:
    void previewImageChanged(const QImage &image) const;

private:
    ImageLoaderInterface* m_imageLoader = nullptr;
    Types::PosterSizeModes m_posterSizeMode = Types::PosterSizeModePages;
    qreal m_posterDimension = 2.0;
    bool m_posterDimensionIsWidth = true;
    Qt::Alignment m_posterAlignment = Qt::AlignCenter;
    bool m_usesCustomPaperSize = false;
    QString m_paperFormat;
    QPrinter::Orientation m_paperOrientation = QPrinter::Portrait;
    qreal m_paperBorderTop = 1.5;
    qreal m_paperBorderRight = 1.5;
    qreal m_paperBorderBottom = 1.5;
    qreal m_paperBorderLeft = 1.5;
    qreal m_customPaperWidth = 20.0;
    qreal m_customPaperHeight = 20.0;
    qreal m_overlappingWidth = 1.0;
    qreal m_overlappingHeight = 1.0;
    Qt::Alignment m_overlappingPosition = Qt::AlignBottom | Qt::AlignRight;
    Types::UnitsOfLength m_unitOfLength = Types::UnitOfLengthCentimeter;
};
