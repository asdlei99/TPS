// CfgAdvanceDlg.cpp: implementation of the CCfgAdvanceDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CfgAdvanceDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgAdvanceDlg::CCfgAdvanceDlg()
: m_strRouteInfoList("CfgAdvanceDlg/RouteCfgDlg/RouteCfgList")
, m_strBtnAdd("CfgAdvanceDlg/RouteCfgDlg/BtnAdd")
, m_strBtnDel("CfgAdvanceDlg/RouteCfgDlg/BtnDelete")
{

}

CCfgAdvanceDlg::~CCfgAdvanceDlg()
{

}

void CCfgAdvanceDlg::RegCBFun()
{
	CCfgAdvanceDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::InitWnd", CCfgAdvanceDlg::InitWnd, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnSwitchLossPacket", CCfgAdvanceDlg::OnSwitchLossPacket, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnLossPacketLevel", CCfgAdvanceDlg::OnLossPacketLevel, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnRouteCfgChange", CCfgAdvanceDlg::OnRouteCfgChange, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnBtnAdd", CCfgAdvanceDlg::OnBtnAdd, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnBtnDel", CCfgAdvanceDlg::OnBtnDel, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnBtnSave", CCfgAdvanceDlg::OnBtnSave, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnBtnCancel", CCfgAdvanceDlg::OnBtnCancel, pThis, CCfgAdvanceDlg );

	REG_LIST_CALLFUNC( "CCfgAdvanceDlg::OnClickRouteMngLst", CCfgAdvanceDlg::OnClickRouteMngLst, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnClickRouteCfgLstBlack", CCfgAdvanceDlg::OnClickRouteCfgLstBlack, pThis, CCfgAdvanceDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnCom2SelectedChange", CCfgAdvanceDlg::OnCom2SelectedChange, pThis, CCfgAdvanceDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdvanceDlg::OnCom3SelectedChange", CCfgAdvanceDlg::OnCom3SelectedChange, pThis, CCfgAdvanceDlg );
}

void CCfgAdvanceDlg::Clear()
{
	memset( &m_tTRouteCfgSel, 0, sizeof(TRouteCfg) );
	ResetAllCtrl();	
}

