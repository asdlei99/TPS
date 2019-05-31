# Microsoft Developer Studio Project File - Name="UmcWebProj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UmcWebProj - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UmcWebProj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UmcWebProj.mak" CFG="UmcWebProj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UmcWebProj - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UmcWebProj - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "$/平台-10-TP产品开发项目/0-业务管理/5-研发领域/01-网真/03-UMS/20111227_TPS_2/Professional_VOB/70-neptune/UmcWeb/UmcWebProj"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UmcWebProj - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /O2 /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 umclib.lib osplib.lib kdvsys.lib kdvaddrbook.lib nmscommon.lib umsmsg.lib xmlengine.lib tpmsgmgr.lib kdvlog.lib commonapi.lib /nologo /subsystem:windows /dll /map /machine:I386 /nodefaultlib:"nafxcw.lib" /nodefaultlib:"libc.lib" /out:"Release/UmcWebProjB3.ocx" /libpath:"..\..\..\10-common\lib\release\win32" /libpath:"..\..\common\include\platform sdk\LIB" /mapinfo:lines
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\UmcWebProjB3.ocx
InputPath=.\Release\UmcWebProjB3.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "UmcWebProj - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\uiexlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 umclib.lib osplib.lib kdvsys.lib kdvaddrbook.lib nmscommon.lib umsmsg.lib xmlengine.lib tpmsgmgr.lib kdvlog.lib gdiplus.lib commonapi.lib /nologo /subsystem:windows /dll /debug /debugtype:both /machine:I386 /nodefaultlib:"nafxcwd.lib" /out:"Debug/UmcWebProjB3.ocx" /pdbtype:sept /libpath:"../../../10-common/lib/debug/win32" /libpath:"..\..\common\include\platform sdk\LIB"
# SUBTRACT LINK32 /map
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\UmcWebProjB3.ocx
InputPath=.\Debug\UmcWebProjB3.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "UmcWebProj - Win32 Release"
# Name "UmcWebProj - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "ui_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\CalendarDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dlgchild.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ItemFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\source\IValue.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ListChild.cpp
# End Source File
# Begin Source File

SOURCE=..\source\Menubar.cpp
# End Source File
# Begin Source File

SOURCE=..\source\MessageDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgdispatch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msghandle.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TouchListHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\transparentbasedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TransparentDlgWarning.cpp
# End Source File
# Begin Source File

SOURCE=..\source\waitingboxdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\waitingrefreshdlg.cpp
# End Source File
# End Group
# Begin Group "logic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\addreditlogic.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\addreditshowoptnlogic.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\gkserversetLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\LoginLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mainLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mediacfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\meetdiscusslogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\meetinfoLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\meettemplateLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\nmcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sipserversetLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\systemmanageLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tvwmanageLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsnetworksetLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umssystimesetLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\usermanageLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vediofilelistlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vediorecordlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vediorecordnameeditlogic.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\videorecordeplogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\videorecordepshowopt.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\videorecordshowopt.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\vtrcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vtrlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vtrsetlogic.cpp
# End Source File
# End Group
# Begin Group "common_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\hzpysearch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\outPrint.cpp
# End Source File
# Begin Source File

SOURCE=..\source\PubFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umcwebcommon.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UmcWebProj.clw
# End Source File
# Begin Source File

SOURCE=..\source\UmcWebProj.cpp
# End Source File
# Begin Source File

SOURCE=.\UmcWebProj.def
# End Source File
# Begin Source File

SOURCE=.\UmcWebProj.odl
# End Source File
# Begin Source File

SOURCE=.\UmcWebProj.rc
# End Source File
# Begin Source File

SOURCE=..\source\UmcWebProjCtl.cpp
# End Source File
# Begin Source File

SOURCE=..\source\UmcWebProjPpg.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "ui_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\CalendarDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\dlgchild.h
# End Source File
# Begin Source File

SOURCE=..\include\ItemFactory.h
# End Source File
# Begin Source File

SOURCE=..\include\IValue.h
# End Source File
# Begin Source File

SOURCE=..\include\ListChild.h
# End Source File
# Begin Source File

SOURCE=..\include\Menubar.h
# End Source File
# Begin Source File

SOURCE=..\include\MessageDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdispatch.h
# End Source File
# Begin Source File

SOURCE=..\include\msghandle.h
# End Source File
# Begin Source File

SOURCE=..\include\TouchListHelp.h
# End Source File
# Begin Source File

SOURCE=..\include\TouchListProperty.h
# End Source File
# Begin Source File

SOURCE=..\include\transparentbasedlg.h
# End Source File
# Begin Source File

SOURCE=..\include\TransparentDlgWarning.h
# End Source File
# Begin Source File

SOURCE=..\include\waitingboxdlg.h
# End Source File
# Begin Source File

SOURCE=..\include\waitingrefreshdlg.h
# End Source File
# End Group
# Begin Group "logic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\addreditlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\addreditshowoptnlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\gkserversetLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\loginLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\mainLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\mediacfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\meetdiscusslogic.h
# End Source File
# Begin Source File

