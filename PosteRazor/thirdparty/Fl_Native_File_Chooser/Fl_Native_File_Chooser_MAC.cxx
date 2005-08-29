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
#include "Fl_Native_File_Chooser_Mac.H"

// Reference:
//     Top Level: http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_concepts/chapter_2_section_2.html#//apple_ref/doc/uid/TP30001147-CH202-CHDEDCBD
//     Functions: http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_tasks/chapter_3_section_3.html#//apple_ref/doc/uid/TP30001147-CH203-BEIGBDGD
//     Nav Tasks: http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_tasks/chapter_3_section_1.html#//apple_ref/doc/uid/TP30001147-CH203-BABGIAGG
//     Preload: http://groups.google.com/groups?q=NavCreateGetFileDialog+directory&hl=en&lr=&c2coff=1&selm=oster-A486E7.08390422102002%40newssvr21-ext.news.prodigy.com&rnum=1
//              http://developer.apple.com/qa/qa2001/qa1151.html
//     CFString: file:///Developer/Documentation/CoreFoundation/Reference/CFStringRef/index.html#//apple_ref/doc/uid/20001211
//
//http://developer.apple.com/documentation/Carbon/Reference/Navigation_Services_Ref/index.html
//http://lists.apple.com/archives/carbon-dev/2005/Feb/msg01230.html
//http://www.mactech.com/macintosh-c/chap18-1.html
//http://developer.apple.com/documentation/Carbon/Reference/Navigation_Services_Ref/nav_serv_ref/chapter_1.4_section_2.html -block New Folder button
//http://developer.apple.com/documentation/Carbon/Reference/Navigation_Services_Ref/nav_serv_ref/chapter_1.4_section_9.html
//http://developer.apple.com/documentation/Carbon/Reference/Navigation_Services_Ref/nav_serv_ref/chapter_1.4_section_6.html
//http://lists.apple.com/archives/nav-serv-developers/2003/Apr/msg00003.html
//http://developer.apple.com/datatype/creatorcode.html
//http://developer.apple.com/documentation/Carbon/Conceptual/ProvidingNavigationDialogs/nsx_tasks/chapter_3_section_3.html
//


// Try to convert an AEDesc to an FSSpec
static int AEDescToFSSpec(const AEDesc* desc, FSSpec* fsspec) {
    AEDesc temp;

    // GOD KNOWS WHAT THIS IS ALL ABOUT
    if (AECoerceDesc(desc, typeFSS, &temp) == noErr) {			// I'm not God, but this attempts to copy the descriptor to a descriptor containing a File System Specification
	AEGetDescData(&temp, fsspec, sizeof(FSSpec));			// if it succeeds, copy the FSSpec out of the new event descriptor
	AEDisposeDesc(&temp);						// we must release our copy of the descriptor
    }
    else {
	if (AECoerceDesc(desc, typeFSRef, &temp) == noErr) {		// Data might be trapped in the clutches of an FSRef
	    FSRef ref;
	    if (AEGetDescData(&temp, &ref, sizeof(FSRef)) == noErr) {
		FSGetCatalogInfo(&ref, kFSCatInfoGettableInfo, NULL, 	// an FSRef is some uber-opaque FSSpec, we must use FSGetCatalogInfo to convert it to an FSSpec
				 NULL, fsspec, NULL);
	    }
	    else {
		AEDisposeDesc(&temp);
                return(-1);
	    }
	    AEDisposeDesc(&temp);
        }
	else return(-1);
    }
    // THAT WAS FUN
    return 0;       // tell the calling function how much fun we had.
}

// CONVERT AN FSSpec TO A PATHNAME
static void FSSpecToPath(const FSSpec &spec, char *buff, int bufflen) {
    FSRef fsRef;
    FSpMakeFSRef(&spec, &fsRef);
    FSRefMakePath(&fsRef, (UInt8*)buff, bufflen);
}

