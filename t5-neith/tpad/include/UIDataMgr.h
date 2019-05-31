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
    //�Ƿ�����ȷ���ļ���
    bool IsValidFolderStr( String strText );

    void GetCharExtent( IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize );

    //��ȡ�ַ�������ĸ
    static void GetFirstLetter(CStringA strName, CString& strFirstLetter);
    static CString FirstLetter(int nCode);

    //�����㷨
	static bool FileMgrCompare( TFileItem& tItem1, TFileItem& tItem2 );

    //���������IP
    void GetClearIP(CString& strIp);

    //utf8�ַ�תΪunicode
    CString UTF82Unicode(const char* szU8);

private:
    static CUIDataMgr *m_pThis;

};

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
