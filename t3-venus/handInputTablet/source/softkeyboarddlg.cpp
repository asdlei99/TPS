/// CSoftKeyboardDlg.cpp : implementation file
//

#include "stdafx.h"
 
#include "softkeyboardDlg.h"
#include <math.h>
#include "inputMgr.h"
#include "nmscommon.h"

//#include "TsfIF.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 

#define TIMER_ID 101

#define TIMER_ID_CHIN_ENTER 102
#define TIMER_ID_CHIN_ENTER_INTERVAL 200

#ifndef WS_EX_LAYERED
#	define WS_EX_LAYERED			0x00080000
#endif

#ifndef LWA_ALPHA
#	define LWA_ALPHA				0x00000002
#endif

#ifndef ULW_ALPHA
#	define ULW_ALPHA				0x00000002
#endif

#ifndef AC_SRC_ALPHA
#	define AC_SRC_ALPHA				0x01
#endif

#define  KEY_UI_LIST_LEFT           9    // 距离左边缘的大小  
#define  KEY_UI_LIST_A_LEFT			23   // A行距离左边缘的大小  
#define  KEY_UI_LIST_1_LEFT			48  // 1行距离左边缘的大小  
#define  KEY_UI_LIST_TOP			7     // 距离上边缘的大小
#define  KEY_UI_LIST_V_SPACE		4     //键垂直间间隔
#define  KEY_UI_LIST_H_SPACE		8     //键水平间间隔


#define TAB 0x02
#define CAPSLOCK 0x03
#define SHIFT 0x04
#define CTRL 0x05
#define BSPACE 0x06
#define ENTER 0x07
#define ALT 0x08
#define WINDOW 0x9
#define LEFT 0x0A
#define RIGHT 0x0B
#define UP 0x0C
#define DOWN 0x0D
#define ESC 0x0E
#define PUP 0x0F
#define PDN 0x10
#define HOME 0x11
#define END 0x12
#define INS 0x13
#define DEL 0x14
#define WWW 0x15
  
/////////////////////////////////////////////////////////////////////////////
// CSoftKeyboardDlg dialog
//CSoftKeyboardDlg *g_pdlg = NULL;

CSoftKeyboardDlg* CSoftKeyboardDlg::m_pMainKeyBoard = NULL;


CSoftKeyboardDlg::CSoftKeyboardDlg( ) 
{  
    m_bDownCap              = FALSE;
	m_bImmEn                = TRUE;
	m_pImgeBK				= NULL;

    m_bCapture				= FALSE;
    
   

	m_bHitCaption			= FALSE; 
	m_hTagWnd				= NULL;
 
	m_bCapsLock				= FALSE;
 
	m_bIsInKeyRect          = FALSE;

    m_bWillUpdateCapsLock = FALSE; 
    

    Init();

   // KeyRectAdp(); 无需做分辨率自适应，当前大小在HP一体机上与系统软键盘一样大小  2012-7-18 yjj


  //   SetCandidateWndPos();
}

CSoftKeyboardDlg::~CSoftKeyboardDlg()
{
 
    POSITION pos = cKeys.GetHeadPosition();
    while(pos)
    {
        delete cKeys.GetNext(pos);
    }
    
    int state = DescribeKeyState();
    if(state & 0x01) keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
    if(state & 0x02) keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
	if(state & 0x04) keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
}

CSoftKeyboardDlg* CSoftKeyboardDlg::GetSingleTon()
{
	
	if ( m_pMainKeyBoard == NULL )
	{
		m_pMainKeyBoard = new CSoftKeyboardDlg(); 
	}
	return m_pMainKeyBoard;
}

  
void CSoftKeyboardDlg::UpdateImm( )
{  
    m_bImmEn = !m_bImmEn;
    if ( CInputMgr::GetSingleTon()->IsWindowVisible() && CInputMgr::GetSingleTon()->GetInputType() == emInputKeyBoard )
    {
        CInputMgr::GetSingleTon()->RedrawUI();
    }
}

