#include "StdAfx.h"
#include "usermanager.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"

APP_BEGIN_MSG_MAP(CUserManagerLogic,CNotifyUIImpl)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

	MSG_CREATEWINDOW(_T("UserManagerLayout"), OnCreate)
	MSG_INIWINDOW(_T("UserManagerLayout"), OnInit)
	MSG_ITEMSELECTD(_T("UserList"), OnUserItemClick)
	
	MSG_SELECTCHANGE(_T("CheckBoxItemSel"), OnCheckItemSel)
	MSG_SELECTCHANGE(_T("CheckShowSel"), OnCheckClearSel)
	MSG_SELECTCHANGE(_T("CheckDefaultPassWord"), OnCheckIfSetDefaultPassword)
	
	MSG_CLICK(_T("BtnSelAll"), OnBtnSelAll)
	MSG_CLICK(_T("BtnRefresh"), OnBtnRefresh)
	MSG_CLICK(_T("BtnUserSet"), OnBtnModifyUser)
	MSG_CLICK(_T("BtnCancelUserSet"), OnBtnCancelUserSet)
	MSG_CLICK(_T("BtnSaveUserSet"), OnBtnSaveUserSet)
	MSG_CLICK(_T("BtnAdd"), OnBtnAdd)
	MSG_CLICK(_T("BtnDel"), OnBtnDel)

	MSG_SETFOCUS(_T("edtUserPasswdSet"), OnUserPasswdSetEditSetFocus)
	MSG_TEXTCHANGED(_T("edtUserPasswdSet"), OnUserPasswdSetEditTextChange)
	MSG_KILLFOCUS(_T("edtUserPasswdSet"), OnUserPasswdSetEditKillFocus)
	MSG_KILLFOCUS(_T("edtCheckUserPasswdSet"), OnCheckUserPasswdSetEditKillFocus)

	MSG_SETFOCUS(_T("edtNewUserPasswd"), OnNewUserPasswdEditSetFocus)
	MSG_TEXTCHANGED(_T("edtNewUserPasswd"), OnNewUserPasswdEditTextChange)
	MSG_KILLFOCUS(_T("edtNewUserPasswd"), OnNewUserPasswdEditKillFocus)
	MSG_KILLFOCUS(_T("edtCheckUserPasswd"), OnCheckUserPasswdEditKillFocus)

	MSG_CLICK(_T("BtnSaveUserPasswd"), OnBtnSaveUserPasswd)
	MSG_CLICK(_T("BtnCancelUserPasswd"), OnBtnCancelUserPasswd)

	MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)

	USER_MSG(UI_UMS_REFRESH_USER_LIST,OnRefreshUserLst) 
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_UMS_OPERATE_USER_RET,OnUserModifyRsp)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
	MSG_LETTERINDEX_CLICK(_T("ListIndex"),OnLetterIndex)
APP_END_MSG_MAP()

const String CUserManagerLogic::m_strUserList = _T("ConfTempList");
const String CUserManagerLogic::m_strUserListItem = _T("UserListItem");
const String CUserManagerLogic::m_strUserItemName = _T("UserItemName");
const String CUserManagerLogic::m_strSeachEdit = _T("EdtSearch");
const String CUserManagerLogic::m_strBtnUserSet = _T("BtnUserSet");
const String CUserManagerLogic::m_strCheckBoxItemSel = _T("CheckBoxItemSel");

const String CUserManagerLogic::m_strEdtOldUserPasswd = _T("edtOldUserPasswd");
const String CUserManagerLogic::m_strEdtNewUserPasswd = _T("edtNewUserPasswd");
const String CUserManagerLogic::m_strEdtCheckUserPasswd = _T("edtCheckUserPasswd");
const String CUserManagerLogic::m_strEdtUserPasswdSet = _T("edtUserPasswdSet");
const String CUserManagerLogic::m_strEdtCheckUserPasswdSet = _T("edtCheckUserPasswdSet");

CUserManagerLogic::CUserManagerLogic(void):m_selUser(),
	m_emModifyType( em_NETMNGOPT_IDLE ),m_pArrayUserList(NULL),m_pArrayUserSelLst(),
	m_bIsSetDefaultPassword(false),m_bIsSelAll(false),m_bIsSearch(false),m_bIsCheckState(false)
{
}


CUserManagerLogic::~CUserManagerLogic(void)
{
}

bool CUserManagerLogic::OnCreate( TNotifyUI& msg )
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

