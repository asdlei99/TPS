// uiDataMgr.cpp: implementation of the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "uiDataMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const string g_stcMsgboxDlg = "MsgboxDlg";	//��ʾ������
const string g_strMainFrame = "MainFrame" ; // 	CfgCnsDlg
const string g_strBasicInfoDlg = "BasicInfoDlg"; //������Ϣ����		 
const string g_strCfgFrame = "CfgFrame";        //���ÿ��	
const string g_strCfgAudioPort = "CfgAudioPortDlg";	//���ÿ���е���Ƶ�ӿڽ���
const string g_strCfgAudioDlg = "CfgAudioDlg";		//���ÿ���е���Ƶ���ý���
const string g_strCfgMainAudioDlg = "CfgMainAudioDlg";		//���ÿ���е�����Ƶ���ý���
const string g_strCfgDemonStrationDlg = "CfgDemonStrationDlg";   //���ÿ���е���ʾԴ���ý���
const string g_strCfgAdjustImageDlg = "CfgAdjustImageDlg" ;   //���ÿ���е�ͼ��������ý���
const String g_strRenameOptDlg = "RenameOptDlg";	//����������
const String g_strCfgEqDlg = "CfgEqDlg";	//���ÿ���еľ���������

const string g_strCnsCfg = "CfgCnsFrame";        //CNS����
const string g_strCfgCnsDlg = "CfgCnsDlg";		//���ÿ���е�cns����	
//const string g_strCfgMixDlg = "CfgMixAudioDlg"; //���ÿ���еĻ������ý���
const String g_strCfgServerDlg = "CfgServerDlg";		//���ÿ���еķ���������
const String g_strCfgCallSer = "CfgCallSerDlg";			//�������ý���
const String g_strCfgAdvanceDlg = "CfgAdvanceDlg";			//�߼����ý���

//const string g_strDiagInfoDlg = "DiagInfoDlg";		//��ϲ��Խ���
const string g_strCfgDiagnosticFrame = "CfgDiagnosticFrame";   //��ϲ��Խ���
const string g_strDiagInterfaceDlg = "InterfaceDiagnosticDlg";  //�ӿ���Ͻ���
const string g_strNetDiagnosticDlg = "NetDiagnosticDlg";        //������Ͻ���
const string g_strNetPacketDlg = "NetPacketDlg";                //����ץ������

const string g_strCentCfgFrame = "CentCfgFrame";		//�п���Ϣ����
const string g_strDiagInTestInfo = "DiagTestInDlg";	//������Խ���
const string g_strDiagOutTestInfo = "DiagTestOutDlg";	//������Խ���
const string g_strDiagTestFrame = "DiagTestFrame";	//��ϲ�����ʾ����
const string g_strDiagStatistic = "StatisticOptDlg";	//ͳ�ƽ���
const String g_stcStrCfgNetMngDlg		= "CfgNetMngDlg";			//�������ý���
const String g_stcStrCfgNetSecurityDlg  = "CfgNetSecurityDlg";      //���簲ȫ���ý���
const String g_stcStrNetMngOptDlg		= "NetMngOptDlg";			//���ܲ�������
const String g_stcStrRouteCfgDlg        = "RouteCfgInfoDlg";        //·�����ý���
const String g_StrCameraDlg			= "CameraDlg";				//������ڽ���
const String g_strAddrbookExpDlg = "AddrbookExpDlg";			//��ַ������
const String g_stcStrImpCommonDlg		= "ImpCommonDlg";		//�ϴ������룩ͨ�õ�������  �磺���������������������ؽ���   ���������ͬ  ͨ����������
const String g_stcStrExpCommonDlg		= "ExpCommonDlg";		//���أ�������ͨ�õ�������  �磺�������á�������־����  ���������ͬ  ͨ����������
const String g_strWarningDlg = "WaringDlg";
const String g_strCentAirCondition = "CentCfgAirConditionDlg";	//�пؿյ����ý���
const String g_strCentCameraDlg = "CentCfgCameraDlg";	//�п����������
const String g_strCentLightDlg = "CentCfgLightDlg";		//�пصƹ����
const String g_strCentDisplayDlg = "CentCfgDisplayDlg";	//�пص��ӻ�����
const String g_strCentStatusMesDlg = "CentCfgStatusMesDlg";	//�п�״̬��Ϣ����
const String g_strCentCurtainDlg = "CentCfgCurtainDlg";	//�пش������ý���
const String g_strCentDuoVideo = "CentCfgDuoVideo";	//�п�˫�������ý���
const String g_strCentMatrix = "CentCfgMatrixDlg";	//�������ý���
const String g_strCentSrceen = "CentCfgSrceenDlg";	//���������ý���

