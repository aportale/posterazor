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

#include "PosteRazorDialog.h"
#include "PosteRazorHelpDialog.h"
#include "Fl_Persistent_Preferences.h"
#include <FL/filename.H>
#include <FL/fl_ask.H>
#include <FL/x.H>
#include "TranslationConstants.h"

#if defined (WIN32)
  #include <math.h>
  #include <io.h>
  #include "PosteRazorResource.h"
  #define CASESENSITIVESTRCMP stricmp
  #define CASESENSITIVESTRNCMP strnicmp
#else
  #include <iostream>
  #define CASESENSITIVESTRCMP strcasecmp
  #define CASESENSITIVESTRNCMP strncasecmp
#endif

#if !defined (WIN32) && !defined(__APPLE__)
  #include <X11/xpm.h>
  #include "PosteRazor.xpm"	
#endif

const char PreferencesVendor[] = "CasaPortale.de";
const char PreferencesProduct[] = "PosteRazor";
const char preferencesKey_UseOpenGLForPreview[] = "UseOpenGLForPreview";
const char preferencesKey_LoadImageChooserLastPath[] = "LoadImageChooserLastPath";
const char preferencesKey_SavePosterChooserLastPath[] = "SavePosterChooserLastPath";
const char preferencesKey_UILanguage[] = "UILanguage";

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

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI(620, 455, "PosteRazor "POSTERAZORVERSION)
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
	Translations::eLanguages language = (Translations::eLanguages)preferences.GetInteger(preferencesKey_UILanguage, Translations::eLanguageUndefined);
	m_UILanguageIsUndefined = language == Translations::eLanguageUndefined;
	if (m_UILanguageIsUndefined)
		language = TRANSLATIONS->GetSystemLanguage();
	TRANSLATIONS->SelectLangue(language);

	strncpy(m_loadImageChooserLastPath, preferences.GetString(preferencesKey_LoadImageChooserLastPath, ""), sizeof(m_loadImageChooserLastPath));
	m_loadImageChooserLastPath[sizeof(m_loadImageChooserLastPath) - 1] = '\0';
	strncpy(m_savePosterChooserLastPath, preferences.GetString(preferencesKey_SavePosterChooserLastPath, ""), sizeof(m_savePosterChooserLastPath));
	m_savePosterChooserLastPath[sizeof(m_savePosterChooserLastPath) - 1] = '\0';

	int paperFormatMenuItemsCount = PaperFormats::GetPaperFormatsCount()+1;
	m_paperFormatMenuItems = new Fl_Menu_Item[paperFormatMenuItemsCount];
	memset(m_paperFormatMenuItems, 0, sizeof(Fl_Menu_Item)*paperFormatMenuItemsCount);
	for (i = 0; i < PaperFormats::GetPaperFormatsCount(); i++)
	{
		const char* paperFormatName = PaperFormats::GetPaperFormatName(PaperFormats::GetPaperFormatForIndex(i));
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

	m_settingsButton->label_image(m_settingsButtonLabel->image());

	UpdateNavigationButtons();
	UpdatePreviewState();
	SetPaperSizeFields();
	SetOverlappingFields();
	UpdateDimensionUnitLabels();
	UpdateStepInfoBar();

	UpdateLanguage();
}

static const char* GetPathFromFileName(const char* fileName)
{
	static char pathName[1024] = "";
	
	strncpy(pathName, fileName, sizeof(pathName));
	pathName[sizeof(pathName) - 1] = '\0';
	
	pathName[strlen(pathName) - strlen(fl_filename_name(pathName))] = '\0';
	
	return pathName;
}

PosteRazorDialog::~PosteRazorDialog()
{
	Fl_Persistent_Preferences preferences(PreferencesVendor, PreferencesProduct);
	m_posteRazor->WritePersistentPreferences(&preferences);
	preferences.SetBoolean(m_paintCanvasGroup->GetPaintCanvasType() == Fl_Paint_Canvas_Group::PaintCanvasTypeGL, preferencesKey_UseOpenGLForPreview);
	preferences.SetString(m_loadImageChooserLastPath, preferencesKey_LoadImageChooserLastPath);
	preferences.SetString(m_savePosterChooserLastPath, preferencesKey_SavePosterChooserLastPath);
	if (m_UILanguageIsUndefined)
		TRANSLATIONS->SelectLangue(Translations::eLanguageUndefined);
	preferences.SetInteger(TRANSLATIONS->GetSelectedLanguage(), preferencesKey_UILanguage);

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
	
	posteRazorSettings settingsbackup = m_settings;
	bool languageIsUndefinedBackup = m_UILanguageIsUndefined;
	if (!m_settingsDialog->show_modal())
	{
		HandleOptionsChangement(&settingsbackup);
		m_UILanguageIsUndefined = languageIsUndefinedBackup;
	}
}

