/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2018 by Alessandro Portale
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
#include "posterazorcore.h"
#include "wizardcontroller.h"

#include <QAction>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QFileDialog>
#include <QLocale>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>
#include <QTranslator>
#include <QUrl>

#ifdef Q_OS_WASM
#include <emscripten.h>
#include <emscripten/html5.h>
#include <QBuffer>
#endif // Q_OS_WASM

const QLatin1String settingsKey_LaunchPDFApplication("LaunchPDFApplication");
const QLatin1String settingsKey_TranslationName("TranslationName");
const QLatin1String settingsKey_ImageLoadPath("ImageLoadPath");
const QLatin1String settingsKey_PosterSavePath("PosterSavePath");

Controller::Controller(PosteRazorCore *posteRazorCore, QWidget *view, QObject *parent)
    : QObject(parent)
    , m_posteRazorCore(posteRazorCore)
    , m_view(view)
{
    connect(m_view, SIGNAL(paperFormatChanged(const QString&)), SLOT(setPaperFormat(const QString&)));
    connect(m_view, SIGNAL(paperOrientationChanged(QPageLayout::Orientation)), SLOT(setPaperOrientation(QPageLayout::Orientation)));
    connect(m_view, SIGNAL(paperBorderTopChanged(qreal)), SLOT(setPaperBorderTop(qreal)));
    connect(m_view, SIGNAL(paperBorderRightChanged(qreal)), SLOT(setPaperBorderRight(qreal)));
    connect(m_view, SIGNAL(paperBorderBottomChanged(qreal)), SLOT(setPaperBorderBottom(qreal)));
    connect(m_view, SIGNAL(paperBorderLeftChanged(qreal)), SLOT(setPaperBorderLeft(qreal)));
    connect(m_view, SIGNAL(useCustomPaperSizeChanged(bool)), SLOT(setUseCustomPaperSize(bool)));
    connect(m_view, SIGNAL(paperCustomWidthChanged(qreal)), SLOT(setCustomPaperWidth(qreal)));
    connect(m_view, SIGNAL(paperCustomHeightChanged(qreal)), SLOT(setCustomPaperHeight(qreal)));
    connect(m_view, SIGNAL(overlappingWidthChanged(qreal)), SLOT(setOverlappingWidth(qreal)));
    connect(m_view, SIGNAL(overlappingHeightChanged(qreal)), SLOT(setOverlappingHeight(qreal)));
    connect(m_view, SIGNAL(overlappingPositionChanged(Qt::Alignment)), SLOT(setOverlappingPosition(Qt::Alignment)));
    connect(m_view, SIGNAL(posterWidthAbsoluteChanged(qreal)), SLOT(setPosterWidthAbsolute(qreal)));
    connect(m_view, SIGNAL(posterHeightAbsoluteChanged(qreal)), SLOT(setPosterHeightAbsolute(qreal)));
    connect(m_view, SIGNAL(posterWidthPagesChanged(qreal)), SLOT(setPosterWidthPages(qreal)));
    connect(m_view, SIGNAL(posterHeightPagesChanged(qreal)), SLOT(setPosterHeightPages(qreal)));
    connect(m_view, SIGNAL(posterSizePercentualChanged(qreal)), SLOT(setPosterSizePercentual(qreal)));
    connect(m_view, SIGNAL(posterAlignmentChanged(Qt::Alignment)), SLOT(setPosterAlignment(Qt::Alignment)));
    connect(m_view, SIGNAL(savePosterSignal()), SLOT(savePoster()));
    connect(m_view, SIGNAL(launchPDFApplicationChanged(bool)), SLOT(setLaunchPDFApplication(bool)));
    connect(m_view, SIGNAL(loadImageSignal()), SLOT(loadInputImage()));
    connect(m_view, SIGNAL(loadImageSignal(const QString&)), SLOT(loadInputImage(const QString&)));
    connect(m_view, SIGNAL(translationChanged(const QString&)), SLOT(loadTranslation(const QString&)));
    connect(m_view, SIGNAL(unitOfLengthChanged(const QString&)), SLOT(setUnitOfLength(const QString&)));
    connect(m_view, SIGNAL(openPosteRazorWebsiteSignal()), SLOT(openPosteRazorWebsite()));
    connect(m_view, SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), m_posteRazorCore, SLOT(paintOnCanvas(PaintCanvasInterface*, const QVariant&)));
    connect(m_view, SIGNAL(imageSuffixSupportedSignal(const QString &, bool &)), SLOT(imageSuffixSupported(const QString &, bool &)));
    connect(m_posteRazorCore, SIGNAL(previewImageChanged(const QImage&)), m_view, SLOT(setPreviewImage(const QImage&)));

    static const struct {
        const char *signal;
        const char *slot;
    } signalsToViewSlotsConnections[] = {
        {SIGNAL(setPaperFormatSignal(const QString&)),              SLOT(setPaperFormat(const QString&))},
        {SIGNAL(setPaperFormatSignal(const QString&)),              SLOT(setPaperFormat(const QString&))},
        {SIGNAL(setPaperOrientationSignal(QPageLayout::Orientation)), SLOT(setPaperOrientation(QPageLayout::Orientation))},
        {SIGNAL(setPaperBorderTopSignal(qreal)),                    SLOT(setPaperBorderTop(qreal))},
        {SIGNAL(setPaperBorderRightSignal(qreal)),                  SLOT(setPaperBorderRight(qreal))},
        {SIGNAL(setPaperBorderBottomSignal(qreal)),                 SLOT(setPaperBorderBottom(qreal))},
        {SIGNAL(setPaperBorderLeftSignal(qreal)),                   SLOT(setPaperBorderLeft(qreal))},
        {SIGNAL(setCustomPaperSizeSignal(const QSizeF&)),           SLOT(setCustomPaperSize(const QSizeF&))},
        {SIGNAL(setUseCustomPaperSizeSignal(bool)),                 SLOT(setUseCustomPaperSize(bool))},
        {SIGNAL(setOverlappingWidthSignal(qreal)),                  SLOT(setOverlappingWidth(qreal))},
        {SIGNAL(setOverlappingHeightSignal(qreal)),                 SLOT(setOverlappingHeight(qreal))},
        {SIGNAL(setOverlappingPositionSignal(Qt::Alignment)),       SLOT(setOverlappingPosition(Qt::Alignment))},
        {SIGNAL(setPosterWidthAbsoluteSignal(qreal)),               SLOT(setPosterWidthAbsolute(qreal))},
        {SIGNAL(setPosterHeightAbsoluteSignal(qreal)),              SLOT(setPosterHeightAbsolute(qreal))},
        {SIGNAL(setPosterWidthPagesSignal(qreal)),                  SLOT(setPosterWidthPages(qreal))},
        {SIGNAL(setPosterHeightPagesSignal(qreal)),                 SLOT(setPosterHeightPages(qreal))},
        {SIGNAL(setPosterSizePercentualSignal(qreal)),              SLOT(setPosterSizePercentual(qreal))},
        {SIGNAL(setPosterSizeModeSignal(Types::PosterSizeModes)),   SLOT(setPosterSizeMode(Types::PosterSizeModes))},
        {SIGNAL(setPosterAlignmentSignal(Qt::Alignment)),           SLOT(setPosterAlignment(Qt::Alignment))},
        {SIGNAL(setLaunchPDFApplicationSignal(bool)),               SLOT(setLaunchPDFApplication(bool))},
        {SIGNAL(updatePreviewSignal()),                             SLOT(updatePreview())},
        {SIGNAL(showImageFileNameSignal(const QString&)),           SLOT(showImageFileName(const QString&))},
        {SIGNAL(updateImageInfoFieldsSignal(const QSize&, const QSizeF&, qreal, qreal, Types::ColorTypes, int)),
                                                                    SLOT(updateImageInfoFields(const QSize&, const QSizeF&, qreal, qreal, Types::ColorTypes, int))},
        {SIGNAL(setCurrentTranslationSignal(const QString&)),       SLOT(setCurrentTranslation(const QString&))},
        {SIGNAL(addAboutDialogActionSignal(QAction*)),              SLOT(addAboutDialogAction(QAction*))},
        {SIGNAL(readSettingsSignal(const QSettings*)),              SLOT(readSettings(const QSettings*))},
        {SIGNAL(writeSettingsSignal(QSettings*)),                   SLOT(writeSettings(QSettings*))},
        {SIGNAL(setCurrentUnitOfLengthSignal(const QString&)),      SLOT(setCurrentUnitOfLength(const QString&))},
        {SIGNAL(setPosterSavingEnabledSignal(bool)),                SLOT(setPosterSavingEnabled(bool))},
        {SIGNAL(setPosterSizeModeAvailableSignal(Types::PosterSizeModes, bool)),
                                                                    SLOT(setPosterSizeModeAvailable(Types::PosterSizeModes, bool))}
    };
    for (auto &connection : signalsToViewSlotsConnections) {
        const QByteArray slot(
                QMetaObject::normalizedSignature(connection.slot + 1));
                // + 1: Remove slot flag '1'
        if (m_view->metaObject()->indexOfSlot(slot) != -1)
            connect(this, connection.signal, m_view, connection.slot);
    }

    m_wizardController = new WizardController(m_view, this);

    if (!m_posteRazorCore->imageIOLibraryAboutText().isEmpty()) {
        auto aboutAction = new QAction(m_view);
        aboutAction->setText(QStringLiteral("A&bout ") + m_posteRazorCore->imageIOLibraryName());
        connect (aboutAction, SIGNAL(triggered()), SLOT(showExtraAboutDialog()));
        emit addAboutDialogActionSignal(aboutAction);
    }

    updateDialog();
    setDialogPosterSizeMode();

    if (m_posteRazorCore->isImageLoaded()) {
        m_posteRazorCore->createPreviewImage();
        m_wizardController->handleImageLoaded();
    }

    m_translator = new QTranslator(this);
    loadTranslation(QString());
}

