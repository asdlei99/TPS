#include "StdAfx.h"
#include "addrbooklogic.h"
#include "confmsglogic.h"
#include "mainframelogic.h"
#include "addreditlogic.h"

//lint -e1054    屏蔽pclint1054错误  
//lint -e309
//lint -e69      can't cast from int to struct
//lint -e78      Symbol XXX used in expression
//lint -e84      sizeof object is zero or object is undefined
//lint -e1018    Expected a type after 'new'
//lint -e1043    Attempting to 'delete' a non-pointer
//lint -e1072    Reference variable '' must be initialized
//lint -e1036


//#include <dwmapi.h> 
//#pragma comment (lib , "dwmapi.lib" ) 
template<> CAddrBookLogic* Singleton<CAddrBookLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CAddrBookLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("AddrBookLayout"), OnCreate)
	MSG_INIWINDOW(_T("AddrBookLayout"), OnInit)

	MSG_ITEMDOWN(_T("AddrListItem"), OnAddrItemClick)
	//MSG_ITEMDBLCLICK(_T("AddrListItem"), OnAddrItemDBClick)

	MSG_SELECTCHANGE(_T("BtnAddrSel"), OnCheckAddrItem)
	MSG_CLICK(_T("BtnAddrCall"), OnBtnAddrCall)
    MSG_CLICK(_T("imgAddrLabel"), OnBtnAddrLabel)
   
	MSG_CLICK(_T("BtnRefresh"), OnBtnRefresh)
    MSG_CLICK(_T("BtnInviteCns"), OnBtnInviteCns)   
    MSG_CLICK(_T("BtnCnsIsSel"), OnBtnCnsIsSel)
    MSG_CLICK(_T("BtnAddrConfig"), OnBtnAddrConfig)   

    MSG_CLICK(_T("BtnAddrMainPath"), OnBtnAddrMainPath)
    MSG_CLICK(_T("BtnGroupPath1"), OnBtnGroupPath1)

    MSG_CLICK(_T("BtnNoticeBack"), OnBtnNoticeBack)

    MSG_ITEMSELECTD(_T("ComboAddrShowEx"), OnComboShowEx)
    MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)

    MSG_CLICK(_T("BtnAddrInviteOther"), OnBtnAddrInviteOther)  
	
	USER_MSG( UI_CNS_ADDRBOOK_CHANGED, UpdateLocalAddrBook )
    USER_MSG( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, OnUpdateGlobalAddrBook )
    
    USER_MSG( UI_CNS_CONFSTATE_NOTIFY, OnConfStateNotify )
    USER_MSG( UI_CNS_HUNGUP_P2P_NOTIFY, OnHungupConfInd )   
    USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

    USER_MSG(UI_CNS_ADDRBOOK_MODIFY, OnAddrBookModify)
    USER_MSG(UI_CNS_ADDRBOOK_DELETE, OnAddrBookDelete)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
	MSG_LETTERINDEX_CLICK(_T("ListIndex"),OnLetterIndex)

APP_END_MSG_MAP()


const String CAddrBookLogic::strAddrList = _T("AddrList");
const String CAddrBookLogic::strAddrListItem = _T("AddrListItem");
const String CAddrBookLogic::strAddrName = _T("AddrName");
const String CAddrBookLogic::strAddrE164 = _T("AddrE164");

static UINT g_nCallingP2PHandle = 0;
static UINT g_nHandleWaiting = 0;

VOID   CALLBACK   CP2PConfTimer(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{   
	if ( idEvent == g_nCallingP2PHandle)
	{  
		::KillTimer( NULL, g_nCallingP2PHandle );
		g_nCallingP2PHandle = 0;
		CAddrBookLogic::GetSingletonPtr()->P2PCallFail();
	}
    else if ( idEvent == g_nHandleWaiting )
    {
        ::KillTimer( NULL, g_nHandleWaiting );
        g_nHandleWaiting = 0;
        CAddrBookLogic::GetSingletonPtr()->OnWaitRefreshOverTime();
    }
}

CAddrBookLogic::CAddrBookLogic(void)
{
	m_pAddrList = NULL;
	m_nSelIndex = -1;
    m_bSearchEdit = FALSE;
    m_emAddrShowState = emShowAllAddr;
}


CAddrBookLogic::~CAddrBookLogic(void)
{
}


bool CAddrBookLogic::OnCreate( TNotifyUI& msg )
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

    m_pAddrList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strAddrList.c_str() );
    if ( m_pAddrList == NULL )
    {
        return false;
    }

	//毛玻璃窗口效果
	/*HWND hWnd = m_pm->GetPaintWindow();
	BOOL bDwm ;
	DwmIsCompositionEnabled (&bDwm );
	if (bDwm )
	{  
		//MARGINS mrg = {-1};  
		//DwmExtendFrameIntoClientArea (hWnd , &mrg );
		//SetBackgroundColor (RGB (0, 0, 0));

		DWM_BLURBEHIND bb = {0};  
		bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;  
		bb.fEnable = true;  
		bb.hRgnBlur = NULL;  
		DwmEnableBlurBehindWindow(hWnd, &bb);
	} */
	return false;
}

bool CAddrBookLogic::OnInit(TNotifyUI& msg)
{
    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboAddrShowEx") );
    if ( pComboEx != NULL )
    {	
        CListLabelElementUI *pListLabelElement1 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement1->SetText(_T("全  部"));
        pComboEx->Add(pListLabelElement1);

        CListLabelElementUI *pListLabelElement2 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement2->SetText(_T("组"));
        pComboEx->Add(pListLabelElement2);

        CListLabelElementUI *pListLabelElement3 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement3->SetText(_T("在  线"));
        pComboEx->Add(pListLabelElement3);

        CListLabelElementUI *pListLabelElement4 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement4->SetText(_T("不在线"));
        pComboEx->Add(pListLabelElement4);
    }

	return true;
}


bool CAddrBookLogic::OnCheckAddrItem(TNotifyUI& msg)
{
	CControlUI *pParent = msg.pSender->GetParent();
	if ( CListContainerElementUI *pAddrItem = dynamic_cast<CListContainerElementUI*>(pParent) )
	{
		TAddrItem tAddrItem = *(TAddrItem*)pAddrItem->GetTag();

		CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
		bool bCheck = pCheckBox->GetCheck();

		if ( bCheck )
		{
			if ( m_nSelIndex != -1 )
			{
				CControlUI *pLastSel = m_pAddrList->GetItemAt(m_nSelIndex);
                if ( pLastSel != NULL )
                {
                    TAddrItem tLastItem = *(TAddrItem*)pLastSel->GetTag();
                    if ( tLastItem.emItemType == emEntryItem && !tLastItem.tAddrInfo.bOnLine )
                    {
                        m_pm->DoCase( _T("caseListOffline"), pLastSel );
                    }
                    else
                    {
                        m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                    } 
                }
				m_nSelIndex = -1;
			}

			pAddrItem->SetBkImage( _T("res\\list\\item_sel.png") );

			m_vctSelectList.push_back( tAddrItem );
		}
		else
		{
            if ( tAddrItem.emItemType == emEntryItem && !tAddrItem.tAddrInfo.bOnLine )
            {
                m_pm->DoCase( _T("caseListOffline"), pParent );
            }
            else
            {
                m_pm->DoCase( _T("caseListNoSel"), pParent );
            } 

			vector<TAddrItem>::iterator iter = m_vctSelectList.begin();
			while( iter != m_vctSelectList.end() )
			{					  
				if ( iter->IsSameName(tAddrItem) )
				{
					m_vctSelectList.erase(iter);
					break;
				}		
				iter++;
			}
		}
	}

    if ( m_vctSelectList.empty() )
    {
        m_pm->DoCase( _T("caseCnsNoSel") );

        ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
    }
    else
    {
        m_pm->DoCase( _T("caseCnsHasSel") );

        CString str = _T("");
        str.Format(_T("(%d)"), m_vctSelectList.size());
        ICncCommonOp::SetControlText(str, m_pm, _T("labSelCount"));
    }

	return true;
}


