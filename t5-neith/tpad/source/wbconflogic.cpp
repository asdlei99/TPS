#include "StdAfx.h"
#include "wbconflogic.h"
#include "messageboxlogic.h"

APP_BEGIN_MSG_MAP(CWBConfLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("WBConfLayout"), OnCreate)
 	MSG_INIWINDOW(_T("WBConfLayout"), OnInit)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_CONFSTATE_NTY,OnConfStateNty)
	USER_MSG(UI_JOINWBCONF_CMD,OnJoinWBConfNty)
	USER_MSG(UI_LEAVEWBCONF_NTY,OnLeaveWBConfNty)
	USER_MSG(UI_NEWWBCONFCALL_REQ,OnNewConfCallReq)
	USER_MSG(UI_CONFROOMNAME_NTY,OnConfRoomNameNty)
	USER_MSG(UI_SELFSTARTWBCONFNTY,OnWBConfStartNty)
	USER_MSG(UI_TPPSETDATASERVERINFONTY,OnCnsSetDataServerInfoNty)
	USER_MSG(UI_SELFSTARTCONF_CMD,OnSelfMakeCallCmdNty)
	USER_MSG(UI_SETWBSERVERIP_NTY,OnSetWBServerIpNty)
	USER_MSG(UI_TPPSETDATACONFNAMENTY,OnCnsSetDataCnfNameNty)

APP_END_MSG_MAP()


CWBConfLogic::CWBConfLogic(void)
{
	m_bInDataConf = FALSE;
	m_bIsSelfStartDataConf= FALSE;
	m_bIsSelfStartCncConf = FALSE;
	m_bCreateDataConfDlg = FALSE;
	m_strConfRoomName = _T("");
	m_strConfName = _T("");
	m_dwWBIp = 0;
	m_strLastConfName = _T("");
	m_strUserName = _T("");
	m_bIsLoginWBServer = false;
}


CWBConfLogic::~CWBConfLogic(void)
{
}


bool CWBConfLogic::OnCreate(TNotifyUI& msg)
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

	if ( !StartJVM() )
	{
		return false;
	}
	return true;
}

bool CWBConfLogic::OnInit(TNotifyUI& msg)
{
	return true;
}

bool CWBConfLogic::StartJVM()
{
	char achPath[120] = {0};
	::GetCurrentDirectoryA(120, achPath);
	char path[130] = {0};
	sprintf(path, "%%path%%;%s\\jre7\\bin\\client", achPath);
	SetEnvironmentVariableA("path", path);

	int status;

	JavaVMOption options[3];
	JavaVMInitArgs vm_args;

	//各种参数
	options[0].optionString="-Djava.class.path=./DocumentConvert.jar";

	options[1].optionString = "-Xmx256M";
	options[2].optionString = "-verbose:NONE"; 

	vm_args.version=JNI_VERSION_1_2;
	vm_args.options=options;
	vm_args.nOptions=1;

	/////////////////////////////////////////////////////////////////////////////
	//该参数指定是否忽略非标准的参数，如果填JNI_FLASE，当遇到非标准参数时，JNI_CreateJavaVM会返回JNI_ERR  
	vm_args.ignoreUnrecognized = JNI_TRUE;  

	//加载JVM.DLL动态库  
	HINSTANCE hInstance = ::LoadLibrary(_T(".\\jre7\\bin\\client\\jvm.dll"));

	if (hInstance == NULL)  
	{  
		PrtMsg( "LoadLibrary jvm.dll failed \n" );
		return false;  
	}  

	typedef jint (WINAPI *PFunCreateJavaVM)(JavaVM **, void **, void *);  

	//取得里面的JNI_CreateJavaVM函数指针  
	PFunCreateJavaVM funCreateJavaVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");  
	//调用JNI_CreateJavaVM创建虚拟机  
	status = (*funCreateJavaVM)(&m_jni_jvm, (void**)&m_jni_env, &vm_args);  

	FreeLibrary(hInstance);

	//如果创建虚拟机失败
	if(status != JNI_OK)
	{
		printf("Can not create JavaVM!\n");
		PrtMsg( "CreateJavaVM failed status:%d\n", status );
		return false;
	}

	//传入jvm dyy 2014-8-28 
	WB_API_setJVM( m_jni_jvm );

	return true;
}

