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
    MSG_ITEMSELECTD(_T("ComboSelPreplanNo"), OnSelPreplanSelectChange)
	MSG_CLICK(_T("BtnUIReName"), OnBtnUIReName)
	MSG_CLICK(_T("BtnUIApply"), OnBtnUIApply)
	MSG_CLICK(_T("BtnUIDelete"), OnBtnUIDelete)
	MSG_CLICK(_T("BtnUICancel"), OnBtnUICancel)

	//保存界面
    MSG_ITEMSELECTD(_T("ComboSavePreplanNo"), OnPreplanSaveChange)
	MSG_CLICK(_T("BtnSaveUICancel"), OnBtnSaveUICancel)
	MSG_CLICK(_T("BtnSaveUISave"), OnBtnSaveUISave)

    //重命名界面
    MSG_ITEMSELECTD(_T("ComboReNamePreplanNo"), OnPreplanReNameChange)
    MSG_CLICK(_T("BtnReNameUICancel"), OnBtnReNameUICancel)
    MSG_CLICK(_T("BtnReNameUISave"), OnBtnReNameUISave)

    USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

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
    CComboUI* pComboSave = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSavePreplanNo") );
    if (pComboSave)
    {
        pComboSave->RemoveAll();
        for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
        {
            CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
            CDuiString strtmp = _T("");
            strtmp.Format(_T("预案%d"),i+1);
            pListLabelElement->SetText(strtmp);
            pListLabelElement->SetnTag(i);
            pComboSave->Add(pListLabelElement);
        }
    }
    return true;
}

CDuiString CMatrixLogic::GetTouchListName(EmTouchList emTouchList, EmTouchListType emTouchListType)
{
    CDuiString strRe = _T("");
    switch (emTouchList)
    {
    case emOperation:
        {
            switch (emTouchListType)
            {
            case emTouchListHTip:
                strRe = _T("MatrixListHeadH");
                break;
            case emTouchListVTip:
                strRe = _T("MatrixListHeadV");
                break;
            default:
                strRe = _T("MatrixList");
                break;
            }
        }
        break;
    default:
        {
            switch (emTouchListType)
            {
            case emTouchListHTip:
                strRe = _T("MatrixEditListHeadH");
                break;
            case emTouchListVTip:
                strRe = _T("MatrixEditListHeadV");
                break;
            default:
                strRe = _T("MatrixEditList");
                break;
            }
        }
        break;
    }
    return strRe;
}

