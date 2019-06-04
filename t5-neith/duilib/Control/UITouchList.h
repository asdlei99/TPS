#ifndef __UITOUCHLIST_H__
#define __UITOUCHLIST_H__

#pragma once
#include "Core\UIBase.h"
#include "Layout/UITileLayout.h"
#include "Control/UIList.h"

namespace DuiLib
{

class UILIB_API CTouchListUI : public CTileLayoutUI, public IListOwnerUI
{
public:
	CTouchListUI();
	~CTouchListUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	bool GetScrollSelect();
	void SetScrollSelect(bool bScrollSelect);
	int GetCurSel() const;
	bool SelectItem(int iIndex, bool bTakeFocus = false);

	TListInfoUI* GetListInfo();

	//CControlUI* GetItemAt(int iIndex) const;
	//int GetItemIndex(CControlUI* pControl) const;
	bool SetItemIndex(CControlUI* pControl, int iIndex);
	int GetCount() const;
	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();

	void EnsureVisible(int iIndex);
	void Scroll(int dx, int dy);
    virtual void SetScrollPos(SIZE szPos);

	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	LPCTSTR GetSelectedItemImage() const;
	void SetSelectedItemImage(LPCTSTR pStrImage); 
	LPCTSTR GetItemBkImage() const;
	void SetItemBkImage(LPCTSTR pStrImage);
	LPCTSTR GetHotItemImage() const;
	void SetHotItemImage(LPCTSTR pStrImage);
	LPCTSTR GetDisabledItemImage() const;
	void SetDisabledItemImage(LPCTSTR pStrImage);
	DWORD GetDisabledItemTextColor() const;
	void SetDisabledItemTextColor(DWORD dwTextColor);
	DWORD GetItemTextColor() const;
	void SetItemTextColor(DWORD dwTextColor);
	DWORD GetSelectedItemTextColor() const;
	void SetSelectedItemTextColor(DWORD dwTextColor);

    CDuiString GetListHeadNameH() const;
    void SetListHeadNameH(CDuiString sListHeadNameH);
    CDuiString GetListHeadNameV() const;
    void SetListHeadNameV(CDuiString sListHeadNameV);

	//letter����ʱ�б���������λ�� dyy 2015-5-26
	void ScrollToIndexLetter(int nItemIndex);

	void SetIsAutoLayout( LPCTSTR pIsAutoLayout );
	bool IsAutoLayout() const;
    void SetListDrag( LPCTSTR pIsListDrag );
    bool IsListDrag() const;
protected:
	bool m_bScrollSelect;
	int m_iCurSel;
	int m_iExpandedItem;
	
	bool            m_bLButtonDown;
	POINT           m_ptLButtonDown;      //��갴��λ��

	bool m_bAutoLayout;
	TListInfoUI m_ListInfo;
    bool m_bListDrag;
    CDuiString m_sListHeadNameH;//�����ͷ
    CDuiString m_sListHeadNameV;//�����ͷ
};

} // namespace DuiLib

#endif // __UITOUCHLIST_H__

