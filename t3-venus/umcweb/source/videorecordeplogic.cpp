// videorecordeplogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "videorecordeplogic.h"
#include "vediorecordlogic.h"
#include "videorecordepshowopt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoRecordEpLogic dialog

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率


CVideoRecordEpLogic::CVideoRecordEpLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CVideoRecordEpLogic::IDD, pParent)
{
	m_pList = NULL;
	m_pLetterIndex = NULL;
	m_pVTRCtrlIF = NULL;

	m_pCVedioRecordNameEditLogic = NULL;
}


void CVideoRecordEpLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoRecordEpLogic)
	DDX_Control(pDX, IDC_STATIC_VTR_RECORD_TIME_REAL, m_stcRecordTimeReal);
	DDX_Control(pDX, IDC_STATIC_VTR_RECORD_TIME, m_stcRecordTime);
	DDX_Control(pDX, IDC_STATIC_Title, m_stcTitle);
	DDX_Control(pDX, IDC_STATIC_CHILDWNDTITLE, m_stcChildTitle);
	DDX_Control(pDX, IDC_EDIT_Search, m_edtSearch);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_STOP, m_btnRecordStop);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_START, m_btnRecordStart);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_RESUME, m_btnRecordResume);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_FINISH, m_btnRecordFinish);
	DDX_Control(pDX, IDC_BUTTON_RECORD_RETURN, m_btnBack);
	DDX_Control(pDX, IDC_BUTTON_ShowEx, m_btnShowEx);
	DDX_Control(pDX, IDC_STATIC_REC_FILENAME, m_stcRecFileName);
	DDX_Control(pDX, IDC_STATIC_REC_FILENAME_REAL, m_stcRecFileNameReal);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoRecordEpLogic, CDlgChild)
	//{{AFX_MSG_MAP(CVideoRecordEpLogic)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_RETURN, OnButtonRecordReturn)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_START, OnButtonVtrRecordStart)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_STOP, OnButtonVtrRecordStop)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_RESUME, OnButtonVtrRecordResume)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_FINISH, OnButtonVtrRecordFinish)
	ON_MESSAGE( WM_EDIT_CHANGED, OnUpdateEDITSearch )
	ON_WM_DESTROY()
	ON_MESSAGE( WM_TIMER, OnTimer )
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, OnHideOptn )
	ON_MESSAGE( UI_UMSTOOL_SHOWOPT_EP_NTY, OnShowOptNty )
	ON_MESSAGE( WM_BUTTON_CLICK, OnBtnSwitch )
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM,  OnNoSelResultNotify )
	ON_MESSAGE( UI_UMSTOOL_VTR_REG_STATE_NTY,  OnVtrRegStateNty )
	ON_MESSAGE( UI_UMSTOOL_REC_MT_FORMAT_RSP,  OnRecMtFormatRsp )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoRecordEpLogic message handlers
void CVideoRecordEpLogic::RegisterFun()
{
	REG_MSG_HANDLER( _T("CVideoRecordEpLogic::OnClickListItem"), CVideoRecordEpLogic::OnClickListItem, this, CVideoRecordEpLogic );
	REG_MSG_HANDLER( _T("CVideoRecordEpLogic::OnClickListItemIcon"), CVideoRecordEpLogic::OnClickListItemIcon, this, CVideoRecordEpLogic );
	REG_MSG( UI_UMSTOOL_SHOWOPT_EP_NTY, GetSafeHwnd() );	
	REG_MSG( UI_UMSTOOL_VTR_REG_STATE_NTY, GetSafeHwnd() );	
	REG_MSG( UI_UMSTOOL_REC_MT_FORMAT_RSP, GetSafeHwnd() );	
}

BOOL CVideoRecordEpLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}

	if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
    }

	SetTimer( 5679, 1000, NULL );
	
	return TRUE;
}

void CVideoRecordEpLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	SAFE_RELEASE(m_pList);
	SAFE_RELEASE(m_pLetterIndex);

	KillTimer( 5679 );

	CVideoRecordEpShowOpt::Clean();
}


