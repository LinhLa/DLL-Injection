#pragma once
#include "HookAPI.h"
namespace Util
{
	class CListControlIAT
	{
	private:
		CListCtrl *m_pListControl;
		std::map<CString, Util::THUNK_DATA_ENTRY> m_MapImportFunction;
	protected:
		CListControlIAT(CListCtrl *pListControl = NULL);
		~CListControlIAT();
		void LoadListControlData();
		void InitListControl();
		void LoadMapImportFunction(const TCHAR* lpszModuleName = NULL, DWORD dwPID = 0, bool IsOtherProcess = false);
	};

}
