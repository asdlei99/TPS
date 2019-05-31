// dlgchild.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "dlgchild.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChild dialog


CDlgChild::CDlgChild(UINT nIDDlgChild,CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CDlgChild::IDD, pParent),	
	m_cMemDC(),    
    m_cBitmap(), 
	m_IsCreateGrp( FALSE ),
	m_bShowMosaicHoriImg(FALSE),
	m_bShowMosaicVertImg(FALSE)
{
	//{{AFX_DATA_INIT(CDlgChild)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bIsSegment = FALSE;
	m_nSegmentLen = 0;
}

CDlgChild::~CDlgChild()
{
	if ( m_bShowMosaicHoriImg || m_bShowMosaicVertImg )
	{
		if ( NULL != m_pImageBK )
		{
			delete m_pImageBK;
			m_pImageBK = NULL;
		}
	}

	::DeleteDC ( m_cMemDC ); 
	::DeleteObject( m_cBitmap ); 
}

void CDlgChild::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChild)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChild, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CDlgChild)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
    ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
    ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChild message handlers

BOOL CDlgChild::OnInitDialog() 
{
	CDialog::OnInitDialog();
	LONG lStyle =  GetWindowLong( GetSafeHwnd(), GWL_STYLE );
	
	if ( !m_IsCreateGrp && ( lStyle & WS_POPUP || lStyle & WS_OVERLAPPED ) )
	{
		m_IsCreateGrp = TRUE;
	}
	
	return TRUE; 
}


LRESULT CDlgChild::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{   
 
    if ( IsWindowVisible() == FALSE || !m_bVisible  )
    {   
// 		TRACE("\n[CDlgChild::OnRedrawUI] handle=%x   IsWindowVisible() =%d , m_bVIsible=%d  and return \n",
// 			             GetSafeHwnd(),IsWindowVisible() ,m_bVisible);
        return S_FALSE;
    }
	

	// 为空的话，则是由子控件发来的，需要再向父窗口转发
    if (  wParam == 0 &&  !m_IsCreateGrp )
    {
		//TRACE("\n[CDlgChild::OnRedrawUI]handle=%x    wParam = %d, m_IsCreateGrp=%d  and sendmessage  \n",GetSafeHwnd(),wParam,m_IsCreateGrp );
		
        CWnd* pParent = GetParent();
        if ( pParent != NULL )
        {
            pParent->SendMessage( WM_REDRAW_UI, wParam, lParam );
        } 
		return S_OK;
        
    }
	 
 

    if ( TRUE == m_bRedrawUIImediately || !m_IsCreateGrp )
    {
        RedrawUI(  wParam,  lParam );
		
        return S_OK;
    }
	
    // 控制刷新，提高效率
    if ( TRUE == m_bReadyToRedrawUI )
    {
		//   TRACE( "[CTransparentBaseDlg::OnRedrawUI] m_bReadyToRedrawUI = TRUE\n" );
		
        return S_OK;
    }
	
    m_bReadyToRedrawUI = TRUE;
    SetTimer( 99, 20, NULL );
	
    return S_OK; 

}

