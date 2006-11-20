#include "PosteRazorDialog.h"
#include <QApplication>
#include <QHeaderView>
#include <QFileDialog>

PosteRazorDialog::PosteRazorDialog(QWidget *parent, Qt::WFlags flags)
:	QDialog(parent, flags)
{
	setupUi(this);
	m_wizard->setCurrentIndex(0);

	createConnections();
	populateUI();
	createPosteRazorDialogController();

	m_imageInfoTable->horizontalHeader()->hide();
	m_imageInfoTable->verticalHeader()->hide();
	updatePosterSizeGroupsState();
}

void PosteRazorDialog::SetUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
{
}

void PosteRazorDialog::SetPaperFormat(PaperFormats::ePaperFormats format)
{
	m_paperFormatComboBox->setCurrentIndex(m_paperFormatComboBox->findData(QVariant(format)));
}

void PosteRazorDialog::SetPaperOrientation(PaperFormats::ePaperOrientations orientation)
{
	(
		orientation == PaperFormats::ePaperOrientationLandscape?m_paperOrientationLandscapeRadioButton
		:m_paperOrientationPortraitRadioButton
	)->setChecked(true);
}

void PosteRazorDialog::SetPaperBorderTop(double border)
{
	m_paperBorderTopInput->setValue(border);
}

void PosteRazorDialog::SetPaperBorderRight(double border)
{
	m_paperBorderRightInput->setValue(border);
}

void PosteRazorDialog::SetPaperBorderBottom(double border)
{
	m_paperBorderBottomInput->setValue(border);
}

void PosteRazorDialog::SetPaperBorderLeft(double border)
{
	m_paperBorderLeftInput->setValue(border);
}

void PosteRazorDialog::SetCustomPaperWidth(double width)
{
	m_paperCustomWidthSpinner->setValue(width);
}

void PosteRazorDialog::SetCustomPaperHeight(double height)
{
	m_paperCustomHeightSpinner->setValue(height);
}

void PosteRazorDialog::SetUseCustomPaperSize(bool useIt)
{
	m_paperFormatTypeTabs->setCurrentWidget(useIt?m_paperFormatCustomTab:m_paperFormatStandardTab);
}

void PosteRazorDialog::SetOverlappingWidth(double width)
{
	m_overlappingWidthInput->setValue(width);
}

void PosteRazorDialog::SetOverlappingHeight(double height)
{
	m_overlappingHeightInput->setValue(height);
}

void PosteRazorDialog::SetOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
{
	(
		position == PosteRazorEnums::eOverlappingPositionTopLeft?m_overlappingPositionTopLeftButton
		:position == PosteRazorEnums::eOverlappingPositionTopRight?m_overlappingPositionTopRightButton
		:position == PosteRazorEnums::eOverlappingPositionBottomRight?m_overlappingPositionBottomRightButton
		:m_overlappingPositionBottomLeftButton
	)->setChecked(true);
}

void PosteRazorDialog::SetPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteWidthInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesWidthInput
		:m_posterPercentualSizeInput
	)->setValue(width);
}

void PosteRazorDialog::SetPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterAbsoluteHeightInput
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterPagesHeightInput
		:m_posterPercentualSizeInput
	)->setValue(height);
}

void PosteRazorDialog::SetPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
{
	(
		mode == PosteRazorEnums::ePosterSizeModeAbsolute?m_posterSizeAbsoluteRadioButton
		:mode == PosteRazorEnums::ePosterSizeModePages?m_posterSizeInPagesRadioButton
		:m_posterSizePercentualRadioButton
	)->setChecked(true);
}

void PosteRazorDialog::SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eHorizontalAlignmentLeft?m_posterAlignmentLeftButton
		:alignment == PosteRazorEnums::eHorizontalAlignmentCenter?m_posterAlignmentCenterButton
		:m_posterAlignmentRightButton
	)->setChecked(true);
}

