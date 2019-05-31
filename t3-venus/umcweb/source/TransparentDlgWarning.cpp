// TransparentDlgWarning.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "TransparentDlgWarning.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainLogic *g_pMainDlg;
extern CLoginLogic* m_pLoginDlg;

/////////////////////////////////////////////////////////////////////////////
// CTransparentDlgWarning dialog
CTransparentDlgWarning * CTransparentDlgWarning::m_pDlg = NULL;
extern BOOL m_gIconShining;

CTransparentDlgWarning::CTransparentDlgWarning(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CTransparentDlgWarning::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransparentDlgWarning)
	//}}AFX_DATA_INIT
	m_dwBkResourceID = IDR_PNG_WARNINGWND_BK;
	m_bDlgShow = FALSE;
    SetAutoHideStatus(TRUE);
}


void CTransparentDlgWarning::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentDlgWarning)
	DDX_Control(pDX, IDC_STATIC_Title, m_stDataTitle);
	DDX_Control(pDX, IDC_STATIC_DATAFIR, m_stDataFir);
	DDX_Control(pDX, IDC_STATIC_DATASEC, m_stDataSec);
	DDX_Control(pDX, IDC_STATIC_DATATHI, m_stDataThi);
	DDX_Control(pDX, IDC_STATIC_DATAFOR, m_stDataFor);
	DDX_Control(pDX, IDC_STATIC_DATAFIF, m_stDataFif);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransparentDlgWarning, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CTransparentDlgWarning)
	ON_MESSAGE( WM_DEF_UPDATESYSTEMINFO_WARNING, UpdateItem )
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER, OnHideWndNotify )
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentDlgWarning message handlers

BOOL CTransparentDlgWarning::OnInitDialog() 
{
    

	CTransparentBaseDlg::OnInitDialog();

	//解决闪烁问题
	CRect rectClient( 0, 0, 1252, 651 );
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW ); 
	ScreenToClient(&rectClient);

	m_stDataTitle.SetWindowPos( NULL, 139,  12, rectClient.Width(), 20, SWP_SHOWWINDOW );
	m_stDataTitle.SetWindowText("系统信息");
	m_stDataTitle.SetTextAlign(StringAlignmentNear);
	m_stDataTitle.SetTextColor(Color( 255, 255, 255 ));
	m_stDataTitle.SetFont( 13, "微软雅黑" );

	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER, GetSafeHwnd() );
	return TRUE;
}

LRESULT CTransparentDlgWarning::UpdateItem( WPARAM wParam, LPARAM lParam )
{
	CRect rectClient;
	GetWindowRect(&rectClient);

	LPCTSTR strWaring = (LPCTSTR)wParam;
	CString strWaringText = (CString)strWaring;
	if ( strWaringText.IsEmpty() )
	{
		return 1L;
	}

//	MessageBoxWnd(strWaringText);

	for ( s32 nIndex = 0; nIndex < m_vecWarning.size(); nIndex++ )
	{
		CString strWarning = m_vecWarning[m_vecWarning.size() - 1 - nIndex];
		s32 nOffset = 0;
		s32 nLen =  strWarning.GetLength();
 		s32 nLineNull = 1;
 		if ( strWarning.GetLength() > 34 )
 		{
			nOffset = 14;
			nLineNull = 2;
 		}

		switch ( nIndex )
		{
		case 0:  //5个Static控件一次赋值  不需定义为enum
			{	
				m_stDataFir.SetWindowPos( NULL, 14, 64 - nOffset, 359 - 28, 16*nLineNull + nOffset, SWP_SHOWWINDOW );
				m_stDataFir.SetWindowText(strWarning);
			}
			break;
		case 1:
			{
				m_stDataSec.SetWindowPos( NULL, 14, 116 - nOffset, 359 - 28, 16*nLineNull + nOffset, SWP_SHOWWINDOW );
				m_stDataSec.SetWindowText(strWarning);
			}
			break;
		case 2:
			{
				m_stDataThi.SetWindowPos( NULL, 14, 168 - nOffset, 359 - 28, 16*nLineNull + nOffset, SWP_SHOWWINDOW );
				m_stDataThi.SetWindowText(strWarning);
			}
			break;
		case 3:
			{
				m_stDataFor.SetWindowPos( NULL, 14, 220 - nOffset, 359 - 28, 16*nLineNull + nOffset, SWP_SHOWWINDOW );
				m_stDataFor.SetWindowText(strWarning);
			}
			break;
		case 4:
			{
				m_stDataFif.SetWindowPos( NULL, 14, 272 - nOffset, 359 - 28, 16*nLineNull + nOffset, SWP_SHOWWINDOW );
				m_stDataFif.SetWindowText(strWarning);
			}
			break;
		}
	}
	UpdateData(FALSE);

	return 0L;
}