bool CCfgAdvanceDlg::InitWnd( const IArgs & arg )
{
	vector<CString> vecConfig;
	CLogicBase::InitWnd( arg );	
	vecConfig.push_back("��");
	vecConfig.push_back("��");
	vecConfig.push_back("��");
	m_emLostPacket = emTPLPSpeedSlow;
	m_emTempLevel = emTPLPSpeedSlow;

	UIFACTORYMGR_PTR->SetComboListData( "CfgAdvanceDlg/ComboboxLevel", vecConfig, m_pWndTree ); 

	vecConfig.clear();
	vecConfig.push_back("LAN1");
	vecConfig.push_back("LAN2");
	UIFACTORYMGR_PTR->SetComboListData( "CfgAdvanceDlg/ComboboxRouteCfg", vecConfig, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboText( "CfgAdvanceDlg/ComboboxRouteCfg", "LAN1", m_pWndTree );

	vecConfig.clear();
	vecConfig.push_back("��ֽ���豸");
	vecConfig.push_back("�ĵ������");
	UIFACTORYMGR_PTR->SetComboListData( "CfgAdvanceDlg/ComboboxCom2", vecConfig, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( "CfgAdvanceDlg/ComboboxCom3", vecConfig, m_pWndTree ); 

	memset( &m_tTRouteCfgSel, 0, sizeof(TRouteCfg) );

	CTransparentList* pRouteList = (CTransparentList* )UIFACTORYMGR_PTR->GetWindowPtr( m_strRouteInfoList, m_pWndTree );

	if( NULL ==  pRouteList )
	{
		return false;
	}

	pRouteList->SetSliderAlwaysShow(TRUE);	
	pRouteList->SetSliderImage("rescnstool/src/CfgRouteInfo/LstRouteStyle/");
	
	//������ʾ����
	CRect rc;
	pRouteList->GetWindowRect(&rc);
	pRouteList->ScreenToClient( &rc );
	//pRouteList->GetClientRect(&rc);
				
	rc.top = rc.top + 37;
	rc.left = rc.Width();
	rc.right = rc.right + 23;
	rc.bottom = rc.bottom + 37;			
				
	pRouteList->SetSliderRect( rc );
			
	return true;
}

void CCfgAdvanceDlg::RegMsg()
{
	CCfgAdvanceDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_LostPacket_Nty, CCfgAdvanceDlg::OnLostPacketNty, pThis, CCfgAdvanceDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgAdvanceDlg::OnConfStateNty, pThis, CCfgAdvanceDlg );
	REG_MSG_HANDLER( UI_ROUTEINFO_Nty, CCfgAdvanceDlg::OnSetRouteInfoNty, pThis, CCfgAdvanceDlg );
	REG_MSG_HANDLER( UI_ADDROUTE_Ind, CCfgAdvanceDlg::OnAddRouteInfoInd, pThis, CCfgAdvanceDlg );
	REG_MSG_HANDLER( UI_DelROUTE_Ind, CCfgAdvanceDlg::OnDelRouteInfoInd, pThis, CCfgAdvanceDlg );

	REG_MSG_HANDLER( UI_SELECTCOMG_IND, CCfgAdvanceDlg::OnSelectComInd, pThis, CCfgAdvanceDlg );
}


bool CCfgAdvanceDlg::OnSwitchLossPacket( const IArgs & arg )
{
	bool bOpen = false;
	EmTpLostPackageRestore emLostPackage;
	string strLevel = "";
	bool bChange = false;

	UIFACTORYMGR_PTR->GetSwitchState("CfgAdvanceDlg/BtnLossPacket",bOpen,m_pWndTree);
	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxLevel",strLevel,m_pWndTree);

/*	if ( strLevel.size() == 0 )
	{
		emLostPackage = emTPLPSpeedSlow;
	}*/
	if ( bOpen == false )
	{
		emLostPackage = emTPLPSpeedFast;
	}
	else if ( m_emTempLevel == emTPLPSpeedFast )
	{
		emLostPackage = emTPLPSpeedSlow;
	}
	else
	{
		emLostPackage = m_emTempLevel;
	}
	
	UpdateBtnLossPacket( emLostPackage );
	
	if ( emLostPackage != m_emLostPacket )
	{
		bChange = true;
	}
	else
	{
		bChange = false;
	}
	CheckData( "CfgAdvanceDlg/BtnLossPacket", bChange );

	UpBtnState();
	return true;
}

bool CCfgAdvanceDlg::OnLossPacketLevel( const IArgs & arg )
{
	string strConf = "";
	EmTpLostPackageRestore emLostPackage;
	bool bChange = false;

	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxLevel",strConf,m_pWndTree);
	emLostPackage = TransLostPacketConf( strConf );
	m_emTempLevel = emLostPackage;

	if ( emLostPackage != m_emLostPacket )
	{
		bChange = true;
	}
	else
	{
		bChange = false;
	}
	CheckData( "CfgAdvanceDlg/BtnLossPacket", bChange );	
	UpBtnState();
	return true;
}

bool CCfgAdvanceDlg::OnRouteCfgChange(const IArgs & arg)
{
	string strRouteCfg = "";
	UIFACTORYMGR_PTR->GetComboText( "CfgAdvanceDlg/ComboboxLevel", strRouteCfg, m_pWndTree );

	return true;
}

bool CCfgAdvanceDlg::OnBtnAdd(const IArgs& args)
{
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_ROUTESELDATA_Click, 0, 0 );

	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrRouteCfgDlg );

	return true;	
}

bool CCfgAdvanceDlg::OnBtnDel(const IArgs& args)
{
	MSGBOX_RET nResult = MSGBOX_OK;
	MSG_BOX( nResult, "·�����ô���ᵼ������̱������ȷ���Ƿ�ɾ������·�ɣ�");
	if (nResult == MSGBOX_OK)
	{
		u16 nRet = COMIFMGRPTR->RouteMngDelCmd(m_tTRouteCfgSel);
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "ɾ��·��������ʧ��" );
		}
	}

	return true;
}

