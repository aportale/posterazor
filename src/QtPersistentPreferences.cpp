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

#include "QtPersistentPreferences.h"

QtPersistentPreferences::QtPersistentPreferences(QObject *parent)
:	QSettings(parent)
{
}

void QtPersistentPreferences::setInteger(int value, const char *key)
{
	setValue(key, value);
}

void QtPersistentPreferences::setDouble(double value, const char *key)
{
	setValue(key, value);
}

void QtPersistentPreferences::setBoolean(bool value, const char *key)
{
	setValue(key, value);
}

void QtPersistentPreferences::setString(const char *value, const char *key)
{
	setValue(key, value);
}

int QtPersistentPreferences::getInteger(const char *key, int defaultValue)
{
	return value(key, defaultValue).toInt();
}

double QtPersistentPreferences::getDouble(const char *key, double defaultValue)
{
	return value(key, defaultValue).toDouble();
}

bool QtPersistentPreferences::getBoolean(const char *key, bool defaultValue)
{
	return value(key, defaultValue).toBool();
}

const char *QtPersistentPreferences::getString(const char *key, const char *defaultValue)
{
	return value(key, defaultValue).toString().toAscii();
}