void CSoftKeyboardDlg::RedrawUI( WPARAM wParam, LPARAM lParam )
{
	if ( m_pImgeBK == NULL )
	{
		return;
	}

    Graphics *pGraphics = (Graphics*)wParam; 
    HWND hGraphWnd = (HWND )lParam; 
   
    if ( pGraphics == NULL || hGraphWnd == 0 )
    {
        return;
    }


    RECT rc;
    ::GetWindowRect( hGraphWnd, &rc );
    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { rc.left, rc.top };
    SIZE szWin;
	
 	szWin.cx = rc.right - rc.left ;//m_pImgeBK->GetWidth();  2012-2-14 自适应分辨率
  	szWin.cy = rc.bottom - rc.top ; //m_pImgeBK->GetHeight();
	
    
    if ( NULL != m_pImgeBK )
    {
        pGraphics->DrawImage( m_pImgeBK, 0, 0, szWin.cx ,  szWin.cy );
    } 
	 

	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();

     
    CString strImgPath = /*GetModuleFullPath*/GetModulePath() + "src" ;
        

	while(pos)
	{
		key = cKeys.GetNext(pos);
		CString strPath = strImgPath + key->strImgPath ;

		Image *pImgeItem = NULL;
		char charkeyNormal = key->cNormal;
		char charkeyShifted = key->cShifted;

        if (  TRUE == key->bIsKeyPress )
        {   
            if ( strPath.Find("switch") >= 0 )
            {
               pImgeItem = CSrcManage::GetImage( strPath + "//Press.png" ); 
            }
            else
            {   
                if ( END == charkeyShifted )
                {
                    if (  !IsChineseIM() )
                    {  
                        int index = strPath.ReverseFind( '/' );

                       // AfxOutputDebugString( "\n" + strPath.Left( index ) + "\n");
                        strPath = strPath.Left( index ) + "//engIme"; 
                    }

                    
                }
                
               pImgeItem = CSrcManage::GetImage( strPath + "//Sel.png" );
              
            }
            
        }
        else
        {  
            if ( strPath.Find("switch") >= 0   )
            { 
                if ( CAPSLOCK == charkeyShifted )
                {
                    if ( IsCapsLock()/* (IsCapsLock() && !m_bDownCap) || (!IsCapsLock() &&  m_bDownCap) */)
                    {
                        pImgeItem = CSrcManage::GetImage( strPath + "//OnNormal.png" );
                        //TRACE("\nCSoftKeyboardDlg::RedrawUI  OnNormal \n");
                    }
                    else
                    {
                        pImgeItem = CSrcManage::GetImage( strPath + "//OffNormal.png" );
                       // TRACE("\nCSoftKeyboardDlg::RedrawUI  OffNormal \n");
                    }

                    m_bDownCap = FALSE;
                    
                } 
//                 else if (  END == charkeyShifted )
//                 {
//                     if ( IsChineseIM() )
//                     {
//                         pImgeItem = CSrcManage::GetImage( strPath + "//OnNormal.png" );
//                     }
//                     else
//                     {
//                         pImgeItem = CSrcManage::GetImage( strPath + "//OffNormal.png" );
//                     }
//                 }
               
            }
            else
            {
                if ( END == charkeyShifted )
                {
                    if (  !IsChineseIM() )
                    {
                        int index = strPath.ReverseFind( '/' );
                    
                        //AfxOutputDebugString( "\n" + strPath.Left( index ) + "\n");
                        strPath = strPath.Left( index + 1 ) + "engIme"; 
                    }
                    
                }
                 
                pImgeItem = CSrcManage::GetImage( strPath + "//Normal.png" ); 
              
                
            }
            
             
             
        }

        pGraphics->DrawImage( pImgeItem, key->rcKey.left, key->rcKey.top, key->rcKey.Width(),key->rcKey.Height() );
    } 
 
   
}
 

 
void CSoftKeyboardDlg::OnShowBoard( HWND hTagWnd )
{
    m_hTagWnd = hTagWnd;
     //SetCandidateWndPos();
}

