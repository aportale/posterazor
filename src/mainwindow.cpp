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
#include <QUrl>
#include <QDesktopServices>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupUi(this);

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

	m_steps->setCurrentIndex(0);
	createConnections();
	populateUI();

	updatePosterSizeGroupsState();
}

MainWindow::~MainWindow()
{
//	QSettings settings;
//	m_posteRazorController->writeSettings(&settings);
}

void MainWindow::setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
	Q_UNUSED(unit)
}

void MainWindow::setPaperFormat(const QString &format)
{
	const int index = m_paperFormatComboBox->findData(format, Qt::DisplayRole);
	m_paperFormatComboBox->setCurrentIndex(index);
}

void MainWindow::setPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
	(
		orientation == PaperFormats::ePaperOrientationLandscape?m_paperOrientationLandscapeRadioButton
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

void MainWindow::setCustomPaperWidth(double width)
{
	m_paperCustomWidthSpinner->setValue(width);
}

void MainWindow::setCustomPaperHeight(double height)
{
	m_paperCustomHeightSpinner->setValue(height);
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

void MainWindow::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterSizeAbsoluteRadioButton
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterSizeInPagesRadioButton
		:m_posterSizePercentualRadioButton
	)->setChecked(true);
}

void MainWindow::setPosterAlignment(Qt::Alignment alignment)
{
	if (m_alignmentButtons.contains(alignment))
		m_alignmentButtons.value(alignment)->setChecked(true);
}

void MainWindow::setPosterOutputFormat(ImageIOTypes::eImageFormats /* format */)
{
}

void MainWindow::setLaunchPDFApplication(bool launch)
{
	m_launchPDFApplicationCheckBox->setCheckState(launch?Qt::Checked:Qt::Unchecked);
}

void MainWindow::updatePreview()
{
	m_paintCanvas->repaint();
}

void MainWindow::showImageFileName(const char *fileName)
{
	m_inputFileNameLabel->setText(QFileInfo(fileName).fileName());
}

void MainWindow::updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel)
{
	Q_UNUSED(horizontalDpi)
	Q_UNUSED(unitOfLength)

	m_imageInformationSizeInPixelsValue->setText(QString("%1 x %2").arg(imageWidthInPixels).arg(imageHeightInPixels));
	m_imageInformationSizeValue->setText(QString("%1 x %2").arg(imageWidth, 0, 'f', 2).arg(imageHeight, 0, 'f', 2));
	m_imageInformationResolutionValue->setText(QString("%1 dpi").arg(verticalDpi, 0, 'f', 1));
	const QString colorTypeString = (
		colorType==ColorTypes::eColorTypeMonochrome?QCoreApplication::translate("PosteRazorDialog", "Monochrome"):
		colorType==ColorTypes::eColorTypeGreyscale?QCoreApplication::translate("PosteRazorDialog", "Gray scale"):
		colorType==ColorTypes::eColorTypePalette?QCoreApplication::translate("PosteRazorDialog", "Palette"):
		colorType==ColorTypes::eColorTypeRGB?QCoreApplication::translate("PosteRazorDialog", "RGB"):
		colorType==ColorTypes::eColorTypeRGBA?QCoreApplication::translate("PosteRazorDialog", "RGBA"):
		/*colorType==eColorTypeCMYK?*/ QCoreApplication::translate("PosteRazorDialog", "CMYK")
	) + QString(" %1bpp").arg(bitsPerPixel);
	m_imageInformationColorTypeValue->setText(colorTypeString);
	emit imageLoaded();
}

void MainWindow::launchPdfApplication(const char *pdfFileName) const
{
	QDesktopServices::openUrl(QUrl(pdfFileName));
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

void MainWindow::setPreviewImage(const unsigned char* rgbData, const QSize &size)
{
	m_paintCanvas->setImage(rgbData, size);
}

void MainWindow::handlePaperFormatTabChanged(int index)
{
//	m_posteRazorController->setUseCustomPaperSize(index == 1);
}

void MainWindow::handlePaperOrientationPortraitSelected()
{
//	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationPortrait);
}

void MainWindow::handlePaperOrientationLandscapeSelected()
{
//	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationLandscape);
}

void MainWindow::handlePosterHorizontalAlignmentLeftSelected()
{
//	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentLeft);
}

void MainWindow::handlePosterHorizontalAlignmentCenterSelected()
{
//	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentCenter);
}

void MainWindow::handlePosterHorizontalAlignmentRightSelected()
{
//	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentRight);
}

void MainWindow::handlePosterVerticalAlignmentTopSelected()
{
//	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentTop);
}

void MainWindow::handlePosterVerticalAlignmentMiddleSelected()
{
//	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentMiddle);
}

void MainWindow::handlePosterVerticalAlignmentBottomSelected()
{
//	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentBottom);
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
	connect(alignmentMapper, SIGNAL(mapped(int)), SLOT(emitPosterAlignmentChange(int)));

	connect(m_savePosterButton,                     SIGNAL(clicked()),                  SIGNAL(savePosterSignal()));
	connect(m_launchPDFApplicationCheckBox,         SIGNAL(toggled(bool)),              SIGNAL(launchPDFApplicationChanged(bool)));

	connect(m_paintCanvas,                          SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)));
}

void MainWindow::populateUI()
{
	QStringList formats = PaperFormats::paperFormats().keys();
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
