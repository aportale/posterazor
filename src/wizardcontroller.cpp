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

#include "wizardcontroller.h"
#include <QCoreApplication>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class HelpDialog : public QDialog
{
private:
    HelpDialog(const QString &title, const QString &text, QWidget *parent = 0);

public:
    static void showHelp(const QString &title, const QString &text, QWidget *parent = 0);
};

HelpDialog::HelpDialog(const QString &title, const QString &text, QWidget *parent)
    : QDialog(parent)
{
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setLayout(new QVBoxLayout);
    layout()->addWidget(new QLabel(text));
}

void HelpDialog::showHelp(const QString &title, const QString &text, QWidget *parent)
{
    HelpDialog *dialog = new HelpDialog(title, text, parent);
    dialog->show();
}

WizardController::WizardController(QObject *wizardDialog, QObject *parent)
    : QObject(parent)
    , m_wizardStep(WizardStepInputImage)
    , m_imageWasLoaded(false)
{
    connect(this, SIGNAL(wizardStepChanged(int)), wizardDialog, SLOT(setWizardStep(int)));
    connect(this, SIGNAL(wizardStepDescriptionChanged(const QString&, const QString&)), wizardDialog, SLOT(setWizardStepDescription(const QString&, const QString&)));
    connect(this, SIGNAL(prevButtonEnabled(bool)), wizardDialog, SLOT(setPrevButtonEnabled(bool)));
    connect(this, SIGNAL(nextButtonEnabled(bool)), wizardDialog, SLOT(setNextButtonEnabled(bool)));
    connect(this, SIGNAL(previewStateChanged(const QString&)), wizardDialog, SLOT(setPreviewState(const QString&)));
    connect(wizardDialog, SIGNAL(imageLoaded()), SLOT(handleImageLoaded()));
    connect(wizardDialog, SIGNAL(prevButtonPressed()), SLOT(handlePrevButtonPressed()));
    connect(wizardDialog, SIGNAL(nextButtonPressed()), SLOT(handleNextButtonPressed()));
    connect(wizardDialog, SIGNAL(wizardStepHelpSignal()), SLOT(showHelpForCurrentStep()));

    updateDialogWizardStep();
}

void WizardController::handleImageLoaded()
{
    m_imageWasLoaded = true;
    updateDialogWizardStep();
}

void WizardController::showManual()
{
}

void WizardController::showHelpForCurrentStep()
{
    HelpDialog::showHelp(stepTitle(m_wizardStep), stepHelp(m_wizardStep), NULL);
}

void WizardController::handlePrevButtonPressed()
{
    m_wizardStep =
        m_wizardStep == WizardStepSavePoster?WizardStepPosterSize
        :m_wizardStep == WizardStepPosterSize?WizardStepOverlapping
        :m_wizardStep == WizardStepOverlapping?WizardStepPaperSize
        :/* m_wizardStep == WizardStepPaperSize? */WizardStepInputImage;

    updateDialogWizardStep();
}

void WizardController::handleNextButtonPressed()
{
    m_wizardStep =
        m_wizardStep == WizardStepInputImage?WizardStepPaperSize
        :m_wizardStep == WizardStepPaperSize?WizardStepOverlapping
        :m_wizardStep == WizardStepOverlapping?WizardStepPosterSize
        :/* m_wizardStep == WizardStepPosterSize? */WizardStepSavePoster;

    updateDialogWizardStep();
}

void WizardController::updateDialogWizardStep()
{
    emit wizardStepChanged(m_wizardStep);
    emit previewStateChanged(
        m_wizardStep == WizardStepInputImage?QLatin1String("image")
        :m_wizardStep == WizardStepOverlapping?QLatin1String("overlapping")
        :m_wizardStep == WizardStepPaperSize?QLatin1String("paper")
        :m_wizardStep == WizardStepPosterSize?QLatin1String("poster")
        :QLatin1String("poster")
    );
    emit prevButtonEnabled(m_wizardStep != WizardStepInputImage);
    emit nextButtonEnabled(
        m_wizardStep != WizardStepSavePoster
        && m_imageWasLoaded
    );
    updateDialogWizardStepDescription();
}

