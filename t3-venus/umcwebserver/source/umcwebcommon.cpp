#include "umcglodef.h"

CUmcwebCommon::CUmcwebCommon()
{
}

CUmcwebCommon::~CUmcwebCommon()
{
}

//主视频格式(TUmsVidFormat) - 格式名称(std::string) 转换
void CUmcwebCommon::ChangeMainVideoToName( const TUmsVidFormat& tTpMainVideoRes, std::string& strFormatName )
{
	strFormatName = "";
	
	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "HP 1080P@50/60fps";
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{	
		strFormatName = "HP 1080P@25/30fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "HP 720P@50/60fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "HP 720P@25/30fps";
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 1080P@50/60fps";
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 1080P@25/30fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 720P@50/60fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 720P@25/30fps";
	}
	
	if( (emTPV4CIF == tTpMainVideoRes.m_emRes) && (25 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 4CIF@25fps";
	}
}

//辅视频格式(TUmsVidFormat) - 格式名称(std::string) 转换
void CUmcwebCommon::ChangeMinorVideoToName( const TUmsVidFormat& tTpMinorVideoRes, std::string& strFormatName )
{
	strFormatName = "";
	
	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "HP 1080P@50/60fps";
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{	
		strFormatName = "HP 1080P@25/30fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "HP 720P@50/60fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "HP 720P@25/30fps";
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 1080P@50/60fps";
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 1080P@25/30fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 720P@50/60fps";
	}
	
	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 720P@25/30fps";
	}
	
	if( (emTPV4CIF == tTpMinorVideoRes.m_emRes) && (25 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP 4CIF@25fps";
	}
	
	if( (emTPVGA1600x1200 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP UXGA@60fps";
	}
	
	if( (emTPVGA1280x800 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP WXGA@30fps";
	}
	
	if( (emTPVGA1280x1024 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP SXGA@30fps";
	}
	
	if( (emTPVGA1280x800 == tTpMinorVideoRes.m_emRes) && (5 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP WXGA@5fps";
	}
	
	if( (emTPVGA1280x1024 == tTpMinorVideoRes.m_emRes) && (5 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP SXGA@5fps";
	}
	
	if( (emTPVGA1024x768 == tTpMinorVideoRes.m_emRes) && (5 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		strFormatName = "BP XGA@5fps";
	}
}

//音频格式(EmTpAudioFormat) - 格式名称(std::string) 转换
void CUmcwebCommon::ChangeAudioFormatToName( const EmTpAudioFormat emTpAudioFormat, std::string& strFormatName )
{
	strFormatName = "";
	
	if ( emTPAMpegAACLD == emTpAudioFormat )
	{
		strFormatName = "MPEG4 AAC-LD单声道";
	} 
	else if ( emTPAG711a == emTpAudioFormat )
	{
		strFormatName = "G.711A";
	}
	else if ( emTPAG711u == emTpAudioFormat )
	{
		strFormatName = "G.711U";
	}
	else if ( emTPAG719 == emTpAudioFormat )
	{
		strFormatName = "G.719";
	}
	else if ( emTPAG7221 == emTpAudioFormat )
	{
		strFormatName = "G.722.1 Annex C Polycom Siren14";
	}
	else if ( emTPAMP3 == emTpAudioFormat )
	{
		strFormatName = "MP3";
	}
	else if ( emTPAMpegAACLC == emTpAudioFormat )
	{
		strFormatName = "MPEG4 AAC-LC单声道";
	}
}

//string - time_t 转换(字符串格式： 2014 - 12 - 10  08 : 56)
void CUmcwebCommon::ChangeStringToTime( const std::string& strTime, time_t& timeData )
{
	struct tm tm1;
	sscanf( strTime.c_str(), "%d - %d - %d  %d : %d", &(tm1.tm_year), &(tm1.tm_mon), &(tm1.tm_mday), &(tm1.tm_hour), &(tm1.tm_min));
	
	tm1.tm_year -= 1900;
	tm1.tm_mon--;
	tm1.tm_isdst = -1;
	timeData = mktime(&tm1);
}

void CUmcwebCommon::ChangeTimeToString( const time_t& timeData, std::string& strTime )
{
	if ( 0 == timeData )
	{
		//即时会议
		strTime = "0";
		return;
	}

	char chTmp[50] = {0};
	struct tm *p;
	p = localtime(&timeData);
	p->tm_year = p->tm_year + 1900;
	p->tm_mon = p->tm_mon + 1;

	sprintf( chTmp, "%04d - %02d - %02d  %02d : %02d", p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min );
	strTime = chTmp;
}