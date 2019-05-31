#include "StdAfx.h"
#include "regservicelogic.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"


APP_BEGIN_MSG_MAP(CRegServiceLogic,CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("RegServiceLayout"), OnCreate)
	MSG_INIWINDOW(_T("RegServiceLayout"), OnInit)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)

	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	MSG_CLICK(_T("BtnFixOrCancel"), OnBtnFixOrCancel)
	MSG_SELECTCHANGE(_T("CheckIsGk"), OnBtnIsGk)
	MSG_SELECTCHANGE(_T("CheckIsQT"), OnBtnIsQT)

	USER_MSG(UI_CNS_REGSIP_NOTIFY,OnSipNty)
	USER_MSG(UI_CNS_REGRESULT_NOTIFY,OnRegResultNty)
	USER_MSG(UI_CNS_SIPREG_ALIASREPEAT_NOTIFY,OnRegAliasRepeatNty)
	USER_MSG(UI_CNS_REG_GK_NTY,OnGkNty)
	USER_MSG(UI_CNS_REG_GK_RSP,OnGkRsp)
	USER_MSG(UI_CNSTOOL_MSG_CallSer_NTY,OnCallSerNty)
	USER_MSG(UI_CNSTOOL_MSG_CallSer_IND,OnCallSerInd)
	USER_MSG(UI_CNSTOOL_MSG_UpgradeSer_NTY,OnUpSerNty)
	USER_MSG(UI_CNSTOOL_MSG_UpgradeSer_IND,OnUpSerInd)
 	USER_MSG(UI_CNSTOOL_MSG_BD_NTY,OnWBServiceIPNty)
 	USER_MSG(UI_CNSTOOL_MSG_BD_IND,OnWBServerInd)
	//量子加密
	USER_MSG(UI_CNC_QTENCRYPT_IND,OnQTEncryptInd)
	USER_MSG(UI_CNC_QTENCRYPT_NTY,OnQTEncryptNty)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
APP_END_MSG_MAP()

const String CRegServiceLogic::m_strBtnFixOrCancel = _T("BtnFixOrCancel");
const String CRegServiceLogic::m_strBtnOk = _T("BtnOk");
const String CRegServiceLogic::m_strBtnIsGk = _T("BtnIsGk");
const String CRegServiceLogic::m_strEdtRigIp = _T("edtRigIp");
const String CRegServiceLogic::m_strEdtGKIp = _T("edtGKIp");
const String CRegServiceLogic::m_strEdtCallIp = _T("edtCallIp");
const String CRegServiceLogic::m_strEdtUpgradeIp = _T("edtUpgradeIp");
const String CRegServiceLogic::m_strEdtDCIp = _T("edtDCIp");
const String CRegServiceLogic::m_strEdtQTIp = _T("edtQuantumIp");
const String CRegServiceLogic::m_strEdtQTID = _T("edtQuantumID");

CRegServiceLogic::CRegServiceLogic(void)
{
	m_bIsFix = false;
	m_bIsGK = false;
}


CRegServiceLogic::~CRegServiceLogic(void)
{
}

bool CRegServiceLogic::OnCreate( TNotifyUI& msg )
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

bool CRegServiceLogic::OnInit( TNotifyUI& msg )
{
	TTPSipRegistrarCfg tOldSipCfg;
	ComInterface->GetSipCfg( tOldSipCfg );
	TTPGKCfg tOldGkCfg;
	ComInterface->GetGkCfg( tOldGkCfg );
	TTPCallSerInfo tCnsCallSerInfo;
	ComInterface->GetCallServerInfo( tCnsCallSerInfo );
	TTPUpgradeSer tCnsUpgSerInfo;
	ComInterface->GetUpgradeSerInfo( tCnsUpgSerInfo );
	TTPDataConfInfo tWBSerIp;
	ComInterface->GetWBSerIp( tWBSerIp );
	
	CLabelUI *plbRigIp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbRigIp") );
	CLabelUI *plbsGk = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbsGk") );
	CLabelUI *plbGKIp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbGKIp") );
	CLabelUI *plbCallIp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbCallIp") );
	CLabelUI *plbUpgradeIp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbUpgradeIp") );
	CLabelUI *plbDCIp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbDCIp") );

	if (plbRigIp)
	{
		in_addr tAddr;
		tAddr.S_un.S_addr = tOldSipCfg.dwRegIP;
		String strServiceIP = (CA2T)inet_ntoa(tAddr);
		if ( strServiceIP == _T("0.0.0.0") )
		{
			strServiceIP = _T("");
		}

		plbRigIp->SetText(strServiceIP.c_str());
	}

	bool bHandle = false;
	OnGkNty( 0 , 0, bHandle );

	return true;
}


bool CRegServiceLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsFix = false;

