#ifndef Fl_Persistent_Preferences_h
#define Fl_Persistent_Preferences_h

#include <FL/Fl_Preferences.H>
#include "..\tools\PersistentPreferencesInterface.h"

class Fl_Persistent_Preferences: public Fl_Preferences, public PersistentPreferencesInterface
{
public:
	Fl_Persistent_Preferences(const char *vendor, const char *application);

	void SetInteger(int value, const char *key);
	void SetDouble(double value, const char *key);
	void SetBoolean(bool value, const char *key);
	void SetString(const char *value, const char *key);
	
	int GetInteger(const char *key, int defaultValue);
	double GetDouble(const char *key, double defaultValue);
	bool GetBoolean(const char *key, bool defaultValue);
	const char *GetString(const char *key, const char *defaultValue);
};

#endif // Fl_Persistent_Preferences_h