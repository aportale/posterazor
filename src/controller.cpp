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

#include "Controller.h"
#include "mainwindow.h"
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

const QLatin1String settingsKey_LaunchPDFApplication("launchPDFApplication");

Controller::Controller(PosteRazor *model, MainWindow *dialog, QObject *parent)
    : QObject(parent)
    , m_PosteRazor(model)
    , m_Dialog(dialog)
    , m_launchPDFApplication(true)
{
    connect(m_Dialog, SIGNAL(paperFormatChanged(const QString&)), SLOT(setPaperFormat(const QString&)));
    connect(m_Dialog, SIGNAL(paperOrientationChanged(PaperFormats::ePaperOrientations)), SLOT(setPaperOrientation(PaperFormats::ePaperOrientations)));
    connect(m_Dialog, SIGNAL(paperBorderTopChanged(double)), SLOT(setPaperBorderTop(double)));
    connect(m_Dialog, SIGNAL(paperBorderRightChanged(double)), SLOT(setPaperBorderRight(double)));
    connect(m_Dialog, SIGNAL(paperBorderBottomChanged(double)), SLOT(setPaperBorderBottom(double)));
    connect(m_Dialog, SIGNAL(paperBorderLeftChanged(double)), SLOT(setPaperBorderLeft(double)));
    connect(m_Dialog, SIGNAL(paperCustomWidthChanged(double)), SLOT(setCustomPaperWidth(double)));
    connect(m_Dialog, SIGNAL(paperCustomHeightChanged(double)), SLOT(setCustomPaperHeight(double)));

    connect(m_Dialog, SIGNAL(overlappingWidthChanged(double)), SLOT(setOverlappingWidth(double)));
    connect(m_Dialog, SIGNAL(overlappingHeightChanged(double)), SLOT(setOverlappingHeight(double)));
    connect(m_Dialog, SIGNAL(overlappingPositionChanged(Qt::Alignment)), SLOT(setOverlappingPosition(Qt::Alignment)));
    connect(m_Dialog, SIGNAL(posterWidthAbsoluteChanged(double)), SLOT(setPosterWidthAbsolute(double)));
    connect(m_Dialog, SIGNAL(posterHeightAbsoluteChanged(double)), SLOT(setPosterHeightAbsolute(double)));
    connect(m_Dialog, SIGNAL(posterWidthPagesChanged(double)), SLOT(setPosterWidthPages(double)));
    connect(m_Dialog, SIGNAL(posterHeightPagesChanged(double)), SLOT(setPosterHeightPages(double)));
    connect(m_Dialog, SIGNAL(posterSizePercentualChanged(double)), SLOT(setPosterSizePercentual(double)));

    connect(m_Dialog, SIGNAL(posterAlignmentChanged(Qt::Alignment)), SLOT(setPosterAlignment(Qt::Alignment)));

    connect(m_Dialog, SIGNAL(savePosterSignal()), SLOT(savePoster()));
    connect(m_Dialog, SIGNAL(loadImageSignal()), SLOT(loadInputImage()));
    connect(m_Dialog, SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), model, SLOT(paintOnCanvas(PaintCanvasInterface*, const QVariant&)));
    connect(model, SIGNAL(previewImageChanged(const unsigned char*, const QSize&)), dialog, SLOT(setPreviewImage(const unsigned char*, const QSize&)));

    updateDialog();
    setDialogPosterSizeMode();
}

void Controller::updateDialog()
{
    setDialogPaperOptions();
    setDialogPosterOptions();
    setDialogOverlappingOptions();
    setDialogImageInfoFields();
    setDialogSaveOptions();
    m_Dialog->setUnitOfLength(m_PosteRazor->getUnitOfLength());
    updatePreview();
}

void Controller::updatePreview()
{
    m_Dialog->updatePreview();
}

void Controller::setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
    m_PosteRazor->setUnitOfLength(unit);
    updateDialog();
}

