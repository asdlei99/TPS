// addreditlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "addreditlogic.h"
#include "addreditshowoptnlogic.h"
//#include "waitingrefreshdlg.h"
#include "waitingboxdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率
/////////////////////////////////////////////////////////////////////////////
// CAddrEditLogic dialog


CAddrEditLogic::CAddrEditLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CAddrEditLogic::IDD, pParent)
{
	m_bShowMosaicHoriImg = TRUE;
	m_bIsSegment = TRUE;
	m_nSegmentLen = 690*CUR_SCREEN_WIDTH_PER;

	m_pLocalAddrList = NULL;
	m_pGlobalAddrList = NULL;
	m_pLetterIndex = NULL;

	m_pListSelect = NULL;


	m_emEditType = emEntryItem;
	m_emAddrBookType = em_AddrBook_Normal;
	m_bWaitAddEntry = FALSE;
	m_bWaitAddGroup = FALSE;
	m_bGlobalAddr = FALSE;
    m_emShowState = emShowAllAddr;

	m_pCncAddrbookIF = NULL;
	m_pUmsConfig = NULL;

	//m_bSipEnd = FALSE;
	//m_bGkEnd = FALSE;

	m_bSearchEdit = FALSE;

	m_bInGroup = FALSE;

	m_dwGlobalAddrIndex = 0;
	m_bLoadToLocal = FALSE;
}


void CAddrEditLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddrEditLogic)
	DDX_Control(pDX, IDC_STATIC_RIGHTTITLE, m_stcRightTitle);
	DDX_Control(pDX, IDC_STATIC_CnNumber, m_stcCnNumber);
	DDX_Control(pDX, IDC_STATIC_CnName, m_stcCnName);
	DDX_Control(pDX, IDC_EDIT_Search, m_edtSearch);
	DDX_Control(pDX, IDC_EDIT_EntryNumber, m_edtEntryNumber);
	DDX_Control(pDX, IDC_EDIT_EntryName, m_edtEntryName);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_Revoke, m_btnRevoke);
	DDX_Control(pDX, IDC_BUTTON_Refresh, m_btnRefresh);
	DDX_Control(pDX, IDC_BUTTON_Paste, m_btnPaste);
	DDX_Control(pDX, IDC_BUTTON_LoadToLocal, m_btnLoadToLocal);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_DeleteItem, m_btnDeleteItem);
	DDX_Control(pDX, IDC_BUTTON_Delete, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_Cut, m_btnCut);
	DDX_Control(pDX, IDC_BUTTON_Copy, m_btnCopy);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_BACK2ADDR, m_btnBackToAddr);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_btnBack);
	DDX_Control(pDX, IDC_BUTTON_AllSel, m_btnAllSel);
	DDX_Control(pDX, IDC_BUTTON_AllNoSel, m_btnAllNoSel);
	DDX_Control(pDX, IDC_BUTTON_AddrShowEx, m_btnAddrShowEx);
	DDX_Control(pDX, IDC_BUTTON_AddEntry, m_btnAddEntry);
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stcLeftTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddrEditLogic, CDlgChild)
	//{{AFX_MSG_MAP(CAddrEditLogic)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnBtnBack)
	ON_BN_CLICKED(IDC_BUTTON_BACK2ADDR, OnBtnLocalAddr)
	ON_BN_CLICKED(IDC_BUTTON_Refresh, OnBtnRefreshGlobalAddr)
	ON_BN_CLICKED(IDC_BUTTON_AllSel, OnBtnSelectAll)
	ON_BN_CLICKED(IDC_BUTTON_AllNoSel, OnBtnUnSelectAll)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_BUTTON_Copy, OnBtnCopy)
	ON_BN_CLICKED(IDC_BUTTON_Cut, OnBtnCut)
	ON_BN_CLICKED(IDC_BUTTON_Paste, OnBtnPaste)
	ON_BN_CLICKED(IDC_BUTTON_Revoke, OnBtnRevoke)
	ON_BN_CLICKED(IDC_BUTTON_Delete, OnBtnDelete)
	ON_BN_CLICKED(IDC_BUTTON_LoadToLocal, OnBtnLoadToLocal)
	ON_BN_CLICKED(IDC_BUTTON_DeleteItem, OnBtnDeleteItem)
	ON_BN_CLICKED(IDC_BUTTON_AddEntry, OnAddEntry)
	ON_MESSAGE( WM_EDIT_CHANGED, OnSearchEditChange )
	ON_MESSAGE(WM_BUTTON_CLICK, OnBtnAddrShowOptn)
	ON_MESSAGE( UI_CNS_ADDRBOOK_CHANGED, CAddrEditLogic::UpdateAddrBook )
	ON_MESSAGE( UI_CNS_ADDRBOOK_ADDENTRY, CAddrEditLogic::OnAddEntryNty )
	ON_MESSAGE( UI_CNS_ADDRBOOK_ADDGROUP, CAddrEditLogic::OnAddGroupNty )
	ON_MESSAGE( UI_CNS_ADDRBOOK_MODIFY, CAddrEditLogic::OnAddrModifyNty )
	ON_MESSAGE( UI_CNS_ADDRBOOKOPT_FAILED, CAddrEditLogic::OnAddrOptFailed )
	ON_MESSAGE( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, CAddrEditLogic::UpdateGlobalAddrBook )
	ON_MESSAGE( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, CAddrEditLogic::UpdateGlobalAddrBookEx )
	ON_MESSAGE( UI_CNC_WAITINGREFRESH_OVERTIME, CAddrEditLogic::OnWaitRefreshOverTime )
	ON_MESSAGE( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, CAddrEditLogic::OnUpdateBtnAddrOptn )
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, CAddrEditLogic::OnHideAddrOptn )
	ON_WM_DESTROY()
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM,  OnNoSelResultNotify )
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAddrEditLogic message handlers
BOOL CAddrEditLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	SetControlPos();             //设置页面控件位置
	
    if( m_pCncAddrbookIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pCncAddrbookIF);
    }

	if( m_pCncAddrbookIF != NULL )
	{
		m_pCncAddrbookIF->SetNotifyWnd(this->m_hWnd);
	}

	if( m_pUmsConfig == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
    }


	UpdateLocalAddrList();
	UpdateGlobalAddrList();

	//CWaitingRefreshDlg* pcWaitDlg = CWaitingRefreshDlg::GetWaitWindow();

	UpdateCtrlButton();

	
	return TRUE;
}

void CAddrEditLogic::OnDestroy()
{
	CDlgChild::OnDestroy();

	SAFE_RELEASE(m_pLocalAddrList);
	SAFE_RELEASE(m_pGlobalAddrList);
	SAFE_RELEASE(m_pLetterIndex);
	SAFE_RELEASE(m_pListSelect);

	//CWaitingRefreshDlg::Clean();
	

	CAddrEditShowOptnLogic::Clean();
}

BOOL CAddrEditLogic::InitControlPane()
{
	CUmcwebCommon::SetTextTransStatic( &m_stcLeftTitle, _T("地址簿") , 14, Color( 24, 25, 27 ) );

	m_btnAddrShowEx.SetImage( IDR_PNG_ADDREDITWND_ADDRSHOWEX_SEL, IDR_PNG_ADDREDITWND_ADDRSHOWEX_DOWN, NULL,
        IDR_PNG_ADDREDITWND_ADDRSHOWEX_UNSEL,IDR_PNG_ADDREDITWND_ADDRSHOWEX_DOWN, NULL);
	m_btnAddrShowEx.SetBindWnd( CAddrEditShowOptnLogic::GetDlgPtr()->GetSafeHwnd() );

	CUmcwebCommon::SetImgForTransSearchEdit(&m_edtSearch);

	m_btnAllNoSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
	m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
	m_btnRefresh.SetImage( IDR_PNG_BTN_Refresh, IDR_PNG_BTN_RefreshDOWN, IDR_PNG_BTN_RefreshDIS );
	m_btnAddEntry.SetImage( IDR_PNG_BTN_NEWMEET, IDR_PNG_BTN_NEWMEETDOWN, IDR_PNG_BTN_NEWMEETDIS );

	m_pLocalAddrList = new CListChild( "", CRect(12, 98, 690 - 57+12, 488+98), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_pLocalAddrList )
	{
		m_pLocalAddrList->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, (690 - 57)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_pLocalAddrList->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_pLocalAddrList->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pLocalAddrList->SetSliderAlwaysShow( TRUE );
		
		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect( 0, 0, 39, 486 ), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterIndex != NULL )
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
			m_pLetterIndex->SetBindList( m_pLocalAddrList );
			
			RECT rect;
			m_pLocalAddrList->GetWindowRect(&rect);
			ScreenToClient( &rect );
			
			rect.left = rect.right - 3;
			rect.right = rect.left + 7;
			m_pLocalAddrList->SetSliderRect( rect );
			
			m_pLetterIndex->SetWindowPos( NULL, rect.right + 2*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );	
		}
	}


	m_pGlobalAddrList = new CListChild( "", CRect(12, 98, 690 - 57+12, 488+98), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_pGlobalAddrList )
	{
		m_pGlobalAddrList->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, (690 - 57)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_pGlobalAddrList->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_pGlobalAddrList->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pGlobalAddrList->SetSliderAlwaysShow( TRUE );

		RECT rect;
		m_pGlobalAddrList->GetWindowRect(&rect);
		ScreenToClient( &rect );
		
		rect.left = rect.right - 3;
		rect.right = rect.left + 7;
		m_pGlobalAddrList->SetSliderRect( rect );
	}

	

	CUmcwebCommon::SetTextTransStatic( &m_stcRightTitle, _T("") , 14, Color( 24, 25, 27 ) );

	m_btnSave.SetImage( IDR_PNG_BTN_SAVE, IDR_PNG_BTN_SAVEDOWN, IDR_PNG_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_BTN_CANCEL, IDR_PNG_BTN_CANCELDOWN, IDR_PNG_BTN_CANCEL );
	m_btnEdit.SetImage( IDR_PNG_BTN_EDIT, IDR_PNG_BTN_EDITDOWN, IDR_PNG_BTN_EDIT );

	CUmcwebCommon::SetTextTransStatic( &m_stcCnName, _T("") , 13, Color( 46, 55, 76 ) );//组名称，会场名称...
	CUmcwebCommon::SetImgForTransEdit(&m_edtEntryName);
	m_edtEntryName.SetLimitLength( 31 );

	m_btnDeleteItem.SetImage( IDR_PNG_BTN_DELETEITEM, IDR_PNG_BTN_DELETEITEMDOWN, NULL );

	CUmcwebCommon::SetTextTransStatic( &m_stcCnNumber, _T("") , 13, Color( 46, 55, 76 ) );
	CUmcwebCommon::SetImgForTransEdit(&m_edtEntryNumber);
	m_edtEntryNumber.SetLimitLength( 13 );

	m_btnBack.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, NULL );
	m_btnBackToAddr.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, NULL );

	m_btnCopy.SetImage( IDR_PNG_BTN_COPY, IDR_PNG_BTN_COPYDOWN, IDR_PNG_BTN_COPYDIS );
	m_btnPaste.SetImage( IDR_PNG_BTN_PASTE, IDR_PNG_BTN_PASTEDOWN, NULL );
	m_btnCut.SetImage( IDR_PNG_BTN_CUT, IDR_PNG_BTN_CUTDOWN, IDR_PNG_BTN_CUTDIS );
	m_btnDelete.SetImage( IDR_PNG_BTN_DELETE, IDR_PNG_BTN_DELETEDOWN, IDR_PNG_BTN_DELETEDIS );
	m_btnRevoke.SetImage( IDR_PNG_ADDREDITWND_BTN_LOADTOLOCAL_CANCEL, IDR_PNG_ADDREDITWND_BTN_LOADTOLOCAL_DOWN, NULL );

	m_btnLoadToLocal.SetImage( IDR_PNG_ADDREDITWND_BTN_LOADTOLOCAL, IDR_PNG_ADDREDITWND_BTN_LOADTOLOCAL_SEL, IDR_PNG_ADDREDITWND_BTN_LOADTOLOCAL_DISABLE );
	

	m_pListSelect = new CListChild( "", CRect(690+12, 98, 1227-690-12-8+690+12, 488+98), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_pListSelect )
	{
		m_pListSelect->SetWindowPos( NULL, (690+12)*CUR_SCREEN_WIDTH_PER, 98*CUR_SCREEN_HEIGHT_PER, (1227-690-12-8)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_pListSelect->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
	}
	

	return TRUE;
}

