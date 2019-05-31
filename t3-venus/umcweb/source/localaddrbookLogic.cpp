// LocalAddr.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "localaddrbookLogic.h"
#include "localaddrbookgroupEdit.h"
#include "localaddrbookmeetEdit.h"
#include "PubFunc.h"
#include "HZPYSearch.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainLogic* g_cmainWnd;

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookLogic dialog
CLocalAddrbookLogic::CLocalAddrbookLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CLocalAddrbookLogic::IDD, pParent)
	,m_pCncAddrBook(NULL)
{
	//{{AFX_DATA_INIT(CLocalAddrbookLogic)
	m_strDir = _T("");
	//}}AFX_DATA_INIT	

	m_bShowMosaicHoriImg = TRUE;

	m_bWaitAdd = FALSE;
}


void CLocalAddrbookLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalAddrbookLogic)
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stLeftTitle);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BTN_CUT, m_btnCut);
	DDX_Control(pDX, IDC_BTN_COPY, m_btnCopy);
	DDX_Control(pDX, IDC_BTN_PASTE, m_btnPaste);
	DDX_Control(pDX, IDC_BTN_REVOKE, m_btnRevoke);
	DDX_Control(pDX, IDC_BTN_NEW_MEETING, m_btnNewMeet);
	DDX_Control(pDX, IDC_BTN_NEW_GRP, m_btnNewGroup);
	DDX_Control(pDX, IDC_BTN_RETURN, m_btnReturn);
	DDX_Control(pDX, IDC_EDIT_FIND, m_etAddrSearch);
	DDX_Text(pDX, IDC_STATIC_DIR, m_strDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLocalAddrbookLogic, CDlgChild)
	//{{AFX_MSG_MAP(CLocalAddrbookLogic)
	ON_BN_CLICKED(IDC_BTN_NEW_GRP, OnBtnNewGrp)
	ON_BN_CLICKED(IDC_BTN_NEW_MEETING, OnBtnNewMeeting)
	ON_BN_CLICKED(IDC_BTN_RETURN, OnBtnReturn)
	ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
	ON_BN_CLICKED(IDC_BTN_CUT, OnBtnCut)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_PASTE, OnBtnPaste)
	ON_BN_CLICKED(IDC_BTN_REVOKE, OnBtnRevoke)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(UI_CNS_ADDRBOOK_CHANGED,OnInitAddrBook)  //地址簿初始化
	ON_MESSAGE(UI_CNS_ADDRBOOK_ADDENTRY,OnAddEntry)
	ON_MESSAGE(UI_CNS_ADDRBOOK_ADDGROUP,OnAddGroup)
	ON_MESSAGE(UI_CNS_ADDRBOOK_MODIFY,OnAddrModifyNty)	
    ON_MESSAGE(UI_CNS_ADDRBOOKOPT_FAILED,OnAddrOptFailed)
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM, OnUnSelAddrList )
	ON_MESSAGE( WM_EDIT_CHANGED, OnSearchEditChange )	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookLogic message handlers

