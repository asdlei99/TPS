/*=======================================================================
ģ����      : �ն˿���̨
�ļ���      : MsgDriver.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��Ϣ������
����        : �ܹ㻯
�汾        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/12/22  3.0         �ܹ㻯      ����
2003/03/02	3.0			�ܹ㻯		����
2004/08/23  3.5         ���ǿ      �淶���룬����CDispEvent��
2013/11/03  4.0         ����ӡ      linuxƽ̨��ֲ fcgi��Ϣͨ���߼���չ
=======================================================================*/
#ifndef MSGDRIVER_H
#define MSGDRIVER_H

class CMsgDriver : public ISingleTon<CMsgDriver>
{
public:
    CMsgDriver();
    ~CMsgDriver();
    // �õ�������Ϣָ��
    CMessage* GetCMsgPtr(BOOL32 bClear = TRUE);
	// �õ������ն���Ϣ��ָ��
	CTpMsg* GetKdvMsgPtr(BOOL32 bClear = TRUE);
    // ������������Ϣ �ɷ�����ͨCMessage��CMtMsg���͵���Ϣ
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);
    // ������������Ϣ����ʱû�г�ʱ����
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 dwWaitEvent,  u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // ע��һ��������Ϣ�����ָ��
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // ע��һ��������Ϣ�����ָ��
    void UnregHandler(CKdvDispEvent* const pDispEvnet);
    // �������ע������ָ��
    void ClearHandler();

	void SetSndInstID( u32 dwDstInstID );
	u32  GetSndInstID();
	
	void SetAppID( u32 dwAppID ){ m_dwAppID = dwAppID;};					//Դ�����ͻ��ˣ�APP ID
	u32  GetAppID(){ return m_dwAppID;};

	void SetDesAppID( u32 dwDesAppID ){ m_dwDesAppID = dwDesAppID;};		//�ˣ��������� Ŀ�ģ�APP ID
	u32  GetDesAppID(){ return m_dwDesAppID;};

	BOOL PostEvent( u32 dwEvent, const boost::any& arg );

	void ReleaseLock();

public:
	void MessageProc(/*CTpMsg *const ptMsg*/);

private:
	// ��յȴ�����Ϣ
    void ClearWaiting();

protected:
    CTpMsg       m_cKdvMsg;             // ���ڷ��� tp��Ϣ����Ϣ�ṹ
	CMessage	 m_cMsg;				//���ڷ����������ն���Ϣ����Ϣ�ṹ
	
private:
    static vector<CKdvDispEvent*> m_vpDispEvent;	// ��Ϣ�ַ���
    u16     m_dwWaitingEvents;						// ���ڵȴ�Ӧ�����Ϣ
    CKdvDispEvent      *m_pCurDispEvent;			// ���ڴ������Ϣ��Ӧ����Ӧ���ָ��
	u32             m_dwInstID;						//ʵ��ID
	u32             m_dwAppID;						//ԴAPP ID
	u32             m_dwDesAppID;					//Ŀ��APP ID
	SEMHANDLE		m_hSem;							//��webǰ̨ͨ���������ڱ������������ͨ�ţ���������postMsg���Ͽ�
};

#define PTR_MSGDRIVER CMsgDriver::GetSingletonPtr()

#endif //MSGDRIVER_H
