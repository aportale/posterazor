/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2011 by Alessandro Portale
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

#include "Translations.h"

#include "TranslationEnglish.h"
#include "TranslationGerman.h"
#include "TranslationFrench.h"
#ifdef WIN32
#include "TranslationPolish.h"
#endif
#include "TranslationItalian.h"
#include "TranslationDutch.h"
#include "TranslationSpanish.h"
#include "TranslationBrazilianPortuguese.h"
#if defined (WIN32)
#include <Windows.h>
#elif defined (__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

static const struct {
	const TranslationInterface &translation;
	Translations::eLanguages language;
} TranslationsMap[] = {
	{english, Translations::eLanguageUndefined}
	,{english, Translations::eLanguageEnglish}
	,{german, Translations::eLanguageGerman}
	,{french, Translations::eLanguageFrench}
#ifdef WIN32
	,{polish, Translations::eLanguagePolish}
#endif
	,{italian, Translations::eLanguageItalian}
	,{dutch, Translations::eLanguageDutch}
	,{spanish, Translations::eLanguageSpanish}
	,{brazilianPortuguese, Translations::eLanguageBrazilianPortuguese}
};
static const int TranslationsMapItemsCount = sizeof(TranslationsMap) / sizeof(TranslationsMap[0]);

class TranslationSwitcher: public Translations
{
private:
	mutable const TranslationInterface *m_selectedTranslation;
	mutable eLanguages m_language;

public:
	TranslationSwitcher()
	{
		selectLangue(eLanguageUndefined);
	}

	void selectLangue(eLanguages language) const
	{
		m_language = language;
		m_selectedTranslation = &getTranslationOfLanguage(m_language);
	}

	eLanguages getSelectedLanguage(void) const
	{
		return m_language;
	}

	const char* languageName(void) const                     {return m_selectedTranslation->languageName();}

