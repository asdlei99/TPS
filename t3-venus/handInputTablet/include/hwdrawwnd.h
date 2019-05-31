// hwdrawwnd.h: interface for the CHWDrawWnd class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_HWDRAWWND_H__8FA1D33A_F895_490A_890E_E4BDB29BD6BF__INCLUDED_)
#define AFX_HWDRAWWND_H__8FA1D33A_F895_490A_890E_E4BDB29BD6BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHWDrawWnd : public CWnd  
{
public:
	CHWDrawWnd();
	virtual ~CHWDrawWnd();
public:
	//{{AFX_VIRTUAL(CBitWnd)
	//}}AFX_VIRTUAL


    //设置需要通知的窗口
    void SetNofifyWnd( CWnd* pNoitfyWnd );
protected:
	//{{AFX_MSG(CBitWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

    afx_msg HRESULT OnHwDrawNotify( WPARAM wparam , LPARAM lparam );
    
	/* afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	*/ //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL  Create(UINT wStyle, CWnd * pParentWnd, UINT nID);
	BOOL  Init(); 
	HWND  GetDrawHwnd();

    void ReDrawUI();
    void  SetImg( Image * pImg )
    {  
        m_pImgeBK = pImg; 
    }

    void SetImgPos( CPoint ImgPos )
    {
        m_posImg = ImgPos;
    }
private:
	Image   *m_pImgeBK;
    CPoint m_posImg;

    CWnd    *m_pNotifyWnd;
    CDC     m_cMemDC;    
    CBitmap m_cBitmap;
    BOOL32  m_bIsCreated;

  
};

#endif // !defined(AFX_HWDRAWWND_H__8FA1D33A_F895_490A_890E_E4BDB29BD6BF__INCLUDED_)
