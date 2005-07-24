#include "PosteRazorDialog.h"
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI(620, 435, "PosteRazor")
{
	m_previewImageData = 0;
	m_previewImage = 0;
	m_posteRazor = PosteRazor::CreatePosteRazor();
	m_needPreviewImageUpdate = false;

	UpdateNavigationButtons();
}

PosteRazorDialog::~PosteRazorDialog()
{
	DisposePreviewImage();
}

void PosteRazorDialog::next(void)
{
	m_wizard->next();
	UpdateNavigationButtons();
}

void PosteRazorDialog::prev(void)
{
	m_wizard->prev();
	UpdateNavigationButtons();
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
		m_previewImageGroup->image(NULL);
		m_previewImageGroup->label("...please wait...");
		Fl::wait();
		m_inputFileNameLabel->copy_label(fl_filename_name(chooser.filename()));
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

	DisposePreviewImage();

	m_posteRazor->GetInputImagePreviewSize(m_previewImageGroup->w() - 14, m_previewImageGroup->h() - 14, previewImageWidth, previewImageHeight);
	m_previewImageData = new unsigned char[previewImageWidth * previewImageHeight * 3];
	m_posteRazor->GetInputImagePreview(m_previewImageData, previewImageWidth,  previewImageHeight);

	m_previewImage = new Fl_RGB_Image(m_previewImageData, previewImageWidth,  previewImageHeight);
	m_previewImageGroup->image(m_previewImage);

	Fl::redraw();
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

void PosteRazorDialog::SetPageSizeFields(void)
{

}

void PosteRazorDialog::UpdatePageSizeFields(void)
{
	if (m_standardPageSizeRadioButton->value())
	{
		m_standardPageSizeGroup->activate();
		m_customPageSizeGroup->deactivate();
	}
	else
	{
		m_standardPageSizeGroup->deactivate();
		m_customPageSizeGroup->activate();
	}
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

int main (int argc, char **argv)
{
	PosteRazorDialog dialog;
	Fl::scheme("plastic");
	dialog.show(argc, argv);

	Fl::run();
}