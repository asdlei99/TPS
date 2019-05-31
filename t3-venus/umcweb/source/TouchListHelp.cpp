// TouchListHelp.cpp: implementation of the CTouchListHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TouchListHelp.h"
#include "TouchListProperty.h"
#include <time.h>
#include <algorithm>
#include "ItemFactory.h"
#include "ListChild.h"

 
// #include "AddrList.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
const String CTouchListHelp::strItemDefault = "ImageItem";
const String CTouchListHelp::strItemText = "TextItem";

const String CTouchListHelp::strItemAddrList = "AddrListItem";

//------模板系统列表-------
const String CTouchListHelp::strConfTemplate = "TouchListConfTemp";
const String CTouchListHelp::strTempCns = "TouchListTempCns";
const String CTouchListHelp::strItemTempPoll = "TouchListTempPoll";

//
const String CTouchListHelp::strConfLst = "TouchListConf";
const String CTouchListHelp::strListConf = "ListConf";
const String CTouchListHelp::strConfCns = "ListConfInfo";
const String CTouchListHelp::strListConfCns = "ListConfCns";

//地址簿列表
const String CTouchListHelp::strListAddr = "TouchListAddr";
const String CTouchListHelp::strListConnectCn = "ListConnectCns";
const String CTouchListHelp::strListCnsOrderList = "TouchListCnsOrderList";

const String CTouchListHelp::strListUser = "TouchListUser";   //用户列表
const String CTouchListHelp::strListAlarm = "TouchListAlarm"; //告警列表
 
//菜单列表
const String CTouchListHelp::strListMenu = "TouchListMenu";
const String CTouchListHelp::strListTvw = "ViewListTvw";		//电视墙列表
const String CTouchListHelp::strListConfMenu = "HoriListConfMenu";
const String CTouchListHelp::strVerListConfMenu = "VerListConfMenu";

//录像文件列表
const String CTouchListHelp::strListFile = _T("ListFile");

//录像和回放列表
const String CTouchListHelp::strListRecord = _T("ListRecord");

//录像和回放会场列表
const String CTouchListHelp::strListRecordEp = _T("ListRecordEp");

CTouchListHelp::CTouchListHelp()
{ 
}

CTouchListHelp::~CTouchListHelp()
{

}

 
bool CTouchListHelp::SetData( IItemList* pList, const IValue* pValue )
{
	if ( pList == 0 || pValue == 0 )
	{
		return false;
    } 

    pList->DeleteAllItem(); 
    String strType = pValue->GetType(); 
   
	//菜单
    if ( strType == CTouchListHelp::strListMenu  )
    {
        if ( const Value_TouchListMenu* pVa = dynamic_cast<const Value_TouchListMenu*>( pValue ) )
        {
            if ( pVa != NULL )
            {
                Value_TouchListMenu  Lst = *const_cast<Value_TouchListMenu*>(pVa);
                return CTouchListHelp::TransData( pList, Lst.m_pMenuLst, FALSE, Lst.m_bDrawRightPic );
            }
		}
    }
	
    // 用户列表
    if ( strType == CTouchListHelp::strListUser )
    {
        if ( const Value_TouchListUser* pVa = dynamic_cast<const Value_TouchListUser*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_TouchListUser  Lst = *const_cast<Value_TouchListUser*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }

	//地址簿
	if ( strType == CTouchListHelp::strListAddr )
	{
		if ( Value_TouchListAddr* pAddrValue = dynamic_cast<Value_TouchListAddr*>( const_cast<IValue*>(pValue) ) )
		{
			if ( pAddrValue != NULL )
			{
				return CTouchListHelp::TransData( pList, pAddrValue->m_pAddrList, pAddrValue->m_strItemFunc, pAddrValue->m_bAddIconShow
					, pAddrValue->m_pSubItem, pAddrValue->m_bSort, pAddrValue->m_pSubItem, pAddrValue->m_bAddrEditDlg, pAddrValue->m_bShowOnline );
			}
		}
	}

    //会议模板列表
	if ( strType == CTouchListHelp::strConfTemplate )
    {     
		if ( Value_TouchListConfTemp* pConfTempValue = dynamic_cast<Value_TouchListConfTemp*>(const_cast<IValue*>(pValue) ) )
		{
			if ( pConfTempValue != 0 )
            { 
                 
				return CTouchListHelp::TransData( pList, *pConfTempValue );
			}
		}
	}


	//模板中的cns列表
    if ( strType == CTouchListHelp::strTempCns)
    {
        if ( Value_TouchListTempCns* pConfTempValue = dynamic_cast<Value_TouchListTempCns*>(const_cast<IValue*>(pValue) ) ) 
        {
            if ( pConfTempValue != 0 )
            {
				return CTouchListHelp::TransData( pList, *pConfTempValue  ); //pConfTempValue->m_tCnsLst,pConfTempValue->m_strClickItemFunc, 
				//                                               pConfTempValue->m_pVctSubItem,pConfTempValue->m_bDrag );
            }
		}
    }
	
    //模板中轮询列
    if ( strType == CTouchListHelp::strItemTempPoll )
    {
        if ( Value_TouchListTempPoll* pTempPollValue = dynamic_cast<Value_TouchListTempPoll*>(const_cast<IValue*>(pValue) ) )
        {
            if ( pTempPollValue != NULL )
            {
                return CTouchListHelp::TransData( pList, pTempPollValue->m_tTemp, pTempPollValue->m_strClickItemFunc, pTempPollValue->m_bAddIconShow,
                    pTempPollValue->m_pVctSubItem ,pTempPollValue->m_bDrag);
            }
        }
    }

	// 当前会议列表
    if ( strType == CTouchListHelp::strConfLst )
    {
        if ( const Value_TouchListConf* pVa = dynamic_cast<const Value_TouchListConf*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_TouchListConf  Lst = *const_cast<Value_TouchListConf*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }

	//预约会议列表
	if ( strType == CTouchListHelp::strListCnsOrderList )
    {     
		if ( Value_TouchListOrderConf* pConfTempValue = dynamic_cast<Value_TouchListOrderConf*>(const_cast<IValue*>(pValue) ) )
		{
			if ( pConfTempValue != 0 )
            { 
				
				return CTouchListHelp::TransData( *pConfTempValue, pList );
			}
		}
	}

    //会议中cns列表
    if ( strType == CTouchListHelp::strConfCns )
    {
        if ( const Value_ListConfInfo* pVa = dynamic_cast<const Value_ListConfInfo*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_ListConfInfo cnsLst = *const_cast<Value_ListConfInfo*>(pVa);
                return CTouchListHelp::TransData( pList, cnsLst );
            }
        }
    }

    if ( strType == CTouchListHelp::strListConfCns )
    {
        if ( const Value_ListConfCns* pVa = dynamic_cast<const Value_ListConfCns*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_ListConfCns cnsLst = *const_cast<Value_ListConfCns*>(pVa);
                return CTouchListHelp::TransData( pList, cnsLst );
            }
        }
    }

    if ( strType == CTouchListHelp::strListConf )
    {
        if ( const Value_ListConf* pVa = dynamic_cast<const Value_ListConf*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_ListConf cnsLst = *const_cast<Value_ListConf*>(pVa);
                return CTouchListHelp::TransData( pList, cnsLst );
            }
        }
    }  

    if ( strType == CTouchListHelp::strListTvw )
    {
        if ( Value_ViewListTvw* pTvwValue = dynamic_cast<Value_ViewListTvw*>( const_cast<IValue*>(pValue) ) )
        {
            if ( pTvwValue != NULL )
            {
                return CTouchListHelp::TransData( pList, *pTvwValue );
            }
        }
    }

	// 录像机文件列表
    if ( strType == CTouchListHelp::strListFile )
    {
        if ( const Value_ListFile* pVa = dynamic_cast<const Value_ListFile*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_ListFile  Lst = *const_cast<Value_ListFile*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }
	
	// 录像和回放
    if ( strType == CTouchListHelp::strListRecord )
    {
        if ( const Value_ListRecord* pVa = dynamic_cast<const Value_ListRecord*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_ListRecord  Lst = *const_cast<Value_ListRecord*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }
	
	// 录像和回放会场
    if ( strType == CTouchListHelp::strListRecordEp )
    {
        if ( const Value_ListRecordEp* pVa = dynamic_cast<const Value_ListRecordEp*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_ListRecordEp  Lst = *const_cast<Value_ListRecordEp*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }

	return true;
}

//菜单列表
bool CTouchListHelp::TransData( IItemList* pList, ARRAY<TMenuItemInfo> *pvctMenuLst, BOOL32 bDrag, BOOL bDrawRightPic )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
	
    ARRAY<TMenuItemInfo>::iterator it = pvctMenuLst->begin();
    s32 nKey = 0;
    while ( it != pvctMenuLst->end() )
    {  
        String txt = it->strTxt;  
		
        String strClickItemFunc = it->strItemFunc; 
        Data_Menu data(*it); 
		
		CListItem* plistItem = new CListItem( "", 0, 40 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( 0, 0, IDR_PNG_LISTITEM_SHORTRIGHT,
				IDR_PNG_LISTITEM_SHORTLEFTSEL, IDR_PNG_LISTITEM_SHORTMIDSEL, IDR_PNG_LISTITEM_SHORTRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			
			//Data_Menu dataMenu( data);
			data.SetDataKey( nKey );
			
			plistItem->SetUserData( &data ); 
			
			if ( strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( strClickItemFunc );	
			}
			
		}
		
		IItemList *pNew = pList->AddItem( nKey, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		CTextItem* pTextItem = new CTextItem( "", 300, 40 );
		pTextItem->SetText( txt);
		
		Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );
		
		pNew->AddItem( 0, pTextItem, emGroup );
		
		SAFE_RELEASE(pTextItem);
		
        it++;
		nKey++;
		
		
		// 添加右侧图片 
		if (bDrawRightPic)
		{
			CImageItem* pImageItem = new CImageItem( "", 39, 47 );
			pImageItem->SetImage( IDR_PNG_LIST_ENTER, IDR_PNG_LIST_ENTERDOWN, "PNG" );
			pNew->AddItem( 1, pImageItem ,emGroup );
			SAFE_RELEASE(pImageItem);
		}
    }
	return true;
}

//用户列表 
bool CTouchListHelp::TransData( IItemList* pList, Value_TouchListUser &val)
{
    if ( pList == NULL || val.m_pvctArryUser == NULL )
    {
        return false;
    }

    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);  

	vector<CUserFullInfo> vctList = *(val.m_pvctArryUser);

//     s32 nCount =  val.m_pTplArryUser->Size();
//     vector<CUserFullInfo> vctList;
//     for ( s32 nIndexPos = 0; nIndexPos < nCount; nIndexPos++ )
//     {
//         vctList.push_back( val.m_pTplArryUser->GetAt(nIndexPos) );
//     }
//     
// 	sort( vctList.begin(), vctList.end(), CListChild::UserItemCompare );

	String strImageFun = val.m_strClickItemFunc;
	strImageFun += "Icon";
	
	for ( s32 nIndex = 0; nIndex < vctList.size(); nIndex++ )
	{
		CUserFullInfo user = vctList[nIndex];
		CString strUserName;
		strUserName = user.GetName();
		if ( strUserName.IsEmpty() || strUserName == "admin" )
		{
			continue;
		}

		CListItem* plistItem = new CListItem( "", 0, 40 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_SHORTLEFT, IDR_PNG_LISTITEM_SHORTMID, IDR_PNG_LISTITEM_SHORTRIGHT,
				IDR_PNG_LISTITEM_SHORTLEFTSEL, IDR_PNG_LISTITEM_SHORTMIDSEL, IDR_PNG_LISTITEM_SHORTRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 

			Data_User data( user);
			data.SetDataKey( nIndex );
			plistItem->SetUserData( &data ); 

			if ( val.m_strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( val.m_strClickItemFunc );
			}
					
		}

		IItemList *pNew = pList->AddItem( nIndex, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);


		CTextItem* pTextItem = new CTextItem( "", 300, 40 );
		pTextItem->SetText( user.GetName() );

		Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );

		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );

		pNew->AddItem( 0, pTextItem, emGroup );

		SAFE_RELEASE(pTextItem);


		// 添加 图标 
		CImageItem* pImageItem = new CImageItem( "", 29, 29 );
		std::set<CString>::iterator iter = val.m_setClickedName.find(strUserName);
		if ( iter != val.m_setClickedName.end() )
		{
			pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
		}
		else
		{
			pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKSEL, "PNG" );
		}

		pImageItem->SetFunc( strImageFun );
		pNew->AddItem( 1, pImageItem ,emGroup ); 
		SAFE_RELEASE(pImageItem);

	}

	return true;
}

