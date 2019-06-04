#include "cnsSession.h"

class CCncPortDiagCtrl : public CCncPortDiagCtrlIF
{
public:
	CCncPortDiagCtrl( CCnsSession &cSession );
	~CCncPortDiagCtrl();

	//��ȡ����汾��Ϣ
	virtual s8* GetSoftVersionInfo();
	virtual EmCnModel GetEmCnModelInfo();
	//��Ƶ�ӿ���Ϣ
	virtual TTpAudioPortInfo* GetAudioPortInfo();							
	virtual	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo );
	virtual u16 SetMic10InfoCmd( const TTpMic10Info &tTPMic10Info );
	virtual u16 SetNoDeskAudioCmd( bool bNoDeskAudio );
	virtual	u16 DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo );		

	//��Ƶ���ýӿ�
	virtual const TTPMPAudioInfo& GetAudioInfo() const;
	virtual BOOL * GetWhiteNoiseInfo();
	virtual u16 SetAudioInfoCmd( const TTPMPAudioInfo* atAudioPortInfo );
	virtual u16 SetListenPortCmd( const EmAudMixType emAudMixtype, const u8 byAudMixVolume );
	virtual u16 SetAux2OutCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume );
	virtual	u16 DefaultAudioSetCmd( const TTPMPAudioInfo* atAudioPortInfo );
	virtual u16 DefaultListenPortSetCmd(const EmAudMixType emAudMixtype, const u8 byAudMixVolume);
	virtual u16 DefaultAux2OutSetCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume);
	virtual u16 SetAudioWhiteNoiseCmd(BOOL bIsOpen ,u32 dwWhiteNoisePort);

	//����Ƶ���ýӿ�
	virtual const TTPVideoInfoTool &GetMainAudioInfo( ) const;
	virtual u16 DefaultMainAudioCmd( const TTPVideoInfoTool* atAudioInfo );
	virtual u16 SetMainAudioInfoCmd( const TTPVideoInfoTool* ptAudioInfo );
	
	//��ʾԴ����
	virtual TVgaInfo *GetDisplaySourceInfo( );
	virtual TTPDualDisplayStrategy &GetDisplayStrategyInfo( );
	virtual	EmVgaType GetDefaultDisplay( );

	virtual u16 SetDefaultDemonStrationCmd( const TVgaInfo *ptDisplaySource, 
		const TTPDualDisplayStrategy *ptDualDisplayStrategy, 
		const EmVgaType emDefaultDisplay );

	u16 SetDemonStrationCmd( const TVgaInfo *ptDisplaySource,
		const TTPDualDisplayStrategy *ptDualDisplayStrategy, const EmVgaType emDefaultDisplay );
	//ͼ���������
	virtual u16 SetDefParameterCmd(const TTPImageAdjustParam * pImageAdjustParam );
	virtual TTPImageAdjustParam * GetImageParam();
	virtual u16 SetParameterCmd(const TTPImageAdjustParam * pImageAdjustParam );

	//��Ӻ�ɾ��·��
	virtual u16  RouteMngAddCmd( const TRouteCfg& tRouteCfg );
	virtual u16  RouteMngDelCmd( const TRouteCfg& tRouteCfg );

	//���綪����Ϣ
	virtual u16 LostPacketInfoReq();
	virtual const CString& GetLostPacketInfo()const;			

	//�ϴ���������
	virtual const TTPUpDownSpeedInfo& GetUpDownstreamRate()const;
	//ץ��
	virtual u16 SetCaptureStateCmd( const BOOL& bCapture ) const;
	//����
	virtual u16 SetSelectComCmd( const EmComType& emComType2, const EmComType& emComType3 ) const;

	//ѡ������Ƶ���󷽰�������
	virtual u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo );
	//��ȡ�˿���Ͻ��
	virtual const TTPVideoDiagInfo& GetVideoDiagInfo()const;
	virtual const TTPAudioDiagInfo& GetAudioDiagInfo()const;

	//��ȡ���簲ȫFTP��TELNET��Ϣ
	virtual const TTPFtpInfo& GetFtpInfo()const;
	virtual const TTPTelnetInfo& GetTelnetInfo()const;

	//ֹͣ��ϲ�������
	virtual u16 StopAVMatrixReq();

	//Tpad�б�
	virtual	const TTPTPadList& GetTpadList()const;								
	virtual	u16 UpdateTpadListReq();	

	//����cns
	virtual u16 RebootCns();

	//����T300
	virtual u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo );

	//ά������ˢ�½�������
	virtual u16 ReqRefresh();

	//��Ƶ��������������
	virtual u16 AudiotMixerCmd( const u8** aAudioMixerInfo );
	virtual u8* GetAudioMixerInfo();
	virtual u16 DefaultMixerCmd( const u8** aAudioMixerInfo );
	virtual	u16 SnapShotCmd( );
	//��Ƶ��������������
	virtual u16 AudioEqualizerCmd( const TTPEqualizer** atEqualizer );
	virtual TTPEqualizer* GetAudioEqualizer();
	virtual u16 DefaultEqCmd( const TTPEqualizer** atEqualizer );

	//���з�������ַ
	virtual u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );
	virtual const TTPCallSerInfo& GetCallServerInfo()const;

	//������������ַ
	virtual u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );
	virtual const TTPUpgradeSer& GetUpgradeSerInfo()const;

	virtual u16 SetDataConfSerCmd( const TTPDataConfInfo& tWBSerIp );

	virtual u16 SetMatrixSerCmd( const TTPMatrixServerInfo& tTPMatrixServerInfo);

	virtual u16 SetNtpSerCmd( const TTPNtpSer& tTpNtpSer);

	virtual u16 SetQtEncryptSerCmd( const TTpQtEncryptCfg& tTpQtEncryptCfg);

	//̨���ļ��ϴ��ɹ�֪ͨ
	virtual u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );

	//������ѡ��ʽ
	virtual u16 VideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetVideoFormatInfo()const;

	//��ʾ��ѡ��ʽ
	virtual u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetDualVideoFormatInfo()const;

	//��������
	virtual u16 CallRateCmd( const u16 wCallRate );
	virtual const u16 GetCallRate()const;

	//��ʾ����
	virtual u16 DualCallRateCmd( const u16 wDualCallRate );
	virtual const u16 GetDualCallRate()const;

	//������ѯ
	virtual u16 ConfPollCmd( const TTPPollInfo& tPollInfo );
	virtual const TTPPollInfo& GetConfPollInfo()const;

	//��������
	virtual u16 ConfDisCmd( const BOOL& bDis );
	virtual const BOOL& GetConfDisInfo()const;

	//��Ƶ��ʽ
	virtual u16 AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
	virtual const EmTpAudioFormat& GetAudioFormatInfo() const;

	//·������
	virtual void GetRouteInfoData( vector<TRouteCfg> &vecTRouteCfg )const;
