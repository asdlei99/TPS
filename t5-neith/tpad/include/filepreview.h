/** @defgroup �ļ�Ԥ���߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016.7.19
 */
#pragma once

class CFilePreviewLogic : public CNotifyUIImpl, public Singleton<CFilePreviewLogic>
{
public:
	CFilePreviewLogic(void);
	~CFilePreviewLogic(void);

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
	
	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�˳�Ԥ��
	bool OnBtnPreviewBack(TNotifyUI& msg);
public:

	const void SetFilePath( const TCHAR*);
	bool WindowPosSet(int X, int Y, int cx, int cy, UINT uFlags);
	APP_DECLARE_MSG_MAP()

private:
	CString m_strFilePath;

};