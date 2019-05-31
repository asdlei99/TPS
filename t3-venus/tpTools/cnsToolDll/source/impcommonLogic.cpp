// impcommonLogic.cpp: implementation of the CImpCommonDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "impcommonLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static UINT g_nTransTime = 0;

VOID  CALLBACK  CWaitTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
	if ( IMPCOMMONLOGICRPTR->GetFtpStatus() != emFtpEnd )
	{
		if ( IMPCOMMONLOGICRPTR->GetTimeOutCount() >= 4 )
		{
			IMPCOMMONLOGICRPTR->ClearTransFile();
		}
		else
		{
			IMPCOMMONLOGICRPTR->SetTimeOutCount();
		}
	}
}

CImpCommonDlgLogic::CImpCommonDlgLogic()
:m_strEdtSaveFolder("EdtImpCommonSaveFolder")
,m_strProgressImp("ProgressImpCommon")
,m_strLstUpgradeFile("BoardUpgradeDlg/LstBoardUpgrade")
,m_strStcUpSerName("UpgradeDlg/StcUpSerName")
,m_strStcUpSerName1("UpgradeDlg/StcUpSerName1")
,m_strStcUpSerName2("UpgradeDlg/StcUpSerName2")
,m_strStcUpSerByte("UpgradeDlg/StcUpSerByte")
,m_strStcUpSerByte1("UpgradeDlg/StcUpSerByte1")
,m_strStcUpSerByte2("UpgradeDlg/StcUpSerByte2")
,m_nCount(0)
{
	m_pWnd = NULL;
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
	m_vecStrImpFileName.clear();
	m_bImportCnsCfg = FALSE;
	m_bUpgradeCns = FALSE;
}

CImpCommonDlgLogic::~CImpCommonDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

bool CImpCommonDlgLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrImpCommonDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}
	
    return true;
}

void CImpCommonDlgLogic::RegMsg()
{
	CImpCommonDlgLogic *pThis =  GetSingletonPtr();
	
    REG_MSG_HANDLER( UI_SETFTPINFO_Rsp, CImpCommonDlgLogic::OnSetFtpInfoRsp, pThis, CImpCommonDlgLogic );
}

void CImpCommonDlgLogic::UnRegMsg()
{
	
}

void CImpCommonDlgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::InitWnd", CImpCommonDlgLogic::InitWnd, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnClose", CImpCommonDlgLogic::OnBtnClose, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportCamCfg", CImpCommonDlgLogic::OnBtnImportCamCfg, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportCnsCfg", CImpCommonDlgLogic::OnBtnImportCnsCfg, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnUpgradeCns", CImpCommonDlgLogic::OnBtnUpgradeCns, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_DEFAULT_WINDOW_MSG( WM_CNSTOOL_UPLODEPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnUploadProgress", CImpCommonDlgLogic::OnUploadProgress, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic );
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnBtnImportScan", CImpCommonDlgLogic::OnBtnImportScan, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CImpCommonDlgLogic::OnFolderEditChange", CImpCommonDlgLogic::OnFolderEditChange, IMPCOMMONLOGICRPTR, CImpCommonDlgLogic ); 

}

void CImpCommonDlgLogic::UnRegFunc()
{
	
}

void CImpCommonDlgLogic::Clear()
{
	BOOL bOk = KillTimer(NULL,g_nTransTime);	//�ص���ʱ��
	CleanTransfer();
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );

	m_vecStrImpFileName.clear();
	m_bImportCnsCfg = FALSE;
	m_bUpgradeCns = FALSE;
}

bool CImpCommonDlgLogic::OnBtnClose( const IArgs & arg )
{
	CleanTransfer();
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
	
	return true;
}

