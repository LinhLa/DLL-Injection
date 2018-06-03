#pragma once


// CDialogTab5 dialog

class CDialogTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab5)

public:
	CDialogTab5(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab5();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
