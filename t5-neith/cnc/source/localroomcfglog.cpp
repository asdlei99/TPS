#include "StdAfx.h"
#include "localroomcfglog.h"
#include "confmsglogic.h"
#include "messageboxlogic.h"

APP_BEGIN_MSG_MAP(CLocalRoomCfgLogic,CNotifyUIImpl)
MSG_CREATEWINDOW(_T("RoomCtrlLayout"), OnCreate)
	MSG_INIWINDOW(_T("RoomCtrlLayout"), OnInit)

	MSG_CLICK(_T("BtnCancleLogo"), OnBtnCancleLogo)
	MSG_CLICK(_T("BtnSaveLogo"), OnBtnSaveLogo)

	MSG_CLICK(_T("BtnCancleBanner"), OnBtnCancleBanner)
	MSG_CLICK(_T("BtnSaveBanner"), OnBtnSaveBanner)
	
	MSG_CLICK(_T("BtnOk"), OnBtnSave)
	MSG_CLICK(_T("BtnFixOrCancel"), OnBtnFixOrCancel)

	MSG_SELECTCHANGE(_T("CheckScreen"), OnCheckScreenSel)

	MSG_SELECTCHANGE(_T("CheckIsNAT"), OnCheckIsNAT) 

    MSG_SELECTCHANGE(_T("opSetIPv4"), OnCheckIPv4Sel)
    MSG_SELECTCHANGE(_T("opSetIPv6"), OnCheckIPv6Sel)

	MSG_SELECTCHANGE(_T("logo"), OnTabLogo)
	MSG_SELECTCHANGE(_T("banner"), OnTabBanner)
	MSG_SELECTCHANGE(_T("confparameter"), OnTabParam)

	MSG_ITEMSELECTD(_T("ConfScreenLogoList"), OnScreenLogoItemClick)
	MSG_ITEMSELECTD(_T("ConfScreenBannerList"), OnScreenBannerItemClick)

//OpLT OpMT  OpRT OpLB OpMB OpRB OpFontBig OpFontMid OpFontSmall OpColorRed OpColorBlue OpColorYellow OpColorBlack  OpColorGreen OpStyle1  OpStyle2 OpStyle3 OpFullTrans OpSemiTrans OpNoTrans OpBannerFontBig OpBannerFontMid OpBannerFontSmall OpBannerColorRed OpBannerColorBlue OpBannerColorYellow OpBannerColorBlack OpBannerColorGreen
	MSG_SELECTCHANGE(_T("OpLT"), OnOpLT)
	MSG_SELECTCHANGE(_T("OpMT"), OnOpMT)
	MSG_SELECTCHANGE(_T("OpRT"), OnOpRT)
	MSG_SELECTCHANGE(_T("OpLB"), OnOpLB)
	MSG_SELECTCHANGE(_T("OpMB"), OnOpMB)
	MSG_SELECTCHANGE(_T("OpRB"), OnOpRB)
	MSG_SELECTCHANGE(_T("OpFontBig"), OnOpFontBig)
	MSG_SELECTCHANGE(_T("OpFontMid"), OnOpFontMid)
	MSG_SELECTCHANGE(_T("OpFontSmall"), OnOpFontSmall)
	MSG_SELECTCHANGE(_T("OpColorRed"), OnOpColorRed)
	MSG_SELECTCHANGE(_T("OpColorBlue"), OnOpColorBlue)
	MSG_SELECTCHANGE(_T("OpColorYellow"), OnOpColorYellow)
	MSG_SELECTCHANGE(_T("OpColorBlack"), OnOpColorBlack)
	MSG_SELECTCHANGE(_T("OpColorGreen"), OnOpColorGreen)
	MSG_SELECTCHANGE(_T("OpStyle1"), OnOpStyle1)
	MSG_SELECTCHANGE(_T("OpStyle2"), OnOpStyle2)
	MSG_SELECTCHANGE(_T("OpStyle3"), OnOpStyle3)
	MSG_SELECTCHANGE(_T("OpStyle4"), OnOpStyle4)
	MSG_SELECTCHANGE(_T("OpStyle5"), OnOpStyle5)
	MSG_SELECTCHANGE(_T("OpFullTrans"), OnOpFullTrans)
	MSG_SELECTCHANGE(_T("OpSemiTrans"), OnOpSemiTrans)     
	MSG_SELECTCHANGE(_T("OpNoTrans"), OnOpNoTrans)
	MSG_SELECTCHANGE(_T("OpBannerFontBig"), OnOpBannerFontBig)
	MSG_SELECTCHANGE(_T("OpBannerFontMid"), OnOpBannerFontMid)
	MSG_SELECTCHANGE(_T("OpBannerFontSmall"), OnOpBannerFontSmall)
	MSG_SELECTCHANGE(_T("OpBannerColorRed"), OnOpBannerColorRed)
	MSG_SELECTCHANGE(_T("OpBannerColorBlue"), OnOpBannerColorBlue)
	MSG_SELECTCHANGE(_T("OpBannerColorYellow"), OnOpBannerColorYellow)
	MSG_SELECTCHANGE(_T("OpBannerColorBlack"), OnOpBannerColorBlack)
	MSG_SELECTCHANGE(_T("OpBannerColorGreen"), OnOpBannerColorGreen)


	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

    USER_MSG(UI_FIRSTLOGINAFTERUPDATE_NTY,OnFirstLoginAfterUpdateNty)

	USER_MSG(UI_CNS_REG_NAT_NTY,UpdateNatInfo)
	USER_MSG(UI_CNS_ETHNETINFO_NOTIFY,UpdateEthnetInfo)
	USER_MSG(UI_CNS_CNSINFO_NOTIFY,OnCnsInfoNotify)
	USER_MSG(UI_CNS_MAINROOM_NOTIFY,OnMainRoomNotify) 

    //IPV6
    USER_MSG( UI_CNS_IPVTYPE_NOTIFY, OnSetIpvTypeNty)
    USER_MSG( UI_CNS_IPV6CFG_NOTIFY, OnSetIpv6CfgNty)

    USER_MSG(WM_CNC_FL_FTPCONFSIGNPROGRESS,OnUploadLogoProgressFirstLogin)
	USER_MSG(WM_CNC_FTPCONFSIGNPROGRESS,OnUploadLogoProgress)
	USER_MSG(WM_CNC_FTPCONFBANNERPROGRESS,OnUploadBannerProgress)

	USER_MSG(UI_CNC_ISSHOWLOGO_IND,OnLogoInd)
	USER_MSG(UI_CNC_ISSHOWLOGO_NTY,OnLogoNty)
	USER_MSG(UI_CNC_ISSHOWBANNER_IND,OnBannerInd) 
	USER_MSG(UI_CNC_ISSHOWBANNER_NTY,OnBannerNty)
	//����ü���������ʾ��
	USER_MSG(UI_CNC_VIDCUTLINE_IND,OnVidCutLineInd)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)

    USER_MSG(UI_CNSETFTPRSP, OnSetCnFtpRsp)

APP_END_MSG_MAP()

const String CLocalRoomCfgLogic::m_strSldTab = _T("slidetab");

CLocalRoomCfgLogic::CLocalRoomCfgLogic(void)
{
	m_bIsFix = false;
	m_dwLogoScreenSelId = -1;
	m_dwBannerScreenSelId = -1;
	m_dwLogoScreenSeUploadlId = -1;
	m_dwBannerScreenUploadId = -1;
	m_emCurrentPage = ID_LOGO;

    m_bWaitFtpUpLogo = false;
    m_bWaitFtpUpbanner = false;

    m_bWaitFtpUploadLogoImgForLogin = false;
}


CLocalRoomCfgLogic::~CLocalRoomCfgLogic(void)
{
}

bool CLocalRoomCfgLogic::OnCreate( TNotifyUI& msg )
{
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = DEFAULT_TITLE_HEIGHT;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), NULL, 0, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CLocalRoomCfgLogic::OnInit( TNotifyUI& msg )
{
	ComInterface->GetLocalCnsInfo( m_SelCnsInfo );
	ShowCnsInfo();

	bool bIs = false;
	UpdateEthnetInfo( 0 ,0, bIs );
	UpdateNatInfo( 0 , 0 , bIs);
	InitVidCutLine();//��ʼ������ü���������ʾ״̬��

	CTouchListUI *pLogoListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenLogoList") );
	CTouchListUI *pBannerListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenBannerList") );
	if ( pLogoListLayoutUI == NULL || pBannerListLayoutUI == NULL )
	{
		return false;
	}

	pLogoListLayoutUI->RemoveAll();
	pBannerListLayoutUI->RemoveAll();
	for ( int dwIndex = 1; dwIndex <= 3; dwIndex++ )
	{
 		CListContainerElementUI *pLogoListContainer = 
 			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfScreenListItem") );
		CListContainerElementUI *pBannerListContainer = 
 			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfScreenListItem") );

		CString strText = _T("");
		strText.Format(_T("��ʾ��0%d"),dwIndex);

		ICncCommonOp::SetControlText( (LPCTSTR)strText,m_pm,_T("lbScreenLogo"),pBannerListContainer);
		ICncCommonOp::SetControlText( (LPCTSTR)strText,m_pm,_T("lbScreenLogo"),pLogoListContainer);

		pLogoListLayoutUI->Add(pLogoListContainer);
		pBannerListLayoutUI->Add(pBannerListContainer);
	}

	UpdateLogoCheck();
	UpdateBannerCheck();
	return true;
}


bool CLocalRoomCfgLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsFix = false;
	m_dwLogoScreenSelId = -1;
	m_dwBannerScreenSelId = -1;
	m_dwLogoScreenSeUploadlId = -1;
	m_dwBannerScreenUploadId = -1;

	m_pm->DoCase(_T("caseBannerSetUnSel"));
	m_pm->DoCase(_T("caseLogoSetUnSel"));
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnFixOrCancel"));

	ComInterface->GetLocalCnsInfo( m_SelCnsInfo );
	ShowCnsInfo();

	bool bIs = false;
	UpdateEthnetInfo( 0 ,0, bIs );
	UpdateNatInfo( 0 , 0 , bIs);

	//add by wangkui 2016-9-18
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
	ICncCommonOp::SetControlText(_T("�� ��"),m_pm,_T("BtnFixOrCancel"));
	m_pm->DoCase(_T("caseSetCancel"));

    m_bWaitFtpUpLogo = false;
    m_bWaitFtpUpbanner = false;
    m_bWaitFtpUploadLogoImgForLogin = false;
	return true;
}

bool CLocalRoomCfgLogic::OnBtnCancleLogo( TNotifyUI& msg )
{
	TTPLogoInfo tTPLogoInfo;
	ComInterface->GetLogoInfo( tTPLogoInfo );

	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0] = tTPLogoInfo.tFirsLogoInfo;
			m_mapIsLogo[0] = tTPLogoInfo.tFirsLogoInfo.bIsShowLogo;
			UpdateLogoTag(m_mapLogoInfo[0]);
			UpdateLogoScreen(m_mapLogoInfo[0],0);
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1] = tTPLogoInfo.tSecondLogoInfo;
			m_mapIsLogo[1] = tTPLogoInfo.tSecondLogoInfo.bIsShowLogo;
			UpdateLogoTag(m_mapLogoInfo[1]);
			UpdateLogoScreen(m_mapLogoInfo[1],1);
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2] = tTPLogoInfo.tThirdLogoInfo;
			m_mapIsLogo[2] = tTPLogoInfo.tThirdLogoInfo.bIsShowLogo;
			UpdateLogoTag(m_mapLogoInfo[2]);
			UpdateLogoScreen(m_mapLogoInfo[2],2);
		}
		break;
	}

	return true;
}