bool CCfgAdvanceDlg::OnCom2SelectedChange( const IArgs & arg )
{
	string strComType = "";
	EmComType emComType;
	bool bChange = false;
	
	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxCom2",strComType,m_pWndTree);
	emComType = TransComType( strComType );
	
	if ( emComType != m_aemComType[0] )
	{
		bChange = true;
	}
	else
	{
		bChange = false;
	}
	CheckData( "CfgAdvanceDlg/ComboboxCom2", bChange );	
	UpBtnState();
	return true;
}

bool CCfgAdvanceDlg::OnCom3SelectedChange( const IArgs & arg )
{
	string strComType = "";
	EmComType emComType;
	bool bChange = false;
	
	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxCom3",strComType,m_pWndTree);
	emComType = TransComType( strComType );
	
	if ( emComType != m_aemComType[1] )
	{
		bChange = true;
	}
	else
	{
		bChange = false;
	}
	CheckData( "CfgAdvanceDlg/ComboboxCom3", bChange );	
	UpBtnState();
	return true;
}

HRESULT CCfgAdvanceDlg::OnLostPacketNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)wparam;
	EmTpLostPackageRestore emLostPackage;
	emLostPackage = *( EmTpLostPackageRestore *)lparam;

	if ( !bSuccess )
	{
		WARNMESSAGE( "���ö����ش�����ʧ��" );
		return S_FALSE;
	}

	m_emLostPacket = emLostPackage;
	m_emTempLevel = emLostPackage;

	UpdateBtnLossPacket( m_emLostPacket );
	m_vctWndName.clear();
	UpBtnState();

	return S_OK;
}

LRESULT CCfgAdvanceDlg::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmInConf", m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );

		UpdateBtnLossPacket( m_emTempLevel );
	}
	return S_FALSE;
}

HRESULT CCfgAdvanceDlg::OnSetRouteInfoNty(WPARAM wparam, LPARAM lparam)
{
	vector<TRouteCfg> vecTRouteCfg;
	LIBDATAMGRPTR->GetRouteInfoData( vecTRouteCfg );

	Value_ItemRouteCfg valStyle(&vecTRouteCfg);
	UIFACTORYMGR_PTR->SetPropertyValue( valStyle, m_strRouteInfoList, m_pWndTree );

	UpdateBtnState();

	return S_OK;
}


HRESULT CCfgAdvanceDlg::OnAddRouteInfoInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bSuccess = *(BOOL*)wparam;

	if( !bSuccess )
	{
		WARNMESSAGE("���·��ʧ��");
		return S_FALSE;
	}

	vector<TRouteCfg> vecTRouteCfg;
	LIBDATAMGRPTR->GetRouteInfoData( vecTRouteCfg );
	
	Value_ItemRouteCfg RouteInfoList( &vecTRouteCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( RouteInfoList, m_strRouteInfoList, m_pWndTree);

	memset( &m_tTRouteCfgSel, 0, sizeof(TRouteCfg) );
	UpdateBtnState();
	return S_OK;
}

HRESULT CCfgAdvanceDlg::OnDelRouteInfoInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bSuccess = *(BOOL*)wparam;
	
	if( !bSuccess )
	{
		WARNMESSAGE("ɾ��·��ʧ��");
		return S_FALSE;
	}
	
	vector<TRouteCfg> vecTRouteCfg;
	LIBDATAMGRPTR->GetRouteInfoData( vecTRouteCfg );
	
	Value_ItemRouteCfg RouteInfoList( &vecTRouteCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( RouteInfoList, m_strRouteInfoList, m_pWndTree);

	memset( &m_tTRouteCfgSel, 0, sizeof(TRouteCfg) );
	UpdateBtnState();

	return S_OK;
}

