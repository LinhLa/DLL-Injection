#pragma once


// CRegrexCheckDlg dialog

class CRegrexCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegrexCheckDlg)

public:
	CRegrexCheckDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRegrexCheckDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGREX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
