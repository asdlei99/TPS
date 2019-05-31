// RenameOptDlg.cpp: implementation of the CCRenameOptDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "renameOptDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCRenameOptDlg::CCRenameOptDlg()
:m_strRenameCombox("RenameOptDlg/ComboboxRenameNo")
,m_strRenameInfo("RenameOptDlg/EdtRenameInfo")
,m_emOldVideoSourceType(emTPVidEnd)
,m_emCurrentVideoSourceType(emTPVidEnd)
,m_emOldDisplaySourceType(emVgaTypeInValid)
,m_emCurrentDisplaySourceType(emVgaTypeInValid)
,m_nLastIndex(0)
{

}

CCRenameOptDlg::~CCRenameOptDlg()
{

}

void CCRenameOptDlg::RegMsg()
{
	CCRenameOptDlg *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_RenameVideoSource_Click, CCRenameOptDlg::OnRenameVideoSource, pThis, CCRenameOptDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_MSG_ReDisplaySrc_Click, CCRenameOptDlg::OnRenameDisplaySource, pThis, CCRenameOptDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_DCCAMERA_PreSet_Nty, CCRenameOptDlg::OnPreSet, pThis, CCRenameOptDlg );

	REG_MSG_HANDLER( UI_CNSTOOL_CurtainRename_Nty, CCRenameOptDlg::OnCurtainRename, pThis, CCRenameOptDlg );
}

void CCRenameOptDlg::RegCBFun()
{
	CCRenameOptDlg *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCRenameOptDlg::InitWnd", CCRenameOptDlg::InitWnd, pThis, CCRenameOptDlg);

	REG_GOBAL_MEMBER_FUNC( "CCRenameOptDlg::OnRenameIDChange", CCRenameOptDlg::OnRenameIDChange, pThis, CCRenameOptDlg);

	REG_GOBAL_MEMBER_FUNC( "CCRenameOptDlg::OnBtnOptMngOk", CCRenameOptDlg::OnBtnOptMngOk, pThis, CCRenameOptDlg);

	REG_GOBAL_MEMBER_FUNC( "CCRenameOptDlg::OnBtnOptMsgCancel", CCRenameOptDlg::OnBtnOptMsgCancel, pThis, CCRenameOptDlg);
}

void CCRenameOptDlg::UnRegFunc()
{
	
}

void CCRenameOptDlg::UnRegMsg()
{
	
}

bool CCRenameOptDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	UpBtnState();
	return true;
}

void CCRenameOptDlg::Clear()
{
	UIFACTORYMGR_PTR->Endmodal(0, g_strRenameOptDlg );
}

HRESULT CCRenameOptDlg::OnRenameVideoSource( WPARAM wparam, LPARAM lparam  )
{
	m_emRenameType = em_RENAME_VIDEOSOURCE;

	UIFACTORYMGR_PTR->LoadScheme( "SchDVIRenameModify", m_pWndTree );
	memcpy( m_atVideoSourceName,(TTPVideoSourceName * )wparam,sizeof(m_atVideoSourceName) );

	SetVideoSourceData();

	m_emOldVideoSourceType = emTPC1Vid ;
	m_emCurrentVideoSourceType = emTPC1Vid;
	return S_OK;
}

void CCRenameOptDlg::SetVideoSourceData()
{
	vector<CString> vecVideoSource;
	string strVideoSourceType;
	string strComboxText;
	string strEditText;

	strVideoSourceType = TransDefaultVideoSource( emTPC1Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());
	
	strVideoSourceType = TransDefaultVideoSource( emTPC2Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());
	
	strVideoSourceType = TransDefaultVideoSource( emTPC3Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());
	
	strVideoSourceType = TransDefaultVideoSource( emTPC4Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());
	
	strVideoSourceType = TransDefaultVideoSource( emTPC5Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());
	
	strVideoSourceType = TransDefaultVideoSource( emTPC6Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());

	strVideoSourceType = TransDefaultVideoSource( emTPC7Vid );
	vecVideoSource.push_back(strVideoSourceType.c_str());
	
	UIFACTORYMGR_PTR->SetComboListData( m_strRenameCombox, vecVideoSource, m_pWndTree );
	
	strComboxText = TransDefaultVideoSource( emTPC1Vid );
	strEditText = TransVideoSourceType( emTPC1Vid );
	UIFACTORYMGR_PTR->SetComboText(m_strRenameCombox, strComboxText, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strRenameInfo, strEditText );
}