void Controller::setPaperFormat(const QString &format)
{
    m_PosteRazor->setPaperFormat(format);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
    m_PosteRazor->setPaperOrientation(orientation);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setPaperBorderTop(double border)
{
    m_PosteRazor->setPaperBorderTop(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderRight(double border)
{
    m_PosteRazor->setPaperBorderRight(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderBottom(double border)
{
    m_PosteRazor->setPaperBorderBottom(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderLeft(double border)
{
    m_PosteRazor->setPaperBorderLeft(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setCustomPaperWidth(double width)
{
    m_PosteRazor->setCustomPaperWidth(width);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setCustomPaperHeight(double height)
{
    m_PosteRazor->setCustomPaperHeight(height);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setUseCustomPaperSize(bool useIt)
{
    m_PosteRazor->setUseCustomPaperSize(useIt);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setOverlappingWidth(double width)
{
    m_PosteRazor->setOverlappingWidth(width);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setOverlappingHeight(double height)
{
    m_PosteRazor->setOverlappingHeight(height);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setOverlappingPosition(Qt::Alignment position)
{
    m_PosteRazor->setOverlappingPosition(position);
    updatePreview();
}

void Controller::setPosterWidthAbsolute(double width)
{
    m_PosteRazor->setPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute, width);
    setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModeAbsolute, true);
}

void Controller::setPosterHeightAbsolute(double height)
{
    m_PosteRazor->setPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute, height);
    setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModeAbsolute, false);
}

void Controller::setPosterWidthPages(double width)
{
    m_PosteRazor->setPosterWidth(PosteRazorEnums::ePosterSizeModePages, width);
    setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModePages, true);
}

void Controller::setPosterHeightPages(double height)
{
    m_PosteRazor->setPosterHeight(PosteRazorEnums::ePosterSizeModePages, height);
    setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModePages, false);
}

void Controller::setPosterSizePercentual(double percent)
{
    m_PosteRazor->setPosterHeight(PosteRazorEnums::ePosterSizeModePercentual, percent);
    setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModePercentual, false);
}

void Controller::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
    m_PosteRazor->setPosterSizeMode(mode);
}

void Controller::setPosterAlignment(Qt::Alignment alignment)
{
    m_PosteRazor->setPosterAlignment(alignment);
    updatePreview();
}

void Controller::setPosterOutputFormat(ImageIOTypes::eImageFormats format)
{
    m_PosteRazor->setPosterOutputFormat(format);
}

void Controller::setLaunchPDFApplication(bool launch)
{
    m_launchPDFApplication = launch;
    setDialogSaveOptions();
}

void Controller::setDialogSaveOptions()
{
    m_Dialog->setLaunchPDFApplication(m_launchPDFApplication);
}

void Controller::setDialogPosterSizeMode()
{
    m_Dialog->setPosterSizeMode(m_PosteRazor->getPosterSizeMode());
}

void Controller::setDialogPosterOptions()
{
    setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModeNone, true);
    m_Dialog->setPosterAlignment(m_PosteRazor->getPosterAlignment());
    m_Dialog->setPosterSizeMode(m_PosteRazor->getPosterSizeMode());
}

void Controller::setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModes excludedMode, bool widthExcluded)
{
    if (excludedMode != PosteRazorEnums::ePosterSizeModeAbsolute || !widthExcluded)
        m_Dialog->setPosterWidthAbsolute(m_PosteRazor->getPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute));
    if (excludedMode != PosteRazorEnums::ePosterSizeModeAbsolute || widthExcluded)
        m_Dialog->setPosterHeightAbsolute(m_PosteRazor->getPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute));
    if (excludedMode != PosteRazorEnums::ePosterSizeModePages || !widthExcluded)
        m_Dialog->setPosterWidthPages(m_PosteRazor->getPosterWidth(PosteRazorEnums::ePosterSizeModePages));
    if (excludedMode != PosteRazorEnums::ePosterSizeModePages || widthExcluded)
        m_Dialog->setPosterHeightPages(m_PosteRazor->getPosterHeight(PosteRazorEnums::ePosterSizeModePages));
    if (excludedMode != PosteRazorEnums::ePosterSizeModePercentual)
        m_Dialog->setPosterSizePercentual(m_PosteRazor->getPosterWidth(PosteRazorEnums::ePosterSizeModePercentual));
    updatePreview();
}

void Controller::setDialogPaperOptions()
{
    setDialogPaperBorders();
    setDialogCustomPaperDimensions();
    m_Dialog->setUseCustomPaperSize(m_PosteRazor->getUseCustomPaperSize());
    m_Dialog->setPaperFormat(m_PosteRazor->getPaperFormat());
    m_Dialog->setPaperOrientation(m_PosteRazor->getPaperOrientation());
}

void Controller::setDialogPaperBorders()
{
    m_Dialog->setPaperBorderTop(m_PosteRazor->getPaperBorderTop());
    m_Dialog->setPaperBorderRight(m_PosteRazor->getPaperBorderRight());
    m_Dialog->setPaperBorderBottom(m_PosteRazor->getPaperBorderBottom());
    m_Dialog->setPaperBorderLeft(m_PosteRazor->getPaperBorderLeft());
}

void Controller::setDialogCustomPaperDimensions()
{
    m_Dialog->setCustomPaperWidth(m_PosteRazor->getCustomPaperWidth());
    m_Dialog->setCustomPaperHeight(m_PosteRazor->getCustomPaperHeight());
}

void Controller::setDialogImageInfoFields()
{
    if (m_PosteRazor->getIsImageLoaded()) {
        m_Dialog->updateImageInfoFields (
            m_PosteRazor->getInputImageWidthPixels(),
            m_PosteRazor->getInputImageHeightPixels(),
            m_PosteRazor->getInputImageWidth(),
            m_PosteRazor->getInputImageHeight(),
            m_PosteRazor->getUnitOfLength(),
            m_PosteRazor->getInputImageVerticalDpi(),
            m_PosteRazor->getInputImageHorizontalDpi(),
            m_PosteRazor->getInputImageColorType(),
            m_PosteRazor->getInputImageBitsPerPixel()
        );
    }
}

void Controller::setDialogOverlappingDimensions()
{
    m_Dialog->setOverlappingWidth(m_PosteRazor->getOverlappingWidth());
    m_Dialog->setOverlappingHeight(m_PosteRazor->getOverlappingHeight());
}

void Controller::setDialogOverlappingOptions()
{
    setDialogOverlappingDimensions();
    m_Dialog->setOverlappingPosition(m_PosteRazor->getOverlappingPosition());
}

bool Controller::readSettings(const QSettings *settings)
{
    const bool result = m_PosteRazor->readSettings(settings);
    m_launchPDFApplication = settings->value(settingsKey_LaunchPDFApplication, m_launchPDFApplication).toBool();

    if (result)
        updateDialog();

    return result;
}

bool Controller::writeSettings(QSettings *settings) const
{
    settings->setValue(settingsKey_LaunchPDFApplication, m_launchPDFApplication);
    return m_PosteRazor->writeSettings(settings);
}

void Controller::loadInputImage()
{
    QStringList filters;
    QStringList allExtensions;

    for (int formatIndex = 0; formatIndex < ImageIOTypes::getInputImageFormatsCount(); formatIndex++) {
        int extensionsCount = ImageIOTypes::getFileExtensionsCount(formatIndex);

        QStringList filterExtensions;
        for (int extensionIndex = 0; extensionIndex < extensionsCount; extensionIndex++) {
            filterExtensions << "*." + QString(ImageIOTypes::getFileExtensionForFormat(extensionIndex, formatIndex));
        }
        allExtensions << filterExtensions;

        filters << QString(ImageIOTypes::getInputImageFormat(formatIndex)) + " (" + filterExtensions.join(" ") + ")";
    }
    filters.prepend(QCoreApplication::translate("PosteRazorDialog", "All image formats") + " (" +  allExtensions.join(" ") + ")"); 

    static const QString loadPathSettingsKey("loadPath");
    QSettings loadPathSettings;

    QString loadFileName = QFileDialog::getOpenFileName (
        NULL,
        QCoreApplication::translate("PosteRazorDialog", "Load an input image"),
        loadPathSettings.value(loadPathSettingsKey, ".").toString(),
        filters.join(";;")
    );

    if (!loadFileName.isEmpty()) {
        bool successful = loadInputImage(loadFileName);
        if (successful)
            loadPathSettings.setValue(loadPathSettingsKey, QFileInfo(loadFileName).absolutePath());
    }
}

bool Controller::loadInputImage(const QString &fileName)
{
    QString loadErrorMessage;
    const bool successful = loadInputImage(fileName, loadErrorMessage);
    if (!successful) {
        const QString errorMessage = QCoreApplication::translate("PosteRazorDialog", "The Image '%1' could not be loaded.\n")
            .arg(QDir::convertSeparators(fileName));
        QMessageBox::critical(NULL, QCoreApplication::translate("PosteRazorDialog", "Loading Error"), errorMessage);
    }
    return successful;
}

bool Controller::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    const bool result = m_PosteRazor->loadInputImage(imageFileName, errorMessage);
    if (result) {
        updateDialog();
        m_Dialog->showImageFileName(imageFileName);
    }
    return result;
}

int Controller::savePoster(const QString &fileName) const
{
    const int result = m_PosteRazor->savePoster(fileName);
    if (result == 0 && m_launchPDFApplication)
        m_Dialog->launchPdfApplication(fileName);
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
            NULL,
            QCoreApplication::translate("PosteRazorDialog", "Choose a filename to save under"),
            saveFileName,
            QLatin1String("Portable Document format (*.pdf)"),
            NULL,
            QFileDialog::DontConfirmOverwrite
        );

        if (!saveFileName.isEmpty()) {
            if (QFileInfo(saveFileName).suffix().toLower() != QLatin1String("pdf"))
                saveFileName.append(".pdf");

            fileExistsAskUserForOverwrite = QFileInfo(saveFileName).exists();

            if (!fileExistsAskUserForOverwrite
                || QMessageBox::Yes == (QMessageBox::question(NULL, "", QCoreApplication::translate("PosteRazorDialog", "The file '%1' already exists.\nDo you want to overwrite it?").arg(QDir::convertSeparators(saveFileName)), QMessageBox::Yes, QMessageBox::No))
                ) {
                int result = savePoster(saveFileName.toAscii());
                if (result != 0)
                    QMessageBox::critical(NULL, "", QCoreApplication::translate("PosteRazorDialog", "The File \"%1\" could not be saved.").arg(saveFileName), QMessageBox::Ok, QMessageBox::NoButton);
                else
                    savePathSettings.setValue(savePathSettingsKey, QFileInfo(saveFileName).absolutePath());
                fileExistsAskUserForOverwrite = false;
            }
        } else {
            break;
        }
    } while (fileExistsAskUserForOverwrite);
}