string CCfgAdvanceDlg::GetLoatPacketConf( EmTpLostPackageRestore emLostPacket )
{
	string strConf = "";

	switch( emLostPacket )
	{
	case emTPLPSpeedFast:
		strConf = "";
		break;
	case emTPLPSpeedNormal:
		strConf = "��";
		break;
	case emTPLPSpeedSlow:
		strConf = "��";
		break;
	case emTPLPQualityFirst:
		strConf = "��";
		break;
	}

	return strConf;
}

void CCfgAdvanceDlg::UpdateBtnLossPacket( EmTpLostPackageRestore emLostPacket )
{
	string strLevel = "";
	strLevel = GetLoatPacketConf( emLostPacket );

	UIFACTORYMGR_PTR->SetComboText("CfgAdvanceDlg/ComboboxLevel",strLevel,m_pWndTree);
	if ( emLostPacket == emTPLPSpeedFast )
	{
		UIFACTORYMGR_PTR->SetSwitchState("CfgAdvanceDlg/BtnLossPacket",false,m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("SchmClose",m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState("CfgAdvanceDlg/BtnLossPacket",true,m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme("SchmNormal",m_pWndTree);
	}
}

void CCfgAdvanceDlg::UpdateBtnState()
{
	if (m_pWndTree == NULL)
	{
		return;
	}
	
	vector<TRouteCfg> vecTRouteCfg;
	LIBDATAMGRPTR->GetRouteInfoData( vecTRouteCfg );
	
	bool bChoose = false;
	if ( (m_tTRouteCfgSel.dwDstNet != 0 ) || ( m_tTRouteCfgSel.dwDstNetMask != 0 ) || (m_tTRouteCfgSel.dwNextIP != 0 )  )
	{
		bChoose = true;
	}
	
	if ( bChoose )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnDel, true, m_pWndTree );
	}
	else
	{
		int nNum = vecTRouteCfg.size();
		if ( nNum == 10 )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, false, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, true, m_pWndTree );
		}

		UIFACTORYMGR_PTR->EnableWindow( m_strBtnDel, false, m_pWndTree );
	}
	
}

void CCfgAdvanceDlg::ResetAllCtrl()
{
	if (m_pWndTree == NULL)
	{
		return;
	}
	
	vector<TRouteCfg> vecTRouteCfg;
	Value_ItemRouteCfg NetRouteList( &vecTRouteCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( NetRouteList, m_strRouteInfoList, m_pWndTree);
		
	UIFACTORYMGR_PTR->LoadScheme( "SchmRouteMngCtrlReset", m_pWndTree );
}

EmTpLostPackageRestore CCfgAdvanceDlg::TransLostPacketConf( string strConf )
{
	EmTpLostPackageRestore emLostPacket;

	if ( strcmp( strConf.c_str(),"" ) == 0 )
	{
		emLostPacket = emTPLPSpeedFast;
	}
	else if ( strcmp( strConf.c_str(),"��" ) == 0 )
	{
		emLostPacket = emTPLPSpeedNormal;
	}
	else if ( strcmp( strConf.c_str(),"��" ) == 0 )
	{
		emLostPacket = emTPLPSpeedSlow;
	}
	else if( strcmp( strConf.c_str(),"��" ) == 0 )
	{
		emLostPacket = emTPLPQualityFirst;
	}
	return emLostPacket;
}

EmComType CCfgAdvanceDlg::TransComType( string strComType )
{
	EmComType emComType;
	
	if ( strcmp( strComType.c_str(),"��ֽ���豸" ) == 0 )
	{
		emComType = emDFScreen;
	}
	else
	{
		emComType = emDCam;
	}
	return emComType;
}

bool CCfgAdvanceDlg::OnBtnSave( const IArgs& args )
{
	string strLevel = "";
	EmTpLostPackageRestore emLostPackage;
	bool bOpen = false;
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("�л�������У���������") );
		m_vctWndName.clear();
		UpBtnState();
		OnConfStateNty(0,0);
		UpdateBtnLossPacket(m_emLostPacket);
		return false;	
	}
	
	UIFACTORYMGR_PTR->GetSwitchState("CfgAdvanceDlg/BtnLossPacket",bOpen,m_pWndTree);
	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxLevel",strLevel,m_pWndTree);

	if ( ( bOpen == TRUE ) && ( strLevel.size() == 0 ))
	{
		MSG_BOX_OK( _T("�����ö����ش�����") );
		return false;
	}
	
	emLostPackage = TransLostPacketConf( strLevel );

	if (emLostPackage != m_emLostPacket)
	{
		u16 wRet = COMIFMGRPTR->SetLostPacketCmd( emLostPackage );	
		if ( wRet != NO_ERROR )
		{
			WARNMESSAGE( "�����ָ����÷���ʧ��" );
		}
	}

	string strComType2 = "";
	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxCom2",strComType2,m_pWndTree);
	EmComType emComType2 = TransComType(strComType2);
	string strComType3 = "";
	UIFACTORYMGR_PTR->GetComboText("CfgAdvanceDlg/ComboboxCom3",strComType3,m_pWndTree);
	EmComType emComType3 = TransComType(strComType3);
	if (emComType2 != m_aemComType[0] || emComType3 != m_aemComType[1])
	{
		u16 wRet = COMIFMGRPTR->SetSelectComCmd( emComType2, emComType3 );	
		if ( wRet != NO_ERROR )
		{
			WARNMESSAGE( "�������÷���ʧ��" );
		}
	}

	return true;
}

