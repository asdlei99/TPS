#pragma once

#include "kdvtype.h"
#include "kdvdef.h"
#include "osp.h"
#include "medianet_win/kdvmedianet.h"
#include "codecwrapper_win32.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "winsock2.h"

// CFULLTEST �Ի���

class CFULLTEST : public CDialogEx
{
	DECLARE_DYNAMIC(CFULLTEST)

public:
	CFULLTEST(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFULLTEST();


	CKdvDecoder  m_KdvDecoder;
	HANDLE      m_hAec;
	CString     m_cIp;
	s8*         m_pLocalIpAddress;
	s8*         m_pRemoteIpAddress;

// �Ի�������
	enum { IDD = IDD_DIALOG_FULLSCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
