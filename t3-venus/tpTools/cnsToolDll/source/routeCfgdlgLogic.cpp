// routeCfgdlgLogic.cpp: implementation of the routeCfgdlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "routeCfgdlgLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRouteCfgdlgLogic::CRouteCfgdlgLogic()
: m_strEdtPriorLevel("EdtPriorLevel")
, m_strIPCtrlDstSubnetIP("IPCtrlDstSubnetIP")
, m_strIPCtrlMastIP("IPCtrlMastIP")
, m_strIPCtrlGatewayIP("IPCtrlGatewayIP")
{
	
}

CRouteCfgdlgLogic::~CRouteCfgdlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CRouteCfgdlgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CRouteCfgdlgLogic::InitWnd", CRouteCfgdlgLogic::InitWnd, ROUTECFGDLGLOGIC, CRouteCfgdlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CRouteCfgdlgLogic::OnBtnRouteCfgOk", CRouteCfgdlgLogic::OnBtnRouteCfgOk, ROUTECFGDLGLOGIC, CRouteCfgdlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CRouteCfgdlgLogic::OnEdtPriorLevelChange", CRouteCfgdlgLogic::OnEdtPriorLevelChange, ROUTECFGDLGLOGIC, CRouteCfgdlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CRouteCfgdlgLogic::OnEdtPriorLevelKillFocus", CRouteCfgdlgLogic::OnEdtPriorLevelKillFocus, ROUTECFGDLGLOGIC, CRouteCfgdlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CRouteCfgdlgLogic::OnBtnRouteCfgCancel", CRouteCfgdlgLogic::OnBtnRouteCfgCancel, ROUTECFGDLGLOGIC, CRouteCfgdlgLogic );
}

void CRouteCfgdlgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_ROUTESELDATA_Click, CRouteCfgdlgLogic::OnRouteAdd, ROUTECFGDLGLOGIC, CRouteCfgdlgLogic );
}

void CRouteCfgdlgLogic::UnRegFunc()
{
	
}

void CRouteCfgdlgLogic::UnRegMsg()
{
	
}

bool CRouteCfgdlgLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );
	
	UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlDstSubnetIP, m_pWndTree );
	
	return true;
}

void CRouteCfgdlgLogic::Clear()
{
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( g_stcStrRouteCfgDlg );
	if ( bIsVisible )
	{
		s32 nResult = 0;
		UIFACTORYMGR_PTR->Endmodal( nResult, g_stcStrRouteCfgDlg );
	}		
}

