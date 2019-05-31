// CTvwManageLogic.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "tvwmanageLogic.h"
#include "mainLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTvwManageLogic dialog
extern CMainLogic* g_cmainWnd;

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

CTvwManageLogic::CTvwManageLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CTvwManageLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTvwManageLogic)
	//}}AFX_DATA_INIT

	m_plsTvw = NULL;
	m_pLetterIndex = NULL;
    m_pconfCtrlIF = NULL;
    m_pTvwCtrlIF = NULL;
    m_bManage = FALSE;
    m_bInCnsList = FALSE;
    m_wSelTvwIndex = TP_INVALID_INDEX;

	m_bShowMosaicHoriImg = TRUE;
	m_bIsSegment = TRUE;
	m_nSegmentLen = 526*CUR_SCREEN_WIDTH_PER;
}

void CTvwManageLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTvwManageLogic)
	DDX_Control(pDX, IDC_STATIC_CHILDFRMRIGHT, m_stChildBkRight);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMLEFT, m_stChildBkLeft);
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stUserLeftTitle);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_stUserRightTitle);
	DDX_Control(pDX, IDC_Btn_Manage, m_btnManage);
    DDX_Control(pDX, IDC_BUTTON_DELALL, m_btnRemoveAll);
    DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
    DDX_Control(pDX, IDC_BUTTON_DONE, m_btnDone);
	DDX_Control(pDX, IDC_EDIT_Ex, m_etSearch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTvwManageLogic, CDlgChild)
	//{{AFX_MSG_MAP(CTvwManageLogic)
	ON_BN_CLICKED(IDC_Btn_Manage, OnBtnManage)
    ON_BN_CLICKED(IDC_BUTTON_DONE, OnBtnDone) 
    ON_BN_CLICKED(IDC_BUTTON_DELALL, OnBtnRemoveAll)
    ON_BN_CLICKED(IDC_BUTTON_BACK, OnBtnBack)
	ON_WM_DESTROY()
    ON_MESSAGE( UI_UMS_REFRESH_CONF_LIST, OnRefreshConfList )
    ON_MESSAGE( UI_UMS_REFRESH_CONFCNS_LIST, OnRefreshConfCnsList )
    ON_MESSAGE( UI_UMS_HDUPLAN_NOTIFY, OnHduPlanNty )
    ON_MESSAGE( WM_EDIT_CHANGED, OnSearchEditChange )
    ON_MESSAGE( WM_LST_UN_SELECT_ITEM, OnUnSelItemNotify )
    ON_MESSAGE( UI_UMS_PLAY_HDU_RSP, OnPlayHduRsp )
    ON_MESSAGE( UI_DRAG_OVER, OnDragOver )
    ON_MESSAGE( UI_DRAG_LEAVE, OnDragLeave )
    ON_MESSAGE( UI_DRAG_END, OnDragEnd )  
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTvwManageLogic message handlers
void CTvwManageLogic::RegisterFun()
{
	REG_MSG_HANDLER( "CTvwManageLogic::OnClickConfListItem", CTvwManageLogic::OnClickConfListItem, this, CTvwManageLogic );	
	REG_MSG_HANDLER( "CTvwManageLogic::OnClickCnsListIcon", CTvwManageLogic::OnClickCnsListIcon, this,CTvwManageLogic );
    REG_MSG_HANDLER( "CTvwManageLogic::OnClickTvwItem", CTvwManageLogic::OnClickTvwItem, this,CTvwManageLogic );
    REG_MSG_HANDLER( "CTvwManageLogic::OnClickTvwItemIcon", CTvwManageLogic::OnClickTvwItemIcon, this,CTvwManageLogic );
    
    REG_MSG( UI_UMS_REFRESH_CONF_LIST, GetSafeHwnd() );
    REG_MSG( UI_UMS_REFRESH_CONFCNS_LIST, GetSafeHwnd() );

    REG_MSG( UI_UMS_HDUPLAN_NOTIFY, GetSafeHwnd() );
}

