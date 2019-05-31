#include "StdAfx.h"
#include "addreditlogic.h"
#include "confmsglogic.h"

template<> CAddrEditLogic* Singleton<CAddrEditLogic>::ms_pSingleton  = NULL;

static UINT g_nTmHandleWaiting;
static UINT g_nTmHandleRefresh = 0;

APP_BEGIN_MSG_MAP(CAddrEditLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("AddrEditSlideTab"), OnCreate)
	MSG_INIWINDOW(_T("AddrEditSlideTab"), OnInit)

    MSG_ITEMSELECTD(_T("ComboAddrShowEx"), OnComboShowEx)
	MSG_ITEMSELECTD(_T("ComboMore"), OnComboMore)

	MSG_ITEMDOWN(_T("AddrListItem"), OnAddrItemClick)
	//MSG_ITEMDBLCLICK(_T("AddrListItem"), OnAddrItemDBClick)
    MSG_CLICK(_T("imgAddrLabel"), OnBtnAddrLabel)
    
	MSG_SELECTCHANGE(_T("BtnAddrSel"), OnCheckAddrItem)
    MSG_CLICK(_T("BtnAddrCall"), OnBtnAddrCfg)

	MSG_CLICK(_T("BtnAddrCancle"), OnBtnCancelAddr)
	MSG_CLICK(_T("BtnAddrOK"), OnBtnSaveAddr)
   
    MSG_CLICK(_T("BtnAllSel"), OnBtnSelectAll)
	MSG_CLICK(_T("BtnCopy"), OnBtnCopy)
	MSG_CLICK(_T("BtnCut"), OnBtnCut)
	MSG_CLICK(_T("BtnDelete"), OnBtnDelete)
    MSG_CLICK(_T("BtnCnsIsSel"), OnBtnCnsIsSel)
    MSG_CLICK(_T("BtnAddrMainPath"), OnBtnAddrMainPath)   
    MSG_CLICK(_T("BtnGroupPath1"), OnBtnGroupPath1)

    MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)
    MSG_EDITCHANGE(_T("EdtSearch2"), OnOnlineSearchEditChange)  
   
    MSG_CLICK(_T("BtnOnlineAllSel"), OnBtnOnlineAllSel)
    MSG_CLICK(_T("BtnRefresh"), OnRefreshAddr)
    MSG_CLICK(_T("BtnLoadToLocal"), OnBtnLoadToLocal)
    MSG_CLICK(_T("BtnOnlineCnsIsSel"), OnBtnOnlineCnsIsSel)   

	USER_MSG( UI_CNS_ADDRBOOK_CHANGED, UpdateLocalAddrBook )
    USER_MSG( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, UpdateGlobalAddrBook )
    USER_MSG( UI_CNS_ADDRBOOK_ADDENTRY, OnAddEntryNty )
    USER_MSG( UI_CNS_ADDRBOOK_ADDGROUP, OnAddGroupNty )
    USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

    USER_MSG(UI_CNS_ADDRBOOK_MODIFY, OnAddrBookModify)
    USER_MSG(UI_CNS_ADDRBOOK_DELETE, OnAddrBookDelete)
    
	MSG_LETTERINDEX_CLICK(_T("ListIndex"),OnLetterIndex)
	MSG_LETTERINDEX_CLICK(_T("ListIndex2"),OnLetterIndex2)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
APP_END_MSG_MAP()


const String CAddrEditLogic::strAddrEditList = _T("AddrEditList");


VOID  CALLBACK  CWaitingTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
    if ( idEvent == g_nTmHandleWaiting )
    {
        ::KillTimer( NULL, g_nTmHandleWaiting );
        g_nTmHandleWaiting = 0;
        CAddrEditLogic::GetSingletonPtr()->OnWaitRefreshOverTime();
    } 
    else if ( idEvent == g_nTmHandleRefresh )
    {
        ::KillTimer( NULL, g_nTmHandleRefresh );
        g_nTmHandleRefresh = 0;
        CAddrEditLogic::GetSingletonPtr()->RefreshTouchlist();
    }
}


CAddrEditLogic::CAddrEditLogic(void)
{
    g_nTmHandleWaiting = 0;
    g_nTmHandleRefresh = 0;
	m_pAddrList = NULL;
    m_pOnlineAddrList = NULL;
	m_bGlobalAddr = FALSE;
	m_bSearchEdit = FALSE;
    m_bLoadToLocal = FALSE;
	m_SelGroup.SetNull();
	m_emEditType = emEntryItem;
	m_emAddrBookType = em_AddrBook_Normal;
	m_emOperateType = em_AddrBook_Copy;
	m_emShowState = emShowAllAddr;
	m_nSelIndex = -1;
    m_nGlobalSelIndex = -1;
}


CAddrEditLogic::~CAddrEditLogic(void)
{
}


bool CAddrEditLogic::OnCreate( TNotifyUI& msg )
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

	m_pAddrList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strAddrEditList.c_str() );
	if ( m_pAddrList == NULL )
	{
		return false;
	}

    m_pOnlineAddrList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("OnlineAddrList") );
    if ( m_pOnlineAddrList == NULL )
    {
        return false;
    }

	return false;
}

