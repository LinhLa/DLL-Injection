// WinFactory.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinFactory.h"
#include "WindowFactory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Util;

BEGIN_MESSAGE_MAP(CWinFactoryApp, CWinApp)
END_MESSAGE_MAP()


// CWinFactoryApp construction

CWinFactoryApp::CWinFactoryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CWinFactoryApp object

CWinFactoryApp theApp;


// CWinFactoryApp initialization

BOOL CWinFactoryApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}


void FunctionNeedToHook()
{
	AfxMessageBox(_T("void WINFACTORY_API FunctionNeedToHook() is called"), 0, 0);
}

void* GetWindFactory()
{
	return (void*)MyAppFactory::GetInstance();

}

CWindFactory::CWindFactory()
{
	m_WndClass.style = 0; // Class style
	m_WndClass.lpfnWndProc = (WNDPROC)WndProc; // Window procedure address
	m_WndClass.cbClsExtra = 0; // Class extra bytes
	m_WndClass.cbWndExtra = 0; // Window extra bytes
	m_WndClass.hInstance = AfxGetInstanceHandle(); // Instance handle
	m_WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Icon handle
	m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor handle
	m_WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Background color
	m_WndClass.lpszMenuName = NULL; // Menu name
	m_WndClass.lpszClassName = m_WndClassName; // WNDCLASS name

	RegisterClass(&m_WndClass);

	m_Hwnd = CreateWindow(
		m_WndClassName, // WNDCLASS name
		_T(""), // Window title
		WS_OVERLAPPEDWINDOW, // Window style
		CW_USEDEFAULT, // Horizontal position
		CW_USEDEFAULT, // Vertical position
		CW_USEDEFAULT, // Initial width
		CW_USEDEFAULT, // Initial height
		HWND_MESSAGE, // HWND_MESSAGE for Window message only
		NULL, // Menu handle
		AfxGetInstanceHandle(), // Application's instance handle
		NULL // Window-creation data
	);

	Run();
}

CWindFactory::~CWindFactory() {
	SendMessage(m_Hwnd, WM_DESTROY, 0, 0);
	UnregisterClass(m_WndClassName, AfxGetInstanceHandle());
}

LRESULT CALLBACK CWindFactory::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_USER + 1:
		AfxMessageBox(_T("WM_USER + 1 Message"), MB_OK, 0);
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void CWindFactory::MessageLooping()
{
	while (GetMessage(&m_Msg, NULL, 0, 0)) {
		TranslateMessage(&m_Msg);
		DispatchMessage(&m_Msg);
	}
}
CWindFactory* CWindFactory::GetInstance()
{
	static CWindFactory instance;
	return &instance;
}

const HWND& CWindFactory::GetHandle() const
{
	return this->m_Hwnd;
}

void CWindFactory::Add(int ID, CWnd* const pCWnd)
{
	auto itr = m_MapCWndHwnd.find(ID);

	if (itr != m_MapCWndHwnd.end() && *itr->second != NULL && IsWindow(*itr->second))
	{
		throw std::exception("ID exist and HWND valid");
	}
	else
	{
		m_MapCWndHwnd[ID] = &pCWnd->m_hWnd;
	}
}

CWnd* const CWindFactory::Get(int ID)
{
	CWnd *pResult = NULL;
	auto itr = m_MapCWndHwnd.find(ID);
	if (itr != m_MapCWndHwnd.end() && *itr->second != NULL && ::IsWindow(*itr->second))
	{
		pResult = CWnd::FromHandle(*itr->second);
	}
	return pResult;
}
void CWindFactory::Run()
{
	std::thread t(&CWindFactory::MessageLooping, this);
	t.detach();
}
