// cfgAudioDlg.h: interface for the CCfgAudioDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGAUDIODLG_H__069DCC21_7725_4859_8C6B_572E35B5833A__INCLUDED_)
#define AFX_CFGAUDIODLG_H__069DCC21_7725_4859_8C6B_572E35B5833A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgAudioDlg : public CLogicBase, public ISingleTon<CCfgAudioDlg>
{
public:
	CCfgAudioDlg();
	virtual ~CCfgAudioDlg();

public:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void RegMsg();
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc( );
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
	virtual bool InitWnd( const IArgs & arg ); 
	/** ����:  ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڴ��ڹرյ�ʱ�����,��մ�������
	*/
	virtual void Clear() ;
	/** ����:  �������д���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	//	void HideAllWnd();
	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();
	/**	 
	* ����: ��ȡ���������ݱ仯�ؼ�����Ŀ
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }

	bool IsCfgAudioChange();

private:

	void SetAudioData();

	void SetMixType();

	void SetAux2Info();

	void InitCtrlEnable();

	bool UpdateGroup( TTPMPAudioInfo& tAudioInfo );
	/**����:  ��һ·�������������䶯�����±༭��
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnSliderGain1Changed(const IArgs & arg );

	bool OnSliderGain2Changed(const IArgs & arg );

	bool OnSliderGain3Changed(const IArgs & arg );

	bool OnSliderGain4Changed(const IArgs & arg );

	bool OnSliderGain5Changed(const IArgs & arg );
	/**����:  ��һ·�������༭��䶯���޸Ļ������
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnEditGain1Changed(const IArgs & arg );

	bool OnEditGain2Changed(const IArgs & arg );

	bool OnEditGain3Changed(const IArgs & arg );

	bool OnEditGain4Changed(const IArgs & arg );

	bool OnEditGain5Changed(const IArgs & arg );
	/**����:  �������رյ�һ·������
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnBtnSwitch1(const IArgs & arg );

	bool OnBtnSwitch2(const IArgs & arg );

	bool OnBtnSwitch3(const IArgs & arg );
	/**����:  �������ر�AGC
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnBtnAGC(const IArgs & arg );
	
	bool OnBtnMAEC(const IArgs & arg );

	bool OnBtnMANS(const IArgs & arg );

    bool OnBtnAE(const IArgs & arg );

	/**����:  ������������ء�Զ�˻��������غ�Զ�˻������
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnSelMixSound( const IArgs& args );

	bool OnBtnAUX2(  const IArgs& args );

	bool OnBtnCancel( const IArgs& args );
	
	bool OnBtnDefault( const IArgs& args );
	
	bool OnBtnSave( const IArgs& args );
private:
	HRESULT OnDefaultAudioNty( WPARAM wparam, LPARAM lparam );
	/**����:  �������رհ������ظ�
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	HRESULT OnWhiteNoiseNty( WPARAM wparam, LPARAM lparam );
	/**����:  ������Ϣ�����°���������ʱ���Լ������λ��
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	HRESULT OnUpdateWhiteNoiseNty( WPARAM wparam, LPARAM lparam );
	/**����:  ����״̬֪ͨ�������н��ð��������ſ���
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );

	/**����:  ������Ƶ����
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	HRESULT OnUpdateAudioNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetMixType( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetAux2Info( WPARAM wparam, LPARAM lparam );
	

//	bool OnSliderNoise1Changed(const IArgs & arg );

//	bool OnSliderNoise2Changed(const IArgs & arg );

//	bool OnSliderNoise3Changed(const IArgs & arg );

	/**����:  �������رհ���������
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool SendWhiteNoiseReq( String strWndName, s32 nNum );
	/**����:  �������رհ���������
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void UpdateGainNum( String strGainName, String strEditName, s32 nNum );

	void UpdateGainEdit( String strEditName, String strSliderName, s32 nNum );
	/**����:  ���ð�����ʱ��ͻ���λ��
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void UpdatePlayTimer( String strGainName, String strPlayTimeName,s32 nNum ,u8 byWhiteNoiseTime );

	void SetDefaultAudioInfo();
	
	void SetDefaultMixType();

	void SetDefaultAux2Info();

	void SaveGroup( );

	void initWhiteNoise( );

	void UpdateWhiteNoiseState( String strWndName ,BOOL bIsOpen );

private:
	TTPMPAudioInfo m_tOldAudioSetInfo;                //��ʱ����Ľ�������
	TTPMPAudioInfo m_atAudioSetInfo;				  
	const String   m_strMaxPlayTime;				  //���ʱ��
	BOOL           m_bOldWhiteNoise[3];				  //
	u8             m_byLastWhiteNoiseTime[3];		  //��һ��ʱ��

private:
	const String m_strMixPort1;	
	const String m_strMixPort2;
	const String m_strMixPort3;

	EmAudMixType  m_emCheckState;
	u8            m_byAudMixVolume;
	EmAudExtend   m_emAux2State;
	u8            m_byAudExtendVolume;

};

#endif // !defined(AFX_CFGAUDIODLG_H__069DCC21_7725_4859_8C6B_572E35B5833A__INCLUDED_)
