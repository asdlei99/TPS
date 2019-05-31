// inputMgr.cpp: implementation of the CInputMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "inputMgr.h" 
#include "handinputtablet.h"
 
#include "softkeyboarddlg.h"
#include "HWRecgBoard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInputMgr * CInputMgr::m_pThis = NULL;
 







CInputMgr::CInputMgr():  
            m_emInputType(  emInputKeyBoard ),
            m_hTagWnd(0),
            m_cMemDC(),
            m_cBitmap(),
            m_hwFocus(0)           
{ 
    BOOL re = Create(  WS_EX_TOPMOST , "HandwriteBoard", 0, NULL,  WS_POPUP  , 0, NULL );

    LONG  style = ::GetWindowLong(GetSafeHwnd(),GWL_STYLE);
    ::SetWindowLong( GetSafeHwnd(),GWL_STYLE,style |WS_CLIPCHILDREN );  
    if ( !re )
    {
      AfxMessageBox( "创建手写板失败 " ) ;
      return ;
    }

    m_szOrig.cx = 778;
    m_szOrig.cy = 289;

   // ResolutionAdp( m_szOrig.cx, m_szOrig.cy );

    SetWindowPos(NULL, 0, 0, m_szOrig.cx, m_szOrig.cy, SWP_NOACTIVATE|SWP_NOMOVE);

    //矫正位置9
    AdjustPos( FALSE ); 

    //去除圆角
//     CRgn cDlgRgn;
//     s32 nRound  =  6;
//     cDlgRgn.CreateRoundRectRgn(  4 , 3, m_szOrig.cx - 3 , m_szOrig.cy, nRound, nRound);
//     SetWindowRgn( cDlgRgn, FALSE ); 

    m_nTimeInterval = 1*1000;   
     
}


CInputMgr::~CInputMgr()
{

}


// BOOL CInputMgr::OnInitDialog() 
// {
//     CTransparentBaseDlg::OnInitDialog();
//     
//     //窗口分层
//     HMODULE hUser32Dll = ::GetModuleHandle( _T("user32.dll") );
//     ASSERT(hUser32Dll);
//     
//     m_s_pfnUpdateLayeredWindow = (PFN_UpdateLayeredWindow)::GetProcAddress( hUser32Dll, "UpdateLayeredWindow" );
//     
//     DWORD dwStyle = GetWindowLong(m_hWnd,GWL_EXSTYLE);
//     if( (dwStyle&0x80000) != 0x80000 )
//     {
//         SetWindowLong( m_hWnd, GWL_EXSTYLE, dwStyle^0x80000 );
//     }
//     
//     //   ::SetWindowLong( m_hWnd, GWL_EXSTYLE, GetWindowLong( m_hWnd, GWL_EXSTYLE)| 0x80000 );
//     
//     int nWndWith = 778;  //m_pImgeBK->GetWidth();
//     int nWndHeigh = 337; //m_pImgeBK->GetHeight();
//     SetWindowPos(NULL,0,0,nWndWith,nWndHeigh,SWP_NOACTIVATE|SWP_NOMOVE);
//     //矫正位置
//     AdjustPos( FALSE );
//     
//     RedrawUI();
//     //SendMessage( WM_REDRAW_UI );
//   
//     return TRUE;  // return TRUE unless you set the focus to a control
//     // EXCEPTION: OCX Property Pages should return FALSE
// }

BEGIN_MESSAGE_MAP(CInputMgr, CWnd)
//{{AFX_MSG_MAP(CWnd)

ON_WM_PAINT()
ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_WM_GETMINMAXINFO()
 
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()

ON_WM_SHOWWINDOW() 

ON_WM_SETCURSOR()
ON_WM_KILLFOCUS() 

ON_WM_DESTROY()
 
ON_WM_CAPTURECHANGED()

