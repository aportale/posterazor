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

#include "PosteRazorDialog.h"
#include "Fl_Persistent_Preferences.h"
#include <Fl/Fl_Native_File_Chooser.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>
#include <FL/x.H>
#include "translations/PosteRazorHelpConstants.h"


#ifdef WIN32
  #include "windowsResources/PosteRazorResource.h"
  #include <Shellapi.h>
#endif

const char PreferencesVendor[] = "CasaPortale.de";
const char PreferencesProduct[] = "PosteRazor";
const char preferencesKey_UseOpenGLForPreview[] = "UseOpenGLForPreview";

PosteRazorDragDropWidget::PosteRazorDragDropWidget(int x, int y, int w, int h, const char *label)
	:Fl_Box(FL_NO_BOX, x, y, w, h, label)
{
}

int PosteRazorDragDropWidget::handle(int event)
{
	switch (event)
	{
	case FL_DND_ENTER:
	case FL_DND_DRAG:
	case FL_DND_LEAVE:
	case FL_DND_RELEASE:
		return 1;
	case FL_PASTE:
		return parent()->handle(event);
	default:
		return 0;
	};
}

class PosteRazorHelpDialog: public PosteRazorHelpDialogUI
{
	char m_homepageURL[2048];
public:
	PosteRazorHelpDialog(const char *homepageButtonLabel, const char *homepageURL)
		:PosteRazorHelpDialogUI(500, 400, "PosteRazor Help")
	{
		SetHomepageButtonLabel(homepageButtonLabel);
		strncpy(m_homepageURL, homepageURL, sizeof(m_homepageURL));
		m_homepageURL[sizeof(m_homepageURL)-1] = '\0';
	}

	void SetHtmlContent(const char *content) {m_help_view->value(content);}
	void JumpToAnchor(const char *anchor) {	m_help_view->topline(anchor);}

	void HandleHomepageButtonClick(void)
	{
#ifdef WIN32
		ShellExecute(HWND_DESKTOP, "open", m_homepageURL, NULL, NULL, SW_SHOW);
#else
		char commandString[2048];
		sprintf(commandString, "open %s", m_homepageURL);
		system(commandString);
#endif;
	}

	void UpdateLanguage(void)
	{
		label(TRANSLATIONS->PosteRazorHelp());

		redraw();
	}
};

class PosteRazorSettingsDialog: public PosteRazorSettingsDialogUI
{
	posteRazorSettings *m_settings;
	posteRazorSettings m_settingsBackup;
	SettingsChangementHandler *m_changementHandler;
	Fl_Menu_Item *m_unitOfLengthMenuItems;
	int m_languageButtonsCount;
	Fl_Button **m_languageButtons;
	Fl_RGB_Image **m_languageButtonImages;

public:
	PosteRazorSettingsDialog()
		:PosteRazorSettingsDialogUI(315, 400, "PosteRazor Settings")
	{
		int UnitOfLengthMenuItemsCount = PosteRazor::GetUnitsOfLengthCount()+1;
		m_unitOfLengthMenuItems = new Fl_Menu_Item[UnitOfLengthMenuItemsCount];
		memset(m_unitOfLengthMenuItems, 0, sizeof(Fl_Menu_Item)*UnitOfLengthMenuItemsCount);
		for (int i = 0; i < PosteRazor::GetUnitsOfLengthCount(); i++)
		{
			const char* UnitOfLengthName = UnitsOfLength::GetUnitOfLengthName(PosteRazor::GetUnitOfLengthForIndex(i));
			m_unitOfLengthMenuItems[i].label(UnitOfLengthName);
			m_unitOfLengthMenuItems[i].callback(HandleUnitOfLengthChoice_cb);
			m_unitOfLengthMenuItems[i].user_data((void*)this);
		}
		m_unitOfLengthChoice->menu(m_unitOfLengthMenuItems);

#define LANGUAGEBUTTONSSPACING 10
		m_languageButtonsCount = TRANSLATIONS->GetLanguagesCount();
		m_languageButtons = new Fl_Button*[m_languageButtonsCount];
		m_languageButtonImages = new Fl_RGB_Image*[m_languageButtonsCount];
		int languageButtonWidth = (m_languageButtonsGroup->w() + LANGUAGEBUTTONSSPACING) / m_languageButtonsCount - LANGUAGEBUTTONSSPACING;

		m_languageButtonsGroup->begin();
		for (int i = 0; i < m_languageButtonsCount; i++)
		{
			m_languageButtons[i] = new Fl_Button
			(
				m_languageButtonsGroup->x() + i * (languageButtonWidth+LANGUAGEBUTTONSSPACING),
				m_languageButtonsGroup->y(),
				languageButtonWidth,
				m_languageButtonsGroup->h()
			);

			enum Translations::eLanguages language = TRANSLATIONS->GetLanguageForIndex(i);
			TranslationInterface *translation = TRANSLATIONS->GetTranslationOfLanguage(language);
			m_languageButtonImages[i] = new Fl_RGB_Image(translation->FlagImageRGBData(), translation->FlagImageWidth(), translation->FlagImageHeight());
			m_languageButtons[i]->image(m_languageButtonImages[i]);
			m_languageButtons[i]->tooltip(translation->LanguageName());
			m_languageButtons[i]->type(FL_RADIO_BUTTON);
			m_languageButtons[i]->color((Fl_Color)40);
			m_languageButtons[i]->selection_color((Fl_Color)55);
			m_languageButtons[i]->callback(HandleLanguageChoice_cb);
			m_languageButtons[i]->user_data((void*)this);
		}
		m_languageButtonsGroup->end();

		UpdateLanguage();
	}

