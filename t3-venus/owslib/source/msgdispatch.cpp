#include "owslib.h"
#include "msgdispatch.h"

CFuncManage::CFuncManage()
{
	
}

CFuncManage::~CFuncManage()
{
	UnRegAllFunc();
}

bool CFuncManage::UnRegFunc( std::string strName )
{
	FuncMap::iterator itr =	m_mapFuncs.find( strName );
	if ( itr != m_mapFuncs.end() )
	{
		delete itr->second;
		itr->second = 0;
		m_mapFuncs.erase( itr );
		return true;
	}
	return false;
}

bool CFuncManage::RegFunc( std::string strName, ICallBackFuncBase* piFunc )
{
	FuncMap::iterator itr =	m_mapFuncs.find( strName );
	if ( itr != m_mapFuncs.end() )
	{
		return false;
	}
	m_mapFuncs.insert( FuncMap::value_type( strName, piFunc ) );
	return true;
}

bool CFuncManage::ExeFunc( std::string strName, const IArgs& args )
{
	FuncMap::iterator itr = m_mapFuncs.find( strName );
	if ( itr == m_mapFuncs.end() )
	{
		return false;
	}
	(*itr->second)( args );
	return false;
}


void CFuncManage::UnRegAllFunc()
{
	FuncMap::iterator itr = m_mapFuncs.begin();
	while( itr != m_mapFuncs.end() )
	{
		delete itr->second;
		itr->second = 0;
		m_mapFuncs.erase( itr );
		itr = m_mapFuncs.begin();
	}
	
}