BOOL CVideoRecordEpLogic::InitControlPane()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
	
	m_btnBack.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnBack.SetWindowPos( NULL, 9*CUR_SCREEN_WIDTH_PER,  6*CUR_SCREEN_HEIGHT_PER, 66, 36, SWP_SHOWWINDOW );

	CString strConfName;
	if ( ((CVedioRecordLogic*)GetParent())->m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0  )
	{
		strConfName = ((CVedioRecordLogic*)GetParent())->m_tUmcConfInfoSel.m_achConfName;
	}
	
	CUmcwebCommon::SetTextTransStatic( &m_stcChildTitle, _T("录像设置") , 14, Color( 24, 25, 27 ) );
	m_stcChildTitle.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcTitle, strConfName , 14, Color( 24, 25, 27 ) );
	m_stcTitle.	SetWindowPos( NULL, (17+70)*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_btnShowEx.SetImage( IDR_PNG_ADDREDITWND_ADDRSHOWEX_SEL, IDR_PNG_ADDREDITWND_ADDRSHOWEX_DOWN, NULL,
        IDR_PNG_ADDREDITWND_ADDRSHOWEX_UNSEL,IDR_PNG_ADDREDITWND_ADDRSHOWEX_DOWN, NULL);
	m_btnShowEx.SetBindWnd( CVideoRecordEpShowOpt::GetDlgPtr()->GetSafeHwnd() );
	m_btnShowEx.SetWindowPos( NULL, (690-8-48)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 48*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );


	CUmcwebCommon::SetImgForTransSearchEdit(&m_edtSearch);
	
	//会场列表加入
	m_pList = new CListChild( "", CRect(12, 100, (690-60)+12, 488+100), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_pList )
	{
		m_pList->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (690-60)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_pList->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_pList->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pList->SetSliderAlwaysShow( TRUE );
		
		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect( 0, 0, 39, 486 ), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterIndex != NULL )
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
			m_pLetterIndex->SetBindList( m_pList );
			
			m_pList->GetWindowRect(&rectClient);
			ScreenToClient( &rectClient );
			
			m_edtSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, rectClient.right - 12, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			
			rectClient.left = rectClient.right - 3;
			rectClient.right = rectClient.left + 7;
			m_pList->SetSliderRect( rectClient );
			
			m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );	
		}
	}


	CUmcwebCommon::SetTextTransStatic( &m_stcRecordTime, _T("录制时间") , 13, Color( 46, 55, 76 ) );
	m_stcRecordTime.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  75*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcRecordTimeReal, _T("") , 13, Color( 24, 25, 27 ) );
	m_stcRecordTimeReal.SetWindowPos( NULL, (690+134)*CUR_SCREEN_WIDTH_PER,  75*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_btnRecordStart.SetImage( IDR_PNG_BTN_START_RECORD_NORMAL, IDR_PNG_BTN_START_RECORD_DOWN, IDR_PNG_BTN_START_RECORD_DISABLE );
	m_btnRecordStart.SetWindowPos( NULL, (1226-10-114)*CUR_SCREEN_WIDTH_PER,  67*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_SHOWWINDOW );
	
	m_btnRecordStop.SetImage( IDR_PNG_BTN_PAUSE_RECORD_NORMAL, IDR_PNG_PAUSE_RECORD_DOWN, IDR_PNG_PAUSE_RECORD_DISABLE );
	m_btnRecordStop.SetWindowPos( NULL, (1226-10-114-14-114)*CUR_SCREEN_WIDTH_PER,  67*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	m_btnRecordResume.SetImage( IDR_PNG_BTN_RESUME_RECORD_NORMAL, IDR_PNG_BTN_RESUME_RECORD_DOWN, IDR_PNG_BTN_RESUME_RECORD_DISABLE );
	m_btnRecordResume.SetWindowPos( NULL, (1226-10-114-14-114)*CUR_SCREEN_WIDTH_PER,  67*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	m_btnRecordFinish.SetImage( IDR_PNG_FINISH_RECORD_NORMAL, IDR_PNG_FINISH_RECORD_DOWN, IDR_PNG_FINISH_RECORD_DISABLE );
	m_btnRecordFinish.SetWindowPos( NULL, (1226-10-114)*CUR_SCREEN_WIDTH_PER,  67*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcRecFileName, _T("录像名称") , 13, Color( 46, 55, 76 ) );
	m_stcRecFileName.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  (75+(20+33))*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stcRecFileNameReal, _T("") , 13, Color( 46, 55, 76 ) );
	m_stcRecFileNameReal.SetWindowPos( NULL, (690+134)*CUR_SCREEN_WIDTH_PER,  (75+(20+33))*CUR_SCREEN_HEIGHT_PER, 350*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );


	return TRUE;
}

void CVideoRecordEpLogic::InitDlg()
{   
	ShowWindow(SW_HIDE);

	m_tRecInfoSel.Clear();
	m_vecTRecInfoSearch.clear();
	m_vecTRecInfo.clear();

	CVideoRecordEpShowOpt::GetDlgPtr()->InitDlg();

	if ( m_pCVedioRecordNameEditLogic )
	{
		m_pCVedioRecordNameEditLogic->SendMessage(WM_COMMAND, IDCANCEL);
	}
}

void CVideoRecordEpLogic::OnButtonRecordReturn() 
{
	((CVedioRecordLogic*)GetParent())->m_tUmcConfInfoSel.Clear();
	m_tRecInfoSel.Clear();
	((CVedioRecordLogic*)GetParent())->ShowChildWnd( em_Wnd_Init );
}

void CVideoRecordEpLogic::RefreshConfEpList(int nRefresh)
{
 	TUmcConfInfo tUmcConfInfoSel = ((CVedioRecordLogic*)GetParent())->m_tUmcConfInfoSel;

	//会议结束，但仍在会议里面时候
	if ( !( tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		m_stcTitle.SetWindowText("");
	}

	vector<TUmcRecInfo> vecTRecInfoNew;
	vector<TUmcRecInfo>::iterator it = tUmcConfInfoSel.m_vecTRecInfo.begin();
	for ( ; it != tUmcConfInfoSel.m_vecTRecInfo.end(); it++ )
	{
		if ( it->m_tInfo.m_tMtRecInfo.m_wMtID != 0 && it->m_tInfo.m_emType == em_rec_recorder_mt )
		{
			vecTRecInfoNew.push_back(*it);
		}
	}


	//2.3.将m_vecTRecInfo中的本地信息植入vecTRecInfoNew
	{
		vector<TUmcRecInfo>::iterator itRecInfoNew = vecTRecInfoNew.begin();
		for ( ; itRecInfoNew != vecTRecInfoNew.end(); itRecInfoNew++ )
		{
			vector<TUmcRecInfo>::iterator itRecInfoOld = m_vecTRecInfo.begin();
			for ( ; itRecInfoOld != m_vecTRecInfo.end(); itRecInfoOld++ )
			{
				if ( itRecInfoOld->m_tInfo.m_emType == em_rec_recorder_mt
					&& itRecInfoNew->m_tInfo.m_emType == em_rec_recorder_mt
					&& itRecInfoOld->m_tInfo.m_tMtRecInfo.m_wMtID == itRecInfoNew->m_tInfo.m_tMtRecInfo.m_wMtID
					&& (strcmp(itRecInfoOld->m_tInfo.m_achFileName, itRecInfoNew->m_tInfo.m_achFileName) == 0) )
				{
					itRecInfoNew->m_dwRecTime = itRecInfoOld->m_dwRecTime;
				}
			}
		}
	}

	
	
	//得到m_vecTUmcConfInfo
	m_vecTRecInfo = vecTRecInfoNew;

	//3.从m_vecTRecInfo中ShowOpt
	vector<TUmcRecInfo> vecTUmcRecInfoShowOpt;
	switch( CVideoRecordEpShowOpt::GetDlgPtr()->m_emShowState )
	{
	case emShowAllRecordEp:
		{
			vecTUmcRecInfoShowOpt = vecTRecInfoNew;
			break;
		}
	case emShowRecordEp:
		{
			vector<TUmcRecInfo>::iterator itRecInfoNew = vecTRecInfoNew.begin();
			for ( ; itRecInfoNew != vecTRecInfoNew.end(); itRecInfoNew++ )
			{
				if ( itRecInfoNew->m_tInfo.m_tMtRecInfo.m_wMtID != 0 && itRecInfoNew->m_tInfo.m_emType == em_rec_recorder_mt
					&& ( itRecInfoNew->m_emState == em_rec_working || itRecInfoNew->m_emState == em_rec_pause ) )
				{
					vecTUmcRecInfoShowOpt.push_back( *itRecInfoNew );
				}
			}
			break;
		}
	default:
		break;
	}


	//Search
	m_vecTRecInfoSearch.clear();
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);
	if ( strSearch != _T("") )
	{
		vector<TUmcRecInfo>::iterator it = vecTUmcRecInfoShowOpt.begin();
		for ( ; it != vecTUmcRecInfoShowOpt.end(); it++ )
		{
			BOOL bFindName = FALSE;	
			BOOL bFindNum = FALSE;
			bFindName = CUmcwebCommon::HZPYMatchList( strSearch, it->m_achName );
			if ( bFindName )
			{		
				m_vecTRecInfoSearch.push_back( *it );
			}
			else
			{
// 				//名字没有匹配到
// 				bFindNum = CUmcwebCommon::HZPYMatchList( strSearch, it->m_achE164 );
// 				if ( bFindNum )
// 				{		
// 					m_vecTRecInfoSearch.push_back( *it );
// 				}
			}
		}
	}
	else
	{
		m_vecTRecInfoSearch = vecTUmcRecInfoShowOpt;
	}
	
    Value_ListRecordEp val_ListRecordEp( &m_vecTRecInfoSearch, "CVideoRecordEpLogic::OnClickListItem" );
    if ( m_pList != NULL )
    {
        m_pList->SetData( val_ListRecordEp );
	}

	vector<TUmcRecInfo>::iterator itr = m_vecTRecInfoSearch.begin();
	int nSelItem = -1;
	for ( ; itr != m_vecTRecInfoSearch.end(); itr++ )
	{
		nSelItem++;
		if ( strcmp(m_tRecInfoSel.m_achName, itr->m_achName ) == 0 )
		{
			m_pList->SetSelItem(nSelItem);
			break;
		}
	}

	//5.在m_vecTRecInfoSearch中查找m_pTRecInfoSel
	bool bFind = false;
	if ( m_tRecInfoSel.m_achName[0] != '\0'/* || m_tRecInfoSel.m_achE164[0] != '\0'*/ )
	{
		vector<TUmcRecInfo>::iterator it = m_vecTRecInfoSearch.begin();
		for ( ; it != m_vecTRecInfoSearch.end(); it++ )
		{
			if ( m_tRecInfoSel.m_tInfo.m_tMtRecInfo.m_wMtID == it->m_tInfo.m_tMtRecInfo.m_wMtID )
			{
				switch( nRefresh )
				{
				case 0:
					{
						break;
					}
				case 1:
					{
						m_tRecInfoSel = *it;
						
						break;
					}
				case 2:
					{
						break;
					}
				default:
					break;
				}

				bFind = true;
				break;
			}
		}
	}
	
	if ( bFind == false )
	{
		m_tRecInfoSel.Clear();
	}
}

BOOL CVideoRecordEpLogic::ShowWindow( int nCmdShow )
{
	BOOL bRet = CDlgChild::ShowWindow( nCmdShow );

	if ( nCmdShow == SW_SHOW )
	{
		TUmcConfInfo tUmcConfInfoSel = ((CVedioRecordLogic*)GetParent())->m_tUmcConfInfoSel;
		m_stcTitle.SetWindowText( tUmcConfInfoSel.m_achConfName );

		LoadScheme(emSchemeRecordEpClean);
	}

	return bRet;
}

bool CVideoRecordEpLogic::OnClickListItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_RecordEpInfo *pItemInfo = dynamic_cast<const Data_RecordEpInfo*>( pBaseItem->GetUserData() )) 
        {
			if ( m_pVTRCtrlIF == NULL )
			{
				return true;
			}

			BOOL32 bRegState;
			m_pVTRCtrlIF->GetVtrRegState( bRegState );
			if( bRegState == FALSE )
			{
				m_tRecInfoSel.Clear();
				LoadScheme(emSchemeRecordEpNoVtr);
			}
			else
			{
				m_tRecInfoSel = *(pItemInfo->m_pTRecInfo);
				LoadScheme(emSchemeRecordEpSelItem);
				ShowSelItem();
			}
		}
    }
	
	return true;
}