void CMatrixLogic::UpdateMatrixTip(const TTPCurMatrixInfo& tTPCurMatrixInfo, EmTouchList emTouchList)
{
    //横向表头 输入
    CTouchListUI* pMatrixListHeadH = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, GetTouchListName(emTouchList, emTouchListHTip)/*_T("MatrixListHeadH")*/ );
    if (pMatrixListHeadH)
    {
        pMatrixListHeadH->RemoveAll();
        pMatrixListHeadH->SetColumns(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum);
        //计数串口
        int nDVI = 0;
        int nHDMI = 0;
        int nSDI = 0;
        int nVGA = 0;
        int nUNKNOW = 0;
        CDuiString strShow = _T("");
        CListContainerElementUI *pInfoListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixInfoListItem"));
        if (pInfoListContainer)
        {
            CTouchListUI* pMatrixInfoList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixInfoList"), pInfoListContainer );
            if (pMatrixInfoList)
            {
                pMatrixInfoList->SetColumns(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum);
                for (int i = 0 ; i < tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum ; i++ )
                {
                    CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixListHeaderItem"));
                    if (pListContainer)
                    {
                        switch(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_atTPAVChannelInfo[i].m_EmAVChannelType)
                        {
                        case emV_DVI:
                            strShow.Format(_T("DVI%d"), ++nDVI);
                            ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                            break;
                        case emV_HDMI:
                            strShow.Format(_T("HDMI%d"), ++nHDMI);
                            ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                            break;
                        case emV_SDI:
                            strShow.Format(_T("SDI%d"), ++nSDI);
                            ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                            break;
                        case emV_VGA:
                            strShow.Format(_T("VGA%d"), ++nVGA);
                            ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                            break;
                        case emAVInvalid:
                        default:
                            strShow.Format(_T("UNKNOW%d"), ++nUNKNOW);
                            ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                            break;
                        }
                        pMatrixInfoList->Add(pListContainer);
                    }
                }
            }
            pInfoListContainer->SetFixedWidth(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum * NUM_MATRIX_WIDTH);
            pMatrixListHeadH->Add(pInfoListContainer);

            //纵向滚动条填充
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("VScorllItem"));
            if (pListContainer)
            {
                pMatrixListHeadH->Add(pListContainer);
            }
        }
    }
    //纵向表头 输出
    CTouchListUI* pMatrixListHeadV = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, GetTouchListName(emTouchList, emTouchListVTip)/*_T("MatrixListHeadV")*/ );
    if (pMatrixListHeadV)
    {
        pMatrixListHeadV->RemoveAll();
        pMatrixListHeadV->SetColumns(1);
        //计数串口
        int nDVI = 0;
        int nHDMI = 0;
        int nSDI = 0;
        int nVGA = 0;
        int nUNKNOW = 0;
        CDuiString strShow = _T("");
        for (int i = 0 ; i < tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_byNum ; i++ )
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("MatrixListHeaderItem"));
            if (pListContainer)
            {
                switch(tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_atTPAVChannelInfo[i].m_EmAVChannelType)
                {
                case emV_DVI:
                    strShow.Format(_T("DVI%d"), ++nDVI);
                    ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_HDMI:
                    strShow.Format(_T("HDMI%d"), ++nHDMI);
                    ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_SDI:
                    strShow.Format(_T("SDI%d"), ++nSDI);
                    ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emV_VGA:
                    strShow.Format(_T("VGA%d"), ++nVGA);
                    ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                case emAVInvalid:
                default:
                    strShow.Format(_T("UNKNOW%d"), ++nUNKNOW);
                    ICncCommonOp::SetControlText( strShow ,m_pm,_T("MatrixListHeadItem") ,pListContainer );
                    break;
                }
                pMatrixListHeadV->Add(pListContainer);
            }
        }
        //纵向滚动条填充
        CListContainerElementUI *pListContainerH = (CListContainerElementUI*)CONTROLFACTORY()->GetControl(_T("HScorllItem"));
        if (pListContainerH)
        {
            pMatrixListHeadV->Add(pListContainerH);
        }
    }
    //列表内容
    CTouchListUI* pMatrixList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, GetTouchListName(emTouchList, emTouchListInfo)/*_T("MatrixList")*/ );
    if ( pMatrixList )
    {
        pMatrixList->RemoveAll();
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
                        if (emTouchList == emOperation)
                        {
                            strGroup.Format(_T("MatrixGroup%d"),iraw);
                        }
                        else
                        {
                            strGroup.Format(_T("EditMatrixGroup%d"),iraw);
                        }
                        CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("OptIsUseful"),pListContainer);
                        pCheckBox->SetGroup(strGroup.GetData());
                        if (emTouchList != emOperation)
                        {
                            pCheckBox->SetEnabled(false);
                        }
                        pMatrixInfoList->Add(pListContainer);
                    }
                    pInfoListContainer->SetFixedWidth(tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum * NUM_MATRIX_WIDTH);
                }
                pMatrixList->Add(pInfoListContainer);
            }
        }
    }
}

