#include "cnsSession.h"


class CCncCenterCtrl : public CCncCenterCtrlIF
{
public:
	CCncCenterCtrl(CCnsSession &cSession);
	virtual ~CCncCenterCtrl();

    /** 
	* ����  ����ϵͳ��Դ
	* @param [in]  emPower  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysPower( EmSchPower emPower );
    /** 
	* ����  ���õƹ�ȫ��
	* @param [in]  emLight  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetSysAllLight( EmSchLight emLight );
    /** 
	* ����  �������ƿ���
	* @param [in]  emMidLight  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetMainLight( EmSchMidLight emMidLight );
    /** 
	* ����  ���ø��ƿ���
	* @param [in]  emScrLight  ����
	* @return 
	* @remarks 
	*/
    virtual u16 SetAuxiLight( EmSchScrLight emScrLight );
    /** 
	* ����  ѡ����ӻ�
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SelectTV( u8 byIndex );
    /** 
	* ����  ���õ��ӻ���Դ
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode );
    /** 
	* ����  ���õ��ӻ�����ģʽ
	* @param [in]  emMode  ����ģʽ
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVAudVisMode( EmTVAudVisMode emMode );
    /** 
	* ����  ���õ��ӻ���ʾģʽ
	* @param [in]  emMode  ��ʾģʽ
	* @return 
	* @remarks 
	*/
    virtual u16 SetTVDisMode( EmTVDisplayMode emMode );
    /** 
	* ����  ���õ��ӻ�����ѡ��
	* @param [in]  emSelect  ����ѡ��
	* @return 
	*/
    virtual u16 SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect );
    /** 
	* ����  ��ȡ���ӻ�����
	* @return TCentreTVCfg*  ���ӻ���������ָ��
	*/
    virtual TCentreTVCfg* GetCentreTVCfg(); 

	/** 
	* ����  �л��ĵ����������
    * @param [in]  byIndex  ����
	* @return 
	*/
    virtual u16 SetDCamSelectIndex( u8 byIndex ) const;

    /** 
	* ����  �����ĵ����������
    * @param [in]  emPower  ����
	* @return 
	*/
    virtual u16 SetDCamPower( EmDCamPower emPower );
    /** 
	* ����  �����ĵ�������Զ��۽�ģʽ
	* @param [in]  emMode  ģʽ
	* @return 
	*/
    virtual u16 SetDCamAFMode( EmDCamAFMode emMode );
    /** 
	* ����  �����ĵ��������ƽ��ģʽ
	* @param [in]  emMode  ģʽ
	* @return 
	*/
    virtual u16 SetDCamWBMode( EmDCamWBMode emMode );
    /** 
	* ����  �����ĵ��������Ұ����
	* @param [in]  emZoom  ��Ұ
	* @return 
	*/
    virtual u16 SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction );
    /** 
	* ����  �����ĵ������Ԥ��λ
	* @param [in]  emNum  Ԥ��λ
	* @return 
	*/
    virtual u16 SetDCamPreset( EmDCamPresetNum emNum );
    /** 
	* ����  �����ĵ������Ԥ��λ
	* @param [in]  emNum  Ԥ��λ
	* @return 
	*/
    virtual u16 SetDCamRecall( EmDCamRecallNum emNum );

    /** 
	* ����  ���ȿյ��¶�
	* @param [in]  wTemp  �¶�
	* @return 
	*/
    virtual u16 SetACTemp( u8 byTemp );
    /** 
	* ����  ���ȿյ��¶�
	* @param [in]  wTemp  �¶�
	* @return 
	*/
    u16 SetACMode( EmCentreACMode emMode );
    /** 
	* ����  �����·����
	* @param [in]  byVol  ����
	* @return 
	*/
    virtual u16 SetACAirVol( EmCentreACAirVol emAirVol );
	/** 
	* ����  ���ȿյ������Դ����
	* @param [in] empower ��Դ����
	* @return 
	*/
 /*   virtual u16 SetAirPower( EmCentreACPower emPower );*/
    /** 
	* ����  ѡ��յ�
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SelectAir( u8 byIndex );
	/** 
	* ����  ��ȡ�յ���������
	* @return TCentreACCfg*  �յ���������ָ��
	*/
    virtual void GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const; 
    /** 
	* ����  ���ÿյ���Դ
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
    virtual u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode );
    /** 
	* ����  ����Ӧ�õ�����
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl );
	virtual BOOL* GetApplyToAllInfo();

	virtual u16 SetCentreTVModle( EmTVModle emTvMode);
	virtual u16 SetDisplayShowCmd( BOOL bDisplayShow);
	virtual u16 SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction );

	void GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName )const;
	virtual void GetDCamStateMap( map<u8, TCentreDCamCfg> &mapDCamCfg ) const;
	virtual void GetDCamState( TCentreDCamCfg &tCentreDCamCfg, u8 byIndex ) const;
	
	virtual u16 SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 );
	virtual const BOOL& GetDisplayState() const;
	virtual const TTPDisplayType& GetDisplayType1() const;
	virtual const TTPDisplayType& GetDisplayType3() const;

	virtual const BOOL& GetDisplayShowState() const;

	virtual const TCentreCurInfo& GetCurtainInfo( ) const;

	virtual	u16 SetPanCamNumber( const u8 &byPanCamNum ) const;
	virtual	u16 SetDCamZoomValueCmd( const u16& wZoom );
	virtual	u16 SetDCCamFocus( EmFocus emFocusMode ,EmCnAction emAction ) const;
	virtual	u16 SetDCCamExposure( EmExpMode emExpMode ) const;
	virtual	u16 SetDCCamExpGainCmd( EmDCamGain emExpGain ) const;
	virtual	u16 SetDCCamAperture( EmDCamIris emAperture ) const;
	virtual	u16 SetDCCamShutCmd( EmDCamShutSpd emShutSpd ) const;
	virtual	u16 SetDcCamRGainCmd( const u16& wRGain ) const;
	virtual	u16 SetDcCamBGainCmd( const u16& wRGain ) const;
	virtual u16 SetCurtainNumberCmd( const u8& byCurNum ) const;
	virtual u16 SetCurtainName( const u8& byCurIndex, const TCentreCurName &tCurtainName) const;
	virtual	u16 SetCurtainOpen( const BOOL& bOpen ) const;
	virtual	u16 SetDuoVideoCmd( const BOOL& bOpen ) const;
	virtual u16 SetDCCamOpenCmd( const BOOL& bOpen ) const;
	virtual	u16 SetDCCamPreset( const BOOL& bPreset ) const;
	virtual u16 SetAirConditionCmd( const u8& byAcNum ) const;
	virtual u16 SetDcCamModel( EmDCamProType emDcCamType ) const;
	virtual u16 SetPaCamModel( EmQCamProType emPaCamType ) const;

	//�������
	virtual const TTPMatrixConfig& GetMatrixConfig() const;//��ȡ����������Ϣ
	virtual u16 SetMatrixConfig( TTPMatrixConfig tTPMatrixConfig ) const;
protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	//������Ϣ����
	void OnLinkBreak(const CMessage& cMsg);


    //�������
    void OnSchStateNty(const CMessage& cMsg);
    void OnSchTempNty(const CMessage& cMsg);
    void OnSchPowerInd(const CMessage& cMsg);
    void OnSchPowerNty(const CMessage& cMsg);
    void OnSchLightInd(const CMessage& cMsg);
    void OnSchMainLightInd(const CMessage& cMsg);
    void OnSchAuxiLightInd(const CMessage& cMsg);
    void OnSchLightNty(const CMessage& cMsg);
    //��ʾ��
    void OnTvStateNty(const CMessage& cMsg);
    void OnSeleteTvInd(const CMessage& cMsg);
    void OnTvPowerModeInd(const CMessage& cMsg);
    void OnTvAudVisModeInd(const CMessage& cMsg);
    void OnTvDisModeInd(const CMessage& cMsg);
    void OnTvAudInpSelectInd(const CMessage& cMsg);
	void OnCentreTVModleInd(const CMessage& cMsg);
    //�ĵ������
	void SetDCamSelectIndexNty(const CMessage& cMsg);
    void SetDCamSelectIndexInd(const CMessage& cMsg);
    void OnDCamPowerInd(const CMessage& cMsg);
    void OnDCamAFModeInd(const CMessage& cMsg);
    void OnDCamWBModeInd(const CMessage& cMsg);
    void OnDCamZoomInd(const CMessage& cMsg);
    void OnDCamPresetInd(const CMessage& cMsg);
    void OnDCamRecallInd(const CMessage& cMsg);
    void OnDCamStateNty(const CMessage& cMsg);
    //�յ�
    void OnACTempInd(const CMessage& cMsg);
    void OnACModeInd(const CMessage& cMsg);
    void OnACAirVolInd(const CMessage& cMsg);
    void OnACStateNty(const CMessage& cMsg);
	void OnAirPowerInd(const CMessage& cMsg);
	void OnSeleteAirInd(const CMessage& cMsg);
	void OnApplyToAllInd(const CMessage& cMsg);
	//����
	void OnCurtainStateNty(const CMessage& cMsg);
	void OnCurtainActInd(const CMessage& cMsg);
	//�����
	void OnCamStateNty(const CMessage& cMsg);
    //�пش���
    void OnCentreSleepNty(const CMessage& cMsg);
	//�пص���ǽ
	void OnDisplayInd(const CMessage& cMsg);
	void OnCfgDisplayShowNty(const CMessage& cMsg);
	void OnCfgDisplayShowInd(const CMessage& cMsg);
	//ȫ�������
	void OnPanCamNty(const CMessage& cMsg);


	void OnDCamExpModeInd( const CMessage& cMsg );
	void OnDCamExpGainNty( const CMessage& cMsg );

	void OnDCamShutSpdNty( const CMessage& cMsg );
	void OnDCamApertureNty( const CMessage& cMsg );
	void OnDCamRGainInd( const CMessage& cMsg );
	void OnDCamBGainInd( const CMessage& cMsg );
	void OnPanCamNumberInd(const CMessage& cMsg);
	void OnDCamZoomValueInd(const CMessage& cMsg);
	void OnCurtainNumberInd( const CMessage& cMsg );
	void OnCurtainNameInd( const CMessage& cMsg );
	void OnCurtainInd( const CMessage& cMsg );
	void OnDualScreenInd( const CMessage& cMsg );
	void OnDualScreenNty( const CMessage& cMsg );
	void OnDCCamCfgInd( const CMessage& cMsg );
	void OnDCCamPresetInd( const CMessage& cMsg );
	void OnAirConditionInd( const CMessage& cMsg );
	void OnDcCamModelInd( const CMessage& cMsg );
	void OnPaCamModelInd( const CMessage& cMsg );

	//����
	void OnMatrixConfigNty( const CMessage& cMsg );
	void OnSetMatrixConfigInd( const CMessage& cMsg );
private:
	CCnsSession				*m_pSession;
    TCentreTVCfg            m_atTVCfg[MAX_CENTRETV_NUM];   //��ʾ����Ϣ 
	#define MAX_AC_NUM      3                         //����
	vector<TCentreACCfg>	m_vecTCentreACCfg;		//�յ���ʾ����Ϣ
	vector<TCentreCurName>  m_vecTCentreCurName;    //������������
	map<u8, TCentreDCamCfg> m_mapDCamCfg;//ylp 2019-3-21 �ĵ������

	TCentreCurInfo			m_tCentreCurtain;
	BOOL m_atbIsCtrl[3];
	BOOL m_bIsCtrl[3];
	BOOL m_bDisplay;
	BOOL m_bDisplayShow;
	TTPDisplayType m_tDisplayType1;
	TTPDisplayType m_tDisplayType3;

	//����
	TTPMatrixConfig m_tTPMatrixConfig;//����������Ϣ
};