bool CAddrBookLogic::OnBtnAddrLabel(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        TAddrItem tAddrItem = *(TAddrItem*)pItem->GetTag();
        if ( tAddrItem.emItemType == emEntryItem )
        {
            if ( !m_vctSelectList.empty() )
            {
                return true;
            }

            m_pm->DoCase( _T("caseItemShowInfo"), pParent );
            int nIndex = pItem->GetIndex();
            if ( m_nSelIndex == -1 )
            {
                //m_pm->DoCase( _T("caseListSel"), msg.pSender );
                m_nSelIndex = nIndex;
            }
            else
            {
                if ( m_nSelIndex == nIndex )
                {
                    //m_pm->DoCase( _T("caseListNoSel"), msg.pSender );
                    //m_nSelIndex = -1;
                }
                else
                {
                    CControlUI *pLastSel = m_pAddrList->GetItemAt(m_nSelIndex);
                    if ( pLastSel != NULL )
                    {
                        TAddrItem tLastItem = *(TAddrItem*)pLastSel->GetTag();
                        if ( tLastItem.emItemType == emEntryItem && !tLastItem.tAddrInfo.bOnLine )
                        {
                            m_pm->DoCase( _T("caseListOffline"), pLastSel );
                        }
                        else
                        {
                            m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                        } 

                        if ( m_emSelType == emEntryItem )
                        {
                            m_pm->DoCase( _T("caseItemShowLabel"), pLastSel );
                        }
                    }                   
                    //m_pm->DoCase( _T("caseListSel"), msg.pSender );
                    m_nSelIndex = nIndex;
                }
            }

            m_emSelType = emEntryItem;
        }
        else//点击组条目，进入组
        {
            m_vctSelectList.clear();
            m_pm->DoCase( _T("caseCnsNoSel") );
            ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
            ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
            m_bSearchEdit = FALSE;

            //进入组
            m_SelGroup = tAddrItem.tGroupInfo;
            UpdateGroupMemberList( m_SelGroup.dwGroupIdx );

            //更新路径
            UpdateAddrPath();
        }
    }

    return true;
}



bool CAddrBookLogic::OnBtnAddrCall(TNotifyUI& msg)
{
	CControlUI *pParent = msg.pSender->GetParent();
	if ( const CListContainerElementUI *pAddrItem = dynamic_cast<const CListContainerElementUI*>(pParent) )
	{
		TAddrItem tAddrItem = *(TAddrItem*)pAddrItem->GetTag();

        TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
        u32 dwIp = 0;
        if ( strlen( tAddrInfo.achIp ) > 0 )
        {
            dwIp = inet_addr( tAddrInfo.achIp );
        }

        TTPCnsInfo tCnsInfo;
        ComInterface->GetLocalCnsInfo( tCnsInfo );
        if ( (strlen( tAddrInfo.achEntryName ) > 0 && strcmp( tAddrInfo.achEntryName, tCnsInfo.m_achRoomName ) == 0 ) ||
            (strlen( tAddrInfo.achE164 ) > 0 && strcmp( tAddrInfo.achE164, tCnsInfo.m_achE164 ) == 0 ) )
        {
            ShowMessageBox( _T("不能呼叫本地会场") );
            return false;
        }

        TCMSConf tConf;
        BOOL32 bInconf = ComInterface->IsInConf( &tConf );
		u16 wRe = NO_ERROR;

		if ( tAddrItem.emItemType == emEntryItem )
		{
            if ( !bInconf )
            {	    
			    TCnAddr tCnAddr;
			    strncpy( tCnAddr.achAlias, tAddrInfo.achEntryName, sizeof(tAddrInfo.achEntryName) );
			    strncpy( tCnAddr.achE164, tAddrInfo.achE164, sizeof(tAddrInfo.achE164) );
                tCnAddr.dwIP = dwIp;
                //tCnAddr.bCallByIPAndAlias = tAddrInfo.bMonitorTer;
				tCnAddr.bCallByIPAndAlias = (1 == tAddrInfo.byTerType);
                switch (tAddrInfo.byTerType)
                {
                case 1://监控终端
                case 2://普通终端
                    tCnAddr.emTpConfProtocol = emTpH323;
                    break;
                default://网呈终端 和 其它
                    tCnAddr.emTpConfProtocol = emTpSIP;
                    break;
                }
			    u16 wRe = ComInterface->StartP2PConf( tCnAddr );
			    if ( wRe == NO_ERROR )
			    {  
				    //BusinessManagePtr->SetCurConfName( PTP_CONF );
                    ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );  
                    UIDATAMGR->setLocalCnsState( emLocalCnsCalling );
// 					if (/*tAddrInfo.bMonitorTer*/1 == tAddrInfo.byTerType)//监控终端点对点35s
// 					{
// 						g_nCallingP2PHandle = SetTimer( NULL, 0, 35000, CP2PConfTimer); 
// 					}
// 					else//非监控终端 10s(量子加密密码获取时间较长改为35s)
// 					{
// 						TTpEncryptKey tEncryt;
// 						ComInterface->GetEncrytInfo( tEncryt );
// 						if (tEncryt.emTPEncryptType == emTPEncryptTypeQt)
// 						{
// 							g_nCallingP2PHandle = SetTimer( NULL, 0, 35000, CP2PConfTimer); 
// 						}
// 						else
// 						{
// 							g_nCallingP2PHandle = SetTimer( NULL, 0, 10000, CP2PConfTimer); 
// 						}
// 					}
				    g_nCallingP2PHandle = SetTimer( NULL, 0, 35000, CP2PConfTimer); //都改为35s
			    }
            }
            else
            {
                //点对点扩展为多点
                if ( tConf.m_emConfType == emCallType_P2P )
                {
                    vector<TCnAddr> tCnAddrList;
                    TCnAddr tCnAddr;
                    tCnAddr.emType = emTpAlias;
                    strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddrList.push_back( tCnAddr );

                    //点对点会议变多点会议,添加点对点会议对端会场
					TTPCallSerInfo tCallSerInfo;
					ComInterface->GetCallServerInfo(tCallSerInfo);
					if ( tCallSerInfo.dwCallServiceIP == 0 )
					{
						ShowMessageBox( _T("呼叫失败：未配置呼叫服务器") );
						return false;
					}

                    TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();
                    if ( strlen( status.achConfName ) > 0  )
                    {
                        TCnAddr tCnAdd;
                        //strncpy( tCnAddr.achAlias, status.achConfName, TP_MAX_H323ALIAS_LEN+1 );
                        tCnAdd = status.tCalledAddr;
                        tCnAdd.emTpConfProtocol = status.m_emConfProtocal;
                        tCnAddrList.push_back( tCnAdd );
                    }

                    tCnAddr.emType = emTpE164Num;
                    strncpy( tCnAddr.achAlias, tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddr.dwIP = dwIp;
                    //tCnAddr.bCallByIPAndAlias = tAddrInfo.bMonitorTer;
					tCnAddr.bCallByIPAndAlias = (1 == tAddrInfo.byTerType);
                    switch (tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCnAddr.emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCnAddr.emTpConfProtocol = emTpSIP;
                        break;
                    }
                    tCnAddrList.push_back( tCnAddr );

					wRe = ComInterface->StartInstantConf( tCnAddrList );		
					if ( wRe == NO_ERROR )
					{   
						ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
						UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
					}
                }
                else
                {
                    TTpCallAddr tCallAddr;
                    tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  tAddrInfo.achEntryName );
                    tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tAddrInfo.achE164 );
                    tCallAddr.m_dwIP = dwIp;
                    tCallAddr.m_bAliasIP = (1 == tAddrInfo.byTerType);
                    switch (tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCallAddr.m_emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCallAddr.m_emTpConfProtocol = emTpSIP;
                        break;
                    }
                    ComInterface->InviteCns( tCallAddr );
                }
            }
		}
        else 
        {
            TTPCallSerInfo tCallSerInfo;
            ComInterface->GetCallServerInfo(tCallSerInfo);
            if ( tCallSerInfo.dwCallServiceIP == 0 )
            {
                ShowMessageBox( _T("呼叫失败：未配置呼叫服务器") );
                return false;
            }

            TGroupInfo tGroupInfo = tAddrItem.tGroupInfo;
            vector<TAddrInfo> vctAddrInfo;
            ComInterface->GetGroupAddrInfo( tGroupInfo, vctAddrInfo );
            if ( vctAddrInfo.size() == 0 )
            {
                return true;
            }

            TConfCallEpAddrList tConfAddrList;
            TEpAddrList tAddrList;
            vector<TCnAddr> tCnAddrList;

            TTPCnsInfo tCnsInfo;
            ComInterface->GetLocalCnsInfo( tCnsInfo );
           
            if ( bInconf  )
            {
                tConfAddrList.m_wConfID = tConf.m_wConfID;
                if ( tConf.m_emConfType == emCallType_P2P )
                {
                    TTpCallAddr tCallAddr;
                    tCallAddr.m_tAlias.SetAlias( tp_Alias_h323, tCnsInfo.m_achRoomName );
                    tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tCnsInfo.m_achE164 );
//                     switch (tCnsInfo.byTerType)
//                     {
//                     case 1://监控终端
//                     case 2://普通终端
//                         tCallAddr.m_emTpConfProtocol = emTpH323;
//                         break;
//                     default://网呈终端 和 其它
//                         tCallAddr.m_emTpConfProtocol = emTpSIP;
//                         break;
//                     }
                    tAddrList.Add( tCallAddr );

                    TCnAddr tCnAddr;
                    tCnAddr.emType = emTpAlias;
                    strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddrList.push_back( tCnAddr );
                }
            }
            else
            {	
                TCnAddr tCnAddr;
                tCnAddr.emType = emTpAlias;
                strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
                strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
                tCnAddrList.push_back( tCnAddr );
            }

            for ( u16 nIndex = 0; nIndex < vctAddrInfo.size(); nIndex++ )
            {
                TAddrInfo tAddrInfo = vctAddrInfo.at(nIndex);

                TTpCallAddr tCallAddr;
                TCnAddr tCnAddr;
						
                EmConfAddEpRet emRet = TP_ConfAddEpRet_Unknow;	

                u32 dwIp = 0;
                if ( strlen( tAddrInfo.achIp ) > 0 )
                {
                    dwIp = inet_addr( tAddrInfo.achIp );
                }

                if ( strlen( tAddrInfo.achE164 ) > 0 )
                {
                    if( strcmp( tAddrInfo.achE164, tCnsInfo.m_achE164 ) == 0 )
                    {
                        continue;
                    }

                    tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  tAddrInfo.achEntryName );
                    tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tAddrInfo.achE164 );
                    tCallAddr.m_dwIP = dwIp;
                    switch (tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCallAddr.m_emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCallAddr.m_emTpConfProtocol = emTpSIP;
                        break;
                    }
                    emRet = tAddrList.Add( tCallAddr );

                    tCnAddr.emType = emTpE164Num;
                    strncpy( tCnAddr.achAlias, tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddr.dwIP = dwIp;
                    //tCnAddr.bCallByIPAndAlias = tAddrInfo.bMonitorTer;
					tCnAddr.bCallByIPAndAlias = (1 == tAddrInfo.byTerType);
                    tCnAddrList.push_back( tCnAddr );
                }
                else
                {
                    if ( strcmp( tAddrInfo.achEntryName, tCnsInfo.m_achRoomName ) == 0  ) 
                    {
                        continue;
                    }

                    if ( bInconf && tConf.IsCnsInConf( tAddrInfo.achEntryName ) )
                    {				
                        //strErr.Format( "会场 %s 已在本会议中", tItem.tAddrInfo.achEntryName );
                        //ShowPopMsg( strErr );
                        continue;
                    }

                    tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  tAddrInfo.achEntryName );
                    tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tAddrInfo.achE164 );
                    tCallAddr.m_dwIP = dwIp;
                    switch (tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCallAddr.m_emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCallAddr.m_emTpConfProtocol = emTpSIP;
                        break;
                    }
                    emRet = tAddrList.Add( tCallAddr );

                    tCnAddr.emType = emTpAlias;
                    strncpy( tCnAddr.achAlias, tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddr.dwIP = dwIp;
                    //tCnAddr.bCallByIPAndAlias = tAddrInfo.bMonitorTer;
					tCnAddr.bCallByIPAndAlias = (1 == tAddrInfo.byTerType);
                    switch (tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCnAddr.emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCnAddr.emTpConfProtocol = emTpSIP;
                        break;
                    }
                    tCnAddrList.push_back( tCnAddr );
                }
                if ( emRet != TP_ConfAddEpRet_Success )
                {
                    if ( emRet == TP_ConfAddEpRet_MaxNum )
                    {
                        //strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
                        //ShowPopMsg( strErr );
                        break;
                    }
                    continue;
                }
                if ( tCnAddrList.size() == TP_CONF_MAX_EPNUM )
                {
                    //strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
                    //ShowPopMsg( strErr );
                    break;
                }
            }

            if ( bInconf )
            {
                if ( tConf.m_emConfType == emCallType_P2P )
                {
                    //点对点会议变多点会议,添加点对点会议对端会场
                    TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();
                    if ( strlen( status.achConfName ) > 0  )
                    {
                        TCnAddr tCnAddr;
                        tCnAddr = status.tCalledAddr;
                        tCnAddrList.push_back( tCnAddr );
                    }
                    else
                    {
                        //tEqAddrLst.Add( tp_Alias_e164, m_tCallAddr.achE164 );
                    }

					wRe = ComInterface->StartInstantConf( tCnAddrList );		
					if ( wRe == NO_ERROR )
					{   
						ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
						UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
					}
                }
                else
                {
                    tConfAddrList.m_tEpAdrLst = tAddrList;
                    ComInterface->InviteCns( tConfAddrList ); 
                }
            }
            else
            {	
				wRe = ComInterface->StartInstantConf( tCnAddrList );		
				if ( wRe == NO_ERROR )
				{   
					ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
					UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
				}
            }
        }
	}
	return true;
}