protected:
	virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void OnLinkBreak(const CMessage& cMsg);

	void OnAudioPortInfoInd(const CMessage& cMsg);
	void OnSetDesktopMicInfoNty( const CMessage& cMsg );
	void OnSetDesktopMicInfoInd( const CMessage& cMsg );
	void OnSetMic10InfoInd( const CMessage& cMsg );
	void OnDefaultAudPortInd(const CMessage& cMsg);
	void OnLostPacketInfoRsp(const CMessage& cMsg);
	void OnUpDownstreamRateNty(const CMessage& cMsg);
	void OnAVMatrixInfoInd(const CMessage& cMsg);
	void OnTpadListRsp(const CMessage& cMsg);
	void OnTpadListNty(const CMessage& cMsg);

	void OnAudiotMixerInd(const CMessage& cMsg);
	void OnDefaulttMixerInd(const CMessage& cMsg);
	void OnAudioEqualizerInd(const CMessage& cMsg);
	void OnDefaultEqInd(const CMessage& cMsg);
	void OnUpgradeCnsInd(const CMessage& cMsg);
	void OnCallServerNty(const CMessage& cMsg);
	void OnCallServerInd(const CMessage& cMsg);

	void OnUpgradeSerNty(const CMessage& cMsg);
	void OnUpgradeSerInd(const CMessage& cMsg);

	void OnVideoFormatInd(const CMessage& cMsg);
	void OnDualVideoFormatInd(const CMessage& cMsg);

	void OnCallRateInd(const CMessage& cMsg);
	void OnDualCallRateInd(const CMessage& cMsg);

	void OnConfPollInd(const CMessage& cMsg);
	void OnConfDisInd(const CMessage& cMsg);

	void OnVerInfoNty(const CMessage& cMsg);
	void OnAudioFormatInd( const CMessage& cMsg );

	void OnStopAVMatrixRsp(const CMessage& cMsg);
    //���ݻ��������ipNty
    void OnWBServerNty( const CMessage& cMsg );
	void OnWBServerInd( const CMessage& cMsg );
	//���������ipNty
	void OnSetMatrixServerInfoNty( const CMessage& cMsg );
	void OnSetMatrixServerInfoInd( const CMessage& cMsg );
	//���Ӽ��ܷ�����ipNty
	void OnSetQtEntryptInfoNty( const CMessage &cMsg );
	void OnSetQtEncryptInfoInd( const CMessage &cMsg );
	//ʱ��ͬ��������
	void OnSetNtpServerInfoNty( const CMessage &cMsg );
	void OnSetNtpServerInfoInd( const CMessage &cMsg ); 
	//���簲ȫ
	void OnSetFtpStateNty( const CMessage &cMsg );
	void OnOpenFtpRsp( const CMessage &cMsg );
	void OnSetFtpInfoNty( const CMessage &cMsg );
	void OnSetFtpRsp( const CMessage &cMsg );
	void OnSetTelnetStateNty( const CMessage &cMsg );
	void OnOpenTelnetRsp( const CMessage &cMsg );
	void OnSetTelnetInfoNty( const CMessage &cMsg );
	void OnSetTelnetRsp( const CMessage &cMsg );

    const TTPDataConfInfo& GetWBSerIp() const;
	const TTpQtEncryptCfg& GetQtEncryptCfg() const;
	const TTPNtpSer& GetNtpSerIP() const;

	const TTPMatrixServerInfo& GetMatrixSerInfo() const;

	void OnAudioInfoInd(const CMessage& cMsg);

	void OnVedioPortNameInd(const CMessage& cMsg);

	void OnDefaultAudioSetInd(const CMessage& cMsg);

	void OnAudioWhiteNoiseRsp(const CMessage& cMsg);

	void OnUpdateWhiteNoise(const CMessage& cMsg);
	
	void OnSetMixTypeInd(const CMessage& cMsg);

	void OnSetAUX2InfoInd(const CMessage& cMsg);

	void OnVedioSourceInd(const CMessage& cMsg);

	void OnDefaultMainAudioInd( const CMessage& cMsg );

	void OnDisplaySourceInd( const CMessage& cMsg );

	void OnDefaultDisplaySourceInd(const CMessage& cMsg);

	void OnImageAdjustInd( const CMessage& cMsg );

	void OnDefaultImageAdjustInd( const CMessage& cMsg );
	void OnSnapShotInd( const CMessage& cMsg );

	//·������
	void OnSetRouteInfoNty( const CMessage& cMsg );
	void OnAddRouteInfoInd( const CMessage& cMsg );
	void OnDelRouteInfoInd( const CMessage& cMsg );

	//��������
	void OnSelectComInd( const CMessage& cMsg );
