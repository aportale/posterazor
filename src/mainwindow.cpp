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
#include <QSignalMapper>
#include <QFileDialog>
#include <QTranslator>
#include <QtDebug>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QTextBrowser>
#include <QMessageBox>

static QString applicationNameWithVersion()
{
    return
        QCoreApplication::applicationName()
#if QT_VERSION >= 0x040400
        + QLatin1Char(' ') + QCoreApplication::applicationVersion()
#endif
    ;
}

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    setupUi(this);

    m_imageInfoGroup->setVisible(false);

    m_unitOfLengthActions = new QActionGroup(m_menuSettings);

    m_actionLoadInputImage->setShortcuts(
        QList<QKeySequence>() << (Qt::CTRL + Qt::Key_L) << (Qt::CTRL + Qt::Key_O));
    m_actionSavePoster->setShortcut(Qt::CTRL + Qt::Key_S);
    m_actionExit->setShortcut(Qt::CTRL + Qt::Key_Q);
    m_actionPosteRazorManual->setShortcut(Qt::Key_F1);

    m_imageLoadButton->setIcon(QApplication::style()->standardPixmap(QStyle::SP_DirOpenIcon)); // SP_DialogOpenButton looks ugly
    m_stepHelpButton->setMinimumSize(m_imageLoadButton->sizeHint()); // Same size. Looks better
    m_savePosterButton->setIcon(QApplication::style()->standardPixmap(QStyle::SP_DialogSaveButton));
    m_actionLoadInputImage->setIcon(m_imageLoadButton->icon());
    m_actionSavePoster->setIcon(m_savePosterButton->icon());
    m_actionSavePoster->setEnabled(false);

    setWindowIcon(QIcon(":/Icons/posterazor.png"));

    const struct {
        QAbstractButton *sender;
        Qt::Alignment alignment;
    } alignmentMap[] = {
        {m_posterAlignmentTopLeftButton,     Qt::AlignTop | Qt::AlignLeft        },
        {m_posterAlignmentTopButton,         Qt::AlignTop | Qt::AlignHCenter     },
        {m_posterAlignmentTopRightButton,    Qt::AlignTop | Qt::AlignRight       },
        {m_posterAlignmentLeftButton,        Qt::AlignVCenter | Qt::AlignLeft    },
        {m_posterAlignmentCenterButton,      Qt::AlignCenter                     },
        {m_posterAlignmentRightButton,       Qt::AlignVCenter | Qt::AlignRight   },
        {m_posterAlignmentBottomLeftButton,  Qt::AlignBottom | Qt::AlignLeft     },
        {m_posterAlignmentBottomButton,      Qt::AlignBottom | Qt::AlignHCenter  },
        {m_posterAlignmentBottomRightButton, Qt::AlignBottom | Qt::AlignRight    }
    };
    const int alignmentMapCount = (int)sizeof(alignmentMap)/sizeof(alignmentMap[0]);
    for (int i = 0; i < alignmentMapCount; i++)
        m_alignmentButtons.insert(alignmentMap[i].alignment, alignmentMap[i].sender);

    const struct {
        QAbstractButton *sender;
        Qt::Alignment alignment;
    } overlappingMap[] = {
        {m_overlappingPositionTopLeftButton,     Qt::AlignTop | Qt::AlignLeft     },
        {m_overlappingPositionTopRightButton,    Qt::AlignTop | Qt::AlignRight    },
        {m_overlappingPositionBottomLeftButton,  Qt::AlignBottom | Qt::AlignLeft  },
        {m_overlappingPositionBottomRightButton, Qt::AlignBottom | Qt::AlignRight }
    };
    const int overlappingMapCount = (int)sizeof(overlappingMap)/sizeof(overlappingMap[0]);
    for (int i = 0; i < overlappingMapCount; i++)
        m_overlappingButtons.insert(overlappingMap[i].alignment, overlappingMap[i].sender);

    setWindowTitle(applicationNameWithVersion());
    m_steps->setCurrentIndex(0);
    createConnections();
    populateUI();
    updatePosterSizeGroupsState();
    retranslateUi();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi();
    QMainWindow::changeEvent(event);
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

    m_imageInfoGroup->setTitle(                     QCoreApplication::translate("Main window", "Image Informations"));
    m_imageInformationColorTypeLabel->setText(      QCoreApplication::translate("Main window", "Color type:"));
    m_imageInformationResolutionLabel->setText(     QCoreApplication::translate("Main window", "Resolution:"));
    m_imageInformationSizeInPixelsLabel->setText(   QCoreApplication::translate("Main window", "Size (in pixels):"));
    m_inputImageGroup->setTitle(                    QCoreApplication::translate("Main window", "Input Image"));
    m_launchPDFApplicationCheckBox->setText(        QCoreApplication::translate("Main window", "Open PDF after saving"));
    m_menuFile->setTitle(                           QCoreApplication::translate("Main window", "&File"));
    m_menuSettings->setTitle(                       QCoreApplication::translate("Main window", "&Settings"));
    m_stepNextButton->setText(                      QCoreApplication::translate("Main window", "Next"));
    m_overlappingHeightLabel->setText(              QCoreApplication::translate("Main window", "Height:"));
    m_overlappingPositionBottomLeftButton->setText( QCoreApplication::translate("Main window", "Bottom left"));
    m_overlappingPositionBottomRightButton->setText(QCoreApplication::translate("Main window", "Bottom right"));
    m_overlappingPositionGroup->setTitle(           QCoreApplication::translate("Main window", "Overlapping position"));
    m_overlappingPositionTopLeftButton->setText(    QCoreApplication::translate("Main window", "Top left"));
    m_overlappingPositionTopRightButton->setText(   QCoreApplication::translate("Main window", "Top right"));
    m_overlappingSizeGroup->setTitle(               QCoreApplication::translate("Main window", "Overlapping size"));
    m_overlappingWidthLabel->setText(               QCoreApplication::translate("Main window", "Width:"));
    m_paperBordersBottomLabel->setText(             QCoreApplication::translate("Main window", "Bottom"));
    m_paperBordersLeftLabel->setText(               QCoreApplication::translate("Main window", "Left"));
    m_paperBordersRightLabel->setText(              QCoreApplication::translate("Main window", "Right"));
    m_paperBordersTopLabel->setText(                QCoreApplication::translate("Main window", "Top"));
    m_paperCustomHeightLabel->setText(              QCoreApplication::translate("Main window", "Height:"));
    m_paperCustomWidthLabel->setText(               QCoreApplication::translate("Main window", "Width:"));
    m_paperFormatLabel->setText(                    QCoreApplication::translate("Main window", "Format:"));
    m_paperFormatTypeTabs->setTabText(m_paperFormatTypeTabs->indexOf(m_paperFormatCustomTab),
                                                    QCoreApplication::translate("Main window", "Custom"));
    m_paperFormatTypeTabs->setTabText(m_paperFormatTypeTabs->indexOf(m_paperFormatStandardTab),
                                                    QCoreApplication::translate("Main window", "Standard"));
    m_paperOrientationLabel->setText(               QCoreApplication::translate("Main window", "Orientation:"));
    m_paperOrientationLandscapeRadioButton->setText(QCoreApplication::translate("Main window", "Landscape"));
    m_paperOrientationPortraitRadioButton->setText( QCoreApplication::translate("Main window", "Portrait"));
    m_paperSizeGroup->setTitle(                     QCoreApplication::translate("Main window", "Paper size"));
    m_posterAbsoluteHeightLabel->setText(           QCoreApplication::translate("Main window", "Height:"));
    m_posterAbsoluteWidthLabel->setText(            QCoreApplication::translate("Main window", "Width:"));
    m_posterAlignmentGroup->setTitle(               QCoreApplication::translate("Main window", "Image alignment"));
    m_posterPagesHeightDimensionUnitLabel->setText( QCoreApplication::translate("Main window", "pages"));
    m_posterPagesHeightLabel->setText(              QCoreApplication::translate("Main window", "Height:"));
    m_posterPagesWidthDimensionUnitLabel->setText(  QCoreApplication::translate("Main window", "pages"));
    m_posterPagesWidthLabel->setText(               QCoreApplication::translate("Main window", "Width:"));
    m_posterPercentualSizeLabel->setText(           QCoreApplication::translate("Main window", "Size:"));
    m_posterSizeAbsoluteRadioButton->setText(       QCoreApplication::translate("Main window", "Absolute size:"));
    m_posterSizeGroup->setTitle(                    QCoreApplication::translate("Main window", "Image size"));
    m_posterSizeInPagesRadioButton->setText(        QCoreApplication::translate("Main window", "Size in pages:"));
    m_posterSizePercentualRadioButton->setText(     QCoreApplication::translate("Main window", "Size in percent:"));
    m_stepPrevButton->setText(                      QCoreApplication::translate("Main window", "Back"));
    m_savePosterGroup->setTitle(                    QCoreApplication::translate("Main window", "Save the poster"));
    retranslateUiWithDimensionUnit();
}

