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

#include "PaintCanvasBase.h"

PaintCanvasBase::PaintCanvasBase()
	: PaintCanvasInterface()
	, m_maxImageWidth(1024)
	, m_maxImageHeight(1024)
	, m_painter(NULL)
{
	m_backgroundColor[0] = m_backgroundColor[1] = m_backgroundColor[2] = 0;
}

void PaintCanvasBase::setPainterInterface(const PainterInterface *painter)
{
	m_painter = painter;
}

void PaintCanvasBase::setBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)
{
	m_backgroundColor[0] = red;
	m_backgroundColor[1] = green;
	m_backgroundColor[2] = blue;
}

void PaintCanvasBase::setState(const QString &state)
{
	m_stateString = state;
}

void PaintCanvasBase::requestImage(void)
{
	if (m_painter)
		m_painter->getImage(this, m_maxImageWidth, m_maxImageHeight);
}
