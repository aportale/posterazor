//
// Fl_Native_File_Chooser_WINDOWS.H -- FLTK native OS file chooser widget
//
// Copyright 2004 by Greg Ercolano.
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
    };

private:
    Fl_Native_File_Chooser::Type btype;		// kind-of browser to show()
    OPENFILENAME ofn;		// GetOpenFileName() & GetSaveFileName() struct
    BROWSEINFO   binf;		// SHBrowseForFolder() struct
    char  **_pathnames;		// array of pathnames
    int   _tpathnames;		// total pathnames
    char  *_preset_dirname;	// default pathname to use
    char  *_title;		// title for window
    char  *_filter;		// search filter
    char  *_errmsg;		// error message

    void errmsg(const char *msg);

    void clear_pathnames();

    void set_single_pathname(const char *s);

    void add_pathname(const char *s);

    void Ctor(Fl_Native_File_Chooser::Type type);
    void FreePIDL(ITEMIDLIST *pidl);
    void ClearOFN();
    void ClearBINF();
    void Win2Unix(char *s);
    void Unix2Win(char *s);
    int showfile();
    static int CALLBACK SetSelect_CB(HWND win, UINT msg, LPARAM param, LPARAM data);
    int showdir();

public:
    Fl_Native_File_Chooser();
    Fl_Native_File_Chooser(Fl_Native_File_Chooser::Type val);
    ~Fl_Native_File_Chooser();
    void type(Fl_Native_File_Chooser::Type val);
    int show();
    const char *errmsg();
    const char* filename() const;
    const char* filename(int i) const;
    int total_filenames() const;
    void preset_dirname(const char *val);
    const char* preset_dirname() const;
    void title(const char *val);
    const char* title() const;
    const char *filter() const;
    void filter(const char *val);
};

#endif /*_FL_NATIVE_FILE_BROWSER_H*/