	~PosteRazorSettingsDialog()
	{
		if (m_unitOfLengthMenuItems)
			delete[] m_unitOfLengthMenuItems;

		if (m_languageButtons)
			delete[] m_languageButtons; // the actual buttons are deleted by FLTK

		if (m_languageButtonImages)
		{
			for (int i = 0; i <m_languageButtonsCount; i++)
				delete m_languageButtonImages[i];
			delete[] m_languageButtonImages;
		}
	}

	void SetOptionsAndHandler(posteRazorSettings *settings, SettingsChangementHandler *changementHandler)
	{
		m_settings = settings;
		m_settingsBackup = *m_settings;
		m_changementHandler = changementHandler;

		enum PosteRazor::eUnitsOfLength selectedUnitOfLength = m_settings->UnitOfLength;
		m_unitOfLengthChoice->value(selectedUnitOfLength);
		m_useOpenGLCheckButton->value(m_settings->previewType == Fl_Paint_Canvas_Group::PaintCanvasTypeGL?1:0);

		for (int i = 0; i < m_languageButtonsCount; i++)
			m_languageButtons[i]->value((m_settings->language == TRANSLATIONS->GetLanguageForIndex(i))?1:0);
	}

	static void HandleUnitOfLengthChoice_cb(Fl_Widget *widget, void *userData)
	{
		((PosteRazorSettingsDialog*)userData)->HandleUnitOfLengthChangement(((PosteRazorSettingsDialog*)userData)->m_unitOfLengthChoice);
	}

	void HandleUnitOfLengthChangement(Fl_Widget *sourceWidget)
	{
		const char* UnitOfLengthName = m_unitOfLengthMenuItems[m_unitOfLengthChoice->value()].label();
		m_settings->UnitOfLength = PosteRazor::GetUnitOfLengthForName(UnitOfLengthName);

		if (m_changementHandler)
			m_changementHandler->HandleOptionsChangement(m_settings);
	}

	void HandleUseOpenGLChangement(void)
	{
		m_settings->previewType = m_useOpenGLCheckButton->value()?Fl_Paint_Canvas_Group::PaintCanvasTypeGL:Fl_Paint_Canvas_Group::PaintCanvasTypeDraw;

		if (m_changementHandler)
			m_changementHandler->HandleOptionsChangement(m_settings);
	}

	static void HandleLanguageChoice_cb(Fl_Widget *widget, void *userData)
	{
		((PosteRazorSettingsDialog*)userData)->HandleLanguageChoice();
	}

	void HandleLanguageChoice(void)
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

	void hide(void)
	{
		if (!m_okWasPressed && m_changementHandler)
		{
			*m_settings = m_settingsBackup;
			m_changementHandler->HandleOptionsChangement(m_settings);
		}

		m_okWasPressed = false;
		Fl_Window::hide();
	}

