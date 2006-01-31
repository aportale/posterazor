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

#include "Fl_Draw_Paint_Canvas.h"
#include <FL/fl_draw.H>
#include <string.h>

#define BORDER 9

Fl_Draw_Paint_Canvas::Fl_Draw_Paint_Canvas(int x, int y, int width, int height)
	:Fl_Box(x, y, width, height), Fl_Paint_Canvas_Base()
{
	m_imageRGBData = NULL;
	m_image = NULL;
	m_scaledImage = NULL;
}

Fl_Draw_Paint_Canvas::~Fl_Draw_Paint_Canvas()
{
	DisposeImage();
}

void Fl_Draw_Paint_Canvas::draw()
{
	Fl_Box::draw();
	DrawFilledRect(-BORDER, -BORDER, w(), h(), m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 255);
	m_painter->PaintOnCanvas(this, m_stateString);
}

void Fl_Draw_Paint_Canvas::DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (alpha < 255)
	{
		DrawRect(x, y, width, height, red, green, blue, alpha);
	}
	else
	{
		fl_color(red, green, blue);
		fl_rectf((int)(x + Fl_Box::x() + BORDER), (int)(y + Fl_Box::y() + BORDER), (int)width, (int)height);
	}
}

void Fl_Draw_Paint_Canvas::DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
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
		fl_color(red, green, blue);
		fl_rect((int)(x + Fl_Box::x() + BORDER), (int)(y + Fl_Box::y() + BORDER), (int)width, (int)height);
	}
}

void Fl_Draw_Paint_Canvas::DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	fl_color(red, green, blue);
	fl_line((int)(x1 + Fl_Box::x() + BORDER), (int)(y1 + Fl_Box::y() + BORDER), (int)(x2 + Fl_Box::x() + BORDER), (int)(y2 + Fl_Box::y() + BORDER));
}

void Fl_Draw_Paint_Canvas::GetSize(double &width, double &height) const
{
	width = w() - BORDER - BORDER;
	height = h() - BORDER - BORDER;
}

void Fl_Draw_Paint_Canvas::SetImage(const unsigned char* rgbData, double width, double height)
{
	DisposeImage();
	m_imageRGBData = new unsigned char[(int)width * (int)height * 3];
	memcpy(m_imageRGBData, rgbData, (int)width * (int)height * 3);
	m_image = new Fl_RGB_Image(m_imageRGBData, (int)width, (int)height);
	redraw();
}

void Fl_Draw_Paint_Canvas::DisposeImage(void)
{
	if (m_image)
	{
		delete(m_image);
		m_image = NULL;
	}
	if (m_scaledImage)
	{
		delete(m_scaledImage);
		m_scaledImage = NULL;
	}
	if (m_imageRGBData)
	{
		delete[] m_imageRGBData;
		m_imageRGBData = NULL;
	}
}

void Fl_Draw_Paint_Canvas::DrawImage(double x, double y, double width, double height)
{
	if (m_image)
	{
		if (m_scaledImage && (width != m_scaledImage->w() || height != m_scaledImage->h()))
		{
			delete m_scaledImage;
			m_scaledImage = NULL;
		}

		if (!m_scaledImage)
			m_scaledImage = m_image->copy((int)width, (int)height);

		if (m_scaledImage)
			m_scaledImage->draw((int)(x + Fl_Box::x() + BORDER), (int)(y + Fl_Box::y() + BORDER));
	}
}