BOOL CTvwManageLogic::InitControlPane()
{
    m_btnBack.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnManage.SetImage( IDR_PNG_BTN_MANAGE, IDR_PNG_BTN_MANAGEDOWN, IDR_PNG_BTN_MANAGEDISABLE );
    m_btnDone.SetImage( IDR_PNG_BTN_DONE, IDR_PNG_BTN_DONEDOWN, IDR_PNG_BTN_DONE );
    m_btnRemoveAll.SetImage( IDR_PNG_BTN_REMOVEALL, IDR_PNG_BTN_REMOVEALLDOWN, IDR_PNG_BTN_REMOVEALLDISABLE );
	
	CUmcwebCommon::SetTextTransStatic( &m_stUserLeftTitle, "会议列表" , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stUserRightTitle, "电视墙" , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetImgForTransSearchEdit(&m_etSearch);

	//会议列表加入
	m_plsTvw = new CListChild( "", CRect(12, 100, 732 - 45+12, 485+100), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_plsTvw )
	{
		m_plsTvw->SetWindowPos( NULL, 12, 100, 732 - 45, 485, SWP_SHOWWINDOW );
		m_plsTvw->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
				IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_plsTvw->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsTvw->SetSliderAlwaysShow( TRUE );

		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect( 0, 0, 39, 486 ), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterIndex != NULL )
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
			m_pLetterIndex->SetBindList( m_plsTvw );
		}

        //m_plsTvw->SetClickNoSel( TRUE );
	}

    m_pTvwView = new CViewList( "", CRect((526 + 14), 55, 647+(526 + 14), 508+55), this, GETUNIQID, WS_CHILD );
    if ( NULL != m_pTvwView )
    {
        //m_plsTvw->SetWindowPos( NULL, (526 + 18)*CUR_SCREEN_WIDTH_PER,  61*CUR_SCREEN_HEIGHT_PER, (684)*CUR_SCREEN_WIDTH_PER, 498*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
        m_pTvwView->SetVertSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pTvwView->SetHoriSliderImage( IDR_PNG_HORISLIDER_NORMALLEFT,IDR_PNG_HORISLIDER_NORMALMID, IDR_PNG_HORISLIDER_NORMALRIGHT, IDR_PNG_HORISLIDER_DOWNLEFT, 
            IDR_PNG_HORISLIDER_DOWNMID, IDR_PNG_HORISLIDER_DOWNRIGHT, IDR_PNG_HORISLIDER_BKGLEFT, IDR_PNG_HORISLIDER_BKGMID, IDR_PNG_HORISLIDER_BKGRIGHT, "PNG" );
    }

	return TRUE;
}

