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

#ifndef Fl_Gl_Paint_Canvas_h
#define Fl_Gl_Paint_Canvas_h

#include <math.h>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#include <FL/Fl_Image.H>
#include "PaintCanvasBase.h"

class Fl_Gl_Paint_Canvas: public Fl_Gl_Window, public PaintCanvasBase
{
private:
	GLuint *m_texturesNames;
	unsigned int m_imageWidth;
	unsigned int m_imageHeight;
	GLint m_texturesSize;
	Fl_Widget *m_parentWidget;
	
public:
	Fl_Gl_Paint_Canvas(int x, int y, int width, int height, Fl_Widget *parentWidget);
	~Fl_Gl_Paint_Canvas();

	virtual void draw();
	virtual int handle(int event);

	virtual void drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void getSize(double &width, double &height) const;

	virtual void setImage(const unsigned char* rgbData, double width, double height);
	virtual void disposeImage(void);
	virtual void drawImage(double x, double y, double width, double height);

	virtual unsigned int getTexturesColumnsCount(void) const                      {return (int)ceil((double)m_imageWidth / (double)m_texturesSize);}
	virtual unsigned int getTexturesRowsCount(void) const                         {return (int)ceil((double)m_imageHeight / (double)m_texturesSize);}
	virtual unsigned int getTexturesCount(void) const                             {return getTexturesColumnsCount() * getTexturesRowsCount();}
	virtual unsigned int getLastTexturesColumnPixelsColumns(void) const           {return m_imageWidth - (getTexturesColumnsCount()-1)*m_texturesSize;}
	virtual unsigned int getLastTexturesRowPixelsRows(void) const                 {return m_imageHeight - (getTexturesRowsCount()-1)*m_texturesSize;}
	virtual unsigned int getTexturesColumnPixelColumns(unsigned int column) const {return column < getTexturesColumnsCount()-1?m_texturesSize:getLastTexturesColumnPixelsColumns();}
	virtual unsigned int getTexturesRowPixelRows(unsigned int row) const          {return row < getTexturesRowsCount()-1?m_texturesSize:getLastTexturesRowPixelsRows();}
};

#endif
