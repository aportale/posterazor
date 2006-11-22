#include "PosteRazorDialogController.h"
#include <vector>

using namespace std;

class PosteRazorDialogControllerImplementation : public PosteRazorDialogController
{
private:
	PosteRazor *m_PosteRazor;
	PosteRazorDialogInterface *m_Dialog;

public:
	PosteRazorDialogControllerImplementation()
		: m_PosteRazor(0)
		, m_Dialog(0)
	{
	}

	void setPosteRazorModel(PosteRazor *model)
	{
		m_PosteRazor = model;
		if (m_Dialog)
		{
			updateDialog();
			SetDialogPosterSizeMode();
		}
	}

	void setPosteRazorDialog(PosteRazorDialogInterface *dialog)
	{
		m_Dialog = dialog;
		if (m_PosteRazor)
		{
			updateDialog();
			SetDialogPosterSizeMode();
		}
	}

	void updateDialog(void)
	{
		SetDialogPaperOptions();
		SetDialogPosterOptions();
		SetDialogOverlappingOptions();
		SetDialogImageInfoFields();
		SetDialogSaveOptions();
		m_Dialog->setUnitOfLength(m_PosteRazor->getUnitOfLength());
		updatePreview();
	}

	void updatePreview(void)
	{
		m_Dialog->updatePreview();
	}

	void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
	{
		m_PosteRazor->setUnitOfLength(unit);
		updateDialog();
	}

	void setPaperFormat(PaperFormats::ePaperFormats format)
	{
		m_PosteRazor->setPaperFormat(format);
		updatePreview();
	}

	void setPaperFormatByName(const char *name)
	{
		PaperFormats::ePaperFormats paperFormat = PaperFormats::getPaperFormatForName(name);
		setPaperFormat(paperFormat);
	}

	void setPaperOrientation(PaperFormats::ePaperOrientations orientation)
	{
		m_PosteRazor->setPaperOrientation(orientation);
		updatePreview();
	}

	void setPaperBorderTop(double border)
	{
		m_PosteRazor->setPaperBorderTop(border);
		updatePreview();
	}

	void setPaperBorderRight(double border)
	{
		m_PosteRazor->setPaperBorderRight(border);
		updatePreview();
	}

	void setPaperBorderBottom(double border)
	{
		m_PosteRazor->setPaperBorderBottom(border);
		updatePreview();
	}

	void setPaperBorderLeft(double border)
	{
		m_PosteRazor->setPaperBorderLeft(border);
		updatePreview();
	}

	void setCustomPaperWidth(double width)
	{
		m_PosteRazor->setCustomPaperWidth(width);
		updatePreview();
	}

	void setCustomPaperHeight(double height)
	{
		m_PosteRazor->setCustomPaperHeight(height);
		updatePreview();
	}

	void setUseCustomPaperSize(bool useIt)
	{
		m_PosteRazor->setUseCustomPaperSize(useIt);
		updatePreview();
	}

	void setOverlappingWidth(double width)
	{
		m_PosteRazor->setOverlappingWidth(width);
		updatePreview();
	}

	void setOverlappingHeight(double height)
	{
		m_PosteRazor->setOverlappingHeight(height);
		updatePreview();
	}

	void setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
	{
		m_PosteRazor->setOverlappingPosition(position);
		updatePreview();
	}

	void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
	{
		m_PosteRazor->setPosterWidth(mode, width);
		SetDialogPosterDimensions(mode, true);
	}

	void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
	{
		m_PosteRazor->setPosterHeight(mode, height);
		SetDialogPosterDimensions(mode, false);
	}

	void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
	{
		m_PosteRazor->setPosterSizeMode(mode);
	}

	void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
	{
		m_PosteRazor->setPosterHorizontalAlignment(alignment);
		updatePreview();
	}

	void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
	{
		m_PosteRazor->setPosterVerticalAlignment(alignment);
		updatePreview();
	}

	void setPosterOutputFormat(ImageIOTypes::eImageFormats format)
	{
		m_PosteRazor->setPosterOutputFormat(format);
	}

	void setLaunchPDFApplication(bool launch)
	{
		m_PosteRazor->setLaunchPDFApplication(launch);
		SetDialogSaveOptions();
	}

	void SetDialogSaveOptions(void)
	{
		m_Dialog->setLaunchPDFApplication(m_PosteRazor->getLaunchPDFApplication());
	}

	void SetDialogPosterSizeMode(void)
	{
		m_Dialog->setPosterSizeMode(m_PosteRazor->getPosterSizeMode());
	}

