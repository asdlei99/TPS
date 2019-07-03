/*=======================================================================
ģ����      : TPad lib�ӿ�
�ļ���      : tpadsessionif.h
����ļ�    : 
�ļ�ʵ�ֹ���: tpadlib���ƽӿ�
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2013.3.6    1.0         Ф��Ȼ        ����
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
    /*��    ��  ��ʼ��lib�⻷��
	��    ��  dwAppID�� ��Ҫ��appID
	�� �� ֵ   
	˵    ��   ʹ�������ӿ�֮ǰ������øýӿ�*/ 
	virtual void InitEnv( u32 dwAppID ) = 0;
	
	/** ����  ���ӵ�CNS 
	 *  @param[in] dwIP	������CNS��IP��ַ
	 *  @param[in] dwPort  ������CNS�Ķ˿�
	 *  @param[in] strUser	�û���
	 *  @param[in] strPwd	����
     *  @param[in] achVersion TPad�汾��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 ConnectCns(u32 dwIP, u32 dwPort,
		LPSTR strUser,LPSTR strPwd,
        s8* achVersion, BOOL32 bConnect = TRUE) = 0;
    //���� ����IPV6��¼
    virtual u16 ConnectCns(TOspNetAddr tRmtAddr,
        LPSTR strUser,LPSTR strPwd,
        s8* achVersion, BOOL32 bConnect = TRUE) = 0;

	/** ����  �Ͽ�CNS���� 
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks ��û�����ӵ�CNSʱ���ô˷����������κ�����
	 */
	virtual u16 DisconnectCns() = 0;

	/** ����  ��ѯ�Ƿ�������CNS 
	 *  @return  TRUE �����ӣ�FALSE	û����
	 *  @remarks 
	 */
	virtual BOOL IsConnectedCns() = 0;

	 /** ����  ��ȡ����ip
	 *  @param[in] 
	 *  @return  ����ip 
	 *  @remarks 
	 */
    virtual u32 GetLocalHostIP() = 0;
	/** ����  ��ȡ�����汾��Ϣ
	 *  @param[in] 
	 *  @return  �����汾��Ϣ
	 *  @remarks 
	 */
	virtual TTPTPadVerInfo GetTPadVerInfo() = 0;
	/** 
	* ����  	��ȡftp��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPFtpInfo GetCnFtpInfo()=0;
    /** 
	* ����  	����ftp��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo)=0;


    /** ����  �ж��Ƿ�ɽ�������(cnc���пؾ�������Tpad)
	 *  @return  TRUE �����ӣ�FALSE	û����
	 *  @remarks 
	 */
    virtual BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList ) = 0;

	
    /** ����  ��ȡ��½ip
	 *  @param[in] 
	 *  @return  ��½ip
	 *  @remarks 
	 */
	virtual u32 GetLoginIp() = 0;

    virtual void TPadHomeKeyNty() = 0;

	virtual void OpenCenterCtrl() = 0;

    virtual void OpenSysConfig() = 0;

    virtual void OpenCnsManage() = 0;

	virtual void T300UpdateInd( BOOL bIsUpT300 ) = 0;

	/**
    * ����:	֪ͨcnc����
	* @param [in]  bActiveExit �Ƿ������˳�
	* @remarks
	*/
	virtual void NotifyCnsDisconnect( BOOL bActiveExit ) = 0;

	//��ȡ�ӿ� 
	virtual u16 TpadGetInterface(CTpadConfCtrlIF **ppCtrl) = 0;

	/** ����  ��ȡ��¼���ؽ��
	 *  @param[in] 
	 *  @return  
	 *  @remarks 
	 */
    virtual TLoginRet GetLoginRet() = 0;
};

#endif