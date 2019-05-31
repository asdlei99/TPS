// outPrint.cpp: implementation of the COutPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmcWebProj.h"
#include "outPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConfCtrlIF* COutPrint::m_pconfCtrlIF = NULL;
CConfTemplateCtrlIF* COutPrint::m_pTmpConfigIF = NULL;    
CUmsConfigCtrlIF* COutPrint::m_pUmsConfig = NULL; 
CCncAddrbookIF* COutPrint::m_pCncAddrBook = NULL; 
COutPrint* COutPrint::m_pOutPrint = NULL;

COutPrint::COutPrint()
{
	if( m_pconfCtrlIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
	}

	if( m_pTmpConfigIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pTmpConfigIF);
	}

	if( m_pUmsConfig == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
	}
	
	if( m_pCncAddrBook == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pCncAddrBook);
	}
}

COutPrint::~COutPrint()
{

}

COutPrint* COutPrint::GetOutPrintPtr()
{
	if ( NULL == m_pOutPrint )
	{
		m_pOutPrint = new COutPrint();
	}

	return m_pOutPrint;
}

void COutPrint::Clean()
{
	SAFE_RELEASE(m_pOutPrint);
}

void COutPrint::GetAllConfInfo()
{
	ARRAY<TCMSConf> vecCurConfRefreshList;
	if ( m_pconfCtrlIF != NULL )
	{
		m_pconfCtrlIF->GetConfList(vecCurConfRefreshList);
		if ( vecCurConfRefreshList.size() == 0 )
		{
	       PrtMsg( "\n    目前无会议信息\n" );
		   return;
		}

		u16 wConfIdTmp;
		TCMSConf tCmsConf;
		CString strChairName;
		CString strAlias;
		CString strDate;
		CString strTime;

		for ( s32 nIndex = 0; nIndex < vecCurConfRefreshList.size(); nIndex++ )
		{ 
			tCmsConf = vecCurConfRefreshList[nIndex];
			wConfIdTmp = tCmsConf.m_wConfID;
			strAlias = tCmsConf.m_achConfName;
			strChairName = tCmsConf.GetChairManAliars();

			time_t tmStartTime = tCmsConf.m_tStartTime;
			CTime ctmStartTime( tmStartTime );
			strDate = ctmStartTime.Format("%Y.%m.%d");
			strTime = ctmStartTime.Format("%H:%M");

		    PrtMsg("\n   Conf ID:%d, Conf Name:%s, ChairMan:%s, Conf Start Date:%s, Conf Start Time:%s  ", 
				   wConfIdTmp, strAlias, strChairName, strDate, strTime ); 
		}
	}
}


void COutPrint::GetConfInfo( u16 wConfID )
{
	ARRAY<TCMSConf> vecCurConfRefreshList;
	if ( m_pconfCtrlIF != NULL )
	{
		m_pconfCtrlIF->GetConfList(vecCurConfRefreshList);
		
		u16 wConfIdTmp;
		TCMSConf tCmsConf;
		CString strChairName;
		CString strAlias;
		CString strDate;
		CString strTime;
		BOOL bFind = FALSE;
		for ( s32 nIndex = 0; nIndex < vecCurConfRefreshList.size(); nIndex++ )
		{ 
			tCmsConf = vecCurConfRefreshList[nIndex];
			wConfIdTmp = tCmsConf.m_wConfID;

			if( wConfIdTmp != wConfID )
			{
				continue;
			}

			bFind = TRUE;

			strAlias = tCmsConf.m_achConfName;
			strChairName = tCmsConf.GetChairManAliars();
			
			time_t tmStartTime = tCmsConf.m_tStartTime;
			CTime ctmStartTime( tmStartTime );
			strDate = ctmStartTime.Format("%Y.%m.%d");
			strTime = ctmStartTime.Format("%H:%M");
			
			PrtMsg("\n   Conf ID:%d, Conf Name:%s, ChairMan:%s, Conf Start Date:%s, Conf Start Time:%s  ", 
				wConfIdTmp, strAlias, strChairName, strDate, strTime ); 
		}

		if ( !bFind )
		{
			PrtMsg( "\n    未找到相应会议信息\n" );
			return;
		}

	}
}

