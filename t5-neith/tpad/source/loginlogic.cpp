#include "StdAfx.h"
#include "UIDataMgr.h"
#include "loginlogic.h"
#include "messageboxlogic.h"
#include "mainframelogic.h"


APP_BEGIN_MSG_MAP(CLoginLogic, CNotifyUIImpl)

	MSG_CLICK(_T("BtnLogin"), OnBtnLogin)
    MSG_CLICK(_T("BtnNetCfg"), OnBtnNetCfg)
    MSG_CLICK(_T("BtnPowerOff"), OnBtnPowerOff)

	MSG_RETURN(_T("EdPassword"), OnBtnLogin)
	MSG_RETURN(_T("EdUserName"), OnBtnLogin)
	MSG_RETURN(_T("EdIp"), OnBtnLogin)

	MSG_SELECTCHANGE(_T("CheckAutoLogin"), OnCheckAutoLogin)
	MSG_SELECTCHANGE(_T("CheckRemPassWord"), OnCheckRemPassWord)

	MSG_TEXTCHANGED(_T("EdUserName"), OnEdUserNameTextChange)

	USER_MSG( UI_CNS_CONNECTED, OnConnectRsp )
	USER_MSG( UI_CNS_LOGIN_TIMEOUT, OnCnsLoginTimeOut )	
	USER_MSG( UI_UMS_GRAB_LOGIN_NOTIFY, OnUmsGrabLogin )	
	USER_MSG(UI_TPAD_SETSYSNAME, OnSysNameChange)
	USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

APP_END_MSG_MAP()

CLoginLogic::CLoginLogic(void)
{
    m_bHaveLogin = FALSE;
}


CLoginLogic::~CLoginLogic(void)
{
}

bool CLoginLogic::OnBtnLogin( TNotifyUI& msg )
{
#ifndef _DEBUG
    String strName = ITPadCommonOp::GetControlText(m_pm,_T("EdUserName"));
    if ( wcscmp( strName.c_str(), _T(MANAGER_USER) ) == 0)
    {
        vector<TNodeInfo> vctNodeList;
        if ( !ComInterface->IsReadyLogin( vctNodeList ) )
        {
            vector<TNodeInfo>::iterator itr = vctNodeList.begin();
            BOOL bIsCncReg = FALSE;
            BOOL bIsCenterltrlReg = FALSE;
            while( itr != vctNodeList.end() )
            {
                if ( itr->emSubType == emTPad_cnc )
                {
                    bIsCncReg = TRUE;
                }
                else if ( itr->emSubType == emTPad_centerctrl )
                {
                    bIsCenterltrlReg = TRUE;
                }

                itr++;
            }

            if ( !bIsCncReg )
            {
                ShowMessageBox((_T("��½ʧ�ܣ��᳡����ģ��δ����")),false);
                return false;
            }
        } 
    }
#endif 


	if (msg.sType == _T("return"))
	{
		CButtonUI* pBtn = (CButtonUI*)ITPadCommonOp::FindControl(m_pm,_T("BtnLogin"));
		if (pBtn)
		{
			pBtn->Activate();
			return true;
		}
	}

	CEditUI* pEdtIp = (CEditUI*)ITPadCommonOp::FindControl(m_pm,_T("EdIp"));
	CString strIP = _T("");
	u32 dwIp;
	if (pEdtIp)
	{
		strIP = pEdtIp->GetText();
	}
    CString strIPTmp = strIP;
	//if(!UIDATAMGR->IsValidIpV4(pEdtIp))
    EmProtocolVersion emIpType = emIPV4;
    if ( CCallAddr::IsValidIpV4(CT2A(strIPTmp)) )
    {
        emIpType = emIPV4;
        UIDATAMGR->GetClearIP(strIP);
        dwIp = ntohl( inet_addr( CT2A(strIP) ) );
    }
    else if( UIDATAMGR->IsValidIpV6(CT2A(strIPTmp)) )
    {
        emIpType = emIPV6;
    }
    else
	{
		ShowMessageBox((_T("��������ַ�Ƿ�")),false);
		pEdtIp->SetFocusX();
		return false;
	}

	CEditUI* pEdUserName = (CEditUI*)ITPadCommonOp::FindControl(m_pm,_T("EdUserName"));
	String strUserName = _T("");
	if (pEdUserName)
	{
		strUserName = pEdUserName->GetText();
	}
	if( strUserName.empty() )
	{
		ShowMessageBox((_T("�û�������Ϊ��")),false);
		pEdUserName->SetFocusX();
		return false;
	}

	CEditUI* pEdPassword = (CEditUI*)ITPadCommonOp::FindControl(m_pm,_T("EdPassword"));
	String strPassword = _T("");
	if (pEdUserName)
	{
		strPassword = pEdPassword->GetText();
	}
	if( strPassword.empty() )
	{
		ShowMessageBox((_T("���벻��Ϊ��")),false);
		pEdPassword->SetFocusX();
		return false;
	}

    ITPadCommonOp::EnableControl( false, m_pm, _T("BtnLogin") );

    ComInterface->SetAutoLogin( FALSE );

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
        ITPadCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );
		return false;
	}

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
			ITPadCommonOp::SetControlText(tchPassWord, m_pm, _T("EdPassword"));
		}
		else
		{
			ITPadCommonOp::SetControlText(_T(""), m_pm, _T("EdPassword"));
		}
	}
	return true;
}