	void UpdateLanguage(void)
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
};

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI(620, 455, "PosteRazor")
{
	m_settingsDialog = NULL;
	m_helpDialog = NULL;

	int i;
	begin();
	m_dragDropWidget = new PosteRazorDragDropWidget(0, 0, w(), h());
	end();

	m_wizard->value(m_loadInputImageStep);

	m_posteRazor = PosteRazor::CreatePosteRazor();

	Fl_Persistent_Preferences preferences(PreferencesVendor, PreferencesProduct);
	m_posteRazor->ReadPersistentPreferences(&preferences);
	Fl_Paint_Canvas_Group::ePaintCanvasTypes paintCanvasType =
		preferences.GetBoolean(preferencesKey_UseOpenGLForPreview, true)?Fl_Paint_Canvas_Group::PaintCanvasTypeGL:Fl_Paint_Canvas_Group::PaintCanvasTypeDraw;

	int paperFormatMenuItemsCount = PosteRazor::GetPaperFormatsCount()+1;
	m_paperFormatMenuItems = new Fl_Menu_Item[paperFormatMenuItemsCount];
	memset(m_paperFormatMenuItems, 0, sizeof(Fl_Menu_Item)*paperFormatMenuItemsCount);
	for (i = 0; i < PosteRazor::GetPaperFormatsCount(); i++)
	{
		const char* paperFormatName = PosteRazor::GetPaperFormatName(PosteRazor::GetPaperFormatForIndex(i));
		m_paperFormatMenuItems[i].label(paperFormatName);
		m_paperFormatMenuItems[i].callback(HandlePaperFormatChoice_cb);
		m_paperFormatMenuItems[i].user_data((void*)this);
	}
	m_paperFormatChoice->menu(m_paperFormatMenuItems);
	m_paperFormatChoice->value((int)m_posteRazor->GetPaperFormat());

	if (m_posteRazor->GetPosterSizeMode() == PosteRazor::ePosterSizeModeAbsolute)
		m_posterSizeAbsoluteRadioButton->setonly();
	else if (m_posteRazor->GetPosterSizeMode() == PosteRazor::ePosterSizeModePages)
		m_posterSizeInPagesRadioButton->setonly();
	else // if (m_posteRazor->GetPosterSizeMode() == PosteRazor::ePosterSizeModePercentual)
		m_posterSizePercentualRadioButton->setonly();
	UpdatePosterSizeGroupsState();
	SetPosterImageAlignmentButtons();

	m_setLaunchPDFApplicationCheckButton->value(m_posteRazor->GetLaunchPDFApplication()?1:0);

	m_imageInfoGroup->deactivate();

	m_paintCanvasGroup->SetPaintCanvasType(paintCanvasType);
	m_paintCanvasGroup->SetPainterInterface(m_posteRazor);

	UpdateNavigationButtons();
	UpdatePreviewState();
	SetPaperSizeFields();
	SetOverlappingFields();
	UpdateDimensionUnitLabels();
	UpdateStepInfoBar();

	UpdateLanguage();
}

PosteRazorDialog::~PosteRazorDialog()
{
	Fl_Persistent_Preferences preferences(PreferencesVendor, PreferencesProduct);
	m_posteRazor->WritePersistentPreferences(&preferences);
	preferences.SetBoolean(m_paintCanvasGroup->GetPaintCanvasType() == Fl_Paint_Canvas_Group::PaintCanvasTypeGL, preferencesKey_UseOpenGLForPreview);

	if (m_paperFormatMenuItems)
		delete[] m_paperFormatMenuItems;

	if (m_settingsDialog)
		delete m_settingsDialog;

	if (m_helpDialog)
		delete m_helpDialog;
}

int PosteRazorDialog::handle(int event)
{
	switch (event)
	{
	case FL_PASTE:
		LoadInputImage(Fl::event_text());
		return 1;
	default:
		return PosteRazorDialogUI::handle(event);
	};
}

void PosteRazorDialog::OpenSettingsDialog(void)
{
	if (!m_settingsDialog)
	{
		m_settings.UnitOfLength = m_posteRazor->GetUnitOfLength();
		m_settings.previewType = m_paintCanvasGroup->GetPaintCanvasType();
		m_settings.language = TRANSLATIONS->GetSelectedLanguage()!=Translations::eLanguageUndefined?TRANSLATIONS->GetSelectedLanguage():Translations::eLanguageEnglish;
		m_settingsDialog = new PosteRazorSettingsDialog();
		m_settingsDialog->set_modal();
	}
	m_settingsDialog->SetOptionsAndHandler(&m_settings, this);
	m_settingsDialog->show();
}

