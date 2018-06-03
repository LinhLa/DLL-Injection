#pragma once


// CDialogTab2 dialog

class CDialogTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab2)

public:
	CDialogTab2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB2};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
