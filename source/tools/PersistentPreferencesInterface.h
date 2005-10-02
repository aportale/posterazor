/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
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
	virtual void SetInteger(int value, const char *key) = 0;
	virtual void SetDouble(double value, const char *key) = 0;
	virtual void SetBoolean(bool value, const char *key) = 0;
	virtual void SetString(const char *value, const char *key) = 0;
	
	virtual int GetInteger(const char *key, int defaultValue) = 0;
	virtual double GetDouble(const char *key, double defaultValue) = 0;
	virtual bool GetBoolean(const char *key, bool defaultValue) = 0;
	virtual const char *GetString(const char *key, const char *defaultValue) = 0;
};

#endif // PersistentPreferencesInterface_h