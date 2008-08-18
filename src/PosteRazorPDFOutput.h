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

#ifndef POSTERAZORPDFOUTPUT_H
#define POSTERAZORPDFOUTPUT_H

#include "ColorTypes.h"
#include "PaintCanvasInterface.h"
#include <QVector>
#include <QRgb>
#include <QSize>

class PosteRazorPDFOutput: public QObject, public PaintCanvasInterface
{
public:
    PosteRazorPDFOutput(QObject *parent = 0);

    void addOffsetToXref();
    int addImageResourcesAndXObject();
    int saveImage(const QString &jpegFileName, const QSize &sizePixels, ColorTypes::eColorTypes colorType);
    int saveImage(const QByteArray &imageData, const QSize &sizePixels, int bitPerPixel, ColorTypes::eColorTypes colorType, const QVector<QRgb> &colorTable);
    int startPage();
    int finishPage();
    int startSaving(const QString &fileName, int pages, double widthCm, double heightCm);
    int finishSaving();
    void drawFilledRect(const QRectF&, const QBrush &brush);
    QSizeF getSize() const;
    void drawImage(const QRectF &rect);

private:
    FILE *m_outputFile;
    char *m_xref;
    int m_pdfObjectCount;
    int m_contentPagesCount;
    int m_objectPagesID;
    int m_objectResourcesID;
    int m_objectImageID;
    char m_pageContent[2048];
    double m_mediaboxWidth;
    double m_mediaboxHeight;
};

#endif // POSTERAZORPDFOUTPUT_H
