#pragma once
#include "confctrllogic.h"

class CTvWallLogic : public CNotifyUIImpl, public Singleton<CTvWallLogic> 
{
public:
	CTvWallLogic(void);
	~CTvWallLogic(void);
public:
    bool init();

    void HideChildWindow();

	APP_DECLARE_MSG_MAP()

protected:
	void clear();

	void UpdateTvWall( );

	bool OnBtnSetTvWall( TNotifyUI& msg );

	bool OnBtnOpenMuteView( TNotifyUI& msg );

	bool OnBtnCloseMuteView( TNotifyUI& msg );

	bool OnHduPlanNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnHduChangeModeInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnBtnStopPlay( TNotifyUI& msg );

	bool OnBtnSetVoice( TNotifyUI& msg );

    bool OnBtnTvWallItem( TNotifyUI& msg );

	bool OnBtnAddTvWall( TNotifyUI& msg );

	bool OnHideChildWindowNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool onHduVolChanging( TNotifyUI& msg );

	bool onHduVolChanged(TNotifyUI& msg );

	bool OnHduVolumeInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnHduStopPlayInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnLetterIndex( TNotifyUI& msg );

	bool OnConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnCheckConfCnsItem(TNotifyUI& msg);

	bool OnBtnCancel(TNotifyUI& msg);

	bool OnBtnShowScreenOption(TNotifyUI& msg);

	bool OnBtnHideScreenOption(TNotifyUI& msg);

	bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnComboShowEx(TNotifyUI& msg);

	bool OnSearchEditChange(TNotifyUI& msg);

	bool OnCheckTvWallShortCut(TNotifyUI& msg);

	//bool OnConfCnsItemClick(TNotifyUI& msg);

	bool OnListBtnRoomSel(TNotifyUI& msg);
    void ListBtnRoomSel(int nSelIndex);

	bool OnBtnConfirm( TNotifyUI& msg );

	void SetCnsInTvw( );
	bool onHduPlayInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnCheckSlient( TNotifyUI& msg );

	bool OnCheckSrceen1( TNotifyUI& msg );
	bool OnCheckSrceen2( TNotifyUI& msg );
	bool OnCheckSrceen3( TNotifyUI& msg );

	void SetBtnRoomSelStatus( TNotifyUI& msg );

    
private:
	void updateItem( CListContainerElementUI * pListContainer , TTpHduPlanUnit & tHduPlanUnit );

	//void UpdateCnsList();
	void UpdateShowList();
	void UpdateCnsList();
	u8 GetStatus( CControlUI *pControl );
	void SetStatus( CControlUI *pControl, u8 byTag );
private:
	s32   m_nSelectIndex;				//�����ĵ���ǽ����
	u8    m_bySubIndex;                 //������ͨ������
	s32   m_nCtrlIndex;                 //���һ�ε�����õ���ǽ����
	const String m_strSetTvWallBtn;
	const String m_strSrceenDesc;
	const String m_strChannelDesc;
	const String m_strSetTvWallLayout;
	const String m_strMuteViewLayout;
	const String m_strBtnSetVoice;
	const String m_strBtnMuteView;
	const String m_strBtnDelMuteView;

	TTpHduPlanPackData m_tHduPlanData[TP_STYLE_DATA_AllPACK_NUM];
	TTpHduPlanPackData m_tOldHduPlanData[TP_STYLE_DATA_AllPACK_NUM];

	EM_CnsListShowState m_emCnsShowState;      //�᳡��ʾ״̬
	int                 m_nSelIndex;           //ѡ�еĻ᳡����

	vector<TSelViewInfo>  m_vctCnsInfoList;        //���ص�ַ���б� 
	vector<TSelViewInfo>  m_vctShowCnsList;   //�û������б� 
	s32                   m_nWaitMessageNum;
	vector<int>           m_vctSelSrceen;	   //ѡ����Щ��(���3��)
	String                m_strArrayScreen[MAX_SEAT_COUNT];//��������ʾ�ַ�     
	string		          m_strChannelAlias;
};