//模板列表
bool CTouchListHelp::TransData( IItemList* pList, Value_TouchListConfTemp &val) 
{
	if ( pList == NULL || val.m_pvctConfTemplate == NULL )
    {
        return false;
    }
	
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert ); 
    pBaseItem->SetMoveStatus(true); 
    
//  sort( val.m_pvctConfTemplate->begin(), val.m_pvctConfTemplate->end(), CListChild::OrderConfTempCompare );

	CListChild::ConfTemplateCompare( val.m_pvctConfTemplate );
    
    s32 nCount =  val.m_pvctConfTemplate->size(); 

	for ( s32 nIndex = 0; nIndex < nCount; nIndex++ )
    {
		Data_ConfTemp ConfTmpData( *( &val.m_pvctConfTemplate->at(nIndex) ) );  //会议模板
		ConfTmpData.SetDataKey( val.m_pvctConfTemplate->at(nIndex).m_wID );
		
		String strConfName = val.m_pvctConfTemplate->at(nIndex).m_achConfName;
		
		CListItem* plistItem = new CListItem( "", 0, 40 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_SHORTLEFT, IDR_PNG_LISTITEM_SHORTMID, IDR_PNG_LISTITEM_SHORTRIGHT,
				IDR_PNG_LISTITEM_SHORTLEFTSEL, IDR_PNG_LISTITEM_SHORTMIDSEL, IDR_PNG_LISTITEM_SHORTRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			plistItem->SetUserData( &ConfTmpData ); 

			if ( val.m_strItemFunc.size() > 0 )
			{
				plistItem->SetFunc( val.m_strItemFunc );	
			}
		}
		
		IItemList *pNew = pList->AddItem( nIndex, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		CTextItem* pTextItem = new CTextItem( "", 300, 40 );
		pTextItem->SetText( strConfName );
		
		Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );
		
		pNew->AddItem( 0, pTextItem, emGroup );
		
		SAFE_RELEASE(pTextItem);

		// 添加 图标 
		CImageItem* pImageItem = new CImageItem( "", 29, 29 );
		std::set<CString>::iterator iter = val.m_setClickedName.find(strConfName.c_str());
		if ( iter != val.m_setClickedName.end() )
		{
			pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
		}
		else
		{
			pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKSEL, "PNG" );
		}
		
		pImageItem->SetFunc( "CMeetTemplateLogic::OnClickTmpLstItemIcon" );
		pNew->AddItem( 1, pImageItem ,emGroup ); 
		SAFE_RELEASE(pImageItem);
	}
    
	return true;
}


