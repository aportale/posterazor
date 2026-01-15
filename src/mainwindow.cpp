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

#include "mainwindow.h"

#include <QActionGroup>
#include <QDialogButtonBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaMethod>
#include <QMimeData>
#include <QSettings>
#include <QSignalMapper>
#include <QTextBrowser>
#include <QTranslator>
#include <QVBoxLayout>
#include <QtDebug>
#ifdef Q_OS_MACOS
#include <QStyleFactory>
#include <QPalette>
#include <QPushButton>
#include <QToolButton>
#include <QGroupBox>
#include <QFrame>
#include <QWidget>
#endif

const QLatin1String settingsKey_MainWindowGeometry("MainWindowGeometry");

static QString applicationNameWithVersion()
{
    return
        QCoreApplication::applicationName()
        + QLatin1Char(' ') + QCoreApplication::applicationVersion() ;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    m_unitOfLengthActions = new QActionGroup(m_menuSettings);

    m_actionLoadInputImage->setShortcuts(
        QList<QKeySequence>() << (Qt::CTRL | Qt::Key_L) << (Qt::CTRL | Qt::Key_O));
    m_actionSavePoster->setShortcut(Qt::CTRL | Qt::Key_S);
    m_actionExit->setShortcut(Qt::CTRL | Qt::Key_Q);
    m_actionPosteRazorManual->setShortcut(Qt::Key_F1);
    m_actionLoadInputImage->setIcon(QApplication::style()->standardPixmap(QStyle::SP_DirOpenIcon));
    m_actionSavePoster->setIcon(QApplication::style()->standardPixmap(QStyle::SP_DialogSaveButton));
    m_actionSavePoster->setEnabled(false);

    setWindowIcon(QIcon(QLatin1String(":/Icons/posterazor.png")));

    setWindowTitle(applicationNameWithVersion());
    createConnections();
    populateUI();
    retranslateUi();

    setAcceptDrops(true);

#ifdef Q_OS_MACOS
    applyMacOSStyling();
#endif
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi();
#ifdef Q_OS_MACOS
    else if (event->type() == QEvent::PaletteChange) {
        // Reapply styling when system appearance changes (light/dark mode)
        applyMacOSStyling();
    }
#endif
    QMainWindow::changeEvent(event);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        const QUrl url = mimeData->urls().constFirst();
        const QString localFile = url.toLocalFile();
        const QString fileSuffix = QFileInfo(localFile).suffix();
        bool suffixIsSupported = false;
        emit imageSuffixSupportedSignal(fileSuffix, suffixIsSupported);
        if (suffixIsSupported)
            event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    emit loadImageSignal(event->mimeData()->urls().first().toLocalFile());
}

void MainWindow::retranslateUi()
{
    // TODO: Add shortcut and trailing "..." for load and save action. Enhance cleanString and use it in WizardController
    m_actionLoadInputImage->setText(                QCoreApplication::translate("Help", "Load an input image"));
    m_actionSavePoster->setText(                    QCoreApplication::translate("Help", "Save the Poster"));
    m_actionPosteRazorManual->setText(              QCoreApplication::translate("Help", "&Manual"));
    m_actionPosteRazorWebSite->setText(             QCoreApplication::translate("Help", "PosteRazor &website"));
    m_actionAboutPosteRazor->setText(               QCoreApplication::translate("Help", "&About PosteRazor"));
    m_actionAboutQt->setText(                       QCoreApplication::translate("Help", "About &Qt"));
    m_actionExit->setText(                          QCoreApplication::translate("Main window", "E&xit"));
    m_menuFile->setTitle(                           QCoreApplication::translate("Main window", "&File"));
    m_menuSettings->setTitle(                       QCoreApplication::translate("Main window", "&Settings"));
}

void MainWindow::setPaperFormat(const QString &format)
{
    m_wizard->setPaperFormat(format);
}

void MainWindow::setPaperOrientation(QPageLayout::Orientation orientation)
{
    m_wizard->setPaperOrientation(orientation);
}

void MainWindow::setPaperBorderTop(qreal border)
{
    m_wizard->setPaperBorderTop(border);
}

void MainWindow::setPaperBorderRight(qreal border)
{
    m_wizard->setPaperBorderRight(border);
}

void MainWindow::setPaperBorderBottom(qreal border)
{
    m_wizard->setPaperBorderBottom(border);
}

void MainWindow::setPaperBorderLeft(qreal border)
{
    m_wizard->setPaperBorderLeft(border);
}

