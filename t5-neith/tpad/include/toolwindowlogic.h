/** @defgroup ������ʾ����
 *  @version V1.1.4
 *  @author  ��ӨӨ
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
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
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