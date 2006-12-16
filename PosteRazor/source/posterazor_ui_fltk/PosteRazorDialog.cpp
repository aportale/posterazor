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
#include "PosteRazorWizardDialogController.h"
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

	m_posteRazor = PosteRazor::createPosteRazor();
	m_posteRazorController = new PosteRazorWizardDialogController();
	m_posteRazorController->setPosteRazorWizardDialog(this);
	m_posteRazorController->setPosteRazorModel(m_posteRazor);

	Fl_Persistent_Preferences preferences(PreferencesVendor, PreferencesProduct);
	m_posteRazorController->readPersistentPreferences(&preferences);
	Fl_Paint_Canvas_Group::ePaintCanvasTypes paintCanvasType =
		preferences.getBoolean(preferencesKey_UseOpenGLForPreview, true)?Fl_Paint_Canvas_Group::PaintCanvasTypeGL:Fl_Paint_Canvas_Group::PaintCanvasTypeDraw;
	Translations::eLanguages language = (Translations::eLanguages)preferences.getInteger(preferencesKey_UILanguage, Translations::eLanguageUndefined);
	m_UILanguageIsUndefined = language == Translations::eLanguageUndefined;
	if (m_UILanguageIsUndefined)
		language = TRANSLATIONS->GetSystemLanguage();
	TRANSLATIONS->SelectLangue(language);

	strncpy(m_loadImageChooserLastPath, preferences.getString(preferencesKey_LoadImageChooserLastPath, ""), sizeof(m_loadImageChooserLastPath));
	m_loadImageChooserLastPath[sizeof(m_loadImageChooserLastPath) - 1] = '\0';
	strncpy(m_savePosterChooserLastPath, preferences.getString(preferencesKey_SavePosterChooserLastPath, ""), sizeof(m_savePosterChooserLastPath));
	m_savePosterChooserLastPath[sizeof(m_savePosterChooserLastPath) - 1] = '\0';

	int paperFormatMenuItemsCount = PaperFormats::getPaperFormatsCount()+1;
	m_paperFormatMenuItems = new Fl_Menu_Item[paperFormatMenuItemsCount];
	memset(m_paperFormatMenuItems, 0, sizeof(Fl_Menu_Item)*paperFormatMenuItemsCount);
	for (i = 0; i < PaperFormats::getPaperFormatsCount(); i++)
	{
		const char* paperFormatName = PaperFormats::getPaperFormatName(PaperFormats::getPaperFormatForIndex(i));
		m_paperFormatMenuItems[i].label(paperFormatName);
		m_paperFormatMenuItems[i].callback(handlePaperFormatChoice_cb);
		m_paperFormatMenuItems[i].user_data((void*)this);
	}
	m_paperFormatChoice->menu(m_paperFormatMenuItems);

	m_imageInfoGroup->deactivate();

	m_paintCanvasGroup->setPaintCanvasType(paintCanvasType);
	m_paintCanvasGroup->setPainterInterface(m_posteRazor);

	m_settingsButton->label_image(m_settingsButtonLabel->image());

	updatePreviewState();
	updateLanguage();
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
	m_posteRazorController->writePersistentPreferences(&preferences);
	preferences.setBoolean(m_paintCanvasGroup->getPaintCanvasType() == Fl_Paint_Canvas_Group::PaintCanvasTypeGL, preferencesKey_UseOpenGLForPreview);
	preferences.setString(m_loadImageChooserLastPath, preferencesKey_LoadImageChooserLastPath);
	preferences.setString(m_savePosterChooserLastPath, preferencesKey_SavePosterChooserLastPath);
	if (m_UILanguageIsUndefined)
		TRANSLATIONS->SelectLangue(Translations::eLanguageUndefined);
	preferences.setInteger(TRANSLATIONS->GetSelectedLanguage(), preferencesKey_UILanguage);

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
		loadInputImage(Fl::event_text());
		return 1;
	default:
		return PosteRazorDialogUI::handle(event);
	};
}