bool CCfgAdvanceDlg::OnBtnCancel( const IArgs& args )
{
	OnSelectComInd(-1,-1);

	m_emTempLevel = m_emLostPacket;
	UpdateBtnLossPacket(m_emLostPacket);

	m_vctWndName.clear();
	UpBtnState();

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;
}

bool CCfgAdvanceDlg::OnClickRouteMngLst(const IArgs & arg)
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_RouteMng * pDataTemp = dynamic_cast< const Data_RouteMng*>(pIData) )
		{
 			m_tTRouteCfgSel = pDataTemp->m_tRouteCfg; 			
 			UpdateBtnState();
		}
	}

	return true;
}

bool CCfgAdvanceDlg::OnClickRouteCfgLstBlack(const IArgs& args)
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	
	memset( &m_tTRouteCfgSel, 0, sizeof(TRouteCfg) );
	UpdateBtnState();

	return true;
}

bool CCfgAdvanceDlg::IsCfgChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgAdvanceDlg::SaveMsgBox()
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

//����
HRESULT CCfgAdvanceDlg::OnSelectComInd(WPARAM wparam, LPARAM lparam)
{
	if (wparam != -1 && lparam != -1)
	{
		m_aemComType[0] = (EmComType)(wparam);
		m_aemComType[1] = (EmComType)(lparam);
	}
	//com2
	switch(m_aemComType[0])
	{
	case emDFScreen:
		UIFACTORYMGR_PTR->SetComboText( "CfgAdvanceDlg/ComboboxCom2", "��ֽ���豸", m_pWndTree ); 
		break;
	case emDCam:
		UIFACTORYMGR_PTR->SetComboText( "CfgAdvanceDlg/ComboboxCom2", "�ĵ������", m_pWndTree ); 
		break;
	default:
		break;
	}
	//com3
	switch(m_aemComType[1])
	{
	case emDFScreen:
		UIFACTORYMGR_PTR->SetComboText( "CfgAdvanceDlg/ComboboxCom3", "��ֽ���豸", m_pWndTree ); 
		break;
	case emDCam:
		UIFACTORYMGR_PTR->SetComboText( "CfgAdvanceDlg/ComboboxCom3", "�ĵ������", m_pWndTree ); 
		break;
	default:
		break;
	}

	CheckData( "CfgAdvanceDlg/ComboboxCom2", false );	
	CheckData( "CfgAdvanceDlg/ComboboxCom3", false );	
	UpBtnState();

	return S_OK;
}