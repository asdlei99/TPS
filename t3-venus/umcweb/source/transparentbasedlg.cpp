// TransparentBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UmcWebProj.h"
#include "TransparentBaseDlg.h"
//#include "Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg dialog

PFN_SetLayeredWindowAttributes CTransparentBaseDlg::m_s_pfnSetLayeredWindowAttributes = NULL;
PFN_UpdateLayeredWindow CTransparentBaseDlg::m_s_pfnUpdateLayeredWindow = NULL;

CTransparentBaseDlg::CTransparentBaseDlg(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CTransparentBaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_dwBkResourceID = 0;
    m_pImageBK = NULL;
    m_bTransparentWithoutBK = FALSE;
    m_bReadyToRedrawUI = FALSE;
    m_bRedrawUIImediately = FALSE;
	m_byteSourceConstantAlpha = 255;
	m_bAjustSize = FALSE;
    m_bScale = FALSE;
     m_bAutoHide = FALSE;
	 
	m_pImgLeft = NULL;
	m_pImgMiddle = NULL;
    m_pImgRight = NULL;

    m_hBindWnd = 0;
	m_hDcMem = NULL;
	m_hBtMap = NULL;
}


void CTransparentBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentBaseDlg)
	//}}AFX_DATA_MAP
}

CTransparentBaseDlg::~CTransparentBaseDlg()
{
// 	if ( m_pImageBK != NULL )
// 	{
// 		delete m_pImageBK;
// 	}

	if ( NULL != m_hDcMem )
	{
		::DeleteDC ( m_hDcMem ); 
	}
	
	if ( NULL != m_hBtMap )
	{
		::DeleteObject( m_hBtMap )  ; 
	}
}

BEGIN_MESSAGE_MAP(CTransparentBaseDlg, CDialog)
	//{{AFX_MSG_MAP(CTransparentBaseDlg)
    ON_WM_TIMER()
    ON_WM_SHOWWINDOW()
    ON_WM_ERASEBKGND()
    ON_WM_ACTIVATE()
    ON_WM_LBUTTONDOWN()    
    ON_WM_CTLCOLOR()
	ON_WM_WINDOWPOSCHANGING()
    ON_WM_SIZE()
	//ON_WM_PAINT()
    //}}AFX_MSG_MAP
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
	ON_MESSAGE( WM_BIND_WND, OnBindWnd )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentBaseDlg message handlers

BOOL CTransparentBaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    HMODULE hUser32Dll = ::GetModuleHandle( _T("user32.dll") );
    ASSERT(hUser32Dll);

    if( NULL == m_s_pfnSetLayeredWindowAttributes )
    {
        m_s_pfnSetLayeredWindowAttributes = (PFN_SetLayeredWindowAttributes)::GetProcAddress( hUser32Dll, "SetLayeredWindowAttributes" );
        ASSERT(m_s_pfnSetLayeredWindowAttributes);
    }

    if( NULL == m_s_pfnUpdateLayeredWindow )
    {
        m_s_pfnUpdateLayeredWindow = (PFN_UpdateLayeredWindow)::GetProcAddress( hUser32Dll, "UpdateLayeredWindow" );
        ASSERT(m_s_pfnUpdateLayeredWindow);
	}

	//2012-7-10 by yjj
	if ( hUser32Dll )
	{
		FreeLibrary( hUser32Dll );
	}

	InitMemDC();

	::SetWindowLong( m_hWnd, GWL_EXSTYLE, GetWindowLong( m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED );
    if ( 0 != m_dwBkResourceID || TRUE == m_bTransparentWithoutBK )
    {
        if ( 0 != m_dwBkResourceID )
        {
            m_pImageBK = CSrcManage::GetImage( m_dwBkResourceID, "PNG" );
        }

        RedrawUI();
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransparentBaseDlg::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == 1 )
	{
		m_bReadyToRedrawUI = FALSE;
		KillTimer( 1 );
		
		RedrawUI();
	}

    CDialog::OnTimer( nIDEvent );
}

BOOL CTransparentBaseDlg::OnEraseBkgnd(CDC* pDC) 
{
    PostMessage( WM_REDRAW_UI, NULL, NULL );

    return CDialog::OnEraseBkgnd(pDC);
}

LRESULT CTransparentBaseDlg::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    if ( 0 == m_dwBkResourceID && FALSE == m_bTransparentWithoutBK ||  g_bNeedDraw == FALSE  )
    {
        return S_FALSE;
    }

