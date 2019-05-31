#include "StdAfx.h"
#include "dualviewlogic.h"
#include "confmsglogic.h"

template<> CDualViewLogic* Singleton<CDualViewLogic>::ms_pSingleton  = NULL;
APP_BEGIN_MSG_MAP(CDualViewLogic, CNotifyUIImpl)

// 	MSG_CREATEWINDOW(_T("DualViewLayout"), OnCreate)
// 	MSG_INIWINDOW(_T("DualViewLayout"), OnInit)
// 	MSG_WINDOWDESTORY(_T("DualViewLayout"), OnDestroy)
// 
// 	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)
// 	MSG_CLICK(_T("BtnOk"), OnBtnOk)
// 	USER_MSG(UI_CNS_DISCONNECTED,OnDisconnect)
// 
// 	MSG_DBCLICK(_T("DualViewLayout"),OnBtnDBLCLKVedioWnd)
// 
// 	USER_MSG(WM_CMS_SHOWVIDEO, OnShowVideo)
// 	USER_MSG(UI_CNSINS_START_DUALCODESTREAM_RSP, OnStartRsp)
// 	USER_MSG(UI_UMS_HANGUP_CONF_RSP,OnHungupConf)
// 	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNotify)
// 	USER_MSG(WM_CMS_HIDE_VEDIO,OnHideVedio)

APP_END_MSG_MAP()


CDualViewLogic::CDualViewLogic( void )//:m_bDecod(false), m_bRecvStream(false)
{
}


CDualViewLogic::~CDualViewLogic(void)
{
}


