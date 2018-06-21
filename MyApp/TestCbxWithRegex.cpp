// TestCbxWithRegex.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "TestCbxWithRegex.h"
#include "Util.h"
#include "afxdialogex.h"

#define DEFAULT_FORMAT	 _T("%d")
#define	DEGREE_FORMAT	_T("%d\u02DA")
#define	PERCENT_FORMAT	_T("%d%%")
#define	MESURE_FORMAT	_T("%d cmm")
#define SECOND_FORMAT	_T("%.1fs")

#define	DEGREE_REGEX	_T("[0-9]{1,2}\u02DA")
#define	PERCENT_REGEX	_T("[0-9]{1,2}%")
#define	MESURE_REGEX	_T("[0-9]{1,2} cmm")

#define DEFAULT_REPLACE _T("")
#define	NOT_NUM_REPLACE	_T("[^-0-9]")
#define NOT_FLOAT_NUM_REPLACE _T("[^-0-9.]")

#define MAX 90
#define MIN 0
// CTestCbxWithRegex dialog

IMPLEMENT_DYNAMIC(CTestCbxWithRegex, CDialogEx)

CTestCbxWithRegex::CTestCbxWithRegex(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMBOBOX_REGEX, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_COMBOBOX_REGEX, this);
	m_data[0] = 2;
	m_data[1] = 20;
	m_data[2] = 30;
	m_MapComboItem = std::map<int, Util::CItem >
	{
		{ IDC_COMBO1, { &m_data[0], CITEM_TYPE::INDEX, DEGREE_FORMAT, DEGREE_REGEX, NOT_NUM_REPLACE, MIN, MAX, 5 } },
		{ IDC_COMBO2, { &m_data[1], CITEM_TYPE::INTEGER, PERCENT_FORMAT, PERCENT_REGEX, NOT_NUM_REPLACE, MIN, MAX, 5 } },
		{ IDC_COMBO3, { &m_data[2], CITEM_TYPE::INTEGER, MESURE_FORMAT, MESURE_REGEX, NOT_NUM_REPLACE, MIN, MAX, 5 } }
	};
}

CTestCbxWithRegex::~CTestCbxWithRegex()
{
}

void CTestCbxWithRegex::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, m_Combobox);
}


BEGIN_MESSAGE_MAP(CTestCbxWithRegex, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTestCbxWithRegex::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTestCbxWithRegex::OnCbnSelchange)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTestCbxWithRegex::OnCbnSelchange)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTestCbxWithRegex::OnCbnSelchange)
END_MESSAGE_MAP()


void CTestCbxWithRegex::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


BOOL CTestCbxWithRegex::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*init value combobox*/
	std::function<void()> OnInitNotify = [&]() {AfxMessageBox(_T("Not Match Regex when init value"), 0, 0); };
	Util::InitValueItemCombobox(this, m_MapComboItem, OnInitNotify);
	/*Set default value*/
	std::function<void()> OnSetNotify = [&]() {AfxMessageBox(_T("Not Match Regex when load default value"), 0, 0); };
	Util::SetValueCombobox(this, m_MapComboItem, OnSetNotify);

	Reload();
	return TRUE;
}


void CTestCbxWithRegex::OnCbnSelchange()
{
	/*Update value*/
	std::function<void()> OnUpdateNotify = [&]() {AfxMessageBox(_T("Not Match Regex when update value"), 0, 0); };
	Util::UpdateCombobox(this, LOWORD(GetCurrentMessage()->wParam), m_MapComboItem, OnUpdateNotify);
	Reload();
}

void CTestCbxWithRegex::Reload()
{
	CString text;
	USHORT uIndex = 0;
	for (auto &idc : { IDC_ITEM_1 , IDC_ITEM_2, IDC_ITEM_3 })
	{
		text.Format(_T("%d"), m_data[uIndex++]);
		GetDlgItem(idc)->SetWindowText(text);
	}
}