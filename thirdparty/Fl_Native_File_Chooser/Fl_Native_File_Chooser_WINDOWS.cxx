//
// Fl_Native_File_Chooser_WINDOWS.cxx -- FLTK native OS file chooser widget
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

// CTOR
Fl_Native_File_Chooser::Fl_Native_File_Chooser() {
    Ctor(BROWSE_FILE);
}

// CTOR
Fl_Native_File_Chooser::Fl_Native_File_Chooser(enum Type val) {
    Ctor(val);
}

// DTOR
Fl_Native_File_Chooser::~Fl_Native_File_Chooser() {
    if ( _errmsg ) free(_errmsg);
    clear_pathnames();
    ClearOFN();
    ClearBINF();
}

void Fl_Native_File_Chooser::type(Fl_Native_File_Chooser::Type val) {
    btype = val;
}

// ADD A PATTERN TO WINDOWS 'DOUBLENULL' STRING
static void AddPattern(char* &wp, const char *name, const char *patt) {
    strcat(wp, name); wp += strlen(wp)+1; *wp = 0;
    strcat(wp, patt); wp += strlen(wp)+1; *wp = 0;
}

#ifdef DEBUG
// DUMP WINDOWS 'DOUBLENULL' STRING (DEBUG)
static void DumpDoubleNull(char *wp, size_t len) {
    for ( size_t t=0; t<len; t++ )
    {
        if ( wp[t]==0 ) fprintf(stderr, "000");
        else            fprintf(stderr, "<%c>",wp[t]);
        fprintf(stderr, (t%8==7||t==len-1)?"\n":" ");
    }
    fprintf(stderr, "\n");
}
#endif /*DEBUG*/

// CONVERT FLTK STYLE PATTERN MATCHES TO WINDOWS 'DOUBLENULL' PATTERN
//    Caller must free() the returned value when done.
//    Handles:
//        *.{ma,mb} -> *.ma;*.mb
//        *.{ma|mb} -> *.ma;*.mb
//        *.[abc]   -> *.a;*.b;*.c
//        *.c       -> *.c
//    Example:
//         IN: "*.{ma,mb}"
//        OUT: "*.ma;*.mb\0*.ma;*.mb\0All Files\0*.*\0"
//
static char *fltk2win_filter(const char *flpat) {
    char winpat[512]   = "";    // resulting windows pattern
    char setprefix[80] = "";    // wildcard component
    char setitem[40]   = "";    // set items
    char comp[512]     = "";    // composite
    char *wp = winpat;
    char *sp = setprefix;
    char *si = setitem;
    char mode = 0;      			// 0=none, '{'=braced, '['=bracketed
    for ( ; *flpat; flpat++ ) {
        switch(*flpat) {
            case '{':				// start braced set? "{cxx,cpp}"
            case '[':				// start bracketed set? "[abc]"
                mode = *flpat;
                continue;
            case '}': {				// end of braced set?
                if ( mode != '{' ) goto regchar;
                if ( comp[0] ) strcat(comp, ";");
                strcat(comp, setprefix);
                strcat(comp, setitem);
                mode = 0;
                setitem[0] = 0; si = setitem;
                continue;
            }
            case ']':				// end of bracketed set?
                if ( mode != '[' )		// ']' only special in []'s
		    goto regchar;
                mode = 0;
                continue;
            case ',':				// set's item separators?
            case '|':
                if ( mode != '{' )		// ',|' only special in {}'s
		    goto regchar;
                if ( comp[0] ) strcat(comp, ";");
                strcat(comp, setprefix);
                strcat(comp, setitem);
                setitem[0] = 0; si = setitem;
                continue;
            case '\\':				// escape next char?
                ++flpat;
                goto regchar;
            default:				// all other 'regular chars'
            regchar:
                if ( mode == '{' ) {		// braced set?
                    *si++ = *flpat; *si = 0;	// add to item accumulator
                } else if ( mode == '[' ) {	// bracketed set?
                    *si++ = *flpat; *si = 0;	// add item, build pattern
                    if ( comp[0] ) strcat(comp, ";");
                    strcat(comp, setprefix);
                    strcat(comp, setitem);
                    setitem[0] = 0; si = setitem;
                } else {
                    *sp++ = *flpat; *sp = 0;	// regular char? Add to prefix accum
                }
                continue;
        }
    }
    // LEFTOVER COMPOSITE PATTERN? ADD IT
    if ( comp[0] ) AddPattern(wp, comp, comp);                  // *.ma;*.mb
    else           AddPattern(wp, setprefix, setprefix);        // *.c
    // ADD "ALL FILES" PATTERN
    AddPattern(wp, "All Files", "*.*");
    // MAKE COPY OF DOUBLE NULL STRING -- NO STRDUP!
    size_t len = (int)(wp - winpat) + 1;
    char *copy = (char*)malloc(len);
    memcpy(copy, winpat, len);
#ifdef DEBUG
    DumpDoubleNull(copy, len);
#endif/*DEBUG*/
    return(copy);
}

