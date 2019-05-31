// vtrsetlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "vtrsetlogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

/////////////////////////////////////////////////////////////////////////////
// CVTRSetLogic dialog


CVTRSetLogic::CVTRSetLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CVTRSetLogic::IDD, pParent)
{
	m_pListMenu = NULL;
	m_pVTRCtrlIF = NULL;
}


void CVTRSetLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVTRSetLogic)
	DDX_Control(pDX, IDC_STATIC_VTRSET_VTRNAME_REAL, m_stcVtrNameReal);
	DDX_Control(pDX, IDC_STATIC_VTRSET_DISK_SPACE_TOTAL_REAL, m_stcDiskSpaceTotalReal);
	DDX_Control(pDX, IDC_STATIC_VTRSET_DISK_SPACE_AVAILABLE_REAL, m_stcDiskSpaceAvailableReal);
	DDX_Control(pDX, IDC_STATIC_Title, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_VTRSET_VTRNAME, m_stcVTRName);
	DDX_Control(pDX, IDC_STATIC_VTRSET_DISK_SPACE_TOTAL, m_stcDiskSpaceTotal);
	DDX_Control(pDX, IDC_STATIC_VTRSET_DISK_SPACE_AVAILABLE, m_stcDiskSpaceAvailable);
	DDX_Control(pDX, IDC_STATIC_CHILDWNDTITLE, m_stcChildWndTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVTRSetLogic, CDlgChild)
	//{{AFX_MSG_MAP(CVTRSetLogic)
	ON_MESSAGE( UI_UMSTOOL_REC_BASE_INFO_NTY,  CVTRSetLogic::OnRecBaseInfoNty )
	ON_MESSAGE( UI_UMSTOOL_VTR_NTY,  OnVtrNty )
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVTRSetLogic message handlers
void CVTRSetLogic::RegisterFun()
{
	REG_MSG_HANDLER( _T("CVTRSetLogic::OnClickLstItem"), CVTRSetLogic::OnClickLstItem, this, CVTRSetLogic );
	REG_MSG( UI_UMSTOOL_REC_BASE_INFO_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_VTR_NTY, GetSafeHwnd() );
}

BOOL CVTRSetLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	SetControlPos();             //设置页面控件位置
	
    if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
    }
	
	return TRUE;
}

