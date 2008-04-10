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

#ifndef PersistentPreferencesInterface_h
#define PersistentPreferencesInterface_h

class PersistentPreferencesInterface
{
public:
	virtual ~PersistentPreferencesInterface() {}

	virtual void setInteger(int value, const char *key) = 0;
	virtual void setDouble(double value, const char *key) = 0;
	virtual void setBoolean(bool value, const char *key) = 0;
	virtual void setString(const char *value, const char *key) = 0;
	
	virtual int getInteger(const char *key, int defaultValue) = 0;
	virtual double getDouble(const char *key, double defaultValue) = 0;
	virtual bool getBoolean(const char *key, bool defaultValue) = 0;
	virtual const char *getString(const char *key, const char *defaultValue) = 0;
};

#endif