// 	OnGkNty( 0 , 0, bHandle );
// 	TTPCallSerInfo tTPCallSerInfo;
// 	SetCallServerInfo( tTPCallSerInfo );
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
	ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));
	m_pm->DoCase(_T("caseSetCancel"));
	return true;
}

bool CRegServiceLogic::OnBtnOk( TNotifyUI& msg )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{		
		ShowMessageBox((_T("会议中，不能修改服务器配置")),false);
		return false;
	}

	CEditUI *pEdtRegIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtRigIp.c_str() );   
	CEditUI *pEdtGKIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtGKIp.c_str() );
	CEditUI *pEdtCallIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtCallIp.c_str() );
	CEditUI *pEdtUpgradeIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtUpgradeIp.c_str() );
	CEditUI *pEdtDCIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtDCIp.c_str() );
    CCheckBoxUI *pCheckBoxQt = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsQT") );
	CEditUI *pEdtQTIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtQTIp.c_str() );
	CEditUI *pEdtQTID = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtQTID.c_str() );


	if (pEdtRegIp)
	{	
		CString strRigIp = pEdtRegIp->GetText();
		//if (!strRigIp.IsEmpty())//可以为空
		{
			TTPSipRegistrarCfg tSipcfg;
			tSipcfg.bUsed = TRUE;

			if(!strRigIp.IsEmpty() && !CCallAddr::IsValidIpV4(CT2A(strRigIp)))
			{
				ShowMessageBox((_T("网呈注册服务器地址非法")),false);
				pEdtRegIp->SetFocusX();
				return false;
			}

            ULONG dwAddr = 0;
            if ( !strRigIp.IsEmpty() )
            {
                UIDATAMGR->GetClearIP(strRigIp);
                dwAddr = inet_addr(CT2A(strRigIp));
            }

			tSipcfg.dwRegIP = /*htonl*/(dwAddr);
			tSipcfg.wRegPort = 5060;
			tSipcfg.wExpire = 40;

			TTPSipRegistrarCfg tOldSipCfg;
			ComInterface->GetSipCfg( tOldSipCfg );

			if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP )
			{
				BOOL bInConf = ComInterface->IsInConf();
				if ( bInConf )
				{		
					ShowMessageBox((_T("会议中，不能修改服务器配置")),false);
					return false;
				}

				u16 wRet = NO_ERROR;		 
				wRet = ComInterface->CnsRegSipService( tSipcfg );
				if ( wRet != NO_ERROR )
				{
					bool bHandle = false;
					OnSipNty(NULL,NULL,bHandle);
					ShowPopMsg(_T("设置Sip失败"));

				}	
			}
		}

	}
	if (pEdtGKIp)
	{
		CString strGKIp = pEdtGKIp->GetText();

		if (m_bIsGK)//开启才校验
		{
			if (!strGKIp.IsEmpty())//不可以为空
			{
				if(!strGKIp.IsEmpty()  && pEdtGKIp->IsEnabled() && !CCallAddr::IsValidIpV4((CT2A(strGKIp))))
				{
					ShowMessageBox((_T("GK服务器地址非法")),false);
					pEdtGKIp->SetFocusX();
					return false;
				}
			}
			else
			{
				ShowMessageBox(_T("GK服务器地址不能为空"));
				pEdtGKIp->SetFocusX();
				return false;
			}
		}

		TTPGKCfg tSipcfg; 
		tSipcfg.wExpire = 40; 
		tSipcfg.bUsed = m_bIsGK;
		if ( strGKIp.IsEmpty() )
		{
			tSipcfg.dwGKIP = 0;
		}
		else
		{
            UIDATAMGR->GetClearIP(strGKIp);
			tSipcfg.dwGKIP = /*htonl*/(inet_addr(CT2A(strGKIp)));  
		}

		TTPGKCfg tOldGkCfg;
		ComInterface->GetGkCfg( tOldGkCfg );

		//不同才更新
		if ( ( m_bIsGK != (bool)tOldGkCfg.bUsed ) || ( tSipcfg.dwGKIP != tOldGkCfg.dwGKIP ) )
		{      
			BOOL bInConf = ComInterface->IsInConf();
			if ( bInConf )
			{		
				ShowMessageBox((_T("会议中，不能修改服务器配置")),false);
				return false;
			}
			else
			{
				u16 wRet  = ComInterface->CnsRegGkService( tSipcfg );
				if ( wRet != NO_ERROR )
				{
					bool bHandle = false;
					OnGkNty(NULL,NULL,bHandle);
					ShowPopMsg(_T("设置GK失败"));

				}
			}
		}
	}

	if (pEdtCallIp)
	{
		CString strCallIp = pEdtCallIp->GetText();
		//if (!strCallIp.IsEmpty())//可以为空
		{
			if( !strCallIp.IsEmpty() && !CCallAddr::IsValidIpV4((CT2A(strCallIp))) )
			{
				ShowMessageBox((_T("网呈呼叫服务器地址非法")),false);
				pEdtCallIp->SetFocusX();
				return false;
			}

			TTPCallSerInfo tCallSerInfo;

			u32_ip dwCallServiceIP = 0;
            if ( !strCallIp.IsEmpty() )
            {
                CString strCallIptmp = strCallIp;

                UIDATAMGR->GetClearIP(strCallIptmp);
                dwCallServiceIP = inet_addr(CT2A(strCallIptmp));
            }

			TTPCallSerInfo tCnsCallSerInfo;
			ComInterface->GetCallServerInfo( tCnsCallSerInfo );
			if ( tCnsCallSerInfo.dwCallServiceIP != dwCallServiceIP )
			{
				if(!strCallIp.IsEmpty() && !CCallAddr::IsValidIpV4((CT2A(strCallIp))))
				{
					ShowMessageBox((_T("呼叫服务器地址无效")),false);
					pEdtCallIp->SetFocusX();
					return false;
				}

				if(!strCallIp.IsEmpty() && !CCallAddr::IsValidCallIP( ntohl(dwCallServiceIP), NULL, 0))
				{
					ShowMessageBox((_T("呼叫服务器地址不可用")),false);
					pEdtCallIp->SetFocusX();
					return false;
				}

                if ( !strCallIp.IsEmpty() )
                {
                    UIDATAMGR->GetClearIP(strCallIp);
                    dwCallServiceIP = inet_addr(CT2A(strCallIp));
                }

				tCallSerInfo.dwCallServiceIP = dwCallServiceIP;

				BOOL bInConf = ComInterface->IsInConf();
				if ( bInConf )
				{
					ShowMessageBox((_T("会议中，不能修改服务器配置")),false);
					return false;
				}

				u16 wRet = NO_ERROR;	
				TTPCallSerInfo tOldCallSerInfo;
				ComInterface->GetCallServerInfo( tOldCallSerInfo );

				if ( tOldCallSerInfo.dwCallServiceIP != dwCallServiceIP )
				{
					wRet = ComInterface->CallServerCmd( tCallSerInfo );		
					if ( wRet != NO_ERROR )
					{
						bool bHandle = false;
						OnCallSerNty(NULL,NULL,bHandle);
						ShowPopMsg(_T("设置呼叫服务器失败"));
					}	
				}
			}
		}
	}
	if (pEdtUpgradeIp)
	{
		CString strUpgradeIp = pEdtUpgradeIp->GetText();
		//if (!strUpgradeIp.IsEmpty())//可以为空
		{
			if( !strUpgradeIp.IsEmpty() && !CCallAddr::IsValidIpV4(CT2A(strUpgradeIp)) )
			{
				ShowMessageBox((_T("升级服务器地址非法")),false);
				pEdtUpgradeIp->SetFocusX();
				return false;
			}
            
            u32_ip dwUpgServiceIP = 0;
            if ( !strUpgradeIp.IsEmpty() )
            {
                UIDATAMGR->GetClearIP(strUpgradeIp);
                dwUpgServiceIP = ntohl(inet_addr(CT2A(strUpgradeIp)));
            }

			TTPUpgradeSer tCnsUpgSerInfo;
			ComInterface->GetUpgradeSerInfo( tCnsUpgSerInfo );

			//u32_ip dwUpgServiceIP = /*htonl*/());

			TTPUpgradeSer tUpgradeSer;
			tUpgradeSer.dwSerIP =  htonl(dwUpgServiceIP);
			if ( tUpgradeSer.dwSerIP != tCnsUpgSerInfo.dwSerIP)
			{	    
				u16 wRet = NO_ERROR;		 
				wRet = ComInterface->UpgradeSerCmd( tUpgradeSer );
				if ( wRet != NO_ERROR )
				{
					bool bHandle = false;
					OnUpSerNty(NULL,NULL,bHandle);
					ShowPopMsg(_T("设置升级服务器失败"));

				}	
			}
		}
	}
	if (pEdtDCIp)
	{
		CString strDCIp = pEdtDCIp->GetText();
		//if (!strDCIp.IsEmpty())// 可以为空
		{
            UIDATAMGR->GetClearIP(strDCIp);
            u32_ip dwIp = inet_addr(CT2A(strDCIp));
			if( !strDCIp.IsEmpty() && !CCallAddr::IsValidIpV4(CT2A(strDCIp)) )
			{
				ShowMessageBox((_T("数据会议服务器地址非法")),false);
				pEdtDCIp->SetFocusX();
				return false;
			}
            if ( strDCIp.IsEmpty() )
            {
                dwIp = 0;
            }

			u16 wRet = NO_ERROR;	
			TTPDataConfInfo tDataConfInfo;
			ComInterface->GetWBSerIp( tDataConfInfo );
			
			if ( tDataConfInfo.dwSerIP != dwIp )
			{
				u16 wRet = ComInterface->SetDataServerInfoCmd( /*htonl*/dwIp );
				if ( wRet != NO_ERROR )
				{
					bool bHandle = false;
					OnWBServiceIPNty(NULL,NULL,bHandle);
					ShowPopMsg(_T("设置数据会议服务器失败"));
				}		
			}
		}
	}

	//量子加密
	if (pCheckBoxQt && pEdtQTIp && pEdtQTID)
	{
		CString strQTIp = pEdtQTIp->GetText();

		if (!strQTIp.IsEmpty())//不可以为空
		{
			if(!CCallAddr::IsValidIpV4((CT2A(strQTIp))))
			{
				ShowMessageBox((_T("量子加密IP地址非法")),false);
				pEdtQTIp->SetFocusX();
				return false;
			}
		}
// 		else
// 		{
// 			ShowMessageBox(_T("量子加密IP地址不能为空"));
// 			pEdtQTIp->SetFocusX();
// 			return false;
// 		}

		CString strQTID = pEdtQTID->GetText();
// 		if (strQTID.IsEmpty())
// 		{
// 			ShowMessageBox(_T("量子加密ID地址不能为空"));
// 			pEdtQTID->SetFocusX();
// 			return false;
// 		}
		u32_ip dwQtIP = 0;
		if (!strQTIp.IsEmpty())
		{
            UIDATAMGR->GetClearIP(strQTIp);
			dwQtIP = inet_addr(CT2A(strQTIp));
		}
		unsigned long long dwQtID = 0;
		if (!strQTID.IsEmpty())
		{
			dwQtID = _ttoi64(strQTID);
			if ( 1 > dwQtID || dwQtID > 4294967295)
			{
				ShowMessageBox((_T("量子ID范围错误(1 - 4294967295)")),false);
				pEdtQTID->SetFocusX();
				return false;
			}
		}

		TTpQtEncryptCfg tQtEncrypt;
		tQtEncrypt.m_dwQtIP = dwQtIP;
		tQtEncrypt.m_dwQtID = dwQtID;
        tQtEncrypt.m_bOpen = pCheckBoxQt->IsSelected();

		TTpQtEncryptCfg tOldQtEncrypt;
		ComInterface->GetQTEncrypt(tOldQtEncrypt);
		
		if (tQtEncrypt.m_dwQtIP != tOldQtEncrypt.m_dwQtIP || tQtEncrypt.m_dwQtID != tOldQtEncrypt.m_dwQtID || tQtEncrypt.m_bOpen != tOldQtEncrypt.m_bOpen )
		{
			u16 wRet  = ComInterface->SetQtEncryptCfg( tQtEncrypt );
			if ( wRet != NO_ERROR )
			{
				bool bHandle = false;
				OnQTEncryptNty(NULL,NULL,bHandle);
				ShowPopMsg(_T("设置量子加密信息失败"));
			}
		}
	}

	OnBtnFixOrCancel(msg);
	return true;
}

