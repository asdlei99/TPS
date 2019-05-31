#include "StdAfx.h"
#include "PanCamlogic.h"
#include "roomctrllogic.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"

template<> CPanCamLogic* Singleton<CPanCamLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CPanCamLogic, CNotifyUIImpl)

	MSG_CLICK(_T("btnPosSet"), OnBtnImplePosSet)
	MSG_CLICK(_T("btnSaveSet"), OnBtnSavePosSet)
	MSG_CLICK(_T("btnCamUp"), OnBtnCamUp)
	MSG_CLICK(_T("btnCamRight"), OnCamRight)
	MSG_CLICK(_T("btnCamLeft"), OnBtnCamLeft)
	MSG_CLICK(_T("btnCamDown"), OnBtnCamDown)
	MSG_CLICK(_T("btnViewPlus"), OnBtnViewPlus)
	MSG_CLICK(_T("btnViewMinus"), OnBtnViewMinus)
	MSG_CLICK(_T("btnFocusPlus"), OnBtnFocusPlus)
	MSG_CLICK(_T("btnFocusAuto"), OnBtnFocusAuto)
	MSG_CLICK(_T("btnFocusMinus"), OnBtnFocusMinus)
	MSG_CLICK(_T("btnBrightPlus"), OnBtnBrightPlus)
	MSG_CLICK(_T("btnBrightMinus"), OnBtnBrightMinus)

//     MSG_MOUSELEAVE(_T("btnPosSet"), OnBtnImplePosSet)
//     MSG_MOUSELEAVE(_T("btnSaveSet"), OnBtnSavePosSet)
    MSG_MOUSELEAVE(_T("btnCamUp"), OnBtnCamUp)
    MSG_MOUSELEAVE(_T("btnCamRight"), OnCamRight)
    MSG_MOUSELEAVE(_T("btnCamLeft"), OnBtnCamLeft)
    MSG_MOUSELEAVE(_T("btnCamDown"), OnBtnCamDown)
    MSG_MOUSELEAVE(_T("btnViewPlus"), OnBtnViewPlus)
    MSG_MOUSELEAVE(_T("btnViewMinus"), OnBtnViewMinus)
    MSG_MOUSELEAVE(_T("btnFocusPlus"), OnBtnFocusPlus)
    MSG_MOUSELEAVE(_T("btnFocusAuto"), OnBtnFocusAuto)
    MSG_MOUSELEAVE(_T("btnFocusMinus"), OnBtnFocusMinus)
    MSG_MOUSELEAVE(_T("btnBrightPlus"), OnBtnBrightPlus)
    MSG_MOUSELEAVE(_T("btnBrightMinus"), OnBtnBrightMinus)

	MSG_BUTTONDOWN(_T("btnCamUp"), OnBtnCamUpDown)
	MSG_BUTTONDOWN(_T("btnCamRight"), OnCamRightDown)
	MSG_BUTTONDOWN(_T("btnCamLeft"), OnBtnCamLeftDown)
	MSG_BUTTONDOWN(_T("btnCamDown"), OnBtnCamDownDown)
	MSG_BUTTONDOWN(_T("btnFocusPlus"), OnBtnFocusPlusDown)
	MSG_BUTTONDOWN(_T("btnFocusMinus"), OnBtnFocusMinusDown)
	MSG_BUTTONDOWN(_T("btnBrightPlus"), OnBtnBrightPlusDown)
	MSG_BUTTONDOWN(_T("btnBrightMinus"), OnBtnBrightMinusDown)
	MSG_BUTTONDOWN(_T("btnViewPlus"), OnBtnViewPlusDown)
	MSG_BUTTONDOWN(_T("btnViewMinus"), OnBtnViewMinusDown)

	MSG_CLICK(_T("btnCamListLeft"), OnBtnCamListLeft)
	MSG_CLICK(_T("btnCamListRight"), OnBtnCamListRight)	

	MSG_SELECTCHANGE(_T("CheckCamShortCut"), OnCheckCamShortCut)
	MSG_SELECTCHANGE(_T("CheckStartCam"), OnCheckStartCam)

	MSG_CLICK(_T("BtnCancle"), OnBtnCancelPanSet)
	MSG_CLICK(_T("BtnSet"), OnBtnSavePanPresetNameSet)
	MSG_CLICK(_T("BtnSetPresetName"), OnBtnSetPresetName)
	MSG_CLICK(_T("BtnPresetDel"), OnBtnPresetDel)
	MSG_CLICK(_T("BtnPresetAdd"), OnBtnPresetAdd)
	MSG_CLICK(_T("BtnPresetCancel"), BtnPresetCancel)
	MSG_CLICK(_T("BtnPresetOk"), OnBtnPresetOk)

	MSG_ITEMSELECTD(_T("ComboCamSel"), OnComboCamSel)
	MSG_ITEMSELECTD(_T("TouchListItem"), OnPresetListItemSelected)

	USER_MSG(UI_CNS_PANCAMSEL_IND,OnSelSelCamInd)  

	USER_MSG(UI_CNS_PANCAMINFO_NTY,OnPanCamLstNotify)
	USER_MSG(UI_CNS_PANCAMPRESETIMPLE_IND,OnPanCamPresetImpleNotify)
	USER_MSG(UI_CNS_PANCAMPRESETSAVE_IND,OnPanCamPresetSaveNotify)
	USER_MSG(UI_CNS_PANCAMPRESETDEL_IND,OnPanCamPresetDeleteNotify)
	USER_MSG(UI_CNS_PANCAMPRESETNAMESAVE_IND,OnPanCamSavePresetNameInd)

	USER_MSG(UI_CNS_PANCAMSTART_RSP,OnPanCamStartInd)
	USER_MSG(WM_CNC_PAMCAMRPRESETPROGRESS,OnDownloadProgress)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
		
	USER_MSG(UI_CNC_SHORTCUTCHECK_NTY,OnSetShortCheck)

    USER_MSG(UI_CNSETFTPRSP, OnSetCnFtpRsp)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)

	APP_END_MSG_MAP()

	const String CPanCamLogic::m_strEdtPresetName = _T("EditName");

