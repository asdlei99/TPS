// GlobalAddrbook.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "globaladdrbookLogic.h"
#include "waitingrefreshdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;

BOOL g_bPrtDebug = FALSE;
/////////////////////////////////////////////////////////////////////////////
// CGlobalAddrbookLogic dialog
CGlobalAddrbookLogic::CGlobalAddrbookLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CGlobalAddrbookLogic::IDD, pParent)
	, m_pCncAddrBook(NULL)
	,m_pUmsConfig(NULL)
{
	//{{AFX_DATA_INIT(CGlobalAddrbookLogic)
	//}}AFX_DATA_INIT
	m_bShowMosaicHoriImg = TRUE;
	m_bIsAllSel = FALSE;

	m_plsGlobalAddrbook = NULL;
	m_pLetterIndex = NULL;
}

void CGlobalAddrbookLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGlobalAddrbookLogic)
	DDX_Control(pDX, IDC_BTN_Refresh, m_btnRefresh);
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stLeftTitle);
	DDX_Control(pDX, IDC_BTN_ALLSEL, m_btnAllSel);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_EDIT_FIND, m_etAddrSearch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGlobalAddrbookLogic, CDlgChild)
	//{{AFX_MSG_MAP(CGlobalAddrbookLogic)
	ON_BN_CLICKED(IDC_BTN_ALLSEL, OnBtnAllSel)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_Refresh, OnBtnRefresh)
	ON_MESSAGE(UI_CNS_REFRESH_GLOBAL_ADDRBOOK,OnRefreshGlobalAddrbook)
	ON_MESSAGE( UI_CNC_WAITINGREFRESH_OVERTIME, OnWaitRefreshOverTime )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalAddrbookLogic message handlers
void CGlobalAddrbookLogic::RegisterFun()
{
	REG_MSG_HANDLER( "CGlobalAddrbookLogic::OnClickGlobalLstItem", CGlobalAddrbookLogic::OnClickGlobalLstItem, this,CGlobalAddrbookLogic );	
	REG_MSG_HANDLER( "CGlobalAddrbookLogic::OnClickGlobalLstItemIcon", CGlobalAddrbookLogic::OnClickGlobalLstItemIcon, this,CGlobalAddrbookLogic );
	REG_MSG( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, GetSafeHwnd() );
	REG_MSG( UI_CNC_WAITINGREFRESH_OVERTIME, GetSafeHwnd() );
}

BOOL CGlobalAddrbookLogic::InitControlPane()
{
	//初始化界面控件图片控件
	CUmcwebCommon::SetImgForTransSearchEdit(&m_etAddrSearch);

	m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
	m_btnExport.SetImage( IDR_PNG_BTN_EXPORT, IDR_PNG_BTN_EXPORTDOWN, IDR_PNG_BTN_EXPORTDIS );
	m_btnRefresh.SetImage( IDR_PNG_BTN_Refresh, IDR_PNG_BTN_RefreshDOWN, IDR_PNG_BTN_RefreshDOWN );

	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stLeftTitle.SetWindowPos( NULL, 17,  14, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stLeftTitle.SetWindowText("全局地址簿");
	m_stLeftTitle.SetTextAlign(StringAlignmentNear);
	m_stLeftTitle.SetTextColor(Color( 24, 25, 27 ));
	m_stLeftTitle.SetFont( 14, "微软雅黑" );

	//本地地址簿列表加入
	m_plsGlobalAddrbook = new CListChild( "", 0, this, "", 0, WS_CHILD );
	if ( NULL != m_plsGlobalAddrbook )
	{
		m_plsGlobalAddrbook->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (1226 - 62)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsGlobalAddrbook->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsGlobalAddrbook->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsGlobalAddrbook->SetSliderAlwaysShow( TRUE );
	}

	m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
	CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
	m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
	m_pLetterIndex->SetBindList( m_plsGlobalAddrbook );
	m_plsGlobalAddrbook->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

	rectClient.left = rectClient.right - 3;
    rectClient.right = rectClient.left + 7;
    m_plsGlobalAddrbook->SetSliderRect( rectClient );

	m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );	
	
	m_plsGlobalAddrbook->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnExport.SetWindowPos( &wndTop, rectClient.right - m_btnExport.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnExport.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnRefresh.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );

	m_btnExport.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
 	m_btnAllSel.SetWindowPos( &wndTop, rectClient.right - m_btnExport.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER 
		- 10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnAllSel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
 	
 	m_btnRefresh.SetWindowPos( &wndTop, rectClient.right - m_btnExport.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 2*m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER 
		- 2*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnRefresh.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnRefresh.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
 	
 	m_btnRefresh.GetWindowRect(&rectClient);
 	ScreenToClient( &rectClient );
 	m_etAddrSearch.SetWindowPos( &wndTop, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, rectClient.right - 
 		m_btnRefresh.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );

	m_btnAllSel.EnableWindow(FALSE);
	m_btnExport.EnableWindow(FALSE);

	return TRUE;
}

BOOL CGlobalAddrbookLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	RegisterFun();
	if ( !InitControlPane() )
	{
		return FALSE;
	}

	CWaitingRefreshDlg* pcWaitDlg = CWaitingRefreshDlg::GetWaitWindow();
	if ( pcWaitDlg != NULL )
	{
		pcWaitDlg->ShowWindow( SW_HIDE );
	}

	BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);

	return TRUE;
}

