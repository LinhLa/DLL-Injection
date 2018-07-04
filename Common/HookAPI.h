#pragma once
#pragma comment(lib, "Dbghelp.lib")
#ifdef _UNICODE
#define HookFunction(pszHookModName, pszFunctionName, newFuncAddr) HookFunctionW(pszHookModName, pszFunctionName, newFuncAddr)

#else
#define HookFunction(pszHookModName, pszFunctionName, newFuncAddr) HookFunctionA(pszHookModName, pszFunctionName, newFuncAddr)

#endif

namespace Util
{
	BOOL FindProcess(std::vector<PROCESSENTRY32> &out);
	BOOL FindProcess(const TCHAR *lpszModulePath, std::pair<DWORD, HANDLE> &out);

	BOOL FindProcessModule(DWORD dwPID, std::vector<MODULEENTRY32> &out);
	BOOL FindProcessModule(DWORD dwPID, const TCHAR* lpszModulePath, MODULEENTRY32 &ModulEntry);


	typedef struct ThunkDataEntry
	{
		std::list<std::pair<CString, ULONG>> lstExportByName;
		std::list<std::pair<ULONG, ULONG>> lstExportByOrdinal;
	} THUNK_DATA_ENTRY;

	void HookFunctionA(const CHAR* pszHookModName, const CHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/);
	void HookFunctionW(const TCHAR* pszHookModName, const TCHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/);

	void TransverseFirstThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut);
	void TransverseOriginalThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut);
	void TransverseImportDirectory(std::map<CString, THUNK_DATA_ENTRY> &OutPut, const TCHAR* lpszModuleName = NULL);
	void TransverseImportDirectoryEx(std::map<CString, THUNK_DATA_ENTRY> &OutPut, const TCHAR* lpszModuleName, DWORD dwPID);

}