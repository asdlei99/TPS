#pragma once
#include <string>
#include <memory>
#include <map>
using namespace std;

#define NS_TEMPLATECLASS_BEGIN namespace TemplateClass{
#define NS_TEMPLATECLASS_END	}
#define US_NS_TEMPLATECLASS using namespace TemplateClass;

#define DEF_MEMBER( type, name, funcname) \
	protected: type name;\
	public: virtual type get##funcname(){return name;} \
	public: virtual void set##funcname(type var){ name = var; }

NS_TEMPLATECLASS_BEGIN
/*
	函数指针基类
*/
class CDelegateBase    
{
public:
	CDelegateBase(void* pObject, void* pFn) : m_pObject( pObject ),m_pFn(pFn){	}
	CDelegateBase(const CDelegateBase& rhs){
		m_pObject = rhs.m_pObject;
		m_pFn = rhs.m_pFn; 
	}
	virtual ~CDelegateBase(){}
	bool Equals(const CDelegateBase& rhs) const{
		return m_pObject == rhs.m_pObject && m_pFn == rhs.m_pFn; 
	}
	bool operator() (void* param){
		return Invoke(param); 
	}
	virtual CDelegateBase* Copy() const = 0; 

protected:
	void* GetFn(){return m_pFn;}
	void* GetObject(){return m_pObject;}
	virtual bool Invoke(void* param) = 0;

private:
	void* m_pObject;
	void* m_pFn;
};

/*
	静态函数指针、C函数指针
*/
class CDelegateStatic: public CDelegateBase
{
	typedef bool (*Fn)(void*);
public:
	CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn) { } 
	CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) { } 
	virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

protected:
	virtual bool Invoke(void* param){
		Fn pFn = (Fn)GetFn();
		return (*pFn)(param); 
	}
};

/*
	成员变量型指针
*/
template <class T> class CDelegate : public CDelegateBase
{
	typedef bool (T::* Fn)(void*);
public:
	CDelegate(T* pObj, Fn pFn) : CDelegateBase(pObj, &pFn), m_pFn(pFn) { }
	CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) { m_pFn = rhs.m_pFn; } 
	virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

protected:
	virtual bool Invoke(void* param){
		T* pObject = (T*) GetObject();
		return (pObject->*m_pFn)(param); 
	}  

private:
	Fn m_pFn;
};

/*
	指针型容器抽象类，负责构造，管理指针
	内部实现为map，Key为键值，Data为数据类型
	使用者需要派生该类，实现add函数
	外部使用指针均使用weak_ptr。保证指针安全。
*/
template<class Key,class Data,class Type = string> class IContainer_SharePtr
{
protected:
	typedef map<Key,shared_ptr<Data> > Container;
	Container m_mapData;
public:
	/*
		必须实现该函数，该容器既是容器也是工厂
	*/
	virtual weak_ptr<Data> add( const Key& key, const Type& strType = "") = 0;
	
	virtual ~IContainer_SharePtr(){}

	virtual bool get(const Key& key, weak_ptr<Data>& result){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() ){
			result = itr->second;
			return true;
		}
		return false;
	}

	virtual bool remove( const Key& key ){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() ){
			itr->second.reset();
			m_mapData.erase( itr );
			return true;
		}
		return false;
	}

	virtual void removeall(){
		Container::iterator itr = m_mapData.begin();
		while ( itr != m_mapData.end() ){
			itr->second.reset();	
			itr++;
		}
		m_mapData.clear();
	}

	unsigned int count(){
		return m_mapData.size();
	}

	virtual void traversal( CDelegateBase* pFun ){
		Container::iterator itr = m_mapData.begin();
		while ( itr != m_mapData.end() ){
			//	weak_ptr<Data> ptr( itr->second );
			if ( (*pFun)((void*)itr->second._Get()) == false ){
				return;
			}
			itr++;
		}
	} 
};

template<class Key,class Data> class IContainer_Struct
{
protected:
	typedef map<Key,Data> Container;
	Container m_mapData;
public:
	virtual void add( const Key& key, const Data& data ){
		m_mapData[key] = data;
	}
	virtual ~IContainer_Struct(){}

	virtual bool get(const Key& key, Data data){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() ){
			data = itr->second;
			return true;
		}
		return false; 
	}

	virtual bool remove( const Key& key ){
		Container::iterator itr = m_mapData.find( key );
		if ( itr != m_mapData.end() ){
			m_mapData.erase( itr );
			return true;
		}
		return false;
	}

	virtual void removeall(){
		m_mapData.clear();
	}
	unsigned int count(){
		return m_mapData.size();
	}

	virtual void traversal( CDelegateBase* pFun ){
		Container::iterator itr = m_mapData.begin();
		while ( itr != m_mapData.end() ){
			if ( (*pFun)( (void*)(&(itr->second)) ) == false ){
				return;
			}
			itr++;
		}
	} 
};

NS_TEMPLATECLASS_END
