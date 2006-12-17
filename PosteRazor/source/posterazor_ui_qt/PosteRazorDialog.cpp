#include "PosteRazorDialog.h"
#include <QApplication>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include "QPersistentPreferences.h"

PosteRazorDialog::PosteRazorDialog(QWidget *parent, Qt::WFlags flags)
:	QDialog(parent, flags)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setupUi(this);
	m_wizard->setCurrentIndex(0);

	createConnections();
	populateUI();
	createPosteRazorDialogController();

	QPersistentPreferences preferences;
	m_posteRazorController->readPersistentPreferences(&preferences);

	updatePosterSizeGroupsState();
}

PosteRazorDialog::~PosteRazorDialog()
{
	QPersistentPreferences preferences;
	m_posteRazorController->writePersistentPreferences(&preferences);
}

void PosteRazorDialog::setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
}

void PosteRazorDialog::setPaperFormat(PaperFormats::ePaperFormats format)
{
	m_paperFormatComboBox->setCurrentIndex(m_paperFormatComboBox->findData(QVariant(format)));
}

void PosteRazorDialog::setPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
	(
		orientation == PaperFormats::ePaperOrientationLandscape?m_paperOrientationLandscapeRadioButton
		:m_paperOrientationPortraitRadioButton
	)->setChecked(true);
}

void PosteRazorDialog::setPaperBorderTop(double border)
{
	m_paperBorderTopInput->setValue(border);
}

void PosteRazorDialog::setPaperBorderRight(double border)
{
	m_paperBorderRightInput->setValue(border);
}

void PosteRazorDialog::setPaperBorderBottom(double border)
{
	m_paperBorderBottomInput->setValue(border);
}

void PosteRazorDialog::setPaperBorderLeft(double border)
{
	m_paperBorderLeftInput->setValue(border);
}

void PosteRazorDialog::setCustomPaperWidth(double width)
{
	m_paperCustomWidthSpinner->setValue(width);
}

void PosteRazorDialog::setCustomPaperHeight(double height)
{
	m_paperCustomHeightSpinner->setValue(height);
}

void PosteRazorDialog::setUseCustomPaperSize(bool useIt)
{
	m_paperFormatTypeTabs->setCurrentWidget(useIt?m_paperFormatCustomTab:m_paperFormatStandardTab);
}

void PosteRazorDialog::setOverlappingWidth(double width)
{
	m_overlappingWidthInput->setValue(width);
}

void PosteRazorDialog::setOverlappingHeight(double height)
{
	m_overlappingHeightInput->setValue(height);
}

void PosteRazorDialog::setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
{
	(
		position == PosteRazorEnums::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:position == PosteRazorEnums::eOverlappingPositionTopRight?m_overlappingPositionTopRightButton
		:position == PosteRazorEnums::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:m_overlappingPositionBottomLeftButton
	)->setChecked(true);
}

void PosteRazorDialog::setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteWidthInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesWidthInput
		:m_posterPercentualSizeInput
	)->setValue(width);
}

void PosteRazorDialog::setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteHeightInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesHeightInput
		:m_posterPercentualSizeInput
	)->setValue(height);
}

void PosteRazorDialog::setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterSizeAbsoluteRadioButton
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterSizeInPagesRadioButton
		:m_posterSizePercentualRadioButton
	)->setChecked(true);
}

void PosteRazorDialog::setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eHorizontalAlignmentLeft?m_posterAlignmentLeftButton
		:alignment == PosteRazorEnums::eHorizontalAlignmentCenter?m_posterAlignmentCenterButton
		:m_posterAlignmentRightButton
	)->setChecked(true);
}

void PosteRazorDialog::setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:alignment == PosteRazorEnums::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton
	)->setChecked(true);
}

void PosteRazorDialog::setPosterOutputFormat(ImageIOTypes::eImageFormats format)
{
}

void PosteRazorDialog::setLaunchPDFApplication(bool launch)
{
	m_launchPDFApplicationCheckBox->setCheckState(launch?Qt::Checked:Qt::Unchecked);
}

void PosteRazorDialog::updatePreview(void)
{
	m_paintCanvas->repaint();
}

void PosteRazorDialog::showImageFileName(const char *fileName)
{
	m_inputFileNameLabel->setText(QFileInfo(fileName).fileName());
}