//2011-9-16 隐藏的时候也绘制，防止再次显示的时候闪烁出原界面
//     if ( IsWindowVisible() == FALSE )
//     {
//         return S_FALSE;
//     }


    if ( TRUE == m_bRedrawUIImediately )
    {
        RedrawUI();

        return S_OK;
    }

    // 控制刷新，提高效率
    if ( TRUE == m_bReadyToRedrawUI )
    {
     //   TRACE( "[CTransparentBaseDlg::OnRedrawUI] m_bReadyToRedrawUI = TRUE\n" );

        return S_OK;
    }

    m_bReadyToRedrawUI = TRUE;
    SetTimer( 1, 20, NULL );

    return S_OK;    
}

void CTransparentBaseDlg::RedrawUI()
{
    if ( 0 == m_dwBkResourceID && FALSE == m_bTransparentWithoutBK )
    {
        return;
    }

    RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin;
  
    szWin.cx = rc.right - rc.left;
    szWin.cy = rc.bottom - rc.top;
     

    BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, m_byteSourceConstantAlpha, AC_SRC_ALPHA };

    HDC hDC = ::GetDC(NULL);
    
    if( NULL != m_hDcMem )   
    {   
         
        Graphics graph( m_hDcMem );
        graph.Clear( Color( 0, 0, 0, 0 ) );

        graph.SetSmoothingMode( SmoothingModeHighQuality );
        
       
        //解决隐藏界面后更改显示方案 再次显示出来会闪烁的问题
        if ( IsWindowVisible() )
        { 
            if ( NULL != m_pImageBK )
            {
                graph.DrawImage( m_pImageBK, 0, 0, szWin.cx, szWin.cy );
                // PrtMsg("\n[CTransparentBaseDlg::RedrawUI]graph.DrawImage:width:%d  height:%d\n",szWin.cx, szWin.cy  );
            }
            
            
            // 绘制所有子窗口
            DrawChildWnd( &graph, GetSafeHwnd() );
        }
        

        m_s_pfnUpdateLayeredWindow( m_hWnd,
                                    hDC,
                                    &ptWinPos,
                                    &szWin,
                                    m_hDcMem,
                                    &ptSrc,
                                    0,
                                    &stBlend,
                                    ULW_ALPHA
                                   );

         
    } 
   
    //::DeleteDC( hDC ); 2012-7-2 by yjj
    ::ReleaseDC( GetSafeHwnd(), hDC );
}

void CTransparentBaseDlg::DrawChildWnd( Graphics *pGraphics, HWND hParentWnd )
{
    HWND hwndChild = ::GetWindow( hParentWnd, GW_CHILD );

    while( hwndChild != NULL )
    {   
		//如果该窗口未显示，则其子窗口也不应当显示，因而该窗口和其子窗口都不再进行绘制 2012.8.30 by yjj 
		if ( ::IsWindowVisible(hwndChild) )  
		{
			// 通知子窗口进行绘制
			::SendMessage( hwndChild, WM_REDRAW_UI, (WPARAM)pGraphics, (LPARAM)m_hWnd );
			
            DrawChildWnd( pGraphics, hwndChild );
		}
        
// #ifdef _DEBUG
//         CString strWindowText;
//         char abyText[128] = { 0 };
//         ::GetWindowText( hwndChild, abyText, 128 );
//         strWindowText = abyText;
//         TRACE( strWindowText );
// #endif // _DEBUG

        hwndChild = ::GetWindow( hwndChild, GW_HWNDNEXT );
    }
}

void CTransparentBaseDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if ( m_hBindWnd != 0 && !bShow )
    {
        // 如果有绑定的窗口，则通知绑定触发绑定窗口 
        CPoint   mousepos; 
        ::GetCursorPos(&mousepos); 
        CPoint   CurPos(mousepos);
		
        ::ScreenToClient(m_hBindWnd, &mousepos );
		
        CRect rect;
        ::GetClientRect(m_hBindWnd, &rect );
		//窗口隐藏，如不点在窗口上或绑定窗口已隐藏，都通知绑定窗口
        if (  !rect.PtInRect( mousepos ) ||!::IsWindowVisible( m_hBindWnd )  )
        {     
            ::PostMessage(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 );  
        }   
    }

    CDialog::OnShowWindow(bShow, nStatus);
    
  
    // TODO: Add your message handler code here
   // if ( TRUE == bShow )  2011-9-16 隐藏的时候也绘制，防止再次显示的时候闪烁出原界面
    {
        PostMessage( WM_REDRAW_UI, NULL, NULL );
    }
}