// CONVERT REGULAR PATH -> FSSpec
//     Note: file (or directory) must /exist/      // TBD?: check existence?
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
    FSSpec fsspec;
    
    if ( AEDescToFSSpec(&reply.selection, &fsspec) ) { // check to see if conversion failed
	s[0] = 0;
        return -1;
    }
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
	    if ( nfb->_directory ) {
		 FSSpec spec;
		 PathToFSSpec(nfb->directory(), spec);
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
		if ( nfb->btype == BROWSE_SAVE_FILE && nfb->_preset_file ) {
		 CFStringRef namestr = CFStringCreateWithCString(NULL,nfb->preset_file(),kCFStringEncodingASCII);
		 NavDialogSetSaveFileName(cbparm->context,namestr);
		 CFRelease(namestr);
		}
		NavCustomControl(cbparm->context, kNavCtlSetActionState, &nfb->keepstate );
            
        // Select the right filter in pop-up menu
            if (nfb->_set_filter==nfb->_nfilters) {				// Select All Documents
             NavPopupMenuItem kAll=kNavAllFiles;
             NavCustomControl(cbparm->context, kNavCtlSelectAllType, &kAll );
            }
            else if (nfb->_set_filter<nfb->_nfilters) {			// Select custom filter
                //NavMenuItemSpec tempitem;
                nfb->tempitem.version=kNavMenuItemSpecVersion;
                nfb->tempitem.menuCreator='extn';
                nfb->tempitem.menuType=nfb->_set_filter;
				*nfb->tempitem.menuItemName='\0';				  // needed on 10.3+
                NavCustomControl(cbparm->context, kNavCtlSelectCustomType, &(nfb->tempitem));
            }
	    break;

	case kNavCBPopupMenuSelect:
            NavMenuItemSpecPtr ptr;
            ptr=(NavMenuItemSpecPtr)cbparm->eventData.eventDataParms.param;	// they really buried this one!
            if (ptr->menuCreator) nfb->_set_filter=ptr->menuType;				// This contains the index to the filter ( menuCreator='extn' )
            else nfb->_set_filter=nfb->_nfilters;						// All documents filter selected ( menuCreator='\0\0\0\0' )
            break;

	case kNavCBSelectEntry:
            NavActionState astate;
            switch (nfb->btype) {
	      case BROWSE_MULTI_FILE:
	      case BROWSE_MULTI_DIRECTORY:
	      case BROWSE_SAVE_FILE:
	        break;			// these don't need selection override
	      case BROWSE_SAVE_DIRECTORY:
	      case BROWSE_DIRECTORY:	// these need to allow only one item, so simply disable
	      case BROWSE_FILE:		// open button if user tries to select multiple files
                SInt32 selectcount;
                AECountItems((AEDescList*)cbparm->eventData.eventDataParms.param,&selectcount);
                if ( selectcount>1 ) {
                    NavCustomControl(cbparm->context, kNavCtlSetSelection, NULL);
                    astate= nfb->keepstate | ( kNavDontOpenState | kNavDontOpenState | kNavDontChooseState );
                    NavCustomControl(cbparm->context, kNavCtlSetActionState, &astate );
                }
                else {
                    astate= nfb->keepstate | kNavNormalState;
                    NavCustomControl(cbparm->context, kNavCtlSetActionState, &astate );
                }
                break;
	    }
	    break;
        }

}

Fl_Native_File_Chooser::Fl_Native_File_Chooser(Type val) {
 Ctor(val);
}

Fl_Native_File_Chooser::Fl_Native_File_Chooser() {
 Ctor (BROWSE_FILE);
}

void Fl_Native_File_Chooser::Ctor(Type type) {
    btype           = type;
    NavGetDefaultDialogCreationOptions(&opts);
    memset(&ref, 0, sizeof(ref));
    _pathnames      = NULL;
    _tpathnames     = 0;
    _title          = NULL;
    _filter         = NULL;
    filt_patt       = NULL;
    filt_arr        = NULL;
    _nfilters       = 0;
    _set_filter     = 0;
    _directory      = NULL;
	_preset_file    = NULL;
    _errmsg         = NULL;
    keepstate       = kNavNormalState;
}