BOOL CLocalAddrbookLogic::InitControlPane()
{
	REG_MSG_HANDLER( "CLocalAddrbookLogic::OnClickLstItem", CLocalAddrbookLogic::OnClickLstItem, this,CLocalAddrbookLogic );	
	REG_MSG_HANDLER( "CLocalAddrbookLogic::OnClickLstItemIcon", CLocalAddrbookLogic::OnClickLstItemIcon, this,CLocalAddrbookLogic );	

	//初始化界面控件图片控件
	CUmcwebCommon::SetImgForTransSearchEdit(&m_etAddrSearch);

	m_btnReturn.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnNewMeet.SetImage( IDR_PNG_BTN_NEWMEET, IDR_PNG_BTN_NEWMEETDOWN, IDR_PNG_BTN_NEWMEET );
	m_btnNewGroup.SetImage( IDR_PNG_BTN_NEWGROUP, IDR_PNG_BTN_NEWGROUPDOWN, IDR_PNG_BTN_NEWGROUP );
	m_btnCut.SetImage( IDR_PNG_BTN_CUT, IDR_PNG_BTN_CUTDOWN, IDR_PNG_BTN_CUTDIS );
	m_btnCopy.SetImage( IDR_PNG_BTN_COPY, IDR_PNG_BTN_COPYDOWN, IDR_PNG_BTN_COPYDIS );
	m_btnEdit.SetImage( IDR_PNG_BTN_EDIT, IDR_PNG_BTN_EDITDOWN, IDR_PNG_BTN_EDITDIS );
	m_btnDelete.SetImage( IDR_PNG_BTN_DELETE, IDR_PNG_BTN_DELETEDOWN, IDR_PNG_BTN_DELETEDIS );
	m_btnPaste.SetImage( IDR_PNG_BTN_PASTE, IDR_PNG_BTN_PASTEDOWN, 0 );
	m_btnRevoke.SetImage( IDR_PNG_BTN_LOCALADDRCANCEL, IDR_PNG_BTN_CANCELDOWN, 0 );

	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stLeftTitle.SetWindowText("本地地址簿");
	m_stLeftTitle.SetTextAlign(StringAlignmentNear);
	m_stLeftTitle.SetTextColor(Color( 24, 25, 27 ));
	m_stLeftTitle.SetFont( 14, "微软雅黑" );

	m_btnReturn.SetWindowPos( &wndTop, 13*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, m_btnReturn.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnReturn.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_HIDEWINDOW );


	//本地地址簿列表加入
	m_plsLocalAddr = new CListChild( "", 0, this, "", 0, WS_CHILD );
	if ( NULL != m_plsLocalAddr )
	{
		m_plsLocalAddr->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (1226 - 62)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsLocalAddr->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_plsLocalAddr->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsLocalAddr->SetSliderAlwaysShow( TRUE );
	}

	m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
	CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
	m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
	m_pLetterIndex->SetBindList( m_plsLocalAddr );
	m_plsLocalAddr->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

    rectClient.left = rectClient.right - 3;
    rectClient.right = rectClient.left + 7;
    m_plsLocalAddr->SetSliderRect( rectClient );

	m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );	

	m_plsLocalAddr->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

	m_btnDelete.SetWindowPos( &wndTop, rectClient.right - m_btnDelete.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnDelete.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDelete.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
	m_btnDelete.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnEdit.SetWindowPos( &wndTop, rectClient.right - 2*m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnEdit.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
	
	m_btnCut.SetWindowPos( &wndTop, rectClient.right - 3*m_btnCut.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 2*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnCut.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCut.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
	m_btnRevoke.SetWindowPos( &wndTop, rectClient.right - 3*m_btnCut.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 2*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnCut.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCut.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_HIDEWINDOW );
 
	m_btnCopy.SetWindowPos( &wndTop, rectClient.right - 4*m_btnCopy.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 3*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnCopy.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCopy.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
	m_btnPaste.SetWindowPos( &wndTop, rectClient.right - 4*m_btnCopy.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 3*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnCopy.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCopy.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_HIDEWINDOW );

	m_btnCopy.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnNewGroup.SetWindowPos( &wndTop, rectClient.right - m_btnCopy.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - m_btnNewGroup.GetImageSize().cx*CUR_SCREEN_WIDTH_PER -
		10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnNewGroup.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnNewGroup.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );

	m_btnNewGroup.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnNewMeet.SetWindowPos( &wndTop, rectClient.right - m_btnNewMeet.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - m_btnNewGroup.GetImageSize().cx*CUR_SCREEN_WIDTH_PER -
		10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnNewMeet.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnNewMeet.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );

 	m_btnNewMeet.GetWindowRect(&rectClient);
 	ScreenToClient( &rectClient );
 	m_etAddrSearch.SetWindowPos( &wndTop, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  rectClient.right - 
		m_btnNewMeet.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );

	m_btnCopy.EnableWindow(FALSE);
	m_btnCut.EnableWindow(FALSE);


	return TRUE;
}


BOOL CLocalAddrbookLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	if( m_pCncAddrBook == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pCncAddrBook);
	}

// 	if( m_pCncAddrBook != NULL )
// 	{
// 		m_pCncAddrBook->SetNotifyWnd(this->m_hWnd);
// 	}

	InitControlPane();

	OnInitAddrBook( 0, 0 );

	return TRUE;
}

void CLocalAddrbookLogic::OnBtnNewGrp() 
{
	if ( !m_vctSelectList.empty() )
	{
		m_vctSelectList.clear();
		UpdateShowList();
	}
	m_vctOperateList.clear();

	UpdateUIState();

	CLocalAddrbookGroupEdit dlgTmp(m_pCncAddrBook);
	dlgTmp.DoModal();
}

void CLocalAddrbookLogic::OnBtnNewMeeting() 
{
	if ( !m_vctSelectList.empty() )
	{
		m_vctSelectList.clear();
		UpdateShowList();
	}
	m_vctOperateList.clear();

	UpdateUIState();

	CLocalAddrbookMeetEdit dlgTmp(m_pCncAddrBook);
	dlgTmp.DoModal();
}

void CLocalAddrbookLogic::OnBtnReturn() 
{
	m_vctSelectList.clear();
	m_etAddrSearch.SetWindowText( "" );
	
	if ( m_CurGroup.dwInGroupIdx == INVALID_INDEX )
	{
		m_CurGroup.SetNull();
		UpdateShowList();
	}
	else
	{
		GetAddrGroupInfo( m_CurGroup.dwInGroupIdx, m_CurGroup );
		
		GetAddrGroupMember( m_CurGroup.dwGroupIdx );
	}

	//设置列表之前的偏移量
	int nSize = m_vctListOffset.size();
	if ( nSize > 0 && m_plsLocalAddr != NULL )
	{
		s32 nOffset = m_vctListOffset.at( nSize - 1 );
		m_plsLocalAddr->SetYOffset( nOffset );
		m_vctListOffset.pop_back();
	}
	
	UpdateAddrTitle();

    UpdateUIState();
}

void CLocalAddrbookLogic::OnBtnCopy() 
{
	m_emOperateType = em_AddrBook_Copy;

	m_vctOperateList = m_vctSelectList;
	m_btnCopy.ShowWindow( SW_HIDE );
	m_btnCut.ShowWindow( SW_HIDE );
	m_btnPaste.ShowWindow( SW_SHOW );
	m_btnRevoke.ShowWindow( SW_SHOW );
}

void CLocalAddrbookLogic::OnBtnCut() 
{
	m_emOperateType = em_AddrBook_Cut;
	
	m_vctOperateList = m_vctSelectList;
	m_btnCopy.ShowWindow( SW_HIDE );
	m_btnCut.ShowWindow( SW_HIDE );
	m_btnPaste.ShowWindow( SW_SHOW );
	m_btnRevoke.ShowWindow( SW_SHOW );
}


void CLocalAddrbookLogic::OnBtnPaste()
{
	if ( m_pCncAddrBook == NULL )
	{
		return;
	}
	for ( int i = 0; i < m_vctOperateList.size(); i++ )
	{
		TAddrItem tAddrItem = m_vctOperateList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
			if ( tAddrInfo.dwInGroupIdx == INVALID_INDEX )
			{
				//从第一级复制/剪切到组中
				if ( !m_CurGroup.IsNull() )
				{				
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( m_CurGroup.dwGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = m_pCncAddrBook->AddEntryToGroup(tEntry);
				}
			}
			else
			{
				if ( m_CurGroup.dwGroupIdx == tAddrInfo.dwInGroupIdx )
				{
					continue;
				}
				//从组中复制/剪切
				if ( m_emOperateType == em_AddrBook_Cut )
				{
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( tAddrInfo.dwInGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = m_pCncAddrBook->DelEntryFromGroup(tEntry);
				}
				
				if ( !m_CurGroup.IsNull() )
				{				
					TADDRMULTISETENTRY tEntry;
					tEntry.SetEntryIndex( m_CurGroup.dwGroupIdx );
					u32 adwEntryTable[1] = {0};
					adwEntryTable[0] = tAddrInfo.dwEntryIdx;	
					tEntry.SetListEntryIndex(adwEntryTable, 1);
					tEntry.SetListEntryNum(1);
					u16 wRe = m_pCncAddrBook->AddEntryToGroup(tEntry);
				}
			}
		}
		else
		{
			//对组只有剪切操作
			if ( m_emOperateType == em_AddrBook_Copy )
			{
				continue;
			}

			TGroupInfo tGroupInfo = tAddrItem.tGroupInfo;
			if ( tGroupInfo.dwInGroupIdx == INVALID_INDEX )
			{
				//从第一级剪切到组中
				if ( !m_CurGroup.IsNull() )
				{
					u16 wRe = m_pCncAddrBook->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_CurGroup.dwGroupIdx );
				}
			}
			else
			{
				if ( m_CurGroup.dwGroupIdx == tGroupInfo.dwInGroupIdx )
				{
					continue;
				}
				//从组中剪切出来
				if ( !m_CurGroup.IsNull() )
				{	
					u16 wRe = m_pCncAddrBook->AddGroupToGroup( tGroupInfo.dwGroupIdx, m_CurGroup.dwGroupIdx );
				}
				else
				{
					u16 wRe = m_pCncAddrBook->DelGroupFromGroup( tGroupInfo.dwGroupIdx, tGroupInfo.dwInGroupIdx );
				}
			}
		}
	}
	
	m_vctOperateList.clear();
	m_vctSelectList.clear();
	
	UpdateShowList();
	UpdateUIState();
}


void CLocalAddrbookLogic::OnBtnRevoke()
{
	//m_vctSelectList.clear();
	//m_nSelGroupNum = 0;
	//UpdateShowList();
	m_vctOperateList.clear();
	UpdateUIState();
}


void CLocalAddrbookLogic::OnBtnDelete() 
{
	s32 nRet = 0;
	MESSAGEWNDBOX( "确定要删除当前条目？", this , nRet, TRUE );
	if( nRet != IDOK )
	{
		return;	
	}


    if ( m_vctSelectList.empty() )
	{
		return;
	}

    vector<u32> vctDelGroup;

    //如果当前有选中项，检测选中项是否被删除
    BOOL bNeedCheckSel = FALSE;
    if ( !m_tAddrItem.IsNull() )
    {
        if ( m_tAddrItem.emItemType == emEntryItem )
        {
            bNeedCheckSel = TRUE;
        }
    }

	if ( m_CurGroup.IsNull() )
	{
        //删除第一级目录中的条目
        vector<u32> vctDelEntry;

		for ( int i = 0; i < m_vctSelectList.size(); i++ )
		{
			TAddrItem tAddrItem = m_vctSelectList.at(i);
			if ( tAddrItem.emItemType == emEntryItem )
			{
				TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
				if ( tAddrInfo.dwInGroupIdx == INVALID_INDEX )
				{
					vctDelEntry.push_back( tAddrInfo.dwEntryIdx );
                    //一次最多删除MAX_DELENTRY_NUM个
                    if ( vctDelEntry.size() == MAX_DELENTRY_NUM )
                    {
                        u16 wRe = m_pCncAddrBook->DeleteMultiEntry( vctDelEntry );
                        vctDelEntry.clear();
                    }

                    if ( bNeedCheckSel )
                    {
                        if ( m_tAddrItem.tAddrInfo.dwEntryIdx == tAddrInfo.dwEntryIdx )
                        {
                            m_tAddrItem.SetNull();
                            bNeedCheckSel = FALSE;
                        }
                    }
				}
			}
            else
            {
                //组及其下级组都删除
			    GetGroupAndLowGroup( tAddrItem.tGroupInfo.dwGroupIdx, vctDelGroup );
            }
		}

		if ( !vctDelEntry.empty() )
		{
			if ( vctDelEntry.size() == 1 )
			{
				u16 wRe = m_pCncAddrBook->DeleteEntry( vctDelEntry.at(0) );
			}
			else
			{
				u16 wRe = m_pCncAddrBook->DeleteMultiEntry( vctDelEntry );
			}
		}      
	}
    else
    {   //删除组中的条目
        int nIndex = 0;
        u32 adwEntryTable[MAXNUM_ENTRY_TABLE] = {0};

        for ( int i = 0; i < m_vctSelectList.size(); i++ )
        {
            TAddrItem tAddrItem = m_vctSelectList.at(i);
            if ( tAddrItem.emItemType == emEntryItem )
			{
                TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
                if ( tAddrInfo.dwInGroupIdx != INVALID_INDEX )
				{
                    if ( nIndex >= MAXNUM_ENTRY_TABLE )
                    {
                        break;
                    }
                    adwEntryTable[nIndex] = tAddrInfo.dwEntryIdx;
                    nIndex++;
                }

                if ( bNeedCheckSel )
                {
                    if ( m_tAddrItem.tAddrInfo == tAddrInfo )
                    {
                        m_tAddrItem.SetNull();
                        bNeedCheckSel = FALSE;
                    }
                }
            }
            else
            {
                GetGroupAndLowGroup( tAddrItem.tGroupInfo.dwGroupIdx, vctDelGroup );
            }
        }

        if ( nIndex > 0 )
        {
            TADDRMULTISETENTRY tEntry;
            tEntry.SetEntryIndex( m_CurGroup.dwGroupIdx );
      	
            tEntry.SetListEntryIndex(adwEntryTable, nIndex);
            tEntry.SetListEntryNum(nIndex);
		    u16 wRe = m_pCncAddrBook->DelEntryFromGroup(tEntry);
        }
        
    }

    if ( !vctDelGroup.empty() )
    {
        if ( vctDelGroup.size() == 1 )
        {
            u16 wRe = m_pCncAddrBook->DeleteGroup( vctDelGroup.at(0) );
        }
        else
        {
            u16 wRe = m_pCncAddrBook->DeleteMultiGroup( vctDelGroup );
        }
    }

	m_vctSelectList.clear();
	//m_SelItem.SetNull();
	UpdateUIState();

	return;
}

void CLocalAddrbookLogic::OnBtnEdit() 
{
	// TODO: Add your control notification handler code here

	EM_ItemType em_type = m_tAddrItem.emItemType;
	if ( em_type == emEntryItem )
	{
		//为会场，编辑会场信息
		CLocalAddrbookMeetEdit dlgAddrMeetEdit( m_pCncAddrBook, m_tAddrItem.tAddrInfo );
		dlgAddrMeetEdit.DoModal();
	}
	else if( em_type == emGroupItem )
	{
		//为分组，编辑分组信息
		CLocalAddrbookGroupEdit dlgAddrGroupEdit( m_pCncAddrBook, m_tAddrItem.tGroupInfo );
		dlgAddrGroupEdit.DoModal();
	}
}



void CLocalAddrbookLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();
	
	SAFE_RELEASE(m_plsLocalAddr);
	SAFE_RELEASE(m_pLetterIndex);

}

