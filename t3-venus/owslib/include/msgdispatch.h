#ifndef _MSGDISPATCH_H
#define _MSGDISPATCH_H

//////////////////////////////////////////////////////////////////////////
// ��Ϣ�ַ��࣬��Ҫ���������ҵ����ע���������Ϣ�ַ�

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
* ��	����ICallBackFuncBase
* ��    �ܣ��ص������ӿ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/08/20	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class ICallBackFuncBase
{
public:
	virtual ~ICallBackFuncBase(){}
	virtual bool operator()( const IArgs& args ) = 0;
};

/*---------------------------------------------------------------------
* ��	����CMemberCallBackFunc
* ��    �ܣ�Ϊ��Ա��������Ļص�����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/08/20	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
template<class T> class CMemberCallBackFunc : public ICallBackFuncBase
{
public:
    //����ص������ĸ�ʽ
    typedef bool (T::*MemberFunctionType)( const IArgs& args );
	
	// �����ʱ����ҪΪ������ֵ
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
* ��	����CMemberCallBackFunc
* ��    �ܣ�Ϊ��Ա��������Ļص�����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/08/20	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CCallBackFunc : public ICallBackFuncBase
{
public:
	virtual bool operator()( const IArgs& args)
	{
		return m_pFuc(args);
	}
	
    //����ص������ĸ�ʽ
    typedef bool (CallBackFunc)( const IArgs& args);
	
	// �����ʱ����ҪΪ������ֵ
    CCallBackFunc(CallBackFunc* pFunc) : m_pFuc( pFunc ) {}
	
private:
    CallBackFunc* m_pFuc;	
};

/*---------------------------------------------------------------------
* ��	����CFuncManage
* ��    �ܣ�����ȫ�ֺ���ָ���һ���ط�
* ����˵�������ֱ���Ψһ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CFuncManage : public ISingleTon< CFuncManage >
{
public:
	CFuncManage();
	virtual ~CFuncManage();
/**  ע��ȫ�ֺ���
 *  @param[in] strName ��������Ӧ������ ����Ψһ
 *  @param[in] piFunc ����ָ�룬�����Ǿ�̬�����������ǳ�Ա������
 *  @return �Ƿ�ɹ�
 */
	bool RegFunc( std::string strName, ICallBackFuncBase* piFunc );

/**  ��ע��ȫ�ֺ���
 *  @param[in] strName ��������Ӧ������
 *  @return �Ƿ�ɹ�
 */
	bool UnRegFunc( std::string strName );

/**  ��ע������ȫ�ֺ��� 
 *  @return �Ƿ�ɹ�
 *  @mark �����Ƴ�uifactoryʱʹ�ã��ͷ�new���ڴ� 2012.12.3 yjj
 */
	void UnRegAllFunc();

/**  ִ�к���
 *  @param[in] strName ������
 *  @param[in] args ���� ���Ը����Լ���Ҫ�������
 *  @see IArgs
 *  @param[out] 
 *  @return �Ƿ�ɹ�
 */
	bool ExeFunc( std::string strName, const IArgs& args );
protected:
	typedef std::map< std::string, ICallBackFuncBase* > FuncMap;
/*
 * ȫ�ֺ���map��\n 
 */
	FuncMap m_mapFuncs;
};

/*
* ע��ȫ�ֺ����������Ա������Ϊ����ָ�� \n
* str ������ʾ func ������ obj ��ָ�� objType ������
*/
#ifndef REG_GOBAL_MEMBER_FUNC
#define REG_GOBAL_MEMBER_FUNC( str, func, obj, objType ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CMemberCallBackFunc<objType>( func, obj ) );
#endif

/*
* ע��ȫ�ֺ�������ȫ�ֻ��߾�̬������Ϊ����ָ�� \n
* str ������ʾ func ������
*/
#ifndef REG_GOBAL_STATIC_FUNC 
#define REG_GOBAL_STATIC_FUNC( str, func ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CCallBackFunc( func ) );
#endif

/*
* ��ע��ȫ�ֺ��� \n
* str ������ʾ
*/
#ifndef UN_REG_GOBAL_FUNC
#define UN_REG_GOBAL_FUNC( str ) CFuncManage::GetSingletonPtr()->UnRegFunc( str );
#endif


#endif