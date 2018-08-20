#pragma once
class CWriteShareMemory : public CDialogEx
{
	DECLARE_DYNAMIC(CWriteShareMemory)

public:
	CWriteShareMemory(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWriteShareMemory();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WRITE_SHARE_MEMORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWriteShareMemory();
};
