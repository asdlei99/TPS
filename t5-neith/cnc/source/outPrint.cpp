// outPrint.cpp: implementation of the COutPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "outPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutPrint::COutPrint()
{

}

COutPrint::~COutPrint()
{

}


void COutPrint::GetAllConfInfo()
{
   TCMSConf tConf;
   BOOL32 bInf =  ComInterface->IsInConf(&tConf);
   if ( !bInf )
   {
       PrtMsg( "\n    目前无会议信息\n" );
   }
   else
   {  
        
	   PrtMsg("\n    ID:%d, Name:%s, E164:%s, confType:%d , ChairMan:%s(CnsID=%d),speaker:%s(CnsID=%d),DualAlairs:%s(CnsID:%d)\n  ",  
                                    tConf.m_wConfID,tConf.m_achConfName,tConf.m_achConfE164,tConf.m_emConfType, tConf.m_tChairName.m_abyAlias, 
                                    tConf.m_wDefaultChairMan,tConf.GetSpeakerAliars(),tConf.m_wSpeaker,tConf.GetDualAliars(),tConf.m_wDual);

           CTime tmStart( tConf.m_tStartTime ); 
           PrtMsg(  "\n    会议开始时间：%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", 
                         tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
                  
   }
}


void COutPrint::GetConfInfo( u16 wConfID )
{
//     TCMSConf* p = ComInterface->GetConfByID( wConfID );
//     if ( p == NULL )
//     {
//         PrtMsg( "\n    未获取到会议板\n" );
//     }
//     else
//     {
//         PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan:%s(CnsID=%d), speaker:%s(CnsID=%d), DualAlairs:%s(CnsID:%d), ConfType=%d\n  ",  
//                                     p->m_wConfID,p->m_achConfName,p->m_achConfE164,p->GetChairManAliars(), p->m_wDefaultChairMan, p->GetSpeakerAliars(),p->m_wSpeaker,p->GetDualAliars(),p->m_wDual,p->m_emConfType);
// 
//         CTime tmStart( p->m_tStartTime ); 
//         PrtMsg(  "\n    会议开始时间：%.4d-%.2d-%.2d %.2d:%.2d:%.2d \n", 
//                          tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
//     }
}


void COutPrint::GetCncBuildVersion(s8 achVersion[MAX_DEVICEVER_LEN])
{
	s8 achMon[16] = {0};
	u32 byDay = 0;
	u32 byMonth = 0;
	u32 wYear = 0;
	s8 achFullDate[24] = {0};

	s8 achDate[32] = {0};
	sprintf(achDate, "%s", __DATE__);

#ifdef WIN32
	sscanf(achDate, "%s %d %d", achMon, &byDay, &wYear );

	if ( 0 == stricmp( achMon, "JAN") )
		byMonth = 1;
	else if ( 0 == stricmp( achMon, "FEB") )
		byMonth = 2;
	else if ( 0 == stricmp( achMon, "MAR") )
		byMonth = 3;
	else if ( 0 == stricmp( achMon, "APR") )
		byMonth = 4;
	else if ( 0 == stricmp( achMon, "MAY") )
		byMonth = 5;
	else if ( 0 == stricmp( achMon, "JUN") )
		byMonth = 6;
	else if ( 0 == stricmp( achMon, "JUL") )
		byMonth = 7;
	else if ( 0 == stricmp( achMon, "AUG") )
		byMonth = 8;
	else if ( 0 == stricmp( achMon, "SEP") )
		byMonth = 9;
	else if ( 0 == stricmp( achMon, "OCT") )
		byMonth = 10;
	else if ( 0 == stricmp( achMon, "NOV") )
		byMonth = 11;
	else if ( 0 == stricmp( achMon, "DEC") )
		byMonth = 12;
	else
		byMonth = 0;

	sprintf( achFullDate, "%04d%02d%02d", wYear, byMonth, byDay );

	_snprintf( achVersion, MAX_DEVICEVER_LEN, "%s.%s", TPAD_VERSION_ID, achFullDate );

#else
	_snprintf( achVersion, MAX_DEVICEVER_LEN, "%s.%s", TPAD_VERSION_ID, achDate );
#endif
	achVersion[strlen(achVersion) + 1] = '\0';
}

void COutPrint::GetConfCnsInfo( u16 wCnsID )
{
    
    TCMSConf tConf;
    BOOL32 bInfo = ComInterface->IsInConf( &tConf );
    if ( !bInfo )
    {
        PrtMsg( "\n    未获取到会议信息\n" );
    }
    else
    {  
        TCnsInfo* pCns = tConf.GetCnsInfoByID( wCnsID );
        if ( pCns == NULL )
        {
            PrtMsg( "\n    未获取到会场信息\n" );
        }
        else
        {
            PrtMsg("\n    ID:%d, Name:%s, emEpType:%d, bOnline:%d, bMute:%d, bQuiet:%d,  emCallReason:%d \n  ",  
                wCnsID,tConf.m_achConfName,pCns->m_emEpType,pCns->m_bOnline,pCns->m_bMute, pCns->m_bQuiet,pCns->m_emCallReason);
 
        }

       
    }
}


void COutPrint::GetConfCnsInfo( )
{
    TCMSConf tConf;
    BOOL32 bInfo = ComInterface->IsInConf( &tConf );
    if ( !bInfo ) 
    {
        PrtMsg( "\n    未获取到会议\n" );
    }
    else
    {    
        for ( int j = 0; j< tConf.m_vctCnsList.size(); j++ )
        {
            PrtMsg("\n    cnsID:%d, ParentEpID:%d, achRoomName:%s, emEpType:%d, bOnLine:%d, wSpeakerNum=%d, bMute:%d, bQuiet:%d, emCallReason:%d \n", 
            tConf.m_vctCnsList.at(j).m_wEpID, tConf.m_vctCnsList.at(j).m_wParentEpID, tConf.m_vctCnsList.at(j).m_achRoomName,
            tConf.m_vctCnsList.at(j).m_emEpType, tConf.m_vctCnsList.at(j).m_bOnline, tConf.m_vctCnsList.at(j).m_wSpeakerNum,
            tConf.m_vctCnsList.at(j).m_bMute, tConf.m_vctCnsList.at(j).m_bQuiet, tConf.m_vctCnsList.at(j).m_emCallReason );
        }       
    }
}


void COutPrint::GetLocalCnsInfo()
{
    TTPCnsInfo tCnsInfo;
    ComInterface->GetLocalCnsInfo( tCnsInfo );
    in_addr addr;
    CString strIp;
    int nCount = sizeof(tCnsInfo.m_adwIP)/sizeof(u32);
    for ( int i = 0 ; i< nCount ; i++ )
    {  
        CString temp;
        addr.S_un.S_addr = tCnsInfo.m_adwIP[i];
        temp.Format(_T("%s") , inet_ntoa(addr));
        strIp += temp;
    } 
    

    PrtMsg("\n    Name:%s, E164:%s, DualPos:%d, Level:%d, ScreenNum:%d, IP:%s\n",
              tCnsInfo.m_achRoomName,tCnsInfo.m_achE164,tCnsInfo.m_byDualPos,tCnsInfo.m_emLevel,tCnsInfo.m_wScreenNum,strIp);
}


void COutPrint::IsLocalCnsInConf()
{ 
    TTPCnsConfStatus  confstate = ComInterface->GetLocalCnsConfState() ;
   
    PrtMsg("\n    TConfState: %d ( %d:CALL_IDLE, %d:CALL_CALLING, %d:CALL_CONNECTED), confID:%d, confName:%s, confType:%d, MixMotive:%d, EncryptType:%d\n, ", 
        confstate.emState, em_CALL_IDLE, em_CALL_CALLING, em_CALL_CONNECTED, confstate.wConfID, confstate.achConfName, confstate.m_emCallType, confstate.m_bMixMotive, confstate.m_emTPEncryptType);

    TCMSConf conf;
    BOOL32 bInConf = ComInterface->IsInConf( &conf );
    if ( bInConf )
    {
        PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan:%s(CnsID=%d)\n  ",  
                conf.m_wConfID,conf.m_achConfName,conf.m_achConfE164,conf.GetChairManAliars(), conf.m_wDefaultChairMan);
     
        CTime tmStart( conf.m_tStartTime );
        PrtMsg(  "    会议开始时间：%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", 
                         tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
    }      
}

void COutPrint::ShowConfTemp( u16 wID )
{
    /*
     if ( wID == INVALID_WORD )  //显示所有
     {
         TplArray<TTPConfTemplate> *pLst = ComInterface->GetConfTemplateList();
         if ( pLst == NULL )
         {
             PrtMsg( "\n    获取会议模板列表失败\n" );
         }
         else
         {  
             CString msg;
             int nCount = pLst->Size();
			 PrtMsg( "    Num: %d \n", nCount );
             for ( int i = 0 ; i< nCount; i++ )
             {  
                  
                 PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan: %d \n  ",  
                     pLst->GetAt(i).m_wID,pLst->GetAt(i).m_achConfName,pLst->GetAt(i).m_achConfE164, pLst->GetAt(i).m_wDefaultChairMan ); 
                                 
             }           
         }
     }
     else 
     {
         // 显示一个
         TTPConfTemplate* p = ComInterface->GetConfTemplateByID( wID );
         if ( p == NULL )
         {
             PrtMsg( "\n    未获取到会议模板\n" );
         }
         else
         {
             PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan: %d\n  ",  
                 p->m_wID,p->m_achConfName,p->m_achConfE164, p->m_wDefaultChairMan);
         }
     }
     */
}


/*

  enum EMPosPic
  {
  emPic_Invalid = 0,
		emPic_Local,
        emPic_Static,
        emPic_Speaker,
        emPic_Dual,
        emPic_Poll,
        emPic_SelView,              //选看远端 
        emPic_SelDual,              //选看双流
        emPic_SelLocal,             //选看本地
};
*/
void COutPrint::ShowScrnInfo()
{
    vector<TScreenInfo> vctScreenInfo;
    u16 re = ComInterface->GetCnsScreenInfo( vctScreenInfo );
    if ( re != NO_ERROR )
    {
       PrtMsg( "\n    获取屏信息失败\n" );  
    }

    vector<TScreenInfo>::iterator it = vctScreenInfo.begin();
    while ( it != vctScreenInfo.end() )
    {
        PrtMsg("\n    ID:%d, Name:%s, emPic:%d  \n ( emPic_Invalid:%d, emPic_Local:%d, emPic_Static:%d, emPic_Speaker:%d, \
 emPic_Dual:%d, emPic_Poll:%d, emPic_SelView:%d, emPic_SelDual:%d,emPic_SelLocal:%d )\n", 
            it->byScreenID, it->achCnsName,it->emPosPic, emPic_Invalid, emPic_Local, emPic_Static,emPic_Speaker, emPic_Dual,
            emPic_Poll, emPic_SelView,emPic_SelDual,emPic_SelLocal);
        it ++;
    }

	//显示选看信息
	PrtMsg( "\n    显示选看信息" );  
	TTPSelViewNtfy tTPSelViewNtfy = ComInterface->GetSelWatchStatus();	
	for (int i=0 ; i<TP_MAX_STREAMNUM; i++)
	{
		PrtMsg("\n--UIType:%d, bSel:%d, ConfID:%d, EpID:%d, ScreenIndx:%d, ViewEpType:%d, DistID:%d, DstScrIndx:%d\n",
			tTPSelViewNtfy.m_atSelView[i].m_emUIType, tTPSelViewNtfy.m_atSelView[i].m_bSel, tTPSelViewNtfy.m_atSelView[i].m_wConfID,
			tTPSelViewNtfy.m_atSelView[i].m_wEpID, tTPSelViewNtfy.m_atSelView[i].m_wScreenIndx, tTPSelViewNtfy.m_atSelView[i].m_emType,
			tTPSelViewNtfy.m_atSelView[i].m_wDstID, tTPSelViewNtfy.m_atSelView[i].m_wDstScrIndx);
	}
}

void COutPrint::ShowVmpInfo()
{
    vector<TBrdVmpResNtfy> vctBrdVmpInfo = ComInterface->GetBrdVmpStatus();

    //画面合成
    PrtMsg( "画面合成信息:\n" );
    PrtMsg( "num= %d", vctBrdVmpInfo.size());

    for ( u16 i = 0; i < vctBrdVmpInfo.size(); i++ )
    {
        TBrdVmpResNtfy tBrdVmp = vctBrdVmpInfo.at(i);
        PrtMsg( "\n-- %d: confId:%d, byEqpID:%d, szEqpAlias:%s, m_emStat:%d(1:空闲;2,3:占用;0,4:错误), m_bVmpAuto:%d\n",
            i, tBrdVmp.m_wConfID, tBrdVmp.m_tEqpInfo.m_byEqpID, tBrdVmp.m_tEqpInfo.m_szEqpAlias, tBrdVmp.m_emStat, tBrdVmp.m_bVmpAuto );

        TBrdVmpStyle tVmpStyle = tBrdVmp.m_tVmpStyle;
        PrtMsg( "m_emVmpStyle:%d, m_wSpeakerIndx:%d, m_wDualIndx:%d, m_wChnlNum:%d\n",
            tVmpStyle.m_emVmpStyle, tVmpStyle.m_wSpeakerIndx, tVmpStyle.m_wDualIndx, tVmpStyle.m_wChnlNum );
        for ( u16 j = 0; j < tVmpStyle.m_wChnlNum; j++ )
        {
            PrtMsg( "*** %d: m_wEpID=%d, m_wScrIndx=%d", 
                j, tVmpStyle.m_atVmpChnl[j].m_wEpID, tVmpStyle.m_atVmpChnl[j].m_wScrIndx );
            if ( j % 2 != 0 )
            {
                PrtMsg( "\n" );
            }
        }
    }
    PrtMsg( "\n" );
}


void COutPrint::ShowAllUseInfo()
{
     
    TplArray<CUserFullInfo>* pUserLst = ComInterface->GetUserList();
    if ( pUserLst == NULL )
    {
        PrtMsg("    未获取到用户信息\n" );  
        return;
    }

    int nSize = pUserLst->Size();
    for( int i = 0; i< nSize ; i++ )
    {
        PrtMsg("    Name: %s\n", pUserLst->GetAt(i).GetName() );  
    }


}

void COutPrint::ShowLocalIP()
{
//    u32 IP;
//    ComInterface->GetLocalIP( IP );
//    in_addr t;
//    t.S_un.S_addr = htonl(IP); 
//    PrtMsg("    LocalIP: %s\n", inet_ntoa( t ) );  
}

void COutPrint::ShowPollList()
{
	vector<u16>    vctPollList; 
	ComInterface->GetPollList( vctPollList );


	int nSize = vctPollList.size();
	for( int i = 0; i< nSize ; i++ )
	{
		PrtMsg("    PollList EpId%d: %d\n", i, vctPollList.at(i) );  
	}

}

void COutPrint::ShowAddrbook()
{
    CAddrBook cAddrBook = ComInterface->GetAddrBook();	

	//获取基本条目个数
    u32 dwEntrySize = cAddrBook.GetAddrEntryUsedSize();
    u32 dwGroupSize = cAddrBook.GetAddrGroupUsedSize();

    vector<TAddrItem> vctLocalList; 
    vctLocalList = *ComInterface->GetLocalAddrList();
    
    PrtMsg("    地址簿 会场个数: %d, 组个数: %d, LocalAddrList.size: %d\n", dwEntrySize, dwGroupSize, vctLocalList.size() ); 

	s32 nIndex = 0;

    CAddrEntry cAddrEntry;
    u32 dwFirstIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );

	while ( nIndex < dwEntrySize )
	{
		if ( dwFirstIndex != INVALID_INDEX )
		{	
			TAddrInfo tAddrInfo;
			ComInterface->SetAddrItemInfo( tAddrInfo, cAddrEntry );
            u16 wRate = cAddrEntry.GetCallRate();

            PrtMsg("    EntryIndex: %d, Type: %d(0网呈 1监控 2普通), Name: %s, E164: %s, IP: %s, CallRate:%d \n", 
                tAddrInfo.dwEntryIdx, tAddrInfo.byTerType, tAddrInfo.achEntryName, tAddrInfo.achE164, tAddrInfo.achIp, wRate );
  	
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrEntry( dwFirstIndex, &cAddrEntry );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwFirstIndex = cAddrEntry.GetEntryIndex();
			}			
		}
		else
		{
			break;
		}
	}

    //PrtMsg("    FirstIndex: %d, EntryIndex: %d, Name: %s, E164: %s\n", dwFirstIndex, tAddrInfo.dwEntryIdx, tAddrInfo.achEntryName, tAddrInfo.achE164 );
}

