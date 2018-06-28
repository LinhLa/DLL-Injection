#pragma once
#include "stdafx.h"
#include "HookAPI.h"

namespace Util
{
	void HookFunctionA(const CHAR* pszHookModName, const CHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/)
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

	void HookFunctionW(const TCHAR* pszHookModName, const TCHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		std::string stdPszHookModName = convert.to_bytes(pszHookModName);
		std::string stdPszFunctionName = convert.to_bytes(pszFunctionName);
		HookFunctionA(stdPszHookModName.c_str(), stdPszFunctionName.c_str(), newFuncAddr);
	}

	void TransverseFirstThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		/*module name = base address + RVA Name*/
		CHAR* pszModName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		std::wstring stdPszModName = convert.from_bytes(pszModName);

		PIMAGE_THUNK_DATA pThunk =	/*get 1st entry FirstThunk*/
			(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->FirstThunk);

		while (pThunk->u1.Function)
		{
			PROC *funcAddr = (PROC*)&pThunk->u1.Function;	/*get function address*/
			OutPut[stdPszModName.c_str()].lstExportByName.push_back({ _T("NONAME"), funcAddr });
			pThunk++;
		}
	}

	void TransverseOriginalThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		/*module name = base address + RVA Name*/
		CHAR* pszModName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
#ifdef  _UNICODE
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		std::wstring stdPszModName = convert.from_bytes(pszModName);
#else
		std::string stdPszModName(pszModName);
#endif //  _UNICODE
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
				OutPut[stdPszModName.c_str()].lstExportByOrdinal.push_back({ LOWORD(oThunk->u1.Ordinal),funcAddr }) :
				OutPut[stdPszModName.c_str()].lstExportByName.push_back({
				convert.from_bytes(pImportByName->Name).c_str(),
				funcAddr
			});
			oThunk++;
			pThunk++;
		}
	}


	void TransverseImportDirectory(std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		HMODULE hInstance = GetModuleHandle(NULL);		/*get current handle instance*/
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
}