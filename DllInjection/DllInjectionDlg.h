#pragma once
#include "DllInject.h"
#include "ListControl.h"
#include "afxcmn.h"

// CDllInjectionDlg dialog
class CDllInjectionDlg : public CDialogEx, public Util::DllInject, public Util::CListControlHMODULE
{
// Construction
public:
	CDllInjectionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLLINJECTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_CListCtrl;
};