void Controller::updateDialog()
{
    const QString unitOfLength = Types::unitsOfLength().value(m_posteRazorCore->unitOfLength()).first;
    emit setCurrentUnitOfLengthSignal(unitOfLength);
    setDialogPaperOptions();
    setDialogPosterOptions();
    setDialogOverlappingOptions();
    setDialogImageInfoFields();
    setDialogSaveOptions();
    updatePreview();
}

void Controller::updatePreview()
{
    emit updatePreviewSignal();
}

void Controller::setPosterSizeModeAvailable(Types::PosterSizeModes mode, bool available)
{
    emit setPosterSizeModeAvailableSignal(mode, available);
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

void Controller::setPaperOrientation(QPageLayout::Orientation orientation)
{
    m_posteRazorCore->setPaperOrientation(orientation);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setPaperBorderTop(qreal border)
{
    m_posteRazorCore->setPaperBorderTop(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderRight(qreal border)
{
    m_posteRazorCore->setPaperBorderRight(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderBottom(qreal border)
{
    m_posteRazorCore->setPaperBorderBottom(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setPaperBorderLeft(qreal border)
{
    m_posteRazorCore->setPaperBorderLeft(border);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setCustomPaperWidth(qreal width)
{
    m_posteRazorCore->setCustomPaperWidth(width);
    setDialogPosterOptions();
    setDialogPaperBorders();
    updatePreview();
}

void Controller::setCustomPaperHeight(qreal height)
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

void Controller::setOverlappingWidth(qreal width)
{
    m_posteRazorCore->setOverlappingWidth(width);
    setDialogPosterOptions();
    updatePreview();
}

void Controller::setOverlappingHeight(qreal height)
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

void Controller::setPosterWidthAbsolute(qreal width)
{
    m_posteRazorCore->setPosterWidth(Types::PosterSizeModeAbsolute, width);
    setDialogPosterDimensions(Types::PosterSizeModeAbsolute, true);
}

void Controller::setPosterHeightAbsolute(qreal height)
{
    m_posteRazorCore->setPosterHeight(Types::PosterSizeModeAbsolute, height);
    setDialogPosterDimensions(Types::PosterSizeModeAbsolute, false);
}

void Controller::setPosterWidthPages(qreal width)
{
    m_posteRazorCore->setPosterWidth(Types::PosterSizeModePages, width);
    setDialogPosterDimensions(Types::PosterSizeModePages, true);
}

void Controller::setPosterHeightPages(qreal height)
{
    m_posteRazorCore->setPosterHeight(Types::PosterSizeModePages, height);
    setDialogPosterDimensions(Types::PosterSizeModePages, false);
}

void Controller::setPosterSizePercentual(qreal percent)
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
    emit setLaunchPDFApplicationSignal(m_launchPDFApplication);
}

void Controller::setDialogPosterSizeMode()
{
    emit setPosterSizeModeSignal(m_posteRazorCore->posterSizeMode());
}

void Controller::setDialogPosterOptions()
{
    setDialogPosterDimensions(Types::PosterSizeModeNone, true);
    emit setPosterAlignmentSignal(m_posteRazorCore->posterAlignment());
    emit setPosterSizeModeSignal(m_posteRazorCore->posterSizeMode());
}

void Controller::setDialogPosterDimensions(Types::PosterSizeModes excludedMode, bool widthExcluded)
{
    const QSizeF posterSizeAbsolute = m_posteRazorCore->posterSize(Types::PosterSizeModeAbsolute);
    const QSizeF posterSizePages = m_posteRazorCore->posterSize(Types::PosterSizeModePages);
    const QSizeF posterSizePercentual = m_posteRazorCore->posterSize(Types::PosterSizeModePercentual);
    if (excludedMode != Types::PosterSizeModeAbsolute || !widthExcluded)
        emit setPosterWidthAbsoluteSignal(posterSizeAbsolute.width());
    if (excludedMode != Types::PosterSizeModeAbsolute || widthExcluded)
        emit setPosterHeightAbsoluteSignal(posterSizeAbsolute.height());
    if (excludedMode != Types::PosterSizeModePages || !widthExcluded)
        emit setPosterWidthPagesSignal(posterSizePages.width());
    if (excludedMode != Types::PosterSizeModePages || widthExcluded)
        emit setPosterHeightPagesSignal(posterSizePages.height());
    if (excludedMode != Types::PosterSizeModePercentual)
        emit setPosterSizePercentualSignal(posterSizePercentual.width());
    updatePreview();
}

void Controller::setDialogPaperOptions()
{
    setDialogPaperBorders();
    setDialogCustomPaperDimensions();
    emit setUseCustomPaperSizeSignal(m_posteRazorCore->usesCustomPaperSize());
    emit setPaperFormatSignal(m_posteRazorCore->paperFormat());
    emit setPaperOrientationSignal(m_posteRazorCore->paperOrientation());
}

void Controller::setDialogPaperBorders()
{
    emit setPaperBorderTopSignal(m_posteRazorCore->paperBorderTop());
    emit setPaperBorderRightSignal(m_posteRazorCore->paperBorderRight());
    emit setPaperBorderBottomSignal(m_posteRazorCore->paperBorderBottom());
    emit setPaperBorderLeftSignal(m_posteRazorCore->paperBorderLeft());
}

void Controller::setDialogCustomPaperDimensions()
{
    emit setCustomPaperSizeSignal(m_posteRazorCore->customPaperSize());
}

void Controller::setDialogImageInfoFields()
{
    if (m_posteRazorCore->isImageLoaded()) {
        emit updateImageInfoFieldsSignal(
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
    emit setOverlappingWidthSignal(m_posteRazorCore->overlappingWidth());
    emit setOverlappingHeightSignal(m_posteRazorCore->overlappingHeight());
}

void Controller::setDialogOverlappingOptions()
{
    setDialogOverlappingDimensions();
    emit setOverlappingPositionSignal(m_posteRazorCore->overlappingPosition());
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
            formatWildcards << QStringLiteral("*.") + extension;
        allWildcards << formatWildcards;
        QString formatName = formats.at(i).second;
        // Some Open File dialogs (at least OSX) ar irritated if there are brackes in the file type name
        formatName.remove(QLatin1Char('('));
        formatName.remove(QLatin1Char(')'));
        allFilters << formatName + QLatin1String(" (") +  formatWildcards.join(QLatin1String(" ")) + QLatin1Char(')');
    }
    allFilters.prepend(QCoreApplication::translate("Main window", "All image formats") + QLatin1String(" (") +  allWildcards.join(QLatin1String(" ")) + QLatin1Char(')'));

    QSettings loadPathSettings;

    const QString loadPathDefault =
            QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).constFirst();
#ifdef Q_OS_WASM
    QFileDialog::getOpenFileContent(allFilters.join(QLatin1String(";;")),
                                    [this](const QString &fileName, const QByteArray &fileContent) {
        const QString previousFileName = m_posteRazorCore->fileName();
        const QString copyFileName = QLatin1String("/home/web_user/") + QFileInfo(fileName).fileName();

        QFile imageFile(copyFileName);
        if (imageFile.open(QIODevice::WriteOnly)) {
            imageFile.write(fileContent);
            imageFile.close();
        }

        if (handleInputImageSelected(copyFileName))
            QFile::remove(previousFileName);
        else
            QFile::remove(copyFileName);
    });
#else
    const QString loadFileName =
            QFileDialog::getOpenFileName(m_view,
                                         QCoreApplication::translate("Main window", "Load an input image"),
                                         loadPathSettings.value(settingsKey_ImageLoadPath, loadPathDefault).toString(),
                                         allFilters.join(QLatin1String(";;")));

    handleInputImageSelected(loadFileName);
#endif // QT_OS_WASM
}

bool Controller::loadInputImage(const QString &fileName)
{
    QString loadErrorMessage;
    const bool successful = loadInputImage(fileName, loadErrorMessage);
    if (!successful)
        QMessageBox::critical(m_view, QString(), QCoreApplication::translate("Main window", "The image '%1' could not be loaded.")
            .arg(QFileInfo(fileName).fileName()));
    return successful;
}

bool Controller::loadInputImage(const QString &imageFileName, QString &errorMessage)
{
    const bool result = m_posteRazorCore->loadInputImage(imageFileName, errorMessage);
    if (result) {
        updateDialog();
        emit showImageFileNameSignal(imageFileName);
        emit setPosterSavingEnabledSignal(true);
    }
    return result;
}

int Controller::savePoster(const QString &fileName) const
{
#ifdef Q_OS_WASM
    QByteArray posterData;
    QBuffer outIODevice(&posterData);
    outIODevice.open(QIODevice::WriteOnly);
#else
    QFile outIODevice(fileName);
    if (!outIODevice.open((QIODevice::WriteOnly)))
        return -1;
#endif // Q_OS_WASM

    const int result = m_posteRazorCore->savePoster(&outIODevice);

#ifdef Q_OS_WASM
    outIODevice.close();
    // Snippet borrowed from my dear colleague Morten:
    // https://codereview.qt-project.org/c/qt/qtbase/+/228599
    EM_ASM_({
        // Make the file contents and file name hint accessible to Javascript: convert
        // the char * to a JavaScript string and create a subarray view into the C heap.
        const contentPointer = $0;
        const contentLength = $1;
        const fileNameHint = UTF8ToString($2);
        const fileContent = Module.HEAPU8.subarray(contentPointer, contentPointer + contentLength);

        // Create a hidden download link and click it programatically
        const fileblob = new Blob([fileContent], { type : "application/octet-stream" } );
        var link = document.createElement("a");
        document.body.appendChild(link);
        link.download = fileNameHint;
        link.href = window.URL.createObjectURL(fileblob);
        link.style = "display:none";
        link.click();
        document.body.removeChild(link);
    }, posterData.constData(), posterData.length(), fileName.toUtf8().constData());
#else
    if (result == 0 && m_launchPDFApplication)
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
#endif // Q_OS_WASM

    return result;
}

void Controller::savePoster() const
{
#ifdef Q_OS_WASM
    savePoster(QFileInfo(m_posteRazorCore->fileName()).baseName() + QLatin1String(".pdf"));
    return;
#endif // Q_OS_WASM

    QSettings savePathSettings;

    QString saveFileName = savePathSettings.value(settingsKey_PosterSavePath,
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString()
            + QDir::separator()
            + QFileInfo(m_posteRazorCore->fileName()).baseName()
            + QLatin1String("-")
            + QCoreApplication::translate("Main window", "poster")
            + QLatin1String(".pdf");
    bool fileExistsAskUserForOverwrite = false;

    do {
        saveFileName = QFileDialog::getSaveFileName(
            m_view,
            QCoreApplication::translate("Main window", "Save the poster"),
            saveFileName,
            QLatin1String("Portable Document format (*.pdf)"),
            nullptr,
            QFileDialog::DontConfirmOverwrite
        );

        if (!saveFileName.isEmpty()) {
            const QFileInfo saveFileInfo(saveFileName);
            if (saveFileInfo.suffix().toLower() != QLatin1String("pdf"))
                saveFileName.append(QLatin1String(".pdf"));

            fileExistsAskUserForOverwrite = QFileInfo::exists(saveFileName);

            if (!fileExistsAskUserForOverwrite
                    || QMessageBox::Yes == (QMessageBox::question(m_view, QString(), QCoreApplication::translate("Main window", "The file '%1' already exists.\nDo you want to overwrite it?").arg(saveFileInfo.fileName()), QMessageBox::Yes, QMessageBox::No))
                ) {
                int result = savePoster(saveFileName);
                if (result != 0)
                    QMessageBox::critical(m_view, QString(), QCoreApplication::translate("Main window", "The file '%1' could not be saved.").arg(saveFileInfo.fileName()), QMessageBox::Ok, QMessageBox::NoButton);
                else
                    savePathSettings.setValue(settingsKey_PosterSavePath,
                        QDir::toNativeSeparators(QFileInfo(saveFileName).absolutePath()));
                fileExistsAskUserForOverwrite = false;
            }
        } else {
            break;
        }
    } while (fileExistsAskUserForOverwrite);
}

void Controller::loadTranslation(const QString &localeName)
{
    const QString saneLocaleName = localeName.isEmpty() ? QLocale::system().name() : localeName;
    const QString translationFileName(QLatin1String(":/Translations/") + saneLocaleName);
    if (m_translator->load(translationFileName)) {
        QCoreApplication::removeTranslator(m_translator);
        QCoreApplication::installTranslator(m_translator);
        emit setCurrentTranslationSignal(saneLocaleName);
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

void Controller::setImageLoadingAvailable(bool available)
{
    m_wizardController->setStepAvailable(WizardController::WizardStepInputImage, available);
}

void Controller::showExtraAboutDialog()
{
    const QString title = QLatin1String("About ") + m_posteRazorCore->imageIOLibraryName();
    QMessageBox::about(
        m_view, title, QStringLiteral("<h3>%1</h3>%2")
                .arg(title, Types::newlineToParagraph(m_posteRazorCore->imageIOLibraryAboutText()))
    );
}

void Controller::imageSuffixSupported(const QString &suffix, bool &outIsSupported) const
{
    outIsSupported = false;
    const QVector<QPair<QStringList, QString> > &formats = m_posteRazorCore->imageFormats();
    for (int i = 0; i < formats.count(); i++) {
        if (formats.at(i).first.contains(suffix, Qt::CaseInsensitive)) {
            outIsSupported = true;
            break;
        }
    }
}

bool Controller::handleInputImageSelected(const QString &fileName)
{
    bool successful = false;

    if (!fileName.isEmpty()) {
        successful = loadInputImage(fileName);
        if (successful) {
            QSettings loadPathSettings;
            loadPathSettings.setValue(settingsKey_ImageLoadPath,
                QDir::toNativeSeparators(QFileInfo(fileName).absolutePath()));
        }
    }

    return successful;
}