void CTvwManageLogic::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stUserLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, 435, 24, SWP_SHOWWINDOW );
	m_stUserRightTitle.SetWindowPos( NULL, 543, 14*CUR_SCREEN_HEIGHT_PER, 200, 24, SWP_SHOWWINDOW );
	
    m_btnBack.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, m_btnBack.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnBack.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_HIDEWINDOW );

	m_btnManage.SetWindowPos( NULL, 1226*CUR_SCREEN_WIDTH_PER - (8 + m_btnManage.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 
		m_btnManage.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnManage.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

    m_btnDone.SetWindowPos( NULL, 1226 - (8 + m_btnDone.GetImageSize().cx), 6*CUR_SCREEN_HEIGHT_PER, 
		m_btnDone.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDone.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

    m_btnRemoveAll.SetWindowPos( NULL, 1226 - (8 + m_btnDone.GetImageSize().cx) - (4 + m_btnRemoveAll.GetImageSize().cx) , 6*CUR_SCREEN_HEIGHT_PER, 
		m_btnRemoveAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnRemoveAll.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	if ( NULL != m_plsTvw )
	{
		m_plsTvw->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, 461*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsTvw->GetWindowRect(&rectClient);
		ScreenToClient( &rectClient );

        rectClient.left = rectClient.right;
        rectClient.right = rectClient.left + 7;
        m_plsTvw->SetSliderRect( rectClient );

		if ( m_pLetterIndex != NULL )
		{
			m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );
		}

		m_plsTvw->GetWindowRect(&rectClient);
		m_etSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  469*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	}

    if ( NULL != m_pTvwView )
    {
        m_pTvwView->SetWindowPos( NULL, (526 + 14)*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, 647*CUR_SCREEN_WIDTH_PER, 509*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
    }

}

BOOL CTvwManageLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	SetControlPos();             //设置页面控件位置

    if( m_pTvwCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pTvwCtrlIF);
    }
    
    if( m_pTvwCtrlIF != NULL )
    {
        m_pTvwCtrlIF->SetNotifyWnd( this->m_hWnd );
 	}

    CDragWindow* p = CDragWindow::GetDragWindow();
	if ( p != NULL && m_pTvwView != NULL )
    {
        p->SetNotifyWindow( m_pTvwView );
    }

	return TRUE;
}

void CTvwManageLogic::OnBtnManage() 
{
    m_bManage = TRUE;

    m_btnManage.ShowWindow( SW_HIDE );
    m_btnRemoveAll.ShowWindow( SW_SHOW );
    m_btnDone.ShowWindow( SW_SHOW );

	BOOL bFind = FALSE;
	vector<TTvwCns>::iterator it = m_vctTvwCnsList.begin();
	for ( ; it != m_vctTvwCnsList.end(); it++ )
	{
		if ( !it->m_tHduUnit->m_tName.IsEmpty() )
		{
			bFind = TRUE;
		}
	}

	if( !bFind )
	{
		m_btnRemoveAll.EnableWindow( FALSE );
	}
	else
	{
		m_btnRemoveAll.EnableWindow( TRUE );
	}

    Value_ViewListTvw val_ListTvw( &m_vctTvwCnsList, "CTvwManageLogic::OnClickTvwItem", m_tHduPlanData.m_byCol, TRUE );
    if ( m_pTvwView != NULL )
    {
        m_pTvwView->SetData( val_ListTvw );
	}

    //管理状态不能拖会场进墙
    if ( m_bInCnsList )
    {
        UpdateConfCnsList();
    }
}

void CTvwManageLogic::OnBtnDone()
{ 
    m_bManage = FALSE;

    m_btnRemoveAll.ShowWindow( SW_HIDE );
    m_btnDone.ShowWindow( SW_HIDE );
    m_btnManage.ShowWindow( SW_SHOW );

    Value_ViewListTvw val_ListTvw( &m_vctTvwCnsList, "CTvwManageLogic::OnClickTvwItem", m_tHduPlanData.m_byCol, FALSE );
    if ( m_pTvwView != NULL )
    {
        m_pTvwView->SetData( val_ListTvw );
	}

    if ( m_bInCnsList )
    {
        UpdateConfCnsList();
    }
}

void CTvwManageLogic::OnBtnRemoveAll()
{
    if( m_pTvwCtrlIF == NULL )
    {
        return;
    }

    m_pTvwCtrlIF->StopAllHduReq();
}

void CTvwManageLogic::OnBtnBack()
{
    m_bInCnsList = FALSE;

    m_etSearch.SetWindowText( "" );

    OnRefreshConfList( 0, 0 );
    
    m_tSelConf.Clear();

    UpdateConfTitle();
}


void CTvwManageLogic::UpdateConfTitle()
{   
    if ( !m_bInCnsList )
    {
        m_stUserLeftTitle.SetWindowPos( NULL, 17, 26, 0, 0, SWP_SHOWWINDOW );
        m_stUserLeftTitle.SetWindowText( "会议列表" );
        
        m_btnBack.ShowWindow( SW_HIDE );
    }
    else
    {
        CString strTitle;
        strTitle =  m_tSelConf.m_achConfName;
        strTitle = "会议列表\\" + strTitle;
        m_stUserLeftTitle.SetWindowText( strTitle );
        
        m_stUserLeftTitle.SetWindowPos( NULL, 89, 26, 0, 0, SWP_SHOWWINDOW );
        
        m_btnBack.ShowWindow( SW_SHOW );
    }
}

void CTvwManageLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

    m_vctTvwCnsList.clear();
    m_vctCurConfList.clear();

    if ( NULL != m_plsTvw )
    {
        m_plsTvw->Clear();
    }
    if ( NULL != m_pTvwView  )
    {
        m_pTvwView->Clear();
	}
	
	SAFE_RELEASE(m_plsTvw);
	SAFE_RELEASE(m_pLetterIndex);
    SAFE_RELEASE(m_pTvwView);
}

void CTvwManageLogic::InitDlg()
{
    OnBtnBack();

    if ( NULL != m_plsTvw )
    {
        m_plsTvw->SetYOffset( 0 ); 
        m_plsTvw->SetSelItem( -1 );
	}

    m_bManage = FALSE;
    m_tHduPlanData.Clear();
    m_vctTvwCnsList.clear();
    Value_ViewListTvw val_ListTvw( &m_vctTvwCnsList, "CTvwManageLogic::OnClickTvwItem", m_tHduPlanData.m_byCol );
    if ( m_pTvwView != NULL )
    {
        m_pTvwView->SetData( val_ListTvw );
	}

	m_btnManage.ShowWindow(SW_SHOW);
	m_btnRemoveAll.ShowWindow(SW_HIDE);
	m_btnDone.ShowWindow(SW_HIDE);
}

