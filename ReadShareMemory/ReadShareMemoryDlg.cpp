
#include "stdafx.h"
#include "ReadShareMemory.h"
#include "ReadShareMemoryDlg.h"
#include "afxdialogex.h"
#include "ShareMemory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CReadShareMemoryDlg::CReadShareMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READSHAREMEMORY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadShareMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadShareMemoryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON1, &CReadShareMemoryDlg::OnShowShareMemory)
	ON_BN_CLICKED(IDOK, &CReadShareMemoryDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReadShareMemoryDlg message handlers

BOOL CReadShareMemoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;
}

void CReadShareMemoryDlg::OnPaint()
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

HCURSOR CReadShareMemoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadShareMemoryDlg::OnShowShareMemory()
{
	TCHAR lpszText[256] = _T("");
	GetSharedMem(lpszText, 255);
	SetDlgItemText(IDC_EDIT2, lpszText);
}


void CReadShareMemoryDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
