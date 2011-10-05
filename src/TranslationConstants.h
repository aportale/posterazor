/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2011 by Alessandro Portale
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

#ifndef PosteRazorHelpConstants_h
#define PosteRazorHelpConstants_h

#define POSTERAZORHELPANCHORTOP "top"
#define POSTERAZORHELPANCHORABOUT "about"
#define POSTERAZORHELPANCHORMANUAL "manual"
#define POSTERAZORHELPANCHORSETTINGS "settings"
#define POSTERAZORHELPANCHORMANUALSTEP "manualstep"
#define POSTERAZORHELPANCHORMANUALSTEP01 "manualstep01"
#define POSTERAZORHELPANCHORMANUALSTEP02 "manualstep02"
#define POSTERAZORHELPANCHORMANUALSTEP03 "manualstep03"
#define POSTERAZORHELPANCHORMANUALSTEP04 "manualstep04"
#define POSTERAZORHELPANCHORMANUALSTEP05 "manualstep05"
#define POSTERAZORHELPANCHORINPUTFILEFORMATS "inputfileformats"
#define POSTERAZORHELPANCHORABOUTPDFOUTPUT "aboutpdfoutput"
#define POSTERAZORHELPANCHORWHYPDFOUTPUT "whypdfoutput"
#define POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "codefromthirdparties"
#define POSTERAZORHELPANCHORLICENSE "license"
#define POSTERAZORVERSION "1.5.3"
#define POSTERAZORWEBSITEDOMAIN "http://posterazor.sourceforge.net/"

#define POSTERAZORHELPLINKTOTOP "&nbsp;&nbsp;&nbsp;<A href=\"#" POSTERAZORHELPANCHORTOP "\">^</A>"

#define POSTERAZORHELPINDENTATION "<br>&nbsp;&nbsp;&nbsp;&nbsp;"
#define POSTERAZORHELPENDLINE ""

#define POSTERAZORHELPSECTIONHEADER(ANCHOR, TITLE) "<br><H3><A name=\"" ANCHOR "\">" TITLE "</A>" POSTERAZORHELPLINKTOTOP "</H3>" POSTERAZORHELPENDLINE

#define POSTERAZORCOPYRIGHT "Copyright (C) 2005-2011 by Alessandro Portale<br>" POSTERAZORHELPENDLINE POSTERAZORHELPENDLINE \

#define POSTERAZORTRANSLATIONCREDITSSTART "<dl>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSEND "</dl>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSFRENCH "<dt>French translation:</dt><dd>&nbsp;&nbsp;&nbsp;Martin Loyer (traduction<b></b>@<b></b>loyer<b></b>.<b></b>name).</dd>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSPOLISH "<dt>Polish translation:</dt><dd>&nbsp;&nbsp;&nbsp;Grzegorz Wacikowski.</dd>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSDUTCH "<dt>Dutch/Belgian translation:</dt><dd>&nbsp;&nbsp;&nbsp;Erik Wijkamp - Lochem (The Netherlands) (e_wijkamp<b></b>@<b></b>yahoo<b></b>.<b></b>com)</dd>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSITALIAN "<dt>Italian translation:</dt><dd>&nbsp;&nbsp;&nbsp;Stefano Nosei (kluster<b></b>@<b></b>imente<b></b>.<b></b>org).</dd>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSSPANISH "<dt>Spanish translation:</dt><dd>&nbsp;&nbsp;&nbsp;Cristobal from <a href=\"http://hispanicoweb.net/\">Hisp&aacute;nicoWeb</a></dd>" POSTERAZORHELPENDLINE
#define POSTERAZORTRANSLATIONCREDITSBRAZILIANPORTUGUESE "<dt>Brazilian Portuguese translation:</dt><dd>&nbsp;&nbsp;&nbsp;&Eacute;derson Gomes dos Santos.</dd>" POSTERAZORHELPENDLINE

#define POSTERAZORLICENSE \
	"This program is free software; you can redistribute it and/or modify it under the terms of the <a href=\"http://www.gnu.org/licenses/gpl.txt\">GNU General Public License</a> as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
	"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
	"You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA." POSTERAZORHELPENDLINE

#endif