BOOL CTvwManageLogic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( HIWORD(wParam) == EN_CHANGE )
	{
		if ( (HWND)lParam == m_etSearch.GetSafeHwnd() )
		{ 
		
		}		
	}
	
	return CDlgChild::OnCommand(wParam, lParam);
}


bool CTvwManageLogic::OnClickConfListItem( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast< const Args_ClickItemInfo*>(&arg) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        if ( const Data_Conf *pData = dynamic_cast<const Data_Conf*>( pBaseItem->GetUserData() ) ) 
		{
            m_tSelConf = pData->m_tCmsConf;
            m_bInCnsList = TRUE;

            m_etSearch.SetWindowText( "" );

            UpdateConfCnsList();

            UpdateConfTitle();
        }
    }
    return true;
}

bool CTvwManageLogic::OnClickCnsListIcon( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast< const Args_ClickItemInfo*>(&arg) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_ConfCns *pData = dynamic_cast<const Data_ConfCns*>( pBaseItem->GetUserData() ) ) 
        {
            TCnsInfo tCnsInfo = pData->m_tConfCns;
            
            if ( m_wSelTvwIndex != TP_INVALID_INDEX && m_wSelTvwIndex < HDU_STYLE_MAX_NUM )
            {
                THduPlanUnit tPlanUnit = m_tHduPlanData.m_atUnits[m_wSelTvwIndex];

                if ( tPlanUnit.m_bValid )
                {
					//Bug00169725  by xhx
					u16 wSelTvwIndex = m_wSelTvwIndex;
					m_wSelTvwIndex = TP_INVALID_INDEX;
                    SetCnsInTvw( wSelTvwIndex, tCnsInfo );
                }            				
            }
        }
    }
    return true;
}


bool CTvwManageLogic::OnClickTvwItem( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_TvwInfo* pData = dynamic_cast< const Data_TvwInfo*>(pIData) )
        {
            m_wSelTvwIndex = pData->m_tTvwInfo.m_wIndex;
        }
    }
    return true;
}

bool CTvwManageLogic::OnClickTvwItemIcon( const IArgs & arg )
{
    if( m_pTvwCtrlIF == NULL )
    {
        return false;
    }

    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_TvwInfo *pData = dynamic_cast<const Data_TvwInfo*>( pBaseItem->GetUserData() ) ) 
        {
            THduPlanUnit tHduUnit = pData->m_tTvwInfo;

            TTPHduPlayReq tTvwInfo;
            tTvwInfo.SetAlias( tHduUnit.m_tName.m_abyAlias );
            tTvwInfo.m_wIndex = tHduUnit.m_wIndex;
            tTvwInfo.m_wScreenNum = tHduUnit.m_wScreenNum;
            u16 re = m_pTvwCtrlIF->StopHduReq( tTvwInfo );
        }
    }
    return true;
}