void CAddrEditLogic::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
	
	m_stcLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_btnAddrShowEx.SetWindowPos( NULL, (690-8-48)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 48*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_edtSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, (690-45-64-2*(10+64)-17-12)*CUR_SCREEN_WIDTH_PER, 41, SWP_SHOWWINDOW );

	m_btnAllNoSel.SetWindowPos( NULL, (690-45-64)*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 37, SWP_HIDEWINDOW );
	m_btnAllSel.SetWindowPos( NULL, (690-45-64)*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 37, SWP_SHOWWINDOW );
	m_btnRefresh.SetWindowPos( NULL, (690-45-64-10-64)*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 37, SWP_SHOWWINDOW );
	m_btnAddEntry.SetWindowPos( NULL, (690-45-64-2*(10+64))*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, 64, 37, SWP_SHOWWINDOW );

	m_stcRightTitle.SetWindowPos( NULL, (690+18)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300, 24, SWP_SHOWWINDOW );

	m_btnCancel.SetWindowPos( NULL, (1226 - 8 - m_btnCancel.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 
		m_btnCancel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCancel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnEdit.SetWindowPos( NULL,  (1226 - 8 - m_btnEdit.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 
		m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnEdit.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnSave.SetWindowPos( NULL, rectClient.left - (4 + m_btnSave.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 
		m_btnSave.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_stcCnName.SetWindowPos( NULL, 708, 77, 300, 20, SWP_SHOWWINDOW );
	m_edtEntryName.SetWindowPos( NULL, 1226-8-391, 66, 391*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_btnDeleteItem.SetWindowPos( NULL, 690+85, 600-47-35, 358, 47, SWP_HIDEWINDOW );

	m_stcCnNumber.SetWindowPos( NULL, 708, 75+20+27, 300, 20, SWP_SHOWWINDOW );
	m_edtEntryNumber.SetWindowPos( NULL, 1226-8-391, 64+6+41, 391*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_btnBack.SetWindowPos( NULL, 9, 6, 66, 36, SWP_HIDEWINDOW );
	m_btnBackToAddr.SetWindowPos( NULL, 9, 6, 66, 36, SWP_HIDEWINDOW );

	m_btnDelete.SetWindowPos( NULL, 1226-8-64, 55, 64, 37, SWP_HIDEWINDOW );
	m_btnCut.SetWindowPos( NULL, 1226-8-64-10-64, 55, 64, 37, SWP_HIDEWINDOW );
	m_btnRevoke.SetWindowPos( NULL, 1226-8-64-10-64, 55, 64, 37, SWP_HIDEWINDOW );
	m_btnCopy.SetWindowPos( NULL, 1226-8-64-10-64-10-64, 55, 64, 37, SWP_HIDEWINDOW );
	m_btnPaste.SetWindowPos( NULL, 1226-8-64-10-64-10-64, 55, 64, 37, SWP_HIDEWINDOW );
	
	m_btnLoadToLocal.SetWindowPos( NULL, 1226-8-78, 55, 78, 37, SWP_HIDEWINDOW );
}

void CAddrEditLogic::RegisterFun()
{
	REG_MSG_HANDLER( _T("CAddrEditLogic::OnClickAddrItem"), CAddrEditLogic::OnClickAddrItem, this, CAddrEditLogic );
	REG_MSG_HANDLER( _T("CAddrEditLogic::OnClickAddrItemIcon"), CAddrEditLogic::OnClickAddrItemIcon, this, CAddrEditLogic );

	REG_MSG_HANDLER( "CAddrEditLogic::OnClickGlobalAddrItem", CAddrEditLogic::OnClickGlobalAddrItem, this, CAddrEditLogic );
	REG_MSG_HANDLER( "CAddrEditLogic::OnClickGlobalAddrItemIcon", CAddrEditLogic::OnClickGlobalAddrItemIcon, this, CAddrEditLogic );

	REG_MSG_HANDLER( "CAddrEditLogic::OnClickSelectItemIcon", CAddrEditLogic::OnClickSelectItemIcon, this, CAddrEditLogic );


	REG_MSG( MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY, GetSafeHwnd() );
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, GetSafeHwnd() );
	REG_MSG( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, GetSafeHwnd() );
	REG_MSG( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, GetSafeHwnd() );
	REG_MSG( UI_CNC_WAITINGREFRESH_OVERTIME, GetSafeHwnd() );
}

BOOL CAddrEditLogic::InitChildWindow()
{
	try
	{
		return TRUE;
	}
	catch (CException* e)
	{
		s8 chErr[1024];
		memset( chErr, 0, 1024 );
		e->GetErrorMessage( chErr,1024 );
		CString strErr;
		strErr += "文件操作失败，错误码";
		strErr += chErr;
		MESSAGEWND( strErr );
		return FALSE;
	}

	return TRUE;
}


void CAddrEditLogic::OnBtnLocalAddr()
{
	m_bGlobalAddr = FALSE;
	m_vctSelectList.clear();

	m_edtSearch.SetWindowText( _T("") );

 	UpdateLocalAddrList();
 	UpdateUIState();
 
 	LoadScheme( "SchmLocalAddr" );
 
 	UpdateAddrTitle();

	UpdRefreshBtn();

	//编辑组后可能有全选按钮变化的情况
	if ( m_vctShowList.empty() )
	{
		m_btnAllSel.EnableWindow(FALSE);
	}

	return;
}


bool CAddrEditLogic::OnBtnGlobalAddr()
{
	m_bGlobalAddr = TRUE;
	m_vctSelectList.clear();
	m_vctOperateList.clear();

	m_edtSearch.SetWindowText("");

	UpdateGlobalAddrList();
	UpdateUIState();

	LoadScheme("SchmGlobalAddr");

	UpdateAddrTitle();

	m_btnRefresh.EnableWindow(TRUE);

	return true;
}

void CAddrEditLogic::OnAddEntry()
//bool CAddrEditLogic::OnAddEntry( const IArgs& args )
{
	m_emAddrBookType = em_AddrBook_Add;
	m_emEditType = emEntryItem;
		
	if ( !m_vctSelectList.empty() )
	{
		m_vctSelectList.clear();
		UpdateShowList();
	}
	m_vctOperateList.clear();
	
	//UpdateUIState();

	m_edtEntryName.SetWindowText("");
	m_edtEntryNumber.SetWindowText("");

	LoadScheme("SchmEditEntry");
	m_edtEntryName.SetFocus();
	return;
}


bool CAddrEditLogic::OnAddGroup()
{
	m_emAddrBookType = em_AddrBook_Add;
	m_emEditType = emGroupItem;

	if ( !m_vctSelectList.empty() )
	{
		m_vctSelectList.clear();
		//UpdateShowList();
	}	
	m_vctOperateList.clear();

	UpdateShowList();
	//UpdateUIState();		

	m_edtEntryName.SetWindowText("");
	m_edtEntryNumber.SetWindowText("");

	LoadScheme("SchmEditGroup");
	m_edtEntryName.SetFocus();
	return true;
}


void CAddrEditLogic::OnSave()
{
    if ( m_emAddrBookType == em_AddrBook_Normal )
    {
        return;
    }

	if ( m_emEditType == emEntryItem )
	{
		if ( SaveAddrEntry() )
		{
			LoadScheme("SchmShowEntry");

            m_emAddrBookType = em_AddrBook_Normal;
		}	
	}
	else
	{
		if ( SaveAddrGroup() )
		{
			LoadScheme("SchmShowGroup");

            //编辑组后可能有全选按钮变化的情况
            if ( m_vctShowList.empty() )
            {
				m_btnAllSel.EnableWindow(FALSE);
            }
            else
            {
				m_btnAllSel.EnableWindow(FALSE);
		    }

            m_emAddrBookType = em_AddrBook_Normal;
		}	
	}
	
	return;
}


bool CAddrEditLogic::SaveAddrEntry()
{
	CString strEntryName;
	m_edtEntryName.GetWindowText(strEntryName);

	CString strE164 = "";
	m_edtEntryNumber.GetWindowText(strE164);

	s32 nRet = 0;
	//错误提示后焦点设到Edit上
	
	if ( strEntryName.IsEmpty() && strE164.IsEmpty() )
	{
		
		MESSAGEWNDBOX( "会场名称和会场号码不能全为空", this , nRet, FALSE );
		m_edtEntryName.SetFocus();
		return false;
	}

	if ( !strEntryName.IsEmpty() )
	{
		if ( CUmcwebCommon::IsAllE164Number( strEntryName ) )
		{
			MESSAGEWNDBOX( "会场名称不能全为数字及*#,号", this , nRet, FALSE );
			m_edtEntryName.SetFocus();
			return false;
		}
		if ( !CUmcwebCommon::IsValidTPStr( strEntryName ) )
		{   
			CString str; 
			str.Format("会场名称不可以包含空格及括号中的任意字符 [ %s ]",INVALID_ALIAS_FOR_SHOW);
			MESSAGEWNDBOX( str, this , nRet, FALSE );
			m_edtEntryName.SetFocus();
			return false;
		}
	}
		

	if ( !strE164.IsEmpty() && !CCallAddr::IsValidE164(strE164))
	{
		MESSAGEWNDBOX( "会场号码不合法，E164号只能包含数字及*#,号", this , nRet, FALSE );
		m_edtEntryNumber.SetFocus();
		return false;
	}

	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();

	CAddrEntry cAddrEntry;

	if ( m_emAddrBookType == em_AddrBook_Add )
	{
		u32 dwNum = 0;
		if ( !strEntryName.IsEmpty() )
		{
			dwNum = cAddrBook.GetAddrEntryByName( (LPTSTR)(LPCTSTR)strEntryName, &cAddrEntry );
			if ( dwNum > 0 )
			{
				MESSAGEWNDBOX( "会场名称已存在", this , nRet, FALSE );
				m_edtEntryName.SetFocus();
				return false;
			}
		}
		
		if ( !strE164.IsEmpty() )
		{
			dwNum = cAddrBook.GetAddrEntryByNumber( (LPTSTR)(LPCTSTR)strE164, &cAddrEntry );
			if ( dwNum > 0 )
			{
				MESSAGEWNDBOX( "会场号码已存在", this , nRet, FALSE );
				m_edtEntryNumber.SetFocus();
				return false;
			}
		}

		u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
		if ( dwSize >= MAX_ADDRENTRY /*MAX_ADDRENTRY_COUNT*/ )
		{
			CString strErr;
            strErr.Format( "会场条目已达到最大值%d个", MAX_ADDRENTRY );
			MESSAGEWNDBOX( strErr, this , nRet, FALSE );
			m_edtEntryName.SetFocus();
			return false;
		}
		
		cAddrEntry.SetEntryName( strEntryName );
		cAddrEntry.SetMtNumber( strE164 );
		
		u16 wRe = m_pCncAddrbookIF->AddEntry( cAddrEntry );
	
		m_bWaitAddEntry = TRUE;
	}
	else
	{
		if ( m_SelItem.emItemType != emEntryItem )
		{
			return false;
		}
		bool bChange = false;
		if ( strcmp( m_SelItem.tAddrInfo.achEntryName, strEntryName ) != 0 )
		{
            if ( !strEntryName.IsEmpty() )
            {
			    u32 dwNum = cAddrBook.GetAddrEntryByName( (LPTSTR)(LPCTSTR)strEntryName, &cAddrEntry );
			    if ( dwNum > 0 )
			    {
					MESSAGEWNDBOX( "会场名称已存在", this , nRet, FALSE );
					m_edtEntryName.SetFocus();
				    return false;
			    }
            }
			bChange = true;
		}

		if ( strcmp( m_SelItem.tAddrInfo.achE164, strE164 ) != 0 )
		{
			if ( !strE164.IsEmpty() )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByNumber( (LPTSTR)(LPCTSTR)strE164, &cAddrEntry );
				if ( dwNum > 0 )
				{
					MESSAGEWNDBOX( "会场号码已存在", this , nRet, FALSE );
					m_edtEntryNumber.SetFocus();
					return false;
				}
			}		
			bChange = true;
		}

		u32 dwEntryIndex = m_SelItem.tAddrInfo.dwEntryIdx;
		if ( bChange )
		{		
			cAddrBook.GetAddrEntry( &cAddrEntry, dwEntryIndex );
			cAddrEntry.SetEntryName( strEntryName );
			cAddrEntry.SetMtNumber( strE164 );

			u16 wRe = m_pCncAddrbookIF->ModifyEntry( cAddrEntry );
		}
	}

	return true;
}


bool CAddrEditLogic::SaveAddrGroup()
{	
	CString cstrNameTemp;
	m_edtEntryName.GetWindowText(cstrNameTemp);
	String strName(cstrNameTemp.GetBuffer(0));
	cstrNameTemp.ReleaseBuffer();


	CString cstrName;
	cstrName.Format( "%s", strName.c_str() );
	cstrName.TrimLeft();
	cstrName.TrimRight();

	s32 nRet = 0;
    if ( cstrName.IsEmpty() )
    {
		MESSAGEWNDBOX( "分组名称不能为空", this , nRet, FALSE );
		m_edtEntryName.SetFocus();
        return false;
	}
	
	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	CAddrMultiSetEntry cAddrGroup;
	
	if ( m_emAddrBookType == em_AddrBook_Add )
	{
		u32 dwNum = cAddrBook.GetAddrMultiSetEntry( (LPSTR)(LPCTSTR)cstrName, &cAddrGroup );
		if ( dwNum > 0 )
		{	
			MESSAGEWNDBOX( "分组名称已存在", this , nRet, FALSE );
			m_edtEntryName.SetFocus();
 			return false;
		}	

		u32 dwSize = cAddrBook.GetAddrGroupUsedSize();
		if ( dwSize >= MAX_ADDRGROUP )
		{
			CString strErr;
            strErr.Format( "会场分组已达到最大值%d个", MAX_ADDRGROUP );
			MESSAGEWNDBOX( strErr, this , nRet, FALSE );
			m_edtEntryName.SetFocus();
			return false;
		}

		cAddrGroup.SetGroupName( (LPCTSTR)cstrName );

		u16 wRe = m_pCncAddrbookIF->AddGroup( cAddrGroup );

        //再设置一次名称，去掉前后空格
		m_edtEntryName.SetWindowText((LPCTSTR)cstrName);

		m_bWaitAddGroup = TRUE;
	}
	else
	{
		if ( m_SelItem.emItemType != emGroupItem )
		{
			return false;
		}

		u32 dwGroupIndex = m_SelItem.tGroupInfo.dwGroupIdx;

		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
		
		if ( cstrName.Compare( m_SelItem.tGroupInfo.achGroupName ) != 0 )
		{
			u32 dwNum = cAddrBook.GetAddrMultiSetEntry( (LPSTR)(LPCTSTR)cstrName, &cAddrGroup );
			if ( dwNum > 0 )
			{	
				MESSAGEWNDBOX( "分组名称已存在", this , nRet, FALSE );
				m_edtEntryName.SetFocus();
				return false;
			}

			cAddrGroup.SetGroupName( (LPCTSTR)cstrName );	
			u16 wRe = m_pCncAddrbookIF->ModifyGroup( cAddrGroup );

			m_edtEntryName.SetWindowText((LPCTSTR)cstrName);
		}		
	}

	return true;
}


void CAddrEditLogic::OnEdit()
{
	if ( m_SelItem.emItemType == emEntryItem )
	{		
		m_emEditType = emEntryItem;	

		LoadScheme("SchmEditEntry");
	}
	else
	{				
		m_emEditType = emGroupItem;
		
		LoadScheme("SchmEditGroup");
	}

	//编辑时焦点设到Edit上
	m_edtEntryName.SetFocus();

	m_emAddrBookType = em_AddrBook_Modify;

	return;
}

void CAddrEditLogic::OnCancel()
{
	m_emAddrBookType = em_AddrBook_Normal;

	UpdateUIState();

	UpdRefreshBtn();

	return;
}

//点击地址簿条目
bool CAddrEditLogic::OnClickAddrItem( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() ) )
		{
 			m_SelItem = pItemInfo->m_tAddrItem;
 			
 			DoClickAddrItem();
			
		}
    } 
	return true;
}

bool CAddrEditLogic::OnClickAddrItemIcon( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&args))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {   
			TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
			
			if ( tAddrItem.emItemType == emEntryItem )
			{
				if( tAddrItem.strImg == "AddrEditSelItem" )
				{
					OnSelAddrItem(args);				
				}
				else
				{
					OnUnSelAddrItem(args);
				}
			}
			else
			{
				OnEnterAddrGroup(args);
				
				//解决bug：选中分组，再进入分组，此时右侧界面依然显示分组信息，造成可将分组删除，且未跳出分组
				m_SelItem.SetNull();
				if ( m_vctSelectList.size() == 0 && m_vctOperateList.size() == 0 )
				{
 					LoadScheme("SchmNoShow");
				}
			}
        } 
    }
    return true;
}

/**	 
* 功能:  勾选/反选 地址簿条目
* @return  bool
* @remarks  
*/
bool CAddrEditLogic::OnSelAddrItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			tAddrItem.strImg.Empty();
			
			m_vctSelectList.push_back( tAddrItem );
			
			//勾选后重新操作，清空操作列表
			m_vctOperateList.clear();
			m_SelItem.SetNull();
			//m_SelItem = tAddrItem;			
			
			UpdateShowList();
			
			UpdateUIState();
			
			//列表显示到新添加的,全选时已选列表显示到顶部
            if ( m_vctSelectList.size() != m_vctShowList.size() )
            {
				if ( m_pListSelect )
				{
					m_pListSelect->SetBottomOffset();
				}
            }
            else
            {
				if ( m_pListSelect )
				{
					m_pListSelect->SetYOffset(0);
				}
            }
		}
	}
	return true;
}

bool CAddrEditLogic::OnUnSelAddrItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			tAddrItem.strImg.Empty();
			
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
			
			m_vctOperateList.clear();
			
			m_SelItem.SetNull();
			//m_SelItem = tAddrItem;
			
			UpdateShowList();
			
			UpdateUIState();
		}
	}
	return true;
}

//已选列表
bool CAddrEditLogic::OnClickSelectItemIcon( const IArgs& args )
{
	return OnBtnDelItem(args);
}

