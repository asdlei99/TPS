// nmcfglogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "nmcfglogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CNMCfgLogic dialog


CNMCfgLogic::CNMCfgLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CNMCfgLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNMCfgLogic)
	m_bIsEdit = FALSE;
	m_pUmsNMConfig = NULL;
	//}}AFX_DATA_INIT
}


void CNMCfgLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNMCfgLogic)
	DDX_Control(pDX, IDC_EDIT_NMReadCommunity2, m_edtNMReadCommunity2);
	DDX_Control(pDX, IDC_EDIT_NMReadCommunity1, m_edtNMReadCommunity1);
	DDX_Control(pDX, IDC_EDIT_NMGetSetPort2, m_edtNMGetSetPort2);
	DDX_Control(pDX, IDC_EDIT_NMServerIP2, m_ipNMServerIP2);
	DDX_Control(pDX, IDC_EDIT_NMTrapPort2, m_edtNMTrapPort2);
	DDX_Control(pDX, IDC_EDIT_NMWriteCommunity2, m_edtNMWriteCommunity2);
	DDX_Control(pDX, IDC_EDIT_NMWriteCommunity1, m_edtNMWriteCommunity1);
	DDX_Control(pDX, IDC_STATIC_NMGetSetPort2, m_stcNMGetSetPort2);
	DDX_Control(pDX, IDC_STATIC_NMReadCommunity1, m_stcNMReadCommunity1);
	DDX_Control(pDX, IDC_STATIC_NMReadCommunity2, m_stcNMReadCommunity2);
	DDX_Control(pDX, IDC_STATIC_NMWriteCommunity1, m_stcNMWriteCommunity1);
	DDX_Control(pDX, IDC_STATIC_NMServerIP2, m_stcNMServerIP2);
	DDX_Control(pDX, IDC_STATIC_NMSvrIP2, m_stcNMSvrIP2);
	DDX_Control(pDX, IDC_STATIC_NMTrapPort2, m_stcNMTrapPort2);
	DDX_Control(pDX, IDC_STATIC_NMWriteCommunity2, m_stcNMWriteCommunity2);
	DDX_Control(pDX, IDC_EDIT_NMTrapPort1, m_edtNMTrapPort1);
	DDX_Control(pDX, IDC_STATIC_NMTrapPort1, m_stcNMTrapPort1);
	DDX_Control(pDX, IDC_EDIT_NMGetSetPort1, m_edtNMGetSetPort1);
	DDX_Control(pDX, IDC_STATIC_NMGetSetPort1, m_stcNMGetSetPort1);
	DDX_Control(pDX, IDC_STATIC_NMServerIP1, m_stcNMServerIP1);
	DDX_Control(pDX, IDC_EDIT_NMServerIP1, m_ipNMServerIP1);
	DDX_Control(pDX, IDC_STATIC_NMSvrIP1, m_stcNMSvrIP1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNMCfgLogic, CDlgChild)
	//{{AFX_MSG_MAP(CNMCfgLogic)
		// NOTE: the ClassWizard will add message map macros here
		ON_MESSAGE( UI_UMSTOOL_NETMNG_NTY,  OnNetMngNty )
		ON_MESSAGE( UI_UMSTOOL_ADD_NETMNG_RSP,  OnAddNMRsp )
		ON_MESSAGE( UI_UMSTOOL_DEL_NETMNG_RSP,  OnDelNMRsp )
		ON_MESSAGE( UI_UMSTOOL_MODIFY_NETMNG_RSP,  OnModNMRsp )
		ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNMCfgLogic message handlers
BOOL CNMCfgLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	if ( m_pUmsNMConfig == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface( &m_pUmsNMConfig );
		m_pUmsNMConfig->SetNotifyWnd(this->m_hWnd);
	}

	if ( !InitControlPane() )
	{
	 	return FALSE;
	}

	return TRUE; 
}


void CNMCfgLogic::InitDlg() 
{
	ShowWindow(SW_HIDE);
	SetDefaultValue();
	SetEditState( FALSE );
    m_bIsEdit = FALSE;
}

