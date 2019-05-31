// TouchListProperty.h: interface for the CTouchListProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOUCHLISTPROPERTY_H__04260821_1F80_4C85_A679_1B121DF07E09__INCLUDED_)
#define AFX_TOUCHLISTPROPERTY_H__04260821_1F80_4C85_A679_1B121DF07E09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "umclib.h"
#include <set>


//会议模板列表
class Value_TouchListConfTemp : public IValue
{
public:
	Value_TouchListConfTemp( vector<TCMSConfTemplate>* pList,String strItemFunc = IBaseItem::strDefaultFunc,
                             vector<String> * pVctSubItem = NULL, BOOL32 bShowALl = FALSE) 
		: IValue( "TouchListConfTemp" ), m_pvctConfTemplate( pList ), m_strItemFunc( strItemFunc ), m_pVctSubItem( pVctSubItem ), m_bShowAll(bShowALl){}
	vector<TCMSConfTemplate>* m_pvctConfTemplate;
	String m_strItemFunc;			 // 条目点击回调函数 
	std::set<CString> m_setClickedName;
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bShowAll;               //是否全部显示，如果是否，则只显示当前所登录会场是默认主席的模板
};

class Data_ConfTemp : public IData
{
public:
    Data_ConfTemp( TCMSConfTemplate &tConfTemp ) : IData( "ConfTemp" ), m_tConfTemp( tConfTemp ){}
    IData* Clone()
    {
        Data_ConfTemp* pData = new Data_ConfTemp( m_tConfTemp );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TCMSConfTemplate  m_tConfTemp;
};

//会议模板所含的cns列表
class Value_TouchListTempCns : public IValue
{
public: 
    Value_TouchListTempCns( TEpAddrList  &tCnsLst , String strClickItemFunc =  IBaseItem::strDefaultFunc , 
        vector<String> * pVctSubItem = NULL,BOOL bDrag = FALSE , u16 wChaim = -1 )
        : IValue( "TouchListTempCns" ), m_tCnsLst( tCnsLst ),m_strClickItemFunc(strClickItemFunc),  m_pVctSubItem( pVctSubItem ),m_bDrag(bDrag), m_wChairManID( wChaim ){}
     TEpAddrList  m_tCnsLst;           // cns列表 
     u16          m_wChairManID;       //主席对应的cnsID，如果无主席的列表，则为0xffff 
     String  m_strClickItemFunc;	   // 条目点击回调函数
	 UINT	 m_nImageId;
     vector<String> * m_pVctSubItem;   //子条目对应的xml中名字
     BOOL32 m_bDrag;                   //是否可以拖动
	 std::set<CString> m_setClickedName;   //点击添加则更换未Disable状态图标
	 std::set<CString> m_setSelectedName;
};

class Data_CnsID : public IData
{
public:
    Data_CnsID( u16 wCnsID ) : IData( "CnsID" ), m_wData( wCnsID ){}
    IData* Clone()
    {
        Data_CnsID* pData = new Data_CnsID( m_wData );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    u16  m_wData;
};
 

//会议模板所含的轮询列表
class Value_TouchListTempPoll : public IValue
{
public: 
    Value_TouchListTempPoll(TCMSConfTemplate &tConfTemp ,String m_strClickItemFunc  =  IBaseItem::strDefaultFunc  , 
		vector<String> * pVctSubItem = NULL, BOOL bDrag = FALSE )
        : IValue( "TouchListTempPoll" ), m_tTemp( tConfTemp), m_strClickItemFunc(m_strClickItemFunc), m_pVctSubItem( pVctSubItem ),m_bDrag(bDrag),m_bAddIconShow(FALSE) {}
    TCMSConfTemplate  m_tTemp;          // 
    String  m_strClickItemFunc;	      // 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
	BOOL m_bAddIconShow;
    BOOL32 m_bDrag;
};

// class Value_TouchListTempPoll : public IValue
// {
// public: 
//     Value_TouchListTempPoll(TCMSConfTemplate &tConfTemp ,String m_strClickItemFunc  =  IBaseItem::strDefaultFunc  , 
//            vector<String> * pVctSubItem = NULL, BOOL bDrag = FALSE )
//         : IValue( "TouchListTempPoll" ), m_tTemp( tConfTemp ), m_strClickItemFunc(m_strClickItemFunc), m_pVctSubItem( pVctSubItem ),m_bDrag(bDrag) {}
//     TCMSConfTemplate  m_tTemp;          // 
//     String  m_strClickItemFunc;	      // 条目点击回调函数 
//     vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
//     BOOL32 m_bDrag;
// };

class Data_CnsAddr : public IData
{
public:
    Data_CnsAddr( TEpAddr  tCnsAddr ) : IData( "CnsAddr" ), m_tEpAddr( tCnsAddr ){}
    IData* Clone()
    {
        Data_CnsAddr* pData = new Data_CnsAddr( m_tEpAddr );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TEpAddr    m_tEpAddr;
};

//地址簿列表
class Value_TouchListAddr : public IValue
{
public:
	Value_TouchListAddr( vector<TAddrItem>* pArray, vector<String>* pSubItem = NULL, String strItemFunc = IBaseItem::strDefaultFunc, BOOL32 bSort = TRUE, BOOL bAddrEditDlg = FALSE, BOOL bShowOnline = FALSE, BOOL bDrag = FALSE )
		: IValue( "TouchListAddr" ), m_pAddrList( pArray ), m_strItemFunc( strItemFunc ), m_pSubItem( pSubItem ), m_bSort( bSort ),m_bAddIconShow(FALSE), m_bAddrEditDlg(bAddrEditDlg), m_bShowOnline(bShowOnline), m_bDrag(bDrag) {}
	vector<TAddrItem>* m_pAddrList;
	String             m_strItemFunc;
	BOOL			   m_bAddIconShow;
	vector<String>*    m_pSubItem;
	BOOL32             m_bSort;
	BOOL			   m_bAddrEditDlg;
	BOOL			   m_bShowOnline;
	BOOL32			   m_bDrag; 
};

class Data_AddrItemInfo : public IData
{
public:
	Data_AddrItemInfo( TAddrItem& tItem ) : IData( "AddrItemInfo" ), m_tAddrItem( tItem ){}
	IData* Clone()
	{
		Data_AddrItemInfo* pItemInfo = new Data_AddrItemInfo( m_tAddrItem );
		pItemInfo->SetDataKey( GetDataKey() );
		return pItemInfo;
	}
	TAddrItem  m_tAddrItem;
};


//登录连接时的会场列表
class Value_ListConnectCns : public IValue
{
public:
	Value_ListConnectCns( TTPCnList* ptCnList, String strItemFunc = IBaseItem::strDefaultFunc )
		: IValue( "ListConnectCns" ), m_ptCnList( ptCnList ), m_strItemFunc( strItemFunc ){}
	TTPCnList*          m_ptCnList;
	String              m_strItemFunc;
};

class Data_TPCnInfo : public IData
{
public:
	Data_TPCnInfo( TTPCn& tInfo ) : IData( "TPCnInfo" ), m_tCnInfo( tInfo ){}
	IData* Clone()
	{
		Data_TPCnInfo* pCnInfo = new Data_TPCnInfo( m_tCnInfo );
		pCnInfo->SetDataKey( GetDataKey() );
		return pCnInfo;
	}
	TTPCn  m_tCnInfo;
};


//会议列表
class Value_TouchListConf : public IValue
{
public:
    Value_TouchListConf( ARRAY<TCMSConf>* pList, String strItemFunc = IBaseItem::strDefaultFunc ,
        ARRAY<String> * pVctSubItem = NULL, BOOL32 bDrag = FALSE) 
        : IValue( "TouchListConf" ), m_pTplAryConf( pList ), m_strItemFunc( strItemFunc ), m_pVctSubItem( pVctSubItem ), m_bDrag(bDrag) {}
    ARRAY<TCMSConf>* m_pTplAryConf ;
	std::set<u16> m_setClickedId;
    String m_strItemFunc;			 // 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
};


//会议列表,只显示名称
class Value_ListConf : public IValue
{
public:
    Value_ListConf( ARRAY<TCMSConf>* pList, String strItemFunc = IBaseItem::strDefaultFunc ) 
        : IValue( "ListConf" ), m_pvctAryConf( pList ), m_strItemFunc( strItemFunc ){}
    ARRAY<TCMSConf>* m_pvctAryConf ;
    String m_strItemFunc;			 // 条目点击回调函数 
};


class Data_Conf : public IData
{
public:
    Data_Conf( TCMSConf  &tConf  ) : IData( "Conf" ), m_tCmsConf( tConf ){}
    IData* Clone()
    {
        Data_Conf* pData = new Data_Conf ( m_tCmsConf );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }

    TCMSConf  m_tCmsConf;
};


//预约会议列表
class Value_TouchListOrderConf : public IValue
{
public:
	Value_TouchListOrderConf( TplArray<TCMSConfTemplate>* pList,String strItemFunc = IBaseItem::strDefaultFunc,
		vector<String> * pVctSubItem = NULL, BOOL32 bShowALl = FALSE) 
		: IValue( "TouchListCnsOrderList" ), m_pvctConfTemplate( pList ), m_strItemFunc( strItemFunc ), m_pVctSubItem( pVctSubItem ), m_bShowAll(bShowALl){}
	TplArray<TCMSConfTemplate>* m_pvctConfTemplate;
	String m_strItemFunc;			 // 条目点击回调函数 
	std::set<u16> m_setClickedId;
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bShowAll;               //是否全部显示，如果是否，则只显示当前所登录会场是默认主席的模板
};

class Data_OrderConf : public IData
{
public:
    Data_OrderConf( TCMSConfTemplate &tConfTemp ) : IData( "ConfTemp" ), m_tConfTemp( tConfTemp ){}
    IData* Clone()
    {
        Data_OrderConf* pData = new Data_OrderConf( m_tConfTemp );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TCMSConfTemplate  m_tConfTemp;
};



enum EM_ConfLst_Type
{
   em_ConfLstTypeCns,    //会议中cns列表
   em_ConfLstTypeAudmix, //混音列表
   em_ConfLstTypePoll,   //会议中轮询列表
   em_ConfLstTypeTvw,    //电视墙界面中的
   em_ConfLstTypwSelView, //选看列表
};

//会议中cns列表
class Value_ListConfInfo : public IValue
{
public:
    Value_ListConfInfo( TCMSConf &tConf, String strClickItemFunc = IBaseItem::strDefaultFunc,
        String strSubItemFunc = IBaseItem::strDefaultFunc, BOOL bShowIcon = TRUE, EM_ConfLst_Type lstType = em_ConfLstTypeCns ) 
        : IValue( "ListConfInfo" ), m_tConf( tConf ), m_strClickItemFunc( strClickItemFunc ),
        m_strSubItemFunc( strSubItemFunc ), m_bShowIcon( bShowIcon ), m_lstType(lstType) {}