bool CAddrEditLogic::OnEnterAddrGroup( const IArgs& args )
{
	m_bInGroup = TRUE;
    UpdateCtrlButton();

    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() ) )
        {
            TAddrItem tSelItem = pItemInfo->m_tAddrItem;
            
            if ( tSelItem.emItemType == emGroupItem )
            {
                m_vctSelectList.clear();
				m_edtSearch.SetWindowText("");

				//有条目操作时，进入到操作条目所在组时，重新选中
				if ( !m_vctOperateList.empty() )
				{
					TAddrItem tItem = m_vctOperateList.at(0);
					if( tItem.emItemType == emEntryItem )
					{
						if ( tSelItem.tGroupInfo.dwGroupIdx == tItem.tAddrInfo.dwInGroupIdx )
						{
							m_vctSelectList = m_vctOperateList;
						}
					}
				}
                
                //记录下当前列表偏移量
				int nOffset = m_pLocalAddrList->GetYOffset();
                m_vctListOffset.push_back( nOffset );              
                
				if ( m_emShowState == emShowGroup )
                {
                    m_emShowState = emShowAllAddr;//进入组后 显示组内全部 dyy
					CAddrEditShowOptnLogic::GetDlgPtr()->SetMenuCheck( em_Menu_Addr_All );
                }  

                //进入组
                m_SelGroup = tSelItem.tGroupInfo;
                GetAddrGroupMember( m_SelGroup.dwGroupIdx );
                
                //进入组之后将偏移量设为0
                nOffset = 0;
				m_pLocalAddrList->SetYOffset( nOffset );
                
                //更新标题
                UpdateAddrTitle();
                
                UpdateUIState();    
				
				UpdRefreshBtn();
			}
        }
    }
    return true;
}


//点击全局地址簿条目
bool CAddrEditLogic::OnClickGlobalAddrItem( const IArgs& args )
{
	return true;
}

bool CAddrEditLogic::OnClickGlobalAddrItemIcon( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&args))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {   
			TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
			
			if ( tAddrItem.emItemType == emEntryItem )
			{
				if( tAddrItem.strImg == "AddrEditSelItem" )
				{
					OnSelAddrItem(args);				
				}
				else
				{
					OnUnSelAddrItem(args);
				}
			}
			else
			{
				OnEnterAddrGroup(args);
			}
        } 
    }
    return true;
}

bool CAddrEditLogic::OnBtnDelItem( const IArgs& args )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&args)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;
			
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

			m_vctOperateList.clear();
			
			UpdateShowList();

			UpdateUIState();
		}
	}
	return true;
}


void CAddrEditLogic::OnBtnBack()
{
	m_vctSelectList.clear();
	m_edtSearch.SetWindowText("");

	//有条目操作时，返回到操作条目所在组时，重新选中
	if ( !m_vctOperateList.empty() )
	{
		TAddrItem tItem = m_vctOperateList.at(0);
		if( tItem.emItemType == emEntryItem )
		{
			if ( m_SelGroup.dwInGroupIdx == tItem.tAddrInfo.dwInGroupIdx )
			{
				m_vctSelectList = m_vctOperateList;
			}
		}
	}

	//如果选中条目不在当前页面，清空选中项
	if ( !m_SelItem.IsNull() )
	{
		if ( m_SelItem.emItemType == emGroupItem )
		{
			if ( m_SelItem.tGroupInfo.dwInGroupIdx == m_SelGroup.dwGroupIdx )
			{
				m_SelItem.SetNull();
			}
		}
		else
		{
			m_SelItem.SetNull();
		}
	}

	if ( m_SelGroup.dwInGroupIdx == INVALID_INDEX )
	{
		m_SelGroup.SetNull();
		UpdateShowList();

		m_bInGroup = FALSE;
        UpdateCtrlButton();
	}
	else
	{
		GetAddrGroupInfo( m_SelGroup.dwInGroupIdx, m_SelGroup );

		GetAddrGroupMember( m_SelGroup.dwGroupIdx );
	}

	//设置列表之前的偏移量
	int nSize = m_vctListOffset.size();
	if ( nSize > 0 )
	{
		s32 nOffset = m_vctListOffset.at( nSize - 1 );
		m_pLocalAddrList->SetYOffset(nOffset);
		m_vctListOffset.pop_back();
	}	
	
	UpdateAddrTitle();

	UpdateUIState();

	UpdRefreshBtn();
	
	return;
}


void CAddrEditLogic::UpdateAddrTitle()
{
	if ( m_bGlobalAddr )
	{
		m_stcLeftTitle.SetWindowText("导入地址簿");
		LoadScheme("SchmInGroup");
		m_btnBack.ShowWindow(SW_HIDE);
	}
	else
	{
		if ( m_SelGroup.IsNull() )
		{
			m_stcLeftTitle.SetWindowText("地址簿");
			LoadScheme("SchmNotInGroup");
			m_btnBack.ShowWindow(SW_HIDE);
		}
		else
		{
			CString strTitle;
			strTitle =  GetAddrGroupPath( m_SelGroup.dwGroupIdx );
			strTitle = "地址簿" + strTitle;

			m_stcLeftTitle.ShowWindow(SW_HIDE);
			m_stcLeftTitle.SetWindowText(strTitle);
			LoadScheme("SchmInGroup");
			m_btnBack.ShowWindow(SW_SHOW);
			
		}
	}
	
}


void CAddrEditLogic::UpdateUIState()
{
	if ( m_bGlobalAddr )
	{
		UpdateGlobalUIState();
	}
	else
	{	
		int nSelSize = m_vctSelectList.size();
		if ( nSelSize > 0 )
		{
			BOOL bAllSel = FALSE;


			int nSizeShow = 0;
			vector<TAddrItem>::iterator it = m_vctShowList.begin();
			for ( ; it != m_vctShowList.end(); it++ )
			{
				if ( it->emItemType == emEntryItem )
				{
					nSizeShow++;
				}
			}
			if ( nSelSize == nSizeShow )
			{
				bAllSel = TRUE;
				LoadScheme("SchmAllSel");
			}
			else
			{
				LoadScheme("SchmNoAllSel");
			}

			if ( m_vctOperateList.empty() )
			{
				LoadScheme("SchmLocalSelect");
			
				//分组只能剪切，当选中项全是组时，禁用复制
				BOOL bCanCopy = FALSE;
				for ( int i = 0; i< nSelSize; i++ )
				{
					if ( m_vctSelectList.at(i).emItemType == emEntryItem )
					{
						bCanCopy = TRUE;
						break;
					}
				}
				if ( bCanCopy )
				{
					m_btnCopy.EnableWindow(TRUE);
				}
				else
				{
					m_btnCopy.EnableWindow(FALSE);
				}
				
				//全选时对已选列表排序
				ARRAY<String> vctSubItem;
				vctSubItem.push_back( "AddrDelItem" );
				Value_TouchListAddr touchListAddr( &m_vctSelectList, &vctSubItem, "CAddrEditLogic::OnClickSelectItem", bAllSel, TRUE, TRUE );
				if (m_pListSelect)
				{
					m_pListSelect->SetData(touchListAddr);
				}

				LoadScheme("SchmMultiSel");
			}
		}
		else if ( nSelSize == 0 && m_vctOperateList.size() != 0 )
		{
			//全选时对已选列表排序
// 			ARRAY<String> vctSubItem;
// 			vctSubItem.push_back( "AddrDelNoItem" );
// 			Value_TouchListAddr touchListAddr( &m_vctOperateList, &vctSubItem, "CAddrEditLogic::OnClickSelectItem", TRUE, TRUE, TRUE );
// 			if (m_pListSelect)
// 			{
// 				m_pListSelect->SetData(touchListAddr);
// 			}
		}
		else
		{
			LoadScheme("SchmNoAllSel");

			if ( m_vctOperateList.empty() )
			{
				LoadScheme("SchmNoSelect");


				ShowSelItemInfo();

			}
		}
	}

	//列表为空或者全为组时，禁用全选
	UpdateAllSelButton();
}


void CAddrEditLogic::UpdateGlobalUIState()
{
	int nSelSize = m_vctSelectList.size();
	if ( nSelSize > 0 )
	{
		m_btnLoadToLocal.ShowWindow(SW_SHOW);

		BOOL bAllSel = FALSE;
		if ( nSelSize == m_vctShowList.size() )
		{
			bAllSel = TRUE;
			LoadScheme("SchmAllSel");
		}
		else
		{
			LoadScheme("SchmNoAllSel");
		}

		ARRAY<String> vctSubItem;
		vctSubItem.push_back( "AddrDelItem" );
		Value_TouchListAddr touchListAddr( &m_vctSelectList, &vctSubItem, "CAddrEditLogic::OnClickSelectItem", bAllSel, TRUE, FALSE );
		if (m_pListSelect)
		{
			m_pListSelect->SetData(touchListAddr);
		}
		
	
		LoadScheme("SchmMultiSel");
	}
	else
	{
		m_btnLoadToLocal.ShowWindow(SW_HIDE);

		LoadScheme("SchmNoAllSel");
		LoadScheme("SchmNoShow");
	}
}


LRESULT CAddrEditLogic::OnSearchEditChange( WPARAM wParam, LPARAM lParam )
{
	HWND hWnd = (HWND)wParam;
	if ( m_edtSearch.GetSafeHwnd() != hWnd )
	{
		return 0;
	}

	String strCaption;
	
	CString strTemp;
	m_edtSearch.GetWindowText(strTemp);
	strCaption = strTemp.GetBuffer(0);
	strTemp.ReleaseBuffer();
	
	if ( strCaption.empty() )
	{
		m_bSearchEdit = FALSE;
		UpdateShowList();
		UpdateAllSelButton();
		
		//将选中项显示出来
		if ( !m_SelItem.IsNull() )
		{
			if ( m_SelItem.emItemType == emEntryItem )
			{
				m_pLocalAddrList->SetSelItem(m_SelItem.tAddrInfo.dwEntryIdx);
			}
			else
			{
				m_pLocalAddrList->SetSelItem(m_SelItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY);
			}		
		}

		UpdRefreshBtn();

		return 0;
	}
	
	m_bSearchEdit = TRUE;
	CString strSearchName;
	strSearchName.Format( "%s", strCaption.c_str() );
	
	
	m_vctSearchList.clear();
	int nOffset = 0; 

	vector<TAddrItem> vctShowList;
	if ( m_bGlobalAddr )
	{
		vctShowList = m_vctGlobalList;

		m_pGlobalAddrList->SetYOffset(nOffset);
	}
	else
	{
		if ( m_SelGroup.IsNull() )
		{
			vctShowList = m_vctLocalList;
		}
		else
		{
			vctShowList = m_vctGroupMemberList;
		}
		
		m_pLocalAddrList->SetYOffset(nOffset);
	}
	
	for ( int i = 0; i < vctShowList.size(); i++ )
	{
		BOOL bMatchNum = FALSE;
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
				bMatchNum = TRUE;
			}		
		}
		else
		{
			strItemName = tAddrItem.tGroupInfo.achGroupName;
		}
		BOOL bFindName = FALSE;	
		BOOL bFindNum = FALSE;
		bFindName = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
		if ( bFindName )
		{		
			m_vctSearchList.push_back( tAddrItem );
		}
		else if ( bMatchNum )
        {
            //名字没有匹配到
            strItemName = tAddrItem.tAddrInfo.achE164;
            bFindNum = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
            if ( bFindNum )
            {		
                m_vctSearchList.push_back( tAddrItem );
			}
        }

		//选中项被过滤掉时，清空选中项
		if ( !(bFindName || bFindNum) )
		{
			if ( !m_SelItem.IsNull() && m_SelItem == tAddrItem )
			{
				m_SelItem.SetNull();
				UpdateUIState();
				
				m_pLocalAddrList->ResetSelItem(-1);
			}
		}
	}

 	UpdateShowList();
	UpdateAllSelButton();

	if ( m_SelItem.IsNull() )
	{
		m_pLocalAddrList->SetSelItem(-1);
	}

	UpdRefreshBtn();
	
	return 0;
}


void CAddrEditLogic::OnBtnCopy()
{
	m_emOperateType = em_AddrBook_Copy;
	m_vctOperateList = m_vctSelectList;
	//m_vctSelectList.clear();

	LoadScheme("SchmCopy");

	UpdateUIState();

	//bug:点击,光标出现在搜索框中 20131209 by xhx
	if ( m_edtSearch.GetSafeHwnd() == ::GetFocus() )
	{
		::SetFocus(NULL);
	}

	return;
}


void CAddrEditLogic::OnBtnCut()
{
	m_emOperateType = em_AddrBook_Cut;
	m_vctOperateList = m_vctSelectList;
	//m_vctSelectList.clear();

	LoadScheme("SchmCopy");

	ARRAY<String> vctSubItem;
	vctSubItem.push_back( "AddrDelNoItem" );
	Value_TouchListAddr touchListAddr( &m_vctOperateList, &vctSubItem, "CAddrEditLogic::OnClickSelectItem", TRUE, TRUE, TRUE );
	if (m_pListSelect)
	{
		m_pListSelect->SetData(touchListAddr);
	}

	//bug:点击,光标出现在搜索框中 20131209 by xhx
	if ( m_edtSearch.GetSafeHwnd() == ::GetFocus() )
	{
		::SetFocus(NULL);
	}

	return;
}


void CAddrEditLogic::OnBtnPaste()
{   
    //操作条目所在分组
    u32 dwInGroupIdx = INVALID_INDEX;
    if ( !m_vctOperateList.empty() )
    {
        TAddrItem tAddrItem = m_vctOperateList.at(0);
        if ( tAddrItem.emItemType == emEntryItem )
        {
            dwInGroupIdx = tAddrItem.tAddrInfo.dwInGroupIdx;
        }
        else
        {
            dwInGroupIdx = tAddrItem.tGroupInfo.dwInGroupIdx;
        }
    }
    else
    {
        return;
    }
   
    if ( m_SelGroup.dwGroupIdx == dwInGroupIdx )
    {
		m_vctOperateList.clear();
		m_vctSelectList.clear();
		
		UpdateShowList();
		UpdateUIState();

        return;
    }

    u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};
    
    s32 nCount = 0; //操作的条目数量
    s32 nMaxOptCount = MAXNUM_ENTRY_TABLE; //可操作的最大数量

    if ( !m_SelGroup.IsNull() )
    {
        nMaxOptCount -= m_SelGroup.nEntryNum;
    }
    
    for ( int i = 0; i < m_vctOperateList.size(); i++ )
	{
        TAddrItem tAddrItem = m_vctOperateList.at(i);
        if ( tAddrItem.emItemType == emEntryItem )
        {
            TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
                                    
            if ( nCount >= nMaxOptCount )
            {
				CString strErr = "操作失败，组内条目数量超过192最大限制，请删除部分条目后再继续";
				int nRet = 0;
				//strErr.Format( "分组中的会场最多%d个", MAXNUM_ENTRY_TABLE );
				MESSAGEWNDBOX( strErr, this , nRet , FALSE );
                return;
            }  
            
            adwEntryTable[nCount] = tAddrInfo.dwEntryIdx;	
            nCount++;
        }
        else
        {
            //对组只有剪切操作
            if ( m_emOperateType == em_AddrBook_Copy )
            {
                continue;
            }
            
            TGroupInfo tGroupInfo = tAddrItem.tGroupInfo;
            if ( !m_SelGroup.IsNull() )
            {
                if ( tGroupInfo.dwGroupIdx == m_SelGroup.dwGroupIdx )
                {
                    continue;
                }
                u16 wRe = m_pCncAddrbookIF->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
            }
            else
            {
                //从组中剪切到第一级
                if ( tGroupInfo.dwInGroupIdx != INVALID_INDEX )
                {
                    u16 wRe = m_pCncAddrbookIF->DelGroupFromGroup( tGroupInfo.dwGroupIdx, tGroupInfo.dwInGroupIdx );
                }
            }
        }
    }

    if ( nCount > 0 )
    {      
        //剪切操作，删掉原分组条目
        if ( m_emOperateType == em_AddrBook_Cut && dwInGroupIdx != INVALID_INDEX )           
        {
            TADDRMULTISETENTRY tDelEntry;
		    tDelEntry.SetEntryIndex( dwInGroupIdx );
            tDelEntry.SetListEntryIndex( adwEntryTable, nCount );
            tDelEntry.SetListEntryNum( nCount );

            u16 wRe = m_pCncAddrbookIF->DelEntryFromGroup(tDelEntry);
        }

        if ( !m_SelGroup.IsNull() )
        {
            //复制进新分组条目
            TADDRMULTISETENTRY tEntry;
            tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
            tEntry.SetListEntryIndex( adwEntryTable, nCount );
            tEntry.SetListEntryNum( nCount );
            u16 wRe = m_pCncAddrbookIF->AddEntryToGroup(tEntry);
        }
    }

    /*
	for ( int i = 0; i < m_vctOperateList.size(); i++ )
	{
		TAddrItem tAddrItem = m_vctOperateList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
			if ( tAddrInfo.dwInGroupIdx == INVALID_INDEX )
			{
				//从第一级复制/剪切到组中
				if ( !m_SelGroup.IsNull() )
				{				
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = ComInterface->AddEntryToGroup(tEntry);
				}
			}
			else
			{
				if ( m_SelGroup.dwGroupIdx == tAddrInfo.dwInGroupIdx )
				{
					continue;
				}
				//从组中复制/剪切
				if ( m_emOperateType == em_AddrBook_Cut )
				{
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( tAddrInfo.dwInGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = ComInterface->DelEntryFromGroup(tEntry);
				}

				if ( !m_SelGroup.IsNull() )
				{				
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = ComInterface->AddEntryToGroup(tEntry);
				}
			}
		}
		else
		{
			//对组只有剪切操作
			if ( m_emOperateType == em_AddrBook_Copy )
			{
				continue;
			}
			
			TGroupInfo tGroupInfo = tAddrItem.tGroupInfo;
			if ( tGroupInfo.dwInGroupIdx == INVALID_INDEX )
			{
				//从第一级剪切到组中
				if ( !m_SelGroup.IsNull() )
				{
					u16 wRe = ComInterface->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
				}
			}
			else
			{
				if ( m_SelGroup.dwGroupIdx == tGroupInfo.dwInGroupIdx )
				{
					continue;
				}
				//从组中剪切出来
				if ( !m_SelGroup.IsNull() )
				{	
					u16 wRe = ComInterface->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
				}
				else
				{
					u16 wRe = ComInterface->DelGroupFromGroup( tGroupInfo.dwGroupIdx, tGroupInfo.dwInGroupIdx );
				}
			}
		}
	}
    */

	m_vctOperateList.clear();
	m_vctSelectList.clear();

	UpdateShowList();
	UpdateUIState();

	return;
}

