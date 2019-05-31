// FocusTestDlg.h : header file
//

#if !defined(AFX_FOCUSTESTDLG_H__EFE558FB_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_)
#define AFX_FOCUSTESTDLG_H__EFE558FB_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSoftKeyboardDlg dialog



struct KEYDEF
{
	char cNormal;
	char cShifted;
	int cWidth;
	CRect rcKey;
	BOOL bIsKeyPress;
    CString strImgPath;  //��ͼ�ļ��У�ȥ���·�� 
	
};
 
 
class CSoftKeyboardDlg  
{
// Construction
public:	
	static CSoftKeyboardDlg* GetSingleTon();
 
    void OnShowBoard( HWND hTagWnd );
    void OnHideBoard();

    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);

    void RedrawUI(WPARAM wParam, LPARAM lparam); 

      

    void UpdateImm( ) ;

	~CSoftKeyboardDlg();



    void IME_Chs2Eng(); 
    //�жϵ�ǰ���뷨�Ƿ������ĵ�
    BOOL32 IsChineseIM();
private:
    CSoftKeyboardDlg( );	// standard constructor
	 
    BOOL Init(); 
 
    void AddKey(
        char pNormal,
        char pShifted,
        CString strImgPath,
        CRect &prcKey ,
		BOOL bIsKeyPress = FALSE);


	void SendKey(KEYDEF * key); 


    VOID keybd_event( BYTE bVk, BYTE bScan, DWORD dwFlags, DWORD dwExtraInfo, BOOL32 bScreenEvent = TRUE )
    {
        
        ::keybd_event(bVk, bScan, dwFlags, dwExtraInfo ); 
       // g_bIsScreenEvent = bScreenEvent;
    }
  
    int DescribeKeyState(); 

    KEYDEF*  FindKey( char cNormal );


	 
	
    BOOL32 IsCapsLock(); 
    
	BOOL32 IsSuperKey( KEYDEF* key );  
  
    //���ú�ѡ�ʴ���λ�ã�ʼ����������Ϸ�
    void SetCandidateWndPos();
 
    void KeyRectAdp();//����rect�ķֱ�������Ӧ

    
public: 
 
    CTypedPtrList<CPtrList, KEYDEF*> cKeys;

	Image *m_pImgeBK;
 
	BOOL32  m_bIsInKeyRect;

    BOOL32  m_bCapture; 
    
    BOOL32	m_bHitCaption;
    CPoint	m_ptOffset;
    HWND	m_hTagWnd; 
	BOOL32  m_bCapsLock;

    BOOL32 m_bWillUpdateCapsLock ;


    static CSoftKeyboardDlg* m_pMainKeyBoard ;
  
   BOOL32  m_bImmEn;//�Ƿ���Ӣ�����뷨
   BOOL32  m_bDownCap;

   
  
};






//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSTESTDLG_H__EFE558FB_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_)
