#pragma once
#include "afxwin.h"

class CMyEdit :public CEdit
{
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

class CDialogTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab1)

public:
	CDialogTab1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogTab1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB1};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	CMyEdit m_CEdit;
	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	HACCEL m_hAccel;
public:
	afx_msg void OnBnClickedNum1();
};