void MainWindow::retranslateUiWithDimensionUnit()
{
    const QString unitOfLength = QString(QLatin1String(" (%1)")).arg(m_currentUnitOfLength);
    m_imageInformationSizeLabel->setText(           QCoreApplication::translate("Main window", "Size (in %1):").arg(m_currentUnitOfLength));
    m_paperBordersGroup->setTitle(                  QCoreApplication::translate("Main window", "Borders") + unitOfLength);
}

void MainWindow::setPaperFormat(const QString &format)
{
    const int index = m_paperFormatComboBox->findData(format, Qt::DisplayRole);
    m_paperFormatComboBox->setCurrentIndex(index);
}

void MainWindow::setPaperOrientation(QPrinter::Orientation orientation)
{
    (
        orientation == QPrinter::Landscape?m_paperOrientationLandscapeRadioButton
        :m_paperOrientationPortraitRadioButton
    )->setChecked(true);
}

void MainWindow::setPaperBorderTop(double border)
{
    m_paperBorderTopInput->setValue(border);
}

void MainWindow::setPaperBorderRight(double border)
{
    m_paperBorderRightInput->setValue(border);
}

void MainWindow::setPaperBorderBottom(double border)
{
    m_paperBorderBottomInput->setValue(border);
}

void MainWindow::setPaperBorderLeft(double border)
{
    m_paperBorderLeftInput->setValue(border);
}

