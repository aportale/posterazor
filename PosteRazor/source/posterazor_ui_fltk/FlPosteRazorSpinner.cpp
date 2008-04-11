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

#include "Fl_PosteRazor_Spinner.h"
#include <FL/Fl_Input.H>
#include <FL/Fl_Repeat_Button.H>
#include <stdio.h>
#include <math.h>
#ifndef WIN32
#include <iostream>
#endif

#define REPEATBUTTONWIDTH 15

Fl_PosteRazor_Spinner::Fl_PosteRazor_Spinner(int x, int y, int width, int height, const char* label)
	: Fl_Group(x, y, width, height, label)
	, m_spinnerVisible(true)
{
	begin();
	m_input = new Fl_Input(1, 1, 1, 1);
	m_input->type(FL_FLOAT_INPUT);
	m_input->value("1");
	m_input->callback((Fl_Callback*)handleValueChangement_cb, this);
	m_input->when(FL_WHEN_CHANGED);

	m_increaseButton = new Fl_Repeat_Button(1, 1, 1, 1);
	m_increaseButton->label("+");
	m_increaseButton->labelsize(11);
	m_increaseButton->labelfont(FL_COURIER_BOLD);
	m_increaseButton->box(FL_THIN_UP_BOX);
	m_increaseButton->callback((Fl_Callback*)handleButtonPress_cb, this);

	m_decreaseButton = new Fl_Repeat_Button(1, 1, 1, 1);
	m_decreaseButton->label("-");
	m_decreaseButton->labelsize(11);
	m_decreaseButton->labelfont(FL_COURIER_BOLD);
	m_decreaseButton->box(FL_THIN_UP_BOX);
	m_decreaseButton->callback((Fl_Callback*)handleButtonPress_cb, this);

	setSpinnerVisible(false);

	updateButtonsState();

	end();
}

const char* Fl_PosteRazor_Spinner::quickNDirtyDoubleToString(double value)
{
	static char valueString[200];
	sprintf(valueString, "%G", round(value, 4));
	return valueString;
}

// "round()" from http://www.c-plusplus.de/forum/viewtopic-var-t-is-39342.html
double Fl_PosteRazor_Spinner::round(double Zahl, int Stellen)
{
    return floor(Zahl * pow( 10.0, Stellen) + 0.5) * pow(10.0, -Stellen);
} 

void Fl_PosteRazor_Spinner::setSpinnerVisible(bool visible)
{
	m_spinnerVisible = visible;

	if (m_spinnerVisible) {
		const int repeatButtonHeight = (int)((float)h()/2);
		m_increaseButton->resize(x() + w() - REPEATBUTTONWIDTH, y(), REPEATBUTTONWIDTH, repeatButtonHeight);
		m_decreaseButton->resize(x() + w() - REPEATBUTTONWIDTH, y() + h() - repeatButtonHeight, REPEATBUTTONWIDTH, repeatButtonHeight);
		m_increaseButton->show();
		m_decreaseButton->show();
		m_input->resize(x(), y(), w() - REPEATBUTTONWIDTH, h());
	} else {
		m_input->resize(x(), y(), w(), h());
		m_increaseButton->hide();
		m_decreaseButton->hide();
	}
}

void Fl_PosteRazor_Spinner::updateButtonsState(void)
{
	if (isValueDecrementationDisabled())
		m_decreaseButton->deactivate();
	else
		m_decreaseButton->activate();
}

void Fl_PosteRazor_Spinner::handleButtonPress_cb(Fl_Repeat_Button *button, void *data)
{
	((Fl_PosteRazor_Spinner*)(data))->handleButtonPress(button);
}

void Fl_PosteRazor_Spinner::handleButtonPress(Fl_Repeat_Button *button)
{
	doValueSpin(button==m_increaseButton);
}

void Fl_PosteRazor_Spinner::doValueSpin(bool increase)
{
	const double increaseValue = increase?.5:-.50001;
	const double oldValue = value();
	const double newValue = round(oldValue + increaseValue, 0);
	if (newValue >= 1.0)
		value(newValue);
	updateButtonsState();
	do_callback();
}

void Fl_PosteRazor_Spinner::handleValueChangement_cb(Fl_Input *input, void *data)
{
	((Fl_PosteRazor_Spinner*)(data))->handleValueChangement(input);
}

void Fl_PosteRazor_Spinner::handleValueChangement(Fl_Input *input)
{
	updateButtonsState();
	do_callback();
}

double Fl_PosteRazor_Spinner::value()
{
	return atof(m_input->value());
}

void Fl_PosteRazor_Spinner::value(double value)
{
	m_input->value(quickNDirtyDoubleToString(value));
	updateButtonsState();
}

int Fl_PosteRazor_Spinner::handle(int event)
{
	const bool mouseIsOnGroup = 
		Fl::event_x() > x()
		&& Fl::event_x() <= x() + w()
		&& Fl::event_y() > y()
		&& Fl::event_y() <= y() + h();

	if (event == FL_MOUSEWHEEL && mouseIsOnGroup) {
		const bool increase = Fl::e_dy < 0;
		if (Fl::e_dy != 0 && (increase || !isValueDecrementationDisabled()))
			doValueSpin(increase);
		return 1; // consume event
	}
	else
		return Fl_Group::handle(event);
}

bool Fl_PosteRazor_Spinner::isValueDecrementationDisabled(void)
{
	return (value() - 1.0 <= 0.0);
}