bool CImpCommonDlgLogic::OnUploadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			m_dwTotalFileSize = static_cast<u32>(msg.lParam);
			
			UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree );
		}
		break;
	case emFtpTransfer:
		{
			m_nCount = 0;
			if ( m_dwTotalFileSize != 0 )
			{
				u32 dwCurrentTransSize = static_cast<u32>(msg.lParam);   //��ǰ����Ĵ�С
				
				float fCurrTransProgress = (float)dwCurrentTransSize/m_dwTotalFileSize*100;
				if ( dwCurrentTransSize < m_dwTotalFileSize )
				{	
					m_valProgress.nPos = (u32)fCurrTransProgress;
					
					UIFACTORYMGR_PTR->SetPropertyValue( m_valProgress, m_strProgressImp, m_pWndTree );
				}
			}
		}
		break;
	case emFtpEnd:
		{
			m_nCount = 0;
			BOOL bOk = KillTimer( NULL, g_nTransTime );	//�ص���ʱ��
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			if ( 0 == dwSuccess )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				
				//����ɹ�   �޸���ʱ�ļ�Ϊʵ���ļ�   ���⴫������������ն˲������쳣
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				if ( !m_cFtp.RenameFtpFile( strCurTransRemoteTempFileFullPath.c_str(), m_strCurTransRemoteFileFullPath.c_str() ) )
				{
					MSG_BOX_OK_SAFE("�����ļ���������ԭ���������ļ�ʧ�ܣ�",g_stcStrImpCommonDlg);
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
				
				String strCaption;    //�����ļ��ϴ��ɹ�   ����������Ϣ��������
				UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
				if ( "����" == strCaption )
				{
					BOOL bInConf = LIBDATAMGRPTR->IsInConf();
					if ( bInConf )
					{
						MSG_BOX_OK("����ʧ��:��ǰ�᳡���ڿ��ᣬ���Ժ��ٴ�����");
						s32 nResult = 0;
						UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
					}
					else
					{
// 						MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 						MSG_BOX( nMsgBoxRet, "�����ļ��ѵ��룬��Ҫ����������Ч���Ƿ�����������" );	
// 						if ( MSGBOX_OK == nMsgBoxRet )
// 						{
// 							bInConf = LIBDATAMGRPTR->IsInConf();
// 							if ( bInConf )
// 							{
// 								MSG_BOX_OK("����ʧ��:��ǰ�᳡���ڿ��ᣬ���Ժ��ٴ�����");
// 								s32 nResult = 0;
// 								UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
// 							}
// 							else
// 							{
								TTPFTPFileInfo tVerFileInfo;
								String strPathName = UPDATEFILE_PATH_NAME;
								strPathName += m_strImpFileName;
								tVerFileInfo.byFilePathLen = sprintf(tVerFileInfo.achFilePath,"%s",strPathName.c_str());
								u16 wRe = COMIFMGRPTR->UpgradeCns(tVerFileInfo);
								if ( wRe != 0 )
								{
									MSG_BOX_OK_SAFE("����ʧ��:�������������ʧ��",g_stcStrImpCommonDlg);
								}
								else
								{
									UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonFolderScan", FALSE, m_pWndTree );
									UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonExport", FALSE, m_pWndTree );
									UIFACTORYMGR_PTR->EnableWindow( "BtnImpCommonDlgClose", FALSE, m_pWndTree );
								}
//							}
//						}
//						else
//						{
//							s32 nResult = 0;
//							UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrImpCommonDlg );
//						}
					}
				}
				else if ( "�������������" == strCaption )
				{
					COMIFMGRPTR->SetLoadCameraFileNty();

					MSG_BOX_OK_SAFE("��������������ɹ���", g_stcStrImpCommonDlg);
					UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
				}
				else if( "��������" == strCaption )
				{
					//MSG_BOX_OK_SAFE("���������ļ��ɹ���", g_stcStrImpCommonDlg);
					m_cFtp.EndFtpFile();
					Value_WindowCaption valFolderName;
					UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
					
					String strFileFullPath;
					strFileFullPath = valFolderName.strCaption.c_str();

					vector<String>::iterator itr = m_vecStrImpFileName.begin();
					m_vecStrImpFileName.erase(itr);
					u32 n= m_vecStrImpFileName.size();

					if( n > 0 )
					{
						strFileFullPath += "\\";
						strFileFullPath += m_vecStrImpFileName.at(0);
						if( m_vecStrImpFileName.at(0) == CNSCONFIG_FILE_NAME )
						{
							UploadCore( CNSCONFIG_FILE_PATH, strFileFullPath, CNSCONFIG_FILE_NAME );
						}
						else if( strCaption == CNSCONFIG_FILE_NAME_ZERO )
						{
							UploadCore( CNSCONFIG_FILE_EXT_PATH, strFileFullPath, CNSCONFIG_FILE_NAME_ZERO );
						}
						else
						{
							UploadCore( CNSCONFIG_FILE_EXT_PATH, strFileFullPath, CNSCONFIG_FILE_NAME_ONE );
						}

						return true;
					}
									
					MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
					MSG_BOX( nMsgBoxRet, " �����ļ��ѵ��룬��Ҫ����������Ч���Ƿ�����������" );
					if( MSGBOX_OK == nMsgBoxRet )
					{
						u16 nRet = COMIFMGRPTR->RebootCns();
						if ( nRet != NO_ERROR )
						{
							WARNMESSAGE( "����cns������ʧ��!" );
						}
					}
				}
			}
			else
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "�����ļ���������ԭ��%s��", pszMsg );
				//MSG_BOX_OK(pszMsg);---  ���ӵ�ʱ�������Ϣ�հ�,�ݲ�����
				String strCurTransRemoteTempFileFullPath;
				strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
				m_cFtp.DeleteFile(strCurTransRemoteTempFileFullPath.c_str());
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
				UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp  );
				LocalFree( pszMsg );
			}
			
			m_cFtp.EndFtpFile();
		}
		break;
	default:
		{
		}
		break;
	}
	
	return true;
}