CPanCamLogic::CPanCamLogic(void)
{
	m_dwCurrentCamID = -1;
	m_dwSelItemId = -1;
	m_wCurPageIndex = 0;
	m_emListState = EMSTATE_NO;
	m_bIsShortCutClosed = false;
//    m_bIsPanCamLisOpenFtp = false;

    m_wPresetID = -1;
}


CPanCamLogic::~CPanCamLogic(void)
{
}

bool CPanCamLogic::OnComboCamSel( TNotifyUI& msg )
{
	if (m_dwCurrentCamID != msg.wParam )
	{
		m_dwCurrentCamID = msg.wParam;
		ComInterface->SetPanCamSelectIndex( m_dwCurrentCamID );
	}

	m_tCurrentPreset.wCamID = m_dwCurrentCamID;

	return true;
}

bool CPanCamLogic::UpdateList()
{
	CSlideTabLayoutUI *pSlideTabLayout = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("preListSlidetab") );
	if (!pSlideTabLayout)
	{
		return false;
	}

	if (pSlideTabLayout->GetCount() > 0)
	{
		for (int i=0; i<pSlideTabLayout->GetCount(); i++)
		{
			CTouchListUI *pTouchListLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(i);
			if (pTouchListLayoutUI)
			{
				pTouchListLayoutUI->RemoveAll();
			}
		}

		pSlideTabLayout->RemoveAll();
	}

	u16 wMaxPage = 0;
	if (m_vctPresetList.size()%6 == 0)
	{
		wMaxPage = m_vctPresetList.size()/6;
	}
	else
	{
		wMaxPage = (m_vctPresetList.size()/6)+1;
	}

	for ( u16 wPage = 0; wPage < wMaxPage ; wPage++ )
	{
		CTouchListUI *pTouchListLayoutUI = NULL;		
		pTouchListLayoutUI = (CTouchListUI*)CONTROLFACTORY()->GetControl( _T("TouchListItem") );
		if ( pTouchListLayoutUI == NULL )
		{
			return false;
		}

		CString strPresetPic = _T("");
		CString strPath = _T("");
		for ( u16 wId = 0; wId < 6 ; wId++ )
		{
			u16 index = wPage * 6 + wId;
			if (index >= m_vctPresetList.size())
			{
				break; 
			}
			CListContainerElementUI *pListContainer = 
				(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PresetListItem") );

			ICncCommonOp::SetControlText( m_vctPresetList.at(index).strPanCamName, m_pm, _T("PresetName"), pListContainer );
			//设置背景图
			if (!m_vctPresetList.at(index).strPanCamName.IsEmpty())
			{
				strPresetPic.Format(_T("pancam%d_%d.jpg"), m_dwCurrentCamID, wPage*6+wId);
				strPath = GetModuleFullPath() + TP_TEMPFILE_PATH + strPresetPic;
				ICncCommonOp::SetControlBkImg(strPath, m_pm, _T("PresetListShotPic"), pListContainer );
			}

			CButtonUI* pBtnPresetName = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnSetPresetName"), pListContainer);
			if ( pBtnPresetName )
			{
				pBtnPresetName->SetTag( (UINT_PTR)&m_vctPresetList.at(index));
			}

			pTouchListLayoutUI->Add(pListContainer);
		}

		pSlideTabLayout->Add((pTouchListLayoutUI));

	}

	CString strPageIndex = _T("");
	strPageIndex.Format(_T("%d"),m_wCurPageIndex);

	pSlideTabLayout->SetAttribute(_T("selectedid"), strPageIndex);
	pSlideTabLayout->SetAttribute(_T("pos"), _T("140,162,1780,852"));
	return true;
}

bool CPanCamLogic::UpdateList( CString strPresetName, u8 wPageID, u8 wItemID)
{
	CSlideTabLayoutUI *pSlideTabLayout = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("preListSlidetab") );
	if (!pSlideTabLayout)
	{
		return false;
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(wPageID);
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CListContainerElementUI *pListContainer = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(wItemID);

	if (pListContainer)
	{
		ICncCommonOp::SetControlText( strPresetName, m_pm, _T("PresetName"), pListContainer );
	}	

	CString strPresetPic = _T("");
	CString strPath = _T("");
	if ( !strPresetName.IsEmpty() && !m_vctPresetList.at(wPageID*6+wItemID).strPanCamName.IsEmpty() )
	{
		strPresetPic.Format(_T("pancam%d_%d.jpg"), m_dwCurrentCamID, wPageID*6+wItemID);
		strPath = GetModuleFullPath() + TP_TEMPFILE_PATH + strPresetPic;
	}

	ICncCommonOp::SetControlBkImg(strPath, m_pm, _T("PresetListShotPic"), pListContainer );

	return true;
}

bool CPanCamLogic::OnBtnImplePosSet( TNotifyUI& msg )
{
	if (m_dwCurrentCamID == -1)
	{
		ShowMessageBox((_T("请先选择配置的摄像机")),false);
		return true;
	}

	m_emListState = EMSTATE_IMPLEMENT;

	m_vctPresetList.clear();
	for ( int wId = 0; wId < MAX_PRESET_NUM; wId++ )
	{
		CString str;
		str.Format(_T("a%d"),wId);
		TPanCam tPanCam;
		tPanCam.wCamID = m_dwCurrentCamID;
		tPanCam.wPresetID = wId;
		tPanCam.strPanCamName = m_tPanCamInfo.tPCamGroupName[m_dwCurrentCamID].tPanCamName[wId].achPanCamName;
		m_vctPresetList.push_back(tPanCam);
	}

	m_wCurPageIndex = 0;
	m_dwSelItemId = -1;
	ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnPresetAdd"));//调用预置位时不可新建 不显示此按钮
	UpdateList();

	ICncCommonOp::ShowControl( true, m_pm, _T("PagePresetList") );
	return true;
}