void PosteRazorDialog::OpenHelpDialog(void)
{
	if (!m_helpDialog)
	{
		m_helpDialog = new PosteRazorHelpDialog("PosteRazor homepage", "http://posterazor.sourceforge.net/");
		m_helpDialog->set_modal();
	}

	char stepTopic[1024];
	sprintf(stepTopic, POSTERAZORHELPANCHORMANUALSTEP "%.2d", GetCurrentWizardStepNumber() + 1);

	m_helpDialog->SetHtmlContent(TRANSLATIONS->HelpHtml());
	m_helpDialog->JumpToAnchor(stepTopic);
	m_helpDialog->show();
}

void PosteRazorDialog::HandleOptionsChangement(posteRazorSettings *settings)
{
	if (m_posteRazor->GetUnitOfLength() != settings->UnitOfLength)
	{
		m_posteRazor->SetUnitOfLength(settings->UnitOfLength);
		UpdateImageInfoFields();
		UpdatePosterSizeFields(NULL);
		SetPaperSizeFields();
		SetOverlappingFields();
		UpdateDimensionUnitLabels();
	}
	if (m_paintCanvasGroup->GetPaintCanvasType() != settings->previewType)
	{
		m_paintCanvasGroup->SetPaintCanvasType(settings->previewType);
		UpdatePreviewState();
	}
	if (TRANSLATIONS->GetSelectedLanguage() != settings->language)
	{
		TRANSLATIONS->SelectLangue(settings->language);
		UpdateLanguage();
	}
}

void PosteRazorDialog::next(void)
{
	UpdatePosterSizeFields(NULL);
	m_wizard->next();
	UpdateNavigationButtons();
	UpdatePreviewState();
	UpdatePosterSizeFields(NULL);
	UpdateStepInfoBar();
}

void PosteRazorDialog::prev(void)
{
	m_wizard->prev();
	UpdateNavigationButtons();
	UpdatePreviewState();
	UpdateStepInfoBar();
}

void PosteRazorDialog::UpdateNavigationButtons(void)
{
	if (m_wizard->value() != m_loadInputImageStep)
		m_prevButton->activate();
	else
		m_prevButton->deactivate();

	if (m_posteRazor->IsImageLoaded()
	    && m_wizard->value() != m_savePosterStep)
		m_nextButton->activate();
	else
		m_nextButton->deactivate();
}

const char* PosteRazorDialog::GetCurrentWizardStepStepInfoString(void)
{
	return
	(
		m_wizard->value() == m_loadInputImageStep?TRANSLATIONS->StepTitle01()
		:m_wizard->value() == m_paperSizeStep?TRANSLATIONS->StepTitle02()
		:m_wizard->value() == m_overlappingStep?TRANSLATIONS->StepTitle03()
		:m_wizard->value() == m_posterSizeStep?TRANSLATIONS->StepTitle04()
		:TRANSLATIONS->StepTitle05()
	);
}

int PosteRazorDialog::GetCurrentWizardStepNumber(void)
{
	return
	(
		m_wizard->value() == m_loadInputImageStep?0
		:m_wizard->value() == m_paperSizeStep?1
		:m_wizard->value() == m_overlappingStep?2
		:m_wizard->value() == m_posterSizeStep?3
		:4
	);
}

void PosteRazorDialog::UpdateStepInfoBar(void)
{
	char stepStr[1024];
	sprintf(stepStr, TRANSLATIONS->StepXOfY(), GetCurrentWizardStepNumber() + 1, 5); 
	char helpTitleStr[1024];
	sprintf(helpTitleStr, "  %s: %s", stepStr, GetCurrentWizardStepStepInfoString());
	m_stepInfoBox->copy_label(helpTitleStr);
}

