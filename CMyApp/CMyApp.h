
// CMyApp.h : main header file for the CMyApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCMyAppApp:
// See CMyApp.cpp for the implementation of this class
//

class CCMyAppApp : public CWinApp
{
public:
	CCMyAppApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCMyAppApp theApp;