void MainWindow::setCustomPaperSize(const QSizeF &size)
{
    m_paperCustomWidthSpinner->setValue(size.width());
    m_paperCustomHeightSpinner->setValue(size.height());
}

void MainWindow::setUseCustomPaperSize(bool useIt)
{
    m_paperFormatTypeTabs->setCurrentWidget(useIt?m_paperFormatCustomTab:m_paperFormatStandardTab);
}

void MainWindow::setOverlappingWidth(double width)
{
    m_overlappingWidthInput->setValue(width);
}

void MainWindow::setOverlappingHeight(double height)
{
    m_overlappingHeightInput->setValue(height);
}

void MainWindow::setOverlappingPosition(Qt::Alignment position)
{
    if (m_overlappingButtons.contains(position))
        m_overlappingButtons.value(position)->setChecked(true);
}

void MainWindow::setPosterWidthAbsolute(double width)
{
    m_posterAbsoluteWidthInput->setValue(width);
}

void MainWindow::setPosterHeightAbsolute(double height)
{
    m_posterAbsoluteHeightInput->setValue(height);
}

void MainWindow::setPosterWidthPages(double width)
{
    m_posterPagesWidthInput->setValue(width);
}

void MainWindow::setPosterHeightPages(double height)
{
    m_posterPagesHeightInput->setValue(height);
}

void MainWindow::setPosterSizePercentual(double percent)
{
    m_posterPercentualSizeInput->setValue(percent);
}

void MainWindow::setPosterSizeMode(Types::PosterSizeModes mode)
{
    (
        mode == Types::PosterSizeModeAbsolute?m_posterSizeAbsoluteRadioButton
        :mode == Types::PosterSizeModePages?m_posterSizeInPagesRadioButton
        :m_posterSizePercentualRadioButton
    )->setChecked(true);
    updatePosterSizeGroupsState();
}

void MainWindow::setPosterAlignment(Qt::Alignment alignment)
{
    if (m_alignmentButtons.contains(alignment))
        m_alignmentButtons.value(alignment)->setChecked(true);
}

void MainWindow::setLaunchPDFApplication(bool launch)
{
    m_launchPDFApplicationCheckBox->setCheckState(launch?Qt::Checked:Qt::Unchecked);
}

void MainWindow::updatePreview()
{
    m_paintCanvas->repaint();
}

void MainWindow::showImageFileName(const QString &fileName)
{
    m_inputFileNameLabel->setText(QFileInfo(fileName).fileName());
}

