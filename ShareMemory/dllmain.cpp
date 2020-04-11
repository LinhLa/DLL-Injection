#include "stdafx.h"
#include "ShareMemory.h"

#define SHARE_MEMORY_SIZE	4096
#define	MAP_OBJ_NAME		_T("dllmemfilemap")

static LPVOID lpvMem = NULL;      // pointer to shared memory
static HANDLE hMapObject = NULL;  // handle to file mapping

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


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	BOOL fInit, fIgnore;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
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
		fInit = (GetLastError() != ERROR_ALREADY_EXISTS);
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

		break;
		// The attached process creates a new thread
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		// Unmap shared memory from the process's address space
		fIgnore = UnmapViewOfFile(lpvMem);
		// Close the process's handle to the file-mapping object
		fIgnore = CloseHandle(hMapObject);
		hMapObject = lpvMem = NULL;
		break;
	}
	return TRUE;
}
