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
	: CDialogEx(IDD_DIALOG_TAB4, pParent), m_hThreadArray{NULL}
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB4, this);
	m_DataArray[0].m_pIDCArray = { IDC_COMBO1,IDC_COMBO5,IDC_COMBO6,IDC_COMBO7,IDC_COMBO8,IDC_COMBO9,IDC_COMBO10 };
	m_DataArray[1].m_pIDCArray = { IDC_COMBO11,IDC_COMBO12,IDC_COMBO13,IDC_COMBO14,IDC_COMBO15,IDC_COMBO16,IDC_COMBO17 };
	m_DataArray[2].m_pIDCArray = { IDC_COMBO18,IDC_COMBO19,IDC_COMBO20,IDC_COMBO21,IDC_COMBO22,IDC_COMBO23,IDC_COMBO24 };
	m_DataArray[3].m_pIDCArray = { IDC_COMBO25,IDC_COMBO26,IDC_COMBO27,IDC_COMBO28,IDC_COMBO29,IDC_COMBO30,IDC_COMBO31 };
	m_DataArray[0].m_pCWnd = m_DataArray[1].m_pCWnd =m_DataArray[2].m_pCWnd = m_DataArray[3].m_pCWnd = this;
}

CDialogTab4::~CDialogTab4()
{
	// Close all thread handles
	//for(int i = 0; i < MAX_THREAD; ++i)
	//{
	//	if (m_hThreadArray[i] != NULL)
	//	{
	//		CloseHandle(m_hThreadArray[i]);
	//		m_hThreadArray[i] = NULL;
	//	}
	//}
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
	for (int i = 0; i < MAX_THREAD; i++)
	{
		// Create the thread to begin execution on its own.
		m_hThreadArray[i] = AfxBeginThread(
			CDialogTab4::InitComboItem,		// thread function name
			(LPVOID)&m_DataArray[i]);		// argument to thread function
	}
	//DWORD dwRet = MsgWaitForMultipleObjects(
	//	MAX_THREAD,         // number of objects in array
	//	m_hThreadArray,     // array of objects
	//	TRUE,				// wait for any object
	//	INFINITE,			// INFINITE-second wait
	//	0);					// Not use WakeMask
	//OutputDebugStringW(_T("Thread exit..."));
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


UINT  CDialogTab4::InitComboItem(LPVOID data)
{
	MYDATA *myData = (MYDATA*)data;
	for (auto &IDC : myData->m_pIDCArray)
	{
		CString lpszValue;
		USHORT uIndex = 0;
		CComboBox *pItem = (CComboBox*)myData->m_pCWnd->GetDlgItem(IDC);
		for (int iValue = MIN; iValue <= MAX; ++iValue)
		{
			lpszValue.Format((iValue > 0) ? _T("+%d") : _T("%d"), iValue);
			pItem->InsertString(uIndex++, lpszValue);
		}
		pItem->SelectString(0, VALUE_RESET);
	}
	return TRUE;
}