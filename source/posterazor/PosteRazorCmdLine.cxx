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
		prz->SetPosterWidth(PosteRazor::ePosterSizeModePages, 20);
		prz->SavePoster("c:\\poster.pdf");
	}

	delete prz;
	return error;
}