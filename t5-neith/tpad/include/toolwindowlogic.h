/** @defgroup 会议提示弹窗
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015.1.5
 */
#pragma once

class CToolWindowLogic : public CNotifyUIImpl
{
public:
	CToolWindowLogic(void);
	~CToolWindowLogic(void);

    void ShowKeyboard();
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
	bool OnBtnPageChange(TNotifyUI& msg);

	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    APP_DECLARE_MSG_MAP()
private:
	bool m_bIsPrePage;
	bool m_bIsKeyBoardWnd;
	bool m_bLButtonDown;
	CPoint m_ptDown;
};

void ToolWindowreSet(bool bIsNextPage = false, bool bIsKeyBoard = false);