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
	emLocalCnsIdle = em_CALL_IDLE , //����״̬ ����EmCALLSTATE ���룬 2012.11.14  by yjj  
        emLocalCnsCalling   = em_CALL_CALLING,      //���ں�����
		emLocalCnsConnected = em_CALL_CONNECTED,
        emLocalCallingTimeOut,  //���ж�������ʾ����5�룬Ӧ���л�������״̬
        emLocalCnsInConf,       //�ڻ�����
        emLocalCnsHungup,       //���鿪����localCns �����ߣ�ִ���˹Ҷϲ���
        
	   
		/*��Ҫ�Ҷ�/�뿪����
         Note:��ʾ��ʱ����ʾ �� �Ƿ�Ҫ�Ҷ�/�뿪����ģ���ʾ��
		 ����ʱ���������;���Ѿ����������ʱ����ʾ��Ӧ�Զ����� 
         Bug00113809
		 2012.11.14 �����*/
		emLocalCnsWillHungup,	

		emLocalCnsLocking,      //���鿪����localCns ������,��ǰ����������״̬
};


enum EmWaitType{
	emWaitRegInfo,		//�ȴ�ע����Ϣ
	emWaitConfInfo,  //�ȴ�������Ϣ
	emWaitLoadAddr   //�ȴ������ַ��
};



enum EMTimer{
	emTimerCalling,  
		emTimerRefreshUI
};


enum EM_NETMNGOPT_TYPE      //���ܲ�������
{
	em_NETMNGOPT_ADD,//�½��û�
	em_NETMNGOPT_MODIFY,//�༭�����û�
	em_NETMNGOPT_IDLE//�鿴
};


typedef struct tagTSelViewInfo
{
	u16		 m_wConfID;
	u16		 m_wEpID;

	EmViewEpType	m_emType;
	u16				m_wDstID;
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//�᳡��
	u16      m_wSpeakerNum;					//�᳡����	
	u16      m_wDstScrIndx;                 //��ѡ���ţ�0,1,2��,TP_MAX_STREAMNUM��ʾѡ�������᳡
	
	EmTPEndpointType m_emEpType;			//�������
	
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
    //�Ƿ���PC��
    void SetPcVersion( BOOL bPcVer ) { m_bIsPcVersion = bPcVer; }
    BOOL IsPcVersion() { return m_bIsPcVersion; }


    String GetCurSimulateDlgName(){ return m_strSimulateCnsDlgName; }
    void SetCurSimulateDlgName( String strName ){ m_strSimulateCnsDlgName = strName ; }


    String GetCurMainMenuType(){ return m_strSchmMainMenuShow ;}
    void SetCurMainMenuType( String strType ) { m_strSchmMainMenuShow = strType ;}

 	
	/** ������Ļ������Ϣ
	 *  @param[in]  tInfo  ��Ļ������Ϣ
	 *  @return 
	 */
	void SetLockScreenInfo( TLockScreenInfo tInfo );

	/** ��ȡ��Ļ������Ϣ
	 *  @param[out]  TLockScreenInfo ��Ļ������Ϣ
	 *  @return 
	 */
	TLockScreenInfo& GetLockScreenInfo();
 
   
     /**
	* ����:  ��ȡ����cns״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    EMLocalCnsState GetLocalCnsState( ){ return m_emLocalCnsState ;}


    /**
	* ����:  ��ȡ����cns������Ϣ
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    void setLocalCnsState( EMLocalCnsState emState  ){ m_emLocalCnsState = emState; }


	/*
	���ܣ�PinYin�����ж�
	������const CString strTextInput: ���жϵĶ���(�û�����PY��)
	      const CString strTextSrc  : �ж�Դ�ֶ���(������)
	����ֵ:��Գɹ� TRUE, ���ʧ�� FALSE;
	*/
	BOOL  HZPYMatchList( const CString strTextInput,  const CString strTextSrc );


	//�Ƿ�����ȷ��164
	bool IsAllE164Number( String strText );
	//�Ƿ�����ȷ��TP
	bool IsValidTPStr( String strText );
	//�Ƿ�����ȷ�������ʽ
	bool IsValidPWStr( CString szPWStr ) ;
	//���뼶��
	void GetPWlevel( CString szPWStr, TPWElement &tPWElementLevel, TPWElement &tPWElementState ) ;

    void GetCharExtent( IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize );

	//���õ�ǰ��ʾ����
	void SetCurShowWndName( String strWnd ) { m_strCurShowWnd = strWnd; }
	String  GetCurShowWndName() { return m_strCurShowWnd; }

    //���õ�ǰ��ַ�������������ڵ�ַ���༭���л�
    void SetCurAddrWndName( String strWnd ) { m_strCurAddrWnd = strWnd; }
    String  GetCurAddrWndName() { return m_strCurAddrWnd; }

    //��ȡ�ַ�������ĸ
    static void GetFirstLetter(CStringA strName, CString& strFirstLetter);
    static CString FirstLetter(int nCode);

    //��ȡcnc������ֱ���
    void SetCncMainPos(SIZE sizeMain){m_sizeMain = sizeMain;}
    SIZE GetCncMainPos(){return m_sizeMain;}

    //�����㷨
    static bool AddrItemCompare(TAddrItem& tItem1, TAddrItem& tItem2);
	static bool ConfTempCompare( TTPAlias& tAlias1, TTPAlias& tAlias2 );
	static bool CnsInfoCompare(TCnsInfo& tInfo1, TCnsInfo& tInfo2);
	static bool SelViewCompare(TSelViewInfo& tSelViewInfo1, TSelViewInfo& tSelViewInfo2);
	static bool UserItemCompare( CUserFullInfo& tItem1, CUserFullInfo& tItem2 );

    //���������IP
    void GetClearIP(CString& strIp);

private:
    static CUIDataMgr *m_pThis;

    BOOL               m_bIsPcVersion;

    String  m_strSimulateCnsDlgName;  //��ǰʹ�õ�ģ��᳡�Ľ����������ڽ����л���ʱ�������غ���ʾ
    String  m_strSchmMainMenuShow;    //��ǰ���˵���ʾ��ĳ�ֲ˵��ķ�������

    TLockScreenInfo    m_tLockScreenInfo;

    EMLocalCnsState m_emLocalCnsState;         ///<����cns�ĵ�ǰ״̬

	String  m_strCurShowWnd;          //��ǰ��ʾ�Ĵ�����
    String  m_strCurAddrWnd;          //��ǰ��ʾ�ĵ�ַ��������

    SIZE    m_sizeMain;              //������ֱ���
};

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