void PosteRazorDialog::openSettingsDialog(void)
{
	if (!m_settingsDialog)
	{
		m_settings.unitOfLength = m_posteRazor->getUnitOfLength();
		m_settings.previewType = m_paintCanvasGroup->getPaintCanvasType();
		m_settings.language = TRANSLATIONS->GetSelectedLanguage()!=Translations::eLanguageUndefined?TRANSLATIONS->GetSelectedLanguage():Translations::eLanguageEnglish;
		m_settingsDialog = new PosteRazorSettingsDialog();
		m_settingsDialog->set_modal();
	}
	
	m_settingsDialog->setOptionsAndHandler(&m_settings, this);
	
	posteRazorSettings settingsbackup = m_settings;
	bool languageIsUndefinedBackup = m_UILanguageIsUndefined;
	if (!m_settingsDialog->show_modal())
	{
		handleOptionsChangement(&settingsbackup);
		m_UILanguageIsUndefined = languageIsUndefinedBackup;
	}
}

void PosteRazorDialog::openHelpDialog(void)
{
	if (!m_helpDialog)
	{
		m_helpDialog = new PosteRazorHelpDialog();
		m_helpDialog->updateLanguage();
		m_helpDialog->set_modal();
	}

	char stepTopic[1024];
	sprintf(stepTopic, POSTERAZORHELPANCHORMANUALSTEP "%.2d", getCurrentWizardStepNumber() + 1);

	m_helpDialog->setHtmlContent(TRANSLATIONS->helpHtml());
	m_helpDialog->jumpToAnchor(stepTopic);
	m_helpDialog->show();
}

void PosteRazorDialog::handleOptionsChangement(posteRazorSettings *settings)
{
	m_posteRazorController->setUnitOfLength(settings->unitOfLength);
	m_paintCanvasGroup->setPaintCanvasType(settings->previewType);
	updatePreviewState();

	if (TRANSLATIONS->GetSelectedLanguage() != settings->language)
	{
		TRANSLATIONS->SelectLangue(settings->language);
		m_UILanguageIsUndefined = false;
		updateLanguage();
	}
	m_settings = *settings;
}

void PosteRazorDialog::next(void)
{
	m_posteRazorController->handleNextButtonPressed();
	updatePreviewState();
}

void PosteRazorDialog::prev(void)
{
	m_posteRazorController->handlePrevButtonPressed();
	updatePreviewState();
}

void PosteRazorDialog::updateNavigationButtons(void)
{
}

const char* PosteRazorDialog::getWizardStepInfoString(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step)
{
	return
	(
		step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage?TRANSLATIONS->stepTitle01()
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize?TRANSLATIONS->stepTitle02()
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?TRANSLATIONS->stepTitle03()
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize?TRANSLATIONS->stepTitle04()
		:TRANSLATIONS->stepTitle05()
	);
}

int PosteRazorDialog::getCurrentWizardStepNumber(void)
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

void PosteRazorDialog::updateStepInfoBar(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step)
{
	char stepStr[1024];
	sprintf(stepStr, TRANSLATIONS->stepXOfY(), getCurrentWizardStepNumber() + 1, 5); 
	char helpTitleStr[1024];
	sprintf(helpTitleStr, "  %s: %s", stepStr, getWizardStepInfoString(step));
	m_stepInfoBox->copy_label(helpTitleStr);
}

void PosteRazorDialog::updatePreview(void)
{
	m_paintCanvasGroup->redraw();
}

void PosteRazorDialog::updatePreviewState(void)
{
	m_paintCanvasGroup->setState
	(
		m_wizard->value() == m_loadInputImageStep?"image"
		:m_wizard->value() == m_paperSizeStep?"paper"
		:m_wizard->value() == m_overlappingStep?"overlapping"
		:"poster"
	);

	updatePreview();
}

