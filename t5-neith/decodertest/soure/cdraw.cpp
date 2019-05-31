#include "stdafx.h"
#include "cdraw.h"


IMPLEMENT_DYNAMIC(CDrawWnd, CStatic)
CDrawWnd::CDrawWnd( BOOL32 bAlloc )
{
	memset(&m_rtPos, 0, sizeof(RECT));
	m_hParentWnd  = NULL;
	m_bFullScreen = FALSE;
	m_pPriData      = NULL;
	if(!bAlloc) return;
	m_pPriData = new TDrawBack;
	if(m_pPriData == NULL )
	{
		return ;    
	}
	memset(m_pPriData, 0, sizeof(TDrawBack));
	InitializeCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
	((TDrawBack *)m_pPriData)->m_pBuf = 
		new u8[MAX_VID_FRAME_WIDTH * MAX_VID_FRAME_HEIGHT * 4];
	((TDrawBack *)m_pPriData)->m_hDrawDib = DrawDibOpen();

}

CDrawWnd::~CDrawWnd()
{
	if(m_pPriData != NULL )
	{
		EnterCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
	}
	if(m_pPriData != NULL && ((TDrawBack *)m_pPriData)->m_pBuf != NULL)
	{
		delete ((TDrawBack *)m_pPriData)->m_pBuf;
		((TDrawBack *)m_pPriData)->m_pBuf = NULL;
	}

	if(m_pPriData != NULL && ((TDrawBack *)m_pPriData)->m_pDrawBuf != NULL)
	{
		delete ((TDrawBack *)m_pPriData)->m_pDrawBuf;
		((TDrawBack *)m_pPriData)->m_pDrawBuf = NULL;
	}

	if(m_pPriData != NULL && ((TDrawBack *)m_pPriData)->m_hDrawDib != NULL)
	{
		DrawDibEnd(((TDrawBack *)m_pPriData)->m_hDrawDib);
		DrawDibClose(((TDrawBack *)m_pPriData)->m_hDrawDib);
		((TDrawBack *)m_pPriData)->m_hDrawDib = NULL;
	}
	if(m_pPriData != NULL )
	{
		LeaveCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
		DeleteCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
	}
	if(m_pPriData != NULL )
	{
		delete ((TDrawBack *)m_pPriData);
		m_pPriData = NULL;
	}
}

BOOL32 CDrawWnd::Create(LPCTSTR lpszWindowName, UINT dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle|=SS_NOTIFY;	
	return CStatic::Create(lpszWindowName, dwStyle, rect, pParentWnd, nID);
}

BEGIN_MESSAGE_MAP(CDrawWnd, CStatic)
	//{{AFX_MSG_MAP(CDrawWnd)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//设置全屏
