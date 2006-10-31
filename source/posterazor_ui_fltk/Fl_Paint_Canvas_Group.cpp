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

#include "Fl_Paint_Canvas_Group.h"
#include <string.h>
#include <FL/Fl.H>

Fl_Paint_Canvas_Group::Fl_Paint_Canvas_Group(int x, int y, int width, int height)
	:Fl_Group(x, y, width, height)
{
	m_imageRGBData = NULL;
	m_imageWidth = 0;
	m_imageHeight = 0;

	begin();
	m_drawPaintCanvas = new Fl_Draw_Paint_Canvas(x+1, y+1, width-2, height-2);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas = new Fl_Gl_Paint_Canvas(x+1, y+1, width-2, height-2, this);
#endif
	end();

	Fl::get_system_colors();
	unsigned int backgroundColor = Fl::get_color(color2());
	SetBackgroundColor((backgroundColor >> 24) & 255, (backgroundColor >> 16) & 255, (backgroundColor >> 8) & 255);
	
	resizable(m_drawPaintCanvas);

#ifndef NO_OPENGL_PREVIEW
	SetPaintCanvasType(PaintCanvasTypeGL);
#else
	SetPaintCanvasType(PaintCanvasTypeDraw);
#endif
}

void Fl_Paint_Canvas_Group::redraw(void)
{
	Fl_Group::redraw();
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->redraw();
#endif
}

void Fl_Paint_Canvas_Group::SetPaintCanvasType(ePaintCanvasTypes type)
{
#ifndef NO_OPENGL_PREVIEW
	m_paintCanvasType = type;

	if (GetPaintCanvasType()==PaintCanvasTypeDraw)
	{
		m_glPaintCanvas->hide();
		m_glPaintCanvas->DisposeImage();
	}
	else
	{
		m_drawPaintCanvas->hide();
		m_drawPaintCanvas->DisposeImage();
	}

	GetPaintCanvasWidget()->show();
	Fl::wait(0.0); // 0.0 is needed for OSX!
	if (m_imageRGBData)
		GetPaintCanvasBase()->SetImage(m_imageRGBData, m_imageWidth, m_imageHeight);
#endif
}

Fl_Paint_Canvas_Base *Fl_Paint_Canvas_Group::GetPaintCanvasBase(void) const
{
#ifndef NO_OPENGL_PREVIEW
	if (GetPaintCanvasType()==PaintCanvasTypeDraw)
		return dynamic_cast<Fl_Paint_Canvas_Base*>(m_drawPaintCanvas);
	else
		return dynamic_cast<Fl_Paint_Canvas_Base*>(m_glPaintCanvas);
#else
	return m_drawPaintCanvas;
#endif
}

Fl_Widget *Fl_Paint_Canvas_Group::GetPaintCanvasWidget(void) const
{
#ifndef NO_OPENGL_PREVIEW
	if (GetPaintCanvasType()==PaintCanvasTypeDraw)
		return dynamic_cast<Fl_Widget*>(m_drawPaintCanvas);
	else
		return dynamic_cast<Fl_Widget*>(m_glPaintCanvas);
#else
	return m_drawPaintCanvas;
#endif
}

void Fl_Paint_Canvas_Group::SetPainterInterface(const PainterInterface *painter)
{
	PaintCanvasInterface::SetPainterInterface(painter);
	m_drawPaintCanvas->SetPainterInterface(m_painter);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->SetPainterInterface(m_painter);
#endif
}

void Fl_Paint_Canvas_Group::SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)
{
	m_drawPaintCanvas->SetBackgroundColor(red, green, blue);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->SetBackgroundColor(red, green, blue);
#endif
}

void Fl_Paint_Canvas_Group::DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {}
void Fl_Paint_Canvas_Group::DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {}
void Fl_Paint_Canvas_Group::DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {}
void Fl_Paint_Canvas_Group::GetSize(double &width, double &height) const {}

void Fl_Paint_Canvas_Group::SetImage(const unsigned char* rgbData, double width, double height)
{
	DisposeImage();
	m_imageRGBData = new unsigned char[(int)width * (int)height * 3];
	memcpy(m_imageRGBData, rgbData, (int)width * (int)height * 3);
	m_imageWidth = width;
	m_imageHeight = height;
	Fl::wait();
	GetPaintCanvasBase()->SetImage(m_imageRGBData, m_imageWidth, m_imageHeight);
}

void Fl_Paint_Canvas_Group::DrawImage(double x, double y, double width, double height) {}

void Fl_Paint_Canvas_Group::SetState(const char *state)
{
	Fl_Paint_Canvas_Base::SetState(state);
	m_drawPaintCanvas->SetState(m_stateString);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->SetState(m_stateString);
#endif
}

void Fl_Paint_Canvas_Group::DisposeImage(void)
{
	m_drawPaintCanvas->DisposeImage();
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->DisposeImage();
#endif

	if (m_imageRGBData)
	{
		delete[] m_imageRGBData;
		m_imageRGBData = NULL;
		m_imageWidth = 0;
		m_imageHeight = 0;
	}
}
