//
// Fl_Native_File_Chooser_MAC.cxx -- FLTK native OS file chooser widget
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

// Reference:
//     Top Level: http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_concepts/chapter_2_section_2.html#//apple_ref/doc/uid/TP30001147-CH202-CHDEDCBD
//     Functions: http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_tasks/chapter_3_section_3.html#//apple_ref/doc/uid/TP30001147-CH203-BEIGBDGD
//     Nav Tasks: http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_tasks/chapter_3_section_1.html#//apple_ref/doc/uid/TP30001147-CH203-BABGIAGG
//     Preload: http://groups.google.com/groups?q=NavCreateGetFileDialog+directory&hl=en&lr=&c2coff=1&selm=oster-A486E7.08390422102002%40newssvr21-ext.news.prodigy.com&rnum=1
//              http://developer.apple.com/qa/qa2001/qa1151.html
//     CFString: file:///Developer/Documentation/CoreFoundation/Reference/CFStringRef/index.html#//apple_ref/doc/uid/20001211
//

// CONVERT AN FSSpec TO A PATHNAME
static void FSSpecToPath(const FSSpec &spec, char *buff, int bufflen) {
    FSRef fsRef;
    FSpMakeFSRef(&spec, &fsRef);
    FSRefMakePath(&fsRef, (UInt8*)buff, bufflen);
}

// CONVERT REGULAR PATH -> FSSpec
//     Note: file (or directory) must /exist/
//
static OSStatus PathToFSSpec(const char *path, FSSpec &spec) {
    OSStatus err;
    FSRef ref;
    if ((err=FSPathMakeRef((const UInt8*)path, &ref, NULL)) != noErr)
	return(err);
    // FSRef -> FSSpec
    if ((err=FSGetCatalogInfo(&ref, kFSCatInfoNone, NULL, NULL, 
    			      &spec, NULL)) != noErr)
	return(err);
    return(noErr);
}

Fl_Native_File_Chooser::NavReply::NavReply() {
    valid = 0;
}

// DTOR
Fl_Native_File_Chooser::NavReply::~NavReply() {
    if ( valid ) {
	NavDisposeReply(&reply);
    }
}

// GET REPLY FROM THE NAV* DIALOG
int Fl_Native_File_Chooser::NavReply::get_reply(NavDialogRef& ref) {
    if ( valid ) {
	NavDisposeReply(&reply);	// dispose of previous
	valid = 0;
    }
    if ( NavDialogGetReply(ref, &reply) != noErr ) {
	return(-1);
    }
    valid = 1;
    return(0);
}

// RETURN THE BASENAME USER WANTS TO 'SAVE AS'
int Fl_Native_File_Chooser::NavReply::get_saveas_basename(char *s, int slen) {
    if (CFStringGetCString(reply.saveFileName, s, slen-1, 
			   kCFStringEncodingUTF8) == false) {
	s[0] = '\0';
	return(-1);
    }
    return(0);
}

// RETURN THE DIRECTORY NAME
int Fl_Native_File_Chooser::NavReply::get_dirname(char *s, int slen) {
    AEDesc desc;
    FSSpec fsspec;
    // GOD KNOWS WHAT THIS IS ALL ABOUT
    if (AECoerceDesc(&reply.selection, typeFSS, &desc) == noErr) {
	AEGetDescData(&desc, &fsspec, sizeof(FSSpec));
	AEDisposeDesc(&desc);
    } else {
	// HUH?
	if (AECoerceDesc(&reply.selection, typeFSRef, &desc) == noErr) {
	    FSRef ref;
	    // I DON'T KNOW
	    if (AEGetDescData(&desc, &ref, sizeof(FSRef)) == noErr) {
		FSGetCatalogInfo(&ref, kFSCatInfoGettableInfo, NULL, 
				 NULL, &fsspec, NULL);
	    } else {
		AEDisposeDesc(&desc);
		s[0] = 0;
		return(-1);
	    }
	    AEDisposeDesc(&desc);
	} else {
	    s[0] = 0;
	    return(-1);
	}
    }
    // THAT WAS FUN
    FSSpecToPath(fsspec, s, slen);
    return(0);
}

// RETURN MULTIPLE DIRECTORIES
// RETURNS:
//     -1 on error
//      0 if OK, pathnames[] will contain the pathnames selected
//
int Fl_Native_File_Chooser::NavReply::get_pathnames(char **&pathnames, 
						    int& tpathnames) {
    char s[512];
    // How many items selected?
    long count = 0;
    if ( AECountItems(&reply.selection, &count) != noErr ) 
	{ return(-1); }
    // Allocate space for that many pathnames
    pathnames = (char**)malloc(count * sizeof(char*));
    memset((void*)pathnames, 0, count*sizeof(char*));
    tpathnames = count;
    // Walk list of pathnames selected
    for (short index=1; index<=count; index++) {
	AEKeyword keyWord;
	AEDesc    desc;
	if (AEGetNthDesc(&reply.selection, index, typeFSS, 
			 &keyWord, &desc) != noErr) {
	    pathnames[index-1] = strdup("");
	    continue;
	}
	FSSpec fsspec;
	if (AEGetDescData(&desc, &fsspec, sizeof(FSSpec)) != noErr ) {
	    pathnames[index-1] = strdup("");
	    continue;
	}
	FSSpecToPath(fsspec, s, sizeof(s)-1);
	pathnames[index-1] = strdup(s);
	AEDisposeDesc(&desc);
    }
    return(0);
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

// GET THE 'SAVE AS' FILENAME
// Returns:
//    -1 -- error, errmsg() has reason, filename == ""
//     0 -- OK, filename() has filename chosen
//
int Fl_Native_File_Chooser::get_saveas_basename(NavDialogRef& ref) {
    NavReply reply;
    OSStatus err;
    if ((err=reply.get_reply(ref)) != noErr ) {
	errmsg("NavReply::get_reply() failed");
	clear_pathnames();
	return(-1);
    }

    char pathname[1024] = "";
    // Directory name..
    if ( reply.get_dirname(pathname, sizeof(pathname)) < 0 ) {
	clear_pathnames();
	errmsg("NavReply::get_dirname() failed");
	return(-1);
    }
    // Append '/'
    int len = strlen(pathname);
    pathname[len++] = '/';
    pathname[len] = '\0';
    // Basename..
    if ( reply.get_saveas_basename(pathname+len, sizeof(pathname)-len) < 0 ) {
	clear_pathnames();
	errmsg("NavReply::get_saveas_basename() failed");
	return(-1);
    }
    set_single_pathname(pathname);
    return(0);
}

// GET (POTENTIALLY) MULTIPLE FILENAMES
// Returns:
//    -1 -- error, errmsg() has reason, filename == ""
//     0 -- OK, pathnames()/filename() has pathname(s) chosen
//
int Fl_Native_File_Chooser::get_pathnames(NavDialogRef& ref) {
    NavReply reply;
    OSStatus err;
    if ((err=reply.get_reply(ref)) != noErr ) { 
	errmsg("NavReply::get_reply() failed");
	clear_pathnames();
	return(-1);
    }
    // First, /clear/ pathnames array of any previous contents
    clear_pathnames();
    if ( reply.get_pathnames(_pathnames, _tpathnames) < 0 ) {
	clear_pathnames();
	errmsg("NavReply::get_dirname() failed");
	return(-1);
    }
    return(0);
}

// Nav callback event handler
void Fl_Native_File_Chooser::event_handler(
		NavEventCallbackMessage callBackSelector, 
		NavCBRecPtr cbparm, void *data) {
    OSStatus err;
    Fl_Native_File_Chooser *nfb = (Fl_Native_File_Chooser*)data;
    switch (callBackSelector) {
	case kNavCBStart:
	    if ( nfb->preset_dirname() ) {
		FSSpec spec;
		PathToFSSpec(nfb->preset_dirname(), spec);
		AEDesc desc;
		if ((err=AECreateDesc(typeFSS, &spec, sizeof(FSSpec), 
				      &desc)) != noErr) {
		    fprintf(stderr, "AECreateDesc() failed: err=%d\n", (int)err);
		}
		if ((err=NavCustomControl(cbparm->context, kNavCtlSetLocation, 
					  &desc)) != noErr) {
		    fprintf(stderr, "NavCustomControl() failed: err=%d\n", 
			(int)err);
		}
		AEDisposeDesc(&desc);
	    }
	    break;
    }
}

Fl_Native_File_Chooser::Fl_Native_File_Chooser() {
    btype           = BROWSE_FILE;
    nftypes         = 0;
    ftypes          = NULL;
    NavGetDefaultDialogCreationOptions(&opts);
    memset(&ref, 0, sizeof(ref));
    _pathnames      = NULL;
    _tpathnames     = 0;
    _title          = NULL;
    _filter         = NULL;
    _preset_dirname = NULL;
    _preset_dirname = NULL;
    _errmsg         = NULL;
}

// Destructor
Fl_Native_File_Chooser::~Fl_Native_File_Chooser() {
    if ( _errmsg ) free(_errmsg);
    _errmsg = NULL;
    if ( _title ) free(_title);
    _title = NULL;
    if ( _filter ) free(_filter);
    _filter = NULL;
    NavDialogDispose(ref);
    if ( ftypes ) DisposeHandle((Handle)ftypes);
    clear_pathnames();
}

/**** TBD
int Fl_Native_File_Chooser::add_file_type(xyz) {
    if (nftypes>0) {
	(NavTypeListHandle)NewHandle(sizeof(NavTypeList) + 
				     (nftypes-1) * sizeof(OSType));
    }
}
****/

void Fl_Native_File_Chooser::type(Type val) {
    btype = val;
}

// RETURNS:
//    0 - user picked a file
//    1 - user cancelled
//   -1 - failed; errmsg() has reason
//
int Fl_Native_File_Chooser::show() {
    // OPTIONS
    if ( _title ) {
        CFStringRef cfstitle = CFStringCreateWithCStringNoCopy(
	    NULL, _title, kCFStringEncodingASCII, NULL);
	opts.windowTitle = cfstitle;
    }
    // INITIALIZE BROWSER
    OSStatus err;
    switch (btype) {
	case BROWSE_FILE:
	    // Prompt user for a single file
	    if ((err = NavCreateChooseFileDialog(
			  &opts,			// options
			  (nftypes>0)?ftypes:NULL,	// file types
			  event_handler,		// event handler
			  NULL,			// preview callback
			  NULL,			// filter callback
			  (void*)this,		// callback data
			  &ref)) != noErr ) {	// dialog ref
		errmsg("NavCreateChooseFileDialog: failed");
		return(-1);
	    }
	    break;
	case BROWSE_MULTI_FILE:
	    // Prompt user for one or more files
	    if ((err = NavCreateGetFileDialog(
			  &opts,			// options
			  (nftypes>0)?ftypes:NULL,	// file types
			  NULL,			// event handler
			  NULL,			// preview callback
			  NULL,			// filter callback
			  NULL,			// callback data
			  &ref)) != noErr ) {	// dialog ref
		errmsg("NavCreateChooseFileDialog: failed");
		return(-1);
	    }
	    break;
	case BROWSE_DIRECTORY:
	    // Prompts user for a single folder
	    if ((err = NavCreateChooseFolderDialog(
			  &opts,			// options
			  NULL,			// event callback
			  NULL,			// filter callback
			  NULL,			// callback data
			  &ref)) != noErr) {	// dialog ref
		errmsg("NavCreateChooseFolderDialog: failed");
		return(-1);
	    }
	    break;
	case BROWSE_MULTI_DIRECTORY:
	    // Prompts user for one or more files or folders
	    if ((err = NavCreateChooseObjectDialog(
			  &opts,			// options
			  NULL,			// event callback
			  NULL,			// preview callback
			  NULL,			// filter callback
			  NULL,			// callback data
			  &ref)) != noErr ) {	// dialog ref
		errmsg("NavCreateChooseObjectDialog: failed");
		return(-1);
	    }
	    break;
	case BROWSE_SAVE_FILE:
	    // Prompt user for filename to 'save as'
	    if ((err = NavCreatePutFileDialog(
			  &opts,		// options
			  0,			// file types
			  0,			// file creator
			  event_handler,	// event handler
			  (void*)this,		// callback data
			  &ref)) != noErr ) {	// dialog ref
		errmsg("NavCreatePutFileDialog: failed");
		return(-1);
	    }
	    break;
    }
    // SHOW THE DIALOG
    if ( ( err = NavDialogRun(ref) ) != 0 ) {
	char msg[80]; sprintf(msg, "NavDialogRun: failed (err=%d)", (int)err);
	errmsg(msg);
	return(-1);
    }
    // WHAT ACTION DID USER CHOOSE?
    NavUserAction act = NavDialogGetUserAction(ref);
    if ( act == kNavUserActionNone ) {
	errmsg("Nothing happened yet (dialog still open)");
	return(-1);
    }
    else if ( act == kNavUserActionCancel ) { 	// user chose 'cancel'
	 return(1);
    }
    else if ( act == kNavUserActionSaveAs ) {	// user chose 'save as'
	return(get_saveas_basename(ref));
    }
    int ret = get_pathnames(ref);
    // Too many files chosen?
    if (btype == BROWSE_FILE && ret == 0 && _tpathnames != 1) {
	char msg[80];
	sprintf(msg, "Expected only one file to be chosen.. you chose %d.",
	    (int)_tpathnames);
	errmsg(msg);
	return(-1);
    }
    return(err);
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

// PUBLIC: PRESET PATHNAME
void Fl_Native_File_Chooser::preset_dirname(const char *val) {
    if ( _preset_dirname ) free(_preset_dirname);
    _preset_dirname = (val) ? strdup(val) : NULL;
}

// PUBLIC: GET PRESET PATHNAME
//    Can return NULL if none set.
//
const char* Fl_Native_File_Chooser::preset_dirname() {
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

