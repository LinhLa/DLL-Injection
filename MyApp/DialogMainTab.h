#pragma once
#include <vector>
#include <map>
// CDialogMainTab dialog

class CDialogMainTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogMainTab)

public:
	CDialogMainTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMainTab();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	DWORD m_ModeActive;
	enum TAB_CONTROL_ITEM {
		SET1,
		SET2,
		SET3,
		SET4,
		SET5,
		SET6,
		SET7,
		SET8
	};
	struct TabItemInfo
	{
		TAB_CONTROL_ITEM SettingGroup;
		DWORD dwIDC;
		CString lpszTitle;
	};
	void InitDialogTab();
	void HideDialogTab();
	void ShowTab(DWORD Mode);
	DWORD TranslateDialogIndex(DWORD tabID);
	std::vector<CWnd*> m_DialogTab;
	std::map<DWORD, std::vector<TabItemInfo>> m_MapModeToControl;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