void MainWindow::updateImageInfoFields(const QSize &inputImageSizeInPixels, const QSizeF &imageSize, double verticalDpi, double horizontalDpi, Types::ColorTypes colorType, int bitsPerPixel)
{
    Q_UNUSED(horizontalDpi)

    m_imageInformationSizeInPixelsValue->setText(QString("%1 x %2").arg(inputImageSizeInPixels.width()).arg(inputImageSizeInPixels.height()));
    m_imageInformationSizeValue->setText(QString("%1 x %2").arg(imageSize.width(), 0, 'f', 2).arg(imageSize.height(), 0, 'f', 2));
    m_imageInformationResolutionValue->setText(QString("%1 dpi").arg(verticalDpi, 0, 'f', 1));
    const QString colorTypeString = (
        colorType==Types::ColorTypeMonochrome?QCoreApplication::translate("Main window", "Monochrome"):
        colorType==Types::ColorTypeGreyscale?QCoreApplication::translate("Main window", "Gray scale"):
        colorType==Types::ColorTypePalette?QCoreApplication::translate("Main window", "Palette"):
        colorType==Types::ColorTypeRGB?QCoreApplication::translate("Main window", "RGB"):
        colorType==Types::ColorTypeRGBA?QCoreApplication::translate("Main window", "RGBA"):
        /*colorType==ColorTypeCMYK?*/ QCoreApplication::translate("Main window", "CMYK")
    ) + QString(" %1bpp").arg(bitsPerPixel);
    m_imageInformationColorTypeValue->setText(colorTypeString);
    m_imageInfoGroup->setVisible(true);
    m_actionSavePoster->setEnabled(true);
    emit imageLoaded();
}

void MainWindow::setCurrentTranslation(const QString &translation)
{
    QAction *translationAction = NULL;
    translationAction = m_translationActions.value(translation);
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
    m_currentUnitOfLength = unit;
    foreach (QAction *action, m_unitOfLengthActions->actions()) {
        if (action->text() == unit) {
            action->setChecked(true);
            break;
        }
    }
    retranslateUiWithDimensionUnit();
    m_posterAbsoluteWidthDimensionUnitLabel->setText(unit);
    m_posterAbsoluteHeightDimensionUnitLabel->setText(unit);
    m_overlappingWidthDimensionUnitLabel->setText(unit);
    m_overlappingHeightDimensionUnitLabel->setText(unit);
    m_paperCustomWidthDimensionUnitLabel->setText(unit);
    m_paperCustomHeightDimensionUnitLabel->setText(unit);
}

void MainWindow::addAboutDialogAction(QAction *action)
{   
    m_menuAbout->addAction(action);
}

void MainWindow::setPrevButtonEnabled(bool enabled)
{
    m_stepPrevButton->setDisabled(!enabled);
}

void MainWindow::setNextButtonEnabled(bool enabled)
{
    m_stepNextButton->setDisabled(!enabled);
}

void MainWindow::setWizardStep(int step)
{
    m_steps->setCurrentIndex(step);
}

void MainWindow::setWizardStepDescription(const QString &number, const QString &description)
{
    m_stepNumberLabel->setText(number);
    m_stepDescriptionLabel->setText(description);
}

void MainWindow::setPreviewState(const QString &state)
{
    m_paintCanvas->setState(state);
}


void MainWindow::setPreviewImage(const QImage &image)
{
    m_paintCanvas->setImage(image);
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
    QTextBrowser *browser = new QTextBrowser;
    browser->setOpenExternalLinks(true);
    browser->document()->setDefaultStyleSheet(
        "dt {font-weight: bold;}"
        "dd {margin-left: 15px;}"
        "p {text-indent: 7px;}"
        "p, dd {margin-top: 0px; margin-bottom: 6px;}"
        "h2 {margin-top: 18px; margin-bottom: 6px;}");
    browser->setHtml(text);
    dialog->layout()->addWidget(browser);
    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted ()), dialog, SLOT(accept()));
    dialog->layout()->addWidget(buttonBox);
    dialog->show();
}

void MainWindow::handlePaperFormatTabChanged(int index)
{
    emit useCustomPaperSizeChanged(index == 1);
}

void MainWindow::handlePaperOrientationPortraitSelected()
{
    emit paperOrientationChanged(QPrinter::Portrait);
}

