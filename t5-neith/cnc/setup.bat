rem echo off
if not exist "..\..\10-common\version\release\win32\cnc" (
    mkdir "..\..\10-common\version\release\win32\cnc"
)


if exist "..\..\10-common\version\compileinfo\cnc_setup.txt" (
    del ..\..\10-common\version\compileinfo\cnc_setup.txt
)


if not exist "setup files" (
    mkdir "setup files"
)


rem 拷贝相应文件
if not exist "setup files\skin" (
    mkdir "setup files\skin"
)

copy /Y ..\..\10-common\lib\release\win32_2010\pfc.dll "setup files\pfc.dll"
copy /Y ..\..\10-common\version\release\win32\cnc\cnc.exe "setup files\cnc.exe"
copy /Y ..\..\10-common\version\release\win32\cnc\system.xml "setup files\system.xml"

xcopy "..\..\10-common\version\release\win32\cnc\skin\*.*" "setup files\skin\" /s /y /h


cd setup
call compile.bat %1
cd..

del /S /Q "setup files\*.*"

:end