void PosteRazorDialog::updateLanguage(void)
{
	char tempStr[1024];

	sprintf(tempStr, "%s @-2->", TRANSLATIONS->next());
	m_nextButton->copy_label(tempStr);
	sprintf(tempStr, "@-2<- %s", TRANSLATIONS->back());
	m_prevButton->copy_label(tempStr);

	m_paperFormatTypeTabs->label(TRANSLATIONS->paperFormat());
	m_paperFormatCustomGroup->label(TRANSLATIONS->custom());
	m_paperFormatStandardGroup->label(TRANSLATIONS->standard());
	m_paperFormatChoice->label(TRANSLATIONS->format());
	m_paperOrientationGroup->label(TRANSLATIONS->orientation());
	m_paperOrientationLandscapeRadioButton->label(TRANSLATIONS->landscape());
	m_paperOrientationPortraitRadioButton->label(TRANSLATIONS->portrait());
	m_paperCustomHeightInput->label(TRANSLATIONS->height());
	m_paperCustomWidthInput->label(TRANSLATIONS->width());
	m_paperBorderTopInput->label(TRANSLATIONS->top());
	m_paperBorderRightInput->label(TRANSLATIONS->right());
	m_paperBorderBottomInput->label(TRANSLATIONS->bottom());
	m_paperBorderLeftInput->label(TRANSLATIONS->left());

	m_overlappingHeightInput->label(TRANSLATIONS->height());
	m_overlappingWidthInput->label(TRANSLATIONS->width());
	m_overlappingPositionGroup->label(TRANSLATIONS->overlappingPosition());
	m_overlappingSizeGroup->label(TRANSLATIONS->overlappingSize());
	m_overlappingPositionBottomLeftButton->label(TRANSLATIONS->bottomLeft());
	m_overlappingPositionBottomRightButton->label(TRANSLATIONS->bottomRight());
	m_overlappingPositionTopLeftButton->label(TRANSLATIONS->topLeft());
	m_overlappingPositionTopRightButton->label(TRANSLATIONS->topRight());

	m_posterSizeGroup->label(TRANSLATIONS->imageSize());
	m_posterSizeAbsoluteRadioButton->label(TRANSLATIONS->absoluteSize());
	m_posterAbsoluteHeightInput->label(TRANSLATIONS->height());
	m_posterAbsoluteWidthInput->label(TRANSLATIONS->width());
	m_posterSizeInPagesRadioButton->label(TRANSLATIONS->sizeInPages());
	m_posterPagesHeightInput->label(TRANSLATIONS->height());
	m_posterPagesHeightLabel->label(TRANSLATIONS->pages());
	m_posterPagesWidthInput->label(TRANSLATIONS->width());
	m_posterPagesWidthLabel->label(TRANSLATIONS->pages());
	m_posterSizePercentualRadioButton->label(TRANSLATIONS->sizeInPercent());
	m_posterPercentualSizeInput->label(TRANSLATIONS->Size());
	m_imageAlignmentGroup->label(TRANSLATIONS->imageAlignment());
	m_imageInfoGroup->label(TRANSLATIONS->imageInformations());
	m_imageLoadGroup->label(TRANSLATIONS->inputImage());
	m_settingsButton->label(TRANSLATIONS->settings());

	m_savePosterGroup->label(TRANSLATIONS->saveThePoster());
	m_setLaunchPDFApplicationCheckButton->label(TRANSLATIONS->launchPDFApplication());

	m_posteRazorController->updateDialog();

	if (m_settingsDialog)
		m_settingsDialog->updateLanguage();

	if (m_helpDialog)
		m_helpDialog->updateLanguage();

	redraw();
}

void PosteRazorDialog::loadInputImage(const char *fileName)
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
		"Graphic Interchange format (*.GIF)\t*.GIF\n"\
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
		"Tagged Image File format (*.TIF;*.TIFF)\t*.{TIF,TIFF}\n"\
		"Wireless Bitmap (*.WBMP)\t*.WBMP\n"\
		"X11 Bitmap (*.XBM)\t*.XBM\n"\
		"X11 Pixmap (*.XPM)\t*.XPM",
		TRANSLATIONS->allImageFormats()
	);
	loadImageChooser.filter(filterString);
#endif
	loadImageChooser.title(TRANSLATIONS->loadAnInputImage());

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
		loaded = m_posteRazorController->loadInputImage(loadFileName, errorMessage, sizeof(errorMessage));
		if (!loaded)
		{
			if (strlen(errorMessage) > 0)
				fl_message(errorMessage);
			else
				fl_message(TRANSLATIONS->fileCouldNotBeLoaded(), fl_filename_name(loadFileName));
		}
	}

	if (loaded)
	{
		m_imageInfoGroup->activate();
		m_paintCanvasGroup->requestImage();
	}

	updateNavigationButtons();
	Fl::flush(); // Needed for windows if image is loaded at startup
}

void PosteRazorDialog::showImageFileName(const char *fileName)
{
	m_inputFileNameLabel->copy_label(fl_filename_name(fileName));
}

