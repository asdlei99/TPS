/** @defgroup 双流窗口
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015.1.5
 */
#pragma once
//#include "Decoder.h"

class CDualViewLogic : public CNotifyUIImpl,public Singleton<CDualViewLogic> 
{
public:
	CDualViewLogic(void);
	~CDualViewLogic(void);
// protected:
// 	/** 窗口创建 
// 	*  @param[in] 消息
// 	*  @return 是否成功
// 	*/
// 	bool OnCreate(TNotifyUI& msg);
// 
// 	/** 初始化消息 
// 	 *  @param[in] 
// 	 *  @node 
// 	 *  @return 
// 	 */
// 	bool OnInit(TNotifyUI& msg);
// 
// 	bool OnDestroy(TNotifyUI& msg);
// 
// 	/** 返回
// 	*  @param[in] 消息
// 	*  @return 是否成功
// 	*/
// 	bool OnBtnCancel(TNotifyUI& msg);
// 	/** 退出
// 	*  @param[in] 消息
// 	*  @return 
// 	*/
// 	bool OnBtnOk(TNotifyUI& msg);
// 
// 	/** 断链
// 	*  @param[in] 消息
// 	*  @return 
// 	*/
// 	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
// 
// public:  
//     
//     bool OnBtnDBLCLKVedioWnd(TNotifyUI& msg);
// 
//     void AskKeyFrame( BOOL32 bForce );
// 
//     void SetDecVol( u8 abyVol );
// 
//     u8 GetDecVol();
// 
// 	bool HideDualView();
//  
// protected: 
// 
//     bool OnShowVideo(WPARAM wParam, LPARAM lParam, bool& bHandle);
//     bool OnHideVedio(WPARAM wParam, LPARAM lParam, bool& bHandle);
// 
//     bool OnStartRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
// 
//     bool OnHungupConf(WPARAM wParam, LPARAM lParam, bool& bHandle);
//     bool OnConfStateNotify( WPARAM wparam, LPARAM lparam, bool& bHandle);
//     void StopRcvVedio();
// 
// private:
//     //开始/停止 观看双流演示
//     void PlayDual();
// 
//     void InitParam();
// 
//     void RestoreVedioWnd(  );
// 
// private:
// 	CDecoder  m_cDecoder;
// 	TTPCnMediaTransPort		m_tVedioIpTransAddr;
//     TTPCnMediaTransPort		m_tAudioIpTransAddr;
//    
//     BOOL32 m_bRecvStream;
//     BOOL32 m_bDecod;

	APP_DECLARE_MSG_MAP()
	 
};