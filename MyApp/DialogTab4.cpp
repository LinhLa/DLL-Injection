// DialogTab4.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab4.h"
#include "afxdialogex.h"
#define MIN -100
#define MAX 100
#define VALUE_RESET _T("0")
IMPLEMENT_DYNAMIC(CDialogTab4, CDialogEx)

CDialogTab4::CDialogTab4(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB4, pParent)
{
}

CDialogTab4::~CDialogTab4()
{

}

void CDialogTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab4, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO7, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO8, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO9, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO10, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO11, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO12, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO13, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO14, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO15, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO16, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO17, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO18, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO19, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO20, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO21, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO22, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO23, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO24, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO25, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO26, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO27, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO28, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO29, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO30, &CDialogTab4::OnComboChanged)
	ON_CBN_SELCHANGE(IDC_COMBO31, &CDialogTab4::OnComboChanged)

	ON_BN_CLICKED(IDC_BUTTON1, &CDialogTab4::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogTab4::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogTab4::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogTab4::OnBnClickedReset)
END_MESSAGE_MAP()

void CDialogTab4::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
}


BOOL CDialogTab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_MapIdcToItem = std::map<int, Util::CItem >
	{
		{ IDC_COMBO1,{ &data[0], INTEGER } },
		{ IDC_COMBO5,{ &data[1], INTEGER } },
		{ IDC_COMBO6,{ &data[2], INTEGER } },
		{ IDC_COMBO7,{ &data[3], INTEGER } },
		{ IDC_COMBO8,{ &data[4], INTEGER } },
		{ IDC_COMBO9,{ &data[5], INTEGER } },
		{ IDC_COMBO10,{ &data[6], INTEGER } },
		{ IDC_COMBO11,{ &data[7], INTEGER } },
		{ IDC_COMBO12,{ &data[8], INTEGER } },
		{ IDC_COMBO13,{ &data[9], INTEGER } },
		{ IDC_COMBO14,{ &data[10], INTEGER } },
		{ IDC_COMBO15,{ &data[11], INTEGER } },
		{ IDC_COMBO16,{ &data[12], INTEGER } },
		{ IDC_COMBO17,{ &data[13], INTEGER } },
		{ IDC_COMBO18,{ &data[14], INTEGER } },
		{ IDC_COMBO19,{ &data[15], INTEGER } },
		{ IDC_COMBO20,{ &data[16], INTEGER } },
		{ IDC_COMBO21,{ &data[17], INTEGER } },
		{ IDC_COMBO22,{ &data[18], INTEGER } },
		{ IDC_COMBO23,{ &data[19], INTEGER } },
		{ IDC_COMBO24,{ &data[20], INTEGER } },
		{ IDC_COMBO25,{ &data[21], INTEGER } },
		{ IDC_COMBO26,{ &data[22], INTEGER } },
		{ IDC_COMBO27,{ &data[23], INTEGER } },
		{ IDC_COMBO28,{ &data[24], INTEGER } },
		{ IDC_COMBO29,{ &data[25], INTEGER } },
		{ IDC_COMBO30,{ &data[26], INTEGER } },
		{ IDC_COMBO31,{ &data[27], INTEGER } }
	};

	/*Init value combobox*/
	for (auto &item : m_MapIdcToItem)
	{
		CString lpszValue;
		USHORT uIndex = 0;
		CComboBox *pItem = (CComboBox*)GetDlgItem(item.first);
		pItem->SetRedraw(FALSE);
		pItem->InitStorage(MAX - MIN + 1, 16);
		for (int iValue = MIN; iValue <= MAX; ++iValue)
		{
			lpszValue.Format((iValue > 0) ? _T("+%d") : _T("%d"), iValue);
			pItem->InsertString(uIndex++, lpszValue);
		}
		pItem->SelectString(0, VALUE_RESET);
		pItem->SetRedraw(TRUE);
		pItem->Invalidate(TRUE);
	}
	return TRUE;
}

void CDialogTab4::OnComboChanged()
{
	CString lpszNotify;
	lpszNotify.Format(_T("Error on update item %d"), LOWORD(CWnd::GetCurrentMessage()->wParam));
	std::function<void()> notifyError = [&]() {AfxMessageBox(lpszNotify); };
	Util::UpdateCombobox(this, LOWORD(CWnd::GetCurrentMessage()->wParam), m_MapIdcToItem, notifyError);
}

void CDialogTab4::OnBnClickedReset()
{
	std::function<void(const DWORD&)> ResetValueCombobox = [&](const DWORD &IDC)
	{
		CComboBox *pItem = (CComboBox*)GetDlgItem(IDC);
		pItem->SelectString(0, VALUE_RESET);
		PostMessage(WM_COMMAND, MAKEWPARAM(IDC, CBN_SELCHANGE), reinterpret_cast<LPARAM>(pItem->m_hWnd));
	};
	switch (LOWORD(CWnd::GetCurrentMessage()->wParam))
	{
	case IDC_BUTTON1:
		for (auto &IDC : { IDC_COMBO1 ,IDC_COMBO8, IDC_COMBO12, IDC_COMBO16, IDC_COMBO20, IDC_COMBO24, IDC_COMBO28 })
		{
			ResetValueCombobox(IDC);
		}
		break;
	case IDC_BUTTON2:
		for (auto &IDC : { IDC_COMBO1, IDC_COMBO8, IDC_COMBO12, IDC_COMBO16, IDC_COMBO20, IDC_COMBO24, IDC_COMBO28 })
		{
			ResetValueCombobox(IDC);
		}
		break;
	case IDC_BUTTON3:
		for (auto &IDC : { IDC_COMBO1, IDC_COMBO8, IDC_COMBO12, IDC_COMBO16, IDC_COMBO20, IDC_COMBO24, IDC_COMBO28 })
		{
			ResetValueCombobox(IDC);
		}
		break;
	case IDC_BUTTON4:
		for (auto &IDC : { IDC_COMBO1, IDC_COMBO8, IDC_COMBO12, IDC_COMBO16, IDC_COMBO20, IDC_COMBO24, IDC_COMBO28 })
		{
			ResetValueCombobox(IDC);
		}
		break;
	default:
		break;
	}
}