void MainWindow::setCustomPaperSize(const QSizeF &size)
{
    m_wizard->setCustomPaperSize(size);
}

void MainWindow::setUseCustomPaperSize(bool useIt)
{
    m_wizard->setUseCustomPaperSize(useIt);
}

void MainWindow::setOverlappingWidth(qreal width)
{
    m_wizard->setOverlappingWidth(width);
}

void MainWindow::setOverlappingHeight(qreal height)
{
    m_wizard->setOverlappingHeight(height);
}

void MainWindow::setOverlappingPosition(Qt::Alignment position)
{
    m_wizard->setOverlappingPosition(position);
}

void MainWindow::setPosterWidthAbsolute(qreal width)
{
    m_wizard->setPosterWidthAbsolute(width);
}

void MainWindow::setPosterHeightAbsolute(qreal height)
{
    m_wizard->setPosterHeightAbsolute(height);
}

void MainWindow::setPosterWidthPages(qreal width)
{
    m_wizard->setPosterWidthPages(width);
}

void MainWindow::setPosterHeightPages(qreal height)
{
    m_wizard->setPosterHeightPages(height);
}

void MainWindow::setPosterSizePercentual(qreal percent)
{
    m_wizard->setPosterSizePercentual(percent);
}

void MainWindow::setPosterSizeMode(Types::PosterSizeModes mode)
{
    m_wizard->setPosterSizeMode(mode);
}

void MainWindow::setPosterAlignment(Qt::Alignment alignment)
{
    m_wizard->setPosterAlignment(alignment);
}

void MainWindow::setLaunchPDFApplication(bool launch)
{
    m_wizard->setLaunchPDFApplication(launch);
}

void MainWindow::updatePreview()
{
    m_wizard->updatePreview();
}

void MainWindow::showImageFileName(const QString &fileName)
{
    m_wizard->showImageFileName(fileName);
}

void MainWindow::updateImageInfoFields(const QSize &inputImageSizeInPixels, const QSizeF &imageSize, qreal verticalDpi, qreal horizontalDpi, Types::ColorTypes colorType, int bitsPerPixel)
{
    m_wizard->updateImageInfoFields(inputImageSizeInPixels, imageSize, verticalDpi, horizontalDpi, colorType, bitsPerPixel);
}

void MainWindow::setCurrentTranslation(const QString &translation)
{
    QAction *translationAction = m_translationActions.value(translation);
    if (!translationAction) {
        // On a Swiss system 'translation' may be "de_CH". So let's fall back to "de"
        const QString translationLanguage = translation.split(QLatin1Char('_')).first();
        translationAction = m_translationActions.value(translationLanguage);
    }
    if (translationAction)
        translationAction->setChecked(true);
}

void MainWindow::setCurrentUnitOfLength(const QString &unit)
{
    foreach (QAction *action, m_unitOfLengthActions->actions()) {
        if (action->text() == unit) {
            action->setChecked(true);
            break;
        }
    }
    m_wizard->setCurrentUnitOfLength(unit);
}

void MainWindow::addAboutDialogAction(QAction *action)
{
    m_menuAbout->addAction(action);
}

void MainWindow::setPrevButtonEnabled(bool enabled)
{
    m_wizard->setPrevButtonEnabled(enabled);
}

void MainWindow::setNextButtonEnabled(bool enabled)
{
    m_wizard->setNextButtonEnabled(enabled);
}

void MainWindow::setPosterSavingEnabled(bool enabled)
{
    m_actionSavePoster->setEnabled(enabled);
    m_wizard->setPosterSavingEnabled(enabled);
}

void MainWindow::setWizardStep(int step)
{
    m_wizard->setWizardStep(step);
}

void MainWindow::setWizardStepDescription(const QString &number, const QString &description)
{
    m_wizard->setWizardStepDescription(number, description);
}

void MainWindow::setPreviewState(const QString &state)
{
    m_wizard->setPreviewState(state);
}

void MainWindow::setPreviewImage(const QImage &image)
{
    m_wizard->setPreviewImage(image);
}

