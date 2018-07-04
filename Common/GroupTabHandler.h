#pragma once
#include "stdafx.h"
class CTabCtrl;
namespace Util
{
	typedef int GroupID;

	template<class ClientClass, class DialogBase> class	GroupTabHandler
	{
	protected:
		enum {
			INVALID_GROUPID = -1,
			FIRST_TAB_ITEM = 0
		};

		struct TAB_ITEM_TEMPLATE
		{
			DialogBase *Dialog;
			DWORD dwIDC;
			CString lpszTitle;
		};

		typedef TAB_ITEM_TEMPLATE TAB_ITEM;

		std::vector<DialogBase*> m_DialogTab;
		std::map<GroupID, std::vector<TAB_ITEM>> m_MapModeToControl;
		CTabCtrl *pCTabCtrl;
		GroupID GroupIDActive;

		GroupTabHandler(CTabCtrl *pCTabCtrl = NULL, int TotalTabItem = 0) :
			pCTabCtrl(pCTabCtrl), m_DialogTab(TotalTabItem), GroupIDActive(INVALID_GROUPID)
		{}

	public:
		/*Insert item Tab control*/
		void InitItemTabControl(TAB_ITEM &TabItem, int tabID)
		{
			TCITEM tcItem;
			tcItem.mask = TCIF_TEXT | TCIF_PARAM;
			tcItem.pszText = TabItem.lpszTitle.GetBuffer();
			tcItem.lParam = (LPARAM)&(*TabItem.Dialog);
			pCTabCtrl->InsertItem(tabID, &tcItem);

			CRect rcItem, rcDisplayArea;
			pCTabCtrl->GetItemRect(0, &rcItem);
			pCTabCtrl->GetClientRect(&rcDisplayArea);
			TabItem.Dialog->SetWindowPos(pCTabCtrl, rcItem.left, rcItem.bottom, rcDisplayArea.Width() - 5, rcDisplayArea.Height() - rcItem.Height() - 5, SWP_NOZORDER);
		}

		/*Init all tab items*/
		void InitDialogTab()
		{
			for (auto &TabGroup : m_MapModeToControl)
			{
				for (auto &DialogTabItem : TabGroup.second)
					DialogTabItem.Dialog->Create(DialogTabItem.dwIDC, pCTabCtrl);
			}
		}

		/*Switch Group Tab*/
		void SwitchGroupTab(GroupID GroupID)
		{

			/*Hide current dialog tab items*/
			GroupIDActive != INVALID_GROUPID? GetDialogFromCurrentTab()->ShowWindow(SW_HIDE): FALSE;

			/*Set GroupID*/
			GroupIDActive = GroupID;

			/*Clear all tab item*/
			pCTabCtrl->DeleteAllItems();
			/*Init tab item*/
			DWORD tabID = FIRST_TAB_ITEM;
			for (auto &TabItem : m_MapModeToControl[GroupID])
			{
				InitItemTabControl(TabItem, tabID++);
			}
			/*Show 1st tab item*/
			pCTabCtrl->SetCurSel(FIRST_TAB_ITEM);
			m_MapModeToControl[GroupID][FIRST_TAB_ITEM].Dialog->ShowWindow(SW_SHOW);
		}

		DialogBase* GetDialogFromCurrentTab()
		{
			int tabID = pCTabCtrl->GetCurSel();
			return m_MapModeToControl[GroupIDActive][tabID].Dialog;
		}
	};
}