// recordOptDlg.h: interface for the RecordOptDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDOPTDLG_H__C7A5678B_ABAF_489F_B595_6E2744B6EA9E__INCLUDED_)
#define AFX_RECORDOPTDLG_H__C7A5678B_ABAF_489F_B595_6E2744B6EA9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  CNSSTATISTIC_FILE_NAME		"�������.ini"

class RecordOptDlg  :public CLogicBase, public ISingleTon<RecordOptDlg>
{
public:
	RecordOptDlg();
	virtual ~RecordOptDlg();
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

	bool OnBtnClose( const IArgs & arg );
	bool OnBtnScan( const IArgs & arg );
	bool OnOpenFolder( const IArgs & arg );

	bool OnBtnSave( const IArgs & arg );

	HRESULT OnInterfaceSelection( WPARAM wparam, LPARAM lparam );
	CString getNewFileName( string strFolder , string strFileName );
private:
	const string		m_StrStartingSch;
	const string		m_StrEndingSch;
	const string		m_StrCleanSch;

	const string		m_StrForder;
	const string		m_StrFileName;

//	string              m_strFullFilePath;
	CFile				m_cFile;
	bool				m_bIsRecording;
};

#endif // !defined(AFX_RECORDOPTDLG_H__C7A5678B_ABAF_489F_B595_6E2744B6EA9E__INCLUDED_)
