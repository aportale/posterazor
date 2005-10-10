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

#include "Fl_Gl_Paint_Canvas.h"
#include <FL/gl.h>
#include <string.h>

#define BORDER 9.0

Fl_Gl_Paint_Canvas::Fl_Gl_Paint_Canvas(int width, int height, int x, int y)
	:Fl_Gl_Window(width, height, x, y), PaintCanvasInterface()
{
	m_stateString[0] = '\0';
	m_imageRGBData = NULL;
	m_image = NULL;
	SetBackgroundColor(255, 255, 255);
}

Fl_Gl_Paint_Canvas::~Fl_Gl_Paint_Canvas()
{
	DisposeImage();
}

void Fl_Gl_Paint_Canvas::SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)
{
	m_backgroundColor[0] = red;
	m_backgroundColor[1] = green;
	m_backgroundColor[2] = blue;
}

void Fl_Gl_Paint_Canvas::SetState(const char *state)
{
	strncpy(m_stateString, state, sizeof(m_stateString));
	m_stateString[sizeof(m_stateString)-1] = '\0';
}

void Fl_Gl_Paint_Canvas::draw()
{
	if (!valid())
	{
		valid(1);
		glLoadIdentity();
		glViewport(0, 0, w(), h());
		glOrtho(0, w(), 0, h(), -1, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glLineWidth(1);
	}
	glClear(GL_COLOR_BUFFER_BIT);

	DrawFilledRect(-BORDER, -BORDER, w(), h(), m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 255);

	m_painter->PaintOnCanvas(this, m_stateString);
}

void Fl_Gl_Paint_Canvas::DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height > 0 && height < 1)
	{
		DrawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width > 0 && width < 1)
	{
		DrawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		glColor4d(red/255.0, green/255.0, blue/255.0, alpha/255.0);
		glRectd(x + BORDER, y + BORDER, width + x + BORDER, height + y + BORDER);
	}
}

void Fl_Gl_Paint_Canvas::DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height > 0 && height < 1)
	{
		DrawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width > 0 && width < 1)
	{
		DrawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		glColor4d(red/255.0, green/255.0, blue/255.0, alpha/255.0);
		glBegin(GL_LINE_LOOP);
		double x1 = x + BORDER;
		double x2 = width + x + BORDER;
		double y1 = y + BORDER;
		double y2 = height + y + BORDER;
		glVertex2d(x1, y1);
		glVertex2d(x2, y1);
		glVertex2d(x2, y2);
		glVertex2d(x1, y2);
		glEnd();
	}
}

void Fl_Gl_Paint_Canvas::DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	glColor4d(red/255.0, green/255.0, blue/255.0, alpha/255.0);
	glBegin(GL_LINES);
	glVertex2d(x1 + BORDER, y1 + BORDER);
	glVertex2d(x2 + BORDER, y2 + BORDER);
	glEnd();
}

void Fl_Gl_Paint_Canvas::GetSize(double &width, double &height) const
{
	width = w() - BORDER - BORDER;
	height = h() - BORDER - BORDER;
}

void Fl_Gl_Paint_Canvas::RequestImage(void)
{
	if (m_painter)
		m_painter->GetImage(this);
}

void Fl_Gl_Paint_Canvas::SetImage(const unsigned char* rgbData, double width, double height)
{
	DisposeImage();
	m_imageRGBData = new unsigned char[(int)width * (int)height * 3];
	memcpy(m_imageRGBData, rgbData, (int)width * (int)height * 3);
	m_image = new Fl_RGB_Image(m_imageRGBData, (int)width, (int)height);
}

void Fl_Gl_Paint_Canvas::DisposeImage(void)
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

void Fl_Gl_Paint_Canvas::DrawImage(double x, double y, double width, double height)
{
	if (m_image)
	{
		glPushMatrix();
		glTranslated(x + BORDER, y + BORDER, 0);
		glDrawPixels((GLsizei)width, (GLsizei)height, GL_RGB, GL_UNSIGNED_BYTE, m_imageRGBData);
		glPopMatrix();
	}
}