bool CUserManagerLogic::OnInit( TNotifyUI& msg )
{
	UpdateUserLst();

	ICncCommonOp::ShowControl( true, m_pm, _T("BtnNotice") );
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameSet") );
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameModify") );
	return true;
}

bool CUserManagerLogic::OnRefreshUserLst( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	UpdateUserLst();

	return true;
}

void CUserManagerLogic::UpdateUserLst()
{
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
	m_bIsSelAll = false;
	//关闭已选列表
	CCheckBoxUI *pCheckBoxUI = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if (pCheckBoxUI && pCheckBoxUI->GetCheck())
	{
		pCheckBoxUI->Selected(false);
	}
	//清空已选
	m_pArrayUserSelLst.Clear();
	//外部直接调用刷新列表 清除搜索项
	if ( m_bIsSearch )
	{
		m_bIsSearch = false;
		ICncCommonOp::SetControlText(_T(""),m_pm,_T("EdtSearch"));
	}

	if (!m_pArrayUserList.IsEmpty())
	{
		m_pArrayUserList.Clear();
	}
	TplArray<CUserFullInfo>* tplUserList;
	tplUserList = ComInterface->GetUserList();

	if (tplUserList->Size() == 0)
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSelAll"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("BtnSelAll"));
	}

	m_pArrayUserList = *tplUserList;
	vector<CUserFullInfo> vctList;
	for ( int i = 0; i < m_pArrayUserList.Size(); i++ )
	{
		vctList.push_back( m_pArrayUserList.GetAt(i) );
	}

	sort( vctList.begin(), vctList.end(), CUIDataMgr::UserItemCompare );

	m_pArrayUserList.Clear();
	for ( int i = 0; i < vctList.size(); i++ )
	{
		m_pArrayUserList.Add(&vctList.at(i));
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("UserList") );
	pTileLayoutUI->RemoveAll();
	if ( pTileLayoutUI == NULL )
	{
		return;
	}
	//当前登录的用户
	TLoginInfo tLoginUser;
	ComInterface->GetLoginInfo(tLoginUser);
	for ( int i = 0; i <  m_pArrayUserList.Size(); i++ )
	{		
 		CString str(m_pArrayUserList.GetAt(i).m_achname);
		if ( str == _T(T300E_TPAD_SUPERUSRNAME) || (str == _T("admin") && (strcmp( "admin", tLoginUser.achName) != 0 && strcmp( T300E_TPAD_SUPERUSRNAME, tLoginUser.achName) != 0 )))
		{
			continue;
		}

		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( m_strUserListItem.c_str() );

 		ICncCommonOp::SetControlText( (CA2T)(m_pArrayUserList.GetAt(i).m_achname), m_pm, m_strUserItemName.c_str(), pListContainer );
		CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, m_strCheckBoxItemSel.c_str(), pListContainer);
		CButtonUI* pBtnUserSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnUserSet.c_str(), pListContainer);
		
		if ( pCheckBoxItemSel )
		{
			pCheckBoxItemSel->SetTag( (UINT_PTR)&m_pArrayUserList.GetAt(i));		
		}

		if ( pBtnUserSet )
		{
			pBtnUserSet->SetTag( (UINT_PTR)&m_pArrayUserList.GetAt(i));
		}		

        if (str == _T("admin"))
        {
            pCheckBoxItemSel->SetVisible(false);
        }

 		pTileLayoutUI->Add(pListContainer);
	}

}

bool CUserManagerLogic::OnUserItemClick( TNotifyUI& msg )
{
	if (m_pArrayUserSelLst.Size() == 0)
	{
		return true;
	}
	int dwIndex = msg.wParam;
	int dwoldIndex = msg.lParam;

	CUserFullInfo userFullInfo = m_pArrayUserList.GetAt(dwIndex);
	CDuiString name=msg.pSender->GetName();
	
	return true;
}

bool CUserManagerLogic::OnBtnRefresh( TNotifyUI& msg )
{

	//NOTIFY_MSG( UI_CNC_BEGINWAITING_REFRESH );
	UpdateUserLst();

	return false;
}