// bool CDualViewLogic::OnCreate( TNotifyUI& msg )
// {
// 	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());
// 
// 	s32 nTop = DEFAULT_TITLE_HEIGHT;
// 	if ( CPaintManagerUI::IsSelfAdaption() )
// 	{
// 		float fAdpX, fAdpY;
// 		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
// 		nTop = s32(nTop * fAdpY);
// 	}
// 	SetWindowPos( m_pm->GetPaintWindow(), NULL, 0, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
// 	return false;
// }
// 
// bool CDualViewLogic::OnInit(TNotifyUI& msg)
// {		
// 	return true;
// }
// 
// bool CDualViewLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 	m_bDecod = FALSE;
// 	m_bRecvStream = FALSE;
// 	
// 	return NO_ERROR;
// }
// 
// 
// bool CDualViewLogic::OnBtnCancel( TNotifyUI& msg )
// {
// 	HideDualView();
// 	return true;
// }
// 
// bool CDualViewLogic::OnBtnOk( TNotifyUI& msg )
// {
// 	//delete this;
// 	return true;
// }
// 
// bool CDualViewLogic::OnDestroy( TNotifyUI& msg )
// {
// 	UNREG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());
// 	return true;
// }
// 
// bool CDualViewLogic::OnBtnDBLCLKVedioWnd( TNotifyUI& msg )
// {
// 	return true;
// }
// 
// void CDualViewLogic::PlayDual()
// {
// 	if (m_cDecoder.IsPlayed() == FALSE)
// 		//没在监控
// 	{   
// 		InitParam();
// 		ComInterface->StartDualCodeStream( m_tVedioIpTransAddr, m_tAudioIpTransAddr );
// 
// 		//等待cns回应然后才开始监控
// 	}
// 	else //已经在监控
// 	{  
// 
// 		ComInterface->StopDualCodeStream(  );
// 		m_cDecoder.StopPlay();
// 		m_bRecvStream = FALSE;
// 		m_bDecod = FALSE; 
// 
// 	}
// }
// 
// void CDualViewLogic::InitParam()
// {
// 	SET_ASK_MAIN_FRAME_FUN( &CDualViewLogic::AskKeyFrame, CDualViewLogic::GetSingletonPtr(), CDualViewLogic )  
// 
//     //获取重传次数  是否要配置？ dyy 
//     int nResendTime = 1;// atoi( strTime.c_str() );
// 
//     TNetRSParam tNetRSParam;
//     tNetRSParam.m_wFirstTimeSpan = 40;
// 
//     switch( nResendTime )
//     {
//     case 1:
//         tNetRSParam.m_wSecondTimeSpan = 0;
//         tNetRSParam.m_wThirdTimeSpan = 0;
//         break;
//     case 2:
//         tNetRSParam.m_wSecondTimeSpan = 80;
//         tNetRSParam.m_wThirdTimeSpan = 0;
//         break;
//     case 3:
//         tNetRSParam.m_wSecondTimeSpan = 80;
//         tNetRSParam.m_wThirdTimeSpan = 120;
//         break;
//     default:
//         tNetRSParam.m_wSecondTimeSpan = 0;
//         tNetRSParam.m_wThirdTimeSpan = 0;
//         break;
//     }
// 
//     //tNetRSParam.m_wSecondTimeSpan = 0 /*80*/;  //第二个重传检测点
//     //tNetRSParam.m_wThirdTimeSpan = 0 /*120*/;   //第三个重传检测点
// 	tNetRSParam.m_wRejectTimeSpan = 2000;  //过期丢弃的时间跨度
//     m_cDecoder.SetNetFeedbackVideoParam( tNetRSParam, TRUE );
//     m_cDecoder.SetNetFeedbackAudioParam( tNetRSParam, TRUE );
// 
//     u32 dwLocalIP = 0;
//     ::ComInterface->GetLocalIP( dwLocalIP ); 
//     
// 	//2012.9.27  避免该端口已经被其他程序占用而导致无法正常接收到音视频码流问题  by yujinjin
//     u16 wVedioPort = GetIdlePort( dwLocalIP,RTP_LOCALVIDEO_PORT, RTP_LOCALVIDEO_PORT + 100 );
// 	u16 wAudioPort = GetIdlePort( dwLocalIP,wVedioPort +2 , RTP_LOCALVIDEO_PORT + 200 );
// 
//     /*
//     CString strGIp = "225.0.2.1"; //组播地址
//     
//     int nIp[4] = {0};
//     sscanf( (LPTSTR)(LPCTSTR)strGIp, "%d.%d.%d.%d", &nIp[0],&nIp[1],&nIp[2],&nIp[3] );
//     
//     CString strIP;
//     strIP.Format( _T("%d.%d.%d.%d"), nIp[0], nIp[1], nIp[2], nIp[3] );
//     
// 	u32 dwIp = ntohl( inet_addr( strIP ) );
// 
//     dwLocalIP = dwIp; */
// 
//     m_tVedioIpTransAddr.m_tRtpPort.m_dwIP = htonl(dwLocalIP);
//     m_tVedioIpTransAddr.m_tRtpPort.m_wPort = wVedioPort;
//     
// 	
//     m_tAudioIpTransAddr.m_tRtpPort.m_dwIP = htonl(dwLocalIP);
//     m_tAudioIpTransAddr.m_tRtpPort.m_wPort = wAudioPort;
//     
//     //设置监控信息接受的端口和Ip地址
//     m_cDecoder.SetInfo(m_tVedioIpTransAddr.m_tRtpPort.m_wPort , dwLocalIP , dwLocalIP );
//     TMediaParam  tMonitorParam;
//     tMonitorParam.abyDynamicPayLoad[0] = MEDIA_TYPE_H264;
//     tMonitorParam.abyDynamicPayLoad[1] = MEDIA_TYPE_AACLC;
//     
//     tMonitorParam.abyRealType[0] = MEDIA_TYPE_H264;
//     tMonitorParam.abyRealType[1] = MEDIA_TYPE_AACLC;
//     
//     tMonitorParam.atEncryptKey[0].byLen = 0;
//     tMonitorParam.atEncryptKey[1].byLen = 0;
//     
//     m_cDecoder.SetVideoParam(tMonitorParam);
//     
//     TAudAACParam tAACParam;
//     tAACParam.dwChannel = 1;
//     tAACParam.dwSamplePerSecond = 32000;
//     m_cDecoder.SetAACParam(tAACParam);
// }
// 
// void CDualViewLogic::RestoreVedioWnd()
// {
// 	Window *pVideo = WINDOW_MGR_PTR->GetWindow(g_stcStrDualViewDlg.c_str());
// 
// 	if ( pVideo != NULL )
// 	{   
// 		m_cDecoder.SetWnd( pVideo->GetHWND() ); 
// 		//pVideo->Invalidate();//2012-7-26 解决窗口还原后人残留大窗口图像       
// 	} 
// 
// 	//切换大小时请求关键帧，防止白屏 -2014.3.4 xcr
// 	m_cDecoder.AskKeyFrame( TRUE );
// 
// 	WINDOW_MGR_PTR->ShowWindow(g_stcStrDualViewDlg.c_str());
// }
// 
// bool CDualViewLogic::OnShowVideo( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 	if ( m_bDecod && m_bRecvStream )
// 	{
// 		bool bVis = WINDOW_MGR_PTR->IsWindowVisible(g_stcStrDualViewDlg.c_str());
// 		if ( bVis )
// 		{   
// 			HideDualView();
// 		}
// 		else
// 		{ 
// 			RestoreVedioWnd( );
// 		}
// 		
// 	}
// 	else if ( !m_bDecod && m_bRecvStream )
// 	{
// 		m_cDecoder.StartPlay(); 
// 		RestoreVedioWnd( );
// 		m_bDecod = FALSE;
// 
// 	}
// 	else
// 	{             
// 		PlayDual();
// 	}
// 
// 	return S_OK;
// }
// 
// bool CDualViewLogic::OnHideVedio( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 	m_bRecvStream = FALSE;
// 	return HideDualView();
// }
// 
// bool CDualViewLogic::HideDualView()
// {      
// 	bool bVis = WINDOW_MGR_PTR->IsWindowVisible(g_stcStrDualViewDlg.c_str());
// 	if ( bVis )
// 	{   
// 		WINDOW_MGR_PTR->ShowWindow(g_stcStrDualViewDlg.c_str(), false);
// 	}
// 	
// 	//m_cDecoder.SetWnd(NULL);
// 	m_cDecoder.StopPlay();
// 	m_bDecod = FALSE;
// 
// 	return true;
// }
// 
// bool CDualViewLogic::OnStartRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 
// 	EmTPAddDualRcvResult emReVideo = (EmTPAddDualRcvResult)wParam;
// 	EmTPAddDualRcvResult emReAudio = (EmTPAddDualRcvResult)lParam;
// 	CString strMsg = _T("");
// 	if( emReAudio != emAddDualRcvSucceed && emReVideo != emAddDualRcvSucceed )
// 	{
// 		switch( emReVideo )
// 		{
// 		case emAddDualRcvFailNoDual:
// 			strMsg = _T("观看演示失败：当前未处于接收双流状态");
// 			break;
// 
// 		case emAddDualRcvFailIllegalPos:
// 			strMsg = _T("观看演示失败：通道非法");
// 			break;
// 		case emAddDualRcvFailNoPos:
// 			strMsg = _T("观看演示失败：无空闲通道");
// 			break;
// 		case emAddDualRcvFailUnKown:
// 			strMsg = _T("观看演示失败");
// 			break;
// 		case emAddDualRcvFailStatusError:
// 			strMsg = _T("观看演示失败：当前已处于双流状态");
// 			break;
// 		default:
// 			strMsg = _T("观看演示失败");
// 			break;
// 		}
// 
// 		ShowPopMsg(strMsg);
// 		return S_FALSE;
// 	}
// 
// 	if ( emReAudio != emAddDualRcvSucceed )
// 	{
// 		switch( emReVideo )
// 		{
// 		case emAddDualRcvFailNoDual:
// 			strMsg = _T("接收演示音频失败:当前未处于接收双流状态");
// 			break;
// 
// 		case emAddDualRcvFailIllegalPos:
// 			strMsg = _T("接收演示音频失败:通道非法");
// 			break;
// 		case emAddDualRcvFailNoPos:
// 			strMsg = _T("接收演示音频失败:无空闲通道");
// 			break;
// 		case emAddDualRcvFailUnKown:
// 			strMsg = _T("接收演示音频失败"); //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
// 			break;
// 		case emAddDualRcvFailStatusError:
// 			strMsg = _T("接收演示音频失败:当前已处于双流状态");
// 			break;
// 		default:
// 			strMsg = _T("接收演示音频失败");
// 			break;
// 		}
// 		ShowPopMsg(strMsg);
// 	}
// 	else
// 	{   
// 		 //cnc不显示双流 
// // 		WINDOW_MGR_PTR->ShowWindow(g_stcStrDualViewDlg.c_str());
// // 
// // 		TTPCnMediaTransPort tMediaTranAddr = ComInterface->GetVedioTransAddr();
// // 		m_cDecoder.SetVideoBackParam( tMediaTranAddr.m_tBackRtcpPort.GetPort(), 
// // 			tMediaTranAddr.m_tBackRtcpPort.GetIP() ); 
// // 
// // 		Window *pVideo = WINDOW_MGR_PTR->GetWindow(g_stcStrDualViewDlg.c_str());
// // 
// // 		if ( pVideo != NULL )
// // 		{   
// // 			m_cDecoder.SetWnd( pVideo->GetHWND() );     
// // 		}
// // 
// // 		m_cDecoder.StartPlay(); 
// // 
// // 		m_bRecvStream = TRUE;
// // 		m_bDecod = TRUE;
// 	}   
// 
// 	return S_OK;
// }
// 
// bool CDualViewLogic::OnHungupConf( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 	HideDualView();
// 	StopRcvVedio();
// 
// 	return S_OK;
// }
// 
// bool CDualViewLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam, bool& bHandle)
// {
// 	BOOL32 bInConf = ComInterface->IsInConf();
// 	if ( !bInConf )
// 	{
// 		HideDualView();
// 		StopRcvVedio();
// 	}
// 
// 	return NO_ERROR;
// }
// 
// void CDualViewLogic::StopRcvVedio()
// {
// 	m_bDecod = FALSE;
// 	if ( m_bRecvStream )
// 	{
// 		ComInterface->StopDualCodeStream(); 
// 		m_bRecvStream = FALSE;
// 	} 
// }
// 
// void CDualViewLogic::AskKeyFrame( BOOL32 bForce )
// {
// 	ComInterface->ReqKeyFrame( bForce );
// }
// 
// void CDualViewLogic::SetDecVol( u8 abyVol )
// {
// 	m_cDecoder.SetAudioVolume(abyVol);
// }
// 
// u8 CDualViewLogic::GetDecVol()
// {
// 	u8 abyVol = 0;
// 	m_cDecoder.GetAudioVolume( abyVol );
// 	return abyVol;
// }
