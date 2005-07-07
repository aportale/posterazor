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
    int nftypes;		//
    NavTypeListHandle ftypes;	// 
    NavDialogCreationOptions opts; // file navigation options
    NavDialogRef ref;		// file navigation reference
    char  **_pathnames;		// array of pathnames
    int   _tpathnames;		// total pathnames
    char  *_preset_dirname;	// default pathname to use
    char  *_title;		// title for window
    char  *_filter;		// search filter
    char  *_errmsg;		// error message
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
public:
    Fl_Native_File_Chooser();
    ~Fl_Native_File_Chooser();
    // int add_file_type(xyz);
    void type(Type val);
    int show();
    const char *errmsg();
    const char* filename() const;
    const char* filename(int i) const;
    int total_filenames() const;
    void preset_dirname(const char *val);
    const char* preset_dirname();
    void title(const char *val);
    const char* title() const;
    const char *filter() const;
    void filter(const char *val);
};