void CGlobalAddrbookLogic::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDlgChild::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		if(  m_pCncAddrBook == NULL  )
		{
			BUSINESSIFPTR->GetCtrlInterface(&m_pCncAddrBook);
		}
	}
}

void CGlobalAddrbookLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();
	
	SAFE_RELEASE(m_plsGlobalAddrbook);
	SAFE_RELEASE(m_pLetterIndex);

	CWaitingRefreshDlg::Clean();
}

void CGlobalAddrbookLogic::OnBtnRefresh() 
{
	m_btnRefresh.EnableWindow( FALSE );
	CMsgHandle::SendMessage( UI_CNC_BEGINWAITING_REFRESH );

	if ( m_pUmsConfig != NULL )
	{
		u16 nRet = m_pUmsConfig->ReqSipRegInfo(emGetRegInfoType_ALL);
	}
	else
	{
		MESSAGEWND( "刷新请求发送失败" );
	}
}

LRESULT CGlobalAddrbookLogic::OnRefreshGlobalAddrbook( WPARAM wParam, LPARAM lParam )
{
	if ( NULL == m_pUmsConfig ) 
	{
		MESSAGEWND( "刷新全局地址簿失败" );
		return 0L;
	}

	vector<TTPAlias> vctAllRegInfo;
	vctAllRegInfo = m_pUmsConfig->GetAllRegInfo();

    CString strLetter;
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;

	m_vctGlobalAddrList.clear();
	m_bIsAllSel = FALSE;
	m_vctSelectList.clear();
	m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );

	s32 nRegInfoCount = vctAllRegInfo.size();
	if ( nRegInfoCount > 0 )
	{
		m_btnAllSel.EnableWindow(TRUE);
		m_btnExport.EnableWindow(FALSE);
	}
	else
	{
		m_btnAllSel.EnableWindow(FALSE);
		m_btnExport.EnableWindow(FALSE);
	}

	for( int i = 0; i < nRegInfoCount; i++ )
	{
		TTPAlias tAlias = vctAllRegInfo.at(i);
		TAddrInfo tAddrInfo;
		tAddrInfo.dwEntryIdx = i;
		if ( tAlias.m_byType == tp_Alias_e164 )
		{
			strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );

            strLetter.Format( " %s", tAddrInfo.achE164 );
		}
		else
		{
			strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );

            CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
		}		
		
		tAddrItem.tAddrInfo = tAddrInfo;
		tAddrItem.strImg = "AddrEditSelItem";
      
		tAddrItem.strNameLetter = strLetter;

		m_vctGlobalAddrList.push_back( tAddrItem );
	}

	m_btnRefresh.EnableWindow( TRUE );
	CMsgHandle::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );

	UpdateShowList();
	
	return NO_ERROR;
}



