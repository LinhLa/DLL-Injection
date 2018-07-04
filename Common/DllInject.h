#pragma once
#include "HookAPI.h"

namespace Util
{
	class DllInject
	{
	private:
		HMODULE hKernel;
		PROC pAddrLoadLibraryA;
	protected:
		std::function<void()> notifyError;
		DllInject();
		~DllInject();
		BOOL Inject(const TCHAR* lpszModule, const TCHAR *lpszDllInject, DWORD &dwPID);
	};
}