bool CLocalRoomCfgLogic::OnBtnSaveLogo( TNotifyUI& msg )
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        //δ������ȴ����������ϴ�
        m_bWaitFtpUpLogo = true;
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
        return false;
    }

	if (m_vecLogoFile.size()>0)//���ϴ�ĳһ����ʱ�� ��ֹ�ϴ�
	{
		return false;
	}

	m_dwLogoScreenSeUploadlId = m_dwLogoScreenSelId;

	TTPLogoInfo tTPLogoInfo;
	ComInterface->GetLogoInfo( tTPLogoInfo );
	//���浱ǰ����
	CEditUI *pEdtConfName = (CEditUI*)ICncCommonOp::FindControl( m_pm,_T("edtLogo") );   
	CString strConfName;
	if (pEdtConfName)
	{
		strConfName = pEdtConfName->GetText();
	}

	if (!strConfName.IsEmpty())
	{
		switch(m_dwLogoScreenSelId)
		{
		case 0:
			{
				strncpy(m_mapLogoInfo[0].achLogoName, (CT2A)strConfName, TP_MAX_ALIAS_LEN_CNC-1);
			}
			break;
		case 1:
			{
				strncpy(m_mapLogoInfo[1].achLogoName, (CT2A)strConfName, TP_MAX_ALIAS_LEN_CNC-1);
			}
			break;
		case 2:
			{
				strncpy(m_mapLogoInfo[2].achLogoName, (CT2A)strConfName, TP_MAX_ALIAS_LEN_CNC-1);
			}
			break;
		}

	}
	else
	{
		ShowMessageBox(_T("������̨�����"));
		return false;
	}

	BOOL bSuccess;
	CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
	if(!PathFileExists(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}

	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			if(strcmp( tTPLogoInfo.tFirsLogoInfo.achLogoName, m_mapLogoInfo[0].achLogoName ) == 0
				&& tTPLogoInfo.tFirsLogoInfo.bIsShowLogo == m_mapLogoInfo[0].bIsShowLogo
				&& tTPLogoInfo.tFirsLogoInfo.emColor == m_mapLogoInfo[0].emColor
				&& tTPLogoInfo.tFirsLogoInfo.emSize == m_mapLogoInfo[0].emSize
				&& tTPLogoInfo.tFirsLogoInfo.emStyle == m_mapLogoInfo[0].emStyle
				)
			{
				return true;
			}

			int nImgType = 0;
            switch(m_mapLogoInfo[0].emStyle)
            {
            case emLeftDown:
            case emLeftUp:
                nImgType = 1;
                break;
            case emRightDown:
            case emRightUp:
                nImgType = 2;
                break;
            default:
                break;
            }

			FontStyle font = FontStyleBold;
			Color clr;
			Color clBorder;
			u32 w1080Size;
			u32 w720Size;
			u32 w4CIFSize;

			GetLogoStyle(m_mapLogoInfo[0], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
			CString strPath = strFullPath + LOGO1080P_POS0_PATH ;
			CString strLogoName(m_mapLogoInfo[0].achLogoName);
			if (/*_tcscmp(strLogoName,_T("������̨�����")) == 0 ||*/ strLogoName.IsEmpty())
			{
				strLogoName.Format(_T("��ʾ��01"));
			}

			bSuccess = MakeImgByChar( strLogoName, _T("����"), font, clr, clBorder, Color(255,255,255), 
				 w1080Size, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("1080P̨��ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + LOGO720P_POS0_PATH;
			bSuccess = MakeImgByChar( strLogoName, _T("����"), font, clr,  clBorder, Color(255,255,255), 
				w720Size, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("720P̨��ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + LOGO4CIF_POS0_PATH;
			bSuccess = MakeImgByChar( strLogoName, _T("����"), font, clr,  clBorder, Color(255,255,255), 
				w4CIFSize, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("4CIF̨��ͼƬ����ʧ��")),false);
				return false;
			}

			m_vecLogoFile.clear();
			m_vecLogoFile.push_back(LOGO720P_POS0_PATH);
			m_vecLogoFile.push_back(LOGO1080P_POS0_PATH);
			m_vecLogoFile.push_back(LOGO4CIF_POS0_PATH);
		}
		break;
	case 1:
		{
			if(strcmp( tTPLogoInfo.tSecondLogoInfo.achLogoName, m_mapLogoInfo[1].achLogoName ) == 0 
				&& tTPLogoInfo.tSecondLogoInfo.bIsShowLogo == m_mapLogoInfo[1].bIsShowLogo
				&& tTPLogoInfo.tSecondLogoInfo.emColor == m_mapLogoInfo[1].emColor
				&& tTPLogoInfo.tSecondLogoInfo.emSize == m_mapLogoInfo[1].emSize
				&& tTPLogoInfo.tSecondLogoInfo.emStyle == m_mapLogoInfo[1].emStyle
				)
			{
				return true;
			}

            int nImgType = 0;
            switch(m_mapLogoInfo[1].emStyle)
            {
            case emLeftDown:
            case emLeftUp:
                nImgType = 1;
                break;
            case emRightDown:
            case emRightUp:
                nImgType = 2;
                break;
            default:
                break;
            }

			FontStyle font = FontStyleBold;
			Color clr;
			Color clBorder;
			u32 w1080Size;
			u32 w720Size;
			u32 w4CIFSize;

			GetLogoStyle(m_mapLogoInfo[1], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
			CString strPath = strFullPath +  LOGO1080P_POS1_PATH;
			CString strLogoName2(m_mapLogoInfo[1].achLogoName);
			if ( strLogoName2.IsEmpty())
			{
				strLogoName2.Format(_T("��ʾ��02"));
			}
			bSuccess = MakeImgByChar( strLogoName2, _T("����"), font, clr, clBorder, Color(255,255,255), 
				w1080Size , 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("1080P̨��ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + LOGO720P_POS1_PATH;
			bSuccess = MakeImgByChar( strLogoName2, _T("����"), font, clr,  clBorder, Color(255,255,255), 
				w720Size, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("720P̨��ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + LOGO4CIF_POS1_PATH;
			bSuccess = MakeImgByChar( strLogoName2, _T("����"), font, clr,  clBorder, Color(255,255,255), 
				w4CIFSize, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("4CIF̨��ͼƬ����ʧ��")),false);
				return false;
			}


			m_vecLogoFile.clear();
			m_vecLogoFile.push_back(LOGO720P_POS1_PATH);
			m_vecLogoFile.push_back(LOGO1080P_POS1_PATH);
			m_vecLogoFile.push_back(LOGO4CIF_POS1_PATH);

		}
		break;
	case 2:
		{
			if(strcmp( tTPLogoInfo.tThirdLogoInfo.achLogoName, m_mapLogoInfo[2].achLogoName ) == 0 
				&& tTPLogoInfo.tThirdLogoInfo.bIsShowLogo == m_mapLogoInfo[2].bIsShowLogo
				&& tTPLogoInfo.tThirdLogoInfo.emColor == m_mapLogoInfo[2].emColor
				&& tTPLogoInfo.tThirdLogoInfo.emSize == m_mapLogoInfo[2].emSize 
				&& tTPLogoInfo.tThirdLogoInfo.emStyle == m_mapLogoInfo[2].emStyle
				)
			{
				return true;
			}

            int nImgType = 0;
            switch(m_mapLogoInfo[2].emStyle)
            {
            case emLeftDown:
            case emLeftUp:
                nImgType = 1;
                break;
            case emRightDown:
            case emRightUp:
                nImgType = 2;
                break;
            default:
                break;
            }

			FontStyle font = FontStyleBold;
			Color clr;
			Color clBorder;
			u32 w1080Size;
			u32 w720Size;
			u32 w4CIFSize;

			GetLogoStyle(m_mapLogoInfo[2], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
			CString strPath = strFullPath + LOGO1080P_POS2_PATH;
			CString strLogoName3(m_mapLogoInfo[2].achLogoName);
			if ( strLogoName3.IsEmpty())
			{
				strLogoName3.Format(_T("��ʾ��03"));
			}
			bSuccess = MakeImgByChar( strLogoName3, _T("����"), font, clr,  clBorder, Color(255,255,255), 
				 w1080Size, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("1080P̨��ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + LOGO720P_POS2_PATH;
			bSuccess = MakeImgByChar( strLogoName3, _T("����"), font, clr, clBorder, Color(255,255,255), 
				w720Size, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("720P̨��ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + LOGO4CIF_POS2_PATH;
			bSuccess = MakeImgByChar( strLogoName3, _T("����"), font, clr,  clBorder, Color(255,255,255), 
				w4CIFSize, 2, strPath, true, nImgType );
			if( !bSuccess )
			{
				ShowMessageBox((_T("4CIF̨��ͼƬ����ʧ��")),false);
				return false;
			}

			m_vecLogoFile.clear();
			m_vecLogoFile.push_back(LOGO720P_POS2_PATH);
			m_vecLogoFile.push_back(LOGO1080P_POS2_PATH);
			m_vecLogoFile.push_back(LOGO4CIF_POS2_PATH);
		}
		break;
	}

	if( !UploadLogoCore( CNSCONF_FILE_PATH, (String)strFullPath+m_vecLogoFile.at(0), m_vecLogoFile.at(0), FALSE) )
	{
		char ach[MAX_PATH];
		strcpy(ach,(CT2A)m_vecLogoFile.at(0).c_str());
		PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", ach );
	}

	return true;
}

bool CLocalRoomCfgLogic::OnBtnCancleBanner( TNotifyUI& msg )
{
	TTPBannerInfo tTPBannerInfo;
	ComInterface->GetBannerInfo( tTPBannerInfo );

	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0] = tTPBannerInfo.tFirstBannerInfo;
			m_mapIsBanner[0] = tTPBannerInfo.tFirstBannerInfo.bIsShowBanner;
			UpdateBannerTag(m_mapBannerInfo[0]);
			UpdateBannerScreen(m_mapBannerInfo[0],0);
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1] = tTPBannerInfo.tSeconfBannerInfo;
			m_mapIsBanner[1] = tTPBannerInfo.tSeconfBannerInfo.bIsShowBanner;
			UpdateBannerTag(m_mapBannerInfo[1]);
			UpdateBannerScreen(m_mapBannerInfo[1],1);
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2] = tTPBannerInfo.tThirdBannerInfo;
			m_mapIsBanner[2] = tTPBannerInfo.tThirdBannerInfo.bIsShowBanner;
			UpdateBannerTag(m_mapBannerInfo[2]);
			UpdateBannerScreen(m_mapBannerInfo[2],2);
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnBtnSaveBanner( TNotifyUI& msg )
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        //δ������ȴ����������ϴ�
        m_bWaitFtpUpbanner = true;
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
        return false;
    }

	if (m_vecBannerFile.size()>0)//���ϴ�ĳһ����ʱ�� ��ֹ�ϴ�
	{
		return false;
	}

	m_dwBannerScreenUploadId = m_dwBannerScreenSelId;

	TTPBannerInfo tTPBannerInfo;
	ComInterface->GetBannerInfo( tTPBannerInfo );
	//���浱ǰ����
	CEditUI *pEdtConfName = (CEditUI*)ICncCommonOp::FindControl( m_pm,_T("edtBanner") );   
	CString strConfName;
	if (pEdtConfName)
	{
		strConfName = pEdtConfName->GetText();
	}

	if (!strConfName.IsEmpty())
	{
		switch(m_dwBannerScreenSelId)
		{
		case 0:
			{
				strncpy(m_mapBannerInfo[0].achBannerName, (CT2A)strConfName, TP_MAX_ALIAS_LEN);
			}
			break;
		case 1:
			{
				strncpy(m_mapBannerInfo[1].achBannerName, (CT2A)strConfName, TP_MAX_ALIAS_LEN);
			}
			break;
		case 2:
			{
				strncpy(m_mapBannerInfo[2].achBannerName, (CT2A)strConfName, TP_MAX_ALIAS_LEN);
			}
			break;
		}
	}
	else
	{
		ShowMessageBox(_T("������������"));
		return false;
	}

	BOOL bSuccess;
	CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
	if(!PathFileExists(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			if(strcmp( tTPBannerInfo.tFirstBannerInfo.achBannerName, m_mapBannerInfo[0].achBannerName ) == 0
				&& tTPBannerInfo.tFirstBannerInfo.bIsShowBanner == m_mapBannerInfo[0].bIsShowBanner
				&& tTPBannerInfo.tFirstBannerInfo.emColor == m_mapBannerInfo[0].emColor
				&& tTPBannerInfo.tFirstBannerInfo.emSize == m_mapBannerInfo[0].emSize
				&& tTPBannerInfo.tFirstBannerInfo.emStyle == m_mapBannerInfo[0].emStyle
				)
			{
				return true;
			}

			FontStyle font = FontStyleBold;
			Color clr;
			Color clBorder;
			u32 w1080Size;
			u32 w720Size;
			u32 w4CIFSize;

			GetBannerStyle(m_mapBannerInfo[0], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
			CString strPath = strFullPath + BANNER1080P_POS0_PATH ;
			CString strBannerName(m_mapBannerInfo[0].achBannerName);
			if (strBannerName.IsEmpty())
			{
				strBannerName.Format(_T("��ʾ��01"));
			}

			bSuccess = MakeImgByChar( strBannerName, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w1080Size, 0, strPath, false, 0, 1920,132);
			if( !bSuccess )
			{
				ShowMessageBox((_T("1080P���ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + BANNER720P_POS0_PATH;
			bSuccess = MakeImgByChar(strBannerName, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w720Size, 0, strPath, false, 0, 1280, 88);
			if( !bSuccess )
			{
				ShowMessageBox((_T("720P���ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + BANNER4CIF_POS0_PATH;
			bSuccess = MakeImgByChar(strBannerName, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w4CIFSize, 0, strPath, false, 0, 720, 70);
			if( !bSuccess )
			{
				ShowMessageBox((_T("4CIF���ͼƬ����ʧ��")),false);
				return false;
			}

			m_vecBannerFile.clear();
			m_vecBannerFile.push_back(BANNER720P_POS0_PATH);
			m_vecBannerFile.push_back(BANNER1080P_POS0_PATH);
			m_vecBannerFile.push_back(BANNER4CIF_POS0_PATH);

		}
		break;
	case 1:
		{
			if(strcmp( tTPBannerInfo.tSeconfBannerInfo.achBannerName, m_mapBannerInfo[1].achBannerName ) == 0 
				&& tTPBannerInfo.tSeconfBannerInfo.bIsShowBanner == m_mapBannerInfo[1].bIsShowBanner
				&& tTPBannerInfo.tSeconfBannerInfo.emColor == m_mapBannerInfo[1].emColor
				&& tTPBannerInfo.tSeconfBannerInfo.emSize == m_mapBannerInfo[1].emSize
				&& tTPBannerInfo.tSeconfBannerInfo.emStyle == m_mapBannerInfo[1].emStyle
				)
			{
				return true;
			}

			FontStyle font = FontStyleBold;
			Color clr;
			Color clBorder;
			u32 w1080Size;
			u32 w720Size;
			u32 w4CIFSize;

			GetBannerStyle(m_mapBannerInfo[1], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
			CString strPath = strFullPath +  BANNER1080P_POS1_PATH;
			CString strBannerName2(m_mapBannerInfo[1].achBannerName);
			if (_tcscmp(strBannerName2,_T("������������")) == 0 || strBannerName2.IsEmpty())
			{
				strBannerName2.Format(_T("��ʾ��02"));
			}
			bSuccess = MakeImgByChar(strBannerName2, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w1080Size , 0, strPath, false, 0, 1920,132);
			if( !bSuccess )
			{
				ShowMessageBox((_T("1080P���ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + BANNER720P_POS1_PATH;
			bSuccess = MakeImgByChar( strBannerName2, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w720Size, 0, strPath, false, 0, 1280, 88 );
			if( !bSuccess )
			{
				ShowMessageBox((_T("720P���ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + BANNER4CIF_POS1_PATH;
			bSuccess = MakeImgByChar(strBannerName2, _T("����"), font, clr,  Color(0,0,0), 
				clBorder, w4CIFSize, 0, strPath, false, 0, 720, 70);
			if( !bSuccess )
			{
				ShowMessageBox((_T("4CIF���ͼƬ����ʧ��")),false);
				return false;
			}

			m_vecBannerFile.clear();
			m_vecBannerFile.push_back(BANNER720P_POS1_PATH);
			m_vecBannerFile.push_back(BANNER1080P_POS1_PATH);
			m_vecBannerFile.push_back(BANNER4CIF_POS1_PATH);

		}
		break;
	case 2:
		{
			if(strcmp( tTPBannerInfo.tThirdBannerInfo.achBannerName, m_mapBannerInfo[2].achBannerName ) == 0 
				&& tTPBannerInfo.tThirdBannerInfo.bIsShowBanner == m_mapBannerInfo[2].bIsShowBanner
				&& tTPBannerInfo.tThirdBannerInfo.emColor == m_mapBannerInfo[2].emColor
				&& tTPBannerInfo.tThirdBannerInfo.emSize == m_mapBannerInfo[2].emSize 
				&& tTPBannerInfo.tThirdBannerInfo.emStyle == m_mapBannerInfo[2].emStyle
				)
			{
				return true;
			}

			FontStyle font = FontStyleBold;
			Color clr;
			Color clBorder;
			u32 w1080Size;
			u32 w720Size;
			u32 w4CIFSize;

			GetBannerStyle(m_mapBannerInfo[2], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
			CString strPath = strFullPath + BANNER1080P_POS2_PATH;
			CString strBannerName3(m_mapBannerInfo[2].achBannerName);
			if (_tcscmp(strBannerName3,_T("������������")) == 0  || strBannerName3.IsEmpty())
			{
				strBannerName3.Format(_T("��ʾ��03"));
			}
			bSuccess = MakeImgByChar(strBannerName3, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w1080Size, 0, strPath, false, 0, 1920,132);
			if( !bSuccess )
			{
				ShowMessageBox((_T("1080P���ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + BANNER720P_POS2_PATH;
			bSuccess = MakeImgByChar(strBannerName3, _T("����"), font, clr, Color(0,0,0), 
				clBorder, w720Size, 0, strPath, false, 0, 1280, 88);
			if( !bSuccess )
			{
				ShowMessageBox((_T("720P���ͼƬ����ʧ��")),false);
				return false;
			}

			strPath = strFullPath + BANNER4CIF_POS2_PATH;
			bSuccess = MakeImgByChar( strBannerName3, _T("����"), font, clr, Color(0,0,0),  
				clBorder, w4CIFSize, 0, strPath, false, 0, 720, 70);
			if( !bSuccess )
			{
				ShowMessageBox((_T("4CIF���ͼƬ����ʧ��")),false);
				return false;
			}

			m_vecBannerFile.clear();
			m_vecBannerFile.push_back(BANNER720P_POS2_PATH);
			m_vecBannerFile.push_back(BANNER1080P_POS2_PATH);
			m_vecBannerFile.push_back(BANNER4CIF_POS2_PATH);

		}
		break;
	}
	
	if( !UploadBannerCore( CNSCONF_FILE_PATH, (String)strFullPath+m_vecBannerFile.at(0), m_vecBannerFile.at(0), FALSE) )
	{
		char ach[MAX_PATH];
		strcpy(ach,(CT2A)m_vecBannerFile.at(0).c_str());
		PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", ach );
		//ʧ����� ��ֹ�����ٴ�
		m_vecBannerFile.clear();
	}

	return true;
}

bool CLocalRoomCfgLogic::OnUploadLogoProgressFirstLogin(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);

    switch( emFileFtpStatus )
    {
    case emFtpBegin:
        {
            //PrtMsg( 0, emEventTypeCmsWindow, _T("%s�Ѿ����봫��״̬��"), m_vecLogoFile.at(0).c_str() );
        }
        break;
    case emFtpTransfer:
        {
        }
        break;
    case emFtpEnd:
        {
            DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
            m_cFtpLogo.EndFtpFile();	
            if ( 0 == dwSuccess )
            {
                PrtMsg( 0, emEventTypeCmsWindow, "��ʱ�������ļ�������%d", m_vecLogoFile.size()-1 );
                if ( m_vecLogoFile.size() >0 )
                {	
                    vector<String>::iterator itr = m_vecLogoFile.begin();
                    m_vecLogoFile.erase(itr);
                    if ( m_vecLogoFile.size() > 0 )
                    {
                        CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
                        if(!PathFileExists(strFullPath))
                        {
                            CreateDirectory(strFullPath, NULL);
                        }
                        if ( !UploadLogoCoreFirstLogin( CNSCONF_FILE_PATH, (String)strFullPath+m_vecLogoFile.at(0), m_vecLogoFile.at(0), FALSE) )
                        {			
                            m_vecLogoFile.clear();
                            char ach[MAX_PATH];
                            strcpy(ach,(CT2A)m_vecLogoFile.at(0).c_str());
                            PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", ach );
                        }		
                    }
                    else
                    {
                        TTPLogoInfo tTPLogoInfo;
                        ComInterface->GetLogoInfo( tTPLogoInfo );
                        //ȫ��������Ϸ�����Ϣ				
                        for (int i = 0 ; i < 3 ; i++)
                        {
                            TTPShowLogo tLogoInfo;
                            switch(i)
                            {
                            case 0:
                                tLogoInfo = tTPLogoInfo.tFirsLogoInfo;
                                break;
                            case 1:
                                tLogoInfo = tTPLogoInfo.tSecondLogoInfo;
                                break;	
                            case 2:
                                tLogoInfo = tTPLogoInfo.tThirdLogoInfo;
                            }

                            if (tLogoInfo.bIsShowLogo == FALSE || tLogoInfo.achLogoName == "")
                            {
                                continue;
                            }

                            TTPLogo tTTPLogo;
                            tTTPLogo.tLogoInfo = m_mapLogoInfo[i];
                            if (tTTPLogo.tLogoInfo.emSize == emMid)
                            {
                                tTTPLogo.tLogoInfo.emSize = emBig;
                            }
                            tTTPLogo.byIndex = i;
                            ComInterface->CnIsShowLogoCmd( tTTPLogo );	
                        }
                        PrtMsg( 0, emEventTypeCmsWindow, "ͼƬ�ϴ����" );
                    }

                }
            }
            else
            {
                CString str(m_vecLogoFile.at(0).c_str());
                char ach[MAX_PATH];
                strcpy(ach,(CT2A)m_vecLogoFile.at(0).c_str());

                LPTSTR pszMsg = NULL;
                m_cFtpLogo.FormatFtpError( dwSuccess, &pszMsg );
                PrtMsg( 0, emEventTypeCmsWindow, "�ϴ�logo�ļ�ʧ�ܣ�%s,����ԭ��%d %s", ach, dwSuccess, pszMsg );
                CString strError;
                strError.Format(_T("�ϴ�logo�ļ�ʧ��"));
                ShowPopMsg(strError);
                //ʧ����� ��ֹ�����ٴ�
                m_vecLogoFile.clear();
                LocalFree( pszMsg );
            }		
        }
        break;
    default:
        {
        }
        break;
    }	
    return true;
}

bool CLocalRoomCfgLogic::OnUploadLogoProgress(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);

	switch( emFileFtpStatus )
	{
	case emFtpBegin:
		{
			//PrtMsg( 0, emEventTypeCmsWindow, _T("%s�Ѿ����봫��״̬��"), m_vecLogoFile.at(0).c_str() );
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			m_cFtpLogo.EndFtpFile();	
			if ( 0 == dwSuccess )
			{
				PrtMsg( 0, emEventTypeCmsWindow, "��ʱ�������ļ�������%d", m_vecLogoFile.size()-1 );
				if ( m_vecLogoFile.size() >0 )
				{	
					vector<String>::iterator itr = m_vecLogoFile.begin();
					m_vecLogoFile.erase(itr);
					if ( m_vecLogoFile.size() > 0 )
					{
						CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
						if(!PathFileExists(strFullPath))
						{
							CreateDirectory(strFullPath, NULL);
						}
						if ( !UploadLogoCore( CNSCONF_FILE_PATH, (String)strFullPath+m_vecLogoFile.at(0), m_vecLogoFile.at(0), FALSE) )
						{			
							m_vecLogoFile.clear();
							char ach[MAX_PATH];
							strcpy(ach,(CT2A)m_vecLogoFile.at(0).c_str());
							PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", ach );
						}		
					}
					else
					{
						//ȫ��������Ϸ�����Ϣ				
						TTPLogo tTTPLogo;
						tTTPLogo.tLogoInfo = m_mapLogoInfo[m_dwLogoScreenSeUploadlId];
						tTTPLogo.byIndex = m_dwLogoScreenSeUploadlId;
						ComInterface->CnIsShowLogoCmd( tTTPLogo );	

						PrtMsg( 0, emEventTypeCmsWindow, "ͼƬ�ϴ����" );
					}

				}
			}
			else
			{
				CString str(m_vecLogoFile.at(0).c_str());
				char ach[MAX_PATH];
				strcpy(ach,(CT2A)m_vecLogoFile.at(0).c_str());
				
				LPTSTR pszMsg = NULL;
				m_cFtpLogo.FormatFtpError( dwSuccess, &pszMsg );
				PrtMsg( 0, emEventTypeCmsWindow, "�ϴ�logo�ļ�ʧ�ܣ�%s,����ԭ��%d %s", ach, dwSuccess, pszMsg );
				CString strError;
				strError.Format(_T("�ϴ�logo�ļ�ʧ��"));
				ShowPopMsg(strError);
				//ʧ����� ��ֹ�����ٴ�
				m_vecLogoFile.clear();
				LocalFree( pszMsg );
			}		
		}
		break;
	default:
		{
		}
		break;
	}	
	return true;
}

bool CLocalRoomCfgLogic::OnUploadBannerProgress(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);

	switch( emFileFtpStatus )
	{
	case emFtpBegin:
		{
			//PrtMsg( 0, emEventTypeCmsWindow, _T("%s�Ѿ����봫��״̬��"), m_vecBannerFile.at(0).c_str() );
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP�ӿ�0Ϊ�ɹ�  Ĭ��ʧ��
			m_cFtpBanner.EndFtpFile();	
			if ( 0 == dwSuccess )
			{
				PrtMsg( 0, emEventTypeCmsWindow, "��ʱ�������ļ�������%d", m_vecBannerFile.size()-1 );
				if ( m_vecBannerFile.size() >0 )
				{	
					vector<String>::iterator itr = m_vecBannerFile.begin();
					m_vecBannerFile.erase(itr);
					if ( m_vecBannerFile.size() > 0 )
					{
						CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
						if(!PathFileExists(strFullPath))
						{
							CreateDirectory(strFullPath, NULL);
						}
						if ( !UploadBannerCore( CNSCONF_FILE_PATH, (String)strFullPath+m_vecBannerFile.at(0), m_vecBannerFile.at(0), FALSE) )
						{			
							char ach[MAX_PATH];
							strcpy(ach,(CT2A)m_vecBannerFile.at(0).c_str());
							PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", ach );
							//ʧ����� ��ֹ�����ٴ�
							m_vecBannerFile.clear();
						}		
					}
					else
					{
						//ȫ��������Ϸ�����Ϣ		
						TTPBanner tTTPBanner;
						tTTPBanner.tBannerInfo = m_mapBannerInfo[m_dwBannerScreenUploadId];
						tTTPBanner.byIndex = m_dwBannerScreenUploadId;
						ComInterface->CnIsShowBannerCmd( tTTPBanner );	
						PrtMsg( 0, emEventTypeCmsWindow, "ͼƬ�ϴ����" );
					}

				}
			}
			else
			{
				CString str(m_vecBannerFile.at(0).c_str());
				char ach[MAX_PATH];
				strcpy(ach,(CT2A)m_vecBannerFile.at(0).c_str());
				
				LPTSTR pszMsg = NULL;
				m_cFtpBanner.FormatFtpError( dwSuccess, &pszMsg );
				PrtMsg( 0, emEventTypeCmsWindow, "�ϴ�Banner�ļ�ʧ�ܣ�%s,����ԭ��%d %s", ach, dwSuccess, pszMsg );
				CString strError;
				strError.Format(_T("�ϴ�banner�ļ�ʧ��"));
				//ʧ����� ��ֹ�����ٴ�
				m_vecBannerFile.clear();
				ShowPopMsg(strError);
				LocalFree( pszMsg );
			}		
		}
		break;
	default:
		{
		}
		break;
	}	
	return true;
}

bool CLocalRoomCfgLogic::OnTabLogo( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_LOGO);
		m_emCurrentPage = ID_LOGO;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnTabBanner( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_BANNER);
		m_emCurrentPage = ID_BANNER;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnTabParam( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_CONFPARAMETERS);
		m_emCurrentPage = ID_CONFPARAMETERS;
	}
	return true;
}

//ֻ�����Ƿ�����״̬ �����Ŀ��ʱ����ƽ����Ƿ���ʾ����
bool CLocalRoomCfgLogic::OnCheckScreenSel( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	CTouchListUI *pTouchlist = (CTouchListUI *)msg.pSender->GetParent()->GetParent()->GetParent();
	if (!pTouchlist)
	{
		return false;
	}

	int dwScreenNo = pTouchlist->GetItemIndex(msg.pSender->GetParent()->GetParent());

	CString  str = pTouchlist->GetName();
	if (str == _T("ConfScreenLogoList"))
	{
		if (dwScreenNo == m_dwLogoScreenSelId)
		{
			switch(m_dwLogoScreenSelId)
			{
			case 0:
				{
					m_mapLogoInfo[0].bIsShowLogo = bIsSet;
					UpdateLogoTag(m_mapLogoInfo[0]);
				}
				break;
			case 1:
				{
					m_mapLogoInfo[1].bIsShowLogo = bIsSet;
					UpdateLogoTag(m_mapLogoInfo[1]);
				}
				break;
			case 2:
				{
					m_mapLogoInfo[2].bIsShowLogo = bIsSet;
					UpdateLogoTag(m_mapLogoInfo[2]);
				}
				break;

			}
		}

		if ( m_mapIsLogo[dwScreenNo] != bIsSet)
		{
			m_mapIsLogo[dwScreenNo] = bIsSet;
			if ( dwScreenNo == m_dwLogoScreenSelId )
			{
				if (bIsSet)
				{
					m_pm->DoCase(_T("caseLogoSetSel"));
				}
				else
				{
					m_pm->DoCase(_T("caseLogoSetUnSel"));
				}
			}

			if (!bIsSet)//�ر�
			{
				//��������ѡ�е��ǲ��ǹرյ��� ��Ҫ���͹ر���Ϣ
				m_mapLogoInfo[dwScreenNo].bIsShowLogo = false;
				TTPLogo tTTPLogo;
				tTTPLogo.tLogoInfo = m_mapLogoInfo[dwScreenNo];
				tTTPLogo.byIndex = dwScreenNo;
				ComInterface->CnIsShowLogoCmd( tTTPLogo );	
			}
		}
	}
	else if (str == _T("ConfScreenBannerList"))
	{
		if (dwScreenNo == m_dwBannerScreenSelId)
		{
			switch(m_dwBannerScreenSelId)
			{
			case 0:
				{
					m_mapBannerInfo[0].bIsShowBanner = bIsSet;
					UpdateBannerTag(m_mapBannerInfo[0]);
				}
				break;
			case 1:
				{
					m_mapBannerInfo[1].bIsShowBanner = bIsSet;
					UpdateBannerTag(m_mapBannerInfo[1]);
				}
				break;
			case 2:
				{
					m_mapBannerInfo[2].bIsShowBanner = bIsSet;
					UpdateBannerTag(m_mapBannerInfo[2]);
				}
				break;
			}
		}
		if ( m_mapIsBanner[dwScreenNo] != bIsSet)
		{
			m_mapIsBanner[dwScreenNo] = bIsSet;
			if ( dwScreenNo == m_dwBannerScreenSelId )
			{
				if (bIsSet)
				{
					m_pm->DoCase(_T("caseBannerSetSel"));
				}
				else
				{
					m_pm->DoCase(_T("caseBannerSetUnSel"));
				}
			}

			if (!bIsSet)//�ر�
			{
				//��������ѡ�е��ǲ��ǹرյ��� ��Ҫ���͹ر���Ϣ
				m_mapBannerInfo[dwScreenNo].bIsShowBanner = false;
				TTPBanner tTTPBanner;
				tTTPBanner.tBannerInfo = m_mapBannerInfo[dwScreenNo];
				tTTPBanner.byIndex = dwScreenNo;
				ComInterface->CnIsShowBannerCmd( tTTPBanner );	
			}
		}
	}

	pTouchlist->SelectItem(dwScreenNo);

	return true;
}

bool CLocalRoomCfgLogic::UpdateEthnetInfo( WPARAM wParam, LPARAM lParam, bool& bHandle )
{

	TTPEthnetInfo tEthnetInfo;
	ComInterface->GetEthnetCfg( tEthnetInfo );

	in_addr tAddr;
	tAddr.S_un.S_addr = tEthnetInfo.dwIP;
	String strIP = CA2T(inet_ntoa(tAddr));
	if ( strIP == _T("0.0.0.0") )
	{
		strIP = _T("");
	}

	ICncCommonOp::SetControlText(strIP.c_str(),m_pm,_T("lbIP"));
	ICncCommonOp::SetControlText(strIP.c_str(),m_pm,_T("edtIP"));

	tAddr.S_un.S_addr = tEthnetInfo.dwMask;
	String strMaskIP = CA2T(inet_ntoa(tAddr));
	if ( strMaskIP == _T("0.0.0.0") )
	{
		strMaskIP = _T("");
	}

	ICncCommonOp::SetControlText(strMaskIP.c_str(),m_pm,_T("lbSubnetMask"));
	ICncCommonOp::SetControlText(strMaskIP.c_str(),m_pm,_T("edtSubnetMask"));

	tAddr.S_un.S_addr = tEthnetInfo.dwGateWay;
	String strGateWayIP = CA2T(inet_ntoa(tAddr));
	if ( strGateWayIP == _T("0.0.0.0") )
	{
		strGateWayIP = _T("");
	}

	ICncCommonOp::SetControlText(strGateWayIP.c_str(),m_pm,_T("lbGateWay"));
	ICncCommonOp::SetControlText(strGateWayIP.c_str(),m_pm,_T("edtGateWay"));

	return NO_ERROR;
}

bool CLocalRoomCfgLogic::UpdateNatInfo( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnFixOrCancel"));
	TTPNatCfg tNatInfo;
	ComInterface->GetNATCfg( tNatInfo );

	in_addr tAddr;
	tAddr.S_un.S_addr = tNatInfo.dwNatIP;
	String strNatIP = CA2T(inet_ntoa(tAddr));
	if ( strNatIP == _T("0.0.0.0") )
	{
		strNatIP = _T("");
	}

	ICncCommonOp::SetControlText(strNatIP.c_str(),m_pm,_T("edtNATIp"));
	ICncCommonOp::SetControlText(strNatIP.c_str(),m_pm,_T("lbNATIp"));

	if (tNatInfo.bUsed)
	{
		ICncCommonOp::SetControlText(_T("����"),m_pm,_T("lbIsNAT"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("�ر�"),m_pm,_T("lbIsNAT"));
	}
	
	CCheckBoxUI *pCheckIsNat = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsNAT") );
	if (pCheckIsNat)
	{
		pCheckIsNat->SetCheck(tNatInfo.bUsed);
	}
	ICncCommonOp::EnableControl(tNatInfo.bUsed,m_pm,_T("edtNATIp"));
	return NO_ERROR;
}

bool CLocalRoomCfgLogic::OnSetIpvTypeNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    EmProtocolVersion emProtocolVer = ComInterface->GetIpvType();

    switch (emProtocolVer)
    {
    default:
    case emIPV4:
        ICncCommonOp::OptionSelect(true,m_pm,_T("opSetIPv4"));
        break;
    case emIPV6:
        ICncCommonOp::OptionSelect(true,m_pm,_T("opSetIPv6"));
        break;
    }
    return true;
}
bool CLocalRoomCfgLogic::OnSetIpv6CfgNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPEthnetIPV6Info tTPEthnetIPV6Info;
    ComInterface->GetIpv6Cfg(tTPEthnetIPV6Info);

    //IPV6��ַ
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achIP), m_pm, _T("edtIPv6Address"));
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achIP), m_pm, _T("lbIPv6Address"));
    //IPV6����ǰ׺����
    CDuiString strIPV6SunLen = _T("");
    strIPV6SunLen.Format(_T("%d"),tTPEthnetIPV6Info.m_dwPrefix);
    ICncCommonOp::SetControlText(strIPV6SunLen, m_pm, _T("edtSubNetLength"));
    ICncCommonOp::SetControlText(strIPV6SunLen, m_pm, _T("lbSubNetLength"));
    //IPV6����
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achGateWay), m_pm, _T("edtGateWayIp"));
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achGateWay), m_pm, _T("lbGateWayIp"));
    //IPV6DNS1
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achDns1), m_pm, _T("edtDNS1Ip"));
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achDns1), m_pm, _T("lbDNS1Ip"));
    //IPV6DNS2
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achDns2), m_pm, _T("edtDNS2Ip"));
    ICncCommonOp::SetControlText(CA2T(tTPEthnetIPV6Info.m_achDns2), m_pm, _T("lbDNS2Ip"));
    return true;
}

bool CLocalRoomCfgLogic::OnCnsInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTPCNSInfoRst emRst = (EmTPCNSInfoRst)lParam;

	if ( emRst != emTPCNSInfoSuccess )
	{
		CString strName;
		strName.Format( _T("�᳡ %s ע�������ʧ��: "), m_SelCnsInfo.m_achRoomName );

		CString strTemp = _T("ע������ظ�");

		if ( emRst == emTPCNSRepeatAliasName )
		{
			strTemp = "�᳡�����ظ�";
		}
		else if ( emRst == emTPCNSRepeatE164 )
		{
			strTemp = "�᳡�����ظ�";
		}

		ShowPopMsg( strName + strTemp );
	}

	ComInterface->GetLocalCnsInfo( m_SelCnsInfo );

	ShowCnsInfo();

	return NO_ERROR;
}

void CLocalRoomCfgLogic::ShowCnsInfo()
{
	ICncCommonOp::SetControlText((CA2T)m_SelCnsInfo.m_achRoomName,m_pm,_T("lbConfName"));
	ICncCommonOp::SetControlText((CA2T)m_SelCnsInfo.m_achE164,m_pm,_T("lbE64"));

	ICncCommonOp::SetControlText((CA2T)m_SelCnsInfo.m_achRoomName,m_pm,_T("edtConfName"));
	ICncCommonOp::SetControlText((CA2T)m_SelCnsInfo.m_achE164,m_pm,_T("edtE64"));

}

bool CLocalRoomCfgLogic::OnMainRoomNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
// 	memcpy( m_achMainCns, ComInterface->GetMainCnsName(), sizeof(m_achMainCns) );
// 
// 	if ( strcmp( m_achMainCns, m_SelCnsInfo.m_achRoomName ) == 0 )
// 	{
// 		UIManagePtr->SetSwitchState( m_strBtnMainCns, true, m_pWndTree );
// 	}
// 	else
// 	{
// 		UIManagePtr->SetSwitchState( m_strBtnMainCns, false, m_pWndTree );
// 	}

	return NO_ERROR;
}

bool CLocalRoomCfgLogic::OnBtnFixOrCancel( TNotifyUI& msg )
{
	if (!m_bIsFix)
	{
		m_bIsFix = true;
	}
	else
	{
		m_bIsFix = false;
	}

	if ( m_bIsFix )
	{
		TTPCnsConfStatus tConfStatus = ComInterface->GetLocalCnsConfState();
		if ( tConfStatus.emState == em_CALL_CONNECTED )
		{
			ShowMessageBox((_T("�����У������޸Ļ᳡����")),false);
			m_bIsFix = false;
			return false;
		}

		BOOL bInConf = ComInterface->IsInConf();
		if ( bInConf )
		{		
			ShowMessageBox((_T("�����У������޸Ļ᳡����")),false);
			m_bIsFix = false;
			return false;
		}

		m_pm->DoCase(_T("caseSet"));

		ICncCommonOp::ShowControl(true,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("ȡ ��"),m_pm,_T("BtnFixOrCancel"));
	}
	else
	{	
		ShowCnsInfo();
		bool bIs = false;
		UpdateEthnetInfo( 0 ,0, bIs );
		UpdateNatInfo( 0 , 0, bIs );
        //������ʾѡ��
        CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckIsVidCurLine"));
        if (pCheck)
        {
           pCheck->SetCheck(ComInterface->IsVidCutLine());
        }

		ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("�� ��"),m_pm,_T("BtnFixOrCancel"));
		m_pm->DoCase(_T("caseSetCancel"));
		return true;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnBtnSave( TNotifyUI& msg )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{		
		ShowMessageBox((_T("�����У������޸Ļ᳡����")),false);
		return false;
	}

	EmIsValid bIsConfInfo = IsConfInfoChanged();
	if (bIsConfInfo == emSaveInValid)
	{
		return false;
	}
	EmIsValid bIsNet = IsNetInfoChanged();
	if (bIsNet == emSaveInValid)
	{
		return false;
	}
	EmIsValid bIsNat = IsNATChanged();
	if (bIsNat == emSaveInValid)
	{
		return false;
	}
    EmIsValid bIsIPV6 = IsIPV6Changed();
    if (bIsIPV6 == emSaveInValid)
    {
        return false;
    }


	EmTpIpNameNatSyn em = emSynInvalid;

	if (bIsConfInfo==emSaveValid && bIsNat==emSaveValid && bIsNet==emSaveValid)
	{
		em = emTpAll;
	}
	else if (bIsConfInfo==emSaveValid && bIsNat==emSaveValid && bIsNet!=emSaveValid)
	{
		em = emTpNameAndNat;
	}
	else if (bIsConfInfo==emSaveValid && bIsNat!=emSaveValid && bIsNet==emSaveValid)
	{
		em = emTpIpAndName;
	}
	else if (bIsConfInfo!=emSaveValid && bIsNat==emSaveValid && bIsNet==emSaveValid)
	{
		em = emTpIpAndNat;
	}

	if (bIsConfInfo==emSaveValid)
	{	
		String strConfName = ICncCommonOp::GetControlText( m_pm,_T("edtConfName") );   
		String strE64 = ICncCommonOp::GetControlText( m_pm, _T("edtE64") );
		TTPCnsInfo tCnsInfo = m_SelCnsInfo;
		strncpy( tCnsInfo.m_achRoomName, CT2A(strConfName.c_str()), TP_MAX_ALIAS_LEN_CNC );
		strncpy( tCnsInfo.m_achE164, CT2A(strE64.c_str()), TP_MAX_ALIAS_LEN_CNC );

		u16 wRet = ComInterface->UpdateCnsInfo( tCnsInfo, 0, em);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("����᳡����������ʧ��")),false);
			return false;
		}
	}

	if (bIsNat==emSaveValid)
	{
		CCheckBoxUI *pCheckIsNat = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsNAT") );
		if (!pCheckIsNat)
		{
			return false;
		}
		bool bIsNat = pCheckIsNat->GetCheck();
		CString strNatIP = ICncCommonOp::GetControlText( m_pm,_T("edtNATIp") ).c_str();

		TTPNatCfg tNatInfo;
		if ( !strNatIP.IsEmpty() )
		{
            UIDATAMGR->GetClearIP(strNatIP);
			ULONG dwAddr = inet_addr(CT2A(strNatIP));
			tNatInfo.dwNatIP = dwAddr;			
		}
		else
		{
			tNatInfo.dwNatIP = 0;
		}

		tNatInfo.bUsed = bIsNat;

		u16 wRet = ComInterface->UpdateNATCfg(tNatInfo, em);
		if (wRet != NO_ERROR)
		{
			ShowPopMsg( _T("����᳡NAT������ʧ��") );
			return false;
		}
	}
	
	//add begin by wangkui 2016-8-31
	EmIsValid bEmIsVidCutLine = IsVidCutLineChanged();
	if (bEmIsVidCutLine == emSaveValid)
	{
		CCheckBoxUI *pCheckIsVidCutLine = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsVidCurLine") );
		if (!pCheckIsVidCutLine)
		{
			return false;
		}
		bool bIsVidCutLine = pCheckIsVidCutLine->GetCheck();

		u16 wRet = ComInterface->SetVidCutLine(bIsVidCutLine);
		if (wRet != NO_ERROR)
		{
			ShowPopMsg( _T("����᳡������ʾ������ʧ��") );
			return false;
		}
	}
	//add end

	if (bIsNet==emSaveValid)
	{
		CString strIp = ICncCommonOp::GetControlText( m_pm,_T("edtIP") ).c_str();   
		CString strGateWay = ICncCommonOp::GetControlText( m_pm,_T("edtGateWay") ).c_str();
		CString strMask = ICncCommonOp::GetControlText( m_pm,_T("edtSubnetMask") ).c_str();


		TTPEthnetInfo tOldEthnetInfo;
		ComInterface->GetEthnetCfg( tOldEthnetInfo );

		TTPEthnetInfo tEthnetInfo;//������ Ϊ������

        UIDATAMGR->GetClearIP(strIp);
		ULONG dwAddr = inet_addr(CT2A(strIp));
		tEthnetInfo.dwIP = dwAddr;
        UIDATAMGR->GetClearIP(strGateWay);
		CT2A GatWay(strGateWay);
		dwAddr = inet_addr(GatWay);
		tEthnetInfo.dwGateWay = dwAddr;
        UIDATAMGR->GetClearIP(strMask);
		dwAddr = inet_addr(CT2A(strMask));
		tEthnetInfo.dwMask = dwAddr;

		u16 wRet = NO_ERROR;
		wRet = ComInterface->UpdateEthnetCfg( tEthnetInfo, em );
		if (wRet != NO_ERROR)
		{
			ShowPopMsg( _T("����᳡������ʧ��") );
			return false;
		}

		ICncCommonOp::SetControlText(strIp,m_pm,_T("lbIP"));
		ICncCommonOp::SetControlText(strMask,m_pm,_T("lbSubnetMask"));
		if ( strGateWay == "0.0.0.0" )
		{
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbGateWay"));
		}
		else
		{
			ICncCommonOp::SetControlText(strGateWay,m_pm,_T("lbGateWay"));
		}
		if ( tEthnetInfo.dwIP != tOldEthnetInfo.dwIP )
		{
			ShowMessageBox(_T("�޸�IP��ַ���Ͽ����ӣ����Ե�"));
			ICncCommonOp::EnableControl(false,m_pm,_T("BtnFixOrCancel"));
		}
	}
    else
    {
        bool bIs = false;
        UpdateEthnetInfo( 0 ,0, bIs );
    }

    //IPV type
    EmIsValid bEmIsIpType = IsIpTypeChanged();
    if (bEmIsIpType == emSaveValid)
    {
        EmProtocolVersion emCurProtocolVer = ComInterface->GetIpvType();
        CCheckBoxUI *pCheckIpvType = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("opSetIPv6") );
        if (pCheckIpvType)
        {
            EmProtocolVersion emProtocolVer = (pCheckIpvType->IsSelected() == false ? emIPV4 : emIPV6);
            if (emProtocolVer != emCurProtocolVer)
            {
                u16 wRet = ComInterface->SetIpvType(emProtocolVer);
                if( wRet != NO_ERROR )
                {
                    ShowPopMsg( _T("����IP��ַ���ͷ���ʧ��") );
                    return false;
                }
            }
        }
    }
    //IPV6
    EmTpIpNameNatSyn emForIpv6 = emSynInvalid;
    if (bIsConfInfo==emSaveValid && bIsNat==emSaveValid && bIsIPV6==emSaveValid)
    {
        emForIpv6 = emTpAll;
    }
    else if (bIsConfInfo==emSaveValid && bIsNat==emSaveValid && bIsIPV6!=emSaveValid)
    {
        emForIpv6 = emTpNameAndNat;
    }
    else if (bIsConfInfo==emSaveValid && bIsNat!=emSaveValid && bIsIPV6==emSaveValid)
    {
        emForIpv6 = emTpIpAndName;
    }
    else if (bIsConfInfo!=emSaveValid && bIsNat==emSaveValid && bIsIPV6==emSaveValid)
    {
        emForIpv6 = emTpIpAndNat;
    }
    if (bIsIPV6==emSaveValid)
    {
        String strIpv6Addr = ICncCommonOp::GetControlText( m_pm,_T("edtIPv6Address") );   
        String strIpv6SubLen = ICncCommonOp::GetControlText( m_pm, _T("edtSubNetLength") );
        String strIpv6GateWay = ICncCommonOp::GetControlText( m_pm, _T("edtGateWayIp") );
        String strIpv6DNS1 = ICncCommonOp::GetControlText( m_pm, _T("edtDNS1Ip") );
        String strIpv6Dns2 = ICncCommonOp::GetControlText( m_pm, _T("edtDNS2Ip") );
        TTPEthnetIPV6Info tTPEthnetIPV6Info;
        strncpy( tTPEthnetIPV6Info.m_achIP, CT2A(strIpv6Addr.c_str()), TP_IPV6_LEN + 1 );
        tTPEthnetIPV6Info.m_dwPrefix = atoi(CT2A(strIpv6SubLen.c_str()));
        strncpy( tTPEthnetIPV6Info.m_achGateWay, CT2A(strIpv6GateWay.c_str()), TP_IPV6_LEN + 1 );
        strncpy( tTPEthnetIPV6Info.m_achDns1, CT2A(strIpv6DNS1.c_str()), TP_IPV6_LEN + 1 );
        strncpy( tTPEthnetIPV6Info.m_achDns2, CT2A(strIpv6Dns2.c_str()), TP_IPV6_LEN + 1 );

        u16 wRet = NO_ERROR;
        wRet = ComInterface->SetIpv6Cfg( tTPEthnetIPV6Info, emForIpv6 );
        if (wRet != NO_ERROR)
        {
            ShowPopMsg( _T("����᳡������ʧ��") );
            return false;
        }
    }

	m_bIsFix = false;
	m_pm->DoCase(_T("caseSetCancel"));
	m_bIsFix = false;
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
	ICncCommonOp::SetControlText(_T("�� ��"),m_pm,_T("BtnFixOrCancel"));
	

	return true;
}


bool CLocalRoomCfgLogic::OnOpFontSmall( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emSize = emlittle;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emSize = emlittle;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emSize = emlittle;
		}
		break;
	}

	return true;
}