void CTransparentDlgWarning::UpdateWarningIcon( BOOL bIcon )
{
	if ( g_pMainDlg != NULL )
	{
		::PostMessage( g_pMainDlg->GetSafeHwnd(), WM_DEF_UPDATE_WARNING_ICON, 0, bIcon );
	}
}

LRESULT CTransparentDlgWarning::OnHideWndNotify( WPARAM wParam, LPARAM lParam )
{
	HideMsgBox();
	return S_OK;
}

void CTransparentDlgWarning::MessageBoxWnd( const CString& strWaringText, CWnd* pWnd)
{
	if ( strWaringText.IsEmpty() )
	{
		return;
	}

	CString strTmpWaringText;
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	char chBuf[20];
	sprintf( chBuf, "%.2d:%.2d:%.2d  ",sysTime.wHour, sysTime.wMinute, sysTime.wSecond );

	strTmpWaringText = chBuf;
	strTmpWaringText += strWaringText;

	ASSERT( m_vecWarning.size() <= 5 );
	
	if ( m_vecWarning.size() == 5 )
	{
		m_vecWarning.erase(m_vecWarning.begin());
	}
	
	if ( 0 <= m_vecWarning.size() && m_vecWarning.size() < 5 )
	{
		m_vecWarning.push_back(strTmpWaringText);
	}
	else
	{
		return;
	}

	UpdateItem( (WPARAM)(LPCTSTR)strTmpWaringText, 0 );
//	::SendMessage( pWnd->GetSafeHwnd(), WM_DEF_UPDATESYSTEMINFO_WARNING, (WPARAM)(LPCTSTR)strWaringText, 0 );
	m_gIconShining = TRUE;
}

CTransparentDlgWarning* CTransparentDlgWarning::GetDlgPtr()
{
	if ( m_pDlg == NULL)
	{
		m_pDlg = new CTransparentDlgWarning;
		m_pDlg->Create( CTransparentDlgWarning::IDD,NULL);
	}

	return m_pDlg;
}

void CTransparentDlgWarning::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
}

void CTransparentDlgWarning::HideMsgBox()
{ 
// 	if ( m_pDlg!= NULL && m_pDlg->GetSafeHwnd() != NULL )
// 	{
// 		//BOOL bRet = m_pDlg->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOACTIVATE ); 
// 		//OspPrintf( TRUE, FALSE, "\n------ShowWindow Return: %d------", bRet );
// 	}

	ShowWindow(SW_HIDE);
}

void CTransparentDlgWarning::Clean()
{
	if ( m_pDlg )
	{
		if ( m_pDlg->GetSafeHwnd() )
		{
			m_pDlg->DestroyWindow();
		}
		SAFE_RELEASE(m_pDlg);
	}
}


void CTransparentDlgWarning::OnShowWindow(BOOL bShow, UINT nStatus)
{ 
//     if ( !bShow )
//     { 
// 		ShowWindow(SW_HIDE);   //注销再登录后,提示框中会残留上次登录时的提示消息,闪一下就被清空了   20131016 - by xhx
//         //SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOACTIVATE ); 
//     }
// 	 
//     CTransparentBaseDlg::OnShowWindow(bShow,nStatus);   

	//Bug00173221
	if ( g_pMainDlg->GetSafeHwnd() || m_pLoginDlg->GetSafeHwnd() )
	{
		if ( !g_pMainDlg->IsWindowVisible() || !m_pLoginDlg->IsWindowVisible() )
		{
			if ( !IsWindowVisible() || !bShow )
			{
				ShowWindow(SW_HIDE); //注销再登录后,提示框中会残留上次登录时的提示消息,闪一下就被清空了   20131016 - by xhx
				//SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOACTIVATE ); 
				//return;
			}			
		}
	}
	
	CTransparentBaseDlg::OnShowWindow(bShow,nStatus); 
}

void CTransparentDlgWarning::InitDlg()
{ 
	m_vecWarning.clear();
	
	m_stDataFir.SetWindowText("");
	m_stDataSec.SetWindowText("");
	m_stDataThi.SetWindowText("");
	m_stDataFor.SetWindowText("");
	m_stDataFif.SetWindowText("");
	
	m_gIconShining = FALSE;
	UpdateWarningIcon( FALSE );
}