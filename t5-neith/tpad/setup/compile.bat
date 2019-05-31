rem copy /Y touchpcmt\Script Files\SetupComm.Rul \touchpcmt\Script Files\Setup.Rul

"%InstallShield12Build%\compile.exe" "tpad\script files\setup.rul" ifx.obl isrt.obl -libpath"%InstallShield12Script%\ifx\lib" -libpath"%InstallShield12Script%\isrt\lib" -i"%InstallShield12Script%\ifx\include" -i"%InstallShield12Script%\isrt\include" -i"%InstallShield12Script%\include" -i"%InstallShield12Script%\SQLRuntime\Include" -i"%InstallShield12Script%\IISRuntime\Include" -i"%InstallShield12Script%\XMLRuntime\Include" -i"tpad\script files"

"%InstallShield12Build%\isbuild.exe" -p"tpad.ism" -m"SINGLE_EXE_IMAGE"

copy /Y tpad\Media\SINGLE_EXE_IMAGE\Package\Setup.exe "..\..\..\10-common\version\release\win32\tpad\tpad_setup.exe"