bool CWBConfLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	WB_API_quitConference();
	WB_API_logOffServer();
	WB_API_showDataConfWindow(false);

	if ( m_bInDataConf )
	{
		m_bInDataConf = FALSE;
		ComInterface->WBConfStateNty(m_bInDataConf);
	}

	m_bIsSelfStartDataConf = FALSE;
	m_bIsSelfStartCncConf = FALSE;
	m_strConfRoomName = _T("");
	m_strConfName = _T("");
	m_dwWBIp = 0;
	m_strLastConfName = _T("");
	m_strUserName = _T("");
	m_bIsLoginWBServer = false;
	return true;
}

bool CWBConfLogic::OnConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPCnsConfStatus tconfState = ComInterface->GetLocalCnsConfState();

	if ( !m_bCreateDataConfDlg )
	{
		CreatWBConfDlg();
	}

	//视频会议结束 修改本地开启视频会议的状态
	if ( tconfState.emState == em_CALL_IDLE )
	{
		//结束会议 数据会议名改为本地会场名 dyy 2014-9-4
		if (m_strConfName != m_strConfRoomName)
		{
			m_strConfName = m_strConfRoomName;
			UpdateWBConfName(m_strConfName);      
		}

		if ( m_bIsSelfStartCncConf )
		{
			m_bIsSelfStartCncConf = FALSE;
		}
	}
	//加入网呈会议，如果已经在会议中，结束白板会议
	if ( tconfState.emState == em_CALL_CONNECTED )
	{
		//点对点数据会议名由消息ev_tpp_DataConfName_Nty给出 只处理多点会议 2014-9-12 
		if ( tconfState.m_emCallType == emCallType_Conf )
		{
			CString strConfName = _T("");
			strConfName.Format(_T("%s"), (CA2T)tconfState.achConfName);
			if ( strConfName != m_strConfName )
			{
				m_strConfName = strConfName;
				UpdateWBConfName(m_strConfName);
			}
		}
	}
	return NO_ERROR;
}

//收到数据会议创建通知，链接到此ip，加入数据会议 ev_tpp_JoinWBConf_Cmd
bool CWBConfLogic::OnJoinWBConfNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if (m_bIsSelfStartDataConf)
	{
		return NO_ERROR;
	}

	if ( !m_bCreateDataConfDlg )
	{
		CreatWBConfDlg();
	}

	TTPDataConfInfo tTPDataConfInfo;
	ComInterface->GetDataConfInfo(tTPDataConfInfo);
	TTPCnsConfStatus tTPCnsConfStatus;
	ComInterface->GetWBCnsConfStatus(tTPCnsConfStatus);

	if ( m_dwWBIp != tTPDataConfInfo.dwSerIP)
	{
		m_dwWBIp = tTPDataConfInfo.dwSerIP;
	}

	CString strConfName;
	strConfName  = tTPCnsConfStatus.achConfName;

	CString strServerIp;     
	//    strServerIp = iptos(m_dwWBIp);

	in_addr tAddr;
	tAddr.S_un.S_addr = m_dwWBIp;
	strServerIp = inet_ntoa(tAddr);   

	if ( !m_bIsLoginWBServer && m_dwWBIp != 0)
	{
		m_bIsLoginWBServer = WB_API_logInServer( strServerIp, 5000);
		if (!m_bIsLoginWBServer)
		{
			OspPrintf(TRUE,FALSE,"[FAILED]WB_API_logInServer");
		}

	}

	//此处的会议名是已经开启的白板会议会议名 如果会议名不同，更新会议名并加入
	if ( strConfName != m_strConfName )
	{
		m_strConfName = strConfName;
		UpdateWBConfName(m_strConfName);       
	}

	//加入白板会议 没有此名的会议 则不处理
	Sleep(20);

	WB_API_joinConference(strConfName, m_strUserName);

	//等待加入成功后再后续处理 dyy 2014-6-5 函数OnWBConfStartNty处理

	//加入白板会议直接显示白板页
	//     m_bInDataConf = TRUE;//测试用
	//     if ( m_bInDataConf )
	//     {       
	//         WB_API_showDataConfWindow(TRUE);
	//     }
	// 
	//     ComInterface->WBConfStateNty(m_bInDataConf);
	return NO_ERROR;
}