void PosteRazorDialog::updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel)
{
	m_imageInformationSizeInPixelsLabel->setText(QString::number(imageWidthInPixels) + " x " + QString::number(imageHeightInPixels));
	m_imageInformationSizeLabel->setText(QString::number(imageWidth, 'f', 2) + " x " + QString::number(imageHeight, 'f', 2));
	m_imageInformationResolutionLabel->setText(QString::number(verticalDpi, 'f', 1) + " dpi");
	QString colorTypeString
	(
		colorType==ColorTypes::eColorTypeMonochrome?tr("Monochrome"):
		colorType==ColorTypes::eColorTypeGreyscale?tr("Gray scale"):
		colorType==ColorTypes::eColorTypePalette?tr("Palette"):
		colorType==ColorTypes::eColorTypeRGB?tr("RGB"):
		colorType==ColorTypes::eColorTypeRGBA?tr("RGBA"):
		/*colorType==eColorTypeCMYK?*/ tr("CMYK")
	);
	colorTypeString += " " + QString::number(bitsPerPixel) + "bpp";
	m_imageInformationColorTypeLabel->setText(colorTypeString);
}

void PosteRazorDialog::setPrevButtonEnabled(bool enabled)
{
	m_prevButton->setDisabled(!enabled);
}

void PosteRazorDialog::setNextButtonEnabled(bool enabled)
{
	m_nextButton->setDisabled(!enabled);
}

void PosteRazorDialog::setWizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step)
{
	m_wizard->setCurrentWidget
	(
		step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage?m_loadInputImageStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize?m_paperSizeStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?m_overlappingStep
		:step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize?m_posterSizeStep
		:/* step == PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster? */m_savePosterStep
	);
}

void PosteRazorDialog::handleNextButtonClicked(void)
{
	m_posteRazorController->handleNextButtonPressed();
}

void PosteRazorDialog::handlePrevButtonClicked(void)
{
	m_posteRazorController->handlePrevButtonPressed();
}

void PosteRazorDialog::handlePaperFormatComboBoxActivated(int index)
{
	m_posteRazorController->setPaperFormat((PaperFormats::ePaperFormats)(m_paperFormatComboBox->itemData(index).toInt()));
}

void PosteRazorDialog::handleImageLoadButtonClicked(void)
{
	QStringList filters;
	QStringList allExtensions;

	for (int formatIndex = 0; formatIndex < ImageIOTypes::getInputImageFormatsCount(); formatIndex++)
	{
		int extensionsCount = ImageIOTypes::getFileExtensionsCount(formatIndex);

		QStringList filterExtensions;
		for (int extensionIndex = 0; extensionIndex < extensionsCount; extensionIndex++)
		{
			filterExtensions << "*." + QString(ImageIOTypes::getFileExtensionForFormat(extensionIndex, formatIndex));
		}
		allExtensions << filterExtensions;

		filters << QString(ImageIOTypes::getInputImageFormat(formatIndex)) + " (" + filterExtensions.join(" ") + ")";
	}
	filters.prepend(tr("All image formats") + " (" +  allExtensions.join(" ") + ")"); 
	QString s = QFileDialog::getOpenFileName(this, "blah", NULL, filters.join(";;"));

	if (s != "")
	{
		loadInputImage(s);
	}
}

void PosteRazorDialog::handlePaperFormatTabChanged(int index)
{
	m_posteRazorController->setUseCustomPaperSize(index == 1);
}

void PosteRazorDialog::handlePaperOrientationPortraitSelected(void)
{
	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationPortrait);
}

void PosteRazorDialog::handlePaperOrientationLandscapeSelected(void)
{
	m_posteRazorController->setPaperOrientation(PaperFormats::ePaperOrientationLandscape);
}

void PosteRazorDialog::handlePaperCustomWidthChanged(double width)
{
	m_posteRazorController->setCustomPaperWidth(width);
}

void PosteRazorDialog::handlePaperCustomHeightChanged(double height)
{
	m_posteRazorController->setCustomPaperHeight(height);
}

void PosteRazorDialog::handlePaperBorderTopChanged(double border)
{
	m_posteRazorController->setPaperBorderTop(border);
}

