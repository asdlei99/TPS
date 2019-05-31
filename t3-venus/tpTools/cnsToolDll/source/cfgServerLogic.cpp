// cfgServerLogic.cpp: implementation of the CCfgServerLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgServerLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgServerLogic::CCfgServerLogic()
: m_strEdtSIp("CfgServerDlg/SIPCtrlAddress")
, m_strBtnGKSwitch("CfgServerDlg/BtnGKSwitch")
, m_strEdtGKIP("CfgServerDlg/IPCtrlGKIp")
, m_strEdtCSIP("CfgServerDlg/IPCtrlCallServer")
, m_strEdtUGIP("CfgServerDlg/IPCtrlUpAddress")
, m_strEdtDCIP("CfgServerDlg/IPCtrlDataConfSer")
, m_strEdtMatrixIP("CfgServerDlg/IPCtrlDataMatrix")
, m_strBtnQTSwitch("CfgServerDlg/BtnQuantumEncrySwitch")
, m_strEdtQtIP("CfgServerDlg/IPCtrlDataQuantumEncry")
, m_strEdtQtID("CfgServerDlg/IPCtrlIDQuantumEncry")
, m_strEdtTimeSyncIP("CfgServerDlg/IPCtrlDataTimeSync")		 
{
	m_vctWndName.clear();
	m_bIsTptoolsSaveQtInfo = FALSE;
}

CCfgServerLogic::~CCfgServerLogic()
{

}

bool CCfgServerLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgServerLogic::RegMsg()
{
	CCfgServerLogic *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CCfgServerLogic::OnUpdateGkNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGSIP_NOTIFY, CCfgServerLogic::OnUpdateSipNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_NTY, CCfgServerLogic::OnCallSerNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_NTY, CCfgServerLogic::OnUpgradeSerNty, pThis, CCfgServerLogic );
	//ע�����ʷ�������Ϣ����
	REG_MSG_HANDLER( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, CCfgServerLogic::OnRegSIPAliasRepeatNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGRESULT_NOTIFY, CCfgServerLogic::OnRegSIPResultNty, pThis, CCfgServerLogic );
	//ע��GK��Ϣ����
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CCfgServerLogic::OnRegGKRsp, pThis, CCfgServerLogic );
	//ע����з�������Ϣ����
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_IND, CCfgServerLogic::OnCallSerInd, pThis, CCfgServerLogic );
	//ע��������������Ϣ����
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_IND, CCfgServerLogic::OnUpgradeSerInd, pThis, CCfgServerLogic );
	//���ջ���״̬��Ϣ
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgServerLogic::OnConfStateNty, pThis, CCfgServerLogic );
	//���ݻ����������Ϣ���� 14/9/4
	REG_MSG_HANDLER( UI_TPPSETDATASERVERINFONTY, CCfgServerLogic::OnWBServerNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_TPPSETDATASERVER_IND, CCfgServerLogic::OnWBServerInd, pThis, CCfgServerLogic );
	//�����������Ϣ����
	REG_MSG_HANDLER( UI_TPSETMATRIXSERVERINFO_NTY, CCfgServerLogic::OnSetMatrixServerInfoNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_TPSETMATRIXSERVERINFO_IND, CCfgServerLogic::OnSetMatrixServerInfoInd, pThis, CCfgServerLogic );
	//���Ӽ��ܷ�������Ϣ����
	REG_MSG_HANDLER( UI_SETQTENCRYPTINFO_Nty, CCfgServerLogic::OnSetQtEncryptInfoNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_SETQTENCRYPTINFO_Ind, CCfgServerLogic::OnSetQtEncryptInfoInd, pThis, CCfgServerLogic );

	//ʱ��ͬ����������Ϣ����
	REG_MSG_HANDLER( UI_TPSETNTPSERVERINFO_NTY, CCfgServerLogic::OnSetNtpServerInfoNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_TPSETNTPSERVERINFO_IND, CCfgServerLogic::OnSetNtpServerInfoInd, pThis, CCfgServerLogic );
	
}

void CCfgServerLogic::UnRegMsg()
{
	
}