void CMatrixLogic::UpdateMatrixInfo(const TTPCurMatrixInfo& tTPCurMatrixInfo, EmTouchList emTouchList)
{
    for (int iout = 0 ; iout < MT_MAX_MATRIX_CHANNEL_LEN ; iout++ )
    {
        int iin = tTPCurMatrixInfo.m_achMatrixInOutRelation[iout];
        if (iin >= 0)
        {
            CTouchListUI* pMatrixList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, GetTouchListName(emTouchList, emTouchListInfo)/*_T("MatrixList")*/ );
            if ( pMatrixList )
            {
                //找到对应输出端口号
                int iControlCol = -1;
                for (int iCol = 0 ; iCol < tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_byNum ; iCol++ )
                {
                    if (iout == tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_atTPAVChannelInfo[iCol].m_dwChannelNo)
                    {
                        iControlCol = iCol;
                        break;
                    }
                }
                CListContainerElementUI* pMatrixListParent = (CListContainerElementUI*)pMatrixList->GetItemAt(iControlCol);
                if (pMatrixListParent)
                {
                    CTouchListUI* pMatrixOutInfoList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MatrixInfoList"), pMatrixListParent);
                    if (pMatrixOutInfoList)
                    {
                        //找到对应输入端口号
                        int iControlRow = -1;
                        for (int iRow = 0 ; iRow < tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum ; iRow++ )
                        {
                            if (iin == tTPCurMatrixInfo.m_tTPMatrixInInfo.m_atTPAVChannelInfo[iRow].m_dwChannelNo)
                            {
                                iControlRow = iRow;
                                break;
                            }
                        }
                        CCheckBoxUI* pStateCheck = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("OptIsUseful"), pMatrixOutInfoList->GetItemAt(iControlRow));
                        if (pStateCheck)
                        {
                            if (emTouchList == emOperation)
                            {
                                pStateCheck->SetCheck(true);
                            }
                            else
                            {
                                pStateCheck->SetCheckNoMsg(true);
                            }
                        }
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

            TTPCurMatrixInfo tTPCurMatrixInfo;
            ComInterface->GetCurMatrixInfo(tTPCurMatrixInfo);
            if ((iin < tTPCurMatrixInfo.m_tTPMatrixInInfo.m_byNum && iout < tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_byNum) &&
                tTPCurMatrixInfo.m_achMatrixInOutRelation[tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_atTPAVChannelInfo[iout].m_dwChannelNo] !=
                tTPCurMatrixInfo.m_tTPMatrixInInfo.m_atTPAVChannelInfo[iin].m_dwChannelNo)
            {
                ComInterface->SetMatrixInOutCmd(    tTPCurMatrixInfo.m_tTPMatrixInInfo.m_atTPAVChannelInfo[iin].m_dwChannelNo,
                                                    tTPCurMatrixInfo.m_tTPMatrixOutInfo.m_atTPAVChannelInfo[iout].m_dwChannelNo);
            }
        }
    }
    return true;
}

bool CMatrixLogic::OnSelPreplanSelectChange(TNotifyUI& msg)
{
    //获取编号
    u32 dwIndex = 0;
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboSelPreplanNo"));
    if (pcombo == NULL)
    {
        return false;
    }
    CListLabelElementUI* pListLabelElementUI = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
    if (pListLabelElementUI == NULL)
    {
        return false;
    }
    dwIndex = pListLabelElementUI->GetnTag();
    //更新显示
    TTPMatrixSceneInfo atTPMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atTPMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );
    if (dwIndex < TP_MATRIX_SCENENUM_MAX)
    {
        if (atTPMatrixSceneInfo[dwIndex].bUsed)
        {
            m_pm->DoCase(_T("caseSelectUsedPrePlan"));

            TTPCurMatrixInfo tTPCurMatrixInfo;
            ComInterface->GetCurMatrixInfo(tTPCurMatrixInfo);
            memcpy(tTPCurMatrixInfo.m_achMatrixInOutRelation, atTPMatrixSceneInfo[dwIndex].m_achMatrixInOutRelation, sizeof(s32) * MT_MAX_MATRIX_CHANNEL_LEN );
            UpdateMatrixTip(tTPCurMatrixInfo, emManager);
            UpdateMatrixInfo(tTPCurMatrixInfo, emManager);
        }
        else
        {
            m_pm->DoCase(_T("caseSelectUsedPrePlan"));

            TTPCurMatrixInfo tTPCurMatrixInfo;
            ComInterface->GetCurMatrixInfo(tTPCurMatrixInfo);
            memset(tTPCurMatrixInfo.m_achMatrixInOutRelation, -1, sizeof(s32) * MT_MAX_MATRIX_CHANNEL_LEN );
            UpdateMatrixTip(tTPCurMatrixInfo, emManager);
            UpdateMatrixInfo(tTPCurMatrixInfo, emManager);
        }
    }
    else
    {
        m_pm->DoCase(_T("caseSelectNULLPrePlan"));
    }
    return NO_ERROR;
}

bool CMatrixLogic::OnPreplanSaveChange(TNotifyUI& msg)
{
    //获取编号
    u32 dwIndex = 0;
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboSavePreplanNo"));
    if (pcombo == NULL)
    {
        return false;
    }
    CListLabelElementUI* pListLabelElementUI = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
    if (pListLabelElementUI == NULL)
    {
        return false;
    }
    dwIndex = pListLabelElementUI->GetnTag();
    //更新显示
    TTPMatrixSceneInfo atTPMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atTPMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );
    if (dwIndex < TP_MATRIX_SCENENUM_MAX)
    {
        ICncCommonOp::SetControlText(CA2T(atTPMatrixSceneInfo[dwIndex].achSceneName), m_pm, _T("EditSavePreplanName"));
    }
}

