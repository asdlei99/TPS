#pragma once

#include "kdvtype.h"
#include "kdvdef.h"
#include "osp.h"
#include "medianet_win/kdvmedianet.h"
#include "codecwrapper_win32.h"
// CPicView dialog

class CPicView : public CDialogEx
{
	DECLARE_DYNAMIC(CPicView)

public:
	CPicView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPicView();

// Dialog Data
	enum { IDD = IDD_PIC_VIEW_DLG };
	CStatic m_Line;
	CStatic *m_pPicView;
	CKdvDecoder *m_pDecoder;
	wchar_t m_szFileName[MAX_PATH];

	void SetDecoderHandle(CKdvDecoder * pDecoder);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

protected:
	virtual BOOL OnInitDialog(void);
	afx_msg void OnClose();
	afx_msg void OnPicSave();
	
};
