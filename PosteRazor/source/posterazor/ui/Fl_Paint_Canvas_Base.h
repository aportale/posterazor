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

#ifndef Fl_Paint_Canvas_Base_h
#define Fl_Paint_Canvas_Base_h

#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include "../../tools/PaintCanvasInterface.h"

class Fl_Paint_Canvas_Base: public PaintCanvasInterface
{
protected:
	char m_stateString[1024];
	unsigned char m_backgroundColor[3];
	double m_maxImageWidth;
	double m_maxImageHeight;
	
public:
	Fl_Paint_Canvas_Base();

	virtual void SetState(const char *state);
	virtual void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue);
	virtual void RequestImage(void);

	virtual void DisposeImage(void) = 0;
};

#endif
