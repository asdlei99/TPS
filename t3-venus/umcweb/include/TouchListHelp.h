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
    const static String strConfCns;    //�����л᳡�б�
    const static String strConfLst;    //�����б�
    const static String strListConf;
    const static String strListConfCns;
    const static String strListUser;   //�û��б�
	const static String strListTvw;		//����ǽ�б�
	const static String strListAlarm;

	const static String strItemDefault;
	const static String strItemText;
    const static String strItemAddrList;
    const static String strListMenu;
	const static String strListConnectCn;
	const static String strListConfMenu;
    const static String strVerListConfMenu;
	const static String strListCnsOrderList;
	const static String strListFile;	//¼���ļ��б�
	const static String strListRecord;	//¼��ͻط��б�
	const static String strListRecordEp;	//¼��ͻطŻ᳡�б�
    
    //static MapLstName m_mapStrListName;
	typedef IItem< IBaseItem, int > IItemList;

    //�б��д���Item�������
    class Args_MakeItem : public IArgs
    {
    public:  
        IItemList* pList;
        BOOL32 bDrag;   //��item�Ƿ�����϶�
        int nKey;      //��item���䵱ǰ����б�����ռ�Ĵ���
        String strTxt;  //item����ʾ���ַ���
        IData* pUserData;  //�û���Ϣ����Ҫ���ڵ��ʱ������click�¼��Ĳ���
        String strClickItemFunc; //����¼�
        ARRAY<String>* pVctSubItem; //item����ʾ��ͼ��
        String strImageItem ;      //��Ӧ��imgItem����
        String strTxtItem;          //��Ӧ��txtItem����
        String strLayoutAlgorithm;  //item�Ĳ����㷨
        EmItemStatus emItemStatus;  //item״̬

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
//     ģ���б�
//         static bool TransData( IItemList* pList, TplArray<TTPConfTemplate>* pConfTemplate, String strItemFunc, 
//                        ARRAY<String> * pVctSubItem ,BOOL32 bDrag); 

	//�û��б�
	static bool TransData( IItemList* pList, Value_TouchListUser &val);

	//��ַ���б�
	static bool TransData( IItemList* pList, ARRAY<TAddrItem>* pArray, String strItemFunc, BOOL m_bAddIconShow,
		            ARRAY<String>* pVctSubItem, BOOL bSort, vector<String>* pSubItem, BOOL bAddrEditDlg, BOOL bShowOnline );


	//�˵��б�
    static bool TransData( IItemList* pList, ARRAY<TMenuItemInfo> *pvctMenuLst, BOOL32 bDrag, BOOL bDrawRightPic );

    //ģ���б�
    static bool TransData( IItemList* pList, Value_TouchListConfTemp &val); 


    
//     //ģ���е�cns�б�
//     static bool TransData( IItemList* pList, TEpAddrList  &tCnsLst ,  String strClickItemFunc,  
//                    ARRAY<String> * pVctSubItem,BOOL32 bDrag);
    
  
    //ģ���е�cns�б�
    static bool TransData( IItemList* pList,Value_TouchListTempCns &val );


    //ģ���е���ѯ�б�
    static bool TransData( IItemList* pList,  TCMSConfTemplate &tConfTemp,  String strClickItemFunc, bool bIsShowIcon,
                  ARRAY<String> * pVctSubItem,BOOL32 bDrag);

	//��ǰ�����б�
    static bool TransData( IItemList* pList, Value_TouchListConf &val);

	//ԤԼ�����б�
    static bool TransData( Value_TouchListOrderConf &val, IItemList* pList ); 

    //����ǽ�б�
    static bool TransData( IItemList* pList, Value_ViewListTvw &val );

    //������cns�б�
    static bool TransData( IItemList* pList, Value_ListConfInfo &val);
    //������cns�б�
    static bool TransData( IItemList* pList, Value_ListConfCns &val);

    //ֻ��ʾ���ƵĻ����б�
    static bool TransData( IItemList* pList, Value_ListConf &val);

	//¼����ļ��б�
	static bool TransData( IItemList* pList, Value_ListFile &val );
	
	//¼��ͻط�
	static bool TransData( IItemList* pList, Value_ListRecord &val );
	
	//¼��ͻطŻ᳡
	static bool TransData( IItemList* pList, Value_ListRecordEp &val );

 /* 
	//�澯�б�
	static bool TransData( IItemList* pList, ARRAY<String>* pArray );
	*/

private:
//   static bool MakeItem ( Args_MakeItem &agrs )  ;
	//static bool InsertItem ( Args_MakeItem &agrs )  ;
};



//����ǽ�б������㷨
class CLayoutAlgorithm_TvwView : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//����ǽ�л᳡�������㷨
class CLayoutAlgorithm_TvwCns : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//��������ǽ
class CLayoutAlgorithm_TvwItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

#endif // !defined(AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_)
