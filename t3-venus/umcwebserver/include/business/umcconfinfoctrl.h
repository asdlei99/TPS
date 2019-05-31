/*****************************************************************************
ģ����      : CUmcConfinfoCtrl
�ļ���      : umcconfinfoctrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ������Ϣҵ����
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/09/17  1.0         ʯ��        ����
******************************************************************************/
#ifndef UMCCONFINFOCTRL_H
#define UMCCONFINFOCTRL_H


class CUmcConfinfoCtrl : public CKdvDispEvent, public ISingleTon<CUmcConfinfoCtrl>
{
public:
	CUmcConfinfoCtrl();
	virtual ~CUmcConfinfoCtrl();

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
	* ����:	��ȡ�����б�����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebListconfGetReq(const boost::any& arg);

	/**
	* ����:	�᳡�б��ȡ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcListMtGetReq(const boost::any& arg);

	/**
	* ����:	�Ҷϻ�������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebHangupconfReq(const boost::any& arg);

	/**
	* ����:	����˫������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperStartdualReq(const boost::any& arg);

	/**
	* ����:	�ر�˫������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperStopdualReq(const boost::any& arg);

	/**
	* ����:	ָ������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperApplyspeakerReq(const boost::any& arg);

	/**
	* ����:	��������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperQuietReq(const boost::any& arg);

	/**
	* ����:	��������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperMuteReq(const boost::any& arg);

	/**
	* ����:	�Ҷ�����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperDropReq(const boost::any& arg);

	/**
	* ����:	��������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperCallReq(const boost::any& arg);

	/**
	* ����:	ѡ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcEpoperSelviewReq(const boost::any& arg);

	/**
	* ����:	��ȡѡ����Ϣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcSelviewInfoGetReq(const boost::any& arg);
	



	/********************���������Ϣ - begin**************************************/

	/**
	* ����:		ˢ�� �������-������Ϣ ֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConfinfoInfoNtyReq(const boost::any& arg);

	/**
	* ����:		ˢ�� �������-������Ϣ-��ѯ�б� ֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConfinfoPollingListNtyReq(const boost::any& arg);

	/**
	* ����:		ˢ�� �������-������Ϣ-�����б� ֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConfinfoDiscussListNtyReq(const boost::any& arg);

	/**********************���������Ϣ - end**************************************/

	/**********************������ѯ - begin****************************************/
	/**
	* ����:		��ͣ���ָ���ѯ ����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebSuspendTurnReq(const boost::any& arg);

	/**
	* ����:		�������ر���ѯ ����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebStartTurnReq(const boost::any& arg);

	/**
	* ����:		������ѯ�б� ����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebUpdateTurnReq(const boost::any& arg);

	/**********************������ѯ - end******************************************/

	/**********************�������� - begin****************************************/
	/**
	* ����:		�������������͹ر� ����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebAuxMixVacSwitchReq(const boost::any& arg);

	/**
	* ����:		��Ӻ�ɾ�����۳�Ա���������ã�����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebUpdateAudMixInfoReq(const boost::any& arg);
	
	/**
	* ����:		�����͹ر����ۣ������͹ر����������� ���߷������£��������۳�Ա ����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebStartAuxMixReq(const boost::any& arg);

	/**********************�������� - end******************************************/

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* ����:	UMS֪ͨUMC���ӻ����б�
	* @return  void
	* @event evtp_AddConfList_Notify
	*/
	void OnAddConfListNotify( const CMessage& cMsg );

	/**
	* ����:	UMS֪ͨUMC����᳡�б�
	* @return  void
	* @event evtp_UpdateConfCnsList_Notify
	*/
	void OnUpdateConfCnsListNotify( const CMessage& cMsg );

	/**
	* ����:	CMS����UMS�Ҷϻ�����
	* @return  void
	* @event evtp_HungUpConf_result
	*/
	void OnHungUpConfRsp( const CMessage& cMsg );

	/**
	* ����:	UMS֪ͨUMCɾ���Ļ����б�
	* @return  void
	* @event evtp_DelConflist_Notify
	*/
	void OnDelConfListNotify( const CMessage& cMsg );

	/**
	* ����:	������˫�����
	* @return  void
	* @event evtp_StartDual_Ind
	*/
	void OnStartdualRsp( const CMessage& cMsg );

	/**
	* ����:	����ر�˫�����
	* @return  void
	* @event evtp_StopDual_Ind
	*/
	void OnStopdualRsp( const CMessage& cMsg );

