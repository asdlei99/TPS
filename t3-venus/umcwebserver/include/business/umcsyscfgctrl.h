/*****************************************************************************
ģ����      : CUmcSysCfgCtrl
�ļ���      : umcsyscfgctrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ϵͳ����ҵ����
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/10/17  1.0         ʯ��        ����
******************************************************************************/
#ifndef UMCSYSCFGCTRL_H
#define UMCSYSCFGCTRL_H


class CUmcSysCfgCtrl : public CKdvDispEvent, public ISingleTon<CUmcSysCfgCtrl>
{
public:
	CUmcSysCfgCtrl();
	virtual ~CUmcSysCfgCtrl();

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
	* ����:	����û�����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebAddUserReq(const boost::any& arg);

	/**
	* ����:	�޸���������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebChangePwdReq(const boost::any& arg);

	/**
	* ����:	ɾ���û�����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebDelUserReq(const boost::any& arg);

	/**
	* ����: �û���Ϣ֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebUserNtyReq(const boost::any& arg);

	/**
	* ����: �����������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebIpCfgReq(const boost::any& arg);

	/**
	* ����:	�������������֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebIpCfgNtyReq(const boost::any& arg);

	/**
	* ����: sip��������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebSipserverReq(const boost::any& arg);

	/**
	* ����: gk��������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebGkserverReq(const boost::any& arg);

	/**
	* ����:	sip����������֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebSipserverNtyReq(const boost::any& arg);

	/**
	* ����:	gk����������֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebGkserverNtyReq(const boost::any& arg);
	

	/**
	* ����:	ʱ��ͬ��������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebSetSysTimeReq(const boost::any& arg);	

	/**
	* ����:	��¼ʱ������ʱ��֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebGetSysTimeNtyReq(const boost::any& arg);

	/**
	* ����:	��/ɾ/�� ���ܷ�������Ϣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
//	u16 OnUmcwebNMServerReq(const boost::any& arg);	

	/**
	* ����:	���ܷ�������Ϣ֪ͨ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
//	u16 OnUmcwebNMServerNtyReq(const boost::any& arg);
	
	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* ����:	�����û�֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_UmsAddUser_Notify
	*/
	void OnAddUserNotify( const CMessage& cMsg );

	/**
	* ����:	�����û�֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_UmsUpdateUser_Notify
	*/
	void OnUpdateUserNotify( const CMessage& cMsg );

	/**
	* ����:	ɾ���û�֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_UmsDelUser_Notify
	*/
	void OnDelUserNotify( const CMessage& cMsg );

	/**
	* ����:	�����û��ظ���UMS->UMC��
	* @return  void
	* @event ev_UMSAddUserRet
	*/
	void OnAddUserRsp( const CMessage& cMsg );

	/**
	* ����:	�����û��ظ���UMS->UMC��
	* @return  void
	* @event ev_UMSChangePWDRet
	*/
	void OnChangePWDRsp( const CMessage& cMsg );

	/**
	* ����:	�����û��ظ���UMS->UMC��
	* @return  void
	* @event ev_UMSDelUserRet
	*/
	void OnDelUserRsp( const CMessage& cMsg );

	/**
	* ����:	�������������֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_UmsIPCfg_Ind
	*/
	void OnIPCfgNty( const CMessage& cMsg );

	/**
	* ����:	sip����������֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_umsreg_notify
	*/
	void OnSipserverNty( const CMessage& cMsg );

	/**
	* ����:	gk����������֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_umsGKReg_notify
	*/
	void OnGkserverNty( const CMessage& cMsg );

	/**
	* ����:	��ѯʱ����Ӧ��UMS->UMC��
	* @return  void
	* @event ev_UmsGetSysTime_Rsp
	*/
	void OnUmsGetSysTimeRsp( const CMessage& cMsg );

	/**
	* ����:	������Ϣ֪ͨ��UMS->UMC��
	* @return  void
	* @event ev_NMServer_nty
	*/
//	void OnNetMngNty( const CMessage& cMsg );

	/**
	* ����:	������ܷ�����Ӧ��UMS->UMC��
	* @return  void
	* @event ev_NMServerAdd_rsp
	*/
//	void OnAddNetMngRsp(const CMessage& cMsg);

	/**
	* ����:	�޸����ܷ�����Ӧ��UMS->UMC��
	* @return  void
	* @event ev_NMServerMdy_rsp
	*/
//	void OnModifyNetMngRsp(const CMessage& cMsg);

	/**
	* ����:	ɾ�����ܷ�����Ӧ��UMS->UMC��
	* @return  void
	* @event ev_NMServerDel_rsp
	*/
//	void OnDelNetMngRsp(const CMessage& cMsg);
	
	
	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/


private:
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
	* ����:	�������
	* @return  ��
	*/
	void ClearData();

public:
	void ShowSysCfginfo();

	/**
    * ����:	 	        ���� ���/�޸�/ɾ�� ��������(fcgi -> ums)
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_NMServerAdd_req
	*/
//	u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg );
//	u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg );
//	u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg );

	//���ܷ�������Ϣ����(fcgi -> ums)
//	void NetMngInfoReq( vector<TTPNMServerCfg>& vecTTPNMServerCfg );
	//���ܷ�������Ϣ֪ͨ(fcgi -> client)
//	void  NetMngInfoNty();

private:
	////////////////////data begin/////////////////////////////////////////////////////

	vector<CUserFullInfo> m_vecUser;			//�û��б�
	TTPEthnetInfo   m_tEthnet;					//�����������Ϣ
	TTPSipRegistrarCfg m_tSipRegCfg;			//sip����������
	TTPGKCfg m_tGKRegCfg;						//gk����������
	vector<TTPNMServerCfg> m_vecTTPNMServerCfg; //���ܷ�������Ϣ

	////////////////////data end///////////////////////////////////////////////////////
};

#endif