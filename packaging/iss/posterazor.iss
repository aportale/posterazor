#define APPLICATIONTITLE "PosteRazor"
#define VERSION "1.5"
#define COPYRIGHT "2005-2008 Alessandro Portale"
#define PREFERENCESDIR "{userappdata}\CasaPortale.de"
#define PREFERENCESFILE PREFERENCESDIR + "\PosteRazor.prefs"
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
ShowLanguageDialog=yes
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
OutputDir=.
DefaultGroupName={#APPLICATIONTITLE}
WizardImageFile=wizimage.bmp
WizardSmallImageFile=wizsmallimage.bmp

[Files]
Source: ..\..\src\Release\PosteRazor.exe; DestDir: {app}
Source: ..\..\src\LICENSE; DestDir: {app}; DestName: LICENSE.txt
Source: ..\..\src\CHANGES; DestDir: {app}; DestName: CHANGES.txt
Source: ..\..\src\README; DestDir: {app}; DestName: README.txt

[Dirs]
Name: {#PREFERENCESDIR}; AfterInstall: SetLanguagePreferences

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

[CustomMessages]
BrazilianPortuguese.UILanguage=8
Dutch.UILanguage=6
English.UILanguage=1
French.UILanguage=3
German.UILanguage=2
Italian.UILanguage=5
Polish.UILanguage=4
Spanish.UILanguage=7

[UninstallDelete]
Name: {#PREFERENCESFILE}; Type: files
Name: {#PREFERENCESDIR}; Type: dirifempty

[Code]
procedure SetLanguagePreferences;
var
	i: Integer;
	strings: TArrayOfString;
begin
	LoadStringsFromFile(ExpandConstant('{#PREFERENCESFILE}'), strings);
	SaveStringToFile(ExpandConstant('{#PREFERENCESFILE}'),
		'; FLTK preferences file format 1.0' + #13#10 +
		'; vendor: CasaPortale.de' + #13#10 +
		'; application: PosteRazor' + #13#10 +
		'[.]' + #13#10 +
		'UILanguage:' + CustomMessage('UILanguage') + #13#10,
		False);
	for i := 0 to GetArrayLength(strings)-1 do
		if (length(strings[i]) > 0)
		  and (strings[i][1] <> '[')
		  and (strings[i][1] <> ';')
		  and (Copy(strings[i], 1, 11) <> 'UILanguage:') then
			SaveStringToFile(ExpandConstant('{#PREFERENCESFILE}'), strings[i] + #13#10, True);
end;
