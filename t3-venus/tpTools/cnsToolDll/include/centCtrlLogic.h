// centCtrlLogic.h: interface for the CCentCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_)
#define AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"
//״̬��Ϣ
class CCentCfgStatusMesDlg : public CLogicBase, public ISingleTon<CCentCfgStatusMesDlg>  
{
public:
	CCentCfgStatusMesDlg();
	virtual ~CCentCfgStatusMesDlg();
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
//	void HideAllWnd();
private:
	/** ����:  ���շ������˷���������ϢȻ����������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnCameraInfoNty( WPARAM wParam, LPARAM lParam );

	/** ����:  ��������Ŀ���״̬ת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	String CamStateToString( EmCamPowerMode& emSwitchState );
	/** ����:  ���շ������˷���������ϢȻ������ĵ������״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );
	/** ����:  ���շ������˷���������ϢȻ�������ʾ��״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	LRESULT OnDisplayInfoNty( WPARAM wParam, LPARAM lParam );
	/** ����:  ����ʾ���Ŀ���״̬ת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String StateToString( EmTvPowerMode& emSwitchState );
	/** ����:  ���շ������˷���������ϢȻ����¿յ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnUpdateAirInfoNty( WPARAM wParam, LPARAM lParam );
	/** ����:  ���շ������˷���������ϢȻ����µƹ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnLightInfoNty( WPARAM wParam, LPARAM lParam );
	/** ����:  ���շ������˷���������ϢȻ����¿յ�״̬
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnAirInfoNty( WPARAM wParam, LPARAM lParam );
protected:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	void RegMsg();
};

//����
class CCentCfgCurtainDlg  : public CLogicBase, public ISingleTon<CCentCfgCurtainDlg>  
{
public:
	CCentCfgCurtainDlg();
	virtual ~CCentCfgCurtainDlg();
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

	 HRESULT OnUpdateCurNty( WPARAM wparam, LPARAM lparam );
	 /** ����:  ���´�������
	 *  @param[in] 
	 *  @return 
	 *  @remarks 
	 */
	 HRESULT OnUpdateCurName( WPARAM wparam, LPARAM lparam );
	 /** ����:  �������ô������ط���
	 *  @param[in] 
	 *  @return 
	 *  @remarks 
	 */
	 HRESULT OnCurtainInd( WPARAM wparam, LPARAM lparam );
	 /** ����:  �������ô�����������
	 *  @param[in] 
	 *  @return 
	 *  @remarks 
	 */
	 HRESULT OnCurtainNumInd( WPARAM wparam, LPARAM lparam );

	 void RegMsg();
private:
     /** ����:  ��������������
	 *  @param[in] IArgs  �������
	 *  @return bool
	 *  @remarks 
	 */
	bool OnBtnOptRenameDlg( const IArgs& args );
	/** ����:  �����б���Ŀ
	*  @param[in] IArgs  �������
	*  @return bool
	*  @remarks 
	*/
	bool OnClickCurList( const IArgs & arg );
	/** ����:  ���ô�������
	*  @param[in] IArgs  �������
	*  @return bool
	*  @remarks 
	*/
	bool OnCurNumCfg( const IArgs& args );
	/** ����:  ���ô�������
	*  @param[in] IArgs  �������
	*  @return bool
	*  @remarks 
	*/
	bool OnBtnSwitchCurtain( const IArgs& args );
	/** ����:  ����б���ͼƬ
	*  @param[in] IArgs  �������
	*  @return bool
	*  @remarks 
	*/
	bool OnClickCurLstBlack( const IArgs& args );

	void SetDefaultCurName( );
	/** ����:  ��ȡѡ�е��б���Ŀ����
	*  @param[in] IArgs  �������
	*  @return bool
	*  @remarks 
	*/
	s32 GetSelItemIndex( TCentreCurName &tCurtainName );

private:
	TCentreCurInfo m_tCentreCurInfo;
	TCentreCurInfo m_tTempCenCurInfo;
	s32            m_nSelIndex;
};

//�յ��·�
class CCentCfgAirCondition  : public CLogicBase, public ISingleTon<CCentCfgAirCondition>  
{
public:
	CCentCfgAirCondition();
	virtual ~CCentCfgAirCondition();
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
	 *  @remarks 
	 */
	 virtual void Clear() ;

	 void RegMsg();

	 bool IsACChange();
	 /** ����:  
	 *  @param[in] 
	 *  @return 
	 *  @remarks  
	 */
	 LRESULT OnUpdateAirInfoNty( WPARAM wParam, LPARAM lParam );

	 LRESULT OnAirConditionNty( WPARAM wParam, LPARAM lParam );
	 /** ����:  ��ȡ�����޸�����������
	 *  @param[in] 
	 *  @return 
	 *  @remarks  
	 */
	 s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
private:
	 bool OnSwitchAirCondition( const IArgs & arg );

	 bool OnBtnSave( const IArgs & arg );