bool CAddrBookLogic::OnBtnRefresh( TNotifyUI& msg )
{
    ICncCommonOp::EnableControl(false,m_pm,_T("BtnRefresh"));
    g_nHandleWaiting = SetTimer( NULL, 0, 8000, CP2PConfTimer); 

    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
    if ( !strCaption.empty() )
    {
        ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtSearch"));
    }

	u16 re = ComInterface->UpdateGlobalAddrbook();	
	if ( re != NO_ERROR )
	{
		return false;
	}
	return true;
}


bool CAddrBookLogic::UpdateLocalAddrBook( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	UpdateLocalAddrList();

	if ( !m_SelGroup.IsNull() )
	{
		UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
	}

	if ( m_bSearchEdit )
	{
        TNotifyUI msg;
		OnSearchEditChange( msg );
	}

	return true;
}

void CAddrBookLogic::UpdateLocalAddrList()
{
	m_vctLocalList.clear();	
	m_vctLocalList = *ComInterface->GetLocalAddrList();

	m_vctEntryList.clear();
	m_vctEntryList = *ComInterface->GetAddrEntryList();

	UpdateShowList();
}


void CAddrBookLogic::UpdateGroupMemberList( u32 dwGroupIndex )
{
    ComInterface->GetAddrGroupMember( dwGroupIndex, m_vctGroupMemberList );

    UpdateShowList();
}


void CAddrBookLogic::UpdateShowList()
{
    if ( m_pAddrList == NULL )
    {
        return;
    }

    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
    if ( strCaption.empty() )
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
    else
    {
        m_vctShowList = m_vctSearchList;
    }

	//获得条件筛选后的条目
	GetOptnShowList( m_vctShowList );

    sort( m_vctShowList.begin(), m_vctShowList.end(), CUIDataMgr::AddrItemCompare );

	m_pAddrList->RemoveAll();
	for ( u16 i = 0; i < m_vctShowList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( strAddrListItem.c_str() );
		//pListContainer->SetUserData();

		TAddrItem tAddrItem = m_vctShowList.at(i); 

		if ( tAddrItem.emItemType == emEntryItem )
		{
			ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achEntryName), m_pm, strAddrName.c_str(), pListContainer );

			ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achE164), m_pm, strAddrE164.c_str(), pListContainer );

            ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achIp), m_pm, _T("AddrIP"), pListContainer );

            if( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) == 0 )
            {
                if ( strcmp( tAddrItem.tAddrInfo.achE164, "" ) == 0 )
                {
                    ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achIp), m_pm, _T("AddrShowText"), pListContainer );
                }
                else
                {
                    ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achE164), m_pm, _T("AddrShowText"), pListContainer );
                }
            }
            else
            {
                ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achEntryName), m_pm, _T("AddrShowText"), pListContainer );
            }

            if ( !tAddrItem.tAddrInfo.bOnLine )
            {
                m_pm->DoCase( _T("caseListOffline"), pListContainer );
            }
            else
            {
                if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeCNS )
                {
                    m_pm->DoCase( _T("caseSipItem"), pListContainer );
                }
            }

            if ( /*tAddrItem.tAddrInfo.bMonitorTer*/1 == tAddrItem.tAddrInfo.byTerType )
            {
                m_pm->DoCase( _T("caseMonitorItem"), pListContainer );
            }
			else if ( 2 == tAddrItem.tAddrInfo.byTerType )
			{
				m_pm->DoCase( _T("caseOrdinaryItem"), pListContainer );
			}
		}
        else
        {
            m_pm->DoCase( _T("caseAddrGroupItem"), pListContainer );
            ICncCommonOp::SetControlText( CA2T(tAddrItem.tGroupInfo.achGroupName), m_pm, _T("AddrShowText"), pListContainer );
        }

        pListContainer->SetTag( (UINT_PTR)&m_vctShowList.at(i) );

        vector<TAddrItem>::iterator itfind = m_vctSelectList.begin();
		while(itfind != m_vctSelectList.end())
		{
			if (itfind->IsSameName(tAddrItem))
			{
				break;
			}
			itfind++;
		}
        if ( itfind != m_vctSelectList.end() )
        {
            CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnAddrSel"), pListContainer );
            if ( pCheckBox != NULL )
            {
                pCheckBox->SetCheck(true);
            }

            pListContainer->SetBkImage( _T("res\\list\\item_sel.png") );
        }

		m_pAddrList->Add(pListContainer);
	}  
}

