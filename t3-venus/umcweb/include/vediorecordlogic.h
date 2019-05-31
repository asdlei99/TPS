/*****************************************************************************
模块名      : CVedioRecordLogic
文件名      : vediorecordlogic.h
相关文件    : 
文件实现功能: 录像机会议录像页面
作者        : 石城
版本        : V2.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/08      2.0         石城      创建
******************************************************************************/
#if !defined(AFX_VEDIORECORDLOGIC_H__C0283CA9_F852_43D6_8B8E_E8869E7633DE__INCLUDED_)
#define AFX_VEDIORECORDLOGIC_H__C0283CA9_F852_43D6_8B8E_E8869E7633DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// vediorecordlogic.h : header file
//

#include "videorecordeplogic.h"
#include "vediorecordnameeditlogic.h"


enum EmChildWndType
{
	em_Wnd_Record_Cfg = 0,
	em_Wnd_Conf_Type,
	em_Wnd_Show_Type,
	em_Wnd_play_choose,
	em_Wnd_Room,
	em_Wnd_Init,
	em_Wnd_NoVtr,
	em_Wnd_No_Show			
};

enum EmClickType
{
	emClickListItem = 0,
	emClickBtnBack
};

//当前窗口的类型
enum EmCurrentWnd
{
	emCurrentWndConfTyye = 0,
	emCurrentWndShowTyye,
	emCurrentWndPlayTyye,
	emCurrentWndMain,
	emCurrentWndEp,
	emBackTypeEnd
};

//方案的类型
enum EmScheme
{
	emSchmeControlBtn = 0,
	emSchmeEnd
};

//会议状态
enum EmMeetState
{
	emMeetStateRec = 0,		//会议正在录像
	emMeetStateRecMt,		//会场正在录像
	emMeetStatePlay,		//会议正在放像
	emMeetStateEnd
};

enum EmConfType
{
	emConfAdd = 0,
	emConfCnsChange,
	emConfDel,		
};


/////////////////////////////////////////////////////////////////////////////
// CVedioRecordLogic dialog