void PosteRazorDialog::updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel)
{
	char sizeInDimensionUnitString[100];
	sprintf(sizeInDimensionUnitString, TRANSLATIONS->sizeInUnitOfLength(), UnitsOfLength::getUnitOfLengthName(unitOfLength));

	char string[1024];

	sprintf
	(
		string,
		"%s\n%s\n%s\n%s",
		TRANSLATIONS->sizeInPixels(),
		sizeInDimensionUnitString,
		TRANSLATIONS->resolution(),
		TRANSLATIONS->colorType()
	);
	m_imageInfoKeysLabel->copy_label(string);

	sprintf
	(
		string,
		"%d x %d\n%.2f x %.2f\n%.1f dpi\n%s %dbpp",
		imageWidthInPixels, imageHeightInPixels,
		imageWidth, imageHeight,
		verticalDpi,
			colorType==ColorTypes::eColorTypeMonochrome?TRANSLATIONS->monochrome():
			colorType==ColorTypes::eColorTypeGreyscale?TRANSLATIONS->grayscale():
			colorType==ColorTypes::eColorTypePalette?TRANSLATIONS->palette():
			colorType==ColorTypes::eColorTypeRGB?"RGB":
			colorType==ColorTypes::eColorTypeRGBA?"RGBA":
			/*colorType==eColorTypeCMYK?*/ "CMYK",
		bitsPerPixel
	);
	m_imageInfoValuesLabel->copy_label(string);
}

void PosteRazorDialog::updatePosterSizeFields(Fl_Widget *sourceWidget)
{
	if (sourceWidget == m_posterAbsoluteWidthInput)
		m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute, m_posterAbsoluteWidthInput->value());
	else if (sourceWidget == m_posterAbsoluteHeightInput)
		m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute, m_posterAbsoluteHeightInput->value());
	else if (sourceWidget == m_posterPagesWidthInput)
		m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModePages, m_posterPagesWidthInput->value());
	else if (sourceWidget == m_posterPagesHeightInput)
		m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModePages, m_posterPagesHeightInput->value());
	else // if (sourceWidget == m_posterPercentualSizeInput)
		m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModePercentual, m_posterPercentualSizeInput->value());
}

void PosteRazorDialog::handlePaperFormatChoice_cb(Fl_Widget *widget, void *userData)
{
	((PosteRazorDialog*)userData)->handlePaperSizeChangement(((PosteRazorDialog*)userData)->m_paperFormatChoice);
}

void PosteRazorDialog::handlePaperSizeChangement(Fl_Widget *sourceWidget)
{
	if (sourceWidget == m_paperBorderTopInput)
		m_posteRazorController->setPaperBorderTop(m_paperBorderTopInput->value());
	else if (sourceWidget == m_paperBorderRightInput)
		m_posteRazorController->setPaperBorderRight(m_paperBorderRightInput->value());
	else if (sourceWidget == m_paperBorderBottomInput)
		m_posteRazorController->setPaperBorderBottom(m_paperBorderBottomInput->value());
	else if (sourceWidget == m_paperBorderLeftInput)
		m_posteRazorController->setPaperBorderLeft(m_paperBorderLeftInput->value());
	else if (sourceWidget == m_paperFormatTypeTabs)
		m_posteRazorController->setUseCustomPaperSize(m_paperFormatTypeTabs->value() == m_paperFormatCustomGroup);
	else if (sourceWidget == m_paperFormatChoice)
	{
		const char* paperFormatName = m_paperFormatMenuItems[m_paperFormatChoice->value()].label();
		m_posteRazorController->setPaperFormatByName(paperFormatName);
	}
	else if (sourceWidget == m_paperOrientationPortraitRadioButton || sourceWidget == m_paperOrientationLandscapeRadioButton)
		m_posteRazorController->setPaperOrientation(m_paperOrientationLandscapeRadioButton->value() != 0?PaperFormats::ePaperOrientationLandscape:PaperFormats::ePaperOrientationPortrait);
	else if (sourceWidget == m_paperCustomWidthInput)
		m_posteRazorController->setCustomPaperWidth(m_paperCustomWidthInput->value());
	else if (sourceWidget == m_paperCustomHeightInput)
		m_posteRazorController->setCustomPaperHeight(m_paperCustomHeightInput->value());
}

void PosteRazorDialog::handleOverlappingChangement(Fl_Widget *sourceWidget)
{
	if (sourceWidget == m_overlappingWidthInput)
		m_posteRazorController->setOverlappingWidth(m_overlappingWidthInput->value());
	else if (sourceWidget == m_overlappingHeightInput)
		m_posteRazorController->setOverlappingHeight(m_overlappingHeightInput->value());
	else
		m_posteRazorController->setOverlappingPosition
		(
			m_overlappingPositionBottomRightButton->value()?PosteRazorEnums::eOverlappingPositionBottomRight
			:m_overlappingPositionBottomLeftButton->value()?PosteRazorEnums::eOverlappingPositionBottomLeft
			:m_overlappingPositionTopLeftButton->value()?PosteRazorEnums::eOverlappingPositionTopLeft
			:PosteRazorEnums::eOverlappingPositionTopRight
		);
}