bool CLocalRoomCfgLogic::OnOpFontMid( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emSize = emMid;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emSize = emMid;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emSize = emMid;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpFontBig( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emSize = emBig;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emSize = emBig;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emSize = emBig;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpRB( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emStyle = emRightDown;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emStyle = emRightDown;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emStyle = emRightDown;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpMB( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emStyle = emMidDown;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emStyle = emMidDown;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emStyle = emMidDown;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpLB( TNotifyUI& msg )
{	
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emStyle = emLeftDown;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emStyle = emLeftDown;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emStyle = emLeftDown;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpRT( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emStyle = emRightUp;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emStyle = emRightUp;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emStyle = emRightUp;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpMT( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emStyle = emMidUp;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emStyle = emMidUp;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emStyle = emMidUp;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpLT( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emStyle = emLeftUp;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emStyle = emLeftUp;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emStyle = emLeftUp;
		}
		break;
	}
	return true;
}


bool CLocalRoomCfgLogic::OnOpColorGreen( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emColor = emGreen;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emColor = emGreen;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emColor = emGreen;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpColorBlack( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emColor = emBlack;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emColor = emBlack;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emColor = emBlack;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpColorYellow( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emColor = emYellow;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emColor = emYellow;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emColor = emYellow;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpColorBlue( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emColor = emBlue;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emColor = emBlue;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emColor = emBlue;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpColorRed( TNotifyUI& msg )
{
	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].emColor = emRed;
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].emColor = emRed;
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].emColor = emRed;
		}
		break;
	}
	return true;
}


bool CLocalRoomCfgLogic::OnOpStyle1( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emStyle = emStyleOne;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emStyle = emStyleOne;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emStyle = emStyleOne;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpStyle2( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emStyle = emStyleTwo;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emStyle = emStyleTwo;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emStyle = emStyleTwo;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpStyle3( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emStyle = emStyleThree;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emStyle = emStyleThree;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emStyle = emStyleThree;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpStyle4( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emStyle = emStyleFour;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emStyle = emStyleFour;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emStyle = emStyleFour;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpStyle5( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emStyle = emStyleFive;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emStyle = emStyleFive;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emStyle = emStyleFive;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpFullTrans( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emTransparency = emTransparent;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emTransparency = emTransparent;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emTransparency = emTransparent;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpSemiTrans( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emTransparency = emTranslucent;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emTransparency = emTranslucent;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emTransparency = emTranslucent;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpNoTrans( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emTransparency = Opaque;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emTransparency = Opaque;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emTransparency = Opaque;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerFontBig( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emSize = emBig;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emSize = emBig;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emSize = emBig;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerFontMid( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emSize = emMid;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emSize = emMid;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emSize = emMid;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerFontSmall( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emSize = emlittle;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emSize = emlittle;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emSize = emlittle;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerColorRed( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emColor = emRed;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emColor = emRed;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emColor = emRed;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerColorBlue( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emColor = emBlue;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emColor = emBlue;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emColor = emBlue;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerColorYellow( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emColor = emYellow;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emColor = emYellow;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emColor = emYellow;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerColorBlack( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emColor = emBlack;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emColor = emBlack;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emColor = emBlack;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnOpBannerColorGreen( TNotifyUI& msg )
{
	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].emColor = emGreen;
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].emColor = emGreen;
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].emColor = emGreen;
		}
		break;
	}
	return true;
}

bool CLocalRoomCfgLogic::OnCheckIsNAT( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

	bool bCheck = false;
	if (pCheckBox && pCheckBox->GetCheck())
	{
		bCheck = true;
	}
	ICncCommonOp::EnableControl(bCheck,m_pm,_T("edtNATIp"));
	return true;
}

bool CLocalRoomCfgLogic::OnCheckIPv4Sel(TNotifyUI& msg)
{
    m_pm->DoCase(_T("CaseSelIPv4"));
    return true;
}

bool CLocalRoomCfgLogic::OnCheckIPv6Sel(TNotifyUI& msg)
{
    m_pm->DoCase(_T("CaseSelIPv6"));
    return true;
}

EmIsValid CLocalRoomCfgLogic::IsConfInfoChanged()
{
	CEditUI *pEdtConfName = (CEditUI*)ICncCommonOp::FindControl( m_pm,_T("edtConfName") );   
	CEditUI *pEdtE64 = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtE64") );

	EmIsValid EmChange = emSaveNochange;
	CString strConfName;
	CString strE64;
	if (pEdtConfName)
	{
		strConfName = pEdtConfName->GetText();
		if ( strcmp( m_SelCnsInfo.m_achRoomName, (CT2A)strConfName) != 0 )
		{	
			if(strConfName.IsEmpty())
			{
				ShowMessageBox((_T("�᳡���Ʋ���Ϊ��")),false);
				pEdtConfName->SetFocusX();
				return emSaveInValid;
			}

			if ( !UIDATAMGR->IsValidTPStr( (LPCTSTR)strConfName ) )
			{ 
				CString str; 
				str.Format( _T("�᳡���Ʋ����԰����ո������е������ַ� [ %s ]"), INVALID_ALIAS_FOR_SHOW );
				ShowMessageBox((str),false);
				pEdtConfName->SetFocusX();
				return emSaveInValid;
			}
			EmChange = emSaveValid;
		}
	}
	if (pEdtE64)
	{
		strE64 = pEdtE64->GetText();
		if (strcmp( m_SelCnsInfo.m_achE164, (CT2A)strE64) != 0 )
		{
			if(!strE64.IsEmpty() && !CCallAddr::IsValidE164((CT2A)strE64))
			{
				ShowMessageBox((_T("�᳡���벻�Ϸ���E164��ֻ�ܰ������ּ�*,��")),false);
				pEdtE64->SetFocusX();
				return emSaveInValid;
			}

			if (EmChange != emSaveValid)
			{
				EmChange = emSaveValid;
			}
		}
	}

	return EmChange;
}

EmIsValid CLocalRoomCfgLogic::IsNetInfoChanged()
{
	CEditUI *pEdtIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtIP") );
	CEditUI *pEdtGateWay = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtGateWay") );
	CEditUI *pEdtSubnetMask = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtSubnetMask") );

	CString strIp;
	CString strGateWay;
	CString strMask;

	if (pEdtIp && pEdtGateWay && pEdtSubnetMask)
	{		

		strIp = pEdtIp->GetText();
		strGateWay = pEdtGateWay->GetText();
		strMask = pEdtSubnetMask->GetText();

		if (strIp.IsEmpty() && strGateWay.IsEmpty() && strMask.IsEmpty())
		{
			return emSaveInValid;
		}

		if ( strGateWay == "" )
		{
			strGateWay = "0.0.0.0";
		}

		TTPEthnetInfo tOldEthnetInfo;
		ComInterface->GetEthnetCfg( tOldEthnetInfo );

		TTPEthnetInfo tEthnetInfo;//������ Ϊ������
		TTPEthnetInfo tEthnetInfoVer;//��֤�� Ϊ������

        UIDATAMGR->GetClearIP(strIp);
		ULONG dwAddr = inet_addr(CT2A(strIp));
		tEthnetInfo.dwIP = dwAddr;
		tEthnetInfoVer.dwIP = ntohl(dwAddr);
        UIDATAMGR->GetClearIP(strGateWay);
		CT2A GatWay(strGateWay);
		dwAddr = inet_addr(GatWay);
		tEthnetInfo.dwGateWay = dwAddr;
		tEthnetInfoVer.dwGateWay = ntohl(dwAddr);
        UIDATAMGR->GetClearIP(strMask);
		dwAddr = inet_addr(CT2A(strMask));
		tEthnetInfo.dwMask = dwAddr;
		tEthnetInfoVer.dwMask = ntohl(dwAddr);

		if ( strIp.IsEmpty())
		{
			ShowMessageBox((_T("CNS IP��ַ����Ϊ��")),false);
			pEdtIp->SetFocusX();
			return emSaveInValid;
		}

		if(!CCallAddr::IsValidIpV4((CT2A(strIp))) )
		{
			ShowMessageBox((_T("CNS IP��ַ�Ƿ�")),false);
			pEdtIp->SetFocusX();
			return emSaveInValid;
		}

		//char* achErrStr = NULL;
		char achErrStr[256] = {0};
		if ( !CCallAddr::IsValidCallIP( tEthnetInfoVer.dwIP, achErrStr, 0 ) ) 
		{
			CString str(achErrStr);
			if (str.IsEmpty())
			{
				str = _T("CNS IP��ַ�Ƿ�");
			}
			ShowMessageBox(str);
			pEdtIp->SetFocusX();
			return emSaveInValid;
		}

		if ( strMask.IsEmpty())
		{
			ShowMessageBox((_T("�������벻��Ϊ��")),false);
			pEdtSubnetMask->SetFocusX();
			return emSaveInValid;
		}

		if(!CCallAddr::IsValidIpMask(tEthnetInfoVer.dwMask))
		{
			ShowMessageBox((_T("����������Ч������������������ڵģ���������Ч������")),false);
			pEdtSubnetMask->SetFocusX();
			return emSaveInValid;
		}
		
		if(!CCallAddr::IsValidDevIP( tEthnetInfoVer.dwIP, tEthnetInfoVer.dwMask, achErrStr, 0 ))
		{
			CString str(achErrStr);
			if (str.IsEmpty())
			{
				str = _T("IP��ַ�Ƿ�");
			}
			ShowMessageBox(str);
			pEdtSubnetMask->SetFocusX();
			return emSaveInValid;
		}

		if((strGateWay != "0.0.0.0") && !CCallAddr::IsValidIpV4( CT2A(strGateWay) ))
		{
			ShowMessageBox((_T("����IP��ַ�Ƿ�")),false);
			pEdtGateWay->SetFocusX();
			return emSaveInValid;
		}

		if ( strGateWay != "0.0.0.0" )
		{
			DWORD dwNetID = tEthnetInfoVer.dwIP & tEthnetInfoVer.dwMask;
			DWORD dwNetGate = tEthnetInfoVer.dwGateWay & tEthnetInfoVer.dwMask;
			if ( dwNetGate != dwNetID )
			{
				int nReslut = ShowMessageBox((_T("Ĭ�����ز�����IP��ַ���������붨���ͬһ�����(����)��,�Ƿ񱣴�����ã�")),true);
				if ( IDOK != nReslut )
				{
					pEdtGateWay->SetFocusX();
					return emSaveInValid; 
				}  
			}
		}

		if ( tEthnetInfo.dwIP != tOldEthnetInfo.dwIP || tEthnetInfo.dwGateWay != tOldEthnetInfo.dwGateWay 
			||  tEthnetInfo.dwMask != tOldEthnetInfo.dwMask)
		{
			return emSaveValid;
		}
	}

	return emSaveNochange;
}

EmIsValid CLocalRoomCfgLogic::IsNATChanged()
{
	CEditUI *pEdtNAT = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtNATIp") );
	CCheckBoxUI *pCheckIsNat = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsNAT") );
	CString strNatIP;
	if (pEdtNAT && pCheckIsNat)
	{		
		bool bIsNat = pCheckIsNat->GetCheck();
		strNatIP = pEdtNAT->GetText();

		TTPNatCfg tNatInfo;
		if ( !strNatIP.IsEmpty() )
		{
            UIDATAMGR->GetClearIP(strNatIP);
			ULONG dwAddr = inet_addr(CT2A(strNatIP));
			tNatInfo.dwNatIP = dwAddr;			
		}
		else
		{
			tNatInfo.dwNatIP = 0;
		}

		tNatInfo.bUsed = bIsNat;

		TTPNatCfg tOldNatInfo;
		ComInterface->GetNATCfg(tOldNatInfo);

		if (bIsNat)
		{
			if ( strNatIP.IsEmpty() )
			{
				ShowMessageBox((_T("NAT��ַ����Ϊ��")),false);
				pEdtNAT->SetFocusX();
				return emSaveInValid;
			}

			if(!CCallAddr::IsValidIpV4((CT2A(strNatIP))) )//inet_addr
			{
				ShowMessageBox((_T("NAT��ַ�Ƿ�")),false);
				pEdtNAT->SetFocusX();
				return emSaveInValid;
			}

			if ( !strNatIP.IsEmpty() && !CCallAddr::IsValidCallIP( ntohl(tNatInfo.dwNatIP), NULL, 0) ) 
			{
				ShowMessageBox((_T("NAT��ַ�Ƿ�")),false);
				pEdtNAT->SetFocusX();
				return emSaveInValid;
			}
		}

		if ( tNatInfo.bUsed != tOldNatInfo.bUsed || (tNatInfo.bUsed && (tNatInfo.dwNatIP != tOldNatInfo.dwNatIP)))
		{
			return emSaveValid;
		}
	}

	return emSaveNochange;
}

EmIsValid CLocalRoomCfgLogic::IsVidCutLineChanged()
{
	bool bOldIsVidCutLine = (bool)ComInterface->IsVidCutLine();
	
	CCheckBoxUI *pCheckIsVidCutLine = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsVidCurLine") );
	if (pCheckIsVidCutLine)
	{
		bool bIsVidCutLine = pCheckIsVidCutLine->GetCheck();

		if ( bIsVidCutLine != bOldIsVidCutLine)
		{
			return emSaveValid;
		}
	}
	return emSaveNochange;
}

EmIsValid CLocalRoomCfgLogic::IsIpTypeChanged()
{
    EmProtocolVersion emIpType = ComInterface->GetIpvType();

    CCheckBoxUI *pCheckIsIPV6 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("opSetIPv6") );
    if (pCheckIsIPV6)
    {
        EmProtocolVersion emUIIpType = pCheckIsIPV6->GetCheck() ? emIPV6 : emIPV4;

        if ( emIpType != emUIIpType)
        {
            return emSaveValid;
        }
    }
    return emSaveNochange;
}

EmIsValid CLocalRoomCfgLogic::IsIPV6Changed()
{
    CEditUI *pEdtIp = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtIPv6Address") );
    CEditUI *pEdtSubnetlen = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtSubnetMask") );
    CEditUI *pEdtGateWay = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtGateWay") );
    CEditUI *pEdtDNS1 = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtGateWay") );
    CEditUI *pEdtDNS2 = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtGateWay") );

    CString strIp;
    CString strSunLen;
    CString strGateWay;
    CString strDNS1;
    CString strDNS2;

    if (pEdtIp && pEdtSubnetlen && pEdtGateWay && pEdtDNS1 && pEdtDNS2)
    {		

        strIp = pEdtIp->GetText();
        strSunLen = pEdtSubnetlen->GetText();
        strGateWay = pEdtGateWay->GetText();
        strDNS1 = pEdtDNS1->GetText();
        strDNS2 = pEdtDNS2->GetText();

        if (strIp.IsEmpty() && strSunLen.IsEmpty() && strGateWay.IsEmpty() && strDNS1.IsEmpty() && strDNS2.IsEmpty())
        {
            return emSaveInValid;
        }

        TTPEthnetIPV6Info tTPEthnetIPV6Info;
        ComInterface->GetIpv6Cfg( tTPEthnetIPV6Info );

        if(!UIDATAMGR->IsValidIpV6((CT2A(strIp))) )
        {
            ShowMessageBox((_T("CNS IPV6��ַ�Ƿ�")),false);
            pEdtIp->SetFocusX();
            return emSaveInValid;
        }

        if(!UIDATAMGR->IsValidIpV6((CT2A(strGateWay))) )
        {
            ShowMessageBox((_T("CNS ���ص�ַ�Ƿ�")),false);
            pEdtGateWay->SetFocusX();
            return emSaveInValid;
        }

        if(!UIDATAMGR->IsValidIpV6((CT2A(strDNS1))) )
        {
            ShowMessageBox((_T("CNS DNS1��ַ�Ƿ�")),false);
            pEdtDNS1->SetFocusX();
            return emSaveInValid;
        }

        if(!UIDATAMGR->IsValidIpV6((CT2A(strDNS2))) )
        {
            ShowMessageBox((_T("CNS DNS2��ַ�Ƿ�")),false);
            pEdtDNS2->SetFocusX();
            return emSaveInValid;
        }

        u32 dwSubLen = atoi(CT2A(strSunLen));
        if (dwSubLen < 0 || dwSubLen > 128)
        {
            ShowMessageBox((_T("CNS ����ǰ׺���ȷǷ�")),false);
            pEdtSubnetlen->SetFocusX();
            return emSaveInValid;
        }

        //У������
        if ( strcmp(tTPEthnetIPV6Info.m_achIP, CT2A(strIp)) != 0 ||
             strcmp(tTPEthnetIPV6Info.m_achGateWay, CT2A(strGateWay)) != 0 || 
             strcmp(tTPEthnetIPV6Info.m_achDns1, CT2A(strDNS1)) != 0 || 
             strcmp(tTPEthnetIPV6Info.m_achDns2, CT2A(strDNS2)) != 0 || 
             tTPEthnetIPV6Info.m_dwPrefix != dwSubLen)
        {
            return emSaveValid;
        }
    }
    return emSaveNochange;
}

bool CLocalRoomCfgLogic::OnScreenLogoItemClick( TNotifyUI& msg )
{
	CEditUI *pEdtConfName = (CEditUI*)ICncCommonOp::FindControl( m_pm,_T("edtLogo") );   
	CString strConfName;
	if (pEdtConfName)
	{
		strConfName = pEdtConfName->GetText();
	}
	//��¼�л�ǰ��Logo
	if (!strConfName.IsEmpty())
	{
		switch(m_dwLogoScreenSelId)
		{
		case 0:
			{
				strncpy(m_mapLogoInfo[0].achLogoName, (CT2A)strConfName, TP_MAX_ALIAS_LEN_CNC-1);
			}
			break;
		case 1:
			{
				strncpy(m_mapLogoInfo[1].achLogoName, (CT2A)strConfName, TP_MAX_ALIAS_LEN_CNC-1);
			}
			break;
		case 2:
			{
				strncpy(m_mapLogoInfo[2].achLogoName, (CT2A)strConfName, TP_MAX_ALIAS_LEN_CNC-1);
			}
			break;
		}
	}

	m_dwLogoScreenSelId = msg.wParam;

	switch(m_dwLogoScreenSelId)
	{
	case 0:
		{
			m_mapLogoInfo[0].bIsShowLogo = m_mapIsLogo[0];
			UpdateLogoTag(m_mapLogoInfo[0]);
		}
		break;
	case 1:
		{
			m_mapLogoInfo[1].bIsShowLogo = m_mapIsLogo[1];
			UpdateLogoTag(m_mapLogoInfo[1]);
		}
		break;
	case 2:
		{
			m_mapLogoInfo[2].bIsShowLogo = m_mapIsLogo[2];
			UpdateLogoTag(m_mapLogoInfo[2]);
		}
		break;
	}

	if ( m_mapIsLogo[m_dwLogoScreenSelId])
	{
		
		m_pm->DoCase(_T("caseLogoSetSel"));
	}
	else
	{
		m_pm->DoCase(_T("caseLogoSetUnSel"));
	}

	return false;
}

bool CLocalRoomCfgLogic::OnScreenBannerItemClick( TNotifyUI& msg )
{
	CEditUI *pEdtBanner = (CEditUI*)ICncCommonOp::FindControl( m_pm,_T("edtBanner") );   
	CString strBanner;
	if (pEdtBanner)
	{
		strBanner = pEdtBanner->GetText();
	}
	//��¼�л�ǰ��Banner
	if (!strBanner.IsEmpty())
	{
		switch(m_dwBannerScreenSelId)
		{
		case 0:
			{
				strncpy(m_mapBannerInfo[0].achBannerName, (CT2A)strBanner, TP_MAX_ALIAS_LEN);
			}
			break;
		case 1:
			{
				strncpy(m_mapBannerInfo[1].achBannerName, (CT2A)strBanner, TP_MAX_ALIAS_LEN);
			}
			break;
		case 2:
			{
				strncpy(m_mapBannerInfo[2].achBannerName, (CT2A)strBanner, TP_MAX_ALIAS_LEN);
			}
			break;
		}
	}

	m_dwBannerScreenSelId = msg.wParam;

	switch(m_dwBannerScreenSelId)
	{
	case 0:
		{
			m_mapBannerInfo[0].bIsShowBanner = m_mapIsBanner[0];
			UpdateBannerTag(m_mapBannerInfo[0]);
		}
		break;
	case 1:
		{
			m_mapBannerInfo[1].bIsShowBanner = m_mapIsBanner[1];
			UpdateBannerTag(m_mapBannerInfo[1]);
		}
		break;
	case 2:
		{
			m_mapBannerInfo[2].bIsShowBanner = m_mapIsBanner[2];
			UpdateBannerTag(m_mapBannerInfo[2]);
		}
		break;
	}

	if (m_mapIsBanner[m_dwBannerScreenSelId])
	{
		m_pm->DoCase(_T("caseBannerSetSel"));
	}
	else
	{
		m_pm->DoCase(_T("caseBannerSetUnSel"));
	}

	return false;
}

void CLocalRoomCfgLogic::GetCharExtent( IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize )
{
	HDC hDc = ::GetDC( NULL ); 
	Graphics graph(hDc);
	RectF rcf;
	graph.MeasureString(strCharacters,-1,pFont,PointF(0,0),&rcf); 

	cSize.cx = rcf.Width;
	cSize.cy =  rcf.Height;

	if ( rcf.Width > cSize.cx )
	{
		cSize.cx += 1;
	}

	if ( rcf.Height > cSize.cy )
	{
		cSize.cy += 1;
	}

	::ReleaseDC(NULL, hDc ); 
}

BOOL CLocalRoomCfgLogic::MakeImgByChar(const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, 
	const Color clText, const Color clBorder, const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName,
    bool bIsLogo, int nImgtype, int nWidth, int nHeight)
{
	HDC hDc = ::GetDC( NULL );
	HDC hDcMem =  CreateCompatibleDC( hDc); 

	Gdiplus::Font *pFont = new Gdiplus::Font(strFontFamily,(bIsLogo? nFontSizeByPx*72/96 : nFontSizeByPx*72/72),emFontStyle);//DPI��96 ����px�� *72/96 

	CString txt(strCharacters);
	BSTR bstrText = txt.AllocSysString();

	// ���㵱ǰ���ֵĳ��ȣ���ȷ��ͼƬ�ĳ��Ϳ�
	CSize cSize(0,0);
	GetCharExtent( bstrText,pFont,cSize);
	cSize.cx += borderWidthByPx;
	cSize.cy += borderWidthByPx;
	while ( cSize.cx % 4 != 0 )
	{
		cSize.cx++;
	}

	if (nWidth>0)
	{
		cSize.cx = nWidth;
	}
	
	if (nHeight>0)
	{
		cSize.cy = nHeight;
	}

	while ( cSize.cy % 4 != 0 )
	{
		cSize.cy++;
	}


	BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
	int nBytesPerLine = cSize.cx;//((cSize.cx * 32 + 31) & (~31)) >> 3;
	if (cSize.cx%4 != 0)
	{
		nBytesPerLine = cSize.cx + 4;
	}
	stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
	stBmpInfoHeader.biWidth = cSize.cx;   
	stBmpInfoHeader.biHeight = cSize.cy;   
	stBmpInfoHeader.biPlanes = 1;
	stBmpInfoHeader.biBitCount = 32;   
	stBmpInfoHeader.biCompression = BI_RGB;   
	stBmpInfoHeader.biClrUsed = 0;   
	stBmpInfoHeader.biSizeImage = nBytesPerLine * cSize.cy;	

	PUINT32 pvBits = NULL;   
	HBITMAP hBtMap = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);
	if (hBtMap)   
	{   
		::SelectObject(  hDcMem, hBtMap); 
	}


	Graphics graph(hDcMem); 
	graph.Clear( clBkGrd ); 

	if ( strFontFamily != _T("����"))
	{
		graph.SetSmoothingMode(SmoothingModeAntiAlias);     
		graph.SetInterpolationMode(InterpolationModeHighQualityBicubic); 
		// 		graph.SetSmoothingMode( SmoothingModeHighQuality );
		graph.SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
	}
	else
	{
		//graph.SetSmoothingMode(SmoothingModeHighQuality); 

		// 		ARGB argb = clText.GetValue(); 
		// 		argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
		// 		(const_cast<Color &>(clText)).SetValue ( argb );
		// 				
		// 		argb = clBorder.GetValue(); 
		// 		argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
		//         (const_cast<Color &>(clBorder)).SetValue( argb );
	} 	

	StringFormat  cStringFormat ;
    if (nImgtype == 1)
    {
        cStringFormat.SetAlignment( StringAlignmentNear );
    }
    else if (nImgtype == 2)
    {
        cStringFormat.SetAlignment( StringAlignmentFar );
    }
    else
    {
        cStringFormat.SetAlignment( StringAlignmentCenter );
    }
	//cStringFormat.SetAlignment( StringAlignmentCenter );//StringAlignmentNear  ��Ϊ����
	cStringFormat.SetLineAlignment(StringAlignmentCenter);
	cStringFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces );

	GraphicsPath txtPath(FillModeWinding);
	FontFamily fm;
	pFont->GetFamily(&fm); 
	
	txtPath.AddString(bstrText, -1 ,&fm, emFontStyle , (bIsLogo ? nFontSizeByPx *72/96 : nFontSizeByPx *72/72) /* + borderWidthByPx*/ , RectF(0, 0, cSize.cx , cSize.cy ),&cStringFormat); 


	SolidBrush brush( clText );  
	Pen borderPen( clBorder, borderWidthByPx *2 ); 
	borderPen.SetLineJoin(LineJoinRound);


	graph.DrawPath(&borderPen,&txtPath);
	graph.FillPath(&brush,&txtPath); 

	SysFreeString( bstrText ); 
	BOOL bSuccess = SaveBitmapToFile(hBtMap,strFileName);
	DeleteObject(hBtMap);
	DeleteObject(hDcMem);
	::ReleaseDC(NULL, hDc );
	delete pFont;
	pFont = NULL;
	return bSuccess;
}

BOOL CLocalRoomCfgLogic::SaveBitmapToFile(HBITMAP   hBitmap, CString szfilename)
{
	HDC hDC; //   �豸������    
	int iBits; //   ��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ��� 
	WORD wBitCount; //   λͼ��ÿ��������ռ�ֽ���   
	DWORD dwPaletteSize = 0   ; //   �����ɫ���С��  λͼ�������ֽڴ�С  �� 
	//   λͼ�ļ���С  ��  д���ļ��ֽ���

	DWORD dwBmBitsSize   ;  
	DWORD dwDIBSize, dwWritten   ;  
	BITMAP Bitmap;      
	BITMAPFILEHEADER bmfHdr; //λͼ���Խṹ 
	BITMAPINFOHEADER bi; //λͼ�ļ�ͷ�ṹ  
	LPBITMAPINFOHEADER lpbi;   //λͼ��Ϣͷ�ṹ   
	HANDLE fh,   hDib,   hPal,hOldPal = NULL   ; //ָ��λͼ��Ϣͷ�ṹ,�����ļ��������ڴ�������ɫ����

	//����λͼ�ļ�ÿ��������ռ�ֽ��� 
// 	hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL); 
// 	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES)  ;  
// 	DeleteDC(hDC)   ;  
// 	if (iBits <= 1)
// 	{
// 		wBitCount = 1;
// 	}
// 	else if (iBits <= 4)
// 	{
// 		wBitCount = 4;
// 	}
// 	else if (iBits <= 8)
// 	{
// 		wBitCount = 8;
// 	}
// 	else if (iBits <= 24)
// 	{
// 		wBitCount = 24;
// 	}
// 	else if (iBits <= 32)
// 	{
// 		wBitCount = 32;
// 	}  
	wBitCount = 24;
	//�����ɫ���С 

	if (wBitCount <= 8)
	{
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD)   ;
	} 

	//����λͼ��Ϣͷ�ṹ 

	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap)   ;  
	bi.biSize = sizeof(BITMAPINFOHEADER);  
	bi.biWidth = Bitmap.bmWidth;  
	bi.biHeight = Bitmap.bmHeight;   
	bi.biPlanes = 1;  
	bi.biBitCount = wBitCount;     
	bi.biCompression = BI_RGB;  
	bi.biSizeImage = 0;  
	bi.biXPelsPerMeter = 0;  
	bi.biYPelsPerMeter = 0;  
	bi.biClrUsed = 0;  
	bi.biClrImportant = 0;   
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight   ;
	//Ϊλͼ���ݷ����ڴ� 
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER))   ;   
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib)   ;
	*lpbi = bi;  
	//   �����ɫ��  
	hPal = GetStockObject(DEFAULT_PALETTE);  
	if (hPal)
	{
		hDC = ::GetDC(NULL);  
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE)   ;  
		RealizePalette(hDC)   ;
	} 

	//   ��ȡ�õ�ɫ�����µ�����ֵ 
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);   

	//�ָ���ɫ��   
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC)   ;   
		::ReleaseDC(NULL, hDC)   ;
	} 
	//����λͼ�ļ�
	fh = CreateFile(szfilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL)   ; 
	if (fh == INVALID_HANDLE_VALUE)
	{
		return   false;
	}    

	//   ����λͼ�ļ�ͷ 

	bmfHdr.bfType = 0x4D42;  //   "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;    
	bmfHdr.bfSize = dwDIBSize;  
	bmfHdr.bfReserved1 = 0;  
	bmfHdr.bfReserved2 = 0;  
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;  
	//   д��λͼ�ļ�ͷ 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);  
	//   д��λͼ�ļ��������� 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);  
	//�����ڴ����     
	GlobalUnlock(hDib);   
	GlobalFree(hDib);  
	CloseHandle(fh);  
	return   true;
}

BOOL CLocalRoomCfgLogic::UploadLogoCoreFirstLogin( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ )
{
    CString strIpAddr;

    m_cFtpLogo.SethWnd( m_pm->GetPaintWindow() );
    m_cFtpLogo.RegisterMsgHandle( WM_CNC_FL_FTPCONFSIGNPROGRESS );

    u32 dwIp;
    ComInterface->GetLoginIp(dwIp);		
    struct in_addr addrIPAddr;
    addrIPAddr.S_un.S_addr = htonl(dwIp);
    strIpAddr = CA2T(inet_ntoa(addrIPAddr));

    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        ShowPopMsg(_T("FTP�ϴ�������δ����!"));
        return FALSE;
    }
    BOOL32 bRet = m_cFtpLogo.SetServerParam( strIpAddr, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/*_T("kedacomTP")*/ );
    if ( !bRet )
    {
        ShowPopMsg((_T("����FTP�ϴ�������ʧ��!")));
        //ʧ����� ��ֹ�����ٴ�
        m_vecLogoFile.clear();
        return FALSE;
    }

    String strRemoteFilePath = strRemotePath;
    strRemoteFilePath += strCheckFileName;
    m_cFtpLogo.SetAutoEndFtpFile(bAutoEnd/*FALSE*/);

    if ( !m_cFtpLogo.BeginUpload(  strRemoteFilePath.c_str(), strLocalFile.c_str(),FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
    {
        ShowPopMsg((_T("�ϴ��ļ�ʧ�ܣ���������")));
        m_cFtpLogo.SetAutoEndFtpFile(TRUE);
        //ʧ����� ��ֹ�����ٴ�
        m_vecLogoFile.clear();
        return FALSE;
    }
    return TRUE;
}

BOOL CLocalRoomCfgLogic::UploadLogoCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ )
{
	CString strIpAddr;

	m_cFtpLogo.SethWnd( m_pm->GetPaintWindow() );
	m_cFtpLogo.RegisterMsgHandle( WM_CNC_FTPCONFSIGNPROGRESS );

	u32 dwIp;
	ComInterface->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = CA2T(inet_ntoa(addrIPAddr));

	TTPFtpInfo tTPFtpInfo;
	ComInterface->GetCnFtpInfo(tTPFtpInfo);
	if (tTPFtpInfo.bOpen == FALSE)
	{
		ShowPopMsg(_T("FTP�ϴ�������δ����!"));
		return FALSE;
	}
	BOOL32 bRet = m_cFtpLogo.SetServerParam( strIpAddr, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/*_T("kedacomTP")*/ );
	if ( !bRet )
	{
		ShowPopMsg((_T("����FTP�ϴ�������ʧ��!")));
		//ʧ����� ��ֹ�����ٴ�
		m_vecLogoFile.clear();
		return FALSE;
	}

	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	m_cFtpLogo.SetAutoEndFtpFile(bAutoEnd/*FALSE*/);

	if ( !m_cFtpLogo.BeginUpload(  strRemoteFilePath.c_str(), strLocalFile.c_str(),FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
	{
		ShowPopMsg((_T("�ϴ��ļ�ʧ�ܣ���������")));
		m_cFtpLogo.SetAutoEndFtpFile(TRUE);
		//ʧ����� ��ֹ�����ٴ�
		m_vecLogoFile.clear();
		return FALSE;
	}
	return TRUE;
}

BOOL CLocalRoomCfgLogic::UploadBannerCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ )
{
	CString strIpAddr;

	m_cFtpBanner.SethWnd( m_pm->GetPaintWindow() );
	m_cFtpBanner.RegisterMsgHandle( WM_CNC_FTPCONFBANNERPROGRESS );

	u32 dwIp;
	ComInterface->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = CA2T(inet_ntoa(addrIPAddr));

	TTPFtpInfo tTPFtpInfo;
	ComInterface->GetCnFtpInfo(tTPFtpInfo);
	if (tTPFtpInfo.bOpen == FALSE)
	{
		ShowPopMsg(_T("FTP�ϴ�������δ����!"));
		return FALSE;
	}
	BOOL32 bRet = m_cFtpBanner.SetServerParam( strIpAddr, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/*_T("kedacomTP")*/ );
	if ( !bRet )
	{
		ShowPopMsg(_T("����FTP�ϴ�������ʧ��!"));
		//ʧ����� ��ֹ�����ٴ�
		m_vecBannerFile.clear();
		return FALSE;
	}

	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	m_cFtpBanner.SetAutoEndFtpFile(bAutoEnd/*FALSE*/);

	if ( !m_cFtpBanner.BeginUpload(  strRemoteFilePath.c_str(), strLocalFile.c_str(),FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
	{
		ShowPopMsg(_T("�ϴ��ļ�ʧ�ܣ���������"));
		m_cFtpBanner.SetAutoEndFtpFile(TRUE);
		//ʧ����� ��ֹ�����ٴ�
		m_vecBannerFile.clear();
		return FALSE;
	}
	return TRUE;
}

bool CLocalRoomCfgLogic::OnLogoNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPLogoInfo tTPLogoInfo;
	ComInterface->GetLogoInfo( tTPLogoInfo );

	for (int i=0; i<3; i++)
	{
		switch(i)
		{
		case 0:
			m_mapLogoInfo[0] = tTPLogoInfo.tFirsLogoInfo;
			break;
		case 1:
			m_mapLogoInfo[1] = tTPLogoInfo.tSecondLogoInfo;
			break;	
		case 2:
			m_mapLogoInfo[2] = tTPLogoInfo.tThirdLogoInfo;
		}
	}

	UpdateLogoScreen(tTPLogoInfo);
	UpdateLogoCheck();

	return true;
}

bool CLocalRoomCfgLogic::OnFirstLoginAfterUpdateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    UploadLogoImg();
    return true;
}

bool CLocalRoomCfgLogic::OnLogoInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bSuccess = (BOOL)wParam;
	if (!bSuccess)
	{
		ShowMessageBox(_T("̨������ʧ��"));
	}

	u8 wIndex = (u8)lParam;
	TTPLogoInfo tTPLogoInfo;
	ComInterface->GetLogoInfo( tTPLogoInfo );

	switch(wIndex)
	{
	case 0:
		m_mapLogoInfo[0] = tTPLogoInfo.tFirsLogoInfo;
		UpdateLogoScreen(m_mapLogoInfo[0],wIndex);
		break;
	case 1:
		m_mapLogoInfo[1] = tTPLogoInfo.tSecondLogoInfo;
		UpdateLogoScreen(m_mapLogoInfo[1],wIndex);
		break;	
	case 2:
		m_mapLogoInfo[2] = tTPLogoInfo.tThirdLogoInfo;
		UpdateLogoScreen(m_mapLogoInfo[2],wIndex);
	}

	return true;
}

bool CLocalRoomCfgLogic::OnBannerNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPBannerInfo tTPBannerInfo;
	ComInterface->GetBannerInfo( tTPBannerInfo );

	for (int i=0; i<3; i++)
	{
		switch(i)
		{
		case 0:
			m_mapBannerInfo[0] = tTPBannerInfo.tFirstBannerInfo;
			break;
		case 1:
			m_mapBannerInfo[1] = tTPBannerInfo.tSeconfBannerInfo;
			break;	
		case 2:
			m_mapBannerInfo[2] = tTPBannerInfo.tThirdBannerInfo;
		}
	}

	UpdateBannerScreen(tTPBannerInfo);
	UpdateBannerCheck();

	return true;
}

bool CLocalRoomCfgLogic::OnBannerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bSuccess = (BOOL)wParam;
	if (!bSuccess)
	{
		ShowMessageBox(_T("�������ʧ��"));
	}

	u8 wIndex = (u8)lParam;
	TTPBannerInfo tTPBannerInfo;
	ComInterface->GetBannerInfo( tTPBannerInfo );

	switch(wIndex)
	{
	case 0:
		m_mapBannerInfo[0] = tTPBannerInfo.tFirstBannerInfo;
		UpdateBannerScreen(m_mapBannerInfo[0],wIndex);
		break;
	case 1:
		m_mapBannerInfo[1] = tTPBannerInfo.tSeconfBannerInfo;
		UpdateBannerScreen(m_mapBannerInfo[1],wIndex);
		break;	
	case 2:
		m_mapBannerInfo[2] = tTPBannerInfo.tThirdBannerInfo;
		UpdateBannerScreen(m_mapBannerInfo[2],wIndex);
	}

	return true;
}


