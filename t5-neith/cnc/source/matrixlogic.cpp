#include "StdAfx.h"
#include "matrixlogic.h"
#include "confmsglogic.h"

template<> CMatrixLogic* Singleton<CMatrixLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CMatrixLogic,CNotifyUIImpl)

    MSG_INIWINDOW(_T("RoomCtrlLayout"), OnInit)

	//矩阵界面
	MSG_CLICK(_T("BtnEditPreplan"), OnBtnEditPreplan)
	MSG_CLICK(_T("BtnSavePreplan"), OnBtnSavePreplan)
	MSG_CLICK(_T("BtnApplyPreplan"), OnBtnApplyPreplan)
    MSG_SELECTCHANGE(_T("OptIsUseful"), OnOptIsUseFulSelChange)

	//编辑界面
	MSG_CLICK(_T("BtnUIReName"), OnBtnUIReName)
	MSG_CLICK(_T("BtnUIApply"), OnBtnUIApply)
	MSG_CLICK(_T("BtnUIDelete"), OnBtnUIDelete)
	MSG_CLICK(_T("BtnUICancel"), OnBtnUICancel)

	//保存界面
	MSG_CLICK(_T("BtnSaveUICancel"), OnBtnSaveUICancel)
	MSG_CLICK(_T("BtnSaveUISave"), OnBtnSaveUISave)

    //重命名界面
    MSG_CLICK(_T("BtnReNameUICancel"), OnBtnReNameUICancel)
    MSG_CLICK(_T("BtnReNameUISave"), OnBtnReNameUISave)

    USER_MSG(UI_CNS_CNSINFO_NOTIFY,OnCnsInfoNotify)

    USER_MSG(UI_MATRIXCONFIG_NTY,OnMatrixConFigNotify)
    USER_MSG(UI_MATRIXSCENE_NTY,OnMatrixSceneInfoNotify)
    USER_MSG(UI_CURMATRIXSCENE_NTY,OnCurMatrixInfoNotify)
    USER_MSG(UI_SAVEMATRIXSCENE_IND,OnSaveMatrixSceneInd)
    USER_MSG(UI_RENAMEMATRIXSCENE_IND,OnReNameMatrixSceneInd)
    USER_MSG(UI_DELETEMATRIXSCENE_IND,OnDeleteMatrixSceneInd)
    USER_MSG(UI_APPLYMATRIXSCENE_IND,OnApplyMatrixSceneInd)

APP_END_MSG_MAP()

CMatrixLogic::CMatrixLogic()
{
	m_pInputList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("InputList") );
	
}

CMatrixLogic::~CMatrixLogic()
{

}

bool CMatrixLogic::OnInit(TNotifyUI& msg)
{
    //更新可保存的预案编号
    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSavePreplanNo") );
    for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
    {
        CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        CDuiString strtmp = _T("");
        strtmp.Format(_T("预案%d"),i+1);
        pListLabelElement->SetText(strtmp);
        pListLabelElement->SetnTag(i+1);
        pComboEx->Add(pListLabelElement);
    }
    return true;
}