    TCMSConf m_tConf;
    String m_strClickItemFunc;		    // 条目点击回调函数 
    String m_strSubItemFunc;            //子条目点击回调函数
    BOOL   m_bShowIcon;                 //是否显示图标   
    EM_ConfLst_Type m_lstType;
};

class Data_ConfCns : public IData
{
public:
    Data_ConfCns( TCnsInfo tConfCns ) : IData( "ConfCns" ), m_tConfCns( tConfCns ){}
    IData* Clone()
    {
        Data_ConfCns* pData = new Data_ConfCns( m_tConfCns );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TCnsInfo  m_tConfCns;
};

//会议中cns列表
class Value_ListConfCns : public IValue
{
public:
    Value_ListConfCns( vector<TCnsInfo>* pvctCnsList, String strClickItemFunc = IBaseItem::strDefaultFunc,
        String strSubItemFunc = IBaseItem::strDefaultFunc, BOOL bShowIcon = TRUE ) 
        : IValue( "ListConfCns" ), m_pvctCnsList( pvctCnsList ), m_strClickItemFunc( strClickItemFunc ),
        m_strSubItemFunc( strSubItemFunc ), m_bShowIcon( bShowIcon ) {}
    
    vector<TCnsInfo>* m_pvctCnsList;
    String m_strClickItemFunc;		    // 条目点击回调函数 
    String m_strSubItemFunc;            //子条目点击回调函数
    BOOL   m_bShowIcon;                 //是否显示图标
};



//用户列表
class Value_TouchListUser : public IValue
{
public:
    Value_TouchListUser( vector<CUserFullInfo>* pUserLst, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL , bool bIsClickedIcon = false,bool bClickedAllSel = false) 
        : IValue( "TouchListUser" ), m_pvctArryUser( pUserLst ), m_strClickItemFunc( strClickItemFunc ),
        m_pVctSubItem( pVctSubItem ){}
   