	void SetDialogPosterOptions(void)
	{
		SetDialogPosterDimensions(PosteRazorEnums::ePosterSizeModeNone, true);
		m_Dialog->setPosterHorizontalAlignment(m_PosteRazor->getPosterHorizontalAlignment());
		m_Dialog->setPosterVerticalAlignment(m_PosteRazor->getPosterVerticalAlignment());
	}

	void SetDialogPosterDimensions(PosteRazorEnums::ePosterSizeModes excludedMode, bool widthExcluded)
	{
		static const struct
		{
			bool isWidth;
			PosteRazorEnums::ePosterSizeModes sizeMode;
		}
		sizeModes[] = 
		{
			{true, PosteRazorEnums::ePosterSizeModeAbsolute},
			{false, PosteRazorEnums::ePosterSizeModeAbsolute},
			{true, PosteRazorEnums::ePosterSizeModePages},
			{false, PosteRazorEnums::ePosterSizeModePages},
			{true, PosteRazorEnums::ePosterSizeModePercentual}
		};

		int sizeModesCount = sizeof(sizeModes)/sizeof(sizeModes[0]);

		for (int i = 0; i < sizeModesCount; i++)
		{
			if ((excludedMode != sizeModes[i].sizeMode) || (widthExcluded != sizeModes[i].isWidth))
			{
				if (sizeModes[i].isWidth)
					m_Dialog->setPosterWidth(sizeModes[i].sizeMode, m_PosteRazor->getPosterWidth(sizeModes[i].sizeMode));
				else
					m_Dialog->setPosterHeight(sizeModes[i].sizeMode, m_PosteRazor->getPosterHeight(sizeModes[i].sizeMode));
			}
		}
		updatePreview();
	}

	void SetDialogPaperOptions(void)
	{
		SetDialogPaperBorders();
		SetDialogCustomPaperDimensions();
		m_Dialog->setUseCustomPaperSize(m_PosteRazor->getUseCustomPaperSize());
		m_Dialog->setPaperFormat(m_PosteRazor->getPaperFormat());
		m_Dialog->setPaperOrientation(m_PosteRazor->getPaperOrientation());
	}

	void SetDialogPaperBorders(void)
	{
		m_Dialog->setPaperBorderTop(m_PosteRazor->getPaperBorderTop());
		m_Dialog->setPaperBorderRight(m_PosteRazor->getPaperBorderRight());
		m_Dialog->setPaperBorderBottom(m_PosteRazor->getPaperBorderBottom());
		m_Dialog->setPaperBorderLeft(m_PosteRazor->getPaperBorderLeft());
	}

	void SetDialogCustomPaperDimensions(void)
	{
		m_Dialog->setCustomPaperWidth(m_PosteRazor->getCustomPaperWidth());
		m_Dialog->setCustomPaperHeight(m_PosteRazor->getCustomPaperHeight());
	}

	void SetDialogImageInfoFields(void)
	{
		if (m_PosteRazor->getIsImageLoaded())
		{
			m_Dialog->updateImageInfoFields
			(
				m_PosteRazor->getInputImageWidthPixels(),
				m_PosteRazor->getInputImageHeightPixels(),
				m_PosteRazor->getInputImageWidth(),
				m_PosteRazor->getInputImageHeight(),
				m_PosteRazor->getUnitOfLength(),
				m_PosteRazor->getInputImageVerticalDpi(),
				m_PosteRazor->getInputImageHorizontalDpi(),
				m_PosteRazor->getInputImageColorType(),
				m_PosteRazor->getInputImageBitsPerPixel()
			);
		}
	}

	void SetDialogOverlappingDimensions(void)
	{
		m_Dialog->setOverlappingWidth(m_PosteRazor->getOverlappingWidth());
		m_Dialog->setOverlappingHeight(m_PosteRazor->getOverlappingHeight());
	}

	void SetDialogOverlappingOptions(void)
	{
		SetDialogOverlappingDimensions();
		m_Dialog->setOverlappingPosition(m_PosteRazor->getOverlappingPosition());
	}

	bool readPersistentPreferences(PersistentPreferencesInterface *preferences)
	{
		bool result = m_PosteRazor->readPersistentPreferences(preferences);

		if (result)
			updateDialog();

		return result;
	}

	bool writePersistentPreferences(PersistentPreferencesInterface *preferences) const
	{
		return m_PosteRazor->writePersistentPreferences(preferences);
	}

	bool loadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		bool result = m_PosteRazor->loadInputImage(imageFileName, errorMessage, errorMessageSize);

		if (result)
			updateDialog();

		return result;
	}

	int savePoster(const char *fileName) const
	{
		return m_PosteRazor->savePoster(fileName);
	}
};

PosteRazorDialogController* PosteRazorDialogController::createPosteRazorDialogController()
{
	return (PosteRazorDialogController*)new PosteRazorDialogControllerImplementation();
}
