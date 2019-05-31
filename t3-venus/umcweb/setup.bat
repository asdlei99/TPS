if not exist "setup files" (
    mkdir "setup files"
)

if not exist "..\..\10-common\version\release\win32\umcweb\index.htm" (
    echo miss file index.htm >> ..\..\10-common\version\compileinfo\umcweb_setup.txt
    goto end
)

if not exist "..\..\10-common\version\release\win32\umcweb\umcweb.cab" (
    echo miss file index.htm >> ..\..\10-common\version\compileinfo\umcweb_setup.txt
    goto end
)

copy /Y ..\..\10-common\version\release\win32\umcweb\*.* "setup files\"
copy /Y prj_win32\res\umc.ico "setup files\"


cd setup
call compile.bat %1
cd..

rmdir /s/q "setup files"

:end