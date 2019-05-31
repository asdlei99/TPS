// UmcWebProjCtl.cpp : Implementation of the CUmcWebProjCtrl ActiveX Control class.

#include "stdafx.h"
#include "UmcWebProj.h"
#include "UmcWebProjCtl.h"
#include "UmcWebProjPpg.h"

#include <atlbase.h> //key head file
#include <Mshtml.h>  //key head file


#include <wininet.h>

#include "umcwebglobaldef.h"
#define _NMS_COMMON_CPP_
#include "common.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"wininet.lib")

extern CMainLogic * g_pMainDlg;
extern CLoginLogic* m_pLoginDlg;

extern BOOL g_bIsLoginDestory;

HANDLE m_hMutex = NULL;

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
IMPLEMENT_DYNCREATE(CUmcWebProjCtrl, COleControl)
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CUmcWebProjCtrl, COleControl)
	//{{AFX_MSG_MAP(CUmcWebProjCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_DEF_CHANGEBKCOLOR, OnBkColorChange )
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CUmcWebProjCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CUmcWebProjCtrl)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CUmcWebProjCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CUmcWebProjCtrl, COleControl)
	//{{AFX_EVENT_MAP(CUmcWebProjCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CUmcWebProjCtrl, 1)
	PROPPAGEID(CUmcWebProjPropPage::guid)
END_PROPPAGEIDS(CUmcWebProjCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CUmcWebProjCtrl, "UMCWEBPROJ.UmcWebProjCtrl.1",
	0x85797439, 0xd3c2, 0x4dd0, 0xa3, 0xde, 0x1f, 0x79, 0xd2, 0xf2, 0xff, 0x33)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CUmcWebProjCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DUmcWebProj =
		{ 0x2b21b77b, 0x7fa8, 0x4b76, { 0x86, 0x88, 0x30, 0x5d, 0x22, 0x30, 0x2e, 0x7e } };
