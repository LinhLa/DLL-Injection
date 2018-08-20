
// ReadShareMemory.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CReadShareMemoryApp:
// See ReadShareMemory.cpp for the implementation of this class
//

class CReadShareMemoryApp : public CWinApp
{
public:
	CReadShareMemoryApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CReadShareMemoryApp theApp;