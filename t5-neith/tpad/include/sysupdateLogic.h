/** @defgroup u������
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016-9-27
 */
#pragma once

enum EmCopyState
{
	emCopyNo = (u32)0,   //δ�����ļ����Ʋ���
	emCopying,			 //�ļ�������
	emCopyEnd,			 //�ļ����Ƴɹ�
	emCopyFail,			 //�ļ�����ʧ��
};

#define READ_BUF_MAX        128
class CSysUpdateLogic : public CNotifyUIImpl, public Singleton<CSysUpdateLogic>
{
public:
	CSysUpdateLogic(void);
	~CSysUpdateLogic(void);
	void CloseUdiscUpWnd();
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

	bool OnBtnOk(TNotifyUI& msg);
	bool OnBtnCancel(TNotifyUI& msg);
	bool UpdateNow();

	BOOL CopyFiles( CString& strDst, CString& strSrc );
	bool OnSysUpdateOver(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

public:
	bool SysUpdate();

	APP_DECLARE_MSG_MAP()

private:
	CString m_strUDiskName;          //U������
	CString m_strUpdatePath;         //����·��

	EmCopyState m_emCopyState;

};

bool showUdisUpdateDlg(LPCTSTR lpstrVer, LPCTSTR lpstrOriVer);
#define ShowUdisUpdateDlg showUdisUpdateDlg