// BOOL32 CDrawWnd::SetFullScreen()
// {
// 	if(m_bFullScreen) return TRUE;
// 
// 	m_hParentWnd =::GetParent(this->m_hWnd);
// 	POINT ptParent;
// 	ptParent.x = 0;
// 	ptParent.y = 0;
// 	::ClientToScreen(m_hParentWnd, &ptParent);
// 	GetWindowRect( &m_rtPos );
// 	m_rtPos.left   = m_rtPos.left-ptParent.x;
// 	m_rtPos.top    = m_rtPos.top-ptParent.y;
// 	m_rtPos.right  = m_rtPos.right-ptParent.x;
// 	m_rtPos.bottom = m_rtPos.bottom-ptParent.y;
// 
// 	s32 cx = GetSystemMetrics(SM_CXSCREEN);
// 	s32 cy = GetSystemMetrics(SM_CYSCREEN);
// 
// 	SetParent(NULL);
// 	SetWindowPos(NULL, 0, 0, cx, cy, SWP_SHOWWINDOW);
// 	m_bFullScreen = TRUE;
// 	return TRUE;
// }
// 
// //取消全屏
// BOOL32 CDrawWnd::CancelFullScreen()
// {
// 	if(m_hParentWnd == NULL|| !m_bFullScreen)
// 	{
// 		return FALSE;
// 	}
// 	::SetParent(m_hWnd, m_hParentWnd);
// 	SetWindowPos(NULL, m_rtPos.left, m_rtPos.top,
// 		m_rtPos.right-m_rtPos.left,
// 		m_rtPos.bottom-m_rtPos.top,
// 		SWP_SHOWWINDOW);
// 	m_bFullScreen = FALSE;
// 	return TRUE;
// }
// 
// /*=============================================================================
// 函数名		 SetBackBitmap
// 功能		：设置背景图片
// 算法实现	：（可选项）
// 引用全局变量：无
// 输入参数说明：
//             pBuf        数据缓冲
//             nSize       数据大小
//             pbmiHeader  数据格式
// 返回值说明: 成功返回TRUE, 失败返回FALSE
// =============================================================================*/
// BOOL32 CDrawWnd::SetBackBitmap(u8 *pBuf, s32 nSize, 
//                               PBITMAPINFOHEADER pbmiHeader)
// {
//     //判断对象是否建立
//     if(m_pPriData == NULL ) return FALSE;
//     if(((TDrawBack *)m_pPriData)->m_hDrawDib == NULL)
//     {
//          return FALSE;
//     }
//     //和画图同步
//     EnterCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
//    
//     //copy memory
//     memcpy(((TDrawBack *)m_pPriData)->m_pBuf, pBuf, nSize);
//     ((TDrawBack *)m_pPriData)->m_nSize = nSize;
// 
//     //格式检查
//     if(pbmiHeader->biBitCount != ((TDrawBack *)m_pPriData)->m_bmiHeader.biBitCount||
//        pbmiHeader->biCompression != ((TDrawBack *)m_pPriData)->m_bmiHeader.biCompression||
//        pbmiHeader->biWidth != ((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth||
//        pbmiHeader->biHeight != ((TDrawBack *)m_pPriData)->m_bmiHeader.biHeight)
//     {//格式变化，给画图对象设置格式
//         
//         RECT rc;
//         HDC  hDC = ::GetDC(this->m_hWnd);
//         GetWindowRect(&rc);
//         if(!DrawDibBegin(((TDrawBack *)m_pPriData)->m_hDrawDib, hDC,
//                      rc.right - rc.left, rc.bottom - rc.top, pbmiHeader,
//                      pbmiHeader->biWidth, pbmiHeader->biHeight,
//                      DDF_SAME_HDC))
//         {
// 			::ReleaseDC(this->m_hWnd, hDC);
//             LeaveCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
//             return FALSE;
//         }
//         
//         //copy format
//         memcpy(&(((TDrawBack *)m_pPriData)->m_bmiHeader), 
//             pbmiHeader, sizeof(BITMAPINFOHEADER));
// 
// 		::ReleaseDC(this->m_hWnd, hDC);
//     }
//     LeaveCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
//     //刷新界面
//     Invalidate();
//     return TRUE;
// }
// 
// 
// BOOL32 CDrawWnd::SetFrontBmp(u8*  pFrontBuf)
// {
// 	if(m_pPriData == NULL)
// 	{
// 		return FALSE;
// 	}
// 	TDrawBack *pDrawBack = (TDrawBack *)m_pPriData;
// 
// 	EnterCriticalSection(&(pDrawBack->m_csLock));
// 	if(pFrontBuf == NULL)
// 	{
// 		SAFE_DELETE_ARRAY(pDrawBack->m_pDrawBuf);
// 		LeaveCriticalSection(&(pDrawBack->m_csLock));
// 		Invalidate(TRUE);
// 		return TRUE;
// 	}
// 
// 	s32 nSize = pDrawBack->m_bmiHeader.biWidth*
// 		pDrawBack->m_bmiHeader.biHeight*
// 		24/8;
// 
// 	if(pDrawBack->m_pDrawBuf == NULL)
// 	{
// 		pDrawBack->m_pDrawBuf = new u8[nSize];
// 	}
// 
// 	memcpy(pDrawBack->m_pDrawBuf, pDrawBack->m_pBuf, nSize);
// 
// 	FgTransparencyInfo fti;
// 	fti.nWidth = (u16)(pDrawBack->m_bmiHeader.biWidth);
// 	fti.nHeight = (u16)(pDrawBack->m_bmiHeader.biHeight);
// 	fti.byTransparency = 255;
// 	fti.sTop  = 0;
// 	fti.sLeft = 0;
// 	fti.pFg = pFrontBuf;
// 	ImageMerge(pDrawBack->m_pDrawBuf, (u16)(pDrawBack->m_bmiHeader.biWidth),
// 		(u16)(pDrawBack->m_bmiHeader.biHeight), fti);
// 
// 	Invalidate(TRUE);
// 	LeaveCriticalSection(&(pDrawBack->m_csLock));
// 
// 	return TRUE;
// }
// 
// BOOL32 CDrawWnd::GetPicInfo(PBITMAPINFOHEADER pbih)
// {
// 	if(m_pPriData == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	TDrawBack *pDrawBack = (TDrawBack *)m_pPriData;
// 	if(pDrawBack->m_bmiHeader.biWidth!=0)
// 	{
// 		*pbih = pDrawBack->m_bmiHeader;             
// 		return TRUE;
// 	}
// 	return FALSE;
// }
// 
// BOOL32 CDrawWnd::SaveAsPic(LPCSTR lpszFileName, u8 byEncodeMode)
// {
// 	if(m_pPriData == NULL)
// 	{
// 		return FALSE;
// 	}
// 	if(lpszFileName == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	TDrawBack *pDrawBack = (TDrawBack *)m_pPriData;
// 	u8*  pBuf = pDrawBack->m_pBuf;
// 	if(pDrawBack->m_pDrawBuf!= NULL)
// 		pBuf = pDrawBack->m_pDrawBuf;
// 
// 	PBITMAPINFOHEADER pbih = &(pDrawBack->m_bmiHeader);
// 
// 	if(pbih->biWidth == 0 || pbih->biHeight == 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(byEncodeMode == PIC_ENCODE_BMP)
// 	{
// 		HANDLE hf;                 // file handle 
// 		BITMAPFILEHEADER hdr;       // bitmap file-header 
// 		u32 dwTmp;
// 		// Create the .BMP file. 
// 		hf = CreateFile(lpszFileName, 
// 			GENERIC_READ | GENERIC_WRITE, 
// 			(u32) 0, 
// 			NULL, 
// 			CREATE_ALWAYS, 
// 			FILE_ATTRIBUTE_NORMAL, 
// 			(HANDLE) NULL); 
// 
// 		if (hf == INVALID_HANDLE_VALUE) 
// 		{
// 			return FALSE;
// 		}
// 		hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
// 		// Compute the size of the entire file. 
// 		hdr.bfSize = (u32) (sizeof(BITMAPFILEHEADER) + 
// 			pbih->biSize + pbih->biClrUsed 
// 			* sizeof(RGBQUAD) + pbih->biSizeImage); 
// 		hdr.bfReserved1 = 0; 
// 		hdr.bfReserved2 = 0; 
// 
// 		// Compute the offset to the array of color indices. 
// 		hdr.bfOffBits = (u32) sizeof(BITMAPFILEHEADER) + 
// 			pbih->biSize + pbih->biClrUsed 
// 			* sizeof (RGBQUAD); 
// 
// 		// Copy the BITMAPFILEHEADER into the .BMP file. 
// 		if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
// 			(LPDWORD) &dwTmp,  NULL)) 
// 		{
// 			return FALSE;
// 		}
// 
// 		// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
// 		if (!WriteFile(hf, (LPVOID)&(pDrawBack->m_bmiHeader), sizeof(BITMAPINFOHEADER) 
// 			+ pbih->biClrUsed * sizeof (RGBQUAD), 
// 			(LPDWORD) &dwTmp, ( NULL))) 
// 		{
// 			return FALSE;
// 		}
// 
// 		// Copy the array of color indices into the .BMP file. 
// 		if (!WriteFile(hf, (LPSTR) pBuf, (s32) pbih->biSizeImage, (LPDWORD) &dwTmp,NULL)) 
// 		{
// 			return FALSE;
// 		}
// 
// 		// Close the .BMP file. 
// 		if (!CloseHandle(hf)) 
// 		{
// 			return FALSE;
// 		}
// 	}
// 	else if(byEncodeMode == PIC_ENCODE_JPEG)
// 	{
// 		if(!RGB2JPGFile(pBuf, pbih->biWidth, pbih->biHeight, (char *)lpszFileName))
// 		{
// 			return FALSE;
// 		}
// 	}
// 	return TRUE;
// }
// 
// BOOL32 CDrawWnd::PrintfPic()
// {
// 
// 	s32 nWidth = ((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth;
// 	s32 nHeight = ((TDrawBack *)m_pPriData)->m_bmiHeader.biHeight;
// 
// 	if(nWidth == 0 || nHeight == 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	CPrintDialog dlg(FALSE);
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		// Create a printer device context (DC) based on the information
// 		// selected from the Print dialog.
// 		HDC hdcPrinter = dlg.CreatePrinterDC();
// 		if (hdcPrinter == NULL)
// 		{
// 			MessageBox(_T("Buy a printer!"));
// 			return FALSE;
// 		}
// 		// Create a CDC and attach it to the default printer.
// 		CDC dcPrinter;
// 		dcPrinter.Attach(hdcPrinter);
// 
// 		// Call StartDoc() to begin printing.
// 		DOCINFO docinfo;
// 		memset(&docinfo, 0, sizeof(docinfo));
// 		docinfo.cbSize = sizeof(docinfo);
// 		docinfo.lpszDocName = _T("demonstrator");
// 
// 		// If it fails, complain and exit gracefully.
// 		if (dcPrinter.StartDoc(&docinfo) < 0)
// 		{
// 			u32 dw = GetLastError();
// 			char  szError[50];
// 			sprintf(szError, _T("Printer would not initalize:%d"), dw);
// 			MessageBox(szError);
// 			return FALSE;
// 		}
// 		// Start a page.
// 		if (dcPrinter.StartPage() < 0)
// 		{
// 			MessageBox(_T("Could not start page"));
// 			dcPrinter.AbortDoc();
// 			return FALSE;
// 		}
// 
// 		s32 xPage = GetDeviceCaps (dcPrinter, HORZRES) ;
// 		s32 yPage = GetDeviceCaps (dcPrinter, VERTRES) ;
// 
// 		if(xPage*nHeight>yPage*nWidth)
// 		{
// 			xPage = yPage*nWidth/nHeight;
// 		}
// 		else
// 		{
// 			yPage = xPage*nHeight/nWidth;
// 		}
// 
// 		EnterCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
// 		u8*  pBuf = ((TDrawBack *)m_pPriData)->m_pBuf;
// 		if(((TDrawBack *)m_pPriData)->m_pDrawBuf!= NULL)
// 			pBuf = ((TDrawBack *)m_pPriData)->m_pDrawBuf;
// 		//解压
// 		DrawDibDraw( ((TDrawBack *)m_pPriData)->m_hDrawDib, 
// 			hdcPrinter, 0, 0, 
// 			xPage, yPage,
// 			&(((TDrawBack *)m_pPriData)->m_bmiHeader),
// 			pBuf, 0, 0, 
// 			((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth,
// 			((TDrawBack *)m_pPriData)->m_bmiHeader.biHeight, 
// 			DDF_DONTDRAW );
// 		//绘图
// 		DrawDibDraw( ((TDrawBack *)m_pPriData)->m_hDrawDib, 
// 			hdcPrinter, 0, 0, 
// 			xPage, yPage,
// 			&(((TDrawBack *)m_pPriData)->m_bmiHeader),
// 			pBuf, 0, 0, 
// 			((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth,
// 			((TDrawBack *)m_pPriData)->m_bmiHeader.biHeight, 
// 			DDF_UPDATE );
// 		LeaveCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
// 
// 		dcPrinter.EndPage();
// 		dcPrinter.EndDoc();
// 	}	
// 	return TRUE;
// }
// 
// CDrawWnd message handlers

