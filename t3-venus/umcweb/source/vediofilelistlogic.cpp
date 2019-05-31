// vediofilelistlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "vediofilelistlogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

/////////////////////////////////////////////////////////////////////////////
// CVedioFileListLogic dialog

enum emScheme
{
	emSchemeInit = 0,
	emSelAll,
	emUnSelAll,
	emSchemeEnd,
	emEdit,
	emUnEdit,
	emSchemeNoShow,
	emSchemeRefreshFileList
};

CVedioFileListLogic::CVedioFileListLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CVedioFileListLogic::IDD, pParent)
{
	m_pListVedioFile = NULL;
	m_pListDel = NULL;
	m_pLetterIndex = NULL;
	m_pVTRCtrlIF = NULL;
}


void CVedioFileListLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVedioFileListLogic)
	DDX_Control(pDX, IDC_BUTTON_DEL_SINGLE, m_btnDelSingle);
	DDX_Control(pDX, IDC_STATIC_EQP_ID_REAL, m_stcEqpIDReal);
	DDX_Control(pDX, IDC_BUTTON_VTR_CHECK_ALL, m_btnCheckAll);
	DDX_Control(pDX, IDC_BUTTON_VTR_UNCHECK_ALL, m_btnUnCheckAll);
	DDX_Control(pDX, IDC_STATIC_VTR_FILENAME, m_stcFileName);
	DDX_Control(pDX, IDC_EDIT_VTR_SEARCH, m_sedtSearch);
	DDX_Control(pDX, IDC_EDIT_VTR_FILENAME, m_edtFileName);
	DDX_Control(pDX, IDC_BUTTON_VTR_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_VTR_FILEBACK, m_btnBack);
	DDX_Control(pDX, IDC_BUTTON_VTR_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_VTR_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_VTR_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATIC_CHILDWNDTITLE, m_stcChildWndTitle);
	DDX_Control(pDX, IDC_STATIC_Title, m_stcTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVedioFileListLogic, CDlgChild)
	//{{AFX_MSG_MAP(CVedioFileListLogic)
	ON_BN_CLICKED(IDC_BUTTON_VTR_FILEBACK, OnButtonVtrFileback)
	ON_MESSAGE( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, CVedioFileListLogic::OnRecFileListInfoNty )
	ON_MESSAGE( UI_UMSTOOL_REC_MDY_FILE_RSP, CVedioFileListLogic::OnRecMdyFileRsp )	
	ON_MESSAGE( UI_UMSTOOL_REC_DEL_FILE_RSP, CVedioFileListLogic::OnRecDelFileRsp )	
	ON_BN_CLICKED(IDC_BUTTON_VTR_EDIT, OnButtonVtrEdit)
	ON_BN_CLICKED(IDC_BUTTON_VTR_SAVE, OnButtonVtrSave)
	ON_BN_CLICKED(IDC_BUTTON_VTR_CANCEL, OnButtonVtrCancel)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SINGLE, OnButtonDelSingle)
	ON_BN_CLICKED(IDC_BUTTON_VTR_DEL, OnButtonVtrDel)
	ON_BN_CLICKED(IDC_BUTTON_VTR_CHECK_ALL, OnButtonVtrCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_VTR_UNCHECK_ALL, OnButtonVtrUnCheckAll)
	ON_MESSAGE( WM_EDIT_CHANGED, OnUpdateEditVtrSearch )
	ON_WM_DESTROY()
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM,  OnNoSelResultNotify )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVedioFileListLogic message handlers
void CVedioFileListLogic::RegisterFun()
{
	REG_MSG_HANDLER( _T("CVedioFileListLogic::OnClickLstItem"), CVedioFileListLogic::OnClickLstItem, this, CVedioFileListLogic );
	REG_MSG_HANDLER( _T("CVedioFileListLogic::OnClickLstItemIcon"), CVedioFileListLogic::OnClickLstItemIcon, this,CVedioFileListLogic );
	REG_MSG_HANDLER( _T("CVedioFileListLogic::OnClickDelLstItem"), CVedioFileListLogic::OnClickDelLstItem, this, CVedioFileListLogic );
	REG_MSG_HANDLER( _T("CVedioFileListLogic::OnClickDelLstItemIcon"), CVedioFileListLogic::OnClickDelLstItemIcon, this,CVedioFileListLogic );
	REG_MSG( UI_UMSTOOL_REC_MDY_FILE_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_DEL_FILE_RSP, GetSafeHwnd() );
}

