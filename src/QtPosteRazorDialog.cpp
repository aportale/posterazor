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

#include "QtPosteRazorDialog.h"
#include <QSettings>
#include <QApplication>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QUrl>
#include <QTranslator>
#include <QDesktopServices>

QtPosteRazorDialog::QtPosteRazorDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	setupUi(this);
	m_wizard->setCurrentIndex(0);

	createConnections();
	populateUI();
	createPosteRazorDialogController();

	QSettings settings;
	m_posteRazorController->readSettings(&settings);

	updatePosterSizeGroupsState();
}

QtPosteRazorDialog::~QtPosteRazorDialog()
{
	QSettings settings;
	m_posteRazorController->writeSettings(&settings);
}

void QtPosteRazorDialog::setUnitOfLength(UnitsOfLength::eUnitsOfLength /* unit */)
{
}

void QtPosteRazorDialog::setPaperFormat(PaperFormats::ePaperFormats format)
{
	m_paperFormatComboBox->setCurrentIndex(m_paperFormatComboBox->findData(QVariant(format)));
}

void QtPosteRazorDialog::setPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
	(
		orientation == PaperFormats::ePaperOrientationLandscape?m_paperOrientationLandscapeRadioButton
		:m_paperOrientationPortraitRadioButton
	)->setChecked(true);
}

void QtPosteRazorDialog::setPaperBorderTop(double border)
{
	m_paperBorderTopInput->setValue(border);
}

void QtPosteRazorDialog::setPaperBorderRight(double border)
{
	m_paperBorderRightInput->setValue(border);
}

void QtPosteRazorDialog::setPaperBorderBottom(double border)
{
	m_paperBorderBottomInput->setValue(border);
}

void QtPosteRazorDialog::setPaperBorderLeft(double border)
{
	m_paperBorderLeftInput->setValue(border);
}

void QtPosteRazorDialog::setCustomPaperWidth(double width)
{
	m_paperCustomWidthSpinner->setValue(width);
}

void QtPosteRazorDialog::setCustomPaperHeight(double height)
{
	m_paperCustomHeightSpinner->setValue(height);
}

void QtPosteRazorDialog::setUseCustomPaperSize(bool useIt)
{
	m_paperFormatTypeTabs->setCurrentWidget(useIt?m_paperFormatCustomTab:m_paperFormatStandardTab);
}

void QtPosteRazorDialog::setOverlappingWidth(double width)
{
	m_overlappingWidthInput->setValue(width);
}

void QtPosteRazorDialog::setOverlappingHeight(double height)
{
	m_overlappingHeightInput->setValue(height);
}

void QtPosteRazorDialog::setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
{
	(
		position == PosteRazorEnums::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:position == PosteRazorEnums::eOverlappingPositionTopRight?m_overlappingPositionTopRightButton
		:position == PosteRazorEnums::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:m_overlappingPositionBottomLeftButton
	)->setChecked(true);
}

void QtPosteRazorDialog::setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteWidthInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesWidthInput
		:m_posterPercentualSizeInput
	)->setValue(width);
}

void QtPosteRazorDialog::setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteHeightInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesHeightInput
		:m_posterPercentualSizeInput
	)->setValue(height);
}

void QtPosteRazorDialog::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterSizeAbsoluteRadioButton
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterSizeInPagesRadioButton
		:m_posterSizePercentualRadioButton
	)->setChecked(true);
}

void QtPosteRazorDialog::setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eHorizontalAlignmentLeft?m_posterAlignmentLeftButton
		:alignment == PosteRazorEnums::eHorizontalAlignmentCenter?m_posterAlignmentCenterButton
		:m_posterAlignmentRightButton
	)->setChecked(true);
}

void QtPosteRazorDialog::setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:alignment == PosteRazorEnums::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton
	)->setChecked(true);
}

void QtPosteRazorDialog::setPosterOutputFormat(ImageIOTypes::eImageFormats /* format */)
{
}

void QtPosteRazorDialog::setLaunchPDFApplication(bool launch)
{
	m_launchPDFApplicationCheckBox->setCheckState(launch?Qt::Checked:Qt::Unchecked);
}

void QtPosteRazorDialog::updatePreview(void)
{
	m_paintCanvas->repaint();
}

void QtPosteRazorDialog::showImageFileName(const char *fileName)
{
	m_inputFileNameLabel->setText(QFileInfo(fileName).fileName());
}

