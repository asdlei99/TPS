// tpadsession.h: interface for the CTPadSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_)
#define AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tpadsessionif.h"
#include "tpadmsgdriver.h"
#include "msgtransdriver.h"
#include "usermanage.h"
#include "tpadconfctrlif.h"

class CTPadSession : public CTPadSessionIF,
                     public CTPadMsgDriver
{
public:
	CTPadSession();
	virtual ~CTPadSession();

    /*��  ��  ��ʼ��lib�⻷��
	��    ��  dwAppID�� ��Ҫ��appID
	�� �� ֵ   
	˵    ��  ʹ�������ӿ�֮ǰ������øýӿ�*/ 
	virtual void InitEnv( u32 dwAppID );

	//��ȡ�ӿ� 
	virtual u16 TpadGetInterface(CTpadConfCtrlIF **ppCtrl);
    /*===========================================================================
      �� �� ���� ConnectCns
      ��    �ܣ� ����Cns
      �㷨ʵ�֣� 
      ȫ�ֱ����� 
      ��    ���� u32 dwIP    Ҫ���ӵ��ն�IP ������
                 u32 dwPort  ���Ӷ˿�
                 const CString &strUser   ���ӵ��û���
                 const CString &strPwd    �û�����
                 achVersion  tpad�汾��
      �� �� ֵ�� u16 
    ===========================================================================*/
	virtual u16 ConnectCns(u32 dwIP, u32 dwPort, LPSTR strUser,
		LPSTR strPwd, s8* achVersion, BOOL32 bConnect = TRUE);

    virtual u16 DisconnectCns();
	virtual BOOL IsConnectedCns();
	 /** ����  ��ȡ����ip
	 *  @param[in] 
	 *  @return  ����ip 
	 *  @remarks 
	 */
    u32 GetLocalHostIP(){ return m_dwLocalIP; }

	/** 
	* ����  	��ȡftp��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPFtpInfo GetCnFtpInfo(){ return m_tTPFtpInfo; }
    /** 
	* ����  	����ftp��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo);

	u32 GetLoginIp(){ return m_dwCnsIp; }

	TTPTPadVerInfo GetTPadVerInfo(){ return m_tVerInfo; }

    void NotifyLoginUser();
	
    /**
	* ����:  TPad��ӦHome��֪ͨ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    void TPadHomeKeyNty();
	 /**
	* ����:  ���п�
	* @return 
	* @remarks 
	*/
    void OpenCenterCtrl();
	 /**
	* ����:  ��ϵͳ����
	* @return 
	* @remarks 
	*/
    void OpenSysConfig();
     /**����:  �򿪻᳡����
	* @return 
	* @remarks 
	*/
    void OpenCnsManage();
    /**
	* ����:  ���ݻ��鴴��֪ͨ
	* @return 
	* @remarks  bIsSelfStart �Ƿ�Ϊ���˿���
	*/
    void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess  );
	/**
    * ����:	֪ͨcnc����
	* @param [in]  bActiveExit �Ƿ������˳�
	* @remarks
	*/
    void NotifyCnsDisconnect( BOOL bActiveExit );
	//�������������
	TLoginRet GetLoginRet(){ return m_tLoginRet; }

protected:
    // ��ʼ��OSP 
	u16 InitializeOsp();
    // ������Ϣӳ��� 
    void BuildEventsMap(); 	
    
    virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

    //��Ϣ����
    void OnLinkBreak(const CMessage& cMsg);
	void OnCnsLoginRsp(const CMessage& cMsg);
    void OnTpadUpdateCmd(const CMessage& cMsg);
    void OnLoginByOtherNotify(const CMessage& cMsg);
    void OnCentreSleepNty(const CMessage& cMsg);
    void OnCncSetSystemName( const CMessage& cMsg );
	void DisConnectTpad( const CMessage& cMsg );


    //�ж��Ƿ�ɽ�������(cnc���пؾ�������Tpad)
    BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList );


    //���ؿ�����Ƶ����״̬��¼ 
    void OnSelfMakeCallCmd( const CMessage &cMsg );

	//����T300��Ϣ 
    void OnT300UpdateNty( const CMessage &cMsg );
	//�Ƿ�����T300��Ӧ
	void T300UpdateInd( BOOL bIsUpT300 );
	//ftp�˺������ȡ
	void OnCnFtpInfoNty(const CMessage& cMsg);
    //ftp�˺���������֪ͨ
    void OnCnFtpInfoRsp(const CMessage& cMsg);

	void OnCncNoReconnectNty(const CMessage& cMsg);

private:

	CTPadSession *m_pTpadSession;

	BOOL32 m_bInitOsp;
    u32	   m_dwCnsIp;	  //���ӵ�CNS��IP
    u32    m_dwLocalIP;   //����ip
	CLoginRequest   m_cUser; //����ʱ��¼���û�	
	TTPTPadVerInfo m_tVerInfo;//�����汾��Ϣ

	// ����������ӿ���
	CTpadConfCtrlIF *m_pConfCtrlIF;

	TTPFtpInfo      m_tTPFtpInfo;

	TLoginRet       m_tLoginRet;

};

#endif // !defined(AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_)
