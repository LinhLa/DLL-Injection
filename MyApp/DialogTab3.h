#pragma once


// CDialogTab3 dialog

class CDialogTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab3)

public:
	CDialogTab3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