const IID BASED_CODE IID_DUmcWebProjEvents =
		{ 0xd65950a5, 0xc91c, 0x47d2, { 0xbb, 0x59, 0xd6, 0xf, 0x18, 0xb, 0xb7, 0xd5 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwUmcWebProjOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CUmcWebProjCtrl, IDS_UMCWEBPROJ, _dwUmcWebProjOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::CUmcWebProjCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CUmcWebProjCtrl

BOOL CUmcWebProjCtrl::CUmcWebProjCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_UMCWEBPROJ,
			IDB_UMCWEBPROJ,
			afxRegApartmentThreading,
			_dwUmcWebProjOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


///////////////////////////////////////////////////////////////////////////// 
// Interface map for IObjectSafety

BEGIN_INTERFACE_MAP( CUmcWebProjCtrl, COleControl ) 
INTERFACE_PART(CUmcWebProjCtrl, IID_IObjectSafety, ObjSafe) 
END_INTERFACE_MAP()

///////////////////////////////////////////////////////////////////////////// 
// IObjectSafety member functions

// Delegate AddRef, Release, QueryInterface

ULONG FAR EXPORT CUmcWebProjCtrl::XObjSafe::AddRef() 
{ 
    METHOD_PROLOGUE(CUmcWebProjCtrl, ObjSafe) 
    return pThis->ExternalAddRef(); 
}

ULONG FAR EXPORT CUmcWebProjCtrl::XObjSafe::Release() 
{ 
    METHOD_PROLOGUE(CUmcWebProjCtrl, ObjSafe) 
    return pThis->ExternalRelease(); 
}

HRESULT FAR EXPORT CUmcWebProjCtrl::XObjSafe::QueryInterface( 
    REFIID iid, void FAR* FAR* ppvObj) 
{ 
    METHOD_PROLOGUE(CUmcWebProjCtrl, ObjSafe) 
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj); 
}

const DWORD dwSupportedBits = 
INTERFACESAFE_FOR_UNTRUSTED_CALLER | 
INTERFACESAFE_FOR_UNTRUSTED_DATA; 
const DWORD dwNotSupportedBits = ~ dwSupportedBits; 

///////////////////////////////////////////////////////////////////////////// 
// CStopLiteCtrl::XObjSafe::GetInterfaceSafetyOptions 
// Allows container to query what interfaces are safe for what. We're 
// optimizing significantly by ignoring which interface the caller is 
// asking for. 
HRESULT STDMETHODCALLTYPE 
CUmcWebProjCtrl::XObjSafe::GetInterfaceSafetyOptions( 
/* [in] */ REFIID riid, 
        /* [out] */ DWORD __RPC_FAR *pdwSupportedOptions, 
        /* [out] */ DWORD __RPC_FAR *pdwEnabledOptions) 
{ 
METHOD_PROLOGUE(CUmcWebProjCtrl, ObjSafe)

HRESULT retval = ResultFromScode(S_OK);

// does interface exist? 
IUnknown FAR* punkInterface; 
retval = pThis->ExternalQueryInterface(&riid, 
     (void * *)&punkInterface); 
if (retval != E_NOINTERFACE) { // interface exists 
punkInterface->Release(); // release it--just checking! 
} 

// we support both kinds of safety and have always both set, 
// regardless of interface 
*pdwSupportedOptions = *pdwEnabledOptions = dwSupportedBits;

return retval; // E_NOINTERFACE if QI failed 
}

///////////////////////////////////////////////////////////////////////////// 
// CStopLiteCtrl::XObjSafe::SetInterfaceSafetyOptions 
// Since we're always safe, this is a no-brainer--but we do check to make 
// sure the interface requested exists and that the options we're asked to 
// set exist and are set on (we don't support unsafe mode). 
HRESULT STDMETHODCALLTYPE 
CUmcWebProjCtrl::XObjSafe::SetInterfaceSafetyOptions( 
        /* [in] */ REFIID riid, 
        /* [in] */ DWORD dwOptionSetMask, 
        /* [in] */ DWORD dwEnabledOptions) 
{ 
    METHOD_PROLOGUE(CUmcWebProjCtrl, ObjSafe) 

// does interface exist? 
IUnknown FAR* punkInterface; 
pThis->ExternalQueryInterface(&riid, (void * *)&punkInterface); 
if (punkInterface) { // interface exists 
punkInterface->Release(); // release it--just checking! 
} 
else { // interface doesn't exist 
return ResultFromScode(E_NOINTERFACE); 
}

// can't set bits we don't support 
if (dwOptionSetMask & dwNotSupportedBits) { 
return ResultFromScode(E_FAIL); 
} 

// can't set bits we do support to zero 
dwEnabledOptions &= dwSupportedBits; 
// (we already know there are no extra bits in mask ) 
if ((dwOptionSetMask & dwEnabledOptions) != 
   dwOptionSetMask) { 
return ResultFromScode(E_FAIL); 
}        

// don't need to change anything since we're always safe 
return ResultFromScode(S_OK); 
}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::CUmcWebProjCtrl - Constructor

CUmcWebProjCtrl::CUmcWebProjCtrl(): m_bInitBefore(FALSE)
{
	InitializeIIDs(&IID_DUmcWebProj, &IID_DUmcWebProjEvents);

	// TODO: Initialize your control's instance data here.
	//long curX = 4*BASE_SCREEN_WIDTH_INIE*CUR_SCREEN_WIDTH_PER;
	//long curY = 4*BASE_SCREEN_HEIGHT_INIE*CUR_SCREEN_HEIGHT_PER;
	//SetInitialSize(curX,curY);

	//JsRefreshOle("refreshole");
	SetInitialSize(/*BASE_SCREEN_WIDTH*/BASE_SCREEN_WIDTH_INIE,BASE_SCREEN_HEIGHT_INIE);  

	TCHAR   szPath[MAX_PATH] = {0};   
	::GetSystemDirectory( szPath,   MAX_PATH);
	strMidBkDir = szPath;
	size_t nPos = strMidBkDir.rfind("\\");
	if ( nPos != std::string::npos )
	{
		strMidBkDir = strMidBkDir.substr( 0, nPos );
	}
	strMidBkDir += "\\bkmid.jpg";
}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::~CUmcWebProjCtrl - Destructor

CUmcWebProjCtrl::~CUmcWebProjCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::OnDraw - Drawing function

void CUmcWebProjCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
}

