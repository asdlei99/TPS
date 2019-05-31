
// kdvplayertesterDlg.h : 头文件
//

#pragma once

#include "kdvtype.h"
#include "kdvdef.h"
#include "osp.h"
#include "medianet_win/kdvmedianet.h"
#include "codecwrapper_win32.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "cdraw.h"
#include "winsock2.h"


#define   WM_STATICMOUSEDBCLIK   WM_USER+500

#define FAILD_PIC_NUM 4
#define TIME_PACKET_CHECK_EVENT 20000
#define TIME_PACKET_CHECK_SPAN 100

enum EMShowType
{
	em_None,
	em_NoVid,
	em_VidErr,
};

class CMyStatic : public CStatic  
{  
public:  
	CMyStatic(void)
	{
		memset(&m_tRcvStatis, 0, sizeof(m_tRcvStatis));
		m_curType = em_None;
	} 
	~CMyStatic(void){}  

	DECLARE_MESSAGE_MAP()  

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); 
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point); 
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


public:
	void OnRefresh(CKdvDecoder* pDecoder);

protected:
	TKdvDecStatis m_tRcvStatis;		

	EMShowType	m_curType;
};  

	
// CkdvplayertesterDlg 对话框
class CkdvplayertesterDlg : public CDialogEx
{
// 构造
public:
	BOOL m_bRedrawFlag;
	CkdvplayertesterDlg(CWnd* pParent = NULL);	// 标准构造函数
	CKdvDecoder  m_KdvDecoder;
	HANDLE      m_hAec;
	CString     m_cIp;
	s8*         m_pLocalIpAddress;
	s8*         m_pRemoteIpAddress;
// 对话框数据
	enum { IDD = IDD_KDVPLAYERTESTER_DIALOG };

public:
	virtual BOOL DestroyWindow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnTimer(UINT nIDEvent);

// 实现
protected:
	HICON     m_hIcon;
	CMyStatic   m_cPlayerWnd;
	BOOL      m_bFullScreen;
	
	BOOL	m_bStartDecode;
	CRect	m_preRect;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void GetLocalIp(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetNetParam();
	afx_msg void OnStartNetRcv();
	afx_msg void OnStopNetRcv();
	afx_msg void OnStartVideoDecomp();
	afx_msg void OnStopVideoDecomp();
	afx_msg void OnFullscreen();
	afx_msg void OnCheckActivept();
	afx_msg void OnSelchangeComboDectype();
	afx_msg void OnKeyFrameCheck();
	afx_msg void OnClear();
	afx_msg void OnRedraw();
	afx_msg void OnStatus();
	afx_msg void OnSnap();
	afx_msg void OnReleasedcaptureVideoWindowSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureAudioVolumeSlider(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnStartDecVid();
	afx_msg void OnStopDecVid();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

protected:
	void ShowFullScreen();
	void ShowNormal();

	void SetPos();

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT  OnStaticDButtonDown(WPARAM wParam, LPARAM  lParam); 
	UINT m_nVideoPort;
	UINT m_nAudioPort;
	UINT m_nRomoteVidPort;
	UINT m_nRomoteAudPort;
	BOOL m_bActivePT;
	UINT m_nActivePT;
	CComboBox m_comDecType;
	CComboBox m_comboFrame;
	CIPAddressCtrl m_cLocalIpAddr;
	CIPAddressCtrl m_cRemoteIpAddr;
	CSliderCtrl m_cscVideoWindow;
	CSliderCtrl m_cscAudioVolume;
	CStatic m_cAPStatic;
	
	afx_msg void OnStartAudioDecomp();
	afx_msg void OnStopAudioDecomp();
	//afx_msg void OnEnChangeVideoLocalPort();
};