void PosteRazorDialog::handlePaperBorderRightChanged(double border)
{
	m_posteRazorController->setPaperBorderRight(border);
}

void PosteRazorDialog::handlePaperBorderBottomChanged(double border)
{
	m_posteRazorController->setPaperBorderBottom(border);
}

void PosteRazorDialog::handlePaperBorderLeftChanged(double border)
{
	m_posteRazorController->setPaperBorderLeft(border);
}

void PosteRazorDialog::handleOverlappingWidthChanged(double width)
{
	m_posteRazorController->setOverlappingWidth(width);
}

void PosteRazorDialog::handleOverlappingHeightChanged(double height)
{
	m_posteRazorController->setOverlappingHeight(height);
}

void PosteRazorDialog::handleOverlappingPositionTopLeftSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionTopLeft);
}

void PosteRazorDialog::handleOverlappingPositionTopRightSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionTopRight);
}

void PosteRazorDialog::handleOverlappingPositionBottomRightSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionBottomRight);
}

void PosteRazorDialog::handleOverlappingPositionBottomLeftSelected(void)
{
	m_posteRazorController->setOverlappingPosition(PosteRazorEnums::eOverlappingPositionBottomLeft);
}

void PosteRazorDialog::handlePosterWidthAbsoluteChanged(double width)
{
	m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute, width);
}

void PosteRazorDialog::handlePosterHeightAbsoluteChanged(double height)
{
	m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute, height);
}

void PosteRazorDialog::handlePosterWidthPagesChanged(double width)
{
	m_posteRazorController->setPosterWidth(PosteRazorEnums::ePosterSizeModePages, width);
}

void PosteRazorDialog::handlePosterHeightPagesChanged(double height)
{
	m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModePages, height);
}

void PosteRazorDialog::handlePosterSizePercentualChanged(double percent)
{
	m_posteRazorController->setPosterHeight(PosteRazorEnums::ePosterSizeModePercentual, percent);
}

void PosteRazorDialog::handlePosterHorizontalAlignmentLeftSelected(void)
{
	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentLeft);
}

void PosteRazorDialog::handlePosterHorizontalAlignmentCenterSelected(void)
{
	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentCenter);
}

void PosteRazorDialog::handlePosterHorizontalAlignmentRightSelected(void)
{
	m_posteRazorController->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentRight);
}

void PosteRazorDialog::handlePosterVerticalAlignmentTopSelected(void)
{
	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentTop);
}

void PosteRazorDialog::handlePosterVerticalAlignmentMiddleSelected(void)
{
	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentMiddle);
}

void PosteRazorDialog::handlePosterVerticalAlignmentBottomSelected(void)
{
	m_posteRazorController->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentBottom);
}

void PosteRazorDialog::handleSavePosterButtonClicked(void)
{
	static const QString savePathSettingsKey("savePath");
	QSettings savePathSettings;

	QString saveFileName = savePathSettings.value(savePathSettingsKey, ".").toString();
	bool fileExistsAskUserForOverwrite = false;

	do
	{
		saveFileName = QFileDialog::getSaveFileName
		(
			this,
			"Choose a filename to save under",
			saveFileName,
			"Portable Document format (*.PDF)",
			NULL,
			QFileDialog::DontConfirmOverwrite
		);

		if (saveFileName != "")
		{
			if (QFileInfo(saveFileName).suffix().toLower() != "pdf")
				saveFileName += ".pdf";

			fileExistsAskUserForOverwrite = QFileInfo(saveFileName).exists();

			if (!fileExistsAskUserForOverwrite
				|| QMessageBox::Yes == (QMessageBox::question(this, "", tr("The file '%1' already exists.\nDo you want to overwrite it?").arg(saveFileName), QMessageBox::Yes, QMessageBox::No))
				)
			{
				int result = m_posteRazorController->savePoster(saveFileName.toAscii());
				if (result != 0)
					QMessageBox::critical(this, "", tr("The File \"%1\" could not be saved.").arg(saveFileName), QMessageBox::Ok, QMessageBox::NoButton);
				else
					savePathSettings.setValue(savePathSettingsKey, QFileInfo(saveFileName).absolutePath());
				fileExistsAskUserForOverwrite = false;
			}
		}
		else
			break;
	} while (fileExistsAskUserForOverwrite);
}

