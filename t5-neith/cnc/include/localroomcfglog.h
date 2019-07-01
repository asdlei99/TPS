/** @defgroup 会场控制 静音、哑音、音量等
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.17
 */
#pragma once

enum EmLocalRoomCfgID //tab项枚举
{
	ID_CONFPARAMETERS = 0,
	ID_LOGO,
	ID_BANNER,
	
};

enum EmIsValid//是否有效
{
	emSaveValid = 0,
	emSaveInValid,
	emSaveNochange
};

#define LOGO4CIF_POS0_PATH      _T("logoname4CIF0.bmp")
#define LOGO4CIF_POS1_PATH      _T("logoname4CIF1.bmp")
#define LOGO4CIF_POS2_PATH      _T("logoname4CIF2.bmp")

#define BANNER4CIF_POS0_PATH    _T("bannername4CIF0.bmp")
#define BANNER4CIF_POS1_PATH    _T("bannername4CIF1.bmp")
#define BANNER4CIF_POS2_PATH    _T("bannername4CIF2.bmp")

#define LOGO720P_POS0_PATH      _T("logoname720p0.bmp")
#define LOGO1080P_POS0_PATH     _T("logoname1080p0.bmp")
#define LOGO720P_POS1_PATH      _T("logoname720p1.bmp")
#define LOGO1080P_POS1_PATH     _T("logoname1080p1.bmp")
#define LOGO720P_POS2_PATH      _T("logoname720p2.bmp")
#define LOGO1080P_POS2_PATH     _T("logoname1080p2.bmp")

#define BANNER720P_POS0_PATH      _T("bannername720p0.bmp")
#define BANNER1080P_POS0_PATH     _T("bannername1080p0.bmp")
#define BANNER720P_POS1_PATH      _T("bannername720p1.bmp")
#define BANNER1080P_POS1_PATH     _T("bannername1080p1.bmp")
#define BANNER720P_POS2_PATH      _T("bannername720p2.bmp")
#define BANNER1080P_POS2_PATH     _T("bannername1080p2.bmp")

class CLocalRoomCfgLogic : public CNotifyUIImpl
{
public:
	CLocalRoomCfgLogic(void);
	~CLocalRoomCfgLogic(void);

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
	bool OnBtnCancleLogo(TNotifyUI& msg);
	bool OnBtnCancleBanner(TNotifyUI& msg);
	/** 退出cnc 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSaveLogo(TNotifyUI& msg);
	bool OnBtnSaveBanner(TNotifyUI& msg);
	/** 点击显示屏
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnCheckScreenSel(TNotifyUI& msg);

	/** 是否开启NAT
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsNAT(TNotifyUI& msg);
    /* 点击IPv4 */	
    bool OnCheckIPv4Sel(TNotifyUI& msg);
    /* 点击IPv6 */	
    bool OnCheckIPv6Sel(TNotifyUI& msg);

