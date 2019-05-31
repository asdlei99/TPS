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
	tagTSelViewInfo()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTSelViewInfo));

		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;

	}
	BOOL32 IsValid()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}
}TSelViewInfo;


class CUIDataMgr  
{
public:
	virtual ~CUIDataMgr();

    static CUIDataMgr* GetSingleTon();
private:
	CUIDataMgr();


public:
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
    //是否是正确的文件夹
    bool IsValidFolderStr( String strText );

    void GetCharExtent( IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize );

    //获取字符串首字母
    static void GetFirstLetter(CStringA strName, CString& strFirstLetter);
    static CString FirstLetter(int nCode);

    //排序算法
	static bool FileMgrCompare( TFileItem& tItem1, TFileItem& tItem2 );

    //获得清理后的IP
    void GetClearIP(CString& strIp);

    //utf8字符转为unicode
    CString UTF82Unicode(const char* szU8);

private:
    static CUIDataMgr *m_pThis;

};

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