void CAddrEditLogic::OnBtnRevoke()
{
	//现点取消不清空选中项
	//m_vctSelectList.clear();
	//m_nSelGroupNum = 0;
	//UpdateShowList();
	//m_vctSelectList = m_vctOperateList;
	m_vctOperateList.clear();
	UpdateUIState();
	UpdateShowList();

	return;
}


void CAddrEditLogic::OnBtnDelete()
{
	CString strMsg = "是否将所选条目从地址簿中删除?";

	s32 nRet = 0;
	MESSAGEWNDBOX( strMsg, this, nRet, TRUE );

	if ( IDOK == nRet )
	{
		DelAddrEntry();
	}
	

	return;
}


bool CAddrEditLogic::DelAddrEntry()
{
	if ( m_vctSelectList.empty() )
	{
		return false;
	}

    vector<u32> vctDelGroup;

    //如果当前有选中项，检测选中项是否被删除
    BOOL bNeedCheckSel = FALSE;
    if ( !m_SelItem.IsNull() )
    {
        if ( m_SelItem.emItemType == emEntryItem )
        {
            bNeedCheckSel = TRUE;
        }
    }

	if ( m_SelGroup.IsNull() )
	{
        //删除第一级目录中的条目
        vector<u32> vctDelEntry;

		for ( int i = 0; i < m_vctSelectList.size(); i++ )
		{
			TAddrItem tAddrItem = m_vctSelectList.at(i);
			if ( tAddrItem.emItemType == emEntryItem )
			{
				TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
				if ( tAddrInfo.dwInGroupIdx == INVALID_INDEX )
				{
					vctDelEntry.push_back( tAddrInfo.dwEntryIdx );
                    //一次最多删除MAX_DELENTRY_NUM个
                    if ( vctDelEntry.size() == MAX_DELENTRY_NUM )
                    {
                        u16 wRe = m_pCncAddrbookIF->DeleteMultiEntry( vctDelEntry );
                        vctDelEntry.clear();
                    }

                    if ( bNeedCheckSel )
                    {
                        if ( m_SelItem.tAddrInfo.dwEntryIdx == tAddrInfo.dwEntryIdx )
                        {
                            m_SelItem.SetNull();
                            bNeedCheckSel = FALSE;
                        }
                    }
				}
			}
            else
            {
                //组及其下级组都删除
			    GetGroupAndLowGroup( tAddrItem.tGroupInfo.dwGroupIdx, vctDelGroup );
            }
		}

		if ( !vctDelEntry.empty() )
		{
			if ( vctDelEntry.size() == 1 )
			{
				u16 wRe = m_pCncAddrbookIF->DeleteEntry( vctDelEntry.at(0) );
			}
			else
			{
				u16 wRe = m_pCncAddrbookIF->DeleteMultiEntry( vctDelEntry );
			}
		}      
	}
    else
    {   //删除组中的条目
        int nIndex = 0;
        u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};

        for ( int i = 0; i < m_vctSelectList.size(); i++ )
        {
            TAddrItem tAddrItem = m_vctSelectList.at(i);
            if ( tAddrItem.emItemType == emEntryItem )
			{
                TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
                if ( tAddrInfo.dwInGroupIdx != INVALID_INDEX )
				{
                    if ( nIndex >= MAXNUM_ENTRY_TABLE )
                    {
                        return false;
                    }
                    adwEntryTable[nIndex] = tAddrInfo.dwEntryIdx;
                    nIndex++;
                }

                if ( bNeedCheckSel )
                {
                    if ( m_SelItem.tAddrInfo == tAddrInfo )
                    {
                        m_SelItem.SetNull();
                        bNeedCheckSel = FALSE;
                    }
                }
            }
            else
            {
                GetGroupAndLowGroup( tAddrItem.tGroupInfo.dwGroupIdx, vctDelGroup );
            }
        }

        if ( nIndex > 0 )
        {
            TADDRMULTISETENTRY tEntry;
            tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
      	
            tEntry.SetListEntryIndex(adwEntryTable, nIndex);
            tEntry.SetListEntryNum(nIndex);
		    u16 wRe = m_pCncAddrbookIF->DelEntryFromGroup(tEntry);
        }
        
    }

    if ( !vctDelGroup.empty() )
    {
        if ( vctDelGroup.size() == 1 )
        {
            u16 wRe = m_pCncAddrbookIF->DeleteGroup( vctDelGroup.at(0) );
        }
        else
        {
            u16 wRe = m_pCncAddrbookIF->DeleteMultiGroup( vctDelGroup );
        }
    }

	m_vctSelectList.clear();
	//m_SelItem.SetNull();
	UpdateUIState();

	return true;
}


void CAddrEditLogic::OnBtnDeleteItem()
{
    if ( m_SelItem.IsNull() )
    {
        return;
	}

	CString strMsg = "是否将所选条目从地址簿中删除?";
	
	s32 nRet = 0;
	MESSAGEWNDBOX( strMsg, this, nRet, TRUE );
	
	if ( IDOK == nRet )
	{
		if ( m_SelItem.emItemType == emEntryItem )
		{
			u16 wRe = m_pCncAddrbookIF->DeleteEntry( m_SelItem.tAddrInfo.dwEntryIdx );
		}
		else
		{
			u16 wRe = m_pCncAddrbookIF->DeleteGroup( m_SelItem.tGroupInfo.dwGroupIdx );
		}
		
		m_SelItem.SetNull();
		LoadScheme("SchmNoShow");
	}

    return;
}


void CAddrEditLogic::OnBtnRefreshGlobalAddr()
{
	if ( m_vctSelectList.size() > 0 )
	{
		s32 nRet = 0;
		MESSAGEWNDBOX( "刷新后清空已选条目，是否立即刷新?", this , nRet, TRUE );
		if ( IDOK == nRet )
		{
			SureRefreshGlobalAddr();
		}
	}
	else
	{
		m_btnRefresh.EnableWindow(FALSE);
		
		if ( NULL == m_pUmsConfig )
		{
			MESSAGEWND( "刷新请求发送失败" );
		}
		else
		{
			u16 nRet = m_pUmsConfig->ReqSipRegInfo(emGetRegInfoType_ALL);
			if ( nRet != NO_ERROR )
			{
				return;
			}
			//CMsgHandle::SendMessage( UI_CNC_BEGINWAITING_REFRESH, 0, (LPARAM)this );
			WAITINGWNDBOX( this, emUpdateAddr );
		}
	}
	
	return;
}


bool CAddrEditLogic::SureRefreshGlobalAddr()
{
	m_vctSelectList.clear();
	UpdateGlobalUIState();

	m_btnRefresh.EnableWindow(FALSE);
	
	if ( NULL == m_pUmsConfig ) 
	{
		MESSAGEWND( "刷新全局地址簿失败" );
		return false;
	}
	
	vector<TTPAlias> vctAllRegInfo;
	u16 re = m_pUmsConfig->ReqSipRegInfo( emGetRegInfoType_ALL );
	if ( re != NO_ERROR )
	{
		return false;
	}

	//CMsgHandle::SendMessage( UI_CNC_BEGINWAITING_REFRESH, 0, (LPARAM)this );
	WAITINGWNDBOX( this, emUpdateAddr );

	return true;
}


void CAddrEditLogic::OnBtnSelectAll()
{
	m_vctOperateList.clear();
	
    if ( m_bGlobalAddr )
    {
        if ( !m_bSearchEdit )
        {
            m_vctSelectList = m_vctGlobalList;
        }
        else
        {
            m_vctSelectList = m_vctSearchList;
        }
    }
    else
    {
//        if ( !m_bSearchEdit && m_SelGroup.IsNull() && (m_emShowState == emShowAllAddr) )
//        {
		if ( m_SelGroup.IsNull() && (m_emShowState == emShowOffline || m_emShowState == emShowOnline ) )
		{
			//解决bug：筛选框显示在线或显示不在线，点击全选后地址簿出现重复 20131225 by xhx
			BOOL bOnLine = FALSE;
			if ( emShowOnline == m_emShowState )
			{
				bOnLine = TRUE;
			}

			vector<TAddrItem>::iterator iter = m_vctSelectList.begin();
			for ( ; iter != m_vctSelectList.end(); )
			{
				if ( bOnLine == iter->tAddrInfo.bOnLine )
				{
					iter = m_vctSelectList.erase(iter);
					continue;
				}
				iter++;
			}
		}
		else
		{
			m_vctSelectList.clear();
		}
			
		vector<TAddrItem>::iterator it = m_vctLocalList.begin();
        for ( int i = 0; i < m_vctShowList.size(); i++ )
        {
            TAddrItem tItem = m_vctShowList.at(i);
            if ( tItem.emItemType == emEntryItem )
            {
                tItem.strImg.Empty();
                m_vctSelectList.push_back( tItem );
            }
        }
    } 
	
    //全选时已选列表位置置顶
    m_pListSelect->SetYOffset(0);
	
	//UpdateShowList();
	UpdateAllSelShowList();
	
	UpdateUIState();

	//bug:点击全选,光标出现在搜索框中 20131209 by xhx
	if ( m_edtSearch.GetSafeHwnd() == ::GetFocus() )
	{
		::SetFocus(NULL);
	}

	return;
}

void CAddrEditLogic::OnBtnUnSelectAll()
{
	m_vctOperateList.clear();

	m_vctSelectList.clear();
	
//     if ( !m_bSearchEdit && ( m_bGlobalAddr || m_emShowState == emShowAllAddr ) )
//     {
//         m_vctSelectList.clear();
//     }
//     else
//     {
//         for ( int i = 0; i < m_vctShowList.size(); i++ )
//         {
//             TAddrItem tShowItem = m_vctShowList.at(i);
//             if ( tShowItem.emItemType != emEntryItem )
//             {
//                 continue;
//             }
//             vector<TAddrItem>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tShowItem );
// 			
//             if ( itfind != m_vctSelectList.end() )
//             {
//                 m_vctSelectList.erase( itfind );
//             }
//         }     
//     }
	
    m_pListSelect->SetYOffset(0);
	
	UpdateShowList();
	
	UpdateUIState();

	::SetFocus(NULL);
	return;
}

void CAddrEditLogic::LoadToLocal()
{
	BOOL bAdd = TRUE;
	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	TAddrItem tAddrItem = m_vctSelectList.at(m_dwGlobalAddrIndex);
	CAddrEntry cAddrEntry;
	
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

// 		if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 )
// 		{
// 			u32 dwNum = cAddrBook.GetAddrEntryByName( tAddrItem.tAddrInfo.achEntryName, &cAddrEntry/*, 1000*/ );
// 			if ( dwNum > 0 )
// 			{
// 				u32 nMtNumberLen = cAddrEntry.GetMtNumberLen();
// 				char achMtNumber[MAX_E164NUM_LEN + 1] = {0};
// 				cAddrEntry.GetMtNumber( achMtNumber, nMtNumberLen + 1 );
// 				
// 				if ( strcmp( achMtNumber, tAddrItem.tAddrInfo.achE164 ) == 0 )
// 				{
// 					bAdd = FALSE;
// 				}
// 			}				
// 		}
// 		
// 		if ( strcmp( tAddrItem.tAddrInfo.achE164, "" ) != 0 )
// 		{
// 			u32 dwNum = cAddrBook.GetAddrEntryByNumber( tAddrItem.tAddrInfo.achE164, &cAddrEntry );
// 			if ( dwNum > 0 )
// 			{
// 				u32 nEntryNameLen = cAddrEntry.GetEntryNameLen();
// 				char achEntryName[MAX_NAME_LEN + 1] = {0};
// 				cAddrEntry.GetEntryName( achEntryName, nEntryNameLen + 1 );
// 				
// 				
// 				if ( strcmp( achEntryName, tAddrItem.tAddrInfo.achEntryName ) == 0 )
// 				{
// 					bAdd = FALSE;
// 				}
// 			}
// 		}		

		cAddrEntry.SetEntryName( tAddrItem.tAddrInfo.achEntryName );
		cAddrEntry.SetMtNumber( tAddrItem.tAddrInfo.achE164 );
		
		TADDRENTRY tentry;
		ZeroMemory(&tentry, sizeof(TADDRENTRY));
		tentry.SetEntryIndex(cAddrEntry.GetEntryIndex());
		TADDRENTRYINFO info;
		ZeroMemory(&info, sizeof(TADDRENTRYINFO));
		cAddrEntry.GetEntryInfo(&info);
		tentry.SetEntryInfo(&info);
		
		BOOL32 bExist = cAddrBook.IsAddrEntryExist(info) == INVALID_INDEX ? FALSE : TRUE; 
		if (bExist)
		{
			bAdd = FALSE;
		}
 	}

	m_dwGlobalAddrIndex++;
	
	if ( bAdd )
	{		
		u16 wRe = m_pCncAddrbookIF->AddEntry( cAddrEntry );
		if( NO_ERROR != wRe )
		{
			if ( m_dwGlobalAddrIndex < m_vctSelectList.size() )
			{
				OspPrintf( TRUE, FALSE, "导入地址条目 Name: %s, E164: %s 失败\n", tAddrItem.tAddrInfo.achEntryName, tAddrItem.tAddrInfo.achE164 );
				LoadToLocal();
				return;
			}
		}

		m_bLoadToLocal = TRUE;
	}
	else
	{
		if ( m_dwGlobalAddrIndex < m_vctSelectList.size() )
		{
			LoadToLocal();
			return;
		}
	}

	if ( m_dwGlobalAddrIndex == m_vctSelectList.size() )
	{
		m_dwGlobalAddrIndex = 0;
		m_pCncAddrbookIF->SetAddrLoadingState(FALSE);

		m_vctSelectList.clear();
		UpdateShowList();
		UpdateGlobalUIState();

		//bug:导入地址簿后，会议模板地址簿未同步更新
		UpdateAddrBook( 0, 0 );

		if ( m_bLoadToLocal )
		{
			m_bLoadToLocal = FALSE;
			KillTimer(11);
			CMsgHandle::SendMessage( UI_CNC_ENDWAITING_REFRESH );
		}

		//bug:光标出现在搜索框中 by xhx
		if ( m_edtSearch.GetSafeHwnd() == ::GetFocus() )
		{
			::SetFocus(NULL);
		}
	}
}

