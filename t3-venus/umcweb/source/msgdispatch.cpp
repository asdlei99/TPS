// MsgDispatch.cpp: implementation of the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MsgDispatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


FuncMap CMsgDispatch::m_mapFuncs  ;

CMsgDispatch::CMsgDispatch() 
{

}

CMsgDispatch::~CMsgDispatch()
{

}

bool CMsgDispatch::UnRegFunc( String strName )
{
	FuncMap::iterator itr =	m_mapFuncs.find( strName );
	if ( itr != m_mapFuncs.end() )
	{
		delete itr->second;
		itr->second = 0;
		m_mapFuncs.erase( itr );
		//LOGEVENT( "CFuncManage::UnRegFunc 成功注销掉函数 name = " + strName );
		
		String strWarning = "CFuncManage::UnRegFunc 成功注销掉函数 name = ";
		strWarning += strName;
		
		return true;
	}
	//LOGEVENT( "CFuncManage::UnRegFunc 未找到对应函数 name = " + strName );
	
	return false;
}



bool CMsgDispatch::RegFunc( String strName, CCallBackFunBase* piFunc )
{
	FuncMap::iterator itr =	m_mapFuncs.find( strName );
	if ( itr != m_mapFuncs.end() )
	{
		//LOGEVENT( "CFuncManage::RegFunc 该处理函数已经存在 name = " + strName );
		if ( piFunc != itr->second )
		{
			delete itr->second;
			itr->second = piFunc;
			return true;
		}
		else
		{
			return false;
		}
	}

	m_mapFuncs.insert( FuncMap::value_type( strName, piFunc ) );
	//LOGEVENT( "CFuncManage::RegFunc 成功注册函数 name = " + strName );
	
	return true;
}


bool CMsgDispatch::ExeFunc( String strName, const IArgs& args )
{
	FuncMap::iterator itr = m_mapFuncs.find( strName );
	if ( itr == m_mapFuncs.end() )
	{
		return false;
	}
	(*itr->second)( args );
	return false;
}

  




 