void COutPrint::ShowOnlineAddr()
{
	vector<TAddrInfo> vctCnsRegInfo;
	ComInterface->GetCnsRegInfo(&vctCnsRegInfo);

	for( int i = 0; i < vctCnsRegInfo.size(); i++ )
	{
		TAddrInfo tAddrInfo = vctCnsRegInfo.at(i);
		tAddrInfo.dwEntryIdx = i;
		
        PrtMsg("    EntryIndex: %d, Type: %d(0网呈 1监控 2普通), Name: %s, E164: %s, IP: %s \n", 
            tAddrInfo.dwEntryIdx, tAddrInfo.byTerType, tAddrInfo.achEntryName, tAddrInfo.achE164, tAddrInfo.achIp );	
	}
	
    vector<TAddrItem> vctGlobalList; 
    vctGlobalList = *ComInterface->GetGlobalAddrList();

    PrtMsg("    在线地址簿 会场个数: %d, GlobalList.size: %d\n", vctCnsRegInfo.size(), vctGlobalList.size() ); 
}

void COutPrint::ShowAddrEntry( u32 dwEntryIndex )
{
    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    bool bValid = cAddrBook.IsAddrEntryValid( dwEntryIndex );
    if ( !bValid )
    {
        PrtMsg("    地址簿不存在此会场"); 
        return;
    }

    CAddrEntry cEntry;
    cAddrBook.GetAddrEntry( &cEntry, dwEntryIndex );

    TAddrInfo tAddrInfo;
	ComInterface->SetAddrItemInfo( tAddrInfo, cEntry );

    PrtMsg("    EntryIndex: %d, Type: %d(0网呈 1监控 2普通), Name: %s, E164: %s, IP: %s \n", 
        tAddrInfo.dwEntryIdx, tAddrInfo.byTerType, tAddrInfo.achEntryName, tAddrInfo.achE164, tAddrInfo.achIp );
}

void COutPrint::DeleteAddr( u32 dwEntryIndex )
{
    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    bool bValid = cAddrBook.IsAddrEntryValid( dwEntryIndex );
    if ( !bValid )
    {
        PrtMsg("    地址簿不存在此会场"); 
        return;
    }

    CAddrEntry cEntry;
    cAddrBook.GetAddrEntry( &cEntry, dwEntryIndex );

    TAddrInfo tAddrInfo;
    ComInterface->SetAddrItemInfo( tAddrInfo, cEntry );

    PrtMsg("    EntryIndex: %d, Type: %d(0网呈 1监控 2普通), Name: %s, E164: %s, IP: %s \n", 
        tAddrInfo.dwEntryIdx, tAddrInfo.byTerType, tAddrInfo.achEntryName, tAddrInfo.achE164, tAddrInfo.achIp );

    ComInterface->DeleteEntry( dwEntryIndex );
}