void CAddrEditLogic::OnBtnLoadToLocal()
{
	m_dwGlobalAddrIndex = 0;
	m_pCncAddrbookIF->SetAddrLoadingState(TRUE);
	m_bLoadToLocal = FALSE;

	LoadToLocal();
	
	if ( m_bLoadToLocal )
	{
		KillTimer( 11 );
		SetTimer( 11, 1000, NULL );
		
		//CMsgHandle::SendMessage( UI_CNC_BEGINWAITING_REFRESH, emLoadAddr, (LPARAM)this );
		WAITINGWNDBOX( this, emLoadAddr );
	}

	return;
}

void CAddrEditLogic::OnTimer(UINT nIDEvent)
{
	//防止刷新地址簿列表卡死界面
// 	if ( nIDEvent == 10 )
// 	{		
// 		m_vctSelectList.clear();
// 		UpdateShowList();
// 		UpdateGlobalUIState();
// 
// 		CMsgHandle::SendMessage( UI_CNC_ENDWAITING_REFRESH );
// 
// 		KillTimer(10);
// 	}

	if ( 11 == nIDEvent )
	{
		CMsgHandle::SendMessage( UI_CNC_LOADADDRNUM_NTY, (WPARAM)(m_vctSelectList.size() - m_dwGlobalAddrIndex) );
	}

    CTransparentBaseDlg::OnTimer( nIDEvent );
}


/*=============================================================================
函 数 名:UpdateAddrBook
功    能:响应更新本地地址簿消息
参    数:无
注    意:同时更新当前显示列表
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
LRESULT CAddrEditLogic::UpdateAddrBook(WPARAM wParam, LPARAM lParam)
{
	if ( m_pCncAddrbookIF->GetAddrLoadingState() )
	{
		LoadToLocal();
		return NO_ERROR;
	}

	if( this->GetSafeHwnd() == NULL )
	{
		return NO_ERROR;
	}

	if ( m_pCncAddrbookIF->GetAddrLoadingState() )
	{
		return NO_ERROR;
	}
		
	UpdateLocalAddrList();

	if ( !m_SelGroup.IsNull() )	
	{
		GetAddrGroupMember( m_SelGroup.dwGroupIdx );
	}

	if ( m_bSearchEdit )
	{
		OnSearchEditChange( (WPARAM)m_edtSearch.GetSafeHwnd(), 0 );
	}


	//条目若没有当前选中条目，清空选中条目
	if ( !m_SelItem.IsNull() )
	{
		CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();

		if ( m_SelItem.emItemType == emGroupItem )
		{
			CAddrMultiSetEntry cMultiSetEntry;
			u32 nIndex = cAddrBook.GetAddrMultiSetEntry( &cMultiSetEntry, m_SelItem.tGroupInfo.dwGroupIdx );

			u32 nGroupNameLen = cMultiSetEntry.GetGroupNameLen();
			if ( nGroupNameLen == 0 )
			{
				m_SelItem.SetNull();
			}

			m_pLocalAddrList->SetSelItem(m_SelItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY);
		}
		else if ( m_SelItem.emItemType == emEntryItem )
		{
			CAddrEntry cAddrEntry;
			u32 nIndex = cAddrBook.GetAddrEntry( &cAddrEntry, m_SelItem.tAddrInfo.dwEntryIdx );

			u32 nEntryNameLen = cAddrEntry.GetEntryNameLen();
			u32 nEntryNumberLen = cAddrEntry.GetMtNumberLen();
			if ( nEntryNameLen == 0 && nEntryNumberLen == 0 )
			{
				m_SelItem.SetNull();
			}

			m_pLocalAddrList->SetSelItem(m_SelItem.tAddrInfo.dwEntryIdx);
		}
		
	}	

	UpdateUIState();

	UpdRefreshBtn();
	
	CMsgHandle::SendMessage( UI_CNS_ADDRBOOK_CHANGED, (WPARAM)&m_vctLocalList );
	
	return NO_ERROR;
}


LRESULT CAddrEditLogic::UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam )
{
	if( this->GetSafeHwnd() == NULL )
	{
		return NO_ERROR;
	}
		
	CMsgHandle::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
	m_btnRefresh.EnableWindow(TRUE);

	UpdateGlobalAddrList();

	if ( m_bSearchEdit )
	{
		OnSearchEditChange( (WPARAM)m_edtSearch.GetSafeHwnd(), 0 );
	}

	UpdateAddrBook( 0, 0 );

	return NO_ERROR;
}

LRESULT CAddrEditLogic::UpdateGlobalAddrBookEx( WPARAM wParam, LPARAM lParam )
{
	if( this->GetSafeHwnd() == NULL )
	{
		return NO_ERROR;
	}

	//优化全局地址只刷新一次
//	BOOL bRefresh = FALSE;

	CUmsConfigCtrlIF* pUmsConfigCtrlIf = NULL;
	BUSINESSIFPTR->GetCtrlInterface(&pUmsConfigCtrlIf);
	if ( pUmsConfigCtrlIf == NULL )
	{
		return NO_ERROR;
	}

// 	BOOL bIsSipRegistered = pUmsConfigCtrlIf->GetSipRegRsp();
// 	BOOL bIsGKRegistered = pUmsConfigCtrlIf->GetGKRegRsp();
// 	
// // 	TTPGKCfg tGKRegCfg;
// // 	pUmsConfigCtrlIf->GetGkCfg(tGKRegCfg);
// // 
// // 	TTPSipRegistrarCfg tSipCfg;
// // 	pUmsConfigCtrlIf->GetSipCfg(tSipCfg);
// 
// 	BOOL bSip = (BOOL)wParam;
// 	if ( bSip == TRUE )
// 	{
// 		if ( bIsSipRegistered/*tSipCfg.bRegistered*/ )
// 		{
// 			if ( bIsGKRegistered/*tGKRegCfg.bRegistered*/ == TRUE )
// 			{
// 				if ( m_bGkEnd == TRUE )
// 				{
// 					bRefresh = TRUE;
// 					m_bSipEnd = FALSE;
// 					m_bGkEnd = FALSE;
// 				}
// 				else
// 				{
// 					bRefresh = FALSE;
// 					m_bSipEnd = TRUE;
// 				}
// 			}
// 			else
// 			{
// 				bRefresh = TRUE;
// 				m_bSipEnd = FALSE;
// 				m_bGkEnd = FALSE;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if ( bIsGKRegistered/*tGKRegCfg.bRegistered*/ )
// 		{
// 			if ( bIsSipRegistered/*tSipCfg.bRegistered*/ == TRUE )
// 			{
// 				if ( m_bSipEnd == TRUE )
// 				{
// 					bRefresh = TRUE;
// 					m_bSipEnd = FALSE;
// 					m_bGkEnd = FALSE;
// 				}
// 				else
// 				{
// 					bRefresh = FALSE;
// 					m_bGkEnd = TRUE;
// 				}
// 			}
// 			else
// 			{
// 				bRefresh = TRUE;
// 				m_bSipEnd = FALSE;
// 				m_bGkEnd = FALSE;
// 			}
// 		}
// 	}
	
// 	if ( bRefresh == FALSE )
// 	{
// 		return NO_ERROR;
// 	}
	
	UpdateGlobalAddrList();
	
	String strCaption;
	CString strTemp;
	m_edtSearch.GetWindowText(strTemp);
	strCaption = strTemp.GetBuffer(0);
	strTemp.ReleaseBuffer();
	
	if ( !strCaption.empty() )
	{
		OnSearchEditChange( (WPARAM)m_edtSearch.GetSafeHwnd(), 0 );
	}

	UpdateAddrBook( 0, 0 );

	CMsgHandle::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
	m_btnRefresh.EnableWindow(TRUE);
	
	return NO_ERROR;
}

void CAddrEditLogic::UpdateLocalAddrList()
{
	m_vctLocalList.clear();

	UpdateAddrEntryList();
	UpdateLevelOneGroup();

	UpdateShowList();
}

void CAddrEditLogic::UpdateGlobalAddrList()
{
	if ( NULL == m_pUmsConfig ) 
	{
		MESSAGEWND( "刷新全局地址簿失败" );
		return;
	}
	
	vector<TAliasEx> vctAllRegInfo;
	vctAllRegInfo = m_pUmsConfig->GetAllTAliasEx();
	
    CString strLetter;
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;
	
	m_vctGlobalList.clear();
	//m_vctSelectList.clear();
	
	s32 nRegInfoCount = vctAllRegInfo.size();
	if ( nRegInfoCount > 0 )
	{
		m_btnAllSel.EnableWindow(TRUE);
		m_btnLoadToLocal.EnableWindow(TRUE);
	}
	else
	{
		m_btnAllSel.EnableWindow(FALSE);
		m_btnLoadToLocal.EnableWindow(FALSE);
	}
	
	for( int i = 0; i < nRegInfoCount; i++ )
	{
		TAliasEx tAlias = vctAllRegInfo.at(i);
		TAddrInfo tAddrInfo;
		tAddrInfo.dwEntryIdx = i;

		BOOL bFindName = FALSE;
		vector<TTPAlias>::iterator it = tAlias.m_vecTTPAlias.begin();
		for ( ; it != tAlias.m_vecTTPAlias.end(); it++ )
		{
			if ( it->m_byType == tp_Alias_e164 )
			{
				strncpy( tAddrInfo.achE164, it->m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
			else
			{
				bFindName = TRUE;
				strncpy( tAddrInfo.achEntryName, it->m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
		}

		if ( bFindName )
		{
			CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
		}
		else
		{
			strLetter.Format( " %s", tAddrInfo.achE164 );
		}

		tAddrInfo.m_emEndpointType = tAlias.m_emEndpointType;
		
		
		tAddrItem.tAddrInfo = tAddrInfo;
		tAddrItem.strImg = "AddrEditSelItem";
		
		tAddrItem.strNameLetter = strLetter;
		
		m_vctGlobalList.push_back( tAddrItem );
	}



	UpdateShowList();
}


LRESULT CAddrEditLogic::OnAddEntryNty( WPARAM wParam, LPARAM lParam )
{
// 	if ( m_pCncAddrbookIF->GetAddrLoadingState() )
// 	{
// 		LoadToLocal();
// 	}

	if ( !m_bWaitAddEntry )
	{
		return NO_ERROR;
	}

	u32 dwEntryIndex = (u32)wParam;

    CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
    CAddrEntry cEntry;
    cAddrBook.GetAddrEntry( &cEntry, dwEntryIndex );
    
    TAddrInfo tAddrInfo;
    SetAddrItemInfo( tAddrInfo, cEntry );

	if ( !m_SelGroup.IsNull() )
	{
		TADDRMULTISETENTRY tEntry;
		
		u32 adwEntryTable[1] = {0};
		tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
		adwEntryTable[0] = dwEntryIndex;
		tEntry.SetListEntryIndex(adwEntryTable, 1);
		tEntry.SetListEntryNum(1);
		u16 wRe = m_pCncAddrbookIF->AddEntryToGroup(tEntry);		
	}

	m_SelItem.emItemType = emEntryItem;
	m_SelItem.tAddrInfo = tAddrInfo;

	DoClickAddrItem();

	return NO_ERROR;
}

LRESULT CAddrEditLogic::OnAddGroupNty( WPARAM wParam, LPARAM lParam )
{
	if ( !m_bWaitAddGroup )
	{
		return NO_ERROR;
	}
	
	TGroupInfo tGroupInfo;
	u32 dwGroupIndex = (u32)wParam;
	tGroupInfo.dwGroupIdx = dwGroupIndex;
	strncpy( tGroupInfo.achGroupName, (s8*)lParam, TP_MAX_ALIAS_LEN_CNC+1 ); 

	if ( !m_SelGroup.IsNull() )
	{
		u16 wRe = m_pCncAddrbookIF->AddGroupToGroup( dwGroupIndex, m_SelGroup.dwGroupIdx );
	}

	m_SelItem.emItemType = emGroupItem;
	m_SelItem.tGroupInfo = tGroupInfo;

	return NO_ERROR;
}

LRESULT CAddrEditLogic::OnAddrModifyNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bEntry = (BOOL)wParam;
	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();

	if ( bEntry )
	{
		if ( m_SelItem.emItemType != emEntryItem || m_SelItem.tAddrInfo.dwEntryIdx != lParam )
		{
			return NO_ERROR;
		}
		
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, m_SelItem.tAddrInfo.dwEntryIdx );
		
		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );
		m_SelItem.tAddrInfo = tAddrInfo;	
		//m_bWaitAddEntry = TRUE;//设置修改后列表的位置
	}
	else
	{
		if ( m_SelItem.emItemType != emGroupItem || m_SelItem.tGroupInfo.dwGroupIdx != lParam )
		{
			return NO_ERROR;
		}
		
		TGroupInfo tGroupInfo;
		GetAddrGroupInfo( m_SelItem.tGroupInfo.dwGroupIdx, tGroupInfo );

		m_SelItem.tGroupInfo = tGroupInfo;
		//m_SelGroup = tGroupInfo;
		//m_bWaitAddGroup = TRUE;

		UpdateAddrTitle();	
	}
	return NO_ERROR;
}


LRESULT CAddrEditLogic::OnAddrOptFailed(WPARAM wParam, LPARAM lParam)
{
    u16 wCmd = wParam;
    switch( wCmd )
    {
    case ADDRBOOK_ADD_ENTRY_REQ:
        MESSAGEWND( "新建会场失败");
        break;
    case ADDRBOOK_MODIFYENTRY_REQ:
        MESSAGEWND( "修改会场失败");
        break;
    case ADDRBOOK_DEL_ENTRY_REQ:
        MESSAGEWND( "删除会场失败");
        break;
    case ADDRBOOK_ADD_MULSETENTRY_REQ:
        MESSAGEWND( "新建分组失败");
        break;
    case ADDRBOOK_MODIFYMULSETENTRY_REQ:
        MESSAGEWND( "修改分组失败");
        break;
    case ADDRBOOK_DEL_MULSETENTRY_REQ:
        MESSAGEWND( "删除分组失败");
        break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_REQ:
        MESSAGEWND( "添加会场到分组失败");
        break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_REQ:
        MESSAGEWND( "从分组中删除会场失败");
        break;
    default:
        break;
    }
	LoadScheme("SchmNoShow");
    return NO_ERROR;
}


/*=============================================================================
函 数 名:UnSelAddrList
功    能:响应列表没有选中项消息
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
bool CAddrEditLogic::UnSelAddrList( const IArgs& args )
{
	m_SelItem.SetNull();
	if ( m_vctSelectList.empty() && m_vctOperateList.empty() )
	{
		LoadScheme("SchmNoShow");
	}
	
	return true;
}


/*=============================================================================
函 数 名:UpdateShowList
功    能:更新当前显示列表
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CAddrEditLogic::UpdateShowList()
{
	if ( !m_bSearchEdit )
	{
		if ( m_bGlobalAddr )
		{
			m_vctShowList = m_vctGlobalList;
		}
		else
		{
			if ( m_SelGroup.IsNull() )
			{
				m_vctShowList = m_vctLocalList;
			}
			else
			{
				m_vctShowList = m_vctGroupMemberList;
			}
		}		
	}
	else
	{
		m_vctShowList = m_vctSearchList;
	}


    //获得条件筛选后的条目
    GetOptnShowList( m_vctShowList );

	/*vector<TAddrItem> vctSelectList;
	if ( m_vctSelectList.size() != 0 )
	{
		vctSelectList = m_vctSelectList;
	}
	else if ( m_vctOperateList.size() != 0 )
	{
		vctSelectList = m_vctOperateList;
	}*/
	
	for ( int i = 0; i < m_vctShowList.size(); i++ )
	{
        TAddrItem tShowItem = m_vctShowList.at(i);
        if ( tShowItem.emItemType != emEntryItem )
        {
            m_vctShowList.at(i).strImg = "AddrEditEnterGroupItem";
            continue;
        }
		
		//shishi
		/*vector<TAddrItem>::iterator itfind = vctSelectList.begin();
		for ( ; itfind != vctSelectList.end(); itfind++ )
		{
			if ( itfind->IsSameName( tShowItem ) )
			{
				//解决勾选条目bug：名称和E164号需全部匹配 20131123 by xhx
				if ( 0 == strcmp( itfind->tAddrInfo.achE164, tShowItem.tAddrInfo.achE164 ) )
				{
					break;
				}
			}
		}*/
		vector<TAddrItem>::iterator  itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tShowItem );
		
		if ( itfind == m_vctSelectList.end() )
		{
			m_vctShowList.at(i).strImg = "AddrEditSelItem";
		}
		else
		{
			m_vctShowList.at(i).strImg = "AddrEditUnSelItem";
		}
	}
	
	if ( m_bGlobalAddr )
	{
		Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrEditLogic::OnClickGlobalAddrItem", TRUE, TRUE, FALSE );
		if (m_pGlobalAddrList)
		{
			m_pGlobalAddrList->SetData(touchListAddr);
		}
	}
	else
	{		
		Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrEditLogic::OnClickAddrItem", TRUE, TRUE, TRUE );
		if (m_pLocalAddrList)
		{
			m_pLocalAddrList->SetData(touchListAddr);	
		}
	}
}

