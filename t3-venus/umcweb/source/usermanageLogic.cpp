// CUserManageLogic.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "usermanageLogic.h"
#include "mainLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManageLogic dialog
CMainLogic* g_cmainWnd;

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

CUserManageLogic::CUserManageLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CUserManageLogic::IDD, pParent),
	m_pUserctrlIF(NULL)
{
	//{{AFX_DATA_INIT(CUserManageLogic)
	//}}AFX_DATA_INIT

	m_bIsAllSel = FALSE;
	//m_bShowMosaicHoriImg = FALSE;
	m_bJumpFlag = FALSE;

	m_plsUser = NULL;
	m_pLetterIndex = NULL;

	m_bShowMosaicHoriImg = TRUE;
	m_bIsSegment = TRUE;
	m_nSegmentLen = 708*CUR_SCREEN_WIDTH_PER;
}

void CUserManageLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManageLogic)
	DDX_Control(pDX, IDC_STATIC_CHILDFRMRIGHT, m_stChildBkRight);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMLEFT, m_stChildBkLeft);
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stUserLeftTitle);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_stUserRightTitle);
	DDX_Control(pDX, IDC_STATIC_Name, m_stUserName);
	DDX_Control(pDX, IDC_STATIC_PassWord, m_stPassword);
	DDX_Control(pDX, IDC_EDIT_UserName, m_etUserName);
	DDX_Control(pDX, IDC_EDIT_Pwd, m_etPassword);
	DDX_Control(pDX, IDC_Btn_Save, m_btnSave);
	DDX_Control(pDX, IDC_Btn_Cancel, m_btnCancel);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_EDIT_Ex, m_etSearch);
	DDX_Control(pDX, IDC_Btn_NewUser, m_btnNewUser);
	DDX_Control(pDX, IDC_BtnDelete, m_btnDelete);
	DDX_Control(pDX, IDC_BtnAllSelect, m_btnAllSel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUserManageLogic, CDlgChild)
	//{{AFX_MSG_MAP(CUserManageLogic)
	ON_BN_CLICKED(IDC_Btn_Save, OnBtnSave)
	ON_BN_CLICKED(IDC_Btn_Cancel, OnBtnCancel)
	ON_BN_CLICKED(IDC_BtnDelete, OnBtnDelete)
	ON_BN_CLICKED(IDC_BtnAllSelect, OnBtnAllSelect)
	ON_BN_CLICKED(IDC_Btn_NewUser, OnBtnNewUser)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_MESSAGE( UI_UMS_REFRESH_USER_LIST,  OnRefreshUserList )
 	ON_MESSAGE( UI_UMS_OPERATE_USER_RET,  OnUserOperateResultNotify )
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM,  OnNoSelResultNotify )
	//ON_MESSAGE( WM_EDIT_ONCHAR, OnSearchEditChange )
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManageLogic message handlers
void CUserManageLogic::RegisterFun()
{
	REG_MSG_HANDLER( "CUserManageLogic::OnClickLstItem", CUserManageLogic::OnClickLstItem, this,CUserManageLogic );	
	REG_MSG_HANDLER( "CUserManageLogic::OnClickLstItemIcon", CUserManageLogic::OnClickLstItemIcon, this,CUserManageLogic );
}

