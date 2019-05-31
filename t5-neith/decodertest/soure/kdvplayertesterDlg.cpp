
// kdvplayertesterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "kdvplayertester.h"
#include "kdvplayertesterDlg.h"
#include "PlayStatus.h"
#include "PicView.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CkdvplayertesterDlg 对话框




BEGIN_MESSAGE_MAP(CMyStatic,   CStatic)  
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()  


void   CMyStatic::OnLButtonDown(UINT   nFlags,   CPoint   point)
{
	if(this->GetParent() !=NULL)  
	{

	}
	CStatic::OnLButtonDown(nFlags,point);
}


void CMyStatic::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(this->GetParent() !=NULL)  
	{
		GetParent()->SendMessage(WM_STATICMOUSEDBCLIK); 
	}
	CStatic::OnLButtonDblClk(nFlags,point);
}
BOOL CMyStatic::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

HANDLE	m_BmpNoVid;
HANDLE	m_BmpNoVid_Small;
HANDLE	m_BmpHandle[FAILD_PIC_NUM];

void CMyStatic::OnPaint() 
{
	CStatic::OnPaint();

	CDC *pDC = GetDC();

	CDC dcMem;                     
	dcMem.CreateCompatibleDC(NULL); 

	CBitmap bmp;
	static DWORD totalNum = 0;

	CRect client; 
	GetClientRect(&client); 

	bmp.CreateCompatibleBitmap(&dcMem,client.Width(),client.Height());

	if (m_curType == em_NoVid)
	{
		//pDC->BitBlt(0, 0, client.Width(),client.Height(), &dcMem, 0, 0, SRCCOPY); 
		
		BITMAP m_sbitmap;
		if (client.Width() < 1200)
		{
			dcMem.SelectObject(m_BmpNoVid_Small);		
			GetObject(m_BmpNoVid_Small,sizeof(m_sbitmap),&m_sbitmap);
		}
		else
		{
			dcMem.SelectObject(m_BmpNoVid);		
			GetObject(m_BmpNoVid,sizeof(m_sbitmap),&m_sbitmap);
		}
		
		
		//BITMAP m_sbitmap;
		//GetObject(m_BmpNoVid,sizeof(m_sbitmap),&m_sbitmap);

		pDC->StretchBlt(0,0,client.Width(),client.Height(), &dcMem, 0, 0, m_sbitmap.bmWidth, m_sbitmap.bmHeight, SRCCOPY);
	}
	else if (m_curType == em_VidErr)
	{
		static DWORD totalNum = 0;
		dcMem.SelectObject(m_BmpHandle[(totalNum++)%FAILD_PIC_NUM]);		
		pDC->BitBlt(0, 0, client.Width(),client.Height(), &dcMem, 0, 0, SRCCOPY); 
	}
	else
	{
		dcMem.SelectObject(&bmp);
		dcMem.FillSolidRect(client,pDC->GetBkColor());
		pDC->BitBlt(0, 0, client.Width(),client.Height(), &dcMem, 0, 0, SRCCOPY); 
	}

	ReleaseDC(pDC);
	bmp.DeleteObject();
	dcMem.DeleteDC();


	//static DWORD totalNum = 0;
	//SetBitmap((HBITMAP)m_BmpHandle[(totalNum++)%FAILD_PIC_NUM]); 
}

BOOL32 g_bPrintLog = FALSE;
API void printlog()
{
	g_bPrintLog = !g_bPrintLog;
}

//应用于量子场景，播放存在三种状态：解码无视频流、正常视频解码、量子视频帧被丢弃
void CMyStatic::OnRefresh(CKdvDecoder* pDecoder)
{
	static DWORD totalProcCount = 1;	
	static DWORD dwlasttime = 1;

	static DWORD dwlastnovid = 0;		//上一次统计没有视频的时间
	static DWORD dwlastlose = 0;		//上一次丢帧的时间
	static DWORD dwLastAllPacket = 0;	//上次无视频时，被丢掉的帧数；

	if (pDecoder == NULL)
	{
		dwlastlose = 0;
		dwlastnovid = 0;
		m_curType = em_None;
		OnPaint();
		return;
	}
	TKdvDecStatis Statis;
	memset(&Statis,0,sizeof(Statis));
	
	++totalProcCount;

	if ((totalProcCount-dwlasttime)*TIME_PACKET_CHECK_SPAN >= 500)
	{//大于500毫秒，更新统计数据
		pDecoder->GetVidDecoderStatis(Statis);

		if (g_bPrintLog)
		{
			OspPrintf(1, 0, "LastFrame:%d, LastLost:%d, m_dwTotalPackNum:%d, curFrame:%d, curLost:%d, totaltime:%d, lasttime:%d, lastnovid:%d, lastlose:%d\n",
				m_tRcvStatis.m_dwVideoRecvFrame, m_tRcvStatis.m_dwVideoLoseFrame, Statis.m_dwTotalPackNum,  Statis.m_dwVideoRecvFrame, Statis.m_dwVideoLoseFrame,
				totalProcCount, dwlasttime, dwlastnovid, dwlastlose);
		}
		
		if (Statis.m_dwVideoRecvFrame - m_tRcvStatis.m_dwVideoRecvFrame >= 1)
		{//只要存在解码，则认为显示正常图像
			m_curType = em_None;
			dwlastnovid = 0;
			dwlastlose = 0;

			if (g_bPrintLog)
			{
				OspPrintf(TRUE, FALSE, "*********** change status to em_None ******** \n");
			}

		}
		else if (Statis.m_dwTotalPackNum - m_tRcvStatis.m_dwTotalPackNum >= 5)
		{//收到包,但无法解													
			dwlastnovid = 0;			

			if (dwlastlose != 0)
			{
				if ((totalProcCount-dwlastlose)*TIME_PACKET_CHECK_SPAN >= 500)
				{//超过500毫秒还在丢帧，则认为是加密码流
					m_curType = em_VidErr;
					if (g_bPrintLog)
					{
						OspPrintf(TRUE, FALSE, "*********** change status to em_VidErr ******** \n");
					}
				}
			}	
			else
			{
				dwlastlose = totalProcCount;				
			}
		}
		else
		{//没有收到数据帧：即没有正常解码，也没有被丢的视频帧
			dwlastlose = 0;

			if (dwlastnovid != 0)
			{
				if ((totalProcCount-dwlastnovid)*TIME_PACKET_CHECK_SPAN >= 800)
				{//800毫秒秒内没有收到包
					if ((Statis.m_dwTotalPackNum - dwLastAllPacket) < 1)
					{
						m_curType = em_NoVid;
						if (g_bPrintLog)
						{
							OspPrintf(TRUE, FALSE, "*********** change status to em_NoVid ******** \n");
						}
					}

					//清除统计数据
					dwLastAllPacket = 0;
					dwlastnovid = 0;
				}
			}	
			else
			{
				//记录最后一次无视频的时间，以及当前的丢帧数
				dwlastnovid = totalProcCount;
				dwLastAllPacket = Statis.m_dwTotalPackNum;
			}
		}

		memcpy(&m_tRcvStatis, &Statis, sizeof(m_tRcvStatis));
		dwlasttime = totalProcCount;
	}

	if (m_curType != em_None)
	{
		OnPaint();
	}
}