void CSoftKeyboardDlg::OnHideBoard()
{

}
 

 
void CSoftKeyboardDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{  
  
	BOOL32 bIsHitCaption = TRUE; 
	KEYDEF * key;
  
	POSITION pos = cKeys.GetHeadPosition();
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if(key->rcKey.PtInRect(point))
		{
			m_bIsInKeyRect = TRUE;
		 
			CString str = key->cNormal;
		 
			SendKey(key); 

			key->bIsKeyPress = TRUE; 

			bIsHitCaption = FALSE;
		 
            CInputMgr::GetSingleTon()->RedrawUI();	
			break;
		}
	}

    if ( key != NULL )
    {
        key->bIsKeyPress = FALSE;
	 
    }
	 
    //SetCandidateWndPos();

    //暂时不允许拖动
// 	if ( TRUE == bIsHitCaption )
// 	{
//  //		m_pLastFocusWnd = GetFocus(); 
// 		m_bHitCaption = TRUE; 
// 		CRect   rtWin; 
// 		GetWindowRect(&rtWin); 
// 		
// 		ClientToScreen(&point); 
// 		m_ptOffset.x=point.x-rtWin.left; 
// 		m_ptOffset.y=point.y-rtWin.top; 
// 	 
// 		SetCapture(); 	
// 	}
}



void CSoftKeyboardDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{   
 
}



