
// MyAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "DialogMainTab.h"
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
}

void CMyAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyAppDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyAppDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyAppDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyAppDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK2, &CMyAppDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMyAppDlg message handlers

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	//CStringPtr myCstrPtr(_T("CLick to Gen 128 Object"));
	CStringPtr myCstrPtr1;
	*myCstrPtr1 = _T("CLick to Gen 128 Object");
	//*myCstrPtr1 = *myCstrPtr;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

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



void CMyAppDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CStringPtr myCstringArray[128];
	myCstringArray[0]->Format(_T("%d"), POOL_CSTRING()->size());
	myCstringArray[1]->Format(_T("%d"), POOL_CSTRING()->capacity());
	GetDlgItem(IDC_EDIT1)->SetWindowText(*myCstringArray[0]);
	GetDlgItem(IDC_EDIT2)->SetWindowText(*myCstringArray[1]);
}


void CMyAppDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CStringPtr myCstringArray[256];
	myCstringArray[0]->Format(_T("%d"), POOL_CSTRING()->size());
	myCstringArray[1]->Format(_T("%d"), POOL_CSTRING()->capacity());
	GetDlgItem(IDC_EDIT1)->SetWindowText(*myCstringArray[0]);
	GetDlgItem(IDC_EDIT2)->SetWindowText(*myCstringArray[1]);
}


void CMyAppDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CStringPtr myCstringArray[512];
	myCstringArray[0]->Format(_T("%d"), POOL_CSTRING()->size());
	myCstringArray[1]->Format(_T("%d"), POOL_CSTRING()->capacity());
	GetDlgItem(IDC_EDIT1)->SetWindowText(*myCstringArray[0]);
	GetDlgItem(IDC_EDIT2)->SetWindowText(*myCstringArray[1]);
}


void CMyAppDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CStringPtr myCstringArray[1024];
	myCstringArray[0]->Format(_T("%d"), POOL_CSTRING()->size());
	myCstringArray[1]->Format(_T("%d"), POOL_CSTRING()->capacity());
	GetDlgItem(IDC_EDIT1)->SetWindowText(*myCstringArray[0]);
	GetDlgItem(IDC_EDIT2)->SetWindowText(*myCstringArray[1]);
}


void CMyAppDlg::OnBnClickedOk2()
{
	// TODO: Add your control notification handler code here
	CDialogMainTab DialogMainTab(this);
	DialogMainTab.DoModal();
}