void QtPosteRazorDialog::updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel)
{
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

void QtPosteRazorDialog::launchPdfApplication(const char *pdfFileName) const
{
	QDesktopServices::openUrl(QUrl(pdfFileName));
}

void QtPosteRazorDialog::setPrevButtonEnabled(bool enabled)
{
	m_prevButton->setDisabled(!enabled);
}

void QtPosteRazorDialog::setNextButtonEnabled(bool enabled)
{
	m_nextButton->setDisabled(!enabled);
}

void QtPosteRazorDialog::setWizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step)
{
	m_wizard->setCurrentWidget (
		step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage?m_loadInputImageStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize?m_paperSizeStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?m_overlappingStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize?m_posterSizeStep
		:/* step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster? */m_savePosterStep
	);
}

void QtPosteRazorDialog::setPreviewState(const char *state)
{
	m_paintCanvas->setState(state);
}

void QtPosteRazorDialog::handleNextButtonClicked(void)
{
	m_posteRazorController->handleNextButtonPressed();
}

void QtPosteRazorDialog::handlePrevButtonClicked(void)
{
	m_posteRazorController->handlePrevButtonPressed();
}

void QtPosteRazorDialog::handlePaperFormatComboBoxActivated(int index)
{
	m_posteRazorController->setPaperFormat((PaperFormats::ePaperFormats)(m_paperFormatComboBox->itemData(index).toInt()));
}

void QtPosteRazorDialog::handleImageLoadButtonClicked(void)
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
		this,
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

void QtPosteRazorDialog::handlePaperFormatTabChanged(int index)
{
	m_posteRazorController->setUseCustomPaperSize(index == 1);
}

void QtPosteRazorDialog::handlePaperOrientationPortraitSelected(void)
{
	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationPortrait);
}

void QtPosteRazorDialog::handlePaperOrientationLandscapeSelected(void)
{
	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationLandscape);
}

void QtPosteRazorDialog::handlePaperCustomWidthChanged(double width)
{
	m_posteRazorController->setCustomPaperWidth(width);
}

void QtPosteRazorDialog::handlePaperCustomHeightChanged(double height)
{
	m_posteRazorController->setCustomPaperHeight(height);
}

void QtPosteRazorDialog::handlePaperBorderTopChanged(double border)
{
	m_posteRazorController->setPaperBorderTop(border);
}

void QtPosteRazorDialog::handlePaperBorderRightChanged(double border)
{
	m_posteRazorController->setPaperBorderRight(border);
}

void QtPosteRazorDialog::handlePaperBorderBottomChanged(double border)
{
	m_posteRazorController->setPaperBorderBottom(border);
}

void QtPosteRazorDialog::handlePaperBorderLeftChanged(double border)
{
	m_posteRazorController->setPaperBorderLeft(border);
}

void QtPosteRazorDialog::handleOverlappingWidthChanged(double width)
{
	m_posteRazorController->setOverlappingWidth(width);
}

void QtPosteRazorDialog::handleOverlappingHeightChanged(double height)
{
	m_posteRazorController->setOverlappingHeight(height);
}

void QtPosteRazorDialog::handleOverlappingPositionTopLeftSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionTopLeft);
}

void QtPosteRazorDialog::handleOverlappingPositionTopRightSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionTopRight);
}

void QtPosteRazorDialog::handleOverlappingPositionBottomRightSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionBottomRight);
}

void QtPosteRazorDialog::handleOverlappingPositionBottomLeftSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionBottomLeft);
}

void QtPosteRazorDialog::handlePosterWidthAbsoluteChanged(double width)
{
	m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute, width);
}

void QtPosteRazorDialog::handlePosterHeightAbsoluteChanged(double height)
{
	m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute, height);
}

void QtPosteRazorDialog::handlePosterWidthPagesChanged(double width)
{
	m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModePages, width);
}

void QtPosteRazorDialog::handlePosterHeightPagesChanged(double height)
{
	m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModePages, height);
}

void QtPosteRazorDialog::handlePosterSizePercentualChanged(double percent)
{
	m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModePercentual, percent);
}

void QtPosteRazorDialog::handlePosterHorizontalAlignmentLeftSelected(void)
{
	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentLeft);
}