void CSoftKeyboardDlg::SendKey(KEYDEF * keydef)
{   
    m_bDownCap = FALSE;
	BOOL32 bCloseWnd = FALSE;
		if(keydef->cNormal == 0x00)
	{
		int vk;
		BOOL uptoo = TRUE;
		if(keydef->cShifted > 0x6F) //is a function key
		{
			vk = keydef->cShifted;
		}
		else
		{
			switch(keydef->cShifted)
			{
			case TAB:    // 0x02
				vk = VkKeyScan(0x09) & 0xFF;
				break;
			case CAPSLOCK:    // 0x03
               	vk = VK_CAPITAL;
                m_bDownCap = TRUE;
				CInputMgr::GetSingleTon()->RefreshCapsLock();  //2012-7-30 解决触摸引起的大写锁定状态显示错误的问题 by yjj
//                 {
//                     m_bCapsLock = !m_bCapsLock;
//                     if ( m_bCapsLock == TRUE )
//                     {
//                         if ( IsChineseIM() )
//                         {
//                             IME_Chs2Eng( m_hTagWnd );
//                         }
//                     }
//                     return;
//                 }
				break;
			case SHIFT:    // 0x04
				vk = VK_SHIFT;
				if(GetKeyState(vk) & 0xF000) return;
				uptoo = FALSE;
				break;
			case CTRL:    // 0x05
// 				vk = VK_CONTROL;
// 				if(GetKeyState(vk) & 0xF000) return;
// 				uptoo = FALSE;
			//	::SendMessage( ::GetParent( m_hTagWnd ), WM_KILLFOCUS, 0, 0 );
                CInputMgr::GetSingleTon()->HideBoard();
				return;
				break;
            case ESC:    // 0x0E  //切换到手写
                 CInputMgr::GetSingleTon()->SetInputType( emInputHandWrite ); 
                 CInputMgr::GetSingleTon()->RedrawUI();
                return;
				break;
			case BSPACE:    // 0x06
				vk = VK_BACK;
				break;
			case ENTER:    // 0x07
                {  
//  					if ( !IsChineseIM() )  //如何是英文输入法则直接ruturn出去
//                     {
//   						return;
//                     }
					vk =  VkKeyScan(0x0D) & 0xFF;
                   
					break;
				}
			case ALT:    // 0x08
				vk = VK_MENU;
				break;
			case WINDOW:    // 0x9
				vk = VK_LWIN;
				break;
			case LEFT:    // 0x0A
				vk = VK_LEFT;
				break;
			case RIGHT:    // 0x0B
				vk = VK_RIGHT;
				break;
			case UP:    // 0x0C
				vk = VK_UP;
				break;
			case DOWN:    // 0x0D
				vk = VK_DOWN;
				break;
			case PUP: //0x0F
				vk = VK_PRIOR;
				break;
			case PDN: //0x10
				vk = VK_NEXT;
				break;
			case HOME: //0x11
				vk = VK_HOME;
				break;
			case END: //0x12
			//	 vk = VK_END;
				IME_Chs2Eng(  );
				return;
				break;
			case INS: //0x13
				vk = VK_INSERT;
				break;
			case DEL: //0x14
				vk = VK_DELETE;
				break;
			case WWW:
                {
		            KEYDEF key;
		            key.cNormal = key.cShifted = 'H';
		            SendKey(&key);
		            key.cNormal = key.cShifted = 'T';
		            SendKey(&key);
		            SendKey(&key);
		            key.cNormal = key.cShifted = 'P';
		            SendKey(&key);
		            key.cNormal = key.cShifted = ':';
		            SendKey(&key);
		            key.cNormal = key.cShifted = '/';
		            SendKey(&key);
		            SendKey(&key);
		            key.cNormal = key.cShifted = 'W';
		            SendKey(&key);
		            SendKey(&key);
		            SendKey(&key);
		            vk = VkKeyScan('.') & 0xFF;
                }
				break;
			default:
				ASSERT(FALSE);
				break;
			}
		}
		if ( keydef->cShifted != CTRL && keydef->cShifted != END )
		{
			keybd_event(vk,0,0,0);

			if(uptoo)
			{
				keybd_event(vk,0,KEYEVENTF_KEYUP,0);
			}
		} 		
	}
	else
	{
		char pChar = keydef->cNormal;
// 		if ( m_bCapsLock == TRUE && m_bNbrOnly == FALSE )
//  		{
// 			if ( IsSuperKey( keydef ) == FALSE )
// 			{
// 				keybd_event(VK_SHIFT,0,0,0);
// 			}	 
//  		}
		
		if ( '*' == pChar || '@' == pChar || '#' == pChar )
		{
			keybd_event(VK_SHIFT,0,0,0);
		}

		unsigned char vk1 = VK_SHIFT;
		SHORT ks = VkKeyScan(pChar);
		BYTE key = ks & 0xFF;

		keybd_event(key,0,0,0);
		keybd_event(key,0,KEYEVENTF_KEYUP,0);

		//turn off the control and shift if they were down
		unsigned char vk = VK_SHIFT;
		if(GetKeyState(vk) & 0xF000)
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}	
// 		if ( m_bCapsLock == TRUE )
// 		{
// 			if ( IsSuperKey( keydef ) == FALSE )
// 			{
// 				keybd_event(vk,0,KEYEVENTF_KEYUP,0);
// 			}	
// 		}
		if ( '*' == pChar || '@' == pChar || '#' == pChar )
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
		

// 		vk = VK_CONTROL;
// 		if(GetKeyState(vk) & 0xF000) //allow toggle
// 		{
// 			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
// 		}
	}
}

  

KEYDEF*  CSoftKeyboardDlg::FindKey( char cNormal )
{
	KEYDEF *keyTmp = NULL;

	POSITION pos = cKeys.GetHeadPosition();
	
	while ( pos )
	{
		keyTmp = cKeys.GetNext( pos );

		if ( NULL != keyTmp && ( keyTmp->cNormal == cNormal ) )
		{
			return keyTmp;
		}
	}
	
	return keyTmp;
}

 

  
//判断当前输入法是否是中文的
BOOL32 CSoftKeyboardDlg::IsChineseIM()
{
    return  !m_bImmEn;//CTsfIF::GetSingleTon()->IsChineseIM(m_hTagWnd);
}

 
void CSoftKeyboardDlg::IME_Chs2Eng()
{
    //CTsfIF::GetSingleTon()->IME_Switch( ::GetParent(m_hTagWnd));
    keybd_event(VK_CONTROL,0,0,0);
    keybd_event(VK_SPACE,0,0,0);
    keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);

    UpdateImm();
} 
   
 