bool CAddrEditLogic::OnInit(TNotifyUI& msg)
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

	CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboMore") );
	if ( pCombo != NULL )
	{	
		CListLabelElementUI *pListLabelElement1 = 
			(CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
		pListLabelElement1->SetText(_T("刷新"));
		pCombo->Add(pListLabelElement1);

		CListLabelElementUI *pListLabelElement2 = 
			(CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
		pListLabelElement2->SetText(_T("新建会场"));
		pCombo->Add(pListLabelElement2);

		CListLabelElementUI *pListLabelElement3 = 
			(CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
		pListLabelElement3->SetText(_T("新建组"));
		pCombo->Add(pListLabelElement3);

	}

	return true;
}

bool CAddrEditLogic::OnAddrItemDBClick( TNotifyUI& msg )
{
	if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
	{
		TAddrItem tAddrItem = *(TAddrItem*)pItem->GetTag();

		if ( tAddrItem.emItemType == emGroupItem )//点击组条目，进入组
		{
			m_vctSelectList.clear();
			ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
            m_bSearchEdit = FALSE;
			
			//进入组
			m_SelGroup = tAddrItem.tGroupInfo;
			GetAddrGroupMember( m_SelGroup.dwGroupIdx );
			
			//更新路径
			UpdateAddrPath();
		}

	}
	return true;
}

bool CAddrEditLogic::OnAddrItemClick(TNotifyUI& msg)
{
    if ( m_bGlobalAddr )
    {
        OnGlobalAddrItemClick(msg);
        return true;
    }

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
            m_tSelItem = tAddrItem;
		}
		else
		{
			if ( m_nSelIndex == nIndex )
			{
				m_pm->DoCase( _T("caseListNoSel"), msg.pSender );
				m_nSelIndex = -1;
                m_tSelItem.SetNull();
			}
			else
			{
				CControlUI *pLastSel = m_pAddrList->GetItemAt(m_nSelIndex);
				m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                if ( m_emSelType == emEntryItem )
                {
                    m_pm->DoCase( _T("caseItemShowLabel"), pLastSel );
                }

				m_pm->DoCase( _T("caseListSel"), msg.pSender );
				m_nSelIndex = nIndex;
                m_tSelItem = tAddrItem;
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
  
        /*else//点击组条目，进入组
        {
            m_vctSelectList.clear();
            ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
            m_bSearchEdit = FALSE;
 
            //进入组
            m_SelGroup = tAddrItem.tGroupInfo;
            GetAddrGroupMember( m_SelGroup.dwGroupIdx );
 
            //更新路径
            UpdateAddrPath();
        }*/
    }

	return true;
}


bool CAddrEditLogic::OnGlobalAddrItemClick(TNotifyUI& msg)
{
    if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
    {
        TAddrItem tAddrItem = *(TAddrItem*)pItem->GetTag(); 
	    if ( !m_vctGlobalSelectList.empty() )
	    {
		    return true;
	    }

        if ( tAddrItem.emItemType == emEntryItem )
        {
            m_pm->DoCase( _T("caseItemShowLabel"), msg.pSender );
        }

		int nIndex = pItem->GetIndex();
		if ( m_nGlobalSelIndex == -1 )
		{
            m_pm->DoCase( _T("caseListSel"), msg.pSender );
			m_nGlobalSelIndex = nIndex;
		}
		else
		{
			if ( m_nGlobalSelIndex == nIndex )
			{
				m_pm->DoCase( _T("caseListNoSel"), msg.pSender );
				m_nGlobalSelIndex = -1;
			}
			else
			{
				CControlUI *pLastSel = m_pOnlineAddrList->GetItemAt(m_nGlobalSelIndex);
				m_pm->DoCase( _T("caseListNoSel"), pLastSel );

                m_pm->DoCase( _T("caseItemShowLabel"), pLastSel );

				m_pm->DoCase( _T("caseListSel"), msg.pSender );
				m_nGlobalSelIndex = nIndex;
			}
		}
    }

    return true;
}


bool CAddrEditLogic::OnCheckAddrItem(TNotifyUI& msg)
{
    if ( m_bGlobalAddr )
    {
        CControlUI *pParent = msg.pSender->GetParent();
        if ( CListContainerElementUI *pAddrItem = dynamic_cast<CListContainerElementUI*>(pParent) )
        {
            TAddrItem tAddrItem = *(TAddrItem*)pAddrItem->GetTag();

            CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
            bool bCheck = pCheckBox->GetCheck();

            if ( bCheck )
            {   
                if ( m_nGlobalSelIndex != -1 )
                {
                    CControlUI *pLastSel = m_pOnlineAddrList->GetItemAt(m_nGlobalSelIndex);
                    m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                    m_nGlobalSelIndex = -1;
                }

                pAddrItem->SetBkImage( _T("res\\list\\item_sel.png") );

                m_vctGlobalSelectList.push_back( tAddrItem );
            }
            else
            {
                pAddrItem->SetBkImage( _T("res\\list\\item_normal.png") );

                vector<TAddrItem>::iterator iter = m_vctGlobalSelectList.begin();
                while( iter != m_vctGlobalSelectList.end() )
                {					  
                    if ( *iter == tAddrItem )
                    {
                        m_vctGlobalSelectList.erase(iter);
                        break;
                    }		
                    iter++;
                }
            }
         
            UpdateGlobalUIState();
        }
    } 
    else 
    {   //操作本地地址簿条目
	    CControlUI *pParent = msg.pSender->GetParent();
	    if ( CListContainerElementUI *pAddrItem = dynamic_cast<CListContainerElementUI*>(pParent) )
	    {
		    TAddrItem tAddrItem = *(TAddrItem*)pAddrItem->GetTag();

            //勾选后重新操作，清空操作列表
            if ( !m_vctOperateList.empty() )
            {
                m_vctOperateList.clear();
                m_pm->DoCase( _T("caseAddrCopy") );
            }    

		    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
		    bool bCheck = pCheckBox->GetCheck();

		    if ( bCheck )
		    {
			    if ( m_nSelIndex != -1 )
			    {
				    CControlUI *pLastSel = m_pAddrList->GetItemAt(m_nSelIndex);
				    m_pm->DoCase( _T("caseListNoSel"), pLastSel );
				    m_nSelIndex = -1;
                    m_tSelItem.SetNull();
			    }

			    pAddrItem->SetBkImage( _T("res\\list\\item_sel.png") );

			    m_vctSelectList.push_back( tAddrItem );
		    }
		    else
		    {
			    pAddrItem->SetBkImage( _T("res\\list\\item_normal.png") );

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

            UpdateUIState();
	    }
    }
	return true;
}


bool CAddrEditLogic::OnBtnAddrCfg(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pAddrItem = dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        m_tEditItem = *(TAddrItem*)pAddrItem->GetTag();

        if ( m_tEditItem.emItemType == emEntryItem )
        {
            m_emEditType = emEntryItem;

            m_pm->DoCase( _T("caseEditEntry") );

            ICncCommonOp::SetControlText( CA2T(m_tEditItem.tAddrInfo.achEntryName), m_pm, _T("EditName") );
            ICncCommonOp::SetControlText( CA2T(m_tEditItem.tAddrInfo.achE164), m_pm, _T("EditE164") );
            ICncCommonOp::SetControlText( CA2T(m_tEditItem.tAddrInfo.achIp), m_pm, _T("EditIp") );

            if ( /*m_tEditItem.tAddrInfo.bMonitorTer*/1 == m_tEditItem.tAddrInfo.byTerType )
            {
                COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("opMonitorTer") );
                if (pOp != NULL)
                {
                    pOp->Selected(true);
                }
            }   
			if ( /*m_tEditItem.tAddrInfo.bMonitorTer*/2 == m_tEditItem.tAddrInfo.byTerType )
			{
				COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("opOrdinaryTer") );
				if (pOp != NULL)
				{
					pOp->Selected(true);
				}
			} 
        }
        else
        {
            m_emEditType = emGroupItem;

            m_pm->DoCase( _T("caseEditGroup") );

            ICncCommonOp::SetControlText( CA2T(m_tEditItem.tGroupInfo.achGroupName), m_pm, _T("EditName") );
        }

        m_emAddrBookType = em_AddrBook_Modify;
        ICncCommonOp::ShowControl( true, m_pm, _T("PageEditAddr") );
    }

    return true;
}


bool CAddrEditLogic::OnBtnAddrLabel(TNotifyUI& msg)
{
    if ( m_bGlobalAddr )
    {
        OnBtnGlobalAddrLabel(msg);
        return true;
    }

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
                m_tSelItem = tAddrItem;
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
                    m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                    if ( m_emSelType == emEntryItem )
                    {
                        m_pm->DoCase( _T("caseItemShowLabel"), pLastSel );
                    }
                    //m_pm->DoCase( _T("caseListSel"), msg.pSender );
                    m_nSelIndex = nIndex;
                    m_tSelItem = tAddrItem;
                }
            }

            m_emSelType = emEntryItem;
        }
        else//点击组条目，进入组
        {
            m_vctSelectList.clear();
            ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
            m_bSearchEdit = FALSE;

            //进入组
            m_SelGroup = tAddrItem.tGroupInfo;
            GetAddrGroupMember( m_SelGroup.dwGroupIdx );

            //更新路径
            UpdateAddrPath();
            UpdateUIState();
        }
    }

    return true;
}

