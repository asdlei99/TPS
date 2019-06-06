// mainframelogic.h: interface for the CMainFrameLogic class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRAMELOGIC_H__D2D7F34D_34EC_4A78_9C9F_4A11AD89D464__INCLUDED_)
#define AFX_MAINFRAMELOGIC_H__D2D7F34D_34EC_4A78_9C9F_4A11AD89D464__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrameLogic : public CNotifyUIImpl, public Singleton<CMainFrameLogic> 
{
public:
	CMainFrameLogic();
	~CMainFrameLogic();

	bool SetTitle( LPCTSTR lpstrTitle );//������ʾ���� dyy 
	bool SetTitlePic( LPCTSTR lpstrTitle );//���ñ�����ͼƬ dyy
	/** ���ñ�����Tab 
	*  @param[in] bShow ��ʾ/����  lpstrDlgName �����Ĵ�����
	*  @return �Ƿ�ɹ�
	*/
	bool SetTitleTab( bool bShow, LPCTSTR lpstrDlgName = _T("") );
	//������ʾ��ťȡ����ʾ�ŷ������
	void HideTipBtn();
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

	/** �ر�Ӧ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnQuit(TNotifyUI& msg);
	/** �˳�
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnExit(TNotifyUI& msg);

	/** ����
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnBack(TNotifyUI& msg);

	/** ���������Tab 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnTabTitleLeft(TNotifyUI& msg);
	bool OnTabTitleRight(TNotifyUI& msg);
	//������� ��Ӧ��Ŀ�ظ�δѡ״̬
	bool OnContainerClick(TNotifyUI& msg);

	//bool OnConnetcted(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tpad������ʾ�п�
	bool OnTpadShowCenterCtrlNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tpad����ϵͳ����
	bool OnTpadShowSysConfigNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //tpad���û᳡����
    bool OnTpadShowCnsManageNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//tpad���home�� 2015-10-8 
	bool OnTpadHomeKeyNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tpad��˫����ʼ�������ţ��Զ�����cnc����
	bool OnTpadShowDual(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�пش���
	bool OnCentreSleepNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);	
	//UMS������ʾ
	bool OnUmsReasonInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����Ϣ����
	 *  @param[in] 
	 *  @return 
	 */
	bool OnShowMsgNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
		/** �����Ϣ֪ͨ��ť
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnTip(TNotifyUI& msg);
	/** ����Զ���¼��ť
	 *  @param[in] 
	 *  @return 
	 */
	bool OnCheckAutoLogin(TNotifyUI& msg);
	bool OnCheckRemPassWord(TNotifyUI& msg);
	//���ӳɹ� ��ʼˢ��ʱ��
	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�᳡���ָ���
	bool OnCnsInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//���ն�������ϯ�Ƿ�׼��������
	bool OnJoinConfReqChair( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//���ݻ���״̬֪ͨ
	bool OnWBConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnNewConfCallReq( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//tpad��¼ʱ�û���Ϣ��¼
	bool OnTpadLoginInfoNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
    //��Ļ�ֱ��ʱ仯
    bool OnDisplayChange( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnCnsDisconnectNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDisconnectClear( WPARAM wParam, LPARAM lParam, bool& bHandle );
    //����״̬�仯
    bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
public:
	/** ������Ϣ֪ͨ��ťͼƬ
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateMsgImg();
	/** ����ʱ����ʾ
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateTime();
	//ini�ļ�·��
	CString GetIniFilePath();

	//���µ�¼������ʾ��Ϣ
	void UpdateLoginShowInfo();

	APP_DECLARE_MSG_MAP()
		
private:
	CWndShadow m_cWndShadow;
	BOOL m_bMsgOn;   //��ϢͼƬ�Ƿ����
	String m_strLastWnd;//����Ϣ��ʾʱ����¼��һ�β����Ĵ��ڣ�������أ����ش˴���

	bool m_bIsPadShowCenterOrSys;//�Ƿ���tpad������ʾ���п� dyy 2015-5-26 && �Ƿ���tpad������ϵͳ����
};

#endif // !defined(AFX_MAINFRAMELOGIC_H__D2D7F34D_34EC_4A78_9C9F_4A11AD89D464__INCLUDED_)