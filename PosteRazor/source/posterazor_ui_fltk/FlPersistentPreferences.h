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

#ifndef Fl_Persistent_Preferences_h
#define Fl_Persistent_Preferences_h

#include <FL/Fl_Preferences.H>
#include "PersistentPreferencesInterface.h"

class Fl_Persistent_Preferences: public Fl_Preferences, public PersistentPreferencesInterface
{
public:
	Fl_Persistent_Preferences(const char *vendor, const char *application);

	void setInteger(int value, const char *key);
	void setDouble(double value, const char *key);
	void setBoolean(bool value, const char *key);
	void setString(const char *value, const char *key);
	
	int getInteger(const char *key, int defaultValue);
	double getDouble(const char *key, double defaultValue);
	bool getBoolean(const char *key, bool defaultValue);
	const char *getString(const char *key, const char *defaultValue);
};

#endif
