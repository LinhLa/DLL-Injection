#include "stdafx.h"
#include "DllInject.h"
#include "UtilRegex.h"
#define KERNEL_MODULE		_T("kernel32.dll")
#define LOAD_LIBRARY_API	"LoadLibraryA"

#define DLLINJECT_REGEX _T("[A-Z]:\\\\([a-zA-Z0-9_\\. ]+\\\\)+([a-zA-Z0-9_\\. ]+\\.(dll|DLL))")
#define MODULE_REGEX	_T("[A-Z]:\\\\([a-zA-Z0-9_\\. ]+\\\\)+([a-zA-Z0-9_\\. ]+\\.exe)")

#define THREAD_ATTRIBUTE (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)

typedef DWORD PID;

namespace Util
{
	/*Constructor get handle kernel32 and function addr LoadLibraryA */
	DllInject::DllInject() :
		hKernel(GetModuleHandle(KERNEL_MODULE)),
		pAddrLoadLibraryA(GetProcAddress(this->hKernel, LOAD_LIBRARY_API)),
		hToken(NULL)
	{
		//Get handle kernel32.dll
		if (!hKernel)
			AfxMessageBox(_T("kernel32.dll can not load"));

		if (!pAddrLoadLibraryA)
			AfxMessageBox(_T("LoadLibraryA fail to get address"));

		//Get handle token Current process
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			AfxMessageBox(_T("OpenProcessToken fail"));

		//Set Privilege Current process to Debug
		if (!Util::SetPrivilege(hToken, SE_DEBUG_NAME, TRUE))
			AfxMessageBox(_T("SetPrivilege fail to set SE_DEBUG_NAME"));
	}

	DllInject::~DllInject(){
		if (hToken)
			CloseHandle(hToken);
	}

	BOOL DllInject::Inject(const TCHAR* lpszModule, const TCHAR *lpszDllInject, DWORD &dwPID)
	{
		/*Check Module name and DLLinject path*/
		if (/*!Util::IsMatchRegex<ECMA>(lpszModule, MODULE_REGEX) ||*/
			!PathFileExists(lpszModule)
			)
		{
			notifyError = [](){AfxMessageBox(_T("Module path invalid")); };
			return FALSE;
		}

		if (/*!Util::IsMatchRegex<ECMA>(lpszDllInject, DLLINJECT_REGEX) ||*/
			!PathFileExists(lpszDllInject)
			)
		{
			notifyError = []() {AfxMessageBox(_T("DLLinject path invalid")); };
			return FALSE;
		}

		/*Get handle target process by Module name*/
		std::pair<PID, HANDLE> PID2HandleProcess;
		if (!Util::FindProcess(lpszModule, PID2HandleProcess))
		{
			notifyError = []() {AfxMessageBox(_T("FindProcess failed")); };
			return FALSE;
		}

		if (!PID2HandleProcess.second)
		{
			notifyError = [](){AfxMessageBox(_T("OpenProcess failed")); };
			return FALSE;
		}

		/*Allocate new commit page memory in target process*/
		LPVOID pBaseAddr = VirtualAllocEx(PID2HandleProcess.second, NULL, _tcslen(lpszDllInject)* sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
		if (!pBaseAddr)
		{
			notifyError = [](){AfxMessageBox(_T("VirtualAllocEx failed")); };
			CloseHandle(PID2HandleProcess.second);
			return FALSE;
		}

		/*Convert DllInject path to ANSI string*/
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
		std::string stdPszDllInject = convert.to_bytes(lpszDllInject);

		/*Write DllInject Path to targe process's virtual memory*/
		SIZE_T lpNumberOfBytesWritten = 0;
		if (!WriteProcessMemory(PID2HandleProcess.second, pBaseAddr, stdPszDllInject.c_str(), stdPszDllInject.length(), &lpNumberOfBytesWritten))
		{
			notifyError = [](){AfxMessageBox(_T("WriteProcessMemory failed")); };
			CloseHandle(PID2HandleProcess.second);
			return FALSE;
		}

		/*Init new thread to load DllInject in target process*/
		DWORD dwThreadID = 0;
		HANDLE hThread = CreateRemoteThread(PID2HandleProcess.second, NULL, 0, (LPTHREAD_START_ROUTINE)pAddrLoadLibraryA, pBaseAddr, 0, &dwThreadID);
		if (!hThread)
		{
			notifyError = [](){AfxMessageBox(_T("CreateRemoteThread failed")); };
			CloseHandle(PID2HandleProcess.second);
			return FALSE;
		}

		/*Free memory and close Handle target process, thread*/
		VirtualFreeEx(PID2HandleProcess.second, pBaseAddr, _tcslen(lpszDllInject) * sizeof(TCHAR), PAGE_NOACCESS);
		CloseHandle(PID2HandleProcess.second);
		CloseHandle(hThread);

		/*Return PID*/
		dwPID = PID2HandleProcess.first;
		return TRUE;
	}

}