void MainWindow::handlePaperOrientationLandscapeSelected()
{
    emit paperOrientationChanged(QPrinter::Landscape);
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
    connect(m_stepNextButton,                       SIGNAL(clicked()),                  SIGNAL(nextButtonPressed()));
    connect(m_stepPrevButton,                       SIGNAL(clicked()),                  SIGNAL(prevButtonPressed()));
    connect(m_stepHelpButton,                       SIGNAL(clicked()),                  SIGNAL(wizardStepHelpSignal()));
    connect(m_paperFormatTypeTabs,                  SIGNAL(currentChanged(int)),        SLOT(handlePaperFormatTabChanged(int)));
    connect(m_paperFormatComboBox,                  SIGNAL(activated(const QString &)), SIGNAL(paperFormatChanged(const QString &)));
    connect(m_paperOrientationPortraitRadioButton,  SIGNAL(clicked()),                  SLOT(handlePaperOrientationPortraitSelected()));
    connect(m_paperOrientationLandscapeRadioButton, SIGNAL(clicked()),                  SLOT(handlePaperOrientationLandscapeSelected()));
    connect(m_paperCustomWidthSpinner,              SIGNAL(valueEdited(double)),        SIGNAL(paperCustomWidthChanged(double)));
    connect(m_paperCustomHeightSpinner,             SIGNAL(valueEdited(double)),        SIGNAL(paperCustomHeightChanged(double)));
    connect(m_paperBorderTopInput,                  SIGNAL(valueEdited(double)),        SIGNAL(paperBorderTopChanged(double)));
    connect(m_paperBorderRightInput,                SIGNAL(valueEdited(double)),        SIGNAL(paperBorderRightChanged(double)));
    connect(m_paperBorderBottomInput,               SIGNAL(valueEdited(double)),        SIGNAL(paperBorderBottomChanged(double)));
    connect(m_paperBorderLeftInput,                 SIGNAL(valueEdited(double)),        SIGNAL(paperBorderLeftChanged(double)));
    connect(m_actionLoadInputImage,                 SIGNAL(triggered()),                SIGNAL(loadImageSignal()));
    connect(m_imageLoadButton,                      SIGNAL(clicked()),                  SIGNAL(loadImageSignal()));
    connect(m_posterSizeAbsoluteRadioButton,        SIGNAL(clicked()),                  SLOT(updatePosterSizeGroupsState()));
    connect(m_posterSizeInPagesRadioButton,         SIGNAL(clicked()),                  SLOT(updatePosterSizeGroupsState()));
    connect(m_posterSizePercentualRadioButton,      SIGNAL(clicked()),                  SLOT(updatePosterSizeGroupsState()));
    connect(m_overlappingWidthInput,                SIGNAL(valueEdited(double)),        SIGNAL(overlappingWidthChanged(double)));
    connect(m_overlappingHeightInput,               SIGNAL(valueEdited(double)),        SIGNAL(overlappingHeightChanged(double)));
    QSignalMapper *overlappingMapper = new QSignalMapper(this);
    foreach (const Qt::Alignment alignment, m_overlappingButtons.keys()) {
        QAbstractButton *sender = m_overlappingButtons.value(alignment);
        connect(sender, SIGNAL(clicked()), overlappingMapper, SLOT(map()));
        overlappingMapper->setMapping(sender, alignment);
    }
    connect(overlappingMapper, SIGNAL(mapped(int)), SLOT(emitOverlappingPositionChange(int)));
    connect(m_posterAbsoluteWidthInput,             SIGNAL(valueEdited(double)),        SIGNAL(posterWidthAbsoluteChanged(double)));
    connect(m_posterAbsoluteHeightInput,            SIGNAL(valueEdited(double)),        SIGNAL(posterHeightAbsoluteChanged(double)));
    connect(m_posterPagesWidthInput,                SIGNAL(valueEdited(double)),        SIGNAL(posterWidthPagesChanged(double)));
    connect(m_posterPagesHeightInput,               SIGNAL(valueEdited(double)),        SIGNAL(posterHeightPagesChanged(double)));
    connect(m_posterPercentualSizeInput,            SIGNAL(valueEdited(double)),        SIGNAL(posterSizePercentualChanged(double)));
    QSignalMapper *alignmentMapper = new QSignalMapper(this);
    foreach (const Qt::Alignment alignment, m_alignmentButtons.keys()) {
        QAbstractButton *sender = m_alignmentButtons.value(alignment);
        connect(sender, SIGNAL(clicked()), alignmentMapper, SLOT(map()));
        alignmentMapper->setMapping(sender, alignment);
    }
    connect(alignmentMapper, SIGNAL(mapped(int)),   SLOT(emitPosterAlignmentChange(int)));
    connect(m_actionSavePoster,                     SIGNAL(triggered()),                SIGNAL(savePosterSignal()));
    connect(m_savePosterButton,                     SIGNAL(clicked()),                  SIGNAL(savePosterSignal()));
    connect(m_launchPDFApplicationCheckBox,         SIGNAL(toggled(bool)),              SIGNAL(launchPDFApplicationChanged(bool)));
    connect(m_paintCanvas,                          SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)));
    connect(m_actionPosteRazorWebSite,              SIGNAL(triggered()),                SIGNAL(openPosteRazorWebsiteSignal()));
    connect(m_actionAboutQt,                        SIGNAL(triggered()),                SLOT(showAboutQtDialog()));
    connect(m_actionAboutPosteRazor,                SIGNAL(triggered()),                SLOT(showAboutPosteRazorDialog()));
    connect(m_actionPosteRazorManual,               SIGNAL(triggered()),                SIGNAL(manualSignal()));
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

    QActionGroup *translationActions = new QActionGroup(m_menuSettings);
    connect (translationActions, SIGNAL(triggered(QAction*)), SLOT(handleTranslationAction(QAction*)));
    translationActions->setExclusive(true);
    QDir translationDir(":/Translations/");
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

    QStringList formats = Types::paperFormats().keys();
    formats.sort();
    m_paperFormatComboBox->addItems(formats);
}

