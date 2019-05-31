// CfgMainAudioDlg.h: interface for the CCfgMainAudioDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGMAINAUDIODLG_H__BA02C747_CF77_4F21_8478_6B2B758621E6__INCLUDED_)
#define AFX_CFGMAINAUDIODLG_H__BA02C747_CF77_4F21_8478_6B2B758621E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgMainAudioDlg  : public CLogicBase, public ISingleTon<CCfgMainAudioDlg>
{
public:
	CCfgMainAudioDlg();
	virtual ~CCfgMainAudioDlg();

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
	/* ����: ��ȡ���������ݱ仯�ؼ�����Ŀ
	* @return   s32
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
	/* ����: �����иĶ�����ʾ����
	* @return   bool
	* @remarks  
	*/
	bool IsCfgMainAudioChange();
	//���س�ʱ
	void DownloadOvertime();
private:
	/* ����: ��������Ƶ����
	* @return   HRESULT
	* @remarks  
	*/
	HRESULT OnUpdateMainAudioNty( WPARAM wparam, LPARAM lparam );
	/* ����: ����ָ�Ĭ����Ϣ����
	* @return   HRESULT
	* @remarks  
	*/
	HRESULT OnDefMainAudioNty( WPARAM wparam, LPARAM lparam );
	/* ����: ��������ˢ������Ƶ��ͼ��Сͼ������
	* @param[in] wparam ������ʾԴ����
	* @return   HRESULT
	* @remarks  
	*/
	HRESULT OnRefreshVideoInfoNty( WPARAM wparam, LPARAM lparam );

//	HRESULT OnUpdatePanCamNty( WPARAM wparam, LPARAM lparam );
	/* ����: ����״̬֪ͨ
	* @return   LRESULT
	* @remarks  
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );
	/* ����: ����֪ͨ
	* @return   LRESULT
	* @remarks  
	*/
	LRESULT OnSnapShotNty( WPARAM wparam, LPARAM lparam );
private:
	/* ����: ��ͼ��1Combobox�����޸�
	* @return   bool
	* @remarks  
	*/
	bool OnLargeImage1Change( const IArgs& args );

	bool OnLargeImage2Change( const IArgs& args );

	bool OnLargeImage3Change( const IArgs& args );
	/* ����: Сͼ��1Combobox�����޸�
	* @return   bool
	* @remarks  
	*/
	bool OnSmallImage1Change( const IArgs& args );

	bool OnSmallImage2Change( const IArgs& args );

	bool OnSmallImage3Change( const IArgs& args );
	/* ����: ��������������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnOptRenameDlg( const IArgs& args );

	bool OnSwitchSynthesis(const IArgs & arg );
	/* ����: ȡ�������޸�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnCancel( const IArgs& args );
	/* ����: ��������ָ���Ĭ��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDefault( const IArgs& args );
	/* ����: ��������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnSave( const IArgs& args );

	bool OnLayoutChange( const IArgs& args );

	bool OnBtnPreview( const IArgs& args );
	/* ����: ѡ������
	* @return   bool
	* @remarks  
	*/
	bool OnSelSynthesisStyle( const IArgs& args );

private:
	/**����:  �ж���·��ͼ���Ƿ��б䶯�����°���״̬
	*  @param[in] nIndex �ڼ�·��ͼ��  emVideoSourceType �����ͼ���Ӧ��ö��ֵ
	*  @return  bool
	*  @remarks  
	*/
	bool UpdateLargeImage( s32 nIndex , EmTPMtVideoPort emVideoSourceType );
	/**����:  �ж���·Сͼ���Ƿ��б䶯�����°���״̬
	*  @param[in] nIndex �ڼ�·Сͼ��  emVideoSourceType ��·Сͼ���Ӧ��ö��ֵ
	*  @return  bool
	*  @remarks  
	*/
	bool UpdateSmallImage( s32 nIndex ,EmTPMtVideoPort emVideoSourceType );
	/**����:  ͨ���ַ���ת��Ϊ��Ӧ��ö��ֵ
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	EmTPMtVideoPort GetVideoSourceType( String strCtrl );
	/**����:  ��ͼ����������ַ���תΪ��Ӧö��
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	EmVidEncResizeMode GetResizeModeType( String strCtrl );
	/**����:  ��������Ƶ������ʾ
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void SetMainAudioDate();
	/**����:  ��Сͼ���Ӧ��ö��ת��Ϊ�ַ���
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	string TransVideoSourceType( EmTPMtVideoPort emType );
	/**����:  ��ͼ���������ö��ת��Ϊ�ַ���
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	string TransResizeModType( EmVidEncResizeMode emType );
	/**����:  ����Ĭ������
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void SetDefVideoSrcInfo();

	void SaveMainAudioInfo( );
	/* ����: ���õ�һ·COMBOLIST����
	* @return  
	* @remarks  
	*/
	void SetVideoSrc1Data( );
	/* ����: ���õڶ�·COMBOLIST����
	* @return  
	* @remarks  
	*/
	void SetVideoSrc2Data( );
	/* ����: ���õ���·COMBOLIST����
	* @return  
	* @remarks  
	*/
	void SetVideoSrc3Data( );
	/* ����: �ͷſ���ͼƬ
	* @return  
	* @remarks  
	*/
	void ReleaseSnapImage();
	/* ����: ����ͼƬ����
	* @return  
	* @remarks  
	*/
	string GetSnapShotFileName( const string strFileName );

	BOOL DownloadCore(const String& strFilePath,const String & strFileName );

	bool OnDownloadProgress( const IArgs & arg );
private:
	vector<CString> m_vecLayout;                    //��������

	TTPVideoInfoTool m_tMainAudioInfo;              //��������ϵ���ʱ����
	TTPVideoInfoTool m_tOldMainAudioInfo;
	String m_strLargeImage[emEndMPCodec-1];		    //�洢XML�ж�Ӧ�Ĵ�ͼ��ؼ�����	
	String m_strSmallImage[emEndMPCodec-1];			//�洢XML�ж�Ӧ��Сͼ��ؼ�����	
	const String m_strLayout;						//�洢XML�еĲ�������
	const String m_strImageSynthesis;				//�洢XML�е�ͼ���ںϲ��Կ���
	const String m_strDefault;						//�洢XML�лָ�Ĭ�ϰ�ť
	const String m_strSave;							//�洢XML�б��水ť
	const String m_strCancel;						//�洢XML��ȡ����ť
	const String m_strStatus;						//�洢XML�����ؿؼ��������������޸�ʱ�����±��水����״̬
	const String m_strThreeImage;					//������
	const String m_strFourImage;                    //�Ļ���
	vector<string> m_vecShatShot;					//�洢XML�ж�Ӧ3�ſ��տؼ�����
	CFtpCtrl m_cFtp;
	vector<String> m_vctDownFile;                   //��������ؿ����ļ�
	vector<String> m_vecFilePath;					//���ؿ��յ�·��
	Window* m_pWnd;
	bool		   m_bIsUsedGroup1;				   //δʹ��snapshot0.jpg snapshot1.jpg snapshot2.jpg��ͼƬ
};

#endif // !defined(AFX_CFGMAINAUDIODLG_H__BA02C747_CF77_4F21_8478_6B2B758621E6__INCLUDED_)
