/*****************************************************************************
ģ����      : CUmcConfTemplateCtrl
�ļ���      : umcconftemplatectrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ����ģ��ҵ����
����        : �컪��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/11/19  1.0         �컪��      ����
******************************************************************************/
#ifndef UMCCONFTEMPLATECTRL_H
#define UMCCONFTEMPLATECTRL_H


class CUmcConfTemplateCtrl : public CKdvDispEvent, public ISingleTon<CUmcConfTemplateCtrl>
{
public:
	CUmcConfTemplateCtrl();
	virtual ~CUmcConfTemplateCtrl();

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

	u16 GetResUsedCount(){ return m_wResUsedCount; };

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

private:
	/*******************************************************************************
	----------------function that handle msg from client:begin----------------------
	*******************************************************************************/

	/**
	* ����:		��ӻ���ģ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebAddConftemplateReq(const boost::any& arg);

	/**
	* ����:		���»���ģ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebUpdateConftemplateReq(const boost::any& arg);

	/**
	* ����:		ɾ������ģ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebDelConftemplateReq(const boost::any& arg);

	/**
	* ����:		ɾ��ȫ��ģ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebDelAllConftempReq(const boost::any& arg);

	/**
	* ����:		�ٿ���������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebStartConfTemplateReq(const boost::any& arg);

	/**
	* ����:		ˢ�»���ģ���б�֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConftempListNtyReq(const boost::any& arg);

	/**
	* ����:		ˢ�»���ģ�������Ϣ֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConftempInfoNtyReq(const boost::any& arg);

	/**
	* ����:		ˢ�»���ģ�����᳡�б�֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConftempMeetNameListNtyReq(const boost::any& arg);

	/**
	* ����:		ˢ�»���ģ����ѯ�б�֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConftempPollingListNtyReq(const boost::any& arg);

	/**
	* ����:		ˢ�»���ģ�������б�֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebRefreshConftempDiscussListNtyReq(const boost::any& arg);

	/**
	* ����:		��ǰ��Դ��֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebConfBasUsedNtyReq(const boost::any& arg);

	/**
	* ����:		��ȡԤԼ����֪ͨ������
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebConfmngListconfbookGetReq(const boost::any& arg);

	/**
	* ����:		У��ģ�����ơ������Ƿ��ظ� ����
	* @return	u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnUmcwebCheckConftempRepeatReq(const boost::any& arg);

	/*******************************************************************************
	----------------function that handle msg from client:end------------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* ����		��ӻ���ģ���б��֪ͨ(ums -> fcgi)
	* @return	void
	* @event	evtp_AddConftemplate_Notify
	*/
	void OnAddConfTempNotify( const CMessage& cMsg );

	/**
	* ����		�޸Ļ���ģ���б��֪ͨ(ums -> fcgi)
	* @return	void
	* @event	evtp_Updateconftemplate_Notify
	*/
	void OnUpdateConfTempNotify( const CMessage& cMsg );

	/**
	* ����		ɾ������ģ���б��֪ͨ(ums -> fcgi)
	* @return	void
	* @event	evtp_Delconftemplate_Notify
	*/
	void OnDelConfTempNotify( const CMessage& cMsg );

	/**
	* ����		ɾ��ȫ��ģ����ϢӦ��(ums -> fcgi)
	* @return	void
	* @event	ev_del_all_conftemp_rsp
	*/
	void OnDelAllConfTempRsp( const CMessage& cMsg );

	/**
	* ����		������ӡ�ɾ�����޸Ļ���ģ��Ļظ�(ums -> fcgi)
	* @return	void
	* @event	evpt_OperatorConfTemplate_Ret
	*/
	void OnOperateConfTempRsp( const CMessage& cMsg );

	/**
	* ����		�ٿ�������(ums -> fcgi)
	* @return	void
	* @event	evtp_StartConfTemplate_Ret
	*/
	void OnStartConfTemplateRsp( const CMessage& cMsg );

