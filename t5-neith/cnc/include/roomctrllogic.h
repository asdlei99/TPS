/** @defgroup 会场控制 静音、哑音、音量等
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.17
 */
#pragma once

#define NUM_MIC_FIRLINE               3
#define NUM_MIC_SECLINE               6

#define NUM_SRCEEN_COUNT               5
#define FLAG_FIRST          0x00000001
#define FLAG_SECOND         0x00000002
#define FLAG_THIRD          0x00000004
#define FLAG_FOURTH         0x00000008
#define FLAG_FIFTH          0x00000010
//用于屏幕的取位
const int adwTagArray[NUM_SRCEEN_COUNT] = {FLAG_FIRST,FLAG_SECOND,FLAG_THIRD,FLAG_FOURTH,FLAG_FIFTH};

enum EmTabID //tab项枚举
{
	ID_CAMERA = 1,  //摄像机
	ID_SPEAKER,     //扬声器
	ID_MIC,         //麦克风
//	ID_VEDIOSOURCE, //演示源
	ID_MAINVEDIO,   //主视频源（视频源）
};

class CRoomCtrlLogic : public CNotifyUIImpl
{
public:
	CRoomCtrlLogic(void);
	~CRoomCtrlLogic(void);

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
	
	/** 退出此页面 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** 退出cnc 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	/** 点击静音
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckSlient(TNotifyUI& msg);
	/** 是否创建扬声器快捷控制
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckSpeakerShortCut(TNotifyUI& msg);
	/** 点击哑音
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnCheckMute(TNotifyUI& msg);
	/** 是否创建麦克风快捷控制
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnCheckMicShortCut(TNotifyUI& msg);
	/** 选择视频项条目
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnBtnVedioItemSel(TNotifyUI& msg);
	/** 单个麦克风控制
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnBtnMicControl(TNotifyUI& msg);
	/** 点击摄像头Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabCamera(TNotifyUI& msg);
	/** 点击扬声器Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabSpeaker(TNotifyUI& msg);
	/** 点击麦克Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabMic(TNotifyUI& msg);
	/** 点击视频源Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	//bool OnTabVedioSource(TNotifyUI& msg);
	/** 点击主视频源Tab
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabMainVedio(TNotifyUI& msg);

	/** 主视频源选择
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabVedio1Op1(TNotifyUI& msg);
	bool OnTabVedio1Op2(TNotifyUI& msg);
	bool OnTabVedio2Op1(TNotifyUI& msg);
	bool OnTabVedio2Op2(TNotifyUI& msg);
	bool OnTabVedio2Op3(TNotifyUI& msg);
	bool OnTabVedio3Op1(TNotifyUI& msg);
	bool OnTabVedio3Op2(TNotifyUI& msg);

    //升降屏选择
    bool OnCheckSrceenControl(TNotifyUI& msg);

    bool OnBtnLiftSrceenUp(TNotifyUI& msg);
    bool OnBtnLiftSrceenDown(TNotifyUI& msg);
    bool OnBtnLiftSrceenStop(TNotifyUI& msg);

    bool OnBtnFlipSrceenOpen(TNotifyUI& msg);
    bool OnBtnFlipSrceenClose(TNotifyUI& msg);
    bool OnBtnFlipSrceenStop(TNotifyUI& msg);

	/** 点击全景摄像机
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabFullCamera(TNotifyUI& msg);
	/** 点击文档摄像机
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabFileCamera(TNotifyUI& msg);

	/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 扬声器音量通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnSpeakerVolNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 麦克风音量通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnMicVolNty(WPARAM wParam, LPARAM lParam, bool& bHandle);	
	/** 静音、哑音通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnMuteOrSilencNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** VGA信息通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnVgaInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 双流端口通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSelDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelDefaultDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 显示Tab
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnSetTabShow(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 快捷方式check状态设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnSetShortCheck(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 扬声器音量变化响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool onSpeakerVolChanged(TNotifyUI& msg);
	bool onSpeakerVolChanging(TNotifyUI& msg);
	/** 麦克风音量变化响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool onMicVolChanged(TNotifyUI& msg);
	bool onMicVolChanging(TNotifyUI& msg);
	/** 更新视频源列表 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateVedioSourceList();
	//选择视频源列表中一项
	bool OnVedioItemSel(TNotifyUI& msg);
	bool OnComboItemSel(TNotifyUI& msg);

	//主视频源设置消息
	bool OnMainVedioSetInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//主视频源设置消息
	bool OnVidSrcNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//辅视频进行限制主视频选项
	bool OnMinVedioInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tptool设置主视频源的名字
	bool OnSetVedioInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	void UpdateSourceName();

	//麦克风相关
	bool OnCnDesktopMicInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnMicPowerStyleNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnMicPowerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnSetMicPowerRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	void UpdateMicStyle();
	void UpdateMicState();
    //升降屏相关
    bool OnCentreDFScreenConfigNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnCentreSelectDFScreenNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnCentreScreenTypeNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnModifyDFScreenGroupInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnCentreDFScreenCmdInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnSelectDFScreenInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:

	static const String m_strBtnFixOrCancel;	 //修改、取消按钮
	static const String m_strBtnOk;				 //确认按钮
	static const String m_strSldTab;			 //菜单Tab
	static const String m_strFullCamera;	     //全景摄像机
	static const String m_strSldSpeaker;		 //扬声器	
	static const String m_strSldMic;			 //麦克风
	static const String m_strBtnMute;			 //哑音
	static const String m_strBtnSlience;		 //静音

    static const int m_nFirstLineMic[NUM_MIC_FIRLINE];		 //第一排麦克风顺序
    static const int m_nSecondLineMic[NUM_MIC_SECLINE];		 //第二排麦克风顺序

	TDualSrcInfo  m_tDualSrcInfo;
	map<u16, EmTPMtVideoPort>       m_mapEmTPMtVideoPort;     // 主视频源选择
	bool m_bIsVSListExt;//是否已经有了视频源列表
	bool m_bSetVedioSourc;//是否进行了演示源切换，如果已经发了消息，在ind来之前不重复发送消息
	bool m_bIsIni;//是否进行了初始化
	EM_ShortcutType m_em;//初始化之前收到的快捷方式调出
	TTPVideoInfoTool m_tTPVideoInfoTool;//主视频配置项  

	BOOL			 m_bIsFullState;          //会场麦克风数量为9的全状态
	BOOL			 m_bIsNonDesktopMic;
	BOOL             m_byMicStyle[TP_MIC_NUM];//麦克风状态
	BOOL             m_byMicState[TP_MIC_NUM];//麦克风状态

    u32              m_dwGroupNum;            //升降屏组数
    u8               m_byScreenControl;       //升降屏：标记升降屏控制的标号
    u8               m_byAllScreenCtrlSel;    //升降屏：有效屏幕全选（有效屏幕数由tptools配置
};