void CLocalAddrbookLogic::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDlgChild::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		//地址簿请求语句
  		BUSINESSIFPTR->GetCtrlInterface(&m_pCncAddrBook);
 		ASSERT(m_pCncAddrBook!=NULL);
// 		m_pCncAddrBook->SetNotifyWnd(this->m_hWnd);
  		//RefreshGrpMeetList(m_AddrBookCurStep);
	}
	else
	{
		//注销地址簿请求
	}
}

LRESULT CLocalAddrbookLogic::OnInitAddrBook(WPARAM wParam, LPARAM lParam)
{
	UpdateAddrbook();

	if ( !m_CurGroup.IsNull() )	
	{
		GetAddrGroupMember( m_CurGroup.dwGroupIdx );
	}

	CString strSearchName;
	m_etAddrSearch.GetWindowText( strSearchName );
	if ( !strSearchName.IsEmpty() )
	{
		OnSearchEditChange( 0 , 0 );
	}

	if ( m_bWaitAdd && !m_tAddrItem.IsNull() && m_plsLocalAddr != NULL )
	{
		if ( m_tAddrItem.emItemType == emEntryItem )
		{
			m_plsLocalAddr->SetSelItem( m_tAddrItem.tAddrInfo.dwEntryIdx );
		}
		else
		{
			m_plsLocalAddr->SetSelItem( m_tAddrItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY );
		}
		m_btnEdit.EnableWindow(TRUE);
	}

	CMsgHandle::SendMessage( UI_CNS_ADDRBOOK_CHANGED, (WPARAM)&m_vctLocalList );

	return 0;
}



