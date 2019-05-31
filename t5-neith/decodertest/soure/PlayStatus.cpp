// PlayStatus.cpp : implementation file
//

#include "stdafx.h"
#include "kdvplayertester.h"
#include "PlayStatus.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// PlayStatus dialog

IMPLEMENT_DYNAMIC(CPlayStatus, CDialogEx)

CPlayStatus::CPlayStatus(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayStatus::IDD, pParent)
{
	m_uTimer = 0;
	memset(&m_tDecStatis,0,sizeof(m_tDecStatis));
}

CPlayStatus::~CPlayStatus()
{
}

void CPlayStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPlayStatus, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// PlayStatus message handlers


BOOL CPlayStatus::OnInitDialog(void)
{
	CDialogEx::OnInitDialog();
	TKdvDecStatis tDecStatis;
	memset(&tDecStatis,0,sizeof(tDecStatis));
	m_pDecoder->GetVidDecoderStatis(tDecStatis);

	SetDlgItemInt(IDC_VIDEO_FRAME_RATE, tDecStatis.m_byVideoFrameRate);
	SetDlgItemInt(IDC_VIDEO_BITRATE, tDecStatis.m_dwVideoBitRate);
	SetDlgItemInt(IDC_VIDEO_LOSE_NUM, tDecStatis.m_dwIndexLose);
	SetDlgItemInt(IDC_VIDEO_AVBITRATE, tDecStatis.m_wAvrVideoBitRate);
	//OspPrintf(TRUE, FALSE, "ÊÓÆµ½âÂëÖ¡ÂÊ:     %d\n",   tDecStatis.m_dwVideoBitRate);
	SetTimer(0,2000,0);
	return TRUE;
}



void CPlayStatus::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(0);
	CDialogEx::OnClose();
}


void CPlayStatus::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_pDecoder->GetVidDecoderStatis(m_tDecStatis);

	SetDlgItemInt(IDC_VIDEO_FRAME_RATE, m_tDecStatis.m_byVideoFrameRate);
	SetDlgItemInt(IDC_VIDEO_BITRATE, m_tDecStatis.m_dwVideoBitRate);
	SetDlgItemInt(IDC_VIDEO_LOSE_NUM, m_tDecStatis.m_dwIndexLose);
	SetDlgItemInt(IDC_VIDEO_AVBITRATE, m_tDecStatis.m_wAvrVideoBitRate);
	// 	SetDlgItemInt(IDC_VIDEO_FRAME_RATE, tDecStatis.m_bVideoDecStart/*tDecStatis.m_byVideoFrameRate*/);
	// 	SetDlgItemInt(IDC_VIDEO_BITRATE, tDecStatis.m_bRcvVideoStart/*tDecStatis.m_dwVideoBitRate*/);
	// 	SetDlgItemInt(IDC_VIDEO_LOSE_NUM, tDecStatis.m_dwVideoDecType/*tDecStatis.m_dwVideoLoseFrame*/);

	CDialogEx::OnTimer(nIDEvent);
}
