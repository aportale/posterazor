#include "PosteRazorDialog.h"
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI(620, 455, "PosteRazor")
{
	m_posteRazor = PosteRazor::CreatePosteRazor();

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

	if (m_posteRazor->GetPosterSizeMode() == PosteRazor::ePosterSizeModeAbsolute)
		m_posterSizeAbsoluteRadioButton->value(1);
	else if (m_posteRazor->GetPosterSizeMode() == PosteRazor::ePosterSizeModePages)
		m_posterSizeInPagesRadioButton->value(1);
	else // if (m_posteRazor->GetPosterSizeMode() == PosteRazor::ePosterSizeModePercentual)
		m_posterSizePercentualRadioButton->value(1);
	UpdatePosterSizeGroupsState();

	m_imageInfoGroup->deactivate();

	m_previewPaintCanvas->SetPainterInterface(m_posteRazor);

	UpdateNavigationButtons();
	UpdatePreviewState();
	SetPaperSizeFields();
}

PosteRazorDialog::~PosteRazorDialog()
{
	if (m_paperFormatMenuItems)
		delete[] m_paperFormatMenuItems;
}

void PosteRazorDialog::next(void)
{
	UpdatePosterSizeFields(NULL);
	m_wizard->next();
	UpdateNavigationButtons();
	UpdatePreviewState();
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
		:"poster"
	);
	m_previewPaintCanvas->redraw();
}

void PosteRazorDialog::LoadInputImage(void)
{
	Fl_Native_File_Chooser chooser;
	char errorMessage[1024] = "";
	bool loaded = false;

//	chooser.AddPattern();

	if (chooser.show() == 0)
	{
		loaded = m_posteRazor->LoadInputImage(chooser.filename(), errorMessage, sizeof(errorMessage));
		if (!loaded)
		{
			if (strlen(errorMessage) > 0)
				fl_message(errorMessage);
			else
				fl_message("The file '%s' could not be loaded.", fl_filename_name(chooser.filename()));
		}
	}

	if (loaded)
	{
		UpdateImageInfoFields();
		m_imageInfoGroup->activate();
		m_inputFileNameLabel->copy_label(fl_filename_name(chooser.filename()));
		m_previewPaintCanvas->RequestImage();
		m_previewPaintCanvas->redraw();
		UpdatePosterSizeFields(NULL);
		Fl::wait();
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

	for (int i = 0; i < sizeInputWidgetsCount; i++)
	{
		if (sizeInputWidgets[i].inputWidget == sourceWidget)
		{
			if (sizeInputWidgets[i].width)
				m_posteRazor->SetPosterWidth(sizeInputWidgets[i].sizeMode, sizeInputWidgets[i].inputWidget->value());
			else
				m_posteRazor->SetPosterHeight(sizeInputWidgets[i].sizeMode, sizeInputWidgets[i].inputWidget->value());
		}
	}

	for (int i = 0; i < sizeInputWidgetsCount; i++)
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
}

void PosteRazorDialog::SetPaperSizeFields(void)
{
	// standard paper format
	m_paperOrientationPortraitRadioButton->value(m_posteRazor->GetPaperOrientation() == PosteRazor::ePaperOrientationPortrait);
	m_paperOrientationLandscapeRadioButton->value(m_posteRazor->GetPaperOrientation() == PosteRazor::ePaperOrientationLandscape);
	m_paperBorderTopInput->value(m_posteRazor->GetPaperBorderTop());
	m_paperBorderRightInput->value(m_posteRazor->GetPaperBorderRight());
	m_paperBorderBottomInput->value(m_posteRazor->GetPaperBorderBottom());
	m_paperBorderLeftInput->value(m_posteRazor->GetPaperBorderLeft());

	// custom paper format
	double customWidth, customHeight;
	m_posteRazor->GetCustomPaperSize(customWidth, customHeight);
	m_paperCustomWidthInput->value(customWidth);
	m_paperCustomHeightInput->value(customHeight);

	// radio buttons
	m_paperFormatTypeTabs->value(m_paperFormatCustomGroup);
}

void PosteRazorDialog::HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData)
{
	((PosteRazorDialog*)userData)->HandlePaperSizeChangement();
}

void PosteRazorDialog::HandlePaperSizeChangement(void)
{
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
		m_posteRazor->SetCustomPaperSize(m_paperCustomWidthInput->value(), m_paperCustomHeightInput->value());
	}

	m_posteRazor->SetPaperBorderTop(m_paperBorderTopInput->value());
	m_posteRazor->SetPaperBorderRight(m_paperBorderRightInput->value());
	m_posteRazor->SetPaperBorderBottom(m_paperBorderBottomInput->value());
	m_posteRazor->SetPaperBorderLeft(m_paperBorderLeftInput->value());

	m_previewPaintCanvas->redraw();
}

void PosteRazorDialog::UpdatePosterSizeGroupsState(void)
{
	m_posterSizeAbsoluteRadioButton->value() == 0?m_posterSizeAbsoluteGroup->deactivate():m_posterSizeAbsoluteGroup->activate();
	m_posterSizeInPagesRadioButton->value() == 0?m_posterSizeInPagesGroup->deactivate():m_posterSizeInPagesGroup->activate();
	m_posterSizePercentualRadioButton->value() == 0?m_posterSizePercentualGroup->deactivate():m_posterSizePercentualGroup->activate();
}

int main (int argc, char **argv)
{
	PosteRazorDialog dialog;
	Fl::scheme("plastic");
	dialog.show(argc, argv);

	Fl::run();
}