bool CVideoRecordEpLogic::OnClickListItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_RecordEpInfo *pItemInfo = dynamic_cast<const Data_RecordEpInfo*>( pBaseItem->GetUserData() )) 
        {
		}
    }
	
	return true;
}

void CVideoRecordEpLogic::SetRecordEpInfo()
{
	if ( m_tRecInfoSel.m_achName[0] == '\0'/* && m_tRecInfoSel.m_achE164[0] == '\0'*/ )
	{
		return;
	}
	
	switch ( m_tRecInfoSel.m_emState )
	{
	case em_rec_unknow:
		{
			m_btnRecordStart.ShowWindow( SW_SHOW );
			m_btnRecordResume.ShowWindow( SW_HIDE );
			m_btnRecordStop.ShowWindow( SW_HIDE );
			m_btnRecordFinish.ShowWindow( SW_HIDE );
			break;
		}
	case em_rec_working:
		{
			m_btnRecordStart.ShowWindow( SW_HIDE );
			m_btnRecordResume.ShowWindow( SW_HIDE );
			m_btnRecordStop.ShowWindow( SW_SHOW );
			m_btnRecordFinish.ShowWindow( SW_SHOW );
			break;
		}
	case em_rec_pause:
		{
			m_btnRecordStart.ShowWindow( SW_HIDE );
			m_btnRecordResume.ShowWindow( SW_SHOW );
			m_btnRecordStop.ShowWindow( SW_HIDE );
			m_btnRecordFinish.ShowWindow( SW_SHOW );
			break;
		}
	case em_rec_finish:
		{
			m_btnRecordStart.ShowWindow( SW_SHOW );
			m_btnRecordResume.ShowWindow( SW_HIDE );
			m_btnRecordStop.ShowWindow( SW_HIDE );
			m_btnRecordFinish.ShowWindow( SW_HIDE );
			break;
		}
	default:
		break;
	}
}

