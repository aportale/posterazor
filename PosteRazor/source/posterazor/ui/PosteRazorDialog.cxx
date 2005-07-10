#include "PosteRazorDialog.h"
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI()
{
	m_previewImageData = 0;
	m_previewImage = 0;
	m_posteRazor = PosteRazor::CreatePosteRazor();
}

PosteRazorDialog::~PosteRazorDialog()
{
	DisposePreviewImage();
}

void PosteRazorDialog::next(void)
{
	m_wizard->next();
}

void PosteRazorDialog::prev(void)
{
	m_wizard->prev();
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
		Fl::wait();
	}
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

void PosteRazorDialog::UpdatePreviewImage(void)
{
	int previewImageWidth;
	int previewImageHeight;

	DisposePreviewImage();

	m_posteRazor->GetPreviewSize(m_previewImageGroup->w() - 14, m_previewImageGroup->h() - 14, previewImageWidth, previewImageHeight);

	m_previewImageData = new unsigned char[previewImageWidth * previewImageHeight * 3];
		
	m_posteRazor->GetPreview(m_previewImageData, previewImageWidth,  previewImageHeight);

	m_previewImage = new Fl_RGB_Image(m_previewImageData, previewImageWidth,  previewImageHeight);
	m_previewImageGroup->image(m_previewImage);

	Fl::redraw();
}

int main (int argc, char **argv)
{
	PosteRazorDialog dialog;
	Fl::scheme("plastic");
	dialog.show(argc, argv);

	Fl::run();
}