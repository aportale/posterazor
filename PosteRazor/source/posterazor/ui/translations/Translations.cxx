#include "Translations.h"

#include "TranslationEnglish.h"
#include "TranslationGerman.h"
#include "TranslationItalian.h"
#define LANGUAGESCOUNT 2

Translations *Translations::m_instance = 0;

static TranslationEnglish m_english;
static TranslationGerman m_german;
static TranslationItalian m_italian;

typedef struct
{
	TranslationInterface *translation;
	Translations::eLanguages language;
} TranslationSet;

static const TranslationSet TranslationsMap[] =
{
	{&m_english, Translations::eLanguageUndefined},
	{&m_english, Translations::eLanguageEnglish},
	{&m_german, Translations::eLanguageGerman},
	{&m_italian, Translations::eLanguageItalian}
};

static int TranslationsMapItemsCount = sizeof(TranslationsMap) / sizeof(TranslationSet);

class TranslationSwitcher: public Translations
{
private:
	TranslationInterface *m_selectedTranslation;
	enum eLanguages m_language;

public:
	TranslationSwitcher()
	{
		SelectLangue(eLanguageUndefined);
	}

	void SelectLangue(enum eLanguages language)
	{
		m_language = language;
		for (int i = 0; i < TranslationsMapItemsCount; i++)
		{
			if(TranslationsMap[i].language == language)
			{
				m_selectedTranslation = TranslationsMap[i].translation;
				break;
			}
		}
	}

	const char* Borders(void)                         {return m_selectedTranslation->Borders();}
	const char* ImageInformations(void)               {return m_selectedTranslation->ImageInformations();}
	const char* InputImage(void)                      {return m_selectedTranslation->InputImage();}
	const char* Settings(void)                        {return m_selectedTranslation->Settings();}
	const char* StepXOfY(void)                        {return m_selectedTranslation->StepXOfY();}

	const char* StepTitle01(void)                     {return m_selectedTranslation->StepTitle01();}
	const char* StepTitle02(void)                     {return m_selectedTranslation->StepTitle02();}
	const char* StepTitle03(void)                     {return m_selectedTranslation->StepTitle03();}
	const char* StepTitle04(void)                     {return m_selectedTranslation->StepTitle04();}
	const char* StepTitle05(void)                     {return m_selectedTranslation->StepTitle05();}
	const char* HelpHtml(void)                        {return m_selectedTranslation->HelpHtml();}
};

Translations* Translations::Instance(void)
{
	if (m_instance == 0)
		m_instance = (Translations*)new TranslationSwitcher();

	return m_instance;
}