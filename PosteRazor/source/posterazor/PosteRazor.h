#ifndef PosteRazor_h
#define PosteRazor_h

#include "../tools/PaperFormats.h"
#include "../tools/ColorTypes.h"
#include "../tools/ImageIOTypes.h"
#include "../tools/PaintCanvasInterface.h"

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

	virtual bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize) = 0;
	virtual bool IsImageLoaded(void) = 0;

	virtual int GetInputImageWidthPixels(void) = 0;
	virtual int GetInputImageHeightPixels(void) = 0;

	virtual double GetInputImageHorizontalDpi(void) = 0;
	virtual double GetInputImageVerticalDpi(void) = 0;

	virtual double GetInputImageWidth(void) = 0;
	virtual double GetInputImageHeight(void) = 0;
	
	virtual int GetInputImageBitsPerPixel(void) = 0;
	virtual enum eColorTypes GetInputImageColorType(void) = 0;

	virtual void SetDistanceUnit(enum eDistanceUnits unit) = 0;
	virtual enum eDistanceUnits GetDistanceUnit(void) = 0;
	virtual const char* GetDistanceUnitName(void) = 0;

	virtual void SetPaperFormat(enum ePaperFormats format) = 0;
	virtual void SetPaperOrientation(enum ePaperOrientations orientation) = 0;
	virtual void SetPaperBorderTop(double border) = 0;
	virtual void SetPaperBorderRight(double border) = 0;
	virtual void SetPaperBorderBottom(double border) = 0;
	virtual void SetPaperBorderLeft(double border) = 0;

	virtual enum ePaperFormats GetPaperFormat(void) = 0;
	virtual enum ePaperOrientations GetPaperOrientation(void) = 0;
	virtual double GetPaperBorderTop(void) = 0;
	virtual double GetPaperBorderRight(void) = 0;
	virtual double GetPaperBorderBottom(void) = 0;
	virtual double GetPaperBorderLeft(void) = 0;

	virtual void SetCustomPaperWidth(double width) = 0;
	virtual void SetCustomPaperHeight(double height) = 0;
	virtual double GetCustomPaperWidth(void) = 0;
	virtual double GetCustomPaperHeight(void) = 0;
	virtual void SetUseCustomPaperSize(bool useIt) = 0;
	virtual bool GetUseCustomPaperSize(void) = 0;
	virtual double GetPaperWidth(void) = 0;
	virtual double GetPaperHeight(void) = 0;
	virtual double GetPrintablePaperAreaWidth(void) = 0;
	virtual double GetPrintablePaperAreaHeight(void) = 0;

	virtual void SetOverlappingWidth(double width) = 0;
	virtual void SetOverlappingHeight(double height) = 0;
	virtual double GetOverlappingWidth(void) = 0;
	virtual double GetOverlappingHeight(void) = 0;
	virtual void SetOverlappingPosition(enum eOverlappingPositions position) = 0;
	virtual enum eOverlappingPositions GetOverlappingPosition(void) = 0;
	
	virtual void SetPosterWidth(enum ePosterSizeModes mode, double width) = 0;
	virtual void SetPosterHeight(enum ePosterSizeModes mode, double height) = 0;
	virtual double GetPosterWidth(enum ePosterSizeModes mode) = 0;
	virtual double GetPosterHeight(enum ePosterSizeModes mode) = 0;
	virtual enum ePosterSizeModes GetPosterSizeMode(void) = 0;
	virtual void SetPosterHorizontalAlignment(enum eHorizontalAlignments alignment) = 0;
	virtual void SetPosterVerticalAlignment(enum eVerticalAlignments alignment) = 0;
	virtual enum eHorizontalAlignments GetPosterHorizontalAlignment(void) = 0;
	virtual enum eVerticalAlignments GetPosterVerticalAlignment(void) = 0;

	virtual void SetPosterOutputFormat(enum eImageFormats format) = 0;
	virtual enum eImageFormats GetPosterOutputFormat(void) = 0;
	virtual void SetPosterOutputLossy(bool lossy) = 0;
	virtual bool GetPosterOutputLossy(void) = 0;
	virtual void SetPosterOutputLossyQuality(double quality) = 0;
	virtual double GetPosterOutputLossyQuality(void) = 0;

	virtual int SavePoster(const char *fileName) = 0;
};

#endif