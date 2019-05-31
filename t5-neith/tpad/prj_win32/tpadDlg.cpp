
// tpadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tpad.h"
#include "tpadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtpadDlg dialog




CtpadDlg::CtpadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtpadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtpadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtpadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CtpadDlg message handlers

BOOL CtpadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtpadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtpadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打印接口
API void help()
{
	PrtMsg( "\nshowver: 显示版本和编译时间");
	PrtMsg( "\nprt: 打印所有级别为3以上的消息");
	PrtMsg( "\nprtlevel: 设置打印级别");
	PrtMsg( "\nstopprt: 停止打印所有消息");
	PrtMsg( "\nkilltpad: 结束tpad相关所有进程");
}

API void showver()
{
	s8 achVersion[MAX_DEVICEVER_LEN] = {0};
	ComInterface->GetTPadVersion( achVersion );
	PrtMsg( "TPad version: V%s\n", achVersion );
	PrtMsg( "compile time: %s %s", __DATE__, __TIME__ );
}


API void prt()
{
	CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}

API void prtlevel( u8 byLevel )
{
	CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
	CPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void killtpad()
{
	ComInterface->KillProcess( "cnc" );
	ComInterface->KillProcess( "loadtpad" );
	TerminateProcess( GetCurrentProcess(), 0 ); 
}