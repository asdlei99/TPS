#ifndef _MSGDISPATCH_H
#define _MSGDISPATCH_H

//////////////////////////////////////////////////////////////////////////
// 消息分发类，主要用于向各个业务类注册的请求消息分发

class IArgs
{
public:
	IArgs( std::string strType ) : m_strType( strType ){}
	virtual ~IArgs(){}
	std::string GetType() const { return m_strType; } 
protected:
	std::string m_strType;
};

/*---------------------------------------------------------------------
* 类	名：ICallBackFuncBase
* 功    能：回调函数接口
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class ICallBackFuncBase
{
public:
	virtual ~ICallBackFuncBase(){}
	virtual bool operator()( const IArgs& args ) = 0;
};

/*---------------------------------------------------------------------
* 类	名：CMemberCallBackFunc
* 功    能：为成员函数定义的回调函数
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
template<class T> class CMemberCallBackFunc : public ICallBackFuncBase
{
public:
    //定义回调函数的格式
    typedef bool (T::*MemberFunctionType)( const IArgs& args );
	
	// 构造的时候需要为函数赋值
    CMemberCallBackFunc( MemberFunctionType pFunc, T* pObject ) : m_pObject(pObject), m_pFuc( pFunc ) {}
	
    virtual bool operator()( const IArgs& args )
    {
        return (m_pObject->*m_pFuc)( args );
    }
	
private:
	T* m_pObject;
    MemberFunctionType m_pFuc;	
};

/*---------------------------------------------------------------------
* 类	名：CMemberCallBackFunc
* 功    能：为成员函数定义的回调函数
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CCallBackFunc : public ICallBackFuncBase
{
public:
	virtual bool operator()( const IArgs& args)
	{
		return m_pFuc(args);
	}
	
    //定义回调函数的格式
    typedef bool (CallBackFunc)( const IArgs& args);
	
	// 构造的时候需要为函数赋值
    CCallBackFunc(CallBackFunc* pFunc) : m_pFuc( pFunc ) {}
	
private:
    CallBackFunc* m_pFuc;	
};

/*---------------------------------------------------------------------
* 类	名：CFuncManage
* 功    能：管理全局函数指针的一个地方
* 特殊说明：名字必须唯一
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CFuncManage : public ISingleTon< CFuncManage >
{
public:
	CFuncManage();
	virtual ~CFuncManage();
/**  注册全局函数
 *  @param[in] strName 函数所对应的名称 必须唯一
 *  @param[in] piFunc 函数指针，可以是静态函数，可以是成员函数等
 *  @return 是否成功
 */
	bool RegFunc( std::string strName, ICallBackFuncBase* piFunc );

/**  反注册全局函数
 *  @param[in] strName 函数所对应的名称
 *  @return 是否成功
 */
	bool UnRegFunc( std::string strName );

/**  反注册所有全局函数 
 *  @return 是否成功
 *  @mark 用于推出uifactory时使用，释放new的内存 2012.12.3 yjj
 */
	void UnRegAllFunc();

/**  执行函数
 *  @param[in] strName 函数名
 *  @param[in] args 参数 可以根据自己需要进行添加
 *  @see IArgs
 *  @param[out] 
 *  @return 是否成功
 */
	bool ExeFunc( std::string strName, const IArgs& args );
protected:
	typedef std::map< std::string, ICallBackFuncBase* > FuncMap;
/*
 * 全局函数map表\n 
 */
	FuncMap m_mapFuncs;
};

/*
* 注册全局函数、以类成员函数作为函数指针 \n
* str 函数标示 func 函数名 obj 类指针 objType 类类型
*/
#ifndef REG_GOBAL_MEMBER_FUNC
#define REG_GOBAL_MEMBER_FUNC( str, func, obj, objType ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CMemberCallBackFunc<objType>( func, obj ) );
#endif

/*
* 注册全局函数、以全局或者静态函数作为函数指针 \n
* str 函数标示 func 函数名
*/
#ifndef REG_GOBAL_STATIC_FUNC 
#define REG_GOBAL_STATIC_FUNC( str, func ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CCallBackFunc( func ) );
#endif

/*
* 反注册全局函数 \n
* str 函数标示
*/
#ifndef UN_REG_GOBAL_FUNC
#define UN_REG_GOBAL_FUNC( str ) CFuncManage::GetSingletonPtr()->UnRegFunc( str );
#endif


#endif