/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::DoPropExchange - Persistence support

void CUmcWebProjCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::OnResetState - Reset control to default state

void CUmcWebProjCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl::AboutBox - Display an "About" box to the user

void CUmcWebProjCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_UMCWEBPROJ);
	dlgAbout.DoModal();
}

BOOL CUmcWebProjCtrl::DeleteUrlCache()
{
    BOOL bRet = FALSE;
	HANDLE hEntry;
    LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
    DWORD dwEntrySize;
	
	dwEntrySize = 0;
    hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
    hEntry = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwEntrySize);
	if ( !hEntry )
	{
		if (lpCacheEntry)
		{
			SAFE_RELEASE_ARRAY(lpCacheEntry); 
		}

		return bRet;
	}
	
	do
    {
		if ( !( lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY ) )
		{
			DeleteUrlCacheEntry( lpCacheEntry->lpszSourceUrlName );
		}
		
		dwEntrySize = 0;
		FindNextUrlCacheEntry( hEntry, NULL, &dwEntrySize );

		SAFE_RELEASE_ARRAY(lpCacheEntry); 

		lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];

		bRet = TRUE;
	}
	while (FindNextUrlCacheEntry( hEntry, lpCacheEntry, &dwEntrySize ) );
	
	SAFE_RELEASE_ARRAY(lpCacheEntry); 

    return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjCtrl message handler
int CUmcWebProjCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{   
	JsRefreshOle( "showtitle", "����ͳһ�������̨" );
	JsRefreshOle( "showloginbk", strMidBkDir.c_str() );
	REG_MSG( WM_DEF_CHANGEBKCOLOR, GetSafeHwnd() );

	//��ֹ����ͬʱ����
	CString strClassName = "UmcSingleInstanceClientB3";   
    HANDLE  hMutex = NULL;
	hMutex = CreateMutex( NULL, FALSE, strClassName );
	if( GetLastError() == ERROR_ALREADY_EXISTS )
	{   
		CloseHandle(hMutex);
		ReleaseMutex(hMutex);
		m_bInitBefore = TRUE;
		return 0;
	}
	
	m_hMutex = hMutex;


	g_bNeedDraw = TRUE;
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;   

// #ifndef _DEBUG
// 	OnActivateInPlace (TRUE, NULL); // == UI-Activate the control
// #endif



	//���IE
    if (::AfxGetMainWnd() != NULL && ::IsWindow(AfxGetMainWnd()->m_hWnd))
    {
        AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
    }

// 	if ( g_bIsLoginDestory )
// 	{
// 		if ( m_pLoginDlg != NULL )
// 		{
// 			m_bInitBefore = TRUE;
// 			return 0;
// 		}
// 	}

	//����IE�����澯
	HKEY hKey;
	LONG lRet = RegOpenKeyEx( HKEY_CURRENT_USER, 
		_T("Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_LOCALMACHINE_LOCKDOWN"),
		0, KEY_ALL_ACCESS, &hKey );
	if( lRet == ERROR_SUCCESS )
	{
		DWORD dwLock = 0;
		lRet = RegSetValueEx( hKey, "iexplore.exe", 0, REG_DWORD, (LPBYTE) &dwLock, sizeof( DWORD ) );
		RegCloseKey( hKey );
	}

	//��ȡIP 
	DWORD dwIP = 0;
	CString strUrl;
    GetUrl( this, strUrl );
    if ( strUrl.Left( 7 ).CompareNoCase( _T("http://") ) == 0 )
    { 
        strUrl = strUrl.Right( strUrl.GetLength() - 7 );
        int nFind = strUrl.Find( "/" );
        if ( nFind != -1 )
        {
            strUrl = strUrl.Left( nFind );
			
			//����bug:ipβ����'.'�����
			int nLen = strUrl.GetLength();
			nFind = strUrl.ReverseFind('.');
			if ( nFind != -1 && ((nLen-1) == nFind) )
			{
				strUrl = strUrl.Left(nFind);
			}

            if ( CCallAddr::IsValidIpV4( strUrl ) )
            {
                dwIP = ntohl( inet_addr( strUrl ) ); 
            }
        }
    }

	DeleteUrlCache();

	BOOL bCon = BUSINESSIFPTR->IsConnectedUms();
	if ( bCon )
	{   
		
		BUSINESSIFPTR->DisconnectUms();
	}
	
	if ( NULL != m_pLoginDlg )
	{   
		m_pLoginDlg->DestroyWindow();
		delete m_pLoginDlg;
		m_pLoginDlg = NULL;
		
	}


	{
		m_pLoginDlg = new CLoginLogic( this );
		if ( NULL != m_pLoginDlg )
		{
			m_pLoginDlg->SetIP( dwIP );
			m_pLoginDlg->Create(IDD_DIALOG_LOGIN,this);		
			m_pLoginDlg->ShowWindow( SW_SHOW );
			//m_pLoginDlg->PostMessage( WM_SETFOCUS, 0, 0 ); //120806---ldy ȥ��Ϊ�û��ṩĬ�Ͻ���
		}
	}
	
	
	if ( NULL != g_pMainDlg )
	{ 		 
		g_pMainDlg->DestroyWindow();
		delete g_pMainDlg;
		g_pMainDlg = NULL;
		
	}

 
	{
		g_pMainDlg = new CMainLogic( this );
		if( NULL != g_pMainDlg )
		{
			g_pMainDlg->Create(IDD_DIALOG_MAIN,this);
			g_pMainDlg->ShowWindow( SW_HIDE );
		}
	}


	return 0;
}