bool CRegServiceLogic::OnBtnFixOrCancel( TNotifyUI& msg )
{
	m_bIsFix = !m_bIsFix;

	if ( m_bIsFix )
	{
		TTPCnsConfStatus tConfStatus = ComInterface->GetLocalCnsConfState();
		if ( tConfStatus.emState == em_CALL_CONNECTED )
		{
			ShowMessageBox((_T("会议中，不能修改服务器配置")),false);
			m_bIsFix = !m_bIsFix;
			return false;
		}

		BOOL bInConf = ComInterface->IsInConf();
		if ( bInConf )
		{		
			ShowMessageBox((_T("会议中，不能修改服务器配置")),false);
			m_bIsFix = !m_bIsFix;
			return false;
		}

		m_pm->DoCase(_T("caseSet"));

		ICncCommonOp::ShowControl(true,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("取 消"),m_pm,_T("BtnFixOrCancel"));	
	}
	else
	{	

		ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));

		m_pm->DoCase(_T("caseSetCancel"));

		bool bHandle = false;
		OnGkNty( 0, 0, bHandle );
		OnSipNty(0, 0, bHandle);
		OnCallSerNty(0, 0, bHandle);
		OnUpSerNty(0, 0, bHandle);
		OnWBServiceIPNty(0, 0, bHandle);
		OnQTEncryptNty(0, 0, bHandle);
		return true;
	}
	return true;
}

