// dlggkset.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "gkserversetLogic.h"
#include "eventoutumsreg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CGkServerSetLogic dialog
CGkServerSetLogic::CGkServerSetLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CGkServerSetLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGkServerSetLogic)
	//}}AFX_DATA_INIT

	m_bSwitchStatus = FALSE;
	//m_bShowMosaicHoriImg = FALSE; 
    m_bIsEdit = FALSE;

}

void CGkServerSetLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGkServerSetLogic)
	DDX_Control(pDX, IDC_STATIC_GKONANOFF, m_stGkOnAndOff);
	DDX_Control(pDX, IDC_STATIC_IPADDR, m_stIpAddr);
	DDX_Control(pDX, IDC_GK_IPADDRESS, m_Ip);
	DDX_Control(pDX, IDC_BtnGk, m_btnSwitch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGkServerSetLogic, CDlgChild)
	//{{AFX_MSG_MAP(CGkServerSetLogic)
	ON_MESSAGE( WM_BUTTON_CLICK, OnClickSwitchBtn )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGkServerSetLogic message handlers
BOOL CGkServerSetLogic::InitControlPane()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
	ScreenToClient(&rectClient);
	
	CUmcwebCommon::SetImgForTransIpEdit(&m_Ip);
	
	m_stGkOnAndOff.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (66 - 46 - 6 + 7)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stGkOnAndOff.SetWindowText("GK·þÎñ");
	m_stGkOnAndOff.SetTextAlign(StringAlignmentNear);
	m_stGkOnAndOff.SetTextColor(Color( 46, 55, 76 ));
	m_stGkOnAndOff.SetFont( 13, "Î¢ÈíÑÅºÚ" );
	
	m_stIpAddr.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (66 - 46 + 51)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stIpAddr.SetWindowText("GK·þÎñÆ÷µØÖ·");
	m_stIpAddr.SetTextAlign(StringAlignmentNear);
	m_stIpAddr.SetTextColor(Color( 46, 55, 76 ));
	m_stIpAddr.SetFont( 13, "Î¢ÈíÑÅºÚ" );
	
	m_Ip.SetWindowPos( NULL, 159*CUR_SCREEN_WIDTH_PER, (64 - 46 + 51 - 11)*CUR_SCREEN_HEIGHT_PER, 528*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER,	SWP_SHOWWINDOW );

    m_btnSwitch.SetImage( IDR_PNG_LOGINWND_BTN_ON, IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS,
        IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS);

	m_btnSwitch.SetWindowPos( NULL, 574*CUR_SCREEN_WIDTH_PER, 10*CUR_SCREEN_HEIGHT_PER, 113*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_btnSwitch.EnableWindow(FALSE);
	m_emGkSerBtnStatus = GK_OFF;
	m_Ip.EnableWindow(FALSE);

	return TRUE;
}

BOOL CGkServerSetLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	if ( !InitControlPane() )
	{
		return FALSE;
	}

	return TRUE; 
}

LRESULT CGkServerSetLogic::OnClickSwitchBtn(WPARAM wParam, LPARAM lParam) 
{
    m_bSwitchStatus = m_btnSwitch.GetSwitchState();
    if ( m_bSwitchStatus )
    {
        m_Ip.EnableWindow( TRUE );
    }else
    {
        m_Ip.EnableWindow( FALSE );
        
    }

	return 0L;
}

//set on/off
void CGkServerSetLogic::SetSwitch()
{
    if ( m_btnSwitch.GetSwitchState() )
    {
        m_Ip.EnableWindow( TRUE );
    }else
    {
        m_Ip.EnableWindow( FALSE );

    }
}

void CGkServerSetLogic::InitDlg()
{
	m_Ip.EnableWindow(FALSE);
    m_bIsEdit = FALSE;  //restore
}