LRESULT CLocalAddrbookLogic::OnAddEntry(WPARAM wParam, LPARAM lParam)
{
	u32 dwEntryIndex = (u32)wParam;

	TAddrInfo tAddrInfo;
	tAddrInfo.dwEntryIdx = dwEntryIndex;
	strncpy( tAddrInfo.achEntryName, (s8*)lParam, TP_MAX_ALIAS_LEN_CNC+1 );

	if ( !m_CurGroup.IsNull() )
	{
		TADDRMULTISETENTRY tEntry;
		
		u32 adwEntryTable[1] = {0};
		tEntry.SetEntryIndex( m_CurGroup.dwGroupIdx );
		adwEntryTable[0] = dwEntryIndex;
		tEntry.SetListEntryIndex(adwEntryTable, 1);
		tEntry.SetListEntryNum(1);
		u16 wRe = m_pCncAddrBook->AddEntryToGroup(tEntry);		
	}

	if ( m_pCncAddrBook != NULL )
	{
		CAddrEntry cEntry;
		m_pCncAddrBook->GetAddrBook().GetAddrEntry( &cEntry, dwEntryIndex );
		SetAddrItemInfo( tAddrInfo, cEntry );
	}

	m_tAddrItem.emItemType = emEntryItem;
	m_tAddrItem.tAddrInfo = tAddrInfo;
	m_bWaitAdd = TRUE;

	return NO_ERROR;
}

