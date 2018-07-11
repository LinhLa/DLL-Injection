#pragma once
#include "ListControl.h"
#include "afxcmn.h"
class CHookingDlg : public CDialogEx, public Util::CListControlIAT
{
	DECLARE_DYNAMIC(CHookingDlg)

public:
	CHookingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHookingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOOKING_API };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	enum HOOK_BUTTON_STATUS {
		HOOK,
		CALL
	} m_hooking_status;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancle();
	CListCtrl m_CListCtrl;
};

void FunctionHooked();

