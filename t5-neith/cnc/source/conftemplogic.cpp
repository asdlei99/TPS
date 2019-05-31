#include "StdAfx.h"
#include "conftemplogic.h"
#include "confmsglogic.h"
#include "messageboxlogic.h"
#include "contentreqlogic.h"

template<> CConfTempLogic* Singleton<CConfTempLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CConfTempLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("ConfTempLayout"), OnCreate)
	MSG_INIWINDOW(_T("ConfTempLayout"), OnInit)
	MSG_ITEMSELECTD(_T("ConfTempList"), OnConfTempItemClick)
	MSG_CLICK(_T("BtnRefresh"), OnBtnRefresh)
	MSG_CLICK(_T("BtnTmpCall"), OnBtnTmpCall)
	MSG_CLICK(_T("BtnNoticeBack"), OnBtnNoticeBack)
	MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)	

	USER_MSG(UI_CNS_REFRESH_CONFTEMPLATE_LIST,OnRefreshConftempLst) 
    USER_MSG( UI_GETTEMPPWD_CMD, OnCnGetTempPwdCmd )
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNotify)
    USER_MSG( UI_CNS_HUNGUP_P2P_NOTIFY, OnHungupConfInd )  

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
	MSG_LETTERINDEX_CLICK(_T("ListIndex"),OnLetterIndex)

APP_END_MSG_MAP()

const String CConfTempLogic::m_strConfTempListItem = _T("ConfTempListItem");
const String CConfTempLogic::m_strConfTempName = _T("ConfTempName");
const String CConfTempLogic::m_strSeachEdit = _T("EdtSearch");
const String CConfTempLogic::m_strBtnTmpCall = _T("BtnTmpCall");

static UINT g_nCallingTmHandle = 0;
static UINT g_nFreshWaiting = 0;

VOID   CALLBACK   CTempConfTimer(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{   
	if ( idEvent == g_nCallingTmHandle)
	{  
		::KillTimer( NULL, g_nCallingTmHandle );
		g_nCallingTmHandle = 0;
		CConfTempLogic::GetSingletonPtr()->TempCallFail();
	}
	else if ( idEvent == g_nFreshWaiting )
	{
		::KillTimer( NULL, g_nFreshWaiting );
		g_nFreshWaiting = 0;
		CConfTempLogic::GetSingletonPtr()->OnWaitRefreshOverTime();
	}
}

CConfTempLogic::CConfTempLogic(void)
{
}

CConfTempLogic::~CConfTempLogic(void)
{
}

bool CConfTempLogic::OnCreate( TNotifyUI& msg )
{
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = DEFAULT_TITLE_HEIGHT;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), NULL, 0, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

	return false;
}

bool CConfTempLogic::OnInit( TNotifyUI& msg )
{
	//ComInterface->UpdateConfTemplate(); ������������Ϣˢ�� 2015-5-5 

	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	
	return true;
}

bool CConfTempLogic::OnRefreshConftempLst( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));
	if (g_nFreshWaiting != 0)
	{
		::KillTimer( NULL, g_nFreshWaiting );
		g_nFreshWaiting = 0;
	}
	m_vctConfTempList.clear();
	m_vctConfTempList = ComInterface->GetConfTempList();
	UpdateConfTempList();

	return true;
}

bool CConfTempLogic::OnCnGetTempPwdCmd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    s8 achTempPwd[MT_MAX_TEMP_PWD_LEN + 1] = {0};
    if (ShowContentReq() == IDCANCEL)
    {
        ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
        ICncCommonOp::SetControlText( _T("���ں���.."), m_pm, _T("LabelTip") );
        return false;
    }
    strcpy(achTempPwd, g_strContentReq.c_str());
    ComInterface->GetCnTempPwdInd(achTempPwd);
    return true;
}

void CConfTempLogic::OnWaitRefreshOverTime()
{
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));
}

TTPAlias CConfTempLogic::GetCallTempName()
{
    return m_tTPAlias;
}

void CConfTempLogic::UpdateConfTempList()
{
	tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
	if ( !strCaption.empty() )
	{
		m_vctShowTempList = m_vctSearchTempList;
	}
	else
	{
		m_vctShowTempList = m_vctConfTempList;
	}

	sort( m_vctShowTempList.begin(), m_vctShowTempList.end(), CUIDataMgr::ConfTempCompare );

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfTempList") );
	if ( pTileLayoutUI == NULL )
	{
		return;
	}
	pTileLayoutUI->RemoveAll();
	for ( int i = 0; i < m_vctShowTempList.size(); i++ )
	{
 		CListContainerElementUI *pListContainer = 
 			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( m_strConfTempListItem.c_str() );

		ICncCommonOp::SetControlText( CA2T(m_vctShowTempList.at(i).m_abyAlias), m_pm, m_strConfTempName.c_str(), pListContainer );
		CButtonUI* pBtnTmpCall = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnTmpCall.c_str(), pListContainer);
		if ( pBtnTmpCall )
		{
			pBtnTmpCall->SetTag( (UINT_PTR)&m_vctShowTempList.at(i));
		}

		pTileLayoutUI->Add(pListContainer);
	}
}