HRESULT CCRenameOptDlg::OnRenameDisplaySource( WPARAM wparam, LPARAM lparam  )
{
	m_emRenameType = em_RENAME_DISPLAYDOURCE;
	UIFACTORYMGR_PTR->LoadScheme( "SchDisplayRenameModify", m_pWndTree );
	memcpy( m_atDisplaySourceInfo,(TVgaInfo * )wparam,sizeof(m_atDisplaySourceInfo) );

	if ( lparam == NULL )
	{
		SetDisplaySourceData();
		
		m_emOldDisplaySourceType = emVgaTypeDocCamera;
		m_emCurrentDisplaySourceType = emVgaTypeDocCamera;
	}
	else
	{
		TVgaInfo tVgaInfo = *(TVgaInfo *)lparam;
		string strDisplaySourceType;
		vector<CString> vecDiplaySource;
		string strComboxText;
		string strEditText;

		vecDiplaySource.clear();
		UIFACTORYMGR_PTR->SetComboListData( m_strRenameCombox, vecDiplaySource, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strRenameCombox, false, m_pWndTree );

		strComboxText = TransDefaultDisplaySource( tVgaInfo.m_emVgaType );
		UIFACTORYMGR_PTR->SetComboText(m_strRenameCombox, strComboxText, m_pWndTree );

		strEditText = TransDisplaySourceType(tVgaInfo.m_emVgaType);
		UIFACTORYMGR_PTR->SetCaption( m_strRenameInfo, strEditText );

		m_emOldDisplaySourceType = tVgaInfo.m_emVgaType;
		m_emCurrentDisplaySourceType = tVgaInfo.m_emVgaType;
	}
	
	return S_OK;
}

HRESULT CCRenameOptDlg::OnPreSet( WPARAM wparam, LPARAM lparam  )
{
	BOOL bSave = *(BOOL *)wparam;
	if ( bSave == TRUE )
	{
		m_emRenameType = em_SAVE_PRESET;
		UIFACTORYMGR_PTR->LoadScheme( "SchSavePreSet", m_pWndTree );
	}
	else
	{
		m_emRenameType = em_CALL_PRESET;
		UIFACTORYMGR_PTR->LoadScheme( "SchCallPreSet", m_pWndTree );
	}

	SetPreSetData();
	return S_OK;
}

