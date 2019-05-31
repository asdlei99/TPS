// routeCfgdlgLogic.h: interface for the routeCfgdlgLogic class.
//·��������ӶԻ���
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUTECFGDLGLOGIC_H__9353F1F3_BA28_482A_8E01_BFD93BB0A411__INCLUDED_)
#define AFX_ROUTECFGDLGLOGIC_H__9353F1F3_BA28_482A_8E01_BFD93BB0A411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogicBase.h"

class CRouteCfgdlgLogic: public CLogicBase, public ISingleTon<CRouteCfgdlgLogic> 
{
public:
	CRouteCfgdlgLogic();
	virtual ~CRouteCfgdlgLogic();

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

protected:
	/**	 
	* ����:  ����BtnOK�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRouteCfgOk( const IArgs & arg );
	
	/**	 
	* ����:  ����BtnCancel�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRouteCfgCancel( const IArgs & arg );

	/**	 
	* ����:  �༭EdtPriorLevel�ؼ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtPriorLevelChange( const IArgs & arg );
	bool OnEdtPriorLevelKillFocus( const IArgs & arg );

	HRESULT OnRouteAdd( WPARAM wparam, LPARAM lparam );

private:

	vector<CString> m_vecComboPriorLevel;

	const String  m_strEdtPriorLevel;
	const String  m_strIPCtrlDstSubnetIP;
	const String  m_strIPCtrlMastIP;
	const String  m_strIPCtrlGatewayIP;

};

#define ROUTECFGDLGLOGIC    CRouteCfgdlgLogic::GetSingletonPtr()               //NetMngOptlogicָ��

#endif // !defined(AFX_ROUTECFGDLGLOGIC_H__9353F1F3_BA28_482A_8E01_BFD93BB0A411__INCLUDED_)
