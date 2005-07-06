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
	bool loaded = m_posteRazor->LoadInputImage("c:\\buibui.png");

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
	m_previewImageData = new unsigned char[m_previewImageGroup->w() * m_previewImageGroup->h() * 3];
		
	m_posteRazor->GetPreview(m_previewImageData, m_previewImageGroup->w(),  m_previewImageGroup->h());

	m_previewImage = new Fl_RGB_Image(m_previewImageData, m_previewImageGroup->w(),  m_previewImageGroup->h());
	m_previewImageGroup->image(m_previewImage);

	Fl::redraw();
}

void PosteRazorDialog::resize(int x, int y, int w, int h)
{
	int huhu = 1;
}

int main (int argc, char **argv)
{
	PosteRazorDialog dialog;
	Fl::scheme("plastic");
	dialog.show(argc, argv);

	Fl::run();
}