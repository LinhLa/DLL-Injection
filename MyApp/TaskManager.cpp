// TaskManager.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "TaskManager.h"
#include "afxdialogex.h"
#define PROCESS_NAME _T("Process name")
#define PROCESS_ID _T("PID")
#define PROCESS_THREAD_NO _T("ThreadNo")

IMPLEMENT_DYNAMIC(CTaskManager, CDialogEx)

CTaskManager::CTaskManager(CWnd* pParent /*=NULL*/)
: CDialogEx(CTaskManager::IDD, pParent)
{
	MyAppFactory::GetInstance()->Add(CTaskManager::IDD, this);
}

CTaskManager::~CTaskManager()
{
}

void CTaskManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CListCtrl);
}


BEGIN_MESSAGE_MAP(CTaskManager, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTaskManager::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CTaskManager::OnBnClickedOk)
END_MESSAGE_MAP()

void CTaskManager::LoadListControlData()
{
	m_CListCtrl.DeleteAllItems();
	CString lpszText;
	for (auto &item : m_LstProcess)
	{
		int nIndex = m_CListCtrl.InsertItem(0, item.szExeFile);

		lpszText.Format(_T("%d"), item.th32ProcessID);
		m_CListCtrl.SetItemText(nIndex, 1, lpszText);//PID

		lpszText.Format(_T("%d"), item.cntThreads);
		m_CListCtrl.SetItemText(nIndex, 2, lpszText);//ThreadNo
	}
}

BOOL CTaskManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_CListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE);
	RECT lstCtrlRect;
	m_CListCtrl.GetWindowRect(&lstCtrlRect);
	m_CListCtrl.InsertColumn(
		0,              // Rank/order of item
		PROCESS_NAME,    // Caption for this header
		LVCFMT_LEFT,    // Relative position of items under header
		(lstCtrlRect.right - lstCtrlRect.left) / 3);// Width of items under header

	m_CListCtrl.InsertColumn(1, PROCESS_ID, LVCFMT_LEFT, (lstCtrlRect.right - lstCtrlRect.left) / 3);
	m_CListCtrl.InsertColumn(2, PROCESS_THREAD_NO, LVCFMT_LEFT, (lstCtrlRect.right - lstCtrlRect.left) / 3);

	Util::FindProcess(m_LstProcess);
	LoadListControlData();

	return TRUE;
}


void CTaskManager::OnBnClickedButton1()
{
	POSITION pos = m_CListCtrl.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_CListCtrl.GetNextSelectedItem(pos);
		DWORD nPID = _ttoi(m_CListCtrl.GetItemText(nItem, 1).GetBuffer());
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, nPID);
		if (hProcess != INVALID_HANDLE_VALUE && TerminateProcess(hProcess, 0))
		{
			for (auto itr = m_LstProcess.begin(); itr != m_LstProcess.end(); ++itr)
			{
				if (itr->th32ProcessID == nPID)
				{
					m_LstProcess.erase(itr);
					break;
				}
			}
			m_CListCtrl.DeleteItem(nItem);
		}
	}
}


void CTaskManager::OnBnClickedOk()
{
	m_LstProcess.clear();
	Util::FindProcess(m_LstProcess);
	LoadListControlData();
}