bool CAddrEditLogic::OnBtnGlobalAddrLabel(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        TAddrItem tAddrItem = *(TAddrItem*)pItem->GetTag();
        if ( tAddrItem.emItemType == emEntryItem )
        {
            if ( !m_vctGlobalSelectList.empty() )
            {
                return true;
            }

            m_pm->DoCase( _T("caseItemShowInfo"), pParent );
            int nIndex = pItem->GetIndex();
            if ( m_nGlobalSelIndex == -1 )
            {
                //m_pm->DoCase( _T("caseListSel"), msg.pSender );
                m_nGlobalSelIndex = nIndex;
            }
            else
            {
                if ( m_nGlobalSelIndex == nIndex )
                {
                    //m_pm->DoCase( _T("caseListNoSel"), msg.pSender );
                    //m_nSelIndex = -1;
                }
                else
                {
                    CControlUI *pLastSel = m_pOnlineAddrList->GetItemAt(m_nGlobalSelIndex);
                    m_pm->DoCase( _T("caseListNoSel"), pLastSel );

                    m_pm->DoCase( _T("caseItemShowLabel"), pLastSel );

                    m_nGlobalSelIndex = nIndex;
                }
            }
        }
    }
    return true;
}



bool CAddrEditLogic::OnBtnSelectAll(TNotifyUI& msg)
{
    m_vctOperateList.clear();

    if ( !m_bSearchEdit && m_SelGroup.IsNull() && (m_emShowState == emShowAllAddr) )
    {
        m_vctSelectList = *ComInterface->GetAddrEntryList();   
    }
    else
    {
        m_vctSelectList.clear();
        //将没有选中的项都选中
        for ( int i = 0; i < m_vctShowList.size(); i++ )
        {
            TAddrItem tItem = m_vctShowList.at(i);
            if ( tItem.emItemType == emEntryItem  )
            {
                m_vctSelectList.push_back( tItem );
            }
        }        
    }

    UpdateUIState();
    UpdateShowList();
    return true;
}


bool CAddrEditLogic::OnBtnOnlineAllSel(TNotifyUI& msg)
{
    m_vctGlobalSelectList = m_vctGlobalList;
    
    UpdateGlobalShowList();

    UpdateGlobalUIState();

    return true;
}



bool CAddrEditLogic::OnBtnCopy(TNotifyUI& msg)
{
    tstring strName = ICncCommonOp::GetControlText( m_pm, _T("BtnCopy") );
    if ( strName == _T( "复 制" ) )
    {
	    m_emOperateType = em_AddrBook_Copy;
	    m_vctOperateList = m_vctSelectList;

        m_pm->DoCase( _T("caseAddrPaste") );
    }
    else //取消
    {
        //取消不清空选中项
        m_vctOperateList.clear();
        //UpdateUIState();
        m_pm->DoCase( _T("caseAddrCopy") );
    }    

	return true;
}

bool CAddrEditLogic::OnBtnCut(TNotifyUI& msg)
{
    tstring strName = ICncCommonOp::GetControlText( m_pm, _T("BtnCut") );
    if ( strName == _T( "移 动" ) )
    {
        m_emOperateType = em_AddrBook_Cut;
        m_vctOperateList = m_vctSelectList;

        m_pm->DoCase( _T("caseAddrPaste") );
    }
    else
    {
        OnBtnPaste(msg);

        m_pm->DoCase( _T("caseAddrCopy") );
    }

	return true;
}

bool CAddrEditLogic::OnBtnPaste(TNotifyUI& msg)
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
        return false;
    }

    if ( m_SelGroup.dwGroupIdx == dwInGroupIdx )
    {
        m_vctOperateList.clear();
        m_vctSelectList.clear();     
        UpdateUIState();
        UpdateShowList();
        return true;
    }

    u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};

    s32 nCount = 0; //操作的条目数量
    s32 nMaxOptCount = MAXNUM_ENTRY_TABLE; //可操作的最大数量

    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    
    if ( !m_SelGroup.IsNull() )
    {
        nMaxOptCount -= m_SelGroup.nEntryNum;
    }

    for ( u16 i = 0; i < m_vctOperateList.size(); i++ )
    {
        TAddrItem tAddrItem = m_vctOperateList.at(i);
        if ( tAddrItem.emItemType == emEntryItem )
        {
            TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;

            if ( nCount >= nMaxOptCount )
            {
                CString strErr;
                strErr.Format( _T("分组中的会场最多%d个"), MAXNUM_ENTRY_TABLE );
                ShowPopMsg( strErr );
                break;
            }  

            if (  m_emOperateType == em_AddrBook_Cut )
            {
                if ( dwInGroupIdx == INVALID_INDEX )//从最外层剪切到组内
                {
                    CAddrEntry cAddrEntry;
                    cAddrBook.GetAddrEntry( &cAddrEntry, tAddrInfo.dwEntryIdx );
                    u16 wRate = cAddrEntry.GetCallRate();             
                    if ( wRate == 0 )
                    {
                        cAddrEntry.SetCallRate( 1 ); //CallRate为1,表示不在最外层显示
                        u16 wRe = ComInterface->ModifyEntry( cAddrEntry );
                    } 
                }
                else if ( m_SelGroup.IsNull() )  //从组内剪切到最外层   
                {
                    CAddrEntry cAddrEntry;
                    cAddrBook.GetAddrEntry( &cAddrEntry, tAddrInfo.dwEntryIdx );
                    u16 wRate = cAddrEntry.GetCallRate();             
                    if ( wRate == 1 )
                    {
                        cAddrEntry.SetCallRate( 0 ); //CallRate为0,表示在最外层显示
                        u16 wRe = ComInterface->ModifyEntry( cAddrEntry );
                    }
                }
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
                u16 wRe = ComInterface->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_SelGroup.dwGroupIdx );
            }
            else
            {
                //从组中剪切到第一级
                if ( tGroupInfo.dwInGroupIdx != INVALID_INDEX )
                {
                    u16 wRe = ComInterface->DelGroupFromGroup( tGroupInfo.dwGroupIdx, tGroupInfo.dwInGroupIdx );
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

            u16 wRe = ComInterface->DelEntryFromGroup(tDelEntry);
        }

        if ( !m_SelGroup.IsNull() )
        {
            //复制进新分组条目
            TADDRMULTISETENTRY tEntry;
            tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
            tEntry.SetListEntryIndex( adwEntryTable, nCount );
            tEntry.SetListEntryNum( nCount );
            u16 wRe = ComInterface->AddEntryToGroup(tEntry);
        }
    }

    m_vctOperateList.clear();
    m_vctSelectList.clear();
    UpdateUIState();

	return true;
}

bool CAddrEditLogic::OnBtnDelete(TNotifyUI& msg)
{
	if ( !m_vctSelectList.empty() )
	{
        int nResult = ShowMessageBox( _T("是否将所选条目从地址簿中删除"), true );
        if ( IDOK == nResult )
        {
            DelAddrEntry();
        }
	}
    else
    {
        if ( !m_tSelItem.IsNull() )
        {
            if ( m_tSelItem.emItemType == emGroupItem )
            {
                int nResult = ShowMessageBox( _T("是否删除所选分组"), true );
                if ( IDOK == nResult )
                {
                    //u16 wRe = ComInterface->DeleteGroup( m_tSelItem.tGroupInfo.dwGroupIdx );
                    DeleteGroupAndSubGroup( m_tSelItem.tGroupInfo.dwGroupIdx );
                }
            }
            else
            {
                int nResult = ShowMessageBox( _T("是否删除所选地址簿条目"), true );
                if ( IDOK == nResult )
                {
                    u16 wRe = ComInterface->DeleteEntry( m_tSelItem.tAddrInfo.dwEntryIdx );
                }
            }

            m_tSelItem.SetNull();
        }
    }

	
	return true;
}

