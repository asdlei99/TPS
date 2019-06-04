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

    /*功  能  初始化lib库环境
	参    数  dwAppID： 需要的appID
	返 回 值   
	说    明  使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u32 dwAppID );

	//获取接口 
	virtual u16 TpadGetInterface(CTpadConfCtrlIF **ppCtrl);
    /*===========================================================================
      函 数 名： ConnectCns
      功    能： 连接Cns
      算法实现： 
      全局变量： 
      参    数： u32 dwIP    要连接的终端IP 本机序
                 u32 dwPort  连接端口
                 const CString &strUser   连接的用户名
                 const CString &strPwd    用户密码
                 achVersion  tpad版本号
      返 回 值： u16 
    ===========================================================================*/
	virtual u16 ConnectCns(u32 dwIP, u32 dwPort, LPSTR strUser,
		LPSTR strPwd, s8* achVersion, BOOL32 bConnect = TRUE);

    virtual u16 DisconnectCns();
	virtual BOOL IsConnectedCns();
	 /** 功能  获取本地ip
	 *  @param[in] 
	 *  @return  本地ip 
	 *  @remarks 
	 */
    u32 GetLocalHostIP(){ return m_dwLocalIP; }

	/** 
	* 功能  	获取ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPFtpInfo GetCnFtpInfo(){ return m_tTPFtpInfo; }
    /** 
	* 功能  	设置ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo);

	u32 GetLoginIp(){ return m_dwCnsIp; }

	TTPTPadVerInfo GetTPadVerInfo(){ return m_tVerInfo; }

    void NotifyLoginUser();
	
    /**
	* 功能:  TPad响应Home键通知
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    void TPadHomeKeyNty();
	 /**
	* 功能:  开中控
	* @return 
	* @remarks 
	*/
    void OpenCenterCtrl();
	 /**
	* 功能:  开系统设置
	* @return 
	* @remarks 
	*/
    void OpenSysConfig();
     /**功能:  打开会场管理
	* @return 
	* @remarks 
	*/
    void OpenCnsManage();
    /**
	* 功能:  数据会议创建通知
	* @return 
	* @remarks  bIsSelfStart 是否为本端开启
	*/
    void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess  );
	/**
    * 功能:	通知cnc断链
	* @param [in]  bActiveExit 是否主动退出
	* @remarks
	*/
    void NotifyCnsDisconnect( BOOL bActiveExit );
	//获得密码输错次数
	TLoginRet GetLoginRet(){ return m_tLoginRet; }

protected:
    // 初始化OSP 
	u16 InitializeOsp();
    // 构建消息映射表 
    void BuildEventsMap(); 	
    
    virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

    //消息处理
    void OnLinkBreak(const CMessage& cMsg);
	void OnCnsLoginRsp(const CMessage& cMsg);
    void OnTpadUpdateCmd(const CMessage& cMsg);
    void OnLoginByOtherNotify(const CMessage& cMsg);
    void OnCentreSleepNty(const CMessage& cMsg);
    void OnCncSetSystemName( const CMessage& cMsg );
	void DisConnectTpad( const CMessage& cMsg );


    //判断是否可进行链接(cnc、中控均以连上Tpad)
    BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList );


    //本地开启视频会议状态记录 
    void OnSelfMakeCallCmd( const CMessage &cMsg );

	//升级T300消息 
    void OnT300UpdateNty( const CMessage &cMsg );
	//是否升级T300回应
	void T300UpdateInd( BOOL bIsUpT300 );
	//ftp账号密码获取
	void OnCnFtpInfoNty(const CMessage& cMsg);
    //ftp账号密码配置通知
    void OnCnFtpInfoRsp(const CMessage& cMsg);

	void OnCncNoReconnectNty(const CMessage& cMsg);

private:

	CTPadSession *m_pTpadSession;

	BOOL32 m_bInitOsp;
    u32	   m_dwCnsIp;	  //连接的CNS的IP
    u32    m_dwLocalIP;   //本地ip
	CLoginRequest   m_cUser; //连接时登录的用户	
	TTPTPadVerInfo m_tVerInfo;//升级版本信息

	// 各个功能类接口类
	CTpadConfCtrlIF *m_pConfCtrlIF;

	TTPFtpInfo      m_tTPFtpInfo;

	TLoginRet       m_tLoginRet;

};

#endif // !defined(AFX_TPADSESSION_H__C5B58BB4_5F50_4D9C_9277_F5E9847D62BA__INCLUDED_)