bool CRegServiceLogic::OnBtnIsGk( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	CEditUI *pEdtGKIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtGKIp.c_str() );
	if ( !pEdtGKIp )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		m_bIsGK = true;
		pEdtGKIp->SetAttribute(_T("enabled"),_T("true"));
	}
	else
	{
		m_bIsGK = false;
		pEdtGKIp->SetAttribute(_T("enabled"),_T("false"));
	}

	return true;
}

bool CRegServiceLogic::OnBtnIsQT( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	CEditUI *pEdtQTIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtQTIp.c_str() );
	if ( !pEdtQTIp )
	{
		return false;
	}
	CEditUI *pEdtQTID = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtQTID.c_str() );
	if ( !pEdtQTID )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		pEdtQTIp->SetAttribute(_T("enabled"),_T("true"));
		pEdtQTID->SetAttribute(_T("enabled"),_T("true"));
	}
	else
	{
		pEdtQTIp->SetAttribute(_T("enabled"),_T("false"));
		pEdtQTID->SetAttribute(_T("enabled"),_T("false"));
	}

	return true;
}

bool CRegServiceLogic::OnBtnBack( TNotifyUI& msg )
{

	if ( m_bIsFix )
    {
		CEditUI *pEdtRegIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtRigIp.c_str() );   
		CEditUI *pEdtGKIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtGKIp.c_str() );
		CEditUI *pEdtCallIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtCallIp.c_str() );
		CEditUI *pEdtUpgradeIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtUpgradeIp.c_str() );
		CEditUI *pEdtDCIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtDCIp.c_str() );
        
        TTPSipRegistrarCfg tOldSipCfg;
        ComInterface->GetSipCfg( tOldSipCfg );
		in_addr tAddr;
		tAddr.S_un.S_addr = tOldSipCfg.dwRegIP;

		String strOldInfo = CA2T(inet_ntoa(tAddr));
		if ( strOldInfo.compare(_T("0.0.0.0")) == 0 )
		{
			strOldInfo = _T("");
		}

		CString strRigIp = pEdtRegIp->GetText();
		TTPSipRegistrarCfg tSipcfg;
		tSipcfg.bUsed = TRUE;

        UIDATAMGR->GetClearIP(strRigIp);
		ULONG dwAddr = inet_addr(CT2A(strRigIp));
		if (!strRigIp.IsEmpty())
		{
			tSipcfg.dwRegIP = /*htonl*/(dwAddr);
		}

		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;

		//GK
		TTPGKCfg tOldGkCfg;
        ComInterface->GetGkCfg( tOldGkCfg );
		in_addr tGkAddr;
		tGkAddr.S_un.S_addr = tOldGkCfg.dwGKIP;
		String strOldGkInfo = CA2T(inet_ntoa(tAddr));
		if ( strOldGkInfo.compare(_T("0.0.0.0")) == 0 )
		{
			strOldGkInfo = _T("");
		}

		CString strGKIp = pEdtGKIp->GetText();
		TTPGKCfg tGkcfg; 
		tGkcfg.wExpire = 40; 
		tGkcfg.bUsed = m_bIsGK;
		if (!strGKIp.IsEmpty())
		{
            UIDATAMGR->GetClearIP(strGKIp);
			tGkcfg.dwGKIP = /*htonl*/(inet_addr(CT2A(strGKIp)));
		}
		  

		//CallServerIP
		CString strCallServiceIP = pEdtCallIp->GetText();
        UIDATAMGR->GetClearIP(strCallServiceIP);
		u32_ip dwCallServiceIP = inet_addr(CT2A(strCallServiceIP));
		
		if ( _T("") == strCallServiceIP )
		{
			dwCallServiceIP = 0;
		}
        
        TTPCallSerInfo tCnsCallSerInfo;
        ComInterface->GetCallServerInfo( tCnsCallSerInfo );
		in_addr tCallSerAddr;
		tCallSerAddr.S_un.S_addr = tCnsCallSerInfo.dwCallServiceIP;
		String strOldCallSerInfo = CA2T(inet_ntoa(tAddr));
		if ( strOldCallSerInfo.compare(_T("0.0.0.0")) == 0 )
		{
			strOldCallSerInfo = _T("");
		}

		//UpdSerIP
		TTPUpgradeSer tCnsUpgSerInfo;
        ComInterface->GetUpgradeSerInfo( tCnsUpgSerInfo );
		in_addr tUpdAddr;
		tUpdAddr.S_un.S_addr = tCnsUpgSerInfo.dwSerIP;
		String strOldUpdInfo = CA2T(inet_ntoa(tUpdAddr));
		if (strGKIp.IsEmpty()/* strOldUpdInfo.compare(_T("0.0.0.0")) == 0*/ )
		{
			strOldUpdInfo = _T("");
		}
        
		CString strUpdServiceIp = pEdtUpgradeIp->GetText();
        UIDATAMGR->GetClearIP(strUpdServiceIp);
		u32_ip dwUpgServiceIP = inet_addr(CT2A(strUpdServiceIp));

		if ( "" == strUpdServiceIp )
		{
			dwUpgServiceIP = 0;
		}
	
		if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP || strOldInfo.compare(strRigIp) != 0  || 
		( m_bIsGK != (bool)tOldGkCfg.bUsed ) || ( tGkcfg.dwGKIP != tOldGkCfg.dwGKIP ) || strOldGkInfo.compare(strGKIp) != 0 ||
		tCnsCallSerInfo.dwCallServiceIP != dwCallServiceIP || strOldCallSerInfo.compare(strCallServiceIP) != 0 ||
		dwUpgServiceIP != tCnsUpgSerInfo.dwSerIP || strOldUpdInfo.compare(strUpdServiceIp) != 0 )
		{

			int nResult = ShowMessageBox((_T("是否对编辑进行保存")),true);
			if ( IDOK == nResult )
			{
				TNotifyUI msg;
				if ( !OnBtnOk(msg) )
				{
					return false;
				}
			}
			else
			{
				TNotifyUI msg;
				OnBtnFixOrCancel( msg );
				m_pm->DoCase(_T("caseSetCancel"));
				WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strRegServiceDlg.c_str(),false );
			}
		}
		else
		{
			TNotifyUI msg;
			OnBtnFixOrCancel( msg );
			m_pm->DoCase(_T("caseSetCancel"));
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strRegServiceDlg.c_str(),false );
		}
	}
   
	return true;
}