void CGlobalAddrbookLogic::UpdateShowList()
{
	if ( g_bPrtDebug )
	{
		PrtMsg( "\n   全局地址簿UpdateShowList begin");
	}
	
	m_vctShowList.clear();

	CString strText;
	m_etAddrSearch.GetWindowText( strText );
	if ( strText.IsEmpty() )
	{
		m_vctShowList = m_vctGlobalAddrList;
	}
	else
	{
		m_vctShowList = m_vctSearchList;
	}

	for ( int i = 0; i < m_vctShowList.size(); i++ )
	{	
		if ( g_bPrtDebug )
		{
			PrtMsg( "\n   全局地址簿UpdateShowList find begin");
		}
		vector<TAddrItem>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), m_vctShowList.at(i) );
		if ( g_bPrtDebug )
		{
			PrtMsg( "\n   全局地址簿UpdateShowList find end");
		}
		if ( itfind == m_vctSelectList.end() )
		{
			m_vctShowList.at(i).strImg = "AddrEditSelItem";
		}
		else
		{
			m_vctShowList.at(i).strImg = "AddrEditUnSelItem";
		}	
	}
	
	if ( g_bPrtDebug )
	{
		PrtMsg( "\n   全局地址簿UpdateShowList end");
	}
	Value_TouchListAddr val_ListAddrList( &m_vctShowList, NULL, "CGlobalAddrbookLogic::OnClickGlobalLstItem" );
	if ( NULL != m_plsGlobalAddrbook )
	{
		m_plsGlobalAddrbook->SetData( val_ListAddrList );
	}
	if ( g_bPrtDebug )
	{
		PrtMsg( "\n   全局地址簿UpdateShowList SetData end");
	}
}

bool CGlobalAddrbookLogic::OnClickGlobalLstItem( const IArgs & arg )
{	
	return true;
}

bool CGlobalAddrbookLogic::OnClickGlobalLstItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {   
			TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
			
			if( tAddrItem.strImg == "AddrEditSelItem" )
			{
				m_vctSelectList.push_back( tAddrItem );
			}
			else
			{
				vector<TAddrItem>::iterator iter = m_vctSelectList.begin();
				while( iter != m_vctSelectList.end() )
				{					  
					if ( *iter == tAddrItem )
					{
						m_vctSelectList.erase(iter);
						break;
					}		
					iter++;
				}
			}
						
			m_tAddrItem.SetNull();
			
			UpdateShowList();
			
			UpdateUIState();
        } 
    }
    return true;
}

void CGlobalAddrbookLogic::OnBtnAllSel() 
{
	if ( m_bIsAllSel )
	{
		m_vctSelectList.clear();	
	}
	else
	{
		m_vctSelectList = m_vctShowList;		
	}

	UpdateShowList();
	UpdateUIState();	
	
}

void CGlobalAddrbookLogic::OnBtnExport() 
{
	if( m_pCncAddrBook == NULL )
	{
		MESSAGEWND( "获取地址簿失败" );
		return;
	}

	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	m_btnExport.EnableWindow(FALSE);
	PrtMsg( "\n   全局地址簿正在导入...");

	//BOOL bWarning = FALSE;
	for ( int i = 0; i < m_vctSelectList.size(); i++ )
	{
		TAddrItem tAddrItem = m_vctSelectList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
			if ( dwSize >= MAX_ADDRENTRY )
			{
				CString strErr;
				int nRet = 0;
				strErr.Format( "会场条目已达到最大值%d个", MAX_ADDRENTRY );
				MESSAGEWNDBOX( strErr, this , nRet , FALSE );
				return;
			}
			
			CAddrEntry cAddrEntry;
			
			if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByName( tAddrItem.tAddrInfo.achEntryName, &cAddrEntry );
				if ( dwNum > 0 )
				{
					continue;
				}				
			}
			
			if ( strcmp( tAddrItem.tAddrInfo.achE164, "" ) != 0 )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByNumber( tAddrItem.tAddrInfo.achE164, &cAddrEntry );
				if ( dwNum > 0 )
				{
					continue;
				}
			}
			
			cAddrEntry.SetEntryName( tAddrItem.tAddrInfo.achEntryName );
			cAddrEntry.SetMtNumber( tAddrItem.tAddrInfo.achE164 );
			
			u16 wRe = m_pCncAddrBook->AddEntry( cAddrEntry );

