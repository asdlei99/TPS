/** @defgroup 用户管理单元
 *  @version V1.1.4
 *  @author  邓莹莹
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
	bool OnUserItemClick(TNotifyUI& msg);

	/** 点击刷新按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRefresh(TNotifyUI& msg);
	/** 点击刷新按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRefreshUserLst(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 断链处理
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 用户信息修改响应 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUserModifyRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 刷新用户列表 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateUserLst();
	/** 搜索 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSearchEditChange(TNotifyUI& msg);

	/** 点击用户信息修改按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnModifyUser(TNotifyUI& msg);
	/** 点击选择条目按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckItemSel(TNotifyUI& msg);
	/** 点击取消修改按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelUserSet(TNotifyUI& msg);
	/** 点击修改保存按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSaveUserSet(TNotifyUI& msg);
	/** 点击返回按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** 点击退出按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	/** 点击全选按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSelAll(TNotifyUI& msg);
	/** 点击添加用户按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnAdd(TNotifyUI& msg);
	/** 点击删除用户按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnDel(TNotifyUI& msg);
	/** 点击显示已选用户列表按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckClearSel(TNotifyUI& msg);
	/** 点击设置默认密码按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIfSetDefaultPassword(TNotifyUI& msg);
	//letterindex点击
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
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool savePassWord( );

    void UpdatePasswordTime();//更新密码安全周期时间
	APP_DECLARE_MSG_MAP()
private:

	TplArray<CUserFullInfo>  m_pArrayUserList;        //用户列表 
	TplArray<CUserFullInfo>  m_pArrayUserSelLst;	  //已选用户列表 
	static const String m_strUserList;       //用户列表  
	static const String m_strUserListItem;   //用户列表条目
	static const String m_strUserItemName;   //用户名称 
	static const String m_strSeachEdit;	     //搜索框edit
	static const String m_strBtnUserSet;     //修改用户信息按钮
	static const String m_strCheckBoxItemSel;//用户选中按钮
	CUserFullInfo       m_selUser;                 //当前选择的用户
	EM_NETMNGOPT_TYPE    m_emModifyType;            //是修改用户  还是 新建用户
	bool m_bIsSetDefaultPassword;                  //是否设置为默认密码
	bool m_bIsSelAll;                              //是否全选
	bool m_bIsSearch;                              //是否搜索

	bool m_bIsCheckState;                              //是否只改变check已选的状态

	static const String m_strEdtOldUserPasswd;		//用户原始密码
	static const String m_strEdtNewUserPasswd;		//新密码
	static const String m_strEdtCheckUserPasswd;	//密码确认
	static const String m_strEdtUserPasswdSet;
	static const String m_strEdtCheckUserPasswdSet;
};