#include "PosteRazorDialog.h"
#include <QApplication>

PosteRazorDialog::PosteRazorDialog(QWidget *parent, Qt::WFlags flags)
:	QDialog(parent)
{
	setupUi(this);
}

int main (int argc, char **argv)
{
	QApplication a(argc, argv);

	PosteRazorDialog *dialog = new PosteRazorDialog;
	dialog->show();

	return a.exec();
}