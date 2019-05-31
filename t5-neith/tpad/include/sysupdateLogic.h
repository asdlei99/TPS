/** @defgroup u盘升级
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016-9-27
 */
#pragma once

enum EmCopyState
{
	emCopyNo = (u32)0,   //未进行文件复制操作
	emCopying,			 //文件复制中
	emCopyEnd,			 //文件复制成功
	emCopyFail,			 //文件复制失败
};

#define READ_BUF_MAX        128
class CSysUpdateLogic : public CNotifyUIImpl, public Singleton<CSysUpdateLogic>
{
public:
	CSysUpdateLogic(void);
	~CSysUpdateLogic(void);
	void CloseUdiscUpWnd();
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

	bool OnDestroy(TNotifyUI& msg);

	bool OnBtnOk(TNotifyUI& msg);
	bool OnBtnCancel(TNotifyUI& msg);
	bool UpdateNow();

	BOOL CopyFiles( CString& strDst, CString& strSrc );
	bool OnSysUpdateOver(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

public:
	bool SysUpdate();

	APP_DECLARE_MSG_MAP()

private:
	CString m_strUDiskName;          //U盘名称
	CString m_strUpdatePath;         //升级路径

	EmCopyState m_emCopyState;

};

bool showUdisUpdateDlg(LPCTSTR lpstrVer, LPCTSTR lpstrOriVer);
#define ShowUdisUpdateDlg showUdisUpdateDlg