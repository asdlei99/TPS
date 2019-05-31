/*****************************************************************************
ģ����      : CUmcSession
�ļ���      : umcsession.h
����ļ�    : 
�ļ�ʵ�ֹ���: һ��umc�ĻỰ,1.����umc 2.����������ӹ��̣��ж����򷢳�֪ͨ 3.��������ֱ�Ӻ�umc�����Ľӿڣ�������Ϣ�ȣ�
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/08/11  1.0         ʯ��        ����
******************************************************************************/
#ifndef UMCSSESSIONCTRL_H
#define UMCSSESSIONCTRL_H

#include "umcaddrbookctrl.h"
#include "umcconfinfoctrl.h"
#include "umcsyscfgctrl.h"
#include "umcconftemplatectrl.h"

class CUmcSessionCtrl : public CKdvDispEvent, public ISingleTon<CUmcSessionCtrl>
{
public:
	CUmcSessionCtrl();
	virtual ~CUmcSessionCtrl();

public:
	/**
	* ����:	�ַ���Ϣ���������Ӧ����ĺ����ĵ��ã�������������ѵĵ���
	* @param [in]  ��Ϣ
	* @return  ��
	* @remarks server->����ҵ����(ͨ��CMsgDriverת��)
	*/
	virtual void DispEvent(const CMessage &cMsg);

	/**
	* ����:	�ַ���Ϣ���������Ӧ����ĺ����ĵ��ã�������������ѵĵ���
	* @param [in]  ��Ϣ
	* @return  ��
	* @remarks client->����ҵ����(ͨ��CMsgDriverת��)
	*/
	virtual void DispReqEvent( u16 wEvent, const boost::any& arg );

private:
	/*******************************************************************************
	----------------function that handle msg from client:begin----------------------
	*******************************************************************************/

	/**
	* ����:	��������DCS����������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnConnectUmsReq(const boost::any& arg);

	/**
	* ����:	����֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	* @eg: "{\"event\":\"ev_dcweb_OSP_DISCONNECT_nty_req\"}"
	*/
	u16 OnLinkBreakReq(const boost::any& arg);

	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

    void  OnConnectUmsRsp( const CMessage& cMsg );		//���ӵ�DCS��������Ӧ
	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/

public:
	/**
	* ����:	��ѯ�Ƿ�������
	* @return  TRUE 	������    FALSE	û������
    */
	BOOL IsConnected();

	CUmcConfinfoCtrl* GetUmcConfinfoCtrl(){ return m_pConfinfoCtrl; };
	CUmcSysCfgCtrl* GetUmcSysCfgCtrl(){ return m_pSysCfgCtrl; };
	CUmcConfTemplateCtrl* GetUmcConfTemplateCtrl(){ return m_pConfTemplateCtrl; };

private:
	/**
	* ����:	��ʼ��OSP,����app 
	* @return  �ɹ�����0��ʧ�ܷ��ش�����  
	*/
	virtual u16 InitializeLib( u16 wAppID, u16 wDesAppID );

	/**
	* ����:	�����������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 ConnectToUms( string strUsr, string strPwd );

	/**
	* ����:	�Ͽ��������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	��û�����ӵ�������ʱ���ô˷����������κ�����
	*/
	u16 DisConnect() ; 
 
	/**
	* ����:	ע��msg from server��Ϣ
	* @return  ��
	*/
	void  BuildEventsMap();

	/**
	* ����:	ע��msg from client��Ϣ
	* @return  ��
	*/
	void  BuildReqEventsMap();
	
	/**
	* ����:	ע���ӡ��Ϣ
	* @return  ��
	*/
	void  MappingEventName();

	/**
	* ����:	�������
	* @return  ��
	*/
	void ClearData();

public:
	BOOL m_bRefresh;		//�Ƿ���Ҫ��ʱ����ǰ��

private:
	////////////////////data begin/////////////////////////////////////////////////////

	BOOL32 m_bLogin;        //�Ƿ��Ѿ���¼

	/////////////////ҵ����////////////////////
	CUmcAddrbookCtrl *m_pAddrbookCtrl;
	CUmcConfinfoCtrl *m_pConfinfoCtrl;
	CUmcSysCfgCtrl *m_pSysCfgCtrl;
	CUmcConfTemplateCtrl *m_pConfTemplateCtrl;

	////////////////////data end///////////////////////////////////////////////////////
};


#define PTR_SESSION    CUmcSessionCtrl::GetSingletonPtr()     //Sessionʵ��ָ��
#endif