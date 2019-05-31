/*****************************************************************************
ģ����      : CLocalAddrbookGroupEdit
�ļ���      : localaddrbookgroupEdit.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ���ص�ַ��ģ��
����        : 
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/10      1.0                     ����
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
	//��ѡ�ұߵĹ�����ĸ
	void OnFilterKey(UINT nID);
	afx_msg LRESULT OnAddEntry(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAddGroup(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddrModifyNty(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnAddrOptFailed(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	CStatic *pFltrKey[26];

public:
	//�ѽ��������еĿؼ������ݶ�����Ϊ��ʼ״̬
	void InitDlg();

	BOOL InitControlPane();

	/**	 
    * ����:  ������û�list item�ϵ�ͼ��
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
	* ����:  ��ȡ�����Ա�б�
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );

	/** ��CAddrEntry�����赽TAddrInfo��
	 *  @param[out] tAddrInfo  ��ַ��Ŀ��Ϣ
	 *  @param[in]  cAddrEntry ��ַ����Ŀ��Ϣ
	 *  @return 
	 */
	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );

	CString GetAddrGroupPath( u32 dwGroupIndex );

	/**
	* ����:  ��ȡ��ַ��������Ϣ
	*  @param[in]  dwGroupIndex  ������
	*  @param[out] tGroupInfo  ������Ϣ
	*  @return
	*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	/**	 
	* ����:  ɾ���鼰���¼���
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void DelGroupAndLowGroup( u32 dwGroupIndex );

    void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );

	BOOL HZPYMatchList( const CString strTextInput,  const CString strTextSrc );

private:
	CListChild* m_plsLocalAddr;
	CLetterIndex* m_pLetterIndex;

	vector<TAddrItem> m_vctLocalList;
	vector<TAddrItem> m_vctGroupMemberList;    //���Ա�б�
	vector<TAddrItem> m_vctSelectList;         //ѡ���б�
	vector<TAddrItem> m_vctShowList;
	vector<TAddrItem> m_vctSearchList;
	vector<TAddrItem> m_vctOperateList;      //ѡ�����ѱ������б�

	vector<s32>       m_vctListOffset;         //��¼ÿһ���б�ƫ����

	BOOL              m_bWaitAdd;              //�ȴ����

	TAddrItem  m_tAddrItem;
	TGroupInfo m_CurGroup;          //��ǰ������

	EM_Addrbook_OperateType  m_emOperateType;        //����/����

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_LOCALADDR_H__DCCEBA94_5601_4337_87FC_59D9A19347EE__INCLUDED_)
