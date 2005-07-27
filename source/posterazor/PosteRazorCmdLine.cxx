#include "PosteRazor.h"

int main(int argc, char *argv[])
{
	int error = 0;

	// This is no real main program, yet. It is just testing the PosteRazor API.

	PosteRazor* prz = PosteRazor::CreatePosteRazor();
	char errorMessage[1024];
	bool loaded = prz->LoadInputImage("D:\\bureau.png", errorMessage, sizeof(errorMessage));

	if (loaded)
	{
		prz->SetPosterHeight(PosteRazor::ePosterSizeModePercentual, 100);
		double inputImageHeight = prz->GetInputImageHeight();
		double posterWidthPercentual = prz->GetPosterWidth(PosteRazor::ePosterSizeModePercentual);
	}

	delete prz;
	return error;
}