BOOL CVedioFileListLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}

	LoadScheme( emSchemeInit );

	if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
    }

	return TRUE;
}

void CVedioFileListLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	SAFE_RELEASE( m_pListVedioFile );
	SAFE_RELEASE( m_pListDel );
	SAFE_RELEASE( m_pLetterIndex );

	UN_REG_MSG_HANDLER( "CVedioFileListLogic::OnClickLstItem" );	
	UN_REG_MSG_HANDLER( "CVedioFileListLogic::OnClickLstItemIcon" );

	UN_REG_MSG_HANDLER( "CVedioFileListLogic::OnClickPollingPageDelItemIcon" );
	UN_REG_MSG_HANDLER( "CVedioFileListLogic::OnClickPollingPageDelItem" );
}


BOOL CVedioFileListLogic::InitControlPane()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_btnBack.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnBack.SetWindowPos( NULL, 9*CUR_SCREEN_WIDTH_PER,  6*CUR_SCREEN_HEIGHT_PER, 66, 36, SWP_SHOWWINDOW );


	CUmcwebCommon::SetTextTransStatic( &m_stcChildWndTitle, _T("已选列表") , 14, Color( 24, 25, 27 ) );
	m_stcChildWndTitle.SetWindowPos( NULL, 702*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcTitle, _T("录像文件列表") , 14, Color( 24, 25, 27 ) );
	m_stcTitle.	SetWindowPos( NULL, (17+70)*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	

	m_btnSave.SetImage( IDR_PNG_BTN_SAVE, IDR_PNG_BTN_SAVEDOWN, IDR_PNG_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_BTN_CANCEL, IDR_PNG_BTN_CANCELDOWN, IDR_PNG_BTN_CANCEL );
	m_btnEdit.SetImage( IDR_PNG_BTN_EDIT, IDR_PNG_BTN_EDITDOWN, IDR_PNG_BTN_EDIT );
	m_btnCancel.SetWindowPos( NULL, (1226 - 8 - m_btnCancel.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnCancel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCancel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnEdit.SetWindowPos( NULL,  (1226 - 8 - m_btnEdit.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnEdit.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnSave.SetWindowPos( NULL, rectClient.left - (8 + m_btnSave.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnSave.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	//列表加入
	if ( m_pListVedioFile == NULL )
	{
		m_pListVedioFile = new CListChild( "", CRect(12, 98, (690 - 57)+12, 488+98), this, "", GETUNIQID, WS_CHILD );

		m_pListVedioFile->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, (690 - 57)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_pListVedioFile->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_pListVedioFile->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pListVedioFile->SetSliderAlwaysShow( TRUE );
		
		
		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
		if (m_pLetterIndex != NULL)
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
			m_pLetterIndex->SetBindList( m_pListVedioFile );

			m_pListVedioFile->GetWindowRect(&rectClient);
			ScreenToClient( &rectClient );

			rectClient.left = rectClient.right - 3;
			rectClient.right = rectClient.left + 7;

			m_pListVedioFile->SetSliderRect( rectClient );

			m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_HIDEWINDOW );	

		}
	}

	m_btnUnCheckAll.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
	m_btnCheckAll.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
	m_btnCheckAll.SetWindowPos( NULL, rectClient.right - m_btnCheckAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnCheckAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCheckAll.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnUnCheckAll.SetWindowPos( NULL, rectClient.right - m_btnUnCheckAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnUnCheckAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCheckAll.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnCheckAll.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

	CUmcwebCommon::SetImgForTransSearchEdit(&m_sedtSearch);
	m_sedtSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  rectClient.right - 
		m_btnCheckAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );


	this->GetClientRect(&rectClient);	
	
	CUmcwebCommon::SetTextTransStatic( &m_stcFileName, _T("文件名称") , 13, Color( 44, 55, 76 ) );
	m_stcFileName.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  77*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	CUmcwebCommon::SetImgForTransEdit(&m_edtFileName);
	m_edtFileName.SetWindowPos( NULL, (1226 - 405)*CUR_SCREEN_WIDTH_PER , 64*CUR_SCREEN_HEIGHT_PER,  (391 - 10)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_edtFileName.EnableWindow( FALSE );
	m_edtFileName.SetLimitLength( 32 );
	

	m_pListDel = new CListChild( "", CRect((690 + 12) , 98, 514+(690 + 12), 488+98), this, "", 0, WS_CHILD );
	if ( NULL != m_pListDel )
	{
		m_pListDel->SetWindowPos( NULL, (690 + 12)*CUR_SCREEN_WIDTH_PER , 98*CUR_SCREEN_HEIGHT_PER, 514*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_pListDel->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_pListDel->GetWindowRect(&rectClient);
		ScreenToClient( &rectClient );
	}

	m_btnDel.SetImage( IDR_PNG_BTN_DELETE, IDR_PNG_BTN_DELETEDOWN, IDR_PNG_BTN_DELETEDIS );
	m_btnDel.SetWindowPos( NULL, (1226 - 10 - m_btnDel.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_WIDTH_PER, 
		m_btnDel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );


	m_btnDelSingle.SetImage( IDR_PNG_BTN_DELETEITEM, IDR_PNG_BTN_DELETEITEMDOWN, NULL );
	m_btnDelSingle.SetWindowPos( NULL, 684*CUR_SCREEN_WIDTH_PER  + ((1226 - 685)*CUR_SCREEN_WIDTH_PER - m_btnDelSingle.GetImageSize().cx*CUR_SCREEN_WIDTH_PER)/2, rectClient.bottom - 5*CUR_SCREEN_HEIGHT_PER -m_btnDelSingle.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, m_btnDelSingle.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDelSingle.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	

	return TRUE;
}

void CVedioFileListLogic::SetControlPos()
{
	
}

void CVedioFileListLogic::InitDlg()
{   
	ShowWindow(SW_HIDE);

	m_tRecFileInfoSel.Clear();
	m_vecTRecFileInfoSel.clear();
	m_vecTRecFileInfoSearch.clear();

	Value_ListFile val_ListFile( &m_vecTRecFileInfoSearch, "CVedioFileListLogic::OnClickLstItem", 0, &m_vecTRecFileInfoSel );
	if ( m_pListVedioFile )
	{
		m_pListVedioFile->SetData( val_ListFile );
	}
	

	Value_ListFile val_ListFileDel( &m_vecTRecFileInfoSel, "CVedioFileListLogic::OnClickDelLstItem", 1 );
	if (m_pListDel)
	{
		m_pListDel->SetData( val_ListFile );
	}
		

	LoadScheme( emSchemeInit );
}

void CVedioFileListLogic::OnButtonVtrFileback() 
{
	GetParent()->SendMessage( MSG_UI_VTR_TAB_CHANGE, em_WND_VTRSET, 0 );
}

bool CVedioFileListLogic::OnClickLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_FileInfo *pItemInfo = dynamic_cast<const Data_FileInfo*>( pBaseItem->GetUserData() )) 
        {
			if ( m_vecTRecFileInfoSel.size() > 0 )
			{
				return true;
			}

			m_tRecFileInfoSel = pItemInfo->m_tRecFileInfo;

			ShowFileInfoPage( TRUE );
			SetFileInfo( m_tRecFileInfoSel );
		}
    }
	
	return true;
}

bool CVedioFileListLogic::OnClickLstItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_FileInfo *pItemInfo = dynamic_cast<const Data_FileInfo*>( pBaseItem->GetUserData() )) 
        {   
			if ( m_bEdit == TRUE )
			{
				return true;
			}

			m_tRecFileInfoSel.Clear();

			bool bFind = false;
			TRecFileInfo tRecFileInfo = pItemInfo->m_tRecFileInfo;
			vector<TRecFileInfo>::iterator it = m_vecTRecFileInfoSel.begin();
			for ( ; it != m_vecTRecFileInfoSel.end(); it++ )
			{
				if ( it->m_byEqpID == tRecFileInfo.m_byEqpID && StrCmp( it->m_szFilelName, tRecFileInfo.m_szFilelName ) == 0 )
				{
					m_vecTRecFileInfoSel.erase(it);
					bFind = true;
					break;
				}
			}

			if ( bFind == false )
			{
				m_vecTRecFileInfoSel.push_back(tRecFileInfo);
			}

			if ( m_vecTRecFileInfoSel.size() > 0 )
			{
				ShowDelPage( TRUE );

				if ( m_vecTRecFileInfoSel.size() != m_vecTRecFileInfoSearch.size() )
				{
					m_btnUnCheckAll.ShowWindow(FALSE);
					m_btnCheckAll.ShowWindow(SW_SHOW);
				}
			}
			else
			{
				m_pListVedioFile->SetSelItem( -1 );
				m_tRecFileInfoSel.Clear();
				LoadScheme(emUnSelAll);
			}

			RefreshAllList();
			
        } 
    }
	
    return true;
}

bool CVedioFileListLogic::OnClickDelLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_FileInfo *pItemInfo = dynamic_cast<const Data_FileInfo*>( pBaseItem->GetUserData() )) 
		{   
			int k = 0;
		}
	}
	return true;
}