HRESULT CCRenameOptDlg::OnCurtainRename( WPARAM wparam, LPARAM lparam  )
{
	m_emRenameType = em_RNAME_CURTAIN;
	m_nLastIndex = 0;
	CString strCurID;

	m_tCurtainInfo = *(TCentreCurInfo *)wparam;
	m_tOldCurtainInfo = m_tCurtainInfo;

	UIFACTORYMGR_PTR->LoadScheme( "SchCurtainRenameModify", m_pWndTree );

	vector<CString> vecCurtainName;

	if ( lparam != NULL )
	{
		m_nLastIndex = *(s32 *)lparam;
		vector<CString> vecCurtainName;
		
		vecCurtainName.clear();
		UIFACTORYMGR_PTR->SetComboListData( m_strRenameCombox, vecCurtainName, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strRenameCombox, false, m_pWndTree );

		strCurID.Format( "%d",m_nLastIndex+1);
		UIFACTORYMGR_PTR->SetComboText(m_strRenameCombox, strCurID.GetBuffer(strCurID.GetLength()-1), m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strRenameInfo, m_tCurtainInfo.tCenCurName[m_nLastIndex].achCurName );
	}
	else
	{
		for ( s32 nIndex = 0 ; nIndex < m_tCurtainInfo.byCurNum ; nIndex ++ )
		{
			strCurID.Format( "%d",nIndex+1);
			vecCurtainName.push_back( strCurID);
		}
		UIFACTORYMGR_PTR->SetComboListData( m_strRenameCombox, vecCurtainName, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText(m_strRenameCombox, "1", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strRenameInfo, m_tCurtainInfo.tCenCurName[0].achCurName );
	}
	return S_OK;
}


void CCRenameOptDlg::SetPreSetData()
{
	vector<CString> vecPreSet;
	vecPreSet.push_back("Ԥ��λ1");
	vecPreSet.push_back("Ԥ��λ2");
	vecPreSet.push_back("Ԥ��λ3");

	UIFACTORYMGR_PTR->SetComboListData( m_strRenameCombox, vecPreSet, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText(m_strRenameCombox, "Ԥ��λ1", m_pWndTree );
}

void CCRenameOptDlg::SetDisplaySourceData()
{
	string strDisplaySourceType;
	vector<CString> vecDiplaySource;
	string strComboxText;
	string strEditText;

	strDisplaySourceType = TransDefaultDisplaySource(emVgaTypeDocCamera);
	vecDiplaySource.push_back(strDisplaySourceType.c_str());
	
	strDisplaySourceType = TransDefaultDisplaySource(emVgaType001);
	vecDiplaySource.push_back(strDisplaySourceType.c_str());
	
	strDisplaySourceType = TransDefaultDisplaySource(emVgaType002);
	vecDiplaySource.push_back(strDisplaySourceType.c_str());
	
	strDisplaySourceType = TransDefaultDisplaySource(emVgaType003);
	vecDiplaySource.push_back(strDisplaySourceType.c_str());
	
	strDisplaySourceType = TransDefaultDisplaySource(emVgaTypeFullScreenCamera);
	vecDiplaySource.push_back(strDisplaySourceType.c_str());
	
	UIFACTORYMGR_PTR->SetComboListData( m_strRenameCombox, vecDiplaySource, m_pWndTree );
	
	strComboxText = TransDefaultDisplaySource( emVgaTypeDocCamera );
	strEditText = TransDisplaySourceType( emVgaTypeDocCamera );
	UIFACTORYMGR_PTR->SetComboText(m_strRenameCombox, strComboxText, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strRenameInfo, strEditText );
}

//��ű䶯
bool CCRenameOptDlg::OnRenameIDChange( const IArgs & arg )		
{
	if ( ( em_SAVE_PRESET == m_emRenameType) || ( em_CALL_PRESET == m_emRenameType ) )		//Ԥ��λ����ʱ�������κβ���
	{
		return true;
	}

//	bool bSuccess,bChange;
	String strOldRenameInfo;
	String strLastInfo;
/*	if ( bSuccess != true )
	{
		return false;
	}
*/
	UIFACTORYMGR_PTR->GetCaption( m_strRenameInfo, strOldRenameInfo, m_pWndTree);					//��ȡedit�е��ַ�����ָ��ǰһ��Combox������

	if ( CheckInfo( strOldRenameInfo ) == false )
	{
		strLastInfo= GetLastDefaultContext();
		UIFACTORYMGR_PTR->SetComboText( m_strRenameCombox, strLastInfo, m_pWndTree );				//���б��TEXT��Ϊ�ϴ�״̬
		
		UIFACTORYMGR_PTR->SetFocus( m_strRenameInfo, m_pWndTree );
		return false;
	}

	SaveContext( strOldRenameInfo );
	String strCurrentContext = 	GetCurrentText();

	UIFACTORYMGR_PTR->SetCaption( m_strRenameInfo, strCurrentContext, m_pWndTree);
	UpdateState();
	return true;
}

bool CCRenameOptDlg::OnBtnOptMngOk( const IArgs & arg )
{
	String strPreSet;

	if ( m_emRenameType == em_CALL_PRESET )
	{
		UIFACTORYMGR_PTR->GetComboText( m_strRenameCombox, strPreSet, m_pWndTree);

		EmDCamRecallNum emCallPreSet = GetCallPreSetType(strPreSet);
		if ( emCallPreSet != emDCamRecallInvalid )
		{
			u16 nRet = COMIFMGRPTR->SetDCamRecallCmd( emCallPreSet );
			if ( nRet != NO_ERROR )
			{
				WARNMESSAGE( "����Ԥ��λ������ʧ��" );
			}
		}
	}	
	else if ( m_emRenameType == em_SAVE_PRESET )
	{
		UIFACTORYMGR_PTR->GetComboText( m_strRenameCombox, strPreSet, m_pWndTree);
		
		EmDCamPresetNum emSavePreSet = GetSavePreSetType(strPreSet);
		if ( emSavePreSet != emDCamRecallInvalid )
		{
			u16 nRet = COMIFMGRPTR->SetDCamSavePresetCmd( emSavePreSet );
			if ( nRet != NO_ERROR )
			{
				WARNMESSAGE( "����Ԥ��λ������ʧ��" );
			}
		}
	}
	else
	{
		if ( onRenameOptDlg()  == false )
		{
			return false;
		}
	}

	UIFACTORYMGR_PTR->Endmodal(0, g_strRenameOptDlg );
	return true;
}

bool CCRenameOptDlg::onRenameOptDlg()
{
	String strOldRenameInfo;

	UIFACTORYMGR_PTR->GetCaption( m_strRenameInfo, strOldRenameInfo, m_pWndTree);
	if ( CheckInfo( strOldRenameInfo ) == false )
	{
		UIFACTORYMGR_PTR->SetFocus( m_strRenameInfo, m_pWndTree );
		return false;
	}

	SaveContext( strOldRenameInfo );
	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_UpdateVideoSource_Nty, (WPARAM)m_atVideoSourceName,NULL);
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		CMsgDispatch::SendMessage( ev_UiCnstoolRenameDisplaySourceNty, (WPARAM)m_atDisplaySourceInfo,NULL);
	}
	else if ( m_emRenameType == em_RNAME_CURTAIN )
	{
		for ( s32 nIndex = 0; nIndex < m_tCurtainInfo.byCurNum ; nIndex ++ )
		{
			if ( strcmp(m_tOldCurtainInfo.tCenCurName[nIndex].achCurName,m_tCurtainInfo.tCenCurName[nIndex].achCurName ) != 0 )
			{
				u16 nRet = COMIFMGRPTR->SetCurtainNameCmd( nIndex, m_tCurtainInfo.tCenCurName[nIndex]);
				
				if ( nRet != NO_ERROR )
				{
					WARNMESSAGE( "����������������ʧ��" );
					return false;
				}
			}
		}
	//	CMsgDispatch::SendMessage( UI_CNSTOOL_CENTRE_CurRename_Nty, (WPARAM)&m_tCurtainInfo,NULL);
	}

	return true;
}

