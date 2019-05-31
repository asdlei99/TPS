// TouchListHelp.h: interface for the CTouchListHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_)
#define AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "umclib.h"
#include "cnclib.h"
#include "tplarray.h"
#include "cmsstruct.h"
#include "TouchListProperty.h"


class CTouchListHelp  
{
public:
	const static String strConfTemplate;
    const static String strTempCns;
    const static String strItemTempPoll;
	const static String strListAddr;
	const static String strItemConf;
    const static String strConfCns;    //会议中会场列表
    const static String strConfLst;    //会议列表
    const static String strListConf;
    const static String strListConfCns;
    const static String strListUser;   //用户列表
	const static String strListTvw;		//电视墙列表
	const static String strListAlarm;

	const static String strItemDefault;
	const static String strItemText;
    const static String strItemAddrList;
    const static String strListMenu;
	const static String strListConnectCn;
	const static String strListConfMenu;
    const static String strVerListConfMenu;
	const static String strListCnsOrderList;
	const static String strListFile;	//录像文件列表
	const static String strListRecord;	//录像和回放列表
	const static String strListRecordEp;	//录像和回放会场列表
    
    //static MapLstName m_mapStrListName;
	typedef IItem< IBaseItem, int > IItemList;

    //列表中创建Item所需参数
    class Args_MakeItem : public IArgs
    {
    public:  
        IItemList* pList;
        BOOL32 bDrag;   //该item是否可以拖动
        int nKey;      //该item在其当前层的列表中所占的次序
        String strTxt;  //item上显示的字符串
        IData* pUserData;  //用户信息，主要用于点击时产生的click事件的参数
        String strClickItemFunc; //点击事件
        ARRAY<String>* pVctSubItem; //item上显示的图标
        String strImageItem ;      //对应的imgItem类型
        String strTxtItem;          //对应的txtItem类型
        String strLayoutAlgorithm;  //item的布局算法
        EmItemStatus emItemStatus;  //item状态

        Args_MakeItem( ):IArgs("MakeItem" )
        {
            pList = NULL;
            bDrag = FALSE;
            nKey =-1;
            strTxt.erase();
            pUserData = 0;
            strClickItemFunc.erase();
            pVctSubItem  = NULL;
            strImageItem = CTouchListHelp::strItemAddrList;
            strTxtItem = CTouchListHelp::strItemText;
            strLayoutAlgorithm= IAlgorithm::strNormalItem ;
            emItemStatus = emItemStatusNormal; 
        }
        
};

public:
    CTouchListHelp();
    virtual ~CTouchListHelp();
    static bool SetData( IItemList* pList, const IValue* pValue );
protected: 
//     模板列表
//         static bool TransData( IItemList* pList, TplArray<TTPConfTemplate>* pConfTemplate, String strItemFunc, 
//                        ARRAY<String> * pVctSubItem ,BOOL32 bDrag); 

	//用户列表
	static bool TransData( IItemList* pList, Value_TouchListUser &val);

	//地址簿列表
	static bool TransData( IItemList* pList, ARRAY<TAddrItem>* pArray, String strItemFunc, BOOL m_bAddIconShow,
		            ARRAY<String>* pVctSubItem, BOOL bSort, vector<String>* pSubItem, BOOL bAddrEditDlg, BOOL bShowOnline );


	//菜单列表
    static bool TransData( IItemList* pList, ARRAY<TMenuItemInfo> *pvctMenuLst, BOOL32 bDrag, BOOL bDrawRightPic );

    //模板列表
    static bool TransData( IItemList* pList, Value_TouchListConfTemp &val); 


    
//     //模板中的cns列表
//     static bool TransData( IItemList* pList, TEpAddrList  &tCnsLst ,  String strClickItemFunc,  
//                    ARRAY<String> * pVctSubItem,BOOL32 bDrag);
    
  
    //模板中的cns列表
    static bool TransData( IItemList* pList,Value_TouchListTempCns &val );


    //模板中的轮询列表
    static bool TransData( IItemList* pList,  TCMSConfTemplate &tConfTemp,  String strClickItemFunc, bool bIsShowIcon,
                  ARRAY<String> * pVctSubItem,BOOL32 bDrag);

	//当前会议列表
    static bool TransData( IItemList* pList, Value_TouchListConf &val);

	//预约会议列表
    static bool TransData( Value_TouchListOrderConf &val, IItemList* pList ); 

    //电视墙列表
    static bool TransData( IItemList* pList, Value_ViewListTvw &val );

    //会议中cns列表
    static bool TransData( IItemList* pList, Value_ListConfInfo &val);
    //会议中cns列表
    static bool TransData( IItemList* pList, Value_ListConfCns &val);

    //只显示名称的会议列表
    static bool TransData( IItemList* pList, Value_ListConf &val);

	//录像机文件列表
	static bool TransData( IItemList* pList, Value_ListFile &val );
	
	//录像和回放
	static bool TransData( IItemList* pList, Value_ListRecord &val );
	
	//录像和回放会场
	static bool TransData( IItemList* pList, Value_ListRecordEp &val );

 /* 
	//告警列表
	static bool TransData( IItemList* pList, ARRAY<String>* pArray );
	*/

private:
//   static bool MakeItem ( Args_MakeItem &agrs )  ;
	//static bool InsertItem ( Args_MakeItem &agrs )  ;
};



//电视墙列表排列算法
class CLayoutAlgorithm_TvwView : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//电视墙中会场内排列算法
class CLayoutAlgorithm_TvwCns : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//单个电视墙
class CLayoutAlgorithm_TvwItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

#endif // !defined(AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_)
