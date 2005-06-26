#include "PosteRazorDialog.h"
#include "PosteRazor.h"

PosteRazorDialog::PosteRazorDialog(void)
	:PosteRazorDialogUI()
{
}

void PosteRazorDialog::next(void)
{
	m_wizard->next();
}

void PosteRazorDialog::prev(void)
{
	m_wizard->prev();
}

int main (int argc, char **argv)
{
	PosteRazorDialog dialog;
	Fl::scheme("plastic");
	dialog.show(argc, argv);
	PosteRazor* prz = PosteRazor::CreatePosteRazor("c:\\IMG_0184.tif");

	delete prz;
	Fl::run();
}