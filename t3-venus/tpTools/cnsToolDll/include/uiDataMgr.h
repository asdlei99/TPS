// uiDataMgr.h: interface for the CUIDataMgr class.

/*****************************************************************************
ģ����      : ������صĹ������ݹ���ģ��
�ļ���      : uiDataMgr.h
����ļ�    : ���д�����ص�ȫ������Ӧ����ڴ˴�
�ļ�ʵ�ֹ���: ������������
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/23     1.0         ������      ����
******************************************************************************/


#if !defined(AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_)
#define AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"

//ip�����ݽṹ
typedef struct IP_Struct{  
    //ip��ַ���ֺ�������ֵ  
    struct IpAdress_Struct  
    {  
        int first;    
        int second;    
        int third;    
        int forth;  
    }IpAdress,*pIPAdress;  
    //ip��ַ  
    char szIPAdress[MAX_PATH];  
    //��������  
    char szIPMask[MAX_PATH];  
    IP_Struct()  
    {  
        strcpy(szIPAdress,"");  
        strcpy(szIPMask,"");  
    }  
    IP_Struct(char szIPAdress[],char szIPMask[])  
    {  
        strcpy(this->szIPAdress,szIPAdress);  
        strcpy(this->szIPMask,szIPMask);  
    }  
}IP,*pIP;  

class CUIDataMgr:public ISingleTon<CUIDataMgr> 
{
public:
	CUIDataMgr();
	virtual ~CUIDataMgr();

	/*---------------------------------------------------------------------
	* ��    �ܣ����ⲿ���ڷ���֪ͨ
	* ���������
	* ���������
	* �� �� ֵ������FALSE����ʧ��
	* ��    ע��  
	* ����			�汾		�޸���		�޸ļ�¼
	* 2012.12.13    1.0         �����        ����
	----------------------------------------------------------------------*/
	 BOOL NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam );
	/*=============================================================================
    �� �� ��:IsFileExist
    ��    ��:����ļ��Ƿ����
    ��    ��:const CString& strFileFullPath    [in]     �ļ�ȫ·������
    ע    ��:��
    �� �� ֵ:TRUE: �ɹ�   FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL IsFileExist(const CString& strFileFullPath);

	/*=============================================================================
    �� �� ��:IsFolderExist
    ��    ��:���Ŀ¼�Ƿ����
    ��    ��:const CString& strFolderFullPath    [in]     Ŀ¼ȫ·������
    ע    ��:��
    �� �� ֵ:TRUE: �ɹ�   FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL IsFolderExist(const CString& strFolderFullPath);

	/*=============================================================================
    �� �� ��:IsIniFile
    ��    ��:����Ƿ���ini�ļ����ڻ���ģ��͵�ַ�ļ����
    ��    ��:const String& strFileName    [in]     �ļ�ȫ·������
    ע    ��:��
    �� �� ֵ:TRUE: �ɹ�   FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL IsIniFile(const String& strFileName);

	/*=============================================================================
    �� �� ��:GetIpStr
    ��    ��:����ͨ����ת��ΪIP��
    ��    ��:unsigned int dwIPAddr    [in]     IP�����ͱ�ʾ��ʽ
    ע    ��:��
    �� �� ֵ:���ơ�127.0.0.1����ʽ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 CString GetIpStr(unsigned int dwIPAddr);

	/*=============================================================================
    �� �� ��: GetFileFolderPath
    ��    ��: �õ��ļ������ļ���·����
    ��    ��: const String& strFilePath        [in]    �ļ�ȫ·����
    ע    ��:��
    �� �� ֵ:String     �ļ������ļ���·����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 String GetFileFolderPath(const String& strFilePath);

	/*=============================================================================
    �� �� ��: OpenBrowseForFolder
    ��    ��: ������ļ�Ŀ¼��Ӧ�����ļ����桢���ء������ȣ�
    ��    ��: const String& strFileName        [in]    �ļ���
	��    ��: HWND hWnd                        [in]    ��Ϊģ̬�Ի���hWndΪ�����ھ��   by xhx
    ��    ��: BOOL bIsAddFileName              [in]    �Ƿ񸽼��ļ���   FALSE��ֱ�ӵõ�Ŀ¼��
    ע    ��:��
    �� �� ֵ:String     �ļ�ȫ·��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 String OpenBrowseForFolder(const String& strFileName, HWND hWnd = NULL, BOOL bIsAddFileName = TRUE );

	/*=============================================================================
    �� �� ��: OpenFileDialog
    ��    ��: ���ļ�Ŀ¼��Ӧ�����ļ�����Ϊ�����롢�򿪵ȣ�
    ��    ��: const String& strFilter			  [in]    �����ļ�
    ��    ��: const String& strDefFileName        [in]    Ĭ����ʾ�ļ���
    ��    ��: const String& strFilePathName       [out]    �ļ�ȫ·��
    ��    ��: String strFileName				  [out]    �ļ���
    ��    ��: BOOL bOpenStyle					  [in]    ������������Ǳ���
    ע    ��:��
    �� �� ֵ:String     �ļ�ȫ·��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName,
		 String& strFileName, BOOL bOpenStyle = TRUE );

	/*=============================================================================
    �� �� ��: OpenMutiFileDlg
    ��    ��: ���ļ�Ŀ¼��Ӧ�����ļ�����Ϊ�����롢�򿪵ȣ�, ѡ�����ļ�
    ��    ��: const String& strFilter			  [in]    �����ļ�
    ��    ��: const String& strDefFileName        [in]    Ĭ����ʾ�ļ���
    ��    ��: const String& strFilePathName       [out]    �ļ�ȫ·��
    ��    ��: vector<String>& vecStrFileName	  [out]    ȫ���ļ���
    ��    ��: BOOL bOpenStyle					  [in]    ������������Ǳ���
    ע    ��:��
    �� �� ֵ:String     �ļ�ȫ·��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL OpenMutiFileDlg( const String& strFilter, const String& strDefFileName, String& strFilePathName,
		 vector<String>& vecStrFileName, BOOL bOpenStyle = TRUE );

	/*=============================================================================
    �� �� ��: CheckTransferFile
    ��    ��: ��⴫��ȫ·�����ļ����ĺϷ���
    ��    ��: const String strFileFullPath    [in]     �������ļ�ȫ·��
    ��    ��: const String strCheckFileName   [in]     �������ļ��� 
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName );

	/*=============================================================================
    �� �� ��: GetFileSize
    ��    ��: �õ��ļ���С
    ��    ��: const String strFilePath    [in]     �ļ�ȫ·��
    ע    ��:��
    �� �� ֵ:u64 �ֽ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/02/01  1.0     ����ӡ    ����
    =============================================================================*/
	 u64 GetFileSize( const String& strFilePath );
 
	/*=============================================================================
    �� �� ��: RecusionMkDir
    ��    ��: �ݹ鴴��Ŀ¼�� ���Ŀ¼�Ѿ����ڻ��ߴ����ɹ�����TRUE
    ��    ��: CString strFolder        [in]    �������ļ���·��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL RecusionMkDir(CString strFolder);

	/*=============================================================================
    �� �� ��:SetLstSelItem
    ��    ��: �����б��ؼ���ѡ���У�Ĭ��ȥ��ѡ���
    ��    ��: const String& strLstWnd        [in]    �б���
	��    ��: IWndTree* pWndTree		     [in]    ��������
	��    ��: s32 nItemNo					 [in]    ѡ���к�
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/17  1.0     ����ӡ    ����
    =============================================================================*/
	 void SetLstSelItem( const String& strLstWnd, IWndTree* pWndTree = NULL, s32 nItemNo = -1 );

	 //�Ƿ�����ȷ�������ʽ
	 bool IsValidPWStr( CString szPWStr ) ;
	 //�Ƿ�����ȷ�Ļ᳡����
     bool IsValidNameStr( String strText );
     //�ж�ip�Ƿ��������ȡip�������ֵ
	 bool JudgeIp(char *szIP, IP_Struct::IpAdress_Struct *ipAdress);
     //�ж��Ƿ�ͬһ����
	 int IsSameNetworkSegment(char *szIPAdress, char *szIPAdresss1, char *szMask);

private:
	

};

#define  UIDATAMGR_PTR CUIDataMgr::GetSingletonPtr()

//��Ҫ������Ϣ
extern const  string g_stcMsgboxDlg;		//��ʾ������
extern const  string g_strMainFrame;		//cnsTool ������		
extern const  string g_strBasicInfoDlg;		//������Ϣ����		
extern const  string g_strCfgFrame;			//���ÿ��
extern const  string g_strCfgCnsDlg;		//���ÿ���е�cns����
extern const  string g_strCfgAudioPort;		//���ÿ���е���Ƶ���ý���
//extern const  String g_strCfgMixDlg;		//���ÿ���еĻ������ý���
extern const  String g_strCfgAudioDlg;		//���ÿ���е���Ƶ���ý���
extern const  string g_strCfgMainAudioDlg;   //���ÿ���е�����Ƶ���ý���
extern const  string g_strCfgDemonStrationDlg;   //���ÿ���е���ʾԴ���ý���
extern const  string g_strCfgAdjustImageDlg;   //���ÿ���е�ͼ��������ý���
extern const  String g_strRenameOptDlg;		//����������
extern const  string g_strCnsCfg ;        //CNS����

//extern const  string g_strDiagInfoDlg;		//��ϲ��Խ���
extern const  string g_strCfgDiagnosticFrame;  //��ϲ��Խ���
extern const  string g_strDiagInterfaceDlg;  //�ӿ���Ͻ���
extern const  string g_strNetDiagnosticDlg;  //������Ͻ���
extern const  string g_strNetPacketDlg;      //����ץ������
extern const  string g_strCentCfgFrame;	//�п���Ϣ����
extern const  string g_strDiagInTestInfo;	//������Խ���
extern const  string g_strDiagOutTestInfo;	//������Խ���
extern const  string g_strDiagTestFrame;	//��ϲ�����ʾ����
extern const  string g_strDiagStatistic;	//ͳ�ƽ���
extern const  String g_stcStrCfgNetMngDlg;	//�������ý���
extern const  String g_stcStrCfgNetSecurityDlg;  //���簲ȫ���ý���  
extern const  String g_stcStrRouteCfgDlg;	//·���������ý���
extern const  String g_stcStrNetMngOptDlg;	//���ܲ�������
extern const  String g_StrCameraDlg;		//������ڽ���
extern const  String g_strAddrbookExpDlg;	//��ַ������
extern const  String g_strCfgServerDlg;		//���ÿ���еķ���������
extern const  String g_strCfgEqDlg;			//���ÿ���еľ���������
extern const  String g_stcStrImpCommonDlg;	//�ϴ������룩ͨ�õ�������
extern const  String g_stcStrExpCommonDlg;	//���أ�������ͨ�õ�������
extern const  String g_strWarningDlg;		//�������½Ǿ�ʾ����
extern const  String g_strCfgCallSer;		//�������ý���
extern const  String g_strCfgAdvanceDlg;	//�߼����ý���
extern const  String g_strCentAirCondition;	//�пؿյ�����
extern const  String g_strCentCameraDlg;	//�п����������
extern const  String g_strCentLightDlg;		//�пصƹ����
extern const  String g_strCentDisplayDlg;	//�пص��ӻ�����
extern const  String g_strCentStatusMesDlg;	//�п�״̬��Ϣ����
extern const  String g_strCentCurtainDlg;	//�пش������ý���
extern const  String g_strCentDuoVideo;	//�п�˫�������ý���
extern const  String g_strCentMatrix;	//�п�˫�������ý���
extern const  String g_strCentSrceen;	//�п�˫�������ý���


//��Ҫ����
extern const  string g_strShmShow ; //��ʾ����, ���е��ø÷����Ĵ�����Ҫ��xml�ķ���������Ϊ "SchmShow" 
extern const  string g_strShmHide ; //���ط���, ���е��ø÷����Ĵ�����Ҫ��xml�ķ���������Ϊ "SchmHide"

#define  ADDRBOOK_FILE_PATH         "/usr/conf/"
#define  ADDRBOOK_FILE_NAME		    "kdvaddrbook.kdv"
#define  CNSLOG_FILE_PATH			"/usr/kdvlog/log/"
#define  CNSLOG_FILE_NAME			"cnlog.ini"
#define  CNSCONFIG_FILE_PATH		"/usr/conf/"
#define  CNSCONFIG_FILE_NAME		"cncfg.ini"
#define  CNSCONFIG_FILE_EXT_PATH	"/usr/"
#define  CNSCONFIG_FILE_NAME_ZERO	"0cncfg.ini"
#define  CNSCONFIG_FILE_NAME_ONE	"1cncfg.ini"
#define  CNSCONF_FILE_PATH			"/usr/bin/"
#define  CNSCAPTURE_FILE_PATH       "/ramdisk/"
#define  REMOTE_FILE_NAME           "/ramdisk/kdvcapture.pcap"
#define  CNS_T300E_TUMP_NAME        "tcpdump.t300e"	
#define  CAPTURE_FILE_NAME          "kdvcapture.pcap"			
#define  CNSUPGRADE_FILE_NAME		"tpcns.bin"
#define  CNSCAMERA_FILE_PATH		"/usr/conf/"
#define  CNSCAMERA_FILE_NAME		"cameracfg.ini"
#define  CNSSNAPSHOT_FILE_PATH		"download"
#define  CNSSNAPSHOT_FILE_NAME1		"snapshot0.jpg"
#define  CNSSNAPSHOT_FILE_NAME2		"snapshot1.jpg"
#define  CNSSNAPSHOT_FILE_NAME3		"snapshot2.jpg"
#define  CNSUPGRADE_NAME			"T300E.bin"
#define  CNSUPGRADE_NAME_Y			"T300E-y.bin"

#define  CAPTURE_FILE_MAX_SIZE      199*1024*1024

#define SOFTWARE_BOUNDARY_VERSION   "V1.1.6"         //ftp�û����������ٽ�汾
//#define  SOFTWARE_BETA_VERSION      6      //���û�������������ϰ汾��

#endif // !defined(AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_)