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

#ifndef QTPAINTCANVAS_H
#define QTPAINTCANVAS_H

#include <QWidget>
#include "PaintCanvasInterface.h"

class QImage;
class QPainter;
class QPaintDevice;

class QtPaintCanvas: public QWidget, public PaintCanvasInterface
{
    Q_OBJECT

private:
    QImage m_image;
    QString m_state;
    QPainter *m_qPainter;

public:
    QtPaintCanvas(QWidget *parent);

    virtual void paintEvent(QPaintEvent *event);
    virtual void drawFilledRect(const QRectF &rect, const QBrush &brush);
    virtual QSizeF getSize() const;
    virtual void drawImage(const QRectF &rect);
    virtual void setState(const QString &state);

public slots:
    void setImage(const QImage &image);

signals:
    void needsPaint(PaintCanvasInterface *paintDevice, const QVariant &options) const;
};

#endif // QTPAINTCANVAS_H
