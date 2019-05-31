// HWRecgBoard.cpp: implementation of the CHWRecgBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handInputTablet.h"
#include "HWRecgBoard.h"

#include "inputMgr.h"

#include "softkeyboarddlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "nmscommon.h"
 
#include "hwcihuiif.h"

UINT g_nTimerRcg = 2000;

 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHWRecgBoard * CHWRecgBoard::m_pThis = NULL;

CHWRecgBoard::CHWRecgBoard(): 
            m_pImgeBK(NULL),
            m_vcCandWords(), 
			m_swCurrPgIndex( 0 ),
			m_swOnePgCount(8),
            m_cRecognize(),
            m_cCommonKeys(),
            m_cRecgsKeys(),
            m_rcHwDrawWnd(),
            m_pcHWDrawWnd( NULL ),
            m_bBeginWrite(FALSE),
            m_bSwitchImm(FALSE),
			m_ptLbtDown(0),     //button down 的状态
	        m_ptMouseMove(0),
			m_pPrevPgKey(NULL),
	        m_pNextPgKey(NULL)
{
    Init(); 

 
    
   // BoardRectAdp();  无需做分辨率自适应，当前大小在HP一体机上与系统软键盘一样大小  2012-7-18 yjj

   
    //初始化手写环境 
    if ( NULL == m_pcHWDrawWnd )
    {
        m_pcHWDrawWnd = new CHWDrawWnd(  );
        m_pcHWDrawWnd->Create( WS_CHILD  , CInputMgr::GetSingleTon(), 0);
 
        
     
        CString strImgPath =  GetModulePath() + "src//" ;
        Image *pBkg = CSrcManage::GetImage( strImgPath + "handinputBoard//write.png" ); 
        m_pcHWDrawWnd->SetImg( pBkg );
        m_pcHWDrawWnd->SetImgPos( m_rcHwDrawWnd.TopLeft() );
         
        
        m_pcHWDrawWnd->MoveWindow( m_rcHwDrawWnd );  
         
        m_pcHWDrawWnd->SetNofifyWnd( CInputMgr::GetSingleTon() );
        m_pcHWDrawWnd->ShowWindow( SW_HIDE );
        
        m_pcHWDrawWnd->Init();

        //初始化手写环境
        m_cRecognize.Initialize();
        m_cRecognize.SetHandWriteParm(  m_pcHWDrawWnd->GetSafeHwnd() );
        m_cRecognize.SetRecResultCnt( 20 ); //手写识别结果
    }
}



CHWRecgBoard::~CHWRecgBoard()
{
    
    POSITION pos = m_cCommonKeys.GetHeadPosition();
    while(pos)
    {
        delete m_cCommonKeys.GetNext(pos);
    }
    

    pos = m_cRecgsKeys.GetHeadPosition();
    while(pos)
    {
        delete m_cRecgsKeys.GetNext(pos);
    }


    if ( NULL != m_pcHWDrawWnd )
    {
        m_pcHWDrawWnd->DestroyWindow(); 

	}

}

CHWRecgBoard*  CHWRecgBoard::GetSingleTon()
{
    if ( m_pThis == NULL )
    {
        m_pThis = new CHWRecgBoard(); 
      
    }
    return m_pThis;
}



