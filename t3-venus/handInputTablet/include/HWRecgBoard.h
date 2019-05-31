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

    void ClearCandWords();//��պ�ѡ��

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
 

   
    //����ʶ�� ��ʶ���������UI
    void  UpdateRecognizeUI(  ) ;

    

    //��ѡ����һ����ѡ��֮��
    void  OnSelCand( CString strCand );

private:
    //�ؼ�λ�ô�С�ֱ�������Ӧ
    void BoardRectAdp();

private:
    BOOL32 m_bBeginWrite;
    static CHWRecgBoard * m_pThis;

    Image *m_pImgeBK;  
    
    CHWRecognizeIF  m_cRecognize;
    vector<CString> m_vcCandWords;         //���к�ѡ��
	int            m_swCurrPgIndex;   //��ǰҳ�ĺ�ѡ��
    int            m_swOnePgCount;    // һҳ��ʾ�ĺ�ѡ�ʸ���
    
    CRect m_rcHwDrawWnd;  //��д���ڵ�rect
    CRect m_rcCandidateWnd; //��ѡ�ʴ��� 
	CPoint m_ptLbtDown;     //button down ��״̬
	CPoint m_ptMouseMove;   //��һ������λ��
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
        CString strImgPath;  //��ͼ�ļ��У�ȥ���·�� 
        
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


    CTypedPtrList<CPtrList, TCommonKey*> m_cCommonKeys;       //���ܼ�
    CTypedPtrList<CPtrList, TRecgKey*> m_cRecgsKeys;    //ʶ���

	TCommonKey* m_pPrevPgKey;
	TCommonKey* m_pNextPgKey;

   
    BOOL m_bSwitchImm;    /*�Ƿ���Ҫ�л����뷨 ����д��������뷨����ΪӢ�ģ�
     ����е���д����ʱ �� ���뷨Ϊ���ģ�����Ҫ�е�Ӣ�ģ���ʱm_bSwitchImm= true ���ٴ��л��������ʱ��Ҫ���л����ģ�*/
   
};

#endif // !defined(AFX_HWRECGBOARD_H__7EA5D667_4161_45CB_995E_AE24C731FFC3__INCLUDED_)
