// addreditshowoptnlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "addreditshowoptnlogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CMainLogic * g_pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CAddrEditShowOptnLogic dialog
CAddrEditShowOptnLogic * CAddrEditShowOptnLogic::m_pDlg = NULL;

CAddrEditShowOptnLogic::CAddrEditShowOptnLogic(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CAddrEditShowOptnLogic::IDD, pParent)
{
	m_dwBkResourceID = IDR_PNG_ADDREDITWND_OPT_BK;
	SetAutoHideStatus(TRUE);
	m_emMenuCheck = em_Menu_Addr_All;
}


void CAddrEditShowOptnLogic::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddrEditShowOptnLogic)
	DDX_Control(pDX, IDC_STATIC_ONLINE, m_stcOnline);
	DDX_Control(pDX, IDC_STATIC_NOTONLINE, m_stcNotOnline);
	DDX_Control(pDX, IDC_STATIC_NEW_GROUP_ICON, m_stcNewGroupIcon);
	DDX_Control(pDX, IDC_STATIC_NEW_GROUP, m_stcNewGroup);
	DDX_Control(pDX, IDC_STATIC_IMPORT_ADDRBOOK_ICON, m_stcImportAddrBookIcon);
	DDX_Control(pDX, IDC_STATIC_IMPORT_ADDRBOOK, m_stcImportAddrBook);
	DDX_Control(pDX, IDC_STATIC_GROUP, m_stcGroup);
	DDX_Control(pDX, IDC_STATIC_CHECK, m_stcCheck);
	DDX_Control(pDX, IDC_STATIC_ALL, m_stcAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddrEditShowOptnLogic, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CAddrEditShowOptnLogic)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, OnHideWndNotify )
	ON_BN_CLICKED(IDC_STATIC_ALL, OnStaticAll)
	ON_BN_CLICKED(IDC_STATIC_CHECK, OnStaticCheck)
	ON_BN_CLICKED(IDC_STATIC_GROUP, OnStaticGroup)
	ON_BN_CLICKED(IDC_STATIC_IMPORT_ADDRBOOK, OnStaticImportAddrbook)
	ON_BN_CLICKED(IDC_STATIC_IMPORT_ADDRBOOK_ICON, OnStaticImportAddrbookIcon)
	ON_BN_CLICKED(IDC_STATIC_NEW_GROUP, OnStaticNewGroup)
	ON_BN_CLICKED(IDC_STATIC_NEW_GROUP_ICON, OnStaticNewGroupIcon)
	ON_BN_CLICKED(IDC_STATIC_NOTONLINE, OnStaticNotonline)
	ON_BN_CLICKED(IDC_STATIC_ONLINE, OnStaticOnline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddrEditShowOptnLogic message handlers
BOOL CAddrEditShowOptnLogic::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();

	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	SetControlPos();             //设置页面控件位置
	
	return TRUE;
}

