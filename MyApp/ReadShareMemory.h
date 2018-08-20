#pragma once
class CReadShareMemory : public CDialogEx
{
	DECLARE_DYNAMIC(CReadShareMemory)

public:
	CReadShareMemory(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReadShareMemory();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READ_SHARE_MEMORY};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReadShareMemory();
};
