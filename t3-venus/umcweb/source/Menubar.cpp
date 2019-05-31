// Menubar.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "Menubar.h"
#include "mainLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainLogic* g_cmainWnd;
/////////////////////////////////////////////////////////////////////////////
// CMenubar dialog
CMenubar::CMenubar(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CMenubar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMenubar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwBkResourceID = IDR_PNG_MEETLISTWND_BK;
}

void CMenubar::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenubar)
	DDX_Control(pDX, IDC_STATIC_ORDERMEET, m_stOrderMeet);
	DDX_Control(pDX, IDC_STATIC_CURMEET, m_stCurMeet);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_stCheck);
	DDX_Control(pDX, IDC_STATIC_ALLMEET, m_stAllMeet);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMenubar, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CMenubar)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STATIC_ALLMEET, OnClickAllMeet)
	ON_BN_CLICKED(IDC_STATIC_CURMEET, OnClickCurMeet)
	ON_BN_CLICKED(IDC_STATIC_ORDERMEET, OnClickOrderMeet)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenubar message handlers
BOOL CMenubar::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();
	
	CRect rectClient( 0, 0, 232, 162 );
	this->ShowWindow(SW_HIDE);

	m_stAllMeet.SetWindowPos( NULL, 0,  4, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stAllMeet.SetWindowText("              显示全部会议");
	m_stAllMeet.SetTextAlign(StringAlignmentNear);
	m_stAllMeet.SetTextColor(Color( 199, 221, 239 ));
	m_stAllMeet.SetFont( 13, "微软雅黑" );

	m_stCurMeet.SetWindowPos( NULL, 0,  4 + 50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stCurMeet.SetWindowText("              显示当前会议");
	m_stCurMeet.SetTextAlign(StringAlignmentNear);
	m_stCurMeet.SetTextColor(Color( 199, 221, 239 ));
	m_stCurMeet.SetFont( 13, "微软雅黑" );

	m_stOrderMeet.SetWindowPos( NULL, 0, 4 + 2*50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stOrderMeet.SetWindowText("              显示预约会议");
	m_stOrderMeet.SetTextAlign(StringAlignmentNear);
	m_stOrderMeet.SetTextColor(Color( 199, 221, 239 ));
	m_stOrderMeet.SetFont( 13, "微软雅黑" );

	m_stCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	m_stCheck.SetWindowText("");
	m_stCheck.SetImage( IDR_PNG_MEETLISTWND_BTN_CHECK );
	
	SetAutoHideStatus(TRUE);
	return TRUE;
}

void CMenubar::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();

}

void CMenubar::InitMenuBtn()
{
	SetMenuCheck(em_Menu_AllMeet);
	m_stCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	Invalidate(); //2012-7-23  解决 登录后再次点开该界面时，闪现上一次的选看界面
}

void CMenubar::OnClickAllMeet() 
{
	SetMenuCheck(em_Menu_AllMeet);
	m_stCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	::SendMessage( g_cmainWnd->m_dlgMeetInfo, WM_DEF_CLICKMEETLISTMENUUPDATE, (WPARAM)em_Menu_AllMeet, 0 );
}

void CMenubar::OnClickCurMeet() 
{
	SetMenuCheck(em_Menu_CurMeet);
	m_stCheck.SetWindowPos( NULL, 20, 12 + 50, 30, 30,  SWP_SHOWWINDOW );
	::SendMessage( g_cmainWnd->m_dlgMeetInfo, WM_DEF_CLICKMEETLISTMENUUPDATE, (WPARAM)em_Menu_CurMeet, 0 );
}

void CMenubar::OnClickOrderMeet() 
{
	SetMenuCheck(em_Menu_OrderMeet);
	m_stCheck.SetWindowPos( NULL, 20, 12 + 2*50, 30, 30,  SWP_SHOWWINDOW );
	::SendMessage( g_cmainWnd->m_dlgMeetInfo, WM_DEF_CLICKMEETLISTMENUUPDATE, (WPARAM)em_Menu_OrderMeet, 0 );
}

void CMenubar::OnShowWindow(BOOL bShow, UINT nStatus)
{ 
    if ( !bShow )
    { 
		SetWindowPos(NULL, -30000, -30000, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE ); 
    }

    CTransparentBaseDlg::OnShowWindow(bShow,nStatus);   
}