void PosteRazorDialog::handleLaunchPDFApplicationChanged(int state)
{
	m_posteRazorController->setLaunchPDFApplication(state == Qt::Checked);
}

void PosteRazorDialog::createConnections(void)
{
	connect(m_nextButton, SIGNAL(clicked()), this, SLOT(handleNextButtonClicked()));
	connect(m_prevButton, SIGNAL(clicked()), this, SLOT(handlePrevButtonClicked()));

	connect(m_paperFormatTypeTabs, SIGNAL(currentChanged(int)), this, SLOT(handlePaperFormatTabChanged(int)));
	connect(m_paperFormatComboBox, SIGNAL(activated(int)), this, SLOT(handlePaperFormatComboBoxActivated(int)));
	connect(m_paperOrientationPortraitRadioButton, SIGNAL(clicked()), this, SLOT(handlePaperOrientationPortraitSelected()));
	connect(m_paperOrientationLandscapeRadioButton, SIGNAL(clicked()), this, SLOT(handlePaperOrientationLandscapeSelected()));
	connect(m_paperCustomWidthSpinner, SIGNAL(valueEdited(double)), this, SLOT(handlePaperCustomWidthChanged(double)));
	connect(m_paperCustomHeightSpinner, SIGNAL(valueEdited(double)), this, SLOT(handlePaperCustomHeightChanged(double)));
	connect(m_paperBorderTopInput, SIGNAL(valueEdited(double)), this, SLOT(handlePaperBorderTopChanged(double)));
	connect(m_paperBorderRightInput, SIGNAL(valueEdited(double)), this, SLOT(handlePaperBorderRightChanged(double)));
	connect(m_paperBorderBottomInput, SIGNAL(valueEdited(double)), this, SLOT(handlePaperBorderBottomChanged(double)));
	connect(m_paperBorderLeftInput, SIGNAL(valueEdited(double)), this, SLOT(handlePaperBorderLeftChanged(double)));

	connect(m_imageLoadButton, SIGNAL(clicked()), this, SLOT(handleImageLoadButtonClicked()));

	connect(m_posterSizeAbsoluteRadioButton, SIGNAL(clicked()), this, SLOT(updatePosterSizeGroupsState()));
	connect(m_posterSizeInPagesRadioButton, SIGNAL(clicked()), this, SLOT(updatePosterSizeGroupsState()));
	connect(m_posterSizePercentualRadioButton, SIGNAL(clicked()), this, SLOT(updatePosterSizeGroupsState()));

	connect(m_overlappingWidthInput, SIGNAL(valueEdited(double)), this, SLOT(handleOverlappingWidthChanged(double)));
	connect(m_overlappingHeightInput, SIGNAL(valueEdited(double)), this, SLOT(handleOverlappingHeightChanged(double)));
	connect(m_overlappingPositionTopLeftButton, SIGNAL(clicked()), this, SLOT(handleOverlappingPositionTopLeftSelected()));
	connect(m_overlappingPositionTopRightButton, SIGNAL(clicked()), this, SLOT(handleOverlappingPositionTopRightSelected()));
	connect(m_overlappingPositionBottomRightButton, SIGNAL(clicked()), this, SLOT(handleOverlappingPositionBottomRightSelected()));
	connect(m_overlappingPositionBottomLeftButton, SIGNAL(clicked()), this, SLOT(handleOverlappingPositionBottomLeftSelected()));

	connect(m_posterAbsoluteWidthInput, SIGNAL(valueEdited(double)), this, SLOT(handlePosterWidthAbsoluteChanged(double)));
	connect(m_posterAbsoluteHeightInput, SIGNAL(valueEdited(double)), this, SLOT(handlePosterHeightAbsoluteChanged(double)));
	connect(m_posterPagesWidthInput, SIGNAL(valueEdited(double)), this, SLOT(handlePosterWidthPagesChanged(double)));
	connect(m_posterPagesHeightInput, SIGNAL(valueEdited(double)), this, SLOT(handlePosterHeightPagesChanged(double)));
	connect(m_posterPercentualSizeInput, SIGNAL(valueEdited(double)), this, SLOT(handlePosterSizePercentualChanged(double)));

	connect(m_posterAlignmentTopButton, SIGNAL(clicked()), this, SLOT(handlePosterVerticalAlignmentTopSelected()));
	connect(m_posterAlignmentMiddleButton, SIGNAL(clicked()), this, SLOT(handlePosterVerticalAlignmentMiddleSelected()));
	connect(m_posterAlignmentBottomButton, SIGNAL(clicked()), this, SLOT(handlePosterVerticalAlignmentBottomSelected()));
	connect(m_posterAlignmentLeftButton, SIGNAL(clicked()), this, SLOT(handlePosterHorizontalAlignmentLeftSelected()));
	connect(m_posterAlignmentCenterButton, SIGNAL(clicked()), this, SLOT(handlePosterHorizontalAlignmentCenterSelected()));
	connect(m_posterAlignmentRightButton, SIGNAL(clicked()), this, SLOT(handlePosterHorizontalAlignmentRightSelected()));

	connect(m_savePosterButton, SIGNAL(clicked()), this, SLOT(handleSavePosterButtonClicked()));
	connect(m_launchPDFApplicationCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handlelaunchPDFApplicationChanged(int)));
}