//地址簿
bool CTouchListHelp::TransData( IItemList* pList, ARRAY<TAddrItem>* pArray, String strItemFunc, BOOL m_bAddIconShow,
							    ARRAY<String>* pVctSubItem, BOOL bSort, vector<String>* pSubItem, BOOL bAddrEditDlg, BOOL bShowOnline )
{
	IBaseItem* pBaseItem = pList->GetItemData();
	CLayoutAlgorithm_Vert::nXSpace = 4;
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

	//排序
	if ( bSort )
	{
		sort( pArray->begin(), pArray->end(), CListChild::AddrItemCompare );
	}
	
	for ( s32 nIndexPos = 0; nIndexPos < pArray->size(); nIndexPos++ )
	{
		TAddrItem tAddrItem = pArray->at(nIndexPos); 
		Data_AddrItemInfo itemInfo(tAddrItem);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			itemInfo.SetDataKey( tAddrItem.tAddrInfo.dwEntryIdx );		
		}
		else
		{
			itemInfo.SetDataKey( tAddrItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY ); //防止跟EntryItem一样
		}

		CListItem* plistItem = new CListItem( "", 0, 50 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
				IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
				IDR_PNG_LIST_SPLIT );

			if ( CListItem* pImageItem = dynamic_cast<CListItem*>(plistItem) )
			{
				if ( tAddrItem.emItemType == emEntryItem )
				{
					plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem );
				}
				else
				{
					plistItem->SetLayoutAlgorithm( IAlgorithm::strAddrGroupItem );
				}
			
				Data_AddrItemInfo dataAddrbook( itemInfo );
				itemInfo.SetDataKey( nIndexPos );
				plistItem->SetUserData( &dataAddrbook ); 
				plistItem->SetFunc( strItemFunc );	
				plistItem->SetDragStatus(true);
			}

			IItemList *pNew = pList->AddItem( nIndexPos, plistItem, emGroup );
			SAFE_RELEASE(plistItem);

			String strImageFun = strItemFunc;
			strImageFun += "Icon";
			int nIndex = 0;
			Font* pFont = NULL;
			CTextItem* pTextItem = NULL;
			CExTextItem* pTextItemEx = NULL;
			CImageItem* pImageItem = NULL;

			if ( tAddrItem.emItemType == emEntryItem )
			{
				if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 && strcmp( tAddrItem.tAddrInfo.achE164, "" ) != 0 )
				{
					if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointH323MT 
						|| tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointH323MCU )
					{
						pFont = CSrcManage::GetFont( "微软雅黑", 13 ); 	
						pTextItemEx = new CExTextItem( "", 0, 10, StringAlignmentNear );
						pTextItemEx->SetFont( pFont );
						pTextItemEx->SetAlignment( StringAlignmentNear );
						pTextItemEx->SetFontColor( Color(46, 55, 76) );
						pTextItemEx->SetSelColor( Color(255, 255, 255) );
						pTextItemEx->SetText( tAddrItem.tAddrInfo.achEntryName );
						pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
						pTextItemEx->AddText( tAddrItem.tAddrInfo.achE164, pFont,  Color(108, 124, 148), StringAlignmentNear );
					}
					else if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeUMS 
						|| tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeCNS )
					{
						pFont = CSrcManage::GetFont( "微软雅黑", 13 ); 	
						pTextItemEx = new CExTextItem( "", 0, 10, StringAlignmentNear );
						pTextItemEx->SetFont( pFont );
						pTextItemEx->SetAlignment( StringAlignmentNear );
						pTextItemEx->SetFontColor( Color(0, 113, 229) );
						pTextItemEx->SetSelColor( Color(255, 255, 255) );
						pTextItemEx->SetText( tAddrItem.tAddrInfo.achEntryName );
						pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
						pTextItemEx->AddText( tAddrItem.tAddrInfo.achE164, pFont,  Color(108, 124, 148), StringAlignmentNear );
					}
					else
					{
						pFont = CSrcManage::GetFont( "微软雅黑", 13 ); 	
						pTextItemEx = new CExTextItem( "", 0, 10, StringAlignmentNear );
						pTextItemEx->SetFont( pFont );
						pTextItemEx->SetAlignment( StringAlignmentNear );
						pTextItemEx->SetFontColor( Color(0, 113, 229) );
						pTextItemEx->SetSelColor( Color(255, 255, 255) );
						pTextItemEx->SetText( tAddrItem.tAddrInfo.achEntryName );
						pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
						pTextItemEx->AddText( tAddrItem.tAddrInfo.achE164, pFont,  Color(108, 124, 148), StringAlignmentNear );
					}
					pNew->AddItem( 0, pTextItemEx, emGroup );
					nIndex = 1;
					SAFE_RELEASE(pTextItemEx);
				}
				else
				{
					if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 )
                    {
                        if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointH323MT 
							|| tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointH323MCU )
						{
							pTextItem = new CTextItem( "", 300, 50 );
							pTextItem->SetText( tAddrItem.tAddrInfo.achEntryName );
							
							Font* pFont = CSrcManage::GetFont( "微软雅黑", 13 );
							pTextItem->SetFont( pFont );
							pTextItem->SetAlignment( StringAlignmentNear );
							
							pTextItem->SetFontColor( Color(46, 55, 76) );
							pTextItem->SetSelColor( Color(255, 255, 255) );
						}
						else if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeUMS 
							|| tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeCNS )
						{
							pTextItem = new CTextItem( "", 300, 50 );
							pTextItem->SetText( tAddrItem.tAddrInfo.achEntryName );
							
							Font* pFont = CSrcManage::GetFont( "微软雅黑", 13 );
							pTextItem->SetFont( pFont );
							pTextItem->SetAlignment( StringAlignmentNear );
							
							pTextItem->SetFontColor( Color(0, 113, 229) );
							pTextItem->SetSelColor( Color(255, 255, 255) );
						}
						else
						{
							pTextItem = new CTextItem( "", 300, 50 );
							pTextItem->SetText( tAddrItem.tAddrInfo.achEntryName );
							
							Font* pFont = CSrcManage::GetFont( "微软雅黑", 13 );
							pTextItem->SetFont( pFont );
							pTextItem->SetAlignment( StringAlignmentNear );
							
							pTextItem->SetFontColor( Color(0, 113, 229) );
							pTextItem->SetSelColor( Color(255, 255, 255) );
						}
                    }
					else
					{
						pTextItem = new CTextItem( "", 300, 50 );
						pTextItem->SetText( tAddrItem.tAddrInfo.achE164 );
						
						Font* pFont = CSrcManage::GetFont( "微软雅黑", 11 );
						pTextItem->SetFont( pFont );
						pTextItem->SetAlignment( StringAlignmentNear );
						
						pTextItem->SetFontColor( Color(108, 124, 148) );
						pTextItem->SetSelColor( Color(255, 255, 255) );
					}
					pNew->AddItem( 0, pTextItem, emGroup );
					nIndex = 1;
					SAFE_RELEASE(pTextItem);
				}
			}
			else
			{
				pTextItem = new CTextItem( "", 300, 50 );
				pTextItem->SetText( tAddrItem.tGroupInfo.achGroupName );
				pFont = CSrcManage::GetFont( "微软雅黑", 13 ); 	
				
				pTextItem->SetFont( pFont );
				pTextItem->SetAlignment( StringAlignmentNear );
				pTextItem->SetFontColor( Color(46, 55, 76) );
				pTextItem->SetSelColor( Color(255, 255, 255) );
				pNew->AddItem( 0, pTextItem, emGroup );
				SAFE_RELEASE(pTextItem);
				
				pTextItem = new CTextItem( "", 48, 50 );
				CString strNum;
				strNum.Format( "(%d)", tAddrItem.tGroupInfo.nEntryNum + tAddrItem.tGroupInfo.nDownGroupNum );
				pTextItem->SetText( (LPCTSTR)(strNum) );		
				pFont = CSrcManage::GetFont( "微软雅黑", 11 );
				pTextItem->SetFont( pFont );
				pTextItem->SetAlignment( StringAlignmentCenter );
				pTextItem->SetFontColor( Color(108, 124, 148) );
				pTextItem->SetSelColor( Color(255, 255, 255) );
				pNew->AddItem( 1, pTextItem, emGroup );
				SAFE_RELEASE(pTextItem);
				
				// 添加 图标 
				pImageItem = new CImageItem( "", 27, 20 );
				pImageItem->SetImage( IDR_PNG_LIST_GROUP, IDR_PNG_LIST_GROUPSEL, "PNG" );
				pImageItem->SetFunc( "" );
				pNew->AddItem( 2, pImageItem ,emGroup ); 
				SAFE_RELEASE(pImageItem);
				nIndex = 3;
			}
			

			// 添加 图标 
			pImageItem = new CImageItem( "", 29, 29 );

			if ( !bAddrEditDlg )
			{
				if ( !m_bAddIconShow )
				{
					if ( tAddrItem.strImg == "AddrEditUnSelItem" )
					{
						pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
					}
					else
					{
						pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKDOWN, "PNG" );
					}
				}
				else
				{
					if ( tAddrItem.strImg == "AddrEditUnSelItem" )
					{
						pImageItem->SetImage( 0, 0, "PNG" );
					}
					else
					{
						pImageItem->SetImage( IDR_PNG_LIST_ADD, IDR_PNG_LIST_ADDDOWN, "PNG" );
					}
				}
				pImageItem->SetFunc( strImageFun );
			}
			else
			{
				String strListType;
				if ( pSubItem == NULL )
				{
					strListType = "";
				}
				else
				{
					if ( (*pSubItem).size() > 0 )
					{
						strListType = (*pSubItem)[0];
					}
					else
					{
						strListType = "";
					}
				}
				
				if ( strListType == "AddrDelItem" )
				{
					pImageItem->SetImage( IDR_PNG_LIST_DEL, IDR_PNG_LIST_DOWN, "PNG" );
					pImageItem->SetFunc( strImageFun );
				}
				else if ( strListType == "AddrDelNoItem" )
				{
					pImageItem->SetItemRect(CRect(0, 0, 21, 21));
					pImageItem->SetImage( IDR_PNG_EDITDELETE, IDR_PNG_EDITDELETE, "PNG" );
					pImageItem->SetFunc( "AddrDelNoItem" );
				}
				else
				{
					if ( tAddrItem.emItemType == emEntryItem )
					{
						if ( tAddrItem.strImg == "AddrEditUnSelItem" )
						{
							pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
						}
						else
						{
							pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKDOWN, "PNG" );
						}
					}
					else
					{
						CRect rt(0,0,39,47);
						pImageItem->SetItemRect( rt );

						pImageItem->SetImage( IDR_PNG_LIST_ENTER, IDR_PNG_LIST_ENTERDOWN, "PNG" );
					}

					pImageItem->SetFunc( strImageFun );
				}
			}

			
			pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
			SAFE_RELEASE(pImageItem);
			
			

			if ( bShowOnline )
			{
				if ( tAddrItem.emItemType == emEntryItem )
				{
					// 添加 图标 
					pImageItem = new CImageItem( "", 50, 29 );

					if ( tAddrItem.tAddrInfo.bOnLine )
					{
						pImageItem->SetImage( IDR_PNG_ADDREDITWND_ICON_ONLINE, IDR_PNG_ADDREDITWND_ICON_ONLINE, "PNG" );
					}
					else
					{
						pImageItem->SetImage( IDR_PNG_ADDREDITWND_ICON_OFFLINE, IDR_PNG_ADDREDITWND_ICON_OFFLINE, "PNG" );
					}
					
					
					//pImageItem->SetFunc( strImageFun );
					pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
					SAFE_RELEASE(pImageItem);
				}
			}
		}
	}
	return true;
}