ON_WM_TIMER()
ON_MESSAGE( WM_HAND_BEGIN_WRITE_NOTIFY, OnHwDrawBeginNotify )
ON_MESSAGE( WM_HAND_END_WRITE_NOTIFY, OnHwDrawNotify )
 
 
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
 
 
BOOL CInputMgr::Create( DWORD dwExStyle, CString strName, CRect rcWnd, CWnd* pWnd,DWORD dStyle,UINT nID, CCreateContext* pContext )
{
    CString szClassName = AfxRegisterWndClass( 0 ,0,(HBRUSH)::GetStockObject( NULL_BRUSH ) );
    
    CheckParam( dwExStyle, &pWnd, dStyle, nID );
    BOOL bRet = CWnd::CreateEx(dwExStyle, szClassName, strName, dStyle, rcWnd, pWnd, nID, pContext);
    
    if (!bRet)
        return FALSE;

    
    return bRet;
    
}

void CInputMgr::CheckParam( DWORD& dwExStyle, CWnd** pWnd,DWORD& dStyle,UINT& nID )
{
    // 如果是想做为一个非子窗口的窗口，ID不能有值，因为在CreateEx里面的参数是作为child的ID
    if ( pWnd == NULL )
    {
        nID = 0;
        if ( dStyle & WS_CHILD )
        {
            dStyle &= ~WS_CHILD;
        }		
    }
    
    if ( !(dStyle & WS_CHILD) )
    {
        nID = 0;
    }
    if ( dStyle & WS_POPUP )
    {
        *pWnd = NULL;
    }
    
}


CInputMgr* CInputMgr::GetSingleTon()
{
    if ( m_pThis == NULL )
    {
        m_pThis = new CInputMgr(); 
      /*  m_pThis->Create( IDD_DLG );*/
        
    }

    return m_pThis;
}



  
 

void CInputMgr::SetInputType( EmInputType emInputType  )
{   
  
    if ( m_emInputType != emInputType )
    {   
        m_emInputType = emInputType;  
    }  
    
    if ( m_emInputType == emInputHandWrite )
    {
        CHWRecgBoard::GetSingleTon()->OnShowBoard();
    }
  
}


 

void CInputMgr::RedrawUI( CDC *pDC /*= BULL*/ )
{ 
    BOOL32 bRelease = FALSE;

    if ( NULL == pDC )
    {
        pDC =  GetDC(  );
        bRelease = TRUE;
    } 

    RECT rc;
    ::GetWindowRect( m_hWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin;
    szWin.cx =  rc.right - rc.left;
    szWin.cy = rc.bottom - rc.top;

    if ( m_cMemDC.GetSafeHdc() == NULL )
    {
        m_cMemDC.CreateCompatibleDC( pDC );	
        m_cBitmap.CreateCompatibleBitmap( pDC, szWin.cx, szWin.cy );	
        m_cMemDC.SelectObject( m_cBitmap );
    }


    Graphics graph( m_cMemDC.GetSafeHdc() );

    graph.SetSmoothingMode( SmoothingModeHighQuality ); 

    
   
    //画软键盘或者手写板
    if ( m_emInputType == emInputKeyBoard )
    {   
        
        CSoftKeyboardDlg::GetSingleTon()->RedrawUI( (WPARAM)&graph, (LPARAM)m_hWnd);
    }
    else
    {   
        
        CHWRecgBoard::GetSingleTon()->RedrawUI( (WPARAM)&graph, (LPARAM)m_hWnd );
    }



    pDC->BitBlt( 0, 0, szWin.cx, szWin.cy, &m_cMemDC, 0, 0, SRCCOPY );

    if ( bRelease )
    {
        ReleaseDC( pDC );
    }  
   
    
}
 
 
void CInputMgr::OnPaint() 
{
    CPaintDC dc(this); // device context for painting 
  
}

HBRUSH CInputMgr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
    
    // TODO: Change any attributes of the DC here
    
    // TODO: Return a different brush if the default is not desired
   return   (HBRUSH)GetStockObject(NULL_BRUSH);
}

BOOL CInputMgr::OnEraseBkgnd(CDC* pDC) 
{
    RedrawUI();
    return CWnd::OnEraseBkgnd(pDC);
}