void PosteRazorDialog::SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
{
	(
		alignment == PosteRazorEnums::eVerticalAlignmentTop?m_posterAlignmentTopButton
		:alignment == PosteRazorEnums::eVerticalAlignmentMiddle?m_posterAlignmentMiddleButton
		:m_posterAlignmentBottomButton
	)->setChecked(true);
}

void PosteRazorDialog::SetPosterOutputFormat(ImageIOTypes::eImageFormats format)
{
}

void PosteRazorDialog::SetLaunchPDFApplication(bool launch)
{
}

void PosteRazorDialog::UpdatePreview(void)
{
}

void PosteRazorDialog::UpdateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel)
{
}

void PosteRazorDialog::handleNextButtonClicked(void)
{
	m_wizard->setCurrentIndex(m_wizard->currentIndex() + 1);
}

void PosteRazorDialog::handlePrevButtonClicked(void)
{
	m_wizard->setCurrentIndex(m_wizard->currentIndex() - 1);
}

void PosteRazorDialog::handlePaperFormatComboBoxActivated(int index)
{
	m_posteRazorController->SetPaperFormat((PaperFormats::ePaperFormats)(m_paperFormatComboBox->itemData(index).toInt()));
}

void PosteRazorDialog::handleImageLoadButtonClicked(void)
{
	QStringList filters;
	QStringList allExtensions;

	for (int formatIndex = 0; formatIndex < ImageIOTypes::GetInputImageFormatsCount(); formatIndex++)
	{
		int extensionsCount = ImageIOTypes::GetFileExtensionsCount(formatIndex);

		QStringList filterExtensions;
		for (int extensionIndex = 0; extensionIndex < extensionsCount; extensionIndex++)
		{
			filterExtensions << "*." + QString(ImageIOTypes::GetFileExtensionForFormat(extensionIndex, formatIndex));
		}
		allExtensions << filterExtensions;

		filters << QString(ImageIOTypes::GetInputImageFormat(formatIndex)) + " (" + filterExtensions.join(" ") + ")";
	}
	filters.prepend(tr("All image formats") + " (" +  allExtensions.join(" ") + ")"); 
	QString s = QFileDialog::getOpenFileName(this, "blah", ".", filters.join(";;"));
}

void PosteRazorDialog::createConnections(void)
{
	connect(m_nextButton, SIGNAL(clicked()), this, SLOT(handleNextButtonClicked()));
	connect(m_prevButton, SIGNAL(clicked()), this, SLOT(handlePrevButtonClicked()));

	connect(m_paperFormatComboBox, SIGNAL(activated(int)), this, SLOT(handlePaperFormatComboBoxActivated(int)));
	connect(m_imageLoadButton, SIGNAL(clicked()), this, SLOT(handleImageLoadButtonClicked()));

	connect(m_posterSizeAbsoluteRadioButton, SIGNAL(clicked()), this, SLOT(updatePosterSizeGroupsState()));
	connect(m_posterSizeInPagesRadioButton, SIGNAL(clicked()), this, SLOT(updatePosterSizeGroupsState()));
	connect(m_posterSizePercentualRadioButton, SIGNAL(clicked()), this, SLOT(updatePosterSizeGroupsState()));
}

void PosteRazorDialog::createPosteRazorDialogController(void)
{
	m_posteRazor = PosteRazor::CreatePosteRazor();
	m_posteRazorController = PosteRazorDialogController::CreatePosteRazorDialogController();
	m_posteRazorController->SetPosteRazorDialog(this);
	m_posteRazorController->SetPosteRazorModel(m_posteRazor);
}

void PosteRazorDialog::populateUI(void)
{
	for (int i = 0; i < PaperFormats::GetPaperFormatsCount(); i++)
	{
		PaperFormats::ePaperFormats format = PaperFormats::GetPaperFormatForIndex(i);
		QString formatName(PaperFormats::GetPaperFormatName(format));
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

int main (int argc, char **argv)
{
	QApplication a(argc, argv);

	PosteRazorDialog *dialog = new PosteRazorDialog(NULL, Qt::Window);
	dialog->show();

	return a.exec();
}
