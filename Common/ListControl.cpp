#include "stdafx.h"
#include "ListControl.h"

#define FUNCTION_NAME		_T("Function name/Ordinal")
#define FUNCTION_ADDRESS	_T("Function address")
#define MODULE_NAME			_T("Module name")
#define MODULE_SIZE			_T("size")
#define MODULE_PATH			_T("path")
#define MODULE_ADDR			_T("address")
namespace Util
{

	CListControl::CListControl(CListCtrl *pListControl, int HeaderNumber) :
		m_pListControl(pListControl),
		m_HeaderNumber(HeaderNumber),
		m_CurrentHeaderIndex(0)
	{}
	void CListControl::OnInitListControl(DWORD dwStyle)
	{
		m_pListControl->SetExtendedStyle(dwStyle);
		m_pListControl->GetWindowRect(&m_ListControlRect);
	}

	void CListControl::AddHeader(const TCHAR* lpszHeader, int ratio)
	{
		if (!lpszHeader || ratio == 0 || m_HeaderNumber <= m_CurrentHeaderIndex)
			return;

		m_pListControl->InsertColumn(
			m_CurrentHeaderIndex++,              // Rank/order of item
			lpszHeader,							// Caption for this header
			LVCFMT_LEFT,						// Relative position of items under header
			(m_ListControlRect.right - m_ListControlRect.left) / ratio);// Width of items under header
	}

	CListControlIAT::CListControlIAT(CListCtrl *pListControl, DWORD HeaderNumber) :
		CListControl(pListControl, HeaderNumber),
		m_bIsOtherProcess(FALSE),
		m_dwPID(0)
	{
	}

	void CListControlIAT::OnInitListControl(DWORD dwStyle)
	{
		CListControl::OnInitListControl(dwStyle);
		CListControl::AddHeader(MODULE_NAME, 4);
		CListControl::AddHeader(FUNCTION_NAME, 2);
		CListControl::AddHeader(FUNCTION_ADDRESS, 4);
	}

	void CListControlIAT::Set(const TCHAR* lpszModuleName, BOOL bIsOtherProcess, DWORD PID)
	{
		m_lpszModuleName = lpszModuleName;
		m_bIsOtherProcess = bIsOtherProcess;
		m_dwPID = PID;
	}

	void CListControlIAT::LoadMapImportFunction()
	{
		m_MapImportFunction.clear();
		m_bIsOtherProcess ?
			Util::TransverseImportDirectoryEx(m_MapImportFunction, m_lpszModuleName, m_dwPID) :
			Util::TransverseImportDirectory(m_MapImportFunction, m_lpszModuleName);
	}

	void CListControlIAT::LoadListControlData()
	{
		LoadMapImportFunction();

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

	CListControlHMODULE::CListControlHMODULE(CListCtrl *pListControl, DWORD HeaderNumber):
	CListControl(pListControl, HeaderNumber)
	{}

	void CListControlHMODULE::Set(DWORD PID)
	{
		m_dwPID = PID;
	}
	void CListControlHMODULE::LoadListControlData()
	{
		if (!FindProcessModule(m_dwPID, m_ListModuleEntry))
		{
			return;
		}

		m_pListControl->DeleteAllItems();
		for (auto &ModuleEntry : m_ListModuleEntry)
		{
			CString lpszText;
			int nIndex = m_pListControl->InsertItem(0, ModuleEntry.szModule);//Module name
			m_pListControl->SetItemText(nIndex, 1, ModuleEntry.szExePath);//Module path

			lpszText.Format(_T("0x%x"), ModuleEntry.modBaseAddr);//Base address
			m_pListControl->SetItemText(nIndex, 2, lpszText);

			lpszText.Format(_T("%d"), ModuleEntry.modBaseSize);//Module size
			m_pListControl->SetItemText(nIndex, 3, lpszText);
		}

	}
	void CListControlHMODULE::OnInitListControl(DWORD dwStyle)
	{
		CListControl::OnInitListControl(dwStyle);
		CListControl::AddHeader(MODULE_NAME, 4);
		CListControl::AddHeader(MODULE_PATH, 4);
		CListControl::AddHeader(MODULE_ADDR, 4);
		CListControl::AddHeader(MODULE_SIZE, 4);
	}

}
