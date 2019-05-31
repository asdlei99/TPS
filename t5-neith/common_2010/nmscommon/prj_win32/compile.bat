echo off
echo NmsCommon.lib build begin

if exist "nmscommon.dep" (
	del "nmscommon.dep"
)

call "%VS100COMNTOOLS%\vsvars32.bat"

echo build unicode debug
rem @msdev NmsCommon.dsp /MAKE "NmsCommon - Win32 Unicode_Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\NmsCommon_D_U.txt
@devenv nmscommon.vcxproj /ReBuild "Unicode_Debug" /Out ..\..\..\..\10-common\version\CompileInfo\nmscommon_u_d.txt

echo build unicode release
rem @msdev NmsCommon.dsp /MAKE "NmsCommon - Win32 Unicode_Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\CompileInfo\NmsCommon_R_U.txt
@devenv nmscommon.vcxproj /ReBuild "Unicode_Release" /Out ..\..\..\..\10-common\version\CompileInfo\nmscommon_u_r.txt

echo NmsCommon.lib build over
echo on