//结束网呈会议，CNS通知连接在其服务器的所有Tpad离开白板会议 
bool CWBConfLogic::OnLeaveWBConfNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTPDataConfInfo tTPDataConfInfo;
	ComInterface->GetDataConfInfo(tTPDataConfInfo);

	u32 dwIp = tTPDataConfInfo.dwSerIP;
	//退出会议
	if ( m_bInDataConf )
	{
		WB_API_quitConference();
		m_bIsSelfStartDataConf = FALSE;
		m_bInDataConf = FALSE;
		ComInterface->WBConfStateNty(m_bInDataConf);
	}

	//更新会议名为本地会场名
	if (m_strConfName != m_strConfRoomName)
	{
		m_strConfName = m_strConfRoomName;
		UpdateWBConfName(m_strConfName);      
	}
	return NO_ERROR;
}

//新会议呼进来请求Tpad是否加入 
bool CWBConfLogic::OnNewConfCallReq(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if ( !m_bInDataConf )//不在数据会议中，不处理
	{
		return NO_ERROR; 
	}

	if ( m_bIsSelfStartCncConf )
	{
		return NO_ERROR;
	}

	//2014-10-20 dyy 改为在白板中弹窗提示
	//     Args_MsgBox msgBoxArgs;
	//     msgBoxArgs.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );  
	//     MSG_BOX_PROMPT( _T("当前数据会议结束，加入到新会议"), &msgBoxArgs ); 

	//当在白板版界面 提示
	LPCSTR className = NULL;
	LPCSTR windName = "whiteboard";   
	HWND hWnd = ::FindWindow( CA2T(className) ,CA2T (windName) );
	if ( IsWindow( hWnd ) )
	{
		if ( ::IsWindowVisible( hWnd ) )
		{            
			CString strTips( _T("当前数据会议结束，加入到新会议")); 

			WB_API_showMessage( strTips );

		}         
	}

	//     if (m_bInDataConf)
	//     {
	//         MSG_BOX( "开启新的会议后将自动结束当前的数据会议，是否继续？", CWBConfLogic::JoinWDConf, CWBConfLogic::QuitJoinWDConf, m_pLogic, CWBConfLogic, &msgBoxArgs, TRUE );  
	//     }
	//     else
	//     {
	//         MSG_BOX( "有其他会议呼叫，是否结束当前数据会议加入到新的会议中？", CWBConfLogic::JoinWDConf, CWBConfLogic::QuitJoinWDConf, m_pLogic, CWBConfLogic, &msgBoxArgs, TRUE );  
	//     }

	//退出会议 

	WB_API_quitConference();
	m_bIsSelfStartDataConf = FALSE;
	m_bInDataConf = FALSE;
	ComInterface->WBConfStateNty(m_bInDataConf);
	return NO_ERROR;
}

//获取会场名称
bool CWBConfLogic::OnConfRoomNameNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTPCnsInfo tTPCnsInfo;
	ComInterface->GetWBCnsInfo(tTPCnsInfo);

	m_strConfRoomName = tTPCnsInfo.m_achRoomName;

	if ( !m_bCreateDataConfDlg )
	{
		CreatWBConfDlg();
	}

	if (m_strConfName != m_strConfRoomName)
	{
		m_strConfName = m_strConfRoomName;
		UpdateWBConfName(m_strConfName);      
	}

	return S_OK;
}

bool CWBConfLogic::OnWBConfStartNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_bIsSelfStartDataConf = (BOOL)lParam;   
	BOOL bIsInDataConf = (BOOL)wParam;

	if ( m_bInDataConf != bIsInDataConf )
	{
		m_bInDataConf = bIsInDataConf;
		ComInterface->WBConfStateNty(m_bInDataConf);
	}

	if ( m_bInDataConf )
	{
		//正在显示双流 隐藏双流窗口
		if ( ComInterface->IsReceiveDual() )
		{
			//CVideoLogic::GetLogicPtr()->BtnHideVedio( args );
		}
		//加入会议后 直接显示白板界面
		WB_API_showDataConfWindow(TRUE);  
	}
	return NO_ERROR;
}