void CMatrixLogic::UpdateMatrixTip(const TTPCurMatrixInfo& tTPCurMatrixInfo)
{
    //横向表头 输入
    CTouchListUI* pMatrixListHeadH = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixListHeadH") );
    if (pMatrixListHeadH)
    {
        pMatrixListHeadH->SetColumns(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum);
        for (int i = 0 ; i < tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum ; i++ )
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixListHeaderItem"));
            if (pListContainer)
            {
                switch(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_atTPAVChannelInfo[i].m_EmAVChannelType)
                {
                case emV_DVI:
                    ICncCommonOp::SetControlText( _T("DVI") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_HDMI:
                    ICncCommonOp::SetControlText( _T("HDMI") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_SDI:
                    ICncCommonOp::SetControlText( _T("SDI") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_VGA:
                    ICncCommonOp::SetControlText( _T("VGA") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emAVInvalid:
                default:
                    ICncCommonOp::SetControlText( _T("UNKNOWN") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                }
                pMatrixListHeadH->Add(pListContainer);
            }
        }
    }
    //纵向表头 输出
    CTouchListUI* pMatrixListHeadV = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixListHeadV") );
    if (pMatrixListHeadV)
    {
        pMatrixListHeadV->SetColumns(1);
        for (int i = 0 ; i < tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_byNum ; i++ )
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixListHeaderItem"));
            if (pListContainer)
            {
                switch(tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_atTPAVChannelInfo[i].m_EmAVChannelType)
                {
                case emV_DVI:
                    ICncCommonOp::SetControlText( _T("DVI") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_HDMI:
                    ICncCommonOp::SetControlText( _T("HDMI") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_SDI:
                    ICncCommonOp::SetControlText( _T("SDI") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_VGA:
                    ICncCommonOp::SetControlText( _T("VGA") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emAVInvalid:
                default:
                    ICncCommonOp::SetControlText( _T("UNKNOWN") ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                }
                pMatrixListHeadV->Add(pListContainer);
            }
        }
    }
    //列表内容
    CTouchListUI* pMatrixList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixList") );
    if ( pMatrixList )
    {
        for (int iraw = 0 ; iraw < tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_byNum ; iraw++)
        {
            CListContainerElementUI *pInfoListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixInfoListItem"));
            if (pInfoListContainer)
            {
                CTouchListUI* pMatrixInfoList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixInfoList"), pInfoListContainer );
                if (pMatrixInfoList)
                {
                    pMatrixInfoList->SetColumns(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum);
                    for (int icol = 0; icol < tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum ; icol++)
                    {
                        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixListItem"));
                        CDuiString strGroup = _T("");
                        strGroup.Format(_T("MatrixGroup%d"),iraw);
                        CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("OptIsUseful"),pListContainer);
                        pCheckBox->SetGroup(strGroup.GetData());
                        pMatrixInfoList->Add(pListContainer);
                    }
                    pInfoListContainer->SetFixedWidth(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum * NUM_MATRIX_WIDTH);
                }
                pMatrixList->Add(pInfoListContainer);
            }
        }
    }
}

void CMatrixLogic::UpdateMatrixInfo(const TTPCurMatrixInfo& tTPCurMatrixInfo)
{
    for (int iout = 0 ; iout < MT_MAX_MATRIX_CHANNEL_LEN ; iout++ )
    {
        int iin = tTPCurMatrixInfo.m_achMatrixInOutRelation[iout];
        if (iin >= 0)
        {
            CTouchListUI* pMatrixList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixList") );
            if ( pMatrixList )
            {
                CTouchListUI* pMatrixOutInfoList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixInfoList"), pMatrixList->GetItemAt(iout));
                if (pMatrixOutInfoList)
                {
                    CCheckBoxUI* pStateCheck = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("OptIsUseful"), pMatrixList->GetItemAt(iin));
                    if (pStateCheck)
                    {
                        pStateCheck->SetCheckNoMsg(true);
                    }
                }
            }
        }
    }
}

bool CMatrixLogic::OnBtnEditPreplan( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseShowEditPreplan"));
	return true;
}

bool CMatrixLogic::OnBtnSavePreplan( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseShowSavePreplan"));
	return true;
}

bool CMatrixLogic::OnBtnApplyPreplan( TNotifyUI& msg )
{
	return true;
}

bool CMatrixLogic::OnOptIsUseFulSelChange(TNotifyUI& msg)
{
    CCheckBoxUI* pCheckSel = (CCheckBoxUI*)msg.pSender;//操作项
    if (!pCheckSel)
    {
        return false;
    }
    CTouchListUI* pTouchListIn = (CTouchListUI*)msg.pSender->GetParent()->GetParent();
    if (pTouchListIn)
    {
        int iin = pTouchListIn->GetItemIndex(msg.pSender->GetParent());
        CTouchListUI* pTouchListOut = (CTouchListUI*)pTouchListIn->GetParent()->GetParent();
        if (pTouchListOut)
        {
            int iout = pTouchListOut->GetItemIndex(pTouchListIn->GetParent());
            ComInterface->SetMatrixInOutCmd(iin, iout);
        }
    }
    return true;
}

bool CMatrixLogic::OnBtnUIReName( TNotifyUI& msg )
{
    m_pm->DoCase(_T("caseShowReNamePreplan"));
    TTPMatrixSceneInfo  atMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );

    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboReNamePreplanNo") );
    for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
    {
        if (atMatrixSceneInfo[i].bUsed == FALSE)
        {
            continue;
        }
        CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        CDuiString strtmp = _T("");
        strtmp.Format(_T("预案%d"),i+1);
        pListLabelElement->SetText(strtmp);
        pListLabelElement->SetnTag(i+1);
        pComboEx->Add(pListLabelElement);
    }
	return true;
}

bool CMatrixLogic::OnBtnUIApply( TNotifyUI& msg )
{
    u32 dwIndex = 0;
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboSelPreplanNo"));
    if (pcombo)
    {
        CListLabelElementUI* pSelItem = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
        if (pSelItem)
        {
            dwIndex = pSelItem->GetnTag();
        }
    }

    ComInterface->ApplyMatrixScenceCmd(dwIndex);
	return true;
}

bool CMatrixLogic::OnBtnUIDelete( TNotifyUI& msg )
{
    u32 dwIndex = 0;
    CString strName = _T("");
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboSelPreplanNo"));
    if (pcombo)
    {
        CListLabelElementUI* pSelItem = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
        if (pSelItem)
        {
            dwIndex = pSelItem->GetnTag();
            strName = pSelItem->GetText();
        }
    }
    CDuiString strMsg = _T("");
    strMsg.Format(_T("是否删除预案“%s”？"),strName);
    int nResult = ShowMessageBox(strMsg,true);
    if ( IDOK == nResult )
    {
        ComInterface->DeleteMatrixScenceCmd(dwIndex);
    }
	return true;
}

bool CMatrixLogic::OnBtnUICancel( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseShowMatrix"));
	return true;
}

bool CMatrixLogic::OnBtnSaveUICancel( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseShowMatrix"));
	return true;
}

bool CMatrixLogic::OnBtnSaveUISave( TNotifyUI& msg )
{
    //获取编号
    u32 dwIndex = 0;
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboSavePreplanNo"));
    if (pcombo)
    {
        dwIndex = pcombo->GetItemAt(pcombo->GetCurSel())->GetnTag();
    }
    //获取名称
    CString strName = (ICncCommonOp::GetControlText(m_pm,_T("EditSavePreplanName"))).c_str();
    s8 achName[TP_MATRIX_SCENENAME_LEN + 1] = {0};
    memcpy(achName,CT2A(strName),sizeof(CT2A(strName)));

    ComInterface->SaveMatrixScenceCmd(dwIndex,achName);
	return true;
}

bool CMatrixLogic::OnBtnReNameUICancel( TNotifyUI& msg )
{
    m_pm->DoCase(_T("caseShowEditPreplan"));
    return true;
}

bool CMatrixLogic::OnBtnReNameUISave( TNotifyUI& msg )
{
    //获取编号
    u32 dwIndex = 0;
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboReNamePreplanNo"));
    if (pcombo)
    {
        dwIndex = pcombo->GetItemAt(pcombo->GetCurSel())->GetnTag();
    }
    //获取名称
    CString strName = (ICncCommonOp::GetControlText(m_pm,_T("EditReNamePreplanName"))).c_str();
    s8 achName[TP_MATRIX_SCENENAME_LEN + 1] = {0};
    memcpy(achName,CT2A(strName),sizeof(CT2A(strName)));

    ComInterface->ReNameMatrixScenceCmd(dwIndex,achName);
    return true;
}

bool CMatrixLogic::OnCnsInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    TTPCnsInfo tLocalCnsInfo;
    ComInterface->GetLocalCnsInfo( tLocalCnsInfo );
    ICncCommonOp::SetControlText((CA2T)tLocalCnsInfo.m_achRoomName,m_pm,_T("ConfRoomName"));
    return NO_ERROR;
}

bool CMatrixLogic::OnMatrixConFigNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    return true;
}

bool CMatrixLogic::OnMatrixSceneInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPMatrixSceneInfo  atMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );

    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSelPreplanNo") );
    for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
    {
        if (atMatrixSceneInfo[i].bUsed == FALSE)
        {
            continue;
        }
        CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        CDuiString strtmp = _T("");
        strtmp.Format(_T("预案%d:%s"),i+1,CA2T(atMatrixSceneInfo[i].achSceneName));
        pListLabelElement->SetText(strtmp);
        pListLabelElement->SetnTag(i+1);
        pComboEx->Add(pListLabelElement);
    }
    return true;
}

bool CMatrixLogic::OnCurMatrixInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPCurMatrixInfo tTPCurMatrixInfo;
    ComInterface->GetCurMatrixInfo(tTPCurMatrixInfo);
    UpdateMatrixTip(tTPCurMatrixInfo);
    UpdateMatrixInfo(tTPCurMatrixInfo);
    return true;
}

bool CMatrixLogic::OnSaveMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (bSuccess == FALSE)
    {
        ShowPopMsg(_T("矩阵预案保存失败"));
    }
    return true;
}

bool CMatrixLogic::OnReNameMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (bSuccess == FALSE)
    {
        ShowPopMsg(_T("矩阵预案重命名失败"));
    }
    return true;
}

bool CMatrixLogic::OnDeleteMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (bSuccess == FALSE)
    {
        ShowPopMsg(_T("矩阵预案删除失败"));
    }
    return true;
}

bool CMatrixLogic::OnApplyMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (bSuccess == FALSE)
    {
        ShowPopMsg(_T("矩阵预案应用失败"));
    }
    return true;
}
