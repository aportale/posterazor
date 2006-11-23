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

#include "QPersistentPreferences.h"

QPersistentPreferences::QPersistentPreferences(QObject *parent)
:	QSettings(parent)
{
}

void QPersistentPreferences::setInteger(int value, const char *key)
{
	setValue(key, value);
}

void QPersistentPreferences::setDouble(double value, const char *key)
{
	setValue(key, value);
}

void QPersistentPreferences::setBoolean(bool value, const char *key)
{
	setValue(key, value);
}

void QPersistentPreferences::setString(const char *value, const char *key)
{
	setValue(key, value);
}

int QPersistentPreferences::getInteger(const char *key, int defaultValue)
{
	return value(key, defaultValue).toInt();
}

double QPersistentPreferences::getDouble(const char *key, double defaultValue)
{
	return value(key, defaultValue).toDouble();
}

bool QPersistentPreferences::getBoolean(const char *key, bool defaultValue)
{
	return value(key, defaultValue).toBool();
}

const char *QPersistentPreferences::getString(const char *key, const char *defaultValue)
{
	return value(key, defaultValue).toString().toAscii();
}