void CAddrBookLogic::GetOptnShowList( vector<TAddrItem>& vctCurrentList )
{
    if ( m_emAddrShowState == emShowAllAddr )
    {
        return;
    }

    vector<TAddrItem> vctList = vctCurrentList;
    vctCurrentList.clear();
    if ( m_emAddrShowState == emShowOnline )
    {
        for ( u16 i = 0; i < vctList.size(); i++ )
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
    else if ( m_emAddrShowState == emShowOffline )
    {
        for ( u16 i = 0; i < vctList.size(); i++ )
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
    else if ( m_emAddrShowState == emShowGroup )
    {
        for ( u16 i = 0; i < vctList.size(); i++ )
        {
            TAddrItem tAddrItem = vctList.at(i);
            if ( tAddrItem.emItemType == emGroupItem )
            {
                vctCurrentList.push_back( tAddrItem );
            }           
        }
    }
}

bool CAddrBookLogic::OnAddrItemDBClick( TNotifyUI& msg )
{
	if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
	{
		TAddrItem tAddrItem = *(TAddrItem*)pItem->GetTag();

		if ( tAddrItem.emItemType == emGroupItem )//点击组条目，进入组
		{
			m_vctSelectList.clear();
			ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );

			//进入组
			m_SelGroup = tAddrItem.tGroupInfo;
			UpdateGroupMemberList( m_SelGroup.dwGroupIdx );

			UpdateAddrPath();
		}

	}
	return true;
}

bool CAddrBookLogic::OnAddrItemClick( TNotifyUI& msg )
{
	if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
	{
        TAddrItem tAddrItem = *(TAddrItem*)pItem->GetTag();

        if ( !m_vctSelectList.empty() )
        {
            return true;
        }

        if ( tAddrItem.emItemType == emEntryItem )
        {
            m_pm->DoCase( _T("caseItemShowLabel"), msg.pSender );
        }

        int nIndex = pItem->GetIndex();
        if ( m_nSelIndex == -1 )
        {
            m_pm->DoCase( _T("caseListSel"), msg.pSender );
            m_nSelIndex = nIndex;
        }
        else
        {
            if ( m_nSelIndex == nIndex )
            {
                if ( tAddrItem.emItemType == emEntryItem && !tAddrItem.tAddrInfo.bOnLine )
                {
                    m_pm->DoCase( _T("caseListOffline"), msg.pSender );
                }
                else
                {
                    m_pm->DoCase( _T("caseListNoSel"), msg.pSender );
                }               
                m_nSelIndex = -1;
            }
            else
            {
                CControlUI *pLastSel = m_pAddrList->GetItemAt(m_nSelIndex);
                if ( pLastSel != NULL )
                {
                    TAddrItem tLastItem = *(TAddrItem*)pLastSel->GetTag();
                    if ( tLastItem.emItemType == emEntryItem && !tLastItem.tAddrInfo.bOnLine )
                    {
                        m_pm->DoCase( _T("caseListOffline"), pLastSel );
                    }
                    else
                    {
                        m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                    } 

                    if ( m_emSelType == emEntryItem )
                    {
                        m_pm->DoCase( _T("caseItemShowLabel"), pLastSel );
                    }
                }
                m_pm->DoCase( _T("caseListSel"), msg.pSender );
                m_nSelIndex = nIndex;
            }
        }

        if ( tAddrItem.emItemType == emEntryItem )
        {
            m_emSelType = emEntryItem;
        }
        else
        {
            m_emSelType = emGroupItem;
        }

        //else //点击组条目，进入组
        //{
        //    m_vctSelectList.clear();
        //    ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
        //    m_bSearchEdit = FALSE;
 
        //    //进入组
        //    m_SelGroup = tAddrItem.tGroupInfo;
        //    UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
 
        //    UpdateAddrPath();
        //}
        
	}
	return true;
}

bool CAddrBookLogic::OnBtnCnsIsSel(TNotifyUI& msg)
{
    if ( !m_vctSelectList.empty() )
    {
        m_vctSelectList.clear();
        m_pm->DoCase( _T("caseCnsNoSel") );
        ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
        UpdateShowList();
    }

    return true;
}


bool CAddrBookLogic::OnBtnInviteCns(TNotifyUI& msg)
{
	u16 wRe = NO_ERROR;
    if ( m_vctSelectList.empty() )
    {
        /*if ( m_nSelIndex != -1 )
        {
            TTPCallSerInfo tCallSerInfo;
            ComInterface->GetCallServerInfo(tCallSerInfo);
            if ( tCallSerInfo.dwCallServiceIP == 0 )
            {
                ShowMessageBox( _T("呼叫失败：未配置呼叫服务器") );
                return false;
            }

            TTPCnsInfo tCnsInfo;
            ComInterface->GetLocalCnsInfo( tCnsInfo );

            CControlUI *pSelControl = m_pAddrList->GetItemAt(m_nSelIndex);

            TAddrItem tAddrItem = *(TAddrItem*)pSelControl->GetTag();
            TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
            if ( (strlen( tAddrInfo.achEntryName ) > 0 && strcmp( tAddrInfo.achEntryName, tCnsInfo.m_achRoomName ) == 0 ) ||
                (strlen( tAddrInfo.achE164 ) > 0 && strcmp( tAddrInfo.achE164, tCnsInfo.m_achE164 ) == 0 ) )
            {
                ShowMessageBox( _T("不能呼叫本地会场") );
                return false;
            }

            u32 dwIp = 0;
            if ( strlen( tAddrInfo.achIp ) > 0 )
            {
                dwIp = inet_addr( tAddrInfo.achIp );
            }

            TCnAddr tCnAddr;
            tCnAddr.emType = emTpAlias;
            strncpy( tCnAddr.achAlias, tAddrInfo.achEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
            strncpy( tCnAddr.achE164, tAddrInfo.achE164, TP_MAX_ALIAS_LEN_CNC+1 );
            tCnAddr.dwIP = dwIp;
            tCnAddr.bCallByIPAndAlias = tAddrInfo.bMonitorTer;
            u16 wRe = ComInterface->StartP2PConf( tCnAddr );
            if ( wRe == NO_ERROR )
            { 
                ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") ); 
                UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
            }
        }*/
    }
    else
    {
        CString strErr;
        TTPCallSerInfo tCallSerInfo;
        ComInterface->GetCallServerInfo(tCallSerInfo);
        if ( tCallSerInfo.dwCallServiceIP == 0 )
        {
            ShowMessageBox( _T("呼叫失败：未配置呼叫服务器") );
            return false;
        }

        TConfCallEpAddrList tConfAddrList;
        TEpAddrList tAddrList;
        vector<TCnAddr> tCnAddrList;

        TTPCnsInfo tCnsInfo;
        ComInterface->GetLocalCnsInfo( tCnsInfo );

        TCMSConf tConf;
        BOOL32 bInconf = ComInterface->IsInConf( &tConf );
        if ( bInconf  )
        {
            tConfAddrList.m_wConfID = tConf.m_wConfID;
            if ( tConf.m_emConfType == emCallType_P2P )
            {
                TTpCallAddr tCallAddr;
                tCallAddr.m_tAlias.SetAlias( tp_Alias_h323, tCnsInfo.m_achRoomName );
                tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tCnsInfo.m_achE164 );
//                 switch (tCnsInfo.byTerType)
//                 {
//                 case 1://监控终端
//                 case 2://普通终端
//                     tCallAddr.m_emTpConfProtocol = emTpH323;
//                     break;
//                 default://网呈终端 和 其它
//                     tCallAddr.m_emTpConfProtocol = emTpSIP;
//                     break;
//                 }
                tAddrList.Add( tCallAddr );

                TCnAddr tCnAddr;
                tCnAddr.emType = emTpAlias;
                strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
                strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
//                 switch (tCnsInfo.byTerType)
//                 {
//                 case 1://监控终端
//                 case 2://普通终端
//                     tCnAddr.emTpConfProtocol = emTpH323;
//                     break;
//                 default://网呈终端 和 其它
//                     tCnAddr.emTpConfProtocol = emTpSIP;
//                     break;
//                 }
                tCnAddrList.push_back( tCnAddr );
            }
        }
        else
        {	
            if ( m_vctSelectList.size() == 1 )
            {
                TAddrItem tItem = m_vctSelectList.at(0);
                TAddrInfo tAddrInfo = tItem.tAddrInfo;
                if ( (strlen( tAddrInfo.achEntryName ) > 0 && strcmp( tAddrInfo.achEntryName, tCnsInfo.m_achRoomName ) == 0 ) ||
                    (strlen( tAddrInfo.achE164 ) > 0 && strcmp( tAddrInfo.achE164, tCnsInfo.m_achE164 ) == 0 ) )
                {
                    ShowMessageBox( _T("不能呼叫本地会场") );
                    return false;
                }

                u32 dwIp = 0;
                if ( strlen( tAddrInfo.achIp ) > 0 )
                {
                    dwIp = inet_addr( tAddrInfo.achIp );
                }

                TCnAddr tCnAddr;
                tCnAddr.emType = emTpAlias;
                strncpy( tCnAddr.achAlias, tAddrInfo.achEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
                strncpy( tCnAddr.achE164, tAddrInfo.achE164, TP_MAX_ALIAS_LEN_CNC+1 );
                tCnAddr.dwIP = dwIp;
                //tCnAddr.bCallByIPAndAlias = tAddrInfo.bMonitorTer;
				tCnAddr.bCallByIPAndAlias = (1 == tAddrInfo.byTerType);
                switch (tAddrInfo.byTerType)
                {
                case 1://监控终端
                case 2://普通终端
                    tCnAddr.emTpConfProtocol = emTpH323;
                    break;
                default://网呈终端 和 其它
                    tCnAddr.emTpConfProtocol = emTpSIP;
                    break;
                }
                wRe = ComInterface->StartP2PConf( tCnAddr );
                if ( wRe == NO_ERROR )
                { 
                    ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") ); 
                    UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
                }
                return true;
            }


            //TTpCallAddr tCallAddr;
            //tCallAddr.m_tAlias.SetAlias( tp_Alias_h323, tCnsInfo.m_achRoomName );
            //tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tCnsInfo.m_achE164 );
            //tAddrList.Add( tCallAddr );

            TCnAddr tCnAddr;
            tCnAddr.emType = emTpAlias;
            strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
            strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
//             switch (tCnsInfo.byTerType)
//             {
//             case 1://监控终端
//             case 2://普通终端
//                 tCnAddr.emTpConfProtocol = emTpH323;
//                 break;
//             default://网呈终端 和 其它
//                 tCnAddr.emTpConfProtocol = emTpSIP;
//                 break;
//             }
            tCnAddrList.push_back( tCnAddr );
        }

        for ( u16 nIndex = 0; nIndex < m_vctSelectList.size(); nIndex++ )
        {
            TAddrItem tItem = m_vctSelectList.at(nIndex);

            TTpCallAddr tCallAddr;
            TCnAddr tCnAddr;
            if( tItem.emItemType == emEntryItem )
            {						
                EmConfAddEpRet emRet = TP_ConfAddEpRet_Unknow;	

                u32 dwIp = 0;
                if ( strlen( tItem.tAddrInfo.achIp ) > 0 )
                {
                    dwIp = inet_addr( tItem.tAddrInfo.achIp );
                }

                if ( strlen( tItem.tAddrInfo.achE164 ) > 0 )
                {
                    if( strcmp( tItem.tAddrInfo.achE164, tCnsInfo.m_achE164 ) == 0 )
                    {
                        continue;
                    }

                    tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  tItem.tAddrInfo.achEntryName );
                    tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tItem.tAddrInfo.achE164 );
                    tCallAddr.m_dwIP = dwIp;
                    switch (tItem.tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCallAddr.m_emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCallAddr.m_emTpConfProtocol = emTpSIP;
                        break;
                    }
                    emRet = tAddrList.Add( tCallAddr );

                    tCnAddr.emType = emTpE164Num;
                    strncpy( tCnAddr.achAlias, tItem.tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tItem.tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddr.dwIP = dwIp;
                    //tCnAddr.bCallByIPAndAlias = tItem.tAddrInfo.bMonitorTer;
					tCnAddr.bCallByIPAndAlias = (1 == tItem.tAddrInfo.byTerType);
                    switch (tItem.tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCnAddr.emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCnAddr.emTpConfProtocol = emTpSIP;
                        break;
                    }
                    tCnAddrList.push_back( tCnAddr );
                }
                else
                {
                    if ( strcmp( tItem.tAddrInfo.achEntryName, tCnsInfo.m_achRoomName ) == 0  ) 
                    {
                        continue;
                    }

                    if ( bInconf && tConf.IsCnsInConf( tItem.tAddrInfo.achEntryName ) )
                    {				
                        //strErr.Format( "会场 %s 已在本会议中", tItem.tAddrInfo.achEntryName );
                        //ShowPopMsg( strErr );
                        continue;
                    }

                    tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  tItem.tAddrInfo.achEntryName );
                    tCallAddr.m_tE164.SetAlias( tp_Alias_e164, tItem.tAddrInfo.achE164 );
                    tCallAddr.m_dwIP = dwIp;
                    switch (tItem.tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCallAddr.m_emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCallAddr.m_emTpConfProtocol = emTpSIP;
                        break;
                    }
                    emRet = tAddrList.Add( tCallAddr );

                    tCnAddr.emType = emTpAlias;
                    strncpy( tCnAddr.achAlias, tItem.tAddrInfo.achEntryName, TP_MAX_H323ALIAS_LEN+1 );
                    strncpy( tCnAddr.achE164, tItem.tAddrInfo.achE164, TP_MAX_H323ALIAS_LEN+1 );
                    tCnAddr.dwIP = dwIp;
                    //tCnAddr.bCallByIPAndAlias = tItem.tAddrInfo.bMonitorTer;
					tCnAddr.bCallByIPAndAlias = (1 == tItem.tAddrInfo.byTerType);
                    switch (tItem.tAddrInfo.byTerType)
                    {
                    case 1://监控终端
                    case 2://普通终端
                        tCnAddr.emTpConfProtocol = emTpH323;
                        break;
                    default://网呈终端 和 其它
                        tCnAddr.emTpConfProtocol = emTpSIP;
                        break;
                    }
                    tCnAddrList.push_back( tCnAddr );
                }
                if ( emRet != TP_ConfAddEpRet_Success )
                {
                    if ( emRet == TP_ConfAddEpRet_MaxNum )
                    {
                        //strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
                        //ShowPopMsg( strErr );
                        break;
                    }
                    continue;
                }
                if ( tCnAddrList.size() == TP_CONF_MAX_EPNUM )
                {
                    //strErr.Format( "会场达到最大呼叫数量: %d个", TP_CONF_MAX_EPNUM );
                    //ShowPopMsg( strErr );
                    break;
                }
            }
        }

        if ( bInconf )
        {
            if ( tConf.m_emConfType == emCallType_P2P )
            {
                //点对点会议变多点会议,添加点对点会议对端会场
                TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();
                if ( strlen( status.achConfName ) > 0  )
                {
                    TCnAddr tCnAddr;
                    tCnAddr = status.tCalledAddr;
                    tCnAddrList.push_back( tCnAddr );
                }
                else
                {
                    //tEqAddrLst.Add( tp_Alias_e164, m_tCallAddr.achE164 );
                }

				wRe = ComInterface->StartInstantConf( tCnAddrList );		
				if ( wRe == NO_ERROR )
				{   
					ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
					UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
				}
            }
            else
            {
                tConfAddrList.m_tEpAdrLst = tAddrList;
                ComInterface->InviteCns( tConfAddrList ); 
            }
        }
        else
        {	
			wRe = ComInterface->StartInstantConf( tCnAddrList );		
			if ( wRe == NO_ERROR )
			{   
				ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
				UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
			}
        }
    }
    
    return true;
}

