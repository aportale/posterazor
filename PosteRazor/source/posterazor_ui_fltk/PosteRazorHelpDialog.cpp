/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "PosteRazorHelpDialog.h"
#include "Translations.h"

#if defined (WIN32)
  #include <Shellapi.h>
  #define CASESENSITIVESTRCMP stricmp
  #define CASESENSITIVESTRNCMP strnicmp
#else
  #include <iostream>
  #define CASESENSITIVESTRCMP strcasecmp
  #define CASESENSITIVESTRNCMP strncasecmp
#endif

PosteRazorHelpDialog::PosteRazorHelpDialog()
	:PosteRazorHelpDialogUI(500, 400, "PosteRazor Help")
{
	m_help_view->link(linkCallback);
}

void PosteRazorHelpDialog::setHtmlContent(const char *content)
{
	m_help_view->value(content);
}

void PosteRazorHelpDialog::jumpToAnchor(const char *anchor)
{
	m_help_view->topline(anchor);
}

void PosteRazorHelpDialog::handleHomepageButtonClick(void)
{
	openURLInBrowser(TRANSLATIONS->posteRazorWebSiteURL());
}

void PosteRazorHelpDialog::openURLInBrowser(const char* url)
{
#if defined (WIN32)
	ShellExecute(HWND_DESKTOP, "open", url, NULL, NULL, SW_SHOW);
#elif defined (__APPLE__)
	char commandString[2048];
	sprintf(commandString, "open \"%s\"", url);
	system(commandString);
#endif
}

const char *PosteRazorHelpDialog::linkCallback(Fl_Widget *w, const char *uri)
{
#define HTTPSCHEMESTART "http://"
	if (0 == CASESENSITIVESTRNCMP(uri, HTTPSCHEMESTART, strlen(HTTPSCHEMESTART)))
	{
		((PosteRazorHelpDialog*)(w->parent()))->openURLInBrowser(uri);
		return NULL;
	}
	else
		return uri;
}

void PosteRazorHelpDialog::updateLanguage(void)
{
	label(TRANSLATIONS->posteRazorHelp());
	SetHomepageButtonLabel(TRANSLATIONS->posteRazorWebSite());
	redraw();
}