//��Ҫ����
const  string g_strShmShow = "SchmShow"; //��ʾ���� 
const  string g_strShmHide = "SchmHide"; //���ط���


CUIDataMgr::CUIDataMgr()
{

}

CUIDataMgr::~CUIDataMgr()
{

}

BOOL CUIDataMgr::NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam )
{
	BOOL bRe = FALSE;
	if ( NULL != g_hNotifyWnd )
	{
		::SendMessage( g_hNotifyWnd, nMsg, wparam, lparam );
		bRe = TRUE;
	}

	return bRe;
}

String CUIDataMgr::GetFileFolderPath( const String& strFilePath )
{
	String strFolderPath = strFilePath;
	s32 nPos = strFolderPath.rfind( "\\" );
	if ( nPos != std::string::npos )
	{
		strFolderPath = strFolderPath.substr( 0, nPos );
	}
	
	return strFolderPath;
}

String CUIDataMgr::OpenBrowseForFolder( const String& strFileName, HWND hWnd /*= NULL*/, BOOL bIsAddFileName /*= TRUE */ )
{
	String    strFolderPath;
	BROWSEINFO broInfo = {0};
	TCHAR       szDisName[MAX_PATH] = {0};
	
	broInfo.hwndOwner = hWnd/*NULL*/;
	broInfo.pidlRoot  = NULL;
	broInfo.pszDisplayName = szDisName;
	broInfo.lpszTitle = _T("ѡ�񱣴�·��");
	broInfo.ulFlags   = BIF_NEWDIALOGSTYLE | BIF_DONTGOBELOWDOMAIN
		| BIF_BROWSEFORCOMPUTER | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
	broInfo.lpfn      = NULL;
	broInfo.lParam    = NULL;
	
	LPITEMIDLIST pIDList = SHBrowseForFolder(&broInfo);
	if (pIDList != NULL)
	{
		memset(szDisName, 0, sizeof(szDisName));
		SHGetPathFromIDList(pIDList, szDisName);
		strFolderPath = szDisName;
		CString str(strFolderPath.c_str());
		s32 nIndex = str.Find( "\\", str.GetLength()-1 );
		if ( nIndex == -1 )
		{
			strFolderPath += "\\";
	    }
		//strFolderPath += "\\";

		if ( bIsAddFileName )
		{
			strFolderPath += strFileName;
		}
	}
	
	return strFolderPath;
}

BOOL CUIDataMgr::OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName, String& strFileName, BOOL bOpenStyle /*= TRUE */ )
{
	CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR, strFilter.c_str() ); // ����һ������������Ǳ���
	CString cstrName  = "";
	if ( dlg.DoModal() == IDOK )  
	{  
		cstrName = dlg.GetPathName();
		strFilePathName = cstrName.GetBuffer(cstrName.GetLength());
		cstrName = dlg.GetFileName();
		strFileName = cstrName.GetBuffer(cstrName.GetLength());
    } 
	else
	{
		return FALSE;
	}
	
	if ( FALSE == bOpenStyle )
	{	
		CFile cFile;
		CFileFind cFindExit;
		BOOL bWorking = cFindExit.FindFile(strFilePathName.c_str());
		if (bWorking == 1)
		{
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "ͬ���ļ��Ѵ���,�Ƿ��滻��" );
			if ( MSGBOX_OK == nMsgBoxRet )
			{
				cFile.Remove(strFilePathName.c_str());
			}
			else
			{
				return false;
			}
		}
	}

	return TRUE;
}

BOOL CUIDataMgr::OpenMutiFileDlg(const String& strFilter, const String& strDefFileName, String& strFilePathName, vector<String>& vecStrFileName, BOOL bOpenStyle /*= TRUE */)
{
	CFileDialog dlg( bOpenStyle, NULL, strDefFileName.c_str(), OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_NOCHANGEDIR, strFilter.c_str() ); // ����һ������������Ǳ���
	CString cstrName  = "";
	if ( IDOK == dlg.DoModal() )
	{
		cstrName = dlg.GetPathName();
		strFilePathName = cstrName.GetBuffer(cstrName.GetLength());

		POSITION pos = dlg.GetStartPosition();
		while ( NULL != pos )
		{
			CString strPathName = dlg.GetNextPathName(pos);
			int length = strPathName.GetLength();     
            for( int i=length-1; i>0; i-- )
			{
				if( '\\' == strPathName.GetAt(i) )
				{
					CString StrTempPathName = strPathName.Right(length - i -1);
					vecStrFileName.push_back(StrTempPathName.GetBuffer(0));
					StrTempPathName.ReleaseBuffer();
                    break;
				}
			}
		}
	}

	return TRUE;
}