void CHWRecgBoard::RedrawUI(WPARAM wParam, LPARAM lparam)
{ 


    Graphics *pGraphics = (Graphics*)wParam; 
    HWND hGraphWnd = (HWND )lparam; 
    
    if ( pGraphics == NULL || hGraphWnd == 0 )
    {
        return;
    }
    
    
   RECT rc;
   
    ::GetWindowRect( hGraphWnd, &rc ); 
    

    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin; 
    
    CString strImgPath =  GetModulePath() + "src//" ;


    if ( NULL != m_pImgeBK )
    {
        szWin.cx = rc.right - rc.left ; //m_pImgeBK->GetWidth();
        szWin.cy = rc.bottom - rc.top; //m_pImgeBK->GetHeight();

        pGraphics->DrawImage( m_pImgeBK, 0, 0, szWin.cx,szWin.cy );
           
//           Image *pCommImgBkg = CSrcManage::GetImage( strImgPath + "handinputBoard//commn.png" );
// 
//           pGraphics->DrawImage( pCommImgBkg, 0, 0,  m_rcHwDrawWnd.left - 0  ,  szWin.cy  );
// 
//          
//           Image *pCandBkg = CSrcManage::GetImage( strImgPath + "handinputBoard//cand.png" );
//           
//            
//           pGraphics->DrawImage( pCandBkg,   m_rcHwDrawWnd.right , 0 ,
//                szWin.cx - m_rcHwDrawWnd.right ,  szWin.cy  );
         
    } 
    
    
     
    //绘制命令按钮
    TCommonKey * key = NULL ;
    POSITION pos = m_cCommonKeys.GetHeadPosition(); 
    while(pos)
	{
        key = m_cCommonKeys.GetNext(pos);
        CString strPath = strImgPath + key->strImgPath ; 
        Image *pImgeItem = NULL; 
        
		switch( key->emKeyState )
		{
		case emKeyStateNormal:
			pImgeItem = CSrcManage::GetImage( strPath + "//Normal.png");
			 break;
		case  emKeyStatePress:
			pImgeItem = CSrcManage::GetImage( strPath + "//Sel.png" ); 
			break;
		default:
            pImgeItem = CSrcManage::GetImage( strPath + "//Disable.png" ); 
			break;
		}
	 
        if ( NULL != pImgeItem )
        {
            pGraphics->DrawImage( pImgeItem, key->rcKey.left, key->rcKey.top, key->rcKey.Width(), key->rcKey.Height() );
        } 
    }


    //绘制候选词
    TRecgKey *regKey = NULL ;
    POSITION regPos = m_cRecgsKeys.GetHeadPosition();
    while( regPos )
    {
        regKey = m_cRecgsKeys.GetNext( regPos );
        if ( !regKey->strTxt.IsEmpty() )
        {
            DrawFont( pGraphics, regKey->rcKey, regKey->strTxt );
        }
    }
    
}


void CHWRecgBoard::OnShowBoard()
{
    if ( CSoftKeyboardDlg::GetSingleTon()->IsChineseIM() )
    {   
        CSoftKeyboardDlg::GetSingleTon()->IME_Chs2Eng();
        m_bSwitchImm = TRUE;
    }
    else
    {
        m_bSwitchImm = FALSE;
    }
    if ( m_pcHWDrawWnd != NULL)
    {
        if ( !m_pcHWDrawWnd->IsWindowVisible() )
        {
            //m_pcHWDrawWnd->CInputMgr::OnTimerShowWindow( SW_SHOW); 
            m_pcHWDrawWnd->SetWindowPos(  NULL, 0 , 0 , 0, 0, SWP_NOACTIVATE| SWP_NOSIZE |SWP_NOMOVE|SWP_SHOWWINDOW); 
        } 
        
    }
}

void CHWRecgBoard::OnHideBoard()
{
    if ( m_bSwitchImm )
    {
        CSoftKeyboardDlg::GetSingleTon()->IME_Chs2Eng();
        m_bSwitchImm = FALSE;
    }
    if ( m_pcHWDrawWnd != NULL)
    {
        if (  m_pcHWDrawWnd->IsWindowVisible() )
        {
            m_pcHWDrawWnd->ShowWindow( SW_HIDE);
        }
         
    }
    ClearCandWords();
    ResetInput();
}

void CHWRecgBoard::OnLButtonDown(UINT nFlags, CPoint point)
{   
// 	CString str;
// 	str.Format("\nCHWRecgBoard::OnLButtonDown point(%d,%d)\n",point.x,point.y);
//     AfxOutputDebugString ( str );
    m_ptLbtDown = point;
	if ( m_rcHwDrawWnd.PtInRect(point) )
    {  
        m_bBeginWrite = TRUE;
        return;
    }


	//如果正在绘制，则down到手写面板的其他 非绘制区域 也不做他操作  2012.10.9 
	if ( m_bBeginWrite )
	{
		return;
	}
    
    bool bDeal = false;
    TCommonKey * key = NULL;
    
    POSITION pos = m_cCommonKeys.GetHeadPosition();
    while(pos)
    {
        key = m_cCommonKeys.GetNext(pos);
        if(key->rcKey.PtInRect(point))
        {              

			if ( key->emKeyState != emKeyStateDisable && key->pOnClickFun != NULL )
			{   
				bDeal = true;
				
				key->emKeyState = emKeyStatePress; 
				
				(this->*(key->pOnClickFun)) ();

				CInputMgr::GetSingleTon()->RedrawUI();	
			}  
            
            break;
        }
    }
 

    if ( bDeal &&  key != NULL && key->emKeyState == emKeyStatePress  )
    {
        key->emKeyState =  emKeyStateNormal;
    } 

 

 /*   else
    { 
        //检测是否是 识别键
        TRecgKey * key = NULL;
        
        POSITION pos = m_cRecgsKeys.GetHeadPosition();
        while(pos)
        {
            key = m_cRecgsKeys.GetNext(pos);
            if(key->rcKey.PtInRect(point))
            {    
                OnSelCand( key->strTxt );  
                CInputMgr::GetSingleTon()->RedrawUI();

                ResetInput(); 

                break;
            }
        }
    }
*/

	 
}


