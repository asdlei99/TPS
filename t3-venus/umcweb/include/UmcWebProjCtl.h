#if !defined(AFX_UMCWEBPROJCTL_H__1D8DBEBE_3ACD_432D_B2EC_FBBDED99953E__INCLUDED_)
#define AFX_UMCWEBPROJCTL_H__1D8DBEBE_3ACD_432D_B2EC_FBBDED99953E__INCLUDED_

// Added by ClassView
#include "loginLogic.h"
#include "objsafe.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// UmcWebProjCtl.h : Declaration of the CUmcWebProjCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl : See UmcWebProjCtl.cpp for implementation.

class CUmcWebProjCtrl : public COleControl
{
	DECLARE_DYNCREATE(CUmcWebProjCtrl)


    //安全接口 ,防止弹出安全框 2012-6-27 by yjj
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety) 
	STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) ( 
		/* [in] */ REFIID riid, 
		/* [out] */ DWORD __RPC_FAR *pdwSupportedOptions, 
		/* [out] */ DWORD __RPC_FAR *pdwEnabledOptions 
	); 

	STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) ( 
		/* [in] */ REFIID riid, 
		/* [in] */ DWORD dwOptionSetMask, 
		/* [in] */ DWORD dwEnabledOptions 
	); 
	END_INTERFACE_PART(ObjSafe);


// Constructor
public:
 
	CUmcWebProjCtrl();
 
	virtual BOOL OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip);
	virtual BOOL OnSetExtent(LPSIZEL lpSizeL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmcWebProjCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CUmcWebProjCtrl();

	DECLARE_OLECREATE_EX(CUmcWebProjCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CUmcWebProjCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CUmcWebProjCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CUmcWebProjCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CUmcWebProjCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
	afx_msg void OnDestroy();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HRESULT OnBkColorChange( WPARAM wparam, LPARAM lparam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CUmcWebProjCtrl)
	
    //void SetDrawFlag( short nDrawFlag );
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CUmcWebProjCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()
    
// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(COcxCtrl)
		dispidSetDrawFlag = 1L,
			//}}AFX_DISP_ID
	};

	BOOL DeleteUrlCache();
	bool JsRefreshOle( s8* strFun, const CString strParam = "" ); //刷新ole界面

private:
	CRect  m_rectClip;
    BOOL32 m_bInitBefore;      //是否在同一进程已打开一个umc
	String strMidBkDir;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMCWEBPROJCTL_H__1D8DBEBE_3ACD_432D_B2EC_FBBDED99953E__INCLUDED)