CkdvplayertesterDlg::CkdvplayertesterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CkdvplayertesterDlg::IDD, pParent)
{
	m_nVideoPort  = 60042;
	m_nAudioPort  = 7202;
	m_nRomoteVidPort = 0;
	m_nRomoteAudPort = 0;
	m_nActivePT   = 106;
	m_bActivePT   = TRUE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pRemoteIpAddress = NULL;
	m_bStartDecode = FALSE;
}

void CkdvplayertesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VIDEO_LOCAL_PORT, m_nVideoPort);
	DDX_Text(pDX, IDC_AUDIO_LOCAL_PORT, m_nAudioPort);
	DDX_Text(pDX, IDC_VIDEO_REMOTE_PORT, m_nRomoteVidPort);
	DDX_Text(pDX, IDC_AUDIO_REMOTE_PORT, m_nRomoteAudPort);
	DDX_Text(pDX, IDC_EDIT_ACTIVEPT, m_nActivePT);
	DDX_Control(pDX, IDC_COMBO_DECTYPE, m_comDecType);
	DDX_Control(pDX, IDC_COMBO_IFRAME, m_comboFrame);
	DDX_Control(pDX, IDC_LOCAL_IPADDR, m_cLocalIpAddr);
	DDX_Control(pDX, IDC_REMOTE_IPADDR, m_cRemoteIpAddr);
	DDX_Control(pDX, IDC_VIDEO_WINDOW_SLIDER, m_cscVideoWindow);
	DDX_Control(pDX, IDC_AUDIO_VOLUME_SLIDER, m_cscAudioVolume);
	DDX_Check(pDX, IDC_CHECK_ACTIVEPT, m_bActivePT);
	DDV_MinMaxUInt(pDX, m_nActivePT, 0, 255);
	DDX_Control(pDX, IDC_AUDIO_POWER, m_cAPStatic);


}

BEGIN_MESSAGE_MAP(CkdvplayertesterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON11, &CkdvplayertesterDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_SET_NET_PARAM, &CkdvplayertesterDlg::OnSetNetParam)
	ON_BN_CLICKED(IDC_START_NET_RCV, &CkdvplayertesterDlg::OnStartNetRcv)
	ON_BN_CLICKED(IDC_STOP_NET_RCV, &CkdvplayertesterDlg::OnStopNetRcv)
	ON_BN_CLICKED(IDC_START_VIDEO_DECOMP, &CkdvplayertesterDlg::OnStartVideoDecomp)
	ON_BN_CLICKED(IDC_STOP_VIDEO_DECOMP, &CkdvplayertesterDlg::OnStopVideoDecomp)
	ON_BN_CLICKED(IDC_FULLSCREEN, &CkdvplayertesterDlg::OnFullscreen)
	ON_BN_CLICKED(IDC_CHECK_ACTIVEPT, &CkdvplayertesterDlg::OnCheckActivept)
	ON_CBN_SELCHANGE(IDC_COMBO_DECTYPE, &CkdvplayertesterDlg::OnSelchangeComboDectype)
	ON_BN_CLICKED(IDC_KEY_FRAME_CHECK, &CkdvplayertesterDlg::OnKeyFrameCheck)
	ON_BN_CLICKED(IDC_CLEAR, &CkdvplayertesterDlg::OnClear)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_VIDEO_WINDOW_SLIDER, &CkdvplayertesterDlg::OnReleasedcaptureVideoWindowSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_AUDIO_VOLUME_SLIDER, &CkdvplayertesterDlg::OnReleasedcaptureAudioVolumeSlider)
	ON_BN_CLICKED(IDC_REDRAW, &CkdvplayertesterDlg::OnRedraw)
	ON_BN_CLICKED(IDC_STATUS, &CkdvplayertesterDlg::OnStatus)
	ON_BN_CLICKED(IDC_SNAP, &CkdvplayertesterDlg::OnSnap)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_AUDIO_VOLUME_SLIDER, &CkdvplayertesterDlg::OnReleasedcaptureAudioVolumeSlider)
	ON_BN_CLICKED(IDC_START_AUDIO_DECOMP, &CkdvplayertesterDlg::OnStartAudioDecomp)
	ON_BN_CLICKED(IDC_STOP_AUDIO_DECOMP, &CkdvplayertesterDlg::OnStopAudioDecomp)
	ON_MESSAGE(WM_STATICMOUSEDBCLIK,   OnStaticDButtonDown)
	ON_BN_CLICKED(IDC_START_DECODE_VID, &CkdvplayertesterDlg::OnStartDecVid)
	ON_BN_CLICKED(IDC_STOP_DECODE_VID, &CkdvplayertesterDlg::OnStopDecVid)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CkdvplayertesterDlg::GetLocalIp(void)
{
	s8 chCpuName[20] = {'\0'};
	s8 *pLocalIpAddress = NULL;
	hostent* pHost;
	if (gethostname(chCpuName, sizeof(chCpuName)) == 0)    //返回本地主机的标准主机名,失败返回SOCKET_ERROR
	{
		if ((pHost = gethostbyname(chCpuName)) != NULL)    
		{
			//返回给定主机名的包含主机名字和地址信息的结构体hostent的指针
			pLocalIpAddress = inet_ntoa(*((in_addr *)pHost->h_addr));  
		}
	}
	m_pLocalIpAddress  = pLocalIpAddress;
	//m_pRemoteIpAddress = pLocalIpAddress;
	m_cIp = (CString)pLocalIpAddress;
}