bool CLocalRoomCfgLogic::UpdateLogoTag( TTPShowLogo tLogoInfo )
{
	EmTpColor emTpColor = tLogoInfo.emColor;
	EmTpSize emSize = tLogoInfo.emSize;
	EmTpLogoStyle emStyle = tLogoInfo.emStyle;

	CString strPos = _T("");
	CString strContent(tLogoInfo.achLogoName);

	CString strTextSet = _T("");
	CString strTextColor = _T("");
	switch(emSize)
	{
	case emBig:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpFontBig") );
		strTextSet = strTextSet + _T("��");
		break;
	case emMid:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpFontMid") );
		strTextSet = strTextSet + _T("��");
		break;	
	case emlittle:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpFontSmall") );
		strTextSet = strTextSet + _T("С");
		break;	
	}

	switch(emTpColor)
	{
	case emRed:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpColorRed") );
		strTextColor = _T("��");
		break;
	case emBlue:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpColorBlue") );
		strTextColor = _T("��");
		break;	
	case emYellow:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpColorYellow") );
		strTextColor = _T("��");
		break;	
	case emBlack:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpColorBlack") );
		strTextColor = _T("��");
		break;
	case emGreen:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpColorGreen") );
		strTextColor = _T("��");
		break;	
	}

	switch(emStyle)
	{
	case emLeftUp:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpLT") );
		strPos = _T("����");
		break;
	case emLeftDown:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpLB") );
		strPos = _T("����");
		break;	
	case emMidUp:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpMT") );
		strPos = _T("����");
		break;	
	case emMidDown:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpMB") );
		strPos = _T("����");
		break;
	case emRightUp:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpRT") );
		strPos = _T("����");
		break;	
	case emRightDown:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpRB") );
		strPos = _T("����");
		break;	
	}

	ICncCommonOp::SetControlText( strPos, m_pm, _T("lblogoPos") ); 
	ICncCommonOp::SetControlText( strTextColor, m_pm, _T("lblogoColor") );
	ICncCommonOp::SetControlText( strContent, m_pm, _T("edtLogo") );
	ICncCommonOp::SetControlText( strTextSet, m_pm, _T("lblogoFontSize") );
	return true;
}
bool CLocalRoomCfgLogic::UpdateBannerTag( TTPShowBanner tBannerInfo )
{
	EmTpColor emTpColor = tBannerInfo.emColor;
	EmTpSize emSize = tBannerInfo.emSize;
	EmTpStyle emStyle = tBannerInfo.emStyle;
	emTpTransparency emTransparency = tBannerInfo.emTransparency;

	CString strStyle = _T("���");
	CString strContent(tBannerInfo.achBannerName);

	switch(emStyle)
	{
	case emStyleOne:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpStyle1") );
		strStyle = strStyle + _T("01");
		break;
	case emStyleTwo:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpStyle2") );
		strStyle = strStyle + _T("02");
		break;	
	case emStyleThree:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpStyle3") );
		strStyle = strStyle + _T("03");
		break;	
	case emStyleFour:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpStyle4") );
		strStyle = strStyle + _T("04");
		break;	
	case emStyleFive:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpStyle5") );
		strStyle = strStyle + _T("05");
		break;	
	}

	CString strTextTans = _T("");
	switch(emTransparency)
	{
	case emTransparent:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpLT") );
		strTextTans = _T(" ȫ͸��");
		break;
	case emTranslucent:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpLB") );
		strTextTans = _T(" ��͸��");
		break;	
	case Opaque:
		ICncCommonOp::OptionSelect( true, m_pm, _T("OpMT") );
		strTextTans = _T(" ��͸��");
		break;	
	}

	ICncCommonOp::SetControlText( strStyle, m_pm, _T("lbBannerStyle") ); 
	ICncCommonOp::SetControlText( strTextTans, m_pm, _T("lbBannerTrans") );
	ICncCommonOp::SetControlText( strContent, m_pm, _T("edtBanner") );
	//ICncCommonOp::SetControlText( strTextSet, m_pm, _T("lbBannerText") );
	return true;
}

