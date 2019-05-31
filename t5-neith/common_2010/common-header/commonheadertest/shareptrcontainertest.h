#pragma once
#include <iostream>
#include "../container.h"

US_NS_TEMPLATECLASS
class Object{
public:
	Object() : m_nData(0){
		cout << "object create" << endl;
	}
	virtual ~Object(){
		cout << "object release" << endl;
	}
	virtual void Print(){
		cout << "Object Data =" << m_nData << endl;
	}
	DEF_MEMBER( int, m_nData, Data )
};

class Human : public Object{
public:
	Human(){
		cout << "Human create" << endl;
	}
	virtual ~Human(){
		cout << "Human release" << endl;
	}
	virtual void Print(){
		cout << "Human Data =" << m_nData << endl;
	}
};

typedef weak_ptr<Object> ObjectWeakPtr;
typedef shared_ptr<Object> ObjectSharePtr;

class ObjectContainerForSharePtr : public IContainer_SharePtr<int,Object>
{
public:
	ObjectWeakPtr add( const int& key, const string& strType = ""){
		ObjectWeakPtr weakPtr;
		if ( get( key, weakPtr) )
		{
			return weakPtr;
		}
		Object* pObject = NULL;
		if ( strType == "Human" ){
			pObject = new Human();
		}
		else{
			pObject = new Object();
		}
		ObjectSharePtr ptr(pObject);
		m_mapData[key] = ptr;
		return ObjectWeakPtr(ptr);
	}
};

class ObjectContainerForWeakPtr : public IContainer_Struct<int, ObjectWeakPtr>{};

class CFuncTest{
public:
	CFuncTest( ObjectWeakPtr ptr):m_ptr(ptr){}
	CFuncTest(){}
	virtual ~CFuncTest(){ m_ptr.reset(); }
	void Print(){
		ObjectSharePtr ptr = m_ptr.lock();
		if ( ptr ){
			ptr->Print();
		}
	}
	bool PrintObjectByPtr( void* pObject ){
		Object* pOb = (Object*)pObject;
		if ( pOb ){
			pOb->Print();
			return true;
		}
		return false;
	}
	bool PrintObjectByWeakPtr( void* pObject ){
		ObjectWeakPtr* ptr = (ObjectWeakPtr*)pObject;
		ObjectSharePtr shptr = (*ptr).lock();
		if ( shptr )
		{
			shptr->Print();
			return true;
		}
		else{
			cout << "object has released" << endl;
		}
		return false;
	}
	void ChangeData( int nData ){
		ObjectSharePtr ptr = m_ptr.lock();
		if ( ptr ){
			ptr->setData( nData );
		}
	}
private:
	ObjectWeakPtr m_ptr;
};