LRESULT CDlgChild::RedrawUI( WPARAM wParam, LPARAM lParam )
{
	if ( wParam == 0  && !m_IsCreateGrp )
	{  
		//TRACE("\n[CDlgChild::RedrawUI]handle=%x    wParam = %d, m_IsCreateGrp=%d  and return  \n",GetSafeHwnd(),wParam,m_IsCreateGrp );
		return S_FALSE;
	}


	if ( !IsWindowVisible() &&  !m_bVisible  )
	{
// 		OspPrintf( TRUE,FALSE,"\n------[CDlgChild::RedrawUI]GetWindowDC=NULL  handle=%x IsWindowVisible=%d -m_bVisible=%d---\n",
// 			   GetSafeHwnd(),IsWindowVisible(),m_bVisible);

		//TRACE("\n[CDlgChild::RedrawUI] handle=%x   IsWindowVisible() =%d , m_bVIsible=%d  and return \n",
			   //          GetSafeHwnd(),IsWindowVisible() ,m_bVisible);
		return S_OK;
	} 
 

	CRect reThis;
	GetWindowRect( &reThis );
	
	
	//若当前区域不在裁剪区域内，则无需绘制//////////////////////////2012-6-8 看效果如何，若有绘制问题，可注掉该段
//  	CDC *pDC = GetDC();
//    // CDC *pDC = GetWindowDC();  
// 	if ( pDC != NULL  )
// 	{
// 		 CRect rect;
// 		 int re = pDC-> GetClipBox( &rect); 
// 		 
// 		 if ( re ==  NULLREGION ||
// 			 ( rect.PtInRect( reThis.TopLeft() ) && rect.PtInRect( CPoint( reThis.bottom, reThis.right ) )) )
// 		 {   
// 			 	OspPrintf( TRUE,FALSE,"\n[CDlgChild::OnRedrawUI]--- 不在裁剪区域，无需绘制，return ----\n");
// 		 	    ReleaseDC( pDC );
// 			    return S_OK;
// 		 }
// 		 
// 		ReleaseDC(pDC);
// 	 }
	 //////////////////////////////////////////////////////////////////////////
   


 
	if( m_pImageBK == NULL )
	{  
        if (  m_bShowMosaicHoriImg && m_pImgLeft == NULL )
        {
			m_pImgLeft = CSrcManage::GetImage( IDR_PNG_WNDCHILDLEFT, "PNG" );
			m_pImgMiddle = CSrcManage::GetImage( IDR_PNG_WNDCHILDMID, "PNG" );
			m_pImgRight = CSrcManage::GetImage( IDR_PNG_WNDCHILDRIGHT, "PNG" );
        }
		
        if (  m_bShowMosaicVertImg && m_pImgLeft == NULL )
        {
			m_pImgLeft = CSrcManage::GetImage( IDR_PNG_WNDCHILDVERTMID, "PNG" );
			m_pImgMiddle = CSrcManage::GetImage( IDR_PNG_WNDCHILDVERTMID, "PNG" );
			m_pImgRight = CSrcManage::GetImage( IDR_PNG_WNDCHILDVERTMID, "PNG" );
		}
 
		if ( m_bShowMosaicHoriImg )
		{
			m_pImageBK = CSrcManage::MosaicHoriImage( reThis,m_pImgLeft, m_pImgRight, m_pImgMiddle );
		}
		else if ( m_bShowMosaicVertImg )
		{
			m_pImageBK = CSrcManage::MosaicVertImage( reThis,m_pImgLeft, m_pImgRight, m_pImgMiddle );
		}
		else if ( m_dwBkResourceID != 0 )
		{
			
			m_pImageBK = CSrcManage::GetImage( m_dwBkResourceID, "PNG" );
		}
		
	
	}

	
	//单纯的子窗口，依靠父窗口的graphic来绘制
    Graphics *pGraphics = (Graphics*)wParam;  
    if ( NULL != pGraphics &&  0 != m_pImageBK && !m_IsCreateGrp )
    {   
		//TRACE("\n[CDlgChild::RedrawUI] handle=%x   use parent grahic \n",GetSafeHwnd() );
		
        POINT point = reThis.TopLeft(); 
		
		HWND hGraphWnd = (HWND )lParam;
        ::ScreenToClient( hGraphWnd, &point );
        
		if ( !m_bIsSegment )
		{
			pGraphics->DrawImage( m_pImageBK, point.x, point.y, reThis.Width(),  reThis.Height() );
		}
		else
		{
			pGraphics->DrawImage( m_pImageBK, point.x, point.y, m_nSegmentLen,  reThis.Height() );
			pGraphics->DrawImage( m_pImageBK, point.x +  m_nSegmentLen - 2, point.y, reThis.Width() - m_nSegmentLen,  reThis.Height() );
		}
   
		return S_OK;
        
    }

	//创建dc，并下发给所有子窗口
	if ( m_IsCreateGrp   )
	{ 
		//TRACE("\n[CDlgChild::RedrawUI] handle=%x  create grahic \n",GetSafeHwnd() );
	    CDC *pDC = GetDC();
		 
		POINT ptSrc = { 0, 0 };
		POINT ptWinPos = { reThis.left, reThis.top };
		SIZE szWin;
		szWin.cx =  reThis.right - reThis.left;
		szWin.cy = reThis.bottom - reThis.top; 
		
        
		if ( m_cMemDC.GetSafeHdc() == NULL )
		{                
			m_cMemDC.CreateCompatibleDC( pDC );	
			m_cBitmap.CreateCompatibleBitmap( pDC, szWin.cx, szWin.cy );	
			m_cMemDC.SelectObject( m_cBitmap );
		}
 	
		
		Graphics graph( m_cMemDC.GetSafeHdc() );
		
		graph.SetSmoothingMode( SmoothingModeHighQuality ); 
		
		//绘制自身
		if ( NULL != m_pImageBK )
        {   
            graph.DrawImage( m_pImageBK, 0, 0, szWin.cx, szWin.cy );
        }


		DrawChildWnd( &graph, GetSafeHwnd() );
		
		
        pDC->BitBlt( 0, 0, szWin.cx, szWin.cy, &m_cMemDC, 0, 0, SRCCOPY );
		
		ReleaseDC( pDC );
		
		return S_OK ;
	} 
    

	//TRACE("\n[CDlgChild::RedrawUI] handle=%x   not draw  Img = NULL  \n",GetSafeHwnd() );
    return  S_OK ;
}

 
void CDlgChild::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == 99 )
	{
		m_bReadyToRedrawUI = FALSE;
		KillTimer( 99 );
		
		RedrawUI( 0, 0 );
	}
	
    CDialog::OnTimer( nIDEvent );
}


void CDlgChild::OnShowWindow(BOOL bShow, UINT nStatus) 
{
    CDialog::OnShowWindow(bShow, nStatus);
    
	
    // TODO: Add your message handler code here
    if ( TRUE == bShow )
    {   
		m_bVisible = TRUE; 	 
		PostMessage( WM_REDRAW_UI, NULL, NULL );		 
	}
	else
	{
		m_bVisible = FALSE; 
	}
}