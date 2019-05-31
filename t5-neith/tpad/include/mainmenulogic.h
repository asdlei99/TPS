/** @defgroup ���˵��߼���Ԫ 
 *  @version V1.1.5
 *  @author  Ф��Ȼ
 *  @date    2016.7.11
 */

#pragma once
class CMainMenuLogic : public CNotifyUIImpl, public Singleton<CMainMenuLogic>
{
public:
	CMainMenuLogic(void);
	~CMainMenuLogic(void);

protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);
	/** ����᳡���� 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnCnsManage(TNotifyUI& msg);
    /** ����пع��� 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnCenterCtrl(TNotifyUI& msg);
    /** ����ļ����� 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnFileManage(TNotifyUI& msg);
    /** �������� 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnBrowser(TNotifyUI& msg);
    /** ������ݻ��� 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnDataConf(TNotifyUI& msg);
    /** ����տ���ʾ 
    *  @param[in] 
	 *  @return 
	 */
    bool OnBtnWatchDual(TNotifyUI& msg);
    //����״̬
    bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//˫������״̬
	bool OnDualRecvStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
public:
	//����menu
	void UpdateMainMenu();
	APP_DECLARE_MSG_MAP()
private:
	HWND m_hWnd;     //g_strMainMenuDlg���
	bool m_bDual;
};

