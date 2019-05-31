// vtrcfglogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "vtrcfglogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CVTRCFGLOGIC dialog


CVTRCfgLogic::CVTRCfgLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CVTRCfgLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVTRCfgLogic)
	m_bIsEdit = FALSE;

	m_pVTRCtrlIF = NULL;
	//}}AFX_DATA_INIT
}


void CVTRCfgLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVTRCfgLogic)
	DDX_Control(pDX, IDC_EDIT_VTRIP, m_ipVTRIP);
	DDX_Control(pDX, IDC_EDIT_VTRNo, m_edtVTRNo);
	DDX_Control(pDX, IDC_EDIT_VTRName, m_edtVTRName);
	DDX_Control(pDX, IDC_STATIC_VTRIP, m_stcVTRIP);
	DDX_Control(pDX, IDC_STATIC_VTRNo, m_stcVTRNo);
	DDX_Control(pDX, IDC_STATIC_VTRName, m_stcVTRName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVTRCfgLogic, CDlgChild)
	//{{AFX_MSG_MAP(CVTRCfgLogic)
	ON_MESSAGE( UI_UMSTOOL_VTR_NTY, CVTRCfgLogic::OnVtrNty )
	ON_MESSAGE( UI_UMSTOOL_ADD_VTR_RSP, CVTRCfgLogic::OnAddVtrRsp )
	ON_MESSAGE( UI_UMSTOOL_DEL_VTR_RSP, CVTRCfgLogic::OnDelVtrRsp )
	ON_MESSAGE( UI_UMSTOOL_MODIFY_VTR_RSP, CVTRCfgLogic::OnMdyVtrRsp )
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVTRCFG message handlers
BOOL CVTRCfgLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	if ( !InitControlPane() )
	{
		return FALSE;
	}

	if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
    }

	REG_MSG( UI_UMSTOOL_VTR_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_ADD_VTR_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_DEL_VTR_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_MODIFY_VTR_RSP, GetSafeHwnd() );
	
	return TRUE; 
}


void CVTRCfgLogic::InitDlg()
{
	ShowWindow(SW_HIDE);
	SetEditState( FALSE );
    m_bIsEdit = FALSE;
}

