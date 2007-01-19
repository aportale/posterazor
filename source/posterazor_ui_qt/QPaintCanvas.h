/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
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

#ifndef QPaintCanvas_h
#define QPaintCanvas_h

#include <QWidget>
#include "PaintCanvasBase.h"

class QImage;
class QPainter;

class QPaintCanvas: public QWidget, public PaintCanvasBase
{
	Q_OBJECT

private:
	unsigned char *m_imageRGBData;
	QImage *m_image;
	QPainter *m_qPainter;
	
public:
	QPaintCanvas(QWidget *parent);
	~QPaintCanvas();

	virtual void paintEvent(QPaintEvent *event);
	virtual void drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void getSize(double &width, double &height) const;

	virtual void setImage(const unsigned char* rgbData, double width, double height);
	virtual void disposeImage(void);
	virtual void drawImage(double x, double y, double width, double height);

	virtual void setState(const char *state);
};

#endif