void CAddrEditLogic::UpdateAllSelShowList()
{
	if ( !m_bSearchEdit )
	{
		if ( m_bGlobalAddr )
		{
			m_vctShowList = m_vctGlobalList;
		}
		else
		{
			if ( m_SelGroup.IsNull() )
			{
				m_vctShowList = m_vctLocalList;
			}
			else
			{
				m_vctShowList = m_vctGroupMemberList;
			}
		}		
	}
	else
	{
		m_vctShowList = m_vctSearchList;
	}	
	
    //获得条件筛选后的条目
    GetOptnShowList( m_vctShowList );
	
	for ( int i = 0; i < m_vctShowList.size(); i++ )
	{
        TAddrItem tShowItem = m_vctShowList.at(i);
        if ( tShowItem.emItemType != emEntryItem )
        {
            m_vctShowList.at(i).strImg = "AddrEditEnterGroupItem";
            continue;
        }

		m_vctShowList.at(i).strImg = "AddrEditUnSelItem";
	}
	
	if ( m_bGlobalAddr )
	{
		Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrEditLogic::OnClickGlobalAddrItem", TRUE, TRUE, FALSE );
		if (m_pGlobalAddrList)
		{
			m_pGlobalAddrList->SetData(touchListAddr);
		}
	}
	else
	{		
		Value_TouchListAddr touchListAddr( &m_vctShowList, NULL, "CAddrEditLogic::OnClickAddrItem", TRUE, TRUE, TRUE );
		if (m_pLocalAddrList)
		{
			m_pLocalAddrList->SetData(touchListAddr);	
		}
	}
}


void CAddrEditLogic::SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry )
{
	s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //条目名称
	s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164号

	cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
	cAddrEntry.GetMtNumber( aszE164, cAddrEntry.GetMtNumberLen() + 1 );
	
	tAddrInfo.dwEntryIdx = cAddrEntry.GetEntryIndex();
	strncpy( tAddrInfo.achEntryName, aszEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
	strncpy( tAddrInfo.achE164, aszE164, MAX_E164NUM_LEN+1 );
}


/*=============================================================================
函 数 名:GetAddrGroupMember
功    能:获取并刷新分组成员列表
参    数:dwGroupIndex 组索引
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/04/01  1.0     肖楚然     创建
=============================================================================*/
void CAddrEditLogic::GetAddrGroupMember( u32 dwGroupIndex )
{
	m_vctGroupMemberList.clear();
	
	if ( m_pCncAddrbookIF == NULL )
	{
		return;
	}

	if ( m_pUmsConfig == NULL )
	{
		return;
	}
	
	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	bool bValid = cAddrBook.IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}

	vector<TAliasEx> vctCnsRegInfo;
	vctCnsRegInfo = m_pUmsConfig->GetAllTAliasEx();

	
	CString strLetter;
	CAddrMultiSetEntry cGroup;
	cAddrBook.GetAddrMultiSetEntry( &cGroup, dwGroupIndex );	
	
	int nNum = cGroup.GetEntryCount();
	u32* pEntryTable = cGroup.GetEntryTable();	
	
	for ( int i = 0; i < nNum; i++ )
	{
		bool bValid = cAddrBook.IsAddrEntryValid( *pEntryTable );
		if ( !bValid )
		{
			pEntryTable++;
			continue;
		}
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, *pEntryTable );
		
		TAddrItem tAddrItem;
		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );

		tAddrInfo.dwInGroupIdx = dwGroupIndex;

		//获取条目名称字母索引。当只有会场号码时对号码排序，索引为空格+号码的形式，保证号码在名字前面 -2012.11.7 xcr		
        if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
        {
            strLetter.Format( " %s", tAddrInfo.achE164 );
        }
        else
        {
			CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
        }

		//如果条目在注册信息中，表示在线
		BOOL bFind = FALSE;
		TAliasEx* pTAliasEx = NULL;
		vector<TAliasEx>::iterator it = vctCnsRegInfo.begin();
		for ( ; it != vctCnsRegInfo.end(); it++ )
		{
			if ( it->m_vecTTPAlias.size() > 0 )
			{
				bFind = TRUE;
			}
		
			//只有当E164和会场名都匹配时，显示在线----------------20131123 by sc
			CString strE164;
			CString strEntryName;
			vector<TTPAlias>::iterator itTTPAlias = it->m_vecTTPAlias.begin();
			for ( ; itTTPAlias != it->m_vecTTPAlias.end(); itTTPAlias++ )
			{
				if ( itTTPAlias->m_byType == tp_Alias_e164 )
				{
					strE164 = itTTPAlias->m_abyAlias;
				}
				else
				{
					strEntryName = itTTPAlias->m_abyAlias;
				}
			}
		
			//名称不存在
			if ( 0 == strcmp( tAddrInfo.achEntryName, "" ) )
			{
				if ( strcmp( tAddrInfo.achE164, strE164 ) != 0 )
				{
					bFind = FALSE;
				}
			} 
			
			//号码不存在
			if ( 0 == strcmp( tAddrInfo.achE164, "" ) )
			{
				if ( strcmp( tAddrInfo.achEntryName, strEntryName ) != 0 )
				{
					bFind = FALSE;
				}
			}
			
			//名称号码都存在
			if ( 0 != strcmp( tAddrInfo.achEntryName, "" ) && 0 != strcmp( tAddrInfo.achE164, "" ) )
			{
				if ( strcmp( tAddrInfo.achE164, strE164 ) != 0 || strcmp( tAddrInfo.achEntryName, strEntryName ) != 0 )
				{
					bFind = FALSE;
				}
			}
		
			if ( bFind )
			{
				pTAliasEx = it;
				break;
			}
		}
			
		if ( pTAliasEx )
		{
			tAddrInfo.bOnLine = TRUE;
			//tAddrInfo.emAliasType = itfind->m_byType;
			tAddrInfo.m_emEndpointType = pTAliasEx->m_emEndpointType;
		}
		else
		{
			tAddrInfo.bOnLine = FALSE;
		}

		tAddrItem.tAddrInfo = tAddrInfo;
		tAddrItem.strNameLetter = strLetter;
		
		m_vctGroupMemberList.push_back(tAddrItem);
		
		pEntryTable++;
	}
	
	//下级分组
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = cAddrBook.FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;
	
	CAddrMultiSetEntry cAddrGroup;
	for ( i = 0; i < dwNum; i++ )
	{
		u32 dwDownGroupIndex = *(pdwGroup + i);
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwDownGroupIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		TGroupInfo tGroupInfo;
		tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
		strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
		tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
		u32* pEntryTable = cAddrGroup.GetEntryTable();
		for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
		{
			tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
		}
		tGroupInfo.dwInGroupIdx = dwGroupIndex;
		u32 adwDownGroup[MAX_ADDRGROUP] = {0};
		tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );
		tAddrItem.tGroupInfo = tGroupInfo;
		
		CListChild::GetFirstLetter( tGroupInfo.achGroupName, strLetter );
		//组的索引前加2个空格，保证组在条目前面 -2013.3.19 xcr
        CString strGroupLetter;
        strGroupLetter.Format( "  %s", (LPCTSTR)strLetter );
		tAddrItem.strNameLetter = strGroupLetter;
		
		m_vctGroupMemberList.push_back(tAddrItem);
	}
	if ( pdwGroup != NULL )
	{
		delete []pdwGroup;
		pdwGroup = NULL;
	}
	
	UpdateShowList();
}