void CInputMgr::OnCaptureChanged( CWnd *pWnd )
{
    CWnd::OnCaptureChanged( pWnd );
    if ( IsWindowVisible() )
    {
        //AfxOutputDebugString( "\n [CInputMgr::OnCaptureChanged] settimer \n" );
        SetCapture();
    }
 
   
}
BOOL CInputMgr::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{ 
    if ( GetCapture() != this )
    {  
        ReleaseCapture();
        SetCapture();
    }
   
    
    return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CInputMgr::OnLButtonDown(UINT nFlags, CPoint point)
{   
    if ( !this->IsWindowVisible() )
    {
        return;
    }  
  
    
    CRect cRect;
    GetClientRect( &cRect );
    if ( cRect.PtInRect( point ) == FALSE  )
    { 
        this->ClientToScreen( &point ); 
        
        HWND hwPt = ::WindowFromPoint( point ); 
    
        ::ScreenToClient(hwPt,&point);
        ::PostMessage( hwPt, WM_LBUTTONDOWN, nFlags, MAKELPARAM( point.x, point.y ) );
        
        return;
    } 
    
    
    if ( m_emInputType == emInputKeyBoard )
    {
        CSoftKeyboardDlg::GetSingleTon()->OnLButtonDown(nFlags,point);
    }
    else
    {
        
        CHWRecgBoard::GetSingleTon()->OnLButtonDown( nFlags, point );
        
    }

   
}

void CInputMgr::OnLButtonUp(UINT nFlags, CPoint point)
{   
    if ( !this->IsWindowVisible() )
    {
        return;
    } 

    if ( m_emInputType == emInputHandWrite )
    {
        CHWRecgBoard::GetSingleTon()->OnLButtonUp(nFlags,point);
    }

    CRect cRect;
    GetClientRect( &cRect );
    if ( cRect.PtInRect( point ) == FALSE  )
    { 
        this->ClientToScreen( &point ); 
        
        HWND hwPt = ::WindowFromPoint( point ); 
        
        ::ScreenToClient(hwPt,&point);
        ::PostMessage( hwPt, WM_LBUTTONUP, nFlags, MAKELPARAM( point.x, point.y ) );
        
        return;
    } 

    if ( m_emInputType == emInputKeyBoard ) 
    {
        CSoftKeyboardDlg::GetSingleTon()->OnLButtonUp( nFlags, point );
    }
    
    
    RedrawUI();
}

void CInputMgr::OnMouseMove(UINT nFlags, CPoint point) 
{

    //2012-2-14 解决软键盘弹出后不可以多选编辑框中文字的问题 yjj
    if ( !this->IsWindowVisible() )
    {
        return;
    }  
    
    
	//鼠标未落在当前窗口内
    CRect cRect;
    GetClientRect( &cRect );
    if ( cRect.PtInRect( point ) == FALSE  )
    { 
        this->ClientToScreen( &point ); 
        
        HWND hwPt = ::WindowFromPoint( point ); 
        
        ::ScreenToClient(hwPt,&point);
        ::PostMessage( hwPt, WM_MOUSEMOVE, nFlags, MAKELPARAM( point.x, point.y ) );
        return;
        
    } 

	//支持滑动候选词  2012.7.18 by yjj
    if ( m_emInputType == emInputHandWrite )
    {
        CHWRecgBoard::GetSingleTon()->OnMouseMove(nFlags,point);
    }

    //  	if( TRUE == m_bHitCaption  )
    // 	{ 	
    // 		CPoint   ptCur; 
    // 		GetCursorPos(&ptCur); 
    // 		ptCur.x-=m_ptOffset.x; 
    // 		ptCur.y-=m_ptOffset.y; 
    // 		SetWindowPos(NULL,ptCur.x,ptCur.y,NULL,NULL,SWP_NOZORDER|SWP_NOSIZE); 
    // 	 
    // 	} 
    // 	else
    // 	{
    // 		CRect cRect;
    // 		GetClientRect( &cRect );
    // 		if ( cRect.PtInRect( point ) == FALSE )
    // 		{
    // 			if ( m_bCapture == TRUE )
    // 			{
    // 				m_bCapture = FALSE;
    // 				
    // 			 	ReleaseCapture();
    // 			}			
    // 			return;
    // 		}
    // 	}
     CWnd::OnMouseMove(nFlags, point);
}


void CInputMgr::OnDestroy() 
{
    CWnd::OnDestroy(); 
    
}

 

void CInputMgr::OnKillFocus(CWnd* pNewWnd)
{ 
   HideBoard( );
   //AfxOutputDebugString("\n[CInputMgr::OnKillFocus]hide board \n");
}

BOOL CInputMgr::PreTranslateMessage(MSG* pMsg) 
{
    HWND wnd = ::GetForegroundWindow();
    if(IsWindow(wnd))
    {
        if(wnd != this->m_hWnd)
        {
            if(m_hwFocus != wnd)
            {
                if(IsWindow(m_hwFocus))
                {
                    AttachThreadInput(
                        GetWindowThreadProcessId(m_hWnd,NULL),
                        GetWindowThreadProcessId(m_hwFocus,NULL),
                        FALSE);
                }
                
                m_hwFocus = wnd;
                AttachThreadInput(
                    GetWindowThreadProcessId(m_hWnd,NULL),
                    GetWindowThreadProcessId(m_hwFocus,NULL),
                    TRUE);
            }
        }
    }
    return CWnd::PreTranslateMessage(pMsg) ;
}

void CInputMgr::ReleaseFocus() 
{  
    ::SetFocus(  m_hTagWnd);
   /* ::SendMessage( m_hTagWnd, WM_KILLFOCUS ,0 ,0 );*/
    return;
    if(IsWindow(m_hwFocus))
    {
        HWND wnd = ::GetForegroundWindow();
        if(IsWindow(wnd))
        {
            if(wnd == m_hwFocus)
            {
                return;
            }
        } 
        
        ::SetForegroundWindow(m_hwFocus);
        ::SetFocus(m_hwFocus);
        //::SetActiveWindow( gFocus );
        
    }

}

// void CSoftKeyboardDlg::OnExit() 
// {
// 	POSITION pos = cKeys.GetHeadPosition();
// 	while(pos)
// 	{
// 		delete cKeys.GetNext(pos);
// 	}
// 
// 	int state = DescribeKeyState();
// 	if(state & 0x01) keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
// 	if(state & 0x02) keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
// 	if(state & 0x04) keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
//  
//     HideKeyBoard();
//  	CDialog::OnOK();
// }

//矫正键盘位置
void CInputMgr::AdjustPos( BOOL32  bShow /*= TRUE*/ )
{  
    
    int nScreenWith=  GetSystemMetrics(SM_CXSCREEN/*SM_CXFULLSCREEN*/); 
    int nScreenHeigh=  GetSystemMetrics(SM_CYSCREEN/*SM_CYFULLSCREEN*/);
    
    
     
    int nX =  ( nScreenWith - m_szOrig.cx )/2;
    int nY  =  nScreenHeigh - m_szOrig.cy  ;
    
    if ( bShow )
    {
        SetWindowPos(  &wndTopMost ,  nX  ,  nY , 0, 0,   SWP_NOACTIVATE| SWP_NOSIZE |SWP_SHOWWINDOW); 
    }
    else
    {
        SetWindowPos( &wndTopMost, nX  , nY, 0, 0,  SWP_NOACTIVATE|SWP_NOSIZE); 
    }
    
}



void CInputMgr::ResetCapture()
{
    if ( ::GetCapture() == m_hWnd )
    {
        ReleaseCapture();
    }
}

void CInputMgr::ShowBoard( HWND hTagWnd )
{  
    m_hTagWnd = hTagWnd; 
    m_hwFocus = hTagWnd; 
    
	//2013.4.27 yjj 显示键盘时已经加过timer,此处直接调用ShowBoardLater()
    /* 
	//延迟100毫秒显示，先执行完WM_LBUTTONDOWN
     SetTimer( TIMER_SHOW_BOARD, 100, NULL ); 
	 */
     ShowBoardLater(); 
}

void CInputMgr::ShowBoardLater()
{
    //解决：程序切换时会引起setcapture 失效的问题
    if( GetCapture() != this )
    { 
        ReleaseCapture();
        SetCapture();
        //  AfxOutputDebugString( "\n CInputMgr::ShowBoard setcaptuer \n" );
    } 
       
    if ( m_emInputType == emInputHandWrite )
    {   
        // CHWRecgBoard::GetSingleTon()->ClearCandWords();
        CHWRecgBoard::GetSingleTon()->ResetInput();
        CHWRecgBoard::GetSingleTon()->OnShowBoard();
        
    }
    else
    {   
        
        CSoftKeyboardDlg::GetSingleTon()->OnShowBoard( m_hTagWnd );
    } 
    
    if ( !IsWindowVisible() )
    {
        CRect rc;
        GetWindowRect( &rc );
        ::PostMessage( m_hTagWnd, WM_SOFTKEYBOARD_SHOW, rc.top, 0 );
        ReleaseFocus();
        AdjustPos();
        RedrawUI();  
    }
    
    SetTimer( TIMER_REDRAW_UI, 500, NULL );
}


void CInputMgr::HideBoard()
{   
    KillTimer( TIMER_REDRAW_UI );
    KillTimer( TIMER_AUTO_RECO );
    
    if ( !IsWindowVisible() )
    {
        return;
    }

	//2013.4.27 yjj 显示键盘时已经加过timer,此处直接调用HideBoardLater
	HideBoardLater();
	/*
    //延迟100毫秒隐藏，先执行完WM_LBUTTONDOWN
    SetTimer( TIMER_HIDE_BOARD, 100, NULL );
    */

    /*
    ::PostMessage(m_hTagWnd,WM_SOFTKEYBOARD_HIDE,0,0);
    ShowWindow( SW_HIDE ); 

    if ( m_emInputType == emInputHandWrite )
    {   
        CHWRecgBoard::GetSingleTon()->OnHideBoard(); 
    } 
	else
	{
		CSoftKeyboardDlg::GetSingleTon()->OnHideBoard();
	}
     
    ReleaseCapture(); 
    */
}

void CInputMgr::HideBoardLater()
{
    
    ShowWindow( SW_HIDE ); 
    ::PostMessage( m_hTagWnd, WM_SOFTKEYBOARD_HIDE, 0, 0 );   
    
    if ( m_emInputType == emInputHandWrite )
    {   
        CHWRecgBoard::GetSingleTon()->OnHideBoard(); 
    } 
    else
    {
        CSoftKeyboardDlg::GetSingleTon()->OnHideBoard();
    }
    
    ReleaseCapture(); 
}


HRESULT CInputMgr::OnHwDrawNotify( WPARAM wparam , LPARAM lparam )
{
    
//     CHWRecgBoard::GetSingleTon()->Recognize();
//     return S_OK;
    
    KillTimer( TIMER_AUTO_RECO ); 
    UINT i = SetTimer( TIMER_AUTO_RECO, m_nTimeInterval,NULL ); 

//    TRACE("\n[CInputMgr::OnHwDrawNotify] %d\n",i);
    return S_OK;
 
}

HRESULT CInputMgr::OnHwDrawBeginNotify( WPARAM wparam , LPARAM lparam )
{
    KillTimer( TIMER_AUTO_RECO ); 
    return S_OK;
}


void CInputMgr::OnTimer(UINT nIDEvent) 
{  
     switch( nIDEvent )
	 {
	 case TIMER_AUTO_RECO:
		 if ( IsWindowVisible() == TRUE )
		 {  
             
			 //             if ( ::IsWindowVisible( m_hTagWnd ) == FALSE )
			 //             {
			 //                 HideKeyBoard();
			 //             }
			 
			 //                 //防止被其他窗口覆盖了，定时检测是否始终处于最上方
			 //                 HWND hWnd = ::GetForegroundWindow();
			 //                 if ( hWnd != m_hWnd )
			 //             { 
			 //                 SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE );
			 //                 
			 //                 RedrawUI();
			 //                 TRACE("\n[CInputMgr::OnTimer]\n");
			 //             }
			 
			 if ( m_emInputType == emInputHandWrite )
			 {    
				 KillTimer(TIMER_AUTO_RECO );
				 CHWRecgBoard::GetSingleTon()->Recognize();
			 }
			 
        }
		 break;
	 case TIMER_REDRAW_UI:
		 if ( !::IsWindowVisible( m_hTagWnd )  )
		 {//解决 Bug00074486  使用软键盘登录后，软键盘未自动隐藏
			 s8 pName[256]={0};
			 GetClassName(  m_hTagWnd,pName,sizeof(pName) ); 
			 //             bool bCandWnd = !strcmp(pName,"QQPinyinCompWnd"); //是否是候选词窗口
			 //             TRACE("\n CursorWnd ClassName = %s \n",pName); 
			 //当窗口是候选词窗口时不隐藏，其余的隐藏情况在鼠标钩子中做处理，此处只判断目标窗口是否隐藏 by yjj 2012-2-9
			 if ( strcmp(pName,"Edit") == 0 || strcmp(pName,"RichEdit") == 0 )
			 {
                 HideBoard();
			 }  
        }
		 break;
	 case TIMER_REFRESH_CAPSLOCK:
		 if ( IsWindowVisible()  )
		 {// 2012-7-30 解决触摸引起的大写锁定状态显示错误的问题 by yjj
			 if ( m_swCurTimes < 5 && m_emInputType ==  emInputKeyBoard )
			{
				RedrawUI();
				m_swCurTimes ++;
			}
			 else
			 {
				 KillTimer( TIMER_REFRESH_CAPSLOCK );
			 } 
        }
		 break;
     case TIMER_SHOW_BOARD:
         {
             KillTimer( TIMER_SHOW_BOARD );
             ShowBoardLater();
         }
         break;
     case TIMER_HIDE_BOARD:
         {
             KillTimer( TIMER_HIDE_BOARD );
             HideBoardLater();
         }       
         break;   
	 }
  
    
    CWnd::OnTimer(nIDEvent);
}


LRESULT CInputMgr::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    if ( message == WM_TOUCH_BUTTONDOWN )
    {
//         int nX = LOWORD( lParam );
//         int nY = HIWORD( lParam );
//         //屏幕坐标点
//         OnLButtonDown(   wParam,   lParam );
        KillTimer( TIMER_AUTO_RECO );
        	
    }
   
    return CWnd::DefWindowProc(message, wParam, lParam);
}

 
 

void CInputMgr::Init()
{
    CSoftKeyboardDlg::GetSingleTon();
    CHWRecgBoard::GetSingleTon();

    //根据分辨率调整当前面板大小
   // ResolutionAdp( m_szOrig.cx, m_szOrig.cy );    无需做分辨率自适应，当前大小在HP一体机上与系统软键盘一样大小  2012-7-18 yjj
    SetWindowPos(NULL, 0, 0, m_szOrig.cx, m_szOrig.cy, SWP_NOACTIVATE|SWP_NOMOVE);

    //去除圆角
    CRgn cDlgRgn;
    s32 nRound  =  6;
    cDlgRgn.CreateRoundRectRgn(  4 , 3, m_szOrig.cx - 3 , m_szOrig.cy, nRound, nRound);
 	SetWindowRgn( cDlgRgn, FALSE ); 
}

void CInputMgr::UpdateImm()
{ 
    CSoftKeyboardDlg::GetSingleTon()->UpdateImm(); 
}

// 2012-7-30 解决触摸引起的大写锁定状态显示错误的问题 by yjj
void CInputMgr::RefreshCapsLock()
{   
	m_swCurTimes = 0;
	SetTimer( TIMER_REFRESH_CAPSLOCK,200, NULL);
}
				