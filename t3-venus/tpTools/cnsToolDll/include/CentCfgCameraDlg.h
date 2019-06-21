// CentCfgCameraDlg.h: interface for the CCentCfgCameraDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCFGCAMERADLG_H__4EF58907_60FB_4087_A492_755896396F1A__INCLUDED_)
#define AFX_CENTCFGCAMERADLG_H__4EF58907_60FB_4087_A492_755896396F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmDocCamCom
{
	emDOCCAM = 0,//�ĵ�
	emCom2,//����2
	emCom3,//����3
};

class CCentCfgCameraDlg  : public CLogicBase, public ISingleTon<CCentCfgCameraDlg> 
{
public:
	CCentCfgCameraDlg();
	virtual ~CCentCfgCameraDlg();
public:	 
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
	 /** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	 void RegMsg();
	 /** ����:  ����ȫ�����������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
//	 LRESULT OnPanCamNty( WPARAM wParam, LPARAM lParam );
	/** ����:  �����ĵ����������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �����ĵ������ѡ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDCamSelectedInd( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ�������۽�֪ͨ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamAutoFocusNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ������ZOOM����֪ͨ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamZoomNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ��������ƽ�����֪ͨ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamWBNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ�������ع�ģʽ�Ƿ����óɹ����ɹ����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDcCamExpMode( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ�������ع��������÷�����ʧ�ܷ����ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDcCamExpGain( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ�������ع�������÷�����ʧ�ܷ����ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDCCamShutNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ�������ع��Ȧ���÷�����ʧ�ܷ����ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDCCamApertureNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ��������ƽ��R�������÷�����ʧ�ܷ����ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamRGainNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ��������ƽ��B�����������÷�����ʧ�ܷ����ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamBGainNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  ȫ��������������÷�����ʧ�ܷ����ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnPanCamNumNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ����������Ԥ��λ������ʧ�ܽ�����ʾ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamSavePreSetNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  �ĵ����������Ԥ��λ������ʧ�ܽ�����ʾ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamCallPreSetNty( WPARAM wParam, LPARAM lParam );

	 LRESULT OnDocCamCfg( WPARAM wParam, LPARAM lParam );

	 LRESULT OnDocCamBootCall( WPARAM wParam, LPARAM lParam );

	 LRESULT OnDocCamModelNty( WPARAM wParam, LPARAM lParam );

	 LRESULT OnPanCamModelNty( WPARAM wParam, LPARAM lParam );

	 //���ڲ���
	 LRESULT OnSelectComInd( WPARAM wparam, LPARAM lparam );
private:
	/** ����:  Ԥ��λ1
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelPreset( const IArgs& args );
	/** ����:  ѡ���ϴ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelLastPreset( const IArgs& args );
	/** ����:  �������ر�ȫ�������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnPanCamBtnChange( const IArgs& args );
	 /** ����:  �������ر��ĵ������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnDocCameraBtnChange( const IArgs& args );
	 /** ����:  �޸�ȫ�����������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnPanCamNumChange( const IArgs& args );
	  /** ����:  �޸��ĵ����������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnDocCamIndexChange( const IArgs& args );
	 /** ����:  ����ZOOM+����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnLBtnDownZoonPlus( const IArgs& args );
	 /** ����:  �ɿ�ZOOM+����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnLBtnUpZoonPlus( const IArgs& args );
	 /** ����:  ����ZOOM-����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnLBtnDownZoonSub( const IArgs& args );
	 /** ����:  �ɿ�ZOOM-����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnLBtnUpZoonSub( const IArgs& args );
	 /** ����:  �л����Զ�ģʽ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnBtnAutoFocusClick( const IArgs& args );
	 /** ����:  ���½�������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnLBtnDownFocusNear( const IArgs& args );
	 /** ����:  �ɿ���������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnLBtnUpFocusNear( const IArgs& args );

	 bool OnLBtnDownFocusFar( const IArgs& args );

	 bool OnLBtnUpFocusFar( const IArgs& args );

	 bool OnBtnManualFocusClick( const IArgs& args );
	 /** ����:  �Զ�/�ֶ��ع�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnBtnSwitchAutoExposure( const IArgs& args );
	 /** ����:  ��������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnBtnSwitchAutoWB( const IArgs& args );
	 /** ����:  ����R���滬��λ�ñ仯�����±༭�����ݣ������͸�������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnSliderRGainChanged( const IArgs& args );
	 /** ����:  ����B���滬��λ�ñ仯�����±༭�����ݣ������͸�������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnSliderBGainChanged( const IArgs& args );
	 /** ����:  R����༭��ʧȥ���㣬��������������R��������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditRGainKillFocus( const IArgs& args );
	 /** ����:  �༭�����ݱ仯���ı������λ��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditRGainChange( const IArgs& args );
	 /** ����:  �༭�����ݱ仯���ı������λ��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditBGainChange( const IArgs& args );
	 /** ����:  B����༭��ʧȥ���㣬��������������B��������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditBGainKillFocus( const IArgs& args );

	 /** ����:  �����Ȧ�����ù�Ȧ��ֵ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnComboboxApertureClick( const IArgs& args );
	 /** ����:  �������COMBOLIST�����ÿ���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnComboboxShutClick( const IArgs& args );
	 /** ����:  �������COMBOLIST�����ÿ���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnComboboxExpGainClick( const IArgs& args );
	 /** ����:  �������Ԥ��λ����������Ԥ��λ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnBtnSavePreSet( const IArgs& args );
	 /** ����:  �������Ԥ��λ����������Ԥ��λ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnBtnCallPreSet( const IArgs& args );
	 /** ����:  Zoom�༭��ֵ�仯
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEdtZoomChange( const IArgs& args );
	 /** ����:  Zoom�༭��ֵʧȥ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEdtZoomKillFocus( const IArgs& args );

	 bool OnSelIPC822( const IArgs& args );

	 bool OnSelPRS200( const IArgs& args );

	 bool OnSel120E( const IArgs& args );
	 
	 bool OnSelMOON50( const IArgs& args );
private:
	/** ����:  ����Editֵ�����»���λ��
	*  @param[in]	strEditName �༭������   strSliderName ��Ӧ�Ľ�������
	*  @return 
	*  @remarks   
	*/
	 void GainEditChange( const IArgs& args ,string strEditName, string strSliderName );
	 /** ����:  ���ݻ���λ�ã����±༭��
	*  @param[in]	strSliderName ��Ӧ�Ľ�������  strEditName �༭������
	*  @return 
	*  @remarks   
	*/
	 void SetGainValue( u16 wRGain ,string strStrliderName, string strEditName );