BOOL32 CSoftKeyboardDlg::IsCapsLock()
{

    BOOL32 bCaps = FALSE;

	CString str;

//     if(	GetAsyncKeyState( VK_CAPITAL ) & 0x1 )
// 	{
// 		bCaps = TRUE;
// 		
// 	}
// 
// 	str.Format("\n[CSoftKeyboardDlg::IsCapsLock] GetAsyncKeyState = %d \n",bCaps);
// 	AfxOutputDebugString( str );


	bCaps = FALSE;
	if( GetKeyState( VK_CAPITAL ) &0x1)
	{  
		bCaps = TRUE;		
	}
	str.Format("\n[CSoftKeyboardDlg::IsCapsLock] GetKeyState = %d \n",bCaps);
	AfxOutputDebugString( str );
// 
//     bCaps = FALSE;
//     BYTE  keyState[256];  
//     GetKeyboardState((LPBYTE)&keyState);  
//     if  ((keyState[VK_CAPITAL]) == 1 )  
//     {    
//          bCaps = TRUE;
//         //CAPS  LOCK按下  
// 
//     }  
// 	str.Format("\n[CSoftKeyboardDlg::IsCapsLock] GetKeyboardState = %d \n",bCaps);
// 	AfxOutputDebugString( str );
   

    return bCaps;
}

int CSoftKeyboardDlg::DescribeKeyState() 
{
    int state = 0;
    short ks;
    ks = GetKeyState(VK_CAPITAL);
    if(ks & 0x000F) state += 0x01;
    ks = GetKeyState(VK_SHIFT);
    if(ks & 0xF000) state += 0x02;
    ks = GetKeyState(VK_CONTROL);
    if(ks & 0xF000) state += 0x04;
    return state;
}


