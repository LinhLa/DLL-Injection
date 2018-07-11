#include "stdafx.h"
#include "UtilRegex.h"
#include "HandleComboboxItem.h"

namespace Util {

	CItem::CItem(int *data, CITEM_TYPE type, CString format, CString regex_match, CString regex_replace) :
	m_data(data), m_type(type), m_format(format), m_regex_match(regex_match), m_regex_replace(regex_replace)
	{}

	CItem::CItem(int *data, CITEM_TYPE type, CString format, CString regex_match, CString regex_replace, int min, int max, int step):
	m_data(data), m_type(type), m_format(format), m_regex_match(regex_match), m_regex_replace(regex_replace), m_Min(min), m_Max(max), m_Step(step)
	{}

	void SetIndexItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		int iResult = ((CComboBox*)dlg->GetDlgItem(ComboItem.first))->SetCurSel(*(int*)ComboItem.second.m_data);
		if (iResult == CB_ERR)
			notifyError();
	}

	void SetValueItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		CString text;
		switch (ComboItem.second.m_type)
		{
		case INTEGER:
			text.Format(ComboItem.second.m_format, *(int*)ComboItem.second.m_data);
			if (((CComboBox*)dlg->GetDlgItem(ComboItem.first))->SelectString(0, text) == CB_ERR)
				notifyError();
			break;
		case FLOAT_POINT:
			text.Format(ComboItem.second.m_format, *(double*)ComboItem.second.m_data);
			if (((CComboBox*)dlg->GetDlgItem(ComboItem.first))->SelectString(0, text) == CB_ERR)
				notifyError();
			break;
		default:
			notifyError();
			break;
		}
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
			case INTEGER:
			case FLOAT_POINT:
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
			for (int value = item.second.m_Min; value <= item.second.m_Max; value += item.second.m_Step)
			{
				text.Format(item.second.m_format, value);
				if (Util::IsMatchRegex<REGEX_POLICY::ECMA>(text, item.second.m_regex_match))
					((CComboBox*)dlg->GetDlgItem(item.first))->AddString(text);
				else
					notifyError();
			}
		}
	}

	void UpdateIndexItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		*(int*)ComboItem.second.m_data = ((CComboBox*)dlg->GetDlgItem(ComboItem.first))->GetCurSel();
	}

	void UpdateValueItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError)
	{
		CString text;
		(dlg->GetDlgItem(ComboItem.first))->GetWindowText(text);
		int iValue = 0;
		double dValue = 0.0;
		switch (ComboItem.second.m_type)
		{
			case INTEGER:
				iValue = _ttoi(Util::RegexReplace<REGEX_POLICY::ECMA>(text, ComboItem.second.m_regex_replace));
				(!iValue && errno == ERANGE) ? notifyError() : *(int*)ComboItem.second.m_data = iValue;
				break;
			case FLOAT_POINT:
				dValue = _ttof(Util::RegexReplace<REGEX_POLICY::ECMA>(text, ComboItem.second.m_regex_replace));
				(!dValue && errno == ERANGE) ? notifyError() : *(double*)ComboItem.second.m_data = dValue;
				break;
			default:
				notifyError();
				break;
		}
	}

	void UpdateCombobox(CWnd* dlg, int IDC, std::map<int, Util::CItem > &MapComboItem, std::function<void()> &notifyError)
	{
		auto itr = MapComboItem.find(IDC);
		if (itr != MapComboItem.end())
		{
			switch (itr->second.m_type)
			{
			case INDEX:
				UpdateIndexItemCombobox(dlg, *itr, notifyError);
				break;
			case INTEGER:
			case FLOAT_POINT:
				UpdateValueItemCombobox(dlg, *itr, notifyError);
				break;
			default:
				notifyError();
				break;
			}
			return;
		}
		else
			notifyError();
	}
}