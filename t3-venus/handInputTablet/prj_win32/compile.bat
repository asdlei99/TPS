echo off
echo handInputTablet.exe build begin

rem copy /Y ..\..\..\10-Common\version\release\win32\incversion\IncVersion.exe
rem IncVersion.exe

if not exist "debug" (
	mkdir debug
)
if not exist "release" (
	mkdir release
)

rmdir /s/q "..\..\..\10-common\version\debug\win32\handInputTablet"
if not exist "..\..\..\10-common\version\debug\win32\handInputTablet" (
	mkdir "..\..\..\10-common\version\debug\win32\handInputTablet"
)

rmdir /s/q "..\..\..\10-common\version\release\win32\handInputTablet"
if not exist "..\..\..\10-common\version\release\win32\handInputTablet" (
	mkdir "..\..\..\10-common\version\release\win32\handInputTablet"
)

if "%1" == "noclean" (
    echo build noclean debug
@msdev handInputTablet.dsp /MAKE "handInputTablet - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\handInputTablet_d.txt

    echo build noclean release	

@msdev handInputTablet.dsp /MAKE "handInputTablet - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\handInputTablet_R.txt
) else (

    echo build clean debug
@msdev handInputTablet.dsp /MAKE "handInputTablet - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\handInputTablet_d.txt

    echo build clean release

@msdev handInputTablet.dsp /MAKE "handInputTablet - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\handInputTablet_R.txt

)

copy /Y debug\handInputTablet.exe ..\..\..\10-common\version\debug\win32\handInputTablet\handInputTablet.exe

copy /Y release\handInputTablet.exe ..\..\..\10-common\version\release\win32\handInputTablet\handInputTablet.exe
 
 
 
if not exist "..\..\..\10-common\version\release\win32\handInputTablet\src" (
	mkdir "..\..\..\10-common\version\release\win32\handInputTablet\src"
) 
 
xcopy  src\*.* ..\..\..\10-common\version\release\win32\handInputTablet\src /s /y /h 

copy /Y  WINPY.TXT ..\..\..\10-common\version\release\win32\handInputTablet\WINPY.TXT 

 
 
copy /Y release\handInputTablet.map ..\..\..\10-common\version\release\win32\handInputTablet\handInputTablet.map

echo build handInputTablet.exe over
echo on