bool CUserManagerLogic::OnBtnModifyUser( TNotifyUI& msg )
{
	m_emModifyType = em_NETMNGOPT_MODIFY;
	m_selUser = *(CUserFullInfo*)msg.pSender->GetTag();

	CString str(m_selUser.m_achname);
	ICncCommonOp::SetControlText( str, m_pm, _T("edtuserName") );
	ICncCommonOp::EnableControl( false, m_pm, _T("edtuserName") );
	ICncCommonOp::ShowControl( true, m_pm, _T("UserNameModify") );

	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtOldUserPasswd.c_str());	
	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtNewUserPasswd.c_str());	
	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtCheckUserPasswd.c_str());	

	m_pm->DoCase(_T("ModifyInitCase"));
	return true;
}

bool CUserManagerLogic::OnSearchEditChange( TNotifyUI& msg )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( !pEditSearch )
	{
		return false;
	}

	//清空已选
	m_pArrayUserSelLst.Clear();
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
	m_bIsSelAll = false;

	CString strSearch = pEditSearch->GetText();
	if ( strSearch.IsEmpty() )
	{
		if (!m_bIsSearch)
		{
			return true;
		}

		m_bIsSearch = false;
		UpdateUserLst();
	}
	else
	{
		m_bIsSearch = true;
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("UserList") );
		if ( pTileLayoutUI == NULL )
		{
			return false;
		}

		pTileLayoutUI->RemoveAll();

        //当前登录的用户
        TLoginInfo tLoginUser;
        ComInterface->GetLoginInfo(tLoginUser);
		for ( int i = 0; i < m_pArrayUserList.Size(); i++ )
		{

            CString str(m_pArrayUserList.GetAt(i).m_achname);
            if ( str == _T(T300E_TPAD_SUPERUSRNAME) || (str == _T("admin") && (strcmp( "admin", tLoginUser.achName) != 0 && strcmp( T300E_TPAD_SUPERUSRNAME, tLoginUser.achName) != 0 )))
            {
                continue;
            }

			CString strConfTempName;
			strConfTempName.Format( _T("%s"),CA2T( m_pArrayUserList.GetAt(i).m_achname));
			BOOL bFind = FALSE;			
			bFind = UIDATAMGR->HZPYMatchList( strSearch, strConfTempName );
			if ( bFind )
			{
				CListContainerElementUI *pListContainer = 
					(CListContainerElementUI*)CONTROLFACTORY()->GetControl( m_strUserListItem.c_str() );

				ICncCommonOp::SetControlText( CA2T(m_pArrayUserList.GetAt(i).m_achname), m_pm, m_strUserItemName.c_str(), pListContainer );
				CButtonUI* pBtnUserSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnUserSet.c_str(), pListContainer);
				CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, m_strCheckBoxItemSel.c_str(), pListContainer);
				if ( pCheckBoxItemSel )
				{
					pCheckBoxItemSel->SetTag( (UINT_PTR)&m_pArrayUserList.GetAt(i));	
				}

				if ( pBtnUserSet )
				{
					pBtnUserSet->SetTag( (UINT_PTR)&m_pArrayUserList.GetAt(i));
				}	
				pTileLayoutUI->Add(pListContainer);
			}
		}

		if (pTileLayoutUI->GetCount() == 0)
		{
			ICncCommonOp::EnableControl(false,m_pm,_T("BtnSelAll"));
		}
		else
		{
			ICncCommonOp::EnableControl(true,m_pm,_T("BtnSelAll"));
		}
	}

	//已选操作按钮状态更新
	CCheckBoxUI *pCheckBoxUI = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if (pCheckBoxUI && pCheckBoxUI->GetCheck())
	{
		m_bIsCheckState = true;
		pCheckBoxUI->SetEnabled(false);
		pCheckBoxUI->Selected(false);
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("lbSelCount"));
	}

	return false;
}

bool CUserManagerLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( pEditSearch )
	{
		pEditSearch->SetText(_T(""));
	}

	m_selUser.Empty();
	m_emModifyType = em_NETMNGOPT_IDLE;
	m_pArrayUserList.Clear();
	m_pArrayUserSelLst.Clear();
	m_bIsSetDefaultPassword = false;
	m_bIsSelAll = false;
	m_bIsSearch = false;
	m_bIsCheckState = false;
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameModify") );
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameSet") );
	return true;
}

bool CUserManagerLogic::OnBtnCancelUserSet( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameSet") );
	return true;
}

bool CUserManagerLogic::OnBtnCancelUserPasswd( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameModify") );
	return true;
}

bool CUserManagerLogic::OnBtnSaveUserPasswd( TNotifyUI& msg )
{
	if ( savePassWord( ) != true )
	{
		return false;
	}
	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameModify") );
	return true;
}

