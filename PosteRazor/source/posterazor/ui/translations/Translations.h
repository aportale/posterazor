/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
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
private:
	static Translations *m_instance;

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
	};

	static Translations* Instance(void);
	
	virtual void SelectLangue(enum eLanguages language) = 0;
	virtual enum eLanguages GetSelectedLanguage(void) = 0;
	virtual int GetLanguagesCount(void) = 0;
	virtual enum eLanguages GetLanguageForIndex(int index) = 0;
	virtual TranslationInterface* GetTranslationOfLanguage(enum eLanguages language) = 0;
	virtual enum eLanguages GetSystemLanguage(void) = 0;
};

#endif