bool CAddrEditLogic::DelAddrEntry()
{
	vector<u32> vctDelGroup;

	if ( m_SelGroup.IsNull() )
	{
		//删除第一级目录中的条目
		vector<u32> vctDelEntry;

		for ( u16 i = 0; i < m_vctSelectList.size(); i++ )
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
						u16 wRe = ComInterface->DeleteMultiEntry( vctDelEntry );
						vctDelEntry.clear();
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
				u16 wRe = ComInterface->DeleteEntry( vctDelEntry.at(0) );
			}
			else
			{
				u16 wRe = ComInterface->DeleteMultiEntry( vctDelEntry );
			}
		}      
	}
	else
	{   //删除组中的条目
		int nIndex = 0;
		u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};
        CAddrBook cAddrBook = ComInterface->GetAddrBook();;

		for ( u16 i = 0; i < m_vctSelectList.size(); i++ )
		{
			TAddrItem tAddrItem = m_vctSelectList.at(i);
			if ( tAddrItem.emItemType == emEntryItem )
			{
				TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
				if ( tAddrInfo.dwInGroupIdx != INVALID_INDEX )
				{
                    CAddrEntry cAddrEntry;
                    cAddrBook.GetAddrEntry( &cAddrEntry, tAddrInfo.dwEntryIdx );
                    u16 wRate = cAddrEntry.GetCallRate();             
                    if ( wRate == 1 ) //不在最外层显示，直接删除
                    {
                        ComInterface->DeleteEntry(tAddrInfo.dwEntryIdx);
                    }
                    else //在最外层显示，只删除组内的
                    {
                        if ( nIndex >= MAXNUM_ENTRY_TABLE )
                        {
                            return false;
                        }
                        adwEntryTable[nIndex] = tAddrInfo.dwEntryIdx;
                        nIndex++;
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
			u16 wRe = ComInterface->DelEntryFromGroup(tEntry);
		}

	}

	if ( !vctDelGroup.empty() )
	{
		if ( vctDelGroup.size() == 1 )
		{
			u16 wRe = ComInterface->DeleteGroup( vctDelGroup.at(0) );
		}
		else
		{
			u16 wRe = ComInterface->DeleteMultiGroup( vctDelGroup );
		}
	}
    
	m_vctSelectList.clear();
	UpdateUIState();

	return true;
}


bool CAddrEditLogic::OnBtnCnsIsSel(TNotifyUI& msg)
{
    if ( !m_vctSelectList.empty() )
    {
        m_vctSelectList.clear();
        UpdateUIState();
        UpdateShowList();
    }
    return true;
}


void CAddrEditLogic::GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup )
{
	bool bValid = ComInterface->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}
	vctGroup.push_back( dwGroupIndex );

	//下级分组
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = ComInterface->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );

	for ( u16 i = 0; i < dwNum; i++ )
	{
		u32 dwLowGroupIndex = *(pdwGroup + i);

		GetGroupAndLowGroup( dwLowGroupIndex, vctGroup );		
	}

	delete []pdwGroup;
	pdwGroup = NULL;
}


bool CAddrEditLogic::OnComboShowEx(TNotifyUI& msg)
{
    int nSel = msg.wParam;

    if ( nSel == 0 )
    {
        m_emShowState = emShowAllAddr;
        UpdateShowList();
    }
    else if ( nSel == 1 )
    {
        m_emShowState = emShowGroup;
        UpdateShowList();
    }
    else if ( nSel == 2 )
    {
        m_emShowState = emShowOnline;
        UpdateShowList();
    }
    else if ( nSel == 3 )
    {
        m_emShowState = emShowOffline;
        UpdateShowList();
    }
    return true;
}


bool CAddrEditLogic::OnComboMore(TNotifyUI& msg)
{
    int nSel = msg.wParam;

    if ( nSel == 0 )
    {
        OnRefreshAddr(msg);
    }
    else if ( nSel == 1 )
    {
        m_emAddrBookType = em_AddrBook_Add;
        m_emEditType = emEntryItem;

        m_pm->DoCase( _T("caseEditEntry") );
        ICncCommonOp::ShowControl( true, m_pm, _T("PageEditAddr") );
    }
    else if ( nSel == 2 )
    {
        m_emAddrBookType = em_AddrBook_Add;
        m_emEditType = emGroupItem;

        m_pm->DoCase( _T("caseEditGroup") );
        ICncCommonOp::ShowControl( true, m_pm, _T("PageEditAddr") );
    }

	return true;
}



bool CAddrEditLogic::OnRefreshAddr(TNotifyUI& msg)
{
    ICncCommonOp::EnableControl(false,m_pm,_T("BtnRefresh"));
    g_nTmHandleWaiting = SetTimer( NULL, 0, 8000, CWaitingTimerFun); 

    u16 re = ComInterface->UpdateGlobalAddrbook();
	tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
	if ( !strCaption.empty() )
	{
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtSearch"));
	}
	tstring strCaption2 = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch2") );
	if ( !strCaption2.empty() )
	{
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtSearch2"));
	}
    if ( re != NO_ERROR )
    {
        return false;
    }
    return true;
}

bool CAddrEditLogic::OnBtnSaveAddr(TNotifyUI& msg)
{
    if ( m_emEditType == emEntryItem )
    {
        if ( SaveAddrEntry() )
        {
            m_emAddrBookType = em_AddrBook_Normal;
        }	
		else
		{
			return false;
		}
    }
    else
    {
        if ( SaveAddrGroup() )
        {
            //编辑组后可能有全选按钮变化的情况
            /*if ( m_vctShowList.empty() )
            {
                UIManagePtr->EnableWindow( m_strBtnAllSel, false, m_pWndTree );
            }
            else
            {
                UIManagePtr->EnableWindow( m_strBtnAllSel, true, m_pWndTree );
            }*/

            m_emAddrBookType = em_AddrBook_Normal;
        }	
    }

	ICncCommonOp::ShowControl( false, m_pm, _T("PageEditAddr") );
	return true;
}

