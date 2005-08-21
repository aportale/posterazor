/*
 *  Fl_PaintCanvas.cpp
 *  PosteRazor
 *
 *  Created by Alessandro Portale on 17.08.05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "Fl_Paint_Canvas.h"
#include <FL/fl_draw.H>
#include <string.h>

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

void Fl_Paint_Canvas::DrawFilledRect(int x, int y, int width, int height, unsigned char red, unsigned char green, unsigned char blue)
{
	fl_color(red, green, blue);
	fl_rectf(x + Fl_Box::x() + 5, y + Fl_Box::y() + 5, width, height);
}

void Fl_Paint_Canvas::GetSize(int &width, int &height)
{
	width = w() - 10;
	height = h() - 10;
}

void Fl_Paint_Canvas::RequestImage(void)
{
	if (m_painter)
		m_painter->GetImage(this);
}

void Fl_Paint_Canvas::SetImage(const unsigned char* rgbData, int width, int height)
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

void Fl_Paint_Canvas::DrawImage(int x, int y, int width, int height)
{
	if (m_image)
	{
		if (m_scaledImage && width != m_scaledImage->w() && height != m_scaledImage->h())
		{
			delete m_scaledImage;
			m_scaledImage = NULL;
		}

		if (!m_scaledImage)
			m_scaledImage = m_image->copy(width, height);

		m_scaledImage->draw(x + Fl_Box::x() + 5, y + Fl_Box::y() + 5);
	}
}
