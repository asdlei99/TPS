#if !defined(AFX_UMCWEBPROJPPG_H__89D6D7AA_27EB_4DD1_BA5F_379704FD151E__INCLUDED_)
#define AFX_UMCWEBPROJPPG_H__89D6D7AA_27EB_4DD1_BA5F_379704FD151E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// UmcWebProjPpg.h : Declaration of the CUmcWebProjPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CUmcWebProjPropPage : See UmcWebProjPpg.cpp.cpp for implementation.

class CUmcWebProjPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CUmcWebProjPropPage)
	DECLARE_OLECREATE_EX(CUmcWebProjPropPage)

// Constructor
public:
	CUmcWebProjPropPage();

// Dialog Data
	//{{AFX_DATA(CUmcWebProjPropPage)
	enum { IDD = IDD_PROPPAGE_UMCWEBPROJ };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CUmcWebProjPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMCWEBPROJPPG_H__89D6D7AA_27EB_4DD1_BA5F_379704FD151E__INCLUDED)
