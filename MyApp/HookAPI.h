#pragma once
#include "stdafx.h"
#ifdef _UNICODE
#define HookFunction(pszHookModName, pszFunctionName, newFuncAddr) HookFunctionW(pszHookModName, pszFunctionName, newFuncAddr)

#else
#define HookFunction(pszHookModName, pszFunctionName, newFuncAddr) HookFunctionA(pszHookModName, pszFunctionName, newFuncAddr)

#endif

namespace Util
{
	typedef struct ThunkDataEntry
	{
		std::list<std::pair<CString, PROC*>> lstExportByName;
		std::list<std::pair<ULONG, PROC*>> lstExportByOrdinal;
	} THUNK_DATA_ENTRY;

	void HookFunctionA(const CHAR* pszHookModName, const CHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/);
	void HookFunctionW(const TCHAR* pszHookModName, const TCHAR* pszFunctionName, PROC *newFuncAddr/*Address to be write*/);

	void TransverseFirstThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut);
	void TransverseOriginalThunk(HMODULE hInstance, IMAGE_IMPORT_DESCRIPTOR *pImportDesc, std::map<CString, THUNK_DATA_ENTRY> &OutPut);
	void TransverseImportDirectory(std::map<CString, THUNK_DATA_ENTRY> &OutPut);
}