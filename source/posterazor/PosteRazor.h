#ifndef PosteRazor_h
#define PosteRazor_h

#include "../tools/PaperFormats.h"
#include "../tools/ColorTypes.h"
#include "../tools/ImageIOTypes.h"
#include "../tools/PaintCanvasInterface.h"
#include "../tools/PersistentPreferencesInterface.h"

class PosteRazor: public PaperFormats, public ColorTypes, public ImageIOTypes, public PainterInterface
{
public:
	typedef enum eOverlappingPositions
	{
		eOverlappingPositionTopRight,
		eOverlappingPositionBottomRight,
		eOverlappingPositionBottomLeft,
		eOverlappingPositionTopLeft
	};

	typedef enum ePosterSizeModes
	{
		ePosterSizeModeAbsolute,
		ePosterSizeModePercentual,
		ePosterSizeModePages
	};

	typedef enum eVerticalAlignments
	{
		eVerticalAlignmentTop,
		eVerticalAlignmentMiddle,
		eVerticalAlignmentBottom
	};

	typedef enum eHorizontalAlignments
	{
		eHorizontalAlignmentLeft,
		eHorizontalAlignmentCenter,
		eHorizontalAlignmentRight
	};

	virtual ~PosteRazor() {};
	static PosteRazor* CreatePosteRazor();

	virtual bool ReadPersistentPreferences(PersistentPreferencesInterface *preferences) = 0;
	virtual bool WritePersistentPreferences(PersistentPreferencesInterface *preferences) const = 0;

	virtual bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize) = 0;
	virtual bool IsImageLoaded(void) const = 0;

	virtual int GetInputImageWidthPixels(void) const = 0;
	virtual int GetInputImageHeightPixels(void) const = 0;

	virtual double GetInputImageHorizontalDpi(void) const = 0;
	virtual double GetInputImageVerticalDpi(void) const = 0;

	virtual double GetInputImageWidth(void) const = 0;
	virtual double GetInputImageHeight(void) const = 0;
	
	virtual int GetInputImageBitsPerPixel(void) const = 0;
	virtual enum eColorTypes GetInputImageColorType(void) const = 0;

	virtual void SetDistanceUnit(enum eDistanceUnits unit) = 0;
	virtual enum eDistanceUnits GetDistanceUnit(void) const = 0;
	virtual const char* GetDistanceUnitName(void) const = 0;

	virtual void SetPaperFormat(enum ePaperFormats format) = 0;
	virtual void SetPaperOrientation(enum ePaperOrientations orientation) = 0;
	virtual void SetPaperBorderTop(double border) = 0;
	virtual void SetPaperBorderRight(double border) = 0;
	virtual void SetPaperBorderBottom(double border) = 0;
	virtual void SetPaperBorderLeft(double border) = 0;

	virtual enum ePaperFormats GetPaperFormat(void) const = 0;
	virtual enum ePaperOrientations GetPaperOrientation(void) const = 0;
	virtual double GetPaperBorderTop(void) const = 0;
	virtual double GetPaperBorderRight(void) const = 0;
	virtual double GetPaperBorderBottom(void) const = 0;
	virtual double GetPaperBorderLeft(void) const = 0;

	virtual void SetCustomPaperWidth(double width) = 0;
	virtual void SetCustomPaperHeight(double height) = 0;
	virtual double GetCustomPaperWidth(void) const = 0;
	virtual double GetCustomPaperHeight(void) const = 0;
	virtual void SetUseCustomPaperSize(bool useIt) = 0;
	virtual bool GetUseCustomPaperSize(void) const = 0;
	virtual double GetPaperWidth(void) const = 0;
	virtual double GetPaperHeight(void) const = 0;
	virtual double GetPrintablePaperAreaWidth(void) const = 0;
	virtual double GetPrintablePaperAreaHeight(void) const = 0;

	virtual void SetOverlappingWidth(double width) = 0;
	virtual void SetOverlappingHeight(double height) = 0;
	virtual double GetOverlappingWidth(void) const = 0;
	virtual double GetOverlappingHeight(void) const = 0;
	virtual void SetOverlappingPosition(enum eOverlappingPositions position) = 0;
	virtual enum eOverlappingPositions GetOverlappingPosition(void) const = 0;
	
	virtual void SetPosterWidth(enum ePosterSizeModes mode, double width) = 0;
	virtual void SetPosterHeight(enum ePosterSizeModes mode, double height) = 0;
	virtual double GetPosterWidth(enum ePosterSizeModes mode) const = 0;
	virtual double GetPosterHeight(enum ePosterSizeModes mode) const = 0;
	virtual enum ePosterSizeModes GetPosterSizeMode(void) const = 0;
	virtual void SetPosterHorizontalAlignment(enum eHorizontalAlignments alignment) = 0;
	virtual void SetPosterVerticalAlignment(enum eVerticalAlignments alignment) = 0;
	virtual enum eHorizontalAlignments GetPosterHorizontalAlignment(void) const  = 0;
	virtual enum eVerticalAlignments GetPosterVerticalAlignment(void) const = 0;

	virtual void SetPosterOutputFormat(enum eImageFormats format) = 0;
	virtual enum eImageFormats GetPosterOutputFormat(void) const = 0;

	virtual int SavePoster(const char *fileName) const = 0;
	virtual void SetLaunchPDFApplication(bool launch) = 0;
	virtual bool GetLaunchPDFApplication(void) const = 0;
};

#endif