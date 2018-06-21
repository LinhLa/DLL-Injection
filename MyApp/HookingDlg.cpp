// HookingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "HookingDlg.h"
#include "Util.h"
#include "afxdialogex.h"

#define MODULE_NAME_REGEX _T("[a-z0-9]+.dll")
#define HOOK_STR _T("Hook")
#define CALL_STR _T("Call")

IMPLEMENT_DYNAMIC(CHookingDlg, CDialogEx)

CHookingDlg::CHookingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOOKING_API, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_HOOKING_API, this);
}

CHookingDlg::~CHookingDlg()
{
}

void CHookingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHookingDlg, CDialogEx)
	ON_BN_CLICKED(ID_PARSE, &CHookingDlg::OnBnClickedParse)
	ON_BN_CLICKED(IDC_BUTTON1, &CHookingDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHookingDlg message handlers


void CHookingDlg::OnBnClickedParse()
{

}

BOOL CHookingDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_CONTROL)
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowText(CALL_STR);
		m_hooking_status = HOOK_BUTTON_STATUS::CALL;
	}
	else if (pMsg->message == WM_KEYUP && pMsg->wParam == VK_CONTROL)
	{
		GetDlgItem(IDC_BUTTON1)->SetWindowText(HOOK_STR);
		m_hooking_status = HOOK_BUTTON_STATUS::HOOK;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CHookingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_hooking_status = HOOK;
	return TRUE;
}



void CHookingDlg::OnBnClickedButton1()
{
	CString pszHookModName, pszFunctionName;
	GetDlgItemText(IDC_EDIT1, pszHookModName);
	GetDlgItemText(IDC_EDIT3, pszFunctionName);

	if (!Util::IsMatchRegex(pszHookModName.GetBuffer(), MODULE_NAME_REGEX))
	{
		AfxMessageBox(_T("Module name is wrong"), 0, 0);
		return;
	}

	switch (m_hooking_status)
	{
	case HOOK_BUTTON_STATUS::HOOK:
		Util::HookFunction<void()>(pszHookModName.GetBuffer(), pszFunctionName.GetBuffer(), &FunctionHooked);
		break;
	case HOOK_BUTTON_STATUS::CALL:
		FunctionNeedToHook();
		break;
	default:
		break;
	}
}

void FunctionHooked()
{
	AfxMessageBox(_T("void FunctionHooked() is called"), 0, 0);
}
