// WriteShareMemory.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "WriteShareMemory.h"
#include "afxdialogex.h"
#include "ShareMemoryMfc.h"

// CWriteShareMemory dialog

IMPLEMENT_DYNAMIC(CWriteShareMemory, CDialogEx)

CWriteShareMemory::CWriteShareMemory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WRITE_SHARE_MEMORY, pParent)
{

}

CWriteShareMemory::~CWriteShareMemory()
{
}

void CWriteShareMemory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWriteShareMemory, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON1, &CWriteShareMemory::OnWriteShareMemory)
END_MESSAGE_MAP()


// CWriteShareMemory message handlers


void CWriteShareMemory::OnWriteShareMemory()
{
	TCHAR lpszText[256] = _T("");
	GetDlgItemText(IDC_EDIT1, lpszText, 255);
	SetSharedMem(lpszText);
}
