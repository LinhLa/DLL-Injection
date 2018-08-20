
// WriteShareMemoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WriteShareMemory.h"
#include "WriteShareMemoryDlg.h"
#include "afxdialogex.h"
#include "ShareMemory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWriteShareMemoryDlg dialog



CWriteShareMemoryDlg::CWriteShareMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WRITESHAREMEMORY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriteShareMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWriteShareMemoryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON1, &CWriteShareMemoryDlg::OnWriteShareMemory)
END_MESSAGE_MAP()

BOOL CWriteShareMemoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	return TRUE;
}

void CWriteShareMemoryDlg::OnPaint()
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

HCURSOR CWriteShareMemoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWriteShareMemoryDlg::OnWriteShareMemory()
{
	TCHAR lpszText[256] = _T("");
	GetDlgItemText(IDC_EDIT1, lpszText, 255);
	SetSharedMem(lpszText);
}
