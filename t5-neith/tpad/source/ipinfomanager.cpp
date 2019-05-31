// IPInfoManager.cpp: implementation of the CIPInfoManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "cms.h"
#include "IPInfoManager.h"
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define  DUMPFILE    _T("c:\\tpadfile\\net.txt") 
#define  DUMPPATH    _T("c:\\tpadfile")
#define  DUMP_FILE_CMD  ("C:\\Windows\\System32\\netsh interface ip show config >c:\\tpadfile\\net.txt")
#define  BAT_FILE      _T("dumpFile.bat")
#define  EXEFILE     "c:\\WINDOWS\\system32\\netsh.exe"
#define  KEYWORD_BEGIN      "�ӿ� \""//"\""  
#define  KEYWORD_END        "\" ������"
#define  DELETEWORD  "Loopback Pseudo-Interface 1"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL IsFileExist(LPCTSTR lpszFilePath)
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = CreateFile( lpszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
		);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		bExist = TRUE;
	}

	return bExist;
}

CIPInfoManager::CIPInfoManager()
{   
	m_strDumpFile = _T("");
	m_strBatFile  = _T("");
	ExistBatFile(); 
}

CIPInfoManager::~CIPInfoManager()
{   
	
}


int CIPInfoManager::GetAllLinker(vector<CString> &v_strLinker)
{    
    v_strLinker.clear();
// 	CString temp ;	
// 	temp = GetAppPath() + "dumpFile.bat";	//"netsh interface ip show config >c:\\net.txt";
	if ( ExistBatFile() == FALSE)
	{   
		OspPrintf(1,0,"\n[CIPInfoManager::GetAllLinker]����bat�ļ�ʧ��\n");
		return 0;
	}

    //�������򴴽�
    BOOL bExist = ComInterface->ExistDir( DUMPPATH );	
    if ( !bExist )
    {
        ComInterface->CreateDir( DUMPPATH );
	}

	if ( IsFileExist( DUMPFILE ) )
	{
		CFile::Remove(DUMPFILE);
	}

	//BOOL bRe = WinExecAndWait(m_strBatFile.GetBuffer(m_strBatFile.GetLength()),NULL ); 
    BOOL bRe = WinExecAndWait( (LPCTSTR)m_strBatFile, NULL ); 
    //BOOL bRe = WinExecAndWait( NULL, (LPTSTR)(LPCTSTR)m_strBatFile ); 
	if (!bRe)
	{   
		//AfxMessageBox("��ȡ����ʧ�ܣ�����������");
		return 0;
	}
	//Sleep(100);//������رպ�5s���ٴδ�ʱ��ȡ�������� 2010-12-17 
	CFile cfNetfile;
	if (cfNetfile.Open(DUMPFILE,CFile::modeRead))
	{
		DWORD dwLen = cfNetfile.GetLength();
		char buf[32767] ={0};
		DWORD dwCurLen = 0;
		while (dwCurLen < dwLen)
		{
			dwCurLen += cfNetfile.Read(buf,sizeof(buf));
			char* index = NULL;
			index = strstr(buf,KEYWORD_BEGIN);
			while (index != NULL)
			{   
				char * tem = NULL;
				int t  = (index-buf);
				tem = strstr/*strchr*/(buf+t+strlen(KEYWORD_BEGIN),KEYWORD_END);
				
				if (tem == NULL)
				{
					break;
				} 

				char linker[100] ={0}; 
				_snprintf(linker,tem-index-strlen(KEYWORD_BEGIN) ,"%s",buf+(index-buf+strlen(KEYWORD_BEGIN))); 
				CString ee(linker);
				//OutputDebugString("\n" + ee +"\n");
				if (ee != DELETEWORD)
				{
					v_strLinker.push_back(ee); 
				}
							 
				//index = strstr(buf+(tem-buf)+1,KEYWORD);
				index = strstr(buf+(tem-buf)+sizeof(KEYWORD_END),KEYWORD_BEGIN);
			}
			
		} 
		cfNetfile.Close();
	}
	

	return v_strLinker.size();
}



CString CIPInfoManager::GetAppPath()
{
	DWORD dwSize;
	CString strAppPath;
	CString strResult;
	int iIndex;
	dwSize=::GetModuleFileName(NULL,strAppPath.GetBufferSetLength(MAX_PATH),MAX_PATH);
	if (dwSize<0 || dwSize>MAX_PATH)
	{
		strAppPath="";
		return strAppPath;
	}
	
    iIndex=strAppPath.ReverseFind('\\') ;
	
    strAppPath=strAppPath.Left(iIndex+1);
	return strAppPath;
}

