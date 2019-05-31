// LocalAddrMeetingEdit.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "localaddrbookmeetEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookMeetEdit dialog
CLocalAddrbookMeetEdit::CLocalAddrbookMeetEdit(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CLocalAddrbookMeetEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalAddrbookMeetEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Editing = false;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
}

CLocalAddrbookMeetEdit::CLocalAddrbookMeetEdit(CCncAddrbookIF* pAdBk,CWnd* pParent)
	: CTransparentBaseDlg(CLocalAddrbookMeetEdit::IDD, pParent)
{
	m_pAddrBook = pAdBk;
	m_Editing = false;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
}

CLocalAddrbookMeetEdit::CLocalAddrbookMeetEdit( CCncAddrbookIF* pAdBk, TAddrInfo tAddrInfo, CWnd* pParent )
: CTransparentBaseDlg(CLocalAddrbookMeetEdit::IDD, pParent)
{
	m_pAddrBook = pAdBk;
	m_tAddrInfo = tAddrInfo;
	m_Editing = true;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
}

void CLocalAddrbookMeetEdit::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalAddrbookMeetEdit)
	DDX_Control(pDX, IDC_STATIC_EDITMEET, m_stEditMeet);
	DDX_Control(pDX, IDC_STATIC_MEETCODE, m_stMeetCode);
	DDX_Control(pDX, IDC_STATIC_MEETNAME, m_stMeetName);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnSave);
	DDX_Control(pDX, IDC_EDIT_MEETINGNAME, m_etMeetName);
	DDX_Control(pDX, IDC_EDIT_MEETINGCODE, m_etMeetCode);	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLocalAddrbookMeetEdit, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CLocalAddrbookMeetEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookMeetEdit message handlers
void CLocalAddrbookMeetEdit::OnOK() 
{
	CString strE164;
	CString strEntryName;
	s32 nRet = 0;

	m_etMeetName.GetWindowText(strEntryName);
	strEntryName.TrimLeft();
	strEntryName.TrimRight();

	m_etMeetCode.GetWindowText(strE164);
	strE164.TrimLeft();
	strE164.TrimRight();

	if( strEntryName.IsEmpty() && strE164.IsEmpty() )
	{
		MESSAGEWNDBOX( "会场名称和会场号码不能全为空", this, nRet, FALSE );
		return;
	}

	if ( CCallAddr::IsValidE164( strEntryName ) )
	{
		MESSAGEWNDBOX( "会场名称不可以全部为数字或[*#,]组合", this, nRet, FALSE );
		return;
	}

	if ( !CUmcwebCommon::IsValidTPStr( strEntryName ) )
    { 
        MESSAGEWNDBOX( "会场名称不可以包含空格及括号中的任意字符[ ; / ? : @ & = + $ , % ^ ]", this, nRet, FALSE ); 
		return;
	}

	if ( strEntryName.GetLength() > 31 )
	{
		MESSAGEWNDBOX( "会场名称大于最长的31字符", this, nRet, FALSE );
		return;
	}

	if ( !strE164.IsEmpty() && !CCallAddr::IsValidE164(strE164))
	{
		MESSAGEWNDBOX( "号码必须全部为数字或[*#,]组合", this, nRet, FALSE );
		return;
	}

	if ( strE164.GetLength() > 13 )
	{
		MESSAGEWNDBOX( "会场号码大于最长的13字符", this, nRet, FALSE );
		return;
	}

	CAddrBook cAddrBook = m_pAddrBook->GetAddrBook();	
	CAddrEntry cAddrEntry;

	if ( m_Editing )
	{
		bool bChange = false;
		if ( strEntryName.Compare( m_tAddrInfo.achEntryName ) != 0 )
		{
			if ( !strEntryName.IsEmpty() )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByName( (LPSTR)(LPCTSTR)strEntryName, &cAddrEntry );
				if ( dwNum > 0 )
				{
					MESSAGEWNDBOX( "会场名称已存在", this, nRet, FALSE );
					return;
				}
				bChange = true;
			}
		}
		
		if ( strE164.Compare( m_tAddrInfo.achE164 ) != 0 )
		{
			if ( !strE164.IsEmpty() )
			{
				u32 dwNum = cAddrBook.GetAddrEntryByNumber( (LPSTR)(LPCTSTR)strE164, &cAddrEntry );
				if ( dwNum > 0 )
				{
					MESSAGEWNDBOX( "会场号码已存在", this, nRet, FALSE );
					return;
				}
			}		
			bChange = true;
		}
		
		u32 dwEntryIndex = m_tAddrInfo.dwEntryIdx;
		if ( bChange )
		{		
			cAddrBook.GetAddrEntry( &cAddrEntry, dwEntryIndex );
			cAddrEntry.SetEntryName( (LPCTSTR)strEntryName );
			cAddrEntry.SetMtNumber( (LPCTSTR)strE164 );
			
			u16 wRe = m_pAddrBook->ModifyEntry( cAddrEntry );
		}
	}
	else
	{
		u32 dwNum = cAddrBook.GetAddrEntryByName( (LPSTR)(LPCTSTR)strEntryName, &cAddrEntry );
		if ( !strEntryName.IsEmpty() )
		{
			if ( dwNum > 0 )
			{
				MESSAGEWNDBOX( "会场名称已存在", this, nRet, FALSE );
				return ;
			}
		}
		
		if ( !strE164.IsEmpty() )
		{
			dwNum = cAddrBook.GetAddrEntryByNumber( (LPSTR)(LPCTSTR)strE164, &cAddrEntry );
			if ( dwNum > 0 )
			{
				MESSAGEWNDBOX( "会场号码已存在", this, nRet, FALSE );
				return ;
			}
		}
		
		u32 dwSize = cAddrBook.GetAddrEntryUsedSize();
		if ( dwSize >= MAX_ADDRENTRY )
		{
			CString strErr;
            strErr.Format( "会场条目已达到最大值%d个", MAX_ADDRENTRY );
			MESSAGEWNDBOX( strErr, this, nRet, FALSE);
			return ;
		}
		
		cAddrEntry.SetEntryName( (LPCTSTR)strEntryName );
		cAddrEntry.SetMtNumber( (LPCTSTR)strE164 );
		
		u16 wRe = m_pAddrBook->AddEntry( cAddrEntry );
	}

	CTransparentBaseDlg::OnOK();
}