bool CImpCommonDlgLogic::OnBtnImportScan( const IArgs & arg )
{
	String strFile;
	String strCaption;
	CString strFilter;
	String strDefFileNameGz;
	UIFACTORYMGR_PTR->GetCaption( "ImpCommonDlg/StcImpCommonCap", strCaption, NULL );
	if ( "�������������" == strCaption )
	{
		strFile = /*CNSCAMERA_FILE_NAME*/"";  //����һ����,������������ļ���
		strFilter = "����������ļ�(cameracfg.ini)|cameracfg.ini||";  
	}
	if ( "����" == strCaption )
	{
		strFile = CNSUPGRADE_NAME;
		strFile = strFile + ";" + CNSUPGRADE_NAME_Y;	//����һ����,������T300�����ļ���,��Ϊ��2��,�ݲ�������
		
		strDefFileNameGz =CNSUPGRADE_NAME;
		strDefFileNameGz = strDefFileNameGz + ".gz;" + CNSUPGRADE_NAME_Y + ".gz";// 

		strFilter.Format("�����ļ�(%s;%s)|%s;%s||",strFile.c_str(),strDefFileNameGz.c_str(),strFile.c_str(),strDefFileNameGz.c_str());
	}
	if( "��������" == strCaption )
	{
		strFile+= "";
		strFilter = "CNC�����ļ�(cncfg.ini;0cncfg.ini;1cncfg.ini)|cncfg.ini;0cncfg.ini;1cncfg.ini||";
	}
	
	if( "��������" == strCaption )
	{
		String strImpFileFullPath;
		m_vecStrImpFileName.clear();
		UIDATAMGR_PTR->OpenMutiFileDlg( strFilter.GetBuffer(strFilter.GetLength()-1), strFile, strImpFileFullPath, m_vecStrImpFileName );

		if ( !strImpFileFullPath.empty() )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strImpFileFullPath, m_pWndTree );
		}

		if( strImpFileFullPath.empty() )
		{
			return false;
		}

		if( (m_vecStrImpFileName.size() != 3) )
		{
			MSG_BOX_OK(" ѡȡ�����ļ������㣬������ѡ��");
			m_vecStrImpFileName.clear();
			UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerName, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerByte, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerName1, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerByte1, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerName2, "", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerByte2, "", m_pWndTree );
			return false;
		}
		else
		{
			SetLineFileInfo( strImpFileFullPath, m_vecStrImpFileName[0], 0 );
			SetLineFileInfo( strImpFileFullPath, m_vecStrImpFileName[1], 1 );
			SetLineFileInfo( strImpFileFullPath, m_vecStrImpFileName[2], 2 );
		}
	}
	else
	{
		String strImpFileFullPath;
		UIDATAMGR_PTR->OpenFileDialog( strFilter.GetBuffer(strFilter.GetLength()-1), strFile, strImpFileFullPath, m_strImpFileName );
		if ( !strImpFileFullPath.empty() )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strEdtSaveFolder, strImpFileFullPath, m_pWndTree );
		}
		if ( m_strImpFileName.empty() || strImpFileFullPath.empty() )
		{
			return false;
		}
		//������ӵ��ļ����ļ��б�
		UIFACTORYMGR_PTR->SetCaption( "UpgradeDlg/StcUpSerName", m_strImpFileName, m_pWndTree );
		s64 nSize = UIDATAMGR_PTR->GetFileSize(strImpFileFullPath);
		s8 chSize[8] = {0};
		String strSize;
		if ( 1024 > nSize )
		{
			sprintf( chSize, "%u", nSize );
			strSize = chSize;
			strSize += "byte";
		}
		else if ( 1024 < nSize && nSize < 1024*1024 )
		{
			float fSize = 1.0*nSize/1024;
			sprintf( chSize, "%.1f", fSize );
			strSize = chSize;
			strSize += "Kb";
		}
		else if ( 1024*1024 < nSize )
		{
			float fSize = 1.0*nSize/(1024*1024);
			sprintf( chSize, "%.1f", fSize );
			strSize = chSize;
			strSize += "M";
		}
 		UIFACTORYMGR_PTR->SetCaption( "UpgradeDlg/StcUpSerByte", strSize, m_pWndTree );
	}
	
