// RegrexCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "RegrexCheckDlg.h"
#include "Util.h"
#include "afxdialogex.h"


// CRegrexCheckDlg dialog

#define REGREX_PATTERN	_T("[a-z0-9]{1,18}")
IMPLEMENT_DYNAMIC(CRegrexCheckDlg, CDialogEx)

CRegrexCheckDlg::CRegrexCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGREX, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_REGREX, this);
}

CRegrexCheckDlg::~CRegrexCheckDlg()
{
}

void CRegrexCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegrexCheckDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegrexCheckDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRegrexCheckDlg message handlers


void CRegrexCheckDlg::OnBnClickedButton1()
{
	CString target;
	CString regrex;
	GetDlgItemText(IDC_EDIT1, target);
	GetDlgItemText(IDC_EDIT2, regrex);
	if (Util::IsMatchRegrex<REGEX_POLICY::ECMA_ICASE>(target.GetBuffer(), regrex.GetBuffer()))
		AfxMessageBox(_T("Match"), MB_OK, 0);
	else
		AfxMessageBox(_T("Not Match"), MB_OK, 0);

}
