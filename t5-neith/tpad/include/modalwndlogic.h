/** @defgroup ģ̬����
 *  @version V1.1.4
 *  @author  ��ӨӨ
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

	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:
    static CString m_strText;
};