// 	TUmsToolFile tFileList;
// 	strncpy( tFileList.chFileName, strImpFileName.c_str(), _MAX_FNAME );
// 	strncpy( tFileList.chFileFullPath, strImpFileFullPath.c_str(), MAX_PATH );
// 	tFileList.nFileSize = CUmstoolCommon::GetFileSize(tFileList.chFileFullPath);
// 	if ( tFileList.nFileSize > 0 )
// 	{
// 		m_vecUpgradeFile.push_back(tFileList);
// 		UpdateUpgradeFileList();
// 	}
	
	return true;
}

void CImpCommonDlgLogic::SetLineFileInfo(String strImpFilePath, String strFileName, int lineNum)
{
	String strImpFileFullPath = strImpFilePath;
	strImpFileFullPath += "\\";
	strImpFileFullPath += strFileName;
	
	s64 nSize = UIDATAMGR_PTR->GetFileSize(strImpFileFullPath);
	s8 chSize[8] = {0};
	String strSize;
	if ( 1024 > nSize )
	{
		sprintf( chSize, "%u", nSize );
		strSize = chSize;
		strSize += "byte";
	}
	else if ( 1024 < nSize && nSize < 1024*1024 )
	{
		float fSize = 1.0*nSize/1024;
		sprintf( chSize, "%.1f", fSize );
		strSize = chSize;
		strSize += "Kb";
	}
	else if ( 1024*1024 < nSize )
	{
		float fSize = 1.0*nSize/(1024*1024);
		sprintf( chSize, "%.1f", fSize );
		strSize = chSize;
		strSize += "M";
	}

	if( 0 == lineNum )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerName, strFileName, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerByte, strSize, m_pWndTree );
	}
	else if( 1 == lineNum )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerName1, strFileName, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerByte1, strSize, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerName2, strFileName, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strStcUpSerByte2, strSize, m_pWndTree );
	}
	
}

bool CImpCommonDlgLogic::OnFolderEditChange( const IArgs & arg )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree, m_strProgressImp );
	
	return true;	
}

bool CImpCommonDlgLogic::OnBtnUpgradeCns( const IArgs & arg )
{
	String strFileFullPath;
	String strFile,strDefFileNameGz;
	String strFileY,strDefFileYNameGz;
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	strFileFullPath = valFolderName.strCaption.c_str();
	
	if ( strFileFullPath.size() == 0 )
	{
		MSG_BOX_OK("·������Ϊ��!");	
		
		return FALSE;
	}

	strFile = CNSUPGRADE_NAME;
	strDefFileNameGz =strFile + ".gz";// 
	strFileY = CNSUPGRADE_NAME_Y;
	strDefFileYNameGz =strFile + ".gz";// 

	if ( ( strcmp(m_strImpFileName.c_str(),strFile.c_str())!=0 )&&( strcmp(m_strImpFileName.c_str(),strDefFileNameGz.c_str())!=0) && 
		 ( strcmp(m_strImpFileName.c_str(),strFileY.c_str())!=0 )&&( strcmp(m_strImpFileName.c_str(),strDefFileYNameGz.c_str())!=0))
	{
		CString CLog = "";
		CLog.Format("�Ƿ��������ļ����������ļ�����Ϊ��%s ; %s.gz �� %s ; %s.gz!", CNSUPGRADE_NAME,CNSUPGRADE_NAME,CNSUPGRADE_NAME_Y,CNSUPGRADE_NAME_Y);
		MSG_BOX_OK(CLog.GetBuffer(CLog.GetLength()-1));
		return false;
	}

	if( LIBDATAMGRPTR->CheckVerNew() == true )
	{
		TTPFtpInfo tTPFtpInfo;
		LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
		if (!tTPFtpInfo.bOpen)
		{
			//������ʾ
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "�����迪��FTP������ȷ���Ƿ�����" );	
			if ( nMsgBoxRet != MSGBOX_OK )
			{
				return false;		 
			}
			
			tTPFtpInfo.bOpen = TRUE;
			u16 wRet = COMIFMGRPTR->SetFtpInfoRsq(tTPFtpInfo);
			
			if( wRet != NO_ERROR)
			{
				WARNMESSAGE("FTP������������ʧ��");
				return false;
			}
			m_bUpgradeCns = TRUE;
		}
		else
		{
			UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //������Ҫ��������
		}
	}
	else
	{
		UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //������Ҫ��������
	}

	return true;
}

