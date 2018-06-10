#include "stdafx.h"
#include "Util.h"
#include "HandleComboboxItem.h"


namespace Util {


	void SetIndexItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		((CComboBox*)dlg->GetDlgItem(ComboItem.first))->SetCurSel(*ComboItem.second.m_data);
	}

	void SetValueItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		CString text;
		text.Format(ComboItem.second.m_format, *ComboItem.second.m_data);
		CComboBox* pCComboBox = (CComboBox*)dlg->GetDlgItem(ComboItem.first);
		int curSel = pCComboBox->SelectString(0, text);
		if (Util::IsMatchRegrex<REGEX_POLICY::ECMA>(
			text.GetBuffer(),
			ComboItem.second.m_regex.GetBuffer()
			)
			&& curSel != -1)
		{
			pCComboBox->SetCurSel(curSel);
		}
		else
			notifyError();
	}

	void SetValueCombobox(CWnd* dlg, std::map<int, Util::CItem > &MapComboItem, std::function<void()> &notifyError)
	{
		for (auto &item : MapComboItem)
		{
			switch (item.second.m_type)
			{
			case INDEX:
				SetIndexItemCombobox(dlg, item, notifyError);
				break;
			case VALUE:
				SetValueItemCombobox(dlg, item, notifyError);
				break;
			default:
				break;
			}
		}
	}



	void InitValueItemCombobox(CWnd* dlg, std::map<int, Util::CItem > &MapComboItem, std::function<void()> notifyError)
	{
		CString text;
		for (auto &item : MapComboItem)
		{
			int index = 0;
			for (int value = item.second.m_Min; value <= item.second.m_Max; value += item.second.m_Step)
			{
				text.Format(item.second.m_format, value);
				if (Util::IsMatchRegrex<REGEX_POLICY::ECMA>(text.GetBuffer(), item.second.m_regex.GetBuffer()))
					((CComboBox*)dlg->GetDlgItem(item.first))->InsertString(index++, text);
				else
					notifyError();
			}
		}
	}

	void UpdateIndexItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		*ComboItem.second.m_data = ((CComboBox*)dlg->GetDlgItem(ComboItem.first))->GetCurSel();

	}
	void UpdateValueItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		CString target;
		(dlg->GetDlgItem(ComboItem.first))->GetWindowText(target);
		int value = _ttoi(RegrexReplace<ECMA_ICASE>(target.GetBuffer(), ComboItem.second.m_extract_regex));
		if (!value && errno == ERANGE)
			notifyError();
		else
			*ComboItem.second.m_data = value;
	}

	void UpdateCombobox(CWnd* dlg, int IDC, std::map<int, Util::CItem > &MapComboItem, std::function<void()> &notifyError)
	{
		auto itr = MapComboItem.find(IDC);
		if (itr!= MapComboItem.end())
		{
			switch (itr->second.m_type)
			{
			case INDEX:
				UpdateIndexItemCombobox(dlg, *itr, notifyError);
				break;
			case VALUE:
				UpdateValueItemCombobox(dlg, *itr, notifyError);
				break;
			default:
				break;
			}
		}
	}
}