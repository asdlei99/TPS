/*=======================================================================
模块名      : TPad lib接口
文件名      : tpadsessionif.h
相关文件    : 
文件实现功能: tpadlib控制接口
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013.3.6    1.0         肖楚然        创建
=======================================================================*/
#if !defined _TPADSESSIONIF_H_
#define _TPADSESSIONIF_H_

#include "kdvdispevent.h"
#include "tpadplatstuct.h"
#include "tpcommonstruct.h"
#include "tpadconfctrlif.h"


class CTPadSessionIF : public CKdvDispEvent 
{
public:	
    /*功    能  初始化lib库环境
	参    数  dwAppID： 需要的appID
	返 回 值   
	说    明   使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u32 dwAppID ) = 0;
	
	/** 功能  连接到CNS 
	 *  @param[in] dwIP	被连接CNS的IP地址
	 *  @param[in] dwPort  被连接CNS的端口
	 *  @param[in] strUser	用户名
	 *  @param[in] strPwd	密码
     *  @param[in] achVersion TPad版本号
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 ConnectCns(u32 dwIP, u32 dwPort,
		LPSTR strUser,LPSTR strPwd,
        s8* achVersion, BOOL32 bConnect = TRUE) = 0;
    //重载 用于IPV6登录
    virtual u16 ConnectCns(TOspNetAddr tRmtAddr,
        LPSTR strUser,LPSTR strPwd,
        s8* achVersion, BOOL32 bConnect = TRUE) = 0;

	/** 功能  断开CNS连接 
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 在没有连接到CNS时调用此方法，不起任何作用
	 */
	virtual u16 DisconnectCns() = 0;

	/** 功能  查询是否已连接CNS 
	 *  @return  TRUE 已连接，FALSE	没连接
	 *  @remarks 
	 */
	virtual BOOL IsConnectedCns() = 0;

	 /** 功能  获取本地ip
	 *  @param[in] 
	 *  @return  本地ip 
	 *  @remarks 
	 */
    virtual u32 GetLocalHostIP() = 0;
	/** 功能  获取升级版本信息
	 *  @param[in] 
	 *  @return  升级版本信息
	 *  @remarks 
	 */
	virtual TTPTPadVerInfo GetTPadVerInfo() = 0;
	/** 
	* 功能  	获取ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPFtpInfo GetCnFtpInfo()=0;
    /** 
	* 功能  	设置ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo)=0;


    /** 功能  判断是否可进行链接(cnc、中控均以连上Tpad)
	 *  @return  TRUE 已连接，FALSE	没连接
	 *  @remarks 
	 */
    virtual BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList ) = 0;

	
    /** 功能  获取登陆ip
	 *  @param[in] 
	 *  @return  登陆ip
	 *  @remarks 
	 */
	virtual u32 GetLoginIp() = 0;

    virtual void TPadHomeKeyNty() = 0;

	virtual void OpenCenterCtrl() = 0;

    virtual void OpenSysConfig() = 0;

    virtual void OpenCnsManage() = 0;

	virtual void T300UpdateInd( BOOL bIsUpT300 ) = 0;

	/**
    * 功能:	通知cnc断链
	* @param [in]  bActiveExit 是否主动退出
	* @remarks
	*/
	virtual void NotifyCnsDisconnect( BOOL bActiveExit ) = 0;

	//获取接口 
	virtual u16 TpadGetInterface(CTpadConfCtrlIF **ppCtrl) = 0;

	/** 功能  获取登录返回结果
	 *  @param[in] 
	 *  @return  
	 *  @remarks 
	 */
    virtual TLoginRet GetLoginRet() = 0;
};

#endif