/** @defgroup 中控接口
 *  @version V1.1.4
 *  @author  dyy
 *  @date    2015-4-1
 */

#include "stdafx.h"
#include "commoninterface.h"




u16 CCommonInterface::SetSysPower( EmSchPower emPower )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetSysPower( emPower );
}

u16 CCommonInterface::SetSysAllLight( EmSchLight emLight )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetSysAllLight( emLight );
}

u16 CCommonInterface::SetSysMainLight( EmSchMidLight emLight )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetMainLight( emLight );
}

//用于补光灯
u16 CCommonInterface::SetSysAuxiLight( EmSchScrLight emLight )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetAuxiLight( emLight );
}

u16 CCommonInterface::SelectTVMonitor( u8 byIndex )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SelectTV( byIndex );
}

u16 CCommonInterface::SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetTVPowerMode( byIndex, emMode );
}


u16 CCommonInterface::SetTVAudVisMode( EmTVAudVisMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetTVAudVisMode( emMode );
}

u16 CCommonInterface::SetTVDisMode( EmTVDisplayMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetTVDisMode( emMode );
}

u16 CCommonInterface::SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetTVInpSelect( byIndex, emSelect );
}

TCentreTVCfg* CCommonInterface::GetCentreTVCfg()
{
	if ( NULL == m_pCenterCtrl )
	{
		return NULL;
	}

	return m_pCenterCtrl->GetCentreTVCfg();
}

u16 CCommonInterface::SetDCamSelectIndex( u8 byIndex )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }

    return m_pCenterCtrl->SetDCamSelectIndex( byIndex );
}

u16 CCommonInterface::SetDCamPower( EmDCamPower emPower )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDCamPower( emPower );
}

u16 CCommonInterface::SetDCamAFMode( EmDCamAFMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDCamAFMode( emMode );
}

u16 CCommonInterface::SetDCamWBMode( EmDCamWBMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDCamWBMode( emMode );
}

u16 CCommonInterface::SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDCamZoom( emZoom, emAction );
}

u16 CCommonInterface::SetDCamPreset( EmDCamRecallNum emNum )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDCamPreset( (EmDCamPresetNum)emNum );
}

u16 CCommonInterface::SetDCamRecall( EmDCamRecallNum emNum )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDCamRecall( emNum );
}

u16 CCommonInterface::SetDocSnapShot()
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetDocSnapShot();
}
// u16 CCommonInterface::SetAirPower( EmCentreACPower emPower )
// {
// 	if ( NULL == m_pCenterCtrl )
// 	{
// 		return ERR_CMS;
// 	}
// 	return m_pCenterCtrl->SetAirPower( emPower );
// }

u16 CCommonInterface::SetACMode( EmCentreACMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}
	return m_pCenterCtrl->SetACMode( emMode );
}

u16 CCommonInterface::SetACTemp( u8 byTemp )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetACTemp( byTemp );
}

u16 CCommonInterface::SetACAirVol( EmCentreACAirVol emAirVol )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetACAirVol( emAirVol );
}

u16 CCommonInterface::SelectAirMonitor( u8 byIndex )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SelectAir( byIndex );
}

u16 CCommonInterface::GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )
{
	if ( NULL == m_pCenterCtrl )
	{
		return NULL;
	}

	m_pCenterCtrl->GetCentreACCfg( vecTCentreACCfg );
	return NO_ERROR;
}

u16 CCommonInterface::SetACPowerMode( u8 byIndex, EmCentreACPower emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetACPowerMode( byIndex, emMode );
}

u16 CCommonInterface::SetApplyToAll( u8 byIndex, BOOL* atbIsCtrl )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetApplyToAll( byIndex, &atbIsCtrl );
}

u16 CCommonInterface::GetApplyToAllInfo( BOOL** pIsCtrl )
{
	*pIsCtrl = m_pCenterCtrl->GetApplyToAllInfo();
	return NO_ERROR;
}

u16 CCommonInterface::SetCurtainState( BOOL* bIsCtrl, EmCurAction emCurAction )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}

	return m_pCenterCtrl->SetCurtainState( &bIsCtrl, emCurAction );
}

u16 CCommonInterface::GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName )
{
	if ( NULL == m_pCenterCtrl )
	{
		return NULL;
	}

	m_pCenterCtrl->GetCentreCurName( vecTCentreCurName );
	return NO_ERROR;
}


u16 CCommonInterface::GetCentreCurInfor( TCentreCurInfo &tCentreCurInfo )
{
	if ( NULL == m_pCenterCtrl )
	{
		return NULL;
	}

	m_pCenterCtrl->GetCentreCurInfor( tCentreCurInfo );
	return NO_ERROR;
}

u16 CCommonInterface::GetCentreSchCfg( TCentreSchCfg &tCentreSchCfg )
{
	if ( NULL == m_pCenterCtrl )
	{
		return NULL;
	}

	m_pCenterCtrl->GetCentreSchCfg( tCentreSchCfg );
	return NO_ERROR;
}

u16 CCommonInterface::GetDCamStateMap( map<u8, TCentreDCamCfg> &mapDCamCfg )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    m_pCenterCtrl->GetDCamStateMap( mapDCamCfg );
    return NO_ERROR;
}

u16 CCommonInterface::GetDCamState(  TCentreDCamCfg &tCentreDCamCfg, u8 byIndex )
{
	if ( NULL == m_pCenterCtrl )
	{
		return NULL;
	}

	m_pCenterCtrl->GetDCamState( tCentreDCamCfg, byIndex);
	return NO_ERROR;
}

//矩阵
BOOL CCommonInterface::GetMatrixOnlineState()
{
    if ( NULL == m_pCenterCtrl )
    {
        return FALSE;
    }

    return m_pCenterCtrl->GetMatrixOnlineState();
}

TTPMatrixSceneInfo* CCommonInterface::GetMatrixScneInfo()
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    return m_pCenterCtrl->GetMatrixScneInfo();
}

u16 CCommonInterface::GetCurMatrixInfo(TTPCurMatrixInfo &tTPCurMatrixInfo)
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    tTPCurMatrixInfo = m_pCenterCtrl->GetCurMatrixInfo();
    return NO_ERROR;
}

u16 CCommonInterface::GetMatrixConfig(TTPMatrixConfig &tTPMatrixConfig)
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    tTPMatrixConfig = m_pCenterCtrl->GetMatrixConfig();
    return NO_ERROR;
}

u16 CCommonInterface::SetMatrixInOutCmd( u32 dwIn, u32 dwOut )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    return m_pCenterCtrl->SetMatrixInOutCmd(dwIn, dwOut);
}

u16 CCommonInterface::SaveMatrixScenceCmd( u32 dwIndex, s8* achName )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    return m_pCenterCtrl->SaveMatrixScenceCmd( dwIndex, achName );
}

u16 CCommonInterface::ReNameMatrixScenceCmd( u32 dwIndex, s8* achName )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    return m_pCenterCtrl->ReNameMatrixScenceCmd( dwIndex, achName );
}

u16 CCommonInterface::DeleteMatrixScenceCmd( u32 dwIndex )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    return m_pCenterCtrl->DeleteMatrixScenceCmd( dwIndex );
}

u16 CCommonInterface::ApplyMatrixScenceCmd( u32 dwIndex )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }

    return m_pCenterCtrl->ApplyMatrixScenceCmd( dwIndex );
}