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

#include "wizard.h"

#include <QDialogButtonBox>
#include <QFileInfo>
#include <QMessageBox>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QtDebug>

Wizard::Wizard(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    m_imageInfoGroup->setVisible(false);
    m_imageLoadButton->setIcon(QApplication::style()->standardPixmap(QStyle::SP_DirOpenIcon));
    m_stepHelpButton->setMinimumSize(m_imageLoadButton->sizeHint());
    m_savePosterButton->setIcon(QApplication::style()->standardPixmap(QStyle::SP_DialogSaveButton));

    m_overlappingButtons = {
        {Qt::AlignTop | Qt::AlignLeft,          m_overlappingPositionTopLeftButton      },
        {Qt::AlignTop | Qt::AlignRight,         m_overlappingPositionTopRightButton     },
        {Qt::AlignBottom | Qt::AlignLeft,       m_overlappingPositionBottomLeftButton   },
        {Qt::AlignBottom | Qt::AlignRight,      m_overlappingPositionBottomRightButton  }
    };

    m_alignmentButtons = {
        {Qt::AlignTop | Qt::AlignLeft,          m_posterAlignmentTopLeftButton          },
        {Qt::AlignTop | Qt::AlignHCenter,       m_posterAlignmentTopButton              },
        {Qt::AlignTop | Qt::AlignRight,         m_posterAlignmentTopRightButton         },
        {Qt::AlignVCenter | Qt::AlignLeft,      m_posterAlignmentLeftButton             },
        {Qt::AlignCenter,                       m_posterAlignmentCenterButton           },
        {Qt::AlignVCenter | Qt::AlignRight,     m_posterAlignmentRightButton            },
        {Qt::AlignBottom | Qt::AlignLeft,       m_posterAlignmentBottomLeftButton       },
        {Qt::AlignBottom | Qt::AlignHCenter,    m_posterAlignmentBottomButton           },
        {Qt::AlignBottom | Qt::AlignRight,      m_posterAlignmentBottomRightButton      }
    };

    m_steps->setCurrentIndex(0);
    createConnections();
    populateUI();
    updatePosterSizeGroupsState();
    retranslateUi();

#ifdef Q_OS_WASM
    m_launchPDFApplicationCheckBox->hide();
#endif // Q_OS_WASM
}

void Wizard::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi();
    QWidget::changeEvent(event);
}

