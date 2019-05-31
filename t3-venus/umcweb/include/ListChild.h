// ListChild.h: interface for the CListChild class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCHILD_H__75DCCA6C_1E75_4FB5_8711_DD702F971697__INCLUDED_)
#define AFX_LISTCHILD_H__75DCCA6C_1E75_4FB5_8711_DD702F971697__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListChild :public CTransparentList
{
public:
	CListChild( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, CString strUI = "", UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CListChild();

	void SetData( const IValue& value );

	virtual void Clicked( UINT nFlags, CPoint point );

 	static CString FirstLetter(int nCode);
 	static void GetFirstLetter(CString strName, CString& strFirstLetter);
 
// 	//排序算法
 	static bool AddrItemCompare(TAddrItem &tItem1, TAddrItem& tItem2);
 	static bool CnsInfoCompare(TCnsInfo& tInfo1, TCnsInfo& tInfo2);
 	static bool TPCnsInfoCompare(TTPCnsInfo& tInfo1, TTPCnsInfo& tInfo2);
    static bool TempCnsCompare( TEpAddr &tCns1, TEpAddr &tCns2 );
    static bool ConfTempCompare( TTPAlias& tAlias1, TTPAlias& tAlias2 );
	static bool OrderConfTempCompare( TTPConfTemplate& tTmpName1, TTPConfTemplate& tTmpName2 );
	static bool ConfTemplateCompare( vector<TCMSConfTemplate>* pAryConfTemplate, BOOL bAscend = TRUE );
	static bool CurConfCompare( TCMSConf& tConfName1, TCMSConf& tConfName2 );
 	
	static bool UserItemCompare(CUserFullInfo& tItem1, CUserFullInfo& tItem2);
    static bool ConfMenuCompare(TConfMenuInfo& tItem1, TConfMenuInfo& tItem2);

	static bool VtrFileListItemCompare(TRecFileInfo &tItem1, TRecFileInfo& tItem2);

	static bool RecConfCompare(TUmcConfInfo& tItem1, TUmcConfInfo& tItem2);
	static bool RecMtCompare(TUmcRecInfo& tItem1, TUmcRecInfo& tItem2);
protected:
	LRESULT OnLetterClick( WPARAM wParam, LPARAM lParam );	
	
	DECLARE_MESSAGE_MAP()
};

//用于获取二级汉字首字母拼音
class CPYChar  
{
public:
    CPYChar();
    virtual ~CPYChar();
    static BOOL In(int Lp, int Hp,int Value);
    char GetPYChar(CString HZ) ;
    static char GetPYChar(TCHAR c1,TCHAR c2); 
    static CString m_ArrQWSecond[32];   //区位码字母头: 56区~87区对应0~30
};


class CViewList : public CTransparentViewList
{
public:
    CViewList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
        DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CViewList();

    void SetData( const IValue& value );

    virtual void Clicked( UINT nFlags, CPoint point );
};


#endif // !defined(AFX_LISTCHILD_H__75DCCA6C_1E75_4FB5_8711_DD702F971697__INCLUDED_)