    vector<CUserFullInfo>*  m_pvctArryUser;
    String m_strClickItemFunc;		    	// 条目点击回调函数
	std::set<CString> m_setClickedName;
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
};

class Data_User : public IData
{
public:
    Data_User( CUserFullInfo &cUser ) : IData( "User" ), m_cUser( cUser ){}
    IData* Clone()
    {
        Data_User* pData = new Data_User( m_cUser );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }

    CUserFullInfo m_cUser;
};

struct TMenuItemInfo
{
    String strTxt;  //条目显示的文字
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    String strItemFunc; //条目的单击事件
    String strImageItem;  
    String strTxtItem;  
    TMenuItemInfo()
    {
		Clear();
    }
	
    void Clear()
    {
        strTxt = "";
		m_pVctSubItem = NULL;
		strItemFunc = "";
        strImageItem =  "SysCfgItem";
        strTxtItem =  "TextItemWhite"; 
    }

};


//菜单列表 
class Value_TouchListMenu: public IValue
{
public:
    Value_TouchListMenu( ARRAY<TMenuItemInfo> *pvctMenuList,  BOOL32 bDrag = FALSE, BOOL bDrawRightPic = FALSE ) 
        : IValue( "TouchListMenu" ), m_pMenuLst( pvctMenuList ),  m_bDrag(bDrag), m_bDrawRightPic(bDrawRightPic) {}
    ARRAY<TMenuItemInfo> *m_pMenuLst; 
    BOOL32 m_bDrag;                  //是否可以拖动
	BOOL m_bDrawRightPic;			 //是否绘制右侧图片
};

class Data_Menu : public IData
{
public:
    Data_Menu( TMenuItemInfo &tMenu ) : IData( "Menu" ), m_tMenuInfo( tMenu ){}
    IData* Clone()
    {
        Data_Menu* pData = new Data_Menu( m_tMenuInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TMenuItemInfo m_tMenuInfo;
};


//告警信息列表
class Value_TouchListAlarm : public IValue
{
public:
	Value_TouchListAlarm( vector<String>* pArray )
		: IValue( "TouchListAlarm" ), m_pAlarmList( pArray ){}
	vector<String>* m_pAlarmList;
};


class Data_ConfMenu : public IData
{
public:
    Data_ConfMenu( TConfMenuInfo &tMenu ) : IData( "Menu" ), m_tConfMenuInfo( tMenu ){}
    IData* Clone()
    {
        Data_ConfMenu* pData = new Data_ConfMenu( m_tConfMenuInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TConfMenuInfo m_tConfMenuInfo;
};



//电视墙列表 
class Value_ViewListTvw: public IValue
{
public:  
    Value_ViewListTvw( vector<TTvwCns> *pTvwLst, String strClickItemFunc = IBaseItem::strDefaultFunc,
        int nColumn = 0, BOOL32 bManage = FALSE ) 
        : IValue( "ViewListTvw" ), m_pTvwList( pTvwLst ), m_strClickItemFunc( strClickItemFunc ),
          m_nColumn( nColumn ), m_bManage( bManage ) {}

    vector<TTvwCns> *m_pTvwList; 
    String m_strClickItemFunc;    //条目点击回调函数
    int    m_nColumn;             //列数
    BOOL32 m_bManage;             //是否处于管理状态中
};

class Data_TvwInfo : public IData
{
public:
    Data_TvwInfo( THduPlanUnit &tTvw ) : IData( "TvwInfo" ), m_tTvwInfo( tTvw ){}
    IData* Clone()
    {
        Data_TvwInfo* pData = new Data_TvwInfo( m_tTvwInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }

    THduPlanUnit m_tTvwInfo;
};

//录像文件列表
class Value_ListFile : public IValue
{
public:
	Value_ListFile( vector<TRecFileInfo> *pArray, String strItemFunc = IBaseItem::strDefaultFunc,
		int nType = 0, vector<TRecFileInfo> *pArraySel = NULL ) : IValue( "ListFile" ),
		m_pVecTRecFileInfo( pArray ),
		m_strItemFunc( strItemFunc ),
		m_nType(nType),
		m_pVecTRecFileInfoSel(pArraySel){}
	vector<TRecFileInfo> *m_pVecTRecFileInfo;
	vector<TRecFileInfo> *m_pVecTRecFileInfoSel;
	String m_strItemFunc;
	int m_nType;		//0:vidiefilelist, 1:dellist, 2:playchooselist
};

class Data_FileInfo : public IData
{
public:
	Data_FileInfo( TRecFileInfo& tItem ) : IData( _T("FileInfo") ), m_tRecFileInfo( tItem ){}
	IData* Clone()
	{
		Data_FileInfo* pItemInfo = new Data_FileInfo( m_tRecFileInfo );
		pItemInfo->SetDataKey( GetDataKey() );
		return pItemInfo;
	}
	TRecFileInfo  m_tRecFileInfo;
};

//录像和回放列表
class Value_ListRecord : public IValue
{
public:
	Value_ListRecord( vector<TUmcConfInfo> *pArray, String strItemFunc = IBaseItem::strDefaultFunc,
		vector<TUmcConfInfo> *pArraySel = NULL )
		: IValue( "ListRecord" )
		, m_pVecTUmcConfInfo( pArray )
		, m_strItemFunc( strItemFunc ){}
	vector<TUmcConfInfo> *m_pVecTUmcConfInfo;
	String             m_strItemFunc;
};

class Data_RecordInfo : public IData
{
public:
	Data_RecordInfo( TUmcConfInfo* pItem ) : IData( _T("RecordInfo") ), m_pTUmcConfInfo( pItem ){}
	IData* Clone()
	{
		Data_RecordInfo* pItemInfo = new Data_RecordInfo( m_pTUmcConfInfo );
		pItemInfo->SetDataKey( GetDataKey() );
		return pItemInfo;
	}
	TUmcConfInfo*  m_pTUmcConfInfo;
};


//录像和回放会场列表
class Value_ListRecordEp : public IValue
{
public:
	Value_ListRecordEp( vector<TUmcRecInfo> *pArray, String strItemFunc = IBaseItem::strDefaultFunc )
		: IValue( "ListRecordEp" ), m_pVecTRecInfo( pArray ), m_strItemFunc( strItemFunc ){}
	vector<TUmcRecInfo> *m_pVecTRecInfo;
	String             m_strItemFunc;
};

class Data_RecordEpInfo : public IData
{
public:
	Data_RecordEpInfo( TUmcRecInfo* pItem ) : IData( _T("RecordEpInfo") ), m_pTRecInfo( pItem ){}
	IData* Clone()
	{
		Data_RecordEpInfo* pItemInfo = new Data_RecordEpInfo( m_pTRecInfo );
		pItemInfo->SetDataKey( GetDataKey() );
		return pItemInfo;
	}
	TUmcRecInfo*  m_pTRecInfo;
};


#endif // !defined(AFX_TOUCHLISTPROPERTY_H__04260821_1F80_4C85_A679_1B121DF07E09__INCLUDED_)
