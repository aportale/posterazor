/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
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
#include "Fl_Paint_Canvas_Base.h"

class Fl_Gl_Paint_Canvas: public Fl_Gl_Window, public Fl_Paint_Canvas_Base
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

	virtual void DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void GetSize(double &width, double &height) const;

	virtual void SetImage(const unsigned char* rgbData, double width, double height);
	virtual void DisposeImage(void);
	virtual void DrawImage(double x, double y, double width, double height);

	virtual unsigned int GetTexturesColumnsCount(void) const                      {return (int)ceil((double)m_imageWidth / (double)m_texturesSize);}
	virtual unsigned int GetTexturesRowsCount(void) const                         {return (int)ceil((double)m_imageHeight / (double)m_texturesSize);}
	virtual unsigned int GetTexturesCount(void) const                             {return GetTexturesColumnsCount() * GetTexturesRowsCount();}
	virtual unsigned int GetLastTexturesColumnPixelsColumns(void) const           {return m_imageWidth - (GetTexturesColumnsCount()-1)*m_texturesSize;}
	virtual unsigned int GetLastTexturesRowPixelsRows(void) const                 {return m_imageHeight - (GetTexturesRowsCount()-1)*m_texturesSize;}
	virtual unsigned int GetTexturesColumnPixelColumns(unsigned int column) const {return column < GetTexturesColumnsCount()-1?m_texturesSize:GetLastTexturesColumnPixelsColumns();}
	virtual unsigned int GetTexturesRowPixelRows(unsigned int row) const          {return row < GetTexturesRowsCount()-1?m_texturesSize:GetLastTexturesRowPixelsRows();}
};

#endif Fl_Gl_Paint_Canvas_h