bool CLocalRoomCfgLogic::UpdateLogoScreen( TTPLogoInfo tLogoInfo )
{
	CTouchListUI *pLogoListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenLogoList") );
	if ( pLogoListLayoutUI == NULL )
	{
		return false;
	}
	if (pLogoListLayoutUI->GetCount() > 0)
	{
		pLogoListLayoutUI->RemoveAll();
	}

	for ( int dwIndex = 0; dwIndex < 3; dwIndex++ )
	{
		CListContainerElementUI *pLogoListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfScreenListItem") );

		CString strText = _T("");
		strText.Format(_T("��ʾ��0%d"),dwIndex+1);

		ICncCommonOp::SetControlText( (LPCTSTR)strText,m_pm,_T("lbScreenLogo"),pLogoListContainer);
		CCheckBoxUI* pCheckBoxLogo = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pLogoListContainer);

		bool bIsLogoCheck = false;
		switch(dwIndex)
		{
		case 0:
			m_mapIsLogo[0] = tLogoInfo.tFirsLogoInfo.bIsShowLogo;
			break;
		case 1:
			m_mapIsLogo[1] = tLogoInfo.tSecondLogoInfo.bIsShowLogo;
			break;	
		case 2:
			m_mapIsLogo[2] = tLogoInfo.tThirdLogoInfo.bIsShowLogo;
			break;	
		}

		pLogoListLayoutUI->Add(pLogoListContainer);
	}

	return true;
}