void PosteRazorDialog::OpenHelpDialog(void)
{
	if (!m_helpDialog)
	{
		m_helpDialog = new PosteRazorHelpDialog();
		m_helpDialog->UpdateLanguage();
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
		m_UILanguageIsUndefined = false;
		UpdateLanguage();
	}
	m_settings = *settings;
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
	char errorMessage[1024] = "";
	const char *loadFileName = fileName;
	bool loaded = false;

	Fl_Native_File_Chooser loadImageChooser(Fl_Native_File_Chooser::BROWSE_FILE);
#ifndef __APPLE__
// filter stuff is still crashy os OSX
	char filterString[1024] = "";
	sprintf
	(
		filterString,
		"%s\t*.{BMP,CUT,DDS,GIF,ICO,IFF,LBM,JNG,JPG,JPEG,JPE,JIF,KOA,MNG,PBM,PCD,PCX,PGM,PNG,PPM,PSD,RAS,TGA,TIF,TIFF,WBMP,XBM,XPM}\n"\
		"Windows, OS/2 Bitmap (*.BMP)\t*.BMP\n"\
		"Dr. Halo (*.CUT)\t*.CUT\n"\
		"DirectDraw Surface (*.DDS)\t*.DDS\n"\
		"Graphic Interchange Format (*.GIF)\t*.GIF\n"\
		"Windows Icon (*.ICO)\t*.ICO\n"\
		"Amiga IFF (*.IFF;*.LBM)\t*.{IFF,LBM}\n"\
		"JBIG (*.JBIG)\t*.JBIG\n"\
		"JPEG Network Graphics (*.JNG)\t*.JNG\n"\
		"Independent JPEG Group (*.JPG;*.JPEG;*.JPE;*.JIF)\t*.{JPG,JIF,JPEG,JPE}\n"\
		"Commodore 64 Koala (*.KOA)\t*.KOA\n"\
		"Multiple Network Graphics (*.MNG)\t*.MNG\n"\
		"Portable Bitmap (*.PBM)\t*.PBM\n"\
		"Kodak PhotoCD (*.PCD)\t*.PCD\n"\
		"PC Paintbrush Bitmap (*.PCX)\t*.PCX\n"\
		"Portable Graymap (*.PGM)\t*.PGM\n"\
		"Portable Network Graphics (*.PNG)\t*.PNG\n"\
		"Portable Pixelmap (*.PPM)\t*.PPM\n"\
		"Photoshop Document (*.PSD)\t*.PSD\n"\
		"Sun Raster Graphic (*.RAS)\t*.RAS\n"\
		"Targa (*.TGA)\t*.TGA\n"\
		"Tagged Image File Format (*.TIF;*.TIFF)\t*.{TIF,TIFF}\n"\
		"Wireless Bitmap (*.WBMP)\t*.WBMP\n"\
		"X11 Bitmap (*.XBM)\t*.XBM\n"\
		"X11 Pixmap (*.XPM)\t*.XPM",
		TRANSLATIONS->AllImageFormats()
	);
	loadImageChooser.filter(filterString);
#endif
	loadImageChooser.title(TRANSLATIONS->LoadAnInputImage());

	if (!loadFileName)
	{
		loadImageChooser.directory(m_loadImageChooserLastPath);
		if (loadImageChooser.show() == 0)
		{
			loadFileName = loadImageChooser.filename();

			strncpy(m_loadImageChooserLastPath, GetPathFromFileName(loadFileName), sizeof(m_loadImageChooserLastPath));
			m_loadImageChooserLastPath[sizeof(m_loadImageChooserLastPath)-1] = '\0';
		}
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
	Fl::flush(); // Needed for windows if image is loaded at startup
}

void PosteRazorDialog::UpdateImageInfoFields(void)
{
	if (!m_posteRazor->IsImageLoaded())
		return;

	char sizeInDimensionUnitString[100];
	sprintf(sizeInDimensionUnitString, TRANSLATIONS->SizeInUnitOfLength(), m_posteRazor->GetUnitOfLengthName());

	char string[1024];
	ColorTypes::eColorTypes colorType = m_posteRazor->GetInputImageColorType();

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
			colorType==ColorTypes::eColorTypeMonochrome?TRANSLATIONS->Monochrome():
			colorType==ColorTypes::eColorTypeGreyscale?TRANSLATIONS->Grayscale():
			colorType==ColorTypes::eColorTypePalette?TRANSLATIONS->Palette():
			colorType==ColorTypes::eColorTypeRGB?"RGB":
			colorType==ColorTypes::eColorTypeRGBA?"RGBA":
			/*colorType==eColorTypeCMYK?*/ "CMYK",
		m_posteRazor->GetInputImageBitsPerPixel()
	);
	m_imageInfoValuesLabel->copy_label(string);
}