void Wizard::retranslateUi()
{
    m_imageInfoGroup->setTitle(                     QCoreApplication::translate("Main window", "Image Informations"));
    m_imageInformationColorTypeLabel->setText(      QCoreApplication::translate("Main window", "Color type:"));
    m_imageInformationResolutionLabel->setText(     QCoreApplication::translate("Main window", "Resolution:"));
    m_imageInformationSizeInPixelsLabel->setText(   QCoreApplication::translate("Main window", "Size (in pixels):"));
    m_inputImageGroup->setTitle(                    QCoreApplication::translate("Main window", "Input Image"));
    m_launchPDFApplicationCheckBox->setText(        QCoreApplication::translate("Main window", "Open PDF after saving"));
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

void Wizard::retranslateUiWithDimensionUnit()
{
    const QString unitOfLength = QString::fromLatin1(" (%1)").arg(m_currentUnitOfLength);
    m_imageInformationSizeLabel->setText(           QCoreApplication::translate("Main window", "Size (in %1):").arg(m_currentUnitOfLength));
    m_paperBordersGroup->setTitle(                  QCoreApplication::translate("Main window", "Borders") + unitOfLength);
}

void Wizard::setPaperFormat(const QString &format)
{
    const int index = m_paperFormatComboBox->findData(format, Qt::DisplayRole);
    m_paperFormatComboBox->setCurrentIndex(index);
}

void Wizard::setPaperOrientation(QPageLayout::Orientation orientation)
{
    (
        orientation == QPageLayout::Landscape ? m_paperOrientationLandscapeRadioButton
        : m_paperOrientationPortraitRadioButton
    )->setChecked(true);
}

void Wizard::setPaperBorderTop(qreal border)
{
    m_paperBorderTopInput->setValue(border);
}

void Wizard::setPaperBorderRight(qreal border)
{
    m_paperBorderRightInput->setValue(border);
}

void Wizard::setPaperBorderBottom(qreal border)
{
    m_paperBorderBottomInput->setValue(border);
}

void Wizard::setPaperBorderLeft(qreal border)
{
    m_paperBorderLeftInput->setValue(border);
}

void Wizard::setCustomPaperSize(const QSizeF &size)
{
    m_paperCustomWidthSpinner->setValue(size.width());
    m_paperCustomHeightSpinner->setValue(size.height());
}

void Wizard::setUseCustomPaperSize(bool useIt)
{
    m_paperFormatTypeTabs->setCurrentWidget(useIt ? m_paperFormatCustomTab : m_paperFormatStandardTab);
}

void Wizard::setOverlappingWidth(qreal width)
{
    m_overlappingWidthInput->setValue(width);
}

void Wizard::setOverlappingHeight(qreal height)
{
    m_overlappingHeightInput->setValue(height);
}

void Wizard::setOverlappingPosition(Qt::Alignment position)
{
    if (m_overlappingButtons.contains(position))
        m_overlappingButtons.value(position)->setChecked(true);
}

void Wizard::setPosterWidthAbsolute(qreal width)
{
    m_posterAbsoluteWidthInput->setValue(width);
}

void Wizard::setPosterHeightAbsolute(qreal height)
{
    m_posterAbsoluteHeightInput->setValue(height);
}

void Wizard::setPosterWidthPages(qreal width)
{
    m_posterPagesWidthInput->setValue(width);
}

void Wizard::setPosterHeightPages(qreal height)
{
    m_posterPagesHeightInput->setValue(height);
}

void Wizard::setPosterSizePercentual(qreal percent)
{
    m_posterPercentualSizeInput->setValue(percent);
}

void Wizard::setPosterSizeMode(Types::PosterSizeModes mode)
{
    (
        mode == Types::PosterSizeModeAbsolute ? m_posterSizeAbsoluteRadioButton
        : mode == Types::PosterSizeModePages ? m_posterSizeInPagesRadioButton
        : m_posterSizePercentualRadioButton
    )->setChecked(true);
    updatePosterSizeGroupsState();
}

void Wizard::setPosterSizeModeAvailable(Types::PosterSizeModes mode, bool available)
{
    QList<QWidget *> widgets;
    switch (mode) {
        case Types::PosterSizeModeAbsolute:
            widgets << m_posterSizeAbsoluteRadioButton
                    << m_posterAbsoluteWidthInput << m_posterAbsoluteHeightInput
                    << m_posterAbsoluteWidthLabel << m_posterAbsoluteHeightLabel
                    << m_posterAbsoluteWidthDimensionUnitLabel << m_posterAbsoluteHeightDimensionUnitLabel;
        break;
        case Types::PosterSizeModePages:
            widgets << m_posterSizeInPagesRadioButton
                    << m_posterPagesWidthInput << m_posterPagesHeightInput
                    << m_posterPagesWidthLabel << m_posterPagesHeightLabel
                    << m_posterPagesWidthDimensionUnitLabel << m_posterPagesHeightDimensionUnitLabel;
        break;
        case Types::PosterSizeModePercentual:
        default:
            widgets << m_posterSizePercentualRadioButton << m_posterPercentualSizeInput
                    << m_posterPercentualSizeLabel << m_posterPercentualSizeUnitLabel;
        break;
    }
    foreach (QWidget *widget, widgets)
        widget->setVisible(available);
}

void Wizard::setPosterAlignment(Qt::Alignment alignment)
{
    if (m_alignmentButtons.contains(alignment))
        m_alignmentButtons.value(alignment)->setChecked(true);
}

void Wizard::setLaunchPDFApplication(bool launch)
{
    m_launchPDFApplicationCheckBox->setCheckState(launch ? Qt::Checked : Qt::Unchecked);
}

void Wizard::updatePreview()
{
    m_paintCanvas->repaint();
}

void Wizard::showImageFileName(const QString &fileName)
{
    m_inputFileNameLabel->setText(QFileInfo(fileName).fileName());
}

void Wizard::updateImageInfoFields(const QSize &inputImageSizeInPixels, const QSizeF &imageSize, qreal verticalDpi, qreal horizontalDpi, Types::ColorTypes colorType, int bitsPerPixel)
{
    Q_UNUSED(horizontalDpi)

    m_imageInformationSizeInPixelsValue->setText(QString::fromLatin1("%1 x %2").arg(inputImageSizeInPixels.width()).arg(inputImageSizeInPixels.height()));
    m_imageInformationSizeValue->setText(QString::fromLatin1("%1 x %2").arg(imageSize.width(), 0, 'f', 2).arg(imageSize.height(), 0, 'f', 2));
    m_imageInformationResolutionValue->setText(QString::fromLatin1("%1 dpi").arg(verticalDpi, 0, 'f', 1));
    const QString colorTypeString = (
        colorType == Types::ColorTypeMonochrome ? QCoreApplication::translate("Main window", "Monochrome")
        : colorType == Types::ColorTypeGreyscale ? QCoreApplication::translate("Main window", "Gray scale")
        : colorType == Types::ColorTypePalette ? QCoreApplication::translate("Main window", "Palette")
        : colorType == Types::ColorTypeRGB ? QCoreApplication::translate("Main window", "RGB")
        : colorType == Types::ColorTypeRGBA ? QCoreApplication::translate("Main window", "RGBA")
        : /*colorType == ColorTypeCMYK?*/ QCoreApplication::translate("Main window", "CMYK")
    ) + QString::fromLatin1(" %1bpp").arg(bitsPerPixel);
    m_imageInformationColorTypeValue->setText(colorTypeString);
    m_imageInfoGroup->setVisible(true);
    emit imageLoaded();
}

void Wizard::setCurrentUnitOfLength(const QString &unit)
{
    m_currentUnitOfLength = unit;
    retranslateUiWithDimensionUnit();
    m_posterAbsoluteWidthDimensionUnitLabel->setText(m_currentUnitOfLength);
    m_posterAbsoluteHeightDimensionUnitLabel->setText(m_currentUnitOfLength);
    m_overlappingWidthDimensionUnitLabel->setText(m_currentUnitOfLength);
    m_overlappingHeightDimensionUnitLabel->setText(m_currentUnitOfLength);
    m_paperCustomWidthDimensionUnitLabel->setText(m_currentUnitOfLength);
    m_paperCustomHeightDimensionUnitLabel->setText(m_currentUnitOfLength);
}

void Wizard::setPrevButtonEnabled(bool enabled)
{
    m_stepPrevButton->setEnabled(enabled);
}

void Wizard::setNextButtonEnabled(bool enabled)
{
    m_stepNextButton->setEnabled(enabled);
}

void Wizard::setPosterSavingEnabled(bool enabled)
{
    m_savePosterButton->setEnabled(enabled);
}

void Wizard::setWizardStep(int step)
{
    m_steps->setCurrentIndex(step);
}

void Wizard::setWizardStepDescription(const QString &number, const QString &description)
{
    m_stepNumberLabel->setText(number);
    m_stepDescriptionLabel->setText(description);
}

void Wizard::setPreviewState(const QString &state)
{
    QString actualState = state;
    if (actualState == QLatin1String("poster")) {
        actualState.append(QLatin1String(" overlapped"));
    }
    m_paintCanvas->setState(actualState);
}

void Wizard::showWizardStepHelp(const QString &title, const QString &text)
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

void Wizard::setPreviewImage(const QImage &image)
{
    m_paintCanvas->setImage(image);
}

void Wizard::handlePaperFormatTabChanged(int index)
{
    emit useCustomPaperSizeChanged(index == 1);
}

void Wizard::handlePaperOrientationPortraitSelected()
{
    emit paperOrientationChanged(QPageLayout::Portrait);
}

void Wizard::handlePaperOrientationLandscapeSelected()
{
    emit paperOrientationChanged(QPageLayout::Landscape);
}

void Wizard::createConnections()
{
    connect(m_stepNextButton,                       SIGNAL(clicked()),                  SIGNAL(nextButtonPressed()));
    connect(m_stepPrevButton,                       SIGNAL(clicked()),                  SIGNAL(prevButtonPressed()));
    connect(m_stepHelpButton,                       SIGNAL(clicked()),                  SIGNAL(wizardStepHelpSignal()));
    connect(m_paperFormatTypeTabs,                  SIGNAL(currentChanged(int)),        SLOT(handlePaperFormatTabChanged(int)));
    connect(m_paperFormatComboBox,                  SIGNAL(textActivated(const QString &)), SIGNAL(paperFormatChanged(const QString &)));
    connect(m_paperOrientationPortraitRadioButton,  SIGNAL(clicked()),                  SLOT(handlePaperOrientationPortraitSelected()));
    connect(m_paperOrientationLandscapeRadioButton, SIGNAL(clicked()),                  SLOT(handlePaperOrientationLandscapeSelected()));
    connect(m_paperCustomWidthSpinner,              SIGNAL(valueEdited(qreal)),        SIGNAL(paperCustomWidthChanged(qreal)));
    connect(m_paperCustomHeightSpinner,             SIGNAL(valueEdited(qreal)),        SIGNAL(paperCustomHeightChanged(qreal)));
    connect(m_paperBorderTopInput,                  SIGNAL(valueEdited(qreal)),        SIGNAL(paperBorderTopChanged(qreal)));
    connect(m_paperBorderRightInput,                SIGNAL(valueEdited(qreal)),        SIGNAL(paperBorderRightChanged(qreal)));
    connect(m_paperBorderBottomInput,               SIGNAL(valueEdited(qreal)),        SIGNAL(paperBorderBottomChanged(qreal)));
    connect(m_paperBorderLeftInput,                 SIGNAL(valueEdited(qreal)),        SIGNAL(paperBorderLeftChanged(qreal)));
    connect(m_imageLoadButton,                      SIGNAL(clicked()),                  SIGNAL(loadImageSignal()));
    connect(m_posterSizeAbsoluteRadioButton,        SIGNAL(clicked()),                  SLOT(updatePosterSizeGroupsState()));
    connect(m_posterSizeInPagesRadioButton,         SIGNAL(clicked()),                  SLOT(updatePosterSizeGroupsState()));
    connect(m_posterSizePercentualRadioButton,      SIGNAL(clicked()),                  SLOT(updatePosterSizeGroupsState()));
    connect(m_overlappingWidthInput,                SIGNAL(valueEdited(qreal)),        SIGNAL(overlappingWidthChanged(qreal)));
    connect(m_overlappingHeightInput,               SIGNAL(valueEdited(qreal)),        SIGNAL(overlappingHeightChanged(qreal)));
    auto overlappingMapper = new QSignalMapper(this);
    for (auto it = m_overlappingButtons.cbegin(), end = m_overlappingButtons.cend(); it != end; ++it) {
        QAbstractButton *sender = it.value();
        connect(sender, SIGNAL(clicked()), overlappingMapper, SLOT(map()));
        overlappingMapper->setMapping(sender, it.key());
    }
    connect(overlappingMapper, SIGNAL(mappedInt(int)), SLOT(emitOverlappingPositionChange(int)));
    connect(m_posterAbsoluteWidthInput,             SIGNAL(valueEdited(qreal)),        SIGNAL(posterWidthAbsoluteChanged(qreal)));
    connect(m_posterAbsoluteHeightInput,            SIGNAL(valueEdited(qreal)),        SIGNAL(posterHeightAbsoluteChanged(qreal)));
    connect(m_posterPagesWidthInput,                SIGNAL(valueEdited(qreal)),        SIGNAL(posterWidthPagesChanged(qreal)));
    connect(m_posterPagesHeightInput,               SIGNAL(valueEdited(qreal)),        SIGNAL(posterHeightPagesChanged(qreal)));
    connect(m_posterPercentualSizeInput,            SIGNAL(valueEdited(qreal)),        SIGNAL(posterSizePercentualChanged(qreal)));
    auto alignmentMapper = new QSignalMapper(this);
    for (auto it = m_alignmentButtons.cbegin(), end = m_alignmentButtons.cend(); it != end; ++it) {
        QAbstractButton *sender = it.value();
        connect(sender, SIGNAL(clicked()), alignmentMapper, SLOT(map()));
        alignmentMapper->setMapping(sender, it.key());
    }
    connect(alignmentMapper, SIGNAL(mappedInt(int)), SLOT(emitPosterAlignmentChange(int)));
    connect(m_savePosterButton,                     SIGNAL(clicked()),                  SIGNAL(savePosterSignal()));
    connect(m_launchPDFApplicationCheckBox,         SIGNAL(toggled(bool)),              SIGNAL(launchPDFApplicationChanged(bool)));
    connect(m_paintCanvas,                          SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)));
}

void Wizard::populateUI()
{
    QStringList formats = Types::paperFormats().keys();
    formats.sort();
    m_paperFormatComboBox->addItems(formats);
}

void Wizard::emitOverlappingPositionChange(int alignmentInt) const
{
    emit overlappingPositionChanged((Qt::Alignment)alignmentInt);
}

void Wizard::emitPosterAlignmentChange(int alignmentInt) const
{
    emit posterAlignmentChanged((Qt::Alignment)alignmentInt);
}

void Wizard::updatePosterSizeGroupsState()
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