void MainWindow::showWizardStepHelp(const QString &title, const QString &text)
{
    QMessageBox box(this);
    box.setWindowTitle(title);
    QString helpText = text;
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

void MainWindow::showManual(const QString &title, const QString &text)
{
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);
    dialog->setWindowTitle(title);
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->setWindowFlags(dialog->windowFlags() ^ Qt::WindowContextHelpButtonHint);
    dialog->resize(500, 400);
    dialog->setLayout(new QVBoxLayout);
    auto browser = new QTextBrowser;
    browser->setOpenExternalLinks(true);
    browser->document()->setDefaultStyleSheet(QLatin1String(
        "dt {font-weight: bold;}"
        "dd {margin-left: 15px;}"
        "p {text-indent: 7px;}"
        "p, dd {margin-top: 0px; margin-bottom: 6px;}"
        "h2 {margin-top: 18px; margin-bottom: 6px;}"));
    browser->setHtml(text);
    dialog->layout()->addWidget(browser);
    auto buttonBox = new QDialogButtonBox;
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted ()), dialog, SLOT(accept()));
    dialog->layout()->addWidget(buttonBox);
    dialog->show();
}

void MainWindow::handleTranslationAction(QAction *action) const
{
    emit translationChanged(action->data().toString());
}

void MainWindow::handleUnitOfLengthAction(QAction *action) const
{
    emit unitOfLengthChanged(action->text());
}

void MainWindow::createConnections()
{
    connect(m_actionExit,                           SIGNAL(triggered()),                SLOT(close()));
    connect(m_actionLoadInputImage,                 SIGNAL(triggered()),                SIGNAL(loadImageSignal()));
    connect(m_actionSavePoster,                     SIGNAL(triggered()),                SIGNAL(savePosterSignal()));
    connect(m_actionPosteRazorWebSite,              SIGNAL(triggered()),                SIGNAL(openPosteRazorWebsiteSignal()));
    connect(m_actionAboutQt,                        SIGNAL(triggered()),                SLOT(showAboutQtDialog()));
    connect(m_actionAboutPosteRazor,                SIGNAL(triggered()),                SLOT(showAboutPosteRazorDialog()));
    connect(m_actionPosteRazorManual,               SIGNAL(triggered()),                SIGNAL(manualSignal()));

    static const char* const relayedSignals[] = {
        SIGNAL(paperFormatChanged(const QString&)),
        SIGNAL(useCustomPaperSizeChanged(bool)),
        SIGNAL(paperOrientationChanged(QPageLayout::Orientation)),
        SIGNAL(paperCustomWidthChanged(qreal)),
        SIGNAL(paperCustomHeightChanged(qreal)),
        SIGNAL(paperBorderTopChanged(qreal)),
        SIGNAL(paperBorderRightChanged(qreal)),
        SIGNAL(paperBorderBottomChanged(qreal)),
        SIGNAL(paperBorderLeftChanged(qreal)),
        SIGNAL(overlappingWidthChanged(qreal)),
        SIGNAL(overlappingHeightChanged(qreal)),
        SIGNAL(overlappingPositionChanged(Qt::Alignment)),
        SIGNAL(posterWidthAbsoluteChanged(qreal)),
        SIGNAL(posterHeightAbsoluteChanged(qreal)),
        SIGNAL(posterWidthPagesChanged(qreal)),
        SIGNAL(posterHeightPagesChanged(qreal)),
        SIGNAL(posterSizePercentualChanged(qreal)),
        SIGNAL(posterAlignmentChanged(Qt::Alignment)),
        SIGNAL(savePosterSelected()),
        SIGNAL(launchPDFApplicationChanged(bool)),
        SIGNAL(nextButtonPressed()),
        SIGNAL(prevButtonPressed()),
        SIGNAL(wizardStepHelpSignal()),
        SIGNAL(savePosterSignal()),
        SIGNAL(loadImageSignal()),
        SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)),
        SIGNAL(imageLoaded()),
    };
    for (auto signal : relayedSignals)
        connect(m_wizard, signal, signal);
}

void MainWindow::populateUI()
{
    connect (m_unitOfLengthActions, SIGNAL(triggered(QAction*)), SLOT(handleUnitOfLengthAction(QAction*)));
    m_unitOfLengthActions->setExclusive(true);
    const int unitsOfLengthCount = Types::unitsOfLength().count();
    for (int i = 0; i < unitsOfLengthCount; i++) {
        const QString unitOfLength = Types::unitsOfLength().value((Types::UnitsOfLength)i).first;
        QAction *unitOfLengthAction = m_unitOfLengthActions->addAction(unitOfLength);
        unitOfLengthAction->setCheckable(true);
    }
    m_menuSettings->addActions(m_unitOfLengthActions->actions());

    m_menuSettings->addSeparator();

    auto translationActions = new QActionGroup(m_menuSettings);
    connect (translationActions, SIGNAL(triggered(QAction*)), SLOT(handleTranslationAction(QAction*)));
    translationActions->setExclusive(true);
    const QDir translationDir(QLatin1String(":/Translations/"));
    foreach (const QFileInfo &translation, translationDir.entryInfoList(QDir::Files)) {
        QTranslator translator;
        translator.load(translation.absoluteFilePath());
        QAction *languageAction = translationActions->addAction(translator.translate("Main window", "Language name"));
        // TODO: Find out why the menu entries are empty on Mac (and maybe on Linux?)
        const QString localeString(translation.baseName());
        languageAction->setData(localeString);
        languageAction->setCheckable(true);
        m_translationActions.insert(localeString, languageAction);
    }
    m_menuSettings->addActions(translationActions->actions());
}

