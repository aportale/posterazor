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
#include <QRgb>
#include <QTextStream>

class PDFWriter: public QObject, public PaintCanvasInterface
{
public:
    PDFWriter(QObject *parent = nullptr);

    void addOffsetToXref();
    int addImageResourcesAndXObject();
    int saveJpegImage(const QString &jpegFileName, const QSize &sizePixels, Types::ColorTypes colorType);
    int saveImage(const QByteArray &imageData, const QSize &sizePixels, int bitPerPixel, Types::ColorTypes colorType, const QVector<QRgb> &colorTable);
    int startPage();
    int finishPage();
    int startSaving(QIODevice *outputDevice, int pages, qreal widthCm, qreal heightCm);
    int finishSaving();
    void drawFilledRect(const QRectF&, const QBrush &brush) override;
    QSizeF size() const override;
    void drawImage(const QRectF &rect) override;
    void drawOverlayText(const QPointF &position, int flags, int size, const QString &text) override;

private:
    QString m_xref;
    int m_pdfObjectCount = 0;
    int m_contentPagesCount = 0;
    int m_objectPagesID = 0;
    int m_firstPageID = 5; // will be ++ed if the image has a SMask
    int m_objectResourcesID = 0;
    int m_objectImageID = 0;
    qreal m_mediaboxWidth = 5000.0;
    qreal m_mediaboxHeight = 5000.0;
    QString m_pageContent;
    QTextStream m_outStream;
};
