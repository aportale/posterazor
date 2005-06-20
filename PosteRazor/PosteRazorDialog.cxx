#include "PosteRazorDialog.h"

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
	dialog.show();

	Fl::run();
}