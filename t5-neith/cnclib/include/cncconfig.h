// cncconfig.h: interface for the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
#define AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncConfig : public CCncConfigIF 
{
	friend class CCnsSession;
public:
	CCncConfig(CCnsSession &cSession);
	virtual ~CCncConfig();

	//ע��SIP����
	virtual u16 RegSipService( const TTPSipRegistrarCfg& tSipCfg );
	virtual u16 UnRegSipService();
	virtual const TTPSipRegistrarCfg& GetSipRegCfg() const;


    //ע��GK
    virtual u16 RegGk( const TTPGKCfg& tGkCfg );
    
 
    /** ����   ���GK����
	 *  @return tagTTPEthnetInfo ����������Ϣ
	 */
	virtual  const TTPGKCfg& GetGkCfg() const ;


	/** ����   ����CNS��Ϣ
	 *  @param[in] tInfo CNS��Ϣ  byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex, EmTpIpNameNatSyn em );

	virtual u16 SetMainCns( s8* pbyRoomName );

	virtual const s8* GetMainCnsName() const;

	//������������
	virtual const TTPEthnetInfo& GetEthnetCfg() const;
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg, EmTpIpNameNatSyn em );

	virtual const TTPCnsInfo& GetLocalCnsInfo() const;
	virtual const vector<TTPCnsInfo>& GetLocalCnsList() const;
    
	//����NAT����*******2012.11.1 JYY���
	virtual u16 UpdateNATCfg( const TTPNatCfg& cfg, EmTpIpNameNatSyn em );
	virtual const TTPNatCfg& GetNATCfg() const;

	//����ϵͳʱ��
    virtual u16 UpdateSysTime( const TTPTime& time );
    //��ȡϵͳʱ��
    virtual u16 ReqSysTime(); 

    //����˫��Դ�˿�
    virtual u16 SelDualInputPort( EmVgaType emType );
    virtual u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault = FALSE );

    virtual const TDualSrcInfo& GetDualSrcInfo() const;
    virtual const TTPVgaMixInfo& GetVgaMixInfo() const;

	//����ϵͳ�����˿�
	virtual u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );
	virtual const TCenDevSleepInfo& GetSysSleepInfo() const;

	/**
    * ����:	 	        ���������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        �����޸���������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

	/** 
	* ����  ��ȡ������Ϣ
	* @param [in]  
	* @return  
	*/
	virtual void GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const;

	/** 
	* ����  ����SIPע����Ϣ
	* @param [in]  
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType );

	/** 
	* ����  ��ȡCnsע����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual const vector<TAddrInfo>& GetCnsRegInfo() const;

	/** 
	* ����  ��ȡUmsע����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual const vector<TTPAlias>& GetUmsRegInfo() const;

	/** ����   ���ȫ���������Ϣ
	 *  @return TDualSrcInfoȫ���������Ϣ
	 */
    virtual const TPanCamInfo& GetPanCamInfo() const;
		/**��ȡ��ǰȫ�������״̬���Ƿ���
	*  @param[in] 
	*  @return BOOL �Ƿ�Ϊ����
	*/
	virtual BOOL32 IsLocalCnsPanCam() const; 

	/**���ػ᳡ȫ�������״̬ ����
	*  @param[in] Quite �Ƿ���
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetLocalCnsPanCam( u8 wCamId ,BOOL bPanCam = TRUE);
//���ݻ������
	virtual u16 SetDataServerInfoCmd( u32 dwIp );
	const TTPDataConfInfo& GetWBSerIp() const;
	void OnWBServerNty( const CMessage& cMsg ) ;
	void OnWBServerInd( const CMessage& cMsg ) ;
	/** 
	* ����  ����ƵԴ����
	* @param [in]  
	* @return  
	*/
	virtual u16 SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID );
	virtual const map<u16, EmTPMtVideoPort>& GetMainVideoPort() const;
	virtual const TTPVideoInfoTool& GetVedioInfo() const{ return m_tTPVideoInfoTool;};
	void OnSetLocalCnsPanCamNty( const CMessage &cMsg );
	/** ����   ����ȫ���������ǰѡ�б��
	*  @param[in] wIndex ��ǰѡ�б��
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetPanCamSelectIndex( u8 wIndex );

	/** ����   ȫ�����������PT
	*  @param[in] emDirection�� ����  emCnAction������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction );

		/** ����   ȫ���������Ұ����
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetPanCamView( EmZoom emZoom, EmCnAction emCnAction );

		/** ����   ȫ���������������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetPanCamLight( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** ����   ȫ����������ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** ����   ȫ��������Զ����ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetPanCamAotoFocus();
		/** 
	* ����  ȫ�����������Ԥ��λ
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	virtual u16 SavePanCamPreset(  u8 wID ); 
	 /** 
	* ����  ȫ�����������Ԥ��λ
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	virtual u16 ImpelPanCamPreset(  u8 wID );
		 /** 
	* ����  ȫ�������ɾ��Ԥ��λ
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	virtual u16 DeletePanCamPreset(  u8 wID );
	/** 
	* ����  ȫ�������Ԥ��λ���޸�
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	virtual u16 SavePanCamPresetName(  u8 wID ,TPanCamName tPanCamName);

	/**��ȡ��ǰ����ü�״̬���Ƿ���
	*  @param[in] 
	*  @return BOOL �Ƿ���
	*/
	virtual BOOL32 IsVidCutLine() const; 
	/** 
	* ����  ���û���ü�
    * @param [in]  BOOL bIsVidCutLine �Ƿ���
	* @return  
	* @remarks 
	*/
	virtual u16 SetVidCutLine( BOOL bIsVidCutLine );

	/** ����   �������Ӽ���
	 *  @return
	 */
	virtual u16 SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt);
	/** ����   ������Ӽ�����Ϣ
	 *  @return TTpQtEncryptCfg���Ӽ�����Ϣ
	 */
    virtual const TTpQtEncryptCfg& GetQTEncrypt() const;

	/**
    * ����:	 	        ʱ��ͬ������
 	* @param [in]       
 	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
 	*/
 	virtual u16  SetTimeSynchroCmd( BOOL bIsCheck );
	//���������������
	virtual u16 SetTpadPasswordUpdate(TTpPasswordUpdateInfo tTpPasswordUpdateInfo);
	//��ȡ�������������Ϣ
	virtual const TTpPasswordUpdateInfo& GetPasswordUpdateInfo()const;

    //��������Ա��Ϣ
    virtual u16 SetSuperadmninInfo(TTpSuperUser tTpSuperUser);
    virtual const TTpSuperUser& GetSuperadmninInfo() const;
    virtual u16 UnlockAllUser();

    //����IPV6����
    virtual u16 SetIpv6Cfg( TTPEthnetIPV6Info tTPEthnetIPV6Info, EmTpIpNameNatSyn emTpIpNameNatSyn);
    //��ȡIPV6����
    virtual const TTPEthnetIPV6Info GetIpv6Cfg();
    //����IPV6����
    virtual u16 SetIpvType( EmProtocolVersion emProtocolVer );
    //��ȡIPV6����
    virtual const EmProtocolVersion GetIpvType();

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void UpdateCnsList( TTPCnsInfo tCnsInfo );

	//��Ϣ����
	void OnLinkBreak(const CMessage& cMsg);
	void OnCnsInfoNty(const CMessage& cMsg);
	void OnRegSipNty(const CMessage& cMsg);	
	void OnEthnetInfoInd(const CMessage& cMsg);
	void OnMainCnsInd(const CMessage& cMsg);
	//void OnCnsOnlineNty(const CMessage& cMsg);
	void OnCnsOfflineNty(const CMessage& cMsg);
    void OnSysTimeRsp(const CMessage& cMsg);
	void OnRegResultNty(const CMessage& cMsg);
	void OnRegResultFailNty(const CMessage& cMsg);
    void OnRegGkRsp(const CMessage& cMsg);
    void OnRegGkNty(const CMessage& cMsg);

	void OnSysSleepNty(const CMessage& cMsg);
	void OnRegNatNty(const CMessage& cMsg);
    void OnSetDualPortNameInd(const CMessage& cMsg);
    void OnSelDualInputPortInd(const CMessage& cMsg);
    void OnVgaInfoNty(const CMessage& cMsg);
    void OnConfVgaInfoNty(const CMessage& cMsg);
	void OnVidCurLineInd(const CMessage& cMsg);

    //Ipv6����
    void OnCfgEthnetIPV6Ind(const CMessage& cMsg);
    void OnIPVtpyeInd(const CMessage& cMsg);

	/**
    * ����:	  �������֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnAddNetMngInd(const CMessage& cMsg);
 
	/**
    * ����:	  ɾ������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnDelNetMngInd(const CMessage& cMsg);

	/**
    * ����:	  �޸�����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnModifyNetMngInd(const CMessage& cMsg);

	/**
    * ����:	  ������Ϣ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnNetMngNty(const CMessage& cMsg);

	//ע����Ϣ��Ϣ����
	void OnRegInfoRsp(const CMessage& cMsg);
	void OnRegInfoNty(const CMessage& cMsg);
	void OnGetGkRegInfo(const CMessage& cMsg);
	void OnGetCnsRegInfo(const CMessage& cMsg);
	void OnGetUmsRegInfo(const CMessage& cMsg);

	//����Ƶ���û�Ӧ
	void OnMainVideoPort(const CMessage& cMsg);

	//ȫ���������Ϣ
	void OnPanCamCfgNty(const CMessage& cMsg);
	//ȫ�����������Ԥ��λ���
	void OnPanCamSavePresetInd(const CMessage& cMsg);
	//ȫ�������ɾ��Ԥ��λ���
	void OnPanCamDeletePresetInd(const CMessage& cMsg);
	//ȫ�����������Ԥ��λ���
	void OnPanCamImplePresetInd(const CMessage& cMsg);
	//ȫ��������޸�Ԥ��λ���Ʊ�����
	void OnPanCamSavePresetNameInd(const CMessage& cMsg);	
	//ȫ�������ѡ����
	void OnPanCamSelInd(const CMessage& cMsg);	
	//��ƵԴ״̬֪ͨ �Ƿ�����ƵԴ dyy 2015-6-17
	void OnVidSrcNty(const CMessage& cMsg);
	//����Ƶ����֪ͨ
	void OnVedioInfoNty(const CMessage& cMsg);

	//���Ӽ���
	void OnSetQTEncryptInd(const CMessage& cMsg);
	void OnSetQTEncryptNty(const CMessage& cMsg);

	//ʱ��ͬ��
	void OnCnSysTimeToCncNty(const CMessage& cMsg);
	void OnCnNtpIsUsedInd(const CMessage& cMsg);

	//�������ڸ���
	void OnCnTpadPasswordUpdateNty(const CMessage& cMsg);
	void OnCnTpadPasswordUpdateInd(const CMessage& cMsg);

    //��������Ա��Ϣ
    void OnSuperadminNty(const CMessage& cMsg);
    void OnSuperadminInd(const CMessage& cMsg);

    //�������һ�ε�¼
    void OnFirstLoginAfterUpdateNty(const CMessage& cMsg);

private:
	CCnsSession        *m_pSession;
	TTPEthnetInfo       m_tEthnetInfo;       //������Ϣ
	TTPSipRegistrarCfg  m_tSipCfg;           //SIPע����Ϣ
	TTPCnsInfo          m_tLocalCnsInfo;     //����CNS��Ϣ
	vector<TTPCnsInfo>  m_vctCnsList;        //��CNS�б�
	s8                  m_achMainRoom[TP_MAX_ALIAS_LEN+1];  //���᳡��
    TTPGKCfg            m_tGkCfg;            //GK����
    TDualSrcInfo        m_tDualSrcInfo;      //˫��Դ��Ϣ
	TCenDevSleepInfo    m_tCenDevSleepInfo;  //ϵͳ������Ϣ
	TTPNatCfg			m_tNATCfg;			 //NAT��Ϣ
	TTPVgaMixInfo       m_tVgaMixInfo;       //��ʾԴ����ӿ���Ϣ

	vector<TTPNMServerCfg>	m_vecTTPNMServerCfg;		//���ܷ�������Ϣ

	vector<TAddrInfo>  m_vctGkRegInfo;
	vector<TAddrInfo>  m_vctCnsRegInfo;
	vector<TTPAlias>   m_vctUmsRegInfo;

	TTPDataConfInfo    m_tWBSerIp;
	map<u16, EmTPMtVideoPort> m_mapEmTPMtVideoPort;
	TPanCamInfo  m_tPanCamInfo;//ȫ���������Ϣ 
	BOOL32           m_bLocalPanCam;	//�Ƿ���ȫ�������
	BOOL32             m_bVidCutLine;//�Ƿ�������ü�
	TTPVideoInfoTool m_tTPVideoInfoTool;//����Ƶ������

	//���Ӽ���
	TTpQtEncryptCfg m_tQTEncrypt;
	TTPTime         m_tTPTime;

	//�������ڸ���
	TTpPasswordUpdateInfo m_tTpPasswordUpdateInfo;
    //��������Ա��Ϣ
    TTpSuperUser m_tTpSuperUser;

    //GKע�����
    TUCSipRegResult m_tUCSipRegResult;

    EmProtocolVersion   m_emProtocolVersion; //IPV����
    TTPEthnetIPV6Info	m_tTPEthnetIPV6Info; //IPV6����
};

#endif // !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