bool CPanCamLogic::OnBtnSavePosSet( TNotifyUI& msg )
{
	if (!IsCanSavePamPos())
	{
		return false;
	}

	if (m_dwCurrentCamID == -1)
	{
		ShowMessageBox((_T("请先选择配置的摄像机")),false);
		return true;
	}
	m_emListState = EMSTATE_SET;

	m_vctPresetList.clear();
	for ( int wId = 0; wId < MAX_PRESET_NUM; wId++ )
	{
		CString str;
		str.Format(_T("a%d"),wId);
		TPanCam tPanCam;
		tPanCam.wCamID = m_dwCurrentCamID;
		tPanCam.wPresetID = wId;
		tPanCam.strPanCamName = m_tPanCamInfo.tPCamGroupName[m_dwCurrentCamID].tPanCamName[wId].achPanCamName;

		m_vctPresetList.push_back(tPanCam);
	}

	m_wCurPageIndex = 0;
	m_dwSelItemId = -1;
	ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
	ICncCommonOp::ShowControl(true,m_pm,_T("BtnPresetAdd"));//保存预置位时不可新建 不显示此按钮
	UpdateList();

	ICncCommonOp::ShowControl( true, m_pm, _T("PagePresetList") );
	return true;
}

bool CPanCamLogic::OnBtnCamUp( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emUP, emCnStop );
	return true;
}
bool CPanCamLogic::OnBtnCamUpDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emUP, emCnStart );
	return true;
}

