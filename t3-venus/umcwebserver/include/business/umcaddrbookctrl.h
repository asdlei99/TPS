/*****************************************************************************
ģ����      : CUmcAddrbookCtrl
�ļ���      : umcaddrbookctrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��ַ��ҵ����
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/08/20  1.0         ʯ��        ����
******************************************************************************/
#ifndef UMCADDRBOOKCTRL_H
#define UMCADDRBOOKCTRL_H

class CUmcAddrbookCtrl : public CKdvDispEvent, public ISingleTon<CUmcAddrbookCtrl>
{
public:
	CUmcAddrbookCtrl();
	virtual ~CUmcAddrbookCtrl();

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
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* ����:	ȫ�ֵ�ַ���ظ�
	* @return  void
	* @event ev_umsGetRegInfo_UmsRspEx
	*/
	void OnAddrbookGlobleUmsRsp( const CMessage& cMsg );

	void OnAddrbookGlobleCnsRsp( const CMessage& cMsg );

	void OnAddrbookGlobleMtRsp( const CMessage& cMsg );
	
	void OnAddrbookGlobleMcuRsp( const CMessage& cMsg );
	

	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/

private:
	/*******************************************************************************
	----------------function that handle msg from client:begin----------------------
	*******************************************************************************/
	/**
	* ����:	ȫ�ֵ�ַ��ˢ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGlobleRefreshReq(const boost::any& arg);

	/**
	* ����:	ȫ�ֵ�ַ����ȡ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGlobleGetReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ�������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemAddReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ�޸�����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemModReq(const boost::any& arg);
	
	/**
	* ����:	���ص�ַ����Ŀɾ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemDelReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ��ȡ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemGetReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ�����ȡ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemgroupGetReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ������������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemgroupSearchReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ��������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookItemNumberReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ�����ȡ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGroupGetReq(const boost::any& arg);
	
	/**
	* ����:	���ص�ַ�����������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGroupAddReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ�����޸�����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGroupModReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����ɾ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGroupDelReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ-���ϵ�������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookIgAddReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����Ŀ-���ϵɾ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookIgDelReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����-���ϵ�������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGgAddReq(const boost::any& arg);

	/**
	* ����:	���ص�ַ����-���ϵɾ������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	u16 OnAddrbookGgDelReq(const boost::any& arg);
	

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/

private:
	void  BuildEventsMap();
	void  BuildReqEventsMap();
	
	void ClearData();

	/**
	* ����:	��ȡ��Ŀ��Ϣ�����ݱ�������->���ض�Ӧ���ַ�����
	* @param tTPAlias��������pChName�����ƣ�pChNumber�����룬pChIp��ip
	* @return  void
	* @remarks	����Ϊǰ�˴��ݹ�����json����
	*/
	void GetItemInfo( TTPAlias tTPAlias, char *pChName, char *pChNumber, char *pChIp );

	/**
	* ����:	���±��ص�ַ�������ߡ�����״̬
	* @param 
	* @return  void
	*/
	void updAddrbookLocalState();

private:
	////////////////////data begin/////////////////////////////////////////////////////

	BOOL32			m_bIsEndSip;			//sip��ַ�Ƿ���ս���
	BOOL32			m_bIsEndGk;				//Gk��ַ�Ƿ���ս���

	////////////////////data end///////////////////////////////////////////////////////
};

#endif