BOOL CUserManageLogic::InitControlPane()
{
	m_btnSave.SetImage( IDR_PNG_BTN_SAVE, IDR_PNG_BTN_SAVEDOWN, IDR_PNG_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_BTN_CANCEL, IDR_PNG_BTN_CANCELDOWN, IDR_PNG_BTN_CANCEL );
	m_btnEdit.SetImage( IDR_PNG_BTN_EDIT, IDR_PNG_BTN_EDITDOWN, IDR_PNG_BTN_EDIT );

	m_btnNewUser.SetImage( IDR_PNG_USERWND_BTN_NEWUSER, IDR_PNG_USERWND_BTN_NEWUSERDOWN, IDR_PNG_USERWND_BTN_NEWUSERDIS );
	m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
	m_btnDelete.SetImage( IDR_PNG_BTN_DELETE, IDR_PNG_BTN_DELETEDOWN, IDR_PNG_BTN_DELETEDIS );
	
	CUmcwebCommon::SetTextTransStatic( &m_stUserLeftTitle, "用户管理" , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stUserRightTitle, "用户信息" , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stUserName, "用户名" );
	CUmcwebCommon::SetTextTransStatic( &m_stPassword, "密码" );

	m_etUserName.SetLimitLength(31);
	m_etPassword.SetLimitLength(31);

	CUmcwebCommon::SetImgForTransEdit(&m_etUserName);
	CUmcwebCommon::SetImgForTransEdit(&m_etPassword);
	CUmcwebCommon::SetImgForTransSearchEdit(&m_etSearch);

	//用户列表加入
	m_plsUser = new CListChild( "", CRect(12, 100, 732 - 62+12, 485+100), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_plsUser )
	{
		m_plsUser->SetWindowPos( NULL, 12, 100, 732 - 62, 485, SWP_SHOWWINDOW );
		m_plsUser->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
				IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsUser->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsUser->SetSliderAlwaysShow( TRUE );

		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect( 0, 0, 39, 486 ), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterIndex != NULL )
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
			m_pLetterIndex->SetBindList( m_plsUser );
		}
	}
	
	m_emCurOperateFlag = em_SCANF_STATUS;
	return TRUE;
}

