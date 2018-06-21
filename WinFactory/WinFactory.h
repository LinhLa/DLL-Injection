// WinFactory.h : main header file for the WinFactory DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinFactoryApp
// See WinFactory.cpp for the implementation of this class
//

class CWinFactoryApp : public CWinApp
{
public:
	CWinFactoryApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
