// vediorecordnameeditlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "vediorecordnameeditlogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVedioRecordNameEditLogic dialog
CVedioRecordNameEditLogic * CVedioRecordNameEditLogic::m_pDlg = NULL;


CVedioRecordNameEditLogic::CVedioRecordNameEditLogic(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CVedioRecordNameEditLogic::IDD, pParent)
{
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
	m_pVTRCtrlIF = NULL;
}

CVedioRecordNameEditLogic::CVedioRecordNameEditLogic( TRecConfInfo tRecConfInfo, CWnd* pParent /*= NULL*/ )
: CTransparentBaseDlg(CVedioRecordNameEditLogic::IDD, pParent)
{
	m_tRecConfInfo = tRecConfInfo;
	m_dwBkResourceID = IDR_PNG_POPWND_BK_BIG;
	m_pVTRCtrlIF = NULL;
}

void CVedioRecordNameEditLogic::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVedioRecordNameEditLogic)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATIC_RECORD_NAME, m_stcRecordName);
	DDX_Control(pDX, IDC_EDIT_RECORD_NAME, m_edtRecordName);
	DDX_Control(pDX, IDC_STATIC_EDIT_RECORD_NAME, m_stcEditRecordName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVedioRecordNameEditLogic, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CVedioRecordNameEditLogic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVedioRecordNameEditLogic message handlers
BOOL CVedioRecordNameEditLogic::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();
	
	this->SetWindowText("VideoRecordNameEdit");
	
	CRect rectClient( 0, 0, 790, 255 );
    this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_HIDEWINDOW );
	AfxGetMainWnd()->CenterWindow();
	
	m_stcEditRecordName.SetWindowPos( NULL, 0,  11, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stcEditRecordName.SetWindowText("编辑录像名称");
	m_stcEditRecordName.SetTextAlign(StringAlignmentCenter);
	m_stcEditRecordName.SetTextColor(Color( 255, 255, 255 ));
	m_stcEditRecordName.SetFont( 13, "微软雅黑" );
	
	m_btnOk.SetImage( IDR_PNG_POPWND_BTN_SAVE, IDR_PNG_POPWND_BTN_SAVEDOWN, IDR_PNG_POPWND_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_POPWND_BTN_CANCLE, IDR_PNG_POPWND_BTN_CANCLEDOWN, IDR_PNG_POPWND_BTN_CANCLE );
	
	m_btnCancel.SetWindowPos( NULL, rectClient.right - 5 - m_btnCancel.GetImageSize().cx, 4, m_btnCancel.GetImageSize().cx, m_btnCancel.GetImageSize().cy, SWP_SHOWWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	m_btnOk.SetWindowPos( NULL, rectClient.left - 4 - m_btnCancel.GetImageSize().cx, 4, m_btnOk.GetImageSize().cx, m_btnOk.GetImageSize().cy, SWP_SHOWWINDOW );
	
	m_stcRecordName.SetWindowPos( NULL, 34,  126, 100, 20, SWP_SHOWWINDOW );
	m_stcRecordName.SetWindowText("录像名称");
	m_stcRecordName.SetTextColor(Color( 46, 55, 76 ));
	m_stcRecordName.SetFont( 13, "微软雅黑" );
	
	CUmcwebCommon::SetImgForTransEdit(&m_edtRecordName);
	m_stcRecordName.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);
	m_edtRecordName.SetWindowPos( NULL, 130, rectClient.bottom - rectClient.Height() - rectClient.Height()/2, 623 , 41, SWP_SHOWWINDOW );
	m_edtRecordName.SetFont( 13, "微软雅黑" );
	m_edtRecordName.SetLimitLength(32);
	m_edtRecordName.SetWindowText("未命名");
	m_edtRecordName.SetSel( 0, -1 );

	if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
    }
	
	return TRUE; 
}

void CVedioRecordNameEditLogic::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CVedioRecordNameEditLogic::OnOK() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}
	
	CString strRecordName;
	bool bGet = GetRecordName( strRecordName );
	if ( bGet == false )
	{
		m_edtRecordName.SetFocus();
		m_edtRecordName.SetSel( 0, -1 );
		return;
	}
	

	strncpy( m_tRecConfInfo.m_achFileName, strRecordName, TP_REC_FILE_LEN-1 );
	u16 nRet = m_pVTRCtrlIF->RecStartConfReq( m_tRecConfInfo );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("开始录像请求发送失败") );
	}

	CDialog::OnOK();
}

