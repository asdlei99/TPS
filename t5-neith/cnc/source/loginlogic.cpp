#include "StdAfx.h"
#include "loginlogic.h"
#include "messageboxlogic.h"
#include <direct.h>
#include "mainframelogic.h"

template<> CLoginLogic* Singleton<CLoginLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CLoginLogic, CNotifyUIImpl)

	MSG_CLICK(_T("BtnLogin"), OnBtnLogin)

	MSG_RETURN(_T("EdPassword"), OnBtnLogin)
	MSG_RETURN(_T("EdUserName"), OnBtnLogin)
	MSG_RETURN(_T("EdIp"), OnBtnLogin)

	MSG_TEXTCHANGED(_T("EdUserName"), OnEdUserNameTextChange)

	USER_MSG( UI_CNS_CONNECTED, OnConnectRsp )
	USER_MSG( UI_CNS_LOGIN_TIMEOUT, OnCnsLoginTimeOut )	
	USER_MSG( UI_UMS_GRAB_LOGIN_NOTIFY, OnUmsGrabLogin )	
	USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

APP_END_MSG_MAP()

CLoginLogic::CLoginLogic(void)
{
}


CLoginLogic::~CLoginLogic(void)
{
}

bool CLoginLogic::OnBtnLogin( TNotifyUI& msg )
{
	if (msg.sType == _T("return"))
	{
		CButtonUI* pBtn = (CButtonUI*)ICncCommonOp::FindControl(m_pm,_T("BtnLogin"));
		if (pBtn)
		{
			pBtn->Activate();
			return true;
		}
	}

	CEditUI* pEdtIp = (CEditUI*)ICncCommonOp::FindControl(m_pm,_T("EdIp"));
	CString strIP = _T("");
	u32 dwIp;
	if (pEdtIp)
	{
		strIP = pEdtIp->GetText();
	}
    CString strIPTmp = strIP;
	//if(!UIDATAMGR->IsValidIpV4(pEdtIp))
    EmProtocolVersion emIpType = emIPV4;
    if( CCallAddr::IsValidIpV4(CT2A(strIPTmp)) )
	{
		emIpType = emIPV4;
        UIDATAMGR->GetClearIP(strIP);
        dwIp = ntohl( inet_addr( CT2A(strIP) ) );
	}
    else if ( UIDATAMGR->IsValidIpV6(CT2A(strIPTmp)) )
    {
        emIpType = emIPV6;
    }
    else
    {
        ShowMessageBox((_T("服务器地址非法")),false);
        pEdtIp->SetFocusX();
        return false;
    }

	CEditUI* pEdUserName = (CEditUI*)ICncCommonOp::FindControl(m_pm,_T("EdUserName"));
	String strUserName = _T("");
	if (pEdUserName)
	{
		strUserName = pEdUserName->GetText();
	}
	if( strUserName.empty() )
	{
		ShowMessageBox((_T("用户名不能为空")),false);
		pEdUserName->SetFocusX();
		return false;
	}

	CEditUI* pEdPassword = (CEditUI*)ICncCommonOp::FindControl(m_pm,_T("EdPassword"));
	String strPassword = _T("");
	if (pEdUserName)
	{
		strPassword = pEdPassword->GetText();
	}
	if( strPassword.empty() )
	{
		ShowMessageBox((_T("密码不能为空")),false);
		pEdPassword->SetFocusX();
		return false;
	}

    ICncCommonOp::EnableControl( false, m_pm, _T("BtnLogin") );
#ifdef LOGIN
	u16 uRe = NO_ERROR;
    if (emIpType == emIPV6)
    {
        uRe = ComInterface->Connect( CT2A(strIP), CONNETCT_CNS_PORT, strUserName.c_str(), strPassword.c_str() );
    }
    else
    {
        uRe = ComInterface->Connect( dwIp, CONNETCT_CNS_PORT, strUserName.c_str(), strPassword.c_str() );
    }
	if ( uRe != NO_ERROR )
	{  
        ICncCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );
		return false;
	}
#else
    NOTIFY_MSG( UI_CNS_CONNECTED, TRUE, NO_ERROR );
    //NOTIFY_MSG( UI_CNS_CONFSTATE_NOTIFY, NULL, NULL );
#endif

	return true;
}