bool CAddrBookLogic::OnBtnAddrMainPath(TNotifyUI& msg)
{
    if ( !m_SelGroup.IsNull() )
    {
        m_SelGroup.SetNull();
        m_vctGroupPath.clear();

        if ( !m_vctSelectList.empty() )
        {
            m_vctSelectList.clear();
            m_pm->DoCase( _T("caseCnsNoSel") );
            ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
        }
        
        UpdateShowList();
        UpdateAddrPath();
    }
    
    return true;
}

bool CAddrBookLogic::OnBtnGroupPath1(TNotifyUI& msg)
{
    /*TGroupInfo tGroupInfo = *(TGroupInfo*)msg.pSender->GetTag();
    if( tGroupInfo == m_SelGroup )
    {
        return true;
    }
    else
    {
        m_SelGroup = tGroupInfo;
        UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
        UpdateShowList();
        m_pm->DoCase( _T("caseGroupPath1") );
    }*/
    CString str = msg.pSender->GetUserData();
    int nIndex = _ttoi(str);
    if( nIndex == m_SelGroup.dwGroupIdx )
    {
        return true;
    }
    else
    {
        CAddrBook cAddrBook = ComInterface->GetAddrBook();
        CAddrMultiSetEntry cAddrGroup;
        s8 aszGroupName[MAX_NAME_LEN + 1] = {0};     //组名称
        cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, nIndex );

        cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );

        TGroupInfo tGroupInfo;
        tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
        strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
        tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();

        m_SelGroup = tGroupInfo;
        UpdateGroupMemberList( m_SelGroup.dwGroupIdx );
        UpdateShowList();
        m_pm->DoCase( _T("caseGroupPath1") );

        while( m_vctGroupPath.size() > 1 )
        {
            m_vctGroupPath.pop_back();
        }
    }

    return true;
}