	const char* absoluteSize(void) const                     {return m_selectedTranslation->absoluteSize();}
	const char* allImageFormats(void) const                  {return m_selectedTranslation->allImageFormats();}
	const char* back(void) const                             {return m_selectedTranslation->back();}
	const char* borders(void) const                          {return m_selectedTranslation->borders();}
	const char* bottom(void) const                           {return m_selectedTranslation->bottom();}
	const char* bottomLeft(void) const                       {return m_selectedTranslation->bottomLeft();}
	const char* bottomRight(void) const                      {return m_selectedTranslation->bottomRight();}
	const char* cancel(void) const                           {return m_selectedTranslation->cancel();}
	const char* colorType(void) const                        {return m_selectedTranslation->colorType();}
	const char* custom(void) const                           {return m_selectedTranslation->custom();}
	const char* fileCouldNotBeLoaded(void) const             {return m_selectedTranslation->fileCouldNotBeLoaded();}
	const char* fileCouldNotBeSaved(void) const              {return m_selectedTranslation->fileCouldNotBeSaved();}
	const char* format(void) const                           {return m_selectedTranslation->format();}
	const char* grayscale(void) const                        {return m_selectedTranslation->grayscale();}
	const char* height(void) const                           {return m_selectedTranslation->height();}
	const char* imageAlignment(void) const                   {return m_selectedTranslation->imageAlignment();}
	const char* imageInformations(void) const                {return m_selectedTranslation->imageInformations();}
	const char* imageSize(void) const                        {return m_selectedTranslation->imageSize();}
	const char* inputImage(void) const                       {return m_selectedTranslation->inputImage();}
	const char* landscape(void) const                        {return m_selectedTranslation->landscape();}
	const char* language(void) const                         {return m_selectedTranslation->language();}
	const char* languageExplanation(void) const              {return m_selectedTranslation->languageExplanation();}
	const char* launchPDFApplication(void) const             {return m_selectedTranslation->launchPDFApplication();}
	const char* left(void) const                             {return m_selectedTranslation->left();}
	const char* loadAnInputImage(void) const                 {return m_selectedTranslation->loadAnInputImage();}
	const char* monochrome(void) const                       {return m_selectedTranslation->monochrome();}
	const char* next(void) const                             {return m_selectedTranslation->next();}
	const char* orientation(void) const                      {return m_selectedTranslation->orientation();}
	const char* overlappingPosition(void) const              {return m_selectedTranslation->overlappingPosition();}
	const char* overlappingSize(void) const                  {return m_selectedTranslation->overlappingSize();}
	const char* overwriteFile(void) const                    {return m_selectedTranslation->overwriteFile();}
	const char* pages(void) const                            {return m_selectedTranslation->pages();}
	const char* palette(void) const                          {return m_selectedTranslation->palette();}
	const char* paperFormat(void) const                      {return m_selectedTranslation->paperFormat();}
	const char* portrait(void) const                         {return m_selectedTranslation->portrait();}
	const char* posteRazorHelp(void) const                   {return m_selectedTranslation->posteRazorHelp();}
	const char* posteRazorSettings(void) const               {return m_selectedTranslation->posteRazorSettings();}
	const char* posteRazorWebSiteURL(void) const             {return m_selectedTranslation->posteRazorWebSiteURL();}
	const char* posteRazorWebSite(void) const                {return m_selectedTranslation->posteRazorWebSite();}
	const char* previewWithOpenGL(void) const                {return m_selectedTranslation->previewWithOpenGL();}
	const char* previewWithOpenGLExplanation(void) const     {return m_selectedTranslation->previewWithOpenGLExplanation();}
	const char* resolution(void) const                       {return m_selectedTranslation->resolution();}
	const char* right(void) const                            {return m_selectedTranslation->right();}
	const char* saveThePoster(void) const                    {return m_selectedTranslation->saveThePoster();}
	const char* saveThePosterAs(void) const                  {return m_selectedTranslation->saveThePosterAs();}
	const char* settings(void) const                         {return m_selectedTranslation->settings();}
	const char* Size(void) const                             {return m_selectedTranslation->Size();}
	const char* sizeInPages(void) const                      {return m_selectedTranslation->sizeInPages();}
	const char* sizeInPercent(void) const                    {return m_selectedTranslation->sizeInPercent();}
	const char* sizeInPixels(void) const                     {return m_selectedTranslation->sizeInPixels();}
	const char* sizeInUnitOfLength(void) const               {return m_selectedTranslation->sizeInUnitOfLength();}
	const char* standard(void) const                         {return m_selectedTranslation->standard();}
	const char* stepXOfY(void) const                         {return m_selectedTranslation->stepXOfY();}
	const char* top(void) const                              {return m_selectedTranslation->top();}
	const char* topLeft(void) const                          {return m_selectedTranslation->topLeft();}
	const char* topRight(void) const                         {return m_selectedTranslation->topRight();}
	const char* unitOfLength(void) const                     {return m_selectedTranslation->unitOfLength();}
	const char* unitOfLengthExplanation(void) const          {return m_selectedTranslation->unitOfLengthExplanation();}
	const char* width(void) const                            {return m_selectedTranslation->width();}

	const char* stepTitle01(void) const                      {return m_selectedTranslation->stepTitle01();}
	const char* stepTitle02(void) const                      {return m_selectedTranslation->stepTitle02();}
	const char* stepTitle03(void) const                      {return m_selectedTranslation->stepTitle03();}
	const char* stepTitle04(void) const                      {return m_selectedTranslation->stepTitle04();}
	const char* stepTitle05(void) const                      {return m_selectedTranslation->stepTitle05();}
	const char* helpHtml(void) const                         {return m_selectedTranslation->helpHtml();}

	const int flagImageWidth(void) const                     {return m_selectedTranslation->flagImageWidth();}
	const int flagImageHeight(void) const                    {return m_selectedTranslation->flagImageHeight();}
	const unsigned char* flagImageRGBData(void) const        {return m_selectedTranslation->flagImageRGBData();}
};