//会议模板中的cns列表
bool CTouchListHelp::TransData(  IItemList* pList , Value_TouchListTempCns &val /* TEpAddrList  &tCnsLst  ,  String strClickItemFunc,  ARRAY<String> * pVctSubItem,BOOL32 bDrag*/)
{
    IBaseItem* pBaseItem = pList->GetItemData();
	CLayoutAlgorithm_Vert::nXSpace = 4;
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert ); 
    pBaseItem->SetMoveStatus(true);
	
    TEpAddrList tCnsLst  = val.m_tCnsLst;
    vector<TEpAddr> vctCnsList;
    int count =  tCnsLst.m_wNum;
    for ( int i = 0; i < count; i++ )
    {
        vctCnsList.push_back( tCnsLst.m_tCnsList[i] );
    }
    
    //sort( vctCnsList.begin(), vctCnsList.end(), CListChild::TempCnsCompare );
    
    for ( int j = 0; j< count ; j++ )
    {   
        String strText = vctCnsList[j].m_tAlias.m_abyAlias;  
		if ( strText.empty() )
		{
			strText = vctCnsList[j].m_tE164.m_abyAlias;
		}

        if ( val.m_wChairManID == vctCnsList[j].m_wEpID ) 
        { 
            continue;  //主cns不在列表中显示
        }

		if ( val.m_nImageId == IDR_PNG_LIST_ADD )
		{
			std::set<CString>::iterator iter =  val.m_setClickedName.find(strText.c_str());
			if ( iter != val.m_setClickedName.end() )
			{
				continue;
			}
		}
			
        Data_CnsAddr userData( vctCnsList[j] );
        userData.SetDataKey( vctCnsList[j].m_wEpID ); 
		
		String strImageFun = val.m_strClickItemFunc;
		strImageFun += "Icon";

		CListItem* plistItem = new CListItem( "", 0, 40 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_SHORTLEFT, IDR_PNG_LISTITEM_SHORTMID, IDR_PNG_LISTITEM_SHORTRIGHT,
				IDR_PNG_LISTITEM_SHORTLEFTSEL, IDR_PNG_LISTITEM_SHORTMIDSEL, IDR_PNG_LISTITEM_SHORTRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			plistItem->SetDragStatus(true);
			
			Data_CnsAddr data( userData);
			data.SetDataKey( j );
			plistItem->SetUserData( &data ); 
			
			if ( val.m_strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( val.m_strClickItemFunc );
			}
			
		}
		
		IItemList *pNew = pList->AddItem( j, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		CTextItem* pTextItem = new CTextItem( "", 300, 40 );
		pTextItem->SetText( strText );
		
		Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );
		
		pNew->AddItem( 0, pTextItem, emGroup );
		
		SAFE_RELEASE(pTextItem);
		
		// 添加 图标 
		CImageItem* pImageItem = new CImageItem( "", 29, 29 );

		if ( val.m_nImageId == IDR_PNG_LIST_ADD )
		{
			pImageItem->SetImage( IDR_PNG_LIST_ADD, IDR_PNG_LIST_ADDDOWN, "PNG" );
		}
		else if( val.m_nImageId == IDR_PNG_LIST_NOCHECK/* || val.m_nImageId == IDR_PNG_LIST_CHECKSEL */)
		{
			std::set<CString>::iterator iter =  val.m_setSelectedName.find(strText.c_str());
			if ( iter != val.m_setSelectedName.end() )
			{
				pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
			}
			else
			{
				pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKSEL, "PNG" );
			}
		}
		else
		{
			pImageItem->SetImage( val.m_nImageId, val.m_nImageId, "PNG" );
		}
	
		if ( val.m_nImageId != 0 )
		{
			pImageItem->SetFunc( strImageFun );
		}

		pNew->AddItem( 1, pImageItem ,emGroup ); 
		SAFE_RELEASE(pImageItem);
    }
    return true;
}

//会议模板中轮询列表
bool CTouchListHelp::TransData( IItemList* pList,  TCMSConfTemplate &tConfTemp,  String strClickItemFunc, bool bIsShowIcon, ARRAY<String> * pVctSubItem,BOOL32 bDrag)
{     
    IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);
	
    for ( int i = 0; i < tConfTemp.m_tTurnList.m_wNum; i++ )
    {  
        String strText = "";
        u16 wCnsID = tConfTemp.m_tTurnList.m_awList[i] - 1;
        TEpAddr *p = tConfTemp.GetCnsAddrByID( wCnsID ) ;
        if ( p != NULL )
        {
            strText = p->m_tAlias.m_abyAlias;
			if ( strText.empty() )
			{
				strText = p->m_tE164.m_abyAlias;
			}
        }
        
        Data_CnsID userData( wCnsID + 1 );
        userData.SetDataKey(i); 

		if ( strText.size() <= 0 )
		{
			continue;
		}

		String strImageFun = strClickItemFunc;
		strImageFun += "Icon";

		CListItem* plistItem = new CListItem( "", 0, 40 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_SHORTLEFT, IDR_PNG_LISTITEM_SHORTMID, IDR_PNG_LISTITEM_SHORTRIGHT,
				IDR_PNG_LISTITEM_SHORTLEFTSEL, IDR_PNG_LISTITEM_SHORTMIDSEL, IDR_PNG_LISTITEM_SHORTRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			
			Data_CnsID data( userData);
			data.SetDataKey( i );
			plistItem->SetUserData( &data ); 
			
			if ( strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( strClickItemFunc );
			}
			
		}
		
		IItemList *pNew = pList->AddItem( i, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		CTextItem* pTextItem = new CTextItem( "", 300, 40 );
		pTextItem->SetText( strText );
		
		Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );
		
		pNew->AddItem( 0, pTextItem, emGroup );
		
		SAFE_RELEASE(pTextItem);

		if ( bIsShowIcon )
		{
			// 添加 图标 
			CImageItem* pImageItem = new CImageItem( "", 29, 29 );
			pImageItem->SetImage( IDR_PNG_LIST_DEL, IDR_PNG_LIST_DOWN, "PNG" );
			pImageItem->SetFunc( strImageFun );
			pNew->AddItem( 1, pImageItem ,emGroup ); 

			SAFE_RELEASE(pImageItem);
		}
    }
    return true;
}

//当前会议列表
bool CTouchListHelp::TransData( IItemList* pList,Value_TouchListConf &val)
{
    if ( val.m_pTplAryConf == NULL )
    {   
        TRACE("\n[CTouchListHelp::TransData] 会议列表中数据为空\n");
        return false;
    }

	sort( val.m_pTplAryConf->begin(), val.m_pTplAryConf->end(), CListChild::CurConfCompare );

    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetSortAlgorithm( IAlgorithm::strCharacter );
    pBaseItem->SetMoveStatus(true);

	String strMeetName;
	String strChairName;
	CString strDate;
	CString strTime; 
	TCMSConf tCmsConf;

    for ( s32 nIndex = 0; nIndex < val.m_pTplAryConf->size(); nIndex++ )
    {  
		//Data_Conf ConfTmpData( *( &val.m_pTplAryConf->at(nIndex) ) );
		//ConfTmpData.SetDataKey( val.m_pTplAryConf->at(nIndex).m_wConfID );
		
		tCmsConf = val.m_pTplAryConf->at(nIndex);

		u16 nConfId = tCmsConf.m_wConfID;
 		String strAlias = tCmsConf.m_achConfName;
 		
		strChairName = tCmsConf.GetChairManAliars();
		strMeetName = tCmsConf.m_achConfName;
	
		time_t tmStartTime = tCmsConf.m_tStartTime;
		//SYSTEMTIME sysStartTime(tmStartTime);
		//tm* tmTime;
		//tmTime = localtime( &tmStartTime );
		//strDate.Format("%d.%d.%d", sysStartTime.wYear, sysStartTime.wMonth, sysStartTime.wDay );
		//strTime.Format("%d:%d", sysStartTime.wHour, sysStartTime.wMinute );

		CTime ctmStartTime( tmStartTime );
		strDate = ctmStartTime.Format("%Y.%m.%d");
		strTime = ctmStartTime.Format("%H:%M");

		u16 nChairId = tCmsConf.GetChairCnsID();

		CListItem* plistItem = new CListItem( "", 0, 50 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
				IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strHoriConfLst ); 
			
			Data_Conf dataConfTmp( tCmsConf );
			dataConfTmp.SetDataKey( tCmsConf.m_wConfID );
			plistItem->SetUserData( &dataConfTmp ); 
			
			if ( val.m_strItemFunc.size() > 0 )
			{
				plistItem->SetFunc( val.m_strItemFunc );	
			}
		}
		
		IItemList *pNew = pList->AddItem( nIndex, plistItem, emGroup );

		SAFE_RELEASE(plistItem);
		
		String strImageFun = val.m_strItemFunc;
		strImageFun += "Icon";
		Font* pFont = NULL;
		
		{
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 	
			CExTextItem* pTextItem = new CExTextItem( "", 0, 50, StringAlignmentNear );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			pTextItem->SetFontColor( Color(46, 55, 76) );
			pTextItem->SetSelColor( Color(255, 255, 255) );
			pTextItem->SetText( (String)strDate );
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
			pTextItem->AddText( (String)strTime, pFont,  Color(46, 55, 76), StringAlignmentNear );
			
			pNew->AddItem( 2, pTextItem, emGroup );
	
			SAFE_RELEASE(pTextItem);
		}
		
		{
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 	
			CExTextItem* pTextItem = new CExTextItem( "", 0, 50, StringAlignmentNear );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			pTextItem->SetFontColor( Color(46, 55, 76) );
			pTextItem->SetSelColor( Color(255, 255, 255) );
			pTextItem->SetText( "会议名称" );
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
			pTextItem->AddText( "主会场", pFont,  Color(46, 55, 76), StringAlignmentNear );
			
			pNew->AddItem( 1, pTextItem, emGroup );

			SAFE_RELEASE(pTextItem);

		}
		
		{
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 	
			CExTextItem* pTextItem = new CExTextItem( "", 0, 50, StringAlignmentNear );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			pTextItem->SetFontColor( Color(46, 55, 76) );
			pTextItem->SetSelColor( Color(255, 255, 255) );
			pTextItem->SetText( strAlias );
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
			pTextItem->AddText( strChairName, pFont,  Color(46, 55, 76), StringAlignmentNear );
			
			pNew->AddItem( 0, pTextItem, emGroup );
			
			SAFE_RELEASE(pTextItem);
		}
		
		{
			// 添加 图标 
			CImageItem* pImageItem = new CImageItem( "", 29, 29 );
			std::set<u16>::iterator iter = val.m_setClickedId.find(nConfId);
			if ( iter != val.m_setClickedId.end() )
			{
				pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
			}
			else
			{
				pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKSEL, "PNG" );
			}
			
			pImageItem->SetFunc( strImageFun );
			pNew->AddItem( 3, pImageItem ,emGroup ); 

			SAFE_RELEASE(pImageItem);
		}

    }

    return true;
}