void PosteRazorDialog::updatePosterSizeGroupsState(void)
{
	m_posterSizeAbsoluteRadioButton->value() == 0?m_posterSizeAbsoluteGroup->deactivate():m_posterSizeAbsoluteGroup->activate();
	m_posterSizeInPagesRadioButton->value() == 0?m_posterSizeInPagesGroup->deactivate():m_posterSizeInPagesGroup->activate();
	m_posterSizePercentualRadioButton->value() == 0?m_posterSizePercentualGroup->deactivate():m_posterSizePercentualGroup->activate();
}

void PosteRazorDialog::handlePosterImageAlignment(void)
{
	m_posteRazorController->setPosterVerticalAlignment
	(
		m_posterAlignmentTopButton->value() == 1?PosteRazorEnums::eVerticalAlignmentTop
		:m_posterAlignmentMiddleButton->value() == 1?PosteRazorEnums::eVerticalAlignmentMiddle
		:PosteRazorEnums::eVerticalAlignmentBottom
	);
	
	m_posteRazorController->setPosterHorizontalAlignment
	(
		m_posterAlignmentLeftButton->value() == 1?PosteRazorEnums::eHorizontalAlignmentLeft
		:m_posterAlignmentCenterButton->value() == 1?PosteRazorEnums::eHorizontalAlignmentCenter
		:PosteRazorEnums::eHorizontalAlignmentRight
	);
}

// dirty 
static bool my_file_exists(const char* fileName)
{
	return (access(fileName, 0) == 0);
}

void PosteRazorDialog::savePoster(void)
{
	char saveFileName[1024] = "";
	bool fileExistsAskUserForOverwrite = false;
	
	Fl_Native_File_Chooser savePosterChooser(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
#ifndef __APPLE__
// filter stuff is still crashy os OSX
	savePosterChooser.filter("Portable Document format (*.PDF)\t*.pdf");
#endif
	savePosterChooser.title(TRANSLATIONS->saveThePosterAs());

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
			sprintf(overwriteQuestion, TRANSLATIONS->overwriteFile(), fl_filename_name(saveFileName));
			if (!fileExistsAskUserForOverwrite || fl_ask(overwriteQuestion))
			{
				int err = m_posteRazorController->savePoster(saveFileName);
				if (err)
					fl_message("The file '%s' could not be saved.", fl_filename_name(saveFileName));
				fileExistsAskUserForOverwrite = false;
			}
		}
		else
			break;
	} while (fileExistsAskUserForOverwrite);
}

void PosteRazorDialog::setLaunchPDFApplication(void)
{
	m_posteRazorController->setLaunchPDFApplication(m_setLaunchPDFApplicationCheckButton->value()==0?false:true);
}

void PosteRazorDialog::setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
	const char* unitName = UnitsOfLength::getUnitOfLengthName(unit);
	m_paperCustomWidthDimensionUnitLabel->label(unitName);
	m_paperCustomHeightDimensionUnitLabel->label(unitName);
	m_overlappingWidthDimensionUnitLabel->label(unitName);
	m_overlappingHeightDimensionUnitLabel->label(unitName);
	m_posterAbsoluteWidthDimensionUnitLabel->label(unitName);
	m_posterAbsoluteHeightDimensionUnitLabel->label(unitName);
	char paperBordersGroupLabel[100];
	sprintf(paperBordersGroupLabel, "%s (%s)", TRANSLATIONS->borders(), unitName);
	m_paperBordersGroup->copy_label(paperBordersGroupLabel);
}

void PosteRazorDialog::setPaperFormat(PaperFormats::ePaperFormats format)
{
	m_paperFormatChoice->value((int)format);
}

void PosteRazorDialog::setPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
	// standard paper format
	m_paperOrientationPortraitRadioButton->value(orientation == PaperFormats::ePaperOrientationPortrait);
	m_paperOrientationLandscapeRadioButton->value(orientation == PaperFormats::ePaperOrientationLandscape);
}

void PosteRazorDialog::setPaperBorderTop(double border)
{
	m_paperBorderTopInput->value(border);
}

void PosteRazorDialog::setPaperBorderRight(double border)
{
	m_paperBorderRightInput->value(border);
}