bool CRegServiceLogic::OnSipNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPSipRegistrarCfg tSipCfg;
	ComInterface->GetSipCfg( tSipCfg );

	SetSipIP(tSipCfg);

	return NO_ERROR;
}

bool CRegServiceLogic::OnRegResultNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTpCnsRegUms emReg = (EmTpCnsRegUms)wParam;

	BOOL bOk = FALSE;
	CString strTemp = _T("");
	switch( emReg )
	{		
	case tp_CnsRegRet_Success:		//成功
		bOk  = TRUE;
		break;
	case tp_CnsRegRet_MaxRegNum:		//注册满
		strTemp =_T( "注册个数已达到最大值");
		break;
	case tp_CnsRegRet_MaxAliasNum:	//注册满
		strTemp = _T("注册别名的个数已达到最大值");
		break;
	case tp_CnsRegRet_MsgError:		//注册消息错误
		strTemp = _T("注册消息错误");
		break;
	case tp_CnsRegRet_AliasRepeat:	//别名重复
		strTemp = _T("注册别名重复");
		break;
	case tp_CnsRegRet_UnReg:		//删除时，未找到删除记录
		strTemp = _T("未找到删除记录");
		break;
	case tp_CnsRegRet_SysError:		//APP错误
		strTemp = _T("APP错误");
		break;
	case tp_CnsRegRet_NotFind:		//查找失败
		strTemp = _T("查找失败");
		break;   
	case tp_CnsRegRet_Unreachable:   //服务器不可达
		strTemp = _T("服务器不可达");
		break;
	default:
		strTemp = ""; //"未知错误";  //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
	}


	CString strName;
	//strName.Format( "会场 %s ", (s8*)lParam );

	if ( bOk )
	{
		ShowPopMsg((_T("注册网呈服务器成功")));
	}
	else
	{   
		strName = _T("注册网呈服务器失败");
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + ": " + strTemp;
		}
		ShowPopMsg(strName );
	}
	return NO_ERROR;
}

