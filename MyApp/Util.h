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
typedef struct ThunkDataEntry
{
	std::list<std::pair<CString, PROC*>> lstExportByName;
	std::list<std::pair<ULONG, PROC*>> lstExportByOrdinal;
} THUNK_DATA_ENTRY;
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

		/*Start Debug infromation*/
		PIMAGE_THUNK_DATA oThunk =	/*get 1st entry function address list*/
			(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->OriginalFirstThunk);

		IMAGE_IMPORT_BY_NAME *pImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hInstance + oThunk->u1.AddressOfData);
		/*End Debug infromation*/

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

	template<unsigned int N = 0> void TransverseImportDirectory(std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		HMODULE hInstance = GetModuleHandleA(NULL);		/*get current handle instance*/
		ULONG ulSize;
		PIMAGE_IMPORT_DESCRIPTOR pImportDesc = /*get address 1st entry IAT*/
			(PIMAGE_IMPORT_DESCRIPTOR)::ImageDirectoryEntryToData(hInstance, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

		while (pImportDesc->Name) /*Check module name*/
		{
			pImportDesc->OriginalFirstThunk ?
				TransverseOriginalThunk(hInstance, pImportDesc, OutPut) :
				TransverseFirstThunk(hInstance, pImportDesc, OutPut);
			pImportDesc++;/*next Import entry*/
		}
	}

	template<class T> void TransverseFirstThunk(T hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		/*module name = base address + RVA Name*/
		CHAR* pszModName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
		PIMAGE_THUNK_DATA pThunk =	/*get 1st entry FirstThunk*/
			(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->FirstThunk);

		while (pThunk->u1.Function)
		{
			PROC *funcAddr = (PROC*)&pThunk->u1.Function;	/*get function address*/
			OutPut[pszModName].lstExportByName.push_back({ _T("NONAME"), funcAddr });
			pThunk++;
		}
	}

	template<class T> void TransverseOriginalThunk(T hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		try
		{
			/*module name = base address + RVA Name*/
			CHAR* pszModName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);

			PIMAGE_THUNK_DATA pThunk =	/*get 1st entry FirstThunk*/
				(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->FirstThunk);

			PIMAGE_THUNK_DATA oThunk =	/*get 1st entry OriginalFirstThunk*/
				(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->OriginalFirstThunk);

			while (oThunk->u1.Function)
			{

				/*Determind function export by name or Ordinal*/
				bool isExportByOrdinal = (IMAGE_ORDINAL_FLAG & oThunk->u1.Ordinal) == IMAGE_ORDINAL_FLAG;

				IMAGE_IMPORT_BY_NAME *pImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hInstance + oThunk->u1.AddressOfData);

				PROC *funcAddr = (PROC*)&pThunk->u1.Function;	/*get function address*/
				isExportByOrdinal ?
					OutPut[pszModName].lstExportByOrdinal.push_back({ LOWORD(oThunk->u1.Ordinal),funcAddr }) :
					OutPut[pszModName].lstExportByName.push_back({
					pImportByName->Name,
					funcAddr
				});
				oThunk++;
				pThunk++;
			}
		}
		catch (...)
		{
			if (EXCEPTION_ACCESS_VIOLATION == GetLastError())
			{
				AfxMessageBox("Exception: EXCEPTION_ACCESS_VIOLATION\n");
				return;
			}
		}
	}
}