bool CUserManagerLogic::OnBtnBack( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strUserManagerDlg.c_str(),false );
	return true;
}

bool CUserManagerLogic::OnBtnExit( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strUserManagerDlg.c_str(),false );
	return true;
}

bool CUserManagerLogic::OnUserModifyRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16 wEvent = wParam;
	EmTpRet emRe = (EmTpRet)lParam;

	if ( lParam != emMtRegSuccess )
	{        
		CString strErr = _T("");
		switch(wEvent)
		{
		case ev_CNSAddUserRet:
			strErr = _T("添加用户失败");
		case ev_CNSChangePWDRet:
			strErr = _T("用户密码修改失败");
			break;
		case ev_CNSDelUserRet:
			strErr = _T("删除用户失败");
			break;
		}

		CString msg;
		if ( strErr.IsEmpty() )
		{
			msg = "用户操作失败";

		}
		else
		{
			msg = _T("操作用户失败: ") + strErr;
		}

		ShowPopMsg(msg);
		//不成功进行更新 成功等nty消息更新
		UpdateUserLst();

	}

	if (m_bIsSelAll)
	{
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		m_bIsSelAll = false;
	}
	
	return NO_ERROR;
}

bool CUserManagerLogic::OnBtnSelAll( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("UserList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnSelAll"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, m_strCheckBoxItemSel.c_str(), pListContainer);

			if ( pCheckBoxItemSel && pCheckBoxItemSel->IsVisible() && !pCheckBoxItemSel->GetCheck())
			{
				pCheckBoxItemSel->SetCheck(true);
			}
		}
	}
	else
	{
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, m_strCheckBoxItemSel.c_str(), pListContainer);

			if ( pCheckBoxItemSel && pCheckBoxItemSel->IsVisible() )
			{
				pCheckBoxItemSel->SetCheck(false);
			}

		}
	}

	return true;
}

bool CUserManagerLogic::OnBtnAdd( TNotifyUI& msg )
{
	TplArray<CUserFullInfo>*  pUserLst = ComInterface->GetUserList();
	if ( pUserLst != NULL )
	{
		if ( pUserLst->Size() >= MAX_USER_COUNT )
		{
			CString str = _T("");
			str.Format(_T("用户个数已达到最大值 %d , 请删除冗余用户后再添加"),MAX_USER_COUNT);
			showMessageBox( str );
			return false;
		}
	}

	m_selUser.Empty();
	m_emModifyType = em_NETMNGOPT_ADD;
	ICncCommonOp::EnableControl( true, m_pm, _T("EditName") );
	
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckDefaultPassWord"));
	if (pCheckBox)
	{
		pCheckBox->SetCheck(true);
	}

	ICncCommonOp::SetControlText(_T(""),m_pm,_T("EditName"));
	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtUserPasswdSet.c_str());
	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtCheckUserPasswdSet.c_str());
	ICncCommonOp::ShowControl( true, m_pm, _T("UserNameSet") );

	m_pm->DoCase(_T("InitCase"));

	return true;
}

bool CUserManagerLogic::OnBtnDel( TNotifyUI& msg )
{
	if ( m_pArrayUserSelLst.Size() <= 0)
	{
		ShowMessageBox(_T("请选择删除用户"),false);
		return true;
	}
	int nResult = ::showMessageBox(_T("是否删除此用户"),true);
	if ( nResult == IDOK )
	{
		for ( int i = 0; i<m_pArrayUserSelLst.Size(); i++)
		{
			u16 wRe = ComInterface->DeleteUser( m_pArrayUserSelLst.GetAt(i) );
			if ( wRe != NO_ERROR )
			{
				ShowMessageBox(_T("删除失败"));
				return false;
			}
		}

		UpdateUserLst();
		return true;
	}
	else
	{
		return false;
	}

}

bool CUserManagerLogic::OnCheckClearSel( TNotifyUI& msg )
{
	if (m_bIsCheckState)
	{
		m_bIsCheckState = false;
		return true;
	}

	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}
	if ( !pCheckBox->GetCheck() )
	{
		UpdateUserLst();
		m_pArrayUserSelLst.Clear();
		m_selUser.Empty();
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("lbSelCount"));
		pCheckBox->SetEnabled(false);
	}
	else
	{
		if (!pCheckBox->IsEnabled())
		{
			pCheckBox->SetEnabled(true);
		}
	}

	return true;
}