void CUserManageLogic::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stUserLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stUserRightTitle.SetWindowPos( NULL, 720*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_btnCancel.SetWindowPos( NULL, (1226 - 8 - m_btnCancel.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnCancel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCancel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnEdit.SetWindowPos( NULL,  (1226 - 8 - m_btnEdit.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnEdit.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnSave.SetWindowPos( NULL, rectClient.left - (8 + m_btnSave.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnSave.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	if ( NULL != m_plsUser )
	{
		m_plsUser->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (708 - 62)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsUser->GetWindowRect(&rectClient);
		ScreenToClient( &rectClient );
		if ( m_pLetterIndex != NULL )
		{
			rectClient.left = rectClient.right - 3;
			rectClient.right = rectClient.left + 7;
			m_plsUser->SetSliderRect( rectClient );

			m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );
		}
	}

	m_plsUser->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	
	m_btnDelete.SetWindowPos( NULL, rectClient.right - m_btnDelete.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnDelete.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDelete.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnDelete.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnAllSel.SetWindowPos( NULL, rectClient.right - 2*m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnAllSel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
	m_btnNewUser.SetWindowPos( NULL, rectClient.right - 3*m_btnNewUser.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 2*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnNewUser.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnNewUser.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_btnNewUser.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_etSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  rectClient.right - 
		m_btnNewUser.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	this->GetClientRect(&rectClient);
	m_stUserName.SetWindowPos( NULL, (708 + 18)*CUR_SCREEN_WIDTH_PER,  77*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stPassword.SetWindowPos( NULL, (708 + 18)*CUR_SCREEN_WIDTH_PER, (77 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_etUserName.SetWindowPos( NULL, (1226 - 391)*CUR_SCREEN_WIDTH_PER , 64*CUR_SCREEN_HEIGHT_PER,  (391 - 10)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etPassword.SetWindowPos( NULL, (1226 - 391)*CUR_SCREEN_WIDTH_PER , (64 + 41 + 9)*CUR_SCREEN_HEIGHT_PER,  (391 - 10)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
}

BOOL CUserManageLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	g_cmainWnd = (CMainLogic*)GetParent();

	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	SetControlPos();             //设置页面控件位置

	if( m_pUserctrlIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pUserctrlIF);
	}
	
	if( m_pUserctrlIF != NULL )
	{
		m_pUserctrlIF->SetNotifyWnd( this->m_hWnd );
	} 

	return TRUE;
}

void CUserManageLogic::OnBtnNewUser() 
{
	m_emCurOperateFlag = em_NEW_STATUS;
	m_stUserRightTitle.SetWindowText("编辑用户信息");

	CString strSearch;
	m_etSearch.GetWindowText(strSearch);
	if ( !strSearch.IsEmpty() )
	{
		m_plsUser->SetSelItem(-1);
		m_selUser.Empty();
		ResetInitPage();
		m_etSearch.SetWindowText("");
	}

	UpdateShowList();
	UpdateUIState();

	m_btnAllSel.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);
	m_etSearch.EnableWindow(FALSE);

	ShowControlNewPage();
}

void CUserManageLogic::OnBtnEdit() 
{	
	m_emCurOperateFlag = em_EDIT_STATUS;
	m_stUserRightTitle.SetWindowText("编辑用户信息");
	
	CString strUserName;
	strUserName = m_selUser.GetName();

	if ( strUserName.IsEmpty() )
	{
		return;
	}
	
	m_etUserName.SetWindowText(strUserName);
	m_etPassword.SetWindowText("");//******

	CString strSearch;
	m_etSearch.GetWindowText(strSearch);
	if ( !strSearch.IsEmpty() )
	{
		m_etSearch.SetWindowText("");
		JumpToSelLine();
	}

	UpdateShowList();
	UpdateUIState();

	m_btnAllSel.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);
	m_etSearch.EnableWindow(FALSE);

	ShowControlEditPage();
}

void CUserManageLogic::OnBtnSave() 
{
	CUserFullInfo tUserInfo;

	CString strName;
	CString strPswd;
	m_etUserName.GetWindowText(strName);
	m_etPassword.GetWindowText(strPswd);
	
	CString strError;
	int nRet = 0;
	if ( strName.IsEmpty() )
	{
		strError = "用户名为空,保存失败!";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	
	if ( strName.GetLength() > 31 )
	{
		strError = "用户名大于最长的31字符,保存失败!";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	
	if ( strPswd.IsEmpty() )
	{
		strError = "密码为空,保存失败!";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	
	if ( strPswd.GetLength() > 31 )
	{
		strError = "密码大于最长的31字符,保存失败!";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	
	strncpy( tUserInfo.name, strName, strName.GetLength() );

	const s8* cpPassword = LPCTSTR(strPswd);
	tUserInfo.SetPassword((s8*)cpPassword);
	
	if( m_emCurOperateFlag == em_EDIT_STATUS )
	{
		if( m_pUserctrlIF->ModifyUserReq(tUserInfo) != 0 )
		{
			MESSAGEWND( "修改用户请求失败"  );
		}
		m_bJumpFlag = TRUE;
	}
	else
	{
		if( m_pUserctrlIF->AddUserReq(tUserInfo) != 0 )
		{
			MESSAGEWND( "添加用户请求失败" );
		}
		m_bJumpFlag = TRUE;
	}

	m_emCurOperateFlag = em_SCANF_STATUS;  //保存后页面状态置为浏览
}

void CUserManageLogic::OnBtnCancel() 
{
	m_emCurOperateFlag = em_SCANF_STATUS;
	m_stUserRightTitle.SetWindowText("用户信息");	
	m_btnNewUser.EnableWindow(TRUE);

	CString strSelUserName = m_selUser.GetName();
	if( strSelUserName.IsEmpty() )
	{
		HideAllPageCtrl();
	}
	else
	{
		ShowControlScanfPage();
		m_etUserName.SetWindowText(m_selUser.GetName());
		m_etPassword.SetWindowText(m_selUser.GetPassword());
	}

	UpdateUIState();
	m_etSearch.EnableWindow(TRUE);
}

void CUserManageLogic::OnBtnDelete() 
{
	m_emCurOperateFlag = em_DELETE_STATUS;

	s32 nRet = 0;
	MESSAGEWNDBOX( "是否删除所选用户信息", this , nRet , TRUE );
	if( nRet == IDOK )
	{
		for ( std::set<CString>::iterator iter = m_setSelectedIconItem.begin(); iter != m_setSelectedIconItem.end(); iter++ )
		{
			LPCTSTR strCurItemName = *iter;
			
			CUserFullInfo cuserInfo;
			strncpy( cuserInfo.name, strCurItemName, strlen(strCurItemName) );
			
			if( m_pUserctrlIF->DeleteUserReq(cuserInfo) != 0 )
			{
				MESSAGEWND( "删除用户请求失败!");
			}
		}

		m_etUserName.SetWindowText("");
		m_etPassword.SetWindowText("");

		m_bJumpFlag = TRUE;
	}
}

bool CUserManageLogic::OnClickLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();        
        if ( const Data_User *pItemInfo = dynamic_cast<const Data_User*>( pBaseItem->GetUserData() )) 
        {   
			m_selUser = pItemInfo->m_cUser;

			CUserFullInfo cuserInfo = pItemInfo->m_cUser;

			CString strUserName;
			strUserName = cuserInfo.GetName();
			if ( strUserName.IsEmpty() )
			{
				return false;
			}

			CString strUserPswd;
			strUserPswd = cuserInfo.GetPassword();

			ShowControlScanfPage();	
			m_etUserName.SetWindowText(strUserName);
			m_etPassword.SetWindowText(strUserPswd);
        } 
    }

	return true;
}

bool CUserManageLogic::OnClickLstItemIcon( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_User *pItemInfo = dynamic_cast<const Data_User*>( pBaseItem->GetUserData() )) 
        {   
			m_selUser.Empty();  //清空当前选择
			ResetInitPage();    //清空右侧显示页面
				
			CUserFullInfo cuserInfo = pItemInfo->m_cUser;
			CString strUserName;
			strUserName = cuserInfo.GetName();

			s32 nPreClickedItemCount = m_setSelectedIconItem.size();
			m_setSelectedIconItem.insert(strUserName);
			s32 nLastClickedItemCount = m_setSelectedIconItem.size();
			
			if ( nPreClickedItemCount == nLastClickedItemCount )
			{
				m_setSelectedIconItem.erase(strUserName);
			}
			
			UpdateShowList();
			UpdateUIState();	
        } 
    }

    return true;
}

void CUserManageLogic::OnBtnAllSelect() 
{
	m_setSelectedIconItem.clear();

	m_bIsAllSel = !m_bIsAllSel;

	if ( m_bIsAllSel )
	{
		for(s32 nIndex = 0; nIndex < m_tplShowList.Size(); nIndex++ )
		{	
			CString strUserName;
			CUserFullInfo tUserInfo;
			tUserInfo = m_tplShowList.GetAt(nIndex);
			strUserName = tUserInfo.GetName();
			if( strUserName.IsEmpty() || strUserName == "admin")
			{
				continue;
			}

			m_setSelectedIconItem.insert(tUserInfo.GetName());
 		}

		UpdateShowList();
		UpdateUIState();
	}
	else
	{
		m_setSelectedIconItem.clear();
		UpdateShowList();
		UpdateUIState();
	}
}

LRESULT CUserManageLogic::OnRefreshUserList(WPARAM wParam, LPARAM lParam)
{
	UserListRefresh();

	if ( m_bJumpFlag )
	{
		CUserFullInfo* pCUserInfo = (CUserFullInfo*)wParam;
		if ( NULL == pCUserInfo )
		{
			m_bJumpFlag = FALSE;
			return 0L;
		}

		m_selUser = *pCUserInfo;

		JumpToSelLine();

		m_bJumpFlag = FALSE;
	}
	
	return 0L;
}

void CUserManageLogic::UserListRefresh()
{
	m_tpRefreshList.Clear();
	if ( NULL != m_pUserctrlIF )
	{
		m_pUserctrlIF->GetUserList(m_tpRefreshList);
		
		OnSearchEditChange();
		UpdateShowList();
		UpdateUIState();
	}
}

LRESULT CUserManageLogic::OnUserOperateResultNotify(WPARAM wParam, LPARAM lParam)
{
	if ( lParam != NO_ERROR )
    {        
        CString strErr = "";
        switch(lParam)
        {
        case UM_LOGIN_NOUSER:
			{
			    strErr = "该用户不存在";
			}
            break;
        case UM_LOGIN_ERRPSW:
			{
			    strErr = "用户名中不可以含有空格" ;
			}
            break;
        case UM_ACTOR_NOTMATCH:
			{
		        strErr = "用户权限不匹配";
			}
            break;
        case UM_USER_DUPLICATE:
			{
			    strErr = "该用户名已存在";
			}
            break;
        case UM_USER_NOTEXIST:
			{
				strErr = "该用户不存在";
			}
            break;
        case UM_NOT_ENOUGHMEM:
			{
				strErr = "用户个数已达到最大值";
			}
            break;		
        case UM_OPERATE_NOTPERMIT:
			{
				strErr = "无操作权限";
			}
			break;
        default:
			{
				 strErr = ""; //"未知错误";2012-8-7 SE石文娟确认未知错误不做提示 by yjj
			}
			break; 			
        }
		
        CString strMsg;
        if ( strErr.IsEmpty() )
        {
            strMsg = "操作用户失败";
            
        }
        else
        {
            strMsg = "操作用户失败: " + strErr;
        }
		
		MESSAGEWND( strMsg  );
    }
	else
	{
		if( m_emCurOperateFlag == em_NEW_STATUS )
		{
			//MESSAGEWND( "用户添加成功" );  //ldy 120926  需求确认  操作成功不提醒
		}
		else if( m_emCurOperateFlag == em_EDIT_STATUS )
		{
			//MESSAGEWND( "用户修改成功" );
		}
		else if( m_emCurOperateFlag == em_DELETE_STATUS )
		{
			//MESSAGEWND( "用户删除成功" );
			m_setSelectedIconItem.clear();
		}

		//用户操作成功刷新列表并重新置控件为初始页
		UserListRefresh();

		m_selUser.Empty();
		ResetInitPage();
	}

    return NO_ERROR;
}

void CUserManageLogic::ResetInitPage()
{
	m_stUserRightTitle.SetWindowText("用户信息");
	 
	HideAllPageCtrl();

	m_btnSave.ShowWindow(SW_HIDE);
	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_HIDE);

	m_btnNewUser.EnableWindow(TRUE);

	m_etUserName.SetWindowText(_T(""));
	m_etPassword.SetWindowText(_T(""));
	m_etSearch.EnableWindow(TRUE);

	if ( NULL != m_plsUser )
	{
		m_plsUser->SetSelItem( -1 );
	}
}

LRESULT CUserManageLogic::OnNoSelResultNotify(WPARAM wParam, LPARAM lParam)
{
	m_selUser.Empty();
	ResetInitPage();
	return 0L;
}

void CUserManageLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	m_tpRefreshList.Clear();
	m_tplShowList.Clear();
	m_tpSearchList.Clear();
	
	SAFE_RELEASE(m_plsUser);
	SAFE_RELEASE(m_pLetterIndex);

	UN_REG_MSG_HANDLER( "CUserManageLogic::OnClickLstItem" );	
	UN_REG_MSG_HANDLER( "CUserManageLogic::OnClickLstItemIcon" );
}

void CUserManageLogic::InitDlg()
{
	m_emCurOperateFlag = em_SCANF_STATUS;
	m_etSearch.SetWindowText("");
	ShowWindow(SW_HIDE);

	if ( NULL != m_plsUser )
	{
		m_plsUser->SetYOffset( 0 ); 
		m_plsUser->SetSelItem( -1 );
	}

    m_setSelectedIconItem.clear();   //选中用户的ITEM集合
	m_selUser.Empty();    		//清空当前选择用户数据
	ResetInitPage();

	UserListRefresh();
}

void CUserManageLogic::ShowControlNewPage()
{
	if ( m_plsUser != NULL )
	{
		m_plsUser->EnableWindow(FALSE);
		m_pLetterIndex->EnableWindow(FALSE);
	}

	m_btnAllSel.EnableWindow(FALSE); //新建禁止全选和删除   取消根据UpdateUIState判断
	m_btnDelete.EnableWindow(FALSE);
	m_btnNewUser.EnableWindow(FALSE);

	m_stUserName.ShowWindow(SW_SHOW);
	m_stPassword.ShowWindow(SW_SHOW);

	m_etUserName.ShowWindow(SW_SHOW);
	m_etPassword.ShowWindow(SW_SHOW);

	m_etUserName.EnableWindow(TRUE);
	m_etPassword.EnableWindow(TRUE);
	m_etUserName.SetWindowText(_T(""));
	m_etPassword.SetWindowText(_T(""));

	m_btnSave.ShowWindow(SW_SHOW);
	m_btnCancel.ShowWindow(SW_SHOW);
	m_btnEdit.ShowWindow(SW_HIDE);

	m_etUserName.SetFocus();
}

void CUserManageLogic::ShowControlScanfPage()
{
	if ( m_plsUser != NULL )
	{
		m_plsUser->EnableWindow(TRUE);	
		m_pLetterIndex->EnableWindow(TRUE);
	}

	m_btnSave.ShowWindow(SW_HIDE);
	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_SHOW);
	
	m_stUserName.ShowWindow(SW_SHOW);
	m_stPassword.ShowWindow(SW_SHOW);
	m_etUserName.ShowWindow(SW_SHOW);
	m_etPassword.ShowWindow(SW_SHOW);
	
	m_etUserName.EnableWindow(FALSE);
	m_etPassword.EnableWindow(FALSE);
}

void CUserManageLogic::ShowControlEditPage()
{
	if ( m_plsUser != NULL )
	{
		m_plsUser->EnableWindow(FALSE);	
		m_pLetterIndex->EnableWindow(FALSE);
	}

	m_stUserName.ShowWindow(SW_SHOW);
	m_stPassword.ShowWindow(SW_SHOW);
	m_etUserName.ShowWindow(SW_SHOW);
	m_etPassword.ShowWindow(SW_SHOW);
	
	m_etUserName.EnableWindow(FALSE);
	m_etPassword.EnableWindow(TRUE);
	
	m_btnSave.ShowWindow(SW_SHOW);
	m_btnCancel.ShowWindow(SW_SHOW);
	m_btnEdit.ShowWindow(SW_HIDE);
	
	m_btnNewUser.EnableWindow(FALSE);
}

void CUserManageLogic::HideAllPageCtrl()
{
	if ( m_plsUser != NULL )
	{
		m_plsUser->EnableWindow(TRUE);	
		m_pLetterIndex->EnableWindow(TRUE);
	}

	m_stUserName.ShowWindow(SW_HIDE);
	m_stPassword.ShowWindow(SW_HIDE);
	m_etUserName.ShowWindow(SW_HIDE);
	m_etPassword.ShowWindow(SW_HIDE);
	m_etUserName.SetWindowText(_T(""));
	m_etPassword.SetWindowText(_T(""));
	
	m_btnSave.ShowWindow(SW_HIDE);
	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_HIDE);

	//m_etUserName.SetFocus();
 
}

void CUserManageLogic::JumpToSelLine()
{
	CString strUserName;
	strUserName = m_selUser.GetName();	
	if ( strUserName.IsEmpty() )
	{
		return;
	}

	CString strUserPswd;
	strUserPswd = m_selUser.GetPassword();		
	ShowControlScanfPage();	
	m_etUserName.SetWindowText(strUserName);
	m_etPassword.SetWindowText(strUserPswd);

	//设置列表选中项
	BOOL bIsMatch = FALSE;
	for ( s32 nIndex = 0; nIndex < m_vecShowList.size(); nIndex++ )
	{
		if ( m_vecShowList.at(nIndex).IsEqualName( m_selUser.name ) )
		{
			if ( m_plsUser != NULL )
			{
				m_plsUser->SetSelItem( nIndex );
				bIsMatch = TRUE;
			}
			break;
		}
	}

	if( !bIsMatch )
	{
		m_selUser.Empty();
		m_plsUser->SetSelItem( -1 );
		ResetInitPage();
	}
}

void CUserManageLogic::OnSearchEditChange()
{
	m_setSelectedIconItem.clear();
	
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if ( strSearchName.IsEmpty() )
	{
		UpdateShowList();
		UpdateUIState();

		if ( m_emCurOperateFlag == em_SCANF_STATUS )
		{
			JumpToSelLine();
		}
	}
	else
	{
		m_tpSearchList.Clear();
		TplArray<CUserFullInfo> tpShowList;
		tpShowList = m_tpRefreshList;
		
		for ( s32 nIndex = 0; nIndex < tpShowList.Size(); nIndex++ )
		{
			CString strItemName;
			CUserFullInfo tAddrItem = tpShowList.GetAt(nIndex);
			strItemName = tAddrItem.GetName();
			
			BOOL bFind = FALSE;			
			bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
			if ( bFind )
			{		
				m_tpSearchList.Add( &tAddrItem );
			}
		}
		
		UpdateShowList();
		UpdateUIState();
		
		if ( m_emCurOperateFlag == em_SCANF_STATUS )
		{
			JumpToSelLine();
		}
		
		if ( NULL != m_plsUser )
		{
			m_plsUser->SetYOffset( 0 );
		}
	}
}

void CUserManageLogic::UpdateShowList()
{
	CString strText;
	m_etSearch.GetWindowText( strText );
	m_tplShowList.Clear();
	if ( strText.IsEmpty() )
	{
		m_tplShowList = m_tpRefreshList;
	}
	else
	{
		m_tplShowList = m_tpSearchList;
	}

	s32 nCount = m_tplShowList.Size();
	m_vecShowList.clear();

    for ( s32 nIndexPos = 0; nIndexPos < nCount; nIndexPos++ )
    {
		CString strUserName = m_tplShowList.GetAt(nIndexPos).GetName();
		if( strUserName.IsEmpty() || strUserName == "admin")
		{
			continue;
		}

        m_vecShowList.push_back( m_tplShowList.GetAt(nIndexPos) );
    }
    
	sort( m_vecShowList.begin(), m_vecShowList.end(), CListChild::UserItemCompare );

	Value_TouchListUser val_UserList( &m_vecShowList, "CUserManageLogic::OnClickLstItem", NULL );
	val_UserList.m_setClickedName = m_setSelectedIconItem;
	if( m_plsUser != NULL )
	{
		m_plsUser->SetData( val_UserList );	
	}
}

void CUserManageLogic::UpdateUIState()
{
	s32 nSelSize = m_setSelectedIconItem.size();
	if ( nSelSize > 0 )
	{
		m_btnDelete.EnableWindow(TRUE);
		
		if ( nSelSize == m_vecShowList.size() )
		{
			m_bIsAllSel = TRUE;
			m_btnAllSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
		}
		else
		{
			m_bIsAllSel = FALSE;
			m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
		}
	}
	else
	{
		m_btnDelete.EnableWindow(FALSE);
		
		m_bIsAllSel = FALSE;
		m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
		m_btnAllSel.EnableWindow(FALSE);
	}
	
	if ( m_vecShowList.size() == 0 )
	{
		m_btnAllSel.EnableWindow(FALSE);
	}
	else
	{
		m_btnAllSel.EnableWindow(TRUE);
	}
}

BOOL CUserManageLogic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( HIWORD(wParam) == EN_CHANGE )
	{
		if ( (HWND)lParam == m_etSearch.GetSafeHwnd() )
		{ 
			OnSearchEditChange();

			CString strSearchName;
			m_etSearch.GetWindowText( strSearchName );
			if ( !strSearchName.IsEmpty() )
			{
				m_plsUser->SetYOffset( 0 );
			}
		}		
	}
	
	return CDlgChild::OnCommand(wParam, lParam);
}