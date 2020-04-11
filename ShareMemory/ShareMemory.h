#pragma once
#include "stdafx.h"

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