bool CMatrixLogic::OnPreplanReNameChange(TNotifyUI& msg)
{
    //获取编号
    u32 dwIndex = 0;
    CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboReNamePreplanNo"));
    if (pcombo == NULL)
    {
        return false;
    }
    CListLabelElementUI* pListLabelElementUI = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
    if (pListLabelElementUI == NULL)
    {
        return false;
    }
    dwIndex = pListLabelElementUI->GetnTag();
    //更新显示
    TTPMatrixSceneInfo atTPMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atTPMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );
    if (dwIndex < TP_MATRIX_SCENENUM_MAX)
    {
        ICncCommonOp::SetControlText(CA2T(atTPMatrixSceneInfo[dwIndex].achSceneName), m_pm, _T("EditReNamePreplanName"));
    }
}

bool CMatrixLogic::OnBtnUIReName( TNotifyUI& msg )
{
    m_pm->DoCase(_T("caseShowReNamePreplan"));
    TTPMatrixSceneInfo  atMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );

    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboReNamePreplanNo") );
    if (pComboEx)
    {
        pComboEx->RemoveAll();
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
            pListLabelElement->SetnTag(i);
            pComboEx->Add(pListLabelElement);
        }
        CComboUI* pcombo = (CComboUI*)ICncCommonOp::FindControl(m_pm,_T("ComboSelPreplanNo"));
        if (pcombo && pcombo->GetCurSel() < pComboEx->GetCount())
        {
            pComboEx->SelectItem(pcombo->GetCurSel());
        }
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
    m_pm->DoCase(_T("caseShowMatrix"));
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
    if (pcombo == NULL)
    {
        return false;
    }
    CListLabelElementUI* pListLabelElementUI = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
    if (pListLabelElementUI == NULL)
    {
        return false;
    }
     dwIndex = pListLabelElementUI->GetnTag();
    //获取名称
    CString strName = (ICncCommonOp::GetControlText(m_pm,_T("EditSavePreplanName"))).c_str();
    s8 achName[TP_MATRIX_SCENENAME_LEN + 1] = {0};
    memcpy(achName,CT2A(strName),sizeof(CT2A(strName)));

    //判断编号是否已保存
    TTPMatrixSceneInfo  atMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );
    if (dwIndex < TP_MATRIX_SCENENUM_MAX)
    {
        if (atMatrixSceneInfo[dwIndex].bUsed)
        {
            int nResult = ShowMessageBox( _T("当前预案已存在，是否覆盖！"), true );
            if ( IDOK != nResult )
            {
                return false;
            }
        }
        ComInterface->SaveMatrixScenceCmd(dwIndex,achName);
    }
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
        CListLabelElementUI* pListLabelElementUI = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
        if (pListLabelElementUI)
        {
            dwIndex = pListLabelElementUI->GetnTag();
        }
    }
    //获取名称
    CString strName = (ICncCommonOp::GetControlText(m_pm,_T("EditReNamePreplanName"))).c_str();
    s8 achName[TP_MATRIX_SCENENAME_LEN + 1] = {0};
    memcpy(achName,CT2A(strName),sizeof(CT2A(strName)));

    ComInterface->ReNameMatrixScenceCmd(dwIndex,achName);
    m_pm->DoCase(_T("caseShowEditPreplan"));
    return true;
}

bool CMatrixLogic::OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    m_pm->DoCase(_T("caseShowMatrix"));
    return true;
}

bool CMatrixLogic::OnMatrixConFigNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPMatrixConfig tTPMatrixConfig;
    ComInterface->GetMatrixConfig(tTPMatrixConfig);

    if (tTPMatrixConfig.m_bOpenUI && ComInterface->GetMatrixOnlineState())
    {
        ICncCommonOp::ShowControl(true,m_pm,_T("Matrix"));
        ICncCommonOp::ShowControl(true,m_pm,_T("Matrixlayout"));
        ICncCommonOp::ShowControl(true,m_pm,_T("ctlMatrix"));
    }
    else
    {
        //不可用时 隐藏此tab 2015-7-8
        ICncCommonOp::ShowControl(false,m_pm,_T("Matrix"));
        ICncCommonOp::ShowControl(false,m_pm,_T("Matrixlayout"));
        ICncCommonOp::ShowControl(false,m_pm,_T("ctlMatrix"));
        //选中第一项
        COptionUI *pOpMatrix = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Matrix"));
        if (pOpMatrix && pOpMatrix->IsSelected())
        {
            COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
            if (pOp)
            {
                pOp->Selected(true);
            }
        }
    }
    return true;
}