bool CPanCamLogic::OnCamRight( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emRight, emCnStop );
	return true;
}
bool CPanCamLogic::OnCamRightDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emRight, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnCamLeft( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emLeft, emCnStop );
	return true;
}
bool CPanCamLogic::OnBtnCamLeftDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emLeft, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnCamDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emDown, emCnStop );
	return true;
}
bool CPanCamLogic::OnBtnCamDownDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamPT( emDown, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnViewPlus( TNotifyUI& msg )
{
	ComInterface->SetPanCamView( emWide, emCnStop );
	return true;
}
bool CPanCamLogic::OnBtnViewPlusDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamView( emWide, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnViewMinus( TNotifyUI& msg )
{
	ComInterface->SetPanCamView( emTele, emCnStop );
	return true;
}
bool CPanCamLogic::OnBtnViewMinusDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamView( emTele, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnFocusPlus( TNotifyUI& msg )
{
	ComInterface->SetPanCamFocus( emNear, emCnStop );
	return true;
}

bool CPanCamLogic::OnBtnFocusPlusDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamFocus( emNear, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnFocusAuto( TNotifyUI& msg )
{
	ComInterface->SetPanCamAotoFocus();
	return true;
}

bool CPanCamLogic::OnBtnFocusMinus( TNotifyUI& msg )
{
	ComInterface->SetPanCamFocus( emFar, emCnStop );
	return true;
}

bool CPanCamLogic::OnBtnFocusMinusDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamFocus( emFar, emCnStart );
	return true;
}

bool CPanCamLogic::OnBtnBrightPlus( TNotifyUI& msg )
{
	ComInterface->SetPanCamBright( emBrightUp, emCnStop );
	return true;
}

bool CPanCamLogic::OnBtnBrightPlusDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamBright( emBrightUp, emCnStart );
	return true;
}
bool CPanCamLogic::OnBtnBrightMinus( TNotifyUI& msg )
{
	ComInterface->SetPanCamBright( emBrightDown, emCnStop );
	return true;
}

bool CPanCamLogic::OnBtnBrightMinusDown( TNotifyUI& msg )
{
	ComInterface->SetPanCamBright( emBrightDown, emCnStart );
	return true;
}

bool CPanCamLogic::OnCheckStartCam( TNotifyUI& msg )
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

	if (m_tPanCamInfo.bPanCamOpen != bIsSet)
	{
		ComInterface->SetLocalCnsPanCam(m_dwCurrentCamID,bIsSet);
	}

	return true;
}

bool CPanCamLogic::OnCheckCamShortCut( TNotifyUI& msg )
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

	if (!bIsSet)
	{
		ComInterface->GetPanCamList( m_tPanCamInfo );
		if (m_tPanCamInfo.byPanCamNum != 0)
		{
			m_bIsShortCutClosed = true;
		}
	}
	else
	{
		m_bIsShortCutClosed = false;
	}

	EM_ShortcutType em = emShortcutPanCam;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CPanCamLogic::OnBtnCancelPanSet( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNameSet") );

	return true;
}

bool CPanCamLogic::OnBtnSavePanPresetNameSet( TNotifyUI& msg )
{
	CEditUI *pEdt = (CEditUI*)ICncCommonOp::FindControl( m_pm,m_strEdtPresetName.c_str() );   
	CString strPresetName=_T("");
	if ( pEdt )
	{
		strPresetName = pEdt->GetText();
	}
	if (strPresetName.IsEmpty())
	{
		ShowMessageBox( _T("请填写预置位名"), false);
		return false;
	}
	UpdateList(strPresetName,m_wCurPageIndex,m_dwSelItemId);
	//list中保存名字 成功了不更新 失败了更新成之前的名字
	u16 wIndex = m_dwSelItemId + m_wCurPageIndex*6;
	m_vctPresetList.at(wIndex).strPanCamName = strPresetName;
	m_tCurrentPreset.strPanCamName = strPresetName;

	TPanCamName tPanCamName; 
	WCharToMByte( strPresetName,tPanCamName.achPanCamName);

	ComInterface->SavePanCamPresetName(wIndex, tPanCamName);
// 		u16 wMaxPage = 0;
// 		if (m_vctPresetList.size()%6 == 0)
// 		{
// 			wMaxPage = m_vctPresetList.size()/6;
// 		}
// 		else
// 		{
// 			wMaxPage = (m_vctPresetList.size()/6)+1;
// 		}
// 		
// 
// 		TPanCam tPanCam;
// 		tPanCam.strPanCamName = strPresetName;
// 
// 		m_vctPresetList.push_back(tPanCam);
// 
// 		u16 wNewMaxPage = 0;
// 		if (m_vctPresetList.size()%6 == 0)
// 		{
// 			wNewMaxPage = m_vctPresetList.size()/6;
// 		}
// 		else
// 		{
// 			wNewMaxPage = (m_vctPresetList.size()/6)+1;
// 		}
// 		CTouchListUI *pTouchListLayoutUI = NULL;
// 		bool bNewPage = false;
// 		if (wNewMaxPage == wMaxPage)
// 		{
// 			pTouchListLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(wMaxPage-1);
// 		}
// 		else
// 		{
// 			bNewPage = true;
// 			pTouchListLayoutUI = (CTouchListUI*)CONTROLFACTORY()->GetControl( _T("TouchListItem") );
// 		}
// 		
// 		if ( pTouchListLayoutUI == NULL )
// 		{
// 			return false;
// 		}
// 
// 		u16 index = m_vctPresetList.size() -1;
// 
// 		CListContainerElementUI *pListContainer = 
// 			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PresetListItem") );
// 
// 		ICncCommonOp::SetControlText( m_vctPresetList.at(index).strPanCamName, m_pm, _T("PresetName"), pListContainer );
// 
// 	// 	CString strFullPath = GetModuleFullPath();
// 	// 	CString strPath = strFullPath + LOGO720P_POS0_PATH;
// 		//设置背景图片
// 	// 	CString strBkImage = _T("");
// 	// 	strBkImage.Format(_T("%s%d"), strFullPath, index);
// 	// 	ICncCommonOp::SetControlBkImg(strBkImage, m_pm, _T("PresetListItem"), pListContainer );
// 
// 		CButtonUI* pBtnPresetName = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnSetPresetName"), pListContainer);
// 		if ( pBtnPresetName )
// 		{
// 			pBtnPresetName->SetTag( (UINT_PTR)&m_vctPresetList.at(index));
// 		}
// 
// 		pTouchListLayoutUI->Add(pListContainer);
// 		
// 		if(bNewPage)
// 		{
// 			pSlideTabLayout->Add((pTouchListLayoutUI));
// 		}
// 		
// 		CString strPageIndex = _T("");
// 		m_wCurPageIndex = wNewMaxPage-1;
// 		strPageIndex.Format(_T("%d"),wNewMaxPage-1);
// 
// 		pSlideTabLayout->SetAttribute(_T("selectedid"), strPageIndex);
// 		if (m_wCurPageIndex == 0)
// 		{
// 			ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
// 		}
// 		else
// 		{
// 			ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListLeft"));
// 		}
// 		if ( (m_wCurPageIndex+1)*6 >= m_vctPresetList.size())
// 		{
// 			ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListRight"));
// 		}
// 		else
// 		{
// 			ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
// 		}
//	}

	ICncCommonOp::ShowControl( false, m_pm, _T("PageNameSet") );
	return true;
}

bool CPanCamLogic::OnBtnPresetDel( TNotifyUI& msg )
{
	if (m_dwSelItemId == -1)
	{
		ShowMessageBox((_T("请先选择删除项")),false);
		return true;
	}

	CString str(m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName);
	if (str.IsEmpty())
	{
		return false;
	}

	int dwRsp = ShowMessageBox(_T("确定要删除此预置位"),true);
	if ( dwRsp == IDOK )
	{
// 		vector<TPanCam>::iterator iter = m_vctPresetList.begin() + (m_dwSelItemId + m_wCurPageIndex*6);
// 		m_vctPresetList.erase(iter);
// 		//删除完判断 应为正好整除并且数值相等
// 		if(m_dwSelItemId + m_wCurPageIndex*6 == m_vctPresetList.size() && m_vctPresetList.size() % 6 == 0 )
// 		{
// 			if(m_wCurPageIndex != 0)
// 			{
// 				m_wCurPageIndex = m_wCurPageIndex - 1;
// 			}
// 		}
// 		
// 		if (m_wCurPageIndex == 0)
// 		{
// 			ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
// 		}
// 		else
// 		{
// 			ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListLeft"));
// 		}
// 		if ( (m_wCurPageIndex+1)*6 >= m_vctPresetList.size())
// 		{
// 			ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListRight"));
// 		}
// 		else
// 		{
// 			ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
// 		}
		u16 wIndex = m_wCurPageIndex*6 + m_dwSelItemId;
		m_vctPresetList[wIndex].strPanCamName = _T("");
		UpdateList(_T(""),m_wCurPageIndex, m_dwSelItemId);

		ComInterface->DeletePanCamPreset(wIndex);
	}

	return true;
}

bool CPanCamLogic::OnBtnPresetAdd( TNotifyUI& msg )
{
	if (!IsCanSavePamPos())
	{
		return false;
	}

	if (m_dwSelItemId == -1)
	{
		ShowMessageBox((_T("请先选择需要设置的预置位")));
		return false;
	}
	CEditUI *pEdt = (CEditUI*)ICncCommonOp::FindControl( m_pm,m_strEdtPresetName.c_str() );   
	if ( pEdt )
	{
		pEdt->SetAttribute(_T("visible"),_T("true"));
		pEdt->SetText(_T(""));
	}
	ICncCommonOp::ShowControl( true, m_pm, _T("PageNameSet") );
	return true;
}

bool CPanCamLogic::BtnPresetCancel( TNotifyUI& msg )
{
	m_dwSelItemId = -1;
	m_wCurPageIndex = 0;
	m_emListState == EMSTATE_NO;
	ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));

	ICncCommonOp::ShowControl( false, m_pm, _T("PagePresetList") );
	return true;
}

