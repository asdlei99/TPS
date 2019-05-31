/** @defgroup 摄像机远摇逻辑单元 
 *  @version V1.1.5
 *  @author  叶良平
 *  @date    2017.5.16
 */
#pragma once

class CCameraControlLogic : public CNotifyUIImpl, public Singleton<CCameraControlLogic> 
{
public:
	CCameraControlLogic(void);
	~CCameraControlLogic(void);

protected:
	//是否开启远摇摄像机控制 //远摇摄像机通知消息中 个数大于0才开启控制，否则不可控
	void EnableFeccCtrl( bool bIsEnable );

	//点击返回按钮
	bool OnBtnCramerBack(TNotifyUI& msg);

	//点击摄像机向上按钮
	bool OnBtnCamUp(TNotifyUI& msg);
	bool OnBtnCamUpDown(TNotifyUI& msg);
	//点击摄像机向右按钮
	bool OnCamRight(TNotifyUI& msg);
	bool OnCamRightDown(TNotifyUI& msg);
	//点击摄像机向左按钮
	bool OnBtnCamLeft(TNotifyUI& msg);
	bool OnBtnCamLeftDown(TNotifyUI& msg);
	//点击摄像机向下按钮
	bool OnBtnCamDown(TNotifyUI& msg);
	bool OnBtnCamDownDown(TNotifyUI& msg);
	//点击视野增加按钮
	bool OnBtnViewPlus(TNotifyUI& msg);
	bool OnBtnViewPlusDown(TNotifyUI& msg);
	//点击视野减少按钮
	bool OnBtnViewMinus(TNotifyUI& msg);
	bool OnBtnViewMinusDown(TNotifyUI& msg);
	//点击焦距增加按钮
	bool OnBtnFocusPlus(TNotifyUI& msg);
	bool OnBtnFocusPlusDown(TNotifyUI& msg);
	//点击自动对焦按钮
	bool OnBtnFocusAuto(TNotifyUI& msg);
	//点击焦距减少按钮
	bool OnBtnFocusMinus(TNotifyUI& msg);
	bool OnBtnFocusMinusDown(TNotifyUI& msg);
	//点击亮度增加按钮
	bool OnBtnBrightPlus(TNotifyUI& msg);
	bool OnBtnBrightPlusDown(TNotifyUI& msg);
	//点击亮度减少按钮
	bool OnBtnBrightMinus(TNotifyUI& msg);
	bool OnBtnBrightMinusDown(TNotifyUI& msg);

	//摄像机下拉菜单
	bool OnComboCamSel(TNotifyUI& msg);

	//更新视频源列表
    bool On323VedioSourceNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//断链响应
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

private:
	TVidFeccInfo m_tVidFeccInfo;

	APP_DECLARE_MSG_MAP()
	
};

