/*****************************************************************************
模块名      : CMS控制台
文件名      : sysconfig.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装CNS配置相关接口
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2011/05/10    1.0         肖楚然        创建
2014/09/23    2.0         吴蒨蒨      由vc6整合至VS2010
******************************************************************************/
#include "stdafx.h"
#include "commoninterface.h"
#include "cncevent.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



u16 CCommonInterface::CnsRegSipService(const TTPSipRegistrarCfg &tSipCfg)
{
    if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	
	u16 re  = m_pCnsConfigCtrl->RegSipService( tSipCfg );
	
	return re;
}

 
u16 CCommonInterface::CnsRegGkService( const TTPGKCfg &tCfg  )
{
    if( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfigCtrl->RegGk( tCfg );
    
    return re;
}

u16 CCommonInterface::CnsUnRegSipService()
{
    if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	
	u16 re  = m_pCnsConfigCtrl->UnRegSipService();
	
	return re;
}

u16 CCommonInterface::UpdateEthnetCfg( const TTPEthnetInfo& tInfo, EmTpIpNameNatSyn em )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
 
	u16 re  = m_pCnsConfigCtrl->UpdateEthnetCfg( tInfo, em );

	return re;
}

u16 CCommonInterface::GetEthnetCfg( TTPEthnetInfo& tInfo )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tInfo = m_pCnsConfigCtrl->GetEthnetCfg();

	return NO_ERROR;
}

u16 CCommonInterface::GetLocalCnsInfo( TTPCnsInfo& tCnsInfo ) const
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tCnsInfo = m_pCnsConfigCtrl->GetLocalCnsInfo();
	return NO_ERROR;
}

u16 CCommonInterface::UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex, EmTpIpNameNatSyn em )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;	
	}
	
	u16 wRe = m_pCnsConfigCtrl->UpdateCnsInfo( tInfo, byIndex, em );
	return wRe;
}
 

// BOOL32 CCommonInterface::IsCnsInConf( s8* achRoomName )  
// {
// 
// 	BOOL32 bInConf = IsInConf() ;
//     if ( bInConf )
//     {
//         u16 wID = m_tConfInfo.GetCnsIDByAlias( achRoomName );
//         if( wID != INVALID_WORD )
//         {
//             bInConf = TRUE;
//         }
//         else
//         {
//             bInConf = FALSE;
//         }
//              
// 
//     }
// 
// 	return bInConf;
// }


/**
* 功能:  本级cns是否是发言人
* @param [int]wConfID 会议信息 
* @return 成功返回TRUE,失败返回FALSE
* @remarks  
*/
// BOOL32 CCommonInterface::IsLocalCnsSpeaker(  )  
// {
//      
//     
//     if (  IsInConf() )
//     { 
//         s8 *Alairs = m_tConfInfo.GetSpeakerAliars();
//         if ( Alairs != NULL  )
//         {
//             TTPCnsInfo  tCnsInfo;
//             GetLocalCnsInfo( tCnsInfo );
//             if ( strcmp(tCnsInfo.m_achRoomName,Alairs) == 0 )
//             {
//                 return TRUE;
//             }
//         }
//     }
// 
//     return FALSE;
// }


/** 功能   设置系统时间
 *  @return 成功返回会场名,失败返回NULL
 *  @remarks 
 */
 u16 CCommonInterface::UpdateSysTime( const TTPTime& time )
 {
   	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
    return m_pCnsConfigCtrl->UpdateSysTime( time );
  
 }



/** 功能   获取系统时间
 *  @return 成功返回会场名,失败返回NULL
 *  @remarks 
 */
u16 CCommonInterface::ReqSysTime()
{
    if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
    return m_pCnsConfigCtrl->ReqSysTime( );
}

u16 CCommonInterface::UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	return m_pPortDiagCtrl->UpgradeSerCmd( tUpgradeSer );
}

u16 CCommonInterface::GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	tUpgradeSer = m_pPortDiagCtrl->GetUpgradeSerInfo();
	return NO_ERROR;
}

u16 CCommonInterface::CallServerCmd( const TTPCallSerInfo& tCallSerInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	return m_pPortDiagCtrl->CallServerCmd( tCallSerInfo );
}

u16 CCommonInterface::GetCallServerInfo( TTPCallSerInfo& tCallSerInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	
	tCallSerInfo = m_pPortDiagCtrl->GetCallServerInfo();
	return NO_ERROR;
}


u16 CCommonInterface::UpdateNATCfg( const TTPNatCfg& tInfo, EmTpIpNameNatSyn em )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
 
	u16 re  = m_pCnsConfigCtrl->UpdateNATCfg( tInfo, em );

	return re;
}

u16 CCommonInterface::GetNATCfg( TTPNatCfg& tInfo )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tInfo = m_pCnsConfigCtrl->GetNATCfg();

	return NO_ERROR;
}

u16 CCommonInterface::GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	m_pCnsConfigCtrl->GetNetMngData( vecTTPNMServerCfg ); 

	return NO_ERROR;
}

