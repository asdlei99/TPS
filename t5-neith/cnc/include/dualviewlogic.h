/** @defgroup ˫������
 *  @version V1.1.4
 *  @author  ��ӨӨ
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
// 	/** ���ڴ��� 
// 	*  @param[in] ��Ϣ
// 	*  @return �Ƿ�ɹ�
// 	*/
// 	bool OnCreate(TNotifyUI& msg);
// 
// 	/** ��ʼ����Ϣ 
// 	 *  @param[in] 
// 	 *  @node 
// 	 *  @return 
// 	 */
// 	bool OnInit(TNotifyUI& msg);
// 
// 	bool OnDestroy(TNotifyUI& msg);
// 
// 	/** ����
// 	*  @param[in] ��Ϣ
// 	*  @return �Ƿ�ɹ�
// 	*/
// 	bool OnBtnCancel(TNotifyUI& msg);
// 	/** �˳�
// 	*  @param[in] ��Ϣ
// 	*  @return 
// 	*/
// 	bool OnBtnOk(TNotifyUI& msg);
// 
// 	/** ����
// 	*  @param[in] ��Ϣ
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
//     //��ʼ/ֹͣ �ۿ�˫����ʾ
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