// CkdvplayertesterDlg 消息处理程序

#include "mstcpip.h"
//#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
SOCKET g_RawSocekt = INVALID_SOCKET;
int SetAdapterReceiveAll()
{
	//检查Winsock版本
	WORD ver=MAKEWORD(2,2);
	WSADATA wsaData;
	int err=WSAStartup(ver,&wsaData);
	if(err!=0)
	{
		_RPT2( _CRT_ERROR,"启动WinSocket version %d.%d 错误!",2,2);
		return 1;
	}
	//创建原始套接字
	g_RawSocekt=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
	if(g_RawSocekt == INVALID_SOCKET)
	{
		int x = GetLastError();
		return 10;
	}
	//设置为对IP头亲自操
	BOOL bFlag=TRUE;
	err=setsockopt(g_RawSocekt,IPPROTO_IP,IP_HDRINCL,(char *)&bFlag,sizeof(bFlag));
	if(err!=0)	
		return 2;
	//获得本机地址
	char hostname[256];
	memset(hostname,0,256);
	err=gethostname(hostname,256);
	if(err!=0)	
		return 3;
	struct hostent * phost=gethostbyname(hostname);
	struct in_addr addr;	

	for (int i=0;phost->h_addr_list[i]!=0;++i)
	{
		memcpy(&addr, phost->h_addr_list[i], sizeof(struct in_addr));
	}

	if(!phost)
		return 4;
	//把原始套接字绑定到本定网卡
	struct sockaddr_in addr_in;
	memset(&addr_in,0,sizeof(addr_in));
	addr_in.sin_addr=*(in_addr *)phost->h_addr_list[0];
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(57274);//端口号，可以是任意值，但最好不要和公共端口冲突	
	err = bind(g_RawSocekt, (PSOCKADDR)&addr_in, sizeof(addr_in));
	if (err == SOCKET_ERROR)
	{
		return 5;
	}
	// dwValue为输入输出参数，为1时执行，0时取消
	DWORD dwValue = 1; 
	// 设置 SOCK_RAW 为SIO_RCVALL，以便接收所有的IP包。其中SIO_RCVALL
	// 的定义为： #define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
	err = ioctlsocket(g_RawSocekt, SIO_RCVALL, &dwValue);
	if (err == SOCKET_ERROR)
	{
		return 6;
	}
	return 0;
}


int SetAdapterReceiveAllByIP(DWORD mIpAddress)
{

	if( g_RawSocekt != INVALID_SOCKET)
	{
		closesocket(g_RawSocekt);
		g_RawSocekt = INVALID_SOCKET;
	}

	//检查Winsock版本
	WORD ver=MAKEWORD(2,2);
	WSADATA wsaData;
	int err=WSAStartup(ver,&wsaData);
	if(err!=0)
	{
		_RPT2( _CRT_ERROR,"启动WinSocket version %d.%d 错误!",2,2);
		return 1;
	}
	//创建原始套接字
	g_RawSocekt=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
	if(g_RawSocekt == INVALID_SOCKET)
	{
		int x = GetLastError();
		return 10;
	}
	//设置为对IP头亲自操
	BOOL bFlag=TRUE;
	err=setsockopt(g_RawSocekt,IPPROTO_IP,IP_HDRINCL,(char *)&bFlag,sizeof(bFlag));
	if(err!=0)	
		return 2;

	//获得本机地址
	char hostname[256];
	memset(hostname,0,256);
	err=gethostname(hostname,256);
	if(err!=0)	
		return 3;
	struct hostent * phost=gethostbyname(hostname);
	struct in_addr addr;	

	for (int i=0;phost->h_addr_list[i]!=0;++i)
	{
		memcpy(&addr, phost->h_addr_list[i], sizeof(struct in_addr));
	}

	if(!phost)
		return 4;
	//把原始套接字绑定到本定网卡
	struct sockaddr_in addr_in;
	memset(&addr_in,0,sizeof(addr_in));
//	addr_in.sin_addr=*(in_addr *)phost->h_addr_list[0];
	addr_in.sin_addr.S_un.S_un_b.s_b1 = UCHAR(mIpAddress);
	addr_in.sin_addr.S_un.S_un_b.s_b2 = UCHAR(mIpAddress>>8);
	addr_in.sin_addr.S_un.S_un_b.s_b3 = UCHAR(mIpAddress>>16);
	addr_in.sin_addr.S_un.S_un_b.s_b4 = UCHAR(mIpAddress>>24);
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(57274);//端口号，可以是任意值，但最好不要和公共端口冲突	
	err = bind(g_RawSocekt, (PSOCKADDR)&addr_in, sizeof(addr_in));
	if (err == SOCKET_ERROR)
	{
		return 5;
	}
	// dwValue为输入输出参数，为1时执行，0时取消
	DWORD dwValue = 1; 
	// 设置 SOCK_RAW 为SIO_RCVALL，以便接收所有的IP包。其中SIO_RCVALL
	// 的定义为： #define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
	err = ioctlsocket(g_RawSocekt, SIO_RCVALL, &dwValue);
	if (err == SOCKET_ERROR)
	{
		return 6;
	}
	return 0;
}