bool CRegServiceLogic::OnRegAliasRepeatNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)wParam;

	CString strName;
	strName.Format( _T("注册网呈服务器失败: "), (s8*)lParam );

	CString strTemp = _T("注册别名重复");

	u32 dwSize = tRepeatInfo.dwsize;
	if ( 1 == dwSize )
	{
		TTPRegName tRegName = tRepeatInfo.atTPRegName[0];
		if ( tRegName.emPAAddrType == emTpAlias )
		{
			strTemp = _T("会场名称重复");
		}
		else if ( tRegName.emPAAddrType == emTpE164Num )
		{
			strTemp = _T("会场号码重复");
		}
	}
	else if ( 2 == dwSize )
	{
		strTemp = _T("会场名称和会场号码都重复");
	}

	ShowPopMsg( strName + strTemp );

	return NO_ERROR;
}

bool CRegServiceLogic::OnGkNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPGKCfg tCfg;
	ComInterface->GetGkCfg( tCfg );

	in_addr tAddr;
	tAddr.S_un.S_addr = /*ntohl*/(tCfg.dwGKIP);
	String strServiceIP = (CA2T)inet_ntoa(tAddr);
	CString strbGk = _T("关闭");
	if ( strServiceIP == _T("0.0.0.0") )
	{
		strServiceIP = _T("");
	}
	if (tCfg.bUsed)
	{
		strbGk = _T("开启");
	}

	ICncCommonOp::SetControlText( strbGk,m_pm,_T("lbsGk"));
	ICncCommonOp::SetControlText( strServiceIP.c_str(),m_pm,_T("lbGKIp"));
	ICncCommonOp::SetControlText( strServiceIP.c_str(),m_pm,_T("edtGKIp"));


	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm,_T("CheckIsGk") );
	if ( !pCheckBox )
	{
		return false;
	}
	pCheckBox->SetCheck(tCfg.bUsed);

	if ( pCheckBox->IsSelected() )
	{
		m_bIsGK = true;
		ICncCommonOp::EnableControl(true,m_pm,m_strEdtGKIp.c_str());
	}
	else
	{
		m_bIsGK = false;
		ICncCommonOp::EnableControl(false,m_pm,m_strEdtGKIp.c_str());
	}

	return NO_ERROR;
}