void CUmcWebProjCtrl::OnDestroy()
{
	CSrcManage::ReleaseImage();
	CSrcManage::ReleaseFont();

	COleControl::OnDestroy();

	if ( m_bInitBefore )
	{
		return;
	}

	
	if ( NULL != m_hMutex )
	{	 
		BOOL bRe =	 CloseHandle (m_hMutex);
		ReleaseMutex(m_hMutex);
		m_hMutex = NULL;	
	}

	if ( m_pLoginDlg )
	{
		if ( m_pLoginDlg->GetSafeHwnd() )
		{
			m_pLoginDlg->DestroyWindow();
		}
		delete m_pLoginDlg;
		m_pLoginDlg = NULL;
	}

	g_bIsLoginDestory = TRUE;
	
	if ( g_pMainDlg )
	{
		if ( g_pMainDlg->GetSafeHwnd() )
		{
			g_pMainDlg->DestroyWindow();
		}
		delete g_pMainDlg;
		g_pMainDlg = NULL;
	}
	
	


	COutPrint::Clean();

	DESTORYUMSSESSION
}

void MyGetClippingCoordinates(LPCRECT pPosRect, LPCRECT pClipRect,
							  LPRECT pIntersectRect, LPPOINT pOffsetPoint)
{
	int clipLeft = 0;
	int clipTop = 0;
	
	if ((pClipRect == NULL) || IsRectEmpty(pClipRect))
	{
		CopyRect(pIntersectRect, pPosRect);
	}
	else
	{
		IntersectRect(pIntersectRect, pPosRect, pClipRect);
		clipLeft = pClipRect->left;
		clipTop = pClipRect->top;
	}
	
	pOffsetPoint->x = min(0, pPosRect->left - clipLeft);
	pOffsetPoint->y = min(0, pPosRect->top - clipTop);
}