bool CVedioFileListLogic::OnClickDelLstItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_FileInfo *pItemInfo = dynamic_cast<const Data_FileInfo*>( pBaseItem->GetUserData() )) 
        {   
			TRecFileInfo tRecFileInfo = pItemInfo->m_tRecFileInfo;
			vector<TRecFileInfo>::iterator it = m_vecTRecFileInfoSel.begin();
			for ( ; it != m_vecTRecFileInfoSel.end(); it++ )
			{
				if ( it->m_byEqpID == tRecFileInfo.m_byEqpID && StrCmp( it->m_szFilelName, tRecFileInfo.m_szFilelName ) == 0 )
				{					
					m_vecTRecFileInfoSel.erase( it );

					if ( m_vecTRecFileInfoSel.size() > 0 )
					{
						ShowDelPage( TRUE );

						if ( m_vecTRecFileInfoSel.size() != m_vecTRecFileInfoSearch.size() )
						{
							m_btnUnCheckAll.ShowWindow(FALSE);
							m_btnCheckAll.ShowWindow(SW_SHOW);
						}
					}
					else
					{
						m_pListVedioFile->SetSelItem( -1 );
						m_tRecFileInfoSel.Clear();
						LoadScheme(emUnSelAll);
					}

					RefreshAllList();

					return true;
				}
			}
        } 
    }
	
    return true;
}

