#if !defined(AFX_DLGCHILD_H__CFA810F1_303B_4A0A_BBF7_465259725327__INCLUDED_)
#define AFX_DLGCHILD_H__CFA810F1_303B_4A0A_BBF7_465259725327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgchild.h : header file
//
 
#include "transparentbasedlg.h"
 
/////////////////////////////////////////////////////////////////////////////
// CDlgChild dialog

class CDlgChild : public CTransparentBaseDlg
{
// Construction
public:
	CDlgChild(UINT nIDDlgChild,CWnd* pParent = NULL);   // standard constructor
	~CDlgChild();

// Dialog Data
	//{{AFX_DATA(CDlgChild)
	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChild)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChild)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
	BOOL ShowWindow(int nCmdShow)
    {
        BOOL bRet = CDialog::ShowWindow( nCmdShow );
        
		
        if ( SW_SHOW == nCmdShow )
        {
			m_bVisible = TRUE; 
            SendMessage( WM_REDRAW_UI, NULL, NULL );
        }
		else
		{
			m_bVisible = FALSE;
		}
		
        return bRet;
    }


private:
	void InitDc();

	LRESULT RedrawUI( WPARAM wParam, LPARAM lParam );

protected:
	CDC     m_cMemDC;    
    CBitmap m_cBitmap; 
	BOOL32  m_IsCreateGrp; //是否需要创建graphics 并下发给子窗口
	BOOL32 m_bIsSegment;
	s32 m_nSegmentLen;
	BOOL32 m_bVisible;
	BOOL m_bShowMosaicHoriImg;
	BOOL m_bShowMosaicVertImg;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHILD_H__CFA810F1_303B_4A0A_BBF7_465259725327__INCLUDED_)
