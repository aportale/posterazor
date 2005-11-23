//
// Fl_Native_File_Chooser_DEFAULT.H -- FLTK native OS file chooser widget
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

// OSX-SPECIFIC NATIVE BROWSER
#include <FL/Fl_File_Chooser.H>

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
    Type btype;			// kind-of browser to show()
    char **_pathnames;		// array of pathnames
    int  _tpathnames;		// total pathnames
    char *_preset_dirname;	// default pathname to use
    char *_title;		// title for window
    char *_filter;		// search filter
    char *_errmsg;		// error message

    void set_single_pathname(const char *s);

    void errmsg(const char *msg);
    void clear_pathnames();
    void _ctor(Type type);


public:
    Fl_Native_File_Chooser();
    Fl_Native_File_Chooser(Type type);
    ~Fl_Native_File_Chooser();

    const char *errmsg() const;

    int total_filenames() const { return(_tpathnames); }

    // Type
    void type(Type val);
    Type type() const;

    // Filename
    const char* filename() const;
    const char* filename(int i) const;

    // Preset Directory
    void preset_dirname(const char *val);
    const char* preset_dirname() const;

    // Title
    void title(const char *val);
    const char* title() const;

    // Filter
    const char *filter() const;
    void filter(const char *val);

    int show();

};