LRESULT CVedioFileListLogic::OnRecFileListInfoNty( WPARAM wparam, LPARAM lparam )
{
	LoadScheme( emSchemeRefreshFileList );

	m_vecTRecFileInfoSel.clear();

	RefreshAllList();

	return S_OK;
}

LRESULT CVedioFileListLogic::OnRecMdyFileRsp( WPARAM wparam, LPARAM lparam )
{
	TRecFileInfo* pTRecFileInfo  = reinterpret_cast<TRecFileInfo*>(wparam);
	TRecFileInfo tRecFileInfoOld = *pTRecFileInfo;
	TRecFileInfo tRecFileInfoNew = *++pTRecFileInfo;

	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		MESSAGEWND( _T("修改文件失败") );
		SetFileInfo( tRecFileInfoOld );
	}
	else
	{
		strncpy( m_tRecFileInfoSel.m_szFilelName, tRecFileInfoNew.m_szFilelName, TP_REC_FILE_LEN-1 );
		m_tRecFileInfoSel.m_szFilelName[TP_REC_FILE_LEN-1] = '\0';

		RefreshRecFileList();
	}
	
	return S_OK;
}

LRESULT CVedioFileListLogic::OnRecDelFileRsp( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		MESSAGEWND( _T("删除文件失败") );
	}
	else
	{
		m_vecTRecFileInfoSel.clear();
		m_tRecFileInfoSel.Clear();

		RefreshAllList();
	}
	
	return S_OK;
}

