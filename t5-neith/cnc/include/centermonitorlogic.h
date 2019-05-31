/** @defgroup �п���ʾ��
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2015-3-31
 */
#pragma once

class CCenterMonitorLogic : public CNotifyUIImpl, public Singleton<CCenterMonitorLogic> 
{
public:
	CCenterMonitorLogic(void);
	~CCenterMonitorLogic(void);
	//������ʾ��״̬
	bool updateMonitorState();
protected:
    /** ��ʼ����Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);
	/** �����ʾ��check
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnCheckScreenSel(TNotifyUI& msg);
	/** ����յ�check
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnCheckAircon(TNotifyUI& msg);

	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ���̨����Ŀ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenMonitorItemClick(TNotifyUI& msg);
	/** ��������Ŀ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenAirconItemClick(TNotifyUI& msg);
	/** AC֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMonitorPowrInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** AC��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMonitorStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** Monitor֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnACStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelectAirInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnAirPowerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** Monitor��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSeleteMonitorInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ̨������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnOpFS(TNotifyUI& msg);
	bool OnOpFView(TNotifyUI& msg);
	bool OnOpStandard(TNotifyUI& msg);
	bool OnOpPTP(TNotifyUI& msg);
	bool OpVStandard(TNotifyUI& msg);
	bool OpVUser(TNotifyUI& msg);
	bool OpVPC(TNotifyUI& msg);
	bool OpVTV(TNotifyUI& msg);
	bool OnOpHDMI1(TNotifyUI& msg);
	bool OnOpHDMI2(TNotifyUI& msg);
	bool OnOpHDMI3(TNotifyUI& msg);
	bool OnOpHDMI4(TNotifyUI& msg);
	bool OnOpYPbPr(TNotifyUI& msg);
	bool OnOpCVBs1(TNotifyUI& msg);
	bool OnOpCVBs2(TNotifyUI& msg);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnOpSPC(TNotifyUI& msg);
	bool OnOpVGA(TNotifyUI& msg);
	bool OnOpCold(TNotifyUI& msg);
	bool OnOpHot(TNotifyUI& msg);
	bool OnOpWind(TNotifyUI& msg);
	bool OnOpWet(TNotifyUI& msg);
	/** �յ�Ӧ�õ�ȫ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnAirAll(TNotifyUI& msg);
	//�յ�ʪ�ȵ���
	bool OnBtnTempPlus(TNotifyUI& msg);
	bool OnBtnTempMinus(TNotifyUI& msg);
	//�յ���������
	bool OnBtnWindPlus(TNotifyUI& msg);
	bool OnBtnWindMinus(TNotifyUI& msg);
	bool OnBtnWindAuto(TNotifyUI& msg);

    //��ʾ��
    bool OnDisPlayShowNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//���¿յ�����״̬
	bool updateACState(CListContainerElementUI *pAircondListContainer, TCentreACCfg tCentreACCfg, u32 dwIndex);
	APP_DECLARE_MSG_MAP()
		

private:

	static const String m_strSldTab;			 //�˵�Tab

	int m_dwMonitorScreenSelId;   //��ʾ��
	int m_dwAirconScreenSelId;   //�յ�

	map<u16, bool>       m_mapIsMonitor;     // ��¼���Ƿ���Monitor
	map<u16, bool>       m_mapIsAirCon;   // ��¼���Ƿ���AC

	TCentreTVCfg          m_atModitorCfg[MAX_CENTRETV_NUM];//��ʾ������	 

	vector<TCentreACCfg> m_vecTCentreACCfg;//�յ���Ϣ

    bool m_bDisplayShow;//��ʾ����ʾ
};