BOOL CkdvplayertesterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//int flag = SetAdapterReceiveAll();
	//if (flag != 0)
	//{
	//	CString strBuf;
	//	//sprintf(buf, "error:%n!", flag);
	//	strBuf.Format(_T("error:%d"), flag);
	//	AfxMessageBox(strBuf);
	//}

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	if (!IsOspInitd())
	{
#ifdef _DEBUG
		OspInit(TRUE);
#else
		OspInit(FALSE);
#endif
	}	
	OspRegistModule("mediasdkvc10.dll");
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_bFullScreen = FALSE;
	GetDlgItem(IDC_START_NET_RCV)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_NET_RCV)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_VIDEO_DECOMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_DECOMP_CONFIG)->EnableWindow(FALSE);
	//GetDlgItem(IDC_START_AUDIO_DECOMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_AUDIO_DECOMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_FULLSCREEN)->EnableWindow(FALSE);
	//GetDlgItem(IDC_STATUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_CPPUNIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GET_AUDIO_POWER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_IFRAME)->EnableWindow(FALSE);
	CRect rect(20, 20, 372, 308);

	GetDlgItem(IDC_START_DECODE_VID)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_DECODE_VID)->EnableWindow(FALSE);

	m_cPlayerWnd.Create(NULL, SS_WHITERECT | SS_NOTIFY , rect, this, IDC_PLAYER);
	m_cPlayerWnd.ShowWindow(SW_SHOW);


	m_cPlayerWnd.ModifyStyle(WS_BORDER, SS_BITMAP|SS_CENTERIMAGE);
	m_cPlayerWnd.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

	GetLocalIp();
	this->SetDlgItemInt(IDC_VIDEO_LOCAL_PORT, m_nVideoPort);
	this->SetDlgItemInt(IDC_AUDIO_LOCAL_PORT,m_nAudioPort);
	this->SetDlgItemInt(IDC_VIDEO_REMOTE_PORT, m_nRomoteVidPort);
	this->SetDlgItemInt(IDC_AUDIO_REMOTE_PORT,m_nRomoteAudPort);
	this->SetDlgItemText(IDC_LOCAL_IPADDR, m_cIp);
	this->SetDlgItemText(IDC_REMOTE_IPADDR, m_cIp);

	this->m_cscAudioVolume.SetRange(0,255);
	this->m_cscAudioVolume.SetPos(128);
	this->m_cscVideoWindow.SetRange(0,352);
	this->m_cscVideoWindow.SetPos(0);

	m_comDecType.InsertString(0, _T("H261"));
	m_comDecType.InsertString(1, _T("H263"));
	m_comDecType.InsertString(2, _T("H263+"));
	m_comDecType.InsertString(3, _T("H264"));
	m_comDecType.InsertString(4, _T("MPEG2"));
	m_comDecType.InsertString(5, _T("MPEG4"));

	m_comDecType.SetItemData(0, MEDIA_TYPE_H261);
	m_comDecType.SetItemData(1, MEDIA_TYPE_H263);
	m_comDecType.SetItemData(2, MEDIA_TYPE_H263PLUS);
	m_comDecType.SetItemData(3, MEDIA_TYPE_H264);
	m_comDecType.SetItemData(4, MEDIA_TYPE_H262);
	m_comDecType.SetItemData(5, MEDIA_TYPE_MP4);

	m_comDecType.SetCurSel(3);
	m_comboFrame.SetCurSel(0);

	GetDlgItem(IDC_EDIT_ACTIVEPT)->EnableWindow(FALSE);
	m_comDecType.EnableWindow(FALSE);

	TInitAudDecoder tAudInitParam;
	memset(&tAudInitParam, 0 , sizeof(tAudInitParam));
	if (CODEC_NO_ERROR != m_KdvDecoder.InitialAudioDecoder(tAudInitParam))
	{
		AfxMessageBox(_T("Create AudioDecoder Error !"));
	}

	TInitVidDecoder tVidInitParam;
	memset(&tVidInitParam, 0 , sizeof(tVidInitParam));
	tVidInitParam.m_hwPlayVideo = m_cPlayerWnd.GetSafeHwnd();
	tVidInitParam.m_nCpuID = 0;
	if (CODEC_NO_ERROR != m_KdvDecoder.InitialVideoDecoder(tVidInitParam))
	{
		AfxMessageBox(_T("Create VideoDecoder Error !"));
	}
	OnCheckActivept();


	SetPos();


	SetTimer(TIME_PACKET_CHECK_EVENT, TIME_PACKET_CHECK_SPAN,NULL);


	TCHAR buf[255];
	for (int i = 0; i<FAILD_PIC_NUM; i++)
	{
		swprintf(buf, _T("./bmp/%d.bmp"), i);
		m_BmpHandle[i] = ::LoadImage(NULL,  
			buf,  //资源号或本地文件名  
			IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标  
			0,                  //宽度 0为默认大小  
			0,                  //高度 像素为单位  
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	}

	m_BmpNoVid = ::LoadImage(NULL, _T("./bmp/novid.bmp"), IMAGE_BITMAP,0,0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	m_BmpNoVid_Small = ::LoadImage(NULL, _T("./bmp/novid_small.bmp"), IMAGE_BITMAP,0,0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);


	if (m_BmpNoVid == 0 || m_BmpNoVid_Small == 0)
	{
		AfxMessageBox(_T("资源加载失败!"), MB_OK);
	}
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CkdvplayertesterDlg::SetPos()
{
	CRect rect;
	CRect vidRect;
	CRect itemRect;

	int wWidth = 0;
	int wHeight = 0;

	int wConstHeight = 17;
	int wConstHeightBtn = 23;

	int wTop;
	////
	GetClientRect(&rect);

	wTop = rect.top + 10;

	GetDlgItem(IDC_STATIC_IP)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left += 10;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_STATIC_IP)->MoveWindow(&rect);

	////
	GetDlgItem(IDC_LOCAL_IPADDR)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left = rect.right + 1;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + 146;
	GetDlgItem(IDC_LOCAL_IPADDR)->MoveWindow(&rect);

	////
	GetDlgItem(IDC_STATIC_PORT)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left = rect.right + 10;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_STATIC_PORT)->MoveWindow(&rect);


	////
	GetDlgItem(IDC_VIDEO_LOCAL_PORT)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left = rect.right + 5;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + 44;
	GetDlgItem(IDC_VIDEO_LOCAL_PORT)->MoveWindow(&rect);


	////
	GetDlgItem(IDC_CHECK_ACTIVEPT)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left = rect.right + 10;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_CHECK_ACTIVEPT)->MoveWindow(&rect);

	////
	GetDlgItem(IDC_EDIT_ACTIVEPT)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left = rect.right + 5;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + 55;
	GetDlgItem(IDC_EDIT_ACTIVEPT)->MoveWindow(&rect);

	////
	GetDlgItem(IDC_STATIC_REALPAYLOAD)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop;
	rect.left = rect.right + 10;

	rect.bottom = rect.top + wConstHeight;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_STATIC_REALPAYLOAD)->MoveWindow(&rect);


	////
	GetDlgItem(IDC_COMBO_DECTYPE)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop-3;
	rect.left = rect.right + 5;

	rect.bottom = rect.top + wConstHeightBtn;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_COMBO_DECTYPE)->MoveWindow(&rect);


	////
	GetDlgItem(IDC_START_DECODE_VID)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop-3;
	rect.left = rect.right + 10;

	rect.bottom = rect.top + wConstHeightBtn;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_START_DECODE_VID)->MoveWindow(&rect);


	////
	GetDlgItem(IDC_STOP_DECODE_VID)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop-3;
	rect.left = rect.right + 10;

	rect.bottom = rect.top + wConstHeightBtn;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_STOP_DECODE_VID)->MoveWindow(&rect);

	////
	GetDlgItem(IDC_STATUS)->GetClientRect(itemRect);
	wWidth = itemRect.Width();
	wHeight = itemRect.Height();

	rect.top = wTop-3;
	rect.left = rect.right + 10;

	rect.bottom = rect.top + wConstHeightBtn;
	rect.right = rect.left + wWidth;
	GetDlgItem(IDC_STATUS)->MoveWindow(&rect);


	/////
	GetClientRect(&itemRect);
	rect.top = rect.bottom+10;
	rect.left = itemRect.left;
	rect.right = itemRect.right;
	rect.bottom = itemRect.bottom;

	m_cPlayerWnd.MoveWindow(&rect);

	::SetFocus(m_cPlayerWnd.GetSafeHwnd()); 

}

void CkdvplayertesterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);

		if (nID == SC_MAXIMIZE)
		{
			SetPos();
		}
		else if (nID == SC_RESTORE)
		{
			SetPos();
		}
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CkdvplayertesterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CkdvplayertesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CkdvplayertesterDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
}



void CkdvplayertesterDlg::OnSetNetParam()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD /*dwLocalIpAddr,*/dwRemoteIpAddr;
	u16 dwRet = 0;
	// 	s8* pLocalIpAddress = NULL;
	s8* pRemoteIpAddress = NULL;
	// 	in_addr ipaddr;
	// 
	// 	m_cLocalIpAddr.GetAddress(dwLocalIpAddr);
	// 	dwLocalIpAddr = htonl(dwLocalIpAddr);
	// 	ipaddr.s_addr = dwLocalIpAddr;
	// 	pLocalIpAddress = inet_ntoa(ipaddr);
	// 
	// 	m_cRemoteIpAddr.GetAddress(dwRemoteIpAddr);
	// 	dwRemoteIpAddr = htonl(dwRemoteIpAddr);
	// 	ipaddr.s_addr = dwRemoteIpAddr;
	// 	pRemoteIpAddress = inet_ntoa(ipaddr);
	//pRemoteIpAddress = "172.16.35.100";
	m_cLocalIpAddr.GetAddress(dwRemoteIpAddr);
	//m_cRemoteIpAddr.GetAddress(dwRemoteIpAddr);
	//dwLocalIpAddr = htonl(dwLocalIpAddr);
	dwRemoteIpAddr = htonl(dwRemoteIpAddr);
	//in_addr ipLocaladdr = {0};
	in_addr ipRemoteaddr = {0};
	//ipLocaladdr.S_un.S_addr= dwLocalIpAddr;
	ipRemoteaddr.S_un.S_addr= dwRemoteIpAddr;
	m_pRemoteIpAddress = inet_ntoa(ipRemoteaddr);
	//m_pLocalIpAddress = inet_ntoa(ipLocaladdr);
	TMnetNetParam tLocalVidNetParam;
	memset(&tLocalVidNetParam, 0 , sizeof(tLocalVidNetParam));
	tLocalVidNetParam.m_byRemoteNum = 1;
	//s8* ipLocaladdr1 = new s8[256];
	//strcpy(ipLocaladdr1, (LPSTR)(LPCTSTR)m_cIp);

	;
	int flag = SetAdapterReceiveAllByIP(dwRemoteIpAddr);
	if (flag != 0)
	{
		CString strBuf;
		//sprintf(buf, "error:%n!", flag);
		strBuf.Format(_T("error:%d"), flag);
		AfxMessageBox(strBuf);
	}

	OSP_SET_NETADDR_PORT(&tLocalVidNetParam.m_tLocalNet.tRTPAddr, AF_INET, m_nVideoPort);
	OSP_SET_NETADDR_PORT(&tLocalVidNetParam.m_tLocalNet.tRTCPAddr, AF_INET, m_nVideoPort + 1);/*m_pLocalIpAddress*/
	OSP_SET_NETADDR_ADDR_STR(&(tLocalVidNetParam.m_tLocalNet.tRTPAddr), AF_INET, (LPSTR)(LPCTSTR)m_cIp);
	OSP_SET_NETADDR_ADDR_STR(&(tLocalVidNetParam.m_tLocalNet.tRTCPAddr), AF_INET, (LPSTR)(LPCTSTR)m_cIp);

	OSP_SET_NETADDR_PORT(&tLocalVidNetParam.m_tRemoteNet[0].tRTPAddr, AF_INET, m_nRomoteVidPort);
	OSP_SET_NETADDR_PORT(&tLocalVidNetParam.m_tRemoteNet[0].tRTCPAddr, AF_INET, m_nRomoteVidPort + 1);/*pRemoteIpAddress*/
	OSP_SET_NETADDR_ADDR_STR(&(tLocalVidNetParam.m_tRemoteNet[0].tRTPAddr), AF_INET, m_pRemoteIpAddress);
	OSP_SET_NETADDR_ADDR_STR(&(tLocalVidNetParam.m_tRemoteNet[0].tRTCPAddr), AF_INET, m_pRemoteIpAddress);

	dwRet = m_KdvDecoder.SetVideoNetRcvParam(&tLocalVidNetParam);

	if (CODEC_NO_ERROR != dwRet)
	{
		AfxMessageBox(_T("SetVideoNetRcvParam Error !"));
		OspPrintf(TRUE, FALSE, "SetVideoNetRcvParam Error:%d\n", dwRet);
	}

	TMnetNetParam tLocalAudNetParam ;
	memset(&tLocalAudNetParam, 0, sizeof(TMnetNetParam));

	tLocalAudNetParam.m_byRemoteNum = 1;
	OSP_SET_NETADDR_PORT(&tLocalAudNetParam.m_tLocalNet.tRTPAddr, AF_INET, m_nAudioPort);
	OSP_SET_NETADDR_PORT(&tLocalAudNetParam.m_tLocalNet.tRTCPAddr, AF_INET, m_nAudioPort + 1);
	OSP_SET_NETADDR_ADDR_STR(&(tLocalAudNetParam.m_tLocalNet.tRTPAddr), AF_INET, (LPSTR)(LPCTSTR)m_cIp);
	OSP_SET_NETADDR_ADDR_STR(&(tLocalAudNetParam.m_tLocalNet.tRTCPAddr), AF_INET, (LPSTR)(LPCTSTR)m_cIp);

	if (m_pRemoteIpAddress == NULL)
	{
		s8* chIpAdress = "127.0.0.0";
		OSP_SET_NETADDR_ADDR_STR(&(tLocalAudNetParam.m_tLocalNet.tRTPAddr), AF_INET, chIpAdress);
	}
	else
	{
		OSP_SET_NETADDR_ADDR_STR(&(tLocalAudNetParam.m_tRemoteNet[0].tRTPAddr), AF_INET, m_pRemoteIpAddress);
		OSP_SET_NETADDR_ADDR_STR(&(tLocalAudNetParam.m_tRemoteNet[0].tRTCPAddr), AF_INET, m_pRemoteIpAddress);
	}
	OSP_SET_NETADDR_PORT(&tLocalAudNetParam.m_tRemoteNet[0].tRTPAddr, AF_INET, m_nRomoteAudPort);
	OSP_SET_NETADDR_PORT(&tLocalAudNetParam.m_tRemoteNet[0].tRTCPAddr, AF_INET, m_nRomoteAudPort + 1);
	dwRet = m_KdvDecoder.SetAudioNetRcvParam(&tLocalAudNetParam);


	if (m_bActivePT)
	{
		m_KdvDecoder.SetVideoActivePT(m_nActivePT,
			m_comDecType.GetItemData(m_comDecType.GetCurSel()));
	}
	else
	{
		//	m_KdvDecoder.SetVideoActivePT(0,106);
	}

	GetDlgItem( IDC_START_NET_RCV )->EnableWindow( TRUE );
	GetDlgItem( IDC_STOP_NET_RCV )->EnableWindow( FALSE );
	GetDlgItem( IDC_SET_NET_PARAM )->EnableWindow( FALSE );
}


