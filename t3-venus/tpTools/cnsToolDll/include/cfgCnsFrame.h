// cfgCnsFrame.h: interface for the CcfgCnsFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGCNSFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
#define AFX_CFGCNSFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgCnsFrame  : public CLogicBase, public ISingleTon<CCfgCnsFrame>  
{
public:
	CCfgCnsFrame();
	virtual ~CCfgCnsFrame();
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
	/** ����:  ��ʼ�����ò˵�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();
	/** ����:  ���cns���ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCnsCfg( const IArgs& args );
	/** ����:  ������簲ȫ���ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetSecurityMgrCfg( const IArgs& args );
	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetMgrCfg( const IArgs& args );
	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
//	bool OnClickMixCfg( const IArgs& args );
	/** ����:  ������������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickServerCfg( const IArgs& args );
	/** ����:  ����������ð�ť����Ӧ�¼�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCallSerCfg( const IArgs& args );
	/** ����:  Tableҳ�л�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
	bool OnClickAdvanceCfg( const IArgs& args );
public:
	string m_strCfgCurWnd;//��ǰ��ʾ�Ĵ���
private:
	string m_strLstFunMenu;//�����б� 
};

#endif // !defined(AFX_CFGCNSFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