void CHWRecgBoard::OnLButtonUp(UINT nFlags, CPoint point)
{    
// 	CString str;
// 	str.Format("\nCHWRecgBoard::OnLButtonDown point(%d,%d)\n",point.x,point.y);
//     AfxOutputDebugString ( str );

    if ( m_rcHwDrawWnd.PtInRect(point) || m_bBeginWrite )
    {
		m_pcHWDrawWnd->SendMessage( WM_LBUTTONUP, 1, 1 );
		return;
    }
	
	
	if( m_ptLbtDown == m_ptMouseMove )
	{ 
	 	//检测是否是 识别键
		TRecgKey * key = NULL;
		
		POSITION pos = m_cRecgsKeys.GetHeadPosition();
		while(pos)
		{
			key = m_cRecgsKeys.GetNext(pos);
			if(key->rcKey.PtInRect(point))
			{    
				OnSelCand( key->strTxt );  
				CInputMgr::GetSingleTon()->RedrawUI();  
				break;
			}
		}
		
	} 
	 
	ResetInput();
	if ( !m_bBeginWrite )
	{
		m_bBeginWrite = FALSE;
	} 	
	

	return; 
}

void CHWRecgBoard::OnMouseMove(UINT nFlags, CPoint point)
{ 
	m_ptMouseMove = point;    
}
 