//预约会议列表
bool CTouchListHelp::TransData( Value_TouchListOrderConf &val, IItemList* pList ) 
{
	if ( pList == NULL || val.m_pvctConfTemplate == NULL )
    {
        return false;
    }
	
    IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true); 

	vector<TCMSConfTemplate> m_pvcConfTmp;
	for ( s32 nIndexTmp = 0; nIndexTmp < val.m_pvctConfTemplate->Size(); nIndexTmp++ )
    {
		TCMSConfTemplate tConfTmp;
		m_pvcConfTmp.push_back(val.m_pvctConfTemplate->GetAt(nIndexTmp));
	}

//	std::sort( m_pvcConfTmp.begin(), m_pvcConfTmp.end(), CListChild::OrderConfTempCompare );

	CListChild::ConfTemplateCompare( &m_pvcConfTmp );
    
    s32 nCount =  m_pvcConfTmp.size(); 
	for ( s32 nIndex = 0; nIndex < nCount; nIndex++ )
    {
		Data_OrderConf ConfTmpData( m_pvcConfTmp.at(nIndex)  );
		ConfTmpData.SetDataKey( m_pvcConfTmp.at(nIndex).m_wID );
		
		String strAlias = m_pvcConfTmp.at(nIndex).m_achConfName;
		u16 nTmpId = m_pvcConfTmp.at(nIndex).m_wID;

		time_t tmStart = m_pvcConfTmp.at(nIndex).m_tStartTime;
		if ( tmStart == 0 )
		{
			continue;
		}
		CTime ctmStartTime(tmStart);
		String strDate = ctmStartTime.Format("%Y.%m.%d");
		String strTime = ctmStartTime.Format("%H:%M");

		String strHomeMeet;
 		strHomeMeet = m_pvcConfTmp.at(nIndex).m_atEpList.m_tCnsList->m_tAlias.m_abyAlias;
		if ( strHomeMeet.empty() )
		{
			strHomeMeet = m_pvcConfTmp.at(nIndex).m_atEpList.m_tCnsList->m_tE164.m_abyAlias;
		}
		
		CListItem* plistItem = new CListItem( "", 0, 50 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
				IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			plistItem->SetLayoutAlgorithm( IAlgorithm::strHoriConfLst ); 
			
			Data_OrderConf dataConfTmp( ConfTmpData );
			dataConfTmp.SetDataKey( nIndex );
			plistItem->SetUserData( &dataConfTmp ); 
			
			if ( val.m_strItemFunc.size() > 0 )
			{
				plistItem->SetFunc( val.m_strItemFunc );	
			}
		}
		
		IItemList *pNew = pList->AddItem( nIndex, plistItem, emGroup );

		SAFE_RELEASE(plistItem);

		String strImageFun = val.m_strItemFunc;
		strImageFun += "Icon";
		Font* pFont = NULL;
		
		{
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 	
			CExTextItem* pTextItem = new CExTextItem( "", 0, 50, StringAlignmentNear );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			pTextItem->SetFontColor( Color(46, 55, 76) );
			pTextItem->SetSelColor( Color(255, 255, 255) );
			pTextItem->SetText( strDate );
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
			pTextItem->AddText( strTime, pFont,  Color(46, 55, 76), StringAlignmentNear );
			
			pNew->AddItem( 2, pTextItem, emGroup );
			
			delete pTextItem;
			pTextItem = NULL;
		}

		{
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 	
			CExTextItem* pTextItem = new CExTextItem( "", 0, 50, StringAlignmentNear );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			pTextItem->SetFontColor( Color(46, 55, 76) );
			pTextItem->SetSelColor( Color(255, 255, 255) );
			pTextItem->SetText( "会议名称" );
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
			pTextItem->AddText( "主会场", pFont,  Color(46, 55, 76), StringAlignmentNear );
			
			pNew->AddItem( 1, pTextItem, emGroup );
			
			delete pTextItem;
			pTextItem = NULL;
		}

		{
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 	
			CExTextItem* pTextItem = new CExTextItem( "", 0, 50, StringAlignmentNear );
			pTextItem->SetFont( pFont );
			pTextItem->SetAlignment( StringAlignmentNear );
			pTextItem->SetFontColor( Color(46, 55, 76) );
			pTextItem->SetSelColor( Color(255, 255, 255) );
			pTextItem->SetText( strAlias );
			pFont = CSrcManage::GetFont( "微软雅黑", 11 ); 
			pTextItem->AddText( strHomeMeet, pFont,  Color(46, 55, 76), StringAlignmentNear );
		
			pNew->AddItem( 0, pTextItem, emGroup );
			SAFE_RELEASE(pTextItem);	
		}
		
		{
			// 添加 图标 
			CImageItem* pImageItem = new CImageItem( "", 29, 29 );
			std::set<u16>::iterator iter = val.m_setClickedId.find(nTmpId);
			if ( iter != val.m_setClickedId.end() )
			{
				pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKDOWN, "PNG" );
			}
			else
			{
				pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKSEL, "PNG" );
			}
			
			pImageItem->SetFunc( strImageFun );
			pNew->AddItem( 3, pImageItem ,emGroup ); 

			SAFE_RELEASE(pImageItem);
		}
		
 	}
    
	return true;
}



bool CTouchListHelp::TransData( IItemList* pList, Value_ListConfInfo &val)
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

    s32 count = val.m_tConf.m_tplCnsList.Size();
    
    vector<TCnsInfo> vctCnsList;
    for ( int i = 0; i < count; i++ )
    {
        vctCnsList.push_back( val.m_tConf.m_tplCnsList.GetAt(i) );
    }
    
	sort( vctCnsList.begin(), vctCnsList.end(), CListChild::CnsInfoCompare );

    for ( i = 0; i < count; i++ )
    {  
        TCnsInfo tCnsInfo = vctCnsList.at(i);
        EmTPEndpointType emType = tCnsInfo.m_emEpType;
        if ( emTPEndpointTypeCNS != emType &&  emTPEndpointH323MT != emType && emTPEndpointH323SingleMCU != emType )
        {   //如果类型不是cns则过滤掉，不显示
            continue;
        }

        if ( !tCnsInfo.m_bOnline )
        {
            continue;
        }
        
        String strTxt = tCnsInfo.m_achRoomName; 

        CListItem* plistItem = new CListItem( "", 0, 50 );
        if ( plistItem != NULL )
        {		
            plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
                IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
                IDR_PNG_LIST_SPLIT );
            plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
            plistItem->SetDragStatus( true );
            
            Data_ConfCns dataConfCns( tCnsInfo );
            dataConfCns.SetDataKey( tCnsInfo.m_wEpID );
            plistItem->SetUserData( &dataConfCns ); 
                       
            plistItem->SetFunc( val.m_strClickItemFunc );	
        }
        
        IItemList *pNew = pList->AddItem( i, plistItem, emGroup );  
		SAFE_RELEASE(plistItem);

        CTextItem* pTextItem = new CTextItem( "", 300, 40 );
        pTextItem->SetText( strTxt );
        
        Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
        pTextItem->SetFont( pFont );
        pTextItem->SetAlignment( StringAlignmentNear );
        
        pTextItem->SetFontColor( Color(46, 55, 76) );
        pTextItem->SetSelColor( Color(255, 255, 255) );
        
        pNew->AddItem( 0, pTextItem, emGroup );
		SAFE_RELEASE(pTextItem);

        if ( val.m_bShowIcon )
        {
            CImageItem* pImageItem = new CImageItem( "", 29, 29 );       
            if ( pImageItem != NULL )
            {
                pImageItem->SetImage( IDR_PNG_LIST_ADD, IDR_PNG_LIST_ADD, "PNG", IDR_PNG_LIST_ADDDOWN );
                
                pImageItem->SetFunc( val.m_strSubItemFunc );
            }
            
            pNew->AddItem( 1, pImageItem, emGroup );
		    SAFE_RELEASE(pTextItem);
        }      
       
    }

    return true;
}


