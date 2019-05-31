/** @defgroup �����Զҡ�߼���Ԫ 
 *  @version V1.1.5
 *  @author  Ҷ��ƽ
 *  @date    2017.5.16
 */
#pragma once

class CCameraControlLogic : public CNotifyUIImpl, public Singleton<CCameraControlLogic> 
{
public:
	CCameraControlLogic(void);
	~CCameraControlLogic(void);

protected:
	//�Ƿ���Զҡ��������� //Զҡ�����֪ͨ��Ϣ�� ��������0�ſ������ƣ����򲻿ɿ�
	void EnableFeccCtrl( bool bIsEnable );

	//������ذ�ť
	bool OnBtnCramerBack(TNotifyUI& msg);

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

	//����������˵�
	bool OnComboCamSel(TNotifyUI& msg);

	//������ƵԴ�б�
    bool On323VedioSourceNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//������Ӧ
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

private:
	TVidFeccInfo m_tVidFeccInfo;

	APP_DECLARE_MSG_MAP()
	
};

