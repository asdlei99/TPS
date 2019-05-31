echo off
echo umcweb.ocx build begin

rem copy /Y ..\..\..\10-Common\version\release\win32\incversion\IncVersion.exe
rem IncVersion.exe


if not exist "release" (
	mkdir release
)


if not exist "..\..\..\10-common\version\release\win32\umcweb" (
	mkdir "..\..\..\10-common\version\release\win32\umcweb"
)

if exist "./UmcWebProjB3.dep" (
	del "./UmcWebProjB3.dep"
)



    echo build noclean release	
@msdev UmcWebProj.dsp /MAKE "UmcWebProj - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\umcweb_R.txt
)
    echo build clean release
@msdev UmcWebProj.dsp /MAKE "UmcWebProj - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\umcweb_R.txt

)

if not exist "..\..\10-common\version\release\win32\umcweb" (
    mkdir "..\..\10-common\version\release\win32\umcweb"
)

copy /Y index.htm ..\..\..\10-common\version\release\win32\umcweb\index.htm
copy /Y release\UmcWebProjB3.ocx ..\..\..\10-common\version\release\win32\umcweb\UmcWebProjB3.ocx

copy /Y release\UmcWebProjB3.map ..\..\..\10-common\version\release\win32\umcweb\UmcWebProjB3.map

echo build UmcWebProjB3.ocx over
echo on

cd cab
call compile.bat
cd ..