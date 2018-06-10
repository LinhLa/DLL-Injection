#pragma once
#include <regex>
#include <string>
#include <functional>
#include "ObjectPool.h"
#include "WindowFactory.h"

#ifdef _UNICODE
#define _tregex std::wregex
#define _string std::wstring
#define _smatch std::wsmatch
#else
#define _tregex std::regex
#define _string std::string
#define _smatch std::smatch
#endif
enum REGEX_POLICY {
	ICASE = 0,
	ECMA,
	ECMA_ICASE
};
namespace Util
{
	/*Insert item Tab control*/
	template<class T> void InitItemTabControl(T *pTabCtrl, CWnd *pDialogItem, int tabID, ::CString &title)
	{
		TCITEM tcItem;
		tcItem.mask = TCIF_TEXT | TCIF_PARAM;
		tcItem.pszText = title.GetBuffer();
		tcItem.lParam = (LPARAM)&(*pDialogItem);
		pTabCtrl->InsertItem(tabID, &tcItem);

		CRect rcItem, rcDisplayArea;
		pTabCtrl->GetItemRect(0, &rcItem);
		pTabCtrl->GetClientRect(&rcDisplayArea);
		pDialogItem->SetWindowPos(pTabCtrl, rcItem.left, rcItem.bottom, rcDisplayArea.Width() - 5, rcDisplayArea.Height() - rcItem.Height() - 5, SWP_NOZORDER);
	}


	template<REGEX_POLICY N = ECMA_ICASE> bool IsMatchRegrex(const TCHAR* target, const TCHAR* regrex)
	{
		const std::regex_constants::syntax_option_type PolicyRegrex[] =
		{
			std::regex_constants::icase,
			std::regex_constants::ECMAScript,
			std::regex_constants::icase | std::regex_constants::ECMAScript
		};
		_tregex self_regex(regrex, PolicyRegrex[N]);
		return std::regex_match(target, self_regex);
	}

	template<REGEX_POLICY N = ECMA_ICASE> const TCHAR* RegrexReplace(const TCHAR* target, const TCHAR* regrex)
	{
		static _string s;
		s.clear();
		const std::regex_constants::syntax_option_type PolicyRegrex[] =
		{
			std::regex_constants::icase,
			std::regex_constants::ECMAScript,
			std::regex_constants::icase | std::regex_constants::ECMAScript
		};
		_tregex self_regex(regrex, PolicyRegrex[N]);
		s = std::regex_replace(target, self_regex, _T(""));
		return s.c_str();
	}
}


