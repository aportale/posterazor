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

#ifndef FLPOSTERAZORSPINNER_H
#define FLPOSTERAZORSPINNER_H

#include <FL/Fl_Group.H>

class Fl_Input;
class Fl_Repeat_Button;

class FlPosteRazorSpinner: public Fl_Group
{
public:
	FlPosteRazorSpinner(int x, int y, int width, int height, const char* label=0);
	static const char* quickNDirtyDoubleToString(double value);
	static double round(double Zahl, int Stellen);
	void setSpinnerVisible(bool visible);
	double value();
	void value(double value);
	int handle(int event);

private:
	Fl_Input *m_input;
	Fl_Repeat_Button *m_increaseButton;
	Fl_Repeat_Button *m_decreaseButton;
	bool m_spinnerVisible;

	void updateButtonsState(void);
	static void handleButtonPress_cb(Fl_Repeat_Button *button, void *data);
	void handleButtonPress(Fl_Repeat_Button *button);
	void doValueSpin(bool increase);
	static void handleValueChangement_cb(Fl_Input *input, void *data);
	void handleValueChangement(Fl_Input *input);
	bool isValueDecrementationDisabled(void);
};

#endif // FLPOSTERAZORSPINNER_H
