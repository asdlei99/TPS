/*****************************************************************************
ģ����      : CUmcwebCommon
�ļ���      : umcwebcommon.h
����ļ�    : 
�ļ�ʵ�ֹ���: �ṩ����������װ
����        : �컪��
�汾        : V1.0  Copyright(C) 2014-2015 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2015/01/06     1.0         �컪��      ����
******************************************************************************/
#ifndef UMCWEBCOMMON_H 
#define UMCWEBCOMMON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcwebCommon  
{
public:
	CUmcwebCommon();
	virtual ~CUmcwebCommon();

	//����Ƶ��ʽ(TUmsVidFormat) - ��ʽ����(std::string) ת��
	static void ChangeMainVideoToName( const TUmsVidFormat& tTpMainVideoRes, std::string& strFormatName );

	//����Ƶ��ʽ(TUmsVidFormat) - ��ʽ����(std::string) ת��
	static void ChangeMinorVideoToName( const TUmsVidFormat& tTpMinorVideoRes, std::string& strFormatName );

	//��Ƶ��ʽ(EmTpAudioFormat) - ��ʽ����(std::string) ת��
	static void ChangeAudioFormatToName( const EmTpAudioFormat emTpAudioFormat, std::string& strFormatName );

	//string - time_t ת��(�ַ�����ʽ�� 2014 - 12 - 10  08 : 56)
	static void ChangeStringToTime( const std::string& strTime, time_t& timeData );
	static void ChangeTimeToString( const time_t& timeData, std::string& strTime );
};

#endif