void CCfgServerLogic::RegCBFun()
{
	CCfgServerLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::InitWnd", CCfgServerLogic::InitWnd, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSave", CCfgServerLogic::OnBtnSave, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnCancel", CCfgServerLogic::OnBtnCancel, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSwitchGK", CCfgServerLogic::OnBtnSwitchGK, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedSIp", CCfgServerLogic::OnChangedSIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedGKIp", CCfgServerLogic::OnChangedGKIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedCallSerIp", CCfgServerLogic::OnChangedCallSerIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedUpSerIp", CCfgServerLogic::OnChangedUpSerIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataConfSerIP",CCfgServerLogic::OnChangedDataConfSerIP, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataMatrix",CCfgServerLogic::OnChangedDataMatrix, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSwitchQuantumEncry", CCfgServerLogic::OnBtnSwitchQuantumEncry, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataQuantumEncryIP",CCfgServerLogic::OnChangedDataQuantumEncryIP, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedQuantumEncryID",CCfgServerLogic::OnChangedQuantumEncryID, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedDataTimeSyncIP",CCfgServerLogic::OnChangedDataTimeSyncIP, pThis, CCfgServerLogic );

}

void CCfgServerLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgServerLogic::InitWnd" );	
}

void CCfgServerLogic::Clear()
{
	m_bIsTptoolsSaveQtInfo = FALSE;
	m_vctWndName.clear();
	UpBtnState();

}

bool CCfgServerLogic::OnBtnSave( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("�л�������У���������") );
		SetCallSerData();
		SetGKData();
		SetSipData();
		SetUpgradeSerData();
		SetDataConfSerData();
		SetMatrixSerData();
		SetQtEncryptData();
		SetNtpSerData();
		m_vctWndName.clear();
		UpBtnState();
		OnConfStateNty(0,0);
		return false;	
	}

	bool bSucceed = true;
	bSucceed = SaveSip();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveGk();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveCallSer();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveUpgradeSer();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveDataConfSer();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveMatrixSer();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveQtEncryptSer();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveNtpSer();
	if (false == bSucceed)
	{
		return false;
	}
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgServerLogic::OnBtnCancel( const IArgs& args )
{
	SetCallSerData();
	SetGKData();
	SetSipData();
	SetUpgradeSerData();
	SetDataConfSerData();
	SetMatrixSerData();
	SetNtpSerData();
	SetQtEncryptData();
	m_vctWndName.clear();
	UpBtnState();
	//�����鿪����,���ý���ȡ�������ȫ�������û�
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�FocusWindow
* ��    �ܣ�������ʾ���λ�����崰��λ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
void CCfgServerLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

/*---------------------------------------------------------------------
* �������ƣ�SaveSip
* ��    �ܣ�����ע�����ʷ���������	
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveSip( /*const IArgs& args*/ )
{		
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	String strServiceIp;
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtSIp, m_pWndTree ); 
	
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree );
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "���ʷ�������ַ�Ƿ�" );
		FocusWindow(m_strEdtSIp);
		return false;
	}

	TTPSipRegistrarCfg tSipcfg;
	if ( strCaption.empty() )
	{  
		tSipcfg.bUsed = FALSE;
		tSipcfg.dwRegIP = 0;
		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;
	}
	else
	{	
		tSipcfg.bUsed = TRUE;
		tSipcfg.dwRegIP = htonl(valIp.dwIP);
		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;
	}		
	
	TTPSipRegistrarCfg tOldSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tOldSipCfg );
	
	if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP )
	{		 
		u16 wRet = COMIFMGRPTR->CnsRegSipService( tSipcfg );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "�������ʷ���������������ʧ��" );
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�SaveGk
* ��    �ܣ�����GK����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveGk()
{	
	//GK����
    TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	
    bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );
	
    Value_IpEditData valGkIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valGkIp, m_strEdtGKIP, m_pWndTree); 
	
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP , strCaption , m_pWndTree ); 

    if ( ( bUseGk != (bool)tOldGkCfg.bUsed ) || htonl( valGkIp.dwIP ) != tOldGkCfg.dwGKIP )
	{   
		if ( bUseGk == true )
		{
			if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP ) )
			{
				if ( strCaption.empty() == true )
				{
					MSG_BOX_OK( "GK��������ַ����Ϊ��" );
				}
				else
				{
					MSG_BOX_OK( "GK��������ַ�Ƿ�" );
				}
				FocusWindow(m_strEdtGKIP);

				return false;
			}
		}
		else
		{
			if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP) && !strCaption.empty() )
			{
				MSG_BOX_OK( "GK��������ַ�Ƿ�" );
				SetGKData();
				return false;
			} 
		}

		TTPGKCfg tGkcfg; 
		tGkcfg.wExpire = 40; 
		tGkcfg.bUsed = bUseGk;
		tGkcfg.dwGKIP = htonl(valGkIp.dwIP);  
	
        u16 wRet  = COMIFMGRPTR->CnsRegGkService( tGkcfg );
		if (wRet != NO_ERROR)
		{
			//MSG_BOX_OK( "����GK����������ʧ��" );
			WARNMESSAGE( "����GK����������������ʧ��" );
			return false;
		}		 
	}
	return true;
}


