===Fl_Native_File_Chooser===
  A library to simplify creation of user-friendly file and directory choosers.


//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//


===LOG===
 2/Apr/2005 took Greg Ercolano's version 0.62, added FLTK support, changed API and added multiple filter selection
 4/Apr/2005 Win32 nullncat fix applied, improved input filter checking
 9/Apr/2005 a lot of Mac filter work done, yet no setting initial filter 
14/Apr/2005 Mac set initial filter, disallow multi-select by disabling 'Choose' button
15/Apr/2005 Win32 disable non-folder locations, got set of initial filter working
20/Apr/2005 Passed event handler to all Mac choosers to fix modal problems, minor Mac tidies
21/Apr/2005 Some minor fixes to Win32 code. Thanks Don!
 3/May/2005 Added one line to enable setting selected filter on 10.3
14/May/2005 Added preset_file which enables setting a default filename**, added AWOL ctor on Mac, made FLTK browser (usually***) keep its place
20/July/2005 Made FLTK-side preset_file not apply to directories, since that was weird looking
20/Aug/2005 merged Ian MacArthur's fix and makefile with my current tree. much thanks a.rburgers and Ian for taking the time to create makefiles!
26/Aug/2005 fixed another warning, removed a CFString.h include, thanks again Ian!

TBD: ensure Windows code will both compile and run across all platforms ( tested a pre-compiled version on Win98 with no trouble )
TBD?: implement multi-folder selection on Win32 if possible
TBD?: enable preset selection on Mac OS X open dialogs
TBD: try working around ugly inactive filtered OS X items, again*
TBD: tidy code if possible (there might be some debug/development leftovers)
TBD: make sure errmsg is always set to suitable end-user messages
TBD: test, test, test.


===USE===
These files are set up to be manually compiled into an application, and no makefile included. A sample unified header is now included.
The 'nativefc' program is an FLTK application that will test the Native Chooser. You will still need to manually select which header file it uses.


===NOTES / KNOWN ISSUES===
OS X:
 *A glitch in Mac OS X (pre-Tiger) causes only the icons to activate/deactivate after the initial filter selection.
  The names of files keep their original higlights. A few attempts at a workaround failed, patches welcome!
 *On OS X, using preset_filename() only works for saving files now.
 *Some apparent bugs in Apple's Spotlight code cause trouble with the leftmost Spotlight results column:
  - even when the Native_Chooser is supposed to be allowing only single selection, it is unable to catch multiple selections there
  - (!) if a directory is picked from that column, the Native_Chooser seems to be told that there were NO PATHNAMES RETURNED
FLTK:
 *If preset_filename() and a NULL directory() is used with the FLTK browser, the cwdir rather than the previous directory will be used

This library is almost beta, see the TBD's above. This library may have undiscovered bugs, use at your own risk.

I suppose the place for bug reports would be via the fltk.general newsgroup, 
although this library is not currently an official part of FLTK.

Enjoy!
-natevw
(at yahoo dot com)
http://homepages.dordt.edu/~nthnlvnd/projects.html
