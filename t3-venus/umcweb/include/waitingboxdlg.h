// waitingboxdlg.h: interface for the CWaitingBox class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_WAITINGBOX_H__94913592_2F00_4D59_BED5_D6705F8209B6__INCLUDED_)
#define AFX_WAITINGBOX_H__94913592_2F00_4D59_BED5_D6705F8209B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// waitingboxdlg.h : header file
//
#include "transparentbasedlg.h"

//当前操作类型
enum Em_OperType
{ 
	emUpdateAddr = 0,
	emLoadAddr
};
/////////////////////////////////////////////////////////////////////////////
// CWaitingBox dialog

class CWaitingBox : public CTransparentBaseDlg
{
// Construction
public:
	CWaitingBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaitingBox)
	enum { IDD = IDD_DIALOG_WAITINGBOX };
	CTransparentStatic	m_stcIcon;
	CTransparentStatic	m_stcMsg;
	//}}AFX_DATA
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitingBox)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWaitingBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
	LRESULT OnEndWaitingRefresh(WPARAM wParam, LPARAM lParam);
	LRESULT OnLoadAddrNumNty(WPARAM wParam, LPARAM lParam);   //提示导入地址簿时剩余的条目数量
	
	void UpdateWaitingImg();
	
public:
	static BOOL IsMsgBoxVisible( BOOL bEndDlg ); 
	void SetOperType( Em_OperType emType ){ m_emType = emType; }
	
private:
	int m_nUpdateTime;
	Em_ImgSchm m_emImgSchm;
	Em_OperType m_emType;
	BOOL m_bRecvAddrNum;
};

//WaitingBox弹出框
#define WAITINGWNDBOX( pthis, emType ){ \
	ISWAITINGBOXVISIBLE( TRUE );\
	CWaitingBox dlg(pthis);\
	dlg.SetOperType(emType);\
	s32 nRetValue = dlg.DoModal();\
}

#define ISWAITINGBOXVISIBLE( bEndDlg )   CWaitingBox::IsMsgBoxVisible( bEndDlg );

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITINGBOX_H__94913592_2F00_4D59_BED5_D6705F8209B6__INCLUDED_)
