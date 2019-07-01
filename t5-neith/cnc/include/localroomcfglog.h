/** @defgroup �᳡���� ������������������
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.17
 */
#pragma once

enum EmLocalRoomCfgID //tab��ö��
{
	ID_CONFPARAMETERS = 0,
	ID_LOGO,
	ID_BANNER,
	
};

enum EmIsValid//�Ƿ���Ч
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

	/** ʧȥ������Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
/*	bool OnKillFocus(TNotifyUI& msg);*/
	
	/** �˳���ҳ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancleLogo(TNotifyUI& msg);
	bool OnBtnCancleBanner(TNotifyUI& msg);
	/** �˳�cnc 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSaveLogo(TNotifyUI& msg);
	bool OnBtnSaveBanner(TNotifyUI& msg);
	/** �����ʾ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnCheckScreenSel(TNotifyUI& msg);

	/** �Ƿ���NAT
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsNAT(TNotifyUI& msg);
    /* ���IPv4 */	
    bool OnCheckIPv4Sel(TNotifyUI& msg);
    /* ���IPv6 */	
    bool OnCheckIPv6Sel(TNotifyUI& msg);

	/** �������ͷTab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabLogo(TNotifyUI& msg);
	/** ���������Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabBanner(TNotifyUI& msg);
	/** ������Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabParam(TNotifyUI& msg);
	/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
    /** �������һ�ε�¼
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnFirstLoginAfterUpdateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����������֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateEthnetInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��˷�����֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateNatInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);	
	/** ����������֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnCnsInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** VGA��Ϣ֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMainRoomNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ������б༭��ȡ���༭��ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnFixOrCancel(TNotifyUI& msg);
	/** ����༭���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSave(TNotifyUI& msg);
	/** ���̨����Ŀ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenLogoItemClick(TNotifyUI& msg);
	/** ��������Ŀ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenBannerItemClick(TNotifyUI& msg);
	/** banner֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnLogoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** banner��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnLogoInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** logo֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnBannerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** logo��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnBannerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ̨������
	*  @param[in] 
	*  @node 
	*  @return 
	*/

	/** ����ü�
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
	/** �������
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
	/** ��ʾcns��Ϣ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void ShowCnsInfo();
	/** �Ƿ��޸��˻᳡����E64��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsConfInfoChanged();
	/** �Ƿ��޸���������Ϣ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsNetInfoChanged();
	/** �Ƿ��޸���Nat
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsNATChanged();
	/** �Ƿ��޸��˼�����ʾ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsVidCutLineChanged();//add by wangkui 2016-8-31

    /** �Ƿ��޸���IP����
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsIpTypeChanged();
    /** �Ƿ��޸���IPV6
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	EmIsValid IsIPV6Changed();
	/**	 
	* ����: ������ʾ���ֵ�ͼƬ
	* @param    const LPCTSTR strCharacters     [in]     ��������
	* @param    const LPCTSTR strFontFamily     [in]     �����ʽ(���塢΢���źڵ�) 
	* @param    const FontStyle emFontStyle     [in]     ����ṹ(�Ӵ֡��»��ߵ�) 
	* @param    const Color clText				[in]     ������ɫ 
	* @param    const Color clBorder			[in]     ����߽���ɫ 
	* @param    const Color clBkGrd				[in]     ͼƬ������ɫ 
	* @param    const int nFontSizeByPx			[in]     ����Px 
	* @param    const int borderWidthByPx		[in]     ����߽�Px 
	* @param    const LPCTSTR strFileName		[in]     ͼƬ�洢·�� 
	* @return   bool
	* @remarks  
	*/
	BOOL MakeImgByChar(const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, const Color clText, const Color clBorder, 
		const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName,
        bool bIsLogo = false/*�Ƿ���logo*/, int nImgtype = 0/*ͼƬ����:0��;1��;2��*/, int nWidth = 0, int nHeight = 0 );
	
	/**	 
	* ����: ��ȡ��ʾ���ֵĴ�С
	* @param    const WCHAR * strCharacters     [in]     ��������
	* @param    Font*pFont				        [in]     ����������Ϣ
	* @param    CSize& cSize					[out]    ���ֵĴ�С
	* @return   
	* @remarks  
	*/
	void GetCharExtent(IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize);
	/**	 
	* ����: ����ͼƬ
	* @param    HBITMAP   hBitmap     [in]     ͼƬ���
	* @param    CString szfilename	  [in]     ���·��
	* @return   BOOL �Ƿ񱣴�ɹ�
	* @remarks  
	*/
	BOOL SaveBitmapToFile(HBITMAP   hBitmap, CString szfilename);
	/**	 
	* ����: �ϴ�̨����
	* @param    const String& strRemotePath     [in]     Զ��·��
	* @param    const String& strLocalFile      [in]     ����·��
	* @param    const String& strCheckFileName     [in]     �ļ���	
	* @return   BOOL bIsLogo true���ϴ�logo  false���ϴ�Banner
	* @return   BOOL �Ƿ��ϴ��ɹ�
	* @remarks  
	*/
    BOOL UploadLogoCoreFirstLogin( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	BOOL UploadLogoCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	BOOL UploadBannerCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	/** ̨���ϴ�ftp��Ϣ��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
    bool OnUploadLogoProgressFirstLogin(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnUploadLogoProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnUploadBannerProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���½���logo����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateLogoTag(TTPShowLogo tLogoInfo);
	/** ���½���Banner����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateBannerTag(TTPShowBanner tBannerInfo);

	/** ����screen logo����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateLogoScreen(TTPLogoInfo tLogoInfo);
	bool UpdateLogoScreen( TTPShowLogo tShowLogoInfo, u8 wId);
	/** ����screen Banner����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool UpdateBannerScreen(TTPBannerInfo tBannerInfo);
	bool UpdateBannerScreen( TTPShowBanner tShowBannerInfo, u8 wId);
	/** �õ�logo��ʽ
	*  @param[in] TTPShowLogo tTPShowLogo logo����
	*  @param[out] FontStyle &fontStyle ������ʽ
	*  @param[out] Color &clr  ��ɫ
	*  @param[out] Color &clBorder  �����ɫ
	*  @param[out] u32 &wSize �ִ�С
	*  @return 
	*/	
	void GetLogoStyle( TTPShowLogo tTPShowLogo, FontStyle &fontStyle, Color &clr, Color &clBorder, u32 &w1080Size, u32 &w720Size , u32 &w4CIF);
	void GetBannerStyle( TTPShowBanner tTPShowBanner, FontStyle &fontStyle, Color &clr, Color &clBorder, u32 &w1080Size, u32 &w720Size , u32 &w4CIF);
	//���¿���״̬
	bool UpdateLogoCheck();
	bool UpdateBannerCheck();

	//��ʼ������ü���������ʾ��״̬
	void InitVidCutLine();

    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool UploadLogoImg();

	APP_DECLARE_MSG_MAP()

private:

	static const String m_strSldTab;			 //�˵�Tab

	bool m_bIsFix;		  //���ÿ�
	int m_dwLogoScreenSelId;   //Logo��ѡ�������
	int m_dwBannerScreenSelId;   //Banner��ѡ�������

	int m_dwLogoScreenSeUploadlId;   //�����ϴ���Logo��ѡ�������
	int m_dwBannerScreenUploadId;   //�����ϴ���Banner��ѡ�������

	EmLocalRoomCfgID     m_emCurrentPage;//��ǰ������
	TTPCnsInfo           m_SelCnsInfo;

	map<u16, bool>       m_mapIsLogo;     // ��¼���Ƿ���logo
	map<u16, bool>       m_mapIsBanner;   // ��¼���Ƿ���Banner

	map<u16, TTPShowLogo>        m_mapLogoInfo;     //logo������Ϣ
	map<u16, TTPShowBanner>        m_mapBannerInfo;   //Banner������Ϣ
	std::vector<String>  m_vecLogoFile;   //�ϴ���logo�ļ���
	std::vector<String>  m_vecBannerFile;   //�ϴ���banner�ļ���
	CFtpCtrl m_cFtpLogo;//ftp̨���ϴ�    
	CFtpCtrl m_cFtpBanner;//ftp����ϴ�    
	
    bool      m_bWaitFtpUpLogo;//��¼�ȴ�ftp�������ϴ�̨������
    bool      m_bWaitFtpUpbanner;//��¼�ȴ�ftp�������ϴ��������

    bool      m_bWaitFtpUploadLogoImgForLogin;//��¼�ȴ�ftp�������һ�ε�¼�ϴ�̨������
};