void COutPrint::GetAllTpl()
{
	TplArray<TTPConfTemplate> tpTmpRefreshList;    //会议模板刷新列表
	if ( m_pTmpConfigIF != NULL )
	{
		m_pTmpConfigIF->GetConfTemplateList(tpTmpRefreshList);

		if ( tpTmpRefreshList.Size() == 0 )
		{
			PrtMsg( "\n    目前无会议模板信息\n" );
			return;
		}

		for( s32 nIndex = 0; nIndex < tpTmpRefreshList.Size(); nIndex++ )
		{
			TCMSConfTemplate* pTConfTemp = (TCMSConfTemplate*)&tpTmpRefreshList.GetAt(nIndex);
			if ( pTConfTemp == NULL )
			{
				continue;
			}
			
			CString strConfTplName = pTConfTemp->m_achConfName;

			PrtMsg("\n   Conf Template Name:%s", strConfTplName ); 
		}
	}
}

void COutPrint::GetAllGlobalAddr()
{
	vector<TAliasEx> vctAllRegInfo;
	vctAllRegInfo = m_pUmsConfig->GetAllTAliasEx();
	s32 nRegInfoCount = vctAllRegInfo.size();
	
	for( int i = 0; i < nRegInfoCount; i++ )
	{
		TAliasEx tAlias = vctAllRegInfo.at(i);
		TAddrInfo tAddrInfo;
		tAddrInfo.dwEntryIdx = i;
		vector<TTPAlias>::iterator it = tAlias.m_vecTTPAlias.begin();
		for ( ; it != tAlias.m_vecTTPAlias.end(); it++ )
		{
			if ( it->m_byType == tp_Alias_e164 )
			{
				strncpy( tAddrInfo.achE164, it->m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
			else
			{
				strncpy( tAddrInfo.achEntryName, it->m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
		}

		CString strName = tAddrInfo.achEntryName;
		CString strE164 = tAddrInfo.achE164;
		PrtMsg("\n   global addrbook Name:%s  global addrbook E164:%s", strName, strE164 );
	}

	PrtMsg("\n   global addrbook count:%d\n", nRegInfoCount );
}

void COutPrint::SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry )
{
	s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //条目名称
	s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164号
	
	cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
	cAddrEntry.GetMtNumber( aszE164, cAddrEntry.GetMtNumberLen() + 1 );
	
	tAddrInfo.dwEntryIdx = cAddrEntry.GetEntryIndex();
	strncpy( tAddrInfo.achEntryName, aszEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
	strncpy( tAddrInfo.achE164, aszE164, MAX_E164NUM_LEN + 1 );
}

void COutPrint::GetAllLocalAddr()
{
	if ( m_pCncAddrBook == NULL )
	{
		return;
	}
	
	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	//获取基本条目个数
	u32 dwUsedSize = cAddrBook.GetAddrEntryUsedSize();	 
	
	u32 dwIndex = 0;
	s32 nIndex = 0;
	CAddrEntry cAddrEntry;
	dwIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );
	while ( nIndex < dwUsedSize )
	{
		if ( dwIndex != INVALID_INDEX )
		{	
			TAddrInfo tAddrInfo;
			SetAddrItemInfo( tAddrInfo, cAddrEntry );

			CString strName = tAddrInfo.achEntryName;
			CString strE164 = tAddrInfo.achE164;
		    PrtMsg("\n   local addrbook Name:%s  local addrbook E164:%s", strName, strE164 );
			
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrEntry( dwIndex, &cAddrEntry );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwIndex = cAddrEntry.GetEntryIndex();
			}			
		}
		else
		{
			break;
		}
	}

	PrtMsg("\n   local addrbook count:%d\n", dwUsedSize );
}
