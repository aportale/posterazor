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
#include <QSettings>
#include <QApplication>
#include <QHeaderView>
#include <QUrl>
#include <QTranslator>
#include <QDesktopServices>
#include <QFileDialog>
#include "PosteRazorWizardDialogController.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupUi(this);
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

void MainWindow::setUnitOfLength(UnitsOfLength::eUnitsOfLength /* unit */)
{
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

void MainWindow::setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
{
	(
		position == PosteRazorEnums::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:position == PosteRazorEnums::eOverlappingPositionTopRight?m_overlappingPositionTopRightButton
		:position == PosteRazorEnums::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:m_overlappingPositionBottomLeftButton
	)->setChecked(true);
}

void MainWindow::setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteWidthInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesWidthInput
		:m_posterPercentualSizeInput
	)->setValue(width);
}

void MainWindow::setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteHeightInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesHeightInput
		:m_posterPercentualSizeInput
	)->setValue(height);
}

void MainWindow::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterSizeAbsoluteRadioButton
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterSizeInPagesRadioButton
		:m_posterSizePercentualRadioButton
	)->setChecked(true);
}

void MainWindow::setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eHorizontalAlignmentLeft?m_posterAlignmentLeftButton
		:alignment == PosteRazorEnums::eHorizontalAlignmentCenter?m_posterAlignmentCenterButton
		:m_posterAlignmentRightButton
	)->setChecked(true);
}

void MainWindow::setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:alignment == PosteRazorEnums::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton
	)->setChecked(true);
}

void MainWindow::setPosterOutputFormat(ImageIOTypes::eImageFormats /* format */)
{
}

void MainWindow::setLaunchPDFApplication(bool launch)
{
	m_launchPDFApplicationCheckBox->setCheckState(launch?Qt::Checked:Qt::Unchecked);
}

void MainWindow::updatePreview(void)
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

void MainWindow::setPreviewState(const char *state)
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

void MainWindow::handlePaperOrientationPortraitSelected(void)
{
//	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationPortrait);
}

void MainWindow::handlePaperOrientationLandscapeSelected(void)
{
//	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationLandscape);
}

void MainWindow::handleOverlappingPositionTopLeftSelected(void)
{
//	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionTopLeft);
}

void MainWindow::handleOverlappingPositionTopRightSelected(void)
{
//	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionTopRight);
}

void MainWindow::handleOverlappingPositionBottomRightSelected(void)
{
//	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionBottomRight);
}

void MainWindow::handleOverlappingPositionBottomLeftSelected(void)
{
//	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionBottomLeft);
}

void MainWindow::handlePosterHorizontalAlignmentLeftSelected(void)
{
//	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentLeft);
}

void MainWindow::handlePosterHorizontalAlignmentCenterSelected(void)
{
//	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentCenter);
}

void MainWindow::handlePosterHorizontalAlignmentRightSelected(void)
{
//	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentRight);
}

void MainWindow::handlePosterVerticalAlignmentTopSelected(void)
{
//	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentTop);
}

void MainWindow::handlePosterVerticalAlignmentMiddleSelected(void)
{
//	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentMiddle);
}

void MainWindow::handlePosterVerticalAlignmentBottomSelected(void)
{
//	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentBottom);
}

void MainWindow::createConnections(void)
{
	connect(m_nextButton,                           SIGNAL(clicked()),                  SIGNAL(nextButtonClicked()));
	connect(m_prevButton,                           SIGNAL(clicked()),                  SIGNAL(prevButtonClicked()));

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
	connect(m_overlappingPositionTopLeftButton,     SIGNAL(clicked()),                  SLOT(handleOverlappingPositionTopLeftSelected()));
	connect(m_overlappingPositionTopRightButton,    SIGNAL(clicked()),                  SLOT(handleOverlappingPositionTopRightSelected()));
	connect(m_overlappingPositionBottomRightButton, SIGNAL(clicked()),                  SLOT(handleOverlappingPositionBottomRightSelected()));
	connect(m_overlappingPositionBottomLeftButton,  SIGNAL(clicked()),                  SLOT(handleOverlappingPositionBottomLeftSelected()));

	connect(m_posterAbsoluteWidthInput,             SIGNAL(valueEdited(double)),        SIGNAL(posterWidthAbsoluteChanged(double)));
	connect(m_posterAbsoluteHeightInput,            SIGNAL(valueEdited(double)),        SIGNAL(posterHeightAbsoluteChanged(double)));
	connect(m_posterPagesWidthInput,                SIGNAL(valueEdited(double)),        SIGNAL(posterWidthPagesChanged(double)));
	connect(m_posterPagesHeightInput,               SIGNAL(valueEdited(double)),        SIGNAL(posterHeightPagesChanged(double)));
	connect(m_posterPercentualSizeInput,            SIGNAL(valueEdited(double)),        SIGNAL(posterSizePercentualChanged(double)));

	connect(m_posterAlignmentTopButton,             SIGNAL(clicked()),                  SLOT(handlePosterVerticalAlignmentTopSelected()));
	connect(m_posterAlignmentMiddleButton,          SIGNAL(clicked()),                  SLOT(handlePosterVerticalAlignmentMiddleSelected()));
	connect(m_posterAlignmentBottomButton,          SIGNAL(clicked()),                  SLOT(handlePosterVerticalAlignmentBottomSelected()));
	connect(m_posterAlignmentLeftButton,            SIGNAL(clicked()),                  SLOT(handlePosterHorizontalAlignmentLeftSelected()));
	connect(m_posterAlignmentCenterButton,          SIGNAL(clicked()),                  SLOT(handlePosterHorizontalAlignmentCenterSelected()));
	connect(m_posterAlignmentRightButton,           SIGNAL(clicked()),                  SLOT(handlePosterHorizontalAlignmentRightSelected()));

	connect(m_savePosterButton,                     SIGNAL(clicked()),                  SIGNAL(savePosterSignal()));
	connect(m_launchPDFApplicationCheckBox,         SIGNAL(toggled(bool)),              SIGNAL(launchPDFApplicationChanged(bool)));

	connect(m_paintCanvas,                          SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)), SIGNAL(needsPaint(PaintCanvasInterface*, const QVariant&)));
}

void MainWindow::populateUI(void)
{
	QStringList formats = PaperFormats::paperFormats().keys();
	formats.sort();
	m_paperFormatComboBox->addItems(formats);
}

void MainWindow::updatePosterSizeGroupsState(void)
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

int main (int argc, char **argv)
{
	QApplication a(argc, argv);

	QTranslator myAppTranslator;
	myAppTranslator.load(":/Translations/" + QLocale::system().name());
	a.installTranslator(&myAppTranslator);

	QCoreApplication::setApplicationName("PosteRazor");
	QCoreApplication::setApplicationVersion("1.9.0-alpha");
	QCoreApplication::setOrganizationName("CasaPortale");
	QCoreApplication::setOrganizationDomain("de.casaportale");

	MainWindow dialog;
	PosteRazor *posteRazor = PosteRazor::createPosteRazor();

//	m_paintCanvas->setPainterInterface(m_posteRazor);

	PosteRazorWizardDialogController *controller = new PosteRazorWizardDialogController();

	QSettings settings;
	controller->setPosteRazorAndDialog(posteRazor, &dialog);
	controller->readSettings(&settings);

	dialog.show();
	if (argc == 2)
		controller->loadInputImage(argv[1]);

	return a.exec();
}
