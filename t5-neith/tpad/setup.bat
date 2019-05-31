rem echo off
if not exist "..\..\10-common\version\release\win32\tpad" (
    mkdir "..\..\10-common\version\release\win32\tpad"
)


if exist "..\..\10-common\version\compileinfo\tpad_setup.txt" (
    del ..\..\10-common\version\compileinfo\tpad_setup.txt
)

rem 1. 编解码器
if not exist "..\..\10-common\version\codec\dll\kdadpcm.acm" (
    echo miss file kdadpcm.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdg722.acm" (
    echo miss file kdg722.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdg7221.acm" (
    echo miss file kdg7221.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdg723.acm" (
    echo miss file kdg723.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdg728.acm" (
    echo miss file kdg728.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdg729.acm" (
     echo miss file kdg729.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
     goto end
)
if not exist "..\..\10-common\version\codec\dll\kdh1.dll" (
    echo miss file kdh1.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdh3.dll" (
    echo miss file kdh3.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdh4.dll" (
    echo miss file kdh4.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdm2.dll" (
    echo miss file kdm2.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdm4.dll" (
    echo miss file kdm4.dll >> ..\..\10-common\version\CompileInfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\lib\release\win32\kdv323.dll" (
    echo miss file kdv323.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdvyuv.dll" (
    echo miss file kdvyuv.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdvyuv8.dll" (
    echo miss file kdvyuv8.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdvyv12.dll" (
    echo miss file kdvyv12.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\lame.acm" (
    echo miss file lame.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\lame_acm.xml" (
    echo miss file lame_acm.xml >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\mp3ad.acm" (
    echo miss file mp3ad.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\mp3pro.acm" (
    echo miss file mp3pro.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdaacld.acm" (
    echo miss file kdaacld.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdaaclc.acm" (
    echo miss file kdaaclc.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdg711a.acm" (
    echo miss file kdg711a.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\CKDCH264Dec.ax" (
    echo miss file CKDCH264Dec.ax >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)

if not exist "..\..\10-common\version\codec\dll\msvcr90.dll" (
    echo miss file msvcr90.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\KdcSource.ax" (
    echo miss file KdcSource.ax >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdaudaec32k.dll" (
    echo miss file kdaudaec32k.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)
if not exist "..\..\10-common\version\codec\dll\kdaudproc.dll" (
    echo miss file kdaudproc.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)

if not exist "..\..\10-common\version\codec\dll\kdimg.dll" (
    echo miss file kdimg.dll >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)

if not exist "..\..\10-common\version\codec\dll\kdg719.acm" (
    echo miss file kdg719.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)

if not exist "..\..\10-common\version\codec\dll\kdg729.acm" (
    echo miss file kdg729.acm >> ..\..\10-common\version\compileinfo\tpad_setup.txt
    goto end
)

if not exist "setup files" (
    mkdir "setup files"
)


rem 拷贝相应文件
if not exist "setup files\layout" (
    mkdir "setup files\layout"
)

if not exist "setup files\help" (
    mkdir "setup files\help"
)

if not exist "setup files\cnc" (
    mkdir "setup files\cnc"
)

if not exist "setup files\cnc\skin" (
    mkdir "setup files\cnc\skin"
)

rem 白板相关
if not exist "setup files\jre7" (
    mkdir "setup files\jre7"
)

if not exist "setup files\OpenOffice4" (
    mkdir "setup files\OpenOffice4"
)

if not exist "setup files\OpenOffice" (
    mkdir "setup files\OpenOffice"
)

if not exist "setup files\skin" (
    mkdir "setup files\skin"
)

if not exist "setup files\xml" (
    mkdir "setup files\xml"
)