bool CLocalRoomCfgLogic::UpdateLogoScreen( TTPShowLogo tShowLogoInfo, u8 wId)
{
	CTouchListUI *pLogoListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenLogoList") );
	if ( pLogoListLayoutUI == NULL )
	{
		return false;
	}

	CListContainerElementUI *pLogoListContainer = (CListContainerElementUI *)pLogoListLayoutUI->GetItemAt(wId);
	if (pLogoListLayoutUI == NULL)
	{
		return false;
	}

	CCheckBoxUI* pCheckBoxLogo = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pLogoListContainer);
	if (!pCheckBoxLogo)
	{
		return false;	
	}
	
	m_mapIsLogo[wId] = tShowLogoInfo.bIsShowLogo;
	pCheckBoxLogo->SetCheckNoMsg(tShowLogoInfo.bIsShowLogo);
	if (m_dwLogoScreenSelId == wId)
	{
		if (tShowLogoInfo.bIsShowLogo )
		{
			m_pm->DoCase(_T("caseLogoSetSel"));
		}
		else
		{
			m_pm->DoCase(_T("caseLogoSetUnSel"));
		}
	}

	return true;
}

//���¿���״̬ ����һ���½�һ�߸�״̬
bool CLocalRoomCfgLogic::UpdateLogoCheck()
{
	CTouchListUI *pLogoListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenLogoList") );
	if (!pLogoListLayoutUI)
	{
		return false;
	}

	for (int i = 0; i<3; i++)
	{
		bool bIsCheck = false;
		CListContainerElementUI *pLogoListContainer = (CListContainerElementUI*)pLogoListLayoutUI->GetItemAt(i);
		if (pLogoListLayoutUI)
		{
			CCheckBoxUI* pCheckBoxLogo = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pLogoListContainer);
			if (pCheckBoxLogo)
			{
				pCheckBoxLogo->SetCheck(m_mapIsLogo[i]);
			}
		}
	}

	return true;
}

