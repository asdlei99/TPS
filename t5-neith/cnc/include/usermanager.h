/** @defgroup �û�����Ԫ
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.10
 */
#pragma once
typedef struct tagUserList
{
	CUserFullInfo UserFullInfo;
	bool bIsSel;
	tagUserList()
	{
		clear();
	}
	void clear()
	{
		UserFullInfo.Empty();
		bIsSel = false;
	}
}TUserList;


class CUserManagerLogic : public CNotifyUIImpl
{
public:
	CUserManagerLogic(void);
	~CUserManagerLogic(void);

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
	bool OnUserItemClick(TNotifyUI& msg);

	/** ���ˢ�°�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRefresh(TNotifyUI& msg);
	/** ���ˢ�°�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRefreshUserLst(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �û���Ϣ�޸���Ӧ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUserModifyRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ˢ���û��б� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateUserLst();
	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSearchEditChange(TNotifyUI& msg);

	/** ����û���Ϣ�޸İ�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnModifyUser(TNotifyUI& msg);
	/** ���ѡ����Ŀ��ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckItemSel(TNotifyUI& msg);
	/** ���ȡ���޸İ�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelUserSet(TNotifyUI& msg);
	/** ����޸ı��水ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSaveUserSet(TNotifyUI& msg);
	/** ������ذ�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** ����˳���ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	/** ���ȫѡ��ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSelAll(TNotifyUI& msg);
	/** �������û���ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnAdd(TNotifyUI& msg);
	/** ���ɾ���û���ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnDel(TNotifyUI& msg);
	/** �����ʾ��ѡ�û��б�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckClearSel(TNotifyUI& msg);
	/** �������Ĭ�����밴ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIfSetDefaultPassword(TNotifyUI& msg);
	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);

	bool OnBtnCancelUserPasswd( TNotifyUI& msg );

	bool OnBtnSaveUserPasswd( TNotifyUI& msg );

	bool OnUserPasswdSetEditSetFocus( TNotifyUI& msg );

	bool OnUserPasswdSetEditTextChange( TNotifyUI& msg );

	bool OnUserPasswdSetEditKillFocus( TNotifyUI& msg );

	bool OnCheckUserPasswdSetEditKillFocus( TNotifyUI& msg );

	bool OnNewUserPasswdEditSetFocus( TNotifyUI& msg );

	bool OnNewUserPasswdEditTextChange( TNotifyUI& msg );

	bool OnNewUserPasswdEditKillFocus( TNotifyUI& msg );

	bool OnCheckUserPasswdEditKillFocus( TNotifyUI& msg );

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool savePassWord( );

    void UpdatePasswordTime();//�������밲ȫ����ʱ��
	APP_DECLARE_MSG_MAP()
private:

	TplArray<CUserFullInfo>  m_pArrayUserList;        //�û��б� 
	TplArray<CUserFullInfo>  m_pArrayUserSelLst;	  //��ѡ�û��б� 
	static const String m_strUserList;       //�û��б�  
	static const String m_strUserListItem;   //�û��б���Ŀ
	static const String m_strUserItemName;   //�û����� 
	static const String m_strSeachEdit;	     //������edit
	static const String m_strBtnUserSet;     //�޸��û���Ϣ��ť
	static const String m_strCheckBoxItemSel;//�û�ѡ�а�ť
	CUserFullInfo       m_selUser;                 //��ǰѡ����û�
	EM_NETMNGOPT_TYPE    m_emModifyType;            //���޸��û�  ���� �½��û�
	bool m_bIsSetDefaultPassword;                  //�Ƿ�����ΪĬ������
	bool m_bIsSelAll;                              //�Ƿ�ȫѡ
	bool m_bIsSearch;                              //�Ƿ�����

	bool m_bIsCheckState;                              //�Ƿ�ֻ�ı�check��ѡ��״̬

	static const String m_strEdtOldUserPasswd;		//�û�ԭʼ����
	static const String m_strEdtNewUserPasswd;		//������
	static const String m_strEdtCheckUserPasswd;	//����ȷ��
	static const String m_strEdtUserPasswdSet;
	static const String m_strEdtCheckUserPasswdSet;
};