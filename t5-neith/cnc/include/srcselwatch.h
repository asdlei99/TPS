/** @defgroup 会议选看界面
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015-2-11 
 */
#pragma once

class CSrcSelWatchLogic : public CNotifyUIImpl, public Singleton<CSrcSelWatchLogic>
{
public:
	CSrcSelWatchLogic(void);
	~CSrcSelWatchLogic(void);

	//取消选看
	void CancelSelWatch(int nIndex);
		/** 刷新用户列表 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateCnsInfoList();

    //重置选中屏
    void ReSetSelScreen();
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

	/** 失去焦点消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
/*	bool OnKillFocus(TNotifyUI& msg);*/

	/** 点击列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCnsInfoListItemClick(TNotifyUI& msg);
	/** 点击已选列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSelConfInfoListItemClick(TNotifyUI& msg);
	/** 点击刷新按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRefreshCnsInfoList(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 断链处理
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 搜索 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSearchEditChange(TNotifyUI& msg);
	/** 点击设为屏1 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSetWatch1(TNotifyUI& msg);
	/** 点击设为屏2 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSetWatch2(TNotifyUI& msg);
	/** 点击设为屏3 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSetWatch3(TNotifyUI& msg);
	/** 显示已选
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnShowSel(TNotifyUI& msg);
	/** 取消 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancel(TNotifyUI& msg);
	/** 确定 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnOK(TNotifyUI& msg);
	/** 点击已选列表中的按钮 显示选择的会场位置 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnGetSelItemInMainList(TNotifyUI& msg);
	/** 取消当前屏幕选看 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelCurWatch(TNotifyUI& msg);
	/** 取消所有选看 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelWatch(TNotifyUI& msg);
	/** 三屏会场显示屏幕选项
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnShowScreenOption(TNotifyUI& msg);
	/** 三屏会场隐藏屏幕选项
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnHideScreenOption(TNotifyUI& msg);
	/** 会场选看
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRoomWatch(TNotifyUI& msg);
	/** 会场选择checkbox
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnListBtnRoomSel(TNotifyUI& msg);
	/** 点击三屏列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenSlectListItemClick(TNotifyUI& msg);
	/** 选看nty
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSelViewNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 拖拽
	*  @param[in] 
	*  @node 
	*  @return 
	*/
    bool OnDragIsStart(TNotifyUI& msg);
	bool OnDragDrop(TNotifyUI& msg);
	bool OnDragEnter(TNotifyUI& msg);
	bool OnDragLeave(TNotifyUI& msg);
	bool OnDragDone(TNotifyUI& msg);
    bool OnDragIsOver(TNotifyUI& msg);

	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);

	//已选列表刷新
	void UpdateSelList();
	bool SetScreenWatch(int nScreenID);
	
	//恢复初始界面
	void RestoreInitUI();
	APP_DECLARE_MSG_MAP()

private:
	
	vector<TSelViewInfo>  m_vctCnsInfoList;        //本地地址簿列表 
	vector<TSelViewInfo>  m_vctSearchLst;   //用户搜索列表 
	TSelViewInfo m_aSelWatch[3];			    //三屏对应的条目
	TSelViewInfo m_tCurSelectViewInfo;          //当前选中条目信息
	TCMSConf            m_tConfInfo;            //当前会议信息
	BOOL                m_bSearchEdit;          //是否在搜索

	static const String m_strCnsInfoList;       //用户列表  
	static const String m_strCnsInfoListItem;   //用户列表条目
	static const String m_strSeachEdit;	     //搜索框edit

	u16 m_wCurrentSelIndex;                  //当前选中条目序号
	bool m_bIsGetScreenState;//判断是否已经将已选列表与screen信息同步
	bool m_bIsVideoMix;//是否开启画面合成   
	bool m_bIsClickBtnCancelWatch;//是否点击了"取消选看"按钮

    bool m_bIsNeedUpdate;//是否需要刷新（拖拽之后）
    bool m_bIsDraging;//正在拖拽控件
};