	 bool OnBtnCancel( const IArgs & arg );
	 /** ����:  �����Ƿ���ڿյ������¿յ�����
	 *  @param[in] 
	 *  @return 
	 *  @remarks  
	 */
	 void UpdateAcState();

	 bool OnACNumCfg( const IArgs & arg );
	 /** ����:  ��������޸�״̬
	 *  @param[in] 
	 *  @return 
	 *  @remarks  
	 */
	 void UpdateState();

	 bool SaveMsgBox();
private:
	u8	m_byAcNum;
};

class CCentCfgDuoVideo  : public CLogicBase, public ISingleTon<CCentCfgDuoVideo>  
{
public:
	CCentCfgDuoVideo();
	virtual ~CCentCfgDuoVideo();
public:
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

	 LRESULT OnDuoVideoNty( WPARAM wParam, LPARAM lParam );

	 bool OnBtnDuoVideo( const IArgs & arg );
private:
	BOOL		m_bOpen;
};

class CCentCfgMatrix  : public CLogicBase, public ISingleTon<CCentCfgMatrix>  
{
public:
	CCentCfgMatrix();
	virtual ~CCentCfgMatrix();
public:
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

	 //�޸ľ�������
	 virtual bool OnChangedMatrixName( const IArgs & arg ); 
	 //�޸ľ�����
	 virtual bool OnChangedMatrixStore( const IArgs & arg ); 
	 //�޸ľ����ͺ�
	 virtual bool OnChangedMatrixModel( const IArgs & arg ); 
	 //�޸ľ��������
	 virtual bool OnChangedMatrixServer( const IArgs & arg ); 
	 //�޸ľ�����ʾ
	 virtual bool OnChangedMatrixSwitch( const IArgs & arg );
	 //����
	 virtual bool OnBtnSave( const IArgs & arg ); 
	 //ȡ��
	 virtual bool OnBtnCancel( const IArgs & arg ); 
	 //����������Ϣ
	 LRESULT OnMatrixConfigNty( WPARAM wParam, LPARAM lParam );

	 bool IsMatrixChange();
	 bool SaveMsgBox();

	 s32 GetCtrlChangeNum() { return m_vctWndName.size(); }

private:
	//��������
	TTPMatrixConfig m_tTPMatrixConfig;
	
};

//�������
enum EmGroupNum{
	emOneGroup = 1,
	emTweGroup,
	emThreeGroup,
	emFourGroup,
	emFiveGroup,
};
class CCentCfgSrceen  : public CLogicBase, public ISingleTon<CCentCfgSrceen>  
{
public:
	CCentCfgSrceen();
	virtual ~CCentCfgSrceen();
public:
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
private:
    //�޸��豸����
    bool OnChangedSrceenType( const IArgs & arg );
    //�޸Ĳ�����
    bool OnChangedBaudRate( const IArgs & arg );
    //�޸�����λ
    bool OnChangedDataBits( const IArgs & arg );
    //�޸�У��λ
    bool OnChangedCheckBits( const IArgs & arg );
    //�޸�ֹͣλ
    bool OnChangedStopBits( const IArgs & arg );
    //�޸ķ�����
	bool OnChangedGroupCount( const IArgs & arg );
    //�޸�����
    bool OnChangedGroupName1( const IArgs & arg );
    bool OnChangedGroupName2( const IArgs & arg );
    bool OnChangedGroupName3( const IArgs & arg );
    bool OnChangedGroupName4( const IArgs & arg );
    bool OnChangedGroupName5( const IArgs & arg );
    //�޸ĵ�ַ��
    bool OnChangedAddrCode1( const IArgs & arg );
    bool OnChangedAddrCode2( const IArgs & arg );
    bool OnChangedAddrCode3( const IArgs & arg );
    bool OnChangedAddrCode4( const IArgs & arg );
    bool OnChangedAddrCode5( const IArgs & arg );
    //����
    bool OnBtnSave( const IArgs & arg ); 
    //ȡ��
	bool OnBtnCancel( const IArgs & arg );

    //������������Ϣ
    LRESULT OnCenDFScreenConfigNty( WPARAM wParam, LPARAM lParam );
    LRESULT OnModifyDFScreenSerCfgInd( WPARAM wParam, LPARAM lParam );
    LRESULT OnModifyDFScreenGroupInd( WPARAM wParam, LPARAM lParam );

    bool IsCenDFScreenSerChange( EmComConfigType emDevieceType, TSerialCfg & tSerialCfg );
    bool IsCenDFScreenGrpChange( u32 dwGrpNum, TCenDownOrFlipScreenCfg* ptCenDFScreenCfg );

private:
	//int m_nGroupNum;//��ǰ�ж�������
    TCenDownOrFlipScreenInfo m_tCenDFScreenInfo;//������������Ϣ
};

#endif // !defined(AFX_CENTCTRLLOGIC_H__777D44E7_A11A_4507_AA4E_F26B05745548__INCLUDED_)