copy /Y ..\..\10-common\version\codec\dll\*.* "setup files\"
copy /Y ..\..\10-common\version\codec\dll\kdh4.dll "setup files\kvh4.dll"
copy /Y ..\..\10-common\lib\release\win32\kdv323.dll "setup files\"
copy /Y ..\..\10-common\version\release\win32\tpad\loadtpad.exe "setup files\loadtpad.exe"
copy /Y ..\..\10-common\version\release\win32\tpad\tpad.exe "setup files\tpad.exe"
copy /Y ..\..\10-common\version\release\win32\tpad\system.xml "setup files\system.xml"
copy /Y ..\..\10-common\version\release\win32\tpad\wlanapidll.dll "setup files\wlanapidll.dll"
copy /Y ..\..\10-common\version\release\win32\tpad\previewdll.dll "setup files\previewdll.dll"
copy /Y ..\..\10-common\version\release\win32\tpad\configure.ini "setup files\configure.ini"
copy /Y ..\..\10-common\version\release\win32\tpad\tpad.map "setup files\tpad.map"

copy /Y ..\..\10-common\lib\release\win32_2010\kdvmedianetdll.dll "setup files\kdvmedianetdll.dll"
copy /Y ..\..\10-common\lib\release\win32_2010\libkdvsrtp.dll "setup files\libkdvsrtp.dll"
copy /Y ..\..\10-common\lib\release\win32_2010\libkdcrypto-1_1.dll "setup files\libkdcrypto-1_1.dll"
copy /Y ..\..\10-common\lib\release\win32\asflib.dll "setup files\asflib.dll"
copy /Y ..\..\10-common\lib\release\win32\h264enc_x.dll "setup files\h264enc_x.dll"
copy /Y ..\..\10-common\lib\release\win32\mediasdkvc10.dll "setup files\mediasdkvc10.dll"
copy /Y ..\..\10-common\lib\release\win32\mediawrapper.dll "setup files\mediawrapper.dll"
copy /Y ..\..\10-common\lib\release\win32\OspDll.dll "setup files\OspDll.dll"
copy /Y ..\..\10-common\lib\release\win32_2010\pfc.dll "setup files\pfc.dll"

xcopy "..\..\10-common\version\release\win32\tpad\layout\*.*" "setup files\layout\" /s /y /h
xcopy "prj_win32\help\*.*" "setup files\help\" /s /y /h

copy /Y ..\..\10-common\lib\release\win32_2010\pfc.dll "setup files\cnc\pfc.dll"
copy /Y ..\..\10-common\version\release\win32\cnc\cnc.exe "setup files\cnc\cnc.exe"
copy /Y ..\..\10-common\version\release\win32\cnc\systempad.xml "setup files\cnc\system.xml"

xcopy "..\..\10-common\version\release\win32\cnc\skin\*.*" "setup files\cnc\skin\" /s /y /h
copy /Y ..\..\10-common\version\release\win32\cnc\skin\mainframe.xml "setup files\cnc\skin\mainframe.xml"

xcopy "whiteboard\jre7\*.*" "setup files\jre7\" /s /y /h
xcopy "whiteboard\OpenOffice4\*.*" "setup files\OpenOffice4\" /s /y /h
xcopy "whiteboard\OpenOffice\*.*" "setup files\OpenOffice\" /s /y /h
xcopy "whiteboard\skin\*.*" "setup files\skin\" /s /y /h
xcopy "whiteboard\xml\*.*" "setup files\xml\" /s /y /h
copy /Y whiteboard\conf.ini "setup files\conf.ini"
copy /Y whiteboard\DocumentConvert.jar "setup files\DocumentConvert.jar"
copy /Y whiteboard\DuiLib.dll "setup files\DuiLib.dll"
copy /Y whiteboard\lib\release\whiteboard.dll "setup files\whiteboard.dll"
copy /Y whiteboard\redist\vcredist_x86.exe "setup files\vcredist_x86.exe"
copy /Y whiteboard\redist\vcredist_x64.exe "setup files\vcredist_x64.exe"
copy /Y whiteboard\help_wb.chm "setup files\help_wb.chm"


cd setup
call compile.bat %1
rem call compile_desk.bat %1
cd..

rmdir /s/q "setup files"

:end