LRESULT CLocalAddrbookLogic::OnAddGroup(WPARAM wParam, LPARAM lParam)
{

	TGroupInfo tGroupInfo;
	u32 dwGroupIndex = (u32)wParam;
	tGroupInfo.dwGroupIdx = dwGroupIndex;
	strncpy( tGroupInfo.achGroupName, (s8*)lParam, TP_MAX_ALIAS_LEN_CNC+1 ); 
	
	if ( !m_CurGroup.IsNull() )
	{
		u16 wRe = m_pCncAddrBook->AddGroupToGroup( dwGroupIndex, m_CurGroup.dwGroupIdx );
	}
	
	m_tAddrItem.emItemType = emGroupItem;
	m_tAddrItem.tGroupInfo = tGroupInfo;
	m_bWaitAdd = TRUE;

	return NO_ERROR;
}


LRESULT CLocalAddrbookLogic::OnAddrModifyNty(WPARAM wParam, LPARAM lParam)
{
	BOOL bEntry = (BOOL)wParam;
	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	if ( bEntry )
	{
		if ( m_tAddrItem.emItemType != emEntryItem || m_tAddrItem.tAddrInfo.dwEntryIdx != lParam )
		{
			return NO_ERROR;
		}
		
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, m_tAddrItem.tAddrInfo.dwEntryIdx );
		
		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );
		m_tAddrItem.tAddrInfo = tAddrInfo;	
	}
	else
	{
		if ( m_tAddrItem.emItemType != emGroupItem || m_tAddrItem.tGroupInfo.dwGroupIdx != lParam )
		{
			return NO_ERROR;
		}
		
		TGroupInfo tGroupInfo;
		GetAddrGroupInfo( m_tAddrItem.tGroupInfo.dwGroupIdx, tGroupInfo );
		
		m_tAddrItem.tGroupInfo = tGroupInfo;
		
		UpdateAddrTitle();	
	}
	return NO_ERROR;
}


LRESULT CLocalAddrbookLogic::OnAddrOptFailed(WPARAM wParam, LPARAM lParam)
{
    u16 wCmd = wParam;
    switch( wCmd )
    {
    case ADDRBOOK_ADD_ENTRY_REQ:
        MESSAGEWND( "新建会场失败");
        break;
    case ADDRBOOK_MODIFYENTRY_REQ:
        MESSAGEWND( "修改会场失败");
        break;
    case ADDRBOOK_DEL_ENTRY_REQ:
        MESSAGEWND( "删除会场失败");
        break;
    case ADDRBOOK_ADD_MULSETENTRY_REQ:
        MESSAGEWND( "新建分组失败");
        break;
    case ADDRBOOK_MODIFYMULSETENTRY_REQ:
        MESSAGEWND( "修改分组失败");
        break;
    case ADDRBOOK_DEL_MULSETENTRY_REQ:
        MESSAGEWND( "删除分组失败");
        break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_REQ:
        MESSAGEWND( "添加会场到分组失败");
        break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_REQ:
        MESSAGEWND( "从分组中删除会场失败");
        break;
    default:
        break;
    }
    return NO_ERROR;
}


bool CLocalAddrbookLogic::OnClickLstItem( const IArgs & arg )
{
	if ( NULL == m_plsLocalAddr )
	{
		return false;
	}

	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {   
			m_tAddrItem = pItemInfo->m_tAddrItem;
						
			if ( m_tAddrItem.emItemType == emGroupItem )
			{
				m_vctSelectList.clear();
				m_etAddrSearch.SetWindowText( "" );
				
				//记录下当前列表偏移量				
				int nOffSet = m_plsLocalAddr->GetYOffset();
				m_vctListOffset.push_back( nOffSet );
				
				//进入组
				m_CurGroup = m_tAddrItem.tGroupInfo;
				GetAddrGroupMember( m_CurGroup.dwGroupIdx );

				//进入组之后将偏移量设为0
				m_plsLocalAddr->SetYOffset( 0 );

				//更新标题
				UpdateAddrTitle();

                UpdateUIState();
			}

			if ( m_vctSelectList.empty() )
			{
				m_btnEdit.EnableWindow(TRUE);
			}
        } 
    }
	
	return true;
}

bool CLocalAddrbookLogic::OnClickLstItemIcon( const IArgs & arg )
{

	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {   
			TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
			
			if( tAddrItem.strImg == "AddrEditSelItem" )
			{
				m_vctSelectList.push_back( tAddrItem );

			}
			else
			{
				vector<TAddrItem>::iterator iter = m_vctSelectList.begin();
				while( iter != m_vctSelectList.end() )
				{					  
					if ( *iter == tAddrItem )
					{
						m_vctSelectList.erase(iter);
						break;
					}		
					iter++;
				}

			}			

			m_vctOperateList.clear();
			m_tAddrItem.SetNull();

			UpdateShowList();

			UpdateUIState();
        } 
    }
    return true;
}