void PosteRazorDialog::UpdatePreviewState(void)
{
	m_paintCanvasGroup->SetState
	(
		m_wizard->value() == m_loadInputImageStep?"image"
		:m_wizard->value() == m_paperSizeStep?"paper"
		:m_wizard->value() == m_overlappingStep?"overlapping"
		:"poster"
	);
	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::UpdateDimensionUnitLabels(void)
{
	m_paperCustomWidthDimensionUnitLabel->label(m_posteRazor->GetUnitOfLengthName());
	m_paperCustomHeightDimensionUnitLabel->label(m_posteRazor->GetUnitOfLengthName());
	m_overlappingWidthDimensionUnitLabel->label(m_posteRazor->GetUnitOfLengthName());
	m_overlappingHeightDimensionUnitLabel->label(m_posteRazor->GetUnitOfLengthName());
	m_posterAbsoluteWidthDimensionUnitLabel->label(m_posteRazor->GetUnitOfLengthName());
	m_posterAbsoluteHeightDimensionUnitLabel->label(m_posteRazor->GetUnitOfLengthName());
	char paperBordersGroupLabel[100];
	sprintf(paperBordersGroupLabel, "%s (%s)", TRANSLATIONS->Borders(), m_posteRazor->GetUnitOfLengthName());
	m_paperBordersGroup->copy_label(paperBordersGroupLabel);
}

void PosteRazorDialog::UpdateLanguage(void)
{
	char tempStr[1024];

	sprintf(tempStr, "%s @-2->", TRANSLATIONS->Next());
	m_nextButton->copy_label(tempStr);
	sprintf(tempStr, "@-2<- %s", TRANSLATIONS->Back());
	m_prevButton->copy_label(tempStr);

	m_paperFormatTypeTabs->label(TRANSLATIONS->PaperFormat());
	m_paperFormatCustomGroup->label(TRANSLATIONS->Custom());
	m_paperFormatStandardGroup->label(TRANSLATIONS->Standard());
	m_paperFormatChoice->label(TRANSLATIONS->Format());
	m_paperOrientationGroup->label(TRANSLATIONS->Orientation());
	m_paperOrientationLandscapeRadioButton->label(TRANSLATIONS->Landscape());
	m_paperOrientationPortraitRadioButton->label(TRANSLATIONS->Portrait());
	m_paperCustomHeightInput->label(TRANSLATIONS->Height());
	m_paperCustomWidthInput->label(TRANSLATIONS->Width());
	m_paperBorderTopInput->label(TRANSLATIONS->Top());
	m_paperBorderRightInput->label(TRANSLATIONS->Right());
	m_paperBorderBottomInput->label(TRANSLATIONS->Bottom());
	m_paperBorderLeftInput->label(TRANSLATIONS->Left());

	m_overlappingHeightInput->label(TRANSLATIONS->Height());
	m_overlappingWidthInput->label(TRANSLATIONS->Width());
	m_overlappingPositionGroup->label(TRANSLATIONS->OverlappingPosition());
	m_overlappingSizeGroup->label(TRANSLATIONS->OverlappingSize());
	m_overlappingPositionBottomLeftButton->label(TRANSLATIONS->BottomLeft());
	m_overlappingPositionBottomRightButton->label(TRANSLATIONS->BottomRight());
	m_overlappingPositionTopLeftButton->label(TRANSLATIONS->TopLeft());
	m_overlappingPositionTopRightButton->label(TRANSLATIONS->TopRight());

	m_posterSizeGroup->label(TRANSLATIONS->ImageSize());
	m_posterSizeAbsoluteRadioButton->label(TRANSLATIONS->AbsoluteSize());
	m_posterAbsoluteHeightInput->label(TRANSLATIONS->Height());
	m_posterAbsoluteWidthInput->label(TRANSLATIONS->Width());
	m_posterSizeInPagesRadioButton->label(TRANSLATIONS->SizeInPages());
	m_posterPagesHeightInput->label(TRANSLATIONS->Height());
	m_posterPagesHeightLabel->label(TRANSLATIONS->Pages());
	m_posterPagesWidthInput->label(TRANSLATIONS->Width());
	m_posterPagesWidthLabel->label(TRANSLATIONS->Pages());
	m_posterSizePercentualRadioButton->label(TRANSLATIONS->SizeInPercent());
	m_posterPercentualSizeInput->label(TRANSLATIONS->Size());
	m_imageAlignmentGroup->label(TRANSLATIONS->ImageAlignment());
	m_imageInfoGroup->label(TRANSLATIONS->ImageInformations());
	m_imageLoadGroup->label(TRANSLATIONS->InputImage());
	m_settingsButton->label(TRANSLATIONS->Settings());

	m_savePosterGroup->label(TRANSLATIONS->SaveThePoster());
	m_setLaunchPDFApplicationCheckButton->label(TRANSLATIONS->LaunchPDFApplication());

	UpdateImageInfoFields();
	UpdateStepInfoBar();
	UpdateDimensionUnitLabels();

	if (m_settingsDialog)
		m_settingsDialog->UpdateLanguage();

	if (m_helpDialog)
		m_helpDialog->UpdateLanguage();

	redraw();
}

void PosteRazorDialog::LoadInputImage(const char *fileName)
{
	Fl_Native_File_Chooser chooser;
	char errorMessage[1024] = "";
	const char *loadFileName = fileName;
	bool loaded = false;

//	chooser.AddPattern();

	if (!loadFileName)
	{
		if (chooser.show() == 0)
			loadFileName = chooser.filename();
	}

	if (loadFileName)
	{
		loaded = m_posteRazor->LoadInputImage(loadFileName, errorMessage, sizeof(errorMessage));
		if (!loaded)
		{
			if (strlen(errorMessage) > 0)
				fl_message(errorMessage);
			else
				fl_message(TRANSLATIONS->FileCouldNotBeLoaded(), fl_filename_name(loadFileName));
		}
	}

	if (loaded)
	{
		UpdateImageInfoFields();
		m_imageInfoGroup->activate();
		m_inputFileNameLabel->copy_label(fl_filename_name(loadFileName));
		m_paintCanvasGroup->RequestImage();
		UpdatePosterSizeFields(NULL);
	}

	UpdateNavigationButtons();
}

void PosteRazorDialog::UpdateImageInfoFields(void)
{
	if (!m_posteRazor->IsImageLoaded())
		return;

	char sizeInDimensionUnitString[100];
	sprintf(sizeInDimensionUnitString, TRANSLATIONS->SizeInUnitOfLength(), m_posteRazor->GetUnitOfLengthName());

	char string[1024];
	enum PosteRazor::eColorTypes colorType = m_posteRazor->GetInputImageColorType();

	sprintf
	(
		string,
		"%s\n%s\n%s\n%s",
		TRANSLATIONS->SizeInPixels(),
		sizeInDimensionUnitString,
		TRANSLATIONS->Resolution(),
		TRANSLATIONS->ColorType()
	);
	m_imageInfoKeysLabel->copy_label(string);

	sprintf
	(
		string,
		"%d x %d\n%.2f x %.2f\n%.1f dpi\n%s %dbpp",
		m_posteRazor->GetInputImageWidthPixels(), m_posteRazor->GetInputImageHeightPixels(),
		m_posteRazor->GetInputImageWidth(), m_posteRazor->GetInputImageHeight(),
		m_posteRazor->GetInputImageVerticalDpi(),
			colorType==PosteRazor::eColorTypeMonochrome?TRANSLATIONS->Monochrome():
			colorType==PosteRazor::eColorTypeGreyscale?TRANSLATIONS->Grayscale():
			colorType==PosteRazor::eColorTypePalette?TRANSLATIONS->Palette():
			colorType==PosteRazor::eColorTypeRGB?"RGB":
			colorType==PosteRazor::eColorTypeRGBA?"RGBA":
			/*colorType==eColorTypeCMYK?*/ "CMYK",
		m_posteRazor->GetInputImageBitsPerPixel()
	);
	m_imageInfoValuesLabel->copy_label(string);
}

void PosteRazorDialog::UpdatePosterSizeFields(Fl_Valuator *sourceWidget)
{
	static const struct
	{
		Fl_Valuator* inputWidget;
		bool width;
		enum PosteRazor::ePosterSizeModes sizeMode;
	}
	sizeInputWidgets[] = 
	{
		{m_posterAbsoluteWidthInput, true, PosteRazor::ePosterSizeModeAbsolute},
		{m_posterAbsoluteHeightInput, false, PosteRazor::ePosterSizeModeAbsolute},
		{m_posterPagesWidthInput, true, PosteRazor::ePosterSizeModePages},
		{m_posterPagesHeightInput, false, PosteRazor::ePosterSizeModePages},
		{m_posterPercentualSizeInput, true, PosteRazor::ePosterSizeModePercentual}
	};

	int sizeInputWidgetsCount = sizeof(sizeInputWidgets)/sizeof(sizeInputWidgets[0]);
	int i = 0;

	for (i = 0; i < sizeInputWidgetsCount; i++)
	{
		if (sizeInputWidgets[i].inputWidget == sourceWidget)
		{
			if (sizeInputWidgets[i].width)
				m_posteRazor->SetPosterWidth(sizeInputWidgets[i].sizeMode, sizeInputWidgets[i].inputWidget->value());
			else
				m_posteRazor->SetPosterHeight(sizeInputWidgets[i].sizeMode, sizeInputWidgets[i].inputWidget->value());
		}
	}

	for (i = 0; i < sizeInputWidgetsCount; i++)
	{
		if (sizeInputWidgets[i].inputWidget != sourceWidget)
		{
			sizeInputWidgets[i].inputWidget->value
			(
				sizeInputWidgets[i].width?
				m_posteRazor->GetPosterWidth(sizeInputWidgets[i].sizeMode)
				:m_posteRazor->GetPosterHeight(sizeInputWidgets[i].sizeMode)
			);
		}
	}

	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::SetPaperSizeFields(void)
{
	// standard paper format
	m_paperOrientationPortraitRadioButton->value(m_posteRazor->GetPaperOrientation() == PosteRazor::ePaperOrientationPortrait);
	m_paperOrientationLandscapeRadioButton->value(m_posteRazor->GetPaperOrientation() == PosteRazor::ePaperOrientationLandscape);

	// custom paper format
	m_paperCustomWidthInput->value(m_posteRazor->GetCustomPaperWidth());
	m_paperCustomHeightInput->value(m_posteRazor->GetCustomPaperHeight());

	// paper borders
	m_paperBorderTopInput->value(m_posteRazor->GetPaperBorderTop());
	m_paperBorderRightInput->value(m_posteRazor->GetPaperBorderRight());
	m_paperBorderBottomInput->value(m_posteRazor->GetPaperBorderBottom());
	m_paperBorderLeftInput->value(m_posteRazor->GetPaperBorderLeft());

	// select the active tab
	m_paperFormatTypeTabs->value(m_posteRazor->GetUseCustomPaperSize()?m_paperFormatCustomGroup:m_paperFormatStandardGroup);
}

void PosteRazorDialog::HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData)
{
	((PosteRazorDialog*)userData)->HandlePaperSizeChangement(((PosteRazorDialog*)userData)->m_paperFormatChoice);
}

void PosteRazorDialog::HandlePaperSizeChangement(Fl_Widget *sourceWidget)
{
	m_posteRazor->SetPaperBorderTop(m_paperBorderTopInput->value());
	m_posteRazor->SetPaperBorderRight(m_paperBorderRightInput->value());
	m_posteRazor->SetPaperBorderBottom(m_paperBorderBottomInput->value());
	m_posteRazor->SetPaperBorderLeft(m_paperBorderLeftInput->value());

	m_posteRazor->SetUseCustomPaperSize(m_paperFormatTypeTabs->value() == m_paperFormatCustomGroup);

	if (!m_posteRazor->GetUseCustomPaperSize())
	{
		const char* paperFormatName = m_paperFormatMenuItems[m_paperFormatChoice->value()].label();
		enum PosteRazor::ePaperFormats paperFormat = PosteRazor::GetPaperFormatForName(paperFormatName);
		m_posteRazor->SetPaperFormat(paperFormat);
		m_posteRazor->SetPaperOrientation(m_paperOrientationLandscapeRadioButton->value() != 0?PosteRazor::ePaperOrientationLandscape:PosteRazor::ePaperOrientationPortrait);
	}
	else
	{
		m_posteRazor->SetCustomPaperWidth(m_paperCustomWidthInput->value());
		m_posteRazor->SetCustomPaperHeight(m_paperCustomHeightInput->value());
	}

	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::SetOverlappingFields(void)
{
	m_overlappingWidthInput->value(m_posteRazor->GetOverlappingWidth());
	m_overlappingHeightInput->value(m_posteRazor->GetOverlappingHeight());

	enum PosteRazor::eOverlappingPositions overlappingPosition = m_posteRazor->GetOverlappingPosition();

	(
		overlappingPosition == PosteRazor::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:overlappingPosition == PosteRazor::eOverlappingPositionBottomLeft?m_overlappingPositionBottomLeftButton
		:overlappingPosition == PosteRazor::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:m_overlappingPositionTopRightButton
	)->setonly();
}

void PosteRazorDialog::HandleOverlappingChangement(Fl_Widget *sourceWidget)
{
	m_posteRazor->SetOverlappingWidth(m_overlappingWidthInput->value());
	m_posteRazor->SetOverlappingHeight(m_overlappingHeightInput->value());

	m_posteRazor->SetOverlappingPosition
	(
		m_overlappingPositionBottomRightButton->value()?PosteRazor::eOverlappingPositionBottomRight
		:m_overlappingPositionBottomLeftButton->value()?PosteRazor::eOverlappingPositionBottomLeft
		:m_overlappingPositionTopLeftButton->value()?PosteRazor::eOverlappingPositionTopLeft
		:PosteRazor::eOverlappingPositionTopRight
	);

	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::UpdatePosterSizeGroupsState(void)
{
	m_posterSizeAbsoluteRadioButton->value() == 0?m_posterSizeAbsoluteGroup->deactivate():m_posterSizeAbsoluteGroup->activate();
	m_posterSizeInPagesRadioButton->value() == 0?m_posterSizeInPagesGroup->deactivate():m_posterSizeInPagesGroup->activate();
	m_posterSizePercentualRadioButton->value() == 0?m_posterSizePercentualGroup->deactivate():m_posterSizePercentualGroup->activate();
}

void PosteRazorDialog::SetPosterImageAlignmentButtons(void)
{
	enum PosteRazor::eVerticalAlignments verticalAlignment = m_posteRazor->GetPosterVerticalAlignment();
	
	(
		verticalAlignment == PosteRazor::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:verticalAlignment == PosteRazor::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton 
	)->setonly();
	
	enum PosteRazor::eHorizontalAlignments horizontalAlignment = m_posteRazor->GetPosterHorizontalAlignment();
	
	(
		horizontalAlignment == PosteRazor::eHorizontalAlignmentLeft?m_posterAlignmentLeftButton
		:horizontalAlignment == PosteRazor::eHorizontalAlignmentCenter?m_posterAlignmentCenterButton
		:m_posterAlignmentRightButton 
	)->setonly();
}

void PosteRazorDialog::HandlePosterImageAlignment(void)
{
	m_posteRazor->SetPosterVerticalAlignment
	(
		m_posterAlignmentTopButton->value() == 1?PosteRazor::eVerticalAlignmentTop
		:m_posterAlignmentMiddleButton->value() == 1?PosteRazor::eVerticalAlignmentMiddle
		:PosteRazor::eVerticalAlignmentBottom
	);
	
	m_posteRazor->SetPosterHorizontalAlignment
	(
		m_posterAlignmentLeftButton->value() == 1?PosteRazor::eHorizontalAlignmentLeft
		:m_posterAlignmentCenterButton->value() == 1?PosteRazor::eHorizontalAlignmentCenter
		:PosteRazor::eHorizontalAlignmentRight
	);
	
	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::SavePoster(void)
{
	Fl_Native_File_Chooser chooser;
	chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	
	if (chooser.show() == 0)
	{
		int err = m_posteRazor->SavePoster(chooser.filename());
		if (err)
			fl_message("The file '%s' could not be saved.", fl_filename_name(chooser.filename()));
	}
}

void PosteRazorDialog::SetLaunchPDFApplication(void)
{
	m_posteRazor->SetLaunchPDFApplication(m_setLaunchPDFApplicationCheckButton->value()==0?false:true);
}

#ifdef OSX
static char OSX_droppedFilenameOnIcon[2048] = "";
static PosteRazorDialog *OSX_posteRazorDialogPointer = NULL;

static void	OSX_open_cb(const char* droppedFileName)
{
	if (OSX_posteRazorDialogPointer)
	{
		// File was dropped on the already running application
		OSX_posteRazorDialogPointer->LoadInputImage(droppedFileName);
	}
	else
	{
		// File was dropped on an application icon, but PosteRazor was not yet running
		if (strcmp(OSX_droppedFilenameOnIcon, "") == 0) // If more than one were dropped, use only the first one.
		{
			strncpy(OSX_droppedFilenameOnIcon, droppedFileName, sizeof(OSX_droppedFilenameOnIcon));
			OSX_droppedFilenameOnIcon[sizeof(OSX_droppedFilenameOnIcon)-1] = '\0';
		}
	}
}
#endif

int main (int argc, char **argv)
{
#ifdef OSX
	fl_open_callback(OSX_open_cb);
#endif

	PosteRazorDialog dialog;

#ifdef WIN32
	dialog.icon((char *)LoadIcon(fl_display, MAKEINTRESOURCE(POSTERAZOR_ICON)));
#endif

	Fl::scheme("plastic");
	Fl::get_system_colors();
	dialog.show();
	Fl::wait();

#ifndef OSX
	if (argc == 2)
		dialog.LoadInputImage(argv[1]);
#else
	if (strcmp(OSX_droppedFilenameOnIcon, "") != 0)
		dialog.LoadInputImage(OSX_droppedFilenameOnIcon);

	OSX_posteRazorDialogPointer = &dialog;
#endif

	return Fl::run();
}
