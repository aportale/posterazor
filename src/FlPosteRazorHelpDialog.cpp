/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
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

#include "FlPosteRazorHelpDialog.h"
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

FlPosteRazorHelpDialog::FlPosteRazorHelpDialog()
	:PosteRazorHelpDialogUI(500, 400, "PosteRazor Help")
{
	m_help_view->link(linkCallback);
#if defined(NO_LAUNCH_URLS_OR_FILES)
	m_homepageButton->hide();
#endif
}

void FlPosteRazorHelpDialog::setHtmlContent(const char *content)
{
	m_help_view->value(content);
}

void FlPosteRazorHelpDialog::jumpToAnchor(const char *anchor)
{
	m_help_view->topline(anchor);
}

void FlPosteRazorHelpDialog::handleHomepageButtonClick(void)
{
	openURLInBrowser(Translations::instance().posteRazorWebSiteURL());
}

void FlPosteRazorHelpDialog::openURLInBrowser(const char* url)
{
#if defined (WIN32)
	ShellExecute(HWND_DESKTOP, "open", url, NULL, NULL, SW_SHOW);
#elif defined (__APPLE__)
	char commandString[2048];
	sprintf(commandString, "open \"%s\"", url);
	system(commandString);
#endif
}

const char *FlPosteRazorHelpDialog::linkCallback(Fl_Widget *w, const char *uri)
{
	const char* const httpSchemeStart = "http://";
	if (0 == CASESENSITIVESTRNCMP(uri, httpSchemeStart, strlen(httpSchemeStart))) {
		((FlPosteRazorHelpDialog*)(w->parent()))->openURLInBrowser(uri);
		return NULL;
	}
	else
		return uri;
}

void FlPosteRazorHelpDialog::updateLanguage(void)
{
	label(Translations::instance().posteRazorHelp());
	setHomepageButtonLabel(Translations::instance().posteRazorWebSite());
	redraw();
}