const Translations& Translations::instance(void)
{
	static const TranslationSwitcher switcher;
	return switcher;
}

Translations::eLanguages Translations::getSystemLanguage(void)
{
	eLanguages systemLanguage = eLanguageUndefined;
#if defined (WIN32)
	const LANGID langID = GetSystemDefaultLangID();
	const WORD primaryLangID = PRIMARYLANGID(langID);
	const WORD subLangID = SUBLANGID(langID);
	systemLanguage =
		(primaryLangID == LANG_ENGLISH)?eLanguageEnglish:
	(primaryLangID == LANG_GERMAN)?eLanguageGerman:
	(primaryLangID == LANG_FRENCH)?eLanguageFrench:
	(primaryLangID == LANG_POLISH)?eLanguagePolish:
	(primaryLangID == LANG_ITALIAN)?eLanguageItalian:
	(primaryLangID == LANG_DUTCH)?eLanguageDutch:
	(primaryLangID == LANG_SPANISH)?eLanguageSpanish:
	(primaryLangID == LANG_PORTUGUESE && subLangID == SUBLANG_PORTUGUESE_BRAZILIAN)?eLanguageBrazilianPortuguese:
	eLanguageUndefined;
#elif defined (__APPLE__)
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFArrayRef locArray = CFBundleCopyBundleLocalizations(mainBundle);
	CFArrayRef preferredLanguages = CFBundleCopyPreferredLocalizationsFromArray(locArray);
	CFStringRef language = (CFStringRef)CFArrayGetValueAtIndex(preferredLanguages, 0);

	CFStringRef languageEnglish = CFSTR("English");
	CFStringRef languageGerman = CFSTR("German");
	CFStringRef languageFrench = CFSTR("French");
	CFStringRef languageItalian = CFSTR("Italian");
	CFStringRef languageDutch = CFSTR("Dutch");
	CFStringRef languageSpanish = CFSTR("Spanish");
	CFStringRef languageBrazilianPortuguese = CFSTR("BrazilianPortuguese");
	systemLanguage =
		(CFStringCompare(language, languageEnglish, 0) == kCFCompareEqualTo)?eLanguageEnglish:
	(CFStringCompare(language, languageGerman, 0) == kCFCompareEqualTo)?eLanguageGerman:
	(CFStringCompare(language, languageFrench, 0) == kCFCompareEqualTo)?eLanguageFrench:
	(CFStringCompare(language, languageItalian, 0) == kCFCompareEqualTo)?eLanguageItalian:
	(CFStringCompare(language, languageDutch, 0) == kCFCompareEqualTo)?eLanguageDutch:
	(CFStringCompare(language, languageSpanish, 0) == kCFCompareEqualTo)?eLanguageSpanish:
	(CFStringCompare(language, languageBrazilianPortuguese, 0) == kCFCompareEqualTo)?eLanguageBrazilianPortuguese:
	eLanguageUndefined;
	CFRelease(languageEnglish);
	CFRelease(languageGerman);
	CFRelease(languageFrench);
	CFRelease(languageItalian);
	CFRelease(languageDutch);
	CFRelease(languageSpanish);
	CFRelease(languageBrazilianPortuguese);

	CFRelease(preferredLanguages);
	CFRelease(locArray);
#endif
	return systemLanguage;
}

int Translations::getLanguagesCount(void)
{
	return TranslationsMapItemsCount - 1;
}

Translations::eLanguages Translations::getLanguageForIndex(int index)
{
	return TranslationsMap[index + 1].language;
}

const TranslationInterface& Translations::getTranslationOfLanguage(eLanguages language)
{
	const TranslationInterface* foundTranslation = 0;
	for (int i = 0; i < TranslationsMapItemsCount; i++) {
		if(TranslationsMap[i].language == language)	{
			foundTranslation = &TranslationsMap[i].translation;
			break;
		}
	}
	if (!foundTranslation)
		foundTranslation = &TranslationsMap[0].translation;
	return *foundTranslation;
}