bool CAddrEditLogic::SaveAddrEntry()
{
    tstring strAddrName = ICncCommonOp::GetControlText( m_pm, _T("EditName") );  

	tstring strAddrE164 = ICncCommonOp::GetControlText( m_pm, _T("EditE164") );

    tstring strAddrIp = ICncCommonOp::GetControlText( m_pm, _T("EditIp") );

	u8 byTertype = 0; //会场类型 0-网呈会场 1-监控会场 2-普通终端

    COptionUI* pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opMonitorTer"));
	COptionUI* pOptOrdinary = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opOrdinaryTer"));
	if (pOpt != NULL && pOpt->IsSelected())
	{
		byTertype = 1;
	}
	else if (pOptOrdinary != NULL && pOptOrdinary->IsSelected())
	{
		byTertype = 2;
	}

    if ( byTertype == 1 )
    {
        if ( strAddrIp.empty() )
        {
            ShowMessageBox((_T("监控终端IP地址不能为空")),false);
            return false;
        }

        if ( strAddrName.empty() && strAddrE164.empty() )
        {
            ShowMessageBox( _T("会场名称、会场号码不能全为空") );
            return false;
        }
    }
    else
    {
	    if ( strAddrName.empty() && strAddrE164.empty() && strAddrIp.empty() )
	    {
		    ShowMessageBox( _T("会场名称、会场号码、IP地址不能全为空") );
		    return false;
	    }
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

    
    if( !strAddrIp.empty() )
    {
        u32 dwIp = ntohl( inet_addr( CT2A(strAddrIp.c_str()) ) );

        if ( !CCallAddr::IsValidIpV4(CT2A(strAddrIp.c_str())) )
        {
            ShowMessageBox((_T("IP地址非法")),false);
            return false;
        }      
    }
   

	CAddrBook cAddrBook = ComInterface->GetAddrBook();

	CAddrEntry cAddrEntry;

	if ( m_emAddrBookType == em_AddrBook_Add )
	{
		u32 dwNum = 0;
		if ( !strAddrName.empty() )
		{
			dwNum = cAddrBook.GetAddrEntryByName( CT2A(strAddrName.c_str()), &cAddrEntry );
			if ( dwNum > 0 )
			{
				ShowMessageBox( _T("会场名称已存在") );
				return false;
			}
		}

		if ( !strAddrE164.empty() )
		{
			dwNum = cAddrBook.GetAddrEntryByNumber( CT2A(strAddrE164.c_str()), &cAddrEntry );
			if ( dwNum > 0 )
			{
				ShowMessageBox( _T("会场号码已存在") );
				return false;
			}
		}

        if ( !strAddrIp.empty() && (byTertype != 1) ) //监控终端IP可以重复
        {
            dwNum = cAddrBook.GetAddrEntryByAddr( CT2A(strAddrIp.c_str()), &cAddrEntry );
            if ( dwNum > 0 )
            {
                ShowMessageBox( _T("IP地址已存在") );
                return false;
            }
        }

		u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
		if ( dwSize >= MAX_ADDRENTRY /*MAX_ADDRENTRY_COUNT*/ )
		{
			CString strErr;
			strErr.Format( _T("会场条目已达到最大值%d个"), MAX_ADDRENTRY );
			ShowMessageBox( strErr );
			return false;
		}

		cAddrEntry.SetEntryName( CT2A(strAddrName.c_str()) );
		cAddrEntry.SetMtNumber( CT2A(strAddrE164.c_str()) );
        cAddrEntry.SetMtIpAddr( CT2A(strAddrIp.c_str()) );
        //cAddrEntry.SetTerminalType( bMonitor );
		TADDRENTRYINFO info;
		ZeroMemory(&info, sizeof(TADDRENTRYINFO));
		cAddrEntry.GetEntryInfo(&info);
		info.bH320Terminal = byTertype;
		cAddrEntry.SetEntryInfo(info);

		u16 wRe = ComInterface->AddEntry( cAddrEntry );

	}
	else
	{
		if ( m_tEditItem.emItemType != emEntryItem )
		{
			return false;
		}
		bool bChange = false;
		if ( strcmp( m_tEditItem.tAddrInfo.achEntryName, CT2A(strAddrName.c_str()) ) != 0 )
		{
			if ( !strAddrName.empty() )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByName( CT2A(strAddrName.c_str()), &cAddrEntry );
				if ( dwNum > 0 )
				{
					ShowMessageBox( _T("会场名称已存在") );
					return false;
				}
			}
			bChange = true;
		}

		if ( strcmp( m_tEditItem.tAddrInfo.achE164, CT2A(strAddrE164.c_str()) ) != 0 )
		{
			if ( !strAddrE164.empty() )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByNumber( CT2A(strAddrE164.c_str()), &cAddrEntry );
				if ( dwNum > 0 )
				{
					ShowMessageBox( _T("会场号码已存在") );
					//pE164Wnd->SetFocus();
					return false;
				}
			}		
			bChange = true;
		}

        if ( strcmp( m_tEditItem.tAddrInfo.achIp, CT2A(strAddrIp.c_str()) ) != 0 )
        {
            if ( !strAddrIp.empty() && (byTertype != 1) )
            {
                u32 dwNum = cAddrBook.GetAddrEntryByAddr( CT2A(strAddrIp.c_str()), &cAddrEntry );
                if ( dwNum > 0 )
                {
                    ShowMessageBox( _T("Ip地址已存在") );
                    //pE164Wnd->SetFocus();
                    return false;
                }
            }		
            bChange = true;
        }

        if ( m_tEditItem.tAddrInfo.byTerType != byTertype )
        {
            bChange = true;
        }

		u32 dwEntryIndex = m_tEditItem.tAddrInfo.dwEntryIdx;
		if ( bChange )
		{		
			cAddrBook.GetAddrEntry( &cAddrEntry, dwEntryIndex );
			cAddrEntry.SetEntryName( CT2A(strAddrName.c_str()) );
			cAddrEntry.SetMtNumber( CT2A(strAddrE164.c_str()) );
            cAddrEntry.SetMtIpAddr( CT2A(strAddrIp.c_str()) );
            //cAddrEntry.SetTerminalType( bMonitor );
			TADDRENTRYINFO info;
			ZeroMemory(&info, sizeof(TADDRENTRYINFO));
			cAddrEntry.GetEntryInfo(&info);
			info.bH320Terminal = byTertype;
			cAddrEntry.SetEntryInfo(info);

			u16 wRe = ComInterface->ModifyEntry( cAddrEntry );
		}
	}
	return true;
}

bool CAddrEditLogic::SaveAddrGroup()
{
    tstring strName = ICncCommonOp::GetControlText( m_pm, _T("EditName") );

    CString cstrName;
    cstrName.Format( _T("%s"), strName.c_str() );
    cstrName.TrimLeft();
    cstrName.TrimRight();
    if ( cstrName.IsEmpty() )
    {
        ShowMessageBox( _T("分组名称不能为空") );
        //msgArg.pOwnerWnd->SetFocus();
        return false;
    }
    strName = cstrName;

    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    CAddrMultiSetEntry cAddrGroup;

    if ( m_emAddrBookType == em_AddrBook_Add )
    {
        if ( m_vctGroupPath.size() >= 2 )
        {
            ShowMessageBox( _T("无法建立三级以上分组") );
            return false;
        }

        u32 dwNum = cAddrBook.GetAddrMultiSetEntry( CT2A(strName.c_str()), &cAddrGroup );
        if ( dwNum > 0 )
        {	
            ShowMessageBox( _T("分组名称已存在") );
            //msgArg.pOwnerWnd->SetFocus();
            return false;
        }	

        u32 dwSize = cAddrBook.GetAddrGroupUsedSize();
        if ( dwSize >= MAX_ADDRGROUP )
        {
            CString strErr;
            strErr.Format( _T("会场分组已达到最大值%d个"), MAX_ADDRGROUP );
            ShowMessageBox( strErr );
            //msgArg.pOwnerWnd->SetFocus();
            return false;
        }

        cAddrGroup.SetGroupName( CT2A(strName.c_str()) );

        u16 wRe = ComInterface->AddGroup( cAddrGroup );

        //m_bWaitAddGroup = TRUE;
    }
    else
    {
        if ( m_tEditItem.emItemType != emGroupItem )
        {
            return false;
        }

        u32 dwGroupIndex = m_tEditItem.tGroupInfo.dwGroupIdx;

        cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );

        if ( strcmp( m_tEditItem.tGroupInfo.achGroupName, CT2A(strName.c_str()) ) != 0 )
        {
            u32 dwNum = cAddrBook.GetAddrMultiSetEntry( CT2A(strName.c_str()), &cAddrGroup );
            if ( dwNum > 0 )
            {	
                ShowMessageBox( _T("分组名称已存在") );
                //msgArg.pOwnerWnd->SetFocus();
                return false;
            }

            cAddrGroup.SetGroupName( CT2A(strName.c_str()) );	
            u16 wRe = ComInterface->ModifyGroup( cAddrGroup );
        }		
    }
    return true;
}