LRESULT CCfgServerLogic::OnUpdateGkNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetGKData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnUpdateSipNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetSipData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegSIPAliasRepeatNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)wParam;
	
	CString strName;
	strName.Format( "%sע�����ʷ�����ʧ�ܣ�", (s8*)lParam );
	
	CString strTemp = "ע������ظ�";
	
	u32 dwSize = tRepeatInfo.dwsize;
	if ( 1 == dwSize )
	{
		TTPRegName tRegName = tRepeatInfo.atTPRegName[0];
		if ( tRegName.emPAAddrType == emTpAlias )
		{
			strTemp = "�᳡�����ظ�";
		}
		else if ( tRegName.emPAAddrType == emTpE164Num )
		{
			strTemp = "�᳡�����ظ�";
		}
	}
	else if ( 2 == dwSize )
	{
		strTemp = "�᳡���ƺͻ᳡���붼�ظ�";
	}
	strName = strName + strTemp;
	//MSG_BOX_OK((String)strName);
	WARNMESSAGE(strName);
	FocusWindow(m_strEdtSIp);
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_SIPRsp_NTY, 0, 0 );
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegSIPResultNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmTpCnsRegUms emReg = (EmTpCnsRegUms)wParam;
	
	BOOL bOk = FALSE;
	CString strTemp = "";
    switch( emReg )
    {		
    case tp_CnsRegRet_Success:		//�ɹ�
        bOk  = TRUE;
        break;
    case tp_CnsRegRet_MaxRegNum:		//ע����
        strTemp = "ע������Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//ע����
        strTemp = "ע������ĸ����Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MsgError:		//ע����Ϣ����
        strTemp = "ע����Ϣ����";
        break;
    case tp_CnsRegRet_AliasRepeat:	//�����ظ�
        strTemp = "ע������ظ�";
        break;
    case tp_CnsRegRet_UnReg:		//ɾ��ʱ��δ�ҵ�ɾ����¼
        strTemp = "δ�ҵ�ɾ����¼";
        break;
    case tp_CnsRegRet_SysError:		//APP����
        strTemp = "APP����";
        break;
    case tp_CnsRegRet_NotFind:		//����ʧ��
        strTemp = "����ʧ��";
        break;   
    case tp_CnsRegRet_Unreachable:   //���������ɴ�
        strTemp = "���������ɴ�";
        break;
    default:
		strTemp = ""; //"δ֪����";  
    }
	
	
    CString strName;
	
	if ( bOk )
	{
		//MSG_BOX_OK( "ע��SIP�������ɹ�" );
		WARNMESSAGE( "ע�����ʷ������ɹ�" );
	}
	else
	{   
		strName = "ע�����ʷ�����ʧ��";
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "��" + strTemp;
		}
		//String str(strName);
		//MSG_BOX_OK(str);
		WARNMESSAGE(strName);
		FocusWindow(m_strEdtSIp);
	}
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_SIPRsp_NTY, (WPARAM)bOk, 0 );
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegGKRsp( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
    bool bOk = false;
    TUCSipRegResult tRegResult = *(TUCSipRegResult*)wParam;
	
    CString strTemp = "";
    switch( tRegResult.m_emTpCnsRegUms )
    {  
    case tp_CnsRegRet_Success:		//�ɹ�
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:		//ע����
        strTemp = "ע������Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//ע����
        strTemp = "ע������ĸ����Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MsgError:		//ע����Ϣ����
        strTemp = "ע����Ϣ����";
        break;
    case tp_CnsRegRet_AliasRepeat:	//�����ظ�
        strTemp = "ע������ظ�";
        break;
    case tp_CnsRegRet_UnReg:	    //ɾ��ʱ��δ�ҵ�ɾ����¼
        strTemp = "δ�ҵ��ü�¼";
        break;
    case tp_CnsRegRet_SysError:		//APP����
        strTemp = "APP����";
        break;
    case tp_CnsRegRet_NotFind:		//����ʧ��
        strTemp = "����ʧ��";
        break;   
    case tp_CnsRegRet_Unreachable:   //���������ɴ�
        strTemp = "���������ɴ�";
        break;
    default:
		strTemp = "";
		break;
    }
	
	CString strName = "ע��GK������ʧ��";
	
	if ( bOk )
	{
		//MSG_BOX_OK( "ע��GK�ɹ�" );
		WARNMESSAGE( "ע��GK�������ɹ�" );
	}
	else
	{
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "��" + strTemp;
		}
		
		//MSG_BOX_OK((String)strName);
		WARNMESSAGE(strName);
		FocusWindow(m_strEdtGKIP);
	}
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_GKRsp_NTY, (WPARAM)bOk, 0 );
	return S_OK;
}

