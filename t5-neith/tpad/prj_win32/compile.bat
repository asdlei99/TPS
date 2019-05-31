echo off
echo tpad.exe build begin


if not exist "debug" (
	mkdir "debug"
)
if not exist "release" (
	mkdir "release"
)


if exist "..\..\..\10-common\version\debug\win32\tpad" (
rmdir /s/q "..\..\..\10-common\version\debug\win32\tpad"
)
if not exist "..\..\..\10-common\version\debug\win32\tpad" (
	mkdir "..\..\..\10-common\version\debug\win32\tpad"
)

if exist "..\..\..\10-common\version\release\win32\tpad" (
rmdir /s/q "..\..\..\10-common\version\release\win32\tpad"
)
if not exist "..\..\..\10-common\version\release\win32\tpad" (
	mkdir "..\..\..\10-common\version\release\win32\tpad"
)



call "%VS100COMNTOOLS%\vsvars32.bat"
echo build clean debug vs2010
@devenv tpad.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\CompileInfo\tpad_d.txt

echo build clean release vs2010
@devenv tpad.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\CompileInfo\tpad_r.txt

rem 还原现场
call "%VS60COMNTOOLS%\vcvars32.bat"



copy /Y Debug\tpad.exe ..\..\..\10-common\version\debug\win32\tpad\tpad.exe
copy /Y Release\tpad.exe ..\..\..\10-common\version\release\win32\tpad\tpad.exe


if not exist "..\..\..\10-common\version\release\win32\tpad\layout" (
	mkdir "..\..\..\10-common\version\release\win32\tpad\layout"
)

copy /Y system.xml ..\..\..\10-common\version\debug\win32\tpad\system.xml
copy /Y system.xml  ..\..\..\10-common\version\release\win32\tpad\system.xml 

copy /Y configure.ini ..\..\..\10-common\version\release\win32\tpad\configure.ini
copy /Y ..\..\..\10-common\lib\release\win32_2010\wlanapidll.dll  ..\..\..\10-common\version\release\win32\tpad\wlanapidll.dll
copy /Y previewdll.dll  ..\..\..\10-common\version\release\win32\tpad\previewdll.dll
copy /Y ..\..\..\10-common\lib\release\win32_2010\pfc.dll ..\..\..\10-common\version\release\win32\tpad\pfc.dll


xcopy  layout\*.* ..\..\..\10-common\version\release\win32\tpad\layout /y /k /s 
copy /Y Release\tpad.map ..\..\..\10-common\version\release\win32\tpad\tpad.map

echo build tpad.exe over
echo on