BOOL CImpCommonDlgLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ /*= TRUE */ )
{
	if ( !UIDATAMGR_PTR->CheckTransferFile( strLocalFile, strCheckFileName ) )
	{
		return false;
	}

	if ( !UIDATAMGR_PTR->IsFileExist( strLocalFile.c_str() ) )
	{
		MSG_BOX_OK("ָ���ļ������ڣ��޷�����!");
		return false;
	}
	
	m_cFtp.RegisterMsgHandle( WM_CNSTOOL_UPLODEPROGRESS );
	
	CString strIpAddr;
	if ( bIsDefServ )
	{
		u32 dwIp;
		LIBDATAMGRPTR->GetLoginIp(dwIp);
		strIpAddr = UIDATAMGR_PTR->GetIpStr( dwIp );
	}
	else
	{
		strIpAddr = UIDATAMGR_PTR->GetIpStr( GetSevrIpAddr() );
	}
	
	EmCnModel emCnModel;
	LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );
	
	BOOL32 bRet;
	if( LIBDATAMGRPTR->CheckVerNew() == false )
	{
		if( ( emCnModel == T300 ) || ( emCnModel == T300E ) || ( emCnModel == em7920 ) )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, FTP_CONNECT_USER, FTP_CONNECT_PSWD );
		}
		else
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, T300E_TEL_USRNAME, T300E_TEL_PWD ); //����-cs�汾
		}
	}
	else
	{
		TTPFtpInfo tTPFtpInfo;
		LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
		
		if( tTPFtpInfo.bOpen )
		{
			bRet = m_cFtp.SetServerParam( strIpAddr, tTPFtpInfo.achUserName, tTPFtpInfo.achPassword );
		}
		else
		{
			bRet = 0;
		}
	}
	
	if ( !bRet )
	{
		MSG_BOX_OK("���ӷ�����ʧ��!");
		
		return false;
	}
	
	if ( NULL != m_pWnd )
	{
		String strRemoteFilePath = strRemotePath;
		strRemoteFilePath += strCheckFileName;
		m_strCurTransRemoteFileFullPath = strRemoteFilePath;
		strRemoteFilePath += ".temp";
		m_cFtp.SetIsRenameTransFile(TRUE);
		if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(),
			FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
		{
			MSG_BOX_OK("�������ʧ��!");
			
			return false;
		}
		m_nCount = 0;
		//���ö�ʱ�� ʱ����10s  �������ϴ��յ���Ϣ��40��û�յ�FTP��Ϣ��û����ʱ�����ر�
		g_nTransTime = SetTimer( NULL, 0, 10000, CWaitTimerFun );
	}
	
	return TRUE;
}

void CImpCommonDlgLogic::CleanTransfer()
{
	if ( emFtpEnd != m_emFileFtpStatus )
	{
		m_cFtp.EndFtpFile();
	}
	
	m_emFileFtpStatus = emFtpEnd;
	m_dwTotalFileSize = 0;
	m_dwCurSevr = 0;
	
	m_strCurTransRemoteFileFullPath = "";
	m_strImpFileName = "";
	//UpdateUpgradeFileList();
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", m_pWndTree );
}

// 
// void CImpCommonDlgLogic::UpdateUpgradeFileList()
// {
// 	if ( NULL == m_pWndTree  )
// 	{
// 		return;
// 	}
// 	
// 	Value_ItemBoardUpgrade itemBoardUpgrade( &m_vecUpgradeFile );
// 	UIFACTORYMGR_PTR->SetPropertyValue( itemBoardUpgrade, m_strLstUpgradeFile, m_pWndTree );
// }

