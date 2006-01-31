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

#include "Fl_Paint_Canvas_Base.h"
#include <FL/fl_draw.H>
#include <string.h>

Fl_Paint_Canvas_Base::Fl_Paint_Canvas_Base()
	:PaintCanvasInterface()
{
	m_stateString[0] = '\0';
	m_backgroundColor[0] = m_backgroundColor[1] = m_backgroundColor[2] = 0;
	m_maxImageWidth = 1024;
	m_maxImageHeight = 1024;
}

void Fl_Paint_Canvas_Base::SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)
{
	m_backgroundColor[0] = red;
	m_backgroundColor[1] = green;
	m_backgroundColor[2] = blue;
}

void Fl_Paint_Canvas_Base::SetState(const char *state)
{
	strncpy(m_stateString, state, sizeof(m_stateString));
	m_stateString[sizeof(m_stateString)-1] = '\0';
}

void Fl_Paint_Canvas_Base::RequestImage(void)
{
	if (m_painter)
		m_painter->GetImage(this, m_maxImageWidth, m_maxImageHeight);
}