bool CLoginLogic::OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ITPadCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );
    
	bool bIsSuc = wParam;
	if ( bIsSuc )
	{
        ITPadCommonOp::ShowControl( !bIsSuc, m_pm, _T("PageLogin") );
        ITPadCommonOp::ShowControl( bIsSuc, m_pm, _T("PageTPadMain") );
        WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), bIsSuc );	
        WINDOW_MGR_PTR->ShowWindow( g_strNetCfgDlg.c_str(), false );

		ITPadCommonOp::ShowControl(false, m_pm,_T("EdPassword"));
		ITPadCommonOp::ShowControl(false, m_pm,_T("EdUserName"));
		ITPadCommonOp::ShowControl(false, m_pm,_T("EdIp"));
        m_bHaveLogin = TRUE;
	}
    else
    {
        //�Զ���½ʱ����ʾ����
        if ( ComInterface->IsAutoLogin() )
        {
            return true;
        }

		ITPadCommonOp::ShowControl(true, m_pm,_T("EdPassword"));
		ITPadCommonOp::ShowControl(true, m_pm,_T("EdUserName"));
		ITPadCommonOp::ShowControl(true, m_pm,_T("EdIp"));

		switch( lParam )
		{
        case tp_LoginUms_NameError:
            {
                ShowMessageBox(_T("��¼ʧ��:�û�������"));                 
            }
            break;
        case tp_LoginUms_PwdError:
            {
                TLoginInfo tLoginUser = ComInterface->GetLoginInfo();
                if ( strcmp( T300E_TPAD_SUPERUSRNAME, tLoginUser.achName) == 0 )
                {
                    ShowMessageBox(_T("��¼ʧ��:�����������"));
                }
                else
                {
                    TLoginRet tTLoginRet;
                    ComInterface->GetLoginRet(tTLoginRet);
                    CString strtmp = _T("");
                    strtmp.Format(_T("��¼ʧ��:�����������,����%d���������,���򽫻�������¼"), tTLoginRet.m_byLockNumber - tTLoginRet.m_byNumber);
                    ShowMessageBox(strtmp); 
                }
            }
            break; 
        case tp_LoginUms_MaxLogin:
            {
                ShowMessageBox(_T("��¼ʧ��:�ﵽ�û���¼����")); 
            }
            break;
        case tp_LoginUms_Logged:
            {
                ShowMessageBox(_T("��¼ʧ��:�û��Ѿ���¼")); 
            }
            break;
        case  tp_LoginUms_SysIniting:
            {
                ShowMessageBox(_T("��¼ʧ��:ϵͳ����׼��")); 
            }
            break;
		case ERR_TPAD_TCPCONNECT:
			{
				ShowMessageBox(_T("��¼ʧ��:��������ʧ��")); 
			}
			break;
		case tp_LoginUms_locking:
			{
				ShowMessageBox(_T("��¼ʧ��:�˺ű�����")); 
			}
			break;
        default:
            {
                ShowMessageBox(_T("��¼ʧ��"));              
            }
            break; 
        }       
    }
    
	return true;
}