BOOL CSoftKeyboardDlg::Init()
{
	//CDialog::OnInitDialog();
   // ModifyStyleEx( 0,0x08000000L | WS_EX_TOPMOST );
  
 

    CString strPath =  /*GetModuleFullPath*/GetModulePath();//GetModuleFileName(); //->GetImagePath() ;
     

	m_pImgeBK = CSrcManage::GetImage( strPath + "src//softKeyboard//softkeyboard_bk.png" );
 
 
    CRect cRect;
    CInputMgr::GetSingleTon()->GetClientRect(&cRect);
    //EnableWindow(FALSE);  //可加可不加,目的是不让软件盘激活
 
    CRect rcTemp( cRect ); 
 
    rcTemp = CRect( cRect.left + KEY_UI_LIST_1_LEFT,  KEY_UI_LIST_TOP + cRect.top, 0, 0 );
	AddKey('1','!',"//softKeyboard//1",rcTemp, FALSE );
    
    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
 	AddKey('2','@',"//softKeyboard//2",rcTemp, FALSE );
 
    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey('3','#',"//softKeyboard//3",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
 	AddKey('4','$',"//softKeyboard//4",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('5','%',"//softKeyboard//5",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('6','^',"//softKeyboard//6",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('7','&',"//softKeyboard//7",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('8','*',"//softKeyboard//8",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('9','(',"//softKeyboard//9",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('0',')',"//softKeyboard//0",rcTemp, FALSE );

	//AddKey('-','_',10);
	//AddKey('=','+',10);
	//AddKey(0x00,BSPACE,14); //backspace
	//AddKey(0x00,PUP,-12);

	//second row
	//AddKey(0x00,0x00,2); //signal row change
	//AddKey(0x00,TAB,14); //tab
    rcTemp =CRect( cRect.left + KEY_UI_LIST_LEFT,  rcTemp.bottom + KEY_UI_LIST_V_SPACE , 0, 0 ); 
	AddKey('q','Q',"//softKeyboard//q",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
 	AddKey('w','W',"//softKeyboard//w",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('e','E',"//softKeyboard//e",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('r','R',"//softKeyboard//r",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('t','T',"//softKeyboard//t",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('y','Y',"//softKeyboard//y",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('u','U',"//softKeyboard//u",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('i','I',"//softKeyboard//i",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('o','O',"//softKeyboard//o",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('p','P',"//softKeyboard//p",rcTemp, FALSE );
  
    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey(0x00,BSPACE,"//softKeyboard//del",rcTemp, FALSE );

    //AddKey('[','{',10);
	//AddKey(']','}',10);
	//AddKey('\\','|',10);
	//AddKey(0x00,PDN,-12);
// 
// 	//third row
// 	AddKey(0x00,0x00,3); //signal row change
// 	//AddKey(0x00,CAPSLOCK,18); //caps lock
    rcTemp =CRect( cRect.left + KEY_UI_LIST_A_LEFT,  rcTemp.bottom + KEY_UI_LIST_V_SPACE , 0, 0 ); 
	AddKey('a','A',"//softKeyboard//a",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('s','S',"//softKeyboard//s",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('d','D',"//softKeyboard//d",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('f','F',"//softKeyboard//f",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('g','G',"//softKeyboard//g",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('h','H',"//softKeyboard//h",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('j','J',"//softKeyboard//j",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('k','K',"//softKeyboard//k",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('l','L',"//softKeyboard//l",rcTemp, FALSE );
    
    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey(0x00,ENTER,"//softKeyboard//enter",rcTemp, FALSE );

// 	//AddKey(';',':',10);
// 	//AddKey('\'','\"',10);
// 	//AddKey(0x00,HOME,-10);
// 
// 	//fourth row
// 	AddKey(0x00,0x00,4); //signal row change
// 	//AddKey(0x00,SHIFT,22); //shift
    rcTemp =CRect( cRect.left + KEY_UI_LIST_LEFT,  rcTemp.bottom + KEY_UI_LIST_V_SPACE , 0, 0 ); 
	AddKey('*','*',"//softKeyboard//star",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
 	AddKey('z','Z',"//softKeyboard//z",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('x','X',"//softKeyboard//x",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('c','C',"//softKeyboard//c",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('v','V',"//softKeyboard//v",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('b','B',"//softKeyboard//b",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('n','N',"//softKeyboard//n",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('m','M',"//softKeyboard//m",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey('.','>',"//softKeyboard//point",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey('@','@',"//softKeyboard//@",rcTemp, FALSE );

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey('#','#',"//softKeyboard//#",rcTemp, FALSE );


	


// 	//AddKey(',','<',10);
// 	//AddKey('.','>',10);
// 	//AddKey('/','?',10);
// //	AddKey(0x00,SHIFT,22); //shift
// 	
// 
// 	//fifth row
//  	AddKey(0x00,0x00,5); //signal row change
// // 	AddKey(0x00,CTRL,12); //ctrl
// // 	AddKey(0x00,WINDOW,12); //window
// // 	AddKey(0x00,ALT,12); //alt
	

    rcTemp =CRect( cRect.left + KEY_UI_LIST_LEFT,  rcTemp.bottom + KEY_UI_LIST_V_SPACE , 0, 0 ); 
	AddKey(0x00,CAPSLOCK,"//softKeyboard//switch//capsLock",rcTemp, FALSE );
    

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
	AddKey(0x00,END,"//softKeyboard//chnIme",rcTemp, FALSE ); //---切换输入法 //switch//chnIme
     
    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
 	AddKey(' ',' ',"//softKeyboard//space",rcTemp, FALSE );
     
 


    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey(0x00,ESC,"//softKeyboard//handInput",rcTemp, FALSE );//ctrl ---切换到手写
    

    rcTemp = CRect( rcTemp.right + KEY_UI_LIST_H_SPACE,  rcTemp.top, 0, 0 );
    AddKey(0x00,CTRL,"//softKeyboard//hideKeyBoard",rcTemp, FALSE );//ctrl ---隐藏键盘 

// 	AddKey(0x00,LEFT,12); //left
// 	AddKey(0x00,UP,12); //up
// 	AddKey(0x00,DOWN,12); //down
// 	AddKey(0x00,RIGHT,12); //right
	//AddKey(0x00,WWW,-m_pImgeNormal->GetWidth()); //http://WWW
	//AddKey(0x00,DEL,16);
 
 
	return TRUE;  
}


 

void CSoftKeyboardDlg::AddKey(
            char pNormal,
            char pShifted,
            CString strImgPath,
            CRect& prcKey /*= 0*/,
            BOOL bIsKeyPress /*= FALSE*/)
{
    KEYDEF *m_key = new KEYDEF;
    m_key->cNormal = pNormal;
    m_key->cShifted = pShifted;
    
    if (  !strImgPath.IsEmpty() )
    {  
        CString strPath = /*GetModuleFullPath*/GetModulePath() ;
        
        Image* pImg = NULL;
        if ( strImgPath.Find("switch") >= 0 )
        {
            pImg = CSrcManage::GetImage( strPath + "src//" +  strImgPath + "//OnNormal.png");
        }
        else
        {   
            pImg = CSrcManage::GetImage( strPath + "src//" +  strImgPath + "//Normal.png");
        }
      
        if ( pImg )
        {
            prcKey.right  = prcKey.left + pImg->GetWidth();
            prcKey.bottom = prcKey.top + pImg->GetHeight();
        }
    }
    m_key->rcKey = prcKey;
    m_key->strImgPath = strImgPath;
    m_key->bIsKeyPress = bIsKeyPress;
	cKeys.AddTail(m_key);
}

 
//功    能: 不受shift约束的key 
BOOL32 CSoftKeyboardDlg::IsSuperKey( KEYDEF* key )
{
    if ( key->cNormal >= '0' && key->cNormal <= '9' )
    {
        return TRUE;
    }
    
    if ( '*' == key->cNormal || '@' == key->cNormal || '#' == key->cNormal || '.' == key->cNormal)
    {
        return TRUE;
    }
    
    if ( key->cShifted == ' ' )
    {
        return TRUE;
    }
    
    return FALSE;
}

//键盘rect的分辨率自适应
void CSoftKeyboardDlg::KeyRectAdp() 
{   


    KEYDEF * key;
    POSITION pos = cKeys.GetHeadPosition();  
    
    while(pos)
    {
		key = cKeys.GetNext(pos);
        ResolutionAdp( key->rcKey.left, key->rcKey.top );
        ResolutionAdp( key->rcKey.right, key->rcKey.bottom );
        
       
    }
}



//设置候选词窗口位置，始终在软件盘上方
/*
ImmGetCandidateWindow
ImmSetCandidateWindow 
ImmSetCompositionWindow
*/
void CSoftKeyboardDlg::SetCandidateWndPos()
{ 

//     HIMC  himc = ImmGetContext( m_hTagWnd  );
// 
//     CRect rect;
//     CInputMgr::GetSingleTon()->GetWindowRect( &rect );
//     rect.top = rect.top - 50;
//     rect.bottom = rect.bottom - 50;
//     
// //     CANDIDATEFORM tCandidateForm; 
// //     tCandidateForm.dwIndex = 0;
// //     tCandidateForm.dwStyle = CFS_CANDIDATEPOS; //CFS_EXCLUDE;
// 
// //     
// //     
// //     tCandidateForm.ptCurrentPos = rect.TopLeft(); 
// //     BOOL32 re = ImmSetCandidateWindow( himc, &tCandidateForm );
//     COMPOSITIONFORM tPos;
//     tPos.dwStyle = CFS_RECT;
//     tPos.rcArea = rect;
// 
// 
//     BOOL32 re = ImmSetCompositionWindow( himc, &tPos );
// 
//     
// //    TRACE("\n[CSoftKeyboardDlg::SetCandidateWndPos] result = %d GetLastError=%d \n",re, GetLastError() );
// 
//     //::ImmAssociateContextEx ( CInputMgr::GetSingleTon()->GetSafeHwnd(), 0, IACE_DEFAULT );
}