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

#include "FlImageTextButton.h"
#include <FL/Fl_Image.H>

FlImageTextButton::FlImageTextButton(int x, int y, int w, int h, const char* label)
	: Fl_Button(x, y, w, h, label)
	, m_labelImage(0)
{
}

void FlImageTextButton::labelImage(Fl_Image *image)
{
	m_labelImage = image;
}

void FlImageTextButton::draw()
{
	Fl_Button::draw();

	if (m_labelImage)
		m_labelImage->draw(x() + 6, y() + (h()-m_labelImage->h()) / 2);
}
