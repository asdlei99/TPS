// UIDataMgr.h: interface for the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
#define AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EMLocalCnsState 
{   
	emLocalCnsIdle = em_CALL_IDLE , //空闲状态 ，与EmCALLSTATE 对齐， 2012.11.14  by yjj  
        emLocalCnsCalling   = em_CALL_CALLING,      //正在呼叫中
		emLocalCnsConnected = em_CALL_CONNECTED,
        emLocalCallingTimeOut,  //呼叫动画已显示超过5秒，应该切换到锁屏状态
        emLocalCnsInConf,       //在会议中
        emLocalCnsHungup,       //会议开启后，localCns 不在线，执行了挂断操作
        
	   
		/*将要挂断/离开会议
         Note:表示此时正显示 （ 是否要挂断/离开会议的）提示框，
		 若此时会议从其他途径已经结束，则此时的提示框应自动隐藏 
         Bug00113809
		 2012.11.14 俞锦锦*/
		emLocalCnsWillHungup,	

		emLocalCnsLocking,      //会议开启后，localCns 不在线,当前正处于锁定状态
};


enum EmWaitType{
	emWaitRegInfo,		//等待注册信息
	emWaitConfInfo,  //等待会议信息
	emWaitLoadAddr   //等待导入地址簿
};



enum EMTimer{
	emTimerCalling,  
		emTimerRefreshUI
};


enum EM_NETMNGOPT_TYPE      //网管操作类型
{
	em_NETMNGOPT_ADD,//新建用户
	em_NETMNGOPT_MODIFY,//编辑已有用户
	em_NETMNGOPT_IDLE//查看
};


typedef struct tagTSelViewInfo
{
	u16		 m_wConfID;
	u16		 m_wEpID;

	EmViewEpType	m_emType;
	u16				m_wDstID;
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//会场名
	u16      m_wSpeakerNum;					//会场屏数	
	u16      m_wDstScrIndx;                 //屏选看号（0,1,2）,TP_MAX_STREAMNUM表示选择整个会场
	
	EmTPEndpointType m_emEpType;			//结点类型
	
	tagTSelViewInfo()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTSelViewInfo));

		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_wSpeakerNum = TP_INVALID_INDEX;
		m_wDstScrIndx = TP_MAX_STREAMNUM;
		m_emEpType = emTPEndpointTypeUnknown;

	}
	BOOL32 IsValid()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}
}TSelViewInfo;

typedef struct tagTPWElement
{
	bool m_bElement0;
	bool m_bElement1;
	bool m_bElement2;

	tagTPWElement()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTPWElement));

		m_bElement0 = false;
		m_bElement1 = false;
		m_bElement2 = false;
	}
	
}TPWElement;


class CUIDataMgr  
{
public:
	virtual ~CUIDataMgr();

    static CUIDataMgr* GetSingleTon();
private:
	CUIDataMgr();


public:
    //是否是PC版
    void SetPcVersion( BOOL bPcVer ) { m_bIsPcVersion = bPcVer; }
    BOOL IsPcVersion() { return m_bIsPcVersion; }


    String GetCurSimulateDlgName(){ return m_strSimulateCnsDlgName; }
    void SetCurSimulateDlgName( String strName ){ m_strSimulateCnsDlgName = strName ; }


    String GetCurMainMenuType(){ return m_strSchmMainMenuShow ;}
    void SetCurMainMenuType( String strType ) { m_strSchmMainMenuShow = strType ;}

 	
	/** 设置屏幕解锁信息
	 *  @param[in]  tInfo  屏幕解锁信息
	 *  @return 
	 */
	void SetLockScreenInfo( TLockScreenInfo tInfo );

	/** 获取屏幕解锁信息
	 *  @param[out]  TLockScreenInfo 屏幕解锁信息
	 *  @return 
	 */
	TLockScreenInfo& GetLockScreenInfo();
 
   
     /**
	* 功能:  获取本地cns状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    EMLocalCnsState GetLocalCnsState( ){ return m_emLocalCnsState ;}


    /**
	* 功能:  获取本地cns会议信息
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    void setLocalCnsState( EMLocalCnsState emState  ){ m_emLocalCnsState = emState; }


	/*
	功能：PinYin检索判断
	参数：const CString strTextInput: 待判断的对象串(用户输入PY项)
	      const CString strTextSrc  : 判断源字对象串(汉字项)
	返回值:配对成功 TRUE, 配对失败 FALSE;
	*/
	BOOL  HZPYMatchList( const CString strTextInput,  const CString strTextSrc );


	//是否是正确的164
	bool IsAllE164Number( String strText );
	//是否是正确的TP
	bool IsValidTPStr( String strText );
	//是否是正确的密码格式
	bool IsValidPWStr( CString szPWStr ) ;
	//密码级别
	void GetPWlevel( CString szPWStr, TPWElement &tPWElementLevel, TPWElement &tPWElementState ) ;

    void GetCharExtent( IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize );

	//设置当前显示窗口
	void SetCurShowWndName( String strWnd ) { m_strCurShowWnd = strWnd; }
	String  GetCurShowWndName() { return m_strCurShowWnd; }

    //设置当前地址簿窗口名，用于地址簿编辑的切换
    void SetCurAddrWndName( String strWnd ) { m_strCurAddrWnd = strWnd; }
    String  GetCurAddrWndName() { return m_strCurAddrWnd; }

    //获取字符串首字母
    static void GetFirstLetter(CStringA strName, CString& strFirstLetter);
    static CString FirstLetter(int nCode);

    //获取cnc主界面分辨率
    void SetCncMainPos(SIZE sizeMain){m_sizeMain = sizeMain;}
    SIZE GetCncMainPos(){return m_sizeMain;}

    //排序算法
    static bool AddrItemCompare(TAddrItem& tItem1, TAddrItem& tItem2);
	static bool ConfTempCompare( TTPAlias& tAlias1, TTPAlias& tAlias2 );
	static bool CnsInfoCompare(TCnsInfo& tInfo1, TCnsInfo& tInfo2);
	static bool SelViewCompare(TSelViewInfo& tSelViewInfo1, TSelViewInfo& tSelViewInfo2);
	static bool UserItemCompare( CUserFullInfo& tItem1, CUserFullInfo& tItem2 );

    //获得清理后的IP
    void GetClearIP(CString& strIp);

private:
    static CUIDataMgr *m_pThis;

    BOOL               m_bIsPcVersion;

    String  m_strSimulateCnsDlgName;  //当前使用的模拟会场的界面名，便于界面切换的时候做隐藏和显示
    String  m_strSchmMainMenuShow;    //当前主菜单显示的某种菜单的方案类型

    TLockScreenInfo    m_tLockScreenInfo;

    EMLocalCnsState m_emLocalCnsState;         ///<本地cns的当前状态

	String  m_strCurShowWnd;          //当前显示的窗口名
    String  m_strCurAddrWnd;          //当前显示的地址簿窗口名

    SIZE    m_sizeMain;              //主界面分辨率
};

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
