
// DllInjectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DllInjection.h"
#include "DllInjectionDlg.h"
#include "DllInject.h"
#include "Util.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDllInjectionDlg::CDllInjectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLLINJECTION_DIALOG, pParent), Util::CListControlIAT(&m_CListCtrl)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	MyAppFactory::GetInstance()->Add(IDD_DLLINJECTION_DIALOG, this);
}

void CDllInjectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CListCtrl);
}

BEGIN_MESSAGE_MAP(CDllInjectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDllInjectionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDllInjectionDlg message handlers

BOOL CDllInjectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CListControlIAT::InitListControl();

	return TRUE;
}

void CDllInjectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}



void CDllInjectionDlg::OnPaint()
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


HCURSOR CDllInjectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDllInjectionDlg::OnBnClickedOk()
{
	CString lpszModuleName, lpszDllInject;
	GetDlgItemText(IDC_EDIT1, lpszModuleName);
	GetDlgItemText(IDC_EDIT2, lpszDllInject);

	DWORD dwPID = 0;
	if (!DllInject::Inject(lpszModuleName.GetBuffer(), lpszDllInject.GetBuffer(), dwPID))
	{
		DllInject::notifyError();
		return;
	}
	AfxMessageBox(_T("Inject Dll Succeeded"));
	CListControlIAT::LoadMapImportFunction(lpszModuleName.GetBuffer(), dwPID, true);
	CListControlIAT::LoadListControlData();
}
