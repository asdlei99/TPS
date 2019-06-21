/** @defgroup 矩阵控制逻辑单元
 *  @version 
 *  @author   wk
 *  @date     2017.5.19
 */

#pragma once

#define NUM_MATRIX_WIDTH    160
#define NUM_MATRIX_HEIGHT   110

enum EmTouchListType
{
    emTouchListHTip = 0,//横向表头
    emTouchListVTip,//纵向表头 
    emTouchListInfo,//内容
};

enum EmTouchList
{
    emOperation = 0,//操作
    emManager,//管理 
};


class CMatrixLogic : public CNotifyUIImpl, public Singleton<CMatrixLogic> 
{
public:
	CMatrixLogic();
	~CMatrixLogic();

    //更新当前矩阵状态
	void UpdateMatrixTip(const TTPCurMatrixInfo& tTPCurMatrixInfo, EmTouchList emTouchList);//更新矩阵表头（输入输出通道）
    void UpdateMatrixInfo(const TTPCurMatrixInfo& tTPCurMatrixInfo, EmTouchList emTouchList);//更新矩阵内容（对应勾选状态）

    //获取更新的列表名称
    CDuiString GetTouchListName(EmTouchList emTouchList, EmTouchListType emTouchListType);
protected:

    /** 初始化消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);
	
	/*--------矩阵界面--------*/
	/** 打开编辑预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnEditPreplan(TNotifyUI& msg);
	/** 保存预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnSavePreplan(TNotifyUI& msg);
	/** 应用预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnApplyPreplan(TNotifyUI& msg);
    // 切换输出对应输入
	bool OnOptIsUseFulSelChange(TNotifyUI& msg);


	/*--------编辑界面--------*/
    //预案管理切换
    bool OnSelPreplanSelectChange(TNotifyUI& msg);
	/** 保存编辑预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUIReName(TNotifyUI& msg);
	/** 应用编辑预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUIApply(TNotifyUI& msg);
	/** 删除编辑预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUIDelete(TNotifyUI& msg);
	/** 取消编辑预案
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnUICancel(TNotifyUI& msg);

	/*--------保存界面--------*/
    //保存切换
    bool OnPreplanSaveChange(TNotifyUI& msg);
	/** 取消
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnSaveUICancel(TNotifyUI& msg);
	/** 保存
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnSaveUISave(TNotifyUI& msg);

    /*--------重命名界面--------*/
    //重命名切换
    bool OnPreplanReNameChange(TNotifyUI& msg);
	/** 取消
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnReNameUICancel(TNotifyUI& msg);
	/** 保存
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnBtnReNameUISave(TNotifyUI& msg);

    //断链
    bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //矩阵配置更新
    bool OnMatrixConFigNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //矩阵预案信息通知
    bool OnMatrixSceneInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //当前操作矩阵信息通知
    bool OnCurMatrixInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //保存矩阵预案反馈
    bool OnSaveMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //重命名矩阵预案反馈
    bool OnReNameMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //删除矩阵预案反馈
    bool OnDeleteMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //应用矩阵预案反馈
    bool OnApplyMatrixSceneInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()
private:
	CTouchListUI     *m_pInputList;
	CTouchListUI     *m_pOutputList;
};