bool CPanCamLogic::OnBtnPresetOk( TNotifyUI& msg )
{	
	if (m_dwSelItemId == -1)
	{
		ShowMessageBox((_T("请先选择需要设置的预置位")),false);
		return false;
	}
	if ( m_emListState == EMSTATE_SET )
	{
		if (!IsCanSavePamPos())
		{
			return false;
		}

		if(m_vctPresetList.at(m_dwSelItemId + m_wCurPageIndex*6).strPanCamName.IsEmpty())
		{
			ShowMessageBox((_T("请先设置预置位名称")),false);
			return false;
		}

		m_vctPresetList.at(m_dwSelItemId + m_wCurPageIndex*6).Copy(m_tCurrentPreset);
		ComInterface->SavePanCamPreset(m_dwSelItemId + m_wCurPageIndex*6);
	}
	else if ( m_emListState == EMSTATE_IMPLEMENT )
	{
		if(m_vctPresetList.at(m_dwSelItemId + m_wCurPageIndex*6).strPanCamName.IsEmpty())
		{
			ShowMessageBox((_T("当前选中预置位无效")),false);
			return false;
		}
		m_tCurrentPreset.Copy( m_vctPresetList.at(m_dwSelItemId + m_wCurPageIndex*6));
		ComInterface->ImpelPanCamPreset(m_dwSelItemId + m_wCurPageIndex*6);
	}
	m_emListState == EMSTATE_NO;
	m_dwSelItemId = -1;
	m_wCurPageIndex = 0;
	ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
	ICncCommonOp::ShowControl( false, m_pm, _T("PagePresetList") );
	return true;
}

bool CPanCamLogic::OnBtnSetPresetName( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pSlideTabLayout = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("preListSlidetab") );
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(m_wCurPageIndex);
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}

	if (m_tPanCamInfo.byPanCamNum == 0  )
	{
		return false;
	}

	CListContainerElementUI *pItem = (CListContainerElementUI *)msg.pSender->GetParent()->GetParent()->GetParent();
	if (pItem)
	{
		pItem->Select(true);
	}
	CString str(m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName);
	if (str.IsEmpty() && m_emListState == EMSTATE_IMPLEMENT)
	{
		return false;
	}

	String strNewName = ICncCommonOp::GetControlText(m_pm,_T("PresetName"),msg.pSender->GetParent()->GetParent());
	CString strName(strNewName.c_str());
	if (strName.IsEmpty() && m_emListState == EMSTATE_SET)
	{
		return false;
	}

	CEditUI *pEdt = (CEditUI*)ICncCommonOp::FindControl( m_pm,m_strEdtPresetName.c_str() );   
	if ( pEdt )
	{
		TPanCam* tPanCam = (TPanCam*)msg.pSender->GetTag();
		pEdt->SetText(LPCTSTR(tPanCam->strPanCamName));
		m_tCurrentPreset.wPresetID = m_wCurPageIndex*6 + m_dwSelItemId;
	}
	ICncCommonOp::ShowControl( true, m_pm, _T("PageNameSet") );
	return true;
}

bool CPanCamLogic::OnPresetListItemSelected( TNotifyUI& msg )
{
	m_dwSelItemId = msg.wParam;
	m_tCurrentPreset.wCamID = m_dwCurrentCamID;
	m_tCurrentPreset.wPresetID = m_wCurPageIndex*6 + m_dwSelItemId;
	m_tCurrentPreset.strPanCamName = m_vctPresetList[m_wCurPageIndex*6 + m_dwSelItemId].strPanCamName;
	return true;
}

bool CPanCamLogic::OnBtnCamListLeft( TNotifyUI& msg )
{
	UpdateShowPreList(true);
	return true;
}

bool CPanCamLogic::OnBtnCamListRight( TNotifyUI& msg )
{
	UpdateShowPreList(false);
	return true;
}

void CPanCamLogic::UpdateShowPreList( bool bLeft )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("preListSlidetab") );
	if (!pControl)
	{
		return ;
	}
	CTouchListUI *pTouchListLayoutUI = NULL;		
	pTouchListLayoutUI = (CTouchListUI*)pControl->GetItemAt(m_wCurPageIndex);
	if (pTouchListLayoutUI && pTouchListLayoutUI->GetCurSel()!= -1)
	{
		pTouchListLayoutUI->SelectItem(-1);
		m_dwSelItemId = -1;
	}

	if (!bLeft)
	{
		m_wCurPageIndex ++;
	}
	else
	{
		m_wCurPageIndex --;
	}

	pControl->SelectItem(m_wCurPageIndex);

	if (m_wCurPageIndex == 0)
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListLeft"));
	}
	if ( (m_wCurPageIndex+1)*6 >= m_vctPresetList.size())
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListRight"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
	}


// 	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("PresetList") );
// 	if ( pTileLayoutUI == NULL )
// 	{
// 		return ;
// 	}
// 	else
// 	{
// 		pTileLayoutUI->RemoveAll();
// 	}
// 	for ( u16 wId = 0; wId < 6 ; wId++ )
// 	{
// 		u16 index = wId + m_wCurPageIndex;
// 		if (index >= m_vctPresetList.size())
// 		{
// 			return;
// 		}
// 		CListContainerElementUI *pListContainer = 
// 			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PresetListItem") );
// 
// 		ICncCommonOp::SetControlText( m_vctPresetList.at(index).m_strPanCamName, m_pm, _T("PresetName"), pListContainer );
// 		CButtonUI* pBtnPresetName = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnSetPresetName"), pListContainer);
// 		if ( pBtnPresetName )
// 		{
// 			pBtnPresetName->SetTag( (UINT_PTR)&m_vctPresetList.at(index));
// 		}
// 
// 		pTileLayoutUI->Add(pListContainer);
// 	}
}

bool CPanCamLogic::OnSelSelCamInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSuccess = wParam;
	u8 wCamID = lParam;
	if (bIsSuccess)
	{
		m_dwCurrentCamID = wCamID;
		m_tCurrentPreset.wCamID = m_dwCurrentCamID;
		EnablePamCtrl(true);
	}
	else
	{
		m_tCurrentPreset.wCamID = -1;
		m_dwCurrentCamID = -1;
		EnablePamCtrl(false);

		ShowPopMsg(_T("选择全景摄像机失败"));
		CComboUI *pCombo = (CComboUI*)ICncCommonOp::FindControl(m_pm, _T("ComboCamSel"));
		if (pCombo)
		{
			pCombo->SelectItem(-1);
		}
	}
	return true;
}


