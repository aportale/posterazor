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

#include "controller.h"
#include "mainwindow.h"
#include "wizardcontroller.h"
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QTranslator>

const QLatin1String settingsKey_LaunchPDFApplication("LaunchPDFApplication");
const QLatin1String settingsKey_TranslationName("TranslationName");

Controller::Controller(PosteRazorCore *posteRazorCore, MainWindow *mainWindow, QObject *parent)
    : QObject(parent)
    , m_posteRazorCore(posteRazorCore)
    , m_mainWindow(mainWindow)
    , m_launchPDFApplication(true)
{
    connect(m_mainWindow, SIGNAL(paperFormatChanged(const QString&)), SLOT(setPaperFormat(const QString&)));
    connect(m_mainWindow, SIGNAL(paperOrientationChanged(QPrinter::Orientation)), SLOT(setPaperOrientation(QPrinter::Orientation)));
    connect(m_mainWindow, SIGNAL(paperBorderTopChanged(double)), SLOT(setPaperBorderTop(double)));
    connect(m_mainWindow, SIGNAL(paperBorderRightChanged(double)), SLOT(setPaperBorderRight(double)));
    connect(m_mainWindow, SIGNAL(paperBorderBottomChanged(double)), SLOT(setPaperBorderBottom(double)));
    connect(m_mainWindow, SIGNAL(paperBorderLeftChanged(double)), SLOT(setPaperBorderLeft(double)));
    connect(m_mainWindow, SIGNAL(useCustomPaperSizeChanged(bool)), SLOT(setUseCustomPaperSize(bool)));
    connect(m_mainWindow, SIGNAL(paperCustomWidthChanged(double)), SLOT(setCustomPaperWidth(double)));
    connect(m_mainWindow, SIGNAL(paperCustomHeightChanged(double)), SLOT(setCustomPaperHeight(double)));
    connect(m_mainWindow, SIGNAL(overlappingWidthChanged(double)), SLOT(setOverlappingWidth(double)));
    connect(m_mainWindow, SIGNAL(overlappingHeightChanged(double)), SLOT(setOverlappingHeight(double)));
    connect(m_mainWindow, SIGNAL(overlappingPositionChanged(Qt::Alignment)), SLOT(setOverlappingPosition(Qt::Alignment)));
    connect(m_mainWindow, SIGNAL(posterWidthAbsoluteChanged(double)), SLOT(setPosterWidthAbsolute(double)));
    connect(m_mainWindow, SIGNAL(posterHeightAbsoluteChanged(double)), SLOT(setPosterHeightAbsolute(double)));
    connect(m_mainWindow, SIGNAL(posterWidthPagesChanged(double)), SLOT(setPosterWidthPages(double)));
    connect(m_mainWindow, SIGNAL(posterHeightPagesChanged(double)), SLOT(setPosterHeightPages(double)));
    connect(m_mainWindow, SIGNAL(posterSizePercentualChanged(double)), SLOT(setPosterSizePercentual(double)));
    connect(m_mainWindow, SIGNAL(posterAlignmentChanged(Qt::Alignment)), SLOT(setPosterAlignment(Qt::Alignment)));
    connect(m_mainWindow, SIGNAL(savePosterSignal()), SLOT(savePoster()));
    connect(m_mainWindow, SIGNAL(launchPDFApplicationChanged(bool)), SLOT(setLaunchPDFApplication(bool)));
    connect(m_mainWindow, SIGNAL(loadImageSignal()), SLOT(loadInputImage()));
    connect(m_mainWindow, SIGNAL(translationChanged(const QString&)), SLOT(loadTranslation(const QString&)));
    connect(m_mainWindow, SIGNAL(unitOfLengthChanged(const QString&)), SLOT(setUnitOfLength(const QString&)));
    connect(m_mainWindow, SIGNAL(openPosteRazorWebsiteSignal()), SLOT(openPosteRazorWebsite()));
    connect(m_mainWindow, SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), m_posteRazorCore, SLOT(paintOnCanvas(PaintCanvasInterface*, const QVariant&)));
    connect(m_posteRazorCore, SIGNAL(previewImageChanged(const QImage&)), m_mainWindow, SLOT(setPreviewImage(const QImage&)));

    m_wizardController = new WizardController(m_mainWindow, this);

    if (!m_posteRazorCore->imageIOLibraryAboutText().isEmpty()) {
        QAction *aboutAction = new QAction(m_mainWindow);
        aboutAction->setText(QLatin1String("A&bout ") + m_posteRazorCore->imageIOLibraryName());
        connect (aboutAction, SIGNAL(triggered()), SLOT(showExtraAboutDialog()));
        m_mainWindow->addAboutDialogAction(aboutAction);
    }

    updateDialog();
    setDialogPosterSizeMode();

    m_translator = new QTranslator(this);
    loadTranslation(QString());
}

