/*****************************************************************************
ģ����      : CUmcwebCommon������
�ļ���      : umcwebcommon.h
����ļ�    : 
�ļ�ʵ�ֹ���: �ṩ����������װ
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/24      1.0         ����ӡ      ����
******************************************************************************/
#ifndef UMSWEBCOMMON_H 
#define UMSWEBCOMMON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
class CUmcwebCommon  
{
public:
	CUmcwebCommon();
	virtual ~CUmcwebCommon();

	/*=============================================================================
    �� �� ��:MapValueCompare
    ��    ��:�º������ж�map���Ƿ���ں�value��ȵ�ֵ
    ��    ��: std::pair<u16,CString> paD                           [in]    ���Ƚ�pair����Դ
	��    ��: CString strTarget                                    [in]    �Ƚ��ı�
    ע    ��:��
    �� �� ֵ:bool
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2012/06/20  1.0     ����ӡ    ����
    =============================================================================*/
	static bool MapValueCompare( std::pair<u16,CString> paData, CString strTarget);

	/*=============================================================================
    �� �� ��:SetImgForTransEdit
    ��    ��:�ṩ�������ñ༭��CTransparentEditͼƬ�ӿ�
    ��    ��:CTransparentEdit *pEdit                          [in]    ������ͼƬ�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static void SetImgForTransEdit( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );


	/*=============================================================================
    �� �� ��:SetImgForTransEditTimeL
    ��    ��:�ṩ��������ʱ��༭�� ����� �м� ���Ҳ��edit
    ��    ��:CTransparentEdit *pEdit                          [in]    ������ͼƬ�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/09/12  1.0     �����    ����
    =============================================================================*/
    static void SetImgForTransEditTimeLft( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );
	static void SetImgForTransEditTimeMdl( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );
	static void SetImgForTransEditTimeRgt( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );


	/*=============================================================================
    �� �� ��:SetImgForTransEdit
    ��    ��:�ṩ�������ò�ѯ�༭��CTransparentEditͼƬ�ӿ�
    ��    ��:CTransparentEdit *pEdit                          [in]    ������ͼƬ�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static void SetImgForTransSearchEdit( CTransparentEdit *pEdit, BOOL bIsSearchEdit = TRUE, s32 nFontSize = 11, const CString& strText = "�������ַ�������", s32 nLimitLen = 31 );

	/*=============================================================================
    �� �� ��:SetImgForTransIpEdit
    ��    ��:�ṩ��������CTransparentIpEditͼƬ�ӿ�
    ��    ��:CTransparentIpEdit *pEdit                          [in]    ������ͼƬ�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static void SetImgForTransIpEdit( CTransparentIpEdit *pIpEdit );

	/*=============================================================================
    �� �� ��:SetImgForLetter
    ��    ��:�ṩ��������CLetterIndexͼƬ�ӿ�
    ��    ��:CLetterIndex* pLetterIndexTmp                          [in]    ��������ĸ�����ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static void SetImgForLetter( CLetterIndex* pLetterIndexTmp );

	/*=============================================================================
    �� �� ��:SetTextTransStatic
    ��    ��:�ṩͳһ����Static�ı���ʽ��Style�ӿ�
    ��    ��:CTransparentStatic *pStatic                          [in]    ������Staic�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static void SetTextTransStatic( CTransparentStatic *pStatic, const CString& strText = "", s32 nFontSize = 13, Color color = Color( 46, 55, 76 ) );
	

	/*=============================================================================
    �� �� ��:SetTextTransCheckBtn
    ��    ��:�ṩͳһ����Static�ı���ʽ��Style�ӿ�
    ��    ��:CTransparentCheckButton *pStatic                          [in]    ������CheckBtn�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2013/02/26  1.0     ����ӡ    ����
    =============================================================================*/
	static void SetTextTransCheckBtn( CTransparentCheckButton *pCheckBtn, const CString& strText = "", s32 nFontSize = 13, Color color = Color( 46, 55, 76 ) );
	