void CAddrBookLogic::UpdateAddrPath()
{
    if ( m_SelGroup.IsNull() )
    {
        m_pm->DoCase( _T("caseAddrMainPath") );
        m_vctGroupPath.clear();
    }
    else
    {
        //CString strLabName;
        CString strBtnName;
        CString strCaseName;

        m_vctGroupPath.push_back( m_SelGroup );
        int nSize = m_vctGroupPath.size();

        //strLabName.Format( _T("txtGroupPath%d"), nSize );
        //ICncCommonOp::SetControlText( CA2T(m_SelGroup.achGroupName), m_pm, strLabName );
		strBtnName.Format( _T("BtnGroupPath%d"), nSize );
		ICncCommonOp::SetControlText( CA2T(m_SelGroup.achGroupName), m_pm, strBtnName );
		CButtonUI* pButton = (CButtonUI*)ICncCommonOp::FindControl( m_pm, strBtnName );
        //CLabelUI* pLabel = (CLabelUI*)ICncCommonOp::FindControl( m_pm, strLabName );
        if ( pButton != NULL )
        {
            TFontInfo* pfont = pButton->GetFontInfo();

            Gdiplus::Font font( pfont->sFontName, pfont->iSize, FontStyleRegular );
            CString strName = CA2T(m_SelGroup.achGroupName);
            BSTR bstrText = strName.AllocSysString();
            // 计算当前文字的长度
            CSize cSize(0,0);
            UIDATAMGR->GetCharExtent( bstrText, &font, cSize );
            pButton->SetFixedWidthDirect( cSize.cx + 50 );

            CString strPathName;
            strPathName.Format( _T("LayoutGroupPath%d"), nSize );            
            CControlUI* pPath = ICncCommonOp::FindControl( m_pm, strPathName );
			if ( pPath != NULL )
			{
				pPath->SetFixedWidthDirect( 100 + cSize.cx );
			}

            SysFreeString( bstrText ); 
        }      

        //strBtnName.Format( _T("BtnGroupPath%d"), nSize );
        //CControlUI* pButton = ICncCommonOp::FindControl( m_pm, strBtnName );
        //pButton->SetTag( (UINT_PTR)&m_vctGroupPath.at(nSize-1) );
        CString strIndex;
        strIndex.Format( _T("%d"), m_SelGroup.dwGroupIdx );
		if (pButton)
		{
			pButton->SetUserData( strIndex );
		}
        
        strCaseName.Format( _T("caseGroupPath%d"), nSize );
        m_pm->DoCase( strCaseName );
    }
}


bool CAddrBookLogic::OnComboShowEx( TNotifyUI& msg )
{
    int nSel = msg.wParam;

    if ( nSel == 0 )
    {
        m_emAddrShowState = emShowAllAddr;
        UpdateShowList();
    }
    else if ( nSel == 1 )
    {
        m_emAddrShowState = emShowGroup;
        UpdateShowList();
    }
    else if ( nSel == 2 )
    {
        m_emAddrShowState = emShowOnline;
        UpdateShowList();
    }
    else if ( nSel == 3 )
    {
        m_emAddrShowState = emShowOffline;
        UpdateShowList();
    }
    return true;
}


bool CAddrBookLogic::OnSearchEditChange( TNotifyUI& msg )
{
    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
	if ( strCaption.empty() )
	{
		m_bSearchEdit = FALSE;
		UpdateShowList();

		return false;
	}

	m_bSearchEdit = TRUE;
	CString strSearchName;
	strSearchName.Format( _T("%s"), strCaption.c_str() );

	m_vctSearchList.clear();

	vector<TAddrItem> vctShowList;

	if ( m_SelGroup.IsNull() )
	{
		vctShowList = m_vctLocalList;
	}
	else
	{
		vctShowList = m_vctGroupMemberList;
	}

	for ( u16 i = 0; i < vctShowList.size(); i++ )
	{
		BOOL bMatchNum = FALSE;
		CString strItemName;
		TAddrItem tAddrItem = vctShowList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			//名称为空用E164号匹配
			if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) == 0 )
			{
                if ( strcmp( tAddrItem.tAddrInfo.achE164, "" ) == 0 )
                {
                    strItemName.Format( _T("%s"), CA2T(tAddrItem.tAddrInfo.achIp) );
                }
                else
                {
				    strItemName = tAddrItem.tAddrInfo.achE164;
                    bMatchNum = TRUE;
                }
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
		BOOL bFind = FALSE;			
		bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
		if ( bFind )
		{		
			m_vctSearchList.push_back( tAddrItem );
		}
		else if ( bMatchNum )
		{
            //名字没有匹配到
            if ( strcmp( tAddrItem.tAddrInfo.achE164, "" ) != 0 )
            {
                strItemName = tAddrItem.tAddrInfo.achE164;
                bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
                if ( bFind )
                {		
                    m_vctSearchList.push_back( tAddrItem );
                }
            }
            if ( !bFind )
            {
                if ( strcmp( tAddrItem.tAddrInfo.achIp, "" ) != 0 ) 
                {
                    strItemName.Format( _T("%s"), CA2T(tAddrItem.tAddrInfo.achIp) );
                    bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
                    if ( bFind )
                    {		
                        m_vctSearchList.push_back( tAddrItem );
                    }
                }
            }
		}
	}

	UpdateShowList();

	return true;
}