void CHWRecgBoard::Init()
{


    CString strImg =  /*GetModuleFullPath*/GetModulePath();
    strImg += "src//"; 

    m_pImgeBK = CSrcManage::GetImage( strImg + "handinputBoard//handinputBoardBkg.png" );


    CRect rcDlg(0,0,0,0);

//     if ( m_pImgeBK )
//     {
//         rcDlg.right = 0 + m_pImgeBK->GetWidth();
//      
//         rcDlg.bottom = 0 + m_pImgeBK->GetHeight();
//     }

   
    CInputMgr::GetSingleTon()->GetClientRect(&rcDlg);

    //第一行控件
    int nLeftMargin = 4; 
    int nBtnInterval = 1;

    int nStcInterval = 2; 
    int nRightMargin = 5;


    CRect rcHide(0); 
    CSize sz(66,71); //m_btnHide.GetImageSize(); 
    rcHide.left = nLeftMargin;
    rcHide.top = nBtnInterval;
    rcHide.right  = rcHide.left + sz.cx;
    rcHide.bottom = rcHide.top +  sz.cy; 


    AddCommonKey("handinputBoard//btnHide", rcHide, FALSE, &CHWRecgBoard::OnClickHide );



    CRect rcDel(0); 
    sz.cx = 66; //m_btnDel.GetImageSize(); 
    rcDel.left = rcHide.right + nBtnInterval;
    rcDel.top = nBtnInterval;
    rcDel.right = rcDel.left +  sz.cx;
    rcDel.bottom = rcDel.top + sz.cy; 

    AddCommonKey( "handinputBoard//btnDel", rcDel, FALSE, &CHWRecgBoard::OnClickDel );



    int nCandWidth =  80 /*78*/;
    int nCandHeigth = 55/*65*/;

    CRect 
        rcCand2(0);   
    rcCand2.right = rcDlg.right - nRightMargin;
    rcCand2.left = rcCand2.right - nCandWidth;
    rcCand2.top = rcDlg.top + nStcInterval;
    rcCand2.bottom = rcCand2.top + nCandHeigth; 



    
    CRect rcCand1(0); 
    rcCand1.right = rcCand2.left - nStcInterval;
    rcCand1.left = rcCand1.right - nCandWidth ;
    rcCand1.top = rcDlg.top + nStcInterval;
    rcCand1.bottom = rcCand1.top + nCandHeigth; 

    AddRecgKey( rcCand1/*,"1" */);


    AddRecgKey( rcCand2/* , "2" */);

	m_rcCandidateWnd.left = rcCand1.left ;
	m_rcCandidateWnd.top =  rcCand1.top; 



     //手写板
     m_rcHwDrawWnd.left = rcDel.right;
     m_rcHwDrawWnd.right = rcCand1.left;
     m_rcHwDrawWnd.top = 0;
     m_rcHwDrawWnd.bottom = rcDlg.bottom;
    // AddRecgKey( m_rcHwDrawWnd , "手写板" );
      

 
//其余控件 
    CRect rcSpace( 0 );
     
    sz.cx = 134;
	sz.cy = 71;
    rcSpace.left = nLeftMargin;
    rcSpace.right = rcSpace.left  + sz.cx;
    rcSpace.top = rcHide.bottom + nBtnInterval;
    rcSpace.bottom = rcSpace.top + sz.cy;
 
    AddCommonKey("handinputBoard//btnSpace", rcSpace, FALSE, &CHWRecgBoard::OnClickSpace  );

 

    CRect rcEnter( 0 );  
    rcEnter.left = nLeftMargin;
    rcEnter.right = rcEnter.left +  sz.cx;
    rcEnter.top = rcSpace.bottom + nBtnInterval;
    rcEnter.bottom = rcEnter.top + sz.cy;
  
    AddCommonKey( "handinputBoard//btnEnter", rcEnter, FALSE, &CHWRecgBoard::OnClickEnter );
    


    CRect rc2( 0 );  
    rc2.left = nLeftMargin ;
    rc2.right = rc2.left +  sz.cx;
    rc2.top = rcEnter.bottom + nBtnInterval;
    rc2.bottom = rc2.top + sz.cy;

    AddCommonKey( "handinputBoard//btn2KeyBoard", rc2, FALSE, &CHWRecgBoard::OnClick2KEYBOARD );
    
    




    rcCand1.top = rcCand1.bottom + nStcInterval ;
    rcCand1.bottom = rcCand1.top + nCandHeigth;

    AddRecgKey( rcCand1/*, "3" */);

    rcCand2.top = rcCand1.top;
    rcCand2.bottom = rcCand1.bottom;

    AddRecgKey( rcCand2/*,"4" */);



    rcCand1.top = rcCand1.bottom + nStcInterval ;
    rcCand1.bottom = rcCand1.top + nCandHeigth;

    AddRecgKey( rcCand1 /*,"5"*/);


    rcCand2.top = rcCand1.top;
    rcCand2.bottom = rcCand1.bottom;

    AddRecgKey( rcCand2/*,"6"*/ );


    rcCand1.top = rcCand1.bottom + nStcInterval ;
    rcCand1.bottom = rcCand1.top + nCandHeigth;

    AddRecgKey( rcCand1 /*,"7"*/);


    rcCand2.top = rcCand1.top;
    rcCand2.bottom = rcCand1.bottom;

    AddRecgKey( rcCand2/*,"8"*/ );

	m_rcCandidateWnd.right = rcCand2.right ;
	m_rcCandidateWnd.bottom =  rcCand2.bottom; 


	//上一页
    rcCand1.top = rcCand1.bottom + nStcInterval ;
    rcCand1.bottom = rcCand1.top + nCandHeigth;

   // AddRecgKey( rcCand1/*,"9"*/ );
	AddCommonKey( "handinputBoard//btnPrevPg", rcCand1, FALSE, &CHWRecgBoard::OnClickPrevPg );
	m_pPrevPgKey = m_cCommonKeys.GetTail();
	if ( NULL != m_pPrevPgKey )
	{
		m_pPrevPgKey->emKeyState = emKeyStateDisable;
	}
	        
	//下一页
    rcCand2.top = rcCand1.top;
    rcCand2.bottom = rcCand1.bottom;
    rcCand2.left += 2;
   // AddRecgKey( rcCand2/*,"10"*/ );
	AddCommonKey( "handinputBoard//btnNextPg", rcCand2, FALSE, &CHWRecgBoard::OnClickNextPg );
    m_pNextPgKey = m_cCommonKeys.GetTail();
	if ( NULL != m_pNextPgKey )
	{
		m_pNextPgKey->emKeyState = emKeyStateDisable;
	}


}

