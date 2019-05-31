// PubFunc.cpp: implementation of the CPubFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umcwebproj.h"
#include "PubFunc.h"

#include "tpmsginit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUmsSessionCtrlIF *CPubFunc::m_pUmsSession = NULL;
CPubFunc* CPubFunc::m_pThis = NULL;
CPubFunc::CPubFunc()
{   
//	InitTpEvent();  
	CreateUmsSession( &m_pUmsSession ); 

	//ÏòOSP×¢²á±¾Ä£¿é
	ModuleRegToOsp();

	DWORD dwProcessId = GetCurrentProcessId();
	TCHAR aszPrompt[32] = "";
	
	sprintf( aszPrompt, "umcweb(%d):", dwProcessId );
	OspSetPrompt( aszPrompt );
}

CPubFunc::~CPubFunc()
{
	//SAFE_RELEASE(m_pThis);

	if ( NULL!= m_pUmsSession )
	{
		DesdoryUmsSession(&m_pUmsSession);
		m_pUmsSession=NULL;
	} 
}

CUmsSessionCtrlIF* CPubFunc::GetUmsSesstionPtr()
{
	if ( m_pThis == NULL )
	{
		m_pThis = new CPubFunc();
	} 
	return m_pThis->m_pUmsSession;
}

void CPubFunc::UmsSessionDestory()
{	
	if ( NULL!= m_pUmsSession )
	{
		DesdoryUmsSession(&m_pUmsSession);
		m_pUmsSession=NULL;
	} 

	SAFE_RELEASE(m_pThis);
}
