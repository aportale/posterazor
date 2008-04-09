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

#include "Fl_Paint_Canvas_Group.h"
#include <string.h>
#include <FL/Fl.H>

Fl_Paint_Canvas_Group::Fl_Paint_Canvas_Group(int x, int y, int width, int height)
	: Fl_Group(x, y, width, height)
	, m_imageRGBData(NULL)
	, m_imageWidth(0)
	, m_imageHeight(0)
{
	begin();
	m_drawPaintCanvas = new Fl_Draw_Paint_Canvas(x+1, y+1, width-2, height-2);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas = new Fl_Gl_Paint_Canvas(x+1, y+1, width-2, height-2, this);
#endif
	end();

	Fl::get_system_colors();
	const unsigned int backgroundColor = Fl::get_color(color2());
	setBackgroundColor((backgroundColor >> 24) & 255, (backgroundColor >> 16) & 255, (backgroundColor >> 8) & 255);
	
	resizable(m_drawPaintCanvas);

#ifndef NO_OPENGL_PREVIEW
	setPaintCanvasType(PaintCanvasTypeGL);
#else
	setPaintCanvasType(PaintCanvasTypeDraw);
#endif
}

void Fl_Paint_Canvas_Group::redraw(void)
{
	Fl_Group::redraw();
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->redraw();
#endif
}

void Fl_Paint_Canvas_Group::setPaintCanvasType(ePaintCanvasTypes type)
{
#ifndef NO_OPENGL_PREVIEW
	m_paintCanvasType = type;

	if (getPaintCanvasType()==PaintCanvasTypeDraw) {
		m_glPaintCanvas->hide();
		m_glPaintCanvas->disposeImage();
	} else {
		m_drawPaintCanvas->hide();
		m_drawPaintCanvas->disposeImage();
	}

	getPaintCanvasWidget()->show();
	Fl::wait(0.0); // 0.0 is needed for OSX!
	if (m_imageRGBData)
		getPaintCanvasBase()->setImage(m_imageRGBData, m_imageWidth, m_imageHeight);
#endif
}

PaintCanvasBase *Fl_Paint_Canvas_Group::getPaintCanvasBase(void) const
{
#ifndef NO_OPENGL_PREVIEW
	if (getPaintCanvasType()==PaintCanvasTypeDraw)
		return dynamic_cast<PaintCanvasBase*>(m_drawPaintCanvas);
	else
		return dynamic_cast<PaintCanvasBase*>(m_glPaintCanvas);
#else
	return m_drawPaintCanvas;
#endif
}

Fl_Widget *Fl_Paint_Canvas_Group::getPaintCanvasWidget(void) const
{
#ifndef NO_OPENGL_PREVIEW
	if (getPaintCanvasType()==PaintCanvasTypeDraw)
		return dynamic_cast<Fl_Widget*>(m_drawPaintCanvas);
	else
		return dynamic_cast<Fl_Widget*>(m_glPaintCanvas);
#else
	return m_drawPaintCanvas;
#endif
}

void Fl_Paint_Canvas_Group::setPainterInterface(const PainterInterface *painter)
{
	PaintCanvasBase::setPainterInterface(painter);
	m_drawPaintCanvas->setPainterInterface(m_painter);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->setPainterInterface(m_painter);
#endif
}

void Fl_Paint_Canvas_Group::setBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)
{
	m_drawPaintCanvas->setBackgroundColor(red, green, blue);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->setBackgroundColor(red, green, blue);
#endif
}

void Fl_Paint_Canvas_Group::drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {}
void Fl_Paint_Canvas_Group::drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {}
void Fl_Paint_Canvas_Group::drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {}
void Fl_Paint_Canvas_Group::getSize(double &width, double &height) const {}

void Fl_Paint_Canvas_Group::setImage(const unsigned char* rgbData, double width, double height)
{
	disposeImage();
	m_imageRGBData = new unsigned char[(int)width * (int)height * 3];
	memcpy(m_imageRGBData, rgbData, (int)width * (int)height * 3);
	m_imageWidth = width;
	m_imageHeight = height;
	Fl::wait();
	getPaintCanvasBase()->setImage(m_imageRGBData, m_imageWidth, m_imageHeight);
}

void Fl_Paint_Canvas_Group::drawImage(double x, double y, double width, double height) {}

void Fl_Paint_Canvas_Group::setState(const char *state)
{
	PaintCanvasBase::setState(state);
	m_drawPaintCanvas->setState(m_stateString);
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->setState(m_stateString);
#endif
}

void Fl_Paint_Canvas_Group::disposeImage(void)
{
	m_drawPaintCanvas->disposeImage();
#ifndef NO_OPENGL_PREVIEW
	m_glPaintCanvas->disposeImage();
#endif

	if (m_imageRGBData) {
		delete[] m_imageRGBData;
		m_imageRGBData = NULL;
		m_imageWidth = 0;
		m_imageHeight = 0;
	}
}