//�������IE������ʱ umc���滨����˸����  2012-7-5
BOOL CUmcWebProjCtrl::OnSetObjectRects(LPCRECT lprcPosRect, LPCRECT lprcClipRect)
{
	ASSERT(lprcPosRect != NULL);
// 	lprcPosRect = &rc1;
// 	lprcClipRect = &rc2;

	
	// Remember the position rectangle for later
	m_rcPos = *lprcPosRect;
	
	// Calculate complete rectangle including the tracker (if present)
	CRect rectPos = m_rcPos;
	if (m_bUIActive && m_pRectTracker != NULL)
	{
		// Save new clipping rectangle (for DestroyTracker)
		if (lprcClipRect != NULL)
			m_pRectTracker->m_rectClip = *lprcClipRect;
		
		// Adjust tracker rectangle to new dimensions
		CRect rectTmp = rectPos;
		rectTmp.OffsetRect(-rectTmp.left, -rectTmp.top);
		m_pRectTracker->m_rect = rectTmp;
		
		// Adjust the "true" rectangle to include handles/hatching
		UINT nHandleSize = m_pRectTracker->m_nHandleSize - 1;
		rectPos.InflateRect(nHandleSize, nHandleSize);
	}
	
	// Now clip that rectangle as appropriate
	CRect rectClip;
	
	// CHANGE - call your own copy of _GetClippingCoordinates
	MyGetClippingCoordinates(rectPos, lprcClipRect, rectClip, &m_ptOffset);
	
	// Move outer window first. then inner window
	
	if (!m_bInPlaceSiteWndless)
	{
		CWnd* pWndOuter = GetOuterWindow();
		
		//BEGIN CHANGE
		if (pWndOuter != NULL)
		{
			
			//		::MoveWindow(pWndOuter->m_hWnd, rectClip.left, rectClip.top,
			//			rectClip.Width(), rectClip.Height(), TRUE);
			
			m_rectClip.left = 0;
			m_rectClip.right = /*4*/1*BASE_SCREEN_WIDTH_INIE*CUR_SCREEN_WIDTH_PER;
			m_rectClip.top = 0;
			m_rectClip.bottom = /*4*/1*BASE_SCREEN_HEIGHT_INIE*CUR_SCREEN_HEIGHT_PER;
			
			::MoveWindow(pWndOuter->m_hWnd, rectPos.left, rectPos.top,
 				rectPos.Width(), rectPos.Height(), TRUE);
		}
		//END CHANGE	
		// 		if (pWndOuter != this)  ��ֹ��קIE������ʱumc��������β����
		// 			MoveWindow(m_ptOffset.x, m_ptOffset.y, rectPos.Width(), rectPos.Height());
	}

	return TRUE;
}
 

BOOL CUmcWebProjCtrl::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    switch (pMsg->message)
    {
    case WM_KEYDOWN:
		{
			if ( pMsg->wParam == VK_TAB )
			{
				HWND hFocus = ::GetFocus(); 

				HWND hNextFcu = ::GetNextDlgTabItem( ::GetParent(hFocus), hFocus, TRUE);

				::SetFocus(hNextFcu);
                //OspPrintf(TRUE,FALSE,"\n===  TAB:%d ==\n", hNextFcu);
				return TRUE;
				//::SendMessage( m_pLoginDlg->GetSafeHwnd(), pMsg->message, pMsg->wParam, pMsg->lParam );        
			} 
        
			if( pMsg->wParam == VK_RETURN  )
			{
				HWND hFocus = ::GetFocus( ); 
				if ( m_pLoginDlg->m_hWnd == ::GetParent(hFocus) )
				{
					m_pLoginDlg->Login();
                    //OspPrintf(TRUE,FALSE,"\n===  Enter:%d ==\n", hFocus);
				}  
			}
		}
	case WM_KEYUP://ʹedit����Ӧ�� ���¼�  2012-9-20 ����������
		{ 
			switch   (pMsg-> wParam) 
			{ 
			case   VK_UP: 
			case   VK_DOWN: 
			case   VK_LEFT: 
			case   VK_RIGHT: 
			case   VK_HOME: 
			case   VK_END: 
		//	case   VK_BACK: 
				{
					::SendMessage   (GetFocus()-> GetSafeHwnd(),   pMsg-> message,   pMsg-> wParam,   pMsg-> lParam);
					
				    return   TRUE; 
				}
				
			} 
		 
		}
		break;
    }

    return COleControl::PreTranslateMessage(pMsg);
}

int CUmcWebProjCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//    if (!m_bUIActive) // ��� childDlg �е�edit�޷�ʹ��ctrl+c ��ݼ����� 2012.9.20 ����������
//    {
//          OnActivateInPlace (TRUE, NULL); // == UI-Activate the control
          
//    }    

// 	if (::AfxGetMainWnd() != NULL && ::IsWindow(AfxGetMainWnd()->m_hWnd))
//     {
//         AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
//     }

	return COleControl::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CUmcWebProjCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if ( ::IsWindowVisible(g_pMainDlg->GetSafeHwnd()) )     //20130815 ����bug �����򾭳��ܵ�����һ��TAB������
	{
		CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER );     //Ŀǰ���Բ�����WM_DEF_HIDE_LOSEFOCUSHIDER����ֹwin7��������ʧ�ܲ�����warning�������� by ldy 2013.05.06
	}

	CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT );

	if ( m_bInitBefore )
    {
        CRect rect;
		this->GetClientRect(rect);

		CBrush brush( RGB(126,151,161) );

		JsRefreshOle("shownullbk");

        dc.FillRect( rect, &brush/*CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH))*/);
		dc.SetBkMode(TRANSPARENT);
        dc.DrawText( "��ʼ��ʧ�ܣ�umcͳһ�������̨ҳ���Ѿ�������", &rect,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE );
    }
}

//////////////////////////////////OSP��ӡ����/////////////////////////////////////////////
API void help()
{
    PrtMsg( "\n    showver:                    ��ʾ�汾�ͱ���ʱ��");
	PrtMsg( "\n    prt:                        ��ӡ���м���Ϊ3���ϵ���Ϣ");
	PrtMsg( "\n    prtlevel nLevel:            ��ӡ����ΪnLevel����Ϣ����Ϣ���� 1-3��\n \
         	1Ϊ������ߵ���Ϣ���ü������Ϣ��ϵͳ���ܲ�������Ӱ��\n \
          	2Ϊһ�㼶�����Ϣ\n \
                3Ϊ��ͼ�����Ϣ " );
	PrtMsg( "\n    stopprt:                    ֹͣ��ӡ");
	PrtMsg( "\n    prtid msgID:                ��ӡ��Ϣ����msgID����Ϣ");
    PrtMsg( "\n    prtrange beginID endID:     ��ӡ��Ϣ�ŷ�Χ�� beginID �� endID ֮�����Ϣ");
    PrtMsg( "\n    prtrecive 0 / 1:            ��ӡ���н��ܵ�����Ϣ, 0:����ӡ��1:��ӡ");
    PrtMsg( "\n    prtsend 0 / 1:              ��ӡ���з��ͳ�ȥ����Ϣ, 0:����ӡ��1:��ӡ"); 
    PrtMsg( "\n    showallconf��               ��ʾ���л�����Ϣ");
    PrtMsg( "\n    showconf wConfID:           ��ʾIDΪwConfID�Ļ�����Ϣ");
	PrtMsg( "\n    showalltpl:                 ��ʾ���л���ģ��");
	PrtMsg( "\n    showlocaladdr:           ��ʾ���б��ص�ַ��");
	PrtMsg( "\n    showglobaladdr:          ��ʾ����ȫ�ֵ�ַ��");
}

API void showver()
{   
    PrtMsg( "Umcweb version: %s ", GetUmcBuildVersion() ); 
    PrtMsg( "compile time:%s %s", __DATE__, __TIME__ );
	
}

API void prt()
{
    CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}

API void prtlevel( u8 byLevel )
{
    CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
	CPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void prtid( u32 msgID )
{
	CPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}

API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
	CPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}

// ��ʾ���л���
API void showallconf()
{
    BUILDOUTPRINTPTR->GetAllConfInfo();
}

//��ʾĳID�Ļ�����Ϣ
API void showconf( u16 wConfID )
{
    BUILDOUTPRINTPTR->GetConfInfo( wConfID );
}

// ��ʾ���л���ģ��
API void showalltpl()
{
    BUILDOUTPRINTPTR->GetAllTpl();
}