BOOL CNMCfgLogic::InitControlPane()
{
	int nFontSize = 13;
	CString strFont = _T("微软雅黑");
	
	CRect rectClient;
	this->GetClientRect(&rectClient);

	
	//网管服务器01
	m_stcNMSvrIP1.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 18*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMSvrIP1.SetTextAlign(StringAlignmentNear);
	m_stcNMSvrIP1.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMSvrIP1.SetFont( nFontSize, strFont );

	//服务器地址
	m_stcNMServerIP1.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 69*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMServerIP1.SetTextAlign(StringAlignmentNear);
	m_stcNMServerIP1.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMServerIP1.SetFont( nFontSize, strFont );

	CUmcwebCommon::SetImgForTransIpEdit(&m_ipNMServerIP1);
	m_ipNMServerIP1.SetWindowPos( NULL, 146*CUR_SCREEN_WIDTH_PER, 58*CUR_SCREEN_HEIGHT_PER, 541*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	//读共同体名
	m_stcNMReadCommunity1.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 120*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMReadCommunity1.SetTextAlign(StringAlignmentNear);
	m_stcNMReadCommunity1.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMReadCommunity1.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMReadCommunity1);
	m_edtNMReadCommunity1.SetLimitLength( UMCWEB_MAX_COMMUNITY_LENGTH );

	//写共同体名
	m_stcNMWriteCommunity1.SetWindowPos( NULL, 396*CUR_SCREEN_WIDTH_PER, 120*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMWriteCommunity1.SetTextAlign(StringAlignmentNear);
	m_stcNMWriteCommunity1.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMWriteCommunity1.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMWriteCommunity1);
	m_edtNMWriteCommunity1.SetLimitLength( UMCWEB_MAX_COMMUNITY_LENGTH );

	//读写端口
	m_stcNMGetSetPort1.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 171*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMGetSetPort1.SetTextAlign(StringAlignmentNear);
	m_stcNMGetSetPort1.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMGetSetPort1.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMGetSetPort1);
	
	//发告警端口
	m_stcNMTrapPort1.SetWindowPos( NULL, 396*CUR_SCREEN_WIDTH_PER, 171*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMTrapPort1.SetTextAlign(StringAlignmentNear);
	m_stcNMTrapPort1.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMTrapPort1.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMTrapPort1);
	


	//网管服务器02
	m_stcNMSvrIP2.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 242*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMSvrIP2.SetTextAlign(StringAlignmentNear);
	m_stcNMSvrIP2.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMSvrIP2.SetFont( nFontSize, strFont );
	
	//服务器地址
	m_stcNMServerIP2.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 293*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMServerIP2.SetTextAlign(StringAlignmentNear);
	m_stcNMServerIP2.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMServerIP2.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransIpEdit(&m_ipNMServerIP2);
		
	//读共同体名
	m_stcNMReadCommunity2.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 344*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMReadCommunity2.SetTextAlign(StringAlignmentNear);
	m_stcNMReadCommunity2.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMReadCommunity2.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMReadCommunity2);
	
	//写共同体名
	m_stcNMWriteCommunity2.SetWindowPos( NULL, 396*CUR_SCREEN_WIDTH_PER, 344*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMWriteCommunity2.SetTextAlign(StringAlignmentNear);
	m_stcNMWriteCommunity2.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMWriteCommunity2.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMWriteCommunity2);
	
	//读写端口
	m_stcNMGetSetPort2.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 395*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMGetSetPort2.SetTextAlign(StringAlignmentNear);
	m_stcNMGetSetPort2.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMGetSetPort2.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMGetSetPort2);
	
	//发告警端口
	m_stcNMTrapPort2.SetWindowPos( NULL, 396*CUR_SCREEN_WIDTH_PER, 395*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcNMTrapPort2.SetTextAlign(StringAlignmentNear);
	m_stcNMTrapPort2.SetTextColor(Color( 46, 55, 76 ));
	m_stcNMTrapPort2.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtNMTrapPort2);



	m_edtNMTrapPort2.SetWindowPos( NULL, 516*CUR_SCREEN_WIDTH_PER, 384*CUR_SCREEN_HEIGHT_PER, 171*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMGetSetPort2.SetWindowPos( NULL, 146*CUR_SCREEN_WIDTH_PER, 384*CUR_SCREEN_HEIGHT_PER, 207*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMWriteCommunity2.SetWindowPos( NULL, 516*CUR_SCREEN_WIDTH_PER, 332*CUR_SCREEN_HEIGHT_PER, 171*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMReadCommunity2.SetWindowPos( NULL, 146*CUR_SCREEN_WIDTH_PER, 332*CUR_SCREEN_HEIGHT_PER, 207*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_ipNMServerIP2.SetWindowPos( NULL, 146*CUR_SCREEN_WIDTH_PER, 280*CUR_SCREEN_HEIGHT_PER, 541*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMTrapPort1.SetWindowPos( NULL, 516*CUR_SCREEN_WIDTH_PER, 160*CUR_SCREEN_HEIGHT_PER, 171*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMGetSetPort1.SetWindowPos( NULL, 146*CUR_SCREEN_WIDTH_PER, 160*CUR_SCREEN_HEIGHT_PER, 207*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMWriteCommunity1.SetWindowPos( NULL, 516*CUR_SCREEN_WIDTH_PER, 108*CUR_SCREEN_HEIGHT_PER, 171*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtNMReadCommunity1.SetWindowPos( NULL, 146*CUR_SCREEN_WIDTH_PER, 108*CUR_SCREEN_HEIGHT_PER, 207*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	SetEditState( FALSE );

	return TRUE;
}

HRESULT CNMCfgLogic::OnNetMngNty( WPARAM wparam, LPARAM lparam )
{
	FreshNMInfo();
	return S_OK;
}

HRESULT CNMCfgLogic::OnAddNMRsp( WPARAM wparam, LPARAM lparam )
{
	FreshNMInfo();
	return S_OK;
}

HRESULT CNMCfgLogic::OnDelNMRsp( WPARAM wparam, LPARAM lparam )
{
	FreshNMInfo();
	return S_OK;
}

HRESULT CNMCfgLogic::OnModNMRsp( WPARAM wparam, LPARAM lparam )
{
	FreshNMInfo();
	return S_OK;
}

void CNMCfgLogic::FreshNMInfo()
{
	SetDefaultValue();

	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	m_pUmsNMConfig->GetUmsNetMngData( vecTTPNMServerCfg );
	
	SetNMSvr( vecTTPNMServerCfg );
}

void CNMCfgLogic::SetDefaultValue()
{
	m_ipNMServerIP1.SetWindowText( _T("") );
	m_edtNMReadCommunity1.SetWindowText( _T("") );
	m_edtNMWriteCommunity1.SetWindowText( _T("") );
	m_edtNMGetSetPort1.SetWindowText( _T("") );
	m_edtNMTrapPort1.SetWindowText( _T("") );
	m_ipNMServerIP2.SetWindowText( _T("") );
	m_edtNMReadCommunity2.SetWindowText( _T("") );
	m_edtNMWriteCommunity2.SetWindowText( _T("") );
	m_edtNMGetSetPort2.SetWindowText( _T("") );
	m_edtNMTrapPort2.SetWindowText( _T("") );
}

void CNMCfgLogic::SetNMSvr( vector<TTPNMServerCfg>& vecTTPNMServerCfg )
{
	vector<TTPNMServerCfg>::iterator it;
	for ( it = vecTTPNMServerCfg.begin(); it != vecTTPNMServerCfg.end(); it++ )
	{
		TTPNMServerCfg tTPNMServerCfg = *it;
		CString strCaption;
		if ( tTPNMServerCfg.wNMServerNO == 0 )
		{
			m_ipNMServerIP1.SetAddress(/*htonl( */tTPNMServerCfg.dwNMServerIP /*)*/);
			m_edtNMReadCommunity1.SetWindowText( tTPNMServerCfg.achNMReadCommunity );
			m_edtNMWriteCommunity1.SetWindowText( tTPNMServerCfg.achNMWriteCommunity );
			strCaption.Format( _T("%d"), tTPNMServerCfg.wNMGetSetPort );
			m_edtNMGetSetPort1.SetWindowText( strCaption );
			strCaption.Format( _T("%d"), tTPNMServerCfg.WNMTrapPort );
			m_edtNMTrapPort1.SetWindowText( strCaption );
		}
		else
		{
			m_ipNMServerIP2.SetAddress(/*htonl(*/ tTPNMServerCfg.dwNMServerIP /*)*/);
			m_edtNMReadCommunity2.SetWindowText( tTPNMServerCfg.achNMReadCommunity );
			m_edtNMWriteCommunity2.SetWindowText( tTPNMServerCfg.achNMWriteCommunity );
			strCaption.Format( _T("%d"), tTPNMServerCfg.wNMGetSetPort );
			m_edtNMGetSetPort2.SetWindowText( strCaption );
			strCaption.Format( _T("%d"), tTPNMServerCfg.WNMTrapPort );
			m_edtNMTrapPort2.SetWindowText( strCaption );
		}
	}
}

bool CNMCfgLogic::GetNMSvr( vector<TTPNMServerCfg>& vecTTPNMServerCfg )
{
	CString strNMServerIP1;
	CString strNMReadCommunity1;
	CString strNMWriteCommunity1;
	CString strNMGetSetPort1;
	CString strNMTrapPort1;
	CString strNMServerIP2;
	CString strNMReadCommunity2;
	CString strNMWriteCommunity2;
	CString strNMGetSetPort2;
	CString strNMTrapPort2;
	m_ipNMServerIP1.GetWindowText( strNMServerIP1 );
	m_edtNMReadCommunity1.GetWindowText( strNMReadCommunity1 );
	m_edtNMWriteCommunity1.GetWindowText( strNMWriteCommunity1 );
	m_edtNMGetSetPort1.GetWindowText( strNMGetSetPort1 );
	m_edtNMTrapPort1.GetWindowText( strNMTrapPort1 );
	m_ipNMServerIP2.GetWindowText( strNMServerIP2 );
	m_edtNMReadCommunity2.GetWindowText( strNMReadCommunity2 );
	m_edtNMWriteCommunity2.GetWindowText( strNMWriteCommunity2 );
	m_edtNMGetSetPort2.GetWindowText( strNMGetSetPort2 );
	m_edtNMTrapPort2.GetWindowText( strNMTrapPort2 );

	CString strError;
	int nRet = 0;
	if ( 0 != strcmp( strNMServerIP1, "" ) && 0 != strcmp( "", strNMServerIP2 ) )
	{
		if ( 0 == strcmp( strNMServerIP1, strNMServerIP2 ) )
		{
			strError = "网管服务器地址不能相同";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipNMServerIP1.SetFocus();
			return false;
		}
	}

	//网管服务器1
	if ( !( strNMServerIP1.IsEmpty() && strNMReadCommunity1.IsEmpty() && strNMWriteCommunity1.IsEmpty() && 
		strNMGetSetPort1.IsEmpty() && strNMTrapPort1.IsEmpty() ) )
	{
		TTPNMServerCfg tTPNMServerCfg1;
		
		if ( strNMServerIP1.IsEmpty() )
		{
			strError = "网管服务器地址不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipNMServerIP1.SetFocus();
			return false;
		}
		
		u32_ip dwNMSververIp1 = htonl(inet_addr((LPCTSTR)strNMServerIP1));
		if ( !CCallAddr::IsValidIpV4( dwNMSververIp1 ) ) 
		{
			strError = "网管服务器地址无效";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipNMServerIP1.SetFocus();
			return false;
		}
		tTPNMServerCfg1.dwNMServerIP = dwNMSververIp1;
		
		
		if ( strNMReadCommunity1.GetLength() > UMCWEB_MAX_COMMUNITY_LENGTH )
		{
			strError.Format( _T("读共同体名超过最大长度：%d"), UMCWEB_MAX_COMMUNITY_LENGTH );
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMReadCommunity1.SetFocus();
			return false;
		}
		strncpy( tTPNMServerCfg1.achNMReadCommunity, (LPCTSTR)strNMReadCommunity1, MAX_COMMUNITY_LENGTH );
		
		
		if ( strNMWriteCommunity1.GetLength() > UMCWEB_MAX_COMMUNITY_LENGTH )
		{
			strError.Format( _T("写共同体名超过最大长度：%d"), UMCWEB_MAX_COMMUNITY_LENGTH );
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMWriteCommunity1.SetFocus();
			return false;
		}
		strncpy( tTPNMServerCfg1.achNMWriteCommunity, (LPCTSTR)strNMWriteCommunity1, MAX_COMMUNITY_LENGTH );
		
		
		if ( strNMGetSetPort1.IsEmpty() )
		{
			strError = "读写端口不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMGetSetPort1.SetFocus();
			return false;
		}
		
		int nNMGetSetPort1 = _ttoi( (LPCTSTR)strNMGetSetPort1 );
		if ( nNMGetSetPort1 > 99999 || nNMGetSetPort1 < 1 )
		{
			strError = "读写端口越界，请在1-9999之间";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMGetSetPort1.SetFocus();
			return false;
		}
		tTPNMServerCfg1.wNMGetSetPort = nNMGetSetPort1;
		
		
		if ( strNMTrapPort1.IsEmpty() )
		{
			strError = "发警告端口不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMTrapPort1.SetFocus();
			return false;
		}

		int nNMTrapPort1 = _ttoi( (LPCTSTR)strNMTrapPort1 );
		if ( nNMTrapPort1 > 99999 || nNMTrapPort1 < 1 )
		{
			strError = "发警告端口越界，请在1-9999之间";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMTrapPort1.SetFocus();
			return false;
		}
		tTPNMServerCfg1.WNMTrapPort = _ttoi( (LPCTSTR)strNMTrapPort1 );

		tTPNMServerCfg1.wNMServerNO = 0;
		vecTTPNMServerCfg.push_back( tTPNMServerCfg1 );
	}
	
	



	//网管服务器2
	if ( !( strNMServerIP2.IsEmpty() && strNMReadCommunity2.IsEmpty() && strNMWriteCommunity2.IsEmpty() && 
		strNMGetSetPort2.IsEmpty() && strNMTrapPort2.IsEmpty() ) )
	{
		TTPNMServerCfg tTPNMServerCfg2;

		if ( strNMServerIP2.IsEmpty() )
		{
			strError = "网管服务器地址不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipNMServerIP2.SetFocus();
			return false;
		}
		
		u32_ip dwNMSververIp2 = htonl(inet_addr((LPCTSTR)strNMServerIP2));
		if ( !CCallAddr::IsValidIpV4( dwNMSververIp2 ) ) 
		{
			strError = "网管服务器地址无效";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipNMServerIP2.SetFocus();
			return false;
		}
		tTPNMServerCfg2.dwNMServerIP = dwNMSververIp2;
		
		if ( strNMReadCommunity2.GetLength() > UMCWEB_MAX_COMMUNITY_LENGTH )
		{
			strError.Format( _T("读共同体名超过最大长度：%d"), UMCWEB_MAX_COMMUNITY_LENGTH );
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMReadCommunity2.SetFocus();
			return false;
		}
		strncpy( tTPNMServerCfg2.achNMReadCommunity, (LPCTSTR)strNMReadCommunity2, MAX_COMMUNITY_LENGTH );
		
		if ( strNMWriteCommunity2.GetLength() > UMCWEB_MAX_COMMUNITY_LENGTH )
		{
			strError.Format( _T("写共同体名超过最大长度：%d"), UMCWEB_MAX_COMMUNITY_LENGTH );
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMWriteCommunity2.SetFocus();
			return false;
		}
		strncpy( tTPNMServerCfg2.achNMWriteCommunity, (LPCTSTR)strNMWriteCommunity2, MAX_COMMUNITY_LENGTH );
		
		if ( strNMGetSetPort2.IsEmpty() )
		{
			strError = "读写端口不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMGetSetPort2.SetFocus();
			return false;
		}
		
		int nNMGetSetPort2 = _ttoi( (LPCTSTR)strNMGetSetPort2 );
		if ( nNMGetSetPort2 > 99999 || nNMGetSetPort2 < 1 )
		{
			strError = "读写端口越界，请在1-9999之间";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMGetSetPort2.SetFocus();
			return false;
		}
		tTPNMServerCfg2.wNMGetSetPort = nNMGetSetPort2;
		
		if ( strNMTrapPort2.IsEmpty() )
		{
			strError = "发警告端口不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMTrapPort2.SetFocus();
			return false;
		}
		int nNMTrapPort2 = _ttoi( (LPCTSTR)strNMTrapPort2 );
		if ( nNMTrapPort2 > 99999 || nNMTrapPort2 < 1 )
		{
			strError = "发警告端口越界，请在1-9999之间";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtNMTrapPort2.SetFocus();
			return false;
		}
		tTPNMServerCfg2.WNMTrapPort = _ttoi( (LPCTSTR)strNMTrapPort2 );

		tTPNMServerCfg2.wNMServerNO = 1;
		vecTTPNMServerCfg.push_back( tTPNMServerCfg2 );
	}

	return true;
}

BOOL CNMCfgLogic::SaveNMCfg()
{
	vector<TTPNMServerCfg> vecTTPNMServerCfgNew;
	bool bGet = GetNMSvr( vecTTPNMServerCfgNew );
	if ( bGet == false )
	{
		return FALSE;
	}

	vector<TTPNMServerCfg> vecTTPNMServerCfgOld;
	m_pUmsNMConfig->GetUmsNetMngData( vecTTPNMServerCfgOld );

	vector<TTPNMServerCfg>::iterator itNew = vecTTPNMServerCfgNew.begin();
	for ( ; itNew != vecTTPNMServerCfgNew.end(); itNew++ )
	{
		bool bFind = false;
		vector<TTPNMServerCfg>::iterator itOld = vecTTPNMServerCfgOld.begin();
		for ( ; itOld != vecTTPNMServerCfgOld.end(); itOld++ )
		{
			if ( itNew->wNMServerNO == itOld->wNMServerNO )
			{
				m_pUmsNMConfig->NetMngModifyReq( *itNew );
				bFind = true;
			}
		}
		if ( bFind == false )
		{
			m_pUmsNMConfig->NetMngAddReq( *itNew );
		}
	}

	vector<TTPNMServerCfg>::iterator itOld = vecTTPNMServerCfgOld.begin();
	for ( ; itOld != vecTTPNMServerCfgOld.end(); itOld++ )
	{
		bool bFind = false;
		vector<TTPNMServerCfg>::iterator itNew = vecTTPNMServerCfgNew.begin();
		for ( ; itNew != vecTTPNMServerCfgNew.end(); itNew++ )
		{
			if ( itOld->wNMServerNO == itNew->wNMServerNO )
			{
				bFind = true;
			}
		}
		if ( bFind == false )
		{
			m_pUmsNMConfig->NetMngDeleteReq( *itOld );
		}
	}

	return TRUE;
}

void CNMCfgLogic::SetEditState( BOOL bEdit )
{
	m_ipNMServerIP1.EnableWindow( bEdit );
	m_edtNMReadCommunity1.EnableWindow( bEdit );
	m_edtNMWriteCommunity1.EnableWindow( bEdit );
	m_edtNMGetSetPort1.EnableWindow( bEdit );
	m_edtNMTrapPort1.EnableWindow( bEdit );
	m_ipNMServerIP2.EnableWindow( bEdit );
	m_edtNMReadCommunity2.EnableWindow( bEdit );
	m_edtNMWriteCommunity2.EnableWindow( bEdit );
	m_edtNMGetSetPort2.EnableWindow( bEdit );
	m_edtNMTrapPort2.EnableWindow( bEdit );
}

void CNMCfgLogic::OnDestroy()
{
	CDlgChild::OnDestroy();
}