BOOL CIPInfoManager::ExistBatFile()
{   
	BOOL bRe = FALSE;
	CString strAppPath = GetAppPath();
	m_strBatFile = strAppPath + BAT_FILE ;  
	bRe = IsFileExist((LPCTSTR)m_strBatFile);
    CString strMsgErr;
	strMsgErr = m_strBatFile + _T("����");
	if (!bRe)
	{
		CFile file;
		if(file.Open(m_strBatFile,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
		{  
			file.Write(DUMP_FILE_CMD,strlen(DUMP_FILE_CMD));
			file.Close();
			bRe = TRUE;
			strMsgErr = _T("����") + m_strBatFile + _T("�ɹ�");
		}
		else
		{
			m_strBatFile.Empty();
			strMsgErr = _T("����") + m_strBatFile + _T("ʧ��");
		}
	}
	
	//OutputDebugString("\n[CIPInfoManager::ExistBatFile] " + strMsgErr);
	
	return bRe;
}


BOOL CIPInfoManager::WinExecAndWait(LPCTSTR lpExeName, LPTSTR lpCmdLine)
{  
	BOOL bRe = FALSE;
	PROCESS_INFORMATION pi;
	
	STARTUPINFO si;
	
	memset(&si,0,sizeof(si));
	
	si.cb=sizeof(si);
	
	si.wShowWindow=SW_HIDE;
	
	si.dwFlags=STARTF_USESHOWWINDOW;	
	
	bRe = CreateProcess( lpExeName, lpCmdLine,NULL, FALSE,NULL,NULL,NULL,NULL,&si,&pi);
	if ( bRe )
	{
        CloseHandle( pi.hThread );// �ر��ӽ��̵����߳̾��
        WaitForSingleObject(pi.hProcess,INFINITE);      
        CloseHandle( pi.hProcess );// �ر��ӽ��̾��
	}

	return bRe;
} 


//��ȡ��ǰ�����ӿ�����, Ŀǰ���ý��õ������ȷ��ֻ��һ����������
CString CIPInfoManager::GetCurNetWorkName( CString& strWifiNetName )
{
	CString strNetName = _T("��������");
    CString strWifiName = _T("������������");

    
// 	LANGID LangID = GetSystemDefaultLangID(); 
// 	LangID = GetUserDefaultLangID();
// 	if( PRIMARYLANGID(LangID) == LANG_CHINESE /*&& SUBLANGID(LangID)==SUBLANG_CHINESE_SIMPLIFIED*/ )   
// 	{ 
// 		strNetName = "��������"; 
// 	}
// 	else //if( PRIMARYLANGID(LangID) == LANG_ENGLISH )   
// 	{ 
// 		strNetName = "Local Area Connection";
// 	} 
	/* ������Ӣ�İ汾�������������ƣ��Ѿ�����Ҫ  -2013.8.28
	HKEY hKey;
	LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\Nls\\Language", REG_OPTION_NON_VOLATILE, KEY_READ, &hKey);
	if (lRes ==  ERROR_SUCCESS)
	{
		char achLangId[32] = {0};
		DWORD dwTypeLen  = sizeof(achLangId);
		if ( RegQueryValueEx(hKey, "InstallLanguage", 0, NULL, (u8*)achLangId, &dwTypeLen) == ERROR_SUCCESS )
		{
			if ( strcmp( achLangId, "0804" ) == 0 )
			{
				strNetName = "��������";
                strWifiName = "������������";
			}
			else
			{
				strNetName = "Local Area Connection";
                strWifiName = "Wi-Fi";
			}
		}
        RegCloseKey( hKey );
	}*/

    //windows8
    if ( ComInterface->IsSysWin8() )
    {
        strNetName = _T("��̫��");
        strWifiName = _T("WLAN");       
    }

	//ö�ٵ�ǰPC��������������Ϣ
	vector<CString> v_strLinker;
	GetAllLinker( v_strLinker );

    vector<CString>::iterator itr = v_strLinker.begin();

	CString strText =_T("");

    //��ȡ������������ 
    BOOL bFind = FALSE;
    for(; itr != v_strLinker.end(); itr++ )
    {
        strText = *itr;
        strText.TrimLeft();
        strText.TrimRight();
        
        int nPos = strText.Find( strWifiName );
        if ( nPos != -1 )
        {
            strWifiNetName = strText;
            bFind = TRUE;
            break;
        }
    }
    if ( !bFind )
    {
        strWifiNetName = strWifiName;
    }

	//��ȡ������������
    for( itr = v_strLinker.begin(); itr != v_strLinker.end(); itr++ )
    {
		strText = *itr;
		strText.TrimLeft();
		strText.TrimRight();

		int nPos = strText.Find( strNetName );
		if ( nPos != -1 )
		{
			return strText;
		}
    }
	
	strText = strNetName;

	return strText;
}