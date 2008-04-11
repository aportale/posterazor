/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
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

#ifndef FLIMAGETEXTBUTTON_H
#define FLIMAGETEXTBUTTON_H

#include <FL/Fl_Button.H>

class Fl_Image;

class FlImageTextButton: public Fl_Button
{
public:
	FlImageTextButton(int x, int y, int w, int h, const char* label = 0);
	void labelImage(Fl_Image *image);

private:
	Fl_Image *m_labelImage;

	virtual void draw();
};

#endif // FLIMAGETEXTBUTTON_H