bool CCfgServerLogic::OnBtnSwitchGK( const IArgs& args )
{
	TTPGKCfg tGkCfg;
	LIBDATAMGRPTR->GetGkCfg( tGkCfg );

	bool bUseGK = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGK, m_pWndTree );
    if ( bUseGK )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP); 
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }

	bool bChange = false;
	if ( (BOOL)bUseGK != tGkCfg.bUsed )
	{
		bChange = true;
	}	
	CheckData(m_strBtnGKSwitch,bChange);
	return true;	
}

bool CCfgServerLogic::OnBtnSwitchQuantumEncry( const IArgs& args )
{
	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg(tTpQtEncryptCfg);

	bool bUseQT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnQTSwitch, bUseQT, m_pWndTree );
    if ( bUseQT )
    {
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtID); 
    }
    else
    {   
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree,m_strEdtQtID);
    }

	bool bChange = false;
	if ( (BOOL)bUseQT != tTpQtEncryptCfg.m_bOpen )
	{
		bChange = true;
	}	
	CheckData(m_strBtnQTSwitch,bChange);
	
	return true;	
}

LRESULT CCfgServerLogic::OnCallSerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetCallSerData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnCallSerInd( WPARAM wParam, LPARAM lParam )
{	
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		//MSG_BOX_OK("���ú��з�������ַʧ��");
		WARNMESSAGE("���ú��з�������ַʧ��");
		FocusWindow(m_strEdtCSIP);
	} 
	return S_OK;	
}

bool CCfgServerLogic::SaveCallSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtCSIP, m_pWndTree ); 
	
	TTPCallSerInfo tCallSerInfo;
	tCallSerInfo.dwCallServiceIP = htonl(valIp.dwIP);
	
	TTPCallSerInfo tOldCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tOldCallSerInfo);

	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "���з�������ַ�Ƿ�" );
		FocusWindow(m_strEdtCSIP);
		return false;
	}

	if ( tOldCallSerInfo.dwCallServiceIP != tCallSerInfo.dwCallServiceIP )
	{
		u16 wRet = COMIFMGRPTR->CallServerCmd( tCallSerInfo );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "������з���������������ʧ��" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::IsCfgSerChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgServerLogic::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "���������޸ģ��Ƿ񱣴����ã�" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{	
		OnBtnCancel(args);
	}
	return true;
}

bool CCfgServerLogic::OnChangedSIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}	
	TTPSipRegistrarCfg tOldSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tOldSipCfg );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldSipCfg.dwRegIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtSIp );
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tOldSipCfg.dwRegIP || */strCaption != strOldInfo )
	{
	 	bChange = true;		
	}

	CheckData(m_strEdtSIp,bChange);
	return true;
}

