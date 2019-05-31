/** @defgroup ����ģ���߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.10
 */
#pragma once

class CConfTempLogic : public CNotifyUIImpl, public Singleton<CConfTempLogic>
{
public:
	CConfTempLogic(void);
	~CConfTempLogic(void);

	void TempCallFail();
	//����ˢ�°�ť
	void OnWaitRefreshOverTime();

    //��ȡ��ǰ���е�ģ������
    TTPAlias GetCallTempName();
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

	/** ʧȥ������Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
/*	bool OnKillFocus(TNotifyUI& msg);*/

	/** ����б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnConfTempItemClick(TNotifyUI& msg);

	/** ���ˢ�°�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRefresh(TNotifyUI& msg);
	
	/** ˢ���б� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRefreshConftempLst(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /** ѯ�ʻ���ģ������ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCnGetTempPwdCmd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ����״̬֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnConfStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** �ؼ�������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSearchEditChange(TNotifyUI& msg);

	/** ���ģ��ѡ��ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnTmpCall(TNotifyUI& msg);

	/** ���ȡ�����а�ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnNoticeBack(TNotifyUI& msg);
	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);

    bool OnHungupConfInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

public:
		/** ˢ���б� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateConfTempList();
	APP_DECLARE_MSG_MAP()

private:

	vector<TTPAlias>     m_vctConfTempList;                 //����ģ���б� 
	vector<TTPAlias>     m_vctSearchTempList;               //�������Ļ���ģ���б� 
	vector<TTPAlias>     m_vctShowTempList;                 //��ʾ�Ļ���ģ���б� 

	static const String m_strConfTempListItem;
	static const String m_strConfTempName;
	static const String m_strSeachEdit;                     //������edit
	static const String m_strBtnTmpCall;                    //ѡ��ť

    TTPAlias            m_tTPAlias;                         //��ǰ���е�ģ�壨��ʾ����ģ������ʱ��Ҫ�õ���

};