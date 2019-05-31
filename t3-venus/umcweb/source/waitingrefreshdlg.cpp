// waitingrefreshdlg.cpp: implementation of the CWaitingRefreshDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umcwebproj.h"
#include "waitingrefreshdlg.h"


CWaitingRefreshDlg* CWaitingRefreshDlg::m_pcWaitWindow = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CWaitingRefreshDlg::CWaitingRefreshDlg( CWnd* pParent )
				: CTransparentBaseDlg(CWaitingRefreshDlg::IDD, pParent)
{
	m_pMainWnd = NULL;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_SMALL;
	m_pMainWnd = NULL;
	m_emType = emTypeUpdAddr;
}

CWaitingRefreshDlg::~CWaitingRefreshDlg()
{

}


void CWaitingRefreshDlg::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaitingRefreshDlg)
	DDX_Control(pDX, IDC_STATIC_ICON, m_stcIcon);
	DDX_Control(pDX, IDC_STATIC_MSG, m_stcMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaitingRefreshDlg, CTransparentBaseDlg)
//{{AFX_MSG_MAP(CWaitingRefreshDlg)
//ON_WM_DESTROY()
// ON_WM_SHOWWINDOW()
// ON_WM_TIMER()
// 
// ON_MESSAGE( UI_CNC_BEGINWAITING_REFRESH, OnBeginWaitingRefresh )
// ON_MESSAGE( UI_CNC_ENDWAITING_REFRESH, OnEndWaitingRefresh )
// ON_MESSAGE( UI_CNC_LOADADDRNUM_NTY, OnLoadAddrNumNty )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CWaitingRefreshDlg* CWaitingRefreshDlg::GetWaitWindow()
{
	if (m_pcWaitWindow == NULL) 
	{
		m_pcWaitWindow = new CWaitingRefreshDlg();
		m_pcWaitWindow->Create( IDD_DIALOG_WAITREFRESH );
	}
	return m_pcWaitWindow;
}

void CWaitingRefreshDlg::Clean()
{
	if ( NULL != m_pcWaitWindow )
	{
		m_pcWaitWindow->DestroyWindow();
		SAFE_RELEASE(m_pcWaitWindow);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWaitingRefreshDlg message handlers
BOOL CWaitingRefreshDlg::OnInitDialog() 
{
	CRect rectClient( 0, 0,  400, 255 ); 
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW );
	this->CenterWindow(NULL);

	CTransparentBaseDlg::OnInitDialog();

	m_stcIcon.SetWindowPos( NULL, 100, 105, 35, 36, SWP_SHOWWINDOW  );
	m_stcIcon.SetImage( IDR_PNG_WAITPIC1 );

	m_stcMsg.SetWindowPos( NULL, 160, 105, 110, 45, SWP_SHOWWINDOW );
	m_stcMsg.SetTextColor( Color( 37, 56, 70 ) );
	m_stcMsg.SetFont( 13, "微软雅黑" ); 
	m_stcMsg.SetWindowText( "正在更新..." );
	
// 	REG_MSG( UI_CNC_BEGINWAITING_REFRESH, GetSafeHwnd() ); 
// 	REG_MSG( UI_CNC_ENDWAITING_REFRESH, GetSafeHwnd() );
// 	REG_MSG( UI_CNC_LOADADDRNUM_NTY, GetSafeHwnd() );

	return TRUE;
}



void CWaitingRefreshDlg::OnTimer(UINT nIDEvent)
{
	if ( nIDEvent == 10 )
	{		
		UpdateWaitingImg();
	}
	
    CTransparentBaseDlg::OnTimer( nIDEvent );
}


void CWaitingRefreshDlg::UpdateWaitingImg()
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
	NOTIF_PARENT_WND

	m_nUpdateTime++;
	
	if ( m_emType == emTypeUpdAddr )
	{
		if ( m_nUpdateTime > 10 )
		{
			//超时
			OnEndWaitingRefresh( 0, 0 );
			//清空列表
			CMsgHandle::SendMessage( UI_CNC_WAITINGREFRESH_OVERTIME );
		}
	}
}

LRESULT CWaitingRefreshDlg::OnBeginWaitingRefresh(WPARAM wParam, LPARAM lParam)
{
	m_emType = (Em_Type)wParam;
	if ( m_emType == emTypeUpdAddr )
	{
		m_bRedrawUIImediately = FALSE;
		m_stcMsg.SetWindowText( "正在更新..." );
	}
	else
	{
		m_bRedrawUIImediately = TRUE;
		m_stcMsg.SetWindowText( "正在导入..." );
	}

	m_nUpdateTime = 0;
	SetTimer( 10, 500, NULL );

	CWaitingRefreshDlg* pcWaitDlg = CWaitingRefreshDlg::GetWaitWindow();
	if ( pcWaitDlg != NULL )
	{
		pcWaitDlg->CenterWindow();
 		pcWaitDlg->ShowWindow( SW_SHOW );
	}
	return NO_ERROR;
}

LRESULT CWaitingRefreshDlg::OnEndWaitingRefresh(WPARAM wParam, LPARAM lParam)
{
	KillTimer( 10 );
	CWaitingRefreshDlg* pcWaitDlg = CWaitingRefreshDlg::GetWaitWindow();
	if ( pcWaitDlg != NULL )
	{
 		pcWaitDlg->ShowWindow( SW_HIDE );
	}
	
	return NO_ERROR;
}

LRESULT CWaitingRefreshDlg::OnLoadAddrNumNty(WPARAM wParam, LPARAM lParam)
{
	u32 dwLoadAddrNum = (u32)wParam;
	if ( dwLoadAddrNum < 0 )
	{
		return NO_ERROR;
	}

	CString strNum;
	strNum.Format( "%d", dwLoadAddrNum );
	CString strTip = "正在导入...\n剩余：";
	strTip += strNum;
	strTip += "条";

	m_bRedrawUIImediately = TRUE;
	m_stcMsg.SetWindowText(strTip);
	return NO_ERROR;
}


void CWaitingRefreshDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);
	
    // TODO: Add your message handler code here	
    
    DWORD dwCurID = GetCurrentProcessId(); 
    if ( TRUE == bShow )
    {    
        DWORD dwID = 0 ;
		
		//禁用该进程中所有dlg
		
		m_pMainWnd = AfxGetMainWnd();
		
		if ( m_pMainWnd == NULL )
		{
			return;
		}

        CWnd* child  = m_pMainWnd->GetWindow( GW_HWNDFIRST );
        while ( child )
        {   
            GetWindowThreadProcessId(child->GetSafeHwnd(), &dwID) ;
            if ( dwID == dwCurID )
            {
                child->EnableWindow(FALSE);
            }
            
            dwID = 0;
            child = child->GetWindow( GW_HWNDNEXT );
        }
		
        this->EnableWindow(TRUE);
        //RunModalLoop();
        SendMessage(WM_REDRAW_UI,0,0);
        SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE ) ;
		
    }
    else
    {  
        DWORD dwID = 0 ;
        //起用该进程中所有dlg
        
		if ( m_pMainWnd == NULL )
		{
			return;
		}

        CWnd* child  = m_pMainWnd->GetWindow( GW_HWNDFIRST );
        while ( child )
        {   
            GetWindowThreadProcessId(child->GetSafeHwnd(), &dwID) ;
            if ( dwID == dwCurID )
            {
                child->EnableWindow(TRUE);				
            } 
            
            dwID = 0 ;
			
            child = child->GetWindow( GW_HWNDNEXT );			
        }
        
    }
}