bool CRouteCfgdlgLogic::OnBtnRouteCfgOk(const IArgs & arg)
{
	TRouteCfg tRouteCfg;	
 	Value_WindowCaption valDstSubnetIP;
 	UIFACTORYMGR_PTR->GetPropertyValue( valDstSubnetIP, m_strIPCtrlDstSubnetIP, m_pWndTree );
	
	Value_IpEditData valSubnetIP;
    UIFACTORYMGR_PTR->GetPropertyValue( valSubnetIP, m_strIPCtrlDstSubnetIP, m_pWndTree ); 
	if ( valSubnetIP.dwIP != 0 && !CCallAddr::IsValidIpV4(valSubnetIP.dwIP) ) 
	{
		MSG_BOX_OK( "Ŀ������IP��ַ���Ϸ�" );
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlDstSubnetIP, m_pWndTree );
		return false;
	}
	
	u32_ip dwDstSubnetIP = inet_addr(valDstSubnetIP.strCaption.c_str());
	
	vector<TRouteCfg> vecTRouteCfg;
	LIBDATAMGRPTR->GetRouteInfoData( vecTRouteCfg );
	vector<TRouteCfg>::iterator it = vecTRouteCfg.begin();
	for ( ; it != vecTRouteCfg.end(); it++ )
	{
		if ( it->dwDstNet == dwDstSubnetIP )
		{
			MSG_BOX_OK( "Ŀ��������ַ�Ѵ��ڣ��޷����" );
			return false;
		}
	}
	
	tRouteCfg.dwDstNet = dwDstSubnetIP;	
	Value_WindowCaption valCtrlMaskIP;
	UIFACTORYMGR_PTR->GetPropertyValue( valCtrlMaskIP, m_strIPCtrlMastIP, m_pWndTree );	
	Value_IpEditData valMaskIP;
    UIFACTORYMGR_PTR->GetPropertyValue( valMaskIP, m_strIPCtrlMastIP, m_pWndTree ); 

	if( 4294967295 == valMaskIP.dwIP )//255.255.255.255
	{
		
	}
	else
	{
		if( valMaskIP.dwIP != 0 && !CCallAddr::IsValidIpMask( valMaskIP.dwIP ) )
		{
			MSG_BOX_OK( "����IP��ַ���Ϸ�" );
			UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlMastIP, m_pWndTree );
			return false;
		}
	}
	
	u32_ip dwMaskIP = inet_addr(valCtrlMaskIP.strCaption.c_str());
	tRouteCfg.dwDstNetMask = dwMaskIP;

	if( ( tRouteCfg.dwDstNet >> 24 ) != 0 )
	{
		if( tRouteCfg.dwDstNetMask != 4294967295 )
		{
			MSG_BOX_OK("�����Ŀ��������ϲ��Ϸ�");
			UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlMastIP, m_pWndTree );
			return false;
		}
	}
	
	Value_WindowCaption valCtrlGatewayIP;
	UIFACTORYMGR_PTR->GetPropertyValue( valCtrlGatewayIP, m_strIPCtrlGatewayIP, m_pWndTree );
	
	Value_IpEditData valGatewayIP;
    UIFACTORYMGR_PTR->GetPropertyValue( valGatewayIP, m_strIPCtrlGatewayIP, m_pWndTree ); 

	if(valGatewayIP.dwIP != 0 && !CCallAddr::IsValidIpV4(valGatewayIP.dwIP))
	{
		MSG_BOX_OK("����IP��ַ���Ϸ�");
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlGatewayIP, m_pWndTree );
		return false;
	}
	
	u32_ip dwGatewayIP = inet_addr( valCtrlGatewayIP.strCaption.c_str() );
	tRouteCfg.dwNextIP = dwGatewayIP;

	if ( ( tRouteCfg.dwNextIP >> 24 ) == 0 ) 
	{
		MSG_BOX_OK("����IP��ַ���Ϸ�");
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlGatewayIP, m_pWndTree );
		return false;
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtPriorLevel, strCaption, m_pWndTree);
	
	u32 nEdtPriorLevel = atoi(strCaption.c_str());
	
	if( strCaption.empty() )
	{
		MSG_BOX_OK( "���ȼ�����Ϊ��" );
		return false;
	}
	
	if( nEdtPriorLevel < 1 || nEdtPriorLevel > 10 )
	{
		MSG_BOX_OK( "·�����ȼ�Ӧ����1-10֮��" );
		return false;
	}
	
	tRouteCfg.dwPri = nEdtPriorLevel;
	
	u16 nRet = COMIFMGRPTR->RouteMngAddCmd( tRouteCfg );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "·�����������ʧ��" );
	}
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrRouteCfgDlg );
	
	return true;
}

bool CRouteCfgdlgLogic::OnBtnRouteCfgCancel(const IArgs & arg)
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal( nResult, g_stcStrRouteCfgDlg );
	
	return true;
}

bool CRouteCfgdlgLogic::OnEdtPriorLevelChange(const IArgs & arg)
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtPriorLevel, strCaption, m_pWndTree);
	
	if( strCaption.empty() )
	{
		UIFACTORYMGR_PTR->LoadScheme( "TipUnVisible", m_pWndTree );
		return false;
	}
	
	u32 nEdtPriorLevel = atoi(strCaption.c_str());
	if( ( nEdtPriorLevel < 1 ) || ( nEdtPriorLevel> 10 ) )
	{
		UIFACTORYMGR_PTR->LoadScheme( "TipVisible", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "TipUnVisible", m_pWndTree );
	}
	
	return true;
}

bool CRouteCfgdlgLogic::OnEdtPriorLevelKillFocus(const IArgs & arg)
{
	return true;
}

HRESULT CRouteCfgdlgLogic::OnRouteAdd(WPARAM wparam, LPARAM lparam)
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmClean", m_pWndTree );
	return true;
}