bool CPanCamLogic::OnPanCamPresetSaveNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSuccess = wParam;
	m_wPresetID = lParam;

	if (!bIsSuccess)
	{	
		ShowPopMsg(_T("保存预置位失败"));
		return false;
	}
	else
	{
		WCharToMByte(m_tCurrentPreset.strPanCamName,m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName);
	}
    //判断ftp是否开启，未开启则开启
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if ( tTPFtpInfo.bOpen == FALSE )
    {
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
        return false;
    }
    else
    {
        //成功了下载图片 
        DownloadPanPosImg();
    }
	
	return true;
}

bool CPanCamLogic::OnPanCamPresetImpleNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSuccess = wParam;
	u8 wPresetID = lParam;

	if (!bIsSuccess)
	{
		ShowPopMsg(_T("调用预置位失败"));
	}

	return true;
}

bool CPanCamLogic::OnPanCamPresetDeleteNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSuccess = wParam;
	u8 wPresetID = lParam;

	if (!bIsSuccess)
	{
		ShowPopMsg(_T("删除预置位失败"));
		return false;
	}
	else
	{
		memset( m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName, 0, sizeof(TPanCamName) );
	}

	return true;
}

bool CPanCamLogic::OnPanCamSavePresetNameInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSuccess = wParam;
	u8 wPresetID = lParam;

	if (!bIsSuccess)
	{
		ShowPopMsg(_T("预置位名称修改失败"));

		CString strPresetName(m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName);
		m_vctPresetList.at(m_dwSelItemId + m_wCurPageIndex*6).strPanCamName = strPresetName;
		m_tCurrentPreset.strPanCamName = strPresetName;

		u8 wPageID;
		u8 wItemID;
		wPageID = m_tCurrentPreset.wPresetID/6;
		wItemID = m_tCurrentPreset.wPresetID%6 - 1;
		UpdateList(strPresetName,wPageID,wItemID);

		return false;
	}
	else
	{
		int nLength = m_tCurrentPreset.strPanCamName.GetLength();
		int nBytes = WideCharToMultiByte(CP_ACP,0,m_tCurrentPreset.strPanCamName,nLength,NULL,0,NULL,NULL);
		char* achName = new char[ nBytes + 1];
		memset(achName,0,nLength + 1);
		WideCharToMultiByte(CP_OEMCP, 0, m_tCurrentPreset.strPanCamName, nLength, achName, nBytes, NULL, NULL); 
		achName[nBytes] = 0;
		memset(m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName,0,MAX_PANCAMNAME_LEN);
		memcpy(m_tPanCamInfo.tPCamGroupName[m_tCurrentPreset.wCamID].tPanCamName[m_tCurrentPreset.wPresetID].achPanCamName,achName/*str*/,/*str.GetLength()*/nBytes);
		delete achName;
	}

	return true;
}

bool CPanCamLogic::OnPanCamStartInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSuccess = lParam;//表示操作是否成功

	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartCam"));
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsStart = ComInterface->IsLocalCnsPanCam();
	m_tPanCamInfo.bPanCamOpen = bIsStart;
	if ( !bIsSuccess  )//操作失败提示
	{
		CString str = _T("");
		if (bIsStart)
		{
			str.Format(_T("摄像机关闭失败"));
		}
		else
		{
			str.Format(_T("摄像机开启失败"));		
		}

		ShowPopMsg(str);

	}

	ICncCommonOp::EnableControl(bIsStart,m_pm,_T("ComboCamSel"));
	pCheckBox->SetCheckNoMsg(bIsStart);

	if (bIsStart && m_dwCurrentCamID != -1)
	{
		EnablePamCtrl(true);
	}
	else
	{
		EnablePamCtrl(false);
	}
	return true;
}

bool CPanCamLogic::OnSetShortCheck( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EM_ShortcutType em = (EM_ShortcutType)wParam;

	if ( em == emShortcutPanCam )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckCamShortCut") );
		if (!pControl)
		{
			return false;
		}

		if (m_tPanCamInfo.byPanCamNum == 0)
		{
			pControl->SetCheck(false);
			EM_ShortcutType em = emShortcutPanCam;
			NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, false );
		}
		else
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	return true;
}

