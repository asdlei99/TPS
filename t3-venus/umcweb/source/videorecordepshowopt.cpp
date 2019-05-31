// videorecordepshowopt.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "videorecordepshowopt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainLogic * g_pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CVideoRecordEpShowOpt dialog
CVideoRecordEpShowOpt * CVideoRecordEpShowOpt::m_pDlg = NULL;

CVideoRecordEpShowOpt::CVideoRecordEpShowOpt(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CVideoRecordEpShowOpt::IDD, pParent)
{
	m_dwBkResourceID = IDR_PNG_RECORDWND_EP_OPT_BK;
	SetAutoHideStatus(TRUE);
	m_emShowState = emShowAllRecordEp;
}


void CVideoRecordEpShowOpt::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoRecordEpShowOpt)
	DDX_Control(pDX, IDC_STATIC_ALL, m_stcAll);
	DDX_Control(pDX, IDC_STATIC_RECORD, m_stcRecord);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_stcCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoRecordEpShowOpt, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CVideoRecordEpShowOpt)
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, OnHideWndNotify )
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STATIC_ALL, OnStaticAll)
	ON_BN_CLICKED(IDC_STATIC_RECORD, OnStaticRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoRecordEpShowOpt message handlers
BOOL CVideoRecordEpShowOpt::OnInitDialog() 
{
	BOOL bRet = CTransparentBaseDlg::OnInitDialog();

	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	SetControlPos();             //设置页面控件位置

	UpdateShowOption();
	
	return bRet;
}

BOOL CVideoRecordEpShowOpt::InitControlPane()
{
	return TRUE;
}

void CVideoRecordEpShowOpt::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
}

void CVideoRecordEpShowOpt::RegisterFun()
{
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, GetSafeHwnd() );
}

CVideoRecordEpShowOpt* CVideoRecordEpShowOpt::GetDlgPtr()
{
	BOOL b = FALSE;
	if ( m_pDlg == NULL)
	{
		m_pDlg = new CVideoRecordEpShowOpt();
		b = m_pDlg->Create( CVideoRecordEpShowOpt::IDD, NULL );
	}
	
	return m_pDlg;
}

void CVideoRecordEpShowOpt::OnShowWindow(BOOL bShow, UINT nStatus)
{ 
	if ( g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic )
	{
		if ( g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->m_pVideoRecordEpLogic )
		{
			if ( g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->m_pVideoRecordEpLogic->GetSafeHwnd() )
			{
				if ( !g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->m_pVideoRecordEpLogic->IsWindowVisible() 
					|| !g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->m_pVideoRecordEpLogic->m_btnShowEx.GetSwitchState() )
				{
					ShowWindow(SW_HIDE);
					//CTransparentBaseDlg::OnShowWindow(FALSE,nStatus);
					return;
				}
			}
		}
	}
	
    CTransparentBaseDlg::OnShowWindow(bShow,nStatus);   
}

void CVideoRecordEpShowOpt::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
}

LRESULT CVideoRecordEpShowOpt::OnHideWndNotify( WPARAM wParam, LPARAM lParam )
{
	HideMsgBox();
	return S_OK;
}

void CVideoRecordEpShowOpt::HideMsgBox()
{
	ShowWindow(SW_HIDE);
}

void CVideoRecordEpShowOpt::Clean()
{
	if (m_pDlg)
	{
		if ( m_pDlg->GetSafeHwnd() )
		{
			m_pDlg->DestroyWindow();
		}
		SAFE_RELEASE(m_pDlg);
	}
}

void CVideoRecordEpShowOpt::InitDlg()
{
	m_emShowState = emShowAllRecordEp;
	m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
}

//更新显示选项信息
void CVideoRecordEpShowOpt::UpdateShowOption()
{ 
    if ( this->GetSafeHwnd() == NULL )
    {
        return;
    }
	
	CRect rectClient( 0, 0, 232, 162 );
	this->ShowWindow(SW_HIDE);
	
	m_stcAll.SetWindowPos( NULL, 0,  2, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcAll.SetWindowText("              显示全部");
	m_stcAll.SetTextAlign(StringAlignmentNear);
	m_stcAll.SetTextColor(Color( 199, 221, 239 ));
	m_stcAll.SetFont( 13, "微软雅黑" );
	
	m_stcRecord.SetWindowPos( NULL, 0,  2 + 50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcRecord.SetWindowText("              正在录像");
	m_stcRecord.SetTextAlign(StringAlignmentNear);
	m_stcRecord.SetTextColor(Color( 199, 221, 239 ));
	m_stcRecord.SetFont( 13, "微软雅黑" );
	
	m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	m_stcCheck.SetWindowText("");
	m_stcCheck.SetImage( IDR_PNG_MEETLISTWND_BTN_CHECK );
}

void CVideoRecordEpShowOpt::OnStaticAll()
{
    m_emShowState = emShowAllRecordEp;
    m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	CMsgHandle::SendMessage( UI_UMSTOOL_SHOWOPT_EP_NTY, m_emShowState, NULL );
}

void CVideoRecordEpShowOpt::OnStaticRecord()
{
    m_emShowState = emShowRecordEp;
    m_stcCheck.SetWindowPos( NULL, 20, 12 + 50, 30, 30,  SWP_SHOWWINDOW );
	CMsgHandle::SendMessage( UI_UMSTOOL_SHOWOPT_EP_NTY, m_emShowState, NULL );
}