bool CRegServiceLogic::OnGkRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	bool bOk = false;
    TUCSipRegResult tRegResult = *(TUCSipRegResult*)wParam;

    CString strTemp = _T("");
    switch( tRegResult.m_emTpCnsRegUms )
    {  
    case tp_CnsRegRet_Success:		//成功
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:    //注册满
        strTemp = _T("注册个数已达到最大值");
        break;
    case tp_CnsRegRet_MaxAliasNum:	//注册满
        strTemp = _T("注册别名的个数已达到最大值");
        break;
    case tp_CnsRegRet_MsgError:		//注册消息错误
        strTemp = _T("注册消息错误");
        break;
    case tp_CnsRegRet_AliasRepeat:	//别名重复
        strTemp = _T("注册别名重复");
        break;
    case tp_CnsRegRet_UnReg:	    //删除时，未找到删除记录
        strTemp = _T("未找到该记录");
        break;
    case tp_CnsRegRet_SysError:		//APP错误
        strTemp =_T( "APP错误");
        break;
    case tp_CnsRegRet_NotFind:		//查找失败
        strTemp = _T("查找失败");
        break;   
    case tp_CnsRegRet_Unreachable:  //服务器不可达
        strTemp = _T("服务器不可达");
        break;
    case tp_CnsRegRet_E164Repeat:   //E164号重复
        strTemp = _T("E164号重复");
        break;
	case tp_CnsRegRet_NameDup:
		strTemp = _T("别名或E164号码重复");
		break;
    default:
		strTemp = "";//2012-8-7 SE石文娟确认未知错误不做提示 by yjj
		break;
    }
	
	CString strName = _T("注册GK失败");
 	 
	if ( bOk )
	{
		ShowPopMsg(_T("注册GK成功"));
	}
	else
	{
        //别名重复时需要详细提示
        
        if ( tRegResult.m_emTpCnsRegUms == tp_CnsRegRet_AliasRepeat )
        {           
            u32 dwSize = tRegResult.m_nAliasNum;
            if ( 1 == dwSize )
            {
                TTPAlias tRegAlias = tRegResult.m_atTPAlias[0];
                if ( tRegAlias.m_byType == tp_Alias_h323  )
                {
                    strTemp = "：会场名称重复";
                }
                else if ( tRegAlias.m_byType == tp_Alias_e164 )
                {
                    strTemp = "：会场号码重复";
                }
            }
            else if ( 2 == dwSize )
            {
                strTemp = "：会场名称和会场号码都重复";
	        }
        }
        
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + strTemp;
		}

		ShowPopMsg(strName);
	}
	return NO_ERROR;
}

bool CRegServiceLogic::OnCallSerNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPCallSerInfo tCallSerInfo;
	ComInterface->GetCallServerInfo( tCallSerInfo );

	SetCallServerInfo( tCallSerInfo );

	return NO_ERROR;
}

void CRegServiceLogic::SetCallServerInfo( TTPCallSerInfo tCallSerInfo )
{
	in_addr tAddr;
	tAddr.S_un.S_addr = /*ntohl*/(tCallSerInfo.dwCallServiceIP);
	String strServiceIP = CA2T(inet_ntoa(tAddr));
	if ( strServiceIP == _T("0.0.0.0") )
	{
		strServiceIP = _T("");
	}

	ICncCommonOp::SetControlText( strServiceIP.c_str(),m_pm,_T("lbCallIp"));
	ICncCommonOp::SetControlText( strServiceIP.c_str(),m_pm,_T("edtCallIp"));
}

bool CRegServiceLogic::OnCallSerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		ShowPopMsg(_T("设置呼叫服务器地址失败"));
	} 

	OnCallSerNty( wParam, lParam, bHandle );
	return S_OK;
}

bool CRegServiceLogic::OnUpSerNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPUpgradeSer tUpgradeSer;
	ComInterface->GetUpgradeSerInfo( tUpgradeSer );
	SetUpgradeServiceIP(tUpgradeSer);

	return NO_ERROR;
}