	/** 点击摄像头Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabLogo(TNotifyUI& msg);
	/** 点击扬声器Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabBanner(TNotifyUI& msg);
	/** 点击麦克Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabParam(TNotifyUI& msg);
	/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
    /** 升级后第一次登录
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnFirstLoginAfterUpdateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 扬声器音量通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateEthnetInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 麦克风音量通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateNatInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);	
	/** 静音、哑音通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnCnsInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** VGA信息通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMainRoomNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 点击进行编辑或取消编辑按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnFixOrCancel(TNotifyUI& msg);
	/** 点击编辑保存 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSave(TNotifyUI& msg);
	/** 点击台标条目
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenLogoItemClick(TNotifyUI& msg);
	/** 点击横幅条目 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenBannerItemClick(TNotifyUI& msg);
	/** banner通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnLogoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** banner响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnLogoInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** logo通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnBannerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** logo响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnBannerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 台标设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/

	/** 画面裁剪
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnVidCutLineInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

    //IPV6
    bool OnSetIpvTypeNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnSetIpv6CfgNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnOpLT(TNotifyUI& msg);
	bool OnOpMT(TNotifyUI& msg);
	bool OnOpRT(TNotifyUI& msg);
	bool OnOpLB(TNotifyUI& msg);
	bool OnOpMB(TNotifyUI& msg);
	bool OnOpRB(TNotifyUI& msg);
	bool OnOpFontBig(TNotifyUI& msg);
	bool OnOpFontMid(TNotifyUI& msg);
	bool OnOpFontSmall(TNotifyUI& msg);
	bool OnOpColorRed(TNotifyUI& msg);
	bool OnOpColorBlue(TNotifyUI& msg);
	bool OnOpColorYellow(TNotifyUI& msg);
	bool OnOpColorBlack(TNotifyUI& msg);
	bool OnOpColorGreen(TNotifyUI& msg);
	/** 横幅设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnOpStyle1(TNotifyUI& msg);
	bool OnOpStyle2(TNotifyUI& msg);
	bool OnOpStyle3(TNotifyUI& msg);
	bool OnOpStyle4(TNotifyUI& msg);
	bool OnOpStyle5(TNotifyUI& msg);
	bool OnOpFullTrans(TNotifyUI& msg);
	bool OnOpSemiTrans(TNotifyUI& msg);
	bool OnOpNoTrans(TNotifyUI& msg);
	bool OnOpBannerFontBig(TNotifyUI& msg);
	bool OnOpBannerFontMid(TNotifyUI& msg);
	bool OnOpBannerFontSmall(TNotifyUI& msg);
	bool OnOpBannerColorRed(TNotifyUI& msg);
	bool OnOpBannerColorBlue(TNotifyUI& msg);
	bool OnOpBannerColorYellow(TNotifyUI& msg);
	bool OnOpBannerColorBlack(TNotifyUI& msg);
	bool OnOpBannerColorGreen(TNotifyUI& msg);
	/** 显示cns信息
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void ShowCnsInfo();
	/** 是否修改了会场名和E64号
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsConfInfoChanged();
	/** 是否修改了网络信息
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsNetInfoChanged();
	/** 是否修改了Nat
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsNATChanged();
	/** 是否修改了兼容显示
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsVidCutLineChanged();//add by wangkui 2016-8-31

    /** 是否修改了IP类型
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsIpTypeChanged();
    /** 是否修改了IPV6
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsIPV6Changed();
	/**	 
	* 功能: 制作显示文字的图片
	* @param    const LPCTSTR strCharacters     [in]     文字内容
	* @param    const LPCTSTR strFontFamily     [in]     字体格式(宋体、微软雅黑等) 
	* @param    const FontStyle emFontStyle     [in]     字体结构(加粗、下划线等) 
	* @param    const Color clText				[in]     字体颜色 
	* @param    const Color clBorder			[in]     字体边界颜色 
	* @param    const Color clBkGrd				[in]     图片背景颜色 
	* @param    const int nFontSizeByPx			[in]     字体Px 
	* @param    const int borderWidthByPx		[in]     字体边界Px 
	* @param    const LPCTSTR strFileName		[in]     图片存储路径 
	* @return   bool
	* @remarks  
	*/
	BOOL MakeImgByChar(const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, const Color clText, const Color clBorder, 
		const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName,
        bool bIsLogo = false/*是否是logo*/, int nImgtype = 0/*图片类型:0中;1左;2右*/, int nWidth = 0, int nHeight = 0 );
	
