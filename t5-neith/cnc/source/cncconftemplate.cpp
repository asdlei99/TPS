#include "stdafx.h"
#include "commoninterface.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void  CCommonInterface::InvalidConfTemp( TTPConfTemplate &temp) const 
{ 
	temp.Clear();
	memset( &temp.m_atAuxMixList,INVALID_WORD,sizeof(temp.m_atAuxMixList));
	temp.m_wID = INVALID_WORD;
}

LRESULT CCommonInterface::OnRefreshConfTemplateLst(  WPARAM wParam, LPARAM lParam )
{ 
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	m_vctConfTempList = m_pCnsConfigCtrl->GetUmsRegInfo();

	NOTIFY_MSG( UI_CNS_REFRESH_CONFTEMPLATE_LIST, wParam, lParam ); 

	return NO_ERROR;
}

vector<TTPAlias>* CCommonInterface::GetConfTempList()
{
	return &m_vctConfTempList;
}

u16 CCommonInterface::UpdateConfTemplate()
{
	if ( NULL == m_pCnsConfigCtrl ) 
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->ReqSipRegInfo( emGetRegInfoType_UMS );
}