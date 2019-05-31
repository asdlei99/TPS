/** @defgroup 会议提示弹窗
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015.1.5
 */
#pragma once

class CCalendarLogic : public CNotifyUIImpl, public Singleton<CCalendarLogic>
{
	enum EMTCState {SELECTED, UNSELECTED, LASTMONTH, NEXTMONTH, EMPTY};

	/*MyDate definition*/
	typedef struct tagTCDate
	{
		int mcDay;
		int mcState;
		bool mcToday;

		tagTCDate()
		{
			clear();
		}
		void clear()
		{
			mcDay = 0;
			mcState = EMPTY;
			mcToday = false;
		}
	}TTCDate;


public:
	CCalendarLogic(void);
	~CCalendarLogic(void);
protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	/** 返回
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnLast(TNotifyUI& msg);
	/** 退出
	*  @param[in] 消息
	*  @return 
	*/
	bool OnBtnNext(TNotifyUI& msg);

	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
		/** 点击列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDateListItemClick(TNotifyUI& msg);
	

public:
	/** 设置位置
	*  @param[in] 左上角坐标
	*  @return 
	*/
	bool SetCalendarInfor(POINT pt, SYSTEMTIME sysTime);

	APP_DECLARE_MSG_MAP()
		
	void FillDates();
	int CalculateDayOfWeek(int day, int month, int year, BOOL bGregorian);
	bool IsLeapYear(int year, BOOL bGregorian);
	int GetNumberOfDays(int month, int year);
	void SetSelDate( int nYear, int nMonth, int nDay );
	void UpdateDates();
private:
	TTCDate m_Dates[42];
	int     m_Day;
	int     m_Month;
	int     m_Year;
	SYSTEMTIME m_LastTime;//调用时传入的时间
	CString m_strSelDate;
	 
};