void CVedioFileListLogic::RefreshRecFileList()
{
	vector<TRecFileInfo> vecTRecFileInfoNoSuffix;
	if ( m_pVTRCtrlIF != NULL )
	{
		m_pVTRCtrlIF->GetRecFileListInfoNoSuffix( vecTRecFileInfoNoSuffix );
	}

	m_vecTRecFileInfoSearch.clear();

	int n = vecTRecFileInfoNoSuffix.size();

	CString strSearch;
	m_sedtSearch.GetWindowText(strSearch);
	if ( strSearch != _T("") )
	{
		vector<TRecFileInfo>::iterator it = vecTRecFileInfoNoSuffix.begin();
		for ( ; it != vecTRecFileInfoNoSuffix.end(); it++ )
		{
			BOOL bFind = FALSE;			
			bFind = CUmcwebCommon::HZPYMatchList( strSearch, it->m_szFilelName );
			if ( bFind )
			{		
				m_vecTRecFileInfoSearch.push_back(*it);
			}
		}
	}
	else
	{
		m_vecTRecFileInfoSearch = vecTRecFileInfoNoSuffix;
	}
	

	if ( m_pListVedioFile != NULL )
	{
		Value_ListFile val_ListFile( &m_vecTRecFileInfoSearch, "CVedioFileListLogic::OnClickLstItem", 0, &m_vecTRecFileInfoSel );
		m_pListVedioFile->SetData( val_ListFile );
		m_pListVedioFile->SetSelItem(-1);

// 		if ( m_tRecFileInfoSel.m_szFilelName[0] != '\0' )
// 		{
// 			int nSelItem = -1;
// 			vector<TRecFileInfo>::iterator it = m_vecTRecFileInfoSearch.begin();
// 			for ( ; it != m_vecTRecFileInfoSearch.end(); it++ )
// 			{
// 				nSelItem++;
// 				if ( strcmp( it->m_szFilelName, m_tRecFileInfoSel.m_szFilelName ) == 0 )
// 				{
// 					m_pListVedioFile->SetSelItem(nSelItem);
// 					break;
// 				}
// 			}
// 		}
 	}

	if ( m_vecTRecFileInfoSearch.size() == 0 )
	{
		m_btnCheckAll.EnableWindow( FALSE );
	}
	else
	{
		m_btnCheckAll.EnableWindow(TRUE);
	}
}

void CVedioFileListLogic::SetFileInfo( TRecFileInfo tRecFileInfo )
{
	CString strCaption;
	strCaption.Format( _T("%d"), tRecFileInfo.m_byEqpID );
	m_edtFileName.SetWindowText( tRecFileInfo.m_szFilelName );
	m_stcEqpIDReal.SetWindowText( strCaption );
}

void CVedioFileListLogic::GetFileInfo( TRecFileInfo &tRecFileInfo )
{
	CString strCaption;
	m_edtFileName.GetWindowText( strCaption );
	strncpy( tRecFileInfo.m_szFilelName, strCaption, TP_REC_FILE_LEN-1 );
	m_stcEqpIDReal.GetWindowText( strCaption );
	tRecFileInfo.m_byEqpID = _ttoi( strCaption );
}

void CVedioFileListLogic::OnButtonVtrEdit() 
{
	m_bEdit = TRUE;
	LoadScheme(emEdit);
}

void CVedioFileListLogic::OnButtonVtrSave() 
{
	TRecFileInfo tRecFileInfoNew;
	GetFileInfo( tRecFileInfoNew );

	if ( tRecFileInfoNew.m_szFilelName[0] == '\0' )
	{
		CString strError;
		int nRet = 0;
		strError = "修改文件名不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}

	int nRet = CheckFileName( tRecFileInfoNew.m_szFilelName );

	int nRes = 0;
	switch( nRet )
	{
	case 0:
		{
			break;
		}
	case 1:
		{
			MESSAGEWNDBOX( "文件名不能为空", this , nRes , FALSE );
			return;
		}
	case 2:
		{
			CString str;
			str.Format( "文件名超过最大长度：%d", MAX_VTR_FILE_LIST_SIZE );
			MESSAGEWNDBOX( str, this , nRes , FALSE );
			return;
		}
	case 3:
		{
			MESSAGEWNDBOX( "文件名不可以包含空格及括号中的任意字符[* ? \" < > | / \ :]", this , nRes , FALSE );
			return;
		}
	case 4:
		{
			if ( 0 == strcmp(tRecFileInfoNew.m_szFilelName, m_tRecFileInfoSel.m_szFilelName) )
			{
				OnButtonVtrCancel();
			}
			else
			{
				MESSAGEWNDBOX( "文件名已存在，不能修改", this , nRes , FALSE );
			}
			return;
		}
	default:
		break;
	}

	if( m_pVTRCtrlIF != NULL )
    {
        u16 nRet = m_pVTRCtrlIF->RecMdyFileReq( m_tRecFileInfoSel, tRecFileInfoNew );
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( _T("修改文件请求发送失败") );
		}
    }
	m_bEdit = FALSE;
	LoadScheme(emUnEdit);
}

void CVedioFileListLogic::OnButtonVtrCancel() 
{
	m_bEdit = FALSE;
	LoadScheme(emUnEdit);
	SetFileInfo( m_tRecFileInfoSel );
}

