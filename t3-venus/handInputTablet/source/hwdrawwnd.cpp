// hwdrawwnd.cpp: implementation of the CHWDrawWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "hwdrawwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern BOOL32 g_bKeyLogOn;

CHWDrawWnd::CHWDrawWnd():m_pNotifyWnd(NULL),
                        m_pImgeBK(NULL),
                        m_cMemDC(),
                        m_bIsCreated(FALSE)
{
   
 
 
}

CHWDrawWnd::~CHWDrawWnd()
{

}

BEGIN_MESSAGE_MAP(CHWDrawWnd, CWnd)
	//{{AFX_MSG_MAP(CBitWnd)
 	ON_WM_ERASEBKGND()
 	ON_WM_PAINT()
 	ON_WM_CTLCOLOR() 
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
 	ON_WM_LBUTTONUP()
 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HWND CHWDrawWnd::GetDrawHwnd()
{
	return this->GetSafeHwnd();
}


//设置需要通知的窗口
void CHWDrawWnd::SetNofifyWnd( CWnd* pNoitfyWnd ) 
{
    TRACE("\n[CHWDrawWnd::SetNofifyWnd] hwnd = %d\n",pNoitfyWnd);
    m_pNotifyWnd = pNoitfyWnd;
}

void CHWDrawWnd::OnPaint() 
{
 	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here 
   
	// Do not call CDialog::OnPaint() for painting messages
}

void CHWDrawWnd::ReDrawUI()
{
    
    if ( !m_pImgeBK   )
    {
        return;
    }

  
    CRect rc;
    GetClientRect(&rc);
   

    //矫正高度  保持与父窗口一致
    CWnd*  prnt = this->GetParent();
    CRect pnRc;
    if ( NULL != prnt )
    {   
        
        prnt->GetWindowRect( &pnRc );
        if ( pnRc.Height() != rc.Height() )
        {
            rc.bottom = pnRc.bottom - pnRc.top ;
            
            SetWindowPos( &wndTopMost, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE );

            TRACE("\n[CHWDrawWnd::ReDrawUI] SetWindowPos height=%d\n",rc.Height() ); 
        }
        
    } 

    CDC *pDc = this->GetDC();
    if ( pDc == NULL )
    {
        return ;
        
    }
   
    
    
    Graphics graph( m_cMemDC.GetSafeHdc()  );
    graph.SetSmoothingMode( SmoothingModeHighQuality );

  
    CString strImg =   GetModulePath();
    strImg += "src//";   
    Image *pImg = CSrcManage::GetImage( strImg + "handinputBoard//handinputBoardBkg.png" );

    Bitmap bitmap( pnRc.Width(),pnRc.Height() );
	Graphics *pGrpTemp = Graphics::FromImage( &bitmap );
    pGrpTemp->DrawImage( pImg,0, 0,pnRc.Width(),pnRc.Height()); 
   

    graph.DrawImage( &bitmap,0, 0, m_posImg.x,  m_posImg.y,rc.Width(), rc.Height(),UnitPixel ); 

 //   graph.DrawImage( m_pImgeBK,0, 0,  rc.Width() , rc.Height() ); 


   pDc->BitBlt( 0, 0,  rc.Width() ,  rc.Height()  ,  &m_cMemDC ,0, 0 , SRCCOPY );

    
    ReleaseDC(pDc); //GetDC---releaseDC ;createDC-----deleteDC  2012-2-13 by yjj

 
    
}

BOOL CHWDrawWnd::Init()
{
// 	LONG  style = ::GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE);
// 	::SetWindowLong( GetSafeHwnd(),GWL_EXSTYLE,style |WS_EX_TOOLWINDOW |WS_EX_NOACTIVATE );  

    if ( m_bIsCreated  )
    {
        return FALSE;
    }


    if ( m_pImgeBK == NULL )
    {
        return FALSE;
    }
	
	CRect cRect;
	GetWindowRect( &cRect );
	
// 	if ( cRect.Width() != m_pImgeBK->GetWidth()
// 		|| cRect.Height() != m_pImgeBK->GetHeight() )
//     { 
//         SetWindowPos( &wndTopMost, 0, 0, m_pImgeBK->GetWidth(), m_pImgeBK->GetHeight(), SWP_NOMOVE );
//     }

    SetWindowPos( &wndTopMost, 0, 0, cRect.Width(), cRect.Height(), SWP_NOMOVE );
// 	//去除圆角
// 	CRgn cDlgRgn;
// 	cDlgRgn.CreateRoundRectRgn( 1, 1, cRect.Width(), cRect.Height(), 6, 6);
// 
// 	SetWindowRgn( cDlgRgn, TRUE );

	if ( FALSE == m_bIsCreated )
	{
		m_bIsCreated = TRUE;
		CDC* pDC = GetDC();
		m_cMemDC.CreateCompatibleDC( pDC );		
		m_cBitmap.CreateCompatibleBitmap( pDC, cRect.Width(), cRect.Height() );		
		m_cMemDC.SelectObject( m_cBitmap );
		ReleaseDC( pDC );
	}
 	
	return TRUE; 
}

BOOL CHWDrawWnd::Create(UINT wStyle, CWnd * pParentWnd, UINT nID)
{
    LPCTSTR lpWndName = NULL;
    lpWndName = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
        AfxGetApp()->LoadStandardCursor(IDC_ARROW),
         (HBRUSH)GetStockObject(NULL_BRUSH)  , NULL );
    if( lpWndName == NULL )
        return FALSE;
    //
    // 2.0 Create the window directly...
    //wStyle |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CWnd::Create(lpWndName, NULL, wStyle , CRect(0, 0, 0, 0), pParentWnd, nID);
   // return CWnd::CreateEx(0 , lpWndName, NULL, wStyle , CRect(0, 0, 0, 0), pParentWnd, nID);
}


HBRUSH CHWDrawWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{   
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

// TODO: Change any attributes of the DC here
    
// TODO: Return a different brush if the default is not desired
	return  hbr = NULL;
}

BOOL CHWDrawWnd::OnEraseBkgnd(CDC* pDC) 
{   
  	//return TRUE; //实现无闪烁
    ReDrawUI();
	return CWnd::OnEraseBkgnd(pDC);
}


void CHWDrawWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
 
}

void CHWDrawWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
 
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CHWDrawWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if ( m_pNotifyWnd )
    {
        
        m_pNotifyWnd->PostMessage( WM_HAND_END_WRITE_NOTIFY );
        
      //  TRACE("\n[CHWDrawWnd::OnLButtonDown]SendMessage( WM_HAND_WRITING_NOTIFY ),%d \n",m_pNotifyWnd);
    }
 
	CWnd::OnLButtonUp(nFlags, point);
}


HRESULT CHWDrawWnd::OnHwDrawNotify( WPARAM wparam , LPARAM lparam )
{
    
    
    return S_OK;
    
}