bool CLocalRoomCfgLogic::UpdateBannerCheck()
{
	CTouchListUI *pbannerListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenBannerList") );
	if (!pbannerListLayoutUI)
	{
		return false;
	}

	for (int i = 0; i<3; i++)
	{
		bool bIsCheck = false;
		CListContainerElementUI *pbannerListContainer = (CListContainerElementUI*)pbannerListLayoutUI->GetItemAt(i);
		if (pbannerListLayoutUI)
		{
			CCheckBoxUI* pCheckBoxbanner = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pbannerListContainer);
			if (pCheckBoxbanner)
			{
				pCheckBoxbanner->SetCheck(m_mapIsBanner[i]);
			}
		}
	}

	return true;
}

bool CLocalRoomCfgLogic::UpdateBannerScreen( TTPBannerInfo tBannerInfo )
{
	CTouchListUI *pBannerListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenBannerList") );
	if ( pBannerListLayoutUI == NULL )
	{
		return false;
	}
	if (pBannerListLayoutUI->GetCount() > 0)
	{
		pBannerListLayoutUI->RemoveAll();
	}

	for ( int dwIndex = 0; dwIndex < 3; dwIndex++ )
	{
		CListContainerElementUI *pBannerListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfScreenListItem") );

		CString strText = _T("");
		strText.Format(_T("��ʾ��0%d"),dwIndex+1);

		ICncCommonOp::SetControlText( (LPCTSTR)strText,m_pm,_T("lbScreenLogo"),pBannerListContainer);
		CCheckBoxUI* pCheckBoxBanner = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pBannerListContainer);

		bool bIsBannerCheck = false;
		switch(dwIndex)
		{
		case 0:
			m_mapIsBanner[0] = tBannerInfo.tFirstBannerInfo.bIsShowBanner;
			break;
		case 1:
			m_mapIsBanner[1] = tBannerInfo.tSeconfBannerInfo.bIsShowBanner;
			break;	
		case 2:
			m_mapIsBanner[2] = tBannerInfo.tThirdBannerInfo.bIsShowBanner;
			break;	
		}

		pBannerListLayoutUI->Add(pBannerListContainer);
	}

	return true;
}