BOOL CLocalAddrbookMeetEdit::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();

	this->SetWindowText("AddrbookConfEdit");
	
	CRect rectClient( 0, 0, 790, 255 );
    this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW );
	AfxGetMainWnd()->CenterWindow();

	m_stEditMeet.SetWindowPos( NULL, 0,  11, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stEditMeet.SetWindowText("编辑会场");
	m_stEditMeet.SetTextAlign(StringAlignmentCenter);
	m_stEditMeet.SetTextColor(Color( 255, 255, 255 ));
	m_stEditMeet.SetFont( 13, "微软雅黑" );
	
	m_btnSave.SetImage( IDR_PNG_POPWND_BTN_SAVE, IDR_PNG_POPWND_BTN_SAVEDOWN, IDR_PNG_POPWND_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_POPWND_BTN_CANCLE, IDR_PNG_POPWND_BTN_CANCLEDOWN, IDR_PNG_POPWND_BTN_CANCLE );

	m_btnCancel.SetWindowPos( NULL, rectClient.right - 5 - m_btnCancel.GetImageSize().cx, 4, m_btnCancel.GetImageSize().cx, m_btnCancel.GetImageSize().cy, SWP_SHOWWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	m_btnSave.SetWindowPos( NULL, rectClient.left - 4 - m_btnCancel.GetImageSize().cx, 4, m_btnSave.GetImageSize().cx, m_btnSave.GetImageSize().cy, SWP_SHOWWINDOW );

	m_stMeetCode.SetWindowPos( NULL, 34,  126 + 25, 100, 20, SWP_SHOWWINDOW );
	m_stMeetCode.SetWindowText("会场号码");
	m_stMeetCode.SetTextColor(Color( 46, 55, 76 ));
	m_stMeetCode.SetFont( 13, "微软雅黑" );
	
	CUmcwebCommon::SetImgForTransEdit(&m_etMeetCode);
	m_stMeetCode.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	m_etMeetCode.SetWindowPos( NULL, 130, rectClient.bottom - rectClient.Height() - rectClient.Height()/2, 623 , 41, SWP_SHOWWINDOW );
	m_etMeetCode.SetFont( 13, "微软雅黑" );

	m_stMeetName.SetWindowPos( NULL, 34,  77 + 15, 100, 20, SWP_SHOWWINDOW );
	m_stMeetName.SetWindowText("会场名称");
	m_stMeetName.SetTextColor(Color( 46, 55, 76 ));
	m_stMeetName.SetFont( 13, "微软雅黑" );

	//设置焦点到m_etMeetName中
	CUmcwebCommon::SetImgForTransEdit(&m_etMeetName);
	m_stMeetName.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	m_etMeetName.SetWindowPos( NULL, 130, rectClient.bottom - rectClient.Height() - rectClient.Height()/2, 623, 41, SWP_SHOWWINDOW|SWP_NOACTIVATE );
	m_etMeetName.SetFont( 13, "微软雅黑" );

	m_etMeetName.SetLimitLength(31);
	m_etMeetCode.SetLimitLength(13);

	if (m_Editing)
	{
		m_stEditMeet.SetWindowText(_T("编辑会场"));

		m_etMeetName.SetWindowText( m_tAddrInfo.achEntryName );
		m_etMeetCode.SetWindowText( m_tAddrInfo.achE164 );	
	}
	else
	{
		m_stEditMeet.SetWindowText(_T("新建会场"));
	}

	return TRUE; 
}