/*=============================================================================
函 数 名:DelGroupAndLowGroup
功    能:删除组及其下级分组
参    数:dwGroupIndex 组索引
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CAddrEditLogic::DelGroupAndLowGroup( u32 dwGroupIndex )
{
	bool bValid = m_pCncAddrbookIF->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}

	//下级分组
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = m_pCncAddrbookIF->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
	
	for ( int i = 0; i < dwNum; i++ )
	{
		u32 dwLowGroupIndex = *(pdwGroup + i);
			
		DelGroupAndLowGroup( dwLowGroupIndex );		
	}

	delete []pdwGroup;
	pdwGroup = NULL;

	u16 wRe = m_pCncAddrbookIF->DeleteGroup( dwGroupIndex );
}


void CAddrEditLogic::GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup )
{
    bool bValid = m_pCncAddrbookIF->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
    if ( !bValid )
    {
        return;
    }
    vctGroup.push_back( dwGroupIndex );
    
    //下级分组
    u32 *pdwGroup = new u32[MAX_ADDRGROUP];
    u32 dwNum = m_pCncAddrbookIF->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
    
    for ( int i = 0; i < dwNum; i++ )
    {
        u32 dwLowGroupIndex = *(pdwGroup + i);
     
        GetGroupAndLowGroup( dwLowGroupIndex, vctGroup );		
    }
    
    delete []pdwGroup;
    pdwGroup = NULL;
}



LRESULT CAddrEditLogic::OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam )
{
	if( this->GetSafeHwnd() == NULL )
	{
		return NO_ERROR;
	}

	if ( NULL == m_pUmsConfig ) 
	{
		MESSAGEWND( "刷新全局地址簿失败" );
		return NO_ERROR;
	}
	
	//2013.1.16 yjj 
	BOOL bVisSelf = this->IsWindowVisible();
	if ( !bVisSelf )
	{
		return NO_ERROR;
	}


	m_btnRefresh.EnableWindow(TRUE);
	m_vctGlobalList.clear();
	UpdateLocalAddrList();
	UpdateShowList();

	//刷新全局地址簿失败后可能有全选按钮变化的情况
	if ( m_vctShowList.empty() )
	{
		m_btnAllSel.EnableWindow(FALSE);
		if ( !m_bGlobalAddr )
		{
			m_btnRefresh.EnableWindow(FALSE);
		}
	}

	return NO_ERROR;
}



void CAddrEditLogic::Clear()
{
	m_SelItem.SetNull();
	m_SelGroup.SetNull();
	m_vctLocalList.clear();
	m_vctGlobalList.clear();
	m_vctGroupMemberList.clear();
	m_vctSelectList.clear();
	m_vctShowList.clear();
	m_vctSearchList.clear();
	m_vctOperateList.clear();
	m_vctListOffset.clear();
	m_bGlobalAddr = FALSE;
	m_emAddrBookType = em_AddrBook_Normal;
	m_bSearchEdit = FALSE;
	m_bInGroup = FALSE;
    UpdateCtrlButton();
}


LRESULT CAddrEditLogic::OnBtnAddrShowOptn(WPARAM wParam, LPARAM lParam)
{ 
    bool bOn = false;
	bOn = m_btnAddrShowEx.GetSwitchState();
    if ( bOn )
    {   
//		CAddrEditShowOptnLogic::GetDlgPtr()->SetOwner(this);

		CRect rect;
		m_btnAddrShowEx.GetWindowRect(&rect);
//		ScreenToClient( &rect );

		EM_MENU_ADDRBOOKTYPE emMenuCheck = em_Menu_Addr_All;
		switch ( m_emShowState )
		{
		case emShowAllAddr:
			{
				emMenuCheck = em_Menu_Addr_All;
				break;
			}
		case emShowGroup:
			{
				emMenuCheck = em_Menu_Addr_Group;
				break;
			}
		case emShowOnline:
			{
				emMenuCheck = em_Menu_Addr_Online;
				break;
			}
		case emShowOffline:
			{
				emMenuCheck = em_Menu_Addr_NotOnline;
				break;
			}
		default:
			break;
		}
		
		CAddrEditShowOptnLogic::GetDlgPtr()->SetMenuCheck(emMenuCheck);
		CAddrEditShowOptnLogic::GetDlgPtr()->ShowWindow(SW_SHOW);
		CAddrEditShowOptnLogic::GetDlgPtr()->SetWindowPos(NULL, rect.right - 232, rect.bottom, 232, 318, SWP_SHOWWINDOW );
    }
    else
    {
		CAddrEditShowOptnLogic::GetDlgPtr()->ShowWindow(SW_HIDE);
    }
    return true; 
}

bool CAddrEditLogic::OnAddrOptnShowAll()
{
    if ( m_emShowState == emShowAllAddr )
    {
        return true;
    }
    m_emShowState = emShowAllAddr;
	UpdateUIState();
    UpdateShowList();
	UpdateAllSelButton();

	UpdRefreshBtn();

    return true;
}

bool CAddrEditLogic::OnAddrOptnShowGroup()
{   
    if ( m_emShowState == emShowGroup )
    {
        return true;
    }
    
    m_emShowState = emShowGroup;
	UpdateUIState();
    UpdateShowList();
	UpdateAllSelButton();

	UpdRefreshBtn();

    return true;
}

bool CAddrEditLogic::OnAddrOptnShowOnline()
{
    if ( m_emShowState == emShowOnline )
    {
        return true;
    }
    m_emShowState = emShowOnline;
	UpdateUIState();
    UpdateShowList();
	UpdateAllSelButton();

	UpdRefreshBtn();

    return true;
}

bool CAddrEditLogic::OnAddrOptnShowOffline()
{
    if ( m_emShowState == emShowOffline )
    {
        return true;
    }
    m_emShowState = emShowOffline;
	UpdateUIState();
    UpdateShowList();
	UpdateAllSelButton();
	
	UpdRefreshBtn();
	
    return true;
}

void CAddrEditLogic::GetOptnShowList( vector<TAddrItem>& vctCurrentList )
{
    if ( m_emShowState == emShowAllAddr || m_bGlobalAddr )
    {
        return;
    }
    
    vector<TAddrItem> vctList = vctCurrentList;
    vctCurrentList.clear();
    if ( m_emShowState == emShowOnline )
    {
        for ( int i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emGroupItem )
            {
                continue;
            }
            if ( tAddrItem.tAddrInfo.bOnLine )
            {
                vctCurrentList.push_back( tAddrItem );
            }
        }
    }
    else if ( m_emShowState == emShowOffline )
    {
        for ( int i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emGroupItem )
            {
                continue;
            }
            if ( !tAddrItem.tAddrInfo.bOnLine )
            {
                vctCurrentList.push_back( tAddrItem );
            }
        }
    }
	else if ( m_emShowState == emShowGroup )
    {
        for ( int i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emEntryItem )
            {
                continue;
            }

            vctCurrentList.push_back( tAddrItem );
        }
    }
}

void CAddrEditLogic::LoadScheme( String strScheme )
{
	if ( strScheme == "SchmNotInGroup" )
	{
		m_stcLeftTitle.ShowWindow(SW_HIDE);
		m_stcLeftTitle.SetWindowPos( NULL, 17, 14, 300, 24, SWP_SHOWWINDOW );
	}
	else if ( strScheme == "SchmInGroup" )
	{
		m_stcLeftTitle.SetWindowPos( NULL, 98, 14, 300, 20, SWP_SHOWWINDOW );
	}
	else if ( strScheme == "SchmLocalAddr" )
	{
		m_btnBackToAddr.ShowWindow( SW_HIDE );
		m_edtSearch.SetWindowPos( NULL, 0, 0, (690-45-64-2*(10+64)-17-12), 41, SWP_NOMOVE );
		m_btnAddEntry.ShowWindow( SW_SHOW );
		m_pLocalAddrList->ShowWindow( SW_SHOW );
		m_pGlobalAddrList->ShowWindow( SW_HIDE );
		m_pLetterIndex->SetBindList( m_pLocalAddrList );
		m_btnLoadToLocal.ShowWindow( SW_HIDE );
		m_btnAddrShowEx.ShowWindow( SW_SHOW );
	}
	else if ( strScheme == "SchmGlobalAddr" )
	{
		m_btnBackToAddr.ShowWindow( SW_SHOW );
		m_edtSearch.SetWindowPos( NULL, 0, 0, (690-45-64-(10+64)-17-12), 41, SWP_NOMOVE );
		m_btnAddEntry.ShowWindow( SW_HIDE );
		m_pLocalAddrList->ShowWindow( SW_HIDE );
		m_pGlobalAddrList->ShowWindow( SW_SHOW );
		m_pLetterIndex->SetBindList( m_pGlobalAddrList );
		m_btnPaste.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
		m_btnAddrShowEx.ShowWindow( SW_HIDE );
	}
	else if ( strScheme == "SchmShowEntry" )
	{
		m_edtSearch.EnableWindow( TRUE );
		m_btnAddEntry.EnableWindow( TRUE );
		m_btnRefresh.EnableWindow( TRUE );
		m_btnAllSel.EnableWindow( TRUE );
		m_pLocalAddrList->EnableWindow( TRUE );
		m_stcRightTitle.SetWindowText( "会场信息" );
		m_stcCnName.SetWindowText( "会场名称" );
		m_edtEntryName.ShowWindow( SW_SHOW );
		m_edtEntryName.EnableWindow( FALSE );
		m_stcCnNumber.SetWindowText( "会场号码" );
		m_edtEntryNumber.ShowWindow( SW_SHOW );
		m_edtEntryNumber.EnableWindow( FALSE );
		m_btnDeleteItem.ShowWindow( SW_SHOW );
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnDelete.ShowWindow( SW_HIDE );
		m_pListSelect->ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_btnEdit.ShowWindow( SW_SHOW );
	}
	else if ( strScheme == "SchmEditEntry" )
	{
		m_edtSearch.EnableWindow( FALSE );
		m_btnAddEntry.EnableWindow( FALSE );
		m_btnRefresh.EnableWindow( FALSE );
		m_btnAllSel.ShowWindow( SW_SHOW );
		m_btnAllSel.EnableWindow( FALSE );
		m_btnAllNoSel.ShowWindow( SW_HIDE);
		//m_pLocalAddrList->EnableWindow( FALSE );
		m_stcRightTitle.SetWindowText( "编辑会场信息" );
		m_stcCnName.SetWindowText( "会场名称" );
		m_edtEntryName.ShowWindow( SW_SHOW );
		m_edtEntryName.EnableWindow( TRUE );
		m_stcCnNumber.SetWindowText( "会场号码" );
		m_edtEntryNumber.ShowWindow( SW_SHOW );
		m_edtEntryNumber.EnableWindow( TRUE );
		m_btnDeleteItem.ShowWindow( SW_HIDE );
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnPaste.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
		m_btnDelete.ShowWindow( SW_HIDE);
		m_pListSelect->ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_SHOW );
		m_btnCancel.ShowWindow( SW_SHOW );
		m_btnEdit.ShowWindow( SW_HIDE );

		if ( m_pLocalAddrList )
		{
			if ( m_pLocalAddrList->GetSafeHwnd() )
			{
				m_pLocalAddrList->EnableWindow( FALSE );
			}
		}
	}
	else if ( strScheme == "SchmShowGroup" )
	{
		m_edtSearch.EnableWindow( TRUE );
		m_btnAddEntry.EnableWindow( TRUE );
		m_btnRefresh.EnableWindow( TRUE );
		m_btnAllSel.EnableWindow( TRUE );
		UpdateAllSelButton();
		m_pLocalAddrList->EnableWindow( TRUE );
		m_stcRightTitle.SetWindowText( "组信息" );
		m_stcCnName.SetWindowText( "分组名称" );
		m_edtEntryName.ShowWindow( SW_SHOW );
		m_edtEntryName.EnableWindow( FALSE );
		m_stcCnNumber.SetWindowText( "" );
		m_edtEntryNumber.ShowWindow( SW_HIDE );
		m_edtEntryNumber.EnableWindow( FALSE );
		m_btnDeleteItem.ShowWindow( SW_SHOW );
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnDelete.ShowWindow( SW_HIDE );
		m_pListSelect->ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_btnEdit.ShowWindow( SW_SHOW );
	}
	else if ( strScheme == "SchmEditGroup" )
	{
		m_edtSearch.EnableWindow( FALSE );
		m_btnAddEntry.EnableWindow( FALSE );
		m_btnRefresh.EnableWindow( FALSE );
		m_btnAllSel.ShowWindow( SW_SHOW );
		m_btnAllSel.EnableWindow( FALSE );
		m_btnAllNoSel.ShowWindow( SW_HIDE );
		//m_pLocalAddrList->EnableWindow( FALSE );
		m_stcRightTitle.SetWindowText( "编辑组信息" );
		m_stcCnName.SetWindowText( "分组名称" );
		m_edtEntryName.ShowWindow( SW_SHOW );
		m_edtEntryName.EnableWindow( TRUE );
		m_stcCnNumber.SetWindowText( "" );
		m_edtEntryNumber.ShowWindow( SW_HIDE );
		m_edtEntryNumber.EnableWindow( FALSE );
		m_btnDeleteItem.ShowWindow( SW_HIDE );
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnPaste.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
		m_btnDelete.ShowWindow( SW_HIDE);
		m_pListSelect->ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_SHOW );
		m_btnCancel.ShowWindow( SW_SHOW );
		m_btnEdit.ShowWindow( SW_HIDE );

		if ( m_pLocalAddrList )
		{
			if ( m_pLocalAddrList->GetSafeHwnd() )
			{
				m_pLocalAddrList->EnableWindow( FALSE );
			}
		}
	}
	else if ( strScheme == "SchmNoShow" )
	{
		m_edtSearch.EnableWindow( TRUE );
		m_btnAddEntry.EnableWindow( TRUE );
		//m_btnRefresh.EnableWindow( TRUE );
		m_pLocalAddrList->EnableWindow( TRUE );
		m_stcRightTitle.SetWindowText( "" );
		m_stcCnName.SetWindowText( "" );
		m_edtEntryName.ShowWindow( SW_HIDE );
		m_stcCnNumber.SetWindowText( "" );
		m_edtEntryNumber.ShowWindow( SW_HIDE );
		m_btnDeleteItem.ShowWindow( SW_HIDE );
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnDelete.ShowWindow( SW_HIDE );
		m_pListSelect->ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_btnEdit.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
	}
	else if ( strScheme == "SchmAllSel" )
	{
		m_btnAllSel.ShowWindow( SW_HIDE );
		m_btnAllNoSel.ShowWindow( SW_SHOW );
	}
	else if ( strScheme == "SchmNoAllSel" )
	{
		m_btnAllSel.ShowWindow( SW_SHOW );
		m_btnAllNoSel.ShowWindow( SW_HIDE );
	}
	else if ( strScheme == "SchmMultiSel" )
	{
		m_stcRightTitle.SetWindowText( "已选列表" );
		m_stcCnName.SetWindowText( "" );
		m_edtEntryName.ShowWindow( SW_HIDE );
		m_stcCnNumber.SetWindowText( "" );
		m_edtEntryNumber.ShowWindow( SW_HIDE );
		m_btnDeleteItem.ShowWindow( SW_HIDE );
		m_pListSelect->ShowWindow( SW_SHOW );
		m_btnSave.ShowWindow( SW_HIDE );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_btnEdit.ShowWindow( SW_HIDE );
	}
	else if ( strScheme == "SchmLocalSelect" )
	{
		m_btnCopy.ShowWindow( SW_SHOW );
		m_btnCut.ShowWindow( SW_SHOW );
		m_btnPaste.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
		m_btnDelete.ShowWindow( SW_SHOW );
		m_btnDelete.EnableWindow( TRUE );
	}
	else if ( strScheme == "SchmNoSelect" )
	{
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnPaste.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
	}
	else if ( strScheme == "SchmCopy" )
	{
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnPaste.ShowWindow( SW_SHOW );
		m_btnRevoke.ShowWindow( SW_SHOW );
		m_btnDelete.EnableWindow( FALSE );
	}
	else if ( strScheme == "SchmInit" )
	{
		m_stcLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, 0, 0, SWP_NOSIZE );
		m_btnAddrShowEx.ShowWindow( SW_SHOW );
		m_edtSearch.SetWindowPos( NULL, 0, 0, (690-45-64-2*(10+64)-17-12), 41, SWP_NOMOVE );
		m_edtSearch.SetWindowText("");
		m_edtSearch.ShowWindow( SW_SHOW );
		m_edtSearch.EnableWindow(TRUE);
		m_btnAllNoSel.ShowWindow( SW_HIDE );
		m_btnAllSel.ShowWindow( SW_SHOW );
		m_btnRefresh.ShowWindow( SW_SHOW );
		m_btnRefresh.EnableWindow(TRUE);
		m_btnAddEntry.ShowWindow( SW_SHOW );
		m_btnAddEntry.EnableWindow(TRUE);
		m_stcRightTitle.SetWindowText( "" );
		m_btnCancel.ShowWindow( SW_HIDE );
		m_btnEdit.ShowWindow( SW_HIDE );
		m_btnSave.ShowWindow( SW_HIDE );
		m_stcCnName.SetWindowText( "" );
		m_edtEntryName.ShowWindow( SW_HIDE );
		m_btnDeleteItem.ShowWindow( SW_HIDE );
		m_stcCnNumber.SetWindowText( "" );
		m_edtEntryNumber.ShowWindow( SW_HIDE );
		m_btnBack.ShowWindow( SW_HIDE );
		m_btnBackToAddr.ShowWindow( SW_HIDE );
		
		m_btnDelete.ShowWindow( SW_HIDE );
		m_btnCut.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
		m_btnCopy.ShowWindow( SW_HIDE );
		m_btnPaste.ShowWindow( SW_HIDE );
		
		m_btnLoadToLocal.ShowWindow( SW_HIDE );

		if(m_pLocalAddrList)
		{
			m_pLocalAddrList->ShowWindow( SW_SHOW );
			if (m_pLetterIndex)
			{
				m_pLetterIndex->SetBindList( m_pLocalAddrList );
			}
		}
		
		if (m_pGlobalAddrList)
		{
			m_pGlobalAddrList->ShowWindow( SW_HIDE );
		}
		
		if (m_pListSelect)
		{
			m_pListSelect->ShowWindow( SW_HIDE );
		}
	}

	if ( m_edtSearch.GetSafeHwnd() != ::GetFocus() )
	{
		::SetFocus(NULL);
	}
}

/*=============================================================================
函 数 名:GetAddrGroupPath
功    能:获取分组路径
参    数:dwGroupIndex  组索引
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
CString CAddrEditLogic::GetAddrGroupPath( u32 dwGroupIndex )
{
	CString strPath = _T("");
	CString strName;
	
	if ( m_pCncAddrbookIF == NULL )
	{
		return strPath;
	}
	
	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	CAddrMultiSetEntry cAddrGroup;
	
	u32 dwIndex = dwGroupIndex;
	while( dwIndex != INVALID_INDEX )
	{		
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		strName.Format( "\\%s", aszGroupName );
		strPath = strName + strPath;
		
		dwIndex = cAddrBook.FindUpGroupOfGroupByIndex( dwIndex );
	}
	return strPath;
}

/*=============================================================================
函 数 名:GetAddrGroupInfo
功    能:获取分组信息
参    数:[in]dwGroupIndex 组索引  
		 [out]tGroupInfo  组信息
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CAddrEditLogic::GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo )
{
	if ( m_pCncAddrbookIF == NULL )
	{
		return ;
	}

	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	
	CAddrMultiSetEntry cAddrGroup;
	cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
	
	cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
	
	tGroupInfo.SetNull();
	tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
	strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
	tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
	u32* pEntryTable = cAddrGroup.GetEntryTable();
	for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
	{
		tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
	}
	tGroupInfo.dwInGroupIdx = cAddrBook.FindUpGroupOfGroupByIndex( dwGroupIndex );
	u32 adwDownGroup[MAX_ADDRGROUP] = {0};
	tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );
}

/*=============================================================================
函 数 名:UpdateAddrEntryList
功    能:更新地址簿条目
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CAddrEditLogic::UpdateAddrEntryList()
{
	if ( m_pCncAddrbookIF == NULL )
	{
		return;
	}

	if ( m_pUmsConfig == NULL )
	{
		return;
	}

	m_vctLocalList.clear();
	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;
	CString strLetter;

	vector<TAliasEx> vctCnsRegInfo;
	vctCnsRegInfo = m_pUmsConfig->GetAllTAliasEx();

	//获取基本条目个数
	u32 dwUsedSize = cAddrBook.GetAddrEntryUsedSize();
	
	u32 dwIndex = 0;
	s32 nIndex = 0;
	CAddrEntry cAddrEntry;
	dwIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );
	while ( nIndex < dwUsedSize )
	{
		if ( dwIndex != INVALID_INDEX )
		{	
			TAddrInfo tAddrInfo;
			SetAddrItemInfo( tAddrInfo, cAddrEntry );
			
			//获取条目名称字母索引。当只有会场号码时对号码排序，索引为空格+号码的形式，保证号码在名字前面 -2012.11.7 xcr
            if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
			{
                strLetter.Format( " %s", tAddrInfo.achE164 );
            }
            else
            {
				CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
            }

			//如果条目在注册信息中，表示在线
			BOOL bFind = FALSE;
			TAliasEx* pTAliasEx = NULL;
			vector<TAliasEx>::iterator it = vctCnsRegInfo.begin();
			for ( ; it != vctCnsRegInfo.end(); it++ )
			{
				if ( it->m_vecTTPAlias.size() > 0 )
				{
					bFind = TRUE;
				}

				//只有当E164和会场名都匹配时，显示在线----------------20131123 by sc
				CString strE164;
				CString strEntryName;
				vector<TTPAlias>::iterator itTTPAlias = it->m_vecTTPAlias.begin();
				for ( ; itTTPAlias != it->m_vecTTPAlias.end(); itTTPAlias++ )
				{
					if ( itTTPAlias->m_byType == tp_Alias_e164 )
					{
						strE164 = itTTPAlias->m_abyAlias;
					}
					else
					{
						strEntryName = itTTPAlias->m_abyAlias;
					}
				}

				//名称不存在
				if ( 0 == strcmp( tAddrInfo.achEntryName, "" ) )
				{
					if ( strcmp( tAddrInfo.achE164, strE164 ) != 0 )
					{
						bFind = FALSE;
					}
				} 

				//号码不存在
				if ( 0 == strcmp( tAddrInfo.achE164, "" ) )
				{
					if ( strcmp( tAddrInfo.achEntryName, strEntryName ) != 0 )
					{
						bFind = FALSE;
					}
				}

				//名称号码都存在
				if ( 0 != strcmp( tAddrInfo.achEntryName, "" ) && 0 != strcmp( tAddrInfo.achE164, "" ) )
				{
					if ( strcmp( tAddrInfo.achE164, strE164 ) != 0 || strcmp( tAddrInfo.achEntryName, strEntryName ) != 0 )
					{
						bFind = FALSE;
					}
				}

				if ( bFind )
				{
					pTAliasEx = it;
				    break;
				}
			}
			
			if ( pTAliasEx )
			{
				tAddrInfo.bOnLine = TRUE;
                //tAddrInfo.emAliasType = itfind->m_byType;
				tAddrInfo.m_emEndpointType = pTAliasEx->m_emEndpointType;
			}
			else
			{
				tAddrInfo.bOnLine = FALSE;
			}

			tAddrItem.tAddrInfo = tAddrInfo;
			tAddrItem.strNameLetter = strLetter;

			m_vctLocalList.push_back(tAddrItem);
			
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrEntry( dwIndex, &cAddrEntry );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwIndex = cAddrEntry.GetEntryIndex();
			}			
		}
		else
		{
			break;
		}
	}
}

/*=============================================================================
函 数 名:UpdateLevelOneGroup
功    能:更新第一级组
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CAddrEditLogic::UpdateLevelOneGroup()
{
	if ( m_pCncAddrbookIF == NULL )
	{
		return;
	}

	CAddrBook cAddrBook = m_pCncAddrbookIF->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T("");     //组名称
	
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;
	CString strLetter;
	
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = cAddrBook.FindLevelOneGroup( pdwGroup );
	
	CAddrMultiSetEntry cAddrGroup;
	for ( int i = 0; i < dwNum; i++ )
	{
		u32 dwGroupIndex = *(pdwGroup + i);
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		TGroupInfo tGroupInfo;
		tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
		strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
		tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
		u32* pEntryTable = cAddrGroup.GetEntryTable();
		for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
		{
			tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
		}
		u32 adwDownGroup[MAX_ADDRGROUP] = {0};
		tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );

		tAddrItem.tGroupInfo = tGroupInfo;

		CListChild::GetFirstLetter( tGroupInfo.achGroupName, strLetter );
		//组的索引前加2个空格，保证组在条目前面 -2013.3.19 xcr
        CString strGroupLetter;
        strGroupLetter.Format( "  %s", (LPCTSTR)strLetter );
		tAddrItem.strNameLetter = strGroupLetter;

		m_vctLocalList.push_back(tAddrItem);
	}
	if ( pdwGroup != NULL )
	{
		delete []pdwGroup;
		pdwGroup = NULL;
	}
	
}

LRESULT CAddrEditLogic::OnUpdateBtnAddrOptn( WPARAM wParam, LPARAM lParam )
{
	EM_MENU_ADDRBOOKTYPE emMenuCheck = static_cast<EM_MENU_ADDRBOOKTYPE>(wParam);
	

	switch(emMenuCheck)
	{
	case em_Menu_Addr_All:
		{
			OnAddrOptnShowAll();
			break;
		}
	case em_Menu_Addr_Group:
		{
			OnAddrOptnShowGroup();
			break;
		}
	case em_Menu_Addr_Online:
		{
			OnAddrOptnShowOnline();
			break;
		}
	case em_Menu_Addr_NotOnline:
		{
			OnAddrOptnShowOffline();
			break;
		}
	case em_Menu_Addr_NewGroup:
		{
			OnAddGroup();
			CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT );
			break;
		}
	case em_Menu_Addr_Import:
		{
			OnBtnGlobalAddr();
			CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT );
			break;
		}
	default:
		break;
	}


	if ( m_vctSelectList.empty() && m_vctOperateList.empty() )
	{
		//筛选后将选中项显示出来
		BOOL bFind = FALSE;
		if ( !m_bGlobalAddr && !m_SelItem.IsNull() &&
			!(m_emAddrBookType == em_AddrBook_Add && m_emEditType == emGroupItem) )
		{
			vector<TAddrItem>::iterator it = m_vctShowList.begin();
			for ( ; it != m_vctShowList.end(); it++ )
			{
				if ( m_SelItem.IsSameName(*it) )
				{
					bFind = TRUE;
				}
			}
			
			if ( !bFind )
			{
				LoadScheme("SchmNoShow");
			}
			else
			{
				//将选中项显示出来
				if ( m_SelItem.emItemType == emEntryItem )
				{
					m_pLocalAddrList->SetSelItem(m_SelItem.tAddrInfo.dwEntryIdx);
				}
				else
				{
					m_pLocalAddrList->SetSelItem(m_SelItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY);
				}
				DoClickAddrItem();
			}
		}
	}
	

	//CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT );

	return S_OK;
}

LRESULT CAddrEditLogic::OnHideAddrOptn( WPARAM wParam, LPARAM lParam )
{
	m_btnAddrShowEx.SetSwitchState(FALSE);
	
	return S_OK;
}

/*=============================================================================
函 数 名:InitDlg
功    能:页面销毁抢断后初始化
参    数:无
注    意:无
返 回 值:void
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人    修改内容
2013/04/08  1.0     石城      创建
=============================================================================*/
void CAddrEditLogic::InitDlg()
{
	ShowWindow(SW_HIDE);

	m_vctLocalList.clear();
	m_vctGlobalList.clear();
	m_vctGroupMemberList.clear();
	m_vctSelectList.clear();
	m_vctShowList.clear();
	m_vctSearchList.clear();
	m_vctOperateList.clear();

	m_emEditType = emEntryItem;
	m_emAddrBookType = em_AddrBook_Normal;
	m_emOperateType = em_AddrBook_Copy;
	m_bWaitAddEntry = FALSE;
	m_bWaitAddGroup = FALSE;
	m_bGlobalAddr = FALSE;
//	m_emShowState = emShowAllAddr;

// 	m_bSipEnd = FALSE;
// 	m_bGkEnd = FALSE;

	if( m_pLocalAddrList != NULL )
	{
		m_pLocalAddrList->SetYOffset( 0 );
		m_pLocalAddrList->SetSelItem( -1 );
	}
	if ( m_pGlobalAddrList != NULL )
	{
		m_pGlobalAddrList->SetYOffset( 0 );
		m_pGlobalAddrList->SetSelItem( -1 );
	}
	m_edtSearch.SetWindowText( "" );
	
	m_SelItem.SetNull();
	m_SelGroup.SetNull();
	
	UpdateShowList();
	UpdateAddrTitle();
	
	UpdateUIState();

	LoadScheme( "SchmInit" );

	m_bInGroup = FALSE;
	UpdateCtrlButton();
	KillTimer(11);

	//bug：导入地址簿时被抢登，弹出框未隐藏   by xhx
	ISWAITINGBOXVISIBLE(TRUE);

	m_bLoadToLocal = FALSE;

	CAddrEditShowOptnLogic::GetDlgPtr()->InitDlg();
}