void WizardController::updateDialogWizardStepDescription()
{
    emit wizardStepDescriptionChanged(
        QCoreApplication::translate("Help", "Step %1 of %2:").arg((int)m_wizardStep + 1).arg((int)m_wizardStepsCount),
        stepTitle(m_wizardStep)
    );
}

QString WizardController::stepTitle(WizardSteps step)
{
    return
        step == WizardStepInputImage?  QCoreApplication::translate("Help", "Load an input image")
        :step == WizardStepPaperSize?  QCoreApplication::translate("Help", "Printer paper format")
        :step == WizardStepOverlapping?QCoreApplication::translate("Help", "Image tile overlapping")
        :step == WizardStepPosterSize? QCoreApplication::translate("Help", "Final poster size")
        :                              QCoreApplication::translate("Help", "Save the Poster");
}

QString WizardController::stepHelp(WizardSteps step)
{
    QString result;
    switch (step) {
    case WizardStepInputImage:
        result = QCoreApplication::translate("Help",
            "Load an image by clicking the button with the open icon and selecting an image file, or by drag & dropping an image file on the PosteRazor. The drag & drop also works during the other steps.\n"
            "After loading the image, the most important informations are listed in the '%1' fields.",
            "Wizard step 1. Place holders: %1 = 'Image informations' (will be automatically inserted)")
            .arg(QCoreApplication::translate("Main window", "Image Informations"));
        break;
    case WizardStepPaperSize:
        result = QCoreApplication::translate("Help",
            "Define the paper sheet size that you use in your printer.\n"
            "A standard paper sheet size can be selected from the '%1' chooser, along with the desired paper sheet orientation.\n"
            "Alternatively, a custom paper sheet size can be defined in the '%2' tab.\n"
            "Paper borders are defined in the '%3' fields. Even if your printer does need no (or small) paper borders, some border might be needed to have enough area for gluing the final poster tiles together.",
            "Wizard step 2. Place holders: %1 = 'Format:', %2 = 'Custom', %3 = 'Borders (%1)' (will be automatically inserted)")
            .arg(QCoreApplication::translate("Main window", "Format:"))
            .arg(QCoreApplication::translate("Main window", "Custom"))
            .arg(QCoreApplication::translate("Main window", "Borders (%1)").arg("xyz")); // TODO: Provide current dimension unit instead of "xyz"
        break;
    case WizardStepOverlapping:
        result = QCoreApplication::translate("Help",
            "Image tile overlapping is needed to have some tolerance for cutting off the unneeded borders from one side. Additionally, like the borders from the previous step, it gives more area for gluing together the final poster tiles.\n"
            "The '%1' defines the borders that are intended to be overlapped by the neighbor tiles. The borders on the opposite sides are intended to be cut (except on the outermost tiles).",
            "Wizard step 3. Place holders: %1 = 'Overlapping position' (will be automatically inserted)")
            .arg(QCoreApplication::translate("Main window", "Overlapping position"));
        break;
    case WizardStepPosterSize:
        result = QCoreApplication::translate("Help",
            "Define the final poster size, in one of the following three modes which can be selected by the corresponding radio buttons:\n"
            "'%1' You want to have a specific size of your poster.\n"
            "'%2' You want to use whole paper sheets and specify how many of them of them you want to use.\n"
            "'%3' Your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlarge the image by a certain factor.\n"
            "The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles.\n"
            "'%4' sets the alignment of the image on the total paper area of the poster. This is useful if you want to keep the unused paper.",
            "Wizard step 4. Place holders: %1 = 'Absolute size:', %2 = 'Size in pages:', %3 = 'Size in percent:', %4 = 'Image alignment' (will be automatically inserted)")
            .arg(QCoreApplication::translate("Main window", "Absolute size:"))
            .arg(QCoreApplication::translate("Main window", "Size in pages:"))
            .arg(QCoreApplication::translate("Main window", "Size in percent:"))
            .arg(QCoreApplication::translate("Main window", "Image alignment"));
        break;
    default:
        result = QCoreApplication::translate("Help",
            "Save the poster by clicking the save button and specifying a destination file name.\n"
            "Check or uncheck the '%1', if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved.",
            "Wizard step 5. Place holders: %1 = 'Open PDF after saving' (will be automatically inserted)")
            .arg(QCoreApplication::translate("Main window", "Open PDF after saving"));
    }
    return result;
}
