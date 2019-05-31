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
	//格式：%属性值%
	//属性: A表示视频格式 B表示H.264画质级别 C表示帧率 D表示视频分辨率
	//      E表示是否双流  F表示双流视频格式 G表示双流H.264画质级别 H表示双流帧率 I表示双流视频分辨率
	static void ParseRecordName(CString strRecordName, TUmsVidFormat& tConfFormat, BOOL& bDual, TUmsVidFormat& tDualFormat);

	//在文件名中是否存在格式标签
	static BOOL IsExistElement( CString strRecordName );

private:
	bool GetRecordName( CString& strRecordName );

	//在文件名之前添加格式标签
	void AddElement( CString& strRecordName, CString strName, int nValue );

	//在文件名中解析格式标签
	static int ParseElement( CString strRecordName, CString strName );

private:
	//---umslib控制接口 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;

	TRecConfInfo m_tRecConfInfo;

private:
	static CVedioRecordNameEditLogic *m_pDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEDIORECORDNAMEEDITLOGIC_H__EF90E0B0_85F3_4179_8D0F_F7E062CB44C6__INCLUDED_)