SOURCE=..\include\meetinfoLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\meettemplateLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\nmcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\sipserversetLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\systemmanageLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\tvwmanageLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\umsnetworksetLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\umssystimesetLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\usermanageLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vediofilelistlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vediorecordlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vediorecordnameeditlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\videorecordeplogic.h
# End Source File
# Begin Source File

SOURCE=..\include\videorecordepshowopt.h
# End Source File
# Begin Source File

SOURCE=..\include\videorecordshowopt.h
# End Source File
# Begin Source File

SOURCE=..\include\vtrcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vtrlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\vtrsetlogic.h
# End Source File
# End Group
# Begin Group "common_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\hzpysearch.h
# End Source File
# Begin Source File

SOURCE=..\include\outPrint.h
# End Source File
# Begin Source File

SOURCE=..\include\PubFunc.h
# End Source File
# Begin Source File

SOURCE=..\include\umcwebcommon.h
# End Source File
# Begin Source File

SOURCE=..\include\umcwebglobaldef.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\UmcWebProj.h
# End Source File
# Begin Source File

SOURCE=..\include\UmcWebProjCtl.h
# End Source File
# Begin Source File

SOURCE=..\include\UmcWebProjPpg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\AddrEditWnd\switchBtnAddrShowEx\AddrShowEx_down.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\switchBtnAddrShowEx\AddrShowEx_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\switchBtnAddrShowEx\AddrShowEx_unsel.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\background.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\background.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\backgroundep.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\bkbottom.png
# End Source File
# Begin Source File

SOURCE=.\res\Progress\BkgLeft.png
# End Source File
# Begin Source File

SOURCE=.\res\Progress\BkgMid.png
# End Source File
# Begin Source File

SOURCE=.\res\Progress\BkgRight.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\bkground.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\bkgroundempty.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\bkmid.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\bktop.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_addredit.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_addredit_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_addredit_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_defset.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_defset_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_defset_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_home.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_home_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_home_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_localaddr.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_localaddr_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_localaddr_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_logoff.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_logoff_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_meetinginfo.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_meetinginfo_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_meetinginfo_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_meetingtmp.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_meetingtmp_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_meetingtmp_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btn_plus.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btn_plusDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btn_plusdown.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_publicaddr.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_publicaddr_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_publicaddr_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btn_sub.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btn_subDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btn_subdown.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_systemset.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_systemset_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_systemset_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_tvwmanage.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_tvwmanage_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_tvwmanage_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_usermanage.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_usermanage_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_usermanage_select.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_vtrset.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_vtrset_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\btn_vtrset_select.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnAllDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnAllSel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnAllSel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnCallConf.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnCallConf_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCancel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCancel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCancelAllSel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCancelAllSel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCancelAllSelDis.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\btncheck.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCopy.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCopy_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCopy_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCut.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCut_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnCut_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnDelete.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnDelete_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnDelete_down.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnDone.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnDonedown.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnDown.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnDown_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnDownDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnEdit.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnEdit_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnEdit_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnEditSystemWnd.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnEditSystemWnd_down.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnEnter.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnEnterDown.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnExport.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnExportDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnExportDown.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnLocaladdrCancel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnLocaladdrCancel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\btnlogin.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\btnlogindis.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnManage.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnManageDisable.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnManageDown.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetAudioFormat.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetAudioFormat_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetAudioFormat_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetConfFormat.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetConfFormat_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetConfFormat_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetDiscuss.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetDiscuss_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetDiscuss_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetGroup.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetGroup_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetGroup_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetInfo.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetInfo_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetInfo_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetPolling.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetPolling_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetPolling_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetShowFormat.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetShowFormat_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetShowFormat_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllAdd.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllAdd_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllAdd_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllRemove.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllRemove_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllRemove_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllsel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllsel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllSelCancel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpAllSelCancel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpDrag.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpDragCacel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpDragCancel.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpSetBottom.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpSetBottom_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpSetBottomDis.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpSetTop.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpSetTop_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnMeetTmpSetTopDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewGroup.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewGroup_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewMeet.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewMeet_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewMeet_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewTmp.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewTmp_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnNewTmp_down.png
# End Source File
# Begin Source File

SOURCE=.\res\UserWnd\btnNewUser.png
# End Source File
# Begin Source File

SOURCE=.\res\UserWnd\btnNewUser_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\UserWnd\btnNewUser_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnPaste.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnPaste_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnRefrens.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnRefrens_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnRefrens_down.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnRemoveAll.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnRemoveAlldisable.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\btnRemoveAlldown.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnReturn.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnReturn_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnSave.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\btnSave_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnUp.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnUp_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetTmpWnd\btnUpDis.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_bk.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_nextmonth.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_nextmonth_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_premonth.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_premonth_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Calendar\calendar_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\MessageBox\Cancel.png
# End Source File
# Begin Source File

SOURCE=.\res\MessageBox\Cancel_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\check_btn_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\check_btn_sel_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\check_btn_unsel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\check_btn_unsel_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\checkmenu.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\checkmenu_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\checkmenu_select.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\deleteitem.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\deleteitem_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_delete.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_delete_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_left.png
# End Source File
# Begin Source File

