#include <vfw.h>
#include "kdvtype.h"

#define MAX_VID_FRAME_WIDTH    (s32)1920//gpfan����ֱ�����չ1024->1920
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
	CDrawWnd(BOOL32 bAlloc = FALSE/*�Ƿ�Ԥ���䱳��������*/);
	
	// Attributes
public:
	
    /*
    SetFullScreen
    ��    ���� u32 nMax    :��Ļ���ָ�ɼ���
               u32 nXIndex :ˮƽ������������1��ʼ
               u32 nYIndex :��ֱ������������1��ʼ
               u32 nCombine:�ϲ��߳���1��nMax��
    */
    BOOL32 SetFullScreen();   //����ȫ��,
    BOOL32 SetFullScreen(u32 nMax, u32 nXIndex, u32 nYIndex);
    BOOL32 SetFullScreen(u32 nMax, u32 nXIndex, u32 nYIndex, u32 nCombine);
    BOOL32 CancelFullScreen();//ȡ��ȫ��
/*ע�⣺
     ����������������Ҫ���µ��ñ���������û�ͼ���ں���
	 ����������SetPlayHwnd,��������SetPreviewHwnd.
*/
    BOOL32 SetBackBitmap(u8 *pBuf, s32 nSize, PBITMAPINFOHEADER pbmiHeader);
    BOOL32 SetFrontBmp(u8 * pFrontBuf);
    BOOL32 GetPicInfo(PBITMAPINFOHEADER pbih);
    BOOL32 SaveAsPic(LPCSTR lpszFileName, u8 byEncodeMode);//ͼ�񱣴�
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
