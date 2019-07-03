/** @defgroup tpad的公共接口 
 *  @version V1.1.5
 *  @author  肖楚然
 *  @date    2016.6.28
 */

#pragma once

#include "tpadlib.h"
#include "cncstruct.h"

class CCommonInterface
{
public:

    ~CCommonInterface(void);


	//TMainMenuInfo &tItemInfo应该是全局变量，或者是类的成员函数 
    void OpenExe( TMainMenuInfo tItemInfo );

	BOOL Is64BitSystem();
	//根据进程ID，显示对应的窗口，返回该窗口的句柄
    HWND ShowWndByProID( u32 dwProcID );

	//退出系统	
	void ExitWindowsOS( EM_OSType emOSType );

	//判断目录是否存在
	BOOL ExistDir( const CString strDir );
	
	//创建目录
    BOOL CreateDir( CString strDir );

	//获得U盘列表
	BOOL GetUDiskList( vector<CString>& vctUDisk );

	//查找第一个存在指定文件名strFileName的U盘的盘符
	BOOL GetFirstUDiskNameByFileName( CString& strPartName, const CString& strFileName, BOOL& bHaveUDisk );

	//文件是否存在
	BOOL IsFileExist( LPCTSTR lpszFilePath );

	//判断指定的U盘是否插入了设备
	BOOL IsUDiskInsert( int nDiskNo );

	/**
	* 功能:  当前登录的用户是否是管理员
	* @return  TRUE 是管理员，FALSE 一般用户
	*/
	BOOL IsManagerUser();

    DWORD GetFolderFilesCount( CString strFolderPath );
    
    DWORD GetFolderFilesCount( CString strFolderPath, vector<TFileItem>& tListFileInfo );
    
    DWORD GetUDiskList( vector<TFileItem>& vctUDisk );

    BOOL IsSysWin8() { return m_bIsWin8; }
    void GetSysVersion( OSVERSIONINFOEX& osvi );

	//请求码流
    u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const;

    u16 StopDualCodeStream() const;
	
    u16 ReqKeyFrame( BOOL32 bForce = TRUE ) const;

	TTPCnMediaTransPort GetVedioTransAddr() const  ;

    TTPCnMediaTransPort GetAudioTransAddr() const  ;	

	BOOL32 IsInConf( TCMSConf *pConf = NULL );

    /**
	* 功能:  获取本地cns会议状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

	//调出软键盘
	void ShowKeyboard();

	/**
	* 功能:	获取登录返回结果
	* @return  
    */
	u16 GetLoginRet(TLoginRet& tLoginRet) ;

public:
    //-----tpadlib业务相关-------------
    /**
    * 功  能	创建会话，包括Ums和Cns两个
    * @return u16 成功返回0;失败返回非0错误码 
    */
	void CreateSession();

    /**
    * 功  能	销毁会话，包括Ums和Cns两个
    * @return u16 成功返回0;失败返回非0错误码 
    */
	void DesdroySession();

    /**
    * 功能   连接到CNS
    * @param [in]  dwIP	被连接UMS的IP地址，主机序
    * @param [in]  pStrUserName 用户名	
    * @param [in]  pStrPswd	密码
    * @return u16 成功返回0;失败返回非0错误码 
    */
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 
    u16 Connect( LPSTR pcIpv6, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd );

    /**
    * 功能:	断开与CNS的连接
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	在没有连接到CNS时调用此方法，不起任何作用
	*/
	u16 DisConnect() ;

    u16 LinkCns();

    /**
    * 功能:	是否连接上cns
    * @return 成功返回0,失败返回非0错误码
    */ 
	BOOL32 IsConnectCns();

    /**
    * 功能:	重连cns
    * @remarks 用于网络断开后重连
    */ 
    void ReConnectCns();

    /**
    * 功能:	获取TPad版本号
	* @return
	* @remarks
	*/
    void GetTPadVersion( s8 achVersion[MAX_DEVICEVER_LEN] );

	/**
	* 功能:	获取本地 的IP 
	* @return  u32  IP
    */
	u16 GetLocalIP( u32 & IP ) ;