void QtPosteRazorDialog::handlePosterHorizontalAlignmentCenterSelected(void)
{
	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentCenter);
}

void QtPosteRazorDialog::handlePosterHorizontalAlignmentRightSelected(void)
{
	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentRight);
}

void QtPosteRazorDialog::handlePosterVerticalAlignmentTopSelected(void)
{
	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentTop);
}

void QtPosteRazorDialog::handlePosterVerticalAlignmentMiddleSelected(void)
{
	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentMiddle);
}

void QtPosteRazorDialog::handlePosterVerticalAlignmentBottomSelected(void)
{
	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentBottom);
}

void QtPosteRazorDialog::handleSavePosterButtonClicked(void)
{
	static const QLatin1String savePathSettingsKey("savePath");
	QSettings savePathSettings;

	QString saveFileName = savePathSettings.value(savePathSettingsKey, ".").toString();
	bool fileExistsAskUserForOverwrite = false;

	do {
		saveFileName = QFileDialog::getSaveFileName(
			this,
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
				|| QMessageBox::Yes == (QMessageBox::question(this, "", QCoreApplication::translate("PosteRazorDialog", "The file '%1' already exists.\nDo you want to overwrite it?").arg(saveFileName), QMessageBox::Yes, QMessageBox::No))
				) {
				int result = m_posteRazorController->savePoster(saveFileName.toAscii());
				if (result != 0)
					QMessageBox::critical(this, "", QCoreApplication::translate("PosteRazorDialog", "The File \"%1\" could not be saved.").arg(saveFileName), QMessageBox::Ok, QMessageBox::NoButton);
				else
					savePathSettings.setValue(savePathSettingsKey, QFileInfo(saveFileName).absolutePath());
				fileExistsAskUserForOverwrite = false;
			}
		}
		else
			break;
	} while (fileExistsAskUserForOverwrite);
}

void QtPosteRazorDialog::handleLaunchPDFApplicationChanged(bool launch)
{
	m_posteRazorController->setLaunchPDFApplication(launch);
}

