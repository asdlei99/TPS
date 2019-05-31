// vtrlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "vtrlogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

/////////////////////////////////////////////////////////////////////////////
// CVTRLogic dialog


CVTRLogic::CVTRLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CVTRLogic::IDD, pParent)
{
	m_pVTRSetLogic = NULL;
	m_pVedioFileListLogic = NULL;
	m_pVedioRecordLogic = NULL;
	m_pCurrentCwd = NULL;
	m_pVTRCtrlIF = NULL;
	m_bShowMosaicHoriImg = TRUE;
	m_bIsSegment = TRUE;
	m_nSegmentLen = 690*CUR_SCREEN_WIDTH_PER;
}


void CVTRLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVTRLogic)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVTRLogic, CDlgChild)
	//{{AFX_MSG_MAP(CVTRLogic)

	//baseinfo
	ON_MESSAGE( UI_UMSTOOL_REC_BASE_INFO_NTY,  CVTRLogic::OnRecBaseInfoNty )

	//filelist
	ON_MESSAGE( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, CVTRLogic::OnRecFileListInfoNty )
	ON_MESSAGE( UI_UMSTOOL_REC_MDY_FILE_RSP, CVTRLogic::OnRecMdyFileRsp )	
	ON_MESSAGE( UI_UMSTOOL_REC_DEL_FILE_RSP, CVTRLogic::OnRecDelFileRsp )

	//record
	ON_MESSAGE( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, CVTRLogic::OnRecConfRecInfoNty )
	ON_MESSAGE( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, CVTRLogic::OnRecConfPlayInfoNty )
//	ON_MESSAGE( UI_UMS_REFRESH_CONF_LIST, CVTRLogic::OnRefreshConfListNty )
	ON_MESSAGE( UI_UMSTOOL_REC_START_CONF_RSP, CVTRLogic::OnRecStartConfRsp )
	ON_MESSAGE( UI_UMSTOOL_REC_STOP_CONF_RSP, CVTRLogic::OnRecStopRecordRsp )
	ON_MESSAGE( UI_UMSTOOL_REC_PAUSE_CONF_RSP, CVTRLogic::OnRecPauseRecordRsp )
	ON_MESSAGE( UI_UMSTOOL_REC_RESUME_CONF_RSP, CVTRLogic::OnRecResumeRecordRsp )
	ON_MESSAGE( UI_UMSTOOL_START_PLAY_RSP, OnRecStartPlayRsp )
	ON_MESSAGE( UI_UMSTOOL_RESUME_PLAY_RSP, OnRecResumePlayRsp )
	ON_MESSAGE( UI_UMSTOOL_PAUSE_PLAY_RSP, OnRecPausePlayRsp )
	ON_MESSAGE( UI_UMSTOOL_STOP_PLAY_RSP, OnRecStopPlayRsp )

	//vtrcfg
	ON_MESSAGE( UI_UMSTOOL_VTR_NTY, CVTRLogic::OnVtrNty )
	ON_MESSAGE( UI_UMSTOOL_ADD_VTR_RSP, CVTRLogic::OnAddVtrRsp )
	ON_MESSAGE( UI_UMSTOOL_DEL_VTR_RSP, CVTRLogic::OnDelVtrRsp )
	ON_MESSAGE( UI_UMSTOOL_MODIFY_VTR_RSP, CVTRLogic::OnMdyVtrRsp )

	ON_MESSAGE( MSG_UI_VTR_TAB_CHANGE, CVTRLogic::OnTabChange )


	ON_MESSAGE( UI_UMSTOOL_VTR_REG_STATE_NTY,  OnVtrRegStateNty )
	ON_MESSAGE( UI_UMSTOOL_REC_MT_FORMAT_RSP,  OnRecMtFormatRsp )
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVTRLogic message handlers
BOOL CVTRLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	if( !InitChildWindow() )
	{
		return FALSE;
	}

	if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
		m_pVTRCtrlIF->SetNotifyWnd( this->m_hWnd );
    }
	
	return TRUE;
}

void CVTRLogic::InitDlg()
{   
	ShowWindow(SW_HIDE);

    //初始化子功能页面
	if ( m_pVTRSetLogic->GetSafeHwnd() )
	{
		m_pVTRSetLogic->InitDlg();
	}

	if ( m_pVedioFileListLogic->GetSafeHwnd() )
	{
		m_pVedioFileListLogic->InitDlg();
	}
	if ( m_pVedioRecordLogic->GetSafeHwnd() )
	{
		m_pVedioRecordLogic->InitDlg();
	}

	m_pCurrentCwd = m_pVTRSetLogic;
}

void CVTRLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();
	
	if ( m_pVTRSetLogic->GetSafeHwnd() )
	{
		m_pVTRSetLogic->DestroyWindow();
		SAFE_RELEASE(m_pVTRSetLogic);
	}
	
	if ( m_pVedioFileListLogic->GetSafeHwnd() )
	{
		m_pVedioFileListLogic->DestroyWindow();
		SAFE_RELEASE(m_pVedioFileListLogic);
	}

	if ( m_pVedioRecordLogic->GetSafeHwnd() )
	{
		m_pVedioRecordLogic->DestroyWindow();
		SAFE_RELEASE(m_pVedioRecordLogic);
	}
}