u16 CCommonInterface::NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsConfigCtrl->NetMngAddCmd( tTPNMServerCfg );
	
	return wRe;
}

u16 CCommonInterface::NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
		
	u16 wRe = m_pCnsConfigCtrl->NetMngModifyCmd( tTPNMServerCfg );
	
	return wRe;
}

u16 CCommonInterface::NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsConfigCtrl->NetMngDeleteCmd( tTPNMServerCfg );
	
	return wRe;
}

u16 CCommonInterface::SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCnsConfigCtrl->SetSysSleepInfo( tCenDevSleepInfo );
}

u16 CCommonInterface::GetSysSleepInfo( TCenDevSleepInfo& tCenDevSleepInfo )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
	
    tCenDevSleepInfo = m_pCnsConfigCtrl->GetSysSleepInfo();
    return NO_ERROR;
}

u16  CCommonInterface::SetTimeSynchroCmd( BOOL bIsCheck )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetTimeSynchroCmd(bIsCheck);
}

u16 CCommonInterface::SetTpadPasswordUpdate( TTpPasswordUpdateInfo tTpPasswordUpdateInfo )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetTpadPasswordUpdate(tTpPasswordUpdateInfo);
}

u16 CCommonInterface::GetPasswordUpdateInfo( TTpPasswordUpdateInfo& tTpPasswordUpdateInfo )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tTpPasswordUpdateInfo = m_pCnsConfigCtrl->GetPasswordUpdateInfo();

	return NO_ERROR;
}

//超级管理员信息
u16 CCommonInterface::SetSuperadmninInfo(TTpSuperUser tTpSuperUser)
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    return m_pCnsConfigCtrl->SetSuperadmninInfo(tTpSuperUser);
}

u16 CCommonInterface::GetSuperadmninInfo(TTpSuperUser& tTpSuperUser)
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    tTpSuperUser = m_pCnsConfigCtrl->GetSuperadmninInfo();

    return NO_ERROR;
}

u16 CCommonInterface::UnlockAllUser()
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    return m_pCnsConfigCtrl->UnlockAllUser();
}

/*用户相关接口*/
/*功  能	获取用户列表
参  数	 
返回值  成功返回用户列表指针，失败返回空
说  明	 */
TplArray<CUserFullInfo>* CCommonInterface::GetUserList()   
{
	u16 wRe = m_pCnsUserCtrl->GetUserList( m_tplUserList );

	return &m_tplUserList;
}

/*功  能	添加用户
参  数	user
返回值  成功返回0，失败返回错误码
说  明	 */
u16 CCommonInterface::AddUser( const CUserFullInfo& user )    
{
	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = NO_ERROR;

	BOOL32 bIexist = IsExistUser( (s8*)user.m_achname );

	if ( bIexist ) 
	{
		wRe = ERR_CMS_UI_NAME_REPEAT;
	}
	else
	{
		wRe = m_pCnsUserCtrl->AddUserReq( user );
	} 

	return wRe;

}

/*功  能	修改用户信息
参  数	user
返回值  成功返回0，失败返回错误码
说  明	 */
u16 CCommonInterface::UpdateUser( const CUserFullInfo& user )   
{
	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pCnsUserCtrl->ModifyUserReq( user );

	return wRe;
}

/*功  能	删除用户
参  数	user
返回值  成功返回0，失败返回错误码
说  明	 */
u16 CCommonInterface::DeleteUser( const CUserFullInfo & user )   
{
	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pCnsUserCtrl->DeleteUserReq( user );

	return wRe;
}

/*功  能	根据用户名获取用户信息
参  数	pUserName
返回值  成功返回用户信息指针，失败返回空指针
说  明	 */
CUserFullInfo *CCommonInterface::GetUserByName (   s8 *pUserName ) const 
{
	s16 nCont = m_tplUserList.Size();
	for ( s16 i = 0; i< nCont; i++)
	{   
		bool re = m_tplUserList.GetAt(i).IsEqualName(pUserName);
		if ( re ) 
		{
			return &m_tplUserList.GetAt(i); 
		}
	}

	return NULL;
}

/*功  能	判断用户名是否以存在
参  数	pUserName
返回值  成功返回TREU，失败返回FLASE
说  明	 */
BOOL32 CCommonInterface::IsExistUser ( s8 *pUserName ) const 
{
	s16 nCont = m_tplUserList.Size();
	for ( s16 i = 0; i< nCont; i++)
	{  
		bool re = m_tplUserList.GetAt(i).IsEqualName(pUserName);
		if ( re ) 
		{
			return TRUE; 
		}
	}

	return FALSE;
}

LRESULT CCommonInterface::OnRefreshUserLst(  WPARAM wParam, LPARAM lParam )
{
	m_tplUserList.Clear();

	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pCnsUserCtrl->GetUserList( m_tplUserList );

	NOTIFY_MSG(UI_UMS_REFRESH_USER_LIST,wParam,lParam);
	return wRe; 
} 

