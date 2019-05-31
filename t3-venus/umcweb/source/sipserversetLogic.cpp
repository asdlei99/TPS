// ServerSetDlg.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "sipserversetLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CSipServerSetLogic dialog
CSipServerSetLogic::CSipServerSetLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CSipServerSetLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSipServerSetLogic)
	//}}AFX_DATA_INIT
	//m_bShowMosaicHoriImg = FALSE;
    m_bIsEdit = FALSE;
}

void CSipServerSetLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSipServerSetLogic)
	DDX_Control(pDX, IDC_STATIC_IPADDR, m_stIpAddr);
	DDX_Control(pDX, IDC_ServerIP, m_Ip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSipServerSetLogic, CDlgChild)
	//{{AFX_MSG_MAP(CSipServerSetLogic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSipServerSetLogic message handlers
BOOL CSipServerSetLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	if ( !InitControlPane() )
	{
		return FALSE;
	}
	
	return TRUE; 
}


void CSipServerSetLogic::InitDlg() 
{
	m_Ip.EnableWindow(FALSE);
    m_Ip.SetAddress( 0 );
    m_bIsEdit = FALSE;
}

BOOL CSipServerSetLogic::InitControlPane()
{
	CUmcwebCommon::SetImgForTransIpEdit(&m_Ip);
	
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stIpAddr.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (77 - 46)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stIpAddr.SetWindowText("Íø³Ê×¢²á·þÎñÆ÷µØÖ·");
	m_stIpAddr.SetTextAlign(StringAlignmentNear);
	m_stIpAddr.SetTextColor(Color( 46, 55, 76 ));
	m_stIpAddr.SetFont( 13, "Î¢ÈíÑÅºÚ" );
	
	m_Ip.SetWindowPos( NULL, (159+50)*CUR_SCREEN_WIDTH_PER, (64 - 46)*CUR_SCREEN_HEIGHT_PER, (528-50)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER,	SWP_SHOWWINDOW );
	m_Ip.EnableWindow(FALSE);

	return TRUE;
}