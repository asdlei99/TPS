#pragma once


/*
	��Ϣ�����ӿ�
*/
class ICncMsgManager : public Singleton<ICncMsgManager>
{
public:
	ICncMsgManager(){}
	virtual ~ICncMsgManager(){}
/** �㲥��Ϣ 
 *  @param[in] tMsgParam ��Ϣ�ṹ�� 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	virtual void SendMsg(TMsgParam& tMsgParam) = 0;
/** �㲥��Ϣ �첽
 *  @param[in] tMsgParam ��Ϣ�ṹ�� 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	virtual void PostMsg(TMsgParam& tMsgParam) = 0;
/** ����/ɾ���۲��� 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	virtual void AddObserver(IObserver_MsgPrama* pOb) = 0;
	virtual void RemoveObserver(IObserver_MsgPrama* pOb) = 0;
	virtual void AddWindowObserver(HWND hwnd) = 0;
	virtual void RemoveWindowObserver(HWND hwnd) = 0;
};

template<> ICncMsgManager* Singleton<ICncMsgManager>::ms_pSingleton  = 0;



class CCncMsgManager : public ICncMsgManager
{
public:
	CCncMsgManager(void);
	~CCncMsgManager(void);

	virtual void SendMsg(TMsgParam& tMsgParam);
	virtual void PostMsg(TMsgParam& tMsgParam);
	virtual void AddObserver(IObserver_MsgPrama* pOb);
	virtual void RemoveObserver(IObserver_MsgPrama* pOb);
	virtual void AddWindowObserver(HWND hwnd);
	virtual void RemoveWindowObserver(HWND hwnd);
protected:
	typedef map<HWND, IObserver_MsgPrama*> WndObMap;

	WndObMap m_mapWndObs;
	CMsgManager m_cMsgManager;
};