void CTvwManageLogic::SetCnsInTvw( u16 wIndex, TCnsInfo tCnsInfo, BOOL bSel /*= FALSE*/ )
{
    if ( wIndex < 0 || wIndex >= HDU_STYLE_MAX_NUM )
    {
        return;
    }
    if( m_pTvwCtrlIF == NULL )
    {
        return;
    }
    
    if ( tCnsInfo.m_wSpeakerNum == 1 )
    {  
        THduPlanUnit tPlanUnit = m_tHduPlanData.m_atUnits[wIndex];
        if ( !tPlanUnit.m_bValid )
        {
            return;
        }

        if ( bSel )
        {
            set<u32> setSelIndex;
            setSelIndex.insert( wIndex );

            if ( m_pTvwView != NULL )
            {
                m_pTvwView->SetMultiSelSet( setSelIndex );
            }
        }
        else
        {
            TTPHduPlayReq  tTvwInfo;
            tTvwInfo.SetAlias( tCnsInfo.m_achRoomName );
            tTvwInfo.m_wIndex = wIndex;
            tTvwInfo.m_wScreenNum = 1;
            u16 re = m_pTvwCtrlIF->PlayHduReq( tTvwInfo );
            if ( re != NO_ERROR )
            {
                //HANDLE_ERROR( re );
            }  
        }       		
    }
    else if ( tCnsInfo.m_wSpeakerNum == 3 || tCnsInfo.m_wSpeakerNum == 5 )
    {
        u8 byMaxCol = m_tHduPlanData.m_byCol;
        u8 byMaxRow = m_tHduPlanData.m_byRow;
        if ( byMaxCol == 0 || byMaxRow == 0 )
        {
            return;
        }

        THduPlanUnit tPlanUnit = m_tHduPlanData.m_atUnits[wIndex];
        if ( !tPlanUnit.m_bValid )
        {
            return;
        }

        u8 byCurtCol = wIndex % byMaxCol;
        u8 byCurtRow = wIndex / byMaxCol;
        
        int anChannel[3] = { 0 };

        u8 byFirstIndex = 0;
        u8 byLastIndex = 0;
        //大于等于3列的电视墙方案，只能进入当前行的电视墙中
        //小于3列的电视墙，支持自动换行
        if ( byMaxCol >= 3 )
        {   
            //找出这一行中配置过的电视墙
            byFirstIndex = byCurtRow * byMaxCol;
            byLastIndex = ( byCurtRow + 1 ) * byMaxCol - 1;
        }
        else
        {
            byFirstIndex = 0;
            byLastIndex = byMaxRow * byMaxCol - 1;
        }

        vector<u8> vctValidIndex;
        int nIndexInVct = 0; //wIndex在vctValidIndex中的索引
        int nValidSize = 0;  //vctValidIndex的size
        for ( u8 n = byFirstIndex; n <= byLastIndex; n++ )
        {
            THduPlanUnit tPlanUnit = m_tHduPlanData.m_atUnits[n];
            if ( tPlanUnit.m_bValid )
            {
                vctValidIndex.push_back( n );
                if ( n == wIndex )
                {
                    nIndexInVct = nValidSize;
                }
                nValidSize++;
            }
        }
        if ( nValidSize < 3 )
        {
            if( !bSel )
            {
                MESSAGEWND( "操作失败:电视墙资源不足" );
				m_wSelTvwIndex = wIndex;  //Bug00169725  by xhx
            }         
            return;
        }

        if ( nIndexInVct == 0 )
        {
            anChannel[0] = wIndex;
            anChannel[1] = vctValidIndex.at(1);
            anChannel[2] = vctValidIndex.at(2);
        }
        else if ( nIndexInVct == (nValidSize - 1) )
        {
            anChannel[0] = vctValidIndex.at( nIndexInVct - 2 );
            anChannel[1] = vctValidIndex.at( nIndexInVct - 1 );
            anChannel[2] = wIndex;
        }
        else
        {
            anChannel[0] = vctValidIndex.at( nIndexInVct - 1 );
            anChannel[1] = wIndex;
            anChannel[2] = vctValidIndex.at( nIndexInVct + 1 );
        }      
        
        set<u32> setSelIndex;

        for ( int i = 0; i < 3; i++ )
        {
            int nChannel = anChannel[i];
            	
            if ( bSel )
            {          
                setSelIndex.insert( nChannel );
            }
            else
            {
                TTPHduPlayReq tTvwInfo;
                tTvwInfo.SetAlias( tCnsInfo.m_achRoomName );
                tTvwInfo.m_wIndex = nChannel;
                tTvwInfo.m_wScreenNum = i;
                u16 re = m_pTvwCtrlIF->PlayHduReq( tTvwInfo );
                if ( re != NO_ERROR )
                {
                    //HANDLE_ERROR( re );
                }
            }
        }

        if ( bSel && !setSelIndex.empty() && m_pTvwView != NULL )
        {
            m_pTvwView->SetMultiSelSet( setSelIndex );
        }
    }
    
}




