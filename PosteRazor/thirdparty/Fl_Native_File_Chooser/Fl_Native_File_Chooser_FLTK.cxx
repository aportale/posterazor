//
// Fl_Native_File_Chooser_DEFAULT.cxx -- FLTK native OS file chooser widget
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
#include "Fl_Native_File_Chooser_FLTK.H"

// CTOR
Fl_Native_File_Chooser::Fl_Native_File_Chooser() {
    Ctor(BROWSE_FILE);
}

// CTOR
Fl_Native_File_Chooser::Fl_Native_File_Chooser(Type val) {
    Ctor(val);
}

// CTOR
void Fl_Native_File_Chooser::Ctor(Type type) {
    _errmsg          = NULL;
    _nfilters        = 0;
    _preset_file     = NULL;
    _directory       = NULL;
    prevvalue        = NULL;
    file_chooser=new Fl_File_Chooser(NULL,NULL,type_fl_file(type),NULL);
}

// DTOR
Fl_Native_File_Chooser::~Fl_Native_File_Chooser() {
    if ( _errmsg ) free(_errmsg);
    if ( file_chooser ) delete file_chooser;
    if ( prevvalue ) free (prevvalue);
    if ( _preset_file ) free (_preset_file);
    if ( _directory ) free (_directory);
}

// PRIVATE: SET ERROR MESSAGE
void Fl_Native_File_Chooser::errmsg(const char *msg) {
    if ( _errmsg ) free(_errmsg);
    _errmsg = strdup(msg);
}

// PRIVATE: translate Native types to Fl_File_Chooser types
int Fl_Native_File_Chooser::type_fl_file(Type val) {
 switch (val) {
  case BROWSE_FILE:
   return (Fl_File_Chooser::SINGLE);
  case BROWSE_DIRECTORY:
   return ( Fl_File_Chooser::SINGLE | Fl_File_Chooser::DIRECTORY );
  case BROWSE_MULTI_FILE:
   return (Fl_File_Chooser::MULTI);
  case BROWSE_MULTI_DIRECTORY:
   return ( Fl_File_Chooser::DIRECTORY | Fl_File_Chooser::MULTI );
  case BROWSE_SAVE_FILE:
   return ( Fl_File_Chooser::SINGLE | Fl_File_Chooser::CREATE );
  case BROWSE_SAVE_DIRECTORY:
   return (Fl_File_Chooser::DIRECTORY | Fl_File_Chooser::SINGLE | Fl_File_Chooser::CREATE );
  default:
   return (Fl_File_Chooser::SINGLE);
 }
}

void Fl_Native_File_Chooser::type(Type val) {
 if (file_chooser) file_chooser->type(type_fl_file(val));
}

// Show chooser, blocks until done.
// RETURNS:
//    0 - user picked a file
//    1 - user cancelled
//   -1 - failed; errmsg() has reason
//
int Fl_Native_File_Chooser::show() {
 if (!file_chooser) { errmsg("Couldn't create default FLTK File Chooser."); return -1; }
 file_chooser->preview(0);

 file_chooser->show();

 if ( !_directory || !*_directory ) file_chooser->directory(prevvalue);
 else file_chooser->directory(_directory);
 if (_preset_file && *_preset_file) file_chooser->value(_preset_file);


 while (file_chooser->shown()) Fl::wait();  // block while shown
 if ( file_chooser->value() ) {
  if (prevvalue) free (prevvalue);
  int dirlen=fl_filename_name(file_chooser->value())-file_chooser->value();
  prevvalue = (char*)malloc(dirlen+1);
  strncpy(prevvalue,file_chooser->value(),dirlen);
  prevvalue[dirlen]='\0';
 }
 if ( file_chooser->count() ) return 0;
 else return 1;                           // ! TBD/XXX How to tell exit status? Is this to do with the (undocumented?) callback of Fl_File_Chooser?
}

// RETURN ERROR MESSAGE
const char *Fl_Native_File_Chooser::errmsg() {
    return(_errmsg?_errmsg:"No error");
}

// GET FILENAME
const char* Fl_Native_File_Chooser::filename() const {
    if ( file_chooser && file_chooser->count()>0 ) return(file_chooser->value());
}

// GET FILENAME FROM LIST OF FILENAMES
const char* Fl_Native_File_Chooser::filename(int i) const {
    if ( file_chooser && i < file_chooser->count() ) return(file_chooser->value(i));
    return("tmbg");
}

// SET TITLE
//     Can be NULL if no title desired.
//
void Fl_Native_File_Chooser::title(const char *val) {
    if (file_chooser) file_chooser->label(val);
}

// GET TITLE
//    Can return NULL if none set.
//
const char *Fl_Native_File_Chooser::title() const {
    if (file_chooser) return(file_chooser->label());
    return NULL;
}

// SET FILTER
//     Can be NULL if no filter needed
//
void Fl_Native_File_Chooser::filter(const char *val) {
    if ( !val ) {
     if (file_chooser) file_chooser->filter("");
     _nfilters=0;
     return;
    }

    filter_ = new char[strlen(val)+1];
    strcpy(filter_,val);

    char* parsed=parse_filter();
    if (file_chooser) file_chooser->filter(parsed);
    delete [] parsed;
}

// GET FILTER
const char *Fl_Native_File_Chooser::filter() const {
 return filter_;
}

// SET OR RETURN SELECTED FILTER
void Fl_Native_File_Chooser::set_filter(int i) {
 if (file_chooser) file_chooser->filter_value(i);
}
int Fl_Native_File_Chooser::set_filter() {
 if (file_chooser) return file_chooser->filter_value();
 else return -1;
}

// GET TOTAL FILENAMES CHOSEN
int Fl_Native_File_Chooser::count() {
    if (file_chooser) return(file_chooser->count());
    return 0;
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

// expects "Description\tfilter\n[...]"

char *Fl_Native_File_Chooser::parse_filter() {
 _nfilters = 0;
 for(int i=0; i<strlen(filter_); i++) if ( filter_[i]=='\t' ) ++_nfilters;

 char* ptr=filter_;
 char* parsed= new char[strlen(filter_)+_nfilters*2+1];
 memset(parsed,'\0',strlen(filter_)+_nfilters*2+1);

 for (int i=0; i<_nfilters; i++) {         // parse each filter string
  char* end;
  end=strchr(ptr,'\t');
  if (!end) break;                         // if not found, continue peacefully

  //strncat(parsed,ptr,end-ptr);
  bool inpars=false;                       // remove parentheses from description before adding to outgoing filter
  for (int j=0; j<end-ptr; j++) {
   switch (ptr[j]) {
     case '(': inpars=true; break;
     case ')': inpars=false; break;
     default:
      if (!inpars) strncat(parsed,ptr+j,1);
   }
  }
  ptr=end+1;
  strcat(parsed," (");                     // put filter in parentheses
  end=strchr(end,'\n');
  if(!end) end=filter_+strlen(filter_);
  strncat(parsed,ptr,end-ptr);             // add filter part to outgoing filter, our spec is compatible w/FLTK's
  ptr=end+1;
  strcat(parsed,")\t");
 }

 return parsed;
}

void Fl_Native_File_Chooser::preset_file(const char* val) {
 if ( _preset_file ) free(_preset_file);
 _preset_file = (val) ? strdup(val) : NULL;
}

const char*  Fl_Native_File_Chooser::preset_file() {
 return _preset_file;
}


