/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
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
#if defined (WIN32)
#include <Windows.h>
#elif defined (__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <stdio.h> // for NULL

Translations *Translations::m_instance = 0;

typedef struct
{
	TranslationInterface *translation;
	Translations::eLanguages language;
} TranslationSet;

static const TranslationSet TranslationsMap[] =
{
	{&english, Translations::eLanguageUndefined}
	,{&english, Translations::eLanguageEnglish}
	,{&german, Translations::eLanguageGerman}
	,{&french, Translations::eLanguageFrench}
#ifdef WIN32
	,{&polish, Translations::eLanguagePolish}
#endif
	,{&italian, Translations::eLanguageItalian}
	,{&dutch, Translations::eLanguageDutch}
	,{&spanish, Translations::eLanguageSpanish}
};

static int TranslationsMapItemsCount = sizeof(TranslationsMap) / sizeof(TranslationSet);

class TranslationSwitcher: public Translations
{
private:
	TranslationInterface *m_selectedTranslation;
	eLanguages m_language;

public:
	TranslationSwitcher()
	{
		SelectLangue(eLanguageUndefined);
	}

	void SelectLangue(eLanguages language)
	{
		m_language = language;
		m_selectedTranslation = GetTranslationOfLanguage(m_language);
	}

	eLanguages GetSelectedLanguage(void)
	{
		return m_language;
	}

	int GetLanguagesCount(void)
	{
		return TranslationsMapItemsCount - 1;
	}

	eLanguages GetLanguageForIndex(int index)
	{
		return TranslationsMap[index + 1].language;
	}

	TranslationInterface* GetTranslationOfLanguage(eLanguages language)
	{
		TranslationInterface* foundTranslation = NULL;
		for (int i = 0; i < TranslationsMapItemsCount; i++)
		{
			if(TranslationsMap[i].language == language)
			{
				foundTranslation = TranslationsMap[i].translation;
				break;
			}
		}
		if (!foundTranslation)
			foundTranslation = TranslationsMap[0].translation;
		return foundTranslation;
	}

	eLanguages GetSystemLanguage(void)
	{
		eLanguages systemLanguage = eLanguageUndefined;
#if defined (WIN32)
		LANGID langID = GetSystemDefaultLangID();
		WORD primaryLangID = PRIMARYLANGID(langID);
		systemLanguage =
			(primaryLangID == LANG_ENGLISH)?eLanguageEnglish:
			(primaryLangID == LANG_GERMAN)?eLanguageGerman:
			(primaryLangID == LANG_FRENCH)?eLanguageFrench:
			(primaryLangID == LANG_POLISH)?eLanguagePolish:
			(primaryLangID == LANG_ITALIAN)?eLanguageItalian:
			(primaryLangID == LANG_DUTCH)?eLanguageDutch:
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
		systemLanguage =
			(CFStringCompare(language, languageEnglish, 0) == kCFCompareEqualTo)?eLanguageEnglish:
			(CFStringCompare(language, languageGerman, 0) == kCFCompareEqualTo)?eLanguageGerman:
			(CFStringCompare(language, languageFrench, 0) == kCFCompareEqualTo)?eLanguageFrench:
			(CFStringCompare(language, languageItalian, 0) == kCFCompareEqualTo)?eLanguageItalian:
			(CFStringCompare(language, languageDutch, 0) == kCFCompareEqualTo)?eLanguageDutch:
			eLanguageUndefined;
		CFRelease(languageEnglish);
		CFRelease(languageGerman);
		CFRelease(languageFrench);
		CFRelease(languageItalian);
		CFRelease(languageDutch);

		CFRelease(preferredLanguages);
		CFRelease(locArray);
#endif
		return systemLanguage;
	}


	const char* languageName(void)                    {return m_selectedTranslation->languageName();}

