#include "PosteRazor.h"

int main(int argc, char *argv[])
{
	int error = 0;
	PosteRazor* prz = PosteRazor::CreatePosteRazor("c:\\IMG_0184.tif");
	int huhu1 = prz->GetPixelWidth();
	int huhu2 = prz->GetPixelHeight();

	const char* name = PosteRazor::GetPaperFormatName(PosteRazor::ePaperFormatLegal);
	enum PosteRazor::ePaperFormats format = PosteRazor::GetPaperFormatForName("Letter");

	int buibui = PosteRazor::buibui;

	delete prz;
	return error;
}