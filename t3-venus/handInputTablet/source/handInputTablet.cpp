// handInputTablet.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "handInputTablet.h"
#include "handInputTabletDlg.h"
#include "inputMgr.h"
#include "nmscommon.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "exceptioncatch.h"
#define EXCEPTION_FILE_PATH _T("exception.log")

/////////////////////////////////////////////////////////////////////////////
// CHandInputTabletApp

BEGIN_MESSAGE_MAP(CHandInputTabletApp, CWinApp)
	//{{AFX_MSG_MAP(CHandInputTabletApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHandInputTabletApp construction

CHandInputTabletApp::CHandInputTabletApp()
{
    
        m_hkKeyboard = 0;
                     m_hkMouse = 0;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHandInputTabletApp object

CHandInputTabletApp theApp;



UINT g_wTimerID = 0;
HWND g_hCurHitWnd = 0;  //��ǰ����Ĵ���
VOID   CALLBACK   CBTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{  
    
    if ( idEvent != g_wTimerID)
    { 
        return;
    }

	KillTimer(NULL,g_wTimerID);

	//ͨ��GetGUIThreadInfo��ȡ�����Ϣ����׼ 2013.4.27 yjj
    GUITHREADINFO thrdInfo;
	ZeroMemory( &thrdInfo,sizeof(thrdInfo) );
	thrdInfo.cbSize = sizeof(thrdInfo);
	BOOL re = GetGUIThreadInfo(  0 , &thrdInfo);
	
// 	CString strMsg;
// 	strMsg.Format("\nmouseHook��ptWnd=%x, thrdInfo.hwndCaret=%x ,thrdInfo.hwndFocus=%x, thrdInfo.hwndActive=%x , thrdInfo.hwndCapture=%x,bCaretBlinking=%d\n", 
// 		g_hCurHitWnd, thrdInfo.hwndCaret,thrdInfo.hwndFocus, thrdInfo.hwndActive,thrdInfo.hwndCapture,thrdInfo.flags&GUI_CARETBLINKING);
// 	AfxOutputDebugString(strMsg); 
	
	if ( re && thrdInfo.hwndCaret  == g_hCurHitWnd )
	{
		
		SetSoftKBDlgShow( thrdInfo.hwndCaret );
	} 
	else
	{
		SetSoftKBDlgHide();
	}
 
}

typedef struct tagMSLLHOOKSTRUCT {
    POINT   pt;
    DWORD   mouseData;
    DWORD   flags;
    DWORD   time;
    DWORD   dwExtraInfo;
} MSLLHOOKSTRUCT, FAR *LPMSLLHOOKSTRUCT, *PMSLLHOOKSTRUCT;
 

//��깳�ӣ��ػ� WM_LBUTTONDOWN  �¼�
LRESULT CALLBACK  LowLevelMouseProc  (int nCode, WPARAM wParam, LPARAM lParam)
{  
    
    if ( HC_ACTION == nCode &&  WM_LBUTTONDOWN ==  wParam  )
    {   
        
        PMSLLHOOKSTRUCT  p = (PMSLLHOOKSTRUCT)lParam;	
        if ( p == NULL )
        {
            return CallNextHookEx( NULL, nCode, wParam, lParam );
        }
      
          if( ( (p->flags) & 0x1 ) == 0  ) //˵������ʵ���
          {   
              //AfxOutputDebugString("\nmouseHook������������ؼ���\n");
              SetSoftKBDlgHide( ); 
  
              return CallNextHookEx( NULL, nCode, wParam, lParam );
          }


	////////////////////////////////////////////////////////////////////////////////////////////
    //ͨ��GetGUIThreadInfo��ȡ�����Ϣ����׼�����ǵ�һ�εõ���ҳ�еĿ�����״̬����ȷ2013.4.27 yjj//
	///////////////////////////////////////////////////////////////////////////////////////////
 		CPoint cpMousePos( p->pt.x, p->pt.y );  
        HWND hPtWnd = WindowFromPoint(cpMousePos);//��ȡ��������ڵ�Ĵ��� 
		//DWORD threadId = GetWindowThreadProcessId(hPtWnd, 0);
         g_hCurHitWnd = hPtWnd;
		 if( hPtWnd != CInputMgr::GetSingleTon()->GetSafeHwnd() )
		 {
			 KillTimer(NULL, g_wTimerID );
			 g_wTimerID = SetTimer(NULL,NULL,30,CBTimerFun);
		 }
		 return CallNextHookEx( NULL, nCode, wParam, lParam );


	  
 
 
	////////////////////////////////////////////////////////////////////////////////////////////
    ////////////ֻ�ʺ�mfc���Ϳ������word uc��ʶ�𲻵�                                ////////
	////////////////////////////////////////////////////////////////////////////////////////////
        CPoint mousepos( p->pt.x, p->pt.y );  
        //::GetCursorPos(&mousepos);  
        HWND ptWnd = WindowFromPoint(mousepos);//��ȡ��������ڵ�Ĵ��� 
         
        if ( !IsWindow( ptWnd ))
        {
            return CallNextHookEx( NULL, nCode, wParam, lParam );
        }
        
        //�жϵ�ǰhwnd�Ƿ��ǿɱ༭�ģ�����ǣ��򵯳�����̣�������ǣ������������
        s8 pName[256]={0};
        GetClassName(  ptWnd,pName,sizeof(pName) ); 
        bool bCandWnd = !strcmp(pName,"QQPinyinCompWnd"); //�Ƿ��Ǻ�ѡ�ʴ���
        //TRACE("\n CursorWnd ClassName = %s \n",pName); 
        if ( strcmp(pName,"Edit") == 0 || strcmp(pName,"RichEdit") == 0  ||  bCandWnd )
        {   
            WINDOWINFO pwi; 
            if ( !bCandWnd  && GetWindowInfo( ptWnd,&pwi ) )
            { 
                if ( pwi.dwStyle & ES_READONLY || !::IsWindowVisible( ptWnd ) )  //ֻ�����Եı༭�򲻵�������
                {
                   SetSoftKBDlgHide( ); 
                   return  CallNextHookEx( NULL, nCode, wParam, lParam );
                }
            } 
            
            SetSoftKBDlgShow( ptWnd );
           
            
        }
        else if( ptWnd != CInputMgr::GetSingleTon()->GetSafeHwnd() )
        {  
            if (  ::GetParent( ptWnd ) != CInputMgr::GetSingleTon()->GetSafeHwnd() )
            {   
                SetSoftKBDlgHide( );
            }

        }
        
    }
    
    return CallNextHookEx( NULL, nCode, wParam, lParam );
}


typedef struct tagKBDLLHOOKSTRUCT {
    DWORD   vkCode;
    DWORD   scanCode;
    DWORD   flags;
    DWORD   time;
    DWORD   dwExtraInfo;
} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

 
//�ж��Ƿ����޸����뷨���ȼ�
void CaptureIMMHotKey( WPARAM wMessage, PKBDLLHOOKSTRUCT pKb)
{
    if ( pKb == NULL )
    {
        return;
    }
    
    switch (wMessage)
    {
    case WM_KEYDOWN:  case WM_SYSKEYDOWN:   
        ////Ctrl + Space
        if (  (GetKeyState(VK_CONTROL) & 0x8000) != 0  && (pKb->vkCode == VK_SPACE)  )
        {
            //�л����뷨
            SoftKBDlgUpdateImm(); 
           // AfxOutputDebugString("\n VK_SPACE\n");
 
        } 
 
        break;
        case  WM_KEYUP:    case WM_SYSKEYUP: 
            if (  (GetKeyState(VK_CONTROL) & 0x8000) != 0  && (pKb->vkCode == VK_SPACE)  )
            {
                //�л����뷨
                SoftKBDlgUpdateImm(); 
                
            } 
               else if (  ( (GetKeyState(VK_CONTROL) & 0x8000) != 0  && ( pKb->vkCode == VK_LSHIFT || pKb->vkCode ==VK_RSHIFT))  
                            ||  ( ( (GetKeyState(VK_SHIFT) & 0x8000) != 0)  && (pKb->vkCode == VK_LCONTROL || pKb->vkCode == VK_RCONTROL) )  ) 
          
            {
                //�л����뷨
                SoftKBDlgUpdateImm(); 
                AfxOutputDebugString("\nshift\n");
                
            } 
        break;
    }
    
    
    
}

//���̹���
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{ 
      
       if (nCode == HC_ACTION )
       { 
            PKBDLLHOOKSTRUCT p; 
            p = (PKBDLLHOOKSTRUCT)lParam;
            if (   wParam == WM_KEYDOWN )
            {
                if ( (( p->flags) & 16 ) == 0 ) //˵������ʵ����
                {   
                    SetSoftKBDlgHide( );
                    //            AfxOutputDebugString("\nkeyboard down hide \n");
                }
            }
           	
            
            CaptureIMMHotKey(wParam, p);

       }
 
 

     return ::CallNextHookEx( NULL, nCode, wParam, lParam );	
}



/////////////////////////////////////////////////////////////////////////////
// CHandInputTabletApp initialization


BOOL OnlyStartOne();

BOOL CHandInputTabletApp::InitInstance()
{

    //ֻ����һ������ʵ��
    if ( !OnlyStartOne() )
    {
        return FALSE;
    }
 
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif 

    //�쳣����
    CString strFullPath = /*GetModuleFullPath*/GetModulePath();
    strFullPath += EXCEPTION_FILE_PATH;
    CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
    CExceptionCatch::Start(); 
    
    //��ס���̣��Ա�ʵʱ���´�Сд��״̬
    m_hkKeyboard = ::SetWindowsHookEx(/*WH_KEYBOARD_LL*/13,LowLevelKeyboardProc, AfxGetApp()->m_hInstance, 0);  
    if ( m_hkKeyboard == NULL )
    {   
        CString strErr;
        strErr.Format("\n[CHandInputTabletApp::InitInstance] kook keyBoard fail, GetLastError() = %d \n", GetLastError() );
        AfxOutputDebugString( strErr );
        return FALSE;
    }
   
    //��ס��꣬�Ա������������ʾ������
    m_hkMouse  = ::SetWindowsHookEx(/* WH_MOUSE_LL*/14  ,   LowLevelMouseProc ,  AfxGetApp()->m_hInstance ,  0 );  
    if (m_hkKeyboard == NULL  )
    {
        CString strErr;
        strErr.Format("\n[CHandInputTabletApp::InitInstance] kook mouse fail, GetLastError() = %d \n", GetLastError() );
        AfxOutputDebugString( strErr );
        
    }

//�ϳ�timer�����ں���Դ��ʹ����깳����� 2011-12-28 by yjj
//    g_wConfTimerID = SetTimer(NULL,NULL,500,CBTimerFun);
    
    CoInitialize(NULL);
    
    CInputMgr* pInput = CInputMgr::GetSingleTon();

    //�ȳ�ʼ�������������깳�Ӻ���д��ʼ������������
    CInputMgr::GetSingleTon()->Init();

    m_pMainWnd = pInput; 

  	::SetProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1 );

    m_pMainWnd->RunModalLoop( ); 
    return FALSE;
 
	CHandInputTabletDlg dlg;
	m_pMainWnd = &dlg; 
   // m_pMainWnd->Attach( GetDesktopWindow() );
	int nResponse = dlg.DoModal();
    
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


int CHandInputTabletApp::ExitInstance() 
{
    // TODO: Add your specialized code here and/or call the base class
    CExceptionCatch::Free();
    UnhookWindowsHookEx(m_hkMouse); 
    UnhookWindowsHookEx(m_hkKeyboard);
    if ( m_pMainWnd != NULL &&  m_pMainWnd->GetSafeHwnd() != NULL )
    {
        m_pMainWnd->DestroyWindow();
        delete m_pMainWnd;  
        m_pMainWnd = 0;
    }  
    
    CoUninitialize();

    return CWinApp::ExitInstance();
}


BOOL CHandInputTabletApp::PreTranslateMessage(MSG* pMsg) 
{ 
    //ֻ�е�ǰ�ļ�������Ǳ�����ʱ����Ӧ����ʹ�ü��̹��� by yjj
//     if( pMsg != NULL && pMsg->message == WM_KEYUP   )
//     {   
//          
//         //�������л���Сдʱ�������Ҳͬ���л�    
//         if ( pMsg->wParam == VK_CAPITAL  )
//         {   
//             CInputMgr::GetSingleTon()->RedrawUI(); 
//         }
//     } 
    
    return CWinApp::PreTranslateMessage(pMsg);
}




BOOL OnlyStartOne()
{  
    HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, AfxGetApp()->m_pszAppName);   
    
      //   �ź������ڣ����������һ��ʵ������   
     if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
     {  		
          //   �ر��ź������   
          CloseHandle(hSem);   
        //   Ѱ����ǰʵ����������   
        HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
        while   (::IsWindow(hWndPrevious))   
        {   
            //   ��鴰���Ƿ���Ԥ��ı��?   
            //   �У���������Ѱ�ҵ�����   
            if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
            {    		 
                //BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
                //(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 
                
                //   ����������С������ָ����С   
//                 if   (::IsIconic(hWndPrevious)) 				
//                     ::ShowWindow(hWndPrevious,SW_RESTORE);   
                
                HWND hdl = GetForegroundWindow();
                if (hWndPrevious !=  hdl )
                {   					
                 //  ::ShowWindow(hWndPrevious,SW_RESTORE); 
                    ::SetForegroundWindow(hWndPrevious);
                }
                
                return   FALSE;   
            }   
            //   ����Ѱ����һ������   
            hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
        }   
        //   ǰһʵ���Ѵ��ڣ����Ҳ���������   
        //   �˳���ʵ��   
        return   FALSE;   
    } 
    return TRUE;
}