void MainWindow::emitOverlappingPositionChange(int alignmentInt) const
{
    emit overlappingPositionChanged((Qt::Alignment)alignmentInt);
}

void MainWindow::emitPosterAlignmentChange(int alignmentInt) const
{
    emit posterAlignmentChanged((Qt::Alignment)alignmentInt);
}

void MainWindow::updatePosterSizeGroupsState()
{
    const bool absolute = m_posterSizeAbsoluteRadioButton->isChecked();
    m_posterAbsoluteWidthLabel->setEnabled(absolute);
    m_posterAbsoluteWidthInput->setEnabled(absolute);
    m_posterAbsoluteWidthDimensionUnitLabel->setEnabled(absolute);
    m_posterAbsoluteHeightLabel->setEnabled(absolute);
    m_posterAbsoluteHeightInput->setEnabled(absolute);
    m_posterAbsoluteHeightDimensionUnitLabel->setEnabled(absolute);

    const bool inPages = m_posterSizeInPagesRadioButton->isChecked();
    m_posterPagesWidthLabel->setEnabled(inPages);
    m_posterPagesWidthInput->setEnabled(inPages);
    m_posterPagesWidthDimensionUnitLabel->setEnabled(inPages);
    m_posterPagesHeightLabel->setEnabled(inPages);
    m_posterPagesHeightInput->setEnabled(inPages);
    m_posterPagesHeightDimensionUnitLabel->setEnabled(inPages);

    const bool percentual = m_posterSizePercentualRadioButton->isChecked();
    m_posterPercentualSizeLabel->setEnabled(percentual);
    m_posterPercentualSizeInput->setEnabled(percentual);
    m_posterPercentualSizeUnitLabel->setEnabled(percentual);
}

void MainWindow::showAboutQtDialog() const
{
    QApplication::aboutQt();
}

void MainWindow::showAboutPosteRazorDialog()
{
    const QString title = Types::cleanString(QCoreApplication::translate("Help", "&About PosteRazor"));
    const QString webpageAnchor = QString(QLatin1String("<a href=\"%1\">posterazor.sourceforge.net</a>"))
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
        QLatin1String("<h2>Translations</h2>"
            "<p>In order of appearance</p>"
            "<dl>"
            "<dt>English</dt><dd>Alessandro Portale (author)</dd>"
            "<dt>German</dt><dd>Alessandro Portale (author)</dd>"
            "<dt>Polish</dt><dd>Grzegorz Wacikowski</dd>"
            "<dt>French</dt><dd>Martin Loyer</dd>"
            "<dt>Italian</dt><dd>Stefano Nosei</dd>"
            "<dt>Dutch/Belgian</dt><dd>Erik Wijkamp</dd>"
            "<dt>Spanish</dt><dd><a href=\"http://hispanicoweb.net/\">Hispánico Web</a></dd>"
            "<dt>Brazilian Portuguese</dt><dd>Éderson Gomes dos Santos</dd>"
            "<dt>European Portuguese</dt><dd>Helder Correia</dd>"
            "<dt>Simplified Chinese</dt><dd>Sun Li</dd>"
            "<dt>Finnish</dt><dd>Olli</dd>"
            "</dl>") +
        QLatin1String("<h2>License</h2>"
            "<p>PosteRazor - Make your own poster!<br/>"
            "posterazor.sourceforge.net<br/>"
            "Copyright (C) 2005-2008 by Alessandro Portale</p>"
            "<p>This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p>"
            "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>"
            "<p>You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.</p>");
    showManual(title, aboutText);
}