	/**
	* ����:	UMS֪ͨCMS˫��Դ�ı�
	* @return  void
	* @event evtp_DualEp_Notify
	*/
	void OnDualNotify( const CMessage& cMsg );

	/**
	* ����:	UMS֪ͨUMCָ�������˽��
	* @return  void
	* @event evtp_ApplySpeaker_result
	*/
	void OnSpeakerRsp( const CMessage& cMsg );

	/**
	* ����:	UMS֪ͨUMC�����˸ı�
	* @return  void
	* @event evtp_SpeakerChange_Notify
	*/
	void OnSpeakerNotify( const CMessage& cMsg );

	/**
	* ����:	UMCָ��Զ�˾�����Ӧ
	* @return  void
	* @event evtp_QuietEp_Ind
	*/
	void OnQuietRsp( const CMessage& cMsg );

	/**
	* ����:	 UMCָ��Զ��������Ӧ
	* @return  void
	* @event evtp_MuteEp_Ind
	*/
	void OnMuteRsp( const CMessage& cMsg );

	/**
	* ����:	 UMC����UMS�Ҷ�EP���
	* @return  void
	* @event evtp_DropEp_Ind
	*/
	void OnDropRsp( const CMessage& cMsg );

	/**
	* ����:	 UMC����UMS�����Ѿ����ڵ�EP���
	* @return  void
	* @event evtp_CallExistEP_result
	*/
	void OnCallRsp( const CMessage& cMsg );

	/**
	* ����:	 ֪ͨUMC��ѡ��״̬
	* @return  void
	* @event ev_UMS_UMC_SelView_Ntfy
	*/
	void OnSelViewNotify( const CMessage& cMsg );

	/**
	* ����:	 UMS->UMC��ѡ����Ӧ
	* @return  void
	* @event ev_UMS_UMC_SelView_Ind
	*/
	void OnSelViewRsp( const CMessage& cMsg );

	/**********************������ѯ - begin**************************************/
	/**
	* ����		UMS֪ͨUMC������ѯ�б�(ums -> fcgi)
	* @return	void
	* @event	evtp_UpdateConfTurnlist_Notify
	*/
	void OnUpdateConfTurnlistNotify( const CMessage& cMsg );

	/**
	* ����		UMC����UMS������ѯ�б��Ӧ(ums -> fcgi)
	* @return	void
	* @event	evtp_UpdateTurn_ind
	*/
	void OnUpdateTurnInd( const CMessage& cMsg );

	/**
	* ����		UMC����UMS������ѯ��Ӧ(ums -> fcgi)
	* @return	void
	* @event	evtp_StartTurn_ind
	*/
	void OnStartTurnInd( const CMessage& cMsg );

	/**
	* ����		UMC����UMS�ر���ѯ��Ӧ(ums -> fcgi)
	* @return	void
	* @event	evtp_StopTurn_ind
	*/
	void OnStopTurnInd( const CMessage& cMsg );

	/**
	* ����		UMC����UMS��ͣ��ͣ��ѯ��Ӧ(ums -> fcgi)
	* @return	void
	* @event	evtp_SuspendTurn_ind
	*/
	void OnSuspendTurnInd( const CMessage& cMsg );

	/**
	* ����		UMS֪ͨUMC��ѯ״̬(ums -> fcgi)
	* @return	void
	* @event	evtp_TurnStat_ntfy
	*/
	void OnTurnStatNotify( const CMessage& cMsg );

	/**********************������ѯ - end****************************************/

	/**********************�������� - begin**************************************/
	/**
	* ����		UMS֪ͨUMC���������б�(ums -> fcgi)
	* @return	void
	* @event	evtp_AuxMixInfo_Notify
	*/
	void OnAuxMixInfoNotify( const CMessage& cMsg );

	/**
	* ����		UMC����UMS��Ӻ�ɾ�����۳�Ա��Ӧ(��������)(ums -> fcgi)
	* @return	void
	* @event	evtp_UpdateAudMixInfo_Ind
	*/
	void OnUpdateAudMixInfoInd( const CMessage& cMsg );

	/**
	* ����		UMC����UMS�����͹ر����ۣ������͹ر����������� ���߷������£��������۳�Ա��Ӧ(ums -> fcgi)
	* @return	void
	* @event	evtp_StartAuxMix_ind
	*/
	void OnStartAuxMixInd( const CMessage& cMsg );

	/**
	* ����		�������������͹رջ�Ӧ(ums -> fcgi)
	* @return	void
	* @event	ev_AuxMixVacSwitchInd
	*/
	void OnAuxMixVacSwitchInd( const CMessage& cMsg );

