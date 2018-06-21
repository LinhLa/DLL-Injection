#pragma once
#include "stdafx.h"
#include "ObjectPool.h"
#include "WindowFactory.h"
#include "SwitchGroupTabHandler.h"




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

	template<class FuncPointer> void HookFunction(const CHAR* pszHookModName, const CHAR* pszFunctionName, FuncPointer newFuncAddr/*Address to be write*/)
	{
		HMODULE hInstance = GetModuleHandleA(NULL);		/*get current handle instance*/
		HMODULE hKernel = GetModuleHandleA(pszHookModName);	/*get handle module to be hooked*/

		PROC pfnHookAPIAddr = GetProcAddress(hKernel, pszFunctionName); /*Get function address to be hooked*/

		ULONG ulSize;
		PIMAGE_IMPORT_DESCRIPTOR pImportDesc = /*get address 1st entry IAT*/
			(PIMAGE_IMPORT_DESCRIPTOR)::ImageDirectoryEntryToData(hInstance, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

		while (pImportDesc->Name) /*Check module name*/
		{	/*module name = base address + RVA Name*/
			CHAR* pszModName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
			if (_stricmp(pszModName, pszHookModName) == 0)
				break;
			pImportDesc++;/*next Name*/
		}

		PIMAGE_THUNK_DATA pThunk =	/*get 1st entry function address list*/
			(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->FirstThunk);

		while (pThunk->u1.Function)
		{
			PROC *funcAddr = (PROC*)&pThunk->u1.Function;	/*get function address*/
			BOOL bFound = (*funcAddr == pfnHookAPIAddr);	/*compare to function address need to hooked*/

			if (bFound)
			{
				MEMORY_BASIC_INFORMATION mbi;
				/*query memory page*/
				VirtualQuery(funcAddr, &mbi, sizeof(MEMORY_BASIC_INFORMATION));

				/*unlock protected memory page*/
				VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);

				*funcAddr = *(PROC)newFuncAddr; /*rewrite address function*/

				DWORD dwOldProtect;
				/*lock protected memory page*/
				VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &dwOldProtect);
				break;
			}
			pThunk++;
		}
	}
}