bool CMatrixLogic::OnMatrixSceneInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    //清理界面
    TTPCurMatrixInfo tTPCurMatrixInfo;
    UpdateMatrixTip(tTPCurMatrixInfo, emManager);
    UpdateMatrixInfo(tTPCurMatrixInfo, emManager);

    //更新数据
    TTPMatrixSceneInfo  atMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );

    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSelPreplanNo") );
    if (pComboEx)
    {
        int nFriseUsed = -1;
        for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
        {
            CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)pComboEx->GetItemAt(i);
            if (pListLabelElement)
            {
                CDuiString strtmp = _T("");
                if (atMatrixSceneInfo[i].bUsed == FALSE)
                {
                    strtmp.Format(_T("预案%d:空"),i+1);
                }
                else
                {
                    if (nFriseUsed == -1)
                    {
                        nFriseUsed = i;
                    }
                    strtmp.Format(_T("预案%d:%s"),i+1,CA2T(atMatrixSceneInfo[i].achSceneName));
                }
                pListLabelElement->SetText(strtmp);
                pListLabelElement->SetnTag(i);
            }
        }
        if (pComboEx->GetCurSel() != -1)
        {
            TNotifyUI msg;
            OnSelPreplanSelectChange(msg);
        }
        else
        {
            if (pComboEx->GetCount() > nFriseUsed && nFriseUsed != -1)
            {
                pComboEx->SelectItem(nFriseUsed);
            }
            else
            {
                pComboEx->SelectItem(0);
            }
        }
    }

    //校验匹配
    TTPCurMatrixInfo tTPCurMatrixManageInfo;
    ComInterface->GetCurMatrixInfo(tTPCurMatrixManageInfo);
    CDuiString strName = _T("");
    for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
    {
        if (memcmp( tTPCurMatrixManageInfo.m_achMatrixInOutRelation , atMatrixSceneInfo[i].m_achMatrixInOutRelation , sizeof(s32) * MT_MAX_MATRIX_CHANNEL_LEN) == 0)
        {
            strName.Format(_T("预案%d:%s"),i+1,CA2T(atMatrixSceneInfo[i].achSceneName));
            break;
        }
    }
    ICncCommonOp::SetControlText(strName,m_pm,_T("ConfRoomName"));
    return true;
}

bool CMatrixLogic::OnCurMatrixInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bIsNty = (BOOL)wParam;
    TTPCurMatrixInfo tTPCurMatrixInfo;
    ComInterface->GetCurMatrixInfo(tTPCurMatrixInfo);
    if (bIsNty)
    {
        UpdateMatrixTip(tTPCurMatrixInfo, emOperation);
    }
    UpdateMatrixInfo(tTPCurMatrixInfo, emOperation);
    //更新数据
    TTPMatrixSceneInfo  atMatrixSceneInfo[TP_MATRIX_SCENENUM_MAX];
    memcpy( atMatrixSceneInfo , ComInterface->GetMatrixScneInfo(), sizeof(TTPMatrixSceneInfo) * TP_MATRIX_SCENENUM_MAX );
    CDuiString strName = _T("");
    for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++ )
    {
        if (memcmp( tTPCurMatrixInfo.m_achMatrixInOutRelation , atMatrixSceneInfo[i].m_achMatrixInOutRelation , sizeof(s32) * MT_MAX_MATRIX_CHANNEL_LEN) == 0)
        {
            strName.Format(_T("预案%d:%s"),i+1,CA2T(atMatrixSceneInfo[i].achSceneName));
            break;
        }
    }
    ICncCommonOp::SetControlText(strName,m_pm,_T("ConfRoomName"));
    return true;
}

bool CMatrixLogic::OnSaveMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (bSuccess == FALSE)
    {
        ShowPopMsg(_T("矩阵预案保存失败"));
    }
    else
    {
        m_pm->DoCase(_T("caseShowMatrix"));
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
