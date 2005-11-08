#ifndef Translations_h
#define Translations_h

#include "TranslationInterface.h"

#define TRANSLATIONS Translations::Instance()

class Translations: public TranslationInterface
{
private:
	static Translations *m_instance;

public:
	virtual ~Translations(void) {};

	enum eLanguages
	{
		eLanguageUndefined,
		eLanguageEnglish,
		eLanguageGerman,
		eLanguageItalian
	};

	static Translations* Instance(void);
	
	virtual void SelectLangue(enum eLanguages language) = 0;
};

#endif