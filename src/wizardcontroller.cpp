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
#include <QMetaObject>
#include <QMetaEnum>
#include <QDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QTextBrowser>

static const QMetaEnum wizardStepsEnum =
    WizardController::staticMetaObject.enumerator(WizardController::staticMetaObject.indexOfEnumerator("WizardSteps"));

const int WizardController::m_wizardStepsCount = wizardStepsEnum.keyCount();

static QString cleanString(const QString &dirtyString)
{
    QString result = dirtyString;
    result.replace(QRegExp("[:&]"), "");
    result.replace('\n', ' ');
    return result.trimmed();
}

static QString newlineToParagraph(const QString &nlText)
{
    QString result = nlText;
    result.replace('\n', "</p><p>");
    return "<p>" + result + "</p>";
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
    connect(wizardDialog, SIGNAL(manualSignal()), SLOT(showManual()));
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
    const QString title = cleanString(QCoreApplication::translate("Help", "&Manual"));
    QString manual = QString(QLatin1String("<h1>%1</h1>")).arg(title);
    manual.append(newlineToParagraph(QCoreApplication::translate("Help",
        "PosteRazor has its user interface organized in a 'Wizard' fashion. All settings for the poster creation can be done in %1 steps.\n"
        "The <b>%2</b> and <b>%3</b> buttons navigate through these steps. The <b>?</b> button opens a help window with an explanation of the current step.\n"
        "All entries and choices are remembered until the next usage of the PosteRazor.",
        "Manual preface. Place holders: %1 = Number of wizard steps, %2 = 'Back', %3 = 'Next' (will be automatically inserted)")
        .arg(m_wizardStepsCount)
        .arg(QCoreApplication::translate("Main window", "Back"))
        .arg(QCoreApplication::translate("Main window", "Next"))));
    for (int i = 0; i < wizardStepsEnum.keyCount(); i++) {
        const WizardSteps step = (WizardSteps)wizardStepsEnum.value(i);
        manual.append(QString(QLatin1String("<h2>%1</h2>")).arg(stepTitle(step)));
        manual.append(stepHelp(step));
    }
    QDialog *dialog = new QDialog;
    dialog->setModal(true);
    dialog->setWindowTitle(title);
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->setWindowFlags(dialog->windowFlags() ^ Qt::WindowContextHelpButtonHint);
    dialog->resize(500, 400);
    dialog->setLayout(new QVBoxLayout);
    QTextBrowser *browser = new QTextBrowser;
    browser->setHtml(manual);
    dialog->layout()->addWidget(browser);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted ()), dialog, SLOT(accept()));
    dialog->layout()->addWidget(buttonBox);
    dialog->show();
}

void WizardController::showHelpForCurrentStep()
{
    QString helpText = QString("<h2>%1</h2>").arg(stepTitle(m_wizardStep)) + stepHelp(m_wizardStep);
    QMessageBox box;
    box.setWindowTitle(cleanString(stepXofYString(m_wizardStep)));
#if defined(Q_WS_MAC)
    // Hack. Since QMessageBoxPrivate sets the whole font to bold on Q_WS_MAC (no matter which style),
    // we put emphasis on the key words by setting them to italic and into single quotes.
    helpText.replace("<b>", "<i>'");
    helpText.replace("</b>", "'</i>");
#endif
    box.setText(helpText);
	box.setTextFormat(Qt::RichText);
    box.addButton(QMessageBox::Ok);
    box.exec();
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
    emit wizardStepDescriptionChanged(stepXofYString(m_wizardStep), stepTitle(m_wizardStep));
}

QString WizardController::stepXofYString(WizardSteps step)
{
    return QCoreApplication::translate("Help", "Step %1 of %2:").arg((int)step + 1).arg((int)m_wizardStepsCount);
}

QString WizardController::stepTitle(WizardSteps step)
{
    QString title;
    title.append(
        step == WizardStepInputImage?  QCoreApplication::translate("Help", "Load an input image")
        :step == WizardStepPaperSize?  QCoreApplication::translate("Help", "Printer paper format")
        :step == WizardStepOverlapping?QCoreApplication::translate("Help", "Image tile overlapping")
        :step == WizardStepPosterSize? QCoreApplication::translate("Help", "Final poster size")
        :                              QCoreApplication::translate("Help", "Save the Poster"));
    return title;
}