bool CTouchListHelp::TransData( IItemList* pList, Value_ListConf& val )
{
    if ( val.m_pvctAryConf == NULL )
    {   
        TRACE("\n[CTouchListHelp::TransData] 会议列表中数据为空\n");
        return false;
    }
      
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

    sort( val.m_pvctAryConf->begin(), val.m_pvctAryConf->end(), CListChild::CurConfCompare );
    
    TCMSConf tCmsConf;
    
    for ( s32 nIndex = 0; nIndex < val.m_pvctAryConf->size(); nIndex++ )
    {
        tCmsConf = val.m_pvctAryConf->at(nIndex);
      
        u16 nConfId = tCmsConf.m_wConfID;
 		String strTxt = tCmsConf.m_achConfName;

        CListItem* plistItem = new CListItem( "", 0, 50 );
        if ( plistItem != NULL )
        {		
            plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
                IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
                IDR_PNG_LIST_SPLIT );
            plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 

            Data_Conf confData( tCmsConf );
            confData.SetDataKey( nConfId );
            
            plistItem->SetUserData( &confData ); 
            
            plistItem->SetFunc( val.m_strItemFunc );
        }

        IItemList *pNew = pList->AddItem( nIndex, plistItem, emGroup );  
        SAFE_RELEASE(plistItem);
            
        CTextItem* pTextItem = new CTextItem( "", 300, 50 );
        pTextItem->SetText( strTxt );
        
        Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
        pTextItem->SetFont( pFont );
        pTextItem->SetAlignment( StringAlignmentNear );
        
        pTextItem->SetFontColor( Color(46, 55, 76) );
        pTextItem->SetSelColor( Color(255, 255, 255) );
        
        pNew->AddItem( 0, pTextItem, emGroup );
        SAFE_RELEASE(pTextItem);
        
        CImageItem* pImageItem = new CImageItem( "", 39, 47 );       
        if ( pImageItem != NULL )
        {
            pImageItem->SetImage( IDR_PNG_LIST_ENTER, IDR_PNG_LIST_ENTERDOWN, "PNG" );
        }
        
        pNew->AddItem( 1, pImageItem, emGroup );
        SAFE_RELEASE(pTextItem);
    }
    
    return true;
}


bool CTouchListHelp::TransData( IItemList* pList, Value_ListConfCns &val)
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);
    
    sort( val.m_pvctCnsList->begin(), val.m_pvctCnsList->end(), CListChild::CnsInfoCompare );
    
    for ( int i = 0; i < val.m_pvctCnsList->size(); i++ )
    {  
        TCnsInfo tCnsInfo = val.m_pvctCnsList->at(i);
        EmTPEndpointType emType = tCnsInfo.m_emEpType;
        if ( emTPEndpointTypeCNS != emType &&  emTPEndpointH323MT != emType && emTPEndpointH323SingleMCU != emType )
        {   //如果类型不是cns则过滤掉，不显示
            continue;
        }

        if ( !tCnsInfo.m_bOnline )
        {
            continue;
        }
        
        String strTxt = tCnsInfo.m_achRoomName; 
        
        CListItem* plistItem = new CListItem( "", 0, 50 );
        if ( plistItem != NULL )
        {		
            plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
                IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
                IDR_PNG_LIST_SPLIT );
            plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
            
            Data_ConfCns dataConfCns( tCnsInfo );
            dataConfCns.SetDataKey( tCnsInfo.m_wEpID );
            plistItem->SetUserData( &dataConfCns ); 
            
            plistItem->SetFunc( val.m_strClickItemFunc );	
        }
        
        IItemList *pNew = pList->AddItem( i, plistItem, emGroup );  
        SAFE_RELEASE(plistItem);
        
        CTextItem* pTextItem = new CTextItem( "", 300, 40 );
        pTextItem->SetText( strTxt );
        
        Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
        pTextItem->SetFont( pFont );
        pTextItem->SetAlignment( StringAlignmentNear );
        
        pTextItem->SetFontColor( Color(46, 55, 76) );
        pTextItem->SetSelColor( Color(255, 255, 255) );
        
        pNew->AddItem( 0, pTextItem, emGroup );
        SAFE_RELEASE(pTextItem);
        
        if ( val.m_bShowIcon )
        {
            CImageItem* pImageItem = new CImageItem( "", 29, 29 );       
            if ( pImageItem != NULL )
            {
                pImageItem->SetImage( IDR_PNG_LIST_ADD, IDR_PNG_LIST_ADDDOWN, "PNG" );
    
                pImageItem->SetFunc( val.m_strSubItemFunc );
            }

            pNew->AddItem( 1, pImageItem, emGroup );
            SAFE_RELEASE(pTextItem);
        }
    }
    
    return true;
}


bool CTouchListHelp::TransData( IItemList* pList, Value_ViewListTvw &val )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strTvwView );
    pBaseItem->SetMoveStatus(true);

    TListRangeInfo tRangeInfo;
    tRangeInfo.nMaxColumn = val.m_nColumn;
    tRangeInfo.nHoriSpace = 4;
    
    Data_ListRangeInfo dataRangeInfo( tRangeInfo );
    pBaseItem->SetUserData( &dataRangeInfo ); 

    for ( int i = 0; i < val.m_pTvwList->size(); i++ )
    {
        TTvwCns tTvwInfo = val.m_pTvwList->at(i); 

        CImageItem* pCnsItem = new CImageItem( "", 126, 101 );
        if ( pCnsItem == NULL )
        {
            return false;
        }
        
        if ( tTvwInfo.m_wScreenNum == 3 )
        {
            pCnsItem->SetItemRect( CRect(0 ,0, 386, 101) );
            pCnsItem->SetImageOffset( CPoint( 0, 101 - 42 ) );
            pCnsItem->SetImage( IDR_PNG_TVW_GROUPBKG, IDR_PNG_TVW_GROUPBKG, "PNG" );  
        }
        pCnsItem->SetLayoutAlgorithm( "TvwCns" );
        
        IItemList *pCnsList = pList->AddItem( i, pCnsItem, emGroup );
        SAFE_RELEASE(pCnsItem);

        for ( int n = 0; n < tTvwInfo.m_wScreenNum; n++ )
        {
            THduPlanUnit tHduUnit = tTvwInfo.m_tHduUnit[n];

            Data_TvwInfo tvwInfo(tHduUnit);
            tvwInfo.SetDataKey( tHduUnit.m_wIndex );		
            
            CImageItem* pImageItem = new CImageItem( "", 112 + 4, 83 + 7 );
            if ( pImageItem != NULL )
            {		
                if ( tHduUnit.m_bReged )
                {
                    if ( val.m_bManage )
                    {
                        pImageItem->SetImage( IDR_PNG_TVW, IDR_PNG_TVW, "PNG" );
                    }
                    else
                    {
                        pImageItem->SetImage( IDR_PNG_TVW, IDR_PNG_TVWDOWN, "PNG" );
                    }                 
                }
                else
                {
                    if ( val.m_bManage )
                    {
                        pImageItem->SetImage( IDR_PNG_TVW_OFFLINE, IDR_PNG_TVW_OFFLINE, "PNG" );
                    }
                    else
                    {
                        pImageItem->SetImage( IDR_PNG_TVW_OFFLINE, IDR_PNG_TVW_OFFLINEDOWN, "PNG" ); 
                    }                 
                }
                
                pImageItem->SetImageOffset( CPoint( 0, 7 ) );
                pImageItem->SetLayoutAlgorithm( IAlgorithm::strTvwItem  );  
                pImageItem->SetUserData( &tvwInfo );
                pImageItem->SetFunc( val.m_strClickItemFunc );               
            }
            
            IItemList *pNew = pCnsList->AddItem( n, pImageItem, emGroup );
            SAFE_RELEASE(pImageItem);
          
            if ( tHduUnit.m_bValid )
            {
                if ( tHduUnit.m_tName.IsEmpty() )
                {
                    //电视墙配置过且没有会场进墙时，显示配置的单板名及通道号
                    CExTextItem* pTextItem = new CExTextItem( "", 104, 75 );
                    if ( pTextItem != NULL )
                    {
                        pTextItem->SetText( tHduUnit.m_tHduName.m_abyAlias );
                        
                        Font* pFont = CSrcManage::GetFont( "微软雅黑", 11 );
                        pTextItem->SetFont( pFont );
                        pTextItem->SetAlignment( StringAlignmentCenter );   
                        pTextItem->SetLineAlignment( StringAlignmentFar ); 
                        Color col;
                        Color colSel;
                        if ( tHduUnit.m_bReged )
                        {
                            col = Color(38, 54, 66);
                            colSel = Color(38, 54, 66);                           
                        }
                        else
                        {
                            col = Color(105, 114, 121);                              
                            if ( val.m_bManage )
                            {
                                colSel = Color(105, 114, 121);  
                            }   
                            else
                            {
                                colSel = Color(38, 54, 66);  
                            }
                        } 
                        pTextItem->SetFontColor( col );
                        pTextItem->SetSelColor( colSel );

                        CString strChan;
                        strChan.Format( "[%d]", tHduUnit.m_wChannel );
                        pTextItem->AddText( (LPCTSTR)strChan, pFont, col, StringAlignmentCenter );
                        
                        pNew->AddItem( 0, pTextItem, emGroup );                       
                        SAFE_RELEASE(pTextItem);
                    }
                }
                else
                {               
                    CTextItem* pTextItem = new CTextItem( "", 104, 75 );
                    if ( pTextItem != NULL )
                    {
                        pTextItem->SetText( tHduUnit.m_tName.m_abyAlias );
                    
                        Font* pFont = CSrcManage::GetFont( "微软雅黑", 11 );
                        pTextItem->SetFont( pFont );
                        pTextItem->SetAlignment( StringAlignmentCenter );                   
                        if ( tHduUnit.m_bReged )
                        {
                            pTextItem->SetFontColor( Color(38, 54, 66) );
                            pTextItem->SetSelColor( Color(38, 54, 66) );
                        }
                        else
                        {
                            pTextItem->SetFontColor( Color(105, 114, 121) ); 
                            if ( val.m_bManage )
                            {
                                pTextItem->SetSelColor( Color(105, 114, 121) );
                            }   
                            else
                            {
                                pTextItem->SetSelColor( Color(38, 54, 66) );
                            }
                        }                      
                    
                        pNew->AddItem( 0, pTextItem, emGroup );                   
                        SAFE_RELEASE(pTextItem);
                    }
                }
            }    
            else
            {
                CTextItem* pTextItem = new CTextItem( "", 104, 75 );
                if ( pTextItem != NULL )
                {
                    pNew->AddItem( 0, pTextItem, emGroup );                  
                    SAFE_RELEASE(pTextItem);
                }
            }
            
            CImageItem *pIconItem = new CImageItem( "", 19, 19 );
            if ( pIconItem != NULL )
            {
                if ( tHduUnit.m_bReged )
                {
                    pIconItem->SetImage( IDR_PNG_TVWICON_ONLINE, IDR_PNG_TVWICON_ONLINE, "PNG" ); 
                }
                else
                {
                    pIconItem->SetImage( IDR_PNG_TVWICON_OFFLINE, IDR_PNG_TVWICON_OFFLINE, "PNG" ); 
                }
                                
                pNew->AddItem( 1, pIconItem, emGroup );         
                SAFE_RELEASE(pIconItem);
            }

            if ( val.m_bManage && !tHduUnit.m_tName.IsEmpty() )
            {
                CImageItem *pDelItem = new CImageItem( "", 29, 29 );
                if ( pDelItem != NULL )
                {                  
                    pDelItem->SetImage( IDR_PNG_LIST_DEL, IDR_PNG_LIST_DOWN, "PNG" );   
                    String strImageFun = val.m_strClickItemFunc + "Icon";
                    pDelItem->SetFunc( strImageFun );
                    pNew->AddItem( 2, pDelItem, emGroup );         
                    SAFE_RELEASE(pDelItem);
                }            
            }
        }  
              
    }

    return true;
}