bool CAddrBookLogic::OnBtnAddrInviteOther( TNotifyUI& msg )
{
    EmTpConfProtocol emProtocol = emTpSIP; //会场类型 0-网呈会场 1-监控会场 2-普通终端
    COptionUI* pOptMonitor = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opMonitorTer"));
    COptionUI* pOptOrdinary = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opOrdinaryTer"));
    if ((pOptMonitor != NULL && pOptMonitor->IsSelected()) || (pOptOrdinary != NULL && pOptOrdinary->IsSelected()))
    {
        emProtocol = emTpH323;
    }

    tstring strAddrName = ICncCommonOp::GetControlText( m_pm, _T("EditName") );  

    tstring strAddrE164 = ICncCommonOp::GetControlText( m_pm, _T("EditE164") );

    tstring strAddrIp = ICncCommonOp::GetControlText( m_pm, _T("EditIP") );

    //监控终端输入内容判断
    if ((pOptMonitor != NULL && pOptMonitor->IsSelected()))
    {
        if (strAddrIp.empty() == true)
        {
            ShowMessageBox( _T("监控终端IP不可为空") );
            return false;
        }
        else if (strAddrName.empty() == true && strAddrE164.empty() == true)
        {
            ShowMessageBox( _T("监控终端别名和E164号不可同时为空") );
            return false;
        }
    }

    if ( strAddrName.empty() && strAddrE164.empty() && strAddrIp.empty() )
    {
        ShowMessageBox( _T("会场名称、号码和IP不能全为空") );
        return false;
    }

    if ( !strAddrName.empty() )
    {
        if ( UIDATAMGR->IsAllE164Number( strAddrName ) )
        {
            ShowMessageBox( _T("会场名称不能全为数字及*,号") );
            return false;
        }
        if ( !UIDATAMGR->IsValidTPStr( strAddrName ) )
        {   
            CString str; 
            str.Format( _T("会场名称不可以包含空格及括号中的任意字符 [ %s ]"), INVALID_ALIAS_FOR_SHOW );
            ShowMessageBox( str );
            return false;
        }
    }

    CString cstrE164;
    cstrE164.Format( _T("%s"), strAddrE164.c_str() );

    if ( !cstrE164.IsEmpty() && !CCallAddr::IsValidE164((CT2A)cstrE164))
    {
        ShowMessageBox( _T("会场号码不合法，E164号只能包含数字及*,号") ); 
        return false;
    }

    u32 dwIp = 0;
    if( !strAddrIp.empty() )
    {
        dwIp = ntohl( inet_addr( CT2A(strAddrIp.c_str()) ) );

        if ( !CCallAddr::IsValidIpV4(CT2A(strAddrIp.c_str())) )
        {
            ShowMessageBox((_T("IP地址非法")),false);
            return false;
        }    

        dwIp = inet_addr( CT2A(strAddrIp.c_str()) );
    } 

    vector<TCnAddr> tCnAddrList;

	u16 wRe = NO_ERROR;
    TCMSConf tConf;
    BOOL32 bInconf = ComInterface->IsInConf( &tConf );
    if ( bInconf  )
    {
        if ( tConf.m_emConfType == emCallType_P2P )
        {
            TTPCnsInfo tCnsInfo;
            ComInterface->GetLocalCnsInfo( tCnsInfo );

            TCnAddr tCnAddr;
            tCnAddr.emType = emTpAlias;
            strncpy( tCnAddr.achAlias, tCnsInfo.m_achRoomName, TP_MAX_H323ALIAS_LEN+1 );
            strncpy( tCnAddr.achE164, tCnsInfo.m_achE164, TP_MAX_H323ALIAS_LEN+1 );
            tCnAddr.emTpConfProtocol = emProtocol;
            tCnAddrList.push_back( tCnAddr );

            //点对点会议变多点会议,添加点对点会议对端会场
            TTPCnsConfStatus status = ComInterface->GetLocalCnsConfState();
            if ( strlen( status.achConfName ) > 0  )
            {
                TCnAddr tCnAdd;
                tCnAdd = status.tCalledAddr;
                tCnAdd.emTpConfProtocol = emProtocol;
                tCnAddrList.push_back( tCnAdd );
            }

            if ( !strAddrE164.empty() )
            {
                TCnAddr tCnAddr;
                tCnAddr.emType = emTpE164Num;
                strncpy( tCnAddr.achAlias, CT2A(strAddrName.c_str()), TP_MAX_H323ALIAS_LEN+1 );
                strncpy( tCnAddr.achE164, CT2A(strAddrE164.c_str()), TP_MAX_H323ALIAS_LEN+1 );
                tCnAddr.dwIP = dwIp;
                tCnAddr.emTpConfProtocol = emProtocol;
                tCnAddrList.push_back( tCnAddr );
            }
            else
            {
                tCnAddr.emType = emTpAlias;
                strncpy( tCnAddr.achAlias, CT2A(strAddrName.c_str()), TP_MAX_H323ALIAS_LEN+1 );
                strncpy( tCnAddr.achE164, CT2A(strAddrE164.c_str()), TP_MAX_H323ALIAS_LEN+1 );
                tCnAddr.dwIP = dwIp;
                tCnAddr.emTpConfProtocol = emProtocol;
                tCnAddrList.push_back( tCnAddr );
            }

			wRe = ComInterface->StartInstantConf( tCnAddrList );		
			if ( wRe == NO_ERROR )
			{   
				ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
				UIDATAMGR->setLocalCnsState(emLocalCnsCalling);
			}
        }
        else
        {
            TTpCallAddr tCallAddr;
            if ( !strAddrE164.empty() )
            {
                tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  CT2A(strAddrName.c_str()) );
                tCallAddr.m_tE164.SetAlias( tp_Alias_e164, CT2A(strAddrE164.c_str()) );
                tCallAddr.m_dwIP = dwIp;
                tCallAddr.m_emTpConfProtocol = emProtocol;
            }
            else
            {
                tCallAddr.m_tAlias.SetAlias( tp_Alias_h323,  CT2A(strAddrName.c_str()) );
                tCallAddr.m_tE164.SetAlias( tp_Alias_e164, CT2A(strAddrE164.c_str()) );
                tCallAddr.m_dwIP = dwIp;
                tCallAddr.m_emTpConfProtocol = emProtocol;
            }

            ComInterface->InviteCns( tCallAddr );
        }
    }

    CPaintManagerUI* pm = CMainFrameLogic::GetSingletonPtr()->GetPaintManagerUI();
    COptionUI *pOption = (COptionUI*)ICncCommonOp::FindControl( pm, _T("titleTabLeft") );
    if (pOption)
    {
        pOption->Selected( true );
    }

	//清空填入信息
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EditName") );  
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EditE164") );
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EditIP") );
    return true;
}



bool CAddrBookLogic::OnBtnNoticeBack(TNotifyUI& msg)
{
    ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	ICncCommonOp::SetControlText( _T("正在呼叫.."), m_pm, _T("LabelTip") );

    if ( m_vctSelectList.size() > 0 )
    {
        m_vctSelectList.clear();
        m_pm->DoCase( _T("caseCnsNoSel") );
        ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
        UpdateShowList();
    }

    return true;
}

bool CAddrBookLogic::OnConfStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
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

        if ( emLocalCnsCalling == emState )
        {   
            ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") ); // 隐藏呼叫动画界面
            ICncCommonOp::SetControlText( _T("正在呼叫.."), m_pm, _T("LabelTip") );
            WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAddrbookDlg.c_str(), false );
            if ( m_vctSelectList.size() > 0 )
            {
                m_vctSelectList.clear();
                m_pm->DoCase( _T("caseCnsNoSel") );
                ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
                UpdateShowList();
            }
			
			if (UIDATAMGR->GetCurShowWndName() == g_strAddrbookDlg)
			{
				WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
				UIDATAMGR->SetCurShowWndName( _T("") );
			}

			if (UIDATAMGR->GetCurShowWndName() == g_strInviteCnsDlg)
			{
				WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
				UIDATAMGR->SetCurShowWndName( _T("") );
				CMainFrameLogic::GetSingletonPtr()->SetTitleTab( false, g_strInviteCnsDlg.c_str() );
			}

            UIDATAMGR->setLocalCnsState( emLocalCnsConnected );
			if (g_nCallingP2PHandle != 0)
			{
				::KillTimer( NULL, g_nCallingP2PHandle );
                g_nCallingP2PHandle = 0;
			}
        }

        if ( emLocalCnsIdle == emState )
        {   //在地址簿界面空闲时入会，也隐藏地址簿界面
            String strAddrWnd = UIDATAMGR->GetCurShowWndName();
            if ( strAddrWnd == g_strAddrbookDlg )
            {
                WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAddrbookDlg.c_str(), false );

				if (UIDATAMGR->GetCurShowWndName() == g_strAddrbookDlg)
				{
					WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
					UIDATAMGR->SetCurShowWndName( _T("") );
				}	

				if (UIDATAMGR->GetCurShowWndName() == g_strInviteCnsDlg)
				{
					WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
					UIDATAMGR->SetCurShowWndName( _T("") );
					CMainFrameLogic::GetSingletonPtr()->SetTitleTab( false, g_strInviteCnsDlg.c_str() );
				}
            }
        }       
    } 
    return true;
}


