#include <vfw.h>
#include "kdvtype.h"

#define MAX_VID_FRAME_WIDTH    (s32)1920//gpfan高清分辨率扩展1024->1920
#define MAX_VID_FRAME_HEIGHT   (s32)1088// gpfan               768->1080


typedef struct 
{
	CRITICAL_SECTION m_csLock;
	u8*             m_pBuf;
	s32            m_nSize;
	BITMAPINFOHEADER m_bmiHeader;
	HDRAWDIB         m_hDrawDib;

	u8*             m_pDrawBuf;

}TDrawBack;

#ifdef SOFT_CODEC
class CDrawWnd : public CStatic
{
	DECLARE_DYNAMIC(CDrawWnd)
public:
	CDrawWnd(BOOL32 bAlloc = FALSE/*是否预分配背景进缓冲*/);
	
	// Attributes
public:
	
    /*
    SetFullScreen
    参    数： u32 nMax    :屏幕被分割成几份
               u32 nXIndex :水平方向索引，从1开始
               u32 nYIndex :垂直方向索引，从1开始
               u32 nCombine:合并边长（1～nMax）
    */
    BOOL32 SetFullScreen();   //设置全屏,
    BOOL32 SetFullScreen(u32 nMax, u32 nXIndex, u32 nYIndex);
    BOOL32 SetFullScreen(u32 nMax, u32 nXIndex, u32 nYIndex, u32 nCombine);
    BOOL32 CancelFullScreen();//取消全屏
/*注意：
     调用这两个函数后要重新调用编解码器设置画图窗口函数
	 解码器的是SetPlayHwnd,编码器是SetPreviewHwnd.
*/
    BOOL32 SetBackBitmap(u8 *pBuf, s32 nSize, PBITMAPINFOHEADER pbmiHeader);
    BOOL32 SetFrontBmp(u8 * pFrontBuf);
    BOOL32 GetPicInfo(PBITMAPINFOHEADER pbih);
    BOOL32 SaveAsPic(LPCSTR lpszFileName, u8 byEncodeMode);//图像保存
    BOOL32 PrintfPic();
public:
    RECT m_rtPos;
	HWND m_hParentWnd;
	BOOL32 m_bFullScreen;
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawWnd)
public:
	virtual BOOL32 Create(LPCTSTR lpszWindowName, UINT dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=0xffff, CCreateContext* pContext = NULL);
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
private:
    void *m_pPriData;
public:
	virtual ~CDrawWnd();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawWnd)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};
#endif
