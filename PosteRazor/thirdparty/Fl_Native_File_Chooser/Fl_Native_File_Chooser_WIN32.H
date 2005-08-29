//
// Fl_Native_File_Chooser_WINDOWS.H -- FLTK native OS file chooser widget
//
// Copyright 2004 by Greg Ercolano.
// April 2005 - API changes, improved filter processing by Nathan Vander Wilt
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
#ifndef _FL_NATIVE_FILE_BROWSER_H
#define _FL_NATIVE_FILE_BROWSER_H

// #define _WIN32_WINNT	0x0501	// needed for OPENFILENAME's 'FlagsEx'
#include <stdio.h>
#include <stdlib.h>		// malloc
#include <windows.h>
#include <commdlg.h>		// OPENFILENAME, GetOpenFileName()
#include <shlobj.h>		// BROWSEINFO, SHBrowseForFolder()

class Fl_Native_File_Chooser {
public:
    enum Type {
	BROWSE_FILE = 0,
        BROWSE_DIRECTORY,
	BROWSE_MULTI_FILE,
	BROWSE_MULTI_DIRECTORY,
	BROWSE_SAVE_FILE,
	BROWSE_SAVE_DIRECTORY
    };

private:
    Type btype;		// kind-of browser to show()
    OPENFILENAME ofn;		// GetOpenFileName() & GetSaveFileName() struct
    BROWSEINFO   binf;		// SHBrowseForFolder() struct
    char  **_pathnames;		// array of pathnames
    int   _tpathnames;		// total pathnames
    char  *_directory;	// default pathname to use
    char  *_title;		// title for window
    char  *_filter;		// user-side search filter
    char  *_parsedfilt;		// filter parsed for Windows dialog
    int   _nfilters;		// number of filters parse_filter counted
    char  *_preset_file;	// the file to preselect
    char  *_errmsg;		// error message

    void errmsg(const char *msg);

    void clear_pathnames();

    void set_single_pathname(const char *s);

    void add_pathname(const char *s);

    void Ctor(Type type);
    void FreePIDL(ITEMIDLIST *pidl);
    void ClearOFN();
    void ClearBINF();
    void Win2Unix(char *s);
    void Unix2Win(char *s);
    int showfile();
    static int CALLBACK Dir_CB(HWND win, UINT msg, LPARAM param, LPARAM data);
    int showdir();

    char* parse_filter();           // allocates an array to contain properly parsed filter
    void fltk2win_filter(const char*, char*);
    static void nullncat(char* &wp, const char *string, int n ) { strncpy(wp, string, n); wp += n; *wp++='\0'; }
    static void nullcat(char* &wp, const char *string) { strcpy(wp, string); wp += strlen(wp)+1; }
    void DumpDoubleNull(char*);  //why can't static?

public:
    Fl_Native_File_Chooser();
    Fl_Native_File_Chooser(Type val);
    ~Fl_Native_File_Chooser();
    void type(Type val);
    int show();
    const char *errmsg();
    const char* filename() const;
    const char* filename(int i) const;
    int count() const;
    void directory(const char *val);
    const char* directory() const;
    void title(const char *val);
    const char* title() const;
    const char *filter() const;
    void filter(const char *val);
    int filters() { return _nfilters; }
    void set_filter(int);
    int set_filter();
    void preset_file(const char*);
    const char* preset_file();
};

#endif /*_FL_NATIVE_FILE_BROWSER_H*/
