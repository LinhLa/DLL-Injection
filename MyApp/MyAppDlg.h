// MyAppDlg.h : header file
//

#pragma once
#include "Util.h"
// CMyAppDlg dialog
class CMyAppDlg : public CDialogEx
{
// Construction
public:
	CMyAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGen128Object();
	afx_msg void OnGen256Object();
	afx_msg void OnGen512Object();
	afx_msg void OnGen1024Object();
private:
	void UpdateStatic(CStringPtr myCstringArray[]);
};