QString WizardController::stepHelp(WizardSteps step)
{
    QString result;
    switch (step) {
    case WizardStepInputImage:
        result = QCoreApplication::translate("Help",
            "Load an image by clicking the button with the open icon and selecting an image file, or by drag & dropping an image file on the PosteRazor. The drag & drop also works during the other steps.\n"
            "After loading the image, the most important informations are listed in the <b>%1</b> fields.",
            "Wizard step 1. Place holders: %1 = 'Image informations' (will be automatically inserted)")
            .arg(cleanString(QCoreApplication::translate("Main window", "Image Informations")));
        break;
    case WizardStepPaperSize:
        result = QCoreApplication::translate("Help",
            "Define the paper sheet size that you use in your printer.\n"
            "A standard paper sheet size can be selected from the <b>%1</b> chooser, along with the desired paper sheet orientation.\n"
            "Alternatively, a custom paper sheet size can be defined in the <b>%2</b> tab.\n"
            "Paper borders are defined in the <b>%3</b> fields. Even if your printer does need no (or small) paper borders, some border might be needed to have enough area for gluing the final poster tiles together.",
            "Wizard step 2. Place holders: %1 = 'Format:', %2 = 'Custom', %3 = 'Borders' (will be automatically inserted)")
            .arg(cleanString(QCoreApplication::translate("Main window", "Format:")))
            .arg(cleanString(QCoreApplication::translate("Main window", "Custom")))
            .arg(cleanString(QCoreApplication::translate("Main window", "Borders")));
        break;
    case WizardStepOverlapping:
        result = QCoreApplication::translate("Help",
            "Image tile overlapping is needed to have some tolerance for cutting off the unneeded borders from one side. Additionally, like the borders from the previous step, it gives more area for gluing together the final poster tiles.\n"
            "The <b>%1</b> defines the borders that are intended to be overlapped by the neighbor tiles. The borders on the opposite sides are intended to be cut (except on the outermost tiles).",
            "Wizard step 3. Place holders: %1 = 'Overlapping position' (will be automatically inserted)")
            .arg(cleanString(QCoreApplication::translate("Main window", "Overlapping position")));
        break;
    case WizardStepPosterSize:
    {
        const QString definitionTemplate(QLatin1String("<dt><b>%1</b></dt><dd>%2</dd>"));
        result = QCoreApplication::translate("Help",
            "Define the final poster size, in one of the following three modes which can be selected by the corresponding radio buttons:",
            "Wizard step 4. Start of the description.");
        result.append("<dl>");
        result.append(definitionTemplate
            .arg(cleanString(QCoreApplication::translate("Main window", "Absolute size:")))
            .arg(QCoreApplication::translate("Help",
                "You want to have a specific size of your poster.",
                "Wizard step 4. Description for 'absolute size'")));
        result.append(definitionTemplate
            .arg(cleanString(QCoreApplication::translate("Main window", "Size in pages:")))
            .arg(QCoreApplication::translate("Help",
                "You want to use whole paper sheets and specify how many of them of them you want to use.",
                "Wizard step 4. Description for 'size in pages'")));
        result.append(definitionTemplate
            .arg(cleanString(QCoreApplication::translate("Main window", "Size in percent:")))
            .arg(QCoreApplication::translate("Help",
                "Your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlarge the image by a certain factor.",
                "Wizard step 4. Description for 'size in percent'")));
        result.append("</dl>");
        result.append(QCoreApplication::translate("Help",
            "The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles.\n"
            "<b>%1</b> sets the alignment of the image on the total paper area of the poster. This is useful if you want to keep the unused paper.",
            "Wizard step 4. End of the description. Place holders: %1 = 'Image alignment' (will be automatically inserted)")
            .arg(cleanString(QCoreApplication::translate("Main window", "Image alignment"))));
        break;
    }
    default:
        result = QCoreApplication::translate("Help",
            "Save the poster by clicking the save button and specifying a destination file name.\n"
            "Check or uncheck the <b>%1</b>, if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved.",
            "Wizard step 5. Place holders: %1 = 'Open PDF after saving' (will be automatically inserted)")
            .arg(cleanString(QCoreApplication::translate("Main window", "Open PDF after saving")));
    }
    return newlineToParagraph(result);
}
