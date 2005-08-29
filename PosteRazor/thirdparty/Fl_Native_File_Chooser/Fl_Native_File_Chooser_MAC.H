//
// Fl_Native_File_Chooser_MAC.H -- FLTK native OS file chooser widget
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
#ifdef __APPLE_CC__
#include <Carbon/Carbon.h>
#else
#include <Carbon.h>
#endif

#include <FL/filename.H>

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
    Type btype;				// kind-of browser to show()
    NavDialogCreationOptions opts; // file navigation options
    NavDialogRef ref;		// file navigation reference
    NavActionState keepstate;	// holds button permissions
    NavMenuItemSpec tempitem;   // Popup menu selection
    char  **_pathnames;		// array of pathnames
    int   _tpathnames;		// total pathnames
    char  *_directory;		// default pathname to use
    char  *_title;			// title for window
    char  *_filter;			// user-side search filter
    CFArrayRef filt_arr;	// Apple's happy array structure ( wraps NavMenuItemSpecArrayPtr )
    char* *filt_patt;		// array of filter patterns
    int   _nfilters;		// number of filters parse_filter counted
    int   _set_filter;		// index of the selected filter
    char  *_errmsg;			// error message
	char  *_preset_file;	// the file to preselect
	void Ctor(Type);
    void errmsg(const char *msg);
    void clear_pathnames();
    void set_single_pathname(const char *s);

    // PRIVATE CLASS TO HANDLE NAVIGATION DIALOG REPLY STRUCT
    //     Class-ified, mainly to ensure proper cleanup.
    //
    class NavReply {
        int valid;
	NavReplyRecord reply;
    public:
        NavReply();
	~NavReply();
	int get_reply(NavDialogRef& ref);
	int get_saveas_basename(char *s, int slen);
	int get_dirname(char *s, int slen);
	int get_pathnames(char **&pathnames, int& tpathnames);
    };

    int get_saveas_basename(NavDialogRef& ref);
    int get_pathnames(NavDialogRef& ref);
    static void event_handler(NavEventCallbackMessage callBackSelector, 
			      NavCBRecPtr cbparm, void *data);
    void clear_filtarrs();
    void parse_filter();
    static Boolean filterProc ( AEDesc * theItem, void * info, void * callBackUD, NavFilterModes filterMode) {
     return ((Fl_Native_File_Chooser*)callBackUD)->filterProc_(theItem,info,callBackUD,filterMode);
    }
    Boolean filterProc_ (AEDesc*, void*, void*, NavFilterModes);
    
public:
    Fl_Native_File_Chooser();
    Fl_Native_File_Chooser(Type);
    ~Fl_Native_File_Chooser();
    int count() const;
    void directory(const char *);
    const char* directory();
    const char *errmsg();
    const char* filename() const;
    const char* filename(int i) const;
    const char *filter() const;
    void filter(const char *);
    void set_filter(int i) { _set_filter=i; }
    int set_filter() { return _set_filter; }
    int filters() { return _nfilters; }
	void preset_file(const char*);
	const char* preset_file();
    int show();
    void title(const char *);
    const char* title() const;
    void type(Type);
};
