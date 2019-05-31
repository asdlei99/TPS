/*****************************************************************************
模块名      : CLocalAddrbookGroupEdit
文件名      : localaddrbookgroupEdit.h
相关文件    : 
文件实现功能: umcweb 本地地址簿模块
作者        : 
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/10      1.0                     创建
******************************************************************************/
#if !defined(AFX_LOCALADDR_H__DCCEBA94_5601_4337_87FC_59D9A19347EE__INCLUDED_)
#define AFX_LOCALADDR_H__DCCEBA94_5601_4337_87FC_59D9A19347EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// localaddrbookLogic.h : header file
//
#include "cncaddrbookif.h"
#include "PubFunc.h"
#include "addrbook.h"
#include "evCmsLib.h"

/////////////////////////////////////////////////////////////////////////////
// CLocalAddrbookLogic dialog
class CLocalAddrbookLogic : public CDlgChild
{
// Construction
public:
	CLocalAddrbookLogic(CWnd* pParent = NULL);   // standard constructor
	CCncAddrbookIF *m_pCncAddrBook;
	CAddrBook *m_pAddrBook;

// Dialog Data
	//{{AFX_DATA(CLocalAddrbookLogic)
	enum { IDD = IDD_DIALOG_LOCALADDRBOOK };
	CTransparentStatic m_stLeftTitle;
	CTransparentBtn	m_btnEdit;
	CTransparentBtn	m_btnDelete;
	CTransparentBtn	m_btnCut;
	CTransparentBtn	m_btnCopy;
	CTransparentBtn m_btnPaste;
	CTransparentBtn m_btnRevoke;
	CTransparentBtn	m_btnNewMeet;
	CTransparentBtn	m_btnNewGroup;
	CTransparentBtn	m_btnReturn;
	CTransparentEdit m_etAddrSearch;
	CListCtrl	m_LstVw;
	CString	m_strDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalAddrbookLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CImageList m_imgLst;
//  	CCncAddrbook cnAddrBk;
	CRect m_CurRect;

	// Generated message map functions
	//{{AFX_MSG(CLocalAddrbookLogic)
	afx_msg void OnBtnNewGrp();
	afx_msg void OnBtnNewMeeting();
	afx_msg void OnBtnReturn();
	afx_msg void OnBtnCopy();
	afx_msg void OnBtnCut();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnPaste();
	afx_msg void OnBtnRevoke();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnInitAddrBook(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnUnSelAddrList(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnSearchEditChange(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	//点选右边的过滤字母
	void OnFilterKey(UINT nID);
	afx_msg LRESULT OnAddEntry(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAddGroup(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddrModifyNty(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnAddrOptFailed(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	CStatic *pFltrKey[26];

public:
	//把界面中所有的控件及数据都重置为初始状态
	void InitDlg();

	BOOL InitControlPane();

	/**	 
    * 功能:  点击了用户list item上的图标
    * @return   bool
    * @remarks  
    */  
    bool OnClickLstItemIcon( const IArgs & arg );

	bool OnClickLstItem( const IArgs & arg );

	void UpdateAddrbook(); 

	void UpdateAddrEntryList();
	void UpdateLevelOneGroup();

	void UpdateShowList();

	void UpdateUIState();

	void UpdateAddrTitle();

	/**	 
	* 功能:  获取分组成员列表
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );

	/** 将CAddrEntry数据设到TAddrInfo中
	 *  @param[out] tAddrInfo  地址条目信息
	 *  @param[in]  cAddrEntry 地址簿条目信息
	 *  @return 
	 */
	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );

	CString GetAddrGroupPath( u32 dwGroupIndex );

	/**
	* 功能:  获取地址簿分组信息
	*  @param[in]  dwGroupIndex  组索引
	*  @param[out] tGroupInfo  分组信息
	*  @return
	*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	/**	 
	* 功能:  删除组及其下级组
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void DelGroupAndLowGroup( u32 dwGroupIndex );

    void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );

	BOOL HZPYMatchList( const CString strTextInput,  const CString strTextSrc );

private:
	CListChild* m_plsLocalAddr;
	CLetterIndex* m_pLetterIndex;

	vector<TAddrItem> m_vctLocalList;
	vector<TAddrItem> m_vctGroupMemberList;    //组成员列表
	vector<TAddrItem> m_vctSelectList;         //选中列表
	vector<TAddrItem> m_vctShowList;
	vector<TAddrItem> m_vctSearchList;
	vector<TAddrItem> m_vctOperateList;      //选中且已被操作列表

	vector<s32>       m_vctListOffset;         //记录每一层列表偏移量

	BOOL              m_bWaitAdd;              //等待添加

	TAddrItem  m_tAddrItem;
	TGroupInfo m_CurGroup;          //当前所在组

	EM_Addrbook_OperateType  m_emOperateType;        //复制/剪切

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_LOCALADDR_H__DCCEBA94_5601_4337_87FC_59D9A19347EE__INCLUDED_)
