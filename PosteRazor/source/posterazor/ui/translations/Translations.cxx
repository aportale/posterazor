/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
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
//#include "TranslationItalian.h"

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
//	,{&italian, Translations::eLanguageItalian} // My italian is too lousy, although it is my native language :/
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
		m_selectedTranslation = GetTranslationOfLanguage(m_language);
	}

	enum eLanguages GetSelectedLanguage(void)         {return m_language;}
	int GetLanguagesCount(void)                       {return TranslationsMapItemsCount - 1;}
	enum eLanguages GetLanguageForIndex(int index)    {return TranslationsMap[index + 1].language;}
	TranslationInterface* GetTranslationOfLanguage(enum eLanguages language)
	{
		TranslationInterface* foundTranslation;
		for (int i = 0; i < TranslationsMapItemsCount; i++)
		{
			if(TranslationsMap[i].language == language)
			{
				foundTranslation = TranslationsMap[i].translation;
				break;
			}
		}
		return foundTranslation;
	}


	const char* LanguageName(void)                    {return m_selectedTranslation->LanguageName();}

	const char* Back(void)                            {return m_selectedTranslation->Back();}
	const char* Borders(void)                         {return m_selectedTranslation->Borders();}
	const char* Bottom(void)                          {return m_selectedTranslation->Bottom();}
	const char* BottomLeft(void)                      {return m_selectedTranslation->BottomLeft();}
	const char* BottomRight(void)                     {return m_selectedTranslation->BottomRight();}
	const char* Cancel(void)                          {return m_selectedTranslation->Cancel();}
	const char* ColorType(void)                       {return m_selectedTranslation->ColorType();}
	const char* Custom(void)                          {return m_selectedTranslation->Custom();}
	const char* FileCouldNotBeLoaded(void)            {return m_selectedTranslation->FileCouldNotBeLoaded();}
	const char* Format(void)                          {return m_selectedTranslation->Format();}
	const char* Grayscale(void)                       {return m_selectedTranslation->Grayscale();}
	const char* Height(void)                          {return m_selectedTranslation->Height();}
	const char* ImageAlignment(void)                  {return m_selectedTranslation->ImageAlignment();}
	const char* ImageInformations(void)               {return m_selectedTranslation->ImageInformations();}
	const char* ImageSize(void)                       {return m_selectedTranslation->ImageSize();}
	const char* InputImage(void)                      {return m_selectedTranslation->InputImage();}
	const char* Landscape(void)                       {return m_selectedTranslation->Landscape();}
	const char* Language(void)                        {return m_selectedTranslation->Language();}
	const char* LanguageExplanation(void)             {return m_selectedTranslation->LanguageExplanation();}
	const char* Left(void)                            {return m_selectedTranslation->Left();}
	const char* Monochrome(void)                      {return m_selectedTranslation->Monochrome();}
	const char* Next(void)                            {return m_selectedTranslation->Next();}
	const char* Orientation(void)                     {return m_selectedTranslation->Orientation();}
	const char* OverlappingPosition(void)             {return m_selectedTranslation->OverlappingPosition();}
	const char* OverlappingSize(void)                 {return m_selectedTranslation->OverlappingSize();}
	const char* Pages(void)                           {return m_selectedTranslation->Pages();}
	const char* Palette(void)                         {return m_selectedTranslation->Palette();}
	const char* PaperFormat(void)                     {return m_selectedTranslation->PaperFormat();}
	const char* Portrait(void)                        {return m_selectedTranslation->Portrait();}
	const char* PosteRazorHelp(void)                  {return m_selectedTranslation->PosteRazorHelp();}
	const char* PosteRazorSettings(void)              {return m_selectedTranslation->PosteRazorSettings();}
	const char* PreviewWithOpenGL(void)               {return m_selectedTranslation->PreviewWithOpenGL();}
	const char* PreviewWithOpenGLExplanation(void)    {return m_selectedTranslation->PreviewWithOpenGLExplanation();}
	const char* Resolution(void)                      {return m_selectedTranslation->Resolution();}
	const char* Right(void)                           {return m_selectedTranslation->Right();}
	const char* Settings(void)                        {return m_selectedTranslation->Settings();}
	const char* SizeInPixels(void)                    {return m_selectedTranslation->SizeInPixels();}
	const char* SizeInUnitOfLength(void)              {return m_selectedTranslation->SizeInUnitOfLength();}
	const char* Standard(void)                        {return m_selectedTranslation->Standard();}
	const char* StepXOfY(void)                        {return m_selectedTranslation->StepXOfY();}
	const char* Top(void)                             {return m_selectedTranslation->Top();}
	const char* TopLeft(void)                         {return m_selectedTranslation->TopLeft();}
	const char* TopRight(void)                        {return m_selectedTranslation->TopRight();}
	const char* UnitOfLength(void)                    {return m_selectedTranslation->UnitOfLength();}
	const char* UnitOfLengthExplanation(void)         {return m_selectedTranslation->UnitOfLengthExplanation();}
	const char* Width(void)                           {return m_selectedTranslation->Width();}

	const char* StepTitle01(void)                     {return m_selectedTranslation->StepTitle01();}
	const char* StepTitle02(void)                     {return m_selectedTranslation->StepTitle02();}
	const char* StepTitle03(void)                     {return m_selectedTranslation->StepTitle03();}
	const char* StepTitle04(void)                     {return m_selectedTranslation->StepTitle04();}
	const char* StepTitle05(void)                     {return m_selectedTranslation->StepTitle05();}
	const char* HelpHtml(void)                        {return m_selectedTranslation->HelpHtml();}

	const int FlagImageWidth(void)                    {return m_selectedTranslation->FlagImageWidth();}
	const int FlagImageHeight(void)                   {return m_selectedTranslation->FlagImageHeight();}
	const unsigned char* FlagImageRGBData(void)       {return m_selectedTranslation->FlagImageRGBData();}
};

Translations* Translations::Instance(void)
{
	if (m_instance == 0)
		m_instance = (Translations*)new TranslationSwitcher();

	return m_instance;
}