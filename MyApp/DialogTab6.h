#pragma once


// CDialogTab6 dialog

class CDialogTab6 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab6)

public:
	CDialogTab6(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab6();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