void CkdvplayertesterDlg::OnStartNetRcv()
{
	// TODO: Add your control notification handler code here
	u32 dwRet = 0;
	dwRet = m_KdvDecoder.StartRcvAudio();
	if(CODEC_NO_ERROR != dwRet)
	{
		AfxMessageBox(_T("StartRcvAudio error!"));
		OspPrintf(TRUE, FALSE, "StartRcvAudio error:%d\n", dwRet);
	}

	dwRet = m_KdvDecoder.StartRcvVideo();
	if (CODEC_NO_ERROR != dwRet)
	{
		AfxMessageBox(_T("StartRcvVideo Error !"));
		OspPrintf(TRUE, FALSE, "StartRcvVideo Error : %d\n",dwRet);
	}
	GetDlgItem(IDC_START_NET_RCV)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_NET_RCV)->EnableWindow(TRUE);
	GetDlgItem(IDC_SET_NET_PARAM)->EnableWindow(FALSE);
}


void CkdvplayertesterDlg::OnStopNetRcv()
{
	// TODO: Add your control notification handler code here
	m_KdvDecoder.StopRcvAudio();
	m_KdvDecoder.StopRcvVideo();
	GetDlgItem(IDC_START_NET_RCV)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_NET_RCV)->EnableWindow(FALSE);
	GetDlgItem(IDC_SET_NET_PARAM)->EnableWindow(TRUE);
}