bool CWBConfLogic::OnCnsSetDataServerInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if ( !m_bCreateDataConfDlg )
	{
		CreatWBConfDlg();
	}

	TTPDataConfInfo tTPDataConfInfo;
	ComInterface->GetDataConfInfo(tTPDataConfInfo);

	m_dwWBIp = tTPDataConfInfo.dwSerIP; 

	CString strServerIp; 

	strServerIp = iptos(m_dwWBIp);

	WB_API_setServerIp( strServerIp );

	return NO_ERROR;
}

bool CWBConfLogic::OnSelfMakeCallCmdNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_bIsSelfStartCncConf = TRUE;
	return NO_ERROR;
}

bool CWBConfLogic::OnSetWBServerIpNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	BOOL bIsSuccess = (BOOL)wParam;

	if ( !bIsSuccess )
	{
		return S_FALSE;
	}

	TTPDataConfInfo tTPDataConfInfo;
	ComInterface->GetDataConfInfo(tTPDataConfInfo);
	u32 dwIp = tTPDataConfInfo.dwSerIP;
	if ( m_dwWBIp == dwIp )
	{
		return NO_ERROR;
	}

	//设置完ip后直接连接 
	if ( m_bInDataConf )
	{
		m_bInDataConf = FALSE;
		WB_API_quitConference();
		ComInterface->WBConfStateNty(m_bInDataConf);
	}

	WB_API_logOffServer();

	m_dwWBIp = dwIp;

	CString strServerIp; 

	strServerIp = iptos(m_dwWBIp);

	WB_API_setServerIp( strServerIp );

	if ( m_dwWBIp != 0 )
	{
		m_bIsLoginWBServer = WB_API_logInServer( strServerIp, 5000);
		if (!m_bIsLoginWBServer)
		{
			OspPrintf(TRUE,FALSE,("[FAILED]WB_API_logInServer"));
		}
	}

	return NO_ERROR;
}

bool CWBConfLogic::OnCnsSetDataCnfNameNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if ( !m_bCreateDataConfDlg )
	{
		CreatWBConfDlg();
	}

	TTPCnsConfStatus tTPCnsConfStatus;
	ComInterface->GetWBCnsConfStatus(tTPCnsConfStatus);

	m_strConfName = tTPCnsConfStatus.achConfName;
	UpdateWBConfName(m_strConfName);
	return NO_ERROR;
}

//更新数据会议会议名
void CWBConfLogic::UpdateWBConfName( CString strConfName )
{  
	if (CStringA(strConfName).GetLength() > TP_MAX_ALIAS_LEN_CNC-1 )
	{
		return;
	}

	if ( m_strLastConfName != strConfName )
	{
		m_strLastConfName = strConfName;
		WB_API_setConfName(strConfName);

	} 
}

//创建数据会议Dlg，并传入用户名
void CWBConfLogic::CreatWBConfDlg()
{
	if ( !m_bCreateDataConfDlg )//不重复创建
	{
		if ( WB_API_dataConfCreate() )
		{           
			TLoginInfo tLoginInfo = ComInterface->GetLoginInfo();

			//m_strUserName.Format(_T("%s"),tLoginInfo.achName);
			m_strUserName = tLoginInfo.achName;

			//用户名为当前Tpad登陆用户名
			WB_API_setUserName(m_strUserName);

			m_bCreateDataConfDlg = TRUE;

		}
	}
}

void CWBConfLogic::SetDataServerInfoCmd( u32 dwIp )
{
	if ( !m_bCreateDataConfDlg )
	{
		CreatWBConfDlg();
	}

	//通知cns修改数据会议配置ip
	ComInterface->SetDataServerInfoCmd( dwIp );
}

CString CWBConfLogic::iptos( u32 dwIPAddr ) 
{ 
	//     static   char   output[3*4+3+1];//输出3点4段的字符串 
	//     u_char   *p; 
	//     
	//     p   =   (u_char   *)&dwIPAddr; //   指向长整数IP地址的字符型指针 
	//     sprintf(output,   "%d.%d.%d.%d ",   p[0],   p[1],   p[2],   p[3]); 

	//转为主机序
	dwIPAddr = ntohl(dwIPAddr);

	unsigned short wHigh  = HIWORD( dwIPAddr );
	unsigned short wLow   = LOWORD( dwIPAddr );
	CString strIP;
	strIP.Format( _T("%d.%d.%d.%d"), HIBYTE( wHigh ), LOBYTE( wHigh ),
		HIBYTE( wLow ), LOBYTE( wLow ) );

	return strIP; 
}