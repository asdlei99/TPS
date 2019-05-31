/** @defgroup cnc会场控制的相关接口 
 *  @version V1.1.4
 *  @author  dyy
 *  @date    2014.12.24
 */

#include "stdafx.h"
#include "commoninterface.h"



BOOL32 CCommonInterface::IsLocalCnsQuite()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->IsLocalCnsQuite();
}


BOOL32 CCommonInterface::IsLocalCnsMute()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->IsLocalCnsMute();
}


u16 CCommonInterface::SetLocalCnsQuite( BOOL bQuite )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->SetCnsQutie( bQuite );
}

BOOL32 CCommonInterface::IsLocalCnsPanCam()
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->IsLocalCnsPanCam();
}


u16 CCommonInterface::SetLocalCnsPanCam(u8 wCamId ,BOOL bPanCam/* = TRUE*/)
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfigCtrl->SetLocalCnsPanCam( wCamId,bPanCam );
}

u16 CCommonInterface::SetLocalCnsMute( BOOL bMute )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->SetCnsMute( bMute );
}

u16 CCommonInterface::AdjustInputVol( u8 byVolume )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->AdjustInputVol( byVolume );
}


u16 CCommonInterface::AdjustOutputVol( u8 byVolume )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->AdjustOutputVol( byVolume );
}

u8 CCommonInterface::GetInputVol()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->GetInputVol();
}

u8 CCommonInterface::GetOutputVol()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->GetOutputVol();
}

u16 CCommonInterface::GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tDualSrcinfo = m_pCnsConfigCtrl->GetDualSrcInfo();
	return NO_ERROR;
}

u16 CCommonInterface::SelDualInputPort( EmVgaType emType )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SelDualInputPort( emType );
}

u16 CCommonInterface::SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetDualPortInfo( tVgaInfo, bDefault );
}


u16 CCommonInterface::GetPanCamList( TPanCamInfo& tPanCamInfo )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tPanCamInfo = m_pCnsConfigCtrl->GetPanCamInfo();
	return NO_ERROR;
}



u16 CCommonInterface::SetPanCamSelectIndex( u8 wIndex )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetPanCamSelectIndex( wIndex );
}



u16 CCommonInterface::SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetMainVideoPort( emTPMtVideoPort, wID );
}


u16 CCommonInterface::GetMainVideoPort( map<u16, EmTPMtVideoPort>& mapEmTPMtVideoPort )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	mapEmTPMtVideoPort = m_pCnsConfigCtrl->GetMainVideoPort();
	return NO_ERROR;
}

u16 CCommonInterface::GetVedioInfo( TTPVideoInfoTool& tTPVideoInfoTool )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tTPVideoInfoTool = m_pCnsConfigCtrl->GetVedioInfo();
	return NO_ERROR;
}

u16 CCommonInterface::SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetPanCamPT( emDirection, emCnAction );
}

u16 CCommonInterface::SetPanCamView( EmZoom emZoom, EmCnAction emCnAction )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetPanCamView( emZoom, emCnAction );
}

u16 CCommonInterface::SetPanCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetPanCamLight( emPanCamBright, emCnAction );
}

u16 CCommonInterface::SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetPanCamFocus( emFocus, emCnAction );
}

u16 CCommonInterface::SetPanCamAotoFocus()
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetPanCamAotoFocus();
}

u16 CCommonInterface::SavePanCamPreset(  u8 wID )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SavePanCamPreset( wID );
}

u16 CCommonInterface::ImpelPanCamPreset(  u8 wID ) 
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->ImpelPanCamPreset( wID );
}

u16 CCommonInterface::DeletePanCamPreset(  u8 wID ) 
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->DeletePanCamPreset( wID );
}

u16 CCommonInterface::SavePanCamPresetName( u8 wID ,TPanCamName tPanCamName)
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SavePanCamPresetName( wID , tPanCamName);
}