bool CCRenameOptDlg::OnBtnOptMsgCancel( const IArgs & arg )
{
	memset( m_atVideoSourceName, 0, sizeof(m_atVideoSourceName) );
	memset( m_atDisplaySourceInfo, 0, sizeof(m_atDisplaySourceInfo) );

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_strRenameOptDlg );
	return true;
}

EmTPMtVideoPort CCRenameOptDlg::GetVideoSourceType( String strCtrl )
{
	for ( s32 nIndex =0; nIndex <= emTPC7Vid ;nIndex ++ )
	{
		if ( strcmp(strCtrl.c_str(),m_atVideoSourceName[nIndex].m_achSourceName ) == 0  )
		{
			return m_atVideoSourceName[nIndex].m_emPortType;
		}
	}
	return emTPVidEnd;
}

string CCRenameOptDlg::TransVideoSourceType( EmTPMtVideoPort emType )
{
	string strType= "";
	
	for ( s32 nIndex =0; nIndex <= emTPC7Vid ;nIndex ++ )
	{
		if ( m_atVideoSourceName[nIndex].m_emPortType == emType )
		{
			strType = m_atVideoSourceName[nIndex].m_achSourceName;
			break;
		}
	}
	
	return strType;
}

string CCRenameOptDlg::TransDefaultVideoSource( EmTPMtVideoPort emType )
{
	String strAudioSource;
	switch( emType )
	{
	case emTPC1Vid:
		strAudioSource = "����Ƶ1"; 
		break;
	case emTPC2Vid:
		strAudioSource = "����Ƶ1"; 
		break;
	case emTPC3Vid:
		strAudioSource = "����Ƶ2"; 
		break;
	case emTPC4Vid:
		strAudioSource = "����Ƶ2"; 
		break;
	case emTPC5Vid:
		strAudioSource = "����Ƶ3"; 
		break;
	case emTPC6Vid:
		strAudioSource = "����Ƶ3"; 
		break;
	case emTPC7Vid:
		strAudioSource = "ȫ�������"; 
		break;
	default:
		strAudioSource = "";
		break;	
	}
	return strAudioSource;
}

