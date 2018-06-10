#pragma once
#include "afxwin.h"
#include "Util.h"
#include "HandleComboboxItem.h"
// CTestCbxWithRegex dialog

class CTestCbxWithRegex : public CDialogEx
{
	DECLARE_DYNAMIC(CTestCbxWithRegex)

public:
	CTestCbxWithRegex(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestCbxWithRegex();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMBOBOX_REGEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchange();
	virtual BOOL OnInitDialog();
private:
	int m_data[3];
	std::map<int, Util::CItem > m_MapComboItem;
	void Reload();

};
