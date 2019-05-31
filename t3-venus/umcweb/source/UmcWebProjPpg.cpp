// UmcWebProjPpg.cpp : Implementation of the CUmcWebProjPropPage property page class.

#include "stdafx.h"
#include "UmcWebProj.h"
#include "UmcWebProjPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CUmcWebProjPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CUmcWebProjPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CUmcWebProjPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CUmcWebProjPropPage, "UMCWEBPROJ.UmcWebProjPropPage.1",
	0x1d41d087, 0x79e8, 0x495c, 0xab, 0xbb, 0x29, 0xd0, 0x2d, 0xa6, 0x99, 0x3e)


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjPropPage::CUmcWebProjPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CUmcWebProjPropPage

BOOL CUmcWebProjPropPage::CUmcWebProjPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_UMCWEBPROJ_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjPropPage::CUmcWebProjPropPage - Constructor

CUmcWebProjPropPage::CUmcWebProjPropPage() :
	COlePropertyPage(IDD, IDS_UMCWEBPROJ_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CUmcWebProjPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjPropPage::DoDataExchange - Moves data between page and properties

void CUmcWebProjPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CUmcWebProjPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjPropPage message handlers
