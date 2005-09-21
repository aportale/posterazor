#include "PosteRazorDialog.h"
#include "Fl_Persistent_Preferences.h"
#include <Fl/Fl_Native_File_Chooser.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>

const char PreferencesVendor[] = "CasaPortale.de";
const char PreferencesProduct[] = "PosteRazor";

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
	:PosteRazorDialogUI(620, 455, "PosteRazor")
{
	begin();
	m_dragDropWidget = new PosteRazorDragDropWidget(0, 0, w(), h());
	end();

	m_posteRazor = PosteRazor::CreatePosteRazor();
	Fl_Persistent_Preferences preferences(PreferencesVendor, PreferencesProduct);
	m_posteRazor->ReadPersistentPreferences(&preferences);

	int paperFormatMenuItemsCount = PosteRazor::GetPaperFormatsCount()+1;
	m_paperFormatMenuItems = new Fl_Menu_Item[paperFormatMenuItemsCount];
	memset(m_paperFormatMenuItems, 0, sizeof(Fl_Menu_Item)*paperFormatMenuItemsCount);
	for (int i = 0; i < PosteRazor::GetPaperFormatsCount(); i++)
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

	m_imageInfoGroup->deactivate();

	m_previewPaintCanvas->SetPainterInterface(m_posteRazor);

	UpdateNavigationButtons();
	UpdatePreviewState();
	SetPaperSizeFields();
	SetOverlappingFields();
}

PosteRazorDialog::~PosteRazorDialog()
{
	Fl_Persistent_Preferences preferences(PreferencesVendor, PreferencesProduct);
	m_posteRazor->WritePersistentPreferences(&preferences);

	if (m_paperFormatMenuItems)
		delete[] m_paperFormatMenuItems;
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

void PosteRazorDialog::next(void)
{
	UpdatePosterSizeFields(NULL);
	m_wizard->next();
	UpdateNavigationButtons();
	UpdatePreviewState();
	UpdatePosterSizeFields(NULL);
}

void PosteRazorDialog::prev(void)
{
	m_wizard->prev();
	UpdateNavigationButtons();
	UpdatePreviewState();
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

void PosteRazorDialog::UpdatePreviewState(void)
{
	m_previewPaintCanvas->SetState
	(
		m_wizard->value() == m_loadInputImageStep?"image"
		:m_wizard->value() == m_paperSizeStep?"paper"
		:m_wizard->value() == m_overlappingStep?"overlapping"
		:"poster"
	);
	m_previewPaintCanvas->redraw();
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
				fl_message("The file '%s' could not be loaded.", fl_filename_name(loadFileName));
		}
	}

	if (loaded)
	{
		UpdateImageInfoFields();
		m_imageInfoGroup->activate();
		m_inputFileNameLabel->copy_label(fl_filename_name(loadFileName));
		m_previewPaintCanvas->RequestImage();
		m_previewPaintCanvas->redraw();
		UpdatePosterSizeFields(NULL);
	}

	UpdateNavigationButtons();
}

void PosteRazorDialog::UpdateImageInfoFields(void)
{
	char string[1024];
	enum PosteRazor::eColorTypes colorType = m_posteRazor->GetInputImageColorType();

	sprintf
	(
		string,
		"Size (pixels):\nSize (%s):\nResolution:\nColor type:",
		m_posteRazor->GetDistanceUnitName()
	);
	m_imageInfoKeysLabel->copy_label(string);

	sprintf
	(
		string,
		"%d x %d\n%.2f x %.2f\n%.1f dpi\n%s %dbpp",
		m_posteRazor->GetInputImageWidthPixels(), m_posteRazor->GetInputImageHeightPixels(),
		m_posteRazor->GetInputImageWidth(), m_posteRazor->GetInputImageHeight(),
		m_posteRazor->GetInputImageVerticalDpi(),
			colorType==PosteRazor::eColorTypeMonochrome?"Monochrome":
			colorType==PosteRazor::eColorTypeGreyscale?"Greyscale":
			colorType==PosteRazor::eColorTypePalette?"Palette":
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

	m_previewPaintCanvas->redraw();
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

	m_previewPaintCanvas->redraw();
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

	m_previewPaintCanvas->redraw();
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
	
	m_previewPaintCanvas->redraw();
}

int main (int argc, char **argv)
{
	PosteRazorDialog dialog;
	dialog.show(argc, argv);
#ifdef WIN32
	dialog.LoadInputImage("c:\\image.png");
#else
	dialog.LoadInputImage("/temp/image.png");
#endif
	Fl::scheme("plastic");

	return Fl::run();
}