bool CConfTempLogic::OnConfTempItemClick( TNotifyUI& msg )
{
	int dwIndex = msg.wParam;
	int dwoldIndex = msg.lParam;
	TTPAlias tTPAlias = m_vctConfTempList.at(dwIndex);
	CDuiString name=msg.pSender->GetName();


	return false;
}

bool CConfTempLogic::OnBtnRefresh( TNotifyUI& msg )
{
	ComInterface->UpdateConfTemplate();
	ICncCommonOp::EnableControl(false,m_pm,_T("BtnRefresh"));
	g_nFreshWaiting = SetTimer( NULL, 0, 8000, CTempConfTimer); 

	tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
	if ( !strCaption.empty() )
	{
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtSearch"));
	}

    UpdateConfTempList();

	return false;
}

bool CConfTempLogic::OnBtnTmpCall( TNotifyUI& msg )
{
	CDuiString name=msg.pSender->GetName();
	TTPAlias tTPAlias;
	if ( name == _T("BtnTmpCall") )
	{
		tTPAlias = *(TTPAlias*)msg.pSender->GetTag();
	}

	CControlUI *pParent = msg.pSender->GetParent();
	if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
	{
		pItem->Select(true);
	}

	u16 wRe = NO_ERROR;
	TCMSConf tConfInfo;
	BOOL32 bIsInconf = ComInterface->IsInConf(&tConfInfo); 

	if ( bIsInconf )
	{
		ShowPopMsg( _T("�Ѿ��ڻ�����" ));
		return false;	
	}  

	TTPCnsInfo tCnsInfo;
	ComInterface->GetLocalCnsInfo( tCnsInfo );
	if( strlen( tCnsInfo.m_achRoomName ) == 0 )
	{  
		ShowMessageBox((_T("��������ʧ�ܣ����ػ᳡������")),false);
		return false;
	}

    m_tTPAlias = tTPAlias;//��ʱ��¼���е�ģ������
	wRe = ComInterface->StartTemplateConf( tTPAlias );
	if ( wRe == NO_ERROR )
	{   
		UIDATAMGR->setLocalCnsState( emLocalCnsCalling ); 
		ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
		//���ڼ���ն˿���Ҫ30s ģ���޷��ж� �ʶ���Ϊ35��δ��������ʾ 2016-10-21
		g_nCallingTmHandle = SetTimer( NULL, 0, 35000, CTempConfTimer); //ԭΪ10s
	}

	return true;
}

bool CConfTempLogic::OnSearchEditChange( TNotifyUI& msg )
{
 	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( !pEditSearch )
	{
		return false;
	}

	m_vctSearchTempList.clear();
	CString strSearch = pEditSearch->GetText();
	if ( !strSearch.IsEmpty() )
	{
		for ( u32 i = 0; i < m_vctConfTempList.size(); i++ )
		{
			CString strConfTempName;
			strConfTempName.Format( _T("%s"),CA2T( m_vctConfTempList.at(i).m_abyAlias));
			BOOL bFind = FALSE;			
			bFind = UIDATAMGR->HZPYMatchList( strSearch, strConfTempName );
			if ( bFind )
			{
				m_vctSearchTempList.push_back(m_vctConfTempList.at(i));
			}
		}
	}

	UpdateConfTempList();
	return false;
}

bool CConfTempLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( pEditSearch )
	{
		pEditSearch->SetText(_T(""));
	}
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	ICncCommonOp::SetControlText( _T("���ں���.."), m_pm, _T("LabelTip") );
	m_vctShowTempList.clear();
	m_vctSearchTempList.clear();
	m_vctConfTempList.clear();
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));
	UpdateConfTempList();
	return true;
}

bool CConfTempLogic::OnBtnNoticeBack( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	ICncCommonOp::SetControlText( _T("���ں���.."), m_pm, _T("LabelTip") );
	return true;
}

bool CConfTempLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf =  ComInterface->IsInConf( &tConfInfo );
	if ( !bInConf )
	{  
		return false;
	}
	TTPCnsConfStatus confState = ComInterface->GetLocalCnsConfState();
	if ( em_CALL_CALLING != confState.emState  )
	{   
		EMLocalCnsState emState = UIDATAMGR->GetLocalCnsState();

		if (  emLocalCnsCalling == emState  || emLocalCnsConnected == emState)
		{   
			ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") ); // ���غ��ж������� 
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strConfTempDlg.c_str(), false );
			UIDATAMGR->setLocalCnsState( emLocalCnsConnected );
			if (g_nCallingTmHandle != 0)
			{
				::KillTimer( NULL, g_nCallingTmHandle );
				g_nCallingTmHandle = 0;
			}

			if (UIDATAMGR->GetCurShowWndName() == g_strConfTempDlg)
			{
				WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
				UIDATAMGR->SetCurShowWndName( _T("") );
			}
		}
	} 

	return NO_ERROR;
}

