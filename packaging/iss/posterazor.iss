#define APPLICATIONTITLE "PosteRazor"
#define VERSION "1.9.7"
#define COPYRIGHT "2005-2020 Alessandro Portale"
#define PREFERENCESDIR "{userappdata}\CasaPortale"
#define PREFERENCESFILE PREFERENCESDIR + "\PosteRazor.ini"
#define WEBSITE "http://posterazor.sourceforge.net/"

[Setup]
InternalCompressLevel=ultra
OutputBaseFilename={#APPLICATIONTITLE}-{#VERSION}-Win32-Installer
SolidCompression=true
VersionInfoVersion={#VERSION}
VersionInfoCompany=CasaPortale.de
VersionInfoDescription=Make your own poster!
VersionInfoTextVersion={#APPLICATIONTITLE} {#VERSION}
VersionInfoCopyright=Copyright (C) {#COPYRIGHT}
Compression=lzma/ultra
AppCopyright={#COPYRIGHT}
AppName={#APPLICATIONTITLE}
AppVerName={#APPLICATIONTITLE} {#VERSION}
ShowLanguageDialog=no
AppPublisher=Alessandro Portale
AppPublisherURL=http://www.casaportale.de/
AppSupportURL=http://sourceforge.net/tracker/?group_id=141842
AppUpdatesURL={#WEBSITE}
AppVersion={#VERSION}
UninstallDisplayIcon={app}\PosteRazor.exe
UninstallDisplayName={#APPLICATIONTITLE}
DefaultDirName={pf}\{#APPLICATIONTITLE}
DisableProgramGroupPage=true
DisableReadyPage=true
LicenseFile=license.rtf
OutputDir=..\
DefaultGroupName={#APPLICATIONTITLE}
WizardImageFile=wizimage.bmp
WizardSmallImageFile=wizsmallimage.bmp

[Files]
Source: ..\..\src\PosteRazor.exe; DestDir: {app}
Source: ..\..\LICENSE; DestDir: {app}; DestName: LICENSE.txt
Source: ..\..\CHANGES; DestDir: {app}; DestName: CHANGES.txt
Source: ..\..\README; DestDir: {app}; DestName: README.txt

[Icons]
Name: {group}\{#APPLICATIONTITLE}; Filename: {app}\PosteRazor.exe; WorkingDir: {app}; IconFilename: {app}\PosteRazor.exe
Name: {group}\License; Filename: {app}\LICENSE.txt
Name: {group}\{cm:ProgramOnTheWeb,{#APPLICATIONTITLE}}; Filename: {#WEBSITE}
Name: {group}\{cm:UninstallProgram,{#APPLICATIONTITLE}}; Filename: {uninstallexe}

[Run]
Filename: {app}\PosteRazor.exe; WorkingDir: {app}; Flags: postinstall

[Languages]
Name: BrazilianPortuguese; MessagesFile: compiler:languages\BrazilianPortuguese.isl
Name: Dutch; MessagesFile: compiler:languages\Dutch.isl
Name: English; MessagesFile: compiler:Default.isl
Name: French; MessagesFile: compiler:languages\French.isl
Name: German; MessagesFile: compiler:languages\German.isl
Name: Italian; MessagesFile: compiler:languages\Italian.isl
Name: Polish; MessagesFile: compiler:languages\Polish.isl
Name: Spanish; MessagesFile: compiler:languages\Spanish.isl

[UninstallDelete]
Name: {#PREFERENCESFILE}; Type: files
Name: {#PREFERENCESDIR}; Type: dirifempty