void CVideoRecordEpLogic::OnButtonVtrRecordStart() 
{
	if ( m_tRecInfoSel.m_achName[0] == '\0' )
	{
		return;
	}

	EmMeetState emMeetState = ((CVedioRecordLogic*)GetParent())->SelItemState();
	if ( emMeetState == emMeetStatePlay )
	{
		CString strError;
		int nRet = 0;
		strError = "当前会议正在放像，不能录像";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	else if ( emMeetState == emMeetStateRecMt )
	{
		CString strError;
		int nRet = 0;
		strError = "会议中只能有一个会场录像";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}

	u16 nRet = m_pVTRCtrlIF->RecMtFormatReq( m_tRecInfoSel.m_tInfo.m_wConfID, m_tRecInfoSel.m_tInfo.m_tMtRecInfo.m_wMtID );

	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("会场格式请求发送失败") );
	}
}

void CVideoRecordEpLogic::OnButtonVtrRecordResume() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	if ( m_tRecInfoSel.m_achName[0] == '\0'/* && m_tRecInfoSel.m_achE164[0] == '\0'*/ )
	{
		return;
	}
	
	
	TRecConfRes tRecConfRes;
	tRecConfRes.m_byEqpID = m_tRecInfoSel.m_tInfo.m_byEqpID;
	tRecConfRes.m_emType = m_tRecInfoSel.m_tInfo.m_emType;
	tRecConfRes.m_wConfID = m_tRecInfoSel.m_tInfo.m_wConfID;
	tRecConfRes.m_wMtID = m_tRecInfoSel.m_tInfo.m_tMtRecInfo.m_wMtID;
	
	u16 nRet = m_pVTRCtrlIF->RecResumeConfReq( tRecConfRes );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("继续录像请求发送失败") );
	}	
}

