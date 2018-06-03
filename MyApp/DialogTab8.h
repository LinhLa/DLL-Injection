#pragma once


// CDialogTab8 dialog

class CDialogTab8 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab8)

public:
	CDialogTab8(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab8();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
