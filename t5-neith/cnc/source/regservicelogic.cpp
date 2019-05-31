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
	//���Ӽ���
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
	ICncCommonOp::SetControlText(_T("�� ��"),m_pm,_T("BtnFixOrCancel"));
	m_pm->DoCase(_T("caseSetCancel"));
	return true;
}

bool CRegServiceLogic::OnBtnOk( TNotifyUI& msg )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{		
		ShowMessageBox((_T("�����У������޸ķ���������")),false);
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
		//if (!strRigIp.IsEmpty())//����Ϊ��
		{
			TTPSipRegistrarCfg tSipcfg;
			tSipcfg.bUsed = TRUE;

			if(!strRigIp.IsEmpty() && !CCallAddr::IsValidIpV4(CT2A(strRigIp)))
			{
				ShowMessageBox((_T("����ע���������ַ�Ƿ�")),false);
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
					ShowMessageBox((_T("�����У������޸ķ���������")),false);
					return false;
				}

				u16 wRet = NO_ERROR;		 
				wRet = ComInterface->CnsRegSipService( tSipcfg );
				if ( wRet != NO_ERROR )
				{
					bool bHandle = false;
					OnSipNty(NULL,NULL,bHandle);
					ShowPopMsg(_T("����Sipʧ��"));

				}	
			}
		}

	}
	if (pEdtGKIp)
	{
		CString strGKIp = pEdtGKIp->GetText();

		if (m_bIsGK)//������У��
		{
			if (!strGKIp.IsEmpty())//������Ϊ��
			{
				if(!strGKIp.IsEmpty()  && pEdtGKIp->IsEnabled() && !CCallAddr::IsValidIpV4((CT2A(strGKIp))))
				{
					ShowMessageBox((_T("GK��������ַ�Ƿ�")),false);
					pEdtGKIp->SetFocusX();
					return false;
				}
			}
			else
			{
				ShowMessageBox(_T("GK��������ַ����Ϊ��"));
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

		//��ͬ�Ÿ���
		if ( ( m_bIsGK != (bool)tOldGkCfg.bUsed ) || ( tSipcfg.dwGKIP != tOldGkCfg.dwGKIP ) )
		{      
			BOOL bInConf = ComInterface->IsInConf();
			if ( bInConf )
			{		
				ShowMessageBox((_T("�����У������޸ķ���������")),false);
				return false;
			}
			else
			{
				u16 wRet  = ComInterface->CnsRegGkService( tSipcfg );
				if ( wRet != NO_ERROR )
				{
					bool bHandle = false;
					OnGkNty(NULL,NULL,bHandle);
					ShowPopMsg(_T("����GKʧ��"));

				}
			}
		}
	}

	if (pEdtCallIp)
	{
		CString strCallIp = pEdtCallIp->GetText();
		//if (!strCallIp.IsEmpty())//����Ϊ��
		{
			if( !strCallIp.IsEmpty() && !CCallAddr::IsValidIpV4((CT2A(strCallIp))) )
			{
				ShowMessageBox((_T("���ʺ��з�������ַ�Ƿ�")),false);
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
					ShowMessageBox((_T("���з�������ַ��Ч")),false);
					pEdtCallIp->SetFocusX();
					return false;
				}

				if(!strCallIp.IsEmpty() && !CCallAddr::IsValidCallIP( ntohl(dwCallServiceIP), NULL, 0))
				{
					ShowMessageBox((_T("���з�������ַ������")),false);
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
					ShowMessageBox((_T("�����У������޸ķ���������")),false);
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
						ShowPopMsg(_T("���ú��з�����ʧ��"));
					}	
				}
			}
		}
	}
	if (pEdtUpgradeIp)
	{
		CString strUpgradeIp = pEdtUpgradeIp->GetText();
		//if (!strUpgradeIp.IsEmpty())//����Ϊ��
		{
			if( !strUpgradeIp.IsEmpty() && !CCallAddr::IsValidIpV4(CT2A(strUpgradeIp)) )
			{
				ShowMessageBox((_T("������������ַ�Ƿ�")),false);
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
					ShowPopMsg(_T("��������������ʧ��"));

				}	
			}
		}
	}
	if (pEdtDCIp)
	{
		CString strDCIp = pEdtDCIp->GetText();
		//if (!strDCIp.IsEmpty())// ����Ϊ��
		{
            UIDATAMGR->GetClearIP(strDCIp);
            u32_ip dwIp = inet_addr(CT2A(strDCIp));
			if( !strDCIp.IsEmpty() && !CCallAddr::IsValidIpV4(CT2A(strDCIp)) )
			{
				ShowMessageBox((_T("���ݻ����������ַ�Ƿ�")),false);
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
					ShowPopMsg(_T("�������ݻ��������ʧ��"));
				}		
			}
		}
	}

	//���Ӽ���
	if (pCheckBoxQt && pEdtQTIp && pEdtQTID)
	{
		CString strQTIp = pEdtQTIp->GetText();

		if (!strQTIp.IsEmpty())//������Ϊ��
		{
			if(!CCallAddr::IsValidIpV4((CT2A(strQTIp))))
			{
				ShowMessageBox((_T("���Ӽ���IP��ַ�Ƿ�")),false);
				pEdtQTIp->SetFocusX();
				return false;
			}
		}
// 		else
// 		{
// 			ShowMessageBox(_T("���Ӽ���IP��ַ����Ϊ��"));
// 			pEdtQTIp->SetFocusX();
// 			return false;
// 		}

		CString strQTID = pEdtQTID->GetText();
// 		if (strQTID.IsEmpty())
// 		{
// 			ShowMessageBox(_T("���Ӽ���ID��ַ����Ϊ��"));
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
				ShowMessageBox((_T("����ID��Χ����(1 - 4294967295)")),false);
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
				ShowPopMsg(_T("�������Ӽ�����Ϣʧ��"));
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
			ShowMessageBox((_T("�����У������޸ķ���������")),false);
			m_bIsFix = !m_bIsFix;
			return false;
		}

		BOOL bInConf = ComInterface->IsInConf();
		if ( bInConf )
		{		
			ShowMessageBox((_T("�����У������޸ķ���������")),false);
			m_bIsFix = !m_bIsFix;
			return false;
		}

		m_pm->DoCase(_T("caseSet"));

		ICncCommonOp::ShowControl(true,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("ȡ ��"),m_pm,_T("BtnFixOrCancel"));	
	}
	else
	{	

		ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("�� ��"),m_pm,_T("BtnFixOrCancel"));

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

			int nResult = ShowMessageBox((_T("�Ƿ�Ա༭���б���")),true);
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
	case tp_CnsRegRet_Success:		//�ɹ�
		bOk  = TRUE;
		break;
	case tp_CnsRegRet_MaxRegNum:		//ע����
		strTemp =_T( "ע������Ѵﵽ���ֵ");
		break;
	case tp_CnsRegRet_MaxAliasNum:	//ע����
		strTemp = _T("ע������ĸ����Ѵﵽ���ֵ");
		break;
	case tp_CnsRegRet_MsgError:		//ע����Ϣ����
		strTemp = _T("ע����Ϣ����");
		break;
	case tp_CnsRegRet_AliasRepeat:	//�����ظ�
		strTemp = _T("ע������ظ�");
		break;
	case tp_CnsRegRet_UnReg:		//ɾ��ʱ��δ�ҵ�ɾ����¼
		strTemp = _T("δ�ҵ�ɾ����¼");
		break;
	case tp_CnsRegRet_SysError:		//APP����
		strTemp = _T("APP����");
		break;
	case tp_CnsRegRet_NotFind:		//����ʧ��
		strTemp = _T("����ʧ��");
		break;   
	case tp_CnsRegRet_Unreachable:   //���������ɴ�
		strTemp = _T("���������ɴ�");
		break;
	default:
		strTemp = ""; //"δ֪����";  //2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
	}


	CString strName;
	//strName.Format( "�᳡ %s ", (s8*)lParam );

	if ( bOk )
	{
		ShowPopMsg((_T("ע�����ʷ������ɹ�")));
	}
	else
	{   
		strName = _T("ע�����ʷ�����ʧ��");
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
	strName.Format( _T("ע�����ʷ�����ʧ��: "), (s8*)lParam );

	CString strTemp = _T("ע������ظ�");

	u32 dwSize = tRepeatInfo.dwsize;
	if ( 1 == dwSize )
	{
		TTPRegName tRegName = tRepeatInfo.atTPRegName[0];
		if ( tRegName.emPAAddrType == emTpAlias )
		{
			strTemp = _T("�᳡�����ظ�");
		}
		else if ( tRegName.emPAAddrType == emTpE164Num )
		{
			strTemp = _T("�᳡�����ظ�");
		}
	}
	else if ( 2 == dwSize )
	{
		strTemp = _T("�᳡���ƺͻ᳡���붼�ظ�");
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
	CString strbGk = _T("�ر�");
	if ( strServiceIP == _T("0.0.0.0") )
	{
		strServiceIP = _T("");
	}
	if (tCfg.bUsed)
	{
		strbGk = _T("����");
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
    case tp_CnsRegRet_Success:		//�ɹ�
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:    //ע����
        strTemp = _T("ע������Ѵﵽ���ֵ");
        break;
    case tp_CnsRegRet_MaxAliasNum:	//ע����
        strTemp = _T("ע������ĸ����Ѵﵽ���ֵ");
        break;
    case tp_CnsRegRet_MsgError:		//ע����Ϣ����
        strTemp = _T("ע����Ϣ����");
        break;
    case tp_CnsRegRet_AliasRepeat:	//�����ظ�
        strTemp = _T("ע������ظ�");
        break;
    case tp_CnsRegRet_UnReg:	    //ɾ��ʱ��δ�ҵ�ɾ����¼
        strTemp = _T("δ�ҵ��ü�¼");
        break;
    case tp_CnsRegRet_SysError:		//APP����
        strTemp =_T( "APP����");
        break;
    case tp_CnsRegRet_NotFind:		//����ʧ��
        strTemp = _T("����ʧ��");
        break;   
    case tp_CnsRegRet_Unreachable:  //���������ɴ�
        strTemp = _T("���������ɴ�");
        break;
    case tp_CnsRegRet_E164Repeat:   //E164���ظ�
        strTemp = _T("E164���ظ�");
        break;
	case tp_CnsRegRet_NameDup:
		strTemp = _T("������E164�����ظ�");
		break;
    default:
		strTemp = "";//2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
		break;
    }
	
	CString strName = _T("ע��GKʧ��");
 	 
	if ( bOk )
	{
		ShowPopMsg(_T("ע��GK�ɹ�"));
	}
	else
	{
        //�����ظ�ʱ��Ҫ��ϸ��ʾ
        
        if ( tRegResult.m_emTpCnsRegUms == tp_CnsRegRet_AliasRepeat )
        {           
            u32 dwSize = tRegResult.m_nAliasNum;
            if ( 1 == dwSize )
            {
                TTPAlias tRegAlias = tRegResult.m_atTPAlias[0];
                if ( tRegAlias.m_byType == tp_Alias_h323  )
                {
                    strTemp = "���᳡�����ظ�";
                }
                else if ( tRegAlias.m_byType == tp_Alias_e164 )
                {
                    strTemp = "���᳡�����ظ�";
                }
            }
            else if ( 2 == dwSize )
            {
                strTemp = "���᳡���ƺͻ᳡���붼�ظ�";
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
		ShowPopMsg(_T("���ú��з�������ַʧ��"));
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
		ShowPopMsg(_T("��������������ʧ��"));
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
		ShowPopMsg(_T("�������ݷ�����ʧ��"));
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
		ShowPopMsg(_T("�������Ӽ���ʧ��"));
	}
	else
	{
		if (bIsReboot)
		{
			int nResult = ShowMessageBox((_T("���Ӽ��ܷ�����������Ҫ�����豸���Ƿ�������")),true);
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
			pLabQT->SetText(_T("�ر�"));
		}
		else
		{
			pCheckQT->Selected(true);
			pLabQT->SetText(_T("����"));
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