    /**
	* 功能:	获取系统版本 
	* @return
    */
    void  GetWindowsSysVersion();

    /**
	* 功能:	结束进程 
	* @return
    */
    void  KillProcess( LPCSTR pszWindowTitle );

    /**
    * 功能:	是否可以进行链接(中控、cnc均启动完毕并链接到Tpad上)
	* @return
	* @remarks
	*/
    BOOL32 IsReadyLogin( vector<TNodeInfo>&vctNodeList );
	
    void TPadHomeKeyNty();
	//B4版本调出中控
	void OpenCenterCtrl();
	//B5版本调出cnc系统设置
	void OpenSysConfig();
    //调出cnc
    void OpenCnsManage();
    /**
	* 功能:	白板会议加入、创会成功Nty，发消息给其他客户端
	* @return  bIsSelfStart 是否是自己开启的会议  
    *          bIsSuccess   是否开启成功
    */    
    void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess );


    /**
	* 功能:	Tpad设置ip通知cns
	* @return  u32  IP
    */    
    void SetDataServerInfoCmd( u32 dwIp );    

    /**
	* 功能:	通知cns是否加入数据会议
	* @return   BOOL bIsJoinWBConf
    */
    void JoinNewConfRsp( BOOL bIsJoinNewConf );

	/**
    * 功能:	设置TPad当前是否正在接收演示
	* @return
	* @remarks
	*/
    void SetReceiveDual( BOOL bDual );
    BOOL IsReceiveDual();

    TLoginInfo GetLoginInfo() { return  m_tLoginInfo;};

    /**
    * 功能:	设置TPad当前是否在自动登陆
	* @return
	* @remarks
	*/
    void SetAutoLogin( BOOL bAuto );
    BOOL IsAutoLogin();
    
    //数据会议状态通知
    void WBConfStateNty( BOOL bIsInWBConf );
	//是否升级T300回应
    void T300UpdateInd( BOOL bIsUpT300 );
	//获取版本信息
	u16 GetTPadVerInfo( TTPTPadVerInfo &tTPTPadVerInfo );

	//获取ftp信息
	u16 GetCnFtpInfo(TTPFtpInfo &tTPFtpInfo);
    //设置ftp信息
    u16 SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo);

	//白板信息获取
	u16 GetWBCnsConfStatus( TTPCnsConfStatus &tTPCnsConfStatus );
	u16 GetDataConfInfo( TTPDataConfInfo &tTPDataConfInfo );
	u16 GetWBCnsInfo( TTPCnsInfo &tTPCnsInfo );

	/**
    * 功能:	通知cnc断链消息
	* @param [in]  bActiveExit 是否主动退出
	* @remarks
	*/
	void NotifyCnsDisconnect( BOOL bActiveExit );
public:	
	/** 获取接口指针 */
	static CCommonInterface* GetCommIF();

	/**销毁接口指针 */
    void DestroyCommIF();

		/** 获取内嵌的窗口句柄
	*   @return HWND 返回窗口句柄 
	*/
	HWND GetRecvWnd(){ return m_hRecvWnd;};
private:
    CCommonInterface(void);
    static  CCommonInterface*  m_pMySelf;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    HWND                 m_hRecvWnd;         // 内嵌接收消息的窗口
    WNDPROC              m_wndprocOld;       // 系统窗口过程

private:

		CTPadSessionIF   *m_pTPadSession;      //cns会话
		CTpadConfCtrlIF   *m_pTpadConfCtrl;   //会议控制 
		
		TLoginInfo        m_tLoginInfo;

		OSVERSIONINFOEX   m_osvi;             //windows系统版本
		BOOL              m_bIsWin8;          //是否win8及以上
		BOOL              m_bReceiveDual;     //是否正在接收演示
        BOOL              m_bAutoLogin;       //是否在自动登陆
		TMainMenuInfo	  m_tItemInfo;//当前控制的item
};


#define ComInterface  CCommonInterface::GetCommIF()