LRESULT CTvwManageLogic::OnRefreshConfList( WPARAM wparam, LPARAM lparam )
{
    if( m_pconfCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
    }
   
    m_vctCurConfList.clear();
    if ( m_pconfCtrlIF != NULL )
    {
		m_pconfCtrlIF->GetConfList( m_vctCurConfList );
    }
    /* 调试代码
    TCMSConf tConf;
    tConf.m_wConfID = 1;
    strcpy( tConf.m_achConfName, "haha" );
    
    TCnsInfo tCns;
    tCns.m_emEpType = emTPEndpointTypeCNS;
    tCns.m_wEpID = 1;
    tCns.m_wLevel = emTPSipCity;
    strcpy( tCns.m_achRoomName, "hehe" );
    tConf.m_tplCnsList.Add( &tCns );
    tCns.m_wEpID = 2;
    tCns.m_wLevel = emTPSipCounty;
    strcpy( tCns.m_achRoomName, "hoho" );
    tConf.m_tplCnsList.Add( &tCns );

    m_vctCurConfList.push_back( tConf );
    */

    if ( m_bInCnsList )
    {
        //如果会场列表的会议结会，跳到会议列表
        BOOL bFind = FALSE;
        for ( int i = 0; i < m_vctCurConfList.size(); i++ )
        {
            if ( m_vctCurConfList.at(i).m_wConfID == m_tSelConf.m_wConfID )
            {
                bFind = TRUE;
                break;
            }
        }
        if ( !bFind )
        {
            OnBtnBack();
        }

        return NO_ERROR;
    }


    CString strSearchName;
    m_etSearch.GetWindowText( strSearchName );
    if ( !strSearchName.IsEmpty() )
    {
        OnSearchEditChange( 0, 0 );
    }
    else
    {
        Value_ListConf val_curConfList( &m_vctCurConfList, "CTvwManageLogic::OnClickConfListItem" );
        if ( m_plsTvw != NULL )
        {
            m_plsTvw->SetData( val_curConfList );
            m_plsTvw->SetDragEnable( FALSE );
	    }
    }  
    
    return NO_ERROR;
}

LRESULT CTvwManageLogic::OnRefreshConfCnsList( WPARAM wparam, LPARAM lparam )
{
    if( m_pconfCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
    }

    if ( !m_bInCnsList )
    {
        OnRefreshConfList( 0, 0 );

        return NO_ERROR;
    }
    
    u16 wConfID = (u16)wparam;
    if ( m_tSelConf.m_wConfID == wConfID )
    {
        m_vctCurConfList.clear();
        if ( m_pconfCtrlIF != NULL )
        {
            m_pconfCtrlIF->GetConfList( m_vctCurConfList );
        }

        for ( int i = 0; i < m_vctCurConfList.size(); i++ )
        {
            if ( m_vctCurConfList.at(i).m_wConfID == m_tSelConf.m_wConfID )
            {
                m_tSelConf = m_vctCurConfList.at(i);
                break;
            }
        }

        UpdateConfCnsList();
            
    }
    
    return NO_ERROR;
}


void CTvwManageLogic::UpdateConfCnsList()
{
    CString strSearchName;
    m_etSearch.GetWindowText( strSearchName );
    if ( !strSearchName.IsEmpty() )
    {
        OnSearchEditChange( 0, 0 );
    }
    else
    {
        Value_ListConfInfo val( m_tSelConf, "", "CTvwManageLogic::OnClickCnsListIcon", !m_bManage );
        if ( m_plsTvw != NULL )
        {
            m_plsTvw->SetData( val );
            m_plsTvw->SetDragEnable( !m_bManage );
        }
    }
}


