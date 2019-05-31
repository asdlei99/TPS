#pragma once


// PlayStatus dialog

#include "kdvtype.h"
#include "kdvdef.h"
#include "osp.h"
#include "medianet_win/kdvmedianet.h"
#include "codecwrapper_win32.h"

class CPlayStatus : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayStatus)

public:
	CPlayStatus(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayStatus();
	CKdvDecoder *m_pDecoder;
	UINT m_uTimer;
	TKdvDecStatis m_tDecStatis;
// Dialog Data
	enum { IDD = IDD_PLAY_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	
};