BOOL CVTRLogic::InitChildWindow()
{
	try
	{
		if ( m_pVTRSetLogic == NULL )
		{
			m_pVTRSetLogic = new CVTRSetLogic;
			m_pVTRSetLogic->Create( IDD_DIALOG_VTRSET, this); 
			m_pVTRSetLogic->SetWindowPos( NULL, 0, 0, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW);
			m_pCurrentCwd = m_pVTRSetLogic;
		}

		if ( m_pVedioFileListLogic == NULL)
		{
			m_pVedioFileListLogic = new CVedioFileListLogic;
			m_pVedioFileListLogic->Create( IDD_DIALOG_VIDEOFILELIST, this); 
			m_pVedioFileListLogic->SetWindowPos( NULL, 0, 0, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW);
		}

		if ( m_pVedioRecordLogic == NULL)
		{
			m_pVedioRecordLogic = new CVedioRecordLogic;
			m_pVedioRecordLogic->Create( IDD_DIALOG_VIDEORECORD, this); 
			m_pVedioRecordLogic->SetWindowPos( NULL, 0, 0, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW);
		}
		
		return TRUE;
	}
	catch (CException* e)
	{
		s8 chErr[1024];
		memset( chErr, 0, 1024 );
		e->GetErrorMessage( chErr,1024 );
		CString strErr;
		strErr += "文件操作失败，错误码";
		strErr += chErr;
		MESSAGEWND( strErr );
		return FALSE;
	}
}

BOOL CVTRLogic::ShowWindow( int nCmdShow )
{
	BOOL bRet = CDlgChild::ShowWindow( nCmdShow );

	return bRet;
}

void CVTRLogic::ShowActiveWindow( EM_CURRENT_WND_VIEW_TYPE emWndType )
{	
	BOOL bShowFlag = FALSE;
	CWnd* pWndNew = NULL;

	CWnd* pWndMain = AfxGetMainWnd();
	
	switch( emWndType )
	{
	case em_WND_VTRSET:	
		{
			if( m_pCurrentCwd != NULL )
			{
				bShowFlag = ( m_pCurrentCwd->GetSafeHwnd() == m_pVTRSetLogic->GetSafeHwnd() )?FALSE:TRUE;			}
			else
			{
				bShowFlag = TRUE;
			}
			pWndNew = m_pVTRSetLogic;
		}
		break;
	case em_WND_VEDIOFILELIST:
		{
			if( m_pCurrentCwd != NULL )
			{
				bShowFlag = ( m_pCurrentCwd->GetSafeHwnd() == m_pVedioFileListLogic->GetSafeHwnd() )?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			pWndNew = m_pVedioFileListLogic;
		}
		break;
	case em_WND_VEDIORECORD:
		{
			if( m_pCurrentCwd != NULL )
			{
				bShowFlag = ( m_pCurrentCwd->GetSafeHwnd() == m_pVedioRecordLogic->GetSafeHwnd() )?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			pWndNew = m_pVedioRecordLogic;
		}
		break;
	default:
		break;
	}
	
	if( bShowFlag )
	{
		if( m_pCurrentCwd != NULL )
		{
			m_pCurrentCwd->ShowWindow(FALSE); //hide the previous window 
		}
		
		if( pWndNew != NULL )
		{
			pWndNew->ShowWindow(SW_SHOW);  //show the current window 
			m_pCurrentCwd = pWndNew;
		}
	}
}

LRESULT CVTRLogic::OnTabChange(WPARAM wParam, LPARAM lParam)
{
	EM_CURRENT_WND_VIEW_TYPE emWndType = static_cast<EM_CURRENT_WND_VIEW_TYPE>(wParam);
	ShowActiveWindow( emWndType );

	return S_OK;
}

LRESULT CVTRLogic::OnRecBaseInfoNty( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_BASE_INFO_NTY, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecFileListInfoNty( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecMdyFileRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_MDY_FILE_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecDelFileRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_DEL_FILE_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecConfRecInfoNty( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecConfPlayInfoNty( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRefreshConfListNty( WPARAM wparam, LPARAM lparam )
{
//	CMsgHandle::SendMessage( UI_UMS_REFRESH_CONF_LIST, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecStartConfRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_START_CONF_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecStopRecordRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_STOP_CONF_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecPauseRecordRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_PAUSE_CONF_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecResumeRecordRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_RESUME_CONF_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecStartPlayRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_START_PLAY_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecStopPlayRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_STOP_PLAY_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecPausePlayRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_PAUSE_PLAY_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecResumePlayRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_RESUME_PLAY_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnVtrNty( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_VTR_NTY, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnAddVtrRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_ADD_VTR_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnDelVtrRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_DEL_VTR_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnMdyVtrRsp( WPARAM wparam, LPARAM lparam )
{
	CMsgHandle::SendMessage( UI_UMSTOOL_MODIFY_VTR_RSP, wparam, lparam );
	return S_OK;
}

LRESULT CVTRLogic::OnVtrRegStateNty(WPARAM wParam, LPARAM lParam)
{
	CMsgHandle::SendMessage( UI_UMSTOOL_VTR_REG_STATE_NTY, wParam, lParam );
	return S_OK;
}

LRESULT CVTRLogic::OnRecMtFormatRsp(WPARAM wParam, LPARAM lParam)
{
	CMsgHandle::SendMessage( UI_UMSTOOL_REC_MT_FORMAT_RSP, wParam, lParam );
	return S_OK;
}