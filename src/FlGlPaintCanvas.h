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

#ifndef FLGLPAINTCANVAS_H
#define FLGLPAINTCANVAS_H

#include <math.h>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#include "PaintCanvasBase.h"

class FlGlPaintCanvas: public Fl_Gl_Window, public PaintCanvasBase
{
private:
	GLuint *m_texturesNames;
	unsigned int m_imageWidth;
	unsigned int m_imageHeight;
	GLint m_texturesSize;
	Fl_Widget *m_parentWidget;
	
public:
	FlGlPaintCanvas(int x, int y, int width, int height, Fl_Widget *parentWidget);
	~FlGlPaintCanvas();

	virtual void draw();
	virtual int handle(int event);

	virtual void drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void getSize(double &width, double &height) const;

	virtual void setImage(const unsigned char* rgbData, double width, double height);
	virtual void disposeImage(void);
	virtual void drawImage(double x, double y, double width, double height);

	virtual unsigned int getTexturesColumnsCount(void) const;
	virtual unsigned int getTexturesRowsCount(void) const;
	virtual unsigned int getTexturesCount(void) const;
	virtual unsigned int getLastTexturesColumnPixelsColumns(void) const;
	virtual unsigned int getLastTexturesRowPixelsRows(void) const;
	virtual unsigned int getTexturesColumnPixelColumns(unsigned int column) const;
	virtual unsigned int getTexturesRowPixelRows(unsigned int row) const;
};

#endif // FLGLPAINTCANVAS_H