	 void SetZoomValue( float fZoom );

	 string TransApertureTypeToString( EmDCamIris emAperture );

	 EmDCamIris TransApertureTextToType( string strAperture );
	 
	 string TransGainTypeToString( EmDCamGain emDCGain );

	 EmDCamGain TransGainTextToType( string strGainText );

	 string TransShutterTypeToString( EmDCamShutSpd emDCShut );

	 EmDCamShutSpd TransShutterTextToType( string strShutterText );

	 CString OnlyFloat( CString str );

	 float StringToFloatTwo( CString str );

	 void SetZoomCmd( CString str );

	 void TranDoccamCom(String& strComName, EmDocCamCom& emDocCamCom);

	 void UpDateDocComConfig();
private:
	 const string m_strPanSwitchBtn;						//ȫ�����������
	 const string m_strPancombobox;							//ȫ�����������
	 const string m_strDCamIndexBox;						//�ĵ����������
	 const string m_strDocSwitch;							//�ĵ����������
	 const string m_strDocZoonPlusBtn;						//�ĵ��������������
	 const string m_strDocZoonSubBtn;						//�ĵ��������������
	 const string m_strDocZoonEdit;							//�ĵ���������۱༭��
	 const string m_strDocAperture;							//�ĵ��������Ȧ
	 const string m_strDocExposureGain;						//�ĵ����������
	 const string m_strDocShutter;							//�ĵ����������
	 const string m_strDocPreset;							//�ĵ��������������Ԥ��λ1
	 const string m_strDocLastState;						//�ĵ��������һ��״̬
	 const string m_strDocAutoFocus;						//�ĵ�������Զ�����
	 const string m_strDocManualFocus;						//�ĵ�������ֶ�����
	 const string m_strDocFocusNear;						//�ĵ��������������
	 const string m_strDocFocusAway;						//�ĵ������������Զ	
	 const string m_strDocAutoExposure;						//�ĵ�������Զ��ع⿪��
	 const string m_strDocAutoWB;							//�ĵ�������Զ���ƽ�⿪��
	 const string m_strDocRGainSlider;						//�ĵ��������ƽ��R����
	 const string m_strDocRGainEdit;						//�ĵ��������ƽ��R����༭��
	 const string m_strDocBGainSlider;						//�ĵ��������ƽ��B����
	 const string m_strDocBGainEdit;						//�ĵ��������ƽ��B����༭��

	 u8				 m_byPanCamNum;							//ȫ�����������
	 TPanCamInfo     m_tQCamInfo;
	 TCentreDCamCfg  m_tDCamInfo;
	 const string StrDocCamExistSch;
	 const string StrDocCamNonExistSch;

	  u8          m_byDCamSelIndex;							//�ĵ������ѡ����
};

#endif // !defined(AFX_CENTCFGCAMERADLG_H__4EF58907_60FB_4087_A492_755896396F1A__INCLUDED_)