	/*=============================================================================
    �� �� ��:SetTextTransRadioBtn
    ��    ��:�ṩͳһ����Static�ı���ʽ��Style�ӿ�
    ��    ��:CTransparentCheckButton *pStatic                          [in]    ������CheckBtn�ؼ�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/14  1.0     ʯ��    ����
    =============================================================================*/
	static void SetTextTransRadioBtn( CTransparentCheckButton *pCheckBtn, const CString& strText = "", s32 nFontSize = 13, Color color = Color( 46, 55, 76 ) );


	/*=============================================================================
    �� �� ��:GetUniqID
    ��    ��:��ȡ����ΨһID
    ��    ��:��
    ע    ��:��
    �� �� ֵ:unsigned int
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/16  1.0     ����ӡ    ����
    =============================================================================*/
	static unsigned int GetUniqID();

	/*=============================================================================
    �� �� ��:IsValidTPStr
    ��    ��:" ;/?:@&=+$,%^"�������ַ������ж�
    ��    ��: const CString& strText                          [in]    �������ı�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2012/05/15  1.0     ����ӡ    ����
    =============================================================================*/
	static bool IsValidTPStr( const CString& strText = "" );

	/*=============================================================================
    �� �� ��:IsAllNumber
    ��    ��:�ж��ִ�ȫ��Ϊ����
    ��    ��: const CString& strText                          [in]    �������ı�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static bool IsAllNumber( const CString& strText = "" );
	static bool IsAllE164Number( const CString& strText = "" );

	/*=============================================================================
    �� �� ��:HZPYMatchList
    ��    ��:��ѯ�����������ƥ����������б���
    ��    ��: const CString& strTextInput                          [in]    ����������ı�
	��    ��: const CString& strTextSrc                            [in]    �������ı�
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static BOOL HZPYMatchList( const CString& strTextInput,  const CString& strTextSrc );

	/*=============================================================================
    �� �� ��:PlusHourBtn SubHourBtn PlusMinBtn SubMinBtn PlusSecBtn SubSecBtn
    ��    ��:���õ��ʱ��Ӽ��Ĺ���������
    ��    ��: CTransparentEdit *pEdit                          [in]    �����ؼ�ָ��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	static void PlusHourBtn( CTransparentEdit *pEdit ); 
	static void SubHourBtn( CTransparentEdit *pEdit ); 
	static void PlusMinBtn( CTransparentEdit *pEdit ); 
	static void SubMinBtn( CTransparentEdit *pEdit ); 
	static void PlusSecBtn( CTransparentEdit *pEdit ); 
	static void SubSecBtn( CTransparentEdit *pEdit ); 

	static void GetResolutionScale( float &fx, float &fy);
	static void ResolutionAdp( long &nx, long &ny);
	static void FontSizeAdp( int &nFontSize );
	static void ResetChildWndSize( HWND hParentWnd );

	/*=============================================================================
    �� �� ��:TimeToTm
    ��    ��:ת��time_tʱ��Ϊtm�ṹ
    ��    ��: struct tm& tmDate                          [in]    time_t��ת��ʱ��
	��    ��: const time_t& timeDate                     [in]    ת�����tmʱ��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2012/08/09  1.0     ����ӡ    ����
    =============================================================================*/
	static void TimeToTm( struct tm& tmDate, const time_t& timeDate );

	/*=============================================================================
    �� �� ��:GetTime
    ��    ��:��dwTimeתΪnHour, nMin, nSec
    ��    ��: u32 dwTime								 [in]    ��ת����ʱ��
	��    ��: int& nHour			                     [out]   ת�����Сʱ
	��    ��: int& nMin				                     [out]   ת����ķ���
	��    ��: int& nSec				                     [out]   ת�������
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    20132/05/23  1.0     ʯ��    ����
    =============================================================================*/
	static void GetTime( u32 dwTime, int& nHour, int& nMin, int& nSec );

};

#endif