BOOL CVTRCfgLogic::InitControlPane()
{
	int nFontSize = 13;
	CString strFont = _T("微软雅黑");
	
	CRect rectClient;
	this->GetClientRect(&rectClient);

	//录像机名称
	m_stcVTRName.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (77 - 46)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcVTRName.SetTextAlign(StringAlignmentNear);
	m_stcVTRName.SetTextColor(Color( 46, 55, 76 ));
	m_stcVTRName.SetFont( nFontSize, strFont );

	CUmcwebCommon::SetImgForTransEdit(&m_edtVTRName);
	m_edtVTRName.SetLimitLength( MAX_VTR_NAME_LENGTH-1 );

	//录像机编号
	m_stcVTRNo.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (77 - 46 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcVTRNo.SetTextAlign(StringAlignmentNear);
	m_stcVTRNo.SetTextColor(Color( 46, 55, 76 ));
	m_stcVTRNo.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtVTRNo);
	m_edtVTRNo.SetLimitLength( 3 );

	//录像机IP
	m_stcVTRIP.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (77 - 46 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stcVTRIP.SetTextAlign(StringAlignmentNear);
	m_stcVTRIP.SetTextColor(Color( 46, 55, 76 ));
	m_stcVTRIP.SetFont( nFontSize, strFont );
	
	CUmcwebCommon::SetImgForTransIpEdit(&m_ipVTRIP);


	m_edtVTRName.SetWindowPos( NULL, 159*CUR_SCREEN_WIDTH_PER, (64 - 46)*CUR_SCREEN_HEIGHT_PER, 528*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_ipVTRIP.SetWindowPos( NULL, 159*CUR_SCREEN_WIDTH_PER, (64 - 46 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, 528*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_edtVTRNo.SetWindowPos( NULL, 159*CUR_SCREEN_WIDTH_PER, (64 - 46 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, 528*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	

	SetEditState( FALSE );

	return TRUE;
}

void CVTRCfgLogic::SetEditState( BOOL bEdit )
{
	m_edtVTRName.EnableWindow( bEdit );
	m_edtVTRNo.EnableWindow( bEdit );
	m_ipVTRIP.EnableWindow( bEdit );
}

BOOL CVTRCfgLogic::SaveVTRCfg()
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return FALSE;
	}
	TVcrCfg tVTRCfgOld;
	m_pVTRCtrlIF->GetUmsVTRData( tVTRCfgOld );


	TVcrCfg tVTRCfg;
	bool bGet = GetVTRCfg( tVTRCfg, tVTRCfgOld );
	if ( bGet == false )
	{
		return FALSE;
	}
	

	bool bFind = false;

	if ( tVTRCfgOld.m_byEqpID == 0 )
	{
		if ( tVTRCfg.m_byEqpID == 0 )
		{
			return TRUE;
		}

		u16 nRet = m_pVTRCtrlIF->VTRAddReq( tVTRCfg );
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( _T("添加录像机请求发送失败") );
		}
	}
	else
	{
		if ( tVTRCfg.m_byEqpID == 0 )
		{
			u16 nRet = m_pVTRCtrlIF->VTRDeleteReq( tVTRCfgOld );
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( _T("删除录像机请求发送失败") );
			}
		}
		else
		{
			u16 nRet = m_pVTRCtrlIF->VTRModifyReq( tVTRCfgOld, tVTRCfg );
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( _T("修改录像机请求发送失败") );
			}
		}
	}

	
	return TRUE;
}

void CVTRCfgLogic::SetVTRCfg()
{
	TVcrCfg tVTRCfg;
	if ( m_pVTRCtrlIF != NULL )
	{
		m_pVTRCtrlIF->GetUmsVTRData( tVTRCfg );
	}

	if ( tVTRCfg.m_byEqpID == 0 )
	{
		m_edtVTRName.SetWindowText( _T("") );
		m_edtVTRNo.SetWindowText( _T("") );
		m_ipVTRIP.SetWindowText( _T("") );
		return;
	}

	m_edtVTRName.SetWindowText( tVTRCfg.m_achName );

	char achVtrID[3];
	_itot( tVTRCfg.m_byEqpID, achVtrID, 10 );
	m_edtVTRNo.SetWindowText( achVtrID );
	m_ipVTRIP.SetAddress(ntohl( tVTRCfg.m_dwIP ));
}

bool CVTRCfgLogic::GetVTRCfg( TVcrCfg& tVTRCfg, TVcrCfg& tVTRCfgOld )
{
	CString strVTRName;
	CString strVTRNo;
	CString strVTRIp;
	m_edtVTRName.GetWindowText( strVTRName );
	m_edtVTRNo.GetWindowText( strVTRNo );
	m_ipVTRIP.GetWindowText( strVTRIp );
		

	s32 nRet = 0;
	CString strError;

	if ( !( strVTRName.IsEmpty() && strVTRNo.IsEmpty() && strVTRIp.IsEmpty() ) )
	{
		if ( strVTRName.IsEmpty() )
		{
			strError = "录像机名称不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtVTRName.SetFocus();
			return false;
		}
		
		if ( strVTRName.GetLength() > MAX_VTR_NAME_LENGTH-1 )
		{
			strError = "录像机名称长度超过31";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtVTRName.SetFocus();
			return false;
		}
		strncpy( tVTRCfg.m_achName, strVTRName, MAX_VTR_NAME_LENGTH );
		
		
		if ( strVTRNo.IsEmpty() )
		{
			strError = "录像机编号不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtVTRNo.SetFocus();
			return false;
		}
		
		int nVTRNo = _ttoi( strVTRNo );
		if ( nVTRNo < 17 || nVTRNo > 32 )
		{
			strError = "录像机编号超出范围:17-32";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_edtVTRNo.SetFocus();
			return false;
		}

		vector<TVcrCfg> vecTVcrCfg;
		m_pVTRCtrlIF->GetUmsVTRData( vecTVcrCfg );
		vector<TVcrCfg>::iterator it = vecTVcrCfg.begin();
		for ( ; it != vecTVcrCfg.end(); it++ )
		{
			if ( it->m_byEqpID == tVTRCfgOld.m_byEqpID )
			{
				continue;
			}
			if ( it->m_byEqpID == nVTRNo )
			{
				strError = "录像机编号已被占用2";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				m_edtVTRNo.SetFocus();
				return false;
			}
		}
		tVTRCfg.m_byEqpID = nVTRNo;
		
		
		if ( strVTRIp.IsEmpty() )
		{
			strError = "录像机地址不能为空";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipVTRIP.SetFocus();
			return false;
		}
		
		u32_ip dwVtrIp = inet_addr((LPCTSTR)strVTRIp);
		
		if ( !CCallAddr::IsValidIpV4( dwVtrIp ) ) 
		{
			strError = "录像机地址无效";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			m_ipVTRIP.SetFocus();
			return false;
		}
		tVTRCfg.m_dwIP = dwVtrIp;
	}

	return true;
}

LRESULT CVTRCfgLogic::OnVtrNty(WPARAM wParam, LPARAM lParam)
{
	SetVTRCfg();
	return S_OK;
}

LRESULT CVTRCfgLogic::OnAddVtrRsp(WPARAM wParam, LPARAM lParam)
{
	EmModifyVcrRet emRet = static_cast<EmModifyVcrRet>(wParam);

	UpdateTip(emRet);
	SetVTRCfg();

	return S_OK;
}

LRESULT CVTRCfgLogic::OnDelVtrRsp(WPARAM wParam, LPARAM lParam)
{
	EmModifyVcrRet emRet = static_cast<EmModifyVcrRet>(wParam);

	UpdateTip(emRet);
	SetVTRCfg();
	
	return S_OK;
}

LRESULT CVTRCfgLogic::OnMdyVtrRsp(WPARAM wParam, LPARAM lParam)
{
	EmModifyVcrRet emRet = static_cast<EmModifyVcrRet>(wParam);

	UpdateTip(emRet);
	SetVTRCfg();
	
	return S_OK;
}

void CVTRCfgLogic::UpdateTip( EmModifyVcrRet emRet )
{
	switch ( emRet )
	{
	case em_vcr_modify_success:
		{
			break;
		}
	case em_vcr_invalid:
		{
			MESSAGEWND("录像机无效");
			break;
		}
	case em_vcr_full:
		{
			MESSAGEWND("录像机已满");
			break;
		}
	case em_vcr_no_exist:
		{
			MESSAGEWND("录像机不存在");
			break;
		}
	case em_vcr_exist:
		{
			MESSAGEWND("录像机已存在");
			break;
		}
	default:
		break;
	}
}

void CVTRCfgLogic::OnDestroy()
{
	CDlgChild::OnDestroy();
}

void CVTRCfgLogic::FreshNMInfo()
{
	SetVTRCfg();
}