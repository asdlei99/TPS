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
	arDes.RemoveAll();//初始化
	while(strSrc.GetLength()>0)
	{
		int   pos   =   strSrc.Find(strSplite,0);//定位分割符
		CString   strLeft;
		
		if(pos!=-1)
		{
			//定位成功
			strLeft   =   strSrc.Left(pos);//前面的字符串为新的分割单元
			arDes.Add(strLeft);
			strSrc   =   strSrc.Right(strSrc.GetLength()-pos-strSplite.GetLength());//指定新的分割对象   
			
			if(strSrc.IsEmpty())
			{
				//如果已空
				arDes.Add(strSrc);//剩下的字符串为分割单元
				break;
			}
		}
		else
		{
			//定位不成功
			strLeft   =   strSrc;//将原字符串作为分割单元入目标数组
			arDes.Add(strLeft);
			strSrc.Empty();//清空原字符串
		}
	}
	
	return   arDes.GetSize() > 1; //如果分割单元数量大于1定义为操作成功   
}

CHWCiHuiIF*    CHWCiHuiIF::s_pcInstance   = NULL;

CHWCiHuiIF::CHWCiHuiIF():m_vcNumb()
{
	LoadData();


    //如果是IP控件，直接显示0-9和dot供其输入
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
    //如何是数字，则联想出 0-9的数字
   // CString strNum = strKey.SpanIncluding("0123456789"); 
    CString strNonNum = strKey.SpanExcluding( "0123456789" );
    if ( !strKey.IsEmpty() &&  strNonNum.IsEmpty() )
    {
        //如果是IP控件，直接显示0-9和dot供其输入
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
分析有IMEGEN.EXE生成的的拼音词组(词汇比较全)
简单分析法则:读取每一行, 只有第一个和第二个都是汉字的才加入到联想词库m_mapDict中
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
		//汉字
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

	//查找MAP 	std::map<CString, std::vector<CString> > m_mapDict;

	bool bRet = FALSE;

	std::map<CString, std::vector<CString> >::const_iterator iter = m_mapDict.find( strKey );

	if ( iter != m_mapDict.end() )
	{
		 //std::vector<CString> vect = static_cast<std::vector<CString>>(*iter);
		 
		 std::vector<CString> vect  = m_mapDict[ strKey ];
 
		 //判断字库是否已经存在

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
 
 