void CHWRecgBoard::AddCommonKey(  CString strImgPath,
                              CRect& prcKey /*= 0*/,
                              BOOL bIsKeyPress /*= FALSE*/,
                              OnCommonClick click /*= NULL */)
{
    TCommonKey *pkey = new TCommonKey; 
    
    if (  !strImgPath.IsEmpty() )
    {  
        CString strPath = /*GetModuleFullPath*/GetModulePath() ;
        
        Image* pImg = CSrcManage::GetImage( strPath + "src//" +  strImgPath + "//Disable.png");
         
    }
    pkey->rcKey = prcKey;
    pkey->strImgPath = strImgPath;
    pkey->emKeyState = emKeyStateNormal;
    pkey->pOnClickFun =  click;
    m_cCommonKeys.AddTail(pkey);


}

void CHWRecgBoard::AddRecgKey( CRect& prcKey, CString str /*= ""*/ ) 
{
    TRecgKey *pkey = new TRecgKey;
    pkey->strTxt = str;
    pkey->rcKey = prcKey; 
   
    m_cRecgsKeys.AddTail(pkey);
}




void CHWRecgBoard::DrawFont( Graphics *pGraphics, CRect& cRect, CString strText )
{ 
    if ( pGraphics == NULL || strText.IsEmpty() )
    {
        return ;
    }
    
    POINT point = cRect.TopLeft();  
    
    SolidBrush brush( Color(0,0,0)  ); // 创建白色的实心刷（写字符串用）
    Font* pFont = CSrcManage::GetFont( "微软雅黑", 13 ); 
    Color cColor = Color( 146, 157, 183 );	 
    
    StringFormat cStringFormat;
    cStringFormat.SetAlignment( /*StringAlignmentNear*/ StringAlignmentCenter);
    cStringFormat.SetLineAlignment( StringAlignmentCenter );
    
    pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
    
    BSTR bstr = strText.AllocSysString();
    pGraphics->DrawString( bstr , -1, pFont, RectF( (float)point.x, (float)point.y, cRect.Width(), cRect.Height() ), &cStringFormat, &brush );
    SysFreeString( bstr );
}


void CHWRecgBoard::OnClickHide()
{
    CInputMgr::GetSingleTon()->HideBoard();
}

void CHWRecgBoard::OnClick2KEYBOARD()
{
    CInputMgr::GetSingleTon()->SetInputType( emInputKeyBoard ); 

    OnHideBoard();

    CInputMgr::GetSingleTon()->RedrawUI();

    

}

void CHWRecgBoard::OnClickDel()
{
    BYTE  vk = VK_BACK ; 
    keybd_event(vk,0,0,0);
    ::keybd_event(vk,0,KEYEVENTF_KEYUP,0); 
     
}

void CHWRecgBoard::OnClickSpace()
{
    BYTE  vk = VK_SPACE;
    
    keybd_event(vk,0,0,0);
    ::keybd_event(vk,0,KEYEVENTF_KEYUP,0);
}

void CHWRecgBoard::OnClickEnter()
{   
    BYTE  vk = VK_RETURN;
    keybd_event(vk,0,0,0);
    ::keybd_event(vk,0,KEYEVENTF_KEYUP,0);
}

void CHWRecgBoard::OnClickPrevPg()
{   
	 
	if ( m_swCurrPgIndex <= 0 )
	{
		return;
	}

	m_swCurrPgIndex -= m_swOnePgCount; 
	
	UpdateRecognizeUI();
    

}

void CHWRecgBoard::OnClickNextPg()
{
    if ( m_swCurrPgIndex + m_swOnePgCount > m_vcCandWords.size() )
	{
		return;
	}

	m_swCurrPgIndex += m_swOnePgCount; 

	UpdateRecognizeUI();
	 
	
}

