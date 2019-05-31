// RenameOptDlg.h: interface for the CCRenameOptDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RENAMEOPTDLG_H__50CA3A04_095D_42B6_B075_F568638BA64E__INCLUDED_)
#define AFX_RENAMEOPTDLG_H__50CA3A04_095D_42B6_B075_F568638BA64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EM_RENAME_TYPE      //��������
{
	em_RENAME_VIDEOSOURCE,			//��ƵԴ������   
	em_RENAME_DISPLAYDOURCE,		//��ʾԴ������
	em_SAVE_PRESET,					//����Ԥ��λ
	em_CALL_PRESET,					//����Ԥ��λ
	em_RNAME_CURTAIN				//����������
};

class CCRenameOptDlg  :public CLogicBase, public ISingleTon<CCRenameOptDlg>
{
public:
	CCRenameOptDlg();
	virtual ~CCRenameOptDlg();
public:  
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual void RegCBFun();

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
	virtual void RegMsg(); 

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegFunc( );

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  ����ʱ�������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
private:
	/** ����:  �յ���������ƵԴ������Ϣ�����½���
	*  @param[in] wparam �洢��ƵԴ���ƽṹ��
	*  @return 
	*  @remarks   
	*/
	HRESULT OnRenameVideoSource( WPARAM wparam, LPARAM lparam );
	/** ����:  �յ����á�����Ԥ��λ��Ϣ
	*  @param[in] wparam �Ƿ�Ϊ����Ԥ��λ
	*  @return 
	*  @remarks   
	*/
	HRESULT OnPreSet( WPARAM wparam, LPARAM lparam );
	/** ����:  ��������ʾԴ��Ϣ
	*  @param[in] wparam ������ʾԴ���ƻ�ȫ����ʾԴ����  lparam �Ƿ�������������ʾԴ
	*  @return 
	*  @remarks   
	*/
	HRESULT OnRenameDisplaySource( WPARAM wparam, LPARAM lparam );
	/** ����:  ����������
	*  @param[in] wparam �����������ƻ�������  lparam �Ƿ���������������
	*  @return 
	*  @remarks   
	*/
	HRESULT OnCurtainRename( WPARAM wparam, LPARAM lparam );
	/**	 
	* ����:  ��ű䶯
	* @return   
	* @remarks	 
	*/
	bool OnRenameIDChange( const IArgs & arg );

	bool OnBtnOptMsgCancel( const IArgs & arg );
	/** ����:  �����޸�
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	bool OnBtnOptMngOk( const IArgs & arg );

private:
	/** ����:  ���ַ�����Ӧ����ƵԴö��
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	EmTPMtVideoPort GetVideoSourceType( String strCtrl );
	/** ����:  ��Ĭ���ַ�����Ӧ����ƵԴö��
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	EmTPMtVideoPort GetDefaultVideoSource( string strVideoSource );
	/** ����:  ��ö�ٶ�Ӧ�ɵ�ǰ�޸������ַ���
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransVideoSourceType( EmTPMtVideoPort emType );
	/** ����:  ��ö�ٶ�Ӧ��Ĭ�������ַ���
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransDefaultVideoSource( EmTPMtVideoPort emType );
	/** ����:  �������Ƿ��Ѿ�����
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	bool IsExist( String strOldRenameInfo );

	bool IsVisible( String strOldRenameInfo );

	bool CheckInfo( String strOldRenameInfo );

	void SetVideoSourceData();

	void SetDisplaySourceData();
	/** ����:  ����ʾԴö�ٶ�Ӧ���޸ĵ��ַ���
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransDisplaySourceType( EmVgaType emType );
	/** ����:  ����ʾԴö�ٶ�Ӧ��Ĭ�ϵ��ַ���
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransDefaultDisplaySource( EmVgaType emType );

	EmVgaType GetDisplaySourceType( String strCtrl );

	EmVgaType GetDefaultDisplaySource( string strDisplaySource );
	/** ����:  ���޸ĵ����ݱ��浽�ṹ����
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	void SaveContext( String strLastRenameInfo );

	void UpdateState();

//	bool IsChange( );

	bool GetType( String strContext );
	/** ����:  ��Ͽ�ѡ������Ŀʱ������һ�����Ƽ��δͨ�������ڻ�ȡ��һ����Ͽ��ֵ
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	String GetLastDefaultContext( );

	void SetPreSetData();

	bool onRenameOptDlg();
	/** ����:  ���ַ�����Ӧ�ɵ���Ԥ��λö��ֵ
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	EmDCamRecallNum GetCallPreSetType( string strDCamCallPreSet );

	EmDCamPresetNum GetSavePreSetType( string strDCamCallPreSet );
	/** ����:  ��ȡCombobox��Text,��Ӧ��Ĭ��ö�٣�ͨ��ö�٣���Ӧ�ɵ�ǰ��ʱ������ַ���
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	String GetCurrentText( );
private:
	TTPVideoSourceName     m_atVideoSourceName[emTPC7Vid+1];					//��ƵԴ����
	const String           m_strRenameCombox;									//XML�е�Combobox ��Ӧ���ַ���
	const String           m_strRenameInfo;										//�洢XML��Ӧ���������༭��

	EmTPMtVideoPort		   m_emOldVideoSourceType;								//��һ����ʾԴ��Ӧ��ö��ֵ
	EmTPMtVideoPort		   m_emCurrentVideoSourceType;							//��ǰ��Ӧ��ö��ֵ

	TVgaInfo			   m_atDisplaySourceInfo[5];							//��ƵԴ����
	EM_RENAME_TYPE         m_emRenameType;										//��������

	EmVgaType			   m_emOldDisplaySourceType;							//��һ��״̬
	EmVgaType			   m_emCurrentDisplaySourceType;						//��ǰ��ʾԴ��Ӧ��ö��ֵ
	TCentreCurInfo		   m_tCurtainInfo;										//��ʱ��������
	TCentreCurInfo		   m_tOldCurtainInfo;									//δ�޸�֮ǰ������
	s32					   m_nLastIndex;										//���һ���޸ĵĴ�������
};

#endif // !defined(AFX_RENAMEOPTDLG_H__50CA3A04_095D_42B6_B075_F568638BA64E__INCLUDED_)
