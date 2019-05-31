/** @defgroup 会场控制 全景摄像机控制逻辑
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.17
 */
#pragma once


enum EmPancamPrePosState//预置位列表状态 调用或保存
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
	//获取当前摄像机ID
	int GetCamID(){return m_dwCurrentCamID;};
protected:

	//点击预置位按钮
	bool OnBtnImplePosSet(TNotifyUI& msg);
	//点击保存预置位按钮
	bool OnBtnSavePosSet(TNotifyUI& msg);
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
	//点击开启全景摄像头按钮
	bool OnCheckStartCam(TNotifyUI& msg);
	//点击创建快捷方式按钮
	bool OnCheckCamShortCut(TNotifyUI& msg);
	//点击全景摄像机下拉菜单
	bool OnComboCamSel(TNotifyUI& msg);
	//选择全景摄像机列表中一项
	bool OnPresetListItemSelected(TNotifyUI& msg);
	//点击取消预置位编辑
	bool OnBtnCancelPanSet(TNotifyUI& msg);
	//点击保存预置位编辑
	bool OnBtnSavePanPresetNameSet(TNotifyUI& msg);
	//点击保存预置位编辑
	bool OnBtnSetPresetName(TNotifyUI& msg);   
	//点击删除预置位
	bool OnBtnPresetDel(TNotifyUI& msg);
	//点击增加预置位
	bool OnBtnPresetAdd(TNotifyUI& msg);
	//点击取消预置位列表预览
	bool BtnPresetCancel(TNotifyUI& msg);
	//点击预置位列表选择确定按钮
	bool OnBtnPresetOk(TNotifyUI& msg);
	//点击预置位列表向左
	bool OnBtnCamListLeft(TNotifyUI& msg);
	//点击预置位列表向右
	bool OnBtnCamListRight(TNotifyUI& msg);
	//摄像机选择通知
	bool OnSelSelCamInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//更新列表
	bool UpdateList();
	bool UpdateList(CString strPresetName, u8 wPageID, u8 wItemID);
	//更新显示的预置位列表 bLeft是否向左更新
	void UpdateShowPreList(bool bLeft);

	//全景摄像机列表通知
	bool OnPanCamLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//全景摄像机保存预置位结果
	bool OnPanCamPresetSaveNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//全景摄像机调用预置位结果
	bool OnPanCamPresetImpleNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//全景摄像机删除预置位结果
	bool OnPanCamPresetDeleteNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//全景摄像机修改预置位名称保存结果
	bool OnPanCamSavePresetNameInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//全景摄像机开启结果
	bool OnPanCamStartInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //弹出软键盘
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/* 功能: 预置位列表截图下载
	* @param    const String& strRemotePath     [in]     远端路径
	* @param    const String& strLocalFile      [in]     本地路径
	* @param    const String& strCheckFileName     [in]     文件名	
	* @return   BOOL 是否上传成功
	* @remarks  
	*/
	BOOL DownloadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	/** 台标下载ftp消息响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnDownloadProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//ctring转char数组
	bool WCharToMByte(CString strPresetName, char* achName);

		/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//是否开启全景摄像机控制 //全景摄像机通知消息中 个数大于0才开启控制，否则不可控
	void EnablePamCtrl(bool bIsEnable);
	//全景摄像机快捷方式通知，若无全景摄像机，控制menu列表去掉快捷方式
	bool OnSetShortCheck( WPARAM wParam, LPARAM lParam, bool& bHandle );
    //开启ftp反馈
    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//是否可以保存到预置位
	bool IsCanSavePamPos();
    //下载预置位图片
    void DownloadPanPosImg();
	APP_DECLARE_MSG_MAP()
		

private:
		static const String m_strEdtPresetName;//预置位名称

		int m_dwCurrentCamID;//当前选中的摄像机ID

// 		enum EmSetStyle//编辑类型 新建或修改
// 		{
// 			EMSET_NEW = 0,
// 			EMSET_MODIFY,
// 			EMSET_NO,
// 		};
// 		EmSetStyle m_emSetStyle;
		EmPancamPrePosState m_emListState;
		vector<TPanCam>     m_vctPresetList;  //预置位列表
		int m_dwSelItemId;  //当前选中的在当前页下的预置位Id
		u16 m_wCurPageIndex;  //当前预置位列表起始项索引

		TPanCam m_tCurrentPreset;//当前操作的信息
		TPanCamInfo m_tPanCamInfo;//全景摄像机信息 登录时nty通知
		CFtpCtrl m_cFtp;//预置位列表截图下载   
		std::vector<String>  m_vecDownloadPicName;   //下载的文件名
		bool m_bIsShortCutClosed;//是否人工开关闭捷方式

        int m_wPresetID;//当前通知的预制位ID
//        bool m_bIsPanCamLisOpenFtp;//更新预制位列表时打开ftp
};