// PRIVATE: SET ERROR MESSAGE
void Fl_Native_File_Chooser::errmsg(const char *msg) {
    if ( _errmsg ) free(_errmsg);
    _errmsg = strdup(msg);
}

// FREE PATHNAMES ARRAY, IF IT HAS ANY CONTENTS
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

void Fl_Native_File_Chooser::set_single_pathname(const char *s) {
    clear_pathnames();
    _pathnames = (char**)malloc(sizeof(char*));
    _pathnames[0] = strdup(s);
    _tpathnames = 1;
}

void Fl_Native_File_Chooser::add_pathname(const char *s) {
    ++_tpathnames;
    if ( ! _pathnames ) {
	_pathnames = (char**)malloc(sizeof(char*));
    } else {
	_pathnames = (char**)realloc((void*)_pathnames, sizeof(char*) * _tpathnames);
    }
    _pathnames[_tpathnames-1] = strdup(s);
}

void Fl_Native_File_Chooser::Ctor(Fl_Native_File_Chooser::Type type) {
    btype            = type;
    memset((void*)&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = NULL;
    memset((void*)&binf, 0, sizeof(BROWSEINFO));
    _pathnames       = NULL;
    _tpathnames      = 0;
    _preset_dirname  = NULL;
    _title           = NULL;
    _filter          = NULL;
    _errmsg          = NULL;
}

void Fl_Native_File_Chooser::FreePIDL(ITEMIDLIST *pidl) {
    IMalloc *imalloc = NULL;
    if ( SUCCEEDED(SHGetMalloc(&imalloc)) )
	{ imalloc->Free(pidl); imalloc->Release(); imalloc = NULL; }
}

void Fl_Native_File_Chooser::ClearOFN() {
    // Free any previously allocated lpstrFile before zeroing out ofn
    if ( ofn.lpstrFile ) 
	{ free((void*)ofn.lpstrFile); ofn.lpstrFile = NULL; }
    if ( ofn.lpstrInitialDir ) 
	{ free((void*)ofn.lpstrInitialDir); ofn.lpstrInitialDir = NULL; }
    if ( ofn.lpstrFilter ) 
	{ free((void*)ofn.lpstrFilter); ofn.lpstrFilter = NULL; }
    memset((void*)&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
}

void Fl_Native_File_Chooser::ClearBINF() {
    if ( binf.pidlRoot ) {
	FreePIDL((ITEMIDLIST*)binf.pidlRoot);
	binf.pidlRoot = NULL;
    }
    memset((void*)&binf, 0, sizeof(binf));
}

void Fl_Native_File_Chooser::Win2Unix(char *s) {
    for ( ; *s; s++ )
	if ( *s == '\\' ) *s = '/';
}

void Fl_Native_File_Chooser::Unix2Win(char *s) {
    for ( ; *s; s++ )
	if ( *s == '/' ) *s = '\\';
}

// SHOW FILE BROWSER
int Fl_Native_File_Chooser::showfile() {
    ClearOFN();
    clear_pathnames();
    size_t fsize = 1024;
    ofn.Flags |= OFN_NOVALIDATE;	// prevent disabling of front slashes
    ofn.Flags |= OFN_HIDEREADONLY;	// hide goofy readonly flag
    // USE NEW BROWSER
    ofn.Flags |= OFN_EXPLORER;		// use newer explorer windows
//	// USE OLD BROWSER
//	ofn.lpfnHook = MyHook;
//	ofn.Flags |= OFN_ENABLEHOOK;
    switch (btype) {
	case BROWSE_DIRECTORY:
	case BROWSE_MULTI_DIRECTORY:
	    abort();			// not here
	case BROWSE_FILE:
	    fsize = 65536;		// XXX: there must be a better way
	    break;
	case BROWSE_MULTI_FILE:
	    ofn.Flags |= OFN_ALLOWMULTISELECT;
	    fsize = 65536;		// XXX: there must be a better way
	    break;
	case BROWSE_SAVE_FILE:
	    // TBD
	    break;
    }
    // SPACE FOR RETURNED FILENAME
    ofn.lpstrFile    = (char*)malloc(fsize);
    ofn.lpstrFile[0] = 0;
    ofn.nMaxFile     = fsize-1;
    // PARENT WINDOW
    ofn.hwndOwner = GetForegroundWindow();
    // DIALOG TITLE
    ofn.lpstrTitle = _title ? _title : NULL;
    // FILTER
    ofn.lpstrFilter = _filter ? fltk2win_filter(_filter) : NULL;
    // PRESET DIR
    if ( _preset_dirname ) {
	ofn.lpstrInitialDir = strdup(_preset_dirname);
	Unix2Win((char*)ofn.lpstrInitialDir);
    }
    int err;
    if ( btype == BROWSE_SAVE_FILE ) {
	// OPEN DIALOG
	err = GetSaveFileName(&ofn);
    } else {
	// OPEN DIALOG
	err = GetOpenFileName(&ofn);
    }
    if ( err == 0 ) {
	// EXTENDED ERROR CHECK
	int err = CommDlgExtendedError();
	// CANCEL?
	if ( err == 0 ) 
	    return(1);	// user hit 'cancel'
	// AN ERROR OCCURRED
	char msg[80];
	sprintf(msg, "CommDlgExtendedError() code=%d", err);
	errmsg(msg);
	return(-1);
    }
    // PREPARE PATHNAMES FOR RETURN
    switch ( btype ) {
	case BROWSE_FILE: 
	case BROWSE_SAVE_FILE:
	    set_single_pathname(ofn.lpstrFile);
	    Win2Unix(_pathnames[_tpathnames-1]);
	    break;
	case BROWSE_MULTI_FILE: {
	    // EXTRACT MULTIPLE FILENAMES
	    const char *dirname = ofn.lpstrFile;
	    int dirlen = strlen(dirname);
	    if ( dirlen > 0 ) {
		char pathname[1024];

		// WALK STRING SEARCHING FOR 'DOUBLE-NULL'
		//     eg. "/dir/name\0foo1\0foo2\0foo3\0\0"
		//
		for ( const char *s = ofn.lpstrFile + dirlen + 1; *s; s+= (strlen(s)+1)) {
		    strcpy(pathname, dirname);
		    strcat(pathname, "\\");
		    strcat(pathname, s);
		    add_pathname(pathname);
		    Win2Unix(_pathnames[_tpathnames-1]);
		}
	    }
	    // XXX
	    //    Work around problem where someone pastes a forward-slash pathname
	    //    into the file browser. For some reason, the new "Explorer" interface
	    //    doesn't grok forward slashes, passing them back as a 'filename'..!
	    //
	    if ( _tpathnames == 0 )
	    {
		add_pathname(dirname); 
		Win2Unix(_pathnames[_tpathnames-1]);
	    }
	    break;
	}
	case BROWSE_DIRECTORY:
	case BROWSE_MULTI_DIRECTORY:
	    abort();			// not here
    }
    return(0);
}
// Used by SHBrowseForFolder(), sets initial selected dir.
// Ref: Usenet: microsoft.public.vc.mfc, Dec 8 2000, 1:38p David Lowndes
//              Subject: How to specify to select an initial folder .."
//
int CALLBACK Fl_Native_File_Chooser::SetSelect_CB(HWND win, UINT msg, LPARAM param, LPARAM data) {
    if ( msg == BFFM_INITIALIZED ) {
	::SendMessage(win, BFFM_SETSELECTION, TRUE, data);
    }
    return(0);
}
// SHOW DIRECTORY BROWSER
int Fl_Native_File_Chooser::showdir() {
    static int oleinit = 0;
    if ( ! oleinit ) {
	oleinit = 1;
	OleInitialize(NULL);	// init needed by BIF_USENEWUI
    }
    ClearBINF();
    clear_pathnames();
    // PARENT WINDOW
    binf.hwndOwner = GetForegroundWindow();
    // DIALOG TITLE
    binf.lpszTitle = _title ? _title : NULL;
    // FLAGS
//    binf.ulFlags |= BIF_SHAREABLE | BIF_USENEWUI;
    // BUFFER
    char displayname[MAX_PATH];
    binf.pszDisplayName = displayname;
    // PRESET DIR
    char presetname[MAX_PATH];
    if ( _preset_dirname ) {
	strcpy(presetname, _preset_dirname);
	Unix2Win(presetname);
	binf.lpfn = SetSelect_CB;
	binf.lParam = (LPARAM)presetname;
    }
    // OPEN BROWSER
    ITEMIDLIST *pidl = SHBrowseForFolder(&binf);
    // CANCEL?
    if ( pidl == NULL ) return(1);
    // GET THE PATHNAME(S) THE USER SELECTED
    TCHAR path[MAX_PATH];
    if ( SHGetPathFromIDList(pidl, path) )
	{ Win2Unix(path); add_pathname(path); }
    FreePIDL(pidl);
    return(0);
}

// RETURNS:
//    0 - user picked a file
//    1 - user cancelled
//   -1 - failed; errmsg() has reason
//
int Fl_Native_File_Chooser::show() {
    if ( btype == BROWSE_DIRECTORY || btype == BROWSE_MULTI_DIRECTORY )
	return(showdir());
    else
	return(showfile());
}

// RETURN ERROR MESSAGE
const char *Fl_Native_File_Chooser::errmsg() {
    return(_errmsg?_errmsg:"No error");
}

// GET FILENAME
const char* Fl_Native_File_Chooser::filename() const {
    if ( _pathnames && _tpathnames > 0 ) return(_pathnames[0]);
    return("");
}

// GET FILENAME FROM LIST OF FILENAMES
const char* Fl_Native_File_Chooser::filename(int i) const {
    if ( _pathnames && i < _tpathnames ) return(_pathnames[i]);
    return("");
}

// GET TOTAL FILENAMES CHOSEN
int Fl_Native_File_Chooser::total_filenames() const {
    return(_tpathnames);
}

// PRESET PATHNAME
//     Can be NULL if no preset is desired.
//
void Fl_Native_File_Chooser::preset_dirname(const char *val) {
    if ( _preset_dirname ) free(_preset_dirname);
    _preset_dirname = (val) ? strdup(val) : NULL;
}

// GET PRESET PATHNAME
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::preset_dirname() const {
    return(_preset_dirname);
}
// SET TITLE
//     Can be NULL if no title desired.
//
void Fl_Native_File_Chooser::title(const char *val) {
    if ( _title ) free(_title);
    _title = (val) ? strdup(val) : NULL;
}

// GET TITLE
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::title() const {
    return(_title);
}

// SET FILTER
//     Can be NULL if no filter needed
//
void Fl_Native_File_Chooser::filter(const char *val) {
    if ( _filter ) free(_filter);
    _filter = (val) ? strdup(val) : NULL;
}

// GET FILTER
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::filter() const {
    return(_filter);
}

