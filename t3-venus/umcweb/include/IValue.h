// IValue.h: interface for the IValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_)
#define AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{
#ifndef Interface
#define Interface class
#endif
	
#ifndef Window
#define Window CWnd
#endif
	
#ifndef String
#define String string
#endif
	
#ifndef WindowMsg
#define WindowMsg MSG
#endif
	
}

// dynamic_cast
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����IValue
* ��    �ܣ�ֵ�Ļ��� һ�������propertyһ�𱻶���
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
Interface IValue  
{
public:
	IValue( String strType );
	virtual ~IValue();
	String GetType() const { return m_strType; } 

protected:
	String m_strType;
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_)
