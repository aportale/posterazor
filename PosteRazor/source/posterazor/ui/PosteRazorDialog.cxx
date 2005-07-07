#include "PosteRazorDialog.h"

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
	bool loaded = m_posteRazor->LoadInputImage("D:\\Döner.gif");

	if (loaded)
		UpdatePreviewImage();
}

void PosteRazorDialog::DisposePreviewImage(void)
{
	if (m_previewImageData)
		delete[] m_previewImageData;
	if (m_previewImage)
		delete m_previewImage;
}

void PosteRazorDialog::UpdatePreviewImage(void)
{
	int previewImageWidth;
	int previewImageHeight;
	
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