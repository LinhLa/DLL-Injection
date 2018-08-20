
// ReadShareMemoryDlg.h : header file
//

#pragma once


// CReadShareMemoryDlg dialog
class CReadShareMemoryDlg : public CDialogEx
{
// Construction
public:
	CReadShareMemoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READSHAREMEMORY_DIALOG };
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
	afx_msg void OnShowShareMemory();
	afx_msg void OnBnClickedOk();
};
