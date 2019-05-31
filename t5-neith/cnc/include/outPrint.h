// outPrint.h: interface for the COutPrint class.
//输出到telnet打印，用于查询界面中各种数据和状态
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPRINT_H__35BE1928_2B94_4016_8716_06427941EBA4__INCLUDED_)
#define AFX_OUTPRINT_H__35BE1928_2B94_4016_8716_06427941EBA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COutPrint  
{
public:
	COutPrint();
	virtual ~COutPrint();
public:
    static void GetAllConfInfo();
    static void GetConfInfo( u16 wConfID );
    static void GetConfCnsInfo( u16 wCnsID );
    static void GetConfCnsInfo();
    static void GetLocalCnsInfo();
    static void IsLocalCnsInConf();
    static void GetConfInfoByID( u16 wConfID );
    static void ShowConfTemp( u16 wID );
    static void ShowScrnInfo();
    static void ShowAllUseInfo();
    static void ShowLocalIP();
    static void SetDecVol( u8 abyVol );
    static void ShowDecVol();
    static void ShowAlarmInfoLst();
    static void ShowAddrbook();
	static void ShowOnlineAddr();
    static void ShowAddrEntry( u32 dwEntryIndex );
    static void DeleteAddr( u32 dwEntryIndex );
    static void ShowVmpInfo();
	static void ShowPollList();
	static void GetCncBuildVersion(s8 achVersion[MAX_DEVICEVER_LEN]);
};

#endif // !defined(AFX_OUTPRINT_H__35BE1928_2B94_4016_8716_06427941EBA4__INCLUDED_)