private:
	CCnsSession		*m_pSession;
	s8  m_achVerInfo[MAX_DEVICEVER_LEN];
	EmCnModel m_emCnModel;
	TTpAudioPortInfo	m_atAudioPortInfo[3];
	u8	m_aAudioMixerInfo[4];
	CString	m_strLostPacketInfo;
	TTPAudioDiagInfo	m_tAudioDiagInfo;
	TTPVideoDiagInfo	m_tVideoDiagInfo;
	TTPTPadList		m_tTPadList;
	TTPUpDownSpeedInfo		m_tUpDownSpeedInfo;

	TTPEqualizer     m_atEqualizer[3];
	TTPCallSerInfo   m_tCallSerInfo;
	TTPUpgradeSer	 m_tUpgradeSer;
	TTPVidForamt	 m_tVidForamt;
	TTPVidForamt	 m_tDualVidForamt;
	TTPPollInfo		 m_tPollInfo;
	EmTpAudioFormat  m_emAudioFormat;
	BOOL m_bDis;
	u16	 m_wCallRate;
	u16  m_wDualCallRate;

    TTPDataConfInfo m_tWBSerIp;
	TTPMatrixServerInfo m_tMatrixServerInfo;
	TTpQtEncryptCfg m_tTpQtEncryptCfg;
	TTPNtpSer  m_tTpNtpSerIp;
	TTPMPAudioInfo  m_tAudioSetInfo;
	BOOL m_bWhiteNoise[3];

	TTPVideoInfoTool m_tVideoSource;
	TVgaInfo         m_atDemoSourceName[5];
	TTPDualDisplayStrategy   m_tDisplayStrategy;
	EmVgaType        m_emDefaultDisplay;
	TVgaInfo		 m_tDefaultDemoSource;

	TTPImageAdjustParam m_atImageAdjust[3];

	TTPFtpInfo       m_tTPFtpInfo;
	TTPTelnetInfo    m_tTPTelnetInfo;

	vector<TRouteCfg>	m_vecTRouteCfg;		//·�������б�

	TTpMic10Info     m_tTpMic10Info;        //��ũ10��Ƶ����
};