	/**
	* ����		���»���ģ����Դռ����(ums -> fcgi)
	* @return	void
	* @event	ev_conf_bas_used_nty
	*/
	void OnUpdateResUsedCountNotify( const CMessage& cMsg );

	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from server:end------------------------
	*******************************************************************************/

private:
	/*******************************************************************************
	----------------function that post msg to server:begin--------------------------
	*******************************************************************************/

	/**
    * ����:				��ӻ���ģ��(fcgi -> ums)
	* @param [in]		tConfTemp ����ģ�� 
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_AddConfTemplate_req
	                    Ӧ�ظ� ums->fcgi: evpt_OperatorConfTemplate_Ret
	                    ���ɹ��������� ums->fcgi: evtp_AddConftemplate_Notify
	*/
	u16 AddConfTemplateReq( const TTPConfTemplate &tConfTemp );

	/**
    * ����:				�޸Ļ���ģ��(fcgi -> ums)
	* @param [in]		tConfTemp ����ģ�� 
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   fcgi->ums: evtp_Updateconftemplate_Req
	                    Ӧ�ظ� ums->fcgi: evpt_OperatorConfTemplate_Ret
	                    ���ɹ��������� ums->fcgi: evtp_Updateconftemplate_Notify
	*/
	u16 ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp );

	/**
    * ����:				ɾ������ģ��(fcgi -> ums)
	* @param [in]		wConfTempID ����ģ��ID
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   fcgi->ums: evtp_DelConftemplate_Req
	                    Ӧ�ظ� ums->fcgi: evpt_OperatorConfTemplate_Ret
	                    ���ɹ��������� ums->fcgi: evtp_Delconftemplate_Notify
	*/
	u16 DeleteConfTemplateReq( const u16 wConfTempID );

	/**
    * ����:				ɾ��ȫ��ģ��(fcgi -> ums)
	* @param			��
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: ev_del_all_conftemp_req
	                    Ӧ�ظ� ums->fcgi: ev_del_all_conftemp_rsp
	*/
	u16 DelAllConfTempReq();

	/**
    * ����:				�ٿ�����(fcgi -> ums)
	* @param			wConfTemplateID ����ģ��ID
	* @return			u16 �ɹ�����0, ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��	fcgi->ums: evtp_StartConfTemplate_Req
	                    Ӧ�ظ� ums->fcgi: evtp_StartConfTemplate_Ret
	*/
	u16 StartTemplateConfReq( const u16 wConfTemplateID );

	/*******************************************************************************
	----------------function that post msg to server:end----------------------------
	*******************************************************************************/

private:
	//����ģ����Ϣ ptree - TTPConfTemplate ת��
	bool ChangePtreeToTTPConfTemplate( /*const*/ ptree& pte, TTPConfTemplate& tTPConfTemplate );

	//ͨ������ģ��ID���Ҹ�ģ����Ϣ
	bool FindConfTempInfoByID( const u16 wID, TTPConfTemplate& tTPConfTemplate );

	//ͨ���᳡ID���Ҹû᳡��Ϣ
//	u16 FindMeetIDByName( const TTPConfTemplate& tTPConfTemplate, const std::string& strMeetName, const std::string& strMeetNum );
	bool FindMeetInfoByID( const TTPConfTemplate& tTPConfTemplate, const u16 wEpID, TTpCallAddr& tTpCallAddr );
	
	//��ʽ����(std::string) - ����Ƶ��ʽ(TUmsVidFormat) ת��
	void ChangeNameToMainVideo( const u16 wMainCheckCount, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate );

	//��ʽ����(std::string) - ����Ƶ��ʽ(TUmsVidFormat) ת��
	void ChangeNameToMinorVideo( const u16 wMinorCheckCount, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate );

	//��ʽ����(std::string) - ��Ƶ��ʽ(EmTpAudioFormat) ת��
	void ChangeNameToAudioFormat( const u16 wAudFmtNum, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate );

private:
	////////////////////data begin/////////////////////////////////////////////////////
	std::vector<TTPConfTemplate> m_vecConfTempList;
	u16		m_wResUsedCount;	//��ǰ��Դ��
	////////////////////data end///////////////////////////////////////////////////////
};

#endif