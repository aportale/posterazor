#include "PosteRazor.h"

int main(int argc, char *argv[])
{
	int error = 0;

	// This is no real main program, yet. It is just testing the PosteRazor API.

	PosteRazor* prz = PosteRazor::CreatePosteRazor("c:\\IMG_0184.tif");
	int huhu1 = prz->GetInputImageWidthPixels();
	int huhu2 = prz->GetInputImageHeightPixels();

	double test001 = prz->ConvertBetweenDistanceUnits(1, PosteRazor::eDistanceUnitInch, PosteRazor::eDistanceUnitMillimeter);

	double dpiHor = prz->GetInputImageHorizontalDpi();
	double dpiVer = prz->GetInputImageVerticalDpi();

	double widthCm = prz->GetInputImageWidth();
	double heightCm = prz->GetInputImageHeight();
	prz->SetDistanceUnit(PosteRazor::eDistanceUnitInch);
	double widthInch = prz->GetInputImageWidth();
	double heightInch = prz->GetInputImageHeight();

	const char* name = PosteRazor::GetPaperFormatName(PosteRazor::ePaperFormatLegal);
	enum PosteRazor::ePaperFormats format = PosteRazor::GetPaperFormatForName("Letter");


	delete prz;
	return error;
}