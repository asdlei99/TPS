#include "stdafx.h"
#include "ItemFactory.h"
//#include "PropertyHelp.h"
//#include "System.h"

 namespace AutoUIFactory
 {
template<> CItemFactory* Singleton<CItemFactory>::ms_pSingleton  = 0;
const String CItemFactory::strType = "Type";
const String CItemFactory::strSize = "Size";
const String CItemFactory::strImage = "Image";
const String CItemFactory::strText = "Text";

const String CItemFactory::strTextItem = "Text";
const String CItemFactory::strExTextItem = "ExText";
const String CItemFactory::strImageItem = "Image";
const String CItemFactory::strFunc = "Func";
const String CItemFactory::strFontColor = "FontColor";
const String CItemFactory::strFontName = "FontName";
const String CItemFactory::strFontSize = "FontSize";
const String CItemFactory::strSelColor = "SelColor";
const String CItemFactory::strAlignment = "Alignment";
const String CItemFactory::strLayoutAlgorithm = "LayoutAlgorithm";
const String CItemFactory::strSortAlgorithm = "SortAlgorithm";

const String CItemFactory::strSecondText = "SecondText";
const String CItemFactory::strSecondFontColor = "SecondFontColor";
const String CItemFactory::strSecondFontName = "SecondFontName";
const String CItemFactory::strSecondFontSize = "SecondFontSize";
const String CItemFactory::strSecondAlignment = "SecondAlignment";

const String CItemFactory::strCanMove = "Move";
const String CItemFactory::strCanDrag = "Drag";
const String CItemFactory::strAlwaysShow = "AlwaysShow";
const String CItemFactory::strListItem = "ListItem";
const String CItemFactory::strCheckItem = "CheckItem";
const String CItemFactory::strButtonItem = "ButtonItem";
const String CItemFactory::strMidImageItem = "MidImage";
 
bool CItemFactory::bInit = false;
CItemFactory::ItemInfoMap CItemFactory::m_mapItemInfos;

IBaseItem* CItemFactory::CreateItem( String strItemName, String strItemTxt )
{
	if ( !bInit )
	{
		InitItem();
	}

	//根据从itemMapInfo中获取的item属性来创建item
	TItemPropty tItem ;
	GetItemInfo( strItemName , tItem );
  
	IBaseItem* pBase = 0;
	if ( tItem.strType == CItemFactory::strTextItem )
	{
		 
		String strText = strItemTxt;
	 
		CTextItem* pItem = new CTextItem( strText, tItem.szItem.cx, tItem.szItem.cy );
		if ( tItem.strCbFun.size() > 0 )
		{
			 
			pItem->SetFunc( tItem.strCbFun );
		}
		if ( tItem.pft != NULL )
		{
			Font* pFont = tItem.pft;
			pItem->SetFont( pFont );
			Color color = tItem.color;
			pItem->SetFontColor( color );

			pItem->SetSelColor( color );
		}

		StringAlignment align = StringAlignmentCenter;

		pBase = pItem;
	}
	else if ( tItem.strType ==  CItemFactory::strImageItem )
	{
		//String strImage = xmlAttrib.getValue( CItemFactory::strImage );
		SIZE sz = tItem.szItem;
		//strImage = CSystem::GetSingletonPtr()->GetImagePath() + strImage;
		CImageItem* pItem = new CImageItem( strImage.c_str(), sz.cx, sz.cy );
		if ( tItem.strCbFun.size() > 0 )
		{
			pItem->SetFunc( tItem.strCbFun );
		}
		pBase = pItem;
	}

	return pBase; 
}

bool CItemFactory::InitItem()
{
	bInit = true;
	TItemPropty tItemPrp;
    
	//添加TextItem
	tItemPrp.strType = strTextItem;
	tItemPrp.strItemName = "TextItem";
    tItemPrp.strCbFun = "";
	tItemPrp.szItem.cx = 350;
	tItemPrp.szItem.cy = 10;
	tItemPrp.color = Color( 255, 255, 255 );
	AddItemInfo( tItemPrp );

	//ImgItemAdd
	tItemPrp.Clear();
	tItemPrp.strType = strImageItem;
	tItemPrp.strItemName = "ImgItemAdd";
    tItemPrp.strCbFun = "";
	tItemPrp.pImgNormal = CSrcManage::GetImage( IDR_PNG_LIST_ADD, "PNG" );
	tItemPrp.pImgSel = CSrcManage::GetImage( IDR_PNG_LIST_ADDDOWN, "PNG" );
	tItemPrp.pImgDisable = CSrcManage::GetImage( IDR_PNG_LIST_ADD, "PNG" );
 
	AddItemInfo( tItemPrp );



	//ImgItemDel
	tItemPrp.Clear();
	tItemPrp.strType = strImageItem;
	tItemPrp.strItemName = "ImgItemDel";
    tItemPrp.strCbFun = "";
	tItemPrp.pImgNormal = CSrcManage::GetImage( IDR_PNG_LIST_DEL, "PNG" );
	tItemPrp.pImgSel = CSrcManage::GetImage( IDR_PNG_LIST_DEL, "PNG" );
	tItemPrp.pImgDisable = CSrcManage::GetImage( IDR_PNG_LIST_DEL, "PNG" );	 
	AddItemInfo( tItemPrp );

	return true;
}

bool CItemFactory::AddItemInfo( TItemPropty tItemPrp )  
{
	ItemInfoMap::iterator itr = m_mapItemInfos.find( tItemPrp.strType );
	if ( itr == m_mapItemInfos.end() )
	{   	 

		m_mapItemInfos.insert( ItemInfoMap::value_type(tItemPrp.strType, tItemPrp) );
		return true;
	}
	return false;
}

bool CItemFactory::GetItemInfo( String strType, TItemPropty& tItemPrps )
{
	ItemInfoMap::iterator itr = m_mapItemInfos.find( strType );
	if ( itr == m_mapItemInfos.end() )
	{
//		LOGEVENT( "没有找到该条目" + strType );
		return false;
	}
	tItemPrps = itr->second;
//	xmlAttribs = itr->second;
	return true;
}

// 
// IBaseItem* CItemFactory::CreateItem( String strType )
// {
// 	XMLAttributes xmlAttribs;
// 	if ( GetItemInfo( strType, xmlAttribs ) )
// 	{
// 		return CreateItem( xmlAttribs );
// 	}
// 	return 0;
// }


 


 }