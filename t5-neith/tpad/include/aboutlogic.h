/** @defgroup �����ĵ�
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016.8.10
 */
#pragma once

class CAboutLogic : public CNotifyUIImpl, public Singleton<CAboutLogic>
{
public:
	CAboutLogic(void);
	~CAboutLogic(void);

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

	/** ����б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnFileItemClick(TNotifyUI& msg);
	
	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//����
	bool OnBtnBack(TNotifyUI& msg);
	//�˳�
	bool OnBtnExit(TNotifyUI& msg);
public:

	//ˢ���б�
	void UpdateShowFileList();
	//�����ļ������мĿ¼

	//����ʱ��
	void UpdateShowTime();
	APP_DECLARE_MSG_MAP()


private:

	map<CString, CString> m_mapAboutFileList; 
	//vector<CString>     m_vctAboutFileList;           //��ǰ��ʾ���ļ�
	bool m_bPreview; //�Ƿ����Ԥ��

};