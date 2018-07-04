#include "stdafx.h"
#include "ListControlIAT.h"

#define FUNCTION_NAME		_T("Function name/Ordinal")
#define FUNCTION_ADDRESS	_T("Function address")
#define MODULE_NAME			_T("Module name")

#define LIST_CONTROL_STYLE	(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE)

namespace Util
{

	CListControlIAT::CListControlIAT(CListCtrl *pListControl) :m_pListControl(pListControl)
	{
	}

	CListControlIAT::~CListControlIAT()
	{
	}

	void CListControlIAT::InitListControl()
	{
		m_pListControl->SetExtendedStyle(LIST_CONTROL_STYLE);
		RECT lstCtrlRect;
		m_pListControl->GetWindowRect(&lstCtrlRect);
		m_pListControl->InsertColumn(
			0,              // Rank/order of item
			MODULE_NAME,    // Caption for this header
			LVCFMT_LEFT,    // Relative position of items under header
			(lstCtrlRect.right - lstCtrlRect.left) / 4);// Width of items under header

		m_pListControl->InsertColumn(1, FUNCTION_NAME, LVCFMT_LEFT, (lstCtrlRect.right - lstCtrlRect.left) / 2);
		m_pListControl->InsertColumn(2, FUNCTION_ADDRESS, LVCFMT_LEFT, (lstCtrlRect.right - lstCtrlRect.left) / 4);

	}

	void CListControlIAT::LoadMapImportFunction(const TCHAR* lpszModuleName, DWORD dwPID, bool IsOtherProcess)
	{
		m_MapImportFunction.clear();
		IsOtherProcess ?
			Util::TransverseImportDirectoryEx(m_MapImportFunction, lpszModuleName, dwPID) :
			Util::TransverseImportDirectory(m_MapImportFunction, lpszModuleName);
	}

	void CListControlIAT::LoadListControlData()
	{
		m_pListControl->DeleteAllItems();
		for (auto &ImportEntry : m_MapImportFunction)
		{
			CString lpszText;
			/*Transverse list function export by name*/
			if (ImportEntry.second.lstExportByName.size())
			{
				for (auto &fEntry : ImportEntry.second.lstExportByName)
				{
					int nIndex = m_pListControl->InsertItem(0, ImportEntry.first);
					m_pListControl->SetItemText(nIndex, 1, fEntry.first);//Function name

					lpszText.Format(_T("0x%x"), fEntry.second);
					m_pListControl->SetItemText(nIndex, 2, lpszText);//Function address
				}
			}
			/*Transverse list function export by ordinal*/
			if (ImportEntry.second.lstExportByOrdinal.size())
			{
				for (auto &fEntry : ImportEntry.second.lstExportByOrdinal)
				{
					int nIndex = m_pListControl->InsertItem(0, ImportEntry.first);

					lpszText.Format(_T("%d"), fEntry.first);
					m_pListControl->SetItemText(nIndex, 1, lpszText);//Function ordinal

					lpszText.Format(_T("0x%x"), fEntry.second);
					m_pListControl->SetItemText(nIndex, 2, lpszText);//Function address
				}
			}
		}
	}

}
