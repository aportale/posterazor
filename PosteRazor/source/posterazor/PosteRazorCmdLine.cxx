#include "PosteRazor.h"

int main(int argc, char *argv[])
{
	int error = 0;

	// This is no real main program, yet. It is just testing the PosteRazor API.

	PosteRazor* prz = PosteRazor::CreatePosteRazor();
	char errorMessage[1024];
	bool loaded = prz->LoadInputImage("c:\\image.png", errorMessage, sizeof(errorMessage));

	if (loaded)
	{
		prz->SetPosterWidth(PosteRazor::ePosterSizeModePages, 2.5);
		prz->SetPosterVerticalAlignment(PosteRazor::eVerticalAlignmentMiddle);
		prz->SetPosterHorizontalAlignment(PosteRazor::eHorizontalAlignmentCenter);
		int err = prz->SavePoster("c:\\poster.pdf");
		int huhu= 1;
	}

	delete prz;
	return error;
}