void PosteRazorDialog::setPaperBorderBottom(double border)
{
	m_paperBorderBottomInput->value(border);
}

void PosteRazorDialog::setPaperBorderLeft(double border)
{
	m_paperBorderLeftInput->value(border);
}

void PosteRazorDialog::setCustomPaperWidth(double width)
{
	m_paperCustomWidthInput->value(width);
}

void PosteRazorDialog::setCustomPaperHeight(double height)
{
	m_paperCustomHeightInput->value(height);
}

void PosteRazorDialog::setUseCustomPaperSize(bool useIt)
{
	// select the active tab
	m_paperFormatTypeTabs->value(useIt?m_paperFormatCustomGroup:m_paperFormatStandardGroup);
}

void PosteRazorDialog::setOverlappingWidth(double width)
{
	m_overlappingWidthInput->value(width);
}

void PosteRazorDialog::setOverlappingHeight(double height)
{
	m_overlappingHeightInput->value(height);
}

void PosteRazorDialog::setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
{
	(
		position == PosteRazorEnums::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:position == PosteRazorEnums::eOverlappingPositionBottomLeft?m_overlappingPositionBottomLeftButton
		:position == PosteRazorEnums::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:m_overlappingPositionTopRightButton
	)->setonly();
}

void PosteRazorDialog::setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
	if (mode == PosteRazorEnums::ePosterSizeModeAbsolute)
		m_posterAbsoluteWidthInput->value(width);
	else if (mode == PosteRazorEnums::ePosterSizeModePages)
		m_posterPagesWidthInput->value(width);
	else
		m_posterPercentualSizeInput->value(width);
}

void PosteRazorDialog::setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
	if (mode == PosteRazorEnums::ePosterSizeModeAbsolute)
		m_posterAbsoluteHeightInput->value(height);
	else if (mode == PosteRazorEnums::ePosterSizeModePages)
		m_posterPagesHeightInput->value(height);
	else
		m_posterPercentualSizeInput->value(height);
}

void PosteRazorDialog::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
	if (mode == PosteRazorEnums::ePosterSizeModeAbsolute)
		m_posterSizeAbsoluteRadioButton->setonly();
	else if (mode == PosteRazorEnums::ePosterSizeModePages)
		m_posterSizeInPagesRadioButton->setonly();
	else // if (mode == PosteRazorEnums::ePosterSizeModePercentual)
		m_posterSizePercentualRadioButton->setonly();
	updatePosterSizeGroupsState();
}

void PosteRazorDialog::setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eHorizontalAlignmentLeft?m_posterAlignmentLeftButton
		:alignment == PosteRazorEnums::eHorizontalAlignmentCenter?m_posterAlignmentCenterButton
		:m_posterAlignmentRightButton 
	)->setonly();
}

void PosteRazorDialog::setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:alignment == PosteRazorEnums::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton 
	)->setonly();
}

void PosteRazorDialog::setPosterOutputFormat(ImageIOTypes::eImageFormats format)
{
}

void PosteRazorDialog::setLaunchPDFApplication(bool launch)
{
	m_setLaunchPDFApplicationCheckButton->value(launch?1:0);
}

void PosteRazorDialog::setPrevButtonEnabled(bool enabled)
{
	enabled?m_prevButton->activate():m_prevButton->deactivate();
}

void PosteRazorDialog::setNextButtonEnabled(bool enabled)
{
	enabled?m_nextButton->activate():m_nextButton->deactivate();
}

void PosteRazorDialog::setWizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step)
{
	m_wizard->value
	(
		step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage?m_loadInputImageStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize?m_paperSizeStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?m_overlappingStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize?m_posterSizeStep
		:/* step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster? */m_savePosterStep
	);

	updateStepInfoBar(step);
}

#ifdef __APPLE__
static char OSX_droppedFilenameOnIcon[2048] = "";
static PosteRazorDialog *OSX_posteRazorDialogPointer = NULL;

static void	OSX_open_cb(const char* droppedFileName)
{
	if (OSX_posteRazorDialogPointer)
	{
		// File was dropped on the already running application
		OSX_posteRazorDialogPointer->loadInputImage(droppedFileName);
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
		dialog.loadInputImage(argv[1]);
#else
	if (strcmp(OSX_droppedFilenameOnIcon, "") != 0)
		dialog.loadInputImage(OSX_droppedFilenameOnIcon);

	OSX_posteRazorDialogPointer = &dialog;
#endif

	return Fl::run();
}