BOOL CUIDataMgr::CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName )
{
	if ( strFileFullPath.empty() )
	{
		MSG_BOX_OK("·������Ϊ��!");	
		
		return FALSE;
	}
	
	s32 nPos = strFileFullPath.rfind( "\\" );
	String strFileName = strFileFullPath;
	if ( nPos != std::string::npos )
	{
		strFileName = strFileName.substr( nPos + 1, strFileName.size() );
	}
	
	if ( strCheckFileName != strFileName )
	{
		MSG_BOX_OK("������Ϸ����ļ�ȫ·��!"); 
		
		return FALSE;
	}
	
	return TRUE;
}

u64 CUIDataMgr::GetFileSize( const String& strFilePath )
{
	if( strFilePath.empty() )
	{
		return 0;
	}
	
	if ( !::PathFileExists(strFilePath.c_str()) )
	{
		return 0;
	}
	
	CFileException ex;
	CFile file;
	if ( !file.Open( strFilePath.c_str(), CFile::modeRead|CFile::shareDenyNone ) )
	{
		TCHAR chError[1024];
		ex.GetErrorMessage( chError, 1024 );
		return 0;
	}
	
	u64 nFileSize = file.GetLength();
	file.Close();
	
	return nFileSize;
}

BOOL CUIDataMgr::IsFileExist( const CString& strFileFullPath )
{
	if( strFileFullPath.IsEmpty() )
	{
		return FALSE;
	}
	
	DWORD dwAttr = GetFileAttributes(strFileFullPath);
	if( INVALID_FILE_ATTRIBUTES == dwAttr || ( dwAttr & FILE_ATTRIBUTE_DIRECTORY ) )
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CUIDataMgr::IsFolderExist( const CString& strFolderFullPath )
{
	DWORD dwAttr; 
    dwAttr = GetFileAttributes(strFolderFullPath); 
    return ( dwAttr != INVALID_FILE_ATTRIBUTES ) && ( dwAttr & FILE_ATTRIBUTE_DIRECTORY); 
}

BOOL CUIDataMgr::IsIniFile( const String& strFileName )
{
	if ( !IsFileExist(strFileName.c_str()) )
	{
		return FALSE;
	}
	
	String strFileExtName;
	s32 nPos = strFileName.rfind( "." );
	if ( nPos != std::string::npos )
	{
		strFileExtName = strFileName.substr( nPos + 1, strFileName.size() );
		if ( strFileExtName == "ini" )
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
	
	return FALSE;
}

CString CUIDataMgr::GetIpStr( unsigned int dwIPAddr )
{
	CString strIP;
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIPAddr);
	strIP = inet_ntoa(addrIPAddr);
	
    return strIP;
}

BOOL CUIDataMgr::RecusionMkDir( CString strFolder )
{
	s32 nLen = strFolder.GetLength();
    if( nLen < 2 ) 
	{
		return FALSE; 
    }
	
    if( '\\' == strFolder[nLen-1] )
    {
        strFolder = strFolder.Left( nLen-1 );
        nLen = strFolder.GetLength();
    }
	
    if ( nLen <= 0 ) 
	{
		return FALSE;
    }
	
    if ( nLen <= 3 ) 
    {
        if ( IsFolderExist(strFolder) )
		{
			return TRUE;
        }
		else
		{
			return FALSE; 
		}
    }
	
    if ( IsFolderExist(strFolder) )
	{
		return TRUE;
	}
	
    CString strParent;
    strParent = strFolder.Left( strFolder.ReverseFind('\\') );
    if( strParent.GetLength() <= 0)
	{
		return FALSE; 
    }
	
    BOOL bRet = RecusionMkDir(strParent); 
    if( bRet ) 
    {
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.lpSecurityDescriptor = NULL;
        sa.bInheritHandle = 0;
        bRet = CreateDirectory( strFolder, &sa );
		
        return bRet;
    }
    else
	{
        return FALSE;
	}
	
	return TRUE;
}

void CUIDataMgr::SetLstSelItem(const String& strLstWnd, IWndTree* pWndTree /*= NULL*/, s32 nItemNo)
{
	CTransparentList* pWnd = (CTransparentList*)UIFACTORYMGR_PTR->GetWindowPtr( strLstWnd, pWndTree );
	if ( NULL != pWnd )
	{
		pWnd->SetSelItem(nItemNo);
	}
}

bool CUIDataMgr::IsValidPWStr(CString szPWStr)
{
	if (szPWStr.IsEmpty())
	{
		return false;
	}
	//Ҫ��:8-16���ַ������ٰ�����ĸ�����֣������ַ������е�����
	int nCount = szPWStr.GetLength();
	if (nCount < 8 || nCount > 16)
	{
		return false;
	}
	//������
	CString szTemp = szPWStr.SpanIncluding(_T("0123456789"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//��Ӣ����ĸ
	szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//�������ַ�'.','_'
	szTemp = szPWStr.SpanIncluding(_T("._"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	
	return true;
}

bool CUIDataMgr::IsValidNameStr( String strText )
{
	CString strError = INVALID_ALIAS_FOR_CODE;
	CString str(strText.c_str());
	CString strRe = str.SpanExcluding( strError );
	if ( strRe != str )
	{
		return false;
	} 
	return true;
}

bool CUIDataMgr::JudgeIp(char *szIP, IP_Struct::IpAdress_Struct *ipAdress)  
{  
    if (!szIP)
	{
		return false;  
	}
    int index = 0;  
    int first = 0, second = 0, third = 0, forth = 0;     
    std::string ip = std::string(szIP);  
    first = atoi(&ip[index]);    
    if ( first > 255 ) 
	{
        return false;  
	}
    if ( ipAdress )  
	{
        ipAdress->first=first;  
	}
	
    index ++;    
    index = ip.find_first_of('.',index);    
    second = atoi(&ip[++index]);    
    if( second > 255 )
	{
        return false;   
	}
    if (ipAdress)  
	{
        ipAdress->second=second;  
	}
	
    index ++;    
    index = ip.find_first_of('.',index);    
    third=atoi(&ip[++index]);    
    if( third > 255 ) 
	{
        return false;   
	}
    if (ipAdress)  
	{
        ipAdress->third=third;  
	}
	
    index ++;    
    index = ip.find_first_of('.',index);    
    forth = atoi(&ip[++index]);    
    if( forth > 255 )  
	{
        return false;    
	}
    if (ipAdress)
	{
        ipAdress->forth=forth;  
	}
	
    return true;    
}  

//-1 indicates ip��ʽ����0��ʾ��ͬ���Σ�1��ʾͬ����  
int CUIDataMgr::IsSameNetworkSegment(char *szIPAdress, char *szIPAdresss1, char *szMask)  
{  
    if (!szIPAdress || !szMask || !szIPAdresss1) 
	{ 
		return false;  
	}
    IP_Struct::IpAdress_Struct ip,ip1,mask;  
    if (JudgeIp(szIPAdress, &ip) && JudgeIp(szIPAdresss1, &ip1) && JudgeIp(szMask, &mask))  
    {  
		ip.first = ip.first & mask.first;    
		ip.second = ip.second & mask.second;    
		ip.third = ip.third & mask.third;    
		ip.forth = ip.forth & mask.forth;    
		
		ip1.first = ip1.first & mask.first;    
		ip1.second = ip1.second & mask.second;    
		ip1.third = ip1.third & mask.third;    
		ip1.forth = ip1.forth & mask.forth;    
		
		if(ip.first == ip1.first && ip.second == ip1.second && ip.third == ip1.third && ip.forth == ip1.forth )    
		{
			return 1;  
		}
		else    
		{
			return 0;  
		}
    }  
    else  
	{
        return -1;  
	}
}  

bool CUIDataMgr::IsValidIpV6(CString lptrIPStr)
{
    int nCheckChar = 0;
    int nCheckColon = 0;
    int nEllipsis = 0;
    s32 nLen = strlen( lptrIPStr );    //  �ַ�������
    for ( s32 nCount = 0 ; nCount < nLen ; ++nCount )
    {
        if ((lptrIPStr[nCount] >= '0') && (lptrIPStr[nCount] <= '9'))
        {
            nCheckChar = 0;
        }
        else if ((lptrIPStr[nCount] >= 'a') && (lptrIPStr[nCount] <= 'f'))
        {
            nCheckChar = 0;
        }
        else if ((lptrIPStr[nCount] >= 'A') && (lptrIPStr[nCount] <= 'F'))
        {
            nCheckChar = 0;
        }
        else if (lptrIPStr[nCount] == ':')
        {
            nCheckColon++;
            nCheckChar++;
            if (nCheckChar > 2)//��������ð��
            {
                return false;
            }
            else if (nCheckChar == 2)
            {
                nEllipsis++;
                if (nEllipsis > 1)//����һ�ε�ʡ��
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return (nCheckColon == 7) || (nEllipsis != 0);
}