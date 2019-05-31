// MsgDispatch.h: interface for the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
#define AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_

#pragma warning( disable : 4786 )	// ��ʶ�����Ƴ���255�ֽ�

#include <map>
#include <vector>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;
 
class CCallBackFunBase
{ 
public:
    //����ص������ĸ�ʽ
     virtual bool operator() ( const IArgs& args ) = 0;
};

template<class T> class CMsgCallBackFun:public  CCallBackFunBase
{
public:
    //����ص������ĸ�ʽ
    typedef bool (T::*MemberFunctionType)( const IArgs& args );
    
    // �����ʱ����ҪΪ������ֵ
    CMsgCallBackFun ( MemberFunctionType pFunc, T* pObject )
    {
         m_pObject = pObject;
         m_pFuc = pFunc ;
    }
    
    virtual bool operator()( const IArgs& args )
    {
        return (m_pObject->*m_pFuc)( args);
    }
    
private:
    T* m_pObject;
    MemberFunctionType m_pFuc;	
};

 
typedef std::map< String, CCallBackFunBase* > FuncMap;
class CMsgDispatch 
{
public:
	CMsgDispatch();
	virtual ~CMsgDispatch();
/**  ע��ȫ�ֺ���
 *  @param[in] strName ��������Ӧ������ ����Ψһ
 *  @param[in] piFunc ����ָ�룬�����Ǿ�̬�����������ǳ�Ա������
 *  @return �Ƿ�ɹ�
 */
	static bool RegFunc( String strName, CCallBackFunBase* piFunc );

/**  ��ע��ȫ�ֺ���
 *  @param[in] dwMsgID ��������Ӧ����ϢID
 *  @return �Ƿ�ɹ�
 */
    static bool UnRegFunc( String strName  );
 
   

/**  ִ�к���
 *  @param[in] dwMsgID ��������Ӧ����ϢID
 *  @param[in]  
 *  @see IArgs
 *  @param[out] 
 *  @return �Ƿ�ɹ�
 */
   static bool ExeFunc( String strName, const IArgs& args );
protected:
	
    static FuncMap m_mapFuncs;
 
};
 
 



/*
* ע��ȫ�ֺ����������Ա������Ϊ����ָ�� \n
* str ������ʾ func ������ obj ��ָ�� objType ������
*/ 
#ifndef REG_MSG_HANDLER
#define REG_MSG_HANDLER( str, func, obj, objType ) \
CMsgDispatch::RegFunc( str, new CMsgCallBackFun<objType>( func, obj ) );
#endif


/*
* ��ע��ȫ�ֺ��� \n
* str ������ʾ
*/
#ifndef UN_REG_MSG_HANDLER
#define UN_REG_MSG_HANDLER( str ) CMsgDispatch::UnRegFunc( str );
#endif




#endif