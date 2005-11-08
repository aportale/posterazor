#ifndef Translations_h
#define Translations_h

#include "TranslationInterface.h"

#define TRANSLATIONS Translations::Instance()

class Translations: public TranslationInterface
{
private:
	static Translations *m_instance;

protected:
	Translations() {}

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
	virtual enum eLanguages GetSelectedLanguage(void) = 0;
	virtual int GetLanguagesCount(void) = 0;
	virtual enum eLanguages GetLanguageForIndex(int index) = 0;
	virtual TranslationInterface* GetTranslationOfLanguage(enum eLanguages language) = 0;
};

#endif