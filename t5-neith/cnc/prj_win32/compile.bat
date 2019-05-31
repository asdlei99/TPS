echo off
echo cnc.exe build begin


if not exist "debug" (
	mkdir "debug"
)
if not exist "release" (
	mkdir "release"
)


if exist "..\..\..\10-common\version\debug\win32\cnc" (
rmdir /s/q "..\..\..\10-common\version\debug\win32\cnc"
)
if not exist "..\..\..\10-common\version\debug\win32\cnc" (
	mkdir "..\..\..\10-common\version\debug\win32\cnc"
)

if exist "..\..\..\10-common\version\release\win32\cnc" (
rmdir /s/q "..\..\..\10-common\version\release\win32\cnc"
)
if not exist "..\..\..\10-common\version\release\win32\cnc" (
	mkdir "..\..\..\10-common\version\release\win32\cnc"
)



call "%VS100COMNTOOLS%\vsvars32.bat"
echo build clean debug vs2010
@devenv cnc.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\CompileInfo\cnc_d.txt

echo build clean release vs2010
@devenv cnc.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\CompileInfo\cnc_r.txt

rem 还原现场
call "%VS60COMNTOOLS%\vcvars32.bat"



copy /Y Debug\cnc.exe ..\..\..\10-common\version\debug\win32\cnc\cnc.exe
copy /Y Release\cnc.exe ..\..\..\10-common\version\release\win32\cnc\cnc.exe
rem pdb调试文件
copy /Y Release\cnc.pdb ..\..\..\10-common\version\release\win32\cnc\cnc.pdb
rem dll need
copy /Y ..\..\..\10-common\lib\release\win32_2010\pfc.dll ..\..\..\10-common\version\release\win32\cnc\pfc.dll

if not exist "..\..\..\10-common\version\release\win32\cnc\skin" (
	mkdir "..\..\..\10-common\version\release\win32\cnc\skin"
)

copy /Y system.xml ..\..\..\10-common\version\debug\win32\cnc\system.xml
copy /Y system.xml  ..\..\..\10-common\version\release\win32\cnc\system.xml 

copy /Y systempad.xml ..\..\..\10-common\version\debug\win32\cnc\systempad.xml
copy /Y systempad.xml  ..\..\..\10-common\version\release\win32\cnc\systempad.xml 

xcopy  skin\*.* ..\..\..\10-common\version\release\win32\cnc\skin /y /k /s 
copy /Y Release\cnc.map ..\..\..\10-common\version\release\win32\cnc\cnc.map

echo build cnc.exe over
echo on
