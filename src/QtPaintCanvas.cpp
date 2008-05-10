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
:	QWidget(parent)
,	PaintCanvasBase()
,	m_image(NULL)
,	m_imageRGBData(NULL)
,	m_qPainter(NULL)
{
}

QtPaintCanvas::~QtPaintCanvas()
{
	disposeImage();
}

void QtPaintCanvas::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	m_qPainter = &painter;
	m_painter->paintOnCanvas(this, m_stateString);
	m_qPainter = NULL;
}

void QtPaintCanvas::drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height <= 1.0)
	{
		drawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width <= 1.0)
	{
		drawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		m_qPainter->fillRect((int)x, (int)y, (int)width, (int)height, QColor(red, green, blue, alpha));
	}
}

void QtPaintCanvas::drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height <= 1.0)
	{
		drawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width <= 1.0)
	{
		drawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		m_qPainter->setPen(QColor(red, green, blue, alpha));
		m_qPainter->drawRect((int)x, (int)y, (int)width, (int)height);
	}
}

void QtPaintCanvas::drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	m_qPainter->setPen(QColor(red, green, blue, alpha));
	m_qPainter->drawLine((int)x1, (int)y1, (int)x2, (int)y2);
}

void QtPaintCanvas::getSize(double &width, double &height) const
{
	width = (double)(this->width());
	height = (double)(this->height());
}

void QtPaintCanvas::setImage(const unsigned char* rgbData, double width, double height)
{
	disposeImage();
	// We have to transfrom the image data from rgb to bgra
	int pixelsCount = (int)width * (int)height;
	size_t bytesCount = pixelsCount * 4;
	m_imageRGBData = new unsigned char[bytesCount];
	memset(m_imageRGBData, 255, bytesCount); // Making sure, that all alpha bytes are opaque
	const unsigned char* sourcePixel = rgbData;
	unsigned char* destinationPixel = m_imageRGBData;
	for (int pixel = 0; pixel < pixelsCount; pixel++)
	{
		destinationPixel[0] = sourcePixel[2];
		destinationPixel[1] = sourcePixel[1];
		destinationPixel[2] = sourcePixel[0];
		destinationPixel += 4;
		sourcePixel += 3;
	}
	m_image = new QImage(m_imageRGBData, (int)width, (int)height, QImage::Format_RGB32);
	repaint();
}

void QtPaintCanvas::disposeImage(void)
{
	if (m_image)
	{
		delete(m_image);
		m_image = NULL;
	}
	if (m_imageRGBData)
	{
		delete[] m_imageRGBData;
		m_imageRGBData = NULL;
	}
}

void QtPaintCanvas::drawImage(double x, double y, double width, double height)
{
	if (m_image && width >= 1.0 && height >= 1.0) // >= 1.0 because otherwise an assertion would fail deep in Qt
	{	
		double widthResizeFactor = width/(double)m_image->width();

		m_qPainter->setRenderHint(QPainter::SmoothPixmapTransform, widthResizeFactor < 2.75);

		m_qPainter->drawImage(QRect((int)x, (int)y, (int)width, (int)height), *m_image);
	}
}

void QtPaintCanvas::setState(const char *state)
{
	PaintCanvasBase::setState(state);
	repaint();
}
