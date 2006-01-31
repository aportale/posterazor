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

#ifndef Fl_Paint_Canvas_Group_h
#define Fl_Paint_Canvas_Group_h

#include <FL/Fl_Group.H>
#ifndef NO_OPENGL_PREVIEW
  #include "Fl_Gl_Paint_Canvas.h"
#endif
#include "Fl_Draw_Paint_Canvas.h"

class Fl_Paint_Canvas_Group: public Fl_Group, public Fl_Paint_Canvas_Base
{
private:
	unsigned char *m_imageRGBData;
	double m_imageWidth;
	double m_imageHeight;

public:
	enum ePaintCanvasTypes
	{
		PaintCanvasTypeDraw,
		PaintCanvasTypeGL
	};

	Fl_Paint_Canvas_Group(int x, int y, int width, int height);

	void redraw(void);

	void SetPaintCanvasType(enum ePaintCanvasTypes type);
	enum ePaintCanvasTypes GetPaintCanvasType(void) const {return m_paintCanvasType;}
	Fl_Paint_Canvas_Base *GetPaintCanvasBase(void) const;
	Fl_Widget *GetPaintCanvasWidget(void) const;

	void SetPainterInterface(const PainterInterface *painter);
	void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue);
	void DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	void DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	void GetSize(double &width, double &height) const;
	void SetImage(const unsigned char* rgbData, double width, double height);
	void DrawImage(double x, double y, double width, double height);

	void SetState(const char *state);

	void DisposeImage(void);

protected:
	enum ePaintCanvasTypes m_paintCanvasType;
	Fl_Draw_Paint_Canvas *m_drawPaintCanvas;
#ifndef NO_OPENGL_PREVIEW
	Fl_Gl_Paint_Canvas *m_glPaintCanvas;
#endif
};

#endif Fl_Paint_Canvas_Group_h