bool CUserManagerLogic::OnBtnSaveUserSet( TNotifyUI& msg )
{
	String strName;
	CEditUI *pEdt = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EditName") );   
	CEditUI *pEdtNewPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtUserPasswdSet.c_str() );
	CEditUI *pEdtCheckPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtCheckUserPasswdSet.c_str() );

	String strNewPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtUserPasswdSet.c_str());
	String strCheckPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtCheckUserPasswdSet.c_str());

	if ( !pEdt ||( pEdtNewPassword == NULL ) ||( pEdtCheckPassword == NULL ))
	{
		return false;
	}

	strName = pEdt->GetText();
	if ( strName.empty() )
	{
		ShowMessageBox(_T("用户名不可为空"));
		pEdt->SetFocus();
		return false;
	}

	if ( strName.find(_T(" ")) != -1 )
	{
		showMessageBox(_T("用户名中不可以含有空格"));
		pEdt->SetFocus();
		return false;
	}

	if ( strName.compare(_T(T300E_TPAD_USRNAME)) == 0 || strName.compare(_T(T300E_TPAD_SUPERUSRNAME)) == 0 )
	{
		showMessageBox(_T("不可添加管理员用户"));
		pEdt->SetFocus();
		return false;
	}

	if ( strNewPassWord == _T("") )
	{    
		showMessageBox(_T("密码不能为空"));
		pEdtNewPassword->SetFocusX();
		return false;
	}

	if ( strCheckPassWord == _T("") )
	{    
		showMessageBox(_T("校验密码不能为空"));
		pEdtCheckPassword->SetFocusX();
		return false;
	}

	if ( strNewPassWord != strCheckPassWord )
	{    
		showMessageBox(_T("请确认两次密码输入一致"));
		pEdtNewPassword->SetFocusX();
		return false;
	}

	if (!UIDATAMGR->IsValidPWStr(strNewPassWord.c_str()))
	{
		showMessageBox(_T("密码设置不规范，请重新输入"));
		return false;
	}

	m_selUser.SetName( CT2A(strName.c_str() ));
	m_selUser.SetPassword( CT2A(strNewPassWord.c_str()) );

	//有改变，需要保存
	//if ( strName.compare((LPCTSTR)m_selUser.GetName()) != 0 || strPswd.compare((LPCTSTR)m_selUser.GetPassword() ) != 0
//		/*|| strNote != m_selUser.GetDiscription()*/ )

	u16 wRe = NO_ERROR;
	wRe = ComInterface->AddUser( m_selUser );

	if (wRe == ERR_CMS_UI_NAME_REPEAT)
	{
		showMessageBox(_T("此用户已存在"));
		return false;
	}

	if ( wRe != NO_ERROR )
	{
		showMessageBox(_T("设置失败"));
		return false;
	}

	ICncCommonOp::ShowControl( false, m_pm, _T("UserNameSet") );
	return false;
}

