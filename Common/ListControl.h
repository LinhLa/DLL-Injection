#pragma once
#include "HookAPI.h"
#define LIST_CONTROL_STYLE	(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE)

namespace Util
{

	/*Base CListControl*/
	class CListControl
	{
	protected:
		CListCtrl *m_pListControl;
		const int m_HeaderNumber;
		int m_CurrentHeaderIndex;
		RECT m_ListControlRect;
		CListControl(CListCtrl *pListControl = NULL, int HeaderNumber = 0);
		virtual void LoadListControlData() = 0;
		virtual void OnInitListControl(DWORD dwStyle);
		void AddHeader(const TCHAR* lpszHeader = NULL, int ratio = 0);
	};

	class CListControlIAT:public CListControl
	{
	private:
		std::map<CString, Util::THUNK_DATA_ENTRY> m_MapImportFunction;
		CString m_lpszModuleName;
		BOOL m_bIsOtherProcess;
		DWORD m_dwPID;
	protected:
		CListControlIAT(CListCtrl *pListControl = NULL, DWORD HeaderNumber = 0);
		void Set(const TCHAR* lpszModuleName = NULL, BOOL bIsOtherProcess = FALSE, DWORD PID = 0);
		void LoadListControlData();
		void OnInitListControl(DWORD dwStyle = LIST_CONTROL_STYLE);
		void LoadMapImportFunction();
	};

	class CListControlHMODULE :public CListControl
	{
	private:
		std::vector<MODULEENTRY32> m_ListModuleEntry;
		DWORD m_dwPID;
	protected:
		CListControlHMODULE(CListCtrl *pListControl = NULL, DWORD HeaderNumber = 0);
		void Set(DWORD PID = 0);
		void LoadListControlData();
		void OnInitListControl(DWORD dwStyle = LIST_CONTROL_STYLE);
	};
}