bool CAddrBookLogic::OnHungupConfInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    EmCnsCallReason emRe = (EmCnsCallReason)wParam;
    CString strErr = _T("");
    switch ( emRe )
    { 
    case EmCnsCallReason_success:
        strErr = _T("");
        break;
    case EmCnsCallReason_hungup://本地挂断
        strErr = _T("对端挂断");
        break;
    case EmCnsCallReason_Unreachable:
        strErr = _T("对端不可达");
        break;
    case EmCnsCallReason_resourcefull:
        strErr = _T("已达到会场最大接入数");
        break;
    case EmCnsCallReason_dstnotfind:
        strErr = _T("对端不存在");
        break;
    case EmCnsCallReason_Busy:
        strErr = _T("对端忙");
        break;
    case EmCnsCallReason_Local:
        strErr = _T("本地原因");
        break;
    case EmCnsCallReason_Rejected:		//对端拒绝
        strErr = _T("对端拒绝");
        break;
    case EmCnsCallReason_peerhungup:	//对端挂断
        strErr = _T("会议结束：对端挂断");
        break;
    // 	case EmCnsCallReason_Abnormal:  会有“本地会场掉线”的提示，本条不应提示出来
    // 		strErr = ": 本端不在线";
    // 		break;
    case EmCnsCallReason_PeerAbnormal:
        strErr = _T("对端不可达");
        break;
    case EmCnsCallReason_ConfOver:	//会议结束
        strErr = _T("会议结束"); 
        break;
    case EmCnsCallReason_cncallexception:
        strErr = _T("接入模块掉线");
        break;
    case EmCnsCallReason_ConfExist:		//会议已存在
        strErr = _T("会议已存在");
        break; 
    case EmCnsCallReason_StreamEncryptKeyNotEqual:
        strErr = "";
        break;
    case EmCnsCallReason_unknown:
        strErr = _T("呼叫失败");             //未知错误不做提示 
        break;
    default:
        strErr = _T("呼叫失败");
        break; 
    }

    TCMSConf tConfInfo;
    BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
    if ( bInConf )
    {   		
        if ( !strErr.IsEmpty() )
        {   
            if ( tConfInfo.m_emConfType == emCallType_Conf && emRe == EmCnsCallReason_peerhungup )
            {
                strErr = _T("对端挂断");
            }
            ShowPopMsg( strErr ); 
        }  
    } 
    else
    { 
        //不在会议中收到此消息，说明是点对点呼叫失败
        TTPCnsConfStatus tConfStatus = ComInterface->GetLocalCnsConfState();		
        if ( !strErr.IsEmpty() && tConfStatus.emState != em_CALL_CONNECTED )
        {
            ShowPopMsg( _T("呼叫失败：") + strErr );

            //失败时不隐藏
            /*EMLocalCnsState emState = UIDATAMGR->GetLocalCnsState();
            if (  emLocalCnsCalling == emState )
            {   
                ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") ); // 隐藏呼叫动画界面 
                ICncCommonOp::SetControlText( _T("正在呼叫.."), m_pm, _T("LabelTip") );

                if ( m_vctSelectList.size() > 0 )
                {
                    m_vctSelectList.clear();
                    m_pm->DoCase( _T("caseCnsNoSel") );
                    ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
                    UpdateShowList();
                }
            }*/
        } 
    }

    UIDATAMGR->setLocalCnsState(emLocalCnsIdle);

    CLabelUI* pLable = (CLabelUI*)ICncCommonOp::FindControl(m_pm, _T("LabelTip"));
    if (pLable && pLable->IsVisible())
    {
        ICncCommonOp::SetControlText( strErr, m_pm, _T("LabelTip") );
    }

	if (g_nCallingP2PHandle != 0)
	{
		::KillTimer( NULL, g_nCallingP2PHandle );
		g_nCallingP2PHandle = 0;	
	}

    return true;
}

void CAddrBookLogic::OnWaitRefreshOverTime()
{
    ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));
}


bool CAddrBookLogic::OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    m_nSelIndex = -1;
    m_bSearchEdit = FALSE;
    m_vctLocalList.clear();
    m_vctGroupMemberList.clear();
    m_vctSearchList.clear();
    m_vctSelectList.clear();
    m_vctShowList.clear();
    m_vctGroupPath.clear();
    m_SelGroup.SetNull();
    m_pm->DoCase( _T("caseAddrMainPath") );
    ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
    ICncCommonOp::SetControlText( _T("正在呼叫.."), m_pm, _T("LabelTip") );
    ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
    ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));

    m_pm->DoCase( _T("caseCnsNoSel") );
    ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
    
    if ( m_pAddrList != NULL )
    {
        m_pAddrList->RemoveAll();
    }

	CComboBoxUI *pCombo = (CComboBoxUI*)ICncCommonOp::FindControl(m_pm,_T("ComboAddrShowEx"));
	if (pCombo)
	{
		pCombo->SelectItem(0);
	}
    return true;
}

void CAddrBookLogic::P2PCallFail()
{
	CLabelUI* pLable = (CLabelUI*)ICncCommonOp::FindControl(m_pm, _T("LabelTip"));
	if (pLable && pLable->IsVisible())
	{
		ICncCommonOp::SetControlText( _T("会议开启失败，请稍后再试"), m_pm, _T("LabelTip") );
	}

	ShowPopMsg(_T("会议开启失败，请稍后再试"));
}

bool CAddrBookLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("AddrList"));
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
	int nItemCount = m_vctShowList.size();

	//解决条目过多时，点击字母会卡的问题 ，使用二分法
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //置当前查找区间上、下界的初值 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//当前查找区间R[low..high]非空 
		swMidIndex =( swLowIndex + swHighIndex )/2; 
		if ( nMidIndex == swMidIndex )
		{
			break;
		}

		CString strLetter = _T("");
		//s8     achNameLetter[TP_MAX_ALIAS_LEN_CNC+1] = {0};	
		//memcpy(achNameLetter,CT2A(m_vctShowList.at(swMidIndex).strNameLetter),m_vctShowList.at(swMidIndex).strNameLetter.GetLength()); 
		//UIDATAMGR->GetFirstLetter( achNameLetter, strLetter ); 

        strLetter = m_vctShowList.at(swMidIndex).strNameLetter;

		int nRe = strIndex.Compare( strLetter );
		if(  nRe == 0 )  
		{        
			break;   
		} 
		else if ( nRe < 0 )
		{   
			swHighIndex = swMidIndex;  //当前查找区间R[low..mid]  
		}
		else
		{   
			swLowIndex = swMidIndex + 1;//当前查找区间R[mid..heith] 
		}						 

	} 

	//swLowIndex与swHighIndex相等时，跟swMidIndex比较
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

	//取swLowIndex和swHighIndex中第一个比strIndex大的返回
	if ( swLowIndex > swHighIndex )
	{
		CString strLetter = _T("");
		//s8     achNameLetter[TP_MAX_ALIAS_LEN_CNC+1] = {0};	
		//memcpy(achNameLetter,CT2A(m_vctShowList.at(swMidIndex).strNameLetter),m_vctShowList.at(swMidIndex).strNameLetter.GetLength()); 
		//UIDATAMGR->GetFirstLetter( achNameLetter, strLetter ); 
        strLetter = m_vctShowList.at(swMidIndex).strNameLetter;

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


bool CAddrBookLogic::OnBtnAddrConfig(TNotifyUI& msg)
{
    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    UIDATAMGR->SetCurAddrWndName( strCurWnd );

    WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strAddrEditDlg.c_str() );

    CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("地址簿管理"));
    CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgAddrbook.png"));
    CMainFrameLogic::GetSingletonPtr()->SetTitleTab( true, g_strAddrEditDlg.c_str() );
    WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(), _T("caseShowSubPage") );
    UIDATAMGR->SetCurShowWndName( g_strAddrEditDlg );

    //刷新
    CAddrEditLogic::GetSingletonPtr()->UpdateTouchlist();

    return true;
}

bool CAddrBookLogic::OnUpdateGlobalAddrBook(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));
    if (g_nHandleWaiting != 0)
    {
        ::KillTimer( NULL, g_nHandleWaiting );
		g_nHandleWaiting = 0;
    }
    return true;
}

 bool CAddrBookLogic::OnAddrBookModify(WPARAM wParam, LPARAM lParam, bool& bHandle)
 {
     BOOL bEntry = (BOOL)wParam;
     if (bEntry)
     {
         CAddrBook cAddrBook = ComInterface->GetAddrBook();
         CAddrEntry cEntry;
         cAddrBook.GetAddrEntry( &cEntry, (u32)lParam );
         TAddrInfo tAddrInfo;
         ComInterface->SetAddrItemInfo( tAddrInfo, cEntry );

         vector<TAddrItem>::iterator itSel = m_vctSelectList.begin();
         for ( ; itSel != m_vctSelectList.end() ; itSel++ )
         {
             if (itSel->tAddrInfo.dwEntryIdx == (u32)lParam)
             {
                 itSel->tAddrInfo = tAddrInfo;
                 break;
             }
         }
     }
     
     return true;
 }

 bool CAddrBookLogic::OnAddrBookDelete(WPARAM wParam, LPARAM lParam, bool& bHandle)
 {
     BOOL bEntry = (BOOL)wParam;
     if (bEntry)
     {
         vector<TAddrItem>::iterator itSel = m_vctSelectList.begin();
         for ( ; itSel != m_vctSelectList.end() ; itSel++ )
         {
             if (itSel->tAddrInfo.dwEntryIdx == (u32)lParam)
             {
                 itSel = m_vctSelectList.erase(itSel);
                 break;
             }
         }
         if ( m_vctSelectList.empty() )
         {
             m_pm->DoCase( _T("caseCnsNoSel") );
             ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
         }
         else
         {
             m_pm->DoCase( _T("caseCnsHasSel") );
             CString str = _T("");
             str.Format(_T("(%d)"), m_vctSelectList.size());
             ICncCommonOp::SetControlText(str, m_pm, _T("labSelCount"));
         }
     }
     return true;
 }

bool CAddrBookLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}