// NetPacketLogic.h: interface for the CNetPacketLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
ģ����      : CNetPacketLogic
�ļ���      : NetPacketLogic.h
����ļ�    : telnetsocket.h
�ļ�ʵ�ֹ���: ����ץ������
����        : �����
�汾        : V1.0  Copyright(C) 2012-2016 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2016/8/15      1.0                     ����
******************************************************************************/

#if !defined(AFX_NETPACKETLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_NETPACKETLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"
#include "telnetsocket.h"

enum EM_FTPCAPTURETRANS_TYPE      //�ļ�����򵼳�����
{
	em_FTPCAPTRANS_IMPORT,
	em_FTPCAPTRANS_EXPORT,
};

class CNetPacketLogic: public CLogicBase, public ISingleTon<CNetPacketLogic>
{
public:
	CNetPacketLogic();
	~CNetPacketLogic();

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
	
	//����ץ����Ϣ
	void UpdateCaptureData();
	//��õ�ǰץ��״̬
	bool GetCaptureState();
	//��õ�ǰ����״̬
	bool GetExportState();

	void SetCaptureFileSize();

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

	/**	 
	* ����:  ���´������
	* @return   
	* @remarks	 
	*/
	bool OnExportProgress( const IArgs & arg );  //������������

	bool OnCaptureMaxSize( const IArgs & arg );  //�ﵽץ������ʱ��ֹͣץ������Ӧ

	bool OnCaptureFail(const IArgs & arg);       //ץ��ʧ��

	/** ����:  ftp��Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );
	/** ����:  telnet��Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
    HRESULT OnSetTelnetInfoRsp( WPARAM wparam, LPARAM lparam );

	/** ����:  ������Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );

private:
	bool OnBtnPacket(const IArgs & arg);  //�������ץ����ť
	bool OnBtnExport(const IArgs & arg);  //���ץ����ť

	void BtnStartCapture();  //��ʼץ��
	void BtnStopCapture();   //���ֹͣץ����ť����Ӧ����
	void StartExportFile();  //��ʼ����
    void GetFileSize(u32 m_dwCaptureFileSize, s8 *chFileSize); //�ļ���ʾ��С��ʽ��
	void IsCaptureSuccess(); //�Ƿ�ץ���ɹ�

	void StartCapture();     //ftp��telnet��������ʼץ��
	void ExportPacket();     //ftp�����󵼳�ץ��

private:
	const String m_strBtnStartPacket; 
	const String m_strBtnCaptureExport;
	const String m_strCaptureTimer;
	const String m_strCaptureFileSize;
	const String m_strExportProgress;

private:
	Window* m_pWnd;
	CTelnetSocket m_cTelnet;  //Զ�̵�¼������

	CFtpCtrl m_cFtp;    //FTP��
	EM_FTPCAPTURETRANS_TYPE m_emFtpTransType;  //����/����״̬����
	EmFtpStatus m_emFileFtpStatus;      //��ǰFTP����״̬
	Value_ProgressPos m_valProgress;    //��������
	u32   m_dwTime;    //��ʱ��            
	u32   m_dwCaptureFileSize;  //ץ����С
	u32   m_dwTotalFileSize;    //����ץ���ļ���С
	bool  m_bIsCapturing;       //�Ƿ�����ץ��
	bool  m_bIsExporting;       //�Ƿ����ڵ���
	u8    m_nThreeCount;        //3����ж�ץ���Ƿ�ɹ�

	BOOL m_bIsClickBtnPacket;   //�Ƿ�����ʼץ��
	BOOL m_bIsClickBtnExport;   //�Ƿ�������ץ��
};

#define CNETPACKETLOGIC    CNetPacketLogic::GetSingletonPtr()               //CNetPacketLogicָ��

#endif //!defined(AFX_NETPACKETLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)