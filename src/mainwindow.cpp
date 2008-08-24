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

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    setupUi(this);

    m_unitOfLengthActions = new QActionGroup(m_menuSettings);

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

    setWindowTitle(QCoreApplication::applicationName() + QLatin1Char(' ') + QCoreApplication::applicationVersion());
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
    m_actionAboutQt->setText(                       QCoreApplication::translate("PosteRazorDialog", "&About Qt"));
    m_imageInfoGroup->setTitle(                     QCoreApplication::translate("PosteRazorDialog", "Image Informations"));
    m_imageInformationColorTypeLabel->setText(      QCoreApplication::translate("PosteRazorDialog", "Color type:"));
    m_imageInformationResolutionLabel->setText(     QCoreApplication::translate("PosteRazorDialog", "Resolution:"));
    m_imageInformationSizeInPixelsLabel->setText(   QCoreApplication::translate("PosteRazorDialog", "Size (in pixels):"));
    m_imageInformationSizeLabel->setText(           QCoreApplication::translate("PosteRazorDialog", "Size (in %1):").arg(m_currentUnitOfLength));
    m_inputImageGroup->setTitle(                    QCoreApplication::translate("PosteRazorDialog", "Input Image"));
    m_launchPDFApplicationCheckBox->setText(        QCoreApplication::translate("PosteRazorDialog", "Open PDF after saving"));
    m_menuFile->setTitle(                           QCoreApplication::translate("PosteRazorDialog", "&File"));
    m_menuSettings->setTitle(                       QCoreApplication::translate("PosteRazorDialog", "&Settings"));
    m_nextButton->setText(                          QCoreApplication::translate("PosteRazorDialog", "Next"));
    m_overlappingHeightLabel->setText(              QCoreApplication::translate("PosteRazorDialog", "Height:"));
    m_overlappingPositionBottomLeftButton->setText( QCoreApplication::translate("PosteRazorDialog", "Bottom left"));
    m_overlappingPositionBottomRightButton->setText(QCoreApplication::translate("PosteRazorDialog", "Bottom right"));
    m_overlappingPositionGroup->setTitle(           QCoreApplication::translate("PosteRazorDialog", "Overlapping position"));
    m_overlappingPositionTopLeftButton->setText(    QCoreApplication::translate("PosteRazorDialog", "Top left"));
    m_overlappingPositionTopRightButton->setText(   QCoreApplication::translate("PosteRazorDialog", "Top right"));
    m_overlappingSizeGroup->setTitle(               QCoreApplication::translate("PosteRazorDialog", "Overlapping size"));
    m_overlappingWidthLabel->setText(               QCoreApplication::translate("PosteRazorDialog", "Width:"));
    m_paperBordersBottomLabel->setText(             QCoreApplication::translate("PosteRazorDialog", "Bottom"));
    m_paperBordersGroup->setTitle(                  QCoreApplication::translate("PosteRazorDialog", "Borders (%1)").arg(m_currentUnitOfLength));
    m_paperBordersLeftLabel->setText(               QCoreApplication::translate("PosteRazorDialog", "Left"));
    m_paperBordersRightLabel->setText(              QCoreApplication::translate("PosteRazorDialog", "Right"));
    m_paperBordersTopLabel->setText(                QCoreApplication::translate("PosteRazorDialog", "Top"));
    m_paperCustomHeightLabel->setText(              QCoreApplication::translate("PosteRazorDialog", "Height:"));
    m_paperCustomWidthLabel->setText(               QCoreApplication::translate("PosteRazorDialog", "Width:"));
    m_paperFormatLabel->setText(                    QCoreApplication::translate("PosteRazorDialog", "Format:"));
    m_paperFormatTypeTabs->setTabText(m_paperFormatTypeTabs->indexOf(m_paperFormatCustomTab),
                                                    QCoreApplication::translate("PosteRazorDialog", "Custom"));
    m_paperFormatTypeTabs->setTabText(m_paperFormatTypeTabs->indexOf(m_paperFormatStandardTab),
                                                    QCoreApplication::translate("PosteRazorDialog", "Standard"));
    m_paperOrientationLabel->setText(               QCoreApplication::translate("PosteRazorDialog", "Orientation:"));
    m_paperOrientationLandscapeRadioButton->setText(QCoreApplication::translate("PosteRazorDialog", "Landscape"));
    m_paperOrientationPortraitRadioButton->setText( QCoreApplication::translate("PosteRazorDialog", "Portrait"));
    m_paperSizeGroup->setTitle(                     QCoreApplication::translate("PosteRazorDialog", "Paper size"));
    m_posterAbsoluteHeightLabel->setText(           QCoreApplication::translate("PosteRazorDialog", "Height:"));
    m_posterAbsoluteWidthLabel->setText(            QCoreApplication::translate("PosteRazorDialog", "Width:"));
    m_posterAlignmentGroup->setTitle(               QCoreApplication::translate("PosteRazorDialog", "Image alignment"));
    m_posterPagesHeightDimensionUnitLabel->setText( QCoreApplication::translate("PosteRazorDialog", "pages"));
    m_posterPagesHeightLabel->setText(              QCoreApplication::translate("PosteRazorDialog", "Height:"));
    m_posterPagesWidthDimensionUnitLabel->setText(  QCoreApplication::translate("PosteRazorDialog", "pages"));
    m_posterPagesWidthLabel->setText(               QCoreApplication::translate("PosteRazorDialog", "Width:"));
    m_posterPercentualSizeLabel->setText(           QCoreApplication::translate("PosteRazorDialog", "Size:"));
    m_posterSizeAbsoluteRadioButton->setText(       QCoreApplication::translate("PosteRazorDialog", "Absolute size:"));
    m_posterSizeGroup->setTitle(                    QCoreApplication::translate("PosteRazorDialog", "Image size"));
    m_posterSizeInPagesRadioButton->setText(        QCoreApplication::translate("PosteRazorDialog", "Size in pages:"));
    m_posterSizePercentualRadioButton->setText(     QCoreApplication::translate("PosteRazorDialog", "Size in percent:"));
    m_prevButton->setText(                          QCoreApplication::translate("PosteRazorDialog", "Back"));
    m_savePosterButton->setText(                    QCoreApplication::translate("PosteRazorDialog", "Save the poster"));
    m_savePosterGroup->setTitle(                    QCoreApplication::translate("PosteRazorDialog", "Save the poster"));
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
        colorType==Types::ColorTypeMonochrome?QCoreApplication::translate("PosteRazorDialog", "Monochrome"):
        colorType==Types::ColorTypeGreyscale?QCoreApplication::translate("PosteRazorDialog", "Gray scale"):
        colorType==Types::ColorTypePalette?QCoreApplication::translate("PosteRazorDialog", "Palette"):
        colorType==Types::ColorTypeRGB?QCoreApplication::translate("PosteRazorDialog", "RGB"):
        colorType==Types::ColorTypeRGBA?QCoreApplication::translate("PosteRazorDialog", "RGBA"):
        /*colorType==ColorTypeCMYK?*/ QCoreApplication::translate("PosteRazorDialog", "CMYK")
    ) + QString(" %1bpp").arg(bitsPerPixel);
    m_imageInformationColorTypeValue->setText(colorTypeString);
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
    retranslateUi();
    m_posterAbsoluteWidthDimensionUnitLabel->setText(unit);
    m_posterAbsoluteHeightDimensionUnitLabel->setText(unit);
    m_overlappingWidthDimensionUnitLabel->setText(unit);
    m_overlappingHeightDimensionUnitLabel->setText(unit);
    m_paperCustomWidthDimensionUnitLabel->setText(unit);
    m_paperCustomHeightDimensionUnitLabel->setText(unit);
}