	/**********************�������� - end****************************************/


	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/

private:
	/*******************************************************************************
	----------------function that post msg to server:begin--------------------------
	*******************************************************************************/

	/**********************������ѯ - begin**************************************/
	/**
    * ����:				UMC����UMS������ѯ�б�(fcgi -> ums)
	* @param [in]		tConfTurnInfo
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_UpdateTurn_cmd
	                    Ӧ�ظ� ums->fcgi: evtp_UpdateTurn_ind
	*/
	u16 UpdateTurnReq( const TConfTurnInfo &tConfTurnInfo );

	/**
    * ����:				UMC����UMS������ѯ(fcgi -> ums)
	* @param [in]		wConfID
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_StartTurn_cmd
	                    Ӧ�ظ� ums->fcgi: evtp_StartTurn_ind
	*/
	u16 StartTurnReq( const u16 wConfID );

	/**
    * ����:				UMC����UMS�ر���ѯ(fcgi -> ums)
	* @param [in]		wConfID
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_StopTurn_cmd
	                    Ӧ�ظ� ums->fcgi: evtp_StopTurn_ind
	*/
	u16 StopTurnReq( const u16 wConfID );

	/**
    * ����:				UMC����UMS��ͣ��ͣ��ѯ(fcgi -> ums)
	* @param [in]		wConfID
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_SuspendTurn_cmd
	                    Ӧ�ظ� ums->fcgi: evtp_SuspendTurn_ind
	*/
	u16 SuspendTurnReq( const u16 wConfID, const BOOL32 bSuspend );

	/**********************������ѯ - end****************************************/

	/**********************�������� - begin**************************************/
	/**
    * ����:				UMC����UMS��Ӻ�ɾ�����۳�Ա(��������)(fcgi -> ums)
	* @param [in]		tDiscussListOpr
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_UpdateAudMixInfo_cmd
	                    Ӧ�ظ� ums->fcgi: evtp_UpdateAudMixInfo_Ind��evtp_AuxMixInfo_Notify
	*/
	u16 UpdateAudMixInfoReq( const TDiscussListOpr& tDiscussListOpr );

	/**
    * ����:				UMC����UMS�����͹ر����ۣ������͹ر����������� ���߷������£��������۳�Ա(fcgi -> ums)
	* @param [in]		tConfAuxMixInfo
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_StartAuxMix_cmd
	                    Ӧ�ظ� ums->fcgi: evtp_StartAuxMix_ind��evtp_AuxMixInfo_Notify
	*/
	u16 StartAuxMixReq( const TConfAuxMixInfo& tConfAuxMixInfo );

	/**
    * ����:				�������������͹ر�(fcgi -> ums)
	* @param [in]		tConfAuxMixVacOpr
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: ev_AuxMixVacSwitch
	                    Ӧ�ظ� ums->fcgi: ev_AuxMixVacSwitchInd��evtp_AuxMixInfo_Notify
	*/
	u16 AuxMixVacSwitchReq( const TConfAuxMixVacOpr& tConfAuxMixVacOpr );

	/**********************�������� - end****************************************/

	/*******************************************************************************
	----------------function that post msg to server:end----------------------------
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

	/**
    * ����:	ͨ��confID ��ȡ ������Ϣ
	* @param [int]  wConfID	 ����ID
	* @return  TConfinfo*
	* @remarks  
	*/
    TConfinfo*  GetConfInfoByID( u16 wConfID );
	
	/**
    * ����:	ͨ��confID ɾ�� ������Ϣ
	* @param [int]  wConfID	 ����ID
	* @return  TRUE: ɾ���ɹ�, FALSE: ɾ��ʧ�� 
	* @remarks  
	*/
	BOOL DelConfInfoByID( u16 wConfID );

	/**
    * ����:	ͨ��wConfID��ѯ��Ӧ�������ѯ��Ϣ��֪ͨǰ��
	* @param [u16]  wConfID	 ����ID
	* @return u16
	* @remarks  
	*/
	u16 UmcwebRefreshConfinfoPollingList( const u16 wConfID );

	/**
    * ����:	ͨ��wConfID��ѯ��Ӧ�����������Ϣ��֪ͨǰ��
	* @param [u16]  wConfID	 ����ID
	* @return u16
	* @remarks  
	*/
	u16 UmcwebRefreshConfinfoDiscussList( const u16 wConfID );

public:
	void ShowConfinfo();

private:
	////////////////////data begin/////////////////////////////////////////////////////

	vector<TConfinfo> m_vecTConfinfo;			//������Ϣ

	////////////////////data end///////////////////////////////////////////////////////
};

#endif