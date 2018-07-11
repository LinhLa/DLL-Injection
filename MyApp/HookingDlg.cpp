// HookingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "HookingDlg.h"
#include "Util.h"
#include "afxdialogex.h"

#define HOOK_STR			_T("Hook")
#define CALL_STR			_T("Call")
IMPLEMENT_DYNAMIC(CHookingDlg, CDialogEx)

CHookingDlg::CHookingDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_HOOKING_API, pParent), CListControlIAT(&m_CListCtrl)
{
	MyAppFactory::GetInstance()->Add(IDD_HOOKING_API, this);
}

CHookingDlg::~CHookingDlg()
{
}

void CHookingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CListCtrl);
}


BEGIN_MESSAGE_MAP(CHookingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CHookingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(ID_CANCLE, &CHookingDlg::OnBnClickedCancle)
END_MESSAGE_MAP()


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
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("WinFactory.dll"));
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("FunctionNeedToHook"));
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	m_hooking_status = HOOK;

	CListControlIAT::OnInitListControl();
	CListControlIAT::LoadListControlData();
	return TRUE;
}

void CHookingDlg::OnBnClickedButton1()
{
	CString pszModuleName, pszFunctionName;
	GetDlgItemText(IDC_EDIT1, pszModuleName);
	GetDlgItemText(IDC_EDIT3, pszFunctionName);
	switch (m_hooking_status)
	{
	case HOOK_BUTTON_STATUS::HOOK:
		Util::HookFunction(pszModuleName, pszFunctionName, (PROC*)&FunctionHooked);
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


void CHookingDlg::OnBnClickedCancle()
{
	EndDialog(IDCANCEL);
}