//录像机文件列表
bool CTouchListHelp::TransData( IItemList* pList, Value_ListFile &val )
{
	IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );

	String strClickItemFunc = val.m_strItemFunc;
	String strImageFun = val.m_strItemFunc + "Icon";
	
	//排序
	sort( val.m_pVecTRecFileInfo->begin(), val.m_pVecTRecFileInfo->end(), CListChild::VtrFileListItemCompare );


    s32 nKey = 0;
	vector<TRecFileInfo>::iterator it = val.m_pVecTRecFileInfo->begin();
	for ( ; it < val.m_pVecTRecFileInfo->end(); it++ )
	{
		Data_FileInfo data(*it); 
		
		CListItem* plistItem = new CListItem( "", 0, 50 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
				IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			
			data.SetDataKey( nKey );
			plistItem->SetUserData( &data ); 
			if ( strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( strClickItemFunc );	
			}
			
		}
		
		IItemList *pNew = pList->AddItem( nKey, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		
		int nIndex = 0;
		Font* pFont = NULL;
		CTextItem* pTextItem = NULL;
		CImageItem* pImageItem = NULL;


		pTextItem = new CTextItem( "", 0, 50 );
		pTextItem->SetText( it->m_szFilelName );
		pFont = CSrcManage::GetFont( "微软雅黑", 13 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );
		
		pNew->AddItem( 0, pTextItem, emGroup );
		SAFE_RELEASE(pTextItem);
		
		
		
		// 添加 图标 
		switch( val.m_nType )
		{
		case 0:
			{
				bool bFind = false;
				if ( val.m_pVecTRecFileInfoSel != NULL )
				{
					vector<TRecFileInfo>::iterator itSel = val.m_pVecTRecFileInfoSel->begin();
					for( ; itSel != val.m_pVecTRecFileInfoSel->end(); itSel++ )
					{
						if ( it->m_byEqpID == itSel->m_byEqpID && strncmp(it->m_szFilelName, itSel->m_szFilelName, TP_REC_FILE_LEN) == 0 )
						{
							pImageItem = new CImageItem( "", 29, 29 );
							pImageItem->SetImage( IDR_PNG_LIST_CHECKSEL, IDR_PNG_LIST_CHECKSEL, "PNG" );
							pImageItem->SetFunc( strImageFun );
							pNew->AddItem( 1, pImageItem ,emGroup ); 
							SAFE_RELEASE(pImageItem);
							bFind = true;
							break;
						}
					}
				}
				
				if (!bFind)
				{
					pImageItem = new CImageItem( "", 29, 29 );
					pImageItem->SetImage( IDR_PNG_LIST_NOCHECK, IDR_PNG_LIST_CHECKDOWN, "PNG" );
					pImageItem->SetFunc( strImageFun );
					pNew->AddItem( 1, pImageItem ,emGroup ); 
					SAFE_RELEASE(pImageItem);
				}
			}
			break;
		case 1:
			{
				CImageItem* pImageItem = new CImageItem( "", 29, 29 );
				pImageItem->SetImage( IDR_PNG_LIST_DEL, IDR_PNG_LIST_DOWN, "PNG" );
				pImageItem->SetFunc( strImageFun );
				pNew->AddItem( 1, pImageItem ,emGroup ); 
				
				SAFE_RELEASE(pImageItem);
			}
			break;
		case 2:
			{
				pImageItem = new CImageItem( "", 29, 29 );
				pImageItem->SetImage( IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_SEL, "PNG" );
				pNew->AddItem( 1, pImageItem ,emGroup ); 
				SAFE_RELEASE(pImageItem);
			}
			break;
		default:
			break;
		}
		
		nKey++;
	}

	return true;
}