void MainWindow::showAboutQtDialog() const
{
    QApplication::aboutQt();
}

void MainWindow::showAboutPosteRazorDialog()
{
    const QString title = Types::cleanString(QCoreApplication::translate("Help", "&About PosteRazor"));
    const QString webpageAnchor = QString::fromLatin1("<a href=\"%1\">posterazor.sourceforge.net</a>")
        .arg(QCoreApplication::translate("Help", "http://posterazor.sourceforge.net/", "Only translate, if the website has this language."));
    const QString aboutText =
        QLatin1String("<h1>") + applicationNameWithVersion() +
        QLatin1String("</h1>") +
        Types::newlineToParagraph(QCoreApplication::translate("Help",
            "The PosteRazor cuts a raster image into pieces which can be printed on a printer and be put together to a poster.\n"
            "As an input image, raster files of various image file formats are supported. Instead of directly printing the poster, the PosteRazor produces a multi page PDF file which contains the poster tiles.\n"
            "It is an open source program which depends on other open source projects. The PosteRazor is hosted on %1.")
            .arg(webpageAnchor)) +
        QLatin1String("<h2>Code from third parties</h2>"
            "<dl>"
            "<dt>Qt</dt>"
            "<dd>Extensive use of <a href=\"http://www.trolltech.com/\">Trolltech</a>s amazing cross-platform application framework</dd>"
            "<dt>FreeImage</dt>"
            "<dd>Easy and powerful image format support. See the <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></dd>"
            "</dl>") +
        QString::fromUtf8("<h2>Translations</h2>"
            "<p>In order of appearance</p>"
            "<dl>"
            "<dt>English</dt><dd>Alessandro Portale (author)</dd>"
            "<dt>German</dt><dd>Alessandro Portale (author)</dd>"
            "<dt>Polish</dt><dd>Grzegorz Wacikowski</dd>"
            "<dt>French</dt><dd>Martin Loyer</dd>"
            "<dt>Italian</dt><dd>Stefano Nosei</dd>"
            "<dt>Dutch/Belgian</dt><dd>Erik Wijkamp</dd>"
            "<dt>Spanish</dt><dd><a href=\"http://hispanicoweb.net/\">Hisp""\xc3\xa1""nico Web</a></dd>"
            "<dt>Brazilian Portuguese</dt><dd>""\xc3\x89""derson Gomes dos Santos</dd>"
            "<dt>European Portuguese</dt><dd>Helder Correia</dd>"
            "<dt>Simplified Chinese</dt><dd>Sun Li</dd>"
            "<dt>Finnish</dt><dd>Olli</dd>"
            "<dt>Traditional Chinese</dt><dd>Chung-Yu Hsu</dd>"
            "<dt>Russian</dt><dd>Artem Semendyaev</dd>"
            "<dt>Czech</dt><dd>Filip Pivar""\xc4\x8d""i</dd>"
            "<dt>Danish</dt><dd><a href=\"http://www.troels-hansen.dk\">Henrik Troels-Hansen</a></dd>"
            "</dl>") +
        QLatin1String("<h2>License</h2>"
            "<p>PosteRazor - Make your own poster!<br/>"
            "posterazor.sourceforge.net<br/>"
            "Copyright (C) 2005-2018 by Alessandro Portale</p>"
            "<p>This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p>"
            "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>"
            "<p>You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.</p>");
    showManual(title, aboutText);
}

void MainWindow::readSettings(const QSettings *settings)
{
    restoreGeometry(settings->value(settingsKey_MainWindowGeometry, QByteArray()).toByteArray());
}

void MainWindow::writeSettings(QSettings *settings) const
{
    settings->setValue(settingsKey_MainWindowGeometry, saveGeometry());
}

