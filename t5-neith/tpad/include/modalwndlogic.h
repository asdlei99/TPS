/** @defgroup 模态弹窗
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016-9-5
 */
#pragma once

class CModalWndLogic : public CNotifyUIImpl, public Singleton<CModalWndLogic>
{
public:
	CModalWndLogic(void);
	~CModalWndLogic(void);

    static bool ShowModalWnd( LPCTSTR strText );
    void SetWndText( CString strText );
    void CloseModalWnd();
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

	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:
    static CString m_strText;
};

