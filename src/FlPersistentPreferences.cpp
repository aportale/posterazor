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

#include "FlPersistentPreferences.h"

FlPersistentPreferences::FlPersistentPreferences(const char *vendor, const char *application)
	:Fl_Preferences(Fl_Preferences::USER, vendor, application)
{
}

void FlPersistentPreferences::setInteger(int value, const char *key)
{
	Fl_Preferences::set(key, value);
}

void FlPersistentPreferences::setDouble(double value, const char *key)
{
	Fl_Preferences::set(key, value);
}

void FlPersistentPreferences::setBoolean(bool value, const char *key)
{
	Fl_Preferences::set(key, (int)(value?1:0));
}

void FlPersistentPreferences::setString(const char *value, const char *key)
{
	Fl_Preferences::set(key, value);
}

int FlPersistentPreferences::getInteger(const char *key, int defaultValue)
{
	int returnValue = defaultValue;
	Fl_Preferences::get(key, returnValue, defaultValue);
	return returnValue;
}

double FlPersistentPreferences::getDouble(const char *key, double defaultValue)
{
	double returnValue = defaultValue;
	Fl_Preferences::get(key, returnValue, defaultValue);
	return returnValue;
}

bool FlPersistentPreferences::getBoolean(const char *key, bool defaultValue)
{
	int returnValue = defaultValue?1:0;
	Fl_Preferences::get(key, returnValue, defaultValue?1:0);
	return returnValue==0?false:true;
}

const char *FlPersistentPreferences::getString(const char *key, const char *defaultValue)
{
	static char returnValue[2048]="";
	Fl_Preferences::get(key, returnValue, defaultValue, sizeof(returnValue));
	returnValue[sizeof(returnValue)-1] = '\0';
	return returnValue;
}