bool CAddrEditLogic::OnBtnCancelAddr(TNotifyUI& msg)
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageEditAddr") );
	return true;
}


bool CAddrEditLogic::UpdateLocalAddrBook(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    //导入地址簿时不用刷新
    if ( m_bLoadToLocal )
    {
        LoadToLocal();

        return NO_ERROR;
    }

	UpdateLocalAddrList();

	if ( !m_SelGroup.IsNull() )	
	{
		GetAddrGroupMember( m_SelGroup.dwGroupIdx );
	}

	if ( m_bSearchEdit )
	{
        TNotifyUI msg;
		OnSearchEditChange( msg );
	}

	return true;
}


void CAddrEditLogic::UpdateLocalAddrList()
{
	m_vctLocalList.clear();
	m_vctLocalList = *ComInterface->GetLocalAddrList();

	UpdateShowList();
}

void CAddrEditLogic::UpdateGlobalAddrList()
{
	m_vctGlobalList.clear();
	m_vctGlobalList = *ComInterface->GetGlobalAddrList();

    UpdateGlobalShowList();
}


void CAddrEditLogic::UpdateShowList()
{	
	if ( m_pAddrList == NULL )
	{
		return;
	}

	if ( !m_bSearchEdit )
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

	if ( !m_bGlobalAddr )
	{
		//获得条件筛选后的条目
		GetOptnShowList( m_vctShowList );
	}   

    sort( m_vctShowList.begin(), m_vctShowList.end(), CUIDataMgr::AddrItemCompare );

	m_pAddrList->RemoveAll();
    m_nSelIndex = -1;
	for ( u16 i = 0; i < m_vctShowList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("AddrListItem") );
		//pListContainer->SetUserData();

		TAddrItem tAddrItem = m_vctShowList.at(i); 

		if ( tAddrItem.emItemType == emEntryItem )
		{
            m_pm->DoCase( _T("caseAddrEditItem"), pListContainer );
			ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achEntryName), m_pm, _T("AddrName"), pListContainer );

			ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achE164), m_pm, _T("AddrE164"), pListContainer );

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

            if ( 1 == tAddrItem.tAddrInfo.byTerType/*tAddrItem.tAddrInfo.bMonitorTer*/ )
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
            m_pm->DoCase( _T("caseEditGroupItem"), pListContainer );
            ICncCommonOp::SetControlText( CA2T(tAddrItem.tGroupInfo.achGroupName), m_pm, _T("AddrShowText"), pListContainer );
        }

		pListContainer->SetTag( (UINT_PTR)&m_vctShowList.at(i) );

        vector<TAddrItem>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tAddrItem );
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

    if ( !m_tSelItem.IsNull() )
    {
        m_tSelItem.SetNull();
    }

}


void CAddrEditLogic::UpdateGlobalShowList()
{
    if ( m_pOnlineAddrList == NULL )
    {
        return;
    }

    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch2") );
    if ( strCaption.empty() )
    {
        m_vctGlobalShowList = m_vctGlobalList;	
    }
    else
    {
        m_vctGlobalShowList = m_vctGlobalSearchList;
    }

    sort( m_vctGlobalShowList.begin(), m_vctGlobalShowList.end(), CUIDataMgr::AddrItemCompare );

    m_pOnlineAddrList->RemoveAll();

    for ( u16 i = 0; i < m_vctGlobalShowList.size(); i++ )
    {
        CListContainerElementUI *pListContainer = 
            (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("AddrListItem") );

        TAddrItem tAddrItem = m_vctGlobalShowList.at(i); 

        if ( tAddrItem.emItemType == emEntryItem )
        {
            m_pm->DoCase( _T("caseAddrOnlineItem"), pListContainer );
            ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achEntryName), m_pm, _T("AddrName"), pListContainer );

            ICncCommonOp::SetControlText( CA2T(tAddrItem.tAddrInfo.achE164), m_pm, _T("AddrE164"), pListContainer );

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
        }

        if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeCNS )
        {
            m_pm->DoCase( _T("caseSipItem"), pListContainer );
        }

        pListContainer->SetTag( (UINT_PTR)&m_vctGlobalShowList.at(i) );

        vector<TAddrItem>::iterator itfind = find( m_vctGlobalSelectList.begin(), m_vctGlobalSelectList.end(), tAddrItem );
        if ( itfind != m_vctGlobalSelectList.end() )
        {
            CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnAddrSel"), pListContainer );
            if ( pCheckBox != NULL )
            {
                pCheckBox->SetCheck(true);
            }
            pListContainer->SetBkImage( _T("res\\list\\item_sel.png") );
        }

        m_pOnlineAddrList->Add(pListContainer);
    }
}


void CAddrEditLogic::UpdateUIState()
{
    if ( m_vctSelectList.empty() )
    {
        m_pm->DoCase( _T("caseCnsNoSel") );

        if ( m_vctOperateList.empty() )
        {
            m_pm->DoCase( _T("caseAddrCannotCopy") );
        }

        ICncCommonOp::SetControlText(_T(""), m_pm, _T("labSelCount"));
    }
    else
    {
        m_pm->DoCase( _T("caseAddrCanCopy") );

        m_pm->DoCase( _T("caseCnsHasSel") );

        CString str = _T("");
        str.Format(_T("(%d)"), m_vctSelectList.size());
        ICncCommonOp::SetControlText(str, m_pm, _T("labSelCount"));
    }
}

void CAddrEditLogic::UpdateGlobalUIState()
{
    if ( m_vctGlobalSelectList.empty() )
    {
        m_pm->DoCase( _T("caseGlobalCnsNoSel") );

        ICncCommonOp::SetControlText(_T(""), m_pm, _T("labOnlineSelCount"));
    }
    else
    {
        m_pm->DoCase( _T("caseGlobalCnsHasSel") );

        CString str = _T("");
        str.Format(_T("(%d)"), m_vctGlobalSelectList.size());
        ICncCommonOp::SetControlText(str, m_pm, _T("labOnlineSelCount"));
    }
}


void CAddrEditLogic::GetAddrGroupMember( u32 dwGroupIndex )
{
	ComInterface->GetAddrGroupMember( dwGroupIndex, m_vctGroupMemberList );

	UpdateShowList();
}


void CAddrEditLogic::DeleteGroupAndSubGroup( u32 dwGroupIndex )
{
    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    vector<u32> vctDelGroup;

    //组及其下级组都删除
    GetGroupAndLowGroup( dwGroupIndex, vctDelGroup );
    if ( !vctDelGroup.empty() )
    {
        //删除组中不在最外层的会场
        vector<u32> vctDelEntry;
        for ( int i = 0; i < vctDelGroup.size(); i++ )
        {
            u32 dwIndex = vctDelGroup.at(i);
            bool bValid = cAddrBook.IsAddrMultiSetEntryValid( dwIndex );
            if ( !bValid )
            {
                continue;;
            }

            CAddrMultiSetEntry cGroup;
            cAddrBook.GetAddrMultiSetEntry( &cGroup, dwIndex );	
            int nNum = cGroup.GetEntryCount();
            u32* pEntryTable = cGroup.GetEntryTable();	
            for ( int j = 0; j < nNum; j++ )
            {
                bool bValid = cAddrBook.IsAddrEntryValid( *pEntryTable );
                if ( !bValid )
                {
                    pEntryTable++;
                    continue;
                }
                CAddrEntry cEntry;
                cAddrBook.GetAddrEntry( &cEntry, *pEntryTable );

                u16 wRate = cEntry.GetCallRate();//CallRate为1时，不在最外层显示
                if ( wRate != 0 )
                {
                    vctDelEntry.push_back( cEntry.GetEntryIndex() );
                    if ( vctDelEntry.size() == MAX_DELENTRY_NUM )
                    {
                        break;
                    }
                }
                pEntryTable++;
            }
        }
        if ( !vctDelEntry.empty() )
        {
            if ( vctDelEntry.size() == 1 )
            {
                u16 wRe = ComInterface->DeleteEntry( vctDelEntry.at(0) );
            }
            else
            {
                u16 wRe = ComInterface->DeleteMultiEntry( vctDelEntry );
            }
        }  

        if ( vctDelGroup.size() == 1 )
        {
            u16 wRe = ComInterface->DeleteGroup( vctDelGroup.at(0) );
        }
        else
        {
            u16 wRe = ComInterface->DeleteMultiGroup( vctDelGroup );
        }
    }
}


