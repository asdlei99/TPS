/*****************************************************************************
ģ����      : CLocalAddrbookGroupEdit
�ļ���      : localaddrbookgroupEdit.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ���ص�ַ������༭ҳ��
����        : 
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/16      1.0                     ����
******************************************************************************/
#if !defined(AFX_LOCALADDRGRPEDIT_H__4ED973A6_586F_41BE_98E5_D6411C77355C__INCLUDED_)
#define AFX_LOCALADDRGRPEDIT_H__4ED973A6_586F_41BE_98E5_D6411C77355C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalAddrGrpEdit.h : header file
//

class CLocalAddrbookGroupEdit : public CTransparentBaseDlg
{
// Construction
public:
	CLocalAddrbookGroupEdit(CCncAddrbookIF* pAdBk, CWnd* pParent = NULL);   // standard constructor
	CLocalAddrbookGroupEdit(CCncAddrbookIF* pAdBk, TGroupInfo tGroupInfo, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CLocalAddrbookGroupEdit)
	enum { IDD = IDD_DIALOG_LOCALADDR_GRPEDIT };
	CTransparentStatic	m_stEditGroup;
	CTransparentStatic	m_stGroupName;
	CTransparentBtn		m_btnSave;
	CTransparentBtn		m_btnCancel;
	CTransparentEdit	m_etGroupName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalAddrbookGroupEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCncAddrbookIF*  m_pAddrBook;
	CAddrMultiSetEntry m_AddrGroup;
	// Generated message map functions
	//{{AFX_MSG(CLocalAddrbookGroupEdit)
	afx_msg void OnBtnSave();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	TGroupInfo m_tGroupInfo;
	BOOL       m_bEdit;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALADDRGRPEDIT_H__4ED973A6_586F_41BE_98E5_D6411C77355C__INCLUDED_)