LRESULT CDrawWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

	switch(message)
	{
	case WM_PAINT:            
		{
			//是否需要刷背景图
			if(m_pPriData != NULL&& 
				((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth != 0)
			{
				EnterCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
				RECT rc;
				HDC  hDC = ::GetDC(this->m_hWnd);
				GetWindowRect(&rc);

				u8*  pBuf = ((TDrawBack *)m_pPriData)->m_pBuf;
				if(((TDrawBack *)m_pPriData)->m_pDrawBuf!= NULL)
					pBuf = ((TDrawBack *)m_pPriData)->m_pDrawBuf;

				//解压
				DrawDibDraw( ((TDrawBack *)m_pPriData)->m_hDrawDib, 
					hDC, 0, 0, 
					rc.right-rc.left, rc.bottom-rc.top,
					&(((TDrawBack *)m_pPriData)->m_bmiHeader),
					pBuf, 0, 0, 
					((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth,
					((TDrawBack *)m_pPriData)->m_bmiHeader.biHeight, 
					DDF_DONTDRAW );
				//绘图
				DrawDibDraw( ((TDrawBack *)m_pPriData)->m_hDrawDib, 
					hDC, 0, 0, 
					rc.right-rc.left, rc.bottom-rc.top,
					&(((TDrawBack *)m_pPriData)->m_bmiHeader),
					pBuf, 0, 0, 
					((TDrawBack *)m_pPriData)->m_bmiHeader.biWidth,
					((TDrawBack *)m_pPriData)->m_bmiHeader.biHeight, 
					DDF_UPDATE );
				::ReleaseDC(this->m_hWnd, hDC);
				LeaveCriticalSection(&(((TDrawBack *)m_pPriData)->m_csLock));
			}
			break;
		}
	default:break;
	}
	return CStatic::DefWindowProc(message, wParam, lParam);
}

