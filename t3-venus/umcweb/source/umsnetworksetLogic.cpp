// SystemNetworkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "umsnetworksetLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CUmsNetworkSetLogic dialog
CUmsNetworkSetLogic::CUmsNetworkSetLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CUmsNetworkSetLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUmsNetworkSetLogic)
	//}}AFX_DATA_INIT
	//m_bShowMosaicHoriImg = FALSE;
    m_bIsEdit = FALSE;
}

void CUmsNetworkSetLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUmsNetworkSetLogic)
	DDX_Control(pDX, IDC_STATIC_IPADDR, m_stIpAddr);
	DDX_Control(pDX, IDC_STATIC_IPSUB, m_stIpSub);
	DDX_Control(pDX, IDC_STATIC_IPGATWAY, m_stIpGatway);
	DDX_Control(pDX, IDC_IP, m_Ip);
	DDX_Control(pDX, IDC_IP_Sub, m_Ip_Sub);
	DDX_Control(pDX, IDC_IP_GetWay, m_Ip_GetWay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUmsNetworkSetLogic, CDlgChild)
	//{{AFX_MSG_MAP(CUmsNetworkSetLogic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmsNetworkSetLogic message handlers
BOOL CUmsNetworkSetLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	if ( !InitControlPane() )
	{
		return FALSE;
	}

	return TRUE; 
}

void CUmsNetworkSetLogic::InitDlg()
{
	m_Ip.EnableWindow(FALSE);
	m_Ip_Sub.EnableWindow(FALSE);
	m_Ip_GetWay.EnableWindow(FALSE);

	m_Ip.SetAddress( 0 );
	m_Ip_Sub.SetAddress( 0 );
	m_Ip_GetWay.SetAddress( 0 );
    m_bIsEdit = FALSE;
}

BOOL CUmsNetworkSetLogic::InitControlPane()
{
	CUmcwebCommon::SetImgForTransIpEdit(&m_Ip);
	CUmcwebCommon::SetImgForTransIpEdit(&m_Ip_Sub);
	CUmcwebCommon::SetImgForTransIpEdit(&m_Ip_GetWay);
	
	CRect rectClient;
	this->GetClientRect(&rectClient);
	
	m_stIpAddr.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (77 - 46)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stIpAddr.SetWindowText("IPµØÖ·");
	m_stIpAddr.SetTextAlign(StringAlignmentNear);
	m_stIpAddr.SetTextColor(Color( 46, 55, 76 ));
	m_stIpAddr.SetFont( 13, "Î¢ÈíÑÅºÚ" );
	
	m_stIpSub.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (77 - 46 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stIpSub.SetWindowText("×ÓÍøÑÚÂë");
	m_stIpSub.SetTextAlign(StringAlignmentNear);
	m_stIpSub.SetTextColor(Color( 46, 55, 76 ));
	m_stIpSub.SetFont( 13, "Î¢ÈíÑÅºÚ" );
	
	m_stIpGatway.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER,  (77 - 46 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stIpGatway.SetWindowText("Ä¬ÈÏÍø¹Ø");
	m_stIpGatway.SetTextAlign(StringAlignmentNear);
	m_stIpGatway.SetTextColor(Color( 46, 55, 76 ));
	m_stIpGatway.SetFont( 13, "Î¢ÈíÑÅºÚ" );
	
	m_Ip.SetWindowPos( NULL, 142*CUR_SCREEN_WIDTH_PER, (64 - 46)*CUR_SCREEN_HEIGHT_PER, 545*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER,	SWP_SHOWWINDOW );
	m_Ip_GetWay.SetWindowPos( NULL, 142*CUR_SCREEN_WIDTH_PER, (64  - 46 + 2*(41 + 7))*CUR_SCREEN_HEIGHT_PER, 545*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_Ip_Sub.SetWindowPos( NULL, 142*CUR_SCREEN_WIDTH_PER, (64  - 46 + 41 + 7)*CUR_SCREEN_HEIGHT_PER, 545*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_Ip.EnableWindow(FALSE);
	m_Ip_Sub.EnableWindow(FALSE);
	m_Ip_GetWay.EnableWindow(FALSE);
	
	return TRUE;
}