s32 CTransparentBaseDlg::GetWindowWidth()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetWidth();
}

s32 CTransparentBaseDlg::GetWindowHeight()
{
	if ( m_pImageBK == NULL )
	{
		return 0;
	}
	return m_pImageBK->GetHeight();
}


HBRUSH CTransparentBaseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor );
    
    // TODO: Change any attributes of the DC here
	if ( pDC != NULL )
	{ 
		pDC->DeleteDC();
		pDC = NULL;
	}
    
    // TODO: Return a different brush if the default is not desired
	return   NULL;//(HBRUSH)GetStockObject(NULL_BRUSH);
}

void CTransparentBaseDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{    
    if ( m_bAutoHide && nState == WA_INACTIVE )
    {  
        this->PostMessage(WM_SHOWWINDOW,FALSE,SW_OTHERUNZOOM );
		
        //隐藏后，焦点还给Owner窗口 
        HWND hOwner = this->m_hWndOwner;
        pWndOther  = FromHandle(hOwner);
        if (  pWndOther != NULL  )
        {
			
            pWndOther->PostMessage( WM_SETFOCUS, 0, 0 );
        }
    }
	
    CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	
	
}




//解决隐藏后再显示界面刷新慢的问题
void CTransparentBaseDlg::OnWindowPosChanging(WINDOWPOS   FAR*   lpwndpos) 
{   
	
    if (  IsWindowVisible()   )
    {
        PostMessage( WM_REDRAW_UI, 0, 0 );
    }
    
    CDialog::OnWindowPosChanging(lpwndpos); 
} 

void CTransparentBaseDlg::SetBindWnd( HWND hdl )
{
	//绑定窗口改变，通知原绑定窗口不选中
	if ( m_hBindWnd != NULL && m_hBindWnd != hdl )
	{
		::SendMessage(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 ); 
	}
	
    m_hBindWnd = hdl;
}


LRESULT CTransparentBaseDlg::OnBindWnd( WPARAM wParam, LPARAM lParam )
{
	HWND bindWnd = (HWND)wParam;
	if ( m_hBindWnd != NULL && m_hBindWnd != bindWnd )
	{
		::SendMessage(m_hBindWnd, WM_BIND_WND_HIDE, 0, 0 ); 
	}
    
    m_hBindWnd = bindWnd;
    return S_OK;
}
void CTransparentBaseDlg::InitMemDC()
{  
	if ( NULL != m_hDcMem )
	{
		::DeleteDC ( m_hDcMem ); 
	}

	
	if ( NULL != m_hBtMap )
	{
		::DeleteObject( m_hBtMap )  ; 
	} 

	
	RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
	SIZE szWin;
	szWin.cx = rc.right - rc.left;
	szWin.cy = rc.bottom - rc.top ; 

	HDC hDc = ::GetDC( GetSafeHwnd() );
    m_hDcMem =  CreateCompatibleDC(hDc);
	
    BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
    int nBytesPerLine = ((szWin.cx * 32 + 31) & (~31)) >> 3;
    stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
    stBmpInfoHeader.biWidth = szWin.cx;   
    stBmpInfoHeader.biHeight = szWin.cy;   
    stBmpInfoHeader.biPlanes = 1;
    stBmpInfoHeader.biBitCount = 32;   
    stBmpInfoHeader.biCompression = BI_RGB;   
    stBmpInfoHeader.biClrUsed = 0;   
    stBmpInfoHeader.biSizeImage = nBytesPerLine * szWin.cy;	
	
    PUINT32 pvBits = NULL;   
    m_hBtMap = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);
	
	if (m_hBtMap == NULL  )
	{
	  DWORD err = GetLastError();
	  int i = 0;
	}

	if ( m_hBtMap == NULL )
	{   
		if ( NULL != m_hDcMem )
		{
			::DeleteDC ( m_hDcMem ); 
		}
		return;
	}

    ASSERT(m_hBtMap != NULL);
    if(m_hBtMap)   
    {   
       ::SelectObject( m_hDcMem, m_hBtMap); 
	}

	::ReleaseDC( GetSafeHwnd(), hDc );
    
    int i =0;
}


void CTransparentBaseDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	InitMemDC();
	// TODO: Add your message handler code here
	
}
