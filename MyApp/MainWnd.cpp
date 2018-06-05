// MainWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "MainWnd.h"
#include "DialogMainTab.h"
#include "MyAppDlg.h"
#include "RegrexCheckDlg.h"
#include "Util.h"
#include "afxdialogex.h"


// CMainWnd dialog

IMPLEMENT_DYNAMIC(CMainWnd, CDialogEx)

CMainWnd::CMainWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_MAIN, this);
}

CMainWnd::~CMainWnd()
{
}

void CMainWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainWnd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainWnd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainWnd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CMainWnd::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainWnd::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMainWnd message handlers


void CMainWnd::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CMyAppDlg MyAppDlg(this);
	MyAppDlg.DoModal();
}


void CMainWnd::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CDialogMainTab DialogMainTab(this);
	DialogMainTab.DoModal();
}


void CMainWnd::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	::SendMessage(MyAppFactory::GetInstance()->GetHandle(), WM_USER + 1, 0, 0);
}


void CMainWnd::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CRegrexCheckDlg RegrexCheckDlg(this);
	RegrexCheckDlg.DoModal();
}