//录像和回放
bool CTouchListHelp::TransData( IItemList* pList, Value_ListRecord &val )
{
	//排序
	sort( val.m_pVecTUmcConfInfo->begin(), val.m_pVecTUmcConfInfo->end(), CListChild::RecConfCompare );

	IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
	
	String strClickItemFunc = val.m_strItemFunc;
	String strImageFun = val.m_strItemFunc + "Icon";
	
    s32 nKey = 0;
	vector<TUmcConfInfo>::iterator it = val.m_pVecTUmcConfInfo->begin();
	for ( ; it != val.m_pVecTUmcConfInfo->end(); it++ )
	{
		Data_RecordInfo data(it); 
		
		CListItem* plistItem = new CListItem( "", 0, 40 );
		if ( plistItem != NULL )
		{
			plistItem->SetImage( IDR_PNG_LISTITEM_SHORTLEFT, IDR_PNG_LISTITEM_SHORTMID, IDR_PNG_LISTITEM_SHORTRIGHT,
				IDR_PNG_LISTITEM_SHORTLEFTSEL, IDR_PNG_LISTITEM_SHORTMIDSEL, IDR_PNG_LISTITEM_SHORTRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			
			data.SetDataKey( nKey );
			plistItem->SetUserData( &data ); 
			if ( strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( strClickItemFunc );	
			}
			
		}
		
		IItemList *pNew = pList->AddItem( nKey, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		
		int nIndex = 0;

		//添加文字
		CTextItem* pTextItem = new CTextItem( "", 300, 40 );
		pTextItem->SetText( it->m_achConfName );
		Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );
		pNew->AddItem( nIndex++, pTextItem, emGroup );
		SAFE_RELEASE(pTextItem);
		
		
		
		// 添加 图标 
		CImageItem* pImageItem = NULL;
		pImageItem = new CImageItem( "", 39, 47 );
		pImageItem->SetImage( IDR_PNG_LIST_ENTER, IDR_PNG_LIST_ENTERDOWN, "PNG" );
		pImageItem->SetFunc( strImageFun );
		pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
		SAFE_RELEASE(pImageItem);

		bool bRecordEp = false;
		bool bRecord = false;
		vector<TUmcRecInfo>::iterator itEp = it->m_vecTRecInfo.begin();
		for ( ; itEp != it->m_vecTRecInfo.end(); itEp++ )
		{
			if ( itEp->m_emState == em_rec_working || itEp->m_emState == em_rec_pause )
			{
				if ( itEp->m_tInfo.m_tMtRecInfo.m_wMtID != 0 && itEp->m_tInfo.m_emType == em_rec_recorder_mt )
				{
					bRecordEp = true;
				}

				if ( itEp->m_tInfo.m_wConfID != 0 && itEp->m_tInfo.m_emType == em_rec_recorder_conf )
				{
					bRecord = true;
				}
			}
			
		}

		if ( bRecordEp )
		{
			pImageItem = new CImageItem( "", 30, 29);
			pImageItem->SetImage( IDR_PNG_RECORDWND_ICON_RECORDEP, IDR_PNG_RECORDWND_ICON_RECORDEP, "PNG" );
			pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
			SAFE_RELEASE(pImageItem);
		}

		if ( bRecord )
		{
			pImageItem = new CImageItem( "", 30, 29);
			pImageItem->SetImage( IDR_PNG_RECORDWND_ICON_RECORD, IDR_PNG_RECORDWND_ICON_RECORD, "PNG" );
			pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
			SAFE_RELEASE(pImageItem);
		}
		
		if ( it->m_tConfPlayStatus.m_emState == em_rec_working || it->m_tConfPlayStatus.m_emState == em_rec_pause )
		{
			pImageItem = new CImageItem( "", 30, 29);
			pImageItem->SetImage( IDR_PNG_RECORDWND_ICON_PLAY, NULL, "PNG" );
			pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
			SAFE_RELEASE(pImageItem);
		}
		
		
		nKey++;
	}
	
	return true;
}

//录像和回放会场
bool CTouchListHelp::TransData( IItemList* pList, Value_ListRecordEp &val )
{
	//排序
	sort( val.m_pVecTRecInfo->begin(), val.m_pVecTRecInfo->end(), CListChild::RecMtCompare );

	IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
	
	String strClickItemFunc = val.m_strItemFunc;
	String strImageFun = val.m_strItemFunc + "Icon";
	
    s32 nKey = 0;
	vector<TUmcRecInfo>::iterator it = val.m_pVecTRecInfo->begin();
	for ( ; it < val.m_pVecTRecInfo->end(); it++ )
	{
		Data_RecordEpInfo data(it); 
		
		CListItem* plistItem = new CListItem( "", 0, 50 );
		if ( plistItem != NULL )
		{		
			plistItem->SetImage( IDR_PNG_LISTITEM_WIDTHLEFT, IDR_PNG_LISTITEM_WIDTHMID, IDR_PNG_LISTITEM_WIDTHRIGHT,
				IDR_PNG_LISTITEM_WIDTHLEFTSEL, IDR_PNG_LISTITEM_WIDTHMIDSEL, IDR_PNG_LISTITEM_WIDTHRIGHTSEL,
				IDR_PNG_LIST_SPLIT );
			
			plistItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem ); 
			
			data.SetDataKey( nKey );
			plistItem->SetUserData( &data ); 
			if ( strClickItemFunc.size() > 0 )
			{
				plistItem->SetFunc( strClickItemFunc );	
			}
			
		}
		
		IItemList *pNew = pList->AddItem( nKey, plistItem, emGroup );
		
		SAFE_RELEASE(plistItem);
		
		
		int nIndex = 0;
		Font* pFont = NULL;
		CTextItem* pTextItem = NULL;
		CImageItem* pImageItem = NULL;



		pTextItem = new CTextItem( "", 300, 50 );
		pTextItem->SetText( it->m_achName );
		
		pFont = CSrcManage::GetFont( "微软雅黑", 13 );
		pTextItem->SetFont( pFont );
		pTextItem->SetAlignment( StringAlignmentNear );
		
		pTextItem->SetFontColor( Color(46, 55, 76) );
		pTextItem->SetSelColor( Color(255, 255, 255) );

		
		pNew->AddItem( nIndex++, pTextItem, emGroup );
		SAFE_RELEASE(pTextItem);



		if ( it->m_emState == em_rec_pause || it->m_emState == em_rec_working )
		{
			pImageItem = new CImageItem( "", 30, 29);
			pImageItem->SetImage( IDR_PNG_RECORDWND_ICON_RECORDEP, IDR_PNG_RECORDWND_ICON_RECORDEP, "PNG" );
			pNew->AddItem( nIndex++, pImageItem ,emGroup ); 
			SAFE_RELEASE(pImageItem);
		}
		
		nKey++;
	}
	
	return true;
}



/*---------------------------------------------------------------------
* 类	名：CLayoutAlgorithm_TvwView
* 功    能：电视墙视图排列算法
* 特殊说明：用于电视墙配置
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/11/23	v1.0		肖楚然		创建
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_TvwView::Transition( IArgs* pArgs )
{
    Args_ItemList* p = NULL;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }
        
        if ( const Data_ListRangeInfo *pRangeInfo = dynamic_cast<const Data_ListRangeInfo*>( pItem->GetUserData() ) ) 
        {     
            TListRangeInfo tRangeInfo = pRangeInfo->m_tRangeInfo;
           
            int nMaxCol = tRangeInfo.nMaxColumn;
            int nFirstLeft = tRangeInfo.nFirstLeft;
            int nVertSpace = tRangeInfo.nVertSpace;
            int nHoriSpace = tRangeInfo.nHoriSpace;
            if ( nMaxCol == 0 )
            {
                return false;
            }                

            int nTvwCount = 0;
        
            CRect rcLast( 0, 0, 0, 0 );
            for ( int i = 0; i < nItemCounts; i++ )
            {
                IItemList* pSubList = pList->GetItemByIndex( i );
                if ( pSubList == 0 )
                {
                    continue;
                }
                IBaseItem* pItem = pSubList->GetItemData();
                if ( pItem == 0 )
                {
                    continue;
                }
                int nWidht = pItem->GetItemWidth();
                int nHeight = pItem->GetItemHeight();
           
                int nRow = nTvwCount / nMaxCol; //一行nMaxCol个Item
                if( nTvwCount % nMaxCol == 0 )
                {
                    rcLast.SetRect( nFirstLeft, (nHeight + nVertSpace)*nRow, nFirstLeft + nWidht, (nHeight + nVertSpace)*nRow + nHeight );
                }
                else
                {
                    rcLast.SetRect( rcLast.right + nHoriSpace, (nHeight + nVertSpace)*nRow, rcLast.right + nHoriSpace + nWidht, (nHeight + nVertSpace)*nRow + nHeight );
                }
                pItem->SetItemRect( rcLast );

                if ( nWidht == 386 )
                {
                    nTvwCount = nTvwCount + 3;
                }
                else
                {
                    nTvwCount++;
                }            
            }
        }
    }
    return true;
}


bool CLayoutAlgorithm_TvwCns::Transition( IArgs* pArgs )
{
    Args_ItemList* p = NULL;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }
        
        int nParentHeight = pItem->GetItemHeight();
                
        int nFirstLeft = 7;
        int nFirstTop = 0;
        int nHoriSpace = 18 - 4;
        
        CRect rcLast( 0, 0, 0, 0 );
        for ( int i = 0; i < nItemCounts; i++ )
        {
            IItemList* pSubList = pList->GetItemByIndex( i );
            if ( pSubList == 0 )
            {
                continue;
            }
            IBaseItem* pItem = pSubList->GetItemData();
            if ( pItem == 0 )
            {
                continue;
            }
            int nWidht = pItem->GetItemWidth();
            int nHeight = pItem->GetItemHeight();
      
            if ( i == 0 )
            {
                rcLast.SetRect( nFirstLeft, nFirstTop, nFirstLeft + nWidht, nFirstTop + nHeight );
            }
            else
            {
                rcLast.SetRect( rcLast.right + nHoriSpace, nFirstTop, rcLast.right + nHoriSpace + nWidht, nFirstTop + nHeight );
            }
            
            pItem->SetItemRect( rcLast );
        }
    }
    return true;
}

/*---------------------------------------------------------------------
* 类	名：CLayoutAlgorithm_TvwItem
* 功    能：电视墙条目排列算法
* 特殊说明：用于单个电视墙内部
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/11/23	v1.0		肖楚然		创建
----------------------------------------------------------------------*/
bool CLayoutAlgorithm_TvwItem::Transition( IArgs* pArgs )
{
    Args_ItemList* p = NULL;
    if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
    {
        IItemList* pList = p->m_pList;
        if ( pList == 0 )
        {
            return false;
        }
        int nItemCounts = pList->GetItemCount();
        IBaseItem* pItem = pList->GetItemData();
        if ( pItem == 0 )
        {
            return false;
        }
        int nParentWidth = pItem->GetItemWidth();
        int nParentHeight = pItem->GetItemHeight();
        CRect rcLast( 0, 0, 0, 0 );		
        for ( int i = 0; i < nItemCounts; i++ )
        {
            IItemList* pSubList = pList->GetItemByIndex( i );
            if ( pSubList == 0 )
            {
                continue;
            }
            IBaseItem* pSubItem = pSubList->GetItemData();
            if ( pItem == 0 )
            {
                continue;
            }
            int nWidth = pSubItem->GetItemWidth();
            int nHeight = pSubItem->GetItemHeight();

            if ( i == 0 ) 
            {	
                rcLast.SetRect( 4, 11, 4 + nWidth, 11 + nHeight );
                pSubItem->SetItemRect( rcLast );
            }
            else if ( i == 1 )
            {
                rcLast.SetRect( nParentWidth - nWidth - 12, nParentHeight - nHeight - 5, nParentWidth - 12, nParentHeight - 5 );
                pSubItem->SetItemRect( rcLast );
            }
            else
            {
                rcLast.SetRect( nParentWidth - nWidth, 0, nParentWidth, nHeight );
                pSubItem->SetItemRect( rcLast );
            }
        }
    }
    return true;
}

