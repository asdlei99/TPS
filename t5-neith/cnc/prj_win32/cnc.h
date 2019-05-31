
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
///////////////////////��ӡ����//////////////////////////////
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

// ��ʾ���л���
API void showallconf();

//��ʾĳID�Ļ�����Ϣ
API void showconf();


//��ʾ������cns����Ϣ
API void showconfcns( u16 wCnsID );

//�Ҷ�ĳ�����е�ĳ���᳡
API void hangupep( u16 wConfID, u16 epID );


//��������
API void hangupconf( u16 wConfID );

//��ʾ �᳡��Ϣ
API void showcns();

//API void showalltemp( );  //��ʾ����ģ��

//API void showtemp( u16 tempID   );  //��ʾ����ģ��


//��ʾ����cns״̬
API void showcnsstate();

//��ʾ����ѡ����Ϣ
API void showscrninfo();

API void showallcns();

//��ʾ�����û���Ϣ
API void showalluser();

API void  showlocalip();

//���ý���������
API void  setdecvol( u8 abyVol );

//��ʾ��ǰ����������
API void  showdecvol();

//��ʾ�澯��Ϣ
API void showalarm();

//��ʾ��ַ����Ϣ
API void showaddrbook();
API void showaddrentry( u32 dwEntryIndex );
API void deleteaddr( u32 dwEntryIndex );
//��ʾ��������
API void showUIInfo();
/////////////////////////////////////////////////////////////////////////////