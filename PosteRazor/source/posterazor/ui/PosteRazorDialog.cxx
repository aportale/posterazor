#include "PosteRazorDialog.h"
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI(620, 455, "PosteRazor")
{
	m_previewImageData = 0;
	m_previewImage = 0;
	m_posteRazor = PosteRazor::CreatePosteRazor();
	m_needPreviewImageUpdate = false;

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

	UpdateNavigationButtons();
	SetPaperSizeFields();
}

PosteRazorDialog::~PosteRazorDialog()
{
	DisposePreviewImage();

	if (m_paperFormatMenuItems)
		delete[] m_paperFormatMenuItems;
}

void PosteRazorDialog::next(void)
{
	UpdatePosterSizeFields(NULL);
	m_wizard->next();
	UpdateNavigationButtons();
	UpdatePreviewImage();
}

void PosteRazorDialog::prev(void)
{
	m_wizard->prev();
	UpdateNavigationButtons();
	UpdatePreviewImage();
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
		m_previewImageGroup->image(NULL);
		m_previewImageGroup->label("...please wait...");
		Fl::wait();
		UpdatePreviewImage();
		m_previewImageGroup->label(NULL);
		UpdatePosterSizeFields(NULL);
		Fl::wait();
	}

	UpdateNavigationButtons();
}

void PosteRazorDialog::DisposePreviewImage(void)
{
	if (m_previewImageData)
	{
		delete[] m_previewImageData;
		m_previewImageData = NULL;
	}
	if (m_previewImage)
	{
		delete m_previewImage;
		m_previewImage = NULL;
	}
}

void PosteRazorDialog::UpdatePreviewImage_cp(void *ptr)
{
	PosteRazorDialog *dialog = (PosteRazorDialog*)ptr;
	dialog->UpdatePreviewImage();
}

void PosteRazorDialog::UpdatePreviewImage(void)
{
	int previewImageWidth;
	int previewImageHeight;
	int imagePreviewBoxWidth = m_previewImageGroup->w() - 14;
	int imagePreviewBoxHeight = m_previewImageGroup->h() - 14;

	DisposePreviewImage();

	if (m_wizard->value() == m_paperSizeStep)
		m_posteRazor->GetPaperPreviewSize(imagePreviewBoxWidth, imagePreviewBoxHeight, previewImageWidth, previewImageHeight);
	else
		m_posteRazor->GetInputImagePreviewSize(imagePreviewBoxWidth, imagePreviewBoxHeight, previewImageWidth, previewImageHeight);

	m_previewImageData = new unsigned char[previewImageWidth * previewImageHeight * 3];

	if (m_wizard->value() == m_paperSizeStep)
		m_posteRazor->GetPaperPreview(m_previewImageData, previewImageWidth, previewImageHeight, false);
	else
		m_posteRazor->GetInputImagePreview(m_previewImageData, previewImageWidth, previewImageHeight);

	m_previewImage = new Fl_RGB_Image(m_previewImageData, previewImageWidth, previewImageHeight);
	m_previewImageGroup->image(m_previewImage);

	Fl::redraw();
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

void PosteRazorDialog::resize(int x, int y, int w, int h)
{
	int old_w = this->w();
	int old_h = this->h();
	PosteRazorDialogUI::resize(x, y, w, h);
	if ((old_w != this->w()) || (old_h != this->h()))
	{
		if (Fl::has_timeout(UpdatePreviewImage_cp, this))
			Fl::remove_timeout(UpdatePreviewImage_cp, this);
		Fl::add_timeout(0.05, UpdatePreviewImage_cp, this);
	}
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

	UpdatePreviewImage();
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