void CAddrEditLogic::GetOptnShowList( vector<TAddrItem>& vctCurrentList )
{
    if ( m_emShowState == emShowAllAddr )
    {
        return;
    }

    vector<TAddrItem> vctList = vctCurrentList;
    vctCurrentList.clear();
    if ( m_emShowState == emShowOnline )
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
    else if ( m_emShowState == emShowOffline )
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
    else if ( m_emShowState == emShowGroup )
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

bool CAddrEditLogic::OnSearchEditChange( TNotifyUI& msg )
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


bool CAddrEditLogic::OnOnlineSearchEditChange( TNotifyUI& msg )
{
    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch2") );
    if ( strCaption.empty() )
    {
        UpdateGlobalShowList();

        return false;
    }

    CString strSearchName;
    strSearchName.Format( _T("%s"), strCaption.c_str() );

    m_vctGlobalSearchList.clear();

    vector<TAddrItem> vctShowList;
    vctShowList = m_vctGlobalList;

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
            m_vctGlobalSearchList.push_back( tAddrItem );
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
                    m_vctGlobalSearchList.push_back( tAddrItem );
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
                        m_vctGlobalSearchList.push_back( tAddrItem );
                    }
                }
            }
        }

    }

    UpdateGlobalShowList();
    return true;
}



void CAddrEditLogic::UpdateAddrPath()
{
    if ( m_SelGroup.IsNull() )
    {
        m_pm->DoCase( _T("caseAddrMainPath") );
        m_vctGroupPath.clear();
    }
    else
    {
        CString strBtnName;
        CString strCaseName;

        m_vctGroupPath.push_back( m_SelGroup );
        int nSize = m_vctGroupPath.size();

        strBtnName.Format( _T("BtnGroupPath%d"), nSize );
        ICncCommonOp::SetControlText( CA2T(m_SelGroup.achGroupName), m_pm, strBtnName );

        CButtonUI* pButton= (CButtonUI*)ICncCommonOp::FindControl( m_pm, strBtnName );
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

        //pButton->SetTag( (UINT_PTR)&m_vctGroupPath.at(nSize-1) );
        CString strIndex;
        strIndex.Format( _T("%d"), m_SelGroup.dwGroupIdx );
        if ( pButton != NULL )
        {
            pButton->SetUserData( strIndex );
        }     

        strCaseName.Format( _T("caseGroupPath%d"), nSize );
        m_pm->DoCase( strCaseName );

        /*CAddrBook cAddrBook = ComInterface->GetAddrBook();

        s8 aszGroupName[MAX_NAME_LEN + 1] = "";
        CAddrMultiSetEntry cAddrGroup;

        vector<TGroupInfo> vctGroupPath;
        

        u32 dwIndex = m_SelGroup.dwGroupIdx;
        while( dwIndex != INVALID_INDEX )
        {	
            TGroupInfo tGroupInfo;
            tGroupInfo.dwGroupIdx = dwIndex;
            cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwIndex );

            cAddrGroup.GetGroupName( tGroupInfo.achGroupName, cAddrGroup.GetGroupNameLen() + 1 );

            //strName.Format( _T("%s"), CA2T(aszGroupName) );
            vctGroupPath.insert( vctGroupPath.begin(), tGroupInfo );

            dwIndex = cAddrBook.FindUpGroupOfGroupByIndex( dwIndex );
        }

        CString strLabName;
        CString strBtnName;
        CString strCaseName;
        CString strGroupIndex;
        for( u8 i = 0; i < vctGroupPath.size(); i++ )
        {         
            TGroupInfo tGroupInfo = vctGroupPath.at(i);
            strLabName.Format( _T("txtGroupPath%d"), i+1 );
            ICncCommonOp::SetControlText( CA2T(tGroupInfo.achGroupName), m_pm, strLabName );

            strBtnName.Format( _T("BtnGroupPath%d"), i+1 );
            strGroupIndex.Format( _T("%d"), tGroupInfo.dwGroupIdx );
            CControlUI* pButton = ICncCommonOp::FindControl( m_pm, strBtnName );
            pButton->SetUserData( strGroupIndex );

            strCaseName.Format( _T("caseGroupPath%d"), i+1 );
        }

        m_pm->DoCase( strCaseName );  */     
    }
}

bool CAddrEditLogic::OnBtnAddrMainPath(TNotifyUI& msg)
{
    if ( !m_SelGroup.IsNull() )
    {
        m_SelGroup.SetNull();
        m_vctGroupPath.clear();

        if ( !m_vctSelectList.empty() )
        {
            m_vctSelectList.clear();
            UpdateUIState();
        }

        UpdateShowList();
        UpdateAddrPath();
    }
    return true;
}

bool CAddrEditLogic::OnBtnGroupPath1(TNotifyUI& msg)
{
    //TGroupInfo tGroupInfo = *(TGroupInfo*)msg.pSender->GetTag();
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
        GetAddrGroupMember( m_SelGroup.dwGroupIdx );
        UpdateShowList();
        m_pm->DoCase( _T("caseGroupPath1") );

        while( m_vctGroupPath.size() > 1 )
        {
            m_vctGroupPath.pop_back();
        }
    }

    return true;
}



void CAddrEditLogic::OnAddrEditTabSwitch( EmTitleTabID emTab )
{
    if ( emTab == emTabID_Left )
    {
        m_bGlobalAddr = FALSE;
    }
    else
    {
        m_bGlobalAddr = TRUE;
    }
}


bool CAddrEditLogic::UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));
    if (g_nTmHandleWaiting != 0)
    {
        ::KillTimer( NULL, g_nTmHandleWaiting );
    }

    UpdateGlobalAddrList();

    return true;
}

void CAddrEditLogic::OnWaitRefreshOverTime()
{
    ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));

    ComInterface->ClearSipRegInfo( emGetRegInfoType_CNS );

    UpdateGlobalAddrList();
}


bool CAddrEditLogic::OnBtnOnlineCnsIsSel(TNotifyUI& msg)
{
    if ( !m_vctGlobalSelectList.empty() )
    {
        m_vctGlobalSelectList.clear();
        UpdateGlobalUIState();
        UpdateGlobalShowList();
    }
    return true;
}


bool CAddrEditLogic::OnBtnLoadToLocal( TNotifyUI& msg )
{
    if ( m_vctGlobalSelectList.empty() )
    {
        return true;
    }

    m_dwGlobalAddrIndex = 0;
    //ComInterface->SetAddrLoadingState(TRUE);
    m_bLoadToLocal = FALSE;

    LoadToLocal();

    if ( m_bLoadToLocal )
    {
        //g_nTmHandleNtyLoadNum = SetTimer( NULL, 0, 1000, CNtyLoadNumTimerFun );

        //Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrAddrEditDlg );
        //CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, emWaitLoadAddr );
    }

    return true;
}

