#pragma once
#include "Util.h"
#include "afxcmn.h"
// CDialogMainTab dialog

class CDialogMainTab : public CDialogEx, public Util::GroupTabHandler<CDialogMainTab, CDialogEx>
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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CTabCtrl m_CTabCtrl;
	enum TAB_CONTROL_ITEM {
		FLOW1,
		FLOW2,
		FLOW3,
		FLOW4,
		CHE1,
		CHE2,
		CHE3,
		CHE4
	};
	enum MODE_ACTIVE {
		FLOW,
		CHE
	};
};