// 			if( !bWarning )
// 			{	
// 				MESSAGEWND( "添加到本地地址簿成功"  );
// 			}
// 
// 			bWarning = TRUE;
		}
	}

	PrtMsg( "\n   全局地址簿导入完成");

	g_bPrtDebug = TRUE;

	m_vctSelectList.clear();
 	UpdateShowList();
 	UpdateUIState();

	PrtMsg( "\n   全局地址簿导出更新完成");

	g_bPrtDebug = FALSE;
}

void CGlobalAddrbookLogic::UpdateUIState()
{
	if ( g_bPrtDebug )
	{
		PrtMsg( "\n   全局地址簿UpdateUIState begin");
	}
	s32 nSelSize = m_vctSelectList.size();
	if ( nSelSize > 0 )
	{
		m_btnExport.EnableWindow(TRUE);
		
		if ( nSelSize == m_vctShowList.size() )
		{
			m_bIsAllSel = TRUE;
			m_btnAllSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
		}
		else
		{
			m_bIsAllSel = FALSE;
			m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
		}
	}
	else
	{
		m_btnExport.EnableWindow(FALSE);
		
		m_bIsAllSel = FALSE;
		m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
		m_btnAllSel.EnableWindow(FALSE);
	}

	if ( m_vctShowList.size() == 0 )
	{
		m_btnAllSel.EnableWindow(FALSE);
	}
	else
	{
		m_btnAllSel.EnableWindow(TRUE);
	}
	if ( g_bPrtDebug )
	{
		PrtMsg( "\n   全局地址簿UpdateUIState end");
	}
}

void CGlobalAddrbookLogic::InitDlg()
{    
	ShowWindow(SW_HIDE);

	m_vctGlobalAddrList.clear();
	m_vctSelectList.clear();
	m_vctShowList.clear();
	m_vctSearchList.clear();
	UpdateShowList();
	m_bIsAllSel = FALSE;

	if ( m_plsGlobalAddrbook != NULL )
	{
		m_plsGlobalAddrbook->SetYOffset( 0 );
		m_plsGlobalAddrbook->SetSelItem( -1 );
	}	

	m_etAddrSearch.SetWindowText( "" );
}

BOOL CGlobalAddrbookLogic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( (HWND)lParam == m_etAddrSearch.GetSafeHwnd() )
	{
		if ( HIWORD(wParam) == EN_CHANGE )
		{
			m_vctSelectList.clear();
			OnSearchEditChange();
			UpdateUIState();
		}
    }
	
	return CDlgChild::OnCommand(wParam, lParam);
}

void CGlobalAddrbookLogic::OnSearchEditChange()
{
	CString strSearchName;
	m_etAddrSearch.GetWindowText( strSearchName );
	if ( strSearchName.IsEmpty() )
	{
		UpdateShowList();
		return ;
	}	
	
	m_vctSearchList.clear();
	vector<TAddrItem> vctShowList;
	vctShowList = m_vctGlobalAddrList;
	
	if ( m_plsGlobalAddrbook != NULL )
	{
		m_plsGlobalAddrbook->SetYOffset( 0 );
	}
	
	for ( int i = 0; i < vctShowList.size(); i++ )
	{
		CString strItemName;
		TAddrItem tAddrItem = vctShowList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			//名称为空用E164号匹配
			if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) == 0 )
			{
				strItemName = tAddrItem.tAddrInfo.achE164;
			}
			else
			{
				strItemName = tAddrItem.tAddrInfo.achEntryName;
			}
		}
		else
		{
			strItemName = tAddrItem.tGroupInfo.achGroupName;
		}
		BOOL bFind = FALSE;			
		bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
		if ( bFind )
		{		
			m_vctSearchList.push_back( tAddrItem );
		}
	}
	
	UpdateShowList();
}
 

LRESULT CGlobalAddrbookLogic::OnWaitRefreshOverTime( WPARAM wParam,LPARAM lParam )
{
	m_btnRefresh.EnableWindow( TRUE );
	m_vctGlobalAddrList.clear();
	UpdateShowList();

	return NO_ERROR;
}