bool CUserManagerLogic::OnCheckItemSel( TNotifyUI& msg )
{
	CUserFullInfo* userFullInfo = (CUserFullInfo*)msg.pSender->GetTag();
	CControlUI *pParent = msg.pSender->GetParent()->GetParent()->GetParent();
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("UserList") );
	if (pTileLayoutUI)
	{
		if ( pTileLayoutUI->GetCurSel() != -1 )
		{
			CListContainerElementUI *pSelItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(pTileLayoutUI->GetCurSel());
			if (pSelItem)
			{
				pSelItem->Select(false);
			}
		}

	}
	if ( pCheckBox->GetCheck() )
	{
		//搜索以后不重复添加
		if ( m_bIsSearch )
		{
			for ( s16 i = 0; i< m_pArrayUserSelLst.Size(); i++ )
			{
				if (m_pArrayUserSelLst.GetAt(i).IsEqualName( userFullInfo->m_achname ))
				{
					if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
					{
						pItem->SetBkImage(_T("res\\list\\item_sel.png"));
						pTileLayoutUI->SetSelectedItemImage(_T("res\\list\\item_normal.png"));
					}
					return true;
				}
			}
		}

		m_pArrayUserSelLst.Add(userFullInfo);
		if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
		{
			pItem->SetBkImage(_T("res\\list\\item_sel.png"));
			pTileLayoutUI->SetSelectedItemImage(_T("res\\list\\item_normal.png"));
		}
	}
	else
	{	
		if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
		{
			pItem->SetBkImage(_T(""));
		}

		s16 nCont = m_pArrayUserSelLst.Size();
		for ( s16 i = 0; i< nCont; i++ )
		{  
			bool bIsEqual = m_pArrayUserSelLst.GetAt(i).IsEqualName( userFullInfo->m_achname );
			if ( bIsEqual ) 
			{
				m_pArrayUserSelLst.Delete(i);
				break;
			}
		}	
		if ( m_bIsSelAll )
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		}

		if (m_pArrayUserSelLst.Size() == 0)
		{
			pTileLayoutUI->SetSelectedItemImage(_T("res\\list\\item_down.png"));
		}
	}

	if (  m_pArrayUserSelLst.Size() == m_pArrayUserList.Size() - 1 || ( m_bIsSearch && m_pArrayUserSelLst.Size() == pTileLayoutUI->GetCount()))//admin不显示
	{
		m_bIsSelAll = true;
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnSelAll"));
	}

	CCheckBoxUI* pCheckSelected = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm, _T("CheckShowSel"));
	if (m_pArrayUserSelLst.Size() > 0)
	{
		if (pCheckSelected && !pCheckSelected->GetCheck())
		{
			pCheckSelected->SetCheck(true);
		}

		CString str = _T("");
		str.Format(_T("(%d)"), m_pArrayUserSelLst.Size());
		ICncCommonOp::SetControlText(str, m_pm, _T("lbSelCount"));
	}
	else
	{
		if (pCheckSelected)
		{
			m_bIsCheckState = true;
			pCheckSelected->SetEnabled(false);
			pCheckSelected->SetCheck(false);
			ICncCommonOp::SetControlText(_T(""), m_pm, _T("lbSelCount"));
		}
	}
	return NO_ERROR;
}

bool CUserManagerLogic::OnCheckIfSetDefaultPassword( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	m_bIsSetDefaultPassword = pCheckBox->GetCheck();	
	return true;
}

bool CUserManagerLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("UserList"));
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
	int nItemCount = m_pArrayUserList.Size();

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
		UIDATAMGR->GetFirstLetter( m_pArrayUserList[swMidIndex].m_achname, strLetter ); 

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
		UIDATAMGR->GetFirstLetter( m_pArrayUserList[swMidIndex].m_achname, strLetter ); 

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

bool CUserManagerLogic::savePassWord( )
{
	CEditUI *pEdtOldPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtOldUserPasswd.c_str() );   
	CEditUI *pEdtNewPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtNewUserPasswd.c_str() );
	CEditUI *pEdtCheckPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtCheckUserPasswd.c_str() );

	String strOriPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtOldUserPasswd.c_str());
	String strNewPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtNewUserPasswd.c_str());
	String strCheckPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtCheckUserPasswd.c_str());

	if (strOriPassWord.empty() && strNewPassWord.empty() && strCheckPassWord.empty())
	{
		return true;
	}
	TLoginInfo tLoginUser;
	ComInterface->GetLoginInfo(tLoginUser);

	CUserFullInfo cUser,cLoginUser;
	cUser.SetPassword( CT2A(strOriPassWord.c_str()));
	if ( !m_selUser.IsPassWordEqual( cUser.GetPassword()) ) 
	{ 
		showMessageBox(_T("原密码输入错误"));
		pEdtOldPassword->SetFocusX();			
		return false;
	}
	if ( strNewPassWord == _T("") )
	{    
		showMessageBox(_T("密码不能为空"));
		pEdtNewPassword->SetFocusX();
		return false;
	}

	cUser.SetName( m_selUser.m_achname );
	cUser.SetPassword( CT2A(strNewPassWord.c_str()) );
	if (m_selUser.IsPassWordEqual( cUser.GetPassword()) )
	{
		showMessageBox(_T("新密码和原始密码不可一致"));
		pEdtNewPassword->SetFocusX();
		return false;
	}
	if ( strNewPassWord != strCheckPassWord )
	{    
		showMessageBox(_T("请确认两次密码输入一致"));
		pEdtNewPassword->SetFocusX();
		return false;
	}

	if (!UIDATAMGR->IsValidPWStr(strNewPassWord.c_str()))
	{
		showMessageBox(_T("密码设置不规范，请重新输入"));
		return false;
	}

	//admin用户需要管理员权限才可以修改密码
	if ( strcmp( tLoginUser.achName, "admin" ) == 0 || strcmp( tLoginUser.achName, T300E_TPAD_SUPERUSRNAME ) == 0 )
	{
		cUser.SetActor( UM_ADMIN );
		cUser.m_dwGuid = 1;
		cUser.SetDiscription("Administrator");
		cUser.SetFullName( "administrator" );
	}   
	u16 wRe = ComInterface->UpdateUser( cUser ); 
	if ( wRe != NO_ERROR )
	{
		showMessageBox(_T("修改密码失败"));
		return false;
	}
    else
    {
        UpdatePasswordTime();
    }

	return true;
}

