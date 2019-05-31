// HWRecgBoard.h: interface for the CHWRecgBoard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HWRECGBOARD_H__7EA5D667_4161_45CB_995E_AE24C731FFC3__INCLUDED_)
#define AFX_HWRECGBOARD_H__7EA5D667_4161_45CB_995E_AE24C731FFC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HWRecognizeIF.h"
#include "hwdrawwnd.h"

enum EmKeyState{
	    emKeyStateNormal,
		emKeyStatePress,
		emKeyStateDisable
	};

class CHWRecgBoard  
{
public: 
    static  CHWRecgBoard*  GetSingleTon();
 
    void RedrawUI(WPARAM wParam, LPARAM lparam); 

    void  ResetInput();

    void Recognize( );
    
    void OnShowBoard();
    void OnHideBoard();

    void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
    void OnMouseMove(UINT nFlags, CPoint point);

    void ClearCandWords();//清空候选词

    virtual ~CHWRecgBoard();

    CHWDrawWnd* m_pcHWDrawWnd;

protected:

    void OnClickHide();
    void OnClick2KEYBOARD();
    void OnClickDel();
    void OnClickSpace();
    void OnClickEnter();
	void OnClickPrevPg();
	void OnClickNextPg();

protected:
	CHWRecgBoard();
   
    void Init();

     void DrawFont( Graphics *pGraphics, CRect& cRect, CString strText );


    typedef   VOID (CHWRecgBoard::*OnCommonClick) ( VOID );

 


    void AddCommonKey(  CString strImgPath, CRect& prcKey ,
                                         BOOL bIsKeyPress  = FALSE , OnCommonClick click  = NULL );

	
    //   typedef   VOID (CHWRecgBoard::*OnRecgClick) ( CString strTxt); 
    void  AddRecgKey( CRect& prcKey, CString str = "" ) ;
 

   
    //进行识别 把识别结果输出到UI
    void  UpdateRecognizeUI(  ) ;

    

    //当选择了一个候选词之后
    void  OnSelCand( CString strCand );

private:
    //控件位置大小分辨率子适应
    void BoardRectAdp();

private:
    BOOL32 m_bBeginWrite;
    static CHWRecgBoard * m_pThis;

    Image *m_pImgeBK;  
    
    CHWRecognizeIF  m_cRecognize;
    vector<CString> m_vcCandWords;         //所有候选词
	int            m_swCurrPgIndex;   //当前页的候选词
    int            m_swOnePgCount;    // 一页显示的候选词个数
    
    CRect m_rcHwDrawWnd;  //手写窗口的rect
    CRect m_rcCandidateWnd; //候选词窗口 
	CPoint m_ptLbtDown;     //button down 的状态
	CPoint m_ptMouseMove;   //上一次鼠标的位置
    struct TRecgKey 
    {
        CString strTxt;
        CRect rcKey;
       // OnRecgClick  pOnClickFun;  
        
        TRecgKey()
        {
            rcKey.left = 0;
            rcKey.right = 0;
            rcKey.bottom = 0;
            rcKey.top = 0; 
            strTxt = ""; 
        //    pOnClickFun = NULL;
        }
    };
    
 
   
    
    struct TCommonKey
    {  
        CRect rcKey;
        EmKeyState emKeyState;
        CString strImgPath;  //贴图文件夹，去相对路径 
        
        OnCommonClick  pOnClickFun;  
        
        TCommonKey()
        {
            rcKey.left = 0;
            rcKey.right = 0;
            rcKey.bottom = 0;
            rcKey.top = 0;
            pOnClickFun = NULL;
            strImgPath = ""; 
            emKeyState = emKeyStateNormal; 
        }
    };


    CTypedPtrList<CPtrList, TCommonKey*> m_cCommonKeys;       //功能键
    CTypedPtrList<CPtrList, TRecgKey*> m_cRecgsKeys;    //识别键

	TCommonKey* m_pPrevPgKey;
	TCommonKey* m_pNextPgKey;

   
    BOOL m_bSwitchImm;    /*是否需要切换输入法 （手写界面的输入法必须为英文，
     如果切到手写界面时 的 输入法为中文，则需要切到英文，此时m_bSwitchImm= true ，再次切换到软键盘时需要再切回中文）*/
   
};

#endif // !defined(AFX_HWRECGBOARD_H__7EA5D667_4161_45CB_995E_AE24C731FFC3__INCLUDED_)
