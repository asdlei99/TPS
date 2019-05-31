/** @defgroup 系统升级
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016-9-25
 */
#pragma once

enum EmDownState
{
	emDownNo = (u32)0,   //未进行文件下载操作
	emDowning,			 //文件下载中
	emDownEnd,			 //文件下载成功
	emDownFail,			 //文件下载失败
};

class CTPadUpdateLogic : public CNotifyUIImpl, public Singleton<CTPadUpdateLogic>
{
public:
	CTPadUpdateLogic(void);
	~CTPadUpdateLogic(void);
	//解压文件
	bool UnZip();
protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	bool OnDestroy(TNotifyUI& msg);

	bool OnBtnOk(TNotifyUI& msg);
	bool OnBtnCancel(TNotifyUI& msg);

	bool OnLoadTPadProgress( WPARAM wParam, LPARAM lParam, bool& bHandle );

    //开启ftp反馈
    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//下载文件
	bool DownLoadFile();
    bool BeginDownload();

	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:

	CFtpCtrl         m_cFtp;
	EmFtpStatus      m_emFtpStatus;
	TTPTPadVerInfo   m_tTPadVerInfo;   
	int              m_nProgress;        //下载进度
	CString          m_strSavePath;      //下载文件保存路径
	EmDownState      m_emDownState;		 //文件下载状态
    bool             m_bIsWaitForFtp;    //等待开启ftp后升级
};