bool CUserManagerLogic::OnUserPasswdSetEditSetFocus( TNotifyUI& msg )
{
	m_pm->DoCase(_T("PwdEditSetFocus"));
	return true;
}

bool CUserManagerLogic::OnUserPasswdSetEditTextChange( TNotifyUI& msg )
{
	String strPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtUserPasswdSet.c_str());
	TPWElement tPWElementState, tPWElementLevel;
	UIDATAMGR->GetPWlevel(strPassWord.c_str(), tPWElementLevel, tPWElementState);
	//处理等级
	int nlevel = 0;
	if (tPWElementLevel.m_bElement0)
	{
		nlevel++;
	}
	if (tPWElementLevel.m_bElement1)
	{
		nlevel++;
	}
	if (tPWElementLevel.m_bElement2)
	{
		nlevel++;
	}
	if (nlevel == 1)
	{
		m_pm->DoCase(_T("LowerCase"));
	}
	else if (nlevel == 2)
	{
		m_pm->DoCase(_T("SeniorCase"));
	}
	else if (nlevel == 3)
	{
		m_pm->DoCase(_T("HighCase"));
	}
	else
	{
		m_pm->DoCase(_T("NoLevelCase"));
	}
	//处理状态
	if (strPassWord.length() == 0)
	{
		ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNormal.png"), m_pm, _T("LengthLab"));
		ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNormal.png"), m_pm, _T("RangeLab"));
		ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNormal.png"), m_pm, _T("TypeLab"));
	}
	else
	{
		if (!tPWElementState.m_bElement0)
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckYes.png"), m_pm, _T("LengthLab"));
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNo.png"), m_pm, _T("LengthLab"));
		}
		if (!tPWElementState.m_bElement1)
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckYes.png"), m_pm, _T("RangeLab"));
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNo.png"), m_pm, _T("RangeLab"));
		}
		if (!tPWElementState.m_bElement2)
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckYes.png"), m_pm, _T("TypeLab"));
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNo.png"), m_pm, _T("TypeLab"));
		}
	}
	return true;
}

bool CUserManagerLogic::OnUserPasswdSetEditKillFocus( TNotifyUI& msg )
{
	m_pm->DoCase(_T("PwdEditKillFocus"));

	String strPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtUserPasswdSet.c_str());
	if (strPassWord == _T(""))
	{
		m_pm->DoCase(_T("NoPwKillFocus"));
	}
	else
	{
		m_pm->DoCase(_T("PwKillFocus"));
	}

	TPWElement tPWElementState, tPWElementLevel;
	UIDATAMGR->GetPWlevel(strPassWord.c_str(), tPWElementLevel, tPWElementState);

	if (tPWElementState.m_bElement0 || tPWElementState.m_bElement1 || tPWElementState.m_bElement2 )
	{
		m_pm->DoCase(_T("ErrorPwKillFocus"));
	}
	else
	{
		m_pm->DoCase(_T("InfoPwKillFocus"));
	}
	OnCheckUserPasswdSetEditKillFocus(msg);
	return true;
}

bool CUserManagerLogic::OnCheckUserPasswdSetEditKillFocus( TNotifyUI& msg )
{
	String strNewPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtUserPasswdSet.c_str());
	String strCheckPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtCheckUserPasswdSet.c_str());

	if ( strNewPassWord != strCheckPassWord && strCheckPassWord != _T("") )
	{    
		m_pm->DoCase(_T("CheckPasswordError"));
	}
	else
	{
		m_pm->DoCase(_T("CheckPasswordSuccess"));
	}
	return true;
}

bool CUserManagerLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}

bool CUserManagerLogic::OnNewUserPasswdEditSetFocus( TNotifyUI& msg )
{
	m_pm->DoCase(_T("ModifyPwdEditSetFocus"));
	return true;
}