void CAddrEditLogic::LoadToLocal()
{
	BOOL bFindSame = FALSE;
	
    if ( m_dwGlobalAddrIndex >= m_vctGlobalSelectList.size() )
    {
        return;
    }
	TAddrItem tAddrItem = m_vctGlobalSelectList.at(m_dwGlobalAddrIndex);

    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    CAddrEntry cAddrEntry;
	
	if ( tAddrItem.emItemType == emEntryItem )
	{
		u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
		if ( dwSize >= MAX_ADDRENTRY )
		{
            CString strErr;
            strErr.Format( _T("会场分组已达到最大值%d个"), MAX_ADDRGROUP );
            ShowMessageBox( strErr );
			return;
		}

        cAddrEntry.SetEntryName( tAddrItem.tAddrInfo.achEntryName );
        cAddrEntry.SetMtNumber( tAddrItem.tAddrInfo.achE164 );
        cAddrEntry.SetMtIpAddr( tAddrItem.tAddrInfo.achIp );
        
        TADDRENTRY tentry;
        ZeroMemory(&tentry, sizeof(TADDRENTRY));
        tentry.SetEntryIndex(cAddrEntry.GetEntryIndex());
        TADDRENTRYINFO info;
        ZeroMemory(&info, sizeof(TADDRENTRYINFO));
        cAddrEntry.GetEntryInfo(&info);
        tentry.SetEntryInfo(&info);
        
        BOOL32 bExist = (cAddrBook.IsAddrEntryExist(info) == INVALID_INDEX) ? FALSE : TRUE; 
        if (bExist)
        {
            bFindSame = TRUE;
		}
    }

	m_dwGlobalAddrIndex++;
	
	if ( !bFindSame )
	{
		m_bLoadToLocal = TRUE;
		
        u16 wRe = ComInterface->AddEntry( cAddrEntry );
	} 
	else
	{
		if ( m_dwGlobalAddrIndex < m_vctGlobalSelectList.size() )
		{
			LoadToLocal();
			return;
		}
	}

	if ( m_dwGlobalAddrIndex == m_vctGlobalSelectList.size() )
	{
        m_dwGlobalAddrIndex = 0;
        //ComInterface->SetAddrLoadingState(FALSE);

        m_vctGlobalSelectList.clear();
        UpdateGlobalShowList();
        UpdateGlobalUIState();

        if ( m_bLoadToLocal )
        {
            m_bLoadToLocal = FALSE;
            //KillTimer( NULL, g_nTmHandleNtyLoadNum );
            //CMsgDispatch::SendMessage( UI_CNC_ENDWAITING_REFRESH, 0, 0 );
        }
	}
}


bool CAddrEditLogic::OnAddEntryNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    u32 dwEntryIndex = (u32)wParam;

    if ( !m_bGlobalAddr && !m_SelGroup.IsNull() )
    {
        TADDRMULTISETENTRY tEntry;

        u32 adwEntryTable[1] = {0};
        tEntry.SetEntryIndex( m_SelGroup.dwGroupIdx );
        adwEntryTable[0] = dwEntryIndex;
        tEntry.SetListEntryIndex(adwEntryTable, 1);
        tEntry.SetListEntryNum(1);
        u16 wRe = ComInterface->AddEntryToGroup(tEntry);		
    }

    return true;
}

bool CAddrEditLogic::OnAddGroupNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    TGroupInfo tGroupInfo;
    u32 dwGroupIndex = (u32)wParam;
    tGroupInfo.dwGroupIdx = dwGroupIndex;
    strncpy( tGroupInfo.achGroupName, (s8*)lParam, TP_MAX_ALIAS_LEN_CNC+1 ); 

    if ( !m_SelGroup.IsNull() )
    {
        u16 wRe = ComInterface->AddGroupToGroup( dwGroupIndex, m_SelGroup.dwGroupIdx );
    }
    return true;
}


bool CAddrEditLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    m_vctLocalList.clear();
    m_vctGroupMemberList.clear();
    m_vctSelectList.clear();
    m_vctShowList.clear();
    m_vctSearchList.clear();
    m_vctOperateList.clear();
    m_vctGroupPath.clear();
    m_vctGlobalList.clear();
    m_vctGlobalShowList.clear();
    m_vctGlobalSearchList.clear();
    m_vctGlobalSelectList.clear();
    m_nSelIndex = -1;
    m_nGlobalSelIndex = -1;
    m_bGlobalAddr = FALSE;
    m_bSearchEdit = FALSE;
    m_SelGroup.SetNull();
    m_tSelItem.SetNull();
    m_pm->DoCase( _T("caseAddrMainPath") );

    ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
    ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch2") );

    ICncCommonOp::ShowControl( false, m_pm, _T("PageEditAddr") );
    ICncCommonOp::EnableControl(true,m_pm,_T("BtnRefresh"));

    ComInterface->ClearSipRegInfo( emGetRegInfoType_CNS );

    UpdateUIState();

    if ( m_pAddrList != NULL )
    {
        m_pAddrList->RemoveAll();
    }
    if ( m_pOnlineAddrList != NULL )
    {
        m_pOnlineAddrList->RemoveAll();
    }
    return true;
}

bool CAddrEditLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("AddrEditList"));
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

bool CAddrEditLogic::OnLetterIndex2( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("OnlineAddrList"));
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
	int nItemCount = m_vctGlobalShowList.size();

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
		s8     achNameLetter[TP_MAX_ALIAS_LEN_CNC+1] = {0};	
		memcpy(achNameLetter,CT2A(m_vctShowList.at(swMidIndex).strNameLetter),m_vctGlobalShowList.at(swMidIndex).strNameLetter.GetLength()); 

		UIDATAMGR->GetFirstLetter( achNameLetter, strLetter ); 

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
		s8     achNameLetter[TP_MAX_ALIAS_LEN_CNC+1] = {0};	
		memcpy(achNameLetter,CT2A(m_vctShowList.at(swMidIndex).strNameLetter),m_vctGlobalShowList.at(swMidIndex).strNameLetter.GetLength()); 

		UIDATAMGR->GetFirstLetter( achNameLetter, strLetter ); 

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

void CAddrEditLogic::OnExitAddrEdit()
{
    ICncCommonOp::ShowControl( false, m_pm, _T("PageEditAddr") );
}

void CAddrEditLogic::UpdateTouchlist()
{
    g_nTmHandleRefresh = SetTimer( NULL, 0, 100, CWaitingTimerFun);   
}

void CAddrEditLogic::RefreshTouchlist()
{
    CControlUI *pControl = ICncCommonOp::FindControl( m_pm, _T("AddrEditList") );
    if ( pControl != NULL )
    {
        pControl->NeedParentUpdate();
    }
}

bool CAddrEditLogic::OnAddrBookModify(WPARAM wParam, LPARAM lParam, bool& bHandle)
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
                tAddrInfo.dwInGroupIdx = itSel->tAddrInfo.dwInGroupIdx;//组号不会更改 保存 否则被初始化
                itSel->tAddrInfo = tAddrInfo;
                break;
            }
        }
    }

    return true;
}

bool CAddrEditLogic::OnAddrBookDelete(WPARAM wParam, LPARAM lParam, bool& bHandle)
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

bool CAddrEditLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}