/*=============================================================================
函 数 名:UpdateAddrTitle
功    能:更新标题栏
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::UpdateAddrTitle()
{
	CRect rect;
	m_btnReturn.GetWindowRect(&rect);
	ScreenToClient(&rect);

	if ( m_CurGroup.IsNull() )
	{
		m_stLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  26*CUR_SCREEN_HEIGHT_PER, 0, 0, SWP_SHOWWINDOW );
		m_stLeftTitle.SetWindowText("本地地址簿");
		
		m_btnReturn.ShowWindow( SW_HIDE );
	}
	else
	{
		CString strTitle;
		strTitle =  GetAddrGroupPath( m_CurGroup.dwGroupIdx );
		strTitle = "本地地址簿" + strTitle;
		m_stLeftTitle.SetWindowText( strTitle );
		
		m_stLeftTitle.SetWindowPos( NULL, rect.right + 5*CUR_SCREEN_WIDTH_PER, 26*CUR_SCREEN_HEIGHT_PER, 0, 0, SWP_SHOWWINDOW );
		
		m_btnReturn.ShowWindow( SW_SHOW );
	}
}

/*=============================================================================
函 数 名:UpdateUIState
功    能:更新控件状态
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::UpdateUIState()
{
	int nSelSize = m_vctSelectList.size();
	if ( nSelSize > 0 )
	{
		m_btnCopy.ShowWindow( SW_SHOW );
		m_btnCopy.EnableWindow( TRUE );
		m_btnCut.ShowWindow( SW_SHOW );
		m_btnCut.EnableWindow( TRUE );
		m_btnPaste.ShowWindow( SW_HIDE );
		m_btnRevoke.ShowWindow( SW_HIDE );
		m_btnDelete.EnableWindow( TRUE );
		m_btnEdit.EnableWindow( FALSE );
		
		//分组只能剪切，当选中项全是组时，禁用复制
		BOOL bCanCopy = FALSE;
		for ( int i = 0; i< nSelSize; i++ )
		{
			if ( m_vctSelectList.at(i).emItemType == emEntryItem )
			{
				bCanCopy = TRUE;
				break;
			}
		}
		if ( bCanCopy )
		{
			m_btnCopy.EnableWindow( TRUE );
		}
		else
		{
			m_btnCopy.EnableWindow( FALSE );
		}
		
	}
	else
	{
		if ( m_vctOperateList.empty() )
		{
			m_btnCopy.ShowWindow( SW_SHOW );
			m_btnCopy.EnableWindow(FALSE);
			m_btnCut.ShowWindow( SW_SHOW );
			m_btnCut.EnableWindow(FALSE);
			m_btnPaste.ShowWindow( SW_HIDE );
			m_btnRevoke.ShowWindow( SW_HIDE );
			m_btnDelete.EnableWindow( FALSE );
			
			if ( m_tAddrItem.IsNull() )
			{
				m_btnEdit.EnableWindow(FALSE);
			}
			else
			{
				m_btnEdit.EnableWindow(TRUE);
			}
		}
	}
}


/*=============================================================================
函 数 名:UpdateShowList
功    能:更新当前显示列表
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::UpdateShowList()
{
	CString strText;
	m_etAddrSearch.GetWindowText( strText );

	if ( strText.IsEmpty() )
	{
		if ( m_CurGroup.IsNull() )
		{
			m_vctShowList = m_vctLocalList;
		}
		else
		{
			m_vctShowList = m_vctGroupMemberList;
		}
	}
	else
	{
		m_vctShowList = m_vctSearchList;
	}

	for ( int i = 0; i < m_vctShowList.size(); i++ )
	{		
		vector<TAddrItem>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), m_vctShowList.at(i) );

		if ( itfind == m_vctSelectList.end() )
		{
			m_vctShowList.at(i).strImg = "AddrEditSelItem";
		}
		else
		{
			m_vctShowList.at(i).strImg = "AddrEditUnSelItem";
		}	
	}

	Value_TouchListAddr val_ListAddrList( &m_vctShowList, NULL, "CLocalAddrbookLogic::OnClickLstItem" );
	if ( m_plsLocalAddr != NULL )
	{
		m_plsLocalAddr->SetData( val_ListAddrList );
	}	
}


void CLocalAddrbookLogic::UpdateAddrbook()
{
	m_vctLocalList.clear();

	UpdateAddrEntryList();
	UpdateLevelOneGroup();

	UpdateShowList();
}

/*=============================================================================
函 数 名:UpdateAddrEntryList
功    能:更新地址簿条目
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::UpdateAddrEntryList()
{
	if ( m_pCncAddrBook == NULL )
	{
		return;
	}

	m_vctLocalList.clear();
	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;
	CString strLetter;
	
	//获取基本条目个数
	u32 dwUsedSize = cAddrBook.GetAddrEntryUsedSize();
	
	u32 dwIndex = 0;
	s32 nIndex = 0;
	CAddrEntry cAddrEntry;
	dwIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );
	while ( nIndex < dwUsedSize )
	{
		if ( dwIndex != INVALID_INDEX )
		{	
			TAddrInfo tAddrInfo;
			SetAddrItemInfo( tAddrInfo, cAddrEntry );
			tAddrItem.tAddrInfo = tAddrInfo;

            //获取条目名称字母索引。当只有会场号码时对号码排序，索引为空格+号码的形式，保证号码在最前面 -2012.11.7 xcr
            if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
            {
                strLetter.Format( " %s", tAddrInfo.achE164 );
            }
            else
            {
			    CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
            }
			tAddrItem.strNameLetter = strLetter;

			m_vctLocalList.push_back(tAddrItem);
			
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrEntry( dwIndex, &cAddrEntry );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwIndex = cAddrEntry.GetEntryIndex();
			}			
		}
		else
		{
			break;
		}
	}
}

/*=============================================================================
函 数 名:UpdateLevelOneGroup
功    能:更新第一级组
参    数:无
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::UpdateLevelOneGroup()
{
	if ( m_pCncAddrBook == NULL )
	{
		return;
	}

	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T("");     //组名称
	
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;
	CString strLetter;
	
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = cAddrBook.FindLevelOneGroup( pdwGroup );
	
	CAddrMultiSetEntry cAddrGroup;
	for ( int i = 0; i < dwNum; i++ )
	{
		u32 dwGroupIndex = *(pdwGroup + i);
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		TGroupInfo tGroupInfo;
		tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
		strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
		tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
		u32* pEntryTable = cAddrGroup.GetEntryTable();
		for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
		{
			tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
		}
		u32 adwDownGroup[MAX_ADDRGROUP] = {0};
		tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );

		tAddrItem.tGroupInfo = tGroupInfo;

		CListChild::GetFirstLetter( tGroupInfo.achGroupName, strLetter );
		tAddrItem.strNameLetter = strLetter;

		m_vctLocalList.push_back(tAddrItem);
	}
	if ( pdwGroup != NULL )
	{
		delete []pdwGroup;
		pdwGroup = NULL;
	}
	
}


/*=============================================================================
函 数 名:GetAddrGroupMember
功    能:获取分组成员
参    数:dwGroupIndex  组索引
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::GetAddrGroupMember( u32 dwGroupIndex )
{
	m_vctGroupMemberList.clear();
	
	if ( m_pCncAddrBook == NULL )
	{
		return;
	}

	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	bool bValid = cAddrBook.IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}
	
	CString strLetter;
	CAddrMultiSetEntry cGroup;
	cAddrBook.GetAddrMultiSetEntry( &cGroup, dwGroupIndex );	
	
	int nNum = cGroup.GetEntryCount();
	u32* pEntryTable = cGroup.GetEntryTable();	
	
	for ( int i = 0; i < nNum; i++ )
	{
		bool bValid = cAddrBook.IsAddrEntryValid( *pEntryTable );
		if ( !bValid )
		{
			pEntryTable++;
			continue;
		}
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, *pEntryTable );
		
		TAddrItem tAddrItem;
		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );
		
		tAddrInfo.dwInGroupIdx = dwGroupIndex;
		tAddrItem.tAddrInfo = tAddrInfo;

        if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
        {
            strLetter.Format( " %s", tAddrInfo.achE164 );
        }
        else
        {
		    CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
        }
		tAddrItem.strNameLetter = strLetter;

		m_vctGroupMemberList.push_back(tAddrItem);
		
		pEntryTable++;
	}
	
	//下级分组
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = cAddrBook.FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;
	
	CAddrMultiSetEntry cAddrGroup;
	for ( i = 0; i < dwNum; i++ )
	{
		u32 dwDownGroupIndex = *(pdwGroup + i);
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwDownGroupIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		TGroupInfo tGroupInfo;
		tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
		strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
		tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
		u32* pEntryTable = cAddrGroup.GetEntryTable();
		for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
		{
			tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
		}
		tGroupInfo.dwInGroupIdx = dwGroupIndex;
		u32 adwDownGroup[MAX_ADDRGROUP] = {0};
		tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );
		tAddrItem.tGroupInfo = tGroupInfo;

		CListChild::GetFirstLetter( tGroupInfo.achGroupName, strLetter );
		tAddrItem.strNameLetter = strLetter;

		m_vctGroupMemberList.push_back(tAddrItem);
	}
	if ( pdwGroup != NULL )
	{
		delete []pdwGroup;
		pdwGroup = NULL;
	}
	
	UpdateShowList();
}


void CLocalAddrbookLogic::SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry )
{
	s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //条目名称
	s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164号
	
	cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
	cAddrEntry.GetMtNumber( aszE164, cAddrEntry.GetMtNumberLen() + 1 );
	
	tAddrInfo.dwEntryIdx = cAddrEntry.GetEntryIndex();
	strncpy( tAddrInfo.achEntryName, aszEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
	strncpy( tAddrInfo.achE164, aszE164, MAX_E164NUM_LEN + 1 );
}

/*=============================================================================
函 数 名:GetAddrGroupPath
功    能:获取分组路径
参    数:dwGroupIndex  组索引
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
CString CLocalAddrbookLogic::GetAddrGroupPath( u32 dwGroupIndex )
{
	CString strPath = _T("");
	CString strName;

	if ( m_pCncAddrBook == NULL )
	{
		return strPath;
	}
	
	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	CAddrMultiSetEntry cAddrGroup;
	
	u32 dwIndex = dwGroupIndex;
	while( dwIndex != INVALID_INDEX )
	{		
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		strName.Format( "\\%s", aszGroupName );
		strPath = strName + strPath;
		
		dwIndex = cAddrBook.FindUpGroupOfGroupByIndex( dwIndex );
	}
	return strPath;
}

/*=============================================================================
函 数 名:GetAddrGroupInfo
功    能:获取分组信息
参    数:[in]dwGroupIndex 组索引  
		 [out]tGroupInfo  组信息
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo )
{
	if ( m_pCncAddrBook == NULL )
	{
		return ;
	}

	CAddrBook cAddrBook = m_pCncAddrBook->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	
	CAddrMultiSetEntry cAddrGroup;
	cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );
	
	cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
	
	tGroupInfo.SetNull();
	tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
	strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
	tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
	u32* pEntryTable = cAddrGroup.GetEntryTable();
	for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
	{
		tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
	}
	tGroupInfo.dwInGroupIdx = cAddrBook.FindUpGroupOfGroupByIndex( dwGroupIndex );
	u32 adwDownGroup[MAX_ADDRGROUP] = {0};
	tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );
}

/*=============================================================================
函 数 名:DelGroupAndLowGroup
功    能:删除组及其下级组
参    数:[in]dwGroupIndex 组索引  
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
void CLocalAddrbookLogic::DelGroupAndLowGroup( u32 dwGroupIndex )
{
	if ( m_pCncAddrBook == NULL )
	{
		return;
	}

	bool bValid = m_pCncAddrBook->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}
	
	//下级分组
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = m_pCncAddrBook->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
	
	for ( int i = 0; i < dwNum; i++ )
	{
		u32 dwLowGroupIndex = *(pdwGroup + i);
		
		DelGroupAndLowGroup( dwLowGroupIndex );		
	}
	
	delete []pdwGroup;
	pdwGroup = NULL;
	
	u16 wRe = m_pCncAddrBook->DeleteGroup( dwGroupIndex );
}


void CLocalAddrbookLogic::GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup )
{
    if ( m_pCncAddrBook == NULL )
    {
        return;
	}

    bool bValid = m_pCncAddrBook->GetAddrBook().IsAddrMultiSetEntryValid( dwGroupIndex );
    if ( !bValid )
    {
        return;
    }
    vctGroup.push_back( dwGroupIndex );
    
    //下级分组
    u32 *pdwGroup = new u32[MAX_ADDRGROUP];
    u32 dwNum = m_pCncAddrBook->GetAddrBook().FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
    
    for ( int i = 0; i < dwNum; i++ )
    {
        u32 dwLowGroupIndex = *(pdwGroup + i);
        
        GetGroupAndLowGroup( dwLowGroupIndex, vctGroup );		
    }
    
    delete []pdwGroup;
    pdwGroup = NULL;
}

/*=============================================================================
函 数 名:OnSearchEditChange
功    能:响应搜索框变化消息
参    数: 
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人   修改内容
2012/06/01  1.0     肖楚然     创建
=============================================================================*/
LRESULT CLocalAddrbookLogic::OnSearchEditChange( WPARAM wParam, LPARAM lParam )
{
	//清空选中项
	if ( m_vctSelectList.size() > 0 )
	{
		m_vctSelectList.clear();
		UpdateUIState();
	}

	CString strSearchName;
	m_etAddrSearch.GetWindowText( strSearchName );
	if ( strSearchName.IsEmpty() )
	{
		UpdateShowList();

		//将选中项显示出来
		if ( !m_tAddrItem.IsNull() && m_plsLocalAddr != NULL )
		{
			if ( m_tAddrItem.emItemType == emEntryItem )
			{
				m_plsLocalAddr->SetSelItem( m_tAddrItem.tAddrInfo.dwEntryIdx );
			}
			else
			{
				m_plsLocalAddr->SetSelItem( m_tAddrItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY );
			}		
		}
		return NO_ERROR;
	}	
	
	m_vctSearchList.clear();
	vector<TAddrItem> vctShowList;

	if ( m_CurGroup.IsNull() )
	{
		vctShowList = m_vctLocalList;
	}
	else
	{
		vctShowList = m_vctGroupMemberList;
	}
	
	if ( m_plsLocalAddr != NULL )
	{
		m_plsLocalAddr->SetYOffset( 0 );
	}
	
	for ( int i = 0; i < vctShowList.size(); i++ )
	{
		CString strItemName;
		TAddrItem tAddrItem = vctShowList.at(i);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			//名称为空用E164号匹配
			if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) == 0 )
			{
				strItemName = tAddrItem.tAddrInfo.achE164;
			}
			else
			{
				strItemName = tAddrItem.tAddrInfo.achEntryName;
			}
		}
		else
		{
			strItemName = tAddrItem.tGroupInfo.achGroupName;
		}
		BOOL bFind = FALSE;			
		bFind = HZPYMatchList( strSearchName, strItemName );
		if ( bFind )
		{		
			m_vctSearchList.push_back( tAddrItem );
		}
	}
	
	UpdateShowList();

	return NO_ERROR;
}