bool CPanCamLogic::OnPanCamLstNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{	
    //文档摄像机信息
    map<u8, TCentreDCamCfg> mapDCamCfg;
    ComInterface->GetDCamStateMap(mapDCamCfg);
    //判断文档摄像机是否全部可用
    BOOL bIsDCamUsed = FALSE;
    map<u8, TCentreDCamCfg>::iterator itor = mapDCamCfg.begin();
    for ( ; itor != mapDCamCfg.end() ; itor++ )
    {
        if ( itor->second.bDCamUsed )
        {
            bIsDCamUsed = TRUE;
            break;
        }
    }
	//全景摄像机信息
	ComInterface->GetPanCamList( m_tPanCamInfo );
	if (wParam >= m_tPanCamInfo.byPanCamNum && wParam != 0 )//防止数量越界
	{
		return false;
	}

	m_dwCurrentCamID = wParam;
	m_tCurrentPreset.wCamID = m_dwCurrentCamID;

	if (m_tPanCamInfo.byPanCamNum == 0)
	{
		CCheckBoxUI* pCheckShortCut = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCamShortCut"));
		if ( pCheckShortCut )
		{
			pCheckShortCut->SetCheck(false);
		}
		CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartCam"));
		if ( pCheckBox )
		{
			pCheckBox->SetCheckNoMsg(false);
		}

		ICncCommonOp::EnableControl(false,m_pm,_T("ComboCamSel"));
		ICncCommonOp::EnableControl(false,m_pm,_T("CheckStartCam"));
		ICncCommonOp::EnableControl(false,m_pm,_T("CheckCamShortCut"));
		EnablePamCtrl(false);
		//关闭文档摄像机option
		ICncCommonOp::ShowControl(false,m_pm,_T("OptionFullCam"));
		//如果文档摄像机也未开启则关闭tab栏
		if ( !bIsDCamUsed )
		{
			ICncCommonOp::ShowControl(false,m_pm,_T("camera"));
			ICncCommonOp::ShowControl(false,m_pm,_T("ctlCam"));

			//选中默认项
			COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
			if (pOp)
			{
				pOp->Selected(true);
			}
		}
		else
		{
            //选中文档摄像机
            ICncCommonOp::OptionSelect(true, m_pm, _T("OptionFileCam"));
            m_pm->DoCase(_T("caseNoFullCamera"));
		}
		
		return false; 
	}
	else
	{
		//打开全景摄像机option
        if (!ICncCommonOp::IsOptionSelected(m_pm,_T("OptionFullCam")))
        {
            ICncCommonOp::ShowControl(true,m_pm,_T("OptionFullCam"));
        }

		ICncCommonOp::EnableControl(m_tPanCamInfo.bPanCamOpen,m_pm,_T("ComboCamSel"));
		ICncCommonOp::EnableControl(true,m_pm,_T("CheckStartCam"));
		ICncCommonOp::EnableControl(true,m_pm,_T("CheckCamShortCut"));

		CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartCam"));
		if ( pCheckBox )
		{
			pCheckBox->SetCheckNoMsg(m_tPanCamInfo.bPanCamOpen);
		}

		//打开tab栏
		ICncCommonOp::ShowControl(true,m_pm,_T("camera"));
		ICncCommonOp::ShowControl(true,m_pm,_T("ctlCam"));

		if ( !bIsDCamUsed )
		{
            //选中全景摄像机
            ICncCommonOp::OptionSelect(true, m_pm, _T("OptionFullCam"));
		}
        else
        {
            m_pm->DoCase(_T("caseHaveFullCamera"));
        }

		/*CCheckBoxUI* pCheckShortCut = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCamShortCut"));
		if ( pCheckShortCut )
		{
			if (!m_bIsShortCutClosed)
			{
				pCheckShortCut->SetCheck(true);
			}			
		}*/
	}

	CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboCamSel") );
	if (pCombo)
	{
		pCombo->RemoveAll();
		for (int nIndex = 1;nIndex<=m_tPanCamInfo.byPanCamNum ;nIndex++)
		{
			CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
			CString str=_T("");
			str.Format(_T("全景摄像机%d"),nIndex);
			pListLabelElement->SetText(str);
			pCombo->Add(pListLabelElement);
		}
		pCombo->SelectItem(m_dwCurrentCamID);
	}

	if (m_tPanCamInfo.bPanCamOpen && m_dwCurrentCamID != -1)
	{
		EnablePamCtrl(true);
	}
	else
	{
		EnablePamCtrl(false);
	}

    //ftp未开启则不下载预制位图片（防止登录时提示ftp未开启消息）
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        return false;
    }

	m_vecDownloadPicName.clear();
	for (int dwCamID = 0;dwCamID < m_tPanCamInfo.byPanCamNum ;dwCamID++)
	{
		for (int dwPosID = 0;dwPosID < MAX_PRESET_NUM ;dwPosID++)
		{
			CString str(m_tPanCamInfo.tPCamGroupName[dwCamID].tPanCamName[dwPosID].achPanCamName);
			if ( !str.IsEmpty() )
			{
				CString strName = _T("");
				strName.Format(_T("pancam%d_%d.jpg"), dwCamID, dwPosID);
				String str(strName);
				m_vecDownloadPicName.push_back(str);
			}
		}
	}

	if (m_vecDownloadPicName.size() == 0)
	{
		return true;
	}

    String strDownloadPath = (String)GetModuleFullPath() + TP_TEMPFILE_PATH + m_vecDownloadPicName.at(0);
    if( !DownloadCore( _T(TP_SNAPSHOT_PATH), strDownloadPath, m_vecDownloadPicName.at(0), FALSE) )
    {
        PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecDownloadPicName.at(0).c_str() );
    }

    //登录时不自动开启，只在保存预制位时开启

//     TTPFtpInfo tTPFtpInfo;
//     ComInterface->GetCnFtpInfo(tTPFtpInfo);
//     if (tTPFtpInfo.bOpen == FALSE )
//     {
//         m_bIsPanCamLisOpenFtp = true;
//         tTPFtpInfo.bOpen = TRUE;
//         ComInterface->SetCnFtpInfo(tTPFtpInfo);
//         return false;
//     }
//     else
//     {
//         String strDownloadPath = (String)GetModuleFullPath() + TP_TEMPFILE_PATH + m_vecDownloadPicName.at(0);
//         if( !DownloadCore( _T(TP_SNAPSHOT_PATH), strDownloadPath, m_vecDownloadPicName.at(0), FALSE) )
//         {
//             PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecDownloadPicName.at(0).c_str() );
//         }
//     }

	return true;
}

BOOL CPanCamLogic::DownloadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ )
{
	CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
	if(!PathFileExists(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}

	CString strIpAddr;

	m_cFtp.SethWnd( m_pm->GetPaintWindow() );
	m_cFtp.RegisterMsgHandle( WM_CNC_PAMCAMRPRESETPROGRESS );

	u32 dwIp;
	ComInterface->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = CA2T(inet_ntoa(addrIPAddr));

	TTPFtpInfo tTPFtpInfo;
	ComInterface->GetCnFtpInfo(tTPFtpInfo);
	if (tTPFtpInfo.bOpen == FALSE)
	{
		ShowPopMsg(_T("FTP上传服务器未开启!"));
		return FALSE;
	}
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/*_T("kedacomTP")*/ );
	if ( !bRet )
	{
		ShowPopMsg(_T("设置FTP上传服务器失败!"));
		return FALSE;
	}

	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	m_cFtp.SetAutoEndFtpFile(bAutoEnd/*FALSE*/);

	if ( !m_cFtp.BeginDownload(  strRemoteFilePath.c_str(), strLocalFile.c_str(),FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, FALSE ) )
	{
		ShowPopMsg(_T("下载全景摄像机预置位图片失败，参数错误!"));
		m_cFtp.SetAutoEndFtpFile(TRUE);
		return FALSE;
	}
	return TRUE;
}