//进行识别 把识别结果输出到UI
void CHWRecgBoard::UpdateRecognizeUI( )  
{   
    int nCandSize  =  m_vcCandWords.size();
    POSITION pos = m_cRecgsKeys.GetHeadPosition(); 
    
    
   
    //更新到界面
    for ( int i = m_swCurrPgIndex ;  i < m_swCurrPgIndex + m_swOnePgCount && i < nCandSize &&  pos ; i++ )
    {  
        TRecgKey* key = m_cRecgsKeys.GetNext(pos);

        int nCnt = 1;
        CString strTmp = "";
        if ( ( m_vcCandWords[i].GetAt(0) & 0x80 ) )
        {
            nCnt = 2;
        }
        
        if ( m_vcCandWords[i].GetLength() > 0  )
        {
            strTmp =  m_vcCandWords[i].Left( nCnt );
        }
        
        key->strTxt =  strTmp ; 
    }

    while ( pos )
    {
        TRecgKey* key = m_cRecgsKeys.GetNext(pos);
        key->strTxt =  "" ; 
    } 
    

	
	if ( m_swCurrPgIndex - m_swOnePgCount >= 0 )
	{
		m_pPrevPgKey->emKeyState = emKeyStateNormal;
		 
	}
	else
	{
		m_pPrevPgKey->emKeyState = emKeyStateDisable;
		 
	}
	
	if ( m_swCurrPgIndex + m_swOnePgCount >= nCandSize )
	{
		m_pNextPgKey->emKeyState = emKeyStateDisable;
	     
	}
	else
	{ 
		m_pNextPgKey->emKeyState = emKeyStateNormal;
	 
	}
    
 
    CInputMgr::GetSingleTon()->RedrawUI();
     
}

void CHWRecgBoard::OnSelCand( CString strCand )
{
    //2012-1-6 当选中的为空白时，直接返回
    if ( strCand.IsEmpty() )
    {  
		AfxOutputDebugString("\nCHWRecgBoard::OnSelCand  strCand.IsEmpty()\n ");
        return ;
    }
    
	m_swCurrPgIndex = 0;

    SendKeys( strCand ); 

    m_vcCandWords.clear();
    CHWCiHuiIF::Instance()->GetCiHui( strCand, m_vcCandWords ); 
    UpdateRecognizeUI(  );

//     const vector<CString> *p_vcCandWords = NULL;
//     CHWCiHuiIF::Instance()->GetCiHui( strCand, &p_vcCandWords ); 
//     UpdateRecognizeUI(  p_vcCandWords );
     
}


void CHWRecgBoard::Recognize( ) 
{   
    m_swCurrPgIndex = 0;

    m_vcCandWords.clear();  
    m_cRecognize.Recognize( m_vcCandWords );  
    UpdateRecognizeUI( ); 
    ResetInput(); 
    if ( m_bBeginWrite )
    {
         m_bBeginWrite = FALSE;
    }
   
     
}

void CHWRecgBoard::ResetInput()
{
    m_cRecognize.ResetTablet();
    
    if ( m_pcHWDrawWnd != NULL )
    {
       m_pcHWDrawWnd->Invalidate();
       //  m_pcHWDrawWnd->ReDrawUI();
    }
     
}

void CHWRecgBoard::ClearCandWords() //清空候选词
{   
 
    m_vcCandWords.clear();
    UpdateRecognizeUI();
}



//控件位置大小分辨率子适应
void CHWRecgBoard::BoardRectAdp()
{   
	


    if ( m_cCommonKeys.IsEmpty() || m_cRecgsKeys.IsEmpty() )
    {
        return;
    }

    //命令键
    TCommonKey * key = NULL ;
    POSITION pos = m_cCommonKeys.GetHeadPosition(); 
    while(pos)
    {   
        key = m_cCommonKeys.GetNext(pos); 
        ResolutionAdp( key->rcKey.left, key->rcKey.top );
        ResolutionAdp( key->rcKey.right, key->rcKey.bottom ); 
    }

   

    // 识别键
    TRecgKey * rgkey = NULL;
    
    POSITION rgPos = m_cRecgsKeys.GetHeadPosition();
    while(rgPos)
    {
         rgkey = m_cRecgsKeys.GetNext(rgPos);
         ResolutionAdp( rgkey->rcKey.left, rgkey->rcKey.top );
         ResolutionAdp( rgkey->rcKey.right, rgkey->rcKey.bottom ); 
    }

   
    //手写版
    m_rcHwDrawWnd.left = m_cCommonKeys.GetTail()->rcKey.right;
    m_rcHwDrawWnd.right = m_cRecgsKeys.GetHead()->rcKey.left;
    m_rcHwDrawWnd.bottom  = m_cCommonKeys.GetTail()->rcKey.bottom ;
    m_rcHwDrawWnd.top = 0;

   // TRACE("\n[CHWRecgBoard::BoardRectAdp]m_rcHwDrawWnd.width=%d  height=%d \n",m_rcHwDrawWnd.Width(), m_rcHwDrawWnd.Height() );
    
    

}