bool CUserManagerLogic::OnNewUserPasswdEditTextChange( TNotifyUI& msg )
{
	String strPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtNewUserPasswd.c_str());
	TPWElement tPWElementState, tPWElementLevel;
	UIDATAMGR->GetPWlevel(strPassWord.c_str(), tPWElementLevel, tPWElementState);
	//处理等级
	int nlevel = 0;
	if (tPWElementLevel.m_bElement0)
	{
		nlevel++;
	}
	if (tPWElementLevel.m_bElement1)
	{
		nlevel++;
	}
	if (tPWElementLevel.m_bElement2)
	{
		nlevel++;
	}
	if (nlevel == 1)
	{
		m_pm->DoCase(_T("ModifyLowerCase"));
	}
	else if (nlevel == 2)
	{
		m_pm->DoCase(_T("ModifySeniorCase"));
	}
	else if (nlevel == 3)
	{
		m_pm->DoCase(_T("ModifyHighCase"));
	}
	else
	{
		m_pm->DoCase(_T("ModifyNoLevelCase"));
	}
	//处理状态
	if (strPassWord.length() == 0)
	{
		ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNormal.png"), m_pm, _T("ModifyLengthLab"));
		ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNormal.png"), m_pm, _T("ModifyRangeLab"));
		ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNormal.png"), m_pm, _T("ModifyTypeLab"));
	}
	else
	{
		if (!tPWElementState.m_bElement0)
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckYes.png"), m_pm, _T("ModifyLengthLab"));
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNo.png"), m_pm, _T("ModifyLengthLab"));
		}
		if (!tPWElementState.m_bElement1)
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckYes.png"), m_pm, _T("ModifyRangeLab"));
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNo.png"), m_pm, _T("ModifyRangeLab"));
		}
		if (!tPWElementState.m_bElement2)
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckYes.png"), m_pm, _T("ModifyTypeLab"));
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T("res//usermanager//CheckNo.png"), m_pm, _T("ModifyTypeLab"));
		}
	}
	return true;
}

bool CUserManagerLogic::OnNewUserPasswdEditKillFocus( TNotifyUI& msg )
{
	m_pm->DoCase(_T("ModifyPwdEditKillFocus"));

	String strPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtNewUserPasswd.c_str());
	if (strPassWord == _T(""))
	{
		m_pm->DoCase(_T("ModifyNoPwKillFocus"));
	}
	else
	{
		m_pm->DoCase(_T("ModifyPwKillFocus"));
	}

	TPWElement tPWElementState, tPWElementLevel;
	UIDATAMGR->GetPWlevel(strPassWord.c_str(), tPWElementLevel, tPWElementState);

	if (tPWElementState.m_bElement0 || tPWElementState.m_bElement1 || tPWElementState.m_bElement2 )
	{
		m_pm->DoCase(_T("ModifyErrorPwKillFocus"));
	}
	else
	{
		m_pm->DoCase(_T("ModifyInfoPwKillFocus"));
	}
	OnCheckUserPasswdEditKillFocus(msg);
	return true;
}

bool CUserManagerLogic::OnCheckUserPasswdEditKillFocus( TNotifyUI& msg )
{
	String strNewPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtNewUserPasswd.c_str());
	String strCheckPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtCheckUserPasswd.c_str());

	if ( strNewPassWord != strCheckPassWord && strCheckPassWord != _T("") )
	{    
		m_pm->DoCase(_T("ModifyCheckPasswordError"));
	}
	else
	{
		m_pm->DoCase(_T("ModifyCheckPasswordSuccess"));
	}
	return true;
}

void CUserManagerLogic::UpdatePasswordTime()
{
    TTpPasswordUpdateInfo tTpPasswordUpdateInfo;
    ComInterface->GetPasswordUpdateInfo(tTpPasswordUpdateInfo);
    if (tTpPasswordUpdateInfo.m_bOpen == TRUE)
    {
        //当前系统时间
        SYSTEMTIME systime;
        GetLocalTime( &systime );
        TTPTime tTptimeCur;
        tTptimeCur.m_wYear     = systime.wYear;
        tTptimeCur.m_byMonth   = systime.wMonth;
        tTptimeCur.m_byMDay    = systime.wDay;
        tTptimeCur.m_byHour    = systime.wHour;
        tTptimeCur.m_byMinute  = systime.wMinute;
        tTptimeCur.m_bySecond  = systime.wSecond;

        tTpPasswordUpdateInfo.m_tTime = tTptimeCur;
        ComInterface->SetTpadPasswordUpdate(tTpPasswordUpdateInfo);
    }
}