EmTPMtVideoPort CCRenameOptDlg::GetDefaultVideoSource( string strVideoSource )
{
	if (strVideoSource.find( "����Ƶ1", 0 ) != string::npos )
	{
		return emTPC1Vid;
	}
	else if (strVideoSource.find( "����Ƶ1", 0 ) != string::npos )
	{
		return emTPC2Vid;
	}
	else if (strVideoSource.find( "����Ƶ2", 0 ) != string::npos )
	{
		return emTPC3Vid;
	}
	else if (strVideoSource.find( "����Ƶ2", 0 ) != string::npos )
	{
		return emTPC4Vid;
	}
	else if (strVideoSource.find( "����Ƶ3", 0 ) != string::npos )
	{
		return emTPC5Vid;
	}
	else if (strVideoSource.find( "����Ƶ3", 0 ) != string::npos )
	{
		return emTPC6Vid;
	}
	else if ( strcmp(strVideoSource.c_str(),"ȫ�������") == 0 )
	{
		return emTPC7Vid;
	}
	else
	{
		return emTPVidEnd;
	}
}

string CCRenameOptDlg::TransDisplaySourceType( EmVgaType emType )
{
	string strType;
	
	for ( s32 nIndex =0; nIndex < emVgaTypeInValid ;nIndex ++ )
	{
		if ( m_atDisplaySourceInfo[nIndex].m_emVgaType == emType )
		{
			strType = m_atDisplaySourceInfo[nIndex].m_achAlias;
			break;
		}
	}
	
	return strType;
}

EmVgaType CCRenameOptDlg::GetDisplaySourceType( String strCtrl )
{
	for ( s32 nIndex =0; nIndex < emVgaTypeInValid ;nIndex ++ )
	{
		if ( strcmp(strCtrl.c_str(),m_atDisplaySourceInfo[nIndex].m_achAlias) == 0  )
		{
			return m_atDisplaySourceInfo[nIndex].m_emVgaType;
		}
	}
	return emVgaTypeInValid;
}

string CCRenameOptDlg::TransDefaultDisplaySource( EmVgaType emType )
{
	String strAudioSource;
	switch( emType )
	{
	case emVgaTypeFullScreenCamera:
		strAudioSource = "ȫ�������"; 
		break;
	case emVgaType001:
		strAudioSource = "��ʾԴ 1"; 
		break;
	case emVgaType002:
		strAudioSource = "��ʾԴ 2"; 
		break;
	case emVgaType003:
		strAudioSource = "��ʾԴ 3"; 
		break;
	case emVgaTypeDocCamera:
		strAudioSource = "�ĵ������"; 
		break;
	default:
		strAudioSource = "";
		break;	
	}
	return strAudioSource;
}

EmVgaType CCRenameOptDlg::GetDefaultDisplaySource( string strDisplaySource )
{
	if (strDisplaySource.find( "ȫ�������", 0 ) != string::npos )
	{
		return emVgaTypeFullScreenCamera;
	}
	else if (strDisplaySource.find( "��ʾԴ 1", 0 ) != string::npos )
	{
		return emVgaType001;
	}
	else if (strDisplaySource.find( "��ʾԴ 2", 0 ) != string::npos )
	{
		return emVgaType002;
	}
	else if (strDisplaySource.find( "��ʾԴ 3", 0 ) != string::npos )
	{
		return emVgaType003;
	}
	else if (strDisplaySource.find( "�ĵ������", 0 ) != string::npos )
	{
		return emVgaTypeDocCamera;
	}
	else
	{
		return emVgaTypeInValid;
	}
}