void CVideoRecordEpLogic::OnButtonVtrRecordStop() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	if ( m_tRecInfoSel.m_achName[0] == '\0'/* && m_tRecInfoSel.m_achE164[0] == '\0'*/ )
	{
		return;
	}
	
	
	TRecConfRes tRecConfRes;
	tRecConfRes.m_byEqpID = m_tRecInfoSel.m_tInfo.m_byEqpID;
	tRecConfRes.m_emType = m_tRecInfoSel.m_tInfo.m_emType;
	tRecConfRes.m_wConfID = m_tRecInfoSel.m_tInfo.m_wConfID;
	tRecConfRes.m_wMtID = m_tRecInfoSel.m_tInfo.m_tMtRecInfo.m_wMtID;
	
	u16 nRet = m_pVTRCtrlIF->RecPauseConfReq( tRecConfRes );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("暂停录像请求发送失败") );
	}	
}

void CVideoRecordEpLogic::OnButtonVtrRecordFinish() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}
	
	if ( m_tRecInfoSel.m_achName[0] == '\0'/* && m_tRecInfoSel.m_achE164[0] == '\0'*/ )
	{
		return;
	}
	
	TRecConfRes tRecConfRes;
	tRecConfRes.m_byEqpID = m_tRecInfoSel.m_tInfo.m_byEqpID;
	tRecConfRes.m_emType = m_tRecInfoSel.m_tInfo.m_emType;
	tRecConfRes.m_wConfID = m_tRecInfoSel.m_tInfo.m_wConfID;
	tRecConfRes.m_wMtID = m_tRecInfoSel.m_tInfo.m_tMtRecInfo.m_wMtID;
	
	u16 nRet = m_pVTRCtrlIF->RecStopConfReq( tRecConfRes );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("结束录像请求发送失败") );
	}
}