void CConfTempLogic::TempCallFail()
{
	CLabelUI* pLable = (CLabelUI*)ICncCommonOp::FindControl(m_pm, _T("LabelTip"));
	if (pLable && pLable->IsVisible())
	{
		ICncCommonOp::SetControlText( _T("ģ����鿪��ʧ�ܣ����Ժ�����"), m_pm, _T("LabelTip") );
	}

	ShowPopMsg(_T("ģ����鿪��ʧ�ܣ����Ժ�����"));
}

bool CConfTempLogic::OnHungupConfInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    EmCnsCallReason emRe = (EmCnsCallReason)wParam;
    CString strErr = _T("");
    switch ( emRe )
    { 
    case EmCnsCallReason_success:
        strErr = _T("");
        break;
    case EmCnsCallReason_hungup://���عҶ�
        strErr = _T("");
        break;
    case EmCnsCallReason_Unreachable:
        strErr = _T("�Զ˲�����");
        break;
    case EmCnsCallReason_resourcefull:
        strErr = _T("�Ѵﵽ�᳡��������");
        break;
    case EmCnsCallReason_dstnotfind:
        strErr = _T("�Զ˲�����");
        break;
    case EmCnsCallReason_Busy:
        strErr = _T("�Զ�æ");
        break;
    case EmCnsCallReason_Local:
        strErr = _T("����ԭ��");
        break;
    case EmCnsCallReason_Rejected:		//�Զ˾ܾ�
        strErr = _T("�Զ˾ܾ�");
        break;
    case EmCnsCallReason_peerhungup:	//�Զ˹Ҷ�
        strErr = _T("����������Զ˹Ҷ�");
        break;
        // 	case EmCnsCallReason_Abnormal:  ���С����ػ᳡���ߡ�����ʾ��������Ӧ��ʾ����
        // 		strErr = ": ���˲�����";
        // 		break;
    case EmCnsCallReason_PeerAbnormal:
        strErr = _T("�Զ˲�����");
        break;
    case EmCnsCallReason_ConfOver:	//�������
        strErr = _T("�������"); 
        break;
    case EmCnsCallReason_cncallexception:
        strErr = _T("����ģ�����");
        break;
    case EmCnsCallReason_ConfExist:		//�����Ѵ���
        strErr = _T("�����Ѵ���");
        break; 
    case EmCnsCallReason_unknown:
        strErr = _T("����ʧ��");             //δ֪��������ʾ 
        break;
    default:
        strErr = _T("����ʧ��");
        break; 
    }

    CLabelUI* pLable = (CLabelUI*)ICncCommonOp::FindControl(m_pm, _T("LabelTip"));
    if (pLable && pLable->IsVisible() && !strErr.IsEmpty())
    {
        ICncCommonOp::SetControlText( strErr, m_pm, _T("LabelTip") );
    }

    if (g_nCallingTmHandle != 0)
    {
        ::KillTimer( NULL, g_nCallingTmHandle );
        g_nCallingTmHandle = 0;
    }
    return true;
}



bool CConfTempLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("ConfTempList"));
	if (!pTouch)
	{
		return false;
	}

	if (nLetterIndex == 0)
	{
		pTouch->ScrollToIndexLetter(0);
		return true;
	}

	CString strIndex;
	nLetterIndex = 'A' + nLetterIndex -1;
	strIndex.Format( _T("%c"), (char)nLetterIndex );
	int nYOffset = 0;
	int nItemCount = m_vctShowTempList.size();

	//�����Ŀ����ʱ�������ĸ�Ῠ������ ��ʹ�ö��ַ�
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //�õ�ǰ���������ϡ��½�ĳ�ֵ 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//��ǰ��������R[low..high]�ǿ� 
		swMidIndex =( swLowIndex + swHighIndex )/2; 
		if ( nMidIndex == swMidIndex )
		{
			break;
		}

		CString strLetter = _T("");
		UIDATAMGR->GetFirstLetter( m_vctShowTempList.at(swMidIndex).m_abyAlias, strLetter ); 

		int nRe = strIndex.Compare( strLetter );
		if(  nRe == 0 )  
		{        
			break;   
		} 
		else if ( nRe < 0 )
		{   
			swHighIndex = swMidIndex;  //��ǰ��������R[low..mid]  
		}
		else
		{   
			swLowIndex = swMidIndex + 1;//��ǰ��������R[mid..heith] 
		}						 

	} 

	//swLowIndex��swHighIndex���ʱ����swMidIndex�Ƚ�
	if ( swLowIndex == swHighIndex )
	{
		if ( swMidIndex < swHighIndex )
		{
			swHighIndex = swMidIndex;
		}
		else
		{
			swLowIndex = swMidIndex;
		}
	}

	//ȡswLowIndex��swHighIndex�е�һ����strIndex��ķ���
	if ( swLowIndex > swHighIndex )
	{
		CString strLetter = _T("");
		UIDATAMGR->GetFirstLetter(  m_vctShowTempList.at(swMidIndex).m_abyAlias, strLetter ); 

		int nRe = strIndex.Compare( strLetter );
		if( nRe > 0 )		 
		{
			swMidIndex = swLowIndex;
		}
		else
		{
			swMidIndex = swHighIndex;
		}

	}

	pTouch->ScrollToIndexLetter(swMidIndex);

	return true;
}

bool CConfTempLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}

