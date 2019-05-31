// NetDiagnosticLogic.h: interface for the CNetDiagnosticLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETDIAGNOSTICLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_NETDIAGNOSTICLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CNetDiagnosticLogic: public CLogicBase, public ISingleTon<CNetDiagnosticLogic> 
{
public:
	CNetDiagnosticLogic();
	virtual ~CNetDiagnosticLogic();

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
	virtual void UnRegFunc();
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
    virtual void Clear();

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

private:
		/** ����:  �յ����������ʵ���Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnUpDownstreamNty( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ�������Ϣ�Ļظ�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnLostPacketRsp( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ��������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);
	bool OnBtnStatistic( const IArgs & arg );
	bool OnBtnRefresh( const IArgs & arg );

	HRESULT OnRecordMes( WPARAM wparam, LPARAM lparam );
	void WriteToFile();

private:
	const String m_strLostPacket;					//������
    const String m_strUpstream;						//������������
    const String m_strDownstream;					//������������
	CFile		 m_cFile;
	BOOL		 m_bIsRecording;					//����ͳ��	
};

#endif   // !defined(AFX_NETDIAGNOSTICLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)