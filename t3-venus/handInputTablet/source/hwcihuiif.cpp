// hwcihuiif.cpp: implementation of the CHWCiHuiIF class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 

#include "hwcihuiif.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define  CIHUI_FILE_PAHT    "WINPY.TXT"        //"cihui2.txt"

#define  CIHUI_SPLITE_CHAR  " "

bool _splite(CString strSrc, CString strSplite,CStringArray& arDes)
{
	arDes.RemoveAll();//��ʼ��
	while(strSrc.GetLength()>0)
	{
		int   pos   =   strSrc.Find(strSplite,0);//��λ�ָ��
		CString   strLeft;
		
		if(pos!=-1)
		{
			//��λ�ɹ�
			strLeft   =   strSrc.Left(pos);//ǰ����ַ���Ϊ�µķָԪ
			arDes.Add(strLeft);
			strSrc   =   strSrc.Right(strSrc.GetLength()-pos-strSplite.GetLength());//ָ���µķָ����   
			
			if(strSrc.IsEmpty())
			{
				//����ѿ�
				arDes.Add(strSrc);//ʣ�µ��ַ���Ϊ�ָԪ
				break;
			}
		}
		else
		{
			//��λ���ɹ�
			strLeft   =   strSrc;//��ԭ�ַ�����Ϊ�ָԪ��Ŀ������
			arDes.Add(strLeft);
			strSrc.Empty();//���ԭ�ַ���
		}
	}
	
	return   arDes.GetSize() > 1; //����ָԪ��������1����Ϊ�����ɹ�   
}

CHWCiHuiIF*    CHWCiHuiIF::s_pcInstance   = NULL;

CHWCiHuiIF::CHWCiHuiIF():m_vcNumb()
{
	LoadData();


    //�����IP�ؼ���ֱ����ʾ0-9��dot��������
    CString strText = ""; 
    
    for ( int i = 0; i< 10; i ++ )
    {
        strText.Format("%d", i);
        m_vcNumb.push_back( strText );
   } 
}

CHWCiHuiIF::~CHWCiHuiIF()
{

}


CHWCiHuiIF* CHWCiHuiIF::Instance()
{
	if ( NULL == s_pcInstance ) 
	{
		s_pcInstance = new CHWCiHuiIF();
	}
	
	return s_pcInstance;
}

VOID CHWCiHuiIF::Destroy()
{
	if ( NULL != s_pcInstance )
	{
		delete s_pcInstance;
		s_pcInstance = NULL;
	}
}


BOOL CHWCiHuiIF::LoadData()
{
 

	BOOL bRet = FALSE;

	m_mapDict.clear();
	
	CString strPath = GetModulePath() +  CIHUI_FILE_PAHT;

	CStdioFile file;
	
	bRet = file.Open( strPath, CFile::modeRead, NULL );

	if ( !bRet )
	{
		return FALSE;
	}

	CString strLineText = "";

	while (  file.ReadString( strLineText ) )
	{
		ParseString( strLineText );
		strLineText = "";	
	}

	file.Close();

	return TRUE;
}
 




CString CHWCiHuiIF::GetModulePath()
{
	TCHAR buf[MAX_PATH] = {'\0'};
	CString strDir, strTemp;
	
	::GetModuleFileName( NULL, buf, MAX_PATH);
	strTemp = buf;
	strDir = strTemp.Left( strTemp.ReverseFind('\\') + 1 );

	return strDir;
}


BOOL CHWCiHuiIF::GetCiHui( const CString strKey, std::vector<CString>& vectResult )
{ 
    //��������֣�������� 0-9������
   // CString strNum = strKey.SpanIncluding("0123456789"); 
    CString strNonNum = strKey.SpanExcluding( "0123456789" );
    if ( !strKey.IsEmpty() &&  strNonNum.IsEmpty() )
    {
        //�����IP�ؼ���ֱ����ʾ0-9��dot��������
        vectResult = m_vcNumb;        
        return TRUE;
    }


	std::map<CString, std::vector<CString> >::const_iterator iter = m_mapDict.find( strKey );
	
	if ( iter != m_mapDict.end() )
	{
		vectResult  = m_mapDict[ strKey ]; // iter->second  	 
	}
	else
	{
		return FALSE;
	}

    

	return TRUE;
}



/*
������IMEGEN.EXE���ɵĵ�ƴ������(�ʻ�Ƚ�ȫ)
�򵥷�������:��ȡÿһ��, ֻ�е�һ���͵ڶ������Ǻ��ֵĲż��뵽����ʿ�m_mapDict��
*/
BOOL CHWCiHuiIF::ParseString( const CString& strText )
{
	CString strTmp    = "";
	CString strSubTmp = "";
	CString strSubTmpValue = "";
	
	if ( strText.GetLength() < 4 )
	{
		return FALSE;
	}

	if ( (strText.GetAt(0) & 0x80 ) &&  ( strText.GetAt(2) & 0x80 ) )
	{
		//����
		strTmp = strText.Left(4);
		strSubTmp = strTmp.Left(2);
		strSubTmpValue = strTmp.Right( 2 );	
		AddDict( strSubTmp, strSubTmpValue );
	}
	
	return TRUE;
	
}




BOOL CHWCiHuiIF::AddDict( const CString& strKey, const CString& strValue )
{
	if ( strKey.GetLength() <= 0 || strValue.GetLength() <= 0 )
	{
		return FALSE;
	}

	//����MAP 	std::map<CString, std::vector<CString> > m_mapDict;

	bool bRet = FALSE;

	std::map<CString, std::vector<CString> >::const_iterator iter = m_mapDict.find( strKey );

	if ( iter != m_mapDict.end() )
	{
		 //std::vector<CString> vect = static_cast<std::vector<CString>>(*iter);
		 
		 std::vector<CString> vect  = m_mapDict[ strKey ];
 
		 //�ж��ֿ��Ƿ��Ѿ�����

		 for ( int i = 0; i< vect.size(); ++ i)
		 {
			 if ( vect[i] == strValue )
			 {
				 return TRUE;
			 }
		 }

		 vect.push_back( strValue );

		 m_mapDict[strKey] = vect;		 
	}
	else
	{
		std::vector<CString> vect;
		
		vect.push_back( strValue );
		
		 m_mapDict[strKey] = vect;	
	}

	return TRUE;

}
 
 