bool CCfgServerLogic::OnChangedGKIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldGkCfg.dwGKIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtGKIP );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

    if ( /*dwIP != tOldGkCfg.dwGKIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}

	CheckData(m_strEdtGKIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedCallSerIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtCSIP );

	TTPCallSerInfo tCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tCallSerInfo);
	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tCallSerInfo.dwCallServiceIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtCSIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedUpSerIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtUGIP );

	TTPUpgradeSer tUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tUpgradeSer );
	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tUpgradeSer.dwSerIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}

	CheckData(m_strEdtUGIP, bChange);
	return true;		
}

void CCfgServerLogic::SetGKData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPGKCfg tGkCfg;
	LIBDATAMGRPTR->GetGkCfg( tGkCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tGkCfg.dwGKIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGKIP, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strBtnGKSwitch, tGkCfg.bUsed, m_pWndTree );
    if ( tGkCfg.bUsed )
    {
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( !bInConf )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP); 
		}
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }
	CheckData(m_strBtnGKSwitch,false);
	CheckData(m_strEdtGKIP,false);
}

void CCfgServerLogic::SetSipData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPSipRegistrarCfg tSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tSipCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tSipCfg.dwRegIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSIp, m_pWndTree ); 
}

void CCfgServerLogic::SetCallSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPCallSerInfo tCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tCallSerInfo);

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tCallSerInfo.dwCallServiceIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtCSIP, m_pWndTree ); 
}

LRESULT CCfgServerLogic::OnUpgradeSerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetUpgradeSerData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnUpgradeSerInd( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		//MSG_BOX_OK("����������������ַʧ��");
		WARNMESSAGE("����������������ַʧ��");
		FocusWindow(m_strEdtUGIP);
	} 
	return S_OK;
}

void CCfgServerLogic::SetUpgradeSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPUpgradeSer tUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tUpgradeSer );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tUpgradeSer.dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtUGIP, m_pWndTree ); 
}

bool CCfgServerLogic::SaveUpgradeSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtUGIP, m_pWndTree ); 

	TTPUpgradeSer tOldUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tOldUpgradeSer );

	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree );

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "������������ַ�Ƿ�" );
		FocusWindow(m_strEdtUGIP);
		return false;
	}

	if ( htonl(valIp.dwIP) != tOldUpgradeSer.dwSerIP )
	{
		TTPUpgradeSer tUpgradeSer;
		tUpgradeSer.dwSerIP = htonl(valIp.dwIP);
		u16 wRet = COMIFMGRPTR->UpgradeSerCmd( tUpgradeSer );
		if (wRet != NO_ERROR)
		{
			//MSG_BOX_OK( "������������������������ʧ��" );
			WARNMESSAGE( "������������������������ʧ��" );
			return false;
		}
	}
	return true;
}

LRESULT CCfgServerLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0  && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );

	bool bUseQT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnQTSwitch, bUseQT, m_pWndTree );

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
		if ( bUseGk )		//���������еĴ�����Ϊdisable״̬
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, false, m_pWndTree );
		}
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
		if ( bUseGk )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, true, m_pWndTree );
		} 
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, false, m_pWndTree );
		}
		if (!bUseQT)
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtIP); 
			UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtID); 
		}
	}
	return S_OK;
}

DWORD CCfgServerLogic::StrToDWIp( String strName )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( strName, strCaption, m_pWndTree);
	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
	{
		MSG_BOX_OK( "0������Ч��.��ָ��һ������1��223���ֵ." );
		UIFACTORYMGR_PTR->SetCaption( strName, "1.", m_pWndTree);
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strName, m_pWndTree );
		if ( pWnd )
		{
			(( CEdit *) pWnd)->SetSel( -1 );
		}
	}
	DWORD dwIP = inet_addr(strCaption.c_str());
	if ( strCaption.empty() )
	{
		dwIP = 0;
	}
	return dwIP;
}

// ���ݻ����������ַ�����߼�/��Ϣ���� 14/9/4
LRESULT CCfgServerLogic::OnWBServerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetDataConfSerData();
	return S_OK;
}

bool CCfgServerLogic::OnChangedDataConfSerIP( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	
    TTPDataConfInfo tWBSerIp;
	LIBDATAMGRPTR->GetWBSerIp( tWBSerIp );
	in_addr tAddr;
	tAddr.S_un.S_addr = tWBSerIp.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtDCIP, strCaption, m_pWndTree);
	
	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtDCIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedDataMatrix(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	bool bChange = false;
	TTPMatrixServerInfo tTPMatrixServerInfo;
	LIBDATAMGRPTR->GetMatrixSerInfo(tTPMatrixServerInfo);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTPMatrixServerInfo.m_dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtMatrixIP, strCaption, m_pWndTree);
	
	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtMatrixIP, bChange );
	
	return true;
}

bool CCfgServerLogic::OnChangedDataQuantumEncryIP(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	bool bChange = false;
	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg(tTpQtEncryptCfg);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTpQtEncryptCfg.m_dwQtIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtIP, strCaption, m_pWndTree);

	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtQtIP, bChange );
	return true;
}

bool CCfgServerLogic::OnChangedQuantumEncryID(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	bool bChange = false;
	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg( tTpQtEncryptCfg );

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtID, strCaption, m_pWndTree);
	u32 dwCaption = atoi(strCaption.c_str());

	if ( dwCaption != tTpQtEncryptCfg.m_dwQtID )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtQtID, bChange );
	return true;
}

bool CCfgServerLogic::OnChangedDataTimeSyncIP(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	bool bChange = false;
	TTPNtpSer tTpNtpSer;
	LIBDATAMGRPTR->GetNtpSerIP( tTpNtpSer );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tTpNtpSer.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTimeSyncIP, strCaption, m_pWndTree);
	
	if ( strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData( m_strEdtTimeSyncIP, bChange );

	return true;
}

void CCfgServerLogic::SetDataConfSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	
    TTPDataConfInfo tWBSerIp;
	LIBDATAMGRPTR->GetWBSerIp( tWBSerIp );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tWBSerIp.dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtDCIP, m_pWndTree ); 
}

void CCfgServerLogic::SetQtEncryptData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	TTpQtEncryptCfg tTpQtEncryptCfg;
	LIBDATAMGRPTR->GetQtEncryptCfg(tTpQtEncryptCfg);
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tTpQtEncryptCfg.m_dwQtIP);
	
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtQtIP, m_pWndTree );
	
	s8 chEdtQtID[10] = {0};
	if( tTpQtEncryptCfg.m_dwQtID == 0 )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtQtID, "", m_pWndTree );
	}
	else
	{
		sprintf( chEdtQtID, "%u", tTpQtEncryptCfg.m_dwQtID );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtQtID, chEdtQtID, m_pWndTree );
	}

	if ( tTpQtEncryptCfg.m_bOpen == FALSE )
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnQTSwitch, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree, m_strEdtQtID); 
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnQTSwitch, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtIP); 
        UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree, m_strEdtQtID); 
	}
}

void CCfgServerLogic::SetMatrixSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	TTPMatrixServerInfo tTPMatrixServerInfo;
	LIBDATAMGRPTR->GetMatrixSerInfo(tTPMatrixServerInfo);

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tTPMatrixServerInfo.m_dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtMatrixIP, m_pWndTree );
}

void CCfgServerLogic::SetNtpSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	TTPNtpSer tTpNtpSer;
	LIBDATAMGRPTR->GetNtpSerIP( tTpNtpSer );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl( tTpNtpSer.dwSerIP );
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtTimeSyncIP, m_pWndTree );
}

LRESULT CCfgServerLogic::OnWBServerInd( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("�������ݻ����������ַʧ��");
		FocusWindow(m_strEdtDCIP);
	} 
	return S_OK;
}

LRESULT CCfgServerLogic::OnSetMatrixServerInfoNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetMatrixSerData();

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetMatrixServerInfoInd(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("���þ����������ַʧ��");
		FocusWindow(m_strEdtMatrixIP);
	} 

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetQtEncryptInfoNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}

	SetQtEncryptData();

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetQtEncryptInfoInd(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("�������Ӽ��ܷ�������ַʧ��");
		FocusWindow(m_strEdtQtIP);
	} 
	
	SetQtEncryptData();

	//bug cnc�޸�������Ϣ��tptoolsҲ��ʾ��������
	if ( bSuccess && m_bIsTptoolsSaveQtInfo)
	{
		m_bIsTptoolsSaveQtInfo = FALSE;

		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, " ���ӷ���������Ҫ�����豸���Ƿ�������" );
		if( MSGBOX_OK == nMsgBoxRet )
		{
			u16 nRet = COMIFMGRPTR->RebootCns();
			if ( nRet != NO_ERROR )
			{
				WARNMESSAGE( "����cns������ʧ��!" );
			}
		}
	}

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetNtpServerInfoNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	
	SetNtpSerData();

	return S_OK;
}

LRESULT CCfgServerLogic::OnSetNtpServerInfoInd(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		WARNMESSAGE("����ʱ��ͬ����������ַʧ��");
		FocusWindow(m_strEdtTimeSyncIP);
	} 

	return S_OK;
}

bool CCfgServerLogic::SaveDataConfSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtDCIP, m_pWndTree ); 

	TTPDataConfInfo tWBSerIp;
	tWBSerIp.dwSerIP = htonl(valIp.dwIP);
	
	TTPDataConfInfo tOldWBSerInfo;
	LIBDATAMGRPTR->GetWBSerIp(tOldWBSerInfo);
		
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtDCIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "���ݻ����������ַ�Ƿ�" );
		FocusWindow(m_strEdtDCIP);
		return false;
	}
	
	if ( tWBSerIp.dwSerIP != tOldWBSerInfo.dwSerIP )
	{
		u16 wRet = COMIFMGRPTR->SetDataConfSerCmd( tWBSerIp );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "�������ݻ������������������ʧ��" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::SaveMatrixSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtMatrixIP, m_pWndTree ); 
	
	TTPMatrixServerInfo tTPMatrixServerInfo;
	tTPMatrixServerInfo.m_dwSerIP = htonl(valIp.dwIP);
	
	TTPMatrixServerInfo tTPOldMatrixServerInfo;
	LIBDATAMGRPTR->GetMatrixSerInfo(tTPOldMatrixServerInfo);
	
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtMatrixIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "�����������ַ�Ƿ�" );
		FocusWindow(m_strEdtMatrixIP);
		return false;
	}
	
	if ( tTPMatrixServerInfo.m_dwSerIP != tTPOldMatrixServerInfo.m_dwSerIP )
	{
		u16 wRet = COMIFMGRPTR->SetMatrixSerCmd( tTPMatrixServerInfo );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "����������������������ʧ��" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::SaveQtEncryptSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtQtIP, m_pWndTree );

	TTpQtEncryptCfg tTpQtEncryptCfg;
	tTpQtEncryptCfg.m_dwQtIP = htonl(valIp.dwIP);

	TTpQtEncryptCfg tOldQtSerInfo;
	LIBDATAMGRPTR->GetQtEncryptCfg(tOldQtSerInfo);

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtIP, strCaption, m_pWndTree );

	String strCaption1;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtQtID, strCaption1, m_pWndTree );

	bool bUseQT = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnQTSwitch, bUseQT, m_pWndTree );

	tTpQtEncryptCfg.m_bOpen = bUseQT;

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "���Ӽ��ܷ�������ַ�Ƿ�" );
		FocusWindow(m_strEdtQtIP);
		return false;
	}

	if( strCaption1.empty() )
	{
		tTpQtEncryptCfg.m_dwQtID = 0;
	}
	else
	{
		u64 dwQtID = _atoi64(strCaption1.c_str());
		if( ( dwQtID < 1 ) || ( dwQtID > 4294967295 ) )
		{
			MSG_BOX_OK("���Ӽ��ܵ�ID��Χ������1-4294967295֮��");
			FocusWindow(m_strEdtQtID);
			return false;
		}
		else
		{
			tTpQtEncryptCfg.m_dwQtID = atoi( strCaption1.c_str() );
		}
	}

	if( (tTpQtEncryptCfg.m_bOpen != tOldQtSerInfo.m_bOpen) || (tTpQtEncryptCfg.m_dwQtIP != tOldQtSerInfo.m_dwQtIP) || ( tTpQtEncryptCfg.m_dwQtID != tOldQtSerInfo.m_dwQtID ) )
	{
		u16 wRet = COMIFMGRPTR->SetQtEncryptSerCmd(tTpQtEncryptCfg);
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "�������Ӽ��ܷ���������������ʧ��" );
			return false;
		}
		else
		{
			if ((tTpQtEncryptCfg.m_dwQtIP != tOldQtSerInfo.m_dwQtIP) || ( tTpQtEncryptCfg.m_dwQtID != tOldQtSerInfo.m_dwQtID ))
			{
				m_bIsTptoolsSaveQtInfo = TRUE;
			}
		}
	}

	return true;
}

bool CCfgServerLogic::SaveNtpSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtTimeSyncIP, m_pWndTree ); 
	
	TTPNtpSer tTpNtpSer;
	tTpNtpSer.dwSerIP = htonl(valIp.dwIP);
	
	TTPNtpSer tTPOldNtpSer;
	LIBDATAMGRPTR->GetNtpSerIP(tTPOldNtpSer);
	
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtTimeSyncIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "ʱ��ͬ����������ַ�Ƿ�" );
		FocusWindow(m_strEdtTimeSyncIP);
		return false;
	}
	
	if ( tTpNtpSer.dwSerIP != tTPOldNtpSer.dwSerIP )
	{
		u16 wRet = COMIFMGRPTR->SetNtpSerCmd( tTpNtpSer );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "����ʱ��ͬ������������������ʧ��" );
			return false;
		}
	}

	return true;
}