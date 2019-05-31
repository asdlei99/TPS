
// cnc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CcncApp:
// See cnc.cpp for the implementation of this class
//

class CcncApp : public CWinApp
{
public:
	CcncApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CcncApp theApp;

BOOL OnlyStartOne();
///////////////////////打印控制//////////////////////////////
//AIP void findeName( LPSTR name );

API void help();

API void task( BOOL bEnable = TRUE );


API void prt(); 

API void prtlevel( u8 byLevel );

API void prtid( u32 msgID );

API void prtrange( u32 beginID, u32 endID );

API void stopprt();

API void prtrecive( BOOL bPrint = TRUE );

API void prtsend( BOOL bPrint = TRUE  );

API void showver();

// 显示所有会议
API void showallconf();

//显示某ID的会议信息
API void showconf();


//显示会议中cns的信息
API void showconfcns( u16 wCnsID );

//挂断某会议中的某个会场
API void hangupep( u16 wConfID, u16 epID );


//结束会议
API void hangupconf( u16 wConfID );

//显示 会场信息
API void showcns();

//API void showalltemp( );  //显示会议模板

//API void showtemp( u16 tempID   );  //显示会议模板


//显示本地cns状态
API void showcnsstate();

//显示屏和选看信息
API void showscrninfo();

API void showallcns();

//显示所有用户信息
API void showalluser();

API void  showlocalip();

//设置解码器音量
API void  setdecvol( u8 abyVol );

//显示当前解码器音量
API void  showdecvol();

//显示告警信息
API void showalarm();

//显示地址簿信息
API void showaddrbook();
API void showaddrentry( u32 dwEntryIndex );
API void deleteaddr( u32 dwEntryIndex );
//显示界面数据
API void showUIInfo();
/////////////////////////////////////////////////////////////////////////////