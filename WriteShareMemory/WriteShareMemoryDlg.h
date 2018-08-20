
// WriteShareMemoryDlg.h : header file
//

#pragma once


// CWriteShareMemoryDlg dialog
class CWriteShareMemoryDlg : public CDialogEx
{
// Construction
public:
	CWriteShareMemoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WRITESHAREMEMORY_DIALOG };
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
	afx_msg void OnWriteShareMemory();
};
