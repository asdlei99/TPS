/** @defgroup 会议提示信息界面
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015.1.5
 */
#pragma once

typedef struct tagConfMsg
{
	String strMsg;
	String strTime;

	tagConfMsg()
	{
		Clear();
	}

	void Clear()
	{
		strMsg = _T("");
		strTime = _T("");
	}

}TConfMsg;

class CConfMsgDlgLogic : public CNotifyUIImpl, public Singleton<CConfMsgDlgLogic>
{
public:
	CConfMsgDlgLogic(void);
	~CConfMsgDlgLogic(void);
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
	/** 点击地址簿条目
	*  @param[in] 消息
	*  @return 
	*/
	bool OnMsgListItemSelected(TNotifyUI& msg);
	
	/** 连接成功
	*  @param[in] 消息
	*  @return 
	*/
	bool OnConnectOk(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//更新显示出的列表
	void UpdateMsgList();

public:
	/** 添加通知消息
	*  @param[in] 消息
	*  @return 
	*/
	void AddMsg( CString strMsg, BOOL bShowNow = FALSE );

	APP_DECLARE_MSG_MAP()

private:
	CListUI      *m_pMsgList;

	vector<TConfMsg> m_vctMsg;//消息列表
	BOOL m_bLoginOK;

};


#define ShowPopMsg(p)\
{\
	CConfMsgDlgLogic::GetSingletonPtr()->AddMsg(p);\
}

#define ShowPopMsgNow(p)\
{\
	CConfMsgDlgLogic::GetSingletonPtr()->AddMsg(p, TRUE);\
}