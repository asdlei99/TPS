// waitingrefreshdlg.h: interface for the CWaitingRefreshDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITINGREFRESHDLG_H__097D226D_6FCB_4C1F_A9DE_D4C622DBD701__INCLUDED_)
#define AFX_WAITINGREFRESHDLG_H__097D226D_6FCB_4C1F_A9DE_D4C622DBD701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparentbasedlg.h"

//当前操作类型
enum Em_Type{ 
    emTypeUpdAddr = 0,
	emTypeExpAddr
};

class CWaitingRefreshDlg : public CTransparentBaseDlg
{
	// Construction
public:
	CWaitingRefreshDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaitingRefreshDlg();

	static CWaitingRefreshDlg* GetWaitWindow();
	static void Clean();  //120821 ldy 加入内存释放
	
	// Dialog Data
	//{{AFX_DATA(CWaitingRefreshDlg)
	enum { IDD = IDD_DIALOG_WAITREFRESH };
	CTransparentStatic	m_stcIcon;
	CTransparentStatic	m_stcMsg;
	//}}AFX_DATA
		
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitingRefreshDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void OnShowWindow(BOOL bShow, UINT nStatus); 
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CMessageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnDestroy();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnBeginWaitingRefresh(WPARAM wParam, LPARAM lParam);
	LRESULT OnEndWaitingRefresh(WPARAM wParam, LPARAM lParam);
	LRESULT OnLoadAddrNumNty(WPARAM wParam, LPARAM lParam);   //提示导入地址簿时剩余的条目数量

	void UpdateWaitingImg();
private:
	int                 m_nUpdateTime;
	
	Em_ImgSchm          m_emImgSchm;

	static CWaitingRefreshDlg* m_pcWaitWindow;

	//防止AfxGetMainWnd获取不到的bug
	Window *m_pMainWnd;		//在OnShowWindow中记录操作的AfxGetMainWnd

	Em_Type m_emType;
};

#endif // !defined(AFX_WAITINGREFRESHDLG_H__097D226D_6FCB_4C1F_A9DE_D4C622DBD701__INCLUDED_)