LRESULT CVideoRecordEpLogic::OnUpdateEDITSearch( WPARAM wparam, LPARAM lparam ) 
{
	HWND wnd = (HWND)wparam;

	if ( m_edtSearch.GetSafeHwnd() == wnd )
	{
		RefreshConfEpList();
	}

	return S_OK;
}

void CVideoRecordEpLogic::LoadScheme( EmSchemeRecordEp emScheme )
{
	switch( emScheme )
	{
	case emSchemeRecordEpClean:
		{
			m_edtSearch.SetWindowText("");
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);

			m_pList->SetSelItem(-1);

			break;
		}
	case emSchemeRecordEpSelItem:
		{
			m_stcRecordTime.ShowWindow(SW_SHOW);
			m_stcRecordTimeReal.ShowWindow(SW_SHOW);
			m_btnRecordStop.ShowWindow(SW_SHOW);
			m_btnRecordStart.ShowWindow(SW_SHOW);
			m_btnRecordResume.ShowWindow(SW_SHOW);
			m_btnRecordFinish.ShowWindow(SW_SHOW);
			m_stcRecFileName.ShowWindow(SW_SHOW);
			m_stcRecFileNameReal.ShowWindow(SW_SHOW);

			SetRecordEpInfo();
			
			break;
		}
	case emSchemeRecordEpNoVtr:
		{
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);

			break;
		}
	case emSchemeRecordEpNoShow:
		{
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			
			m_pList->SetSelItem(-1);

			break;
		}
	case emSchemeRecordEpDelConf:
		{
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);

			m_tRecInfoSel.Clear();
			m_vecTRecInfoSearch.clear();
			m_vecTRecInfo.clear();
			Value_ListRecordEp val_ListRecordEp( &m_vecTRecInfoSearch, "CVideoRecordEpLogic::OnClickListItem" );
			m_pList->SetData(val_ListRecordEp);

			OnButtonRecordReturn();

			break;
		}
	default:
		break;
	}
}

LRESULT CVideoRecordEpLogic::OnTimer( WPARAM wparam, LPARAM lparam )
{
	if ( m_tRecInfoSel.m_achName[0] == '\0'/* && m_tRecInfoSel.m_achE164[0] == '\0'*/ )
	{
		if ( ((CVedioRecordLogic*)GetParent())->m_emCurrentWnd == emCurrentWndEp )
		{
			LoadScheme( emSchemeRecordEpNoShow );
		}
		return S_OK;
	}

	

	vector<TUmcRecInfo>::iterator itMt = m_vecTRecInfo.begin();
	for ( ; itMt != m_vecTRecInfo.end(); itMt++ )
	{		
		if ( itMt->m_emState == em_rec_working )
		{
			itMt->m_dwRecTime++;
		}		
	}

	ShowSelItem();

	return S_OK;
}

LRESULT CVideoRecordEpLogic::OnShowOptNty( WPARAM wParam, LPARAM lParam )
{
	EM_ShowStateRecordEp emShowState = (EM_ShowStateRecordEp)wParam;
	RefreshConfEpList();

	//CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT );

	return S_OK;
}

