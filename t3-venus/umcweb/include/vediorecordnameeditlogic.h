#if !defined(AFX_VEDIORECORDNAMEEDITLOGIC_H__EF90E0B0_85F3_4179_8D0F_F7E062CB44C6__INCLUDED_)
#define AFX_VEDIORECORDNAMEEDITLOGIC_H__EF90E0B0_85F3_4179_8D0F_F7E062CB44C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// vediorecordnameeditlogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVedioRecordNameEditLogic dialog

class CVedioRecordNameEditLogic : public CTransparentBaseDlg
{
// Construction
public:
	CVedioRecordNameEditLogic(CWnd* pParent = NULL);   // standard constructor
	CVedioRecordNameEditLogic( TRecConfInfo tRecConfInfo, CWnd* pParent = NULL );

// Dialog Data
	//{{AFX_DATA(CVedioRecordNameEditLogic)
	enum { IDD = IDD_DIALOG_VIDEORECORD_NAME_EDIT };
	CTransparentBtn	m_btnOk;
	CTransparentBtn	m_btnCancel;
	CTransparentStatic	m_stcRecordName;
	CTransparentEdit	m_edtRecordName;
	CTransparentStatic	m_stcEditRecordName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVedioRecordNameEditLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVedioRecordNameEditLogic)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//��ʽ��%����ֵ%
	//����: A��ʾ��Ƶ��ʽ B��ʾH.264���ʼ��� C��ʾ֡�� D��ʾ��Ƶ�ֱ���
	//      E��ʾ�Ƿ�˫��  F��ʾ˫����Ƶ��ʽ G��ʾ˫��H.264���ʼ��� H��ʾ˫��֡�� I��ʾ˫����Ƶ�ֱ���
	static void ParseRecordName(CString strRecordName, TUmsVidFormat& tConfFormat, BOOL& bDual, TUmsVidFormat& tDualFormat);

	//���ļ������Ƿ���ڸ�ʽ��ǩ
	static BOOL IsExistElement( CString strRecordName );

private:
	bool GetRecordName( CString& strRecordName );

	//���ļ���֮ǰ��Ӹ�ʽ��ǩ
	void AddElement( CString& strRecordName, CString strName, int nValue );

	//���ļ����н�����ʽ��ǩ
	static int ParseElement( CString strRecordName, CString strName );

private:
	//---umslib���ƽӿ� 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;

	TRecConfInfo m_tRecConfInfo;

private:
	static CVedioRecordNameEditLogic *m_pDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEDIORECORDNAMEEDITLOGIC_H__EF90E0B0_85F3_4179_8D0F_F7E062CB44C6__INCLUDED_)
