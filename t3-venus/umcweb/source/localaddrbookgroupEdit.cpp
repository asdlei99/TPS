// LocalAddrGrpEdit.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "localaddrbookgroupEdit.h"
#include "localaddrbookLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookGroupEdit dialog

CLocalAddrbookGroupEdit::CLocalAddrbookGroupEdit(CCncAddrbookIF* pAdBk, CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CLocalAddrbookGroupEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalAddrbookGroupEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pAddrBook = pAdBk;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
	m_bEdit = FALSE;
}

CLocalAddrbookGroupEdit::CLocalAddrbookGroupEdit( CCncAddrbookIF* pAdBk, TGroupInfo tGroupInfo, CWnd* pParent )
	: CTransparentBaseDlg(CLocalAddrbookGroupEdit::IDD, pParent)
{
	m_pAddrBook = pAdBk;
	m_tGroupInfo = tGroupInfo;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
	m_bEdit = TRUE;
}



void CLocalAddrbookGroupEdit::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalAddrbookGroupEdit)
	DDX_Control(pDX, IDC_STATIC_EDITGROUP, m_stEditGroup);
	DDX_Control(pDX, IDC_STATIC_GROUPNAME, m_stGroupName);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_GRPNAME, m_etGroupName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalAddrbookGroupEdit, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CLocalAddrbookGroupEdit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookGroupEdit message handlers

BOOL CLocalAddrbookGroupEdit::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();

	this->SetWindowText("AddrbookGroupEdit");
	
	CRect rectClient( 0, 0, 790, 255 );
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW );
	AfxGetMainWnd()->CenterWindow();

	m_stEditGroup.SetWindowPos( NULL, 0,  11, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stEditGroup.SetWindowText("编辑分组");
	m_stEditGroup.SetTextAlign(StringAlignmentCenter);
	m_stEditGroup.SetTextColor(Color( 255, 255, 255 ));
	m_stEditGroup.SetFont( 13, "微软雅黑" );

	m_btnSave.SetImage( IDR_PNG_POPWND_BTN_SAVE, IDR_PNG_POPWND_BTN_SAVEDOWN, IDR_PNG_POPWND_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_POPWND_BTN_CANCLE, IDR_PNG_POPWND_BTN_CANCLEDOWN, IDR_PNG_POPWND_BTN_CANCLE );

	m_btnCancel.SetWindowPos( NULL, rectClient.right - 5 - m_btnCancel.GetImageSize().cx, 4, m_btnCancel.GetImageSize().cx, m_btnCancel.GetImageSize().cy, SWP_SHOWWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	m_btnSave.SetWindowPos( NULL, rectClient.left - 4 - m_btnCancel.GetImageSize().cx, 4, m_btnSave.GetImageSize().cx, m_btnSave.GetImageSize().cy, SWP_SHOWWINDOW );
	
	m_stGroupName.SetWindowPos( NULL, 34,  77 + 36, 400, 20, SWP_SHOWWINDOW );
	m_stGroupName.SetWindowText("分组名称");
	m_stGroupName.SetTextColor(Color( 46, 55, 76 ));
	m_stGroupName.SetFont( 13, "微软雅黑" );

	CUmcwebCommon::SetImgForTransEdit(&m_etGroupName);
	m_etGroupName.SetSearchEdit(FALSE);
	m_etGroupName.SetWindowPos( NULL, 130, 66  + 36, 623, 41, SWP_SHOWWINDOW );
	m_etGroupName.SetFont( 13, "微软雅黑" );
	m_etGroupName.SetFocus();

	m_etGroupName.SetLimitLength(31);

	if ( m_bEdit )
	{
		m_stEditGroup.SetWindowText("编辑分组");
		m_etGroupName.SetWindowText( m_tGroupInfo.achGroupName );
	} 
	else
	{
		m_stEditGroup.SetWindowText("新建分组");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLocalAddrbookGroupEdit::OnBtnSave() 
{
	// TODO: Add extra validation here
	CString strName;
	s32 nRet = 0;

	m_etGroupName.GetWindowText(strName);
	strName.TrimLeft();
	strName.TrimRight();
	if( strName.IsEmpty() )
	{
		MESSAGEWNDBOX( "分组名称不能为空", this, nRet, FALSE );
		return;
	}

	if ( strName.GetLength() > 31 )
	{
		MESSAGEWNDBOX( "分组名称大于最长的31字符", this, nRet, FALSE );
		return;
	}

	CAddrBook cAddrBook = m_pAddrBook->GetAddrBook();

	CAddrMultiSetEntry cAddrGroup;

	if ( !m_bEdit )
	{
		u32 dwNum = cAddrBook.GetAddrMultiSetEntry( (LPSTR)(LPCTSTR)strName, &cAddrGroup );
		if ( dwNum > 0 )
		{	
			MESSAGEWNDBOX( "分组名称已存在", this, nRet, FALSE );
			return ;
		}	
		
		u32 dwSize = cAddrBook.GetAddrGroupUsedSize();
		if ( dwSize >= MAX_ADDRGROUP )
		{
			CString strErr;
            strErr.Format( "会场分组已达到最大值%d个", MAX_ADDRGROUP );
			MESSAGEWNDBOX( strErr, this, nRet, FALSE );
			return ;
		}
		
		cAddrGroup.SetGroupName( (LPCTSTR)strName );
		
		u16 wRe = m_pAddrBook->AddGroup( cAddrGroup );

	}
	else
	{	
		u32 dwGroupIndex = m_tGroupInfo.dwGroupIdx;
		
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
		
		if ( strName.Compare( m_tGroupInfo.achGroupName ) != 0 )
		{
			u32 dwNum = cAddrBook.GetAddrMultiSetEntry( (LPSTR)(LPCTSTR)strName, &cAddrGroup );
			if ( dwNum > 0 )
			{	
				MESSAGEWNDBOX( "分组名称已存在", this, nRet, FALSE );
				return ;
			}
			
			cAddrGroup.SetGroupName( (LPCTSTR)strName );	
			u16 wRe = m_pAddrBook->ModifyGroup( cAddrGroup );
		}		
	}
	
	CTransparentBaseDlg::OnOK();
}

