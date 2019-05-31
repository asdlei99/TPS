#pragma once

#include "kdvtype.h"
#include "kdvdef.h"
#include "osp.h"
#include "medianet_win/kdvmedianet.h"
#include "codecwrapper_win32.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "winsock2.h"

// CFULLTEST 对话框

class CFULLTEST : public CDialogEx
{
	DECLARE_DYNAMIC(CFULLTEST)

public:
	CFULLTEST(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFULLTEST();


	CKdvDecoder  m_KdvDecoder;
	HANDLE      m_hAec;
	CString     m_cIp;
	s8*         m_pLocalIpAddress;
	s8*         m_pRemoteIpAddress;

// 对话框数据
	enum { IDD = IDD_DIALOG_FULLSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