bool CImpCommonDlgLogic::OnBtnImportCamCfg( const IArgs & arg )
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	UploadCore( CNSCAMERA_FILE_PATH, strFileFullPath, CNSCAMERA_FILE_NAME );
	
	return true;
}

bool CImpCommonDlgLogic::OnBtnImportCnsCfg(const IArgs & arg)
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );

	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strStcUpSerName, strCaption, m_pWndTree );

	if( strCaption.empty() )
	{
		MSG_BOX_OK("û��ѡ�����ļ�����ѡ�����ļ���");
		return false;
	}
	else
	{
		TTPFtpInfo tTPFtpInfo;
		LIBDATAMGRPTR->GetFtpInfo( tTPFtpInfo );
		if (!tTPFtpInfo.bOpen)
		{
			//������ʾ
			MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
			MSG_BOX( nMsgBoxRet, "�����ļ��迪��FTP������ȷ���Ƿ�����" );	
			if ( nMsgBoxRet != MSGBOX_OK )
			{
				return false;		 
			}
			
			tTPFtpInfo.bOpen = TRUE;
			u16 wRet = COMIFMGRPTR->SetFtpInfoRsq(tTPFtpInfo);
			
			if( wRet != NO_ERROR)
			{
				WARNMESSAGE("FTP������������ʧ��");
				return false;
			}
			m_bImportCnsCfg = TRUE;
		}
		else
		{
			ImportCnsCfg();
		}
	}

	return true;
}

void CImpCommonDlgLogic::ClearTransFile()
{
	if ( m_cFtp.GetIsRenameTransFile() && m_emFileFtpStatus == emFtpTransfer )
	{
		String strCurTransRemoteTempFileFullPath;
		strCurTransRemoteTempFileFullPath.append(m_strCurTransRemoteFileFullPath).append(".temp");
		m_cFtp.DeleteFile(strCurTransRemoteTempFileFullPath.c_str());
	}
	m_nCount = 0;
	KillTimer( NULL, g_nTransTime );	//�ص���ʱ��	
	MSG_BOX_OK("�����ļ���������ԭ�򣺳�ʱ");
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferEnd", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmTransferBeg", m_pWndTree, m_strProgressImp );
	m_cFtp.EndFtpFile();
}

void CImpCommonDlgLogic::SetTimeOutCount()
{
	m_nCount ++;
}

u32 CImpCommonDlgLogic::GetTimeOutCount()
{
	return m_nCount;
}

void CImpCommonDlgLogic::ImportCnsCfg()
{
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	String strFileFullPath;
	strFileFullPath = valFolderName.strCaption.c_str();
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strStcUpSerName, strCaption, m_pWndTree );

	strFileFullPath += "\\";
	strFileFullPath += strCaption;
	if( strCaption == CNSCONFIG_FILE_NAME )
	{
		UploadCore( CNSCONFIG_FILE_PATH, strFileFullPath, CNSCONFIG_FILE_NAME );
	}
	else if( strCaption == CNSCONFIG_FILE_NAME_ZERO )
	{
		UploadCore( CNSCONFIG_FILE_EXT_PATH, strFileFullPath, CNSCONFIG_FILE_NAME_ZERO );
	}
	else
	{
		UploadCore( CNSCONFIG_FILE_EXT_PATH, strFileFullPath, CNSCONFIG_FILE_NAME_ONE );
	}
}

HRESULT CImpCommonDlgLogic::OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam )
{
	TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	if( bSuccess ) 
	{
		//��������
		if (m_bImportCnsCfg)
		{
			if (tTPFtpInfo.bOpen)
			{
				m_bImportCnsCfg = FALSE;
                ImportCnsCfg();
			}
		}

		//����
		if (m_bUpgradeCns)
		{
			if (tTPFtpInfo.bOpen)
			{
				m_bUpgradeCns = FALSE;
                UpgradeCns();
			}
		}
	}
    return S_OK;
}

void CImpCommonDlgLogic::UpgradeCns()
{
	String strFileFullPath;
	Value_WindowCaption valFolderName;
	UIFACTORYMGR_PTR->GetPropertyValue( valFolderName, m_strEdtSaveFolder, m_pWndTree );
	
	strFileFullPath = valFolderName.strCaption.c_str();

	UploadCore( /*CNSUPGRADE_FILE_PATH*/UPDATEFILE_PATH_NAME, strFileFullPath, /*CNSUPGRADE_FILE_NAME*/m_strImpFileName );  //������Ҫ��������
}
