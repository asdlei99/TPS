/** @defgroup 文件预览逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016.7.19
 */
#pragma once

class CFilePreviewLogic : public CNotifyUIImpl, public Singleton<CFilePreviewLogic>
{
public:
	CFilePreviewLogic(void);
	~CFilePreviewLogic(void);

protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);
	
	/** 断链 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//退出预览
	bool OnBtnPreviewBack(TNotifyUI& msg);
public:

	const void SetFilePath( const TCHAR*);
	bool WindowPosSet(int X, int Y, int cx, int cy, UINT uFlags);
	APP_DECLARE_MSG_MAP()

private:
	CString m_strFilePath;

};