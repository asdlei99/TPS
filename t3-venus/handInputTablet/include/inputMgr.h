// inputMgr.h: interface for the CInputMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTMGR_H__7140DB0E_66E1_4748_8674_82E260855945__INCLUDED_)
#define AFX_INPUTMGR_H__7140DB0E_66E1_4748_8674_82E260855945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 

//输入方式
enum EmInputType
{
    emInputKeyBoard,   //键盘输入
    emInputHandWrite, //手写输入
} ;

 
#define  TIMER_AUTO_RECO    2000
#define  TIMER_REDRAW_UI    101 
#define  TIMER_REFRESH_CAPSLOCK 100
#define  TIMER_SHOW_BOARD   102
#define  TIMER_HIDE_BOARD   103

class CInputMgr: public CWnd  
{
    friend class CSoftKeyboardDlg;

public:
    static CInputMgr* GetSingleTon();
	
	virtual ~CInputMgr();
public:
    
    void RedrawUI( CDC *pDc = NULL );

    void ShowBoard( HWND hTagWnd = NULL );

    void ShowBoardLater();
    
    void HideBoard(); 

    void HideBoardLater();
   
    
    void SetInputType( EmInputType emInputType  );
    EmInputType GetInputType() { return m_emInputType ; }

    void WillUpdateCapsLockState();

    void Init();

    void UpdateImm(  ); 
 
	void RefreshCapsLock();
				 
protected:
   // virtual void RedrawUI();

    BOOL Create( DWORD dwExStyle, CString strName, CRect rcWnd, CWnd* pWnd,DWORD dStyle,UINT nID, CCreateContext* pContext = NULL );
 
	void CheckParam( DWORD& dwExStyle, CWnd** pWnd,DWORD& dStyle,UINT& nID );
 
   void  ReleaseFocus();
   void  ResetCapture();

   
protected:
    CInputMgr(); 
    
   // virtual BOOL OnInitDialog();
   

    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); 
	afx_msg void OnKillFocus(CWnd* pNewWnd);
    
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    
   
    afx_msg void OnDestroy();

    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg HRESULT OnHwDrawNotify( WPARAM wparam , LPARAM lparam );
    afx_msg HRESULT OnHwDrawBeginNotify( WPARAM wparam , LPARAM lparam );
     
    
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    DECLARE_MESSAGE_MAP()

    LRESULT  DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
   
private:
//     typedef BOOL(WINAPI *PFN_UpdateLayeredWindow)( 
//         HWND hWnd,
//         HDC hdcDst,
//         POINT *pptDst,
//         SIZE *psize,
//         HDC hdcSrc,
//         POINT *pptSrc,
//         COLORREF crKey,
//         BLENDFUNCTION *pblend,
// 											  DWORD dwFlags);     
// 	PFN_UpdateLayeredWindow m_s_pfnUpdateLayeredWindow;

   void CInputMgr::AdjustPos( BOOL32 bShow = TRUE );
private:
    static CInputMgr * m_pThis;
 

    EmInputType m_emInputType;

    HWND m_hTagWnd;
    HWND m_hwFocus;
 
    CDC m_cMemDC;
    CBitmap m_cBitmap;   
    u16 m_nTimeInterval;  //自动识别间隔
    
    SIZE  m_szOrig;       //原大小
    
    int   m_swCurTimes;    //当前次数
};





#define SetSoftKBDlgHide() CInputMgr* pInputDlg = CInputMgr::GetSingleTon(); \
    if ( pInputDlg->IsWindowVisible() ) \
{ \
    pInputDlg->HideBoard(); \
}




#define SetSoftKBDlgShow( hWndTag )  CInputMgr::GetSingleTon()->ShowBoard( hWndTag );  

#define SoftKBDlgUpdateImm() CInputMgr::GetSingleTon()->UpdateImm();   


#endif // !defined(AFX_INPUTMGR_H__7140DB0E_66E1_4748_8674_82E260855945__INCLUDED_)

 