/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "QPaintCanvas.h"
#include <QImage>
#include <QPainter>

#define BORDER 9

QPaintCanvas::QPaintCanvas(QWidget *parent)
:	QWidget(parent)
,	PaintCanvasBase()
,	m_image(NULL)
,	m_imageRGBData(NULL)
{
}

QPaintCanvas::~QPaintCanvas()
{
	DisposeImage();
}

void QPaintCanvas::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	m_qPainter = &painter;
	DrawFilledRect(-BORDER, -BORDER, width(), height(), m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 255);
	m_painter->PaintOnCanvas(this, m_stateString);
	m_qPainter = NULL;
}

void QPaintCanvas::DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (alpha < 255)
	{
		DrawRect(x, y, width, height, red, green, blue, alpha);
	}
	else
	{
		m_qPainter->fillRect((int)(x + BORDER), (int)(y + BORDER), (int)width, (int)height, QColor(qRgb(red, green, blue)));
	}
}

void QPaintCanvas::DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height < 1)
	{
		DrawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width < 1)
	{
		DrawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		m_qPainter->setPen(QColor(qRgb(red, green, blue)));
		m_qPainter->drawRect((int)(x + BORDER), (int)(y + BORDER), (int)width, (int)height);
	}
}

void QPaintCanvas::DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	m_qPainter->setPen(QColor(qRgb(red, green, blue)));
	m_qPainter->drawLine((int)(x1 + BORDER), (int)(y1 + BORDER), (int)(x2 + BORDER), (int)(y2 + BORDER));
}

void QPaintCanvas::GetSize(double &width, double &height) const
{
	width = (double)(this->width()) - BORDER - BORDER;
	height = (double)(this->height()) - BORDER - BORDER;
}

void QPaintCanvas::SetImage(const unsigned char* rgbData, double width, double height)
{
	DisposeImage();
	m_imageRGBData = new unsigned char[(int)width * (int)height * 3];
	memcpy(m_imageRGBData, rgbData, (int)width * (int)height * 3);
	m_image = new QImage(m_imageRGBData, (int)width, (int)height, QImage::Format_RGB32);
	repaint();
}

void QPaintCanvas::DisposeImage(void)
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

void QPaintCanvas::DrawImage(double x, double y, double width, double height)
{
	if (m_image)
	{
		m_qPainter->drawImage(QRect((int)(x + BORDER), (int)(y + BORDER), (int)width, (int)height), *m_image);
	}
}