void Controller::updateDialog()
{
    const QString unitOfLength = Types::unitsOfLength().value(m_posteRazorCore->unitOfLength()).first;
    m_mainWindow->setCurrentUnitOfLength(unitOfLength);
    setDialogPaperOptions();
    setDialogPosterOptions();
    setDialogOverlappingOptions();
    setDialogImageInfoFields();
    setDialogSaveOptions();
    updatePreview();
}

void Controller::updatePreview()
{
    m_mainWindow->updatePreview();
}

void Controller::setUnitOfLength(Types::UnitsOfLength unit)
{
    m_posteRazorCore->setUnitOfLength(unit);
    updateDialog();
}

void Controller::setPaperFormat(const QString &format)
{
    m_posteRazorCore->setPaperFormat(format);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setPaperOrientation(QPrinter::Orientation orientation)
{
    m_posteRazorCore->setPaperOrientation(orientation);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setPaperBorderTop(double border)
{
    m_posteRazorCore->setPaperBorderTop(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderRight(double border)
{
    m_posteRazorCore->setPaperBorderRight(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderBottom(double border)
{
    m_posteRazorCore->setPaperBorderBottom(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderLeft(double border)
{
    m_posteRazorCore->setPaperBorderLeft(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setCustomPaperWidth(double width)
{
    m_posteRazorCore->setCustomPaperWidth(width);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setCustomPaperHeight(double height)
{
    m_posteRazorCore->setCustomPaperHeight(height);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setUseCustomPaperSize(bool useIt)
{
    m_posteRazorCore->setUseCustomPaperSize(useIt);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setOverlappingWidth(double width)
{
    m_posteRazorCore->setOverlappingWidth(width);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setOverlappingHeight(double height)
{
    m_posteRazorCore->setOverlappingHeight(height);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setOverlappingPosition(Qt::Alignment position)
{
    m_posteRazorCore->setOverlappingPosition(position);
    updatePreview();
}

void Controller::setPosterWidthAbsolute(double width)
{
    m_posteRazorCore->setPosterWidth(Types::PosterSizeModeAbsolute, width);
    setDialogPosterDimensions(Types::PosterSizeModeAbsolute, true);
}

void Controller::setPosterHeightAbsolute(double height)
{
    m_posteRazorCore->setPosterHeight(Types::PosterSizeModeAbsolute, height);
    setDialogPosterDimensions(Types::PosterSizeModeAbsolute, false);
}

void Controller::setPosterWidthPages(double width)
{
    m_posteRazorCore->setPosterWidth(Types::PosterSizeModePages, width);
    setDialogPosterDimensions(Types::PosterSizeModePages, true);
}

void Controller::setPosterHeightPages(double height)
{
    m_posteRazorCore->setPosterHeight(Types::PosterSizeModePages, height);
    setDialogPosterDimensions(Types::PosterSizeModePages, false);
}

void Controller::setPosterSizePercentual(double percent)
{
    m_posteRazorCore->setPosterHeight(Types::PosterSizeModePercentual, percent);
    setDialogPosterDimensions(Types::PosterSizeModePercentual, false);
}

void Controller::setPosterSizeMode(Types::PosterSizeModes mode)
{
    m_posteRazorCore->setPosterSizeMode(mode);
}

void Controller::setPosterAlignment(Qt::Alignment alignment)
{
    m_posteRazorCore->setPosterAlignment(alignment);
    updatePreview();
}

void Controller::setLaunchPDFApplication(bool launch)
{
    m_launchPDFApplication = launch;
    setDialogSaveOptions();
}

void Controller::setDialogSaveOptions()
{
    m_mainWindow->setLaunchPDFApplication(m_launchPDFApplication);
}

void Controller::setDialogPosterSizeMode()
{
    m_mainWindow->setPosterSizeMode(m_posteRazorCore->posterSizeMode());
}

void Controller::setDialogPosterOptions()
{
    setDialogPosterDimensions(Types::PosterSizeModeNone, true);
    m_mainWindow->setPosterAlignment(m_posteRazorCore->posterAlignment());
    m_mainWindow->setPosterSizeMode(m_posteRazorCore->posterSizeMode());
}

void Controller::setDialogPosterDimensions(Types::PosterSizeModes excludedMode, bool widthExcluded)
{
    const QSizeF posterSizeAbsolute = m_posteRazorCore->posterSize(Types::PosterSizeModeAbsolute);
    const QSizeF posterSizePages = m_posteRazorCore->posterSize(Types::PosterSizeModePages);
    const QSizeF posterSizePercentual = m_posteRazorCore->posterSize(Types::PosterSizeModePercentual);
    if (excludedMode != Types::PosterSizeModeAbsolute || !widthExcluded)
        m_mainWindow->setPosterWidthAbsolute(posterSizeAbsolute.width());
    if (excludedMode != Types::PosterSizeModeAbsolute || widthExcluded)
        m_mainWindow->setPosterHeightAbsolute(posterSizeAbsolute.height());
    if (excludedMode != Types::PosterSizeModePages || !widthExcluded)
        m_mainWindow->setPosterWidthPages(posterSizePages.width());
    if (excludedMode != Types::PosterSizeModePages || widthExcluded)
        m_mainWindow->setPosterHeightPages(posterSizePages.height());
    if (excludedMode != Types::PosterSizeModePercentual)
        m_mainWindow->setPosterSizePercentual(posterSizePercentual.width());
    updatePreview();
}

void Controller::setDialogPaperOptions()
{
    setDialogPaperBorders();
    setDialogCustomPaperDimensions();
    m_mainWindow->setUseCustomPaperSize(m_posteRazorCore->usesCustomPaperSize());
    m_mainWindow->setPaperFormat(m_posteRazorCore->paperFormat());
    m_mainWindow->setPaperOrientation(m_posteRazorCore->paperOrientation());
}

void Controller::setDialogPaperBorders()
{
    m_mainWindow->setPaperBorderTop(m_posteRazorCore->paperBorderTop());
    m_mainWindow->setPaperBorderRight(m_posteRazorCore->paperBorderRight());
    m_mainWindow->setPaperBorderBottom(m_posteRazorCore->paperBorderBottom());
    m_mainWindow->setPaperBorderLeft(m_posteRazorCore->paperBorderLeft());
}

void Controller::setDialogCustomPaperDimensions()
{
    m_mainWindow->setCustomPaperSize(m_posteRazorCore->customPaperSize());
}

void Controller::setDialogImageInfoFields()
{
    if (m_posteRazorCore->isImageLoaded()) {
        m_mainWindow->updateImageInfoFields (
            m_posteRazorCore->inputImageSizePixels(),
            m_posteRazorCore->inputImageSize(),
            m_posteRazorCore->inputImageVerticalDpi(),
            m_posteRazorCore->inputImageHorizontalDpi(),
            m_posteRazorCore->inputImageColorType(),
            m_posteRazorCore->inputImageBitsPerPixel()
        );
    }
}

void Controller::setDialogOverlappingDimensions()
{
    m_mainWindow->setOverlappingWidth(m_posteRazorCore->overlappingWidth());
    m_mainWindow->setOverlappingHeight(m_posteRazorCore->overlappingHeight());
}

void Controller::setDialogOverlappingOptions()
{
    setDialogOverlappingDimensions();
    m_mainWindow->setOverlappingPosition(m_posteRazorCore->overlappingPosition());
}

void Controller::readSettings(const QSettings *settings)
{
    m_posteRazorCore->readSettings(settings);
    m_launchPDFApplication = settings->value(settingsKey_LaunchPDFApplication, m_launchPDFApplication).toBool();
    m_translationName = settings->value(settingsKey_TranslationName, m_translationName).toString();
    loadTranslation(m_translationName);
    updateDialog();
}

void Controller::writeSettings(QSettings *settings) const
{
    settings->setValue(settingsKey_LaunchPDFApplication, m_launchPDFApplication);
    if (!m_translationName.isEmpty())
        settings->setValue(settingsKey_TranslationName, m_translationName);
    m_posteRazorCore->writeSettings(settings);
}

void Controller::loadInputImage()
{
    QStringList allFilters;
    QStringList allWildcards;

    const QVector<QPair<QStringList, QString> > &formats = m_posteRazorCore->imageFormats();
    for (int i = 0; i < formats.count(); i++) {
        QStringList formatWildcards;
        foreach (const QString &extension, formats.at(i).first)
            formatWildcards << "*." + extension;
        allWildcards << formatWildcards;
        QString formatName = formats.at(i).second;
        // Some Open File dialogs (at least OSX) ar irritated if there are brackes in the file type name
        formatName.replace('(', '[');
        formatName.replace(')', ']');
        allFilters << formatName + " (" +  formatWildcards.join(" ") + ")";
    }
    allFilters.prepend(QCoreApplication::translate("Main window", "All image formats") + " (" +  allWildcards.join(" ") + ")");

    static const QString loadPathSettingsKey("loadPath");
    QSettings loadPathSettings;

    QString loadFileName = QFileDialog::getOpenFileName (
        m_mainWindow,
        QCoreApplication::translate("Main window", "Load an input image"),
        loadPathSettings.value(loadPathSettingsKey, ".").toString(),
        allFilters.join(";;")
    );

    if (!loadFileName.isEmpty()) {
        const bool successful = loadInputImage(loadFileName);
        if (successful)
            loadPathSettings.setValue(loadPathSettingsKey, QFileInfo(loadFileName).absolutePath());
    }
}

bool Controller::loadInputImage(const QString &fileName)
{
    QString loadErrorMessage;
    const bool successful = loadInputImage(fileName, loadErrorMessage);
    if (!successful)
        QMessageBox::critical(m_mainWindow, "", QCoreApplication::translate("Main window", "The image '%1' could not be loaded.")
            .arg(QFileInfo(fileName).fileName()));
    return successful;
}

bool Controller::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    const bool result = m_posteRazorCore->loadInputImage(imageFileName, errorMessage);
    if (result) {
        updateDialog();
        m_mainWindow->showImageFileName(imageFileName);
    }
    return result;
}

int Controller::savePoster(const QString &fileName) const
{
    const int result = m_posteRazorCore->savePoster(fileName);
    if (result == 0 && m_launchPDFApplication)
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    return result;
}

void Controller::savePoster() const
{
    static const QLatin1String savePathSettingsKey("savePath");
    QSettings savePathSettings;

    QString saveFileName = savePathSettings.value(savePathSettingsKey, ".").toString();
    bool fileExistsAskUserForOverwrite = false;

    do {
        saveFileName = QFileDialog::getSaveFileName(
            m_mainWindow,
            QCoreApplication::translate("Main window", "Save the poster"),
            saveFileName,
            QLatin1String("Portable Document format (*.pdf)"),
            NULL,
            QFileDialog::DontConfirmOverwrite
        );

        if (!saveFileName.isEmpty()) {
            const QFileInfo saveFileInfo(saveFileName);
            if (saveFileInfo.suffix().toLower() != QLatin1String("pdf"))
                saveFileName.append(".pdf");

            fileExistsAskUserForOverwrite = QFileInfo(saveFileName).exists();

            if (!fileExistsAskUserForOverwrite
                || QMessageBox::Yes == (QMessageBox::question(m_mainWindow, "", QCoreApplication::translate("Main window", "The file '%1' already exists.\nDo you want to overwrite it?").arg(saveFileInfo.fileName()), QMessageBox::Yes, QMessageBox::No))
                ) {
                int result = savePoster(saveFileName.toAscii());
                if (result != 0)
                    QMessageBox::critical(m_mainWindow, "", QCoreApplication::translate("Main window", "The file '%1' could not be saved.").arg(saveFileInfo.fileName()), QMessageBox::Ok, QMessageBox::NoButton);
                else
                    savePathSettings.setValue(savePathSettingsKey, QFileInfo(saveFileName).absolutePath());
                fileExistsAskUserForOverwrite = false;
            }
        } else {
            break;
        }
    } while (fileExistsAskUserForOverwrite);
}

void Controller::loadTranslation(const QString &localeName)
{
    const QString saneLocaleName = localeName.isEmpty()?QLocale::system().name():localeName;
    const QString translationFileName(":/Translations/" + saneLocaleName);
    if (m_translator->load(translationFileName)) {
        QCoreApplication::removeTranslator(m_translator);
        QCoreApplication::installTranslator(m_translator);
        m_mainWindow->setCurrentTranslation(saneLocaleName);
        if (!localeName.isEmpty())
            m_translationName = localeName;
        m_wizardController->updateDialogWizardStepDescription();
    }
}

void Controller::setUnitOfLength(const QString &unit)
{
    m_posteRazorCore->setUnitOfLength(Types::unitOfLenthFromString(unit));
    updateDialog();
}

void Controller::openPosteRazorWebsite()
{
    QDesktopServices::openUrl(QCoreApplication::translate("Help", "http://posterazor.sourceforge.net/", "Only translate, if the website has this language."));
}

void Controller::showExtraAboutDialog()
{
    const QString title = QLatin1String("About ") + m_posteRazorCore->imageIOLibraryName();
    QMessageBox::about(
        m_mainWindow, title,
        QString(QLatin1String("<h3>%1</h3>%2")) // QMessageBox::aboutQt() also uses <h3>
            .arg(title)
            .arg(Types::newlineToParagraph(m_posteRazorCore->imageIOLibraryAboutText()))
    );
}
