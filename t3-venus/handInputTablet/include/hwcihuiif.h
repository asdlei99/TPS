// hwcihuiif.h: interface for the CHWCiHuiIF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HWCIHUIIF_H__DA0531D8_345F_4167_9EDA_E5E1D91A5CEA__INCLUDED_)
#define AFX_HWCIHUIIF_H__DA0531D8_345F_4167_9EDA_E5E1D91A5CEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>

class CHWCiHuiIF  
{
public:	
	static CHWCiHuiIF*	Instance();
	static  VOID Destroy();
	virtual ~CHWCiHuiIF();

	BOOL GetCiHui( const CString strKey,  std::vector<CString>& vectResult );


private:
	CHWCiHuiIF();

	BOOL LoadData();

	CString GetModulePath();

	/*
	������IMEGEN.EXE���ɵĵ�ƴ������(�ʻ�Ƚ�ȫ)
	�򵥷�������:��ȡÿһ��, ֻ�е�һ���͵ڶ������Ǻ��ֵĲż��뵽����ʿ�m_mapDict��
	*/
	BOOL ParseString( const CString& strText );	

	
	BOOL AddDict( const CString& strKey, const CString& strValue );

private:
	static CHWCiHuiIF      *s_pcInstance; 
	std::map<CString, std::vector<CString> > m_mapDict;
    std::vector<CString>   m_vcNumb;
};

#endif // !defined(AFX_HWCIHUIIF_H__DA0531D8_345F_4167_9EDA_E5E1D91A5CEA__INCLUDED_)


 