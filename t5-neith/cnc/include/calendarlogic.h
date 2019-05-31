/** @defgroup ������ʾ����
 *  @version V1.1.4
 *  @author  ��ӨӨ
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
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	/** ����
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnLast(TNotifyUI& msg);
	/** �˳�
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnBtnNext(TNotifyUI& msg);

	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
		/** ����б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDateListItemClick(TNotifyUI& msg);
	

public:
	/** ����λ��
	*  @param[in] ���Ͻ�����
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
	SYSTEMTIME m_LastTime;//����ʱ�����ʱ��
	CString m_strSelDate;
	 
};