void CVedioFileListLogic::OnButtonDelSingle() 
{
	CString strMsg = "是否将所选条目从录像文件列表中删除?";
	
	s32 nRet = 0;
	MESSAGEWNDBOX( strMsg, this, nRet, TRUE );
	
	if ( IDOK == nRet )
	{
		SetDeleteFile(m_tRecFileInfoSel);
	}
}

void CVedioFileListLogic::ShowFileInfoPage( BOOL bShow )
{
	if ( bShow == TRUE )
	{
		m_stcChildWndTitle.SetWindowText( _T("文件信息") );
		m_btnEdit.ShowWindow( SW_SHOW );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_stcFileName.ShowWindow( SW_SHOW );
		m_edtFileName.ShowWindow( SW_SHOW );
		m_btnDelSingle.ShowWindow( SW_SHOW );
		m_btnDel.ShowWindow( SW_HIDE );
		m_pListDel->ShowWindow( SW_HIDE );
	}
	else
	{
		m_stcChildWndTitle.SetWindowText( _T("") );
		m_btnEdit.ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_stcFileName.ShowWindow( SW_HIDE );
		m_edtFileName.ShowWindow( SW_HIDE );
		m_btnDelSingle.ShowWindow( SW_HIDE );
	}
}

void CVedioFileListLogic::ShowDelPage( BOOL bShow )
{
	if ( bShow == TRUE )
	{
		m_stcChildWndTitle.SetWindowText( _T("已选列表") );
		m_btnEdit.ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_stcFileName.ShowWindow( SW_HIDE );
		m_edtFileName.ShowWindow( SW_HIDE );
		m_btnDelSingle.ShowWindow( SW_HIDE );
		m_btnDel.ShowWindow( SW_SHOW );
		m_pListDel->ShowWindow( SW_SHOW );
	}
	else
	{
		m_stcChildWndTitle.SetWindowText( _T("") );
		m_btnDel.ShowWindow( SW_HIDE );
		m_pListDel->ShowWindow( SW_HIDE );
	}
}

void CVedioFileListLogic::RefreshDelList()
{
	if ( m_pListVedioFile != NULL )
	{
		Value_ListFile val_ListFile( &m_vecTRecFileInfoSel, "CVedioFileListLogic::OnClickDelLstItem", 1 );
		m_pListDel->SetData( val_ListFile );
		m_pListDel->SetSelItem(-1);
 	}
}

void CVedioFileListLogic::OnButtonVtrDel() 
{
	CString strMsg = "是否将所选条目从录像文件列表中删除?";
	
	s32 nRet = 0;
	MESSAGEWNDBOX( strMsg, this, nRet, TRUE );
	
	if ( IDOK == nRet )
	{
		vector<TRecFileInfo> vecTRecFileInfoSel = m_vecTRecFileInfoSel;
		vector<TRecFileInfo>::iterator it = vecTRecFileInfoSel.begin();
		for ( ; it != vecTRecFileInfoSel.end(); it++ )
		{
			SetDeleteFile(*it);
		}
	}
}

void CVedioFileListLogic::OnButtonVtrCheckAll() 
{
//	LoadScheme( emSchemeInit );

	m_vecTRecFileInfoSel.clear();
	m_vecTRecFileInfoSel = m_vecTRecFileInfoSearch;

	ShowDelPage( TRUE );
	
	RefreshAllList();
}

void CVedioFileListLogic::OnButtonVtrUnCheckAll() 
{
	LoadScheme( emUnSelAll );
	
	m_vecTRecFileInfoSel.clear();
	
	if ( m_tRecFileInfoSel.m_szFilelName[0] != '\0' )
	{
		ShowFileInfoPage( TRUE );
		SetFileInfo( m_tRecFileInfoSel );
	}
	
	RefreshAllList();
}

LRESULT CVedioFileListLogic::OnUpdateEditVtrSearch( WPARAM wparam, LPARAM lparam ) 
{
	HWND hWnd = (HWND)wparam;
	if ( m_sedtSearch.GetSafeHwnd() != hWnd )
	{
		return 0;
	}

	ShowFileInfoPage( FALSE );
	LoadScheme(emUnSelAll);

	m_pListVedioFile->SetSelItem(-1);
	m_tRecFileInfoSel.Clear();
	m_pListDel->SetSelItem(-1);
	m_vecTRecFileInfoSel.clear();

	RefreshAllList();

	return 0;
}