class CVedioRecordLogic : public CDlgChild
{
// Construction
public:
	CVedioRecordLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVedioRecordLogic)
	enum { IDD = IDD_DIALOG_VIDEORECORD };
	CTransparentBtn	m_btnRecordResume;
	CTransparentBtn	m_btnPlayResume;
	CTransparentStatic	m_stcPlayProgress;
	CTransparentEdit	m_edtSearchPlay;
	CTransparentCheckButton m_radiobtnHP1080P60fpsShow;
	CTransparentCheckButton m_radiobtnHP1080P50fpsShow;
	CTransparentCheckButton m_radiobtnHP1080P30fpsShow;
	CTransparentCheckButton m_radiobtnHP1080P25fpsShow;
	CTransparentCheckButton m_radiobtnHP720P60fpsShow;
	CTransparentCheckButton m_radiobtnHP720P50fpsShow;
	CTransparentCheckButton m_radiobtnHP720P30fpsShow;
	CTransparentCheckButton m_radiobtnHP720P25fpsShow;
	CTransparentCheckButton m_radiobtnBP1080P60fpsShow;
	CTransparentCheckButton m_radiobtnBP1080P50fpsShow;
	CTransparentCheckButton m_radiobtnBP1080P30fpsShow;
	CTransparentCheckButton m_radiobtnBP1080P25fpsShow;
	CTransparentCheckButton m_radiobtnBP720P60fpsShow;
	CTransparentCheckButton m_radiobtnBP720P50fpsShow;
	CTransparentCheckButton m_radiobtnBP720P30fpsShow;
	CTransparentCheckButton m_radiobtnBP720P25fpsShow;
	CTransparentCheckButton m_radiobtnBP4CIF25fpsShow;
	CTransparentCheckButton m_radiobtnBPUXGA60fpsShow;
	CTransparentCheckButton m_radiobtnBPWXGA30fpsShow;
	CTransparentCheckButton m_radiobtnBPSXGA30fpsShow;
	CTransparentCheckButton m_radiobtnBPWXGA5fpsShow;
	CTransparentCheckButton m_radiobtnBPSXGA5fpsShow;
	CTransparentCheckButton m_radiobtnBPXGA5fpsShow;
	CTransparentCheckButton m_radiobtnHP1080P60fps;
	CTransparentCheckButton m_radiobtnHP1080P50fps;
	CTransparentCheckButton m_radiobtnHP1080P30fps;
	CTransparentCheckButton m_radiobtnHP1080P25fps;
	CTransparentCheckButton m_radiobtnHP720P60fps;
	CTransparentCheckButton m_radiobtnHP720P50fps;
	CTransparentCheckButton m_radiobtnHP720P30fps;
	CTransparentCheckButton m_radiobtnHP720P25fps;
	CTransparentCheckButton m_radiobtnBP1080P60fps;
	CTransparentCheckButton m_radiobtnBP1080P50fps;
	CTransparentCheckButton m_radiobtnBP1080P30fps;
	CTransparentCheckButton m_radiobtnBP1080P25fps;
	CTransparentCheckButton m_radiobtnBP720P60fps;
	CTransparentCheckButton m_radiobtnBP720P50fps;
	CTransparentCheckButton m_radiobtnBP720P30fps;
	CTransparentCheckButton m_radiobtnBP720P25fps;
	CTransparentCheckButton m_radiobtnBP4CIF25fps;
	CTransparentBtn	m_btnPlayStart;
	CTransparentStatic	m_stcPlay;
	CTransparentStatic	m_stcH264;
	CTransparentEdit	m_edtPlayChoose;
	CTransparentSwitchButton	m_btnPlaySwitch;
	CTransparentBtn	m_btnPlayStop;
	CTransparentBtn	m_btnPlayFinish;
	CTransparentBtn	m_btnPlayChoose;
	CTransparentBtn	m_btnChildBack;
	CTransparentBtn	m_btnRecordStart;
	CTransparentBtn	m_btnRecordFinish;
	CTransparentBtn	m_btnRecordStop;
	CTransparentStatic	m_stcRecordTimeReal;
	CTransparentStatic	m_stcRecordTime;
	CTransparentBtn	m_btnShowType;
	CTransparentBtn	m_btnConfType;
	CTransparentEdit	m_edtShowType;
	CTransparentEdit	m_edtConfType;
	CTransparentStatic	m_stcShowType;
	CTransparentStatic	m_stcConfType;
	CTransparentSwitchButton	m_btnSwitch;
	CTransparentStatic	m_stcDoubleCurrent;
	CTransparentBtn	m_btnReturn;
	CTransparentEdit	m_sedtSearch;
 	CTransparentStatic	m_stcChildWndTitle;
 	CTransparentStatic	m_stcChildFrmRight;
 	CTransparentStatic	m_stcChildFrmLeft;
 	CTransparentStatic	m_stcTitle;
	CTransparentSwitchButton	m_btnShowEx;
	CTransparentStatic m_stcRecFileName;
	CTransparentStatic m_stcRecFileNameReal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVedioRecordLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVedioRecordLogic)
	afx_msg void OnDestroy();
	afx_msg LRESULT OnRecFileListInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecConfRecInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecConfPlayInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRefreshConfCnsList( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRefreshConfListNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStartConfRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStopRecordRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecPauseRecordRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecResumeRecordRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStartPlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStopPlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecResumePlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecPausePlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnTimer( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnHideOptn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnShowOptNty( WPARAM wParam, LPARAM lParam );
	afx_msg void OnButtonRecordReturn();
	afx_msg void OnButtonVtrRecordStart();
	afx_msg void OnButtonVtrRecordStop();
	afx_msg void OnButtonVtrRecordFinish();
	afx_msg void OnButtonConfType();
	afx_msg void OnButtonShowType();
	afx_msg void OnButtonChildBack();

	afx_msg void OnBUTTONCONFHP1080P60fps();
	afx_msg void OnBUTTONCONFHP1080P50fps();
	afx_msg void OnBUTTONCONFHP1080P30fps();
	afx_msg void OnBUTTONCONFHP1080P25fps();
	afx_msg void OnBUTTONCONFHP720P60fps();
	afx_msg void OnBUTTONCONFHP720P50fps();
	afx_msg void OnBUTTONCONFHP720P30fps();
	afx_msg void OnBUTTONCONFHP720P25fps();
	afx_msg void OnBUTTONCONFBP1080P60fps();
	afx_msg void OnBUTTONCONFBP1080P50fps();
	afx_msg void OnBUTTONCONFBP1080P30fps();
	afx_msg void OnBUTTONCONFBP1080P25fps();
	afx_msg void OnBUTTONCONFBP720P60fps();
	afx_msg void OnBUTTONCONFBP720P50fps();
	afx_msg void OnBUTTONCONFBP720P30fps();
	afx_msg void OnBUTTONCONFBP720P25fps();
	afx_msg void OnBUTTONCONFBP4CIF25fps();

	afx_msg void OnBUTTONSHOWHP1080P60fps();
	afx_msg void OnBUTTONSHOWHP1080P50fps();
	afx_msg void OnBUTTONSHOWHP1080P30fps();
	afx_msg void OnBUTTONSHOWHP1080P25fps();
	afx_msg void OnBUTTONSHOWHP720P60fps();
	afx_msg void OnBUTTONSHOWHP720P50fps();
	afx_msg void OnBUTTONSHOWHP720P30fps();
	afx_msg void OnBUTTONSHOWHP720P25fps();
	afx_msg void OnBUTTONSHOWBP1080P60fps();
	afx_msg void OnBUTTONSHOWBP1080P50fps();
	afx_msg void OnBUTTONSHOWBP1080P30fps();
	afx_msg void OnBUTTONSHOWBP1080P25fps();
	afx_msg void OnBUTTONSHOWBP720P60fps();
	afx_msg void OnBUTTONSHOWBP720P50fps();
	afx_msg void OnBUTTONSHOWBP720P30fps();
	afx_msg void OnBUTTONSHOWBP720P25fps();
	afx_msg void OnBUTTONSHOWBP4CIF25fps();
	afx_msg void OnBUTTONSHOWBPUXGA60fps();
	afx_msg void OnBUTTONSHOWBPWXGA30fps();
	afx_msg void OnBUTTONSHOWBPSXGA30fps();
	afx_msg void OnBUTTONSHOWBPWXGA5fps();
	afx_msg void OnBUTTONSHOWBPSXGA5fps();
	afx_msg void OnBUTTONSHOWBPXGA5fps();

	afx_msg LRESULT OnButtonSwitch( WPARAM wParam, LPARAM lParam );
	afx_msg void OnButtonVtrPalybackStart();
	afx_msg void OnButtonPlayChoose();
	afx_msg LRESULT OnUpdateEDITSearch( WPARAM wParam, LPARAM lParam );
	afx_msg void OnButtonPlaySwitch();
	afx_msg void OnButtonVtrPalybackResume();
	afx_msg void OnButtonVtrRecordResume();
	afx_msg void OnButtonPlayFinish();
	afx_msg void OnButtonPlayPause();	
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVtrRegStateNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecMdyFileRsp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditSetFocus( WPARAM wparam, LPARAM lparam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
    函 数 名:InitControlPane
    功    能:初始化页面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/4/7    1.0     石城      创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    函 数 名:RegisterFun
    功    能:List点击函数注册
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/4/8    1.0     石城      创建
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    函 数 名:InitDlg
    功    能:页面销毁抢断后初始化
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/04/08  1.0     石城      创建
    =============================================================================*/
    void InitDlg();

	void ShowChildWnd( EmChildWndType emChildWndType );

	//当前选中条目状态
	EmMeetState SelItemState();

protected:
	bool OnClickConfListItem( const IArgs & arg );
	bool OnClickConfListItemIcon( const IArgs & arg );
	bool OnClickVedioFileLstItem( const IArgs & arg );
	bool OnClickVedioFileLstItemIcon( const IArgs & arg );
	
	

private:
	/*=============================================================================
    函 数 名:InitChildWindow
    功    能:初始化子窗口视图
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/08  1.0     石城		创建
    =============================================================================*/
	BOOL InitChildWindow();

	//0:非录像放像消息调用	1:录像消息调用	2:放像消息调用
	void RefreshRecList( int nRefresh = 0, int nConfID = 0 );
	
	void ShowOptEx();

	//bAdd:是否添加	 nConfID:会议号
	void RefreshConfList( EmConfType emType, int nConfID );

	//m_vecTUmcConfInfoSearch中查找m_tUmcConfInfoSel
	TUmcConfInfo* FindConfInfoSel();

	//m_vecTUmcConfInfoSearch中查找m_tUmcConfInfoSel中的会议录像信息
	TConRecState* GetRecConfInfoInVec();

	TConRecState* GetRecConfInfoInSel();
	
	

	void SetConfInfo();
	void SetConfType();
	void SetShowType();

	void SetPlayInfo();
	void SetConfTypeToWndRecordCfg();
	void SetShowTypeToWndRecordType();
	void SetPlayChooseToWndPlayChoose();
	void SetPlayChooseToWndRecordType();
	void ShowAllConfType();
	void ShowAllShowType();
	void RefreshRecFileList();

	void ShowTip( EmUseReccorderRes emRes );
	void SetConfAndPlayInfo();

	void LoadScheme( EmScheme emScheme );

	//显示选中条目
	void ShowSelItem();	

	//开始放像时检查放像格式
	BOOL CheckPalyFormat( TUmsVidFormat tConfFormat, BOOL bDual, TUmsVidFormat tDualFormat );

	//检查格式(tUmsVidFormat是否包含tUmsVidFormatChecked)
	BOOL CheckFormat( TUmsVidFormat tUmsVidFormat, TUmsVidFormat tUmsVidFormatChecked );
	
	
public:
	TUmcConfInfo m_tUmcConfInfoSel;
	EmCurrentWnd m_emCurrentWnd;									//点击BtnBackChild的类型

	CVideoRecordEpLogic *m_pVideoRecordEpLogic;				//会场Dlg

private:
	CListChild* m_pListMeeting;
	CLetterIndex* m_pLetterIndex;
	CTransparentProgress* m_pProgressPlay;

	//---umslib控制接口 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;
	CConfCtrlIF* m_pconfCtrlIF;

	

	CListChild* m_pListVedioFile;

	vector<TUmcConfInfo> m_vecTUmcConfInfo;						//会议录像信息
	vector<TUmcConfInfo> m_vecTUmcConfInfoSearch;				//会议录像信息(搜索后)

	CVedioRecordNameEditLogic *m_pCVedioRecordNameEditLogic;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEDIORECORDLOGIC_H__C0283CA9_F852_43D6_8B8E_E8869E7633DE__INCLUDED_)