void CRegServiceLogic::SetUpgradeServiceIP(TTPUpgradeSer tUpgradeSer)
{	
	in_addr tAddr;
	tAddr.S_un.S_addr = /*ntohl*/(tUpgradeSer.dwSerIP);
	String strServiceIP = CA2T(inet_ntoa(tAddr));
	if ( strServiceIP == _T("0.0.0.0") )
	{
		strServiceIP = _T("");
	}

	ICncCommonOp::SetControlText( strServiceIP.c_str(),m_pm,_T("lbUpgradeIp"));
	ICncCommonOp::SetControlText( strServiceIP.c_str(),m_pm,_T("edtUpgradeIp"));
}

bool CRegServiceLogic::OnUpSerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bRes = static_cast<BOOL>(lParam);
	if ( FALSE == bRes )
	{
		ShowPopMsg(_T("设置升级服务器失败"));
	}

	OnUpSerNty( wParam,lParam,bHandle );

	return NO_ERROR;
}

bool CRegServiceLogic::OnWBServiceIPNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPDataConfInfo tWBSerIp;
	ComInterface->GetWBSerIp( tWBSerIp );

	in_addr tAddr;
	tAddr.S_un.S_addr = /*ntohl*/(tWBSerIp.dwSerIP);
	String strWBSerIp = CA2T(inet_ntoa(tAddr));
	if ( strWBSerIp == _T("0.0.0.0") )
	{
		strWBSerIp = _T("");
	}

	ICncCommonOp::SetControlText( strWBSerIp.c_str(),m_pm,_T("lbDCIp"));
	ICncCommonOp::SetControlText( strWBSerIp.c_str(),m_pm,_T("edtDCIp"));
	return NO_ERROR;
}

bool CRegServiceLogic::OnWBServerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bRes = static_cast<BOOL>(lParam);
	if ( FALSE == bRes )
	{
		ShowPopMsg(_T("设置数据服务器失败"));
	}

	OnWBServiceIPNty( wParam, lParam,bHandle );
	return NO_ERROR;
}


bool CRegServiceLogic::OnQTEncryptInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bRes = static_cast<BOOL>(lParam);
	BOOL bIsReboot = static_cast<u8>(wParam);
	OnQTEncryptNty( wParam, lParam,bHandle );
	if ( FALSE == bRes )
	{
		ShowPopMsg(_T("设置量子加密失败"));
	}
	else
	{
		if (bIsReboot)
		{
			int nResult = ShowMessageBox((_T("量子加密服务器配置需要重启设备，是否重启？")),true);
			if (IDOK == nResult)
			{
				ComInterface->RebootCns();
			}
		}
	}
	
	return NO_ERROR;
}

bool CRegServiceLogic::OnQTEncryptNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpQtEncryptCfg tQtEncrypt;
    ComInterface->GetQTEncrypt(tQtEncrypt);

	in_addr tAddr;
	tAddr.S_un.S_addr = /*ntohl*/(tQtEncrypt.m_dwQtIP);
	String strIp = CA2T(inet_ntoa(tAddr));
	if ( strIp == _T("0.0.0.0") )
	{
		strIp = _T("");
	}

	CString strQtID = _T("");
	if (tQtEncrypt.m_dwQtID != 0)
	{
		strQtID.Format(_T("%u"), tQtEncrypt.m_dwQtID);
	}

	ICncCommonOp::SetControlText( strIp.c_str(),m_pm,_T("edtQuantumIp"));
	ICncCommonOp::SetControlText( strIp.c_str(),m_pm,_T("lbQuantumIp"));

	ICncCommonOp::SetControlText( strQtID,m_pm,_T("edtQuantumID"));
	ICncCommonOp::SetControlText( strQtID,m_pm,_T("lbQuantumID"));

	CCheckBoxUI* pCheckQT = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsQT") );
	CLabelUI* pLabQT = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbsQT") );
	if ( pCheckQT && pLabQT)
	{
		if (tQtEncrypt.m_bOpen == FALSE)
		{
			pCheckQT->Selected(false);
			pLabQT->SetText(_T("关闭"));
		}
		else
		{
			pCheckQT->Selected(true);
			pLabQT->SetText(_T("开启"));
		}
	}
	
	return NO_ERROR;
}

void CRegServiceLogic::SetSipIP( TTPSipRegistrarCfg tTPSipRegistrarCfg )
{
	in_addr tAddr;
	tAddr.S_un.S_addr = /*ntohl*/(tTPSipRegistrarCfg.dwRegIP);
	String strSipIp = CA2T(inet_ntoa(tAddr));
	if ( strSipIp == _T("0.0.0.0") )
	{
		strSipIp = _T("");
	}

	ICncCommonOp::SetControlText(strSipIp.c_str(), m_pm, _T("lbRigIp"));
	ICncCommonOp::SetControlText(strSipIp.c_str(), m_pm, _T("edtRigIp"));
}

bool CRegServiceLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}