// ��ʾ���б��ص�ַ��
API void showlocaladdr()
{
    BUILDOUTPRINTPTR->GetAllLocalAddr();
}

// ��ʾ����ȫ�ֵ�ַ��
API void showglobaladdr()
{
    BUILDOUTPRINTPTR->GetAllGlobalAddr();
}

BOOL CUmcWebProjCtrl::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectRight;
	this->GetClientRect(rectRight);
	
	CBrush brush( RGB(126,151,161) );
	pDC->FillRect(rectRight, &brush/*CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH))*/);

 	return COleControl::OnEraseBkgnd(pDC);
}

BOOL CUmcWebProjCtrl::OnSetExtent(LPSIZEL lpSizeL)
{
	JsRefreshOle("refreshole");
	SetInitialSize(/*BASE_SCREEN_WIDTH*/BASE_SCREEN_WIDTH_INIE,BASE_SCREEN_HEIGHT_INIE);  

	return TRUE;
}

bool CUmcWebProjCtrl::JsRefreshOle( s8* strFun, const CString strParam )
{
 	IWebBrowser2     *browser = NULL;
 	IOleClientSite   *pClientSite = GetClientSite(); 
    HRESULT          hr = S_OK; 
    IServiceProvider *isp, *isp2 = NULL; 

    hr = pClientSite->QueryInterface( IID_IServiceProvider,
		reinterpret_cast<void**>(&isp) ); 

	hr = isp->QueryService( SID_STopLevelBrowser,
		IID_IServiceProvider,
 		reinterpret_cast<void**>(&isp2) ); 

    hr = isp->QueryService( SID_SWebBrowserApp,
		IID_IWebBrowser2,
		reinterpret_cast<void**>(&browser) );

	CComPtr<IHTMLDocument2> m_spDoc = NULL;
	if ( browser )
	{
		hr = browser->get_Document((IDispatch**)&m_spDoc);  
	}
	
	CComPtr<IDispatch> pScript = NULL; 
	if ( m_spDoc )
	{
		hr = m_spDoc->get_Script(&pScript); 
	}

	CComBSTR bstrMember(strFun); 

	DISPID dispid; 
	if ( pScript )
	{
		hr=pScript->GetIDsOfNames( IID_NULL, &bstrMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid ); 
	}

	DISPPARAMS   dispparams; 
	memset( &dispparams, 0, sizeof(dispparams) ); 
	dispparams.cArgs = 1;
	dispparams.rgvarg = new VARIANT[dispparams.cArgs];
	
	for( s32 nIndex = 0; nIndex < 1; nIndex++ ) 
	{
		//dispparams.rgvarg[nIndex].iVal = params;
		//dispparams.rgvarg[nIndex].bstrVal = strParam;
		dispparams.rgvarg[nIndex].bstrVal = strParam.AllocSysString();
		dispparams.rgvarg[nIndex].vt = VT_BSTR; 
	}

	dispparams.cNamedArgs = 0;
	EXCEPINFO excepInfo; 
	memset( &excepInfo, 0, sizeof(excepInfo) ); 

	CComVariant vaResult; 
	UINT nArgErr = (UINT)-1;
	if ( pScript )
	{
		hr = pScript->Invoke( dispid, IID_NULL, 0, DISPATCH_METHOD,
		&dispparams, &vaResult, &excepInfo, &nArgErr); 
	}

	
	if ( NULL != isp2 )
	{
		isp2->Release();
		isp2 = NULL;
	}
	
	if ( NULL != browser )
	{
		browser->Release();
		browser = NULL;
	}
	
	if ( NULL != pClientSite )
	{
		pClientSite->Release();
		pClientSite = NULL;
	}

	SAFE_RELEASE_ARRAY(dispparams.rgvarg);

	return true;
}

HRESULT CUmcWebProjCtrl::OnBkColorChange( WPARAM wparam, LPARAM lparam )
{
	if ( wparam )
	{
		JsRefreshOle("showmainbk");
	}
	else
	{
		JsRefreshOle( "showloginbk", strMidBkDir.c_str() );
	}
	
	return S_OK;
}