u16 CCommonInterface::GetLogoInfo( TTPLogoInfo& tInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	tInfo = m_pPortDiagCtrl->GetLogoInfo();
	return NO_ERROR;
}


u16 CCommonInterface::GetBannerInfo( TTPBannerInfo& tInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	tInfo = m_pPortDiagCtrl->GetBannerInfo();
	return NO_ERROR;
}


u16 CCommonInterface::CnIsShowLogoCmd( const TTPLogo& tTPLogo  )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	return m_pPortDiagCtrl->CnIsShowLogoCmd(tTPLogo);
}

u16 CCommonInterface::CnIsShowBannerCmd( const TTPBanner& tTPBanner )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	return m_pPortDiagCtrl->CnIsShowBannerCmd(tTPBanner);
}


u16 CCommonInterface::GetSipCfg( TTPSipRegistrarCfg& tSipCfg )
{
    if( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    tSipCfg = m_pCnsConfigCtrl->GetSipRegCfg();
    return NO_ERROR;
}


u16 CCommonInterface::GetGkCfg( TTPGKCfg& tGkCfg )
{
    if ( m_pCnsConfigCtrl != NULL )
    {
        tGkCfg = m_pCnsConfigCtrl->GetGkCfg();
    }

    return NO_ERROR;
}

u16 CCommonInterface::SetDataServerInfoCmd( const u32 dwIp )
{
    if( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    return m_pCnsConfigCtrl->SetDataServerInfoCmd(dwIp);
}

u16 CCommonInterface::SetMicStateCmd( u8 nIndex, BOOL bCheck )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfCtrl->SetMicStateCmd(nIndex, bCheck);
}

u16 CCommonInterface::GetWBSerIp( TTPDataConfInfo& tWBSerIp )
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    tWBSerIp = m_pCnsConfigCtrl->GetWBSerIp();
    return NO_ERROR;
}

u16 CCommonInterface::GetVideoFormatInfo( TTPVidForamt& tVidForamt ) const
{
    if ( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;	
    }

    tVidForamt = m_pPortDiagCtrl->GetVideoFormatInfo();
    return NO_ERROR;
}

u16 CCommonInterface::CallRateCmd( const u16 wDualCallRate )
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    m_pPortDiagCtrl->CallRateCmd(wDualCallRate);
    return NO_ERROR;
}

u16 CCommonInterface::GetCallRateInfo( u16& wCallRate ) const
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    wCallRate = m_pPortDiagCtrl->GetCallRate();
    return NO_ERROR;
}

u16 CCommonInterface::DualCallRateCmd( const u16 wDualCallRate )
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    m_pPortDiagCtrl->DualCallRateCmd(wDualCallRate);
    return NO_ERROR;
}

u16 CCommonInterface::GetDualCallRateInfo( u16& wDualCallRate ) const
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    wDualCallRate = m_pPortDiagCtrl->GetDualCallRate();
    return NO_ERROR;
}

u16 CCommonInterface::GetDualVideoFormatInfo( TTPVidForamt& tVidForamt ) const
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    tVidForamt = m_pPortDiagCtrl->GetDualVideoFormatInfo();
    return NO_ERROR;
}

u16 CCommonInterface::VideoFormatCmd( const TTPVidForamt& tVidForamt )
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    m_pPortDiagCtrl->VideoFormatCmd(tVidForamt);
    return NO_ERROR;
}

u16 CCommonInterface::DualVideoFormatCmd( const TTPVidForamt& tVidForamt )
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    m_pPortDiagCtrl->DualVideoFormatCmd(tVidForamt);
    return NO_ERROR;
}

EmTpAudioFormat CCommonInterface::GetAudioFormatInfo() const
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return emTPAEnd;
    }

    EmTpAudioFormat emTpAudioFormat = m_pPortDiagCtrl->GetAudioFormatInfo();
    return emTpAudioFormat;
}

u16 CCommonInterface::AudioFormatCmd( const EmTpAudioFormat& emAudioFormat )
{
    if ( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    m_pPortDiagCtrl->AudioFormatCmd(emAudioFormat);
    return NO_ERROR;
}

BOOL32 CCommonInterface::IsVidCutLine() const
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    return m_pCnsConfigCtrl->IsVidCutLine();
}

u16 CCommonInterface::SetVidCutLine( BOOL bIsVidCutLine )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    u16 re  =  m_pCnsConfigCtrl->SetVidCutLine(bIsVidCutLine);

    return re;
}

u16 CCommonInterface::SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt)
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfigCtrl->SetQtEncryptCfg( tQtEncrypt );

	return re;
}

 u16 CCommonInterface::GetQTEncrypt(TTpQtEncryptCfg& tQtEncrypt)
 {
	 if ( NULL == m_pCnsConfigCtrl )
	 {
		 return ERR_CMS;
	 }

	 tQtEncrypt = m_pCnsConfigCtrl->GetQTEncrypt();

	 return NO_ERROR;
 }