void PosteRazorDialog::createPosteRazorDialogController(void)
{
	m_posteRazor = PosteRazor::createPosteRazor();
	m_paintCanvas->setPainterInterface(m_posteRazor);
	m_posteRazorController = new PosteRazorWizardDialogController();
	m_posteRazorController->setPosteRazorWizardDialog(this);
	m_posteRazorController->setPosteRazorModel(m_posteRazor);
}

void PosteRazorDialog::populateUI(void)
{
	for (int i = 0; i < PaperFormats::getPaperFormatsCount(); i++)
	{
		PaperFormats::ePaperFormats format = PaperFormats::getPaperFormatForIndex(i);
		QString formatName(PaperFormats::getPaperFormatName(format));
		m_paperFormatComboBox->addItem(formatName, QVariant(format));
	}
}

void PosteRazorDialog::updatePosterSizeGroupsState(void)
{
	bool absolute = m_posterSizeAbsoluteRadioButton->isChecked();
	m_posterAbsoluteWidthLabel->setEnabled(absolute);
	m_posterAbsoluteWidthInput->setEnabled(absolute);
	m_posterAbsoluteWidthDimensionUnitLabel->setEnabled(absolute);
	m_posterAbsoluteHeightLabel->setEnabled(absolute);
	m_posterAbsoluteHeightInput->setEnabled(absolute);
	m_posterAbsoluteHeightDimensionUnitLabel->setEnabled(absolute);

	bool inPages = m_posterSizeInPagesRadioButton->isChecked();
	m_posterPagesHeightLabel->setEnabled(inPages);
	m_posterPagesWidthInput->setEnabled(inPages);
	m_posterPagesWidthDimensionUnitLabel->setEnabled(inPages);
	m_posterPagesHeightLabel->setEnabled(inPages);
	m_posterPagesHeightInput->setEnabled(inPages);
	m_posterPagesHeightDimensionUnitLabel->setEnabled(inPages);

	bool percentual = m_posterSizePercentualRadioButton->isChecked();
	m_posterPercentualSizeLabel->setEnabled(percentual);
	m_posterPercentualSizeInput->setEnabled(percentual);
	m_posterPercentualSizeUnitLabel->setEnabled(percentual);
}

void PosteRazorDialog::loadInputImage(const QString &fileName)
{
	char errorMessage[1024];
	bool successful = m_posteRazorController->loadInputImage(fileName.toAscii(), errorMessage, sizeof(errorMessage));
	if (!successful)
	{

	}
	else
	{
		m_paintCanvas->requestImage();
		m_paintCanvas->setState("poster");
	}
}

int main (int argc, char **argv)
{
	QApplication a(argc, argv);
	QCoreApplication::setApplicationName("PosteRazor 1.4");
	QCoreApplication::setOrganizationName("CasaPortale");
	QCoreApplication::setOrganizationDomain("de.casaportale");

	PosteRazorDialog *dialog = new PosteRazorDialog(NULL, Qt::Window);
	dialog->show();

	return a.exec();
}
