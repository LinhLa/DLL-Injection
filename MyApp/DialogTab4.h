#pragma once


// CDialogTab4 dialog

class CDialogTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab4)

public:
	CDialogTab4(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab4();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