void CkdvplayertesterDlg::OnStartVideoDecomp()
{
	// TODO: Add your control notification handler code here
	if (CODEC_NO_ERROR != m_KdvDecoder.StartVideoDec())
	{
		AfxMessageBox(_T("StartVideoDec Error !"));
	}

	GetDlgItem(IDC_START_VIDEO_DECOMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_VIDEO_DECOMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_DECOMP_CONFIG)->EnableWindow(FALSE);
}


void CkdvplayertesterDlg::OnStopVideoDecomp()
{
	// TODO: Add your control notification handler code here
	m_KdvDecoder.StopVideoDec();

	m_KdvDecoder.ClearWindow();  //之后加上
	GetDlgItem(IDC_START_VIDEO_DECOMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_VIDEO_DECOMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_DECOMP_CONFIG)->EnableWindow(TRUE);
}


void CkdvplayertesterDlg::OnFullscreen()
{
	// TODO: Add your control notification handler code here
}


void CkdvplayertesterDlg::OnCheckActivept()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bActivePT)
	{
		m_nActivePT = m_comDecType.GetItemData(m_comDecType.GetCurSel());
		m_KdvDecoder.SetVideoActivePT(m_nActivePT,
			m_comDecType.GetItemData(m_comDecType.GetCurSel()));
		//UINT A = m_comDecType.GetItemData(m_comDecType.GetCurSel());
		GetDlgItem(IDC_EDIT_ACTIVEPT)->EnableWindow(TRUE);
		m_comDecType.EnableWindow(TRUE);
	}
	else
	{
		m_KdvDecoder.SetVideoActivePT(0, 0);
		GetDlgItem(IDC_EDIT_ACTIVEPT)->EnableWindow(FALSE);
		m_comDecType.EnableWindow(FALSE);
	}

}


void CkdvplayertesterDlg::OnSelchangeComboDectype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nActivePT = m_comDecType.GetItemData(m_comDecType.GetCurSel());
	UpdateData(FALSE);
}


BOOL CkdvplayertesterDlg::DestroyWindow(void)
{
	OspQuit();
	return CDialogEx::DestroyWindow();
}


LRESULT CkdvplayertesterDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}

BOOL CkdvplayertesterDlg::PreTranslateMessage(MSG* pMsg)
{
	//屏蔽ESC关闭窗体/
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE ) 
		return TRUE;

	 if(pMsg->message == WM_NCLBUTTONDBLCLK) // 非client区域的双击消息
		 return TRUE; 

	return CDialog::PreTranslateMessage(pMsg);
}

void CkdvplayertesterDlg::OnKeyFrameCheck()
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_KEY_FRAME_CHECK) == BST_CHECKED)
	{
		m_KdvDecoder.SetOnlyKeyFrame(TRUE);
	} 
	else
	{
		m_KdvDecoder.SetOnlyKeyFrame(FALSE);
	}
}


void CkdvplayertesterDlg::OnClear()
{
	// TODO: Add your control notification handler code here
	m_KdvDecoder.ClearWindow();
}


void CkdvplayertesterDlg::OnReleasedcaptureVideoWindowSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	s32 nSliderPos = m_cscVideoWindow.GetPos();
	m_cPlayerWnd.MoveWindow(20, 20, 352 + nSliderPos, 288 + 288 * nSliderPos /352);
	*pResult = 0;
}


void CkdvplayertesterDlg::OnRedraw()
{
	// TODO: Add your control notification handler code here
	//m_KdvDecoder.RedrawLastFrame();
}


void CkdvplayertesterDlg::OnStatus()
{
	// TODO: Add your control notification handler code here
	CPlayStatus cPlayStatis;
	cPlayStatis.m_pDecoder = &m_KdvDecoder;
	cPlayStatis.DoModal();
}


