// FULLTEST.cpp : 实现文件
//

#include "stdafx.h"
#include "kdvplayertester.h"
#include "FULLTEST.h"
#include "afxdialogex.h"


// CFULLTEST 对话框

IMPLEMENT_DYNAMIC(CFULLTEST, CDialogEx)

CFULLTEST::CFULLTEST(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFULLTEST::IDD, pParent)
{

}

CFULLTEST::~CFULLTEST()
{
}

void CFULLTEST::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFULLTEST, CDialogEx)
END_MESSAGE_MAP()


// CFULLTEST 消息处理程序
