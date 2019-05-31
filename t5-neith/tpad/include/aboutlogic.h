/** @defgroup 帮助文档
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016.8.10
 */
#pragma once

class CAboutLogic : public CNotifyUIImpl, public Singleton<CAboutLogic>
{
public:
	CAboutLogic(void);
	~CAboutLogic(void);

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

	/** 点击列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnFileItemClick(TNotifyUI& msg);
	
	/** 断链 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//返回
	bool OnBtnBack(TNotifyUI& msg);
	//退出
	bool OnBtnExit(TNotifyUI& msg);
public:

	//刷新列表
	void UpdateShowFileList();
	//更新文件夹面包屑目录

	//更新时间
	void UpdateShowTime();
	APP_DECLARE_MSG_MAP()


private:

	map<CString, CString> m_mapAboutFileList; 
	//vector<CString>     m_vctAboutFileList;           //当前显示的文件
	bool m_bPreview; //是否进行预览

};