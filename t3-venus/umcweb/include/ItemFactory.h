// ItemFactory.h: interface for the CItemFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMFACTORY_H__CEDBB4B6_E51C_4067_A953_6A354F57216D__INCLUDED_)
#define AFX_ITEMFACTORY_H__CEDBB4B6_E51C_4067_A953_6A354F57216D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "utility.h"
#include <map>

//#include "XmlAttrib.h"
 namespace AutoUIFactory
 {
class CItemFactory : public Singleton<CItemFactory>
{
public:
	static const String strType;
	static const String strImage;
	static const String strText;
	static const String strSize;

	static const String strTextItem;	
	static const String strImageItem;
	static const String strMidImageItem;
	static const String strFunc;
	static const String strFontColor;
	static const String strFontName;
	static const String strFontSize;
	static const String strSelColor;
	static const String strAlignment;
	static const String strLayoutAlgorithm;
	static const String strSortAlgorithm;

	static const String strExTextItem;
	static const String strSecondText;
	static const String strSecondFontColor;
	static const String strSecondFontName;
	static const String strSecondFontSize;
	static const String strSecondAlignment;

	static const String strCanMove;
	static const String strCanDrag;
	static const String strAlwaysShow;
	static const String strListItem;
	static const String strCheckItem;
	static const String strButtonItem;


protected:

	struct TItemPropty{
        string strType;
		string strItemName;
		string strCbFun;
		Font*  pft;
		Color color;
		SIZE  szItem;
		Color selcolor;

		Image *pImgNormal;
		Image *pImgSel;
		Image *pImgDisable;

	    void Clear()
		{
			strType.empty();
			
			strItemName = "";

			strCbFun = "";
			pft = CSrcManage::GetFont( "微软雅黑", 12 );
			color = Color( 46, 76, 12 );
			selcolor = Color( 255, 255, 255 );

			szItem.cx = 355;
			szItem.cy = 10;

			pImgNormal = NULL;
			pImgSel = NULL;
			pImgDisable = NULL;


		}

		TItemPropty()
		{
			Clear();
		}


	};
	/*
	 * 记录所有item信息  
	 */
	typedef std::map<String, TItemPropty> ItemInfoMap;
	static bool bInit;
	static ItemInfoMap m_mapItemInfos;

public:
/**  创建条目
 *  @param[in] xmlAttrib xml信息 
 *  @return 新条目
 */
//	IBaseItem* CreateItem( XMLAttributes& xmlAttrib );

/**  创建条目
 *  @param[in] strType 条目名称
 *  @return 新条目
 */
//	IBaseItem* CreateItem( String strType );

// 	bool AddItemInfo( String strType, XMLAttributes xmlAttribs );
// 	bool GetItemInfo( String strType, XMLAttributes& xmlAttribs );

	IBaseItem* CreateItem( String strItemName, String strItemTxt );
	bool InitItem();
	bool AddItemInfo( TItemPropty tItemPrp );
	bool GetItemInfo( String strType, TItemPropty& tItemPrps );


};

 }


#endif // !defined(AFX_ITEMFACTORY_H__CEDBB4B6_E51C_4067_A953_6A354F57216D__INCLUDED_)
