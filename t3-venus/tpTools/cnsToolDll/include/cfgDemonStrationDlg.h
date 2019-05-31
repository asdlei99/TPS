// cfgDemonStrationDlg.h: interface for the CCfgDemonStrationDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGDEMONSTRATIONDLG_H__2C5DCC8D_7069_4EC1_AD0F_50C94CB2E640__INCLUDED_)
#define AFX_CFGDEMONSTRATIONDLG_H__2C5DCC8D_7069_4EC1_AD0F_50C94CB2E640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgDemonStrationDlg  : public CLogicBase, public ISingleTon<CCfgDemonStrationDlg>
{
public:
	CCfgDemonStrationDlg();
	virtual ~CCfgDemonStrationDlg();

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
	/** ����:  ���շ�������Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDisplaySourceNty( WPARAM wparam, LPARAM lparam );
	/** ����:  ���շ�������Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDefDisplaySourceNty( WPARAM wparam, LPARAM lparam );
	/** ����:  ������������������Ϣ�����͸�������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDisplaySource( WPARAM wparam, LPARAM lparam );

	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );

	/** ����:  ���ؼ�����Ϊ������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void InitCtrlEnable();					
	/** ����:  ������ʾ��ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnIdleSwitch( const IArgs & arg );
	/** ����:  ������ʾ��ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnConfSwitch( const IArgs & arg );
	/** ����:  ������ʾ ѡ������Ļ�������������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelLeft1( const IArgs & arg );
	/** ����:  ������ʾ ѡ���м���Ļ�������������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelMid1( const IArgs & arg );
	/** ����:  ������ʾ ѡ������Ļ�������������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelRight1( const IArgs & arg );
	
	bool OnSelLeft2( const IArgs & arg );
	
	bool OnSelMid2( const IArgs & arg );
	
	bool OnSelRight2( const IArgs & arg );
	/** ����:  ���������ܣ���������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnOptRenameDlg( const IArgs& args );
	/** ����:  ����ǰѡ����ʾԴ��ΪĬ����ʾԴ�������������������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSetDefault( const IArgs & arg );
	
	bool OnClickDisplayLstBlack( const IArgs& args );

	bool OnClickVideoSourceList( const IArgs & arg );

	void SetDemonStrationDate( );
	/** ����:  �ָ�Ĭ����ʾԴ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnDefault( const IArgs & arg );

	void SetDefaultDemonStration( TTPDualDisplayStrategy & tDualDisplayStrategy, EmVgaType &emDefaultDisplay );

	void SendCommand();
	/** ����:  �����б�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetListDate( );
	/** ����:  �б���������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SoftDemoStrationData( vector<Value_DisplaySrc::TDisplaySrcData> &vecTDisplaySource );
	/** ����:  �б����ݽ���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwapDemoSourceData( s32 nNum ,EmVgaType emType , vector<Value_DisplaySrc::TDisplaySrcData> &vecTDisplaySource );
	/** ����:  ��ȡ��ʾԴ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void GetDemoStrationData();
	/** ����:  ������ʾԴ����ʾ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SaveDemoStrationData( TTPDualDisplayStrategy &tDualDisplayStrategy );
	
	BOOL CheckIdleStrategy( );
	BOOL CheckConfStrategy( );
private:
	String							    m_strIdleStrategy[emEndMPCodec-1];					//�������ʱ��ʾ3��CheckBox�ַ���
	String								m_strConfStrategy[emEndMPCodec-1];					//����ʱ��ʾ3��CheckBox�ַ���

	const String						m_strIdleSwitch;
	const String						m_strConfSwitch;
	const String						m_strList;	
	TVgaInfo							m_atDemoSourceName[5];							   //��ƵԴ����
	EmVgaType							m_emDefault;
	TTPDualDisplayStrategy				m_tDualDisplayStrategy;
	vector<Value_DisplaySrc::TDisplaySrcData>   m_vecDisplaySource;
	Value_DisplaySrc::TDisplaySrcData	m_tCurSelEntry;
};

#endif // !defined(AFX_CFGDEMONSTRATIONDLG_H__2C5DCC8D_7069_4EC1_AD0F_50C94CB2E640__INCLUDED_)