void CkdvplayertesterDlg::OnSnap()
{
	// TODO: Add your control notification handler code here
	// 	CPicView cPicView;
	// 	cPicView.SetDecoderHandle(&m_KdvDecoder);
	// 	cPicView.DoModal();
}

void CkdvplayertesterDlg::OnReleasedcaptureAudioVolumeSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	u16 wSliderPos = this->m_cscAudioVolume.GetPos();
	this->m_KdvDecoder.SetAudioVolume((BYTE)wSliderPos);
	*pResult = 0;
}


void CkdvplayertesterDlg::OnStartAudioDecomp()
{
	// TODO: Add your control notification handler code here
	m_KdvDecoder.StartAudioDec();

	GetDlgItem( IDC_START_AUDIO_DECOMP )->EnableWindow( FALSE );
	GetDlgItem( IDC_STOP_AUDIO_DECOMP )->EnableWindow( TRUE );
}


void CkdvplayertesterDlg::OnStopAudioDecomp()
{
	// TODO: Add your control notification handler code here
	m_KdvDecoder.StopAudioDec();

	GetDlgItem( IDC_START_AUDIO_DECOMP )->EnableWindow( TRUE );
	GetDlgItem( IDC_STOP_AUDIO_DECOMP )->EnableWindow( FALSE );
}



void CkdvplayertesterDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	bool bInRect = FALSE;
	CRect rc;
	GetDlgItem(IDC_PLAYER)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	if (PtInRect(&rc,point))
	{
		bInRect = TRUE;
	}
	else
	{
		bInRect = FALSE;
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}


LRESULT   CkdvplayertesterDlg::OnStaticDButtonDown(WPARAM wParam, LPARAM  lParam)
{
	CPoint point; 
	GetCursorPos(&point); 
	CRect rect; 
	::GetClientRect(GetDlgItem(IDC_PLAYER)->GetSafeHwnd(), &rect); 

	//然后把当前鼠标坐标转为相对于rect的坐标。 
	::ScreenToClient(GetDlgItem(IDC_PLAYER)->GetSafeHwnd(), &point); 

	if(!rect.PtInRect(point)) 
	{ 
		return TRUE;
	} 


	m_bFullScreen = !m_bFullScreen;

	if (m_bFullScreen)
	{
		ShowFullScreen();
	}
	else
	{
		ShowNormal();
	}

	return TRUE;
}



void CkdvplayertesterDlg::ShowFullScreen()
{

	::GetWindowRect(m_hWnd, m_preRect);


	ModifyStyle(WS_CAPTION | DS_MODALFRAME,0,0);	
	ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, 0, 0);

	int cx,cy;
	cx = GetSystemMetrics(SM_CXSCREEN); 
	cy = GetSystemMetrics(SM_CYSCREEN); 

	CRect rcTemp;
	rcTemp.BottomRight() = CPoint(cx, cy); 
	rcTemp.TopLeft() = CPoint(0, 0); 

	MoveWindow(&rcTemp);
	m_cPlayerWnd.MoveWindow(&rcTemp);



	GetDlgItem(IDC_STATIC_IP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOCAL_IPADDR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_VIDEO_LOCAL_PORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_ACTIVEPT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ACTIVEPT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_REALPAYLOAD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_DECTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_START_DECODE_VID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STOP_DECODE_VID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATUS)->ShowWindow(SW_HIDE);


	UpdateWindow();
}

void CkdvplayertesterDlg::ShowNormal()
{

	ModifyStyle(0,WS_CAPTION,0);
	MoveWindow(&m_preRect);

	SetPos();


	GetDlgItem(IDC_STATIC_IP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LOCAL_IPADDR)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_VIDEO_LOCAL_PORT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHECK_ACTIVEPT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_ACTIVEPT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_REALPAYLOAD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_COMBO_DECTYPE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_START_DECODE_VID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STOP_DECODE_VID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATUS)->ShowWindow(SW_SHOW);

	UpdateWindow();
}



void CkdvplayertesterDlg::OnStartDecVid()
{	
	OnSetNetParam();
	OnStartNetRcv();
	OnStartVideoDecomp();

	GetDlgItem(IDC_START_DECODE_VID)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_DECODE_VID)->EnableWindow(TRUE);

	GetDlgItem(IDC_LOCAL_IPADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_VIDEO_LOCAL_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ACTIVEPT)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DECTYPE)->EnableWindow(FALSE);

	::SetFocus(m_cPlayerWnd.GetSafeHwnd()); 

	m_bStartDecode = TRUE;
}

void CkdvplayertesterDlg::OnStopDecVid()
{	
	OnStopVideoDecomp();
	OnStopNetRcv();

	GetDlgItem(IDC_START_DECODE_VID)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_DECODE_VID)->EnableWindow(FALSE);

	GetDlgItem(IDC_LOCAL_IPADDR)->EnableWindow(TRUE);
	GetDlgItem(IDC_VIDEO_LOCAL_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ACTIVEPT)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_DECTYPE)->EnableWindow(TRUE);

	::SetFocus(m_cPlayerWnd.GetSafeHwnd()); 

	m_bStartDecode = FALSE; 

	m_cPlayerWnd.OnRefresh(NULL);

}


void CkdvplayertesterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

//	SetPos();
}


void CkdvplayertesterDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case TIME_PACKET_CHECK_EVENT:
		{
			if (m_bStartDecode)
			{
				m_cPlayerWnd.OnRefresh(&m_KdvDecoder);
			}
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}