BOOL CVedioFileListLogic::SetDeleteFile( TRecFileInfo tRecFileInfo )
{
	if( m_pVTRCtrlIF != NULL )
	{
		vector<TConfPlayStatus> vecTConfPlayStatus;
		m_pVTRCtrlIF->GetPlayConfInfo(vecTConfPlayStatus);
		vector<TConfPlayStatus>::iterator it = vecTConfPlayStatus.begin();
		for ( ; it != vecTConfPlayStatus.end(); it++ )
		{
			if ( ( it->m_emState == em_rec_working || it->m_emState == em_rec_pause )
				&& ( strcmp( it->m_tInfo.m_szFileName, tRecFileInfo.m_szFilelName ) == 0 ) )
			{
				s32 nRet = 0;
				CString str;
				str.Format( "%s:正在放像，无法删除", tRecFileInfo.m_szFilelName );
				MESSAGEWNDBOX( str, this , nRet , FALSE );
				return FALSE;
			}
		}

		u16 nRet = m_pVTRCtrlIF->RecDelFileReq( tRecFileInfo );
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( _T("删除文件请求发送失败") );
			return FALSE;
		}
		else
		{
			return TRUE;
		}
    }

	return FALSE;
}

void CVedioFileListLogic::RefreshAllList()
{
	RefreshRecFileList();
	RefreshDelList();
	if ( m_vecTRecFileInfoSel.size() == m_vecTRecFileInfoSearch.size()
		&& m_vecTRecFileInfoSel.size() > 0
		&& m_vecTRecFileInfoSearch.size() > 0 )
	{
		LoadScheme( emSelAll );
	}
}