void PosteRazorDialog::UpdatePosterSizeFields(Fl_Widget *sourceWidget)
{
	static const struct
	{
		Fl_PosteRazor_Spinner* inputWidget;
		bool width;
		PosteRazor::ePosterSizeModes sizeMode;
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
	m_paperOrientationPortraitRadioButton->value(m_posteRazor->GetPaperOrientation() == PaperFormats::ePaperOrientationPortrait);
	m_paperOrientationLandscapeRadioButton->value(m_posteRazor->GetPaperOrientation() == PaperFormats::ePaperOrientationLandscape);

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
	if (sourceWidget == m_paperBorderTopInput)
		m_posteRazor->SetPaperBorderTop(m_paperBorderTopInput->value());
	else if (sourceWidget == m_paperBorderRightInput)
		m_posteRazor->SetPaperBorderRight(m_paperBorderRightInput->value());
	else if (sourceWidget == m_paperBorderBottomInput)
		m_posteRazor->SetPaperBorderBottom(m_paperBorderBottomInput->value());
	else if (sourceWidget == m_paperBorderLeftInput)
		m_posteRazor->SetPaperBorderLeft(m_paperBorderLeftInput->value());
	else if (sourceWidget == m_paperFormatTypeTabs)
		m_posteRazor->SetUseCustomPaperSize(m_paperFormatTypeTabs->value() == m_paperFormatCustomGroup);
	else if (!m_posteRazor->GetUseCustomPaperSize())
	{
		if (sourceWidget == m_paperFormatChoice)
		{
			const char* paperFormatName = m_paperFormatMenuItems[m_paperFormatChoice->value()].label();
			PaperFormats::ePaperFormats paperFormat = PaperFormats::GetPaperFormatForName(paperFormatName);
			m_posteRazor->SetPaperFormat(paperFormat);
		}
		else if (sourceWidget == m_paperOrientationPortraitRadioButton || sourceWidget == m_paperOrientationLandscapeRadioButton)
			m_posteRazor->SetPaperOrientation(m_paperOrientationLandscapeRadioButton->value() != 0?PaperFormats::ePaperOrientationLandscape:PaperFormats::ePaperOrientationPortrait);
	}
	else
	{
		if (sourceWidget == m_paperCustomWidthInput)
			m_posteRazor->SetCustomPaperWidth(m_paperCustomWidthInput->value());
		else if (sourceWidget == m_paperCustomHeightInput)
			m_posteRazor->SetCustomPaperHeight(m_paperCustomHeightInput->value());
	}

	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::SetOverlappingFields(void)
{
	m_overlappingWidthInput->value(m_posteRazor->GetOverlappingWidth());
	m_overlappingHeightInput->value(m_posteRazor->GetOverlappingHeight());

	PosteRazor::eOverlappingPositions overlappingPosition = m_posteRazor->GetOverlappingPosition();

	(
		overlappingPosition == PosteRazor::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:overlappingPosition == PosteRazor::eOverlappingPositionBottomLeft?m_overlappingPositionBottomLeftButton
		:overlappingPosition == PosteRazor::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:m_overlappingPositionTopRightButton
	)->setonly();
}

void PosteRazorDialog::HandleOverlappingChangement(Fl_Widget *sourceWidget)
{
	if (sourceWidget == m_overlappingWidthInput)
		m_posteRazor->SetOverlappingWidth(m_overlappingWidthInput->value());
	else if (sourceWidget == m_overlappingHeightInput)
		m_posteRazor->SetOverlappingHeight(m_overlappingHeightInput->value());
	else
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
	PosteRazor::eVerticalAlignments verticalAlignment = m_posteRazor->GetPosterVerticalAlignment();
	
	(
		verticalAlignment == PosteRazor::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:verticalAlignment == PosteRazor::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton 
	)->setonly();
	
	PosteRazor::eHorizontalAlignments horizontalAlignment = m_posteRazor->GetPosterHorizontalAlignment();
	
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

// dirty 
static bool my_file_exists(const char* fileName)
{
	return (access(fileName, 0) == 0);
}

void PosteRazorDialog::SavePoster(void)
{
	char saveFileName[1024] = "";
	bool fileExistsAskUserForOverwrite = false;
	
	Fl_Native_File_Chooser savePosterChooser(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
#ifndef __APPLE__
// filter stuff is still crashy os OSX
	savePosterChooser.filter("Portable Document Format (*.PDF)\t*.pdf");
#endif
	savePosterChooser.title(TRANSLATIONS->SaveThePosterAs());

	do
	{
		if (fileExistsAskUserForOverwrite)
			savePosterChooser.preset_file(fl_filename_name(saveFileName));

		savePosterChooser.directory(m_savePosterChooserLastPath);
		if (savePosterChooser.show() == 0)
		{
			strcpy(saveFileName, savePosterChooser.filename());

			strncpy(m_savePosterChooserLastPath, GetPathFromFileName(saveFileName), sizeof(m_savePosterChooserLastPath));
			m_savePosterChooserLastPath[sizeof(m_savePosterChooserLastPath) - 1] = '\0';

			if (0 != CASESENSITIVESTRCMP(fl_filename_ext(savePosterChooser.filename()), ".pdf"))
				strcat(saveFileName, ".pdf");

			fileExistsAskUserForOverwrite = my_file_exists(saveFileName);
			char overwriteQuestion[1024] = "";
			sprintf(overwriteQuestion, TRANSLATIONS->OverwriteFile(), fl_filename_name(saveFileName));
			if (!fileExistsAskUserForOverwrite || fl_ask(overwriteQuestion))
			{
				int err = m_posteRazor->SavePoster(saveFileName);
				if (err)
					fl_message("The file '%s' could not be saved.", fl_filename_name(saveFileName));
				fileExistsAskUserForOverwrite = false;
			}
		}
		else
			break;
	} while (fileExistsAskUserForOverwrite);
}

void PosteRazorDialog::SetLaunchPDFApplication(void)
{
	m_posteRazor->SetLaunchPDFApplication(m_setLaunchPDFApplicationCheckButton->value()==0?false:true);
}

#ifdef __APPLE__
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
#ifdef __APPLE__
	fl_open_callback(OSX_open_cb);
#endif

	Fl::get_system_colors();
	Fl::scheme("plastic");
	PosteRazorDialog dialog;

#ifdef WIN32
	dialog.icon((char *)LoadIcon(fl_display, MAKEINTRESOURCE(POSTERAZOR_ICON)));
#endif

	dialog.show();
	Fl::wait();

#if !defined(WIN32) && !defined(__APPLE__)
	XpmAttributes icon_attributes;
	Pixmap icon, icon_mask;
	icon_attributes.valuemask = XpmSize | XpmReturnPixels;
	XWMHints *hints;	
	XpmCreatePixmapFromData(fl_display, DefaultRootWindow(fl_display), posteRazorXpm, &icon, &icon_mask, &icon_attributes);
	hints = XGetWMHints(fl_display, fl_xid(&dialog));
	hints->icon_pixmap = icon;
	hints->icon_mask = icon_mask;
	hints->flags = IconPixmapHint | IconMaskHint;
	XSetWMHints(fl_display, fl_xid(&dialog), hints);
#endif

#ifndef __APPLE__
	if (argc == 2)
		dialog.LoadInputImage(argv[1]);
#else
	if (strcmp(OSX_droppedFilenameOnIcon, "") != 0)
		dialog.LoadInputImage(OSX_droppedFilenameOnIcon);

	OSX_posteRazorDialogPointer = &dialog;
#endif

	return Fl::run();
}
