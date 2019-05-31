// commonheadertest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "shareptrcontainertest.h"

void SharePtrContainerTest(){
	ObjectContainerForSharePtr shareptrContainer;
	ObjectWeakPtr ptr = shareptrContainer.add( 1 );
	shareptrContainer.add( 2 );

	ObjectContainerForWeakPtr weakptrContainer;
	weakptrContainer.add( 1, ptr );

	CFuncTest test(ptr);
	test.Print();

	cout << endl;
	shareptrContainer.traversal( &CDelegate<CFuncTest>( &test, &CFuncTest::PrintObjectByPtr) );
	cout << endl;
	// 改变一个值
	test.ChangeData( 100 );
	cout << "============================weakptr container data ============================" << endl;
	weakptrContainer.traversal( &CDelegate<CFuncTest>( &test, &CFuncTest::PrintObjectByWeakPtr) );	
	cout << "============================sharptr container data ============================" << endl;
	shareptrContainer.traversal( &CDelegate<CFuncTest>( &test, &CFuncTest::PrintObjectByPtr) );
	cout << endl;

	// 当离开作用域的时候，shareptrContainer会释放资源
	// 其它引用的值会失效。
}
int _tmain(int argc, _TCHAR* argv[])
{
	SharePtrContainerTest();
	system("pause");
	return 0;
}