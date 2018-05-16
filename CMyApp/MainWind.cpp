
// MainWind.cpp : implementation of the CMainWindow class
//

#include "stdafx.h"
#include "CMyApp.h"

#include "MainWind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainWindow

IMPLEMENT_DYNCREATE(CMainWindow, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainWindow construction/destruction

CMainWindow::CMainWindow()
{
	// TODO: add member initialization code here
}

CMainWindow::~CMainWindow()
{
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainWindow::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	return TRUE;
}

// CMainWindow diagnostics

#ifdef _DEBUG
void CMainWindow::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainWindow::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainWindow message handlers

