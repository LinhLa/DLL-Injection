#pragma once
#include "stdafx.h"
#include "ObjectPool.h"
#include "WindowFactory.h"
#include "GroupTabHandler.h"
#include "HookAPI.h"

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
	template<REGEX_POLICY N = ECMA_ICASE> bool IsMatchRegex(const TCHAR* target, const TCHAR* regrex)
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

	template<REGEX_POLICY N = ECMA_ICASE> const TCHAR* RegexReplace(const TCHAR* target, const TCHAR* regrex)
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

	template<class T> BOOL FindProcess(std::vector<PROCESSENTRY32> &out)
	{
		HANDLE hProcessSnap;
		PROCESSENTRY32 pe32;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hProcessSnap)
			return(FALSE);

		pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

		// Retrieve information about the first process and exit if unsuccessful
		if (!Process32First(hProcessSnap, &pe32))
		{
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return(FALSE);
		}

		do
		{
			out.push_back(pe32);
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
		return TRUE;
	}

}