LRESULT CTvwManageLogic::OnHduPlanNty( WPARAM wparam, LPARAM lparam )
{
    if( m_pTvwCtrlIF == NULL )
    {
        return NO_ERROR;
    }

    //m_tHduPlanData = *(THduStyleData*)wparam;
    m_tHduPlanData = m_pTvwCtrlIF->GetTvwPlanData();

	//解决bug：ums未配置电视墙服务器，umc电视墙界面右侧不应该显示出通道和控件------------20130710sc
	if ( m_tHduPlanData.m_byCol != 0 || m_tHduPlanData.m_byRow != 0 )
	{
		if ( m_btnManage.IsWindowVisible() == FALSE && m_btnRemoveAll.IsWindowVisible() == FALSE )
		{
			m_btnManage.ShowWindow(SW_SHOW);
		}
		
		m_pTvwView->ShowWindow(SW_SHOW);
	}
	
    
    /* 调试代码
    m_tHduPlanData.m_byRow = 6;
    m_tHduPlanData.m_byCol = 9;
    THduPlanUnit tUnit;
    for ( int j = 0; j < 56; j++ )
    {
        tUnit.Clear();
        if ( j < 33 )
        {
            tUnit.m_bReged = TRUE;
        }       
        tUnit.m_bValid = TRUE;

        int n = j/3;
        CString str;
        str.Format( "CNS %d", n );
        tUnit.m_tName.SetAlias( (LPCTSTR)str );
        tUnit.m_wIndex = j;
        
        m_tHduPlanData.m_atUnits[j] = tUnit;
    }
    */
    
    //OnRefreshConfList( 0,0 );

    m_vctTvwCnsList.clear();

    s32 nHduCount = m_tHduPlanData.m_byRow * m_tHduPlanData.m_byCol;

    TTvwCns tTvwCns;

    BOOL bAllEmpty = TRUE; //是否电视墙中没会场

    for ( int i = 0; i < nHduCount; i++ )
    {
        THduPlanUnit tHduUnit = m_tHduPlanData.m_atUnits[i];

        if ( bAllEmpty && !tHduUnit.m_tName.IsEmpty() )
        {
            bAllEmpty = FALSE;
        }

        tTvwCns.Clear();
        tTvwCns.m_tHduUnit[0] = tHduUnit;

        //如果预案小于3列，不将3个屏连起来
        if ( m_tHduPlanData.m_byCol > 2 && tHduUnit.m_bValid && (tHduUnit.m_wScreenNum == 0) 
            && !tHduUnit.m_tName.IsEmpty() && (i+2) < nHduCount )
        {
            //判断是否是一个会场的3个屏
            THduPlanUnit tHduUnit1 = m_tHduPlanData.m_atUnits[i+1];
            THduPlanUnit tHduUnit2 = m_tHduPlanData.m_atUnits[i+2];

            if ( strcmp( tHduUnit1.m_tName.m_abyAlias, tHduUnit.m_tName.m_abyAlias ) == 0 &&
                 strcmp( tHduUnit2.m_tName.m_abyAlias, tHduUnit.m_tName.m_abyAlias ) == 0 &&
                 tHduUnit1. m_wScreenNum == 1 && tHduUnit2.m_wScreenNum == 2 )
            {
                tTvwCns.m_tHduUnit[1] = tHduUnit1;
                tTvwCns.m_tHduUnit[2] = tHduUnit2;
                tTvwCns.m_wScreenNum = 3;

                m_vctTvwCnsList.push_back( tTvwCns );
                i = i + 2;
                continue;
            }
        }

        m_vctTvwCnsList.push_back( tTvwCns );
    }
    
    Value_ViewListTvw val_ListTvw( &m_vctTvwCnsList, "CTvwManageLogic::OnClickTvwItem", m_tHduPlanData.m_byCol, m_bManage );
    if ( m_pTvwView != NULL )
    {
        m_pTvwView->SetData( val_ListTvw );
	}

	
	if( bAllEmpty )
	{
		m_btnRemoveAll.EnableWindow( FALSE );
	}
	else
	{
		m_btnRemoveAll.EnableWindow( TRUE );
	}

    return NO_ERROR;
}



LRESULT CTvwManageLogic::OnSearchEditChange(WPARAM wParam, LPARAM lParam)
{
    CString strSearchName;
    m_etSearch.GetWindowText( strSearchName );
    //if ( strSearchName.IsEmpty() )
    //{
        //UpdateShowList();
        
    //    return NO_ERROR;
    //}	
  
    if ( m_plsTvw != NULL )
    {
        m_plsTvw->SetYOffset( 0 );
    }
    
    BOOL bFind = FALSE;	
    if ( m_bInCnsList )
    {
        s32 nCount = m_tSelConf.m_tplCnsList.Size();

        vector<TCnsInfo> vctCnsList;
        for ( int i = 0; i < nCount; i++ )
        {
            TCnsInfo tCnsInfo = m_tSelConf.m_tplCnsList.GetAt(i);
           		
            bFind = CUmcwebCommon::HZPYMatchList( strSearchName, tCnsInfo.m_achRoomName );
            if ( bFind )
            {		
                vctCnsList.push_back( tCnsInfo );
            }
        }

        Value_ListConfCns val( &vctCnsList, "", "CTvwManageLogic::OnClickCnsListIcon", !m_bManage );
        if ( m_plsTvw != NULL )
        {
            m_plsTvw->SetData( val );
            m_plsTvw->SetDragEnable( !m_bManage );
	    }
    }
    else
    {     
        vector<TCMSConf> vctConfList;
        for ( int i = 0; i < m_vctCurConfList.size(); i++ )
        {
            TCMSConf tConf = m_vctCurConfList.at(i);
            
            bFind = CUmcwebCommon::HZPYMatchList( strSearchName, tConf.m_achConfName );
            if ( bFind )
            {		
                vctConfList.push_back( tConf );
            }
        }

        Value_ListConf val_ConfList( &vctConfList, "CTvwManageLogic::OnClickConfListItem" );
        if ( m_plsTvw != NULL )
        {
            m_plsTvw->SetData( val_ConfList );
	    }
    }

    return NO_ERROR;
}

