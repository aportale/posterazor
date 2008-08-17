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

#include "QtPaintCanvas.h"
#include <QImage>
#include <QPainter>

QtPaintCanvas::QtPaintCanvas(QWidget *parent)
    : QWidget(parent)
    , m_qPainter(NULL)
    , m_state("image")
{
}

void QtPaintCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    m_qPainter = &painter;
    m_qPainter->setRenderHint(QPainter::Antialiasing);
    emit needsPaint(this, m_state);
    m_qPainter = NULL;
}

void QtPaintCanvas::drawFilledRect(const QRectF &rect, const QBrush &brush)
{
    m_qPainter->fillRect(rect, brush);
}

QSizeF QtPaintCanvas::getSize() const
{
    return this->size();
}

void QtPaintCanvas::setImage(const QImage &image)
{
    m_image = image;
    repaint();
}

void QtPaintCanvas::drawImage(const QRectF &rect)
{
    double widthResizeFactor = rect.width()/(double)m_image.width();
    m_qPainter->setRenderHint(QPainter::SmoothPixmapTransform, widthResizeFactor < 2.75);
    m_qPainter->drawImage(rect, m_image);
}

void QtPaintCanvas::setState(const QString &state)
{
    m_state = state;
    repaint();
}