bool CLoginLogic::OnCnsLoginTimeOut( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    ITPadCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );

    //�Զ���½ʱ����ʾ����
    if ( ComInterface->IsAutoLogin() )
    {
        return true;
    }
	else
	{
		CMainFrameLogic::GetSingletonPtr()->SetActiveExit( TRUE );//��ʱ���Զ�����
	}

	ShowMessageBox(_T("���ӳ�ʱ"));
	return true;
}

bool CLoginLogic::OnUmsGrabLogin( WPARAM wParam, LPARAM lParam, bool& bHandle )
{   
    CMainFrameLogic::GetSingletonPtr()->SetActiveExit( TRUE );//�����ǲ��Զ�����

	if ( !WINDOW_MGR_PTR->IsWindowVisible(_T("MessageBoxDlg")) )//pc�洦��������Ϣ
	{
		ShowMessageBox(_T("�����ͻ�������"));
	}

	OnDisconnect( wParam, lParam, bHandle );

	return true;
}

bool CLoginLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    ITPadCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );

    if ( m_bHaveLogin )
    {
        //��½�ɹ���������ʱ���µ�¼������ʾ��Ϣ
        CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
        TCHAR tchPassWord[MAX_NAME_LEN]={0};
        GetPrivateProfileString(_T("LoginInfo"), _T("PassWord"),_T(""), tchPassWord, MAX_NAME_LEN-1, strIniPath);
        ITPadCommonOp::SetControlText(tchPassWord, m_pm, _T("EdPassword"));
    }  

    ITPadCommonOp::ShowControl(true, m_pm,_T("EdPassword"));
    ITPadCommonOp::ShowControl(true, m_pm,_T("EdUserName"));
    ITPadCommonOp::ShowControl(true, m_pm,_T("EdIp"));

    m_bHaveLogin = FALSE;

	return true;
}

bool CLoginLogic::OnSysNameChange(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath(_T("cnc"));
	TCHAR tchSysName[MAX_NAME_LEN]={0};
	GetPrivateProfileString(_T("SysNameInfo"),_T("name"), _T("���ʻ᳡����̨"),tchSysName, MAX_NAME_LEN, strIniPath);
	ITPadCommonOp::SetControlText(tchSysName, m_pm, _T("lbSysName"));
	return true;
}

bool CLoginLogic::OnBtnNetCfg(TNotifyUI& msg)
{
    ITPadCommonOp::ShowControl( false, m_pm, _T("PageLogin") );
    WINDOW_MGR_PTR->ShowWindow( g_strNetCfgDlg.c_str(), true );
    return true;
}

bool CLoginLogic::OnBtnPowerOff(TNotifyUI& msg)
{
    int nResult = ShowMessageBox( _T("�Ƿ�Ҫ�ر�ϵͳ��"), true );
    if ( IDOK == nResult )
    {
#ifndef _DEBUG

        ComInterface->ExitWindowsOS( emShutDown );
#else
        //UINT uExitCode = 0;
        //ExitProcess( uExitCode );
        TerminateProcess(GetCurrentProcess(), 0); 
#endif
    }

    return true;
}

//�Զ���¼һ����ס����
bool CLoginLogic::OnCheckAutoLogin( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)msg.pSender;
	CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
	if (pCheckAutoLogin && pCheckRemPassWord)
	{
		if (pCheckAutoLogin->GetCheck())
		{
			pCheckRemPassWord->SetCheckNoMsg(true);
		}
	}
	return true;
}

//ȡ����ס���� �����Զ���¼
bool CLoginLogic::OnCheckRemPassWord( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
	CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)msg.pSender;
	if (pCheckAutoLogin && pCheckRemPassWord)
	{
		if (pCheckAutoLogin->GetCheck())
		{
			if ( !pCheckRemPassWord->GetCheck())
			{
				pCheckAutoLogin->SetCheckNoMsg(false);
			}
		}
	}
	return true;
}