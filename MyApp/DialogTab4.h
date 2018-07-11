#pragma once
#include "Util.h"
#include "HandleComboboxItem.h"
#define MAX_THREAD 4

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
	afx_msg void OnComboChanged();
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
private:
	int data[28];
	std::map<int, Util::CItem > m_MapIdcToItem;
public:
	afx_msg void OnBnClickedReset();
};
