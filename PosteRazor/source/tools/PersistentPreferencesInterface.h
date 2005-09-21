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