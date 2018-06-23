// HookingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "HookingDlg.h"
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
	ON_BN_CLICKED(IDC_BUTTON1, &CHookingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(ID_CANCLE, &CHookingDlg::OnBnClickedCancle)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CHookingDlg::OnCbnSelchangeCombo1)
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

void CHookingDlg::SetComboFunction()
{
	CComboBox *pModuleFunction = (CComboBox*)GetDlgItem(IDC_COMBO2);
	pModuleFunction->Clear();

	USHORT uIndexModuleFunction = 0;
	CString lpszText;
	GetDlgItemText(IDC_COMBO1, lpszText);

	auto &ImportEntry = m_MapImportFunction[lpszText];
	if (ImportEntry.lstExportByName.size())
	{
		for (auto &fEntry : ImportEntry.lstExportByName)
		{
			lpszText.Format(_T("%s - %d"), fEntry.first, *fEntry.second);
			pModuleFunction->InsertString(uIndexModuleFunction++, lpszText);
		}
	}
	if (ImportEntry.lstExportByOrdinal.size())
	{
		for (auto &fEntry : ImportEntry.lstExportByOrdinal)
		{
			lpszText.Format(_T("%d - %d"), fEntry.first, *fEntry.second);
			pModuleFunction->InsertString(uIndexModuleFunction++, lpszText);
		}
	}
	pModuleFunction->SetCurSel(0);
}

BOOL CHookingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("WinFactory.dll"));
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("FunctionNeedToHook"));
	m_hooking_status = HOOK;
	Util::TransverseImportDirectory<0>(m_MapImportFunction);

	CComboBox *pModuleName = (CComboBox*)GetDlgItem(IDC_COMBO1);
	USHORT uIndexModuleName = 0;
	for (auto &ImportEntry : m_MapImportFunction)
	{
		pModuleName->InsertString(uIndexModuleName++, ImportEntry.first);
	}
	pModuleName->SetCurSel(0);
	SetComboFunction();
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


void CHookingDlg::OnBnClickedCancle()
{
	EndDialog(IDCANCEL);
}


void CHookingDlg::OnCbnSelchangeCombo1()
{
	SetComboFunction();
}