bool CPanCamLogic::OnDownloadProgress( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);

	switch( emFileFtpStatus )
	{
	case emFtpBegin:
		{
			//PrtMsg( 0, emEventTypeCmsWindow, _T("%s已经进入传输状态！"), m_vecDownloadPicName.at(0).c_str() );
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP接口0为成功  默认失败
			m_cFtp.EndFtpFile();	
			if ( 0 != dwSuccess )
			{
				PrtMsg( 0, emEventTypeCmsWindow, "进行ftp后%s传输失败！", m_vecDownloadPicName.at(0).c_str() );
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "导入文件出错，错误原因：%s！", (CT2A)pszMsg );
				LocalFree( pszMsg );
			}	
			//不管当前是否成功 都要进行下一个文件的下载 
			if ( m_vecDownloadPicName.size() > 0 )
			{	
				vector<String>::iterator itr = m_vecDownloadPicName.begin();
				m_vecDownloadPicName.erase(itr);
				PrtMsg( 0, emEventTypeCmsWindow, "此时待传输文件个数：%d", m_vecDownloadPicName.size()-1 );
				if ( m_vecDownloadPicName.size() > 0 )
				{
					String strDownloadPath = (String)GetModuleFullPath() + TP_TEMPFILE_PATH + m_vecDownloadPicName.at(0);
					if ( !DownloadCore( _T(TP_SNAPSHOT_PATH), strDownloadPath, m_vecDownloadPicName.at(0), FALSE) )
					{			
						PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecDownloadPicName.at(0).c_str() );
					}		
				}
				else
				{
					//全部传输完毕发送消息				
					PrtMsg( 0, emEventTypeCmsWindow, "图片下载完毕" );
				}
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

bool CPanCamLogic::WCharToMByte(CString strPresetName, char* achOut)
{
	int nLength = strPresetName.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP,0,strPresetName,nLength,NULL,0,NULL,NULL);
	char* achName = new char[ nBytes + 1];
	memset(achName,0,nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, strPresetName, nLength, achName, nBytes, NULL, NULL); 
	achName[nBytes] = 0;
	memcpy(achOut,achName/*str*/,/*str.GetLength()*/nBytes);
	delete achName;

	return true;
}

bool CPanCamLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_dwCurrentCamID = -1;
	m_dwSelItemId = -1;
	m_wCurPageIndex = 0;
	m_emListState = EMSTATE_NO;
    m_wPresetID = -1;
//    m_bIsPanCamLisOpenFtp = false;

	m_cFtp.EndFtpFile();

	ICncCommonOp::EnableControl(false,m_pm,_T("btnCamListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnCamListRight"));
	ICncCommonOp::ShowControl( false, m_pm, _T("PagePresetList") );
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNameSet") );

	return true;
}

void CPanCamLogic::EnablePamCtrl( bool bIsEnable )
{
	//ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("ComboCamSel"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnPosSet"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnSaveSet"));

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamUp"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamLeft"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamRight"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamDown"));

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnViewPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnViewMinus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnFocusPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnFocusAuto"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnFocusMinus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnBrightPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnBrightMinus"));

}

bool CPanCamLogic::IsCanSavePamPos()
{
	//1.双流源不是全景摄像机并且开启了双流 不能进行快照设置 包括本地双流
	//2.会议中不能保存
	TScreenInfo tScrnInfo0,tScrnInfo1,tScrnInfo2;
	ComInterface->GetCnsScreenInfoByID( 0, tScrnInfo0 );
	ComInterface->GetCnsScreenInfoByID( 1, tScrnInfo1 );
	ComInterface->GetCnsScreenInfoByID( 2, tScrnInfo2 );
	TDualSrcInfo  tDualSrcInfo; 
	ComInterface->GetDualSrcInfo( tDualSrcInfo );
	if (ComInterface->IsInConf())
	{
		ShowMessageBox((_T("会议中，不能进行预置位保存")));
		return false;
	}

	if(tDualSrcInfo.emCurrentType != emVgaTypeFullScreenCamera 
		&& ( (tScrnInfo0.emPosPic == emPic_SelDual || tScrnInfo0.emPosPic == emPic_Dual) ||
		     (tScrnInfo1.emPosPic == emPic_SelDual || tScrnInfo1.emPosPic == emPic_Dual) ||
			 (tScrnInfo2.emPosPic == emPic_SelDual || tScrnInfo2.emPosPic == emPic_Dual) ))
	{
		ShowMessageBox((_T("开启演示时不能进行预置位保存")));
		return false;
	}

	return true;
}

void CPanCamLogic::DownloadPanPosImg()
{
    CString strName = _T("");
    strName.Format(_T("pancam%d_%d.jpg"), m_dwCurrentCamID, m_wPresetID);
    String str(strName);
    m_vecDownloadPicName.push_back(str);
    String strDownloadPath = (String)GetModuleFullPath() + TP_TEMPFILE_PATH + m_vecDownloadPicName.at(0);
    if (m_vecDownloadPicName.size() == 1)
    {
        if( !DownloadCore( _T(TP_SNAPSHOT_PATH), strDownloadPath, m_vecDownloadPicName.at(0), FALSE) )
        {
            PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecDownloadPicName.at(0).c_str() );
        }
    }
}

bool CPanCamLogic::OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE )
    {
        if (m_wPresetID != -1 /*|| m_bIsPanCamLisOpenFtp*/)
        {
            m_wPresetID = -1;
//            m_bIsPanCamLisOpenFtp = false;
            ShowPopMsg(_T("FTP上传服务器开启失败!"));
            return false;
        }
    }
    else
    {
        if (m_wPresetID != -1)
        {
            DownloadPanPosImg();
            m_wPresetID = -1;
            return false;
        }
//         if (m_bIsPanCamLisOpenFtp)
//         {
//             m_bIsPanCamLisOpenFtp = false;
//             if (m_vecDownloadPicName.size() != 0)
//             {
//                 String strDownloadPath = (String)GetModuleFullPath() + TP_TEMPFILE_PATH + m_vecDownloadPicName.at(0);
//                 if( !DownloadCore( _T(TP_SNAPSHOT_PATH), strDownloadPath, m_vecDownloadPicName.at(0), FALSE) )
//                 {
//                     PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecDownloadPicName.at(0).c_str() );
//                 }
//             }
//         }
    }
    
    return true;
}

bool CPanCamLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}