	const char* absoluteSize(void)                    {return m_selectedTranslation->absoluteSize();}
	const char* allImageFormats(void)                 {return m_selectedTranslation->allImageFormats();}
	const char* back(void)                            {return m_selectedTranslation->back();}
	const char* borders(void)                         {return m_selectedTranslation->borders();}
	const char* bottom(void)                          {return m_selectedTranslation->bottom();}
	const char* bottomLeft(void)                      {return m_selectedTranslation->bottomLeft();}
	const char* bottomRight(void)                     {return m_selectedTranslation->bottomRight();}
	const char* cancel(void)                          {return m_selectedTranslation->cancel();}
	const char* colorType(void)                       {return m_selectedTranslation->colorType();}
	const char* custom(void)                          {return m_selectedTranslation->custom();}
	const char* fileCouldNotBeLoaded(void)            {return m_selectedTranslation->fileCouldNotBeLoaded();}
	const char* fileCouldNotBeSaved(void)             {return m_selectedTranslation->fileCouldNotBeSaved();}
	const char* format(void)                          {return m_selectedTranslation->format();}
	const char* grayscale(void)                       {return m_selectedTranslation->grayscale();}
	const char* height(void)                          {return m_selectedTranslation->height();}
	const char* imageAlignment(void)                  {return m_selectedTranslation->imageAlignment();}
	const char* imageInformations(void)               {return m_selectedTranslation->imageInformations();}
	const char* imageSize(void)                       {return m_selectedTranslation->imageSize();}
	const char* inputImage(void)                      {return m_selectedTranslation->inputImage();}
	const char* landscape(void)                       {return m_selectedTranslation->landscape();}
	const char* language(void)                        {return m_selectedTranslation->language();}
	const char* languageExplanation(void)             {return m_selectedTranslation->languageExplanation();}
	const char* launchPDFApplication(void)            {return m_selectedTranslation->launchPDFApplication();}
	const char* left(void)                            {return m_selectedTranslation->left();}
	const char* loadAnInputImage(void)                {return m_selectedTranslation->loadAnInputImage();}
	const char* monochrome(void)                      {return m_selectedTranslation->monochrome();}
	const char* next(void)                            {return m_selectedTranslation->next();}
	const char* orientation(void)                     {return m_selectedTranslation->orientation();}
	const char* overlappingPosition(void)             {return m_selectedTranslation->overlappingPosition();}
	const char* overlappingSize(void)                 {return m_selectedTranslation->overlappingSize();}
	const char* overwriteFile(void)                   {return m_selectedTranslation->overwriteFile();}
	const char* pages(void)                           {return m_selectedTranslation->pages();}
	const char* palette(void)                         {return m_selectedTranslation->palette();}
	const char* paperFormat(void)                     {return m_selectedTranslation->paperFormat();}
	const char* portrait(void)                        {return m_selectedTranslation->portrait();}
	const char* posteRazorHelp(void)                  {return m_selectedTranslation->posteRazorHelp();}
	const char* posteRazorSettings(void)              {return m_selectedTranslation->posteRazorSettings();}
	const char* posteRazorWebSiteURL(void)            {return m_selectedTranslation->posteRazorWebSiteURL();}
	const char* posteRazorWebSite(void)               {return m_selectedTranslation->posteRazorWebSite();}
	const char* previewWithOpenGL(void)               {return m_selectedTranslation->previewWithOpenGL();}
	const char* previewWithOpenGLExplanation(void)    {return m_selectedTranslation->previewWithOpenGLExplanation();}
	const char* resolution(void)                      {return m_selectedTranslation->resolution();}
	const char* right(void)                           {return m_selectedTranslation->right();}
	const char* saveThePoster(void)                   {return m_selectedTranslation->saveThePoster();}
	const char* saveThePosterAs(void)                 {return m_selectedTranslation->saveThePosterAs();}
	const char* settings(void)                        {return m_selectedTranslation->settings();}
	const char* Size(void)                            {return m_selectedTranslation->Size();}
	const char* sizeInPages(void)                     {return m_selectedTranslation->sizeInPages();}
	const char* sizeInPercent(void)                   {return m_selectedTranslation->sizeInPercent();}
	const char* sizeInPixels(void)                    {return m_selectedTranslation->sizeInPixels();}
	const char* sizeInUnitOfLength(void)              {return m_selectedTranslation->sizeInUnitOfLength();}
	const char* standard(void)                        {return m_selectedTranslation->standard();}
	const char* stepXOfY(void)                        {return m_selectedTranslation->stepXOfY();}
	const char* top(void)                             {return m_selectedTranslation->top();}
	const char* topLeft(void)                         {return m_selectedTranslation->topLeft();}
	const char* topRight(void)                        {return m_selectedTranslation->topRight();}
	const char* unitOfLength(void)                    {return m_selectedTranslation->unitOfLength();}
	const char* unitOfLengthExplanation(void)         {return m_selectedTranslation->unitOfLengthExplanation();}
	const char* width(void)                           {return m_selectedTranslation->width();}

	const char* stepTitle01(void)                     {return m_selectedTranslation->stepTitle01();}
	const char* stepTitle02(void)                     {return m_selectedTranslation->stepTitle02();}
	const char* stepTitle03(void)                     {return m_selectedTranslation->stepTitle03();}
	const char* stepTitle04(void)                     {return m_selectedTranslation->stepTitle04();}
	const char* stepTitle05(void)                     {return m_selectedTranslation->stepTitle05();}
	const char* helpHtml(void)                        {return m_selectedTranslation->helpHtml();}

	const int flagImageWidth(void)                    {return m_selectedTranslation->flagImageWidth();}
	const int flagImageHeight(void)                   {return m_selectedTranslation->flagImageHeight();}
	const unsigned char* flagImageRGBData(void)       {return m_selectedTranslation->flagImageRGBData();}
};

Translations* Translations::Instance(void)
{
	if (m_instance == 0)
		m_instance = (Translations*)new TranslationSwitcher();

	return m_instance;
}
