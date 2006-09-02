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

#ifndef PosteRazorSettingsDialog_h
#define PosteRazorSettingsDialog_h

#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"
#include "Fl_Paint_Canvas_Group.h"
#include "translations/Translations.h"

typedef struct
{
	enum PosteRazor::eUnitsOfLength UnitOfLength;
	enum Fl_Paint_Canvas_Group::ePaintCanvasTypes previewType;
	enum Translations::eLanguages language;
} posteRazorSettings;

class SettingsChangementHandler
{
public:
	virtual void HandleOptionsChangement(posteRazorSettings *settings) = 0;
};

class PosteRazorSettingsDialog: public PosteRazorSettingsDialogUI
{
	posteRazorSettings *m_settings;
	SettingsChangementHandler *m_changementHandler;
	int m_unitOfLengthButtonsCount;
	Fl_Button **m_unitOfLengthButtons;
	int m_languageButtonsCount;
	Fl_Button **m_languageButtons;
	Fl_RGB_Image **m_languageButtonImages;

public:
	PosteRazorSettingsDialog();
	~PosteRazorSettingsDialog();

	void SetOptionsAndHandler(posteRazorSettings *settings, SettingsChangementHandler *changementHandler);
	static void HandleUnitOfLengthChoice_cb(Fl_Widget *widget, void *userData);
	void HandleUnitOfLengthChoice(void);
	void HandleUseOpenGLChangement(void);
	static void HandleLanguageChoice_cb(Fl_Widget *widget, void *userData);
	void HandleLanguageChoice(void);
	void UpdateLanguage(void);
	void show(void);
};

#endif
