/** @defgroup ������ʾ��Ϣ����
 *  @version V1.1.4
 *  @author  ��ӨӨ
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
	/** �����ַ����Ŀ
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnMsgListItemSelected(TNotifyUI& msg);
	
	/** ���ӳɹ�
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnConnectOk(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//������ʾ�����б�
	void UpdateMsgList();

public:
	/** ���֪ͨ��Ϣ
	*  @param[in] ��Ϣ
	*  @return 
	*/
	void AddMsg( CString strMsg, BOOL bShowNow = FALSE );

	APP_DECLARE_MSG_MAP()

private:
	CListUI      *m_pMsgList;

	vector<TConfMsg> m_vctMsg;//��Ϣ�б�
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