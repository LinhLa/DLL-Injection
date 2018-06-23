#pragma once
#include "Util.h"
class CHookingDlg : public CDialogEx
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
	std::map<CString, THUNK_DATA_ENTRY> m_MapImportFunction;
	void SetComboFunction();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancle();
	afx_msg void OnCbnSelchangeCombo1();
};

void FunctionHooked();

