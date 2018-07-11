#pragma once
#include "stdafx.h"
#include "HookAPI.h"
#include "UtilRegex.h"

#define PATH_REPLACE_REGEX	_T("[A-Z]:\\\\([a-zA-Z0-9_\\. ]+\\\\)+")
#define THREAD_ATTRIBUTE	(PROCESS_CREATE_THREAD | \
							PROCESS_QUERY_INFORMATION | \
							PROCESS_VM_OPERATION | \
							PROCESS_VM_WRITE | \
							PROCESS_VM_READ)

#ifdef  _UNICODE
#define _tstring  std::wstring
#define ToGenericString(lpszString) (std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>().from_bytes(lpszString))
#else
#define _tstring std::string
#define ToGenericString(lpszString)
#endif

namespace Util
{
	BOOL SetPrivilege(HANDLE hToken,LPCTSTR lpszPrivilege,BOOL bEnablePrivilege)
	{
		TOKEN_PRIVILEGES tp;
		LUID luid;

		if (!LookupPrivilegeValue(
			NULL,				// lookup privilege on local system
			lpszPrivilege,		// privilege to lookup
			&luid))				// receives LUID of privilege
		{
			return FALSE;
		}

		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		if (bEnablePrivilege)
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		else
			tp.Privileges[0].Attributes = 0;

		// Enable the privilege or disable all privileges.
		if (!AdjustTokenPrivileges(
			hToken,
			FALSE,
			&tp,
			sizeof(TOKEN_PRIVILEGES),
			(PTOKEN_PRIVILEGES)NULL,
			(PDWORD)NULL))
		{
			return FALSE;
		}
		return TRUE;
	}


	BOOL FindProcess(std::vector<PROCESSENTRY32> &out)
	{
		PROCESSENTRY32 pe32;

		// Take a snapshot of all processes in the system.
		HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hProcessSnap)
			return FALSE;

		pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

		// Retrieve information about the first process and exit if unsuccessful
		if (!Process32First(hProcessSnap, &pe32))
		{
			CloseHandle(hProcessSnap);          // clean the snapshot object
			return FALSE;
		}

		do
		{
			out.push_back(pe32);
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
		return TRUE;
	}

	BOOL FindProcess(const TCHAR *lpszModulePath, std::pair<DWORD, HANDLE> &out)
	{
		if (!lpszModulePath)
			return FALSE;

		TCHAR lpszExePath[MAX_PATH] = {0};
		/*Retrive execute file name*/
		const TCHAR *lpszExeName = Util::RegexReplace<ECMA_ICASE>(lpszModulePath, PATH_REPLACE_REGEX);

		/*Find in list Process entry*/
		std::vector<PROCESSENTRY32> lstProcess;
		if (!FindProcess(lstProcess))
			return FALSE;

		for (auto &item : lstProcess)
		{
			/*Process handle*/HANDLE hProcess = NULL;

			/*Check if match execute file name*/
			if (0 == _tcsicmp(item.szExeFile, lpszExeName))
			{
				hProcess = OpenProcess(THREAD_ATTRIBUTE, TRUE, item.th32ProcessID);
				if (hProcess == INVALID_HANDLE_VALUE)
					continue;
				out = { item.th32ProcessID , hProcess };
				return TRUE;
			}

			/*Check if match Full path execute file*/
			DWORD dwExePathSize = 0;
			if (QueryFullProcessImageName(hProcess, 0, lpszExePath, &dwExePathSize) &&
				dwExePathSize > 0 &&
				0 == _tcsicmp(lpszExePath, lpszModulePath))
			{
				hProcess = OpenProcess(THREAD_ATTRIBUTE, TRUE, item.th32ProcessID);
				if (hProcess == INVALID_HANDLE_VALUE)
					continue;
				out = { item.th32ProcessID , hProcess };
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL FindProcessModule(DWORD dwPID ,std::vector<MODULEENTRY32> &out)
	{
		MODULEENTRY32 me32;

		//  Take a snapshot of all modules in the specified process.
		HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
		if (hModuleSnap == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		//  Set the size of the structure before using it.
		me32.dwSize = sizeof(MODULEENTRY32);

		//  Retrieve information about the first module, and exit if unsuccessful
		if (!Module32First(hModuleSnap, &me32))
		{
			CloseHandle(hModuleSnap);     // Must clean up the snapshot object!
			return FALSE;
		}

		//  Now walk the module list of the process and display information about each module
		do
		{
			out.push_back(me32);
		} while (Module32Next(hModuleSnap, &me32));

		//  Do not forget to clean up the snapshot object.
		CloseHandle(hModuleSnap);
		return TRUE;
	}

	BOOL FindProcessModule(DWORD dwPID, const TCHAR* lpszModulePath, MODULEENTRY32 &ModulEntry)
	{
		if (!lpszModulePath)
			return NULL;

		/*Find in list Process module*/
		std::vector<MODULEENTRY32> lstProcessModule;
		if (!FindProcessModule(dwPID, lstProcessModule))
			return FALSE;

		for (auto &item : lstProcessModule)
		{
			if (0 == _tcsicmp(item.szExePath, lpszModulePath))
			{
				ModulEntry = item;
				return TRUE;
			}
		}
		return NULL;
	}


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
			CHAR* pszModuleName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
			if (_stricmp(pszModuleName, pszHookModName) == 0)
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

	void HookFunctionW(const WCHAR* pszHookModName, const WCHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		std::string stdPszHookModName = convert.to_bytes(pszHookModName);
		std::string stdPszFunctionName = convert.to_bytes(pszFunctionName);
		HookFunctionA(stdPszHookModName.c_str(), stdPszFunctionName.c_str(), newFuncAddr);
	}

	void TransverseFirstThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		/*module name = base address + RVA Name*/
		CHAR* lpszModuleName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
		_tstring stdPszModuleName(ToGenericString(lpszModuleName));
		PIMAGE_THUNK_DATA pThunk =	/*get 1st entry FirstThunk*/
			(PIMAGE_THUNK_DATA)((PBYTE)hInstance + pImportDesc->FirstThunk);

		while (pThunk->u1.Function)
		{
			PROC *funcAddr = (PROC*)&pThunk->u1.Function;	/*get function address*/
			OutPut[stdPszModuleName.c_str()].lstExportByName.push_back({ _T("NONAME"), *reinterpret_cast<ULONG*>(funcAddr) });
			pThunk++;
		}
	}

	void TransverseOriginalThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut)
	{
		/*module name = base address + RVA Name*/
		CHAR* lpszModuleName = (CHAR*)((PBYTE)hInstance + pImportDesc->Name);
		_tstring stdPszModuleName(ToGenericString(lpszModuleName));
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
				OutPut[stdPszModuleName.c_str()].lstExportByOrdinal.push_back({ LOWORD(oThunk->u1.Ordinal), *reinterpret_cast<ULONG*>(funcAddr) }) :
				OutPut[stdPszModuleName.c_str()].lstExportByName.push_back({
				ToGenericString(pImportByName->Name).c_str(),
				*reinterpret_cast<ULONG*>(funcAddr)
			});
			oThunk++;
			pThunk++;
		}
	}


	void TransverseImportDirectory(std::map<CString, THUNK_DATA_ENTRY> &OutPut, const TCHAR* lpszModuleName)
	{
		HMODULE hInstance = GetModuleHandle(lpszModuleName);	/*lpszModuleName = NULL for current process*/
		if (!hInstance)
			return;

		ULONG ulSize = 0;
		IMAGE_IMPORT_DESCRIPTOR *pImportDesc = /*get address 1st entry IAT*/
			(IMAGE_IMPORT_DESCRIPTOR*)::ImageDirectoryEntryToData(hInstance, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

		while (pImportDesc->Name) /*Check module name*/
		{
			pImportDesc->OriginalFirstThunk ?
				TransverseOriginalThunk(hInstance, pImportDesc, OutPut) :
				TransverseFirstThunk(hInstance, pImportDesc, OutPut);
			pImportDesc++;/*next Import entry*/
		}
	}

	void TransverseImportDirectoryEx(std::map<CString, THUNK_DATA_ENTRY> &OutPut, const TCHAR* lpszModuleName, DWORD dwPID)
	{
		/*Find target Process Module*/
		MODULEENTRY32 ModulEntry;
		if (!FindProcessModule(dwPID, lpszModuleName, ModulEntry))
			return;

		/*Get handle target process*/
		HANDLE hProcess = OpenProcess(THREAD_ATTRIBUTE, TRUE, dwPID);
		if (hProcess == INVALID_HANDLE_VALUE)
			return;

		/*Change module Virtual memory protection to PAGE_READWRITE*/
		std::vector<MEMORY_BASIC_INFORMATION> lstRegionMemory;
		MEMORY_BASIC_INFORMATION mbi;
		SIZE_T lNumberOfBytesRead = 0;
		while (lNumberOfBytesRead < ModulEntry.modBaseSize)
		{
			VirtualQueryEx(hProcess, ModulEntry.modBaseAddr + lNumberOfBytesRead, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
			VirtualProtectEx(hProcess, ModulEntry.modBaseAddr + lNumberOfBytesRead, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);
			lstRegionMemory.push_back(mbi);
			lNumberOfBytesRead += mbi.RegionSize;
		}

		/*Read module memory to current process memory*/
		LPVOID lpBaseAddr = malloc(ModulEntry.modBaseSize);
		lNumberOfBytesRead = 0;
		if (!ReadProcessMemory(hProcess, ModulEntry.modBaseAddr, lpBaseAddr, ModulEntry.modBaseSize, &lNumberOfBytesRead) ||
			lNumberOfBytesRead == 0)
			return;

		ULONG ulSize = 0;
		IMAGE_IMPORT_DESCRIPTOR *pImportDesc = /*get address 1st entry IAT*/
			(IMAGE_IMPORT_DESCRIPTOR*)::ImageDirectoryEntryToData(lpBaseAddr, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

		if (!pImportDesc || ulSize == 0)
			return;

		while (pImportDesc->Name) /*Check module name*/
		{
			pImportDesc->OriginalFirstThunk ?
				TransverseOriginalThunk((HMODULE)lpBaseAddr, pImportDesc, OutPut) :
				TransverseFirstThunk((HMODULE)lpBaseAddr, pImportDesc, OutPut);
			pImportDesc++;/*next Import entry*/
		}

		/*Restore module memory protection*/
		DWORD dwOldProtect;
		for (auto &item : lstRegionMemory)
		{
			VirtualProtectEx(hProcess, item.BaseAddress, item.RegionSize, item.Protect, &dwOldProtect);
		}

		/*Free memory and handle*/
		CloseHandle(hProcess);
		free(lpBaseAddr);
	}

}