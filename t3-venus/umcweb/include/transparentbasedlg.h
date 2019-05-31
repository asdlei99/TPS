#if !defined(AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_)
#define AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransparentBaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg dialog

typedef BOOL(WINAPI *PFN_SetLayeredWindowAttributes)(
                                                     HWND hwnd,
                                                     COLORREF crKey,
                                                     BYTE bAlpha,
                                                     DWORD dwFlags);

typedef BOOL(WINAPI *PFN_UpdateLayeredWindow)( 
                                              HWND hWnd,
                                              HDC hdcDst,
                                              POINT *pptDst,
                                              SIZE *psize,
                                              HDC hdcSrc,
                                              POINT *pptSrc,
                                              COLORREF crKey,
                                              BLENDFUNCTION *pblend,
											  DWORD dwFlags);

#ifndef WS_EX_LAYERED
#	define WS_EX_LAYERED			0x00080000
#endif

#ifndef LWA_ALPHA
#	define LWA_ALPHA				0x00000002
#endif

#ifndef ULW_ALPHA
#	define ULW_ALPHA				0x00000002
#endif

#ifndef AC_SRC_ALPHA
#	define AC_SRC_ALPHA				0x01
#endif
class CTransparentBaseDlg : public CDialog
{
// Construction
public:
	CTransparentBaseDlg(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransparentBaseDlg();
// Dialog Data
	//{{AFX_DATA(CTransparentBaseDlg)
	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentBaseDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnWindowPosChanging(WINDOWPOS   FAR*   lpwndpos); 
    afx_msg void OnSize(UINT nType, int cx, int cy) ;
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnBindWnd( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:
    void SetAutoHideStatus( BOOL bStatus ){ m_bAutoHide = bStatus; } 
    BOOL ShowWindow(int nCmdShow)
    {
        BOOL bRet = CWnd::ShowWindow( nCmdShow );

        if ( SW_SHOW == nCmdShow )
        {
            SendMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

    BOOL UpdateData(BOOL bSaveAndValidate = TRUE)
    {
        BOOL bRet = CDialog::UpdateData( bSaveAndValidate );

        if ( FALSE == bSaveAndValidate )
        {
            PostMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

	void SetBindWnd( HWND hdl );


protected:
    virtual void RedrawUI();

    virtual void DrawChildWnd( Graphics *pGraphics, HWND hParentWnd );
    
	void InitMemDC(); //2012-7-2 ����ÿ�λ��ƶ�����memeryDc  yjj
public:
    UINT    m_dwBkResourceID;
    BOOL32  m_bTransparentWithoutBK;    // ���ޱ���ͼ��������Ƿ�͸����ʾ
    BOOL32  m_bRedrawUIImediately;      // �Ƿ�����ˢ�£���������ˢ��Ƶ�ʵ�

	virtual s32		GetWindowWidth();
	virtual s32		GetWindowHeight();
	virtual BYTE	GetSourceConstantAlpha(){ return m_byteSourceConstantAlpha; }
	virtual void	SetSourceConstantAlpha(BYTE byteSCA){ m_byteSourceConstantAlpha = byteSCA; }
protected:
    static PFN_SetLayeredWindowAttributes   m_s_pfnSetLayeredWindowAttributes;
	static PFN_UpdateLayeredWindow          m_s_pfnUpdateLayeredWindow;

    Image   *m_pImageBK;
    BOOL32  m_bReadyToRedrawUI; // ����ˢ��̫Ƶ��������Ч�ʽ���
	BYTE	m_byteSourceConstantAlpha; //͸����
	BOOL32  m_bAjustSize;       // �˴����Ƿ���ݴ��ڷֱ��ʵ�������С��
    BOOL32  m_bScale;
    BOOL32 m_bAutoHide;  //ʧȥ�����Զ�����

	//���ʹ��ͼƬ�ļ��У�������ͼƴ�� 
    Image   *m_pImgLeft;           
    Image   *m_pImgMiddle;
    Image   *m_pImgRight;
	HWND     m_hBindWnd;
	HDC      m_hDcMem;
	HBITMAP  m_hBtMap;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSPARENTBASEDLG_H__BCB28327_5163_451D_AE72_6DCD487821DA__INCLUDED_)