void CVedioFileListLogic::LoadScheme( int emScheme )
{
	switch( emScheme )
	{
	case emSchemeInit:
		{
			m_btnBack.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.SetWindowText( _T("") );
			m_stcTitle.ShowWindow(SW_SHOW);

			m_sedtSearch.ShowWindow(SW_SHOW);
			m_sedtSearch.SetWindowText("");
			m_sedtSearch.EnableWindow(TRUE);

			m_btnCheckAll.ShowWindow(SW_SHOW);
			m_btnCheckAll.EnableWindow(FALSE);
			m_btnCheckAll.EnableWindow(FALSE);
			m_btnUnCheckAll.ShowWindow(SW_HIDE);

			m_stcFileName.ShowWindow(SW_HIDE);
			m_edtFileName.EnableWindow( FALSE );
			m_edtFileName.ShowWindow(SW_HIDE);
			m_edtFileName.SetWindowText("");
			m_stcEqpIDReal.ShowWindow(SW_HIDE);
			

			m_btnSave.ShowWindow(SW_HIDE);
			m_btnEdit.ShowWindow(SW_HIDE);
			m_btnCancel.ShowWindow(SW_HIDE);

			m_btnDel.ShowWindow(SW_HIDE);
			m_btnDelSingle.ShowWindow(SW_HIDE);

			m_pListVedioFile->EnableWindow(TRUE);
			m_pListVedioFile->ShowWindow(SW_SHOW);
			m_pListDel->ShowWindow(SW_HIDE);

			break;
		}
	case emSelAll:
		{
			m_btnCheckAll.ShowWindow(SW_HIDE);
			m_btnUnCheckAll.ShowWindow(SW_SHOW);
			break;
		}
	case emUnSelAll:
		{
			m_stcChildWndTitle.SetWindowText( _T("") );
			m_btnDel.ShowWindow(SW_HIDE);
			m_pListDel->ShowWindow(SW_HIDE);
			m_btnCheckAll.ShowWindow(SW_SHOW);
			m_btnUnCheckAll.ShowWindow(SW_HIDE);
			break;
		}
	case emEdit:
		{
			m_btnEdit.ShowWindow( SW_HIDE );
			m_btnSave.ShowWindow( SW_SHOW );
			m_btnCancel.ShowWindow( SW_SHOW );
			m_btnDelSingle.ShowWindow( SW_HIDE );
			m_edtFileName.EnableWindow( TRUE );
			m_pListVedioFile->EnableWindow(FALSE);
			m_btnCheckAll.EnableWindow(FALSE);
			m_btnUnCheckAll.EnableWindow(FALSE);
			m_sedtSearch.EnableWindow(FALSE);
			break;
		}
	case emUnEdit:
		{
			m_btnEdit.ShowWindow( SW_SHOW );
			m_btnSave.ShowWindow( SW_HIDE );
			m_btnCancel.ShowWindow( SW_HIDE );
			m_btnDelSingle.ShowWindow( SW_SHOW );
			m_edtFileName.EnableWindow( FALSE );
			m_pListVedioFile->EnableWindow(TRUE);
			m_btnCheckAll.EnableWindow(TRUE);
			m_btnUnCheckAll.EnableWindow(TRUE);
			m_sedtSearch.EnableWindow(TRUE);

			break;
		}
	case emSchemeNoShow:
		{
			m_btnBack.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.SetWindowText( _T("") );
			m_stcTitle.ShowWindow(SW_SHOW);
			
			m_sedtSearch.ShowWindow(SW_SHOW);
			m_sedtSearch.EnableWindow(TRUE);
			
			m_btnCheckAll.ShowWindow(SW_SHOW);
			m_btnUnCheckAll.ShowWindow(SW_HIDE);
			
			m_stcFileName.ShowWindow(SW_HIDE);
			m_edtFileName.ShowWindow(SW_HIDE);
			m_edtFileName.SetWindowText("");
			m_stcEqpIDReal.ShowWindow(SW_HIDE);
			
			
			m_btnSave.ShowWindow(SW_HIDE);
			m_btnEdit.ShowWindow(SW_HIDE);
			m_btnCancel.ShowWindow(SW_HIDE);
			
			m_btnDel.ShowWindow(SW_HIDE);
			m_btnDelSingle.ShowWindow(SW_HIDE);
			
			m_pListVedioFile->ShowWindow(SW_SHOW);
			m_pListDel->ShowWindow(SW_HIDE);
			
			break;
		}
	case emSchemeRefreshFileList:
		{
			m_btnBack.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.SetWindowText( _T("") );
			m_stcTitle.ShowWindow(SW_SHOW);
			
			m_sedtSearch.ShowWindow(SW_SHOW);
			m_sedtSearch.EnableWindow(TRUE);
			
			m_btnCheckAll.ShowWindow(SW_SHOW);
			m_btnUnCheckAll.ShowWindow(SW_HIDE);
			
			m_stcFileName.ShowWindow(SW_HIDE);
			m_edtFileName.EnableWindow( FALSE );
			m_edtFileName.ShowWindow(SW_HIDE);
			m_edtFileName.SetWindowText("");
			m_stcEqpIDReal.ShowWindow(SW_HIDE);
			
			
			m_btnSave.ShowWindow(SW_HIDE);
			m_btnEdit.ShowWindow(SW_HIDE);
			m_btnCancel.ShowWindow(SW_HIDE);
			
			m_btnDel.ShowWindow(SW_HIDE);
			m_btnDelSingle.ShowWindow(SW_HIDE);
			
			m_pListVedioFile->EnableWindow(TRUE);
			m_pListVedioFile->ShowWindow(SW_SHOW);
			m_pListDel->ShowWindow(SW_HIDE);
			
			break;
		}
	default:
		break;
	}
}

LRESULT CVedioFileListLogic::OnNoSelResultNotify(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;
	
	if ( hWnd == m_pListVedioFile->GetSafeHwnd() )
	{
		if ( m_vecTRecFileInfoSel.size() == 0 )
		{
			LoadScheme(emSchemeNoShow);
		}

		m_tRecFileInfoSel.Clear();
		
	}
	
	return 0;
}

int CVedioFileListLogic::CheckFileName( CString strFileName )
{
	if ( strFileName.IsEmpty() )
	{
		return 1;
	}

	int nLength = strFileName.GetLength();
	if ( nLength > MAX_VTR_FILE_LIST_SIZE )
	{
		return 2;
	}
	
	if (  strFileName.Find( '*') != -1 || strFileName.Find( '?') != -1 || strFileName.Find( '"') != -1
		|| strFileName.Find( '<') != -1 || strFileName.Find( '>') != -1 || strFileName.Find( '|') != -1 
		|| strFileName.Find( '\/' ) != -1 || strFileName.Find( '\\') != -1 || strFileName.Find( ':') != -1
		|| strFileName.Find( ' ') != -1)
	{
		return 3;
	}

	if( m_pVTRCtrlIF != NULL )
    {
		TRecFileInfo tRecFileInfo = m_pVTRCtrlIF->FindFileName( strFileName );
		if ( tRecFileInfo.m_szFilelName[0] != '\0')
		{
			return 4;
		}
    }

	return 0;
}
