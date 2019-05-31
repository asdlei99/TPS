/** @defgroup �᳡���� ȫ������������߼�
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.17
 */
#pragma once


enum EmPancamPrePosState//Ԥ��λ�б�״̬ ���û򱣴�
{
	EMSTATE_SET = 0,
	EMSTATE_IMPLEMENT,
	EMSTATE_NO,
};

class CPanCamLogic : public CNotifyUIImpl, public Singleton<CPanCamLogic>
{
public:
	CPanCamLogic(void);
	~CPanCamLogic(void);
	//��ȡ��ǰ�����ID
	int GetCamID(){return m_dwCurrentCamID;};
protected:

	//���Ԥ��λ��ť
	bool OnBtnImplePosSet(TNotifyUI& msg);
	//�������Ԥ��λ��ť
	bool OnBtnSavePosSet(TNotifyUI& msg);
	//�����������ϰ�ť
	bool OnBtnCamUp(TNotifyUI& msg);
	bool OnBtnCamUpDown(TNotifyUI& msg);
	//�����������Ұ�ť
	bool OnCamRight(TNotifyUI& msg);
	bool OnCamRightDown(TNotifyUI& msg);
	//������������ť
	bool OnBtnCamLeft(TNotifyUI& msg);
	bool OnBtnCamLeftDown(TNotifyUI& msg);
	//�����������°�ť
	bool OnBtnCamDown(TNotifyUI& msg);
	bool OnBtnCamDownDown(TNotifyUI& msg);
	//�����Ұ���Ӱ�ť
	bool OnBtnViewPlus(TNotifyUI& msg);
	bool OnBtnViewPlusDown(TNotifyUI& msg);
	//�����Ұ���ٰ�ť
	bool OnBtnViewMinus(TNotifyUI& msg);
	bool OnBtnViewMinusDown(TNotifyUI& msg);
	//����������Ӱ�ť
	bool OnBtnFocusPlus(TNotifyUI& msg);
	bool OnBtnFocusPlusDown(TNotifyUI& msg);
	//����Զ��Խ���ť
	bool OnBtnFocusAuto(TNotifyUI& msg);
	//���������ٰ�ť
	bool OnBtnFocusMinus(TNotifyUI& msg);
	bool OnBtnFocusMinusDown(TNotifyUI& msg);
	//����������Ӱ�ť
	bool OnBtnBrightPlus(TNotifyUI& msg);
	bool OnBtnBrightPlusDown(TNotifyUI& msg);
	//������ȼ��ٰ�ť
	bool OnBtnBrightMinus(TNotifyUI& msg);
	bool OnBtnBrightMinusDown(TNotifyUI& msg);
	//�������ȫ������ͷ��ť
	bool OnCheckStartCam(TNotifyUI& msg);
	//���������ݷ�ʽ��ť
	bool OnCheckCamShortCut(TNotifyUI& msg);
	//���ȫ������������˵�
	bool OnComboCamSel(TNotifyUI& msg);
	//ѡ��ȫ��������б���һ��
	bool OnPresetListItemSelected(TNotifyUI& msg);
	//���ȡ��Ԥ��λ�༭
	bool OnBtnCancelPanSet(TNotifyUI& msg);
	//�������Ԥ��λ�༭
	bool OnBtnSavePanPresetNameSet(TNotifyUI& msg);
	//�������Ԥ��λ�༭
	bool OnBtnSetPresetName(TNotifyUI& msg);   
	//���ɾ��Ԥ��λ
	bool OnBtnPresetDel(TNotifyUI& msg);
	//�������Ԥ��λ
	bool OnBtnPresetAdd(TNotifyUI& msg);
	//���ȡ��Ԥ��λ�б�Ԥ��
	bool BtnPresetCancel(TNotifyUI& msg);
	//���Ԥ��λ�б�ѡ��ȷ����ť
	bool OnBtnPresetOk(TNotifyUI& msg);
	//���Ԥ��λ�б�����
	bool OnBtnCamListLeft(TNotifyUI& msg);
	//���Ԥ��λ�б�����
	bool OnBtnCamListRight(TNotifyUI& msg);
	//�����ѡ��֪ͨ
	bool OnSelSelCamInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//�����б�
	bool UpdateList();
	bool UpdateList(CString strPresetName, u8 wPageID, u8 wItemID);
	//������ʾ��Ԥ��λ�б� bLeft�Ƿ��������
	void UpdateShowPreList(bool bLeft);

	//ȫ��������б�֪ͨ
	bool OnPanCamLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ȫ�����������Ԥ��λ���
	bool OnPanCamPresetSaveNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ȫ�����������Ԥ��λ���
	bool OnPanCamPresetImpleNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ȫ�������ɾ��Ԥ��λ���
	bool OnPanCamPresetDeleteNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ȫ��������޸�Ԥ��λ���Ʊ�����
	bool OnPanCamSavePresetNameInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ȫ��������������
	bool OnPanCamStartInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //���������
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/* ����: Ԥ��λ�б��ͼ����
	* @param    const String& strRemotePath     [in]     Զ��·��
	* @param    const String& strLocalFile      [in]     ����·��
	* @param    const String& strCheckFileName     [in]     �ļ���	
	* @return   BOOL �Ƿ��ϴ��ɹ�
	* @remarks  
	*/
	BOOL DownloadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	/** ̨������ftp��Ϣ��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnDownloadProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//ctringתchar����
	bool WCharToMByte(CString strPresetName, char* achName);

		/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�Ƿ���ȫ����������� //ȫ�������֪ͨ��Ϣ�� ��������0�ſ������ƣ����򲻿ɿ�
	void EnablePamCtrl(bool bIsEnable);
	//ȫ���������ݷ�ʽ֪ͨ������ȫ�������������menu�б�ȥ����ݷ�ʽ
	bool OnSetShortCheck( WPARAM wParam, LPARAM lParam, bool& bHandle );
    //����ftp����
    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�Ƿ���Ա��浽Ԥ��λ
	bool IsCanSavePamPos();
    //����Ԥ��λͼƬ
    void DownloadPanPosImg();
	APP_DECLARE_MSG_MAP()
		

private:
		static const String m_strEdtPresetName;//Ԥ��λ����

		int m_dwCurrentCamID;//��ǰѡ�е������ID

// 		enum EmSetStyle//�༭���� �½����޸�
// 		{
// 			EMSET_NEW = 0,
// 			EMSET_MODIFY,
// 			EMSET_NO,
// 		};
// 		EmSetStyle m_emSetStyle;
		EmPancamPrePosState m_emListState;
		vector<TPanCam>     m_vctPresetList;  //Ԥ��λ�б�
		int m_dwSelItemId;  //��ǰѡ�е��ڵ�ǰҳ�µ�Ԥ��λId
		u16 m_wCurPageIndex;  //��ǰԤ��λ�б���ʼ������

		TPanCam m_tCurrentPreset;//��ǰ��������Ϣ
		TPanCamInfo m_tPanCamInfo;//ȫ���������Ϣ ��¼ʱnty֪ͨ
		CFtpCtrl m_cFtp;//Ԥ��λ�б��ͼ����   
		std::vector<String>  m_vecDownloadPicName;   //���ص��ļ���
		bool m_bIsShortCutClosed;//�Ƿ��˹����رսݷ�ʽ

        int m_wPresetID;//��ǰ֪ͨ��Ԥ��λID
//        bool m_bIsPanCamLisOpenFtp;//����Ԥ��λ�б�ʱ��ftp
};

