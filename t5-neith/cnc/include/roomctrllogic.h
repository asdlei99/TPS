/** @defgroup �᳡���� ������������������
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.17
 */
#pragma once

#define NUM_MIC_FIRLINE               3
#define NUM_MIC_SECLINE               6

#define NUM_SRCEEN_COUNT               5
#define FLAG_FIRST          0x00000001
#define FLAG_SECOND         0x00000002
#define FLAG_THIRD          0x00000004
#define FLAG_FOURTH         0x00000008
#define FLAG_FIFTH          0x00000010
//������Ļ��ȡλ
const int adwTagArray[NUM_SRCEEN_COUNT] = {FLAG_FIRST,FLAG_SECOND,FLAG_THIRD,FLAG_FOURTH,FLAG_FIFTH};

enum EmTabID //tab��ö��
{
	ID_CAMERA = 1,  //�����
	ID_SPEAKER,     //������
	ID_MIC,         //��˷�
//	ID_VEDIOSOURCE, //��ʾԴ
	ID_MAINVEDIO,   //����ƵԴ����ƵԴ��
};

class CRoomCtrlLogic : public CNotifyUIImpl
{
public:
	CRoomCtrlLogic(void);
	~CRoomCtrlLogic(void);

protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);

	/** ʧȥ������Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
/*	bool OnKillFocus(TNotifyUI& msg);*/
	
	/** �˳���ҳ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** �˳�cnc 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckSlient(TNotifyUI& msg);
	/** �Ƿ񴴽���������ݿ���
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckSpeakerShortCut(TNotifyUI& msg);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnCheckMute(TNotifyUI& msg);
	/** �Ƿ񴴽���˷��ݿ���
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnCheckMicShortCut(TNotifyUI& msg);
	/** ѡ����Ƶ����Ŀ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnBtnVedioItemSel(TNotifyUI& msg);
	/** ������˷����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnBtnMicControl(TNotifyUI& msg);
	/** �������ͷTab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabCamera(TNotifyUI& msg);
	/** ���������Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabSpeaker(TNotifyUI& msg);
	/** ������Tab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabMic(TNotifyUI& msg);
	/** �����ƵԴTab 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	//bool OnTabVedioSource(TNotifyUI& msg);
	/** �������ƵԴTab
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabMainVedio(TNotifyUI& msg);

	/** ����ƵԴѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabVedio1Op1(TNotifyUI& msg);
	bool OnTabVedio1Op2(TNotifyUI& msg);
	bool OnTabVedio2Op1(TNotifyUI& msg);
	bool OnTabVedio2Op2(TNotifyUI& msg);
	bool OnTabVedio2Op3(TNotifyUI& msg);
	bool OnTabVedio3Op1(TNotifyUI& msg);
	bool OnTabVedio3Op2(TNotifyUI& msg);

    //������ѡ��
    bool OnCheckSrceenControl(TNotifyUI& msg);

    bool OnBtnLiftSrceenUp(TNotifyUI& msg);
    bool OnBtnLiftSrceenDown(TNotifyUI& msg);
    bool OnBtnLiftSrceenStop(TNotifyUI& msg);

    bool OnBtnFlipSrceenOpen(TNotifyUI& msg);
    bool OnBtnFlipSrceenClose(TNotifyUI& msg);
    bool OnBtnFlipSrceenStop(TNotifyUI& msg);

	/** ���ȫ�������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabFullCamera(TNotifyUI& msg);
	/** ����ĵ������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabFileCamera(TNotifyUI& msg);

	/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����������֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnSpeakerVolNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��˷�����֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnMicVolNty(WPARAM wParam, LPARAM lParam, bool& bHandle);	
	/** ����������֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnMuteOrSilencNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** VGA��Ϣ֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnVgaInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ˫���˿�֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSelDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelDefaultDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��ʾTab
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnSetTabShow(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��ݷ�ʽcheck״̬����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnSetShortCheck(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �����������仯��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool onSpeakerVolChanged(TNotifyUI& msg);
	bool onSpeakerVolChanging(TNotifyUI& msg);
	/** ��˷������仯��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool onMicVolChanged(TNotifyUI& msg);
	bool onMicVolChanging(TNotifyUI& msg);
	/** ������ƵԴ�б� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateVedioSourceList();
	//ѡ����ƵԴ�б���һ��
	bool OnVedioItemSel(TNotifyUI& msg);
	bool OnComboItemSel(TNotifyUI& msg);

	//����ƵԴ������Ϣ
	bool OnMainVedioSetInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����ƵԴ������Ϣ
	bool OnVidSrcNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����Ƶ������������Ƶѡ��
	bool OnMinVedioInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tptool��������ƵԴ������
	bool OnSetVedioInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	void UpdateSourceName();

	//��˷����
	bool OnCnDesktopMicInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnMicPowerStyleNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnMicPowerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnSetMicPowerRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	void UpdateMicStyle();
	void UpdateMicState();
    //���������
    bool OnCentreDFScreenConfigNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnCentreSelectDFScreenNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnCentreScreenTypeNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnModifyDFScreenGroupInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnCentreDFScreenCmdInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnSelectDFScreenInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:

	static const String m_strBtnFixOrCancel;	 //�޸ġ�ȡ����ť
	static const String m_strBtnOk;				 //ȷ�ϰ�ť
	static const String m_strSldTab;			 //�˵�Tab
	static const String m_strFullCamera;	     //ȫ�������
	static const String m_strSldSpeaker;		 //������	
	static const String m_strSldMic;			 //��˷�
	static const String m_strBtnMute;			 //����
	static const String m_strBtnSlience;		 //����

    static const int m_nFirstLineMic[NUM_MIC_FIRLINE];		 //��һ����˷�˳��
    static const int m_nSecondLineMic[NUM_MIC_SECLINE];		 //�ڶ�����˷�˳��

	TDualSrcInfo  m_tDualSrcInfo;
	map<u16, EmTPMtVideoPort>       m_mapEmTPMtVideoPort;     // ����ƵԴѡ��
	bool m_bIsVSListExt;//�Ƿ��Ѿ�������ƵԴ�б�
	bool m_bSetVedioSourc;//�Ƿ��������ʾԴ�л�������Ѿ�������Ϣ����ind��֮ǰ���ظ�������Ϣ
	bool m_bIsIni;//�Ƿ�����˳�ʼ��
	EM_ShortcutType m_em;//��ʼ��֮ǰ�յ��Ŀ�ݷ�ʽ����
	TTPVideoInfoTool m_tTPVideoInfoTool;//����Ƶ������  

	BOOL			 m_bIsFullState;          //�᳡��˷�����Ϊ9��ȫ״̬
	BOOL			 m_bIsNonDesktopMic;
	BOOL             m_byMicStyle[TP_MIC_NUM];//��˷�״̬
	BOOL             m_byMicState[TP_MIC_NUM];//��˷�״̬

    u32              m_dwGroupNum;            //����������
    u8               m_byScreenControl;       //��������������������Ƶı��
    u8               m_byAllScreenCtrlSel;    //����������Ч��Ļȫѡ����Ч��Ļ����tptools����
};