bool CLocalRoomCfgLogic::UpdateBannerScreen( TTPShowBanner tShowBannerInfo, u8 wId)
{
	CTouchListUI *pBannerListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfScreenBannerList") );
	if ( pBannerListLayoutUI == NULL )
	{
		return false;
	}

	CListContainerElementUI *pLogoListContainer = (CListContainerElementUI *)pBannerListLayoutUI->GetItemAt(wId);
	if (pBannerListLayoutUI == NULL)
	{
		return false;
	}

	CCheckBoxUI* pCheckBoxBanner = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pLogoListContainer);
	if (!pCheckBoxBanner)
	{
		return false;	
	}

	m_mapIsBanner[wId] = tShowBannerInfo.bIsShowBanner;
	pCheckBoxBanner->SetCheckNoMsg(tShowBannerInfo.bIsShowBanner);

	if (m_dwBannerScreenSelId == wId)
	{
		if (tShowBannerInfo.bIsShowBanner)
		{
			m_pm->DoCase(_T("caseBannerSetSel"));
		}
		else
		{
			m_pm->DoCase(_T("caseBannerSetUnSel"));
		}
	}

	return true;
}

void CLocalRoomCfgLogic::GetLogoStyle( TTPShowLogo tTPShowLogo, FontStyle &fontStyle, Color &clr, Color &clBorder, u32 &w1080Size, u32 &w720Size , u32 &w4CIF)
{
	switch(tTPShowLogo.emColor)
	{
	case emRed:
		clr = Color(0,255,255);
		clBorder = Color(0,0,0);
		break;
	case emBlue:
		clr = Color(0,0,255);
		clBorder = Color(255,255,255);
		break;
	case emYellow:
		clr = Color(255,235,0);
		clBorder = Color(0,0,0);
		break;
	case emBlack:
		clr = Color(0,0,0);
		clBorder = Color(255,255,255);
		break;
	case emGreen:
		clr = Color(0,255,0);
		clBorder = Color(0,0,0);
		break;
	}

	switch(tTPShowLogo.emSize)
	{
    default:
	case emBig:
		w1080Size = 50;
		w720Size = 42;
		w4CIF = 34;
		break;
// 	case emMid:
// 		w1080Size = 60;
// 		w720Size = 40;
// 		w4CIF = 32;
// 		break;
	case emlittle:
		w1080Size = 42;
		w720Size = 34;
		w4CIF = 26;
		break;
	}
}

void CLocalRoomCfgLogic::GetBannerStyle( TTPShowBanner tTPShowBanner, FontStyle &fontStyle, Color &clr, Color &clBorder, u32 &w1080Size, u32 &w720Size , u32 &w4CIF)
{
	switch(tTPShowBanner.emStyle)
	{
	case emStyleOne:
		clr = Color(255,235,0);
		clBorder = Color(255,0,0);
		break;
	case emStyleTwo:
		clr = Color(255,255,255);
		clBorder = Color(29,32,136);
		break;
	case emStyleThree:
		clr = Color(255,255,255);
		clBorder = Color(255,0,0);
		break;
	case emStyleFour:
		clr = Color(255,255,255);
		clBorder = Color(0,0,0);
		break;
	case emStyleFive:
		clr = Color(255,0,0);
		clBorder = Color(255,255,0);
		break;
	}

	int dwNameLength = strlen(tTPShowBanner.achBannerName);
	if (dwNameLength < 32)
	{
		tTPShowBanner.emSize = emBig;
	}
	else if (dwNameLength >= 32 && dwNameLength < 44)
	{
		tTPShowBanner.emSize = emMid;
	}
	else
	{
		tTPShowBanner.emSize = emlittle;
	}

	switch(tTPShowBanner.emSize)
	{
	case emBig:
		w1080Size = 78;
		w720Size = 48;
		w4CIF = 38;
		break;
	case emMid:
		w1080Size = 60;
		w720Size = 40;
		w4CIF = 32;
		break;
	case emlittle:
		w1080Size = 44;
		w720Size = 32;
		w4CIF = 26;
		break;
	}
}

bool CLocalRoomCfgLogic::OnVidCutLineInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	BOOL bIsVidCutLine = wParam;
	BOOL bIsSuccess = lParam;
	if (!bIsSuccess)
	{
		if (bIsVidCutLine)
		{
			ShowPopMsg(_T("����������ʾʧ��"));
		}
		else
		{
			ShowPopMsg(_T("�رռ�����ʾʧ��"));
		}
	}

	BOOL bIsNewVidCutLine = ComInterface->IsVidCutLine();
	if (bIsNewVidCutLine)
	{
		ICncCommonOp::SetControlText(_T("����"),m_pm,_T("lbIsVidCurLine"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("�ر�"),m_pm,_T("lbIsVidCurLine"));
	}

	CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckIsVidCurLine"));
	if (pCheck)
	{
		pCheck->Selected(bIsNewVidCutLine);
	}

	return true;
}

void CLocalRoomCfgLogic::InitVidCutLine()
{
	BOOL bIsVidCutLine = ComInterface->IsVidCutLine();
	if (bIsVidCutLine)
	{
		ICncCommonOp::SetControlText(_T("����"),m_pm,_T("lbIsVidCurLine"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("�ر�"),m_pm,_T("lbIsVidCurLine"));
	}

	CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckIsVidCurLine"));
	if (pCheck)
	{
		pCheck->Selected(bIsVidCutLine);
	}
}

bool CLocalRoomCfgLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}

bool CLocalRoomCfgLogic::OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        if (m_bWaitFtpUpLogo || m_bWaitFtpUpbanner || m_bWaitFtpUploadLogoImgForLogin)
        {
            m_bWaitFtpUpLogo = false;
            m_bWaitFtpUpbanner = false;
            m_bWaitFtpUploadLogoImgForLogin = false;
            ShowPopMsg(_T("FTP�ϴ�����������ʧ��!"));
        }
        return false;
    }
    
    if (m_bWaitFtpUpLogo)
    {
        m_bWaitFtpUpLogo = false;
        TNotifyUI msg;
        OnBtnSaveLogo(msg);
    }

    if (m_bWaitFtpUpbanner)
    {
        m_bWaitFtpUpbanner = false;
        TNotifyUI msg;
        OnBtnSaveBanner(msg);
    }

    if (m_bWaitFtpUploadLogoImgForLogin)
    {
        m_bWaitFtpUploadLogoImgForLogin = false;
        UploadLogoImg();
    }

    return true;
}

bool CLocalRoomCfgLogic::UploadLogoImg()
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        //δ������ȴ����������ϴ�
        m_bWaitFtpUploadLogoImgForLogin = true;
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
        return false;
    }

    if (m_vecLogoFile.size()>0)//���ϴ�ĳһ����ʱ�� ��ֹ�ϴ�
    {
        return false;
    }

    TTPLogoInfo tTPLogoInfo;
    ComInterface->GetLogoInfo( tTPLogoInfo );
    CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
    if(!PathFileExists(strFullPath))
    {
        CreateDirectory(strFullPath, NULL);
    }
    //�ϴ�ǰ���
    m_vecLogoFile.clear();
    for (int i = 0 ; i < 3 ; i++)
    {
        TTPShowLogo tLogoInfo;
        switch(i)
        {
        case 0:
            tLogoInfo = tTPLogoInfo.tFirsLogoInfo;
            break;
        case 1:
            tLogoInfo = tTPLogoInfo.tSecondLogoInfo;
            break;	
        case 2:
            tLogoInfo = tTPLogoInfo.tThirdLogoInfo;
        }

        if (tLogoInfo.bIsShowLogo == FALSE)
        {
            continue;
        }

        m_dwLogoScreenSeUploadlId = i;

        //���浱ǰ���� 
        if (tLogoInfo.achLogoName == "")
        {
            continue;
        }

        BOOL bSuccess;
        switch(i)
        {
        case 0:
            {
                int nImgType = 0;
                switch(m_mapLogoInfo[0].emStyle)
                {
                case emLeftDown:
                case emLeftUp:
                    nImgType = 1;
                    break;
                case emRightDown:
                case emRightUp:
                    nImgType = 2;
                    break;
                default:
                    break;
                }

                FontStyle font = FontStyleBold;
                Color clr;
                Color clBorder;
                u32 w1080Size;
                u32 w720Size;
                u32 w4CIFSize;

                GetLogoStyle(tLogoInfo, font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
                CString strLogoName(tLogoInfo.achLogoName);
                if (strLogoName.IsEmpty())
                {
                    strLogoName.Format(_T("��ʾ��01"));
                }

                CString strPath = strFullPath + LOGO1080P_POS0_PATH ;
                bSuccess = MakeImgByChar( strLogoName, _T("����"), font, clr, clBorder, Color(255,255,255), w1080Size, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }

                strPath = strFullPath + LOGO720P_POS0_PATH;
                bSuccess = MakeImgByChar( strLogoName, _T("����"), font, clr,  clBorder, Color(255,255,255),  w720Size, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }

                strPath = strFullPath + LOGO4CIF_POS0_PATH;
                bSuccess = MakeImgByChar( strLogoName, _T("����"), font, clr,  clBorder, Color(255,255,255), w4CIFSize, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }
                m_vecLogoFile.push_back(LOGO720P_POS0_PATH);
                m_vecLogoFile.push_back(LOGO1080P_POS0_PATH);
                m_vecLogoFile.push_back(LOGO4CIF_POS0_PATH);
            }
            break;
        case 1:
            {
                int nImgType = 0;
                switch(m_mapLogoInfo[1].emStyle)
                {
                case emLeftDown:
                case emLeftUp:
                    nImgType = 1;
                    break;
                case emRightDown:
                case emRightUp:
                    nImgType = 2;
                    break;
                default:
                    break;
                }

                FontStyle font = FontStyleBold;
                Color clr;
                Color clBorder;
                u32 w1080Size;
                u32 w720Size;
                u32 w4CIFSize;

                GetLogoStyle(m_mapLogoInfo[1], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
                CString strLogoName2(m_mapLogoInfo[1].achLogoName);
                if ( strLogoName2.IsEmpty())
                {
                    strLogoName2.Format(_T("��ʾ��02"));
                }

                CString strPath = strFullPath +  LOGO1080P_POS1_PATH;
                bSuccess = MakeImgByChar( strLogoName2, _T("����"), font, clr, clBorder, Color(255,255,255), w1080Size , 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }

                strPath = strFullPath + LOGO720P_POS1_PATH;
                bSuccess = MakeImgByChar( strLogoName2, _T("����"), font, clr,  clBorder, Color(255,255,255), w720Size, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }

                strPath = strFullPath + LOGO4CIF_POS1_PATH;
                bSuccess = MakeImgByChar( strLogoName2, _T("����"), font, clr,  clBorder, Color(255,255,255), w4CIFSize, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }
                m_vecLogoFile.push_back(LOGO720P_POS1_PATH);
                m_vecLogoFile.push_back(LOGO1080P_POS1_PATH);
                m_vecLogoFile.push_back(LOGO4CIF_POS1_PATH);

            }
            break;
        case 2:
            {
                int nImgType = 0;
                switch(m_mapLogoInfo[2].emStyle)
                {
                case emLeftDown:
                case emLeftUp:
                    nImgType = 1;
                    break;
                case emRightDown:
                case emRightUp:
                    nImgType = 2;
                    break;
                default:
                    break;
                }

                FontStyle font = FontStyleBold;
                Color clr;
                Color clBorder;
                u32 w1080Size;
                u32 w720Size;
                u32 w4CIFSize;

                GetLogoStyle(m_mapLogoInfo[2], font, clr, clBorder, w1080Size, w720Size, w4CIFSize);
                CString strLogoName3(m_mapLogoInfo[2].achLogoName);
                if ( strLogoName3.IsEmpty())
                {
                    strLogoName3.Format(_T("��ʾ��03"));
                }

                CString strPath = strFullPath + LOGO1080P_POS2_PATH;
                bSuccess = MakeImgByChar( strLogoName3, _T("����"), font, clr,  clBorder, Color(255,255,255), w1080Size, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }

                strPath = strFullPath + LOGO720P_POS2_PATH;
                bSuccess = MakeImgByChar( strLogoName3, _T("����"), font, clr, clBorder, Color(255,255,255), w720Size, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }

                strPath = strFullPath + LOGO4CIF_POS2_PATH;
                bSuccess = MakeImgByChar( strLogoName3, _T("����"), font, clr,  clBorder, Color(255,255,255), w4CIFSize, 2, strPath, true, nImgType );
                if( !bSuccess )
                {
                    continue;
                }
                m_vecLogoFile.push_back(LOGO720P_POS2_PATH);
                m_vecLogoFile.push_back(LOGO1080P_POS2_PATH);
                m_vecLogoFile.push_back(LOGO4CIF_POS2_PATH);
            }
            break;
        }
    }

    if( m_vecLogoFile.size() > 0 && !UploadLogoCoreFirstLogin( CNSCONF_FILE_PATH, (String)strFullPath+m_vecLogoFile.at(0), m_vecLogoFile.at(0), FALSE) )
    {
        char ach[MAX_PATH];
        strcpy(ach,(CT2A)m_vecLogoFile.at(0).c_str());
        PrtMsg( 0, emEventTypeCmsWindow, "%s��û��ʼ����ftp�����ʧ�ܣ�", ach );
    }
}