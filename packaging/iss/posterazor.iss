#define VERSION="1.5"
#define APPLICATIONTITLE="PosteRazor"
#define COPYRIGHT="2005-2008 Alessandro Portale"

[Setup]
InternalCompressLevel=ultra
OutputBaseFilename={#APPLICATIONTITLE}-{#VERSION}-Win32-Installer
SolidCompression=true
VersionInfoVersion={#VERSION}
VersionInfoCompany=CasaPortale.de
VersionInfoDescription=Ein Lernprogram fuer koerperlich behinderte Kinder
VersionInfoTextVersion={#APPLICATIONTITLE} {#VERSION}
VersionInfoCopyright=Copyright (C) {#COPYRIGHT}
Compression=lzma/ultra
AppCopyright={#COPYRIGHT}
AppName={#APPLICATIONTITLE}
AppVerName={#APPLICATIONTITLE} {#VERSION}
ShowLanguageDialog=yes
AppPublisher=Alessandro Portale
AppPublisherURL=http://www.casaportale.de/
AppSupportURL=http://www.casaportale.de/
AppUpdatesURL=http://www.casaportale.de/
AppVersion={#VERSION}
UninstallDisplayIcon={app}\touchandlearn.exe
UninstallDisplayName={#APPLICATIONTITLE}
DefaultDirName={pf}\{#APPLICATIONTITLE}
DisableProgramGroupPage=true
DisableReadyPage=true
LicenseFile=license.rtf
OutputDir=.
DefaultGroupName={#APPLICATIONTITLE}
WizardImageFile=wizimage.bmp
WizardSmallImageFile=wizsmallimage.bmp

[Files]
Source: ..\..\src\Release\PosteRazor.exe; DestDir: {app}
Source: ..\..\src\LICENSE; DestDir: {app}; DestName: LICENSE.txt
Source: ..\..\src\CHANGES; DestDir: {app}; DestName: CHANGES.txt
Source: ..\..\src\README; DestDir: {app}; DestName: README.txt

[Icons]
Name: {group}\{#APPLICATIONTITLE}; Filename: {app}\PosteRazor.exe; WorkingDir: {app}; IconFilename: {app}\PosteRazor.exe
Name: {group}\License; Filename: {app}\LICENSE.txt
Name: {group}\{cm:ProgramOnTheWeb,{#APPLICATIONTITLE}}; Filename: http://posterazor.sourceforge.net/
Name: {group}\{cm:UninstallProgram,{#APPLICATIONTITLE}}; Filename: {uninstallexe}

[Run]
Filename: {app}\PosteRazor.exe; WorkingDir: {app}; Flags: postinstall

[Languages]
Name: English; MessagesFile: compiler:Default.isl
Name: German; MessagesFile: compiler:languages\German.isl
Name: Italian; MessagesFile: compiler:languages\Italian.isl
Name: Polish; MessagesFile: compiler:languages\Polish.isl
Name: Spanish; MessagesFile: compiler:languages\Spanish.isl
Name: Dutch; MessagesFile: compiler:languages\Dutch.isl
Name: French; MessagesFile: compiler:languages\French.isl
Name: BrazilianPortuguese; MessagesFile: compiler:languages\BrazilianPortuguese.isl
