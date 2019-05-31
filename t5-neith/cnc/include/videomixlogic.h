/** @defgroup ����ϳ��߼���Ԫ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.12.26
 */
#pragma once
class CVideoMixLogic : public CNotifyUIImpl, public Singleton<CVideoMixLogic> 
{
public:
	CVideoMixLogic(void);
	~CVideoMixLogic(void);

    void InitVideoMixPage();
	
	//������ذ�ť ���ش˽��� ��Ȼ���������ݷ�ʽ���� ��ͣ���ڴ˽���
	void HideVideoMixStylePage();

protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

    /** ѡ��ϳɷ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnComboSelMix(TNotifyUI& msg);
	
    bool OnChooseMixStyle(TNotifyUI& msg);
    /** ѡ��ϳɷ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnVideoMixStyleClick(TNotifyUI& msg);

    bool OnBtnVidMixStyleOK(TNotifyUI& msg);
    bool OnBtnVidMixStyleCancel(TNotifyUI& msg);

    /** ɾ�����кϳ�ͨ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnBtnVmpDeleteAll(TNotifyUI& msg);

    /** ����Ԥ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnBtnSaveVmpCfg(TNotifyUI& msg);
    /** ����Ԥ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnBtnCallVmpCfg(TNotifyUI& msg);

    /** ����ϳɻ������Ͻ����ð�ť
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnBtnVideoMixCfg(TNotifyUI& msg);

    bool OnBtnVidMixAddCns(TNotifyUI& msg);

    bool OnBtnFollowSpeaker(TNotifyUI& msg);

    bool OnBtnFollowDual(TNotifyUI& msg);
    /** ѡ��᳡������ϳ�ͨ��
	*  @param[in] ��Ϣ
	*  @return 
	*/
    bool OnBtnMixSelCns(TNotifyUI& msg);

    bool OnBtnMixDelete(TNotifyUI& msg);

    bool OnBtnSelRoomOK(TNotifyUI& msg);
    bool OnBtnSelCancel(TNotifyUI& msg);
    bool OnBtnSelAll(TNotifyUI& msg);

	bool OnBtnMixShowScreen(TNotifyUI& msg);
	bool OnBtnMixHideScreen(TNotifyUI& msg);
    bool OnCheckConfCnsItem(TNotifyUI& msg);

	bool OnMixCheckSrceen( TNotifyUI& msg );

    /** ��������ϳ���
	*  @param[in]
	*  @return 
	*/
    bool OnCheckOpenVidMix(TNotifyUI& msg);

    bool OnCheckMixBroadcast(TNotifyUI& msg);

    bool OnCheckVideoMixShortCut(TNotifyUI& msg);

	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);

    bool OnSearchEditChange( TNotifyUI& msg );

    /** ˢ�»���ϳ�ͨ��Layout
	*  @return 
	*/
    void UpdateVmpCfgLayout();

    void UpdateVmpCfgItem( u16 nIndex, CListContainerElementUI* pContainerElementUI );

    //���½��水ť״̬
    void UpdateVmpUIState();

    void UpdateVmpLayoutStyleSpecFour();
    void UpdateVmpLayoutStyleSix();
    void UpdateVmpLayoutStyleSeven();
    void UpdateVmpLayoutStyleEight();
    void UpdateVmpLayoutStyleTen();
    void UpdateVmpLayoutStyleTenM();
    void UpdateVmpLayoutStyleThirteen();
    void UpdateVmpLayoutStyleThirteenM();

    void UpdateCnsList();
	void UpdateShowList();

    void SetBrdVmpReq();

    //����ϳ�״̬֪ͨ
    bool OnBrdVmpNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnRervesBrdVmpInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnSaveVmpCfgInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnShortCutVMix( WPARAM wParam, LPARAM lParam, bool& bHandle );
    
    APP_DECLARE_MSG_MAP()
	
private:
    CTouchListUI*             m_pMixCfgList;        //�����б�
    vector<TVidMixStyleInfo>  m_vctMixStyleInfo;    //����ϳɷ��

    vector<TVidMixBkgImg>     m_vctMixBkgImg;       //���б���ͼƬ����

    //EMVmpStyle                m_emVmpStyle;         //��ǰ�ϳɷ��
    TVidMixStyleInfo          m_tChooseStyleInfo;   //��ѡ��ĺϳɷ��
    int                       m_nCtrlIndex;         //��ǰ�����ĺϳ�ͨ������
    int                       m_nCurrentVmpIndex;   //��ǰѡ�еĺϳ�������

    TBrdVmpStyle              m_tLocalVmpStyle;     //��¼���غϳ�����Ϣ
    TBrdVmpResNtfy            m_tCurrentBrdVmp;     //��������ǰ�ϳ���״̬     
    vector<TBrdVmpResNtfy>    m_vctBrdVmpInfo;      //���кϳ�����״̬

	vector<TCnsInfo>          m_vctCurrentCnsList;   //��ʾ��Cns�б�
    vector<TCnsInfo>          m_vctCnsList;          //Cns�б�
    //vector<TCnsInfo>          m_vctSelCnsList;       //ѡ�л᳡�б�
	vector<pair<TCnsInfo,vector<int>>> m_vctSelCnsList;//ѡ�л᳡�б�<�᳡��Ϣ,ѡ�л᳡��Ļ>

    TCMSConf                  m_tConfInfo;           //��ǰ������Ϣ

    BOOL                      m_bVmpAuto;           //��ǰ����Ƿ����Զ�
    BOOL                      m_bWaitRerves;        //�ȴ�ռ�ûظ���Ϣ���ڼ䲻����ResNtfy

	bool                      m_bIsSelAll;          //�Ƿ�����б�ȫѡ
	String                    m_strArrayScreen[MAX_SEAT_COUNT];  //��������ʾ�ַ�   
};

