// waitingboxdlg.cpp: implementation of the CWaitingBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umcwebproj.h"
#include "waitingboxdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitingBox dialog

CWaitingBox::CWaitingBox(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CWaitingBox::IDD, pParent)
{
	m_dwBkResourceID = IDR_PNG_POPWND_BK_SMALL;
	m_emType = emUpdateAddr;
	m_nUpdateTime = 0;
	m_bRecvAddrNum = FALSE;
}

void CWaitingBox::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitingBox)
	DDX_Control(pDX, IDC_STATIC_WAIT_ICON, m_stcIcon);
	DDX_Control(pDX, IDC_STATIC_WAIT_MSG, m_stcMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaitingBox, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CWaitingBox)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	
	ON_MESSAGE( UI_CNC_ENDWAITING_REFRESH, OnEndWaitingRefresh )
	ON_MESSAGE( UI_CNC_LOADADDRNUM_NTY, OnLoadAddrNumNty )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitingBox message handlers
BOOL CWaitingBox::OnInitDialog() 
{   
	//设置位置和大小的代码放在最前面，防止时闪烁
	CRect rectClient( 0, 0,  400, 255 ); 
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW );
	this->CenterWindow(NULL);

	CTransparentBaseDlg::OnInitDialog();

	m_stcIcon.SetWindowPos( NULL, 100, 105, 35, 36, SWP_SHOWWINDOW  );
	m_stcIcon.SetImage( IDR_PNG_WAITPIC1 );

	m_stcMsg.SetWindowPos( NULL, 160, 105, 110, 45, SWP_SHOWWINDOW );
	m_stcMsg.SetTextColor( Color( 37, 56, 70 ) );
	m_stcMsg.SetFont( 13, "微软雅黑" ); 
	SetWindowText( "CWaitingBox" );

	if ( emUpdateAddr == m_emType )
	{
		m_stcMsg.SetWindowText( "正在更新..." );
	}
	else
	{
		m_stcMsg.SetWindowText( "正在导入..." );
	}
	
	m_nUpdateTime = 0;
	m_bRecvAddrNum = FALSE;
	KillTimer( 12 );
	SetTimer( 12, 500, NULL );
	
	REG_MSG( UI_CNC_ENDWAITING_REFRESH, GetSafeHwnd() );
	REG_MSG( UI_CNC_LOADADDRNUM_NTY, GetSafeHwnd() );
	
	return TRUE;
}

BOOL CWaitingBox::IsMsgBoxVisible( BOOL bEndDlg )
{
    BOOL re = FALSE; 
	CWnd *p = NULL;
	p = CWnd::FindWindow( NULL,  _T("CWaitingBox") ); 
    if( p != NULL )
	{
		if( bEndDlg )  
			((CDialog*)p)->EndDialog( IDCANCEL ); 
		re = TRUE;  
	}

    return re; 
}

void CWaitingBox::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
}

void CWaitingBox::OnTimer(UINT nIDEvent)
{
	if ( nIDEvent == 12 )
	{
		UpdateWaitingImg();
	}
	
    CTransparentBaseDlg::OnTimer( nIDEvent );
}


void CWaitingBox::UpdateWaitingImg()
{
	switch ( m_emImgSchm )
    {
    case emImgSchm1:
        m_emImgSchm = emImgSchm2;
		m_stcIcon.SetImage( IDR_PNG_WAITPIC2 );
        break;
    case emImgSchm2:
        m_emImgSchm = emImgSchm3;
        m_stcIcon.SetImage( IDR_PNG_WAITPIC3 );
        break;
    case emImgSchm3:
        m_emImgSchm = emImgSchm4;
        m_stcIcon.SetImage( IDR_PNG_WAITPIC4 );
        break;  
	case emImgSchm4:
        m_emImgSchm = emImgSchm1;
        m_stcIcon.SetImage( IDR_PNG_WAITPIC1 );
        break;  
    default:
        m_emImgSchm = emImgSchm1;
        m_stcIcon.SetImage( IDR_PNG_WAITPIC1 );
		break;    
    } 
	
	m_nUpdateTime++;
	
	if ( emUpdateAddr == m_emType )
	{
		if ( m_nUpdateTime > 10 )
		{
			//超时
			OnEndWaitingRefresh( 0, 0 );
			//清空列表
			CMsgHandle::SendMessage( UI_CNC_WAITINGREFRESH_OVERTIME );
		}
	}

	//防止条目很少时,CWaitingBox未创建之前接到UI_CNC_ENDWAITING_REFRESH  by xhx
	if ( !m_bRecvAddrNum )
	{
		if ( emLoadAddr == m_emType )
		{
			if ( m_nUpdateTime > 2 )
			{
				OnEndWaitingRefresh( 0, 0 );
			}
		}
	}

	NOTIF_PARENT_WND
}

LRESULT CWaitingBox::OnEndWaitingRefresh(WPARAM wParam, LPARAM lParam)
{
	m_bRecvAddrNum = FALSE;
	KillTimer( 12 );
	OnCancel();
	return NO_ERROR;
}

LRESULT CWaitingBox::OnLoadAddrNumNty(WPARAM wParam, LPARAM lParam)
{
	u32 dwLoadAddrNum = (u32)wParam;
	if ( dwLoadAddrNum < 0 )
	{
		return NO_ERROR;
	}

	m_bRecvAddrNum = TRUE;

	CString strNum;
	strNum.Format( "%d", dwLoadAddrNum );
	CString strTip = "正在导入...\n剩余：";
	strTip += strNum;
	strTip += "条";

	m_bRedrawUIImediately = TRUE;
	m_stcMsg.SetWindowText(strTip,TRUE);

	NOTIF_PARENT_WND

	return NO_ERROR;
}