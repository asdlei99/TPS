// handInputTablet.h : main header file for the HANDINPUTTABLET application
//

#if !defined(AFX_HANDINPUTTABLET_H__C97E3ACB_63EB_4591_8947_DA0BE1062F5B__INCLUDED_)
#define AFX_HANDINPUTTABLET_H__C97E3ACB_63EB_4591_8947_DA0BE1062F5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHandInputTabletApp:
// See handInputTablet.cpp for the implementation of this class
//

class CHandInputTabletApp : public CWinApp
{
public:
	CHandInputTabletApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHandInputTabletApp)
	public:
	virtual BOOL InitInstance(); 
    virtual int  ExitInstance();

    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHandInputTabletApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    HHOOK m_hkKeyboard;
    HHOOK m_hkMouse;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HANDINPUTTABLET_H__C97E3ACB_63EB_4591_8947_DA0BE1062F5B__INCLUDED_)