LRESULT CAddrEditLogic::OnNoSelResultNotify(WPARAM wParam, LPARAM lParam)
{
	if ( m_emAddrBookType == em_AddrBook_Add )
	{
		return 0;
	}

	HWND hWnd = (HWND)wParam;
	if ( hWnd == m_pLocalAddrList->GetSafeHwnd() )
	{
		if ( m_vctSelectList.size() == 0 && m_vctOperateList.size() == 0 )
		{
			LoadScheme("SchmNoShow");
		}
		
		m_SelItem.SetNull();
	}
	
	return 0;
}

void CAddrEditLogic::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDlgChild::OnShowWindow( bShow, nStatus );

	if ( m_pLocalAddrList->IsWindowVisible() )
	{
		m_pLocalAddrList->ShowWindow(SW_HIDE);
		m_pLocalAddrList->ShowWindow(SW_SHOW);
	}
}

void CAddrEditLogic::DoClickAddrItem()
{
// 	if ( m_SelItem.emItemType == emGroupItem )
// 	{
// 	/*
// 	m_vctSelectList.clear();
// 	UIManagePtr->SetCaption( m_strEdtSearch, "", m_pWndTree );
// 	
// 	  //记录下当前列表偏移量
// 	  Value_TransparentListOffset valueOffset;
// 	  UIManagePtr->GetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
// 	  m_vctListOffset.push_back( valueOffset.nOffset );
// 	  
// 		//进入组
// 		m_SelGroup = m_SelItem.tGroupInfo;
// 		GetAddrGroupMember( m_SelGroup.dwGroupIdx );
// 		
// 		  //进入组之后将偏移量设为0
// 		  valueOffset.nOffset = 0;
// 		  UIManagePtr->SetPropertyValue( valueOffset, m_strListLocalAddr, m_pWndTree );
// 		  
// 			//更新标题
// 			UpdateAddrTitle();
// 		*/
// 		UpdateUIState();                
// 	}
// 	else
// 	{				
//		if ( m_vctSelectList.empty() && m_vctOperateList.empty() )
//		{			
// 			TAddrInfo tAddrInfo = m_SelItem.tAddrInfo;
// 			m_edtEntryName.SetWindowText(tAddrInfo.achEntryName);
// 			m_edtEntryNumber.SetWindowText(tAddrInfo.achE164);
// 			LoadScheme("SchmShowEntry");
// 		}
// 	}

	if ( m_vctSelectList.empty() && m_vctOperateList.empty() )
	{
		ShowSelItemInfo();
 	}
}

void CAddrEditLogic::ShowSelItemInfo()
{
	if ( m_SelItem.IsNull() )
	{
		LoadScheme("SchmNoShow");
	}
	else
	{
		if ( m_SelItem.emItemType == emEntryItem )
		{
			TAddrInfo tAddrInfo = m_SelItem.tAddrInfo;
			m_edtEntryName.SetWindowText(tAddrInfo.achEntryName);
			m_edtEntryNumber.SetWindowText(tAddrInfo.achE164);
			
			LoadScheme("SchmShowEntry");
		}
		else
		{
			m_edtEntryName.SetWindowText(m_SelItem.tGroupInfo.achGroupName);
			
			LoadScheme("SchmShowGroup");
		}
	}
}

void CAddrEditLogic::UpdateAllSelButton()
{
    //全选只能选择会场条目，先筛选出会场条目
    vector<TAddrItem> vctShowEntryList;
    
    //简单比较，即通过数量判断是否全选
    BOOL bEasyCompare = FALSE;
    if ( m_bGlobalAddr )
    {
        if ( !m_bSearchEdit )
        {
            vctShowEntryList = m_vctGlobalList;
            bEasyCompare = TRUE;
        }       
    }
    else
    {
        if ( m_emShowState == emShowAllAddr )
        {
            if ( !m_bSearchEdit && m_SelGroup.IsNull() )
            {
				vctShowEntryList.clear();
				vector<TAddrItem>::iterator it = m_vctLocalList.begin();
				for ( ; it != m_vctLocalList.end(); it++ )
				{
					if ( it->emItemType == emEntryItem )
					{
						vctShowEntryList.push_back( *it );
					}
				}

                bEasyCompare = TRUE;
            }    
        }
        else if ( m_emShowState == emShowGroup )
        {
            vctShowEntryList.clear();
            bEasyCompare = TRUE;
        }
    }     
    
    if ( bEasyCompare )
    {
        if ( vctShowEntryList.empty() )
        {
			m_btnAllSel.EnableWindow(FALSE);
			m_btnAllNoSel.EnableWindow(FALSE);
			m_btnAllSel.ShowWindow(SW_SHOW);
			m_btnAllNoSel.ShowWindow(SW_HIDE);
        }
        else
        {
			m_btnAllSel.EnableWindow(TRUE);
			m_btnAllNoSel.EnableWindow(TRUE);
			m_btnRefresh.EnableWindow(TRUE);
            
            //多会场呼叫列表中会场的数目与本地列表会场数目一致,全选按钮变为取消全选
            if ( m_vctSelectList.size() != vctShowEntryList.size() )		
            {
				LoadScheme("SchmNoAllSel");
            } 
            else
            {
				LoadScheme("SchmAllSel");
            }
		}
    }
    else
    {
        int nEntryNum = 0;
        BOOL bAllSel = TRUE;
        for ( int i = 0; i < m_vctShowList.size(); i++ )
        {
            TAddrItem tItem = m_vctShowList.at(i);
            if ( tItem.emItemType == emEntryItem )
            {
                nEntryNum++;
                if ( tItem.strImg == "AddrEditSelItem" )
                {
                    bAllSel = FALSE;
                    break;
                }
            }
        }
		
        if ( nEntryNum == 0 )
        {
			m_btnAllSel.EnableWindow(FALSE);
			m_btnAllNoSel.EnableWindow(FALSE);
			m_btnAllSel.ShowWindow(SW_SHOW);
			m_btnAllNoSel.ShowWindow(SW_HIDE);
        }
        else
        {
			m_btnAllSel.EnableWindow(TRUE);
			m_btnAllNoSel.EnableWindow(TRUE);
			
            if ( bAllSel )
            {
				LoadScheme("SchmAllSel");
            }
            else
            {
				LoadScheme("SchmNoAllSel");
            }
        }       
    }
    
}

//剪切复制粘贴状态更新 dyy 2013年9月25日
void CAddrEditLogic::UpdateCtrlButton()
{
    if ( !m_bInGroup )//组外禁用粘贴 dyy 2013-9-24 
    {
		m_btnCut.EnableWindow(FALSE);
		m_btnPaste.EnableWindow(FALSE);
    }
    else
    {
		m_btnCut.EnableWindow(TRUE);
		m_btnPaste.EnableWindow(TRUE);
    }
}

void CAddrEditLogic::UpdRefreshBtn()
{
	if ( m_bGlobalAddr )
	{
		m_btnRefresh.EnableWindow(TRUE);
		return;
	}

	if ( 0 == m_vctShowList.size() )
	{
		m_btnRefresh.EnableWindow(FALSE);
	}
	else
	{
		m_btnRefresh.EnableWindow(TRUE);
	}
}