BOOL CVTRSetLogic::InitControlPane()
{
	CUmcwebCommon::SetTextTransStatic( &m_stcChildWndTitle, _T("录像机信息") , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcTitle, _T("录像机") , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcVTRName, _T("录像机名称") , 13, Color( 46, 55, 76 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcDiskSpaceAvailable, _T("磁盘可用空间") , 13, Color( 46, 55, 76 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcDiskSpaceTotal, _T("磁盘总空间") , 13, Color( 46, 55, 76 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcVtrNameReal, _T("") , 13, Color( 46, 55, 76 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcDiskSpaceAvailableReal, _T("") , 13, Color( 46, 55, 76 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stcDiskSpaceTotalReal, _T("") , 13, Color( 46, 55, 76 ) );

	//菜单列表加入
	if ( m_pListMenu == NULL )
	{
		m_pListMenu = new CListChild( "", CRect(5, 46, (690 - 5)+5, 488+46), this, "", 0, WS_CHILD );

		ARRAY<TMenuItemInfo> vecMenuLst;
		for ( s32 nIndex = 0; nIndex < 2; nIndex++ )
		{
			TMenuItemInfo tMenuInfo;
			if ( nIndex == 0 )
			{
				tMenuInfo.strTxt = _T("录像文件列表");
			}
			else
			{
				tMenuInfo.strTxt = _T("录像和回放");
			}
			
			tMenuInfo.strItemFunc = _T("CVTRSetLogic::OnClickLstItem");
			vecMenuLst.push_back(tMenuInfo);
		}
		
		Value_TouchListMenu val_MenuList( &vecMenuLst );
		val_MenuList.m_bDrawRightPic = TRUE;
		m_pListMenu->SetData( val_MenuList );
	}


	return TRUE;
}

void CVTRSetLogic::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stcTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcChildWndTitle.SetWindowPos( NULL, (690 + 18)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_stcVTRName.SetWindowPos( NULL, (690 + 18)*CUR_SCREEN_WIDTH_PER,  75*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcDiskSpaceAvailable.SetWindowPos( NULL, (690 + 18)*CUR_SCREEN_WIDTH_PER, (75 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcDiskSpaceTotal.SetWindowPos( NULL, (690 + 18)*CUR_SCREEN_WIDTH_PER, (75 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_stcVtrNameReal.SetWindowPos( NULL, (690 + 18 - 12 + 142)*CUR_SCREEN_WIDTH_PER , 75*CUR_SCREEN_HEIGHT_PER,  500*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcDiskSpaceAvailableReal.SetWindowPos( NULL, (690 + 18 - 12 + 142)*CUR_SCREEN_WIDTH_PER , (75 + 18 + 27)*CUR_SCREEN_HEIGHT_PER,  500*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcDiskSpaceTotalReal.SetWindowPos( NULL, (690 + 18 - 12 + 142)*CUR_SCREEN_WIDTH_PER , (75 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER,  500*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );


	if ( NULL != m_pListMenu )
	{
		m_pListMenu->SetWindowPos( NULL, 5*CUR_SCREEN_WIDTH_PER, 46*CUR_SCREEN_HEIGHT_PER, (690 - 5)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	}
}


void CVTRSetLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();
	
	SAFE_RELEASE(m_pListMenu);
}

void CVTRSetLogic::InitDlg()
{   
	ShowWindow(SW_SHOW);

	m_stcVtrNameReal.SetWindowText("");
	m_stcDiskSpaceAvailableReal.SetWindowText("");
	m_stcDiskSpaceTotalReal.SetWindowText("");
}

bool CVTRSetLogic::OnClickLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        {
			TMenuItemInfo tMenuInfo = pItemInfo->m_tMenuInfo;
			if ( tMenuInfo.strTxt == _T("录像文件列表") )
			{
				GetParent()->SendMessage( MSG_UI_VTR_TAB_CHANGE, em_WND_VEDIOFILELIST, 0 );
			}
			else if ( tMenuInfo.strTxt == _T("录像和回放") )
			{
				GetParent()->SendMessage( MSG_UI_VTR_TAB_CHANGE, em_WND_VEDIORECORD, 0 );
			}
		}
    }
	
	return true;
}

LRESULT CVTRSetLogic::OnRecBaseInfoNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return 0;
	}

	vector<TRecBaseInfo> vecTRecBaseInfo;
	m_pVTRCtrlIF->GetRecBaseInfo( vecTRecBaseInfo );
	SetRecBaseInfo( vecTRecBaseInfo );
	return S_OK;
}

LRESULT CVTRSetLogic::OnVtrNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return 0;
	}

	TVcrCfg tVTRCfg;
	m_pVTRCtrlIF->GetUmsVTRData( tVTRCfg );

	m_stcVtrNameReal.SetWindowText( tVTRCfg.m_achName );
	
	RedrawWindow();

	return 0;
}

void CVTRSetLogic::SetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo )
{
	m_stcDiskSpaceAvailableReal.SetWindowText( "" );
	m_stcDiskSpaceTotalReal.SetWindowText( "" );
	
	vector<TRecBaseInfo>::iterator it = vecTRecBaseInfo.begin();
	for ( ; it != vecTRecBaseInfo.end(); it++ )
	{
		CString strCaption;
		strCaption.Format( _T("%.1fGB"), it->m_dwFreeSize/1024.0 );
		m_stcDiskSpaceAvailableReal.SetWindowText( strCaption );
		strCaption.Format( _T("%.1fGB"), it->m_dwTotalSize/1024.0 );
		m_stcDiskSpaceTotalReal.SetWindowText( strCaption );
		break;
	}
	RedrawWindow();
}

void CVTRSetLogic::OnShowWindow( BOOL bShow, UINT nStatus )
{
	if ( bShow == TRUE )
	{
		m_pListMenu->SetSelItem(-1);
	}

	CDlgChild::OnShowWindow(bShow, nStatus);
}
