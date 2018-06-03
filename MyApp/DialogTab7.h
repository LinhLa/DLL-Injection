#pragma once


// CDialogTab7 dialog

class CDialogTab7 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab7)

public:
	CDialogTab7(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab7();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