BOOL CLocalAddrbookLogic::HZPYMatchList( const CString strTextInput,  const CString strTextSrc )
{
	// TODO: Add your control notification handler code here	
	if ( strTextInput.IsEmpty() )
	{
		return TRUE;
	}

	if ( strTextSrc.IsEmpty() )
	{
		return FALSE;
	}
	
	if ( strTextInput.GetLength() > MAX_FIND_HANZI_LEN )
	{
		return FALSE;
	}
	
    char hzstr[ MAX_FIND_HANZI_LEN + 1] = {0};
	
    strcpy( hzstr, strTextSrc );
	
	CHZPYSearch hzpy;
	
	char arrDest[ MAX_FIND_HANZI_LEN + 1 ] = {0};	
    strcpy( arrDest, strTextInput );   //检索内容
	
	BOOL bFind = FALSE;	
	bFind = hzpy.HZPYMatchList(arrDest, hzstr);
	
	return bFind;
}



void CLocalAddrbookLogic::InitDlg()
{   
	ShowWindow(SW_HIDE);
	
	m_vctLocalList.clear();
	m_vctGroupMemberList.clear();
	m_vctSelectList.clear();
	m_vctShowList.clear();
	m_vctSearchList.clear();
	m_vctOperateList.clear();
	if( m_plsLocalAddr != NULL )
	{
		m_plsLocalAddr->SetYOffset( 0 );
		m_plsLocalAddr->SetSelItem( -1 );
	}
	m_etAddrSearch.SetWindowText( "" );
			
	m_tAddrItem.SetNull();
	m_CurGroup.SetNull();

	UpdateShowList();
	UpdateAddrTitle();

	UpdateUIState();

	m_emOperateType = em_AddrBook_Copy;	
	m_bWaitAdd = FALSE;

	CWnd *pGroup = FindWindow( NULL, "AddrbookGroupEdit"); 
    if( pGroup != NULL )
	{
		pGroup->PostMessage( WM_CLOSE );
	}

	CWnd *pConf = FindWindow( NULL, "AddrbookConfEdit"); 
    if( pConf != NULL )
	{
		pConf->PostMessage( WM_CLOSE );
	}
}
 

LRESULT CLocalAddrbookLogic::OnUnSelAddrList( WPARAM wParam, LPARAM lParam )
{
    m_tAddrItem.SetNull();
	m_btnEdit.EnableWindow( FALSE );
	return NO_ERROR;
}