bool CVedioRecordNameEditLogic::GetRecordName( CString& strRecordName )
{
	CString strClientName;
	m_edtRecordName.GetWindowText( strClientName );

	CString strError;
	int nRet = 0;

	if ( strClientName.IsEmpty() )
	{
		strError = "录像名称不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		m_edtRecordName.SetFocus();
		return false;
	}	

	
	if ( strClientName.GetLength() > MAX_VTR_FILE_LIST_SIZE )
	{
		strError.Format(  "录像名称超过最大长度：%d", MAX_VTR_FILE_LIST_SIZE );
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		m_edtRecordName.SetFocus();
		return false;
	}

	if (  strClientName.Find( '*') != -1 || strClientName.Find( '?') != -1 || strClientName.Find( '"') != -1
		|| strClientName.Find( '<') != -1 || strClientName.Find( '>') != -1 || strClientName.Find( '|') != -1 
		|| strClientName.Find( '\/' ) != -1 || strClientName.Find( '\\') != -1 || strClientName.Find( ':') != -1
		|| strClientName.Find( '_' ) != -1 || strClientName.Find( '+' ) != -1  )
	{
		strError = "录像名称不可以包含空格及括号中的任意字符[* ? \" < > | / \ : _ +]";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		m_edtRecordName.SetFocus();
		return false;
	}

	vector<TRecFileInfo> vecTVtrFileInfoNoSuffix;
	m_pVTRCtrlIF->GetRecFileListInfoNoSuffix(vecTVtrFileInfoNoSuffix);
	vector<TRecFileInfo>::iterator it = vecTVtrFileInfoNoSuffix.begin();
	for ( ; it != vecTVtrFileInfoNoSuffix.end(); it++ )
	{
		
		CString strRecNameExist = it->m_szFilelName;
		if ( strClientName == strRecNameExist )
		{
			strError = "录像名称重名，不能录像";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return false;
		}
	}

	
	////////////////////////////////录制格式
	//视频格式
	AddElement( strRecordName, "A", m_tRecConfInfo.m_tConfRecInfo.m_tConfFormat.m_emFormat );


	//H.264画质级别
	AddElement( strRecordName, "B", m_tRecConfInfo.m_tConfRecInfo.m_tConfFormat.m_emQualityLvl );


	//帧率
	AddElement( strRecordName, "C", m_tRecConfInfo.m_tConfRecInfo.m_tConfFormat.m_wFrameRate );


	//视频分辨率
	AddElement( strRecordName, "D", m_tRecConfInfo.m_tConfRecInfo.m_tConfFormat.m_emRes );



	////////////////////////////////////双流格式
	//是否使用双流
	AddElement( strRecordName, "E", m_tRecConfInfo.m_bRecDual );
	
	//视频格式
	AddElement( strRecordName, "F", m_tRecConfInfo.m_tDualFormat.m_emFormat );
	
	
	//H.264画质级别
	AddElement( strRecordName, "G", m_tRecConfInfo.m_tDualFormat.m_emQualityLvl );
	
	
	//帧率
	AddElement( strRecordName, "H", m_tRecConfInfo.m_tDualFormat.m_wFrameRate );
	
	
	//视频分辨率
	AddElement( strRecordName, "I", m_tRecConfInfo.m_tDualFormat.m_emRes );


	strRecordName += strClientName;

	//文件名之后添加额外信息
	strRecordName += _T("_255_");
	
	//码率
	char achBright[6] = {0};
	itoa( m_tRecConfInfo.m_tConfRecInfo.m_tConfFormat.m_wBitrate, achBright, 10 );
	
	strRecordName += achBright;
	strRecordName += _T("k");

	return true;
}

void CVedioRecordNameEditLogic::ParseRecordName(CString strRecordName, TUmsVidFormat& tConfFormat, BOOL& bDual, TUmsVidFormat& tDualFormat)
{
	int nValue = -1;
	nValue = ParseElement( strRecordName, "A" );
	if ( nValue != -1 )
	{
		tConfFormat.m_emFormat = (EmTpVideoFormat)nValue;
	}

	nValue = ParseElement( strRecordName, "B" );
	if ( nValue != -1 )
	{
		tConfFormat.m_emQualityLvl = (EmTpVideoQualityLevel)nValue;
	}

	nValue = ParseElement( strRecordName, "C" );
	if ( nValue != -1 )
	{
		tConfFormat.m_wFrameRate = nValue;
	}

	nValue = ParseElement( strRecordName, "D" );
	if ( nValue != -1 )
	{
		tConfFormat.m_emRes = (EmTpVideoResolution)nValue;
	}


	nValue = ParseElement( strRecordName, "E" );
	if ( nValue != -1 )
	{
		bDual = nValue;
		if ( bDual == FALSE )
		{
			return;
		}
	}
	else
	{
		return;
	}

	nValue = ParseElement( strRecordName, "F" );
	if ( nValue != -1 )
	{
		tDualFormat.m_emFormat = (EmTpVideoFormat)nValue;
	}

	nValue = ParseElement( strRecordName, "G" );
	if ( nValue != -1 )
	{
		tDualFormat.m_emQualityLvl = (EmTpVideoQualityLevel)nValue;
	}

	nValue = ParseElement( strRecordName, "H" );
	if ( nValue != -1 )
	{
		tDualFormat.m_wFrameRate = nValue;
	}

	nValue = ParseElement( strRecordName, "I" );
	if ( nValue != -1 )
	{
		tDualFormat.m_emRes = (EmTpVideoResolution)nValue;
	}
}

void CVedioRecordNameEditLogic::AddElement( CString& strRecordName, CString strName, int nValue )
{
	//用+开始和+结束识别
	strRecordName = strRecordName + "+" + strName;
	
	char achValue[6] = {0};
	itoa( nValue, achValue, 10 );
	
	strRecordName += achValue;
	strRecordName += _T("+");
}

int CVedioRecordNameEditLogic::ParseElement( CString strRecordName, CString strName )
{
	int nPosBegin = -1;
	int nPosEnd = -1;
	int nLenth = 0;
	
	strName = "+" + strName;
	nPosBegin = strRecordName.Find( strName );
	if ( nPosBegin == -1 )
	{
		return -1;
	}

	nPosEnd = strRecordName.Find( '+', nPosBegin+1 );
	if ( nPosEnd == -1 )
	{
		return -1;
	}

	nLenth = strName.GetLength();
	
	CString strFormat;
	strFormat = strRecordName.Mid( nPosBegin+nLenth, nPosEnd-nPosBegin-nLenth );
	
	int nValue = atoi(strFormat);

	return nValue;
}

BOOL CVedioRecordNameEditLogic::IsExistElement( CString strRecordName )
{
	if ( strRecordName.Find('+') == -1 )
	{
		return FALSE;
	}
	
	return TRUE;
}