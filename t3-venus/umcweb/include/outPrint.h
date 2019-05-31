// outPrint.h: interface for the COutPrint class.
//�����telnet��ӡ�����ڲ�ѯ�����и������ݺ�״̬
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
	static void GetAllTpl();   //��ʾ���л���ģ��
	static void GetAllGlobalAddr();
	static void GetAllLocalAddr();

	/** ��CAddrEntry�����赽TAddrInfo��
	 *  @param[out] tAddrInfo  ��ַ��Ŀ��Ϣ
	 *  @param[in]  cAddrEntry ��ַ����Ŀ��Ϣ
	 *  @return 
	 */
	static void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );
private:
	static CConfCtrlIF* m_pconfCtrlIF;
	static CConfTemplateCtrlIF* m_pTmpConfigIF;    //ģ����ƽӿ� 
	static CUmsConfigCtrlIF *m_pUmsConfig;
	static CCncAddrbookIF *m_pCncAddrBook;
	static COutPrint* m_pOutPrint;
};

#define BUILDOUTPRINTPTR COutPrint::GetOutPrintPtr()

#endif // !defined(AFX_OUTPRINT_H__35BE1928_2B94_4016_8716_06427941EBA4__INCLUDED_)
