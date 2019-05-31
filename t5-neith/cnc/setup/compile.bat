rem copy /Y touchpcmt\Script Files\SetupComm.Rul \touchpcmt\Script Files\Setup.Rul

"%InstallShield12Build%\compile.exe" "cnc\script files\setup.rul" ifx.obl isrt.obl -libpath"%InstallShield12Script%\ifx\lib" -libpath"%InstallShield12Script%\isrt\lib" -i"%InstallShield12Script%\ifx\include" -i"%InstallShield12Script%\isrt\include" -i"%InstallShield12Script%\include" -i"%InstallShield12Script%\SQLRuntime\Include" -i"%InstallShield12Script%\IISRuntime\Include" -i"%InstallShield12Script%\XMLRuntime\Include" -i"cnc\script files\script files"

"%InstallShield12Build%\isbuild.exe" -p"cnc.ism" -m"SINGLE_EXE_IMAGE"

copy /Y cnc\Media\SINGLE_EXE_IMAGE\Package\Setup.exe "..\..\..\10-common\version\release\win32\cnc\cnc_setup.exe"
