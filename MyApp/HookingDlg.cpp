// HookingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "HookingDlg.h"
#include "afxdialogex.h"


#define MODULE_NAME_REGEX	_T("[a-z0-9]+.dll")
#define HOOK_STR			_T("Hook")
#define CALL_STR			_T("Call")
#define FUNCTION_NAME		_T("Function name/Ordinal")
#define FUNCTION_ADDRESS	_T("Function address")
#define MODULE_NAME			_T("Module name")
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
void CHookingDlg::LoadListControlData()
{
	m_CListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE);
	RECT lstCtrlRect;
	m_CListCtrl.GetWindowRect(&lstCtrlRect);
	m_CListCtrl.InsertColumn(
		0,              // Rank/order of item
		MODULE_NAME,    // Caption for this header
		LVCFMT_LEFT,    // Relative position of items under header
		(lstCtrlRect.right - lstCtrlRect.left) / 4);// Width of items under header

	m_CListCtrl.InsertColumn(1, FUNCTION_NAME, LVCFMT_LEFT, (lstCtrlRect.right - lstCtrlRect.left) / 2);
	m_CListCtrl.InsertColumn(2, FUNCTION_ADDRESS, LVCFMT_LEFT, (lstCtrlRect.right - lstCtrlRect.left) / 4);

	for (auto &ImportEntry : m_MapImportFunction)
	{
		CString lpszText;
		if (ImportEntry.second.lstExportByName.size())
		{
			for (auto &fEntry : ImportEntry.second.lstExportByName)
			{
				int nIndex = m_CListCtrl.InsertItem(0, ImportEntry.first);
				m_CListCtrl.SetItemText(nIndex, 1, fEntry.first);//Function name

				lpszText.Format(_T("0x%X"), *fEntry.second);
				m_CListCtrl.SetItemText(nIndex, 2, lpszText);//Function address
			}
		}
		if (ImportEntry.second.lstExportByOrdinal.size())
		{
			for (auto &fEntry : ImportEntry.second.lstExportByOrdinal)
			{
				int nIndex = m_CListCtrl.InsertItem(0, ImportEntry.first);

				lpszText.Format(_T("%d"), fEntry.first);
				m_CListCtrl.SetItemText(nIndex, 1, lpszText);//Function ordinal

				lpszText.Format(_T("0x%X"), *fEntry.second);
				m_CListCtrl.SetItemText(nIndex, 2, lpszText);//Function address
			}
		}
	}
}


BOOL CHookingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("WinFactory.dll"));
	GetDlgItem(IDC_EDIT3)->SetWindowText(_T("FunctionNeedToHook"));
	m_hooking_status = HOOK;
	Util::TransverseImportDirectory(m_MapImportFunction);
	LoadListControlData();
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
		Util::HookFunction(pszHookModName.GetBuffer(), pszFunctionName.GetBuffer(), (PROC*)&FunctionHooked);
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
