/** @defgroup 用户管理单元
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.10
 */
#pragma once
typedef struct tagUserList
{
	CUserFullInfo UserFullInfo;
	bool bIsSel;
	tagUserList()
	{
		clear();
	}
	void clear()
	{
		UserFullInfo.Empty();
		bIsSel = false;
	}
}TUserList;


class CWBConfLogic : public CNotifyUIImpl
{
public:
	CWBConfLogic(void);
	~CWBConfLogic(void);
	    /**	 
    * 功能:  数据会议，会议名更新
    * @return   
    * @remarks 本地开会时，会议名为T300的名字，开启网呈会议以后，名字更新为会议名并结束当前白板会议
    */
    void UpdateWBConfName( CString strConfName );

    /**	 
    * 功能:  创建数据会议窗口，传入白板会议用户名
    * @return   
    * @remarks 白板会议用户名为当前TPAD客户端登陆时显示的名称
    */
    void CreatWBConfDlg(); 
	     /**	 
    * 功能:  TPAD修改白板ip配置
    * @return   
    * @remarks 
    */
    void SetDataServerInfoCmd( u32 dwIp ); 
	CString iptos( u32 dwIPAddr );
protected:
		/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	bool StartJVM();

	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnJoinWBConfNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnLeaveWBConfNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnNewConfCallReq(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnConfRoomNameNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnWBConfStartNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnsSetDataServerInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelfMakeCallCmdNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSetWBServerIpNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnsSetDataCnfNameNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	    /**	 
    * 功能:  加入数据会议
    * @return   
    * @remarks 
    */
    bool JoinWDConf(const IArgs& args);
    /**	 
    * 功能:  不加人数据会议
    * @return   
    * @remarks 	  
    */
    bool QuitJoinWDConf(const IArgs& args);//不加人数据会议
    /**	 
    * 功能:  通知cns是否加入数据会议
    * @return   
    * @remarks 	  
    */
    void JoinNewConfRsp( BOOL bIsJoinWBConf );

	APP_DECLARE_MSG_MAP()
private:

	BOOL m_bCreateDataConfDlg;//是否已经创建了数据会议 dyy 2014年4月28日 
	BOOL m_bInDataConf;//是否已经加入了数据会议 dyy 2014年4月28日 
	BOOL m_bIsSelfStartDataConf;//是否本端开始的数据会议 dyy 2014年4月28日 
	BOOL m_bIsSelfStartCncConf;//是否本端开始的视频会议 dyy 2014年5月27日 

	CString m_strConfRoomName;//会场名
	CString m_strConfName;//会议名

	u32  m_dwWBIp;//白板服务器连接IP dyy 2014-5-16

	CString m_strLastConfName; //最后一次链接会议时的会议名
	//WCHAR *m_pwszUserName;//会场名
	CString m_strUserName;
	bool m_bIsLoginWBServer;//是否连接到数据会议服务器 2014-10-20 


	JNIEnv * m_jni_env;
	JavaVM * m_jni_jvm;

};