BOOL CAddrEditShowOptnLogic::InitControlPane()
{
	CRect rectClient( 0, 0, 232, 318 );
	this->ShowWindow(SW_HIDE);

	m_stcAll.SetWindowPos( NULL, 0,  4, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcAll.SetWindowText("              显示全部");
	m_stcAll.SetTextAlign(StringAlignmentNear);
	m_stcAll.SetTextColor(Color( 199, 221, 239 ));
	m_stcAll.SetFont( 13, "微软雅黑" );

	m_stcGroup.SetWindowPos( NULL, 0,  4 + 50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcGroup.SetWindowText("              显示组");
	m_stcGroup.SetTextAlign(StringAlignmentNear);
	m_stcGroup.SetTextColor(Color( 199, 221, 239 ));
	m_stcGroup.SetFont( 13, "微软雅黑" );
	
	m_stcOnline.SetWindowPos( NULL, 0, 4 + 2*50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcOnline.SetWindowText("              显示在线");
	m_stcOnline.SetTextAlign(StringAlignmentNear);
	m_stcOnline.SetTextColor(Color( 199, 221, 239 ));
	m_stcOnline.SetFont( 13, "微软雅黑" );

	m_stcNotOnline.SetWindowPos( NULL, 0, 4 + 3*50, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcNotOnline.SetWindowText("              显示不在线");
	m_stcNotOnline.SetTextAlign(StringAlignmentNear);
	m_stcNotOnline.SetTextColor(Color( 199, 221, 239 ));
	m_stcNotOnline.SetFont( 13, "微软雅黑" );

	m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
	m_stcCheck.SetWindowText("");
	m_stcCheck.SetImage( IDR_PNG_MEETLISTWND_BTN_CHECK );


	m_stcNewGroup.SetWindowPos( NULL, 0, 4 + 4*50+2, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcNewGroup.SetWindowText("              新建组");
	m_stcNewGroup.SetTextAlign(StringAlignmentNear);
	m_stcNewGroup.SetTextColor(Color( 199, 221, 239 ));
	m_stcNewGroup.SetFont( 13, "微软雅黑" );
	
	m_stcNewGroupIcon.SetWindowPos( NULL, 20, 12 + 4*50+5, 30, 30,  SWP_SHOWWINDOW );
	m_stcNewGroupIcon.SetWindowText("");
	m_stcNewGroupIcon.SetImage( IDR_PNG_ADDREDITWND_ICON_NEWGROUP );


	m_stcImportAddrBook.SetWindowPos( NULL, 0, 4 + 5*50+3, rectClient.Width(), 54, SWP_SHOWWINDOW );
	m_stcImportAddrBook.SetWindowText("              导入地址簿");
	m_stcImportAddrBook.SetTextAlign(StringAlignmentNear);
	m_stcImportAddrBook.SetTextColor(Color( 199, 221, 239 ));
	m_stcImportAddrBook.SetFont( 13, "微软雅黑" );
	
	m_stcImportAddrBookIcon.SetWindowPos( NULL, 20, 12 + 5*50+6, 30, 30,  SWP_SHOWWINDOW );
	m_stcImportAddrBookIcon.SetWindowText("");
	m_stcImportAddrBookIcon.SetImage( IDR_PNG_ADDREDITWND_ICON_IMPORTADDRBOOK );

	return TRUE;
}

void CAddrEditShowOptnLogic::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
}

void CAddrEditShowOptnLogic::RegisterFun()
{
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, GetSafeHwnd() );
}

CAddrEditShowOptnLogic* CAddrEditShowOptnLogic::GetDlgPtr()
{
	BOOL b = FALSE;
	if ( m_pDlg == NULL)
	{
		m_pDlg = new CAddrEditShowOptnLogic;
		b = m_pDlg->Create( CAddrEditShowOptnLogic::IDD,NULL);
	}
	
	return m_pDlg;
}

void CAddrEditShowOptnLogic::OnShowWindow(BOOL bShow, UINT nStatus)
{ 
//	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, bShow, 0 );



	if ( g_pMainDlg->m_dlgAddrEdit.GetSafeHwnd() )
	{
		if ( !g_pMainDlg->m_dlgAddrEdit.IsWindowVisible() || !g_pMainDlg->m_dlgAddrEdit.m_btnAddrShowEx.GetSwitchState() )
		{
			if ( !IsWindowVisible() )
			{
				ShowWindow(SW_HIDE);
				return;
			}
			//CTransparentBaseDlg::OnShowWindow(FALSE,nStatus);   
			
		}
	}


    CTransparentBaseDlg::OnShowWindow(bShow,nStatus);   
}

void CAddrEditShowOptnLogic::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
}

LRESULT CAddrEditShowOptnLogic::OnHideWndNotify( WPARAM wParam, LPARAM lParam )
{
	HideMsgBox();
	return S_OK;
}

void CAddrEditShowOptnLogic::HideMsgBox()
{
	ShowWindow(SW_HIDE);
}

void CAddrEditShowOptnLogic::InitDlg()
{
//	m_emMenuCheck = em_Menu_Addr_All;
//
//	m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
}

void CAddrEditShowOptnLogic::Clean()
{
	SAFE_RELEASE(m_pDlg);
}

void CAddrEditShowOptnLogic::OnStaticAll() 
{
	if ( m_emMenuCheck == em_Menu_Addr_All )
	{
		return;
	}
	SetMenuCheck(em_Menu_Addr_All);
	
	
	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, em_Menu_Addr_All, 0 );
}

void CAddrEditShowOptnLogic::OnStaticCheck() 
{
	// TODO: Add your control notification handler code here
	
}

void CAddrEditShowOptnLogic::OnStaticGroup() 
{
	SetMenuCheck(em_Menu_Addr_Group);
	
	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, em_Menu_Addr_Group, 0 );
}

void CAddrEditShowOptnLogic::OnStaticImportAddrbook() 
{
	SetMenuCheck(em_Menu_Addr_Import);
	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, em_Menu_Addr_Import, 0 );
}

void CAddrEditShowOptnLogic::OnStaticImportAddrbookIcon() 
{
	// TODO: Add your control notification handler code here
	
}

void CAddrEditShowOptnLogic::OnStaticNewGroup() 
{
	SetMenuCheck(em_Menu_Addr_NewGroup);
	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, em_Menu_Addr_NewGroup, 0 );
}

void CAddrEditShowOptnLogic::OnStaticNewGroupIcon() 
{
}

void CAddrEditShowOptnLogic::OnStaticNotonline() 
{
	SetMenuCheck(em_Menu_Addr_NotOnline);
	
	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, em_Menu_Addr_NotOnline, 0 );
}

void CAddrEditShowOptnLogic::OnStaticOnline() 
{
	SetMenuCheck(em_Menu_Addr_Online);
	
	CMsgHandle::SendMessage( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, em_Menu_Addr_Online, 0 );
}

void CAddrEditShowOptnLogic::SetMenuCheck(EM_MENU_ADDRBOOKTYPE emMenuCheck)
{ 
	m_emMenuCheck = emMenuCheck;

	switch ( m_emMenuCheck )
	{
	case em_Menu_Addr_All:
		{
			m_stcCheck.SetWindowPos( NULL, 20, 12, 30, 30,  SWP_SHOWWINDOW );
			break;
		}
	case em_Menu_Addr_Group:
		{
			m_stcCheck.SetWindowPos( NULL, 20, 12 + 50, 30, 30,  SWP_SHOWWINDOW );
			break;
		}
	case em_Menu_Addr_NotOnline:
		{
			m_stcCheck.SetWindowPos( NULL, 20, 12 + 3 * 50, 30, 30,  SWP_SHOWWINDOW );
			break;
		}
	case em_Menu_Addr_Online:
		{
			m_stcCheck.SetWindowPos( NULL, 20, 12 + 2 * 50, 30, 30,  SWP_SHOWWINDOW );
			break;
		}
	default:
		break;
	}
}