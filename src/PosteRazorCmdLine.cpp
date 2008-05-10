/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PosteRazor.h"

int main(int argc, char *argv[])
{
	int error = 0;
	if (argc < 3)
		return 1;

	// This is no real main program, yet. It is just testing the PosteRazor API.

	PosteRazor* prz = PosteRazor::createPosteRazor();
	char errorMessage[1024];
	bool loaded = prz->loadInputImage(argv[1], errorMessage, sizeof(errorMessage));

	if (loaded)
	{
		prz->setPosterWidth(PosteRazorEnums::ePosterSizeModePages, 2.5);
		prz->setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignmentMiddle);
		prz->setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignmentCenter);
		int err = prz->savePoster(argv[2]);
		int huhu= 1;
	}

	delete prz;
	return error;
}
