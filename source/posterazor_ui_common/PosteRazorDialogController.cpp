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

	void SetPosteRazorModel(PosteRazor *model)
	{
		m_PosteRazor = model;
		if (m_Dialog)
		{
			UpdateDialog();
			SetDialogPosterSizeMode();
		}
	}

	void SetPosteRazorDialog(PosteRazorDialogInterface *dialog)
	{
		m_Dialog = dialog;
		if (m_PosteRazor)
		{
			UpdateDialog();
			SetDialogPosterSizeMode();
		}
	}

	void UpdateDialog(void)
	{
		SetDialogPaperOptions();
		SetDialogPosterOptions();
		SetDialogOverlappingOptions();
		SetDialogImageInfoFields();
		SetDialogSaveOptions();
		m_Dialog->SetUnitOfLength(m_PosteRazor->GetUnitOfLength());
		UpdatePreview();
	}

	void UpdatePreview(void)
	{
		m_Dialog->UpdatePreview();
	}

	void SetUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
	{
		m_PosteRazor->SetUnitOfLength(unit);
		UpdateDialog();
	}

	void SetPaperFormat(PaperFormats::ePaperFormats format)
	{
		m_PosteRazor->SetPaperFormat(format);
		UpdatePreview();
	}

	void SetPaperFormatByName(const char *name)
	{
		PaperFormats::ePaperFormats paperFormat = PaperFormats::GetPaperFormatForName(name);
		SetPaperFormat(paperFormat);
	}

	void SetPaperOrientation(PaperFormats::ePaperOrientations orientation)
	{
		m_PosteRazor->SetPaperOrientation(orientation);
		UpdatePreview();
	}

	void SetPaperBorderTop(double border)
	{
		m_PosteRazor->SetPaperBorderTop(border);
		UpdatePreview();
	}

	void SetPaperBorderRight(double border)
	{
		m_PosteRazor->SetPaperBorderRight(border);
		UpdatePreview();
	}

	void SetPaperBorderBottom(double border)
	{
		m_PosteRazor->SetPaperBorderBottom(border);
		UpdatePreview();
	}

	void SetPaperBorderLeft(double border)
	{
		m_PosteRazor->SetPaperBorderLeft(border);
		UpdatePreview();
	}

	void SetCustomPaperWidth(double width)
	{
		m_PosteRazor->SetCustomPaperWidth(width);
		UpdatePreview();
	}

	void SetCustomPaperHeight(double height)
	{
		m_PosteRazor->SetCustomPaperHeight(height);
		UpdatePreview();
	}

	void SetUseCustomPaperSize(bool useIt)
	{
		m_PosteRazor->SetUseCustomPaperSize(useIt);
		UpdatePreview();
	}

	void SetOverlappingWidth(double width)
	{
		m_PosteRazor->SetOverlappingWidth(width);
		UpdatePreview();
	}

	void SetOverlappingHeight(double height)
	{
		m_PosteRazor->SetOverlappingHeight(height);
		UpdatePreview();
	}

	void SetOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
	{
		m_PosteRazor->SetOverlappingPosition(position);
		UpdatePreview();
	}

	void SetPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
	{
		m_PosteRazor->SetPosterWidth(mode, width);
		SetDialogPosterDimensions(mode, true);
	}

	void SetPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
	{
		m_PosteRazor->SetPosterHeight(mode, height);
		SetDialogPosterDimensions(mode, false);
	}

	void SetPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode)
	{
		m_PosteRazor->SetPosterSizeMode(mode);
	}

	void SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment)
	{
		m_PosteRazor->SetPosterHorizontalAlignment(alignment);
		UpdatePreview();
	}

	void SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
	{
		m_PosteRazor->SetPosterVerticalAlignment(alignment);
		UpdatePreview();
	}

	void SetPosterOutputFormat(ImageIOTypes::eImageFormats format)
	{
		m_PosteRazor->SetPosterOutputFormat(format);
	}

	void SetLaunchPDFApplication(bool launch)
	{
		m_PosteRazor->SetLaunchPDFApplication(launch);
		SetDialogSaveOptions();
	}

	void SetDialogSaveOptions(void)
	{
		m_Dialog->SetLaunchPDFApplication(m_PosteRazor->GetLaunchPDFApplication());
	}

	void SetDialogPosterSizeMode(void)
	{
		m_Dialog->SetPosterSizeMode(m_PosteRazor->GetPosterSizeMode());
	}

	void SetDialogPosterOptions(void)
	{
		SetDialogPosterDimensions(PosteRazorEnums::ePosterSizeModeNone, true);
		m_Dialog->SetPosterHorizontalAlignment(m_PosteRazor->GetPosterHorizontalAlignment());
		m_Dialog->SetPosterVerticalAlignment(m_PosteRazor->GetPosterVerticalAlignment());
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
					m_Dialog->SetPosterWidth(sizeModes[i].sizeMode, m_PosteRazor->GetPosterWidth(sizeModes[i].sizeMode));
				else
					m_Dialog->SetPosterHeight(sizeModes[i].sizeMode, m_PosteRazor->GetPosterHeight(sizeModes[i].sizeMode));
			}
		}
		UpdatePreview();
	}

	void SetDialogPaperOptions(void)
	{
		SetDialogPaperBorders();
		SetDialogCustomPaperDimensions();
		m_Dialog->SetUseCustomPaperSize(m_PosteRazor->GetUseCustomPaperSize());
		m_Dialog->SetPaperFormat(m_PosteRazor->GetPaperFormat());
		m_Dialog->SetPaperOrientation(m_PosteRazor->GetPaperOrientation());
	}

	void SetDialogPaperBorders(void)
	{
		m_Dialog->SetPaperBorderTop(m_PosteRazor->GetPaperBorderTop());
		m_Dialog->SetPaperBorderRight(m_PosteRazor->GetPaperBorderRight());
		m_Dialog->SetPaperBorderBottom(m_PosteRazor->GetPaperBorderBottom());
		m_Dialog->SetPaperBorderLeft(m_PosteRazor->GetPaperBorderLeft());
	}

	void SetDialogCustomPaperDimensions(void)
	{
		m_Dialog->SetCustomPaperWidth(m_PosteRazor->GetCustomPaperWidth());
		m_Dialog->SetCustomPaperHeight(m_PosteRazor->GetCustomPaperHeight());
	}

	void SetDialogImageInfoFields(void)
	{
		if (m_PosteRazor->GetIsImageLoaded())
		{
			m_Dialog->UpdateImageInfoFields
			(
				m_PosteRazor->GetInputImageWidthPixels(),
				m_PosteRazor->GetInputImageHeightPixels(),
				m_PosteRazor->GetInputImageWidth(),
				m_PosteRazor->GetInputImageHeight(),
				m_PosteRazor->GetUnitOfLength(),
				m_PosteRazor->GetInputImageVerticalDpi(),
				m_PosteRazor->GetInputImageHorizontalDpi(),
				m_PosteRazor->GetInputImageColorType(),
				m_PosteRazor->GetInputImageBitsPerPixel()
			);
		}
	}

	void SetDialogOverlappingDimensions(void)
	{
		m_Dialog->SetOverlappingWidth(m_PosteRazor->GetOverlappingWidth());
		m_Dialog->SetOverlappingHeight(m_PosteRazor->GetOverlappingHeight());
	}

	void SetDialogOverlappingOptions(void)
	{
		SetDialogOverlappingDimensions();
		m_Dialog->SetOverlappingPosition(m_PosteRazor->GetOverlappingPosition());
	}

	bool ReadPersistentPreferences(PersistentPreferencesInterface *preferences)
	{
		bool result = m_PosteRazor->ReadPersistentPreferences(preferences);

		if (result)
			UpdateDialog();

		return result;
	}

	bool WritePersistentPreferences(PersistentPreferencesInterface *preferences) const
	{
		return m_PosteRazor->WritePersistentPreferences(preferences);
	}

	bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		bool result = m_PosteRazor->LoadInputImage(imageFileName, errorMessage, errorMessageSize);

		if (result)
			UpdateDialog();

		return result;
	}

	int SavePoster(const char *fileName) const
	{
		return m_PosteRazor->SavePoster(fileName);
	}
};

PosteRazorDialogController* PosteRazorDialogController::CreatePosteRazorDialogController()
{
	return (PosteRazorDialogController*)new PosteRazorDialogControllerImplementation();
}
