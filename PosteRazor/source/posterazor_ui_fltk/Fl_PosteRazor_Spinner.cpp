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

#include "Fl_PosteRazor_Spinner.h"
#include <FL/Fl_Input.H>
#include <FL/Fl_Repeat_Button.H>

#define REPEATBUTTONWIDTH 16

Fl_PosteRazor_Spinner::Fl_PosteRazor_Spinner(int x, int y, int width, int height, const char* label)
	:Fl_Group(x, y, width, height, label)
{
	int repeatButtonHeight = (int)((float)height/2);

	begin();
	m_input = new Fl_Input(x, y, width - REPEATBUTTONWIDTH, height);
	m_increaseButton = new Fl_Repeat_Button(x + width - REPEATBUTTONWIDTH, y, REPEATBUTTONWIDTH, repeatButtonHeight);
	m_decreaseButton = new Fl_Repeat_Button(x + width - REPEATBUTTONWIDTH, y + height - repeatButtonHeight, REPEATBUTTONWIDTH, repeatButtonHeight);
	end();
}
