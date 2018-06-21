
// MyAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "Util.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAppDlg dialog

CMyAppDlg::CMyAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	MyAppFactory::GetInstance()->Add(IDD_MYAPP_DIALOG, this);
}

void CMyAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyAppDlg::OnGen128Object)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyAppDlg::OnGen256Object)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyAppDlg::OnGen512Object)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyAppDlg::OnGen1024Object)
END_MESSAGE_MAP()


// CMyAppDlg message handlers

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CStringPtr Mystr(_T("Mystr"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnGen128Object()
{
	CStringPtr myCstringArray[128];
	UpdateStatic(myCstringArray);
}


void CMyAppDlg::OnGen256Object()
{
	CStringPtr myCstringArray[256];
	UpdateStatic(myCstringArray);
}


void CMyAppDlg::OnGen512Object()
{
	CStringPtr myCstringArray[512];
	UpdateStatic(myCstringArray);
}


void CMyAppDlg::OnGen1024Object()
{
	CStringPtr myCstringArray[1024];
	UpdateStatic(myCstringArray);
}

void CMyAppDlg::UpdateStatic(CStringPtr myCstringArray[])
{
	myCstringArray[0]->Format(_T("%d"), POOL_CSTRING()->size());
	myCstringArray[1]->Format(_T("%d"), POOL_CSTRING()->capacity());
	GetDlgItem(IDC_EDIT1)->SetWindowText(*myCstringArray[0]);
	GetDlgItem(IDC_EDIT2)->SetWindowText(*myCstringArray[1]);
}
