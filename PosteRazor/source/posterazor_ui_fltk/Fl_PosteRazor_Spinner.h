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

#ifndef Fl_PosteRazor_Spinner_h
#define Fl_PosteRazor_Spinner_h

#include <FL/Fl_Group.H>

class Fl_Input;
class Fl_Repeat_Button;

class Fl_PosteRazor_Spinner: public Fl_Group
{

public:
	Fl_PosteRazor_Spinner(int x, int y, int width, int height, const char* label=0);
	static const char* quickNDirtyDoubleToString(double value);
	static double Fl_PosteRazor_Spinner::Round(double Zahl, int Stellen);
	void setSpinnerVisible(bool visible);
	double value();
	void value(double value);

private:
	Fl_Input *m_input;
	Fl_Repeat_Button *m_increaseButton;
	Fl_Repeat_Button *m_decreaseButton;
	bool m_spinnerVisible;

	void UpdateButtonsState(void);
	static void handleButtonPress_cb(Fl_Repeat_Button *button, void *data);
	void handleButtonPress(Fl_Repeat_Button *button);
	static void handleValueChangement_cb(Fl_Input *input, void *data);
	void handleValueChangement(Fl_Input *input);
};

#endif