LRESULT CTvwManageLogic::OnUnSelItemNotify(WPARAM wParam, LPARAM lParam)
{
    HWND hWnd = (HWND)wParam;
  
    if ( m_pTvwView->GetSafeHwnd() == hWnd )
	{
        m_wSelTvwIndex = TP_INVALID_INDEX;
    }
    return NO_ERROR;
}

LRESULT CTvwManageLogic::OnPlayHduRsp(WPARAM wParam, LPARAM lParam)
{
    EmTpHduPlayNackReason emReason = (EmTpHduPlayNackReason)lParam;

    CString strMsg = _T("请求电视墙播放失败");

    switch( emReason )
    {
    case em_hdu_play_success:
        return NO_ERROR;
    case em_Hdu_Invalid_Index:
        strMsg += "：无效的位置索引";
        break;
    case em_Hdu_Invalid_ID:
        strMsg += "：无效的ID";
        break;
    case em_Hdu_No_Reged:
        //strMsg += "：HDU未注册";
        return NO_ERROR;
    case em_Hdu_Illegal:
        strMsg += "：无效的HDU";
        break;
    case em_Alias_Illegal:
        strMsg += "：无效的别名";
        break;
    case em_Monitor_Fial:
        strMsg += "：显示失败";
        break;
    case em_Same_Alias:
        //strMsg += "：别名相同";
        return NO_ERROR;
    default:
        break;        
    }

    MESSAGEWND( strMsg );

    return NO_ERROR;
}


LRESULT CTvwManageLogic::OnDragOver(WPARAM wParam, LPARAM lParam)
{
    if ( const Data_ConfCns *pData = dynamic_cast<const Data_ConfCns*>( (IData*)wParam ) ) 
    {
        TCnsInfo tCnsInfo = pData->m_tConfCns;
        IItemList* pItemList = (IItemList*)lParam;
        if ( pItemList == NULL )
        {
            return NO_ERROR;
        }

        const IData *pIData = pItemList->GetItemData()->GetUserData();
        if ( const Data_TvwInfo* pData = dynamic_cast< const Data_TvwInfo*>(pIData) )
        {
            SetCnsInTvw( pData->m_tTvwInfo.m_wIndex, tCnsInfo, TRUE );
        }
    }

    return NO_ERROR;
}

LRESULT CTvwManageLogic::OnDragLeave(WPARAM wParam, LPARAM lParam)
{
    if ( m_pTvwView != NULL )
    {
        m_pTvwView->ClearAllSel();
	}
    
    return NO_ERROR;
}

LRESULT CTvwManageLogic::OnDragEnd(WPARAM wParam, LPARAM lParam)
{
    if ( const Data_ConfCns *pData = dynamic_cast<const Data_ConfCns*>( (IData*)wParam ) ) 
    {
        TCnsInfo tCnsInfo = pData->m_tConfCns;
        IItemList* pItemList = (IItemList*)lParam;
        if ( pItemList == NULL )
        {
            return NO_ERROR;
        }
        
        const IData *pIData = pItemList->GetItemData()->GetUserData();
        if ( const Data_TvwInfo* pData = dynamic_cast< const Data_TvwInfo*>(pIData) )
        {
            SetCnsInTvw( pData->m_tTvwInfo.m_wIndex, tCnsInfo, FALSE );
        }
    }
    return NO_ERROR;
}

void CTvwManageLogic::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDlgChild::OnShowWindow( bShow, nStatus );

	//解决bug：ums未配置电视墙服务器，umc电视墙界面右侧不应该显示出通道和控件------------20130710sc
	if ( bShow == TRUE )
	{
		THduPlanData tHduPlanData;
		tHduPlanData = m_pTvwCtrlIF->GetTvwPlanData();
		if ( tHduPlanData.m_byRow == 0 && tHduPlanData.m_byCol == 0 )
		{
			m_btnManage.ShowWindow(SW_HIDE);
			m_pTvwView->ShowWindow(SW_HIDE);
		}
	}
}