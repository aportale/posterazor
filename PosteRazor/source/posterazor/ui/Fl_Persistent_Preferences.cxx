#include "Fl_Persistent_Preferences.h"

Fl_Persistent_Preferences::Fl_Persistent_Preferences(const char *vendor, const char *application)
	:Fl_Preferences(Fl_Preferences::USER, vendor, application)
{
}

void Fl_Persistent_Preferences::SetInteger(int value, const char *key)
{
	Fl_Preferences::set(key, value);
}

void Fl_Persistent_Preferences::SetDouble(double value, const char *key)
{
	Fl_Preferences::set(key, value);
}

void Fl_Persistent_Preferences::SetBoolean(bool value, const char *key)
{
	Fl_Preferences::set(key, (int)(value?1:0));
}

void Fl_Persistent_Preferences::SetString(const char *value, const char *key)
{
	Fl_Preferences::set(key, value);
}

int Fl_Persistent_Preferences::GetInteger(const char *key, int defaultValue)
{
	int returnValue = defaultValue;
	Fl_Preferences::get(key, returnValue, defaultValue);
	return returnValue;
}

double Fl_Persistent_Preferences::GetDouble(const char *key, double defaultValue)
{
	double returnValue = defaultValue;
	Fl_Preferences::get(key, returnValue, defaultValue);
	return returnValue;
}

bool Fl_Persistent_Preferences::GetBoolean(const char *key, bool defaultValue)
{
	int returnValue = defaultValue?1:0;
	Fl_Preferences::get(key, returnValue, defaultValue?1:0);
	return returnValue==0?false:true;
}

const char *Fl_Persistent_Preferences::GetString(const char *key, const char *defaultValue)
{
	static char returnValue[2048]="";
	Fl_Preferences::get(key, returnValue, defaultValue, sizeof(returnValue));
	returnValue[sizeof(returnValue)-1] = '\0';
	return returnValue;
}
