/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "mainwindow.h"
#include <QSettings>
#include <QApplication>
#include <QTranslator>
#include "PosteRazorDialogController.h"
#include "PosteRazorWizardDialogController.h"

int main (int argc, char **argv)
{
	QApplication a(argc, argv);

	QTranslator myAppTranslator;
	myAppTranslator.load(":/Translations/" + QLocale::system().name());
	a.installTranslator(&myAppTranslator);

	QCoreApplication::setApplicationName("PosteRazor");
	QCoreApplication::setApplicationVersion("1.9.0-alpha");
	QCoreApplication::setOrganizationName("CasaPortale");
	QCoreApplication::setOrganizationDomain("de.casaportale");

	MainWindow dialog;
	PosteRazor posteRazor;

	PosteRazorDialogController *controller = new PosteRazorDialogController;
	PosteRazorWizardDialogController *wizardController = new PosteRazorWizardDialogController;

	QSettings settings;
	controller->setPosteRazorAndDialog(&posteRazor, &dialog);
	controller->readSettings(&settings);
	wizardController->setPosteRazorWizardDialog(&dialog);

	dialog.show();
	if (argc == 2)
		controller->loadInputImage(argv[1]);

	const int appReturn = a.exec();
	controller->writeSettings(&settings);

	return appReturn;
}
