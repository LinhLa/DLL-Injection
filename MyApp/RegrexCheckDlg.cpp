// RegrexCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "RegrexCheckDlg.h"
#include "Util.h"
#include "afxdialogex.h"

#define REGEX_MATCH_STR _T("Check Regrex")
#define REGEX_REPLACE_STR _T("Replace Regrex")
// CRegrexCheckDlg dialog
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
	switch (m_regex_status)
	{
	case REGEX_BUTTON_STATUS::REGEX_MATCH:
		(Util::IsMatchRegex<REGEX_POLICY::ECMA_ICASE>(target.GetBuffer(), regrex.GetBuffer())) ?
			AfxMessageBox(_T("Match"), MB_OK, 0) :
			AfxMessageBox(_T("Not Match"), MB_OK, 0);
		break;
	case REGEX_BUTTON_STATUS::REGEX_REPLACE:
		Util::RegexReplace<REGEX_POLICY::ECMA_ICASE>(target.GetBuffer(), regrex.GetBuffer());
		break;
	default:
		break;
	}
}


BOOL CRegrexCheckDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_CONTROL)
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(REGEX_REPLACE_STR);
		m_regex_status = REGEX_BUTTON_STATUS::REGEX_REPLACE;
	}
	else if(pMsg->message == WM_KEYUP && pMsg->wParam == VK_CONTROL)
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowTextW(REGEX_MATCH_STR);
		m_regex_status = REGEX_BUTTON_STATUS::REGEX_MATCH;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
