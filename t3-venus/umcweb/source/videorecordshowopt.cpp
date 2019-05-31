// videorecordshowopt.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "videorecordshowopt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainLogic * g_pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CVideoRecordShowOpt dialog
CVideoRecordShowOpt * CVideoRecordShowOpt::m_pDlg = NULL;

CVideoRecordShowOpt::CVideoRecordShowOpt(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CVideoRecordShowOpt::IDD, pParent)
{
	m_dwBkResourceID = IDR_PNG_RECORDWND_OPT_BK;
	SetAutoHideStatus(TRUE);
	m_emShowState = emShowAllRecord;
}


void CVideoRecordShowOpt::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoRecordShowOpt)
	DDX_Control(pDX, IDC_STATIC_CHECK, m_stcCheck);
	DDX_Control(pDX, IDC_STATIC_ALL, m_stcAll);
	DDX_Control(pDX, IDC_STATIC_RECORD, m_stcRecord);
	DDX_Control(pDX, IDC_STATIC_PLAY, m_stcPlay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoRecordShowOpt, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CVideoRecordShowOpt)
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, OnHideWndNotify )
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STATIC_ALL, OnStaticAll)
	ON_BN_CLICKED(IDC_STATIC_RECORD, OnStaticRecord)
	ON_BN_CLICKED(IDC_STATIC_PLAY, OnStaticPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoRecordShowOpt message handlers
BOOL CVideoRecordShowOpt::OnInitDialog() 
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

BOOL CVideoRecordShowOpt::InitControlPane()
{
	return TRUE;
}

void CVideoRecordShowOpt::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
}

void CVideoRecordShowOpt::RegisterFun()
{
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, GetSafeHwnd() );
}

CVideoRecordShowOpt* CVideoRecordShowOpt::GetDlgPtr()
{
	BOOL b = FALSE;
	if ( m_pDlg == NULL)
	{
		m_pDlg = new CVideoRecordShowOpt();
		b = m_pDlg->Create( CVideoRecordShowOpt::IDD, NULL );
	}
	
	return m_pDlg;
}

void CVideoRecordShowOpt::OnShowWindow(BOOL bShow, UINT nStatus)
{ 
	if ( g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic )
	{
		if ( g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->GetSafeHwnd() )
		{
			if ( !g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->IsWindowVisible() 
				|| !g_pMainDlg->m_dlgVTR.m_pVedioRecordLogic->m_btnShowEx.GetSwitchState() )
			{
				if ( !IsWindowVisible() )
				{
					ShowWindow(SW_HIDE);
					return;
				}

				//CTransparentBaseDlg::OnShowWindow(FALSE,nStatus);
			}
		}
	}
	
    CTransparentBaseDlg::OnShowWindow(bShow,nStatus);   
}

void CVideoRecordShowOpt::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
}

LRESULT CVideoRecordShowOpt::OnHideWndNotify( WPARAM wParam, LPARAM lParam )
{
	HideMsgBox();
	return S_OK;
}

void CVideoRecordShowOpt::HideMsgBox()
{
	ShowWindow(SW_HIDE);
}

void CVideoRecordShowOpt::Clean()
{
	SAFE_RELEASE(m_pDlg);
}

void CVideoRecordShowOpt::InitDlg()
{
	m_emShowState = emShowAllRecord;
	m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
}

//更新显示选项信息
void CVideoRecordShowOpt::UpdateShowOption()
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
	
	m_stcPlay.SetWindowPos( NULL, 0, 2 + 2*50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcPlay.SetWindowText("              正在放像");
	m_stcPlay.SetTextAlign(StringAlignmentNear);
	m_stcPlay.SetTextColor(Color( 199, 221, 239 ));
	m_stcPlay.SetFont( 13, "微软雅黑" );
	
	m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	m_stcCheck.SetWindowText("");
	m_stcCheck.SetImage( IDR_PNG_MEETLISTWND_BTN_CHECK );
}

void CVideoRecordShowOpt::OnStaticAll() 
{
    m_emShowState = emShowAllRecord;
    m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	CMsgHandle::SendMessage( UI_UMSTOOL_SHOWOPT_NTY, m_emShowState, NULL );
}

void CVideoRecordShowOpt::OnStaticRecord() 
{
    m_emShowState = emShowRecord;
    m_stcCheck.SetWindowPos( NULL, 20, 12 + 50, 30, 30,  SWP_SHOWWINDOW );
	CMsgHandle::SendMessage( UI_UMSTOOL_SHOWOPT_NTY, m_emShowState, NULL );
}

void CVideoRecordShowOpt::OnStaticPlay() 
{
    m_emShowState = emShowPlay;
    m_stcCheck.SetWindowPos( NULL, 20, 12 + 2 * 50, 30, 30,  SWP_SHOWWINDOW );
	CMsgHandle::SendMessage( UI_UMSTOOL_SHOWOPT_NTY, m_emShowState, NULL );
}
