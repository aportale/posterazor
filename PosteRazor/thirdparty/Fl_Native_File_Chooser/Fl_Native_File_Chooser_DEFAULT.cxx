//
// Fl_Native_File_Chooser_DEFAULT.cxx -- FLTK native OS file chooser widget
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
#include <FL/Fl_Native_File_Chooser.H>

void Fl_Native_File_Chooser::_ctor(Type type) {
    btype           = BROWSE_FILE;
    _pathnames      = NULL;
    _tpathnames     = 0;
    _title          = NULL;
    _filter         = NULL;
    _preset_dirname = NULL;
    _errmsg         = NULL;
}

Fl_Native_File_Chooser::Fl_Native_File_Chooser() {
    _ctor(BROWSE_FILE);
}

Fl_Native_File_Chooser::Fl_Native_File_Chooser(Type val) {
    _ctor(val);
}

Fl_Native_File_Chooser::~Fl_Native_File_Chooser() { 
    errmsg(0);
    title(0);
    filter(0);
    preset_dirname(0);
    clear_pathnames();
}

void Fl_Native_File_Chooser::set_single_pathname(const char *s) {
    clear_pathnames();
    _pathnames = (char**)malloc(sizeof(char*));
    _pathnames[0] = strdup(s);
    _tpathnames = 1;
}

void Fl_Native_File_Chooser::clear_pathnames() {
    if ( _pathnames ) {
	while ( --_tpathnames >= 0 ) {
	    free((void*)_pathnames[_tpathnames]);
	    _pathnames[_tpathnames] = NULL;
	}
	free((void*)_pathnames);
	_pathnames = NULL;
    }
    _tpathnames = 0;
}

// Type
void Fl_Native_File_Chooser::type(Type val) {
    btype = val;
}
Fl_Native_File_Chooser::Type Fl_Native_File_Chooser::type() const { 
    return(btype);
}

// Errors
void Fl_Native_File_Chooser::errmsg(const char *val) {
    if ( _errmsg ) free(_errmsg);
    _errmsg = val ? strdup(val) : NULL;
}
const char *Fl_Native_File_Chooser::errmsg() const {
    return(_errmsg);
}

// Filename
const char* Fl_Native_File_Chooser::filename() const { 
    if ( _tpathnames == 0 ) return("");
    return(_pathnames[0]);
}
const char* Fl_Native_File_Chooser::filename(int i) const { 
    if ( _tpathnames == 0 || i >= _tpathnames ) return("");
    return(_pathnames[i]);
}

// Preset Directory
void Fl_Native_File_Chooser::preset_dirname(const char *val) {
    if ( _preset_dirname ) free(_preset_dirname);
    _preset_dirname = val ? strdup(val) : NULL;
}
const char* Fl_Native_File_Chooser::preset_dirname() const {
    return(_preset_dirname);
}

// Title
void Fl_Native_File_Chooser::title(const char *val) {
    if ( _title ) free(_title);
    _title = val ? strdup(val) : NULL;
}
const char* Fl_Native_File_Chooser::title() const {
    return(_title);
}

// Filter
const char *Fl_Native_File_Chooser::filter() const {
    return(_filter);
}
void Fl_Native_File_Chooser::filter(const char *val) {
    if ( _filter ) free(_filter);
    _filter = val ? strdup(val) : NULL;
}

// Show the file browser
int Fl_Native_File_Chooser::show() { 
    int fctype = Fl_File_Chooser::SINGLE;
    switch ( btype ) {
	case BROWSE_FILE:
	    fctype = Fl_File_Chooser::SINGLE;
	    break;
	case BROWSE_DIRECTORY:
	    fctype = Fl_File_Chooser::DIRECTORY;
	    break;
	case BROWSE_MULTI_FILE:
	    fctype = Fl_File_Chooser::MULTI;
	    break;
	case BROWSE_MULTI_DIRECTORY:
	    fctype = Fl_File_Chooser::MULTI | Fl_File_Chooser::DIRECTORY;
	    break;
	case BROWSE_SAVE_FILE:
	    fctype = Fl_File_Chooser::CREATE;
	    break;
    }

    // Open file chooser, block until user picks something
    Fl_File_Chooser chooser(_preset_dirname ? _preset_dirname : ".",
			    _filter ? _filter : "All Files (*)",
			    fctype,
			    _title ? _title : "File Chooser");
    chooser.show();
    while(chooser.shown()) {
	Fl::wait();
    }

    // User hit cancel?
    if ( chooser.value() == NULL ) {
	return(1);
    }

    // Get all pathnames user picked
    if ( chooser.count() < 1 ) {
	set_single_pathname(chooser.value());
    } else {
	clear_pathnames();
	_pathnames = (char**)malloc(sizeof(char*)*chooser.count());
	for ( _tpathnames=0; _tpathnames<chooser.count(); _tpathnames++ ) {
	    _pathnames[_tpathnames] = strdup(chooser.value(_tpathnames+1));
	}
    }

    // Get directory user was in at the time
    preset_dirname(chooser.directory());

    return(0);
}
