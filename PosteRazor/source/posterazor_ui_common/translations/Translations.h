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

#ifndef Translations_h
#define Translations_h

#include "TranslationInterface.h"

#define TRANSLATIONS Translations::Instance()

class Translations: public TranslationInterface
{
protected:
	Translations() {}

public:
	virtual ~Translations(void) {};

	enum eLanguages
	{
		eLanguageUndefined
		,eLanguageEnglish
		,eLanguageGerman
		,eLanguageFrench
#ifdef WIN32
		,eLanguagePolish
#endif
		,eLanguageItalian
		,eLanguageDutch
		,eLanguageSpanish
		,eLanguageBrazilianPortuguese
	};

	static const Translations* Instance(void);
	
	virtual void SelectLangue(eLanguages language) const = 0;
	virtual eLanguages GetSelectedLanguage(void) const = 0;
	virtual int GetLanguagesCount(void) const = 0;
	virtual eLanguages GetLanguageForIndex(int index) const = 0;
	virtual const TranslationInterface* GetTranslationOfLanguage(eLanguages language) const = 0;
	virtual eLanguages GetSystemLanguage(void) const = 0;
};

#endif
