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
	static COutPrint* GetOutPrintPtr();
	static void Clean();
    static void GetAllConfInfo();
    static void GetConfInfo( u16 wConfID );
	static void GetAllTpl();   //显示所有会议模板
	static void GetAllGlobalAddr();
	static void GetAllLocalAddr();

	/** 将CAddrEntry数据设到TAddrInfo中
	 *  @param[out] tAddrInfo  地址条目信息
	 *  @param[in]  cAddrEntry 地址簿条目信息
	 *  @return 
	 */
	static void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );
private:
	static CConfCtrlIF* m_pconfCtrlIF;
	static CConfTemplateCtrlIF* m_pTmpConfigIF;    //模板控制接口 
	static CUmsConfigCtrlIF *m_pUmsConfig;
	static CCncAddrbookIF *m_pCncAddrBook;
	static COutPrint* m_pOutPrint;
};

#define BUILDOUTPRINTPTR COutPrint::GetOutPrintPtr()

#endif // !defined(AFX_OUTPRINT_H__35BE1928_2B94_4016_8716_06427941EBA4__INCLUDED_)