	/**	 
	* 功能: 获取显示文字的大小
	* @param    const WCHAR * strCharacters     [in]     文字内容
	* @param    Font*pFont				        [in]     字体内容信息
	* @param    CSize& cSize					[out]    文字的大小
	* @return   
	* @remarks  
	*/
	void GetCharExtent(IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize);
	/**	 
	* 功能: 保存图片
	* @param    HBITMAP   hBitmap     [in]     图片句柄
	* @param    CString szfilename	  [in]     输出路径
	* @return   BOOL 是否保存成功
	* @remarks  
	*/
	BOOL SaveBitmapToFile(HBITMAP   hBitmap, CString szfilename);
	/**	 
	* 功能: 上传台标横幅
	* @param    const String& strRemotePath     [in]     远端路径
	* @param    const String& strLocalFile      [in]     本地路径
	* @param    const String& strCheckFileName     [in]     文件名	
	* @return   BOOL bIsLogo true：上传logo  false：上传Banner
	* @return   BOOL 是否上传成功
	* @remarks  
	*/
    BOOL UploadLogoCoreFirstLogin( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	BOOL UploadLogoCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	BOOL UploadBannerCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	/** 台标上传ftp消息响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
    bool OnUploadLogoProgressFirstLogin(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnUploadLogoProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnUploadBannerProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 更新界面logo设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateLogoTag(TTPShowLogo tLogoInfo);
	/** 更新界面Banner设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateBannerTag(TTPShowBanner tBannerInfo);

	/** 更新screen logo设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateLogoScreen(TTPLogoInfo tLogoInfo);
	bool UpdateLogoScreen( TTPShowLogo tShowLogoInfo, u8 wId);
	/** 更新screen Banner设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateBannerScreen(TTPBannerInfo tBannerInfo);
	bool UpdateBannerScreen( TTPShowBanner tShowBannerInfo, u8 wId);
	/** 得到logo样式
	*  @param[in] TTPShowLogo tTPShowLogo logo设置
	*  @param[out] FontStyle &fontStyle 字体样式
	*  @param[out] Color &clr  颜色
	*  @param[out] Color &clBorder  描边颜色
	*  @param[out] u32 &wSize 字大小
	*  @return 
	*/	
	void GetLogoStyle( TTPShowLogo tTPShowLogo, FontStyle &fontStyle, Color &clr, Color &clBorder, u32 &w1080Size, u32 &w720Size , u32 &w4CIF);
	void GetBannerStyle( TTPShowBanner tTPShowBanner, FontStyle &fontStyle, Color &clr, Color &clBorder, u32 &w1080Size, u32 &w720Size , u32 &w4CIF);
	//更新开关状态
	bool UpdateLogoCheck();
	bool UpdateBannerCheck();

	//初始化画面裁剪（兼容显示）状态
	void InitVidCutLine();

    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool UploadLogoImg();

	APP_DECLARE_MSG_MAP()

private:

	static const String m_strSldTab;			 //菜单Tab

	bool m_bIsFix;		  //设置开
	int m_dwLogoScreenSelId;   //Logo项选择的屏号
	int m_dwBannerScreenSelId;   //Banner项选择的屏号

	int m_dwLogoScreenSeUploadlId;   //正在上传的Logo项选择的屏号
	int m_dwBannerScreenUploadId;   //正在上传的Banner项选择的屏号

	EmLocalRoomCfgID     m_emCurrentPage;//当前设置项
	TTPCnsInfo           m_SelCnsInfo;

	map<u16, bool>       m_mapIsLogo;     // 记录屏是否开启logo
	map<u16, bool>       m_mapIsBanner;   // 记录屏是否开启Banner

	map<u16, TTPShowLogo>        m_mapLogoInfo;     //logo设置信息
	map<u16, TTPShowBanner>        m_mapBannerInfo;   //Banner设置信息
	std::vector<String>  m_vecLogoFile;   //上传的logo文件名
	std::vector<String>  m_vecBannerFile;   //上传的banner文件名
	CFtpCtrl m_cFtpLogo;//ftp台标上传    
	CFtpCtrl m_cFtpBanner;//ftp横幅上传    
	
    bool      m_bWaitFtpUpLogo;//记录等待ftp开启后上传台标任务
    bool      m_bWaitFtpUpbanner;//记录等待ftp开启后上传横幅任务

    bool      m_bWaitFtpUploadLogoImgForLogin;//记录等待ftp开启后第一次登录上传台标任务
};