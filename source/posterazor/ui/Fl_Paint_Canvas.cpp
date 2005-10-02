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

#include "Fl_Paint_Canvas.h"
#include <FL/fl_draw.H>
#include <string.h>

#define BORDER 10

Fl_Paint_Canvas::Fl_Paint_Canvas(int width, int height, int x, int y)
	:Fl_Box(width, height, x, y), PaintCanvasInterface()
{
	m_stateString[0] = '\0';
	m_image = NULL;
	m_scaledImage = NULL;
}

Fl_Paint_Canvas::~Fl_Paint_Canvas()
{
	DisposeImage();
}

void Fl_Paint_Canvas::SetState(const char *state)
{
	strncpy(m_stateString, state, sizeof(m_stateString));
	m_stateString[sizeof(m_stateString)-1] = '\0';
}

void Fl_Paint_Canvas::draw()
{
	Fl_Box::draw();
	m_painter->PaintOnCanvas(this, m_stateString);
}

void Fl_Paint_Canvas::DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue)
{
	fl_color(red, green, blue);
	fl_rectf(x + Fl_Box::x() + BORDER, y + Fl_Box::y() + BORDER, width, height);
}

void Fl_Paint_Canvas::DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue)
{
	if (height < 1)
	{
		DrawLine(x, y, x+width, y, red, green, blue);
	}
	else if (width < 1)
	{
		DrawLine(x, y, x, y+height, red, green, blue);
	}
	else
	{
		fl_color(red, green, blue);
		fl_rect(x + Fl_Box::x() + BORDER, y + Fl_Box::y() + BORDER, width, height);
	}
}

void Fl_Paint_Canvas::DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue)
{
	fl_color(red, green, blue);
	fl_line(x1 + Fl_Box::x() + BORDER, y1 + Fl_Box::y() + BORDER, x2 + Fl_Box::x() + BORDER, y2 + Fl_Box::y() + BORDER);
}

void Fl_Paint_Canvas::GetSize(double &width, double &height) const
{
	width = w() - BORDER - BORDER;
	height = h() - BORDER - BORDER;
}

void Fl_Paint_Canvas::RequestImage(void)
{
	if (m_painter)
		m_painter->GetImage(this);
}

void Fl_Paint_Canvas::SetImage(const unsigned char* rgbData, double width, double height)
{
	DisposeImage();
	m_image = new Fl_RGB_Image(rgbData, width, height);
}

void Fl_Paint_Canvas::DisposeImage(void)
{
	if (m_image)
	{
		delete(m_image);
		m_image = 0;
	}
	if (m_scaledImage)
	{
		delete(m_scaledImage);
		m_scaledImage = NULL;
	}
}

void Fl_Paint_Canvas::DrawImage(double x, double y, double width, double height)
{
	if (m_image)
	{
		if (m_scaledImage && (width != m_scaledImage->w() || height != m_scaledImage->h()))
		{
			delete m_scaledImage;
			m_scaledImage = NULL;
		}

		if (!m_scaledImage)
			m_scaledImage = m_image->copy(width, height);

		if (m_scaledImage)
			m_scaledImage->draw(x + Fl_Box::x() + BORDER, y + Fl_Box::y() + BORDER);
	}
}
