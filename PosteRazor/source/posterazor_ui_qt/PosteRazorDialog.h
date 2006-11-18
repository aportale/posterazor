#ifndef POSTERAZORDIALOG_H
#define POSTERAZORDIALOG_H

#include <QDialog>
#include "ui_PosteRazorDialog.h"

class PosteRazorDialog : public QDialog, private Ui::PosteRazorDialogUI
{
	Q_OBJECT

public:
	PosteRazorDialog::PosteRazorDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
};

#endif