void QtPosteRazorDialog::createConnections(void)
{
	connect(m_nextButton, SIGNAL(clicked()), SLOT(handleNextButtonClicked()));
	connect(m_prevButton, SIGNAL(clicked()), SLOT(handlePrevButtonClicked()));

	connect(m_paperFormatTypeTabs, SIGNAL(currentChanged(int)), SLOT(handlePaperFormatTabChanged(int)));
	connect(m_paperFormatComboBox, SIGNAL(activated(int)), SLOT(handlePaperFormatComboBoxActivated(int)));
	connect(m_paperOrientationPortraitRadioButton, SIGNAL(clicked()), SLOT(handlePaperOrientationPortraitSelected()));
	connect(m_paperOrientationLandscapeRadioButton, SIGNAL(clicked()), SLOT(handlePaperOrientationLandscapeSelected()));
	connect(m_paperCustomWidthSpinner, SIGNAL(valueEdited(double)), SLOT(handlePaperCustomWidthChanged(double)));
	connect(m_paperCustomHeightSpinner, SIGNAL(valueEdited(double)), SLOT(handlePaperCustomHeightChanged(double)));
	connect(m_paperBorderTopInput, SIGNAL(valueEdited(double)), SLOT(handlePaperBorderTopChanged(double)));
	connect(m_paperBorderRightInput, SIGNAL(valueEdited(double)), SLOT(handlePaperBorderRightChanged(double)));
	connect(m_paperBorderBottomInput, SIGNAL(valueEdited(double)), SLOT(handlePaperBorderBottomChanged(double)));
	connect(m_paperBorderLeftInput, SIGNAL(valueEdited(double)), SLOT(handlePaperBorderLeftChanged(double)));

	connect(m_imageLoadButton, SIGNAL(clicked()), SLOT(handleImageLoadButtonClicked()));

	connect(m_posterSizeAbsoluteRadioButton, SIGNAL(clicked()), SLOT(updatePosterSizeGroupsState()));
	connect(m_posterSizeInPagesRadioButton, SIGNAL(clicked()), SLOT(updatePosterSizeGroupsState()));
	connect(m_posterSizePercentualRadioButton, SIGNAL(clicked()), SLOT(updatePosterSizeGroupsState()));

	connect(m_overlappingWidthInput, SIGNAL(valueEdited(double)), SLOT(handleOverlappingWidthChanged(double)));
	connect(m_overlappingHeightInput, SIGNAL(valueEdited(double)), SLOT(handleOverlappingHeightChanged(double)));
	connect(m_overlappingPositionTopLeftButton, SIGNAL(clicked()), SLOT(handleOverlappingPositionTopLeftSelected()));
	connect(m_overlappingPositionTopRightButton, SIGNAL(clicked()), SLOT(handleOverlappingPositionTopRightSelected()));
	connect(m_overlappingPositionBottomRightButton, SIGNAL(clicked()), SLOT(handleOverlappingPositionBottomRightSelected()));
	connect(m_overlappingPositionBottomLeftButton, SIGNAL(clicked()), SLOT(handleOverlappingPositionBottomLeftSelected()));

	connect(m_posterAbsoluteWidthInput, SIGNAL(valueEdited(double)), SLOT(handlePosterWidthAbsoluteChanged(double)));
	connect(m_posterAbsoluteHeightInput, SIGNAL(valueEdited(double)), SLOT(handlePosterHeightAbsoluteChanged(double)));
	connect(m_posterPagesWidthInput, SIGNAL(valueEdited(double)), SLOT(handlePosterWidthPagesChanged(double)));
	connect(m_posterPagesHeightInput, SIGNAL(valueEdited(double)), SLOT(handlePosterHeightPagesChanged(double)));
	connect(m_posterPercentualSizeInput, SIGNAL(valueEdited(double)), SLOT(handlePosterSizePercentualChanged(double)));

	connect(m_posterAlignmentTopButton, SIGNAL(clicked()), SLOT(handlePosterVerticalAlignmentTopSelected()));
	connect(m_posterAlignmentMiddleButton, SIGNAL(clicked()), SLOT(handlePosterVerticalAlignmentMiddleSelected()));
	connect(m_posterAlignmentBottomButton, SIGNAL(clicked()), SLOT(handlePosterVerticalAlignmentBottomSelected()));
	connect(m_posterAlignmentLeftButton, SIGNAL(clicked()), SLOT(handlePosterHorizontalAlignmentLeftSelected()));
	connect(m_posterAlignmentCenterButton, SIGNAL(clicked()), SLOT(handlePosterHorizontalAlignmentCenterSelected()));
	connect(m_posterAlignmentRightButton, SIGNAL(clicked()), SLOT(handlePosterHorizontalAlignmentRightSelected()));

	connect(m_savePosterButton, SIGNAL(clicked()), SLOT(handleSavePosterButtonClicked()));
	connect(m_launchPDFApplicationCheckBox, SIGNAL(toggled(bool)), SLOT(handleLaunchPDFApplicationChanged(bool)));
}

void QtPosteRazorDialog::createPosteRazorDialogController(void)
{
	m_posteRazor = PosteRazor::createPosteRazor();
	m_paintCanvas->setPainterInterface(m_posteRazor);
	m_posteRazorController = new PosteRazorWizardDialogController();
	m_posteRazorController->setPosteRazorWizardDialog(this);
	m_posteRazorController->setPosteRazorModel(m_posteRazor);
}

void QtPosteRazorDialog::populateUI(void)
{
	for (int i = 0; i < PaperFormats::getPaperFormatsCount(); i++) {
		PaperFormats::ePaperFormats format = PaperFormats::getPaperFormatForIndex(i);
		QString formatName(PaperFormats::getPaperFormatName(format));
		m_paperFormatComboBox->addItem(formatName, QVariant(format));
	}
}

void QtPosteRazorDialog::updatePosterSizeGroupsState(void)
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

bool QtPosteRazorDialog::loadInputImage(const QString &fileName)
{
	char errorMessage[1024];
	const bool successful = m_posteRazorController->loadInputImage(fileName.toAscii(), errorMessage, sizeof(errorMessage));
	if (!successful) {
		QMessageBox::critical(this, QCoreApplication::translate("PosteRazorDialog", "Loading Error"), QCoreApplication::translate("PosteRazorDialog", "The Image '%1' could not be loaded.").arg(fileName));
	} else {
		m_paintCanvas->requestImage();
	}

	return successful;
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

	QtPosteRazorDialog dialog;
	dialog.show();
	if (argc == 2)
		dialog.loadInputImage(argv[1]);

	return a.exec();
}