bool CLoginLogic::OnEdUserNameTextChange(TNotifyUI& msg)
{
	CEditUI* pEditName = (CEditUI*)msg.pSender;
	if (pEditName)
	{
		CString strInputName = pEditName->GetText();

		CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
		TCHAR tchUserName[MAX_NAME_LEN]={0};
		GetPrivateProfileString(_T("LoginInfo"), _T("UserName"),_T(""), tchUserName, MAX_NAME_LEN-1, strIniPath);

		if ( wcscmp(tchUserName, strInputName) == 0 )
		{
			TCHAR tchPassWord[MAX_NAME_LEN]={0};
			GetPrivateProfileString(_T("LoginInfo"), _T("PassWord"),_T(""), tchPassWord, MAX_NAME_LEN-1, strIniPath);
			ICncCommonOp::SetControlText(tchPassWord, m_pm, _T("EdPassword"));
		}
		else
		{
			ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdPassword"));
		}
	}
	return true;
}

bool CLoginLogic::OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ICncCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );

	bool bIsSuc = wParam;
	if ( bIsSuc )
	{
        ICncCommonOp::ShowControl( !bIsSuc, m_pm, _T("PageLogin") );
        ICncCommonOp::ShowControl( bIsSuc, m_pm, _T("PageCnsManage") );
        WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), bIsSuc );	

		ICncCommonOp::ShowControl(false, m_pm,_T("EdPassword"));
		ICncCommonOp::ShowControl(false, m_pm,_T("EdUserName"));
		ICncCommonOp::ShowControl(false, m_pm,_T("EdIp"));
	}
    else
    {
		if ( !UIDATAMGR->IsPcVersion() )
		{
			return true;
		}

		ICncCommonOp::ShowControl(true, m_pm,_T("EdPassword"));
		ICncCommonOp::ShowControl(true, m_pm,_T("EdUserName"));
		ICncCommonOp::ShowControl(true, m_pm,_T("EdIp"));

		switch( lParam )
		{
        case ERR_UMC_LOGIN_UMS_USER_ERR:
            {
                ShowMessageBox(_T("登录失败:用户名错误"));                 
            }
            break;
        case ERR_UMC_LOGIN_UMS_PSWD_ERR:
            {
                TLoginInfo tLoginUser;
                ComInterface->GetLoginInfo(tLoginUser);
                if ( strcmp( T300E_TPAD_SUPERUSRNAME, tLoginUser.achName) == 0 )
                {
                    ShowMessageBox(_T("登录失败:密码输入错误"));
                }
                else
                {
                    TLoginRet tTLoginRet;
                    ComInterface->GetLoginRet(tTLoginRet);
                    CString strtmp = _T("");
                    strtmp.Format(_T("登录失败:密码输入错误,还有%d次输入机会,否则将会锁定登录"), tTLoginRet.m_byLockNumber - tTLoginRet.m_byNumber);
                    ShowMessageBox(strtmp);  
                }
            }
            break; 
        case ERR_UMC_LOGIN_UMS_MAX_LOGIN:
            {
                ShowMessageBox(_T("登录失败:达到用户登录上限")); 
            }
            break;
        case ERR_UMC_LOGIN_UMS_LOGED:
            {
                ShowMessageBox(_T("登录失败:用户已经登录")); 
            }
            break;
        case  ERR_UMC_LOGIN_UMS_SYSINITING:
            {
                ShowMessageBox(_T("登录失败:系统正在准备")); 
            }
            break;
		case ERR_CNC_TCPCONNECT:
			{
				ShowMessageBox(_T("登录失败:网络连接失败")); 
			}
			break;
		case ERR_UMC_LOGIN_UMS_LOCKING:
			{
				ShowMessageBox(_T("登录失败:账号被锁定")); 
			}
			break;
        default:
            {
                ShowMessageBox(_T("登录失败"));              
            }
            break; 
        }       
    }

	return true;
}

bool CLoginLogic::OnCnsLoginTimeOut( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    ICncCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );

	ShowMessageBox(_T("连接超时"));
	return true;
}

bool CLoginLogic::OnUmsGrabLogin( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (UIDATAMGR->IsPcVersion()&& !WINDOW_MGR_PTR->IsWindowVisible(_T("MessageBoxDlg")))//pc版处理抢登消息
	{
		ShowMessageBox(_T("其他客户端抢登"));
	}

	OnDisconnect( wParam, lParam, bHandle );

	return true;
}

bool CLoginLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    ICncCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );

	ICncCommonOp::ShowControl(true, m_pm,_T("EdPassword"));
	ICncCommonOp::ShowControl(true, m_pm,_T("EdUserName"));
	ICncCommonOp::ShowControl(true, m_pm,_T("EdIp"));

	return true;
}

void CLoginLogic::UpdateSysName()
{
	CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
	TCHAR tchSysName[MAX_NAME_LEN]={0};
	GetPrivateProfileString(_T("SysNameInfo"),_T("name"), _T("网呈会场控制台"),tchSysName, MAX_NAME_LEN, strIniPath);

	ICncCommonOp::SetControlText(tchSysName, m_pm, _T("lbSysName"));
}