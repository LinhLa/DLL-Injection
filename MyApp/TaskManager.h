#pragma once
#include "afxcmn.h"
#include "Util.h"

class CTaskManager : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskManager)

public:
	CTaskManager(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTaskManager();

// Dialog Data
	enum { IDD = IDD_TASK_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	std::vector<PROCESSENTRY32> m_LstProcess;
	void LoadListControlData();
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_CListCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
};
