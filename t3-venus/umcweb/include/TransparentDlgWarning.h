#if !defined(AFX_TRANSPARENTDLGWARNING_H__4EBAE969_AF68_4757_87C7_19886326C939__INCLUDED_)
#define AFX_TRANSPARENTDLGWARNING_H__4EBAE969_AF68_4757_87C7_19886326C939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransparentDlgWarning.h : header file
//
#include "uiexhead.h"
#include "dlgchild.h"
/////////////////////////////////////////////////////////////////////////////
// CTransparentDlgWarning dialog

class CTransparentDlgWarning : public CTransparentBaseDlg
{
// Construction
public:
	CTransparentDlgWarning(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransparentDlgWarning)
	enum { IDD = IDD_DIALOG_WARNING };

	CTransparentStatic	m_stDataTitle;
	CTransparentStatic	m_stDataFir;
	CTransparentStatic	m_stDataSec;
	CTransparentStatic	m_stDataThi;
	CTransparentStatic	m_stDataFor;
	CTransparentStatic	m_stDataFif;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentDlgWarning)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentDlgWarning)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT UpdateItem( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnHideWndNotify( WPARAM wParam, LPARAM lParam );
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static CTransparentDlgWarning* GetDlgPtr(); 
	static void Clean();
	void MessageBoxWnd( const CString& strWaringText, CWnd* pWnd = NULL);
	void UpdateWarningIcon( BOOL bIcon );
    void HideMsgBox();
	void InitDlg();

 
private:
	std::vector<CString> m_vecWarning;
	static CTransparentDlgWarning *m_pDlg;
	BOOL m_bDlgShow;

};

//系统消息警告
#define MESSAGEWND(p/*,pwnd*/){ CTransparentDlgWarning::GetDlgPtr()->UpdateWarningIcon( TRUE );\
    CTransparentDlgWarning::GetDlgPtr()->MessageBoxWnd(p ); }

#define HIDEMESSAGEWND  CTransparentDlgWarning::GetDlgPtr()->HideMsgBox();  


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTDLGWARNING_H__4EBAE969_AF68_4757_87C7_19886326C939__INCLUDED_)
