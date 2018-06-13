#pragma once
#include <map>
#include <functional>
enum CITEM_TYPE : unsigned int {
	INDEX = 0,
	INTEGER,
	FLOAT_POINT
};
namespace Util {
	struct CItem {
		void* m_data;
		CITEM_TYPE m_type;
		CString m_format;
		CString m_regex_match;
		CString m_regex_replace;
		int m_Min;
		int m_Max;
		int m_Step;
	};

	void SetIndexItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError);
	void SetValueItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError);
	void SetValueCombobox(CWnd* dlg, std::map<int, Util::CItem > &MapComboItem, std::function<void()> &notifyError);

	void InitValueItemCombobox(CWnd* dlg, std::map<int, Util::CItem > &MapComboItem, std::function<void()> notifyError);

	void UpdateIndexItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError);
	void UpdateValueItemCombobox(CWnd* dlg, std::pair<const int, Util::CItem > &ComboItem, std::function<void()> &notifyError);
	void UpdateCombobox(CWnd* dlg, int IDC, std::map<int, Util::CItem > &MapComboItem, std::function<void()> &notifyError);
}