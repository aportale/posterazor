/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2008 by Alessandro Portale
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

#ifndef Translations_h
#define Translations_h

#include "TranslationInterface.h"

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

    static const Translations& instance(void);
    static eLanguages getSystemLanguage(void);
    static int getLanguagesCount(void);
    static eLanguages getLanguageForIndex(int index);
    static const TranslationInterface& getTranslationOfLanguage(eLanguages language);
    
    virtual void selectLangue(eLanguages language) const = 0;
    virtual eLanguages getSelectedLanguage(void) const = 0;
};

#endif
