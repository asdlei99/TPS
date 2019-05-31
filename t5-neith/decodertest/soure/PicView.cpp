// CPicView.cpp : implementation file
//

#include "stdafx.h"
#include "kdvplayertester.h"
#include "PicView.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CPicView dialog
#define DRAW_WND_WIDTH   (INT32)352//
#define DRAW_WND_HEIGHT  (INT32)288//

IMPLEMENT_DYNAMIC(CPicView, CDialogEx)

CPicView::CPicView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPicView::IDD, pParent)
{
	m_pDecoder = NULL;
	m_pPicView = NULL;
	memset(m_szFileName, 0, sizeof(m_szFileName));

}

CPicView::~CPicView()
{
}

void CPicView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPicView, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CPicView::OnPicSave)
END_MESSAGE_MAP()


// CPicView message handlers


void CPicView::SetDecoderHandle(CKdvDecoder * pDecoder)
{
	m_pDecoder = pDecoder;
}


void CPicView::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (m_pPicView != NULL)
	{
		delete m_pPicView;
		m_pPicView = NULL;
	}
	CDialogEx::OnClose();
}


BOOL CPicView::OnInitDialog(void)
{
	CDialogEx::OnInitDialog();
	m_pPicView = new CStatic;
	if (m_pPicView == NULL)
	{
		return FALSE;
	}
	CRect cRect;
	m_Line.GetWindowRect(&cRect);
	ScreenToClient(&cRect);
	cRect.top = cRect.bottom;

	m_pPicView->Create((NULL),WS_CHILD|WS_VISIBLE|SS_SUNKEN|SS_BITMAP|SS_NOTIFY, cRect,this);
	m_pPicView->SetWindowPos(this,0,0, DRAW_WND_WIDTH, DRAW_WND_HEIGHT,
		                     SWP_NOMOVE|SWP_NOZORDER);
	_stprintf(m_szFileName, _T("F:\\%d.jpg"), GetTickCount());

	CString szCaption("Save Picture");
	szCaption += " - ";
	szCaption += m_szFileName;
	SetWindowText(szCaption);


	return TRUE;
}


void CPicView::OnPicSave()
{
	// TODO: Add your control notification handler code here
	if (m_pDecoder != NULL)
	{
		m_pDecoder->SaveAsPic(m_szFileName, PIC_ENCODE_JPEG);
	}
}
