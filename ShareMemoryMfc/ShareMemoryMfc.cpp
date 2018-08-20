// ShareMemoryMfc.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ShareMemoryMfc.h"

#define SHARE_MEMORY_SIZE	4096
#define	MAP_OBJ_NAME		_T("dllmemfilemapMfc")

static LPVOID lpvMem = NULL;      // pointer to shared memory
static HANDLE hMapObject = NULL;  // handle to file mapping

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CShareMemoryMfcApp

BEGIN_MESSAGE_MAP(CShareMemoryMfcApp, CWinApp)
END_MESSAGE_MAP()


// CShareMemoryMfcApp construction

CShareMemoryMfcApp::CShareMemoryMfcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CShareMemoryMfcApp::~CShareMemoryMfcApp()
{
	// Unmap shared memory from the process's address space
	BOOL fIgnore = UnmapViewOfFile(lpvMem);
	// Close the process's handle to the file-mapping object
	fIgnore = CloseHandle(hMapObject);
	hMapObject = lpvMem = NULL;
}
// The one and only CShareMemoryMfcApp object
CShareMemoryMfcApp theApp;


// CShareMemoryMfcApp initialization
BOOL CShareMemoryMfcApp::InitInstance()
{
	CWinApp::InitInstance();
	// Create a named file mapping object
	hMapObject = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // use paging file
		NULL,                   // default security attributes
		PAGE_READWRITE,         // read/write access
		0,                      // size: high 32-bits
		SHARE_MEMORY_SIZE,      // size: low 32-bits
		MAP_OBJ_NAME); // name of map object

	if (hMapObject == NULL)
		return FALSE;

	// The first process to attach initializes memory
	BOOL fInit = (GetLastError() != ERROR_ALREADY_EXISTS);
	// Get a pointer to the file-mapped shared memory
	lpvMem = MapViewOfFile(
		hMapObject,     // object to map view of
		FILE_MAP_WRITE, // read/write access
		0,              // high offset:  map from
		0,              // low offset:   beginning
		0);             // default: map entire file

	if (lpvMem == NULL)
		return FALSE;

	// Initialize memory if this is the first process
	if (fInit)
		memset(lpvMem, '\0', SHARE_MEMORY_SIZE);

	return TRUE;
}

								  // SetSharedMem sets the contents of the shared memory
void SetSharedMem(TCHAR* lpszBuf)
{
	DWORD dwCount = 1;
	// Get the address of the shared memory block
	TCHAR* lpszTmp = (TCHAR*)lpvMem;

	// Copy the null-terminated string into shared memory
	while (*lpszBuf && dwCount < SHARE_MEMORY_SIZE)
	{
		*lpszTmp++ = *lpszBuf++;
		dwCount++;
	}
	*lpszTmp = '\0';
}

// GetSharedMem gets the contents of the shared memory
void GetSharedMem(TCHAR* lpszBuf, DWORD cchSize)
{
	// Get the address of the shared memory block
	TCHAR* lpszTmp = (TCHAR*)lpvMem;
	// Copy from shared memory into the caller's buffer
	while (*lpszTmp && --cchSize)
		*lpszBuf++ = *lpszTmp++;
	*lpszBuf = '\0';
}
