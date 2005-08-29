//
// Fl_Native_File_Chooser_WINDOWS.cxx -- FLTK native OS file chooser widget
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

// http://www.codeproject.com/dialog/selectfolder.asp - any application to multi-folder implementation?

#include "Fl_Native_File_Chooser_WIN32.H"

// CTOR
Fl_Native_File_Chooser::Fl_Native_File_Chooser() {
    Ctor(BROWSE_FILE);
}

// CTOR
Fl_Native_File_Chooser::Fl_Native_File_Chooser(Type val) {
    Ctor(val);
}

// DTOR
Fl_Native_File_Chooser::~Fl_Native_File_Chooser() {
    if ( _errmsg ) free(_errmsg);
    if (_parsedfilt)  delete [] _parsedfilt;
    if (_filter) delete [] _filter;
    clear_pathnames();
    ClearOFN();
    ClearBINF();
}

void Fl_Native_File_Chooser::type(Type val) {
    btype = val;
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

void Fl_Native_File_Chooser::Ctor(Type type) {
    btype            = type;
    memset((void*)&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = NULL;
    memset((void*)&binf, 0, sizeof(BROWSEINFO));
    _pathnames       = NULL;
    _tpathnames      = 0;
    _directory       = NULL;
    _title           = NULL;
    _filter          = NULL;
    _parsedfilt      = NULL;
   _preset_file      = NULL;
    _errmsg          = NULL;
    _nfilters        = 0;
}

void Fl_Native_File_Chooser::FreePIDL(ITEMIDLIST *pidl) {
    IMalloc *imalloc = NULL;
    if ( SUCCEEDED(SHGetMalloc(&imalloc)) )
	{ imalloc->Free(pidl); imalloc->Release(); imalloc = NULL; }
}

void Fl_Native_File_Chooser::ClearOFN() {
    int temp;

    // Free any previously allocated lpstrFile before zeroing out ofn
    if ( ofn.lpstrFile ) 
	{ free((void*)ofn.lpstrFile); ofn.lpstrFile = NULL; }
    if ( ofn.lpstrInitialDir ) 
	{ free((void*)ofn.lpstrInitialDir); ofn.lpstrInitialDir = NULL; }
    ofn.lpstrFilter = NULL;  // (deleted elsewhere)
    temp=ofn.nFilterIndex;   // keep the set_filter
    memset((void*)&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.nFilterIndex=temp;
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
	case BROWSE_SAVE_DIRECTORY:
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
    if (_preset_file) strcpy(ofn.lpstrFile,_preset_file);
    else ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile     = fsize-1;
    // PARENT WINDOW
    ofn.hwndOwner = GetForegroundWindow();
    // DIALOG TITLE
    ofn.lpstrTitle = _title ? _title : NULL;
    // FILTER
    ofn.lpstrFilter = _parsedfilt ? _parsedfilt : NULL;
    // PRESET DIR
    if ( _directory ) {
	ofn.lpstrInitialDir = strdup(_directory);
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
	case BROWSE_SAVE_DIRECTORY:
	    abort();			// not here
    }
    return(0);
}
// Used by SHBrowseForFolder(), sets initial selected dir.
// Ref: Usenet: microsoft.public.vc.mfc, Dec 8 2000, 1:38p David Lowndes
//              Subject: How to specify to select an initial folder .."
//
int CALLBACK Fl_Native_File_Chooser::Dir_CB(HWND win, UINT msg, LPARAM param, LPARAM data) {
  switch (msg) {
    case BFFM_INITIALIZED:
     if (data) ::SendMessage(win, BFFM_SETSELECTION, TRUE, data);
   case BFFM_SELCHANGED:
     TCHAR path[MAX_PATH];
     if ( SHGetPathFromIDList((ITEMIDLIST*)param, path) ) ::SendMessage(win, BFFM_ENABLEOK, 0, 1);
     else ::SendMessage(win, BFFM_ENABLEOK, 0, 0);					//disable ok button if not a path
   case BFFM_VALIDATEFAILED:
    // we could pop up an annoying message here. also needs set ulFlags |=  BIF_VALIDATE
    break;
   default:
    break;
 }
 return 0;
}

// SHOW DIRECTORY BROWSER
int Fl_Native_File_Chooser::showdir() {
    OleInitialize(NULL);	// init needed by BIF_USENEWUI

    ClearBINF();
    clear_pathnames();
    // PARENT WINDOW
    binf.hwndOwner = GetForegroundWindow();
    // DIALOG TITLE
    binf.lpszTitle = _title ? _title : NULL;
    // FLAGS
    binf.ulFlags =0; 		// initialize

// TBD: make sure matches to runtime system, if need be. ( what if _WIN32_IE doesn't match system? does the program not run? )
// TBD: match all 3 types of directories

#if defined(BIF_NONEWFOLDERBUTTON)					// Version 6.0
    if ( btype == BROWSE_DIRECTORY ) binf.ulFlags |= BIF_NONEWFOLDERBUTTON;
    binf.ulFlags |= USENEWUI | BIF_SHAREABLE | BIF_RETURNONLYFSDIRS;
#elif defined(BIF_USENEWUI)						// Version 5.0
    if ( btype == BROWSE_DIRECTORY ) binf.ulFlags |= BIF_EDITBOX;
    else if ( btype == BROWSE_SAVE_DIRECTORY ) binf.ulFlags |= BIF_USENEWUI;
    binf.ulFlags |= BIF_SHAREABLE | BIF_RETURNONLYFSDIRS;
#elif defined(BIF_EDITBOX)						// Version 4.71
    binf.ulFlags |= BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
#else									// Version Old
    binf.ulFlags |= BIF_RETURNONLYFSDIRS;
#endif


    // BUFFER
    char displayname[MAX_PATH];
    binf.pszDisplayName = displayname;
    // PRESET DIR
    char presetname[MAX_PATH];
    if ( _directory ) {
	strcpy(presetname, _directory);
	Unix2Win(presetname);
	binf.lParam = (LPARAM)presetname;
    }
    else binf.lParam = 0;
    binf.lpfn = Dir_CB;
    // OPEN BROWSER
    ITEMIDLIST *pidl = SHBrowseForFolder(&binf);
    // CANCEL?
    if ( pidl == NULL ) return(1);

    // GET THE PATHNAME(S) THE USER SELECTED
    // TBD: expand NetHood shortcuts from this PIDL??
    // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/shellcc/platform/shell/reference/functions/shbrowseforfolder.asp

    TCHAR path[MAX_PATH];
    if ( SHGetPathFromIDList(pidl, path) )
	{ Win2Unix(path); add_pathname(path); }
    FreePIDL(pidl);
    if ( !strlen(path) ) return(1);             // don't return empty pathnames
    return(0);
}

// RETURNS:
//    0 - user picked a file
//    1 - user cancelled
//   -1 - failed; errmsg() has reason
//
int Fl_Native_File_Chooser::show() {
    if ( btype == BROWSE_DIRECTORY || btype == BROWSE_MULTI_DIRECTORY || btype == BROWSE_SAVE_DIRECTORY )
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
int Fl_Native_File_Chooser::count() const {
    return(_tpathnames);
}

// PRESET PATHNAME
//     Can be NULL if no preset is desired.
//
void Fl_Native_File_Chooser::directory(const char *val) {
    if ( _directory ) free(_directory);
    _directory = (val) ? strdup(val) : NULL;
}

// GET PRESET PATHNAME
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::directory() const {
    return(_directory);
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
    if (_parsedfilt) { delete [] _parsedfilt; }
    if (_filter) delete [] _filter;

    if ( !val ) {
     _nfilters=0;
     _filter = NULL;
     _parsedfilt = NULL;
     return;
    }

    _filter = new char[strlen(val)+1];
    strcpy(_filter,val);                     //copy incoming filter to our storage

    _parsedfilt=parse_filter();
    //DumpDoubleNull(_parsedfilt);
}

// GET FILTER
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::filter() const {
    return(_filter);
}

// expects "Description\tfilter\n[...]"

char *Fl_Native_File_Chooser::parse_filter() {
 int i;		// !! some compilers don't like this declared in loop scope?
 _nfilters = 0;
 for(i=0; i<(int)strlen(_filter); i++) if ( _filter[i]=='\t' ) ++_nfilters;

 char* ptr=_filter;
 char* parsed = new char[1024];   // TBD: size calc??? oiyyy...

 char* parptr=parsed;
 parptr[0]='\0';

 char* inpat;
 char outpat[512];

 for (i=0; i<_nfilters; i++) {        // parse each filter string
  char* end;
  end=strchr(ptr,'\t');
  if(!end) break;                         // if not found, continue peacefully
  nullncat(parptr,ptr,end-ptr);           // add description part to outgoing filter
  ptr=end+1;
  end=strchr(end,'\n');
  if(!end) end=_filter+strlen(_filter);
  inpat = new char[end-ptr+1];
  strncpy(inpat,ptr,end-ptr);
  inpat[end-ptr]='\0';
  ptr=end+1;
  fltk2win_filter(inpat,outpat);          // expand [], {}, and such
  delete [] inpat;
  nullcat(parptr,outpat);                 // add expanded filter part to outgoing filter
 }
 // ADD "ALL FILES" PATTERN
 nullcat(parptr, "All Files");
 nullcat(parptr, "*.*");
 nullcat(parptr,"\0");  //!!              //add double null termination

 return parsed;
}



// DUMP WINDOWS 'DOUBLENULL' STRING (DEBUG)
// TBD: add back debug #ifdefs
void Fl_Native_File_Chooser::DumpDoubleNull(char *wp) {
    bool prevnull=false;

    for ( int t=0; true; t++ )
    {
        if ( wp[t]==0 ) { printf("\\0"); if (prevnull) break; else prevnull=true; }
        else            { prevnull=false; printf("%c",wp[t]); }
    }
    printf("\n");
 fflush(stdout);
}


// CONVERT FLTK STYLE PATTERN MATCHES TO WINDOWS 'DOUBLENULL' PATTERN
//    Handles:
//        *.{ma,mb} -> *.ma;*.mb
//        *.{ma|mb} -> *.ma;*.mb
//        *.[abc]   -> *.a;*.b;*.c
//        *.c       -> *.c
//    Example:
//         IN: "*.{ma,mb}"
//        OUT: "*.ma;*.mb\0*.ma;*.mb\0All Files\0*.*\0"
//
void Fl_Native_File_Chooser::fltk2win_filter(const char *flpat, char* to) {
    char setprefix[80] = "";    // wildcard component
    char setitem[40]   = "";    // set items
    char comp[512]     = "";    // composite
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
    // COPY OUT CORRECT EXPANSION
    if ( comp[0] ) strcpy(to, comp);                  // *.ma;*.mb
    else           strcpy(to, setprefix);             // *.c

}

// SET OR RETURN SELECTED FILTER
void Fl_Native_File_Chooser::set_filter(int i) {
 ofn.nFilterIndex=i+1;
}
int Fl_Native_File_Chooser::set_filter() {
 return ofn.nFilterIndex ? ofn.nFilterIndex-1 : _nfilters+1;
}

void Fl_Native_File_Chooser::preset_file(const char* val) {
 if ( _preset_file ) free(_preset_file);
 _preset_file = (val) ? strdup(val) : NULL;
}

const char*  Fl_Native_File_Chooser::preset_file() {
 return _preset_file;
}


