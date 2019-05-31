// cfgNetSecurityLogic.h: interface for the cfgNetSecurityLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGNETSECURITYLOGIC_H__21896890_9A54_4DE8_96AE_063C6281D3FA__INCLUDED_)
#define AFX_CFGNETSECURITYLOGIC_H__21896890_9A54_4DE8_96AE_063C6281D3FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgNetSecurityLogic : public CLogicBase, public ISingleTon<CCfgNetSecurityLogic>  
{
public:
	CCfgNetSecurityLogic();
	virtual ~CCfgNetSecurityLogic();

	//CLogicBase
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

	/** ����:  �ж�cns����ҳ�����Ϣ�Ƿ�ı�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCfgNetChange();

	/**	 
	* ����: ��ȡ���������ݱ仯�ؼ�����Ŀ
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }

protected:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();

protected:

	/** ����:  �յ�����״̬����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	HRESULT OnSetFtpInfoNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetTelnetInfoNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetTelnetInfoRsp( WPARAM wparam, LPARAM lparam );


private:

	/** ����:  �������õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSave( const IArgs& args );

	/** ����:  ��ԭ���õİ�ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnCancel( const IArgs& args );

	/** ����:  ����/�ر�FTP����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchFtpServer( const IArgs& args );

	/** ����:  �༭FTP�û�������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnFtpUsernameChange( const IArgs& args );

	/** ����:  ��ñ༭FTP���뽹�����Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtFtpPasswdSetFocus( const IArgs& args );

	/** ����:  �༭FTP�������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnFtpPasswdChange( const IArgs& args );
	
	/** ����:  ʧȥ�༭FTP���뽹�����Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtFtpPasswdKillFocus(  const IArgs& args );

	/** ����:  ����/�ر�Telnet����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchTelnetServer( const IArgs& args );

	/** ����:  �༭Telnet�û�������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTelnetUsernameChange( const IArgs& args );

	/** ����:  �༭Telnet�������Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTelnetPasswdChange( const IArgs& args );

	/** ����:  ��ñ༭Telnet���뽹�����Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtTelnetPasswdSetFocus( const IArgs& args );

	/** ����:  ʧȥ�༭Telnet���뽹�����Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtTelnetPasswdKillFocus( const IArgs& args );

	/** ����:  �л�����������ʱ�����Ƿ񱣴�Ĵ���	
	*  @param[in] 
	*  @return 
	*  @remarks
	*/	
	bool SaveMsgBox();

private:
	void SetFtpInfo();

	void SetTelnetInfo();

	bool IsValidPWChar(CString szPWStr);

	bool IsValidPWCharStyle(CString szPWStr);

	void UpdateFtpPasswdTip( String strPasswd);

	void UpdateTelnetPasswdTip( String strPasswd);

private:

	const String    m_strBtnFtpServerSwitch;
	const String    m_strEdtFtpUsername;
	const String    m_strEdtFtpPasswd;
	const String    m_strBtnTelnetServerSwitch;
	const String    m_strEdtTelnetUsername;
	const String    m_strEdtTelnetPasswd;

	TTPFtpInfo  m_tTPFtpInfo;
	TTPTelnetInfo m_tTPTelnetInfo;

};

#endif // !defined(AFX_CFGNETSECURITYLOGIC_H__21896890_9A54_4DE8_96AE_063C6281D3FA__INCLUDED_)