#ifdef Q_OS_MACOS
void MainWindow::applyMacOSStyling()
{
    // Use native macOS style if available
    QStyle *nativeStyle = QStyleFactory::create(QLatin1String("macOS"));
    if (!nativeStyle) {
        nativeStyle = QStyleFactory::create(QLatin1String("Macintosh"));
    }
    if (nativeStyle) {
        QApplication::setStyle(nativeStyle);
    }

    // Apply system colors for proper light/dark mode support
    QPalette palette = QApplication::palette();
    QApplication::setPalette(palette);
    
    // Get system colors for styling
    QColor windowColor = palette.color(QPalette::Window);
    QColor buttonColor = palette.color(QPalette::Button);
    QColor buttonTextColor = palette.color(QPalette::ButtonText);
    QColor highlightColor = palette.color(QPalette::Highlight);
    
    // Determine if we're in dark mode
    bool isDarkMode = windowColor.lightness() < 128;
    
    // Modernize push buttons with rounded corners and hover effects
    QList<QPushButton*> pushButtons = findChildren<QPushButton*>();
    for (QPushButton *button : pushButtons) {
        // Ensure minimum height for macOS standards (30px)
        QSize size = button->sizeHint();
        if (size.height() < 30) {
            button->setMinimumHeight(30);
        }
        
        // Apply modern button styling with rounded corners
        QString buttonStyle = QLatin1String(
            "QPushButton {"
            "    background-color: %1;"
            "    color: %2;"
            "    border: 1px solid %3;"
            "    border-radius: 6px;"
            "    padding: 6px 16px;"
            "    font-size: 13px;"
            "    min-height: 30px;"
            "}"
            "QPushButton:hover {"
            "    background-color: %4;"
            "    border-color: %5;"
            "}"
            "QPushButton:pressed {"
            "    background-color: %6;"
            "}"
            "QPushButton:disabled {"
            "    background-color: %7;"
            "    color: %8;"
            "    border-color: %9;"
            "}"
        ).arg(buttonColor.name())
         .arg(buttonTextColor.name())
         .arg(isDarkMode ? QColor(60, 60, 60).name() : QColor(180, 180, 180).name())
         .arg(isDarkMode ? QColor(buttonColor.lighter(110)).name() : QColor(buttonColor.darker(105)).name())
         .arg(isDarkMode ? QColor(80, 80, 80).name() : QColor(150, 150, 150).name())
         .arg(isDarkMode ? QColor(buttonColor.darker(120)).name() : QColor(buttonColor.lighter(110)).name())
         .arg(isDarkMode ? QColor(40, 40, 40).name() : QColor(240, 240, 240).name())
         .arg(isDarkMode ? QColor(100, 100, 100).name() : QColor(180, 180, 180).name())
         .arg(isDarkMode ? QColor(50, 50, 50).name() : QColor(200, 200, 200).name());
        
        button->setStyleSheet(buttonStyle);
    }
    
    // Modernize tool buttons
    QList<QToolButton*> toolButtons = findChildren<QToolButton*>();
    for (QToolButton *button : toolButtons) {
        // Ensure proper sizing for tool buttons
        if (button->minimumHeight() < 24) {
            button->setMinimumHeight(24);
        }
        
        // Apply rounded corners and hover effects
        QString toolButtonStyle = QLatin1String(
            "QToolButton {"
            "    background-color: transparent;"
            "    border: 1px solid transparent;"
            "    border-radius: 6px;"
            "    padding: 4px 8px;"
            "    min-height: 24px;"
            "}"
            "QToolButton:hover {"
            "    background-color: %1;"
            "}"
            "QToolButton:pressed {"
            "    background-color: %2;"
            "}"
            "QToolButton:checked {"
            "    background-color: %3;"
            "    border-color: %4;"
            "}"
        ).arg(isDarkMode ? QColor(60, 60, 60, 150).name(QColor::HexArgb) : QColor(220, 220, 220, 150).name(QColor::HexArgb))
         .arg(isDarkMode ? QColor(80, 80, 80, 200).name(QColor::HexArgb) : QColor(200, 200, 200, 200).name(QColor::HexArgb))
         .arg(highlightColor.name())
         .arg(highlightColor.darker(120).name());
        
        button->setStyleSheet(toolButtonStyle);
    }
    
    // Apply modern styling to central widget with blur effect background
    if (centralWidget()) {
        QString centralWidgetStyle = QLatin1String(
            "QWidget#centralwidget {"
            "    background-color: %1;"
            "}"
        ).arg(windowColor.name());
        centralWidget()->setStyleSheet(centralWidgetStyle);
    }
}
#endif