LRESULT CVideoRecordEpLogic::OnBtnSwitch(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;
	if ( hWnd == m_btnShowEx.GetSafeHwnd() )
	{
		bool bOn = false;
		bOn = m_btnShowEx.GetSwitchState();
		if ( bOn )
		{
			CRect rect;
			m_btnShowEx.GetWindowRect(&rect);
			CVideoRecordEpShowOpt::GetDlgPtr()->ShowWindow(SW_SHOW);
			CVideoRecordEpShowOpt::GetDlgPtr()->SetWindowPos(NULL, rect.right - 232, rect.bottom, 232, 110, SWP_SHOWWINDOW );
		}
		else
		{
			CVideoRecordEpShowOpt::GetDlgPtr()->ShowWindow(SW_HIDE);
		}
	}
	
	return 0;
}

LRESULT CVideoRecordEpLogic::OnHideOptn( WPARAM wParam, LPARAM lParam )
{
	m_btnShowEx.SetSwitchState(FALSE);
	
	return S_OK;
}

TConRecState* CVideoRecordEpLogic::GetRecMtInfo()
{	
	vector<TUmcRecInfo>::iterator itRec = m_vecTRecInfo.begin();
	for ( ; itRec != m_vecTRecInfo.end(); itRec++ )
	{
		if ( itRec->m_tInfo.m_tMtRecInfo.m_wMtID == m_tRecInfoSel.m_tInfo.m_tMtRecInfo.m_wMtID )
		{
			return itRec;
		}
	}
	
	return NULL;
}

LRESULT CVideoRecordEpLogic::OnNoSelResultNotify(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;
	if ( hWnd == m_pList->GetSafeHwnd() )
	{
		LoadScheme(emSchemeRecordEpClean);
		
		m_tRecInfoSel.Clear();
	}
	
	return 0;
}

LRESULT CVideoRecordEpLogic::OnVtrRegStateNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return 0;
	}
	
	BOOL32 bRegState;
	m_pVTRCtrlIF->GetVtrRegState( bRegState );
	if( bRegState == FALSE )
	{
		m_tRecInfoSel.Clear();
		LoadScheme( emSchemeRecordEpNoVtr );
	}
	
	return 0;
}

void CVideoRecordEpLogic::ShowSelItem()
{
	TConRecState* pTConRecState = GetRecMtInfo();
	if ( pTConRecState == NULL )
	{
		return;
	}
	
	if ( pTConRecState->m_emState == em_rec_working || pTConRecState->m_emState == em_rec_pause
		|| pTConRecState->m_emState == em_rec_finish )
	{
		int nSec = 0;
		int nMin = 0;
		int nHour = 0;
		CUmcwebCommon::GetTime( pTConRecState->m_dwRecTime, nHour, nMin, nSec );
		
		CString strCaption;
		strCaption.Format( "%d:%d:%d",nHour, nMin, nSec );
		m_stcRecordTimeReal.SetWindowText(strCaption);

		strCaption = m_pVTRCtrlIF->GetNoSuffixString(pTConRecState->m_tInfo.m_achFileName);
		m_stcRecFileNameReal.SetWindowText(strCaption);
	}
	else
	{
		m_stcRecordTimeReal.SetWindowText("");

		m_stcRecFileNameReal.SetWindowText("");
	}
	
	LoadScheme(emSchemeRecordEpSelItem);
	
	if ( this->IsWindowVisible() )
	{
		RedrawWindow();
	}
}

LRESULT CVideoRecordEpLogic::OnRecMtFormatRsp(WPARAM wParam, LPARAM lParam)
{
	TTPRecMtFormat tTPRecMtFormat = *((TTPRecMtFormat*)wParam);
	if ( tTPRecMtFormat.m_bValid == FALSE )
	{
		CString strError;
		int nRet = 0;
		strError = "会场格式请求失败，不能录像";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return 0;
	}

	m_tRecInfoSel.m_tInfo.m_tConfRecInfo.m_tConfFormat = tTPRecMtFormat.m_tVidFormat;

	CVedioRecordNameEditLogic cLogic( m_tRecInfoSel.m_tInfo );
	m_pCVedioRecordNameEditLogic = &cLogic;
	cLogic.DoModal();
	m_pCVedioRecordNameEditLogic = NULL;

	return 0;
}