// Destructor
Fl_Native_File_Chooser::~Fl_Native_File_Chooser() {
    if ( _errmsg ) free(_errmsg);
    if ( _title ) free(_title);
    if ( _filter ) free(_filter);
    clear_pathnames();
    clear_filtarrs();
    if (ref) NavDialogDispose(ref);
}

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
    keepstate=kNavNormalState;

    // INITIALIZE BROWSER
    OSStatus err;
    if ( _nfilters==0 ) _set_filter=0;   // Make sure they match TBD: move to someplace more logical?

    switch (btype) {
	case BROWSE_FILE:
	case BROWSE_MULTI_FILE:
        //keepstate=kNavDontNewFolderState;	
	    // Prompt user for one or more files
	    if ((err = NavCreateGetFileDialog(
			  &opts,			// options
			  NULL, 			// file types
			  event_handler,		// event handler
			  NULL,				// preview callback
			  filterProc,			// filter callback
			  (void*)this,			// callback data
			  &ref)) != noErr ) {		// dialog ref
		errmsg("NavCreateGetFileDialog: failed");
		return(-1);
	    }
	    break;
	case BROWSE_DIRECTORY:
	case BROWSE_MULTI_DIRECTORY:
        keepstate=kNavDontNewFolderState;
	case BROWSE_SAVE_DIRECTORY:
	    // Prompts user for one or more files or folders
	    if ((err = NavCreateChooseFolderDialog(
			  &opts,		// options
			  event_handler,	// event callback
			  NULL,			// filter callback
			  (void*)this,		// callback data
			  &ref)) != noErr) {	// dialog ref
		errmsg("NavCreateChooseFolderDialog: failed");
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
int Fl_Native_File_Chooser::count() const {
    return(_tpathnames);
}

// PUBLIC: PRESET PATHNAME
void Fl_Native_File_Chooser::directory(const char *val) {
    if ( _directory ) free(_directory);
    _directory = (val) ? strdup(val) : NULL;
}

// PUBLIC: GET PRESET PATHNAME
//    Can return NULL if none set.
//
const char* Fl_Native_File_Chooser::directory() {
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
    if ( _filter ) free(_filter);
    _filter = (val) ? strdup(val) : NULL;
    parse_filter();
    opts.popupExtension = _nfilters ? filt_arr : NULL;
    opts.optionFlags |= kNavAllFilesInPopup;
}

// GET FILTER
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::filter() const {
    return(_filter);
}

void Fl_Native_File_Chooser::clear_filtarrs() {
 for (int i=0; i<_nfilters; i++) {
  if (filt_patt) delete [] filt_patt[i];
 }
 if (filt_patt) delete [] filt_patt;
 filt_patt=NULL;
 if (filt_arr) CFRelease(filt_arr);
 filt_arr=NULL;
 _nfilters=0;
}

void Fl_Native_File_Chooser::parse_filter() {
 clear_filtarrs();
 for(int i=0; i<(int)strlen(_filter); i++) if ( _filter[i]=='\t' ) ++_nfilters;

 CFStringRef filt_cfs;
 filt_patt=new char*[_nfilters];

 char* ptr=_filter;
 char* buff;
 char* to_cfs=new char[strlen(_filter)+1];
 to_cfs[0]='\0';
 
 CFStringRef tab = CFSTR("\t");

 for(int i=0; i<_nfilters; i++) {
  char* end;
  end=strchr(ptr,'\t');
  if (!end) break;		// if not found, continue peacefully // !!TBD: reset nfilters (fltk and win32 also?)

  ++end;			// include \t char
  buff=new char[end-ptr+1];
  strncpy(buff,ptr,end-ptr);    
  buff[end-ptr]='\0';
  strcat(to_cfs,buff);		// add filter part to descriptions string
  delete [] buff;

  ptr=end;
  end=strchr(end,'\n');
  if(!end) end=_filter+strlen(_filter);

  buff=new char[end-ptr+1];	// add filter part to patterns array
  strncpy(buff,ptr,end-ptr);
  buff[end-ptr]='\0';
  filt_patt[i]=buff;

  ptr=end+1;
 }

 to_cfs[strlen(to_cfs)-1]='\0';   // replace trailing tab with null to not confuse CreateArrayByEtCetera

 filt_cfs = CFStringCreateWithCString(NULL,to_cfs,kCFStringEncodingASCII);
 filt_arr = CFStringCreateArrayBySeparatingStrings(NULL,filt_cfs,tab);

 CFRelease(filt_cfs);
 CFRelease(tab);
}

Boolean Fl_Native_File_Chooser::filterProc_( AEDesc * theItem, void * info, void * callBackUD, NavFilterModes filterMode) {
    if (_set_filter==_nfilters) return true;			// all files chosen or no filters
    
    FSSpec fsspec;
    char pathname[1024];
    
    if ( AEDescToFSSpec(theItem, &fsspec) ) return true;	// if fails, filter function should return true by default
    FSSpecToPath(fsspec, pathname, 1024);
 
    //fprintf(stderr,"%s\n",pathname);

    if ( fl_filename_isdir(pathname) ) return true;
    if ( fl_filename_match(pathname,filt_patt[_set_filter]) ) return true;
    else return false;
}

void Fl_Native_File_Chooser::preset_file(const char* val) {
 if ( _preset_file ) free(_preset_file);
 _preset_file = (val) ? strdup(val) : NULL;
}

const char*  Fl_Native_File_Chooser::preset_file() {
 return _preset_file;
}


