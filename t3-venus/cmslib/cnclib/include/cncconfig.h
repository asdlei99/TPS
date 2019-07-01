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

	//����IPV6����
	virtual u16 SetIpv6Cfg( TTPEthnetIPV6Info tTPEthnetIPV6Info, EmTpIpNameNatSyn emTpIpNameNatSyn);
	//��ȥIPV6����
	virtual const TTPEthnetIPV6Info GetIpv6Cfg();
	//������������
	virtual u16 SetIpvType( EmProtocolVersion emProtocolVer );
	//��ȡ��������
	virtual const EmProtocolVersion GetIpvType();


	/** ����   ����CNS��Ϣ
	 *  @param[in] tInfo CNS��Ϣ  byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex ,EmTpIpNameNatSyn emTpIpType);

	virtual u16 SetMainCns( s8* pbyRoomName );

	virtual const s8* GetMainCnsName() const;

	//������������
	virtual const TTPEthnetInfo& GetEthnetCfg() const;
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg ,EmTpIpNameNatSyn emTpIpType);
	virtual u16 SaveWEthnetCfgCmd( const TTPWEthnetInfo& tTPWEthnetInfo, EmTpIpNameNatSyn emTpIpType );
	virtual const TTPCnsInfo& GetLocalCnsInfo() const;
	virtual const vector<TTPCnsInfo>& GetLocalCnsList() const;
    
	//����NAT����*******2012.11.1 JYY���
	virtual u16 UpdateNATCfg( const TTPNatCfg& cfg,EmTpIpNameNatSyn emTpIpType);
	virtual const TTPNatCfg& GetNATCfg() const;

	virtual u16 SetAesEncrypCmd( const TTpEncryptKey& tEncryptKey );
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

    virtual u16 SetDataServerInfoCmd( u32 dwIp );

	virtual u16 SetLostPacketCmd( EmTpLostPackageRestore emLostPackage );

	virtual u16 SetFtpInfoRsq( const TTPFtpInfo &tTPFtpInfo );

	virtual u16 SetTelInfoRsp( const TTPTelnetInfo &tTPTelnetInfo);
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
	//Ipv6 ����
	void OnCfgEthnetIPV6Ind(const CMessage& cMsg);
	void OnIPVtpyeInd(const CMessage& cMsg);
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
	void OnEncryptionInd( const CMessage &cMsg );
	void OnLostPackageInd( const CMessage &cMsg );

	//˫���ں����ڱ���
	void OnSetCfgWEthnetNty( const CMessage &cMsg );
	void OnSetCfgWEthnetRsp( const CMessage &cMsg );
	void OnSetCfgEthnetStateNty( const CMessage &cMsg );
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

	EmProtocolVersion   m_emProtocolVersion; //IPV����
	TTPEthnetIPV6Info	m_tTPEthnetIPV6Info; //IPV6����
};

#endif // !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
