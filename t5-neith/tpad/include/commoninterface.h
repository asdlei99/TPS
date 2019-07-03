/** @defgroup tpad�Ĺ����ӿ� 
 *  @version V1.1.5
 *  @author  Ф��Ȼ
 *  @date    2016.6.28
 */

#pragma once

#include "tpadlib.h"
#include "cncstruct.h"

class CCommonInterface
{
public:

    ~CCommonInterface(void);


	//TMainMenuInfo &tItemInfoӦ����ȫ�ֱ�������������ĳ�Ա���� 
    void OpenExe( TMainMenuInfo tItemInfo );

	BOOL Is64BitSystem();
	//���ݽ���ID����ʾ��Ӧ�Ĵ��ڣ����ظô��ڵľ��
    HWND ShowWndByProID( u32 dwProcID );

	//�˳�ϵͳ	
	void ExitWindowsOS( EM_OSType emOSType );

	//�ж�Ŀ¼�Ƿ����
	BOOL ExistDir( const CString strDir );
	
	//����Ŀ¼
    BOOL CreateDir( CString strDir );

	//���U���б�
	BOOL GetUDiskList( vector<CString>& vctUDisk );

	//���ҵ�һ������ָ���ļ���strFileName��U�̵��̷�
	BOOL GetFirstUDiskNameByFileName( CString& strPartName, const CString& strFileName, BOOL& bHaveUDisk );

	//�ļ��Ƿ����
	BOOL IsFileExist( LPCTSTR lpszFilePath );

	//�ж�ָ����U���Ƿ�������豸
	BOOL IsUDiskInsert( int nDiskNo );

	/**
	* ����:  ��ǰ��¼���û��Ƿ��ǹ���Ա
	* @return  TRUE �ǹ���Ա��FALSE һ���û�
	*/
	BOOL IsManagerUser();

    DWORD GetFolderFilesCount( CString strFolderPath );
    
    DWORD GetFolderFilesCount( CString strFolderPath, vector<TFileItem>& tListFileInfo );
    
    DWORD GetUDiskList( vector<TFileItem>& vctUDisk );

    BOOL IsSysWin8() { return m_bIsWin8; }
    void GetSysVersion( OSVERSIONINFOEX& osvi );

	//��������
    u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const;

    u16 StopDualCodeStream() const;
	
    u16 ReqKeyFrame( BOOL32 bForce = TRUE ) const;

	TTPCnMediaTransPort GetVedioTransAddr() const  ;

    TTPCnMediaTransPort GetAudioTransAddr() const  ;	

	BOOL32 IsInConf( TCMSConf *pConf = NULL );

    /**
	* ����:  ��ȡ����cns����״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

	//���������
	void ShowKeyboard();

	/**
	* ����:	��ȡ��¼���ؽ��
	* @return  
    */
	u16 GetLoginRet(TLoginRet& tLoginRet) ;

public:
    //-----tpadlibҵ�����-------------
    /**
    * ��  ��	�����Ự������Ums��Cns����
    * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    */
	void CreateSession();

    /**
    * ��  ��	���ٻỰ������Ums��Cns����
    * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    */
	void DesdroySession();

    /**
    * ����   ���ӵ�CNS
    * @param [in]  dwIP	������UMS��IP��ַ��������
    * @param [in]  pStrUserName �û���	
    * @param [in]  pStrPswd	����
    * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    */
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 
    u16 Connect( LPSTR pcIpv6, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd );

    /**
    * ����:	�Ͽ���CNS������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	��û�����ӵ�CNSʱ���ô˷����������κ�����
	*/
	u16 DisConnect() ;

    u16 LinkCns();

    /**
    * ����:	�Ƿ�������cns
    * @return �ɹ�����0,ʧ�ܷ��ط�0������
    */ 
	BOOL32 IsConnectCns();

    /**
    * ����:	����cns
    * @remarks ��������Ͽ�������
    */ 
    void ReConnectCns();

    /**
    * ����:	��ȡTPad�汾��
	* @return
	* @remarks
	*/
    void GetTPadVersion( s8 achVersion[MAX_DEVICEVER_LEN] );

	/**
	* ����:	��ȡ���� ��IP 
	* @return  u32  IP
    */
	u16 GetLocalIP( u32 & IP ) ;

    /**
	* ����:	��ȡϵͳ�汾 
	* @return
    */
    void  GetWindowsSysVersion();

    /**
	* ����:	�������� 
	* @return
    */
    void  KillProcess( LPCSTR pszWindowTitle );

    /**
    * ����:	�Ƿ���Խ�������(�пء�cnc��������ϲ����ӵ�Tpad��)
	* @return
	* @remarks
	*/
    BOOL32 IsReadyLogin( vector<TNodeInfo>&vctNodeList );
	
    void TPadHomeKeyNty();
	//B4�汾�����п�
	void OpenCenterCtrl();
	//B5�汾����cncϵͳ����
	void OpenSysConfig();
    //����cnc
    void OpenCnsManage();
    /**
	* ����:	�װ������롢����ɹ�Nty������Ϣ�������ͻ���
	* @return  bIsSelfStart �Ƿ����Լ������Ļ���  
    *          bIsSuccess   �Ƿ����ɹ�
    */    
    void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess );


    /**
	* ����:	Tpad����ip֪ͨcns
	* @return  u32  IP
    */    
    void SetDataServerInfoCmd( u32 dwIp );    

    /**
	* ����:	֪ͨcns�Ƿ�������ݻ���
	* @return   BOOL bIsJoinWBConf
    */
    void JoinNewConfRsp( BOOL bIsJoinNewConf );

	/**
    * ����:	����TPad��ǰ�Ƿ����ڽ�����ʾ
	* @return
	* @remarks
	*/
    void SetReceiveDual( BOOL bDual );
    BOOL IsReceiveDual();

    TLoginInfo GetLoginInfo() { return  m_tLoginInfo;};

    /**
    * ����:	����TPad��ǰ�Ƿ����Զ���½
	* @return
	* @remarks
	*/
    void SetAutoLogin( BOOL bAuto );
    BOOL IsAutoLogin();
    
    //���ݻ���״̬֪ͨ
    void WBConfStateNty( BOOL bIsInWBConf );
	//�Ƿ�����T300��Ӧ
    void T300UpdateInd( BOOL bIsUpT300 );
	//��ȡ�汾��Ϣ
	u16 GetTPadVerInfo( TTPTPadVerInfo &tTPTPadVerInfo );

	//��ȡftp��Ϣ
	u16 GetCnFtpInfo(TTPFtpInfo &tTPFtpInfo);
    //����ftp��Ϣ
    u16 SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo);

	//�װ���Ϣ��ȡ
	u16 GetWBCnsConfStatus( TTPCnsConfStatus &tTPCnsConfStatus );
	u16 GetDataConfInfo( TTPDataConfInfo &tTPDataConfInfo );
	u16 GetWBCnsInfo( TTPCnsInfo &tTPCnsInfo );

	/**
    * ����:	֪ͨcnc������Ϣ
	* @param [in]  bActiveExit �Ƿ������˳�
	* @remarks
	*/
	void NotifyCnsDisconnect( BOOL bActiveExit );
public:	
	/** ��ȡ�ӿ�ָ�� */
	static CCommonInterface* GetCommIF();

	/**���ٽӿ�ָ�� */
    void DestroyCommIF();

		/** ��ȡ��Ƕ�Ĵ��ھ��
	*   @return HWND ���ش��ھ�� 
	*/
	HWND GetRecvWnd(){ return m_hRecvWnd;};
private:
    CCommonInterface(void);
    static  CCommonInterface*  m_pMySelf;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND                 m_hRecvWnd;         // ��Ƕ������Ϣ�Ĵ���
    WNDPROC              m_wndprocOld;       // ϵͳ���ڹ���

private:

		CTPadSessionIF   *m_pTPadSession;      //cns�Ự
		CTpadConfCtrlIF   *m_pTpadConfCtrl;   //������� 
		
		TLoginInfo        m_tLoginInfo;

		OSVERSIONINFOEX   m_osvi;             //windowsϵͳ�汾
		BOOL              m_bIsWin8;          //�Ƿ�win8������
		BOOL              m_bReceiveDual;     //�Ƿ����ڽ�����ʾ
        BOOL              m_bAutoLogin;       //�Ƿ����Զ���½
		TMainMenuInfo	  m_tItemInfo;//��ǰ���Ƶ�item
};


#define ComInterface  CCommonInterface::GetCommIF()
