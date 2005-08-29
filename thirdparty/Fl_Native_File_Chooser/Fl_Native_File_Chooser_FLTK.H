//
// Fl_Native_File_Chooser_DEFAULT.H -- FLTK native OS file chooser widget
//
// Copyright 2005 by Nathan Vander Wilt.
// March 2005 - wrapper around Fl_File_Chooser
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

// Use FLTK BROWSER
#include <FL/Fl_File_Chooser.H>
#include <string.h>

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
    void Ctor(Type);
    char* _errmsg;		// error message
    char* filter_;
    char* _preset_file;
    char* _directory;
    int _nfilters;              // number of filters counted when parsed
    void errmsg(const char *msg);
    int type_fl_file(Type);
    char* parse_filter();           // allocates an array to contain properly parsed filter
    Fl_File_Chooser* file_chooser;
    char* prevvalue;		// Returned filename
    void keeplocation();
public:
    Fl_Native_File_Chooser();
    Fl_Native_File_Chooser(Type);
    ~Fl_Native_File_Chooser();
    int count();
    void directory(const char *val);
    const char* directory() const;
    const char *errmsg();
    const char* filename() const;
    const char* filename(int i) const;
    const char *filter() const;
    void filter(const char *);
    void set_filter(int i);
    int set_filter();
    int filters() { return _nfilters; }
    void preset_file(const char*);
    const char* preset_file();
    int show();
    void title(const char *);
    const char* title() const;
    void type(Type);
};