void MainWindow::setPrevButtonEnabled(bool enabled)
{
    m_prevButton->setDisabled(!enabled);
}

void MainWindow::setNextButtonEnabled(bool enabled)
{
    m_nextButton->setDisabled(!enabled);
}

void MainWindow::setWizardStep(int step)
{
    m_steps->setCurrentIndex(step);
}

void MainWindow::setPreviewState(const QString &state)
{
    m_paintCanvas->setState(state);
}

void MainWindow::setPreviewImage(const QImage &image)
{
    m_paintCanvas->setImage(image);
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
    connect(m_nextButton,                           SIGNAL(clicked()),                  SIGNAL(nextButtonPressed()));
    connect(m_prevButton,                           SIGNAL(clicked()),                  SIGNAL(prevButtonPressed()));
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
    connect(m_savePosterButton,                     SIGNAL(clicked()),                  SIGNAL(savePosterSignal()));
    connect(m_launchPDFApplicationCheckBox,         SIGNAL(toggled(bool)),              SIGNAL(launchPDFApplicationChanged(bool)));
    connect(m_paintCanvas,                          SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)));
    connect(m_actionAboutQt,                        SIGNAL(triggered()),                SLOT(showAboutQtDialog()));
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
    foreach (const QString &translation, translationDir.entryList(QDir::Files)) {
        QTranslator translator;
        translator.load(translation);
        QAction *languageAction = translationActions->addAction(translator.translate("PosteRazorDialog", "Language name"));
        const QString localeString(QFileInfo(translation).baseName());
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
    m_posterPagesHeightLabel->setEnabled(inPages);
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
