// CfgDiagnosticFrameLogic.h: interface for the CCfgDiagnosticFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGDIAGNOSTICFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
#define AFX_CFGDIAGNOSTICFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgDiagnosticFrameLogic  : public CLogicBase, public ISingleTon<CCfgDiagnosticFrameLogic>  
{
public:
	CCfgDiagnosticFrameLogic();
	virtual ~CCfgDiagnosticFrameLogic();
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
	/** ����:  �������д���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void HideAllWnd();
private:
	/** ����:  ��ʼ����ϲ��Բ˵�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();
	/** ����:  ����ӿ���ϰ�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickInterfaceDiagnostic( const IArgs& args );
	/** ����:  ���������ϰ�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetDiagnostic( const IArgs& args );
	/** ����:  �������ץ����ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetPacket( const IArgs& args );
	/** ����:  Tableҳ�л�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
public:
	string m_strCfgCurWnd;//��ǰ��ʾ�Ĵ���
private:
	string m_strLstFunMenu;//�����б� 
};

#endif // !defined(AFX_CFGDIAGNOSTICFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
