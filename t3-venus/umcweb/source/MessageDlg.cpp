// MessageDlg.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "MessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog
//CMessageDlg * CMessageDlg::m_pDlg = NULL;

 
BOOL CMessageDlg::m_bShowBtnCancel = TRUE;

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CMessageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_dwBkResourceID = IDR_PNG_POPWND_BK_SMALL;
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageDlg)
	DDX_Control(pDX, IDC_STATIC_Title, m_stTitle);
	DDX_Control(pDX, IDC_STATIC_MSGCONTENT, m_stMsgContent);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMessageDlg, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CMessageDlg)
	ON_BN_CLICKED(IDOK, OnBtnOk)
	ON_BN_CLICKED(IDCANCEL, OnBtnCancel)
	ON_WM_DESTROY()
 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg message handlers
BOOL CMessageDlg::OnInitDialog() 
{   
	//设置位置和大小的代码放在最前面，防止时闪烁
	CRect rectClient( 0, 0,  400, 255 ); 
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW );
	this->CenterWindow(NULL);

	CTransparentBaseDlg::OnInitDialog();
    SetWindowText( "CMessageDlg" );

	m_stTitle.SetWindowPos( NULL, 0,  10, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stTitle.SetWindowText("提示信息");
	m_stTitle.SetTextAlign(StringAlignmentCenter);
	m_stTitle.SetTextColor(Color( 255, 255, 255 ));
	m_stTitle.SetFont( 13, "微软雅黑" );

	m_btnCancel.SetImage( IDR_PNG_MESSAGE_CANCEL, IDR_PNG_MESSAGE_CANCELDOWN, IDR_PNG_MESSAGE_CANCEL );
	m_btnOK.SetImage( IDR_PNG_MESSAGE_OK, IDR_PNG_MESSAGE_OKDOWN, IDR_PNG_MESSAGE_OK );
	
	m_btnOK.SetWindowPos( NULL, rectClient.right/2 - 26 - m_btnOK.GetImageSize().cx, rectClient.bottom - 23 - m_btnOK.GetImageSize().cy, m_btnOK.GetImageSize().cx, m_btnOK.GetImageSize().cy, SWP_SHOWWINDOW );
	m_btnCancel.SetWindowPos( NULL, rectClient.right/2 + 26, rectClient.bottom - 23 - m_btnCancel.GetImageSize().cy, m_btnCancel.GetImageSize().cx, m_btnCancel.GetImageSize().cy, SWP_SHOWWINDOW );
 
	GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	
	s32 nOffset = 0;
	s32 nLen =  m_strWndTxt.GetLength();
	s32 nLineNull = 1;
	if ( nLen > 34 )
	{
		nOffset = 14;
		nLineNull = 2;
 	}
	
	if ( !m_bShowBtnCancel )
	{
		m_btnOK.SetWindowPos( NULL, rectClient.right/2 - m_btnOK.GetImageSize().cx/2, rectClient.bottom - 23 - m_btnOK.GetImageSize().cy, m_btnOK.GetImageSize().cx, m_btnOK.GetImageSize().cy, SWP_SHOWWINDOW );
		m_btnCancel.ShowWindow(SW_HIDE);
	}
	
	m_stMsgContent.SetWindowPos( NULL, 14, 110 - nOffset, 400 - 28, 16*nLineNull + nOffset, SWP_SHOWWINDOW );
	m_stMsgContent.SetTextAlign(StringAlignmentCenter);
	m_stMsgContent.SetTextColor(Color( 37, 56, 70 ));
	m_stMsgContent.SetFont( 13, "微软雅黑" ); 
	m_stMsgContent.SetWindowText(m_strWndTxt);
	return TRUE; 
}

void CMessageDlg::MessageBoxWnd( const CString& strText , BOOL bShowBtnCancel )
{
	m_strWndTxt = strText;
	m_bShowBtnCancel = bShowBtnCancel;
 
}

void CMessageDlg::OnBtnOk() 
{
 
	m_strWndTxt = "";
	OnOK();
}

void CMessageDlg::OnBtnCancel() 
{
 
	m_strWndTxt = "";
	OnCancel();
} 

BOOL CMessageDlg::IsMsgBoxVisible( BOOL bEndDlg )
{
    BOOL re = FALSE; 
	CWnd *p = FindWindow( NULL, "CMessageDlg"); 
    if( p != NULL )
	{
		if( bEndDlg )  
			((CDialog*)p)->EndDialog( IDCANCEL ); 
		re = TRUE;  
	}
 	 
    return re; 
}

void CMessageDlg::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();
	
	//SAFE_RELEASE(m_pDlg);
}
 