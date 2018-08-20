// ShareMemoryMfc.h : main header file for the ShareMemoryMfc DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CShareMemoryMfcApp
// See ShareMemoryMfc.cpp for the implementation of this class
//

class CShareMemoryMfcApp : public CWinApp
{
public:
	CShareMemoryMfcApp();
	~CShareMemoryMfcApp();
// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#ifdef _USRDLL
#define SHAREMEMORY_API __declspec(dllexport)
#else
#define SHAREMEMORY_API __declspec(dllimport)
#endif

#ifdef __cplusplus    // If used by C++ code,
extern "C" {          // we need to export the C interface
#endif

	// SetSharedMem sets the contents of the shared memory
	SHAREMEMORY_API void SetSharedMem(TCHAR* lpszBuf);
	// GetSharedMem gets the contents of the shared memory
	SHAREMEMORY_API void GetSharedMem(TCHAR* lpszBuf, DWORD cchSize);

#ifdef __cplusplus
}
#endif