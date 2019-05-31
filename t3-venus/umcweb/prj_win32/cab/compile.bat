@echo off

if exist "..\..\..\..\10-common\version\compileinfo\UmcWebProj_cab.txt" (
    del ..\..\..\..\10-common\version\compileinfo\UmcWebProj_cab.txt
)



rem autosigntool mtc_d.ini

autosigntool umcweb_r.ini

rem move /Y mtc2_d.cab ..\..\..\..\10-common\version\debug\win32\mtc\mtc2.cab 

copy /Y umcweb.cab ..\..\..\..\10-common\version\release\win32\umcweb\umcweb.cab

echo on