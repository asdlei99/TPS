/*=======================================================================
ģ����      : CKdvDispEvent
�ļ���      : kdvdispevent.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���ӿڻ��࣬��Ҫ���ڷַ���Ϣ
����        : ������
�汾        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾  �޸���  �޸�����
2006/08/22  3.0   ������    ����
2013/11/03  4.0   ����ӡ    linuxƽ̨��ֲ fcgi��Ϣͨ���߼���չ
=======================================================================*/
#ifndef __DISPEVENT_H__
#define __DISPEVENT_H__

#define TYPE_CMESSAGE  0         // һ���CMessage��Ϣ
#define TYPE_TPMSG     1         // �շ�����ϢΪCTPMSG ,��Ҫ������Ϣ���͵�ת��

class CKdvDispEvent
{
public:
    typedef void(CKdvDispEvent::*DISPEVENT_PFUN)(const CMessage & cMsg);
    typedef void(CKdvDispEvent::*DISPEVENT_REQ_PFUN)(const boost::any& arg);		//by ldy 2013.11.03��չ
public:
    CKdvDispEvent();
    virtual ~CKdvDispEvent();
    // �ж�һ��Ϣ�Ƿ��ڱ�����ע���
    BOOL HasRegEvent(u16 wEvent) const;
    // �ַ���Ϣ���������Ӧ����ĺ����ĵ��ã�������������ѵĵ���
    virtual void DispEvent(const CMessage &cMsg) = 0;

	// �ж�һ��Ϣ�Ƿ��ڱ�����ע���
    BOOL HasRegReqEvent(u16 wEvent) const;
	// �ַ���Ϣ���������Ӧ����ĺ����ĵ��ã�������������ѵĵ���
	virtual void DispReqEvent( u16 wEvent, const boost::any& arg ) = 0;

    // ��Ϣ��ʱ����Ӧ����ʱδ����ʱ����
    //virtual void OnTimeOut(u16 wEvent) = 0;

protected:
    // ��һ����Ϣ���䴦����ע�����
    void RegDispFunPointer(u16 wEvent, DISPEVENT_PFUN pFun);
    // ��յ�����ע�����Ϣ
    void ClearDisp();

    // ��һ����Ϣ���䴦����ע�����
    void RegDispReqFunPointer(u16 wEvent, DISPEVENT_REQ_PFUN pFun);

protected:
	// 4.0 �޸�Ϊֻ�����¼���Id
	std::map<u16, DISPEVENT_PFUN> m_mappFun;			//���ڻ�Ӧ�ķַ�		ums->ҵ����
	std::map<u16, DISPEVENT_REQ_PFUN> m_mappReqFun;		//����������Ϣ���͵�ӳ��	fcgi->ҵ����  by ldy 2013.11.03��չ

};

//ע���Ӧ��Ϣӳ��
#define REG_PFUN(event, fun)	\
    RegDispFunPointer(event, (void(CKdvDispEvent::*)(const CMessage &cMsg))fun);

//�ַ���Ϣӳ��
#define DISP_FUN(clsName, cMsg)	\
if(m_mappFun.find(cMsg.event) != m_mappFun.end())	\
{	\
   (this->*(void(clsName::*)(const CMessage &cMsg))(m_mappFun[cMsg.event]))(cMsg);	\
}

//ע��������Ϣӳ��		by ldy 2013.11.03��չ
#define REG_REQ_PFUN(event, fun)	\
RegDispReqFunPointer(event, (void(CKdvDispEvent::*)(const boost::any& arg))fun);

//�ַ���Ϣӳ��
#define DISP_REQ_FUN(clsName, event, arg )	\
	if(m_mappReqFun.find(event) != m_mappReqFun.end())	\
{	\
	   (this->*(void(clsName::*)(const boost::any& arg))(m_mappReqFun[event]))( arg );	\
}

#endif