bool CCRenameOptDlg::IsExist( String strRenameInfo )
{
	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		for ( s32 nIndex = 0; nIndex <= emTPC7Vid; nIndex ++ )
		{
			if ( m_atVideoSourceName[nIndex].m_emPortType == m_emOldVideoSourceType )
			{
				continue;
			}
			
			if ( strcmp(strRenameInfo.c_str(),m_atVideoSourceName[nIndex].m_achSourceName ) == 0 )
			{
				return true;
			}
		}
		return false;
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		for ( s32 nIndex = 0; nIndex < emVgaTypeInValid; nIndex ++ )
		{
			if ( m_atDisplaySourceInfo[nIndex].m_emVgaType == m_emOldDisplaySourceType )
			{
				continue;
			}
			
			if ( strcmp(strRenameInfo.c_str(),m_atDisplaySourceInfo[nIndex].m_achAlias ) == 0 )
			{
				return true;
			}
		}
		return false;
	}
	else if ( m_emRenameType == em_RNAME_CURTAIN )
	{
		for ( s32 nIndex = 0; nIndex < m_tCurtainInfo.byCurNum; nIndex ++ )
		{
			if ( nIndex == m_nLastIndex )
			{
				continue;
			}
			
			if ( strcmp( m_tCurtainInfo.tCenCurName[nIndex].achCurName,strRenameInfo.c_str() ) == 0 )
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

bool CCRenameOptDlg::IsVisible( String strOldRenameInfo )
{
	for ( String::size_type nIndex = 0; nIndex < strOldRenameInfo.size(); nIndex ++ )
	{
		if ( !isspace( strOldRenameInfo[nIndex]) )
		{
			return true;
		}
	}
	return false;
}

bool CCRenameOptDlg::CheckInfo( String strRenameInfo )
{
	bool   bSuccess = false;
	String strMessageData;

	if ( strRenameInfo.size() == 0 )
	{
		bSuccess = false;
		strMessageData = "���Ʋ���Ϊ��";
	}
/*	else if ( IsVisible(strRenameInfo) == false )
	{
		bSuccess = false;
		strMessageData = "���Ʋ��ܶ�Ϊ���ɼ��ַ�";
	}*/
	else if ( IsExist(strRenameInfo) == true )
	{
		bSuccess = false;
		strMessageData = "�������Ѿ�����";
	}
	else
	{
		bSuccess = true;
	}

	if ( bSuccess == false )
	{
		MSG_BOX_OK( strMessageData );
	}

	return bSuccess;
}

String CCRenameOptDlg::GetLastDefaultContext()
{
	String strInfo;
	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		strInfo = TransDefaultVideoSource(m_emOldVideoSourceType);
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		strInfo = TransDefaultDisplaySource(m_emOldDisplaySourceType);
	}
	else if ( m_emRenameType == em_RNAME_CURTAIN )
	{
		s8  chNumber[2] = "";
		itoa(m_nLastIndex+1,chNumber,10);

		strInfo = chNumber;
	}
	else
	{
		strInfo = "";
	}
	return strInfo;
}

bool CCRenameOptDlg::GetType( String strContext )
{
	bool bSuccess = false;
	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		m_emCurrentVideoSourceType = GetVideoSourceType( strContext );
		bSuccess = true;
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		m_emCurrentDisplaySourceType = GetDisplaySourceType( strContext );
		bSuccess = true;
	}
	return bSuccess;
}

String CCRenameOptDlg::GetCurrentText( )
{
	String strCurRenameInfo;
	String strCurrentContext;
	UIFACTORYMGR_PTR->GetComboText( m_strRenameCombox, strCurRenameInfo, m_pWndTree );			//��ȡCOMBOBOX��ʾ������

	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )												//ת��Ϊ��Ӧ��ʶ
	{
		m_emCurrentVideoSourceType = GetDefaultVideoSource( strCurRenameInfo );	
		
		strCurrentContext = TransVideoSourceType(m_emCurrentVideoSourceType);					//����ǰ������ת��Ϊ�޸����е��ַ���
		//		bSuccess = true;
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		m_emCurrentDisplaySourceType = GetDefaultDisplaySource( strCurRenameInfo );
		
		strCurrentContext = TransDisplaySourceType(m_emCurrentDisplaySourceType);
		//	bSuccess = true;
	}
	else if ( m_emRenameType == em_RNAME_CURTAIN )
	{
		string strCurNum;
		
		UIFACTORYMGR_PTR->GetComboText( m_strRenameCombox, strCurNum, m_pWndTree);
		s32 nIndex = atoi(strCurNum.c_str()) - 1;
		if ( nIndex < m_tCurtainInfo.byCurNum )
		{
			strCurrentContext = m_tCurtainInfo.tCenCurName[nIndex].achCurName;
		}
	}
	
	return strCurrentContext;
}

/*
bool CCRenameOptDlg::IsChange( )
{
	bool bChange = false;

	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		if ( m_emCurrentVideoSourceType != m_emOldVideoSourceType )
		{
			bChange = true;
		}
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		if ( m_emCurrentDisplaySourceType != m_emOldDisplaySourceType )
		{
			bChange = true;
		}
	}
	return bChange;
}
*/
void CCRenameOptDlg::SaveContext( String strLastRenameInfo )
{
	s32 nIndex;
	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		for ( nIndex = 0; nIndex <= emTPC7Vid; nIndex ++ )											//����EDIT�е�����
		{
			if ( m_atVideoSourceName[nIndex].m_emPortType == m_emOldVideoSourceType )					
			{
				memset(m_atVideoSourceName[nIndex].m_achSourceName,0,sizeof(m_atVideoSourceName[nIndex].m_achSourceName));
				memcpy(m_atVideoSourceName[nIndex].m_achSourceName,strLastRenameInfo.c_str(),strLastRenameInfo.size());
				break;
			}
		}
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		for ( nIndex = 0; nIndex < emVgaTypeInValid; nIndex ++ )											//����EDIT�е�����
		{
			if ( m_atDisplaySourceInfo[nIndex].m_emVgaType == m_emOldDisplaySourceType )					
			{
				memset(m_atDisplaySourceInfo[nIndex].m_achAlias,0,sizeof(m_atDisplaySourceInfo[nIndex].m_achAlias));
				memcpy(m_atDisplaySourceInfo[nIndex].m_achAlias,strLastRenameInfo.c_str(),strLastRenameInfo.size());
				break;
			}
		}
	}
	else if ( m_emRenameType == em_RNAME_CURTAIN )
	{
		memset(m_tCurtainInfo.tCenCurName[m_nLastIndex].achCurName,0,sizeof(m_tCurtainInfo.tCenCurName[m_nLastIndex].achCurName));
		memcpy(m_tCurtainInfo.tCenCurName[m_nLastIndex].achCurName,strLastRenameInfo.c_str(),strLastRenameInfo.size());
	}
}

void CCRenameOptDlg::UpdateState()
{
	if ( m_emRenameType == em_RENAME_VIDEOSOURCE )
	{
		m_emOldVideoSourceType = m_emCurrentVideoSourceType;
	}
	else if ( m_emRenameType == em_RENAME_DISPLAYDOURCE )
	{
		m_emOldDisplaySourceType = m_emCurrentDisplaySourceType;
	}
	else if ( m_emRenameType == em_RNAME_CURTAIN )
	{
		string strCurNum;

		UIFACTORYMGR_PTR->GetComboText( m_strRenameCombox, strCurNum, m_pWndTree);
		m_nLastIndex = atoi(strCurNum.c_str()) - 1;
	}
}

EmDCamRecallNum CCRenameOptDlg::GetCallPreSetType( string strDCamCallPreSet )
{
	if ( strcmp(strDCamCallPreSet.c_str(),"Ԥ��λ1") == 0 )
	{
		return emDCamRecallOne;
	}
	else if ( strcmp(strDCamCallPreSet.c_str(),"Ԥ��λ2") == 0 )
	{
		return emDCamRecallTwo;
	}
	else if ( strcmp(strDCamCallPreSet.c_str(),"Ԥ��λ3") == 0 )
	{
		return emDCamRecallThree;
	}
	else
	{
		return emDCamRecallInvalid;
	}
}

EmDCamPresetNum CCRenameOptDlg::GetSavePreSetType( string strDCamCallPreSet )
{
	if ( strcmp(strDCamCallPreSet.c_str(),"Ԥ��λ1") == 0 )
	{
		return emDCamPresetOne;
	}
	else if ( strcmp(strDCamCallPreSet.c_str(),"Ԥ��λ2") == 0 )
	{
		return emDCamPresetTwo;
	}
	else if ( strcmp(strDCamCallPreSet.c_str(),"Ԥ��λ3") == 0 )
	{
		return emDCamPresetThree;
	}
	else
	{
		return emDCamPresetInvalid;
	}
}