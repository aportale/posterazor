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

#include "PosteRazorSettingsDialog.h"
#include "TranslationConstants.h"

PosteRazorSettingsDialog::PosteRazorSettingsDialog()
	:PosteRazorSettingsDialogUI(315, 400, "PosteRazor Settings")
{
#define SETTINGCHOICEBUTTONSSPACING 10

	int i;
	m_unitOfLengthButtonsCount = UnitsOfLength::GetUnitsOfLengthCount();
	m_unitOfLengthButtons = new Fl_Button*[m_unitOfLengthButtonsCount];
	int unitOfLengthButtonWidth = (m_unitOfLengthButtonsGroup->w() + SETTINGCHOICEBUTTONSSPACING) / m_unitOfLengthButtonsCount - SETTINGCHOICEBUTTONSSPACING;

	m_unitOfLengthButtonsGroup->begin();
	for (i = 0; i < m_unitOfLengthButtonsCount; i++)
	{
		const char* UnitOfLengthName = UnitsOfLength::GetUnitOfLengthName(UnitsOfLength::GetUnitOfLengthForIndex(i));
		m_unitOfLengthButtons[i] = new Fl_Button
		(
			m_unitOfLengthButtonsGroup->x() + i * (unitOfLengthButtonWidth+SETTINGCHOICEBUTTONSSPACING),
			m_unitOfLengthButtonsGroup->y(),
			unitOfLengthButtonWidth,
			m_unitOfLengthButtonsGroup->h(),
			UnitOfLengthName
		);

		m_unitOfLengthButtons[i]->type(FL_RADIO_BUTTON);
		m_unitOfLengthButtons[i]->color((Fl_Color)47);
		m_unitOfLengthButtons[i]->selection_color((Fl_Color)55);
		m_unitOfLengthButtons[i]->callback(HandleUnitOfLengthChoice_cb);
		m_unitOfLengthButtons[i]->user_data((void*)this);
	}
	m_unitOfLengthButtonsGroup->end();

	m_languageButtonsCount = TRANSLATIONS->GetLanguagesCount();
	m_languageButtons = new Fl_Button*[m_languageButtonsCount];
	m_languageButtonImages = new Fl_RGB_Image*[m_languageButtonsCount];
	int languageButtonWidth = (m_languageButtonsGroup->w() + SETTINGCHOICEBUTTONSSPACING) / m_languageButtonsCount - SETTINGCHOICEBUTTONSSPACING;

	m_languageButtonsGroup->begin();
	for (i = 0; i < m_languageButtonsCount; i++)
	{
		m_languageButtons[i] = new Fl_Button
		(
			m_languageButtonsGroup->x() + i * (languageButtonWidth+SETTINGCHOICEBUTTONSSPACING),
			m_languageButtonsGroup->y(),
			languageButtonWidth,
			m_languageButtonsGroup->h()
		);

		Translations::eLanguages language = TRANSLATIONS->GetLanguageForIndex(i);
		TranslationInterface *translation = TRANSLATIONS->GetTranslationOfLanguage(language);
		m_languageButtonImages[i] = new Fl_RGB_Image(translation->FlagImageRGBData(), translation->FlagImageWidth(), translation->FlagImageHeight());
		m_languageButtons[i]->image(m_languageButtonImages[i]);
		m_languageButtons[i]->tooltip(translation->LanguageName());
		m_languageButtons[i]->type(FL_RADIO_BUTTON);
		m_languageButtons[i]->color((Fl_Color)47);
		m_languageButtons[i]->selection_color((Fl_Color)55);
		m_languageButtons[i]->callback(HandleLanguageChoice_cb);
		m_languageButtons[i]->user_data((void*)this);
	}
	m_languageButtonsGroup->end();

#ifdef NO_OPENGL_PREVIEW
	// Hide OpenGL preview option and shrink dialog
	int moveUpDistance = m_languageGroup->y() - m_useOpenGLGroup->y();
	m_useOpenGLGroup->hide();
	m_languageGroup->position(m_languageGroup->x(), m_languageGroup->y() - moveUpDistance);
	m_confirmButtonsGroup->position(m_confirmButtonsGroup->x(), m_confirmButtonsGroup->y() - moveUpDistance);
	m_backgroudGroup->resizable(NULL);
	m_backgroudGroup->size(m_backgroudGroup->w(), m_backgroudGroup->h() - moveUpDistance);
	size(w(), h() - moveUpDistance);
#endif

	UpdateLanguage();
}

PosteRazorSettingsDialog::~PosteRazorSettingsDialog()
{
	if (m_unitOfLengthButtons)
		delete[] m_unitOfLengthButtons;

	if (m_languageButtons)
		delete[] m_languageButtons; // the actual buttons are deleted by FLTK

	if (m_languageButtonImages)
	{
		for (int i = 0; i <m_languageButtonsCount; i++)
			delete m_languageButtonImages[i];
		delete[] m_languageButtonImages;
	}
}

void PosteRazorSettingsDialog::SetOptionsAndHandler(posteRazorSettings *settings, SettingsChangementHandler *changementHandler)
{
	int i;
	m_settings = settings;
	m_changementHandler = changementHandler;

	for (i = 0; i < m_unitOfLengthButtonsCount; i++)
		m_unitOfLengthButtons[i]->value(UnitsOfLength::GetUnitOfLengthForIndex(i) == m_settings->UnitOfLength?1:0);

	m_useOpenGLCheckButton->value(m_settings->previewType == Fl_Paint_Canvas_Group::PaintCanvasTypeGL?1:0);

	for (i = 0; i < m_languageButtonsCount; i++)
		m_languageButtons[i]->value((m_settings->language == TRANSLATIONS->GetLanguageForIndex(i))?1:0);
}

void PosteRazorSettingsDialog::HandleUnitOfLengthChoice_cb(Fl_Widget *widget, void *userData)
{
	((PosteRazorSettingsDialog*)userData)->HandleUnitOfLengthChoice();
}

void PosteRazorSettingsDialog::HandleUnitOfLengthChoice(void)
{
	for (int i = 0; i < m_unitOfLengthButtonsCount; i++)
	{
		if (m_unitOfLengthButtons[i]->value() != 0)
		{
			m_settings->UnitOfLength = UnitsOfLength::GetUnitOfLengthForIndex(i);
			break;
		}
	}

	if (m_changementHandler)
		m_changementHandler->HandleOptionsChangement(m_settings);
}

void PosteRazorSettingsDialog::HandleUseOpenGLChangement(void)
{
	m_settings->previewType = m_useOpenGLCheckButton->value()?Fl_Paint_Canvas_Group::PaintCanvasTypeGL:Fl_Paint_Canvas_Group::PaintCanvasTypeDraw;

	if (m_changementHandler)
		m_changementHandler->HandleOptionsChangement(m_settings);
}

void PosteRazorSettingsDialog::HandleLanguageChoice_cb(Fl_Widget *widget, void *userData)
{
	((PosteRazorSettingsDialog*)userData)->HandleLanguageChoice();
}

void PosteRazorSettingsDialog::HandleLanguageChoice(void)
{
	for (int i = 0; i < m_languageButtonsCount; i++)
	{
		if (m_languageButtons[i]->value() != 0)
		{
			m_settings->language = TRANSLATIONS->GetLanguageForIndex(i);
			break;
		}
	}

	if (m_changementHandler)
		m_changementHandler->HandleOptionsChangement(m_settings);
}

void PosteRazorSettingsDialog::UpdateLanguage(void)
{
	label(TRANSLATIONS->PosteRazorSettings());
	m_unitOfLengthGroup->label(TRANSLATIONS->UnitOfLength());
	m_unitOfLengthExplanationBox->label(TRANSLATIONS->UnitOfLengthExplanation());
	m_useOpenGLGroup->label(TRANSLATIONS->PreviewWithOpenGL());
	m_useOpenGLCheckButton->label(TRANSLATIONS->PreviewWithOpenGL());
	m_useOpenGLExplanationBox->label(TRANSLATIONS->PreviewWithOpenGLExplanation());
	m_languageGroup->label(TRANSLATIONS->Language());
	m_languageExplanationBox->label(TRANSLATIONS->LanguageExplanation());
	m_cancelButton->label(TRANSLATIONS->Cancel());

	redraw();
}

void PosteRazorSettingsDialog::show(void)
{
	m_okWasPressed = false;
	PosteRazorSettingsDialogUI::show();
}