SOURCE=.\res\MediaEdit\edit_left.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_left_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_left_select.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\MediaEdit\edit_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_middle_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_middle_select.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_right.png
# End Source File
# Begin Source File

SOURCE=.\res\MediaEdit\edit_right.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_right_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\MediaEdit\edit_right_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_right_select.png
# End Source File
# Begin Source File

SOURCE=.\res\Edit\edit_search.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\finish_play_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\finish_play_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\finish_play_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\finish_record_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\finish_record_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\finish_record_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\group_bkg.png
# End Source File
# Begin Source File

SOURCE=.\res\Progress\HighLightLeft.png
# End Source File
# Begin Source File

SOURCE=.\res\Progress\HighLightMid.png
# End Source File
# Begin Source File

SOURCE=.\res\Progress\HighLightRight.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_bkg_left.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_bkg_mid.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_bkg_right.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_down_left.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_down_mid.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_down_right.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_normal_left.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_normal_mid.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\horislider_normal_right.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\importaddrbookicon.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index__select_Q.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_bk.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_A.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_B.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_C.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_D.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_E.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_F.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_G.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_H.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_I.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_J.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_K.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_L.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_M.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_N.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_O.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_P.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_R.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_S.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_T.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_U.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_V.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_W.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_X.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_Y.png
# End Source File
# Begin Source File

SOURCE=.\res\Index\index_select_Z.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_bottomcenter.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_bottomleft.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_bottomright.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_centerleft.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_centerright.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_down.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_split.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_topcenter.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_topleft.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\list_topright.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listadd.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listadd_down.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listcheck_down.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listcheck_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listdelete.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listgroup.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listgroup_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_short_left.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_short_left_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_short_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_short_middle_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_short_right.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_short_right_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_width_left.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_width_left_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_width_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_width_middle_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_width_right.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listitem_width_right_select.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listnocheck.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_bkg_bottom.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_bkg_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_bkg_top.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_down_bottom.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_down_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_down_top.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_normal_bottom.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_normal_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\ListWnd\listslider_normal_top.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\loadtolocal.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\loadtolocal_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\loadtolocal_down.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\loginchild.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\loginDialog.png
# End Source File
# Begin Source File

SOURCE=.\res\LoginWnd\logo.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetclose.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetclose_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetclose_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetlist_bg.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetlist_sepa_left.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetlist_sepa_mid.png
# End Source File
# Begin Source File

SOURCE=.\res\MeetList\meetlist_sepa_right.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\newgroupicon.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\off.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\off_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\off_down.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\offline.png
# End Source File
# Begin Source File

SOURCE=.\res\MessageBox\Ok.png
# End Source File
# Begin Source File

SOURCE=.\res\MessageBox\Ok_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\on.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\on_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\on_down.png
# End Source File
# Begin Source File

SOURCE=.\res\AddrEditWnd\online.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\pause_play_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\pause_play_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\pause_play_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\pause_record_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\pause_record_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\pause_record_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\play.png
# End Source File
# Begin Source File

SOURCE=.\res\PopWnd\popwnd_bk__small.png
# End Source File
# Begin Source File

SOURCE=.\res\PopWnd\popwnd_bk_big.png
# End Source File
# Begin Source File

SOURCE=.\res\PopWnd\popwnd_cancel_rightup.png
# End Source File
# Begin Source File

SOURCE=.\res\PopWnd\popwnd_cancle_rightup_down.png
# End Source File
# Begin Source File

SOURCE=.\res\PopWnd\popwnd_save_rightup.png
# End Source File
# Begin Source File

SOURCE=.\res\PopWnd\popwnd_save_rightup_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\radio_btn_sel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\radio_btn_sel_dis.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\radio_btn_unsel.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\radio_btn_unsel_dis.png
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\record.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\RecordEp.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\resume_play_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\resume_play_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\resume_play_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\resume_record_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\resume_record_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\resume_record_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\start_play_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\start_play_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\start_play_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\start_record_disable.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\start_record_down.png
# End Source File
# Begin Source File

SOURCE=.\res\RecordWnd\Button\start_record_normal.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\timesync.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\timesync_down.png
# End Source File
# Begin Source File

SOURCE=.\res\MainWnd\toolbarbg.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\tvw.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\tvw_down.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\tvw_icon_offline.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\tvw_icon_online.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\tvw_offline.png
# End Source File
# Begin Source File

SOURCE=.\res\TvwWnd\tvw_offline_down.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\waitpic1.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\waitpic2.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\waitpic3.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\waitpic4.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\wndChild_left.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\wndChild_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\Common\wndChild_right.png
# End Source File
# Begin Source File

SOURCE=.\res\WarningWnd\wndwarning_bk.png
# End Source File
# Begin Source File

SOURCE=.\res\WarningWnd\wndwarning_btnactive.png
# End Source File
# Begin Source File

SOURCE=.\res\WarningWnd\wndwarning_btndis.png
# End Source File
# End Target
# End Project
