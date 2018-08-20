// ReadShareMemory.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "ReadShareMemory.h"
#include "afxdialogex.h"
#include "ShareMemoryMfc.h"

// CReadShareMemory dialog

IMPLEMENT_DYNAMIC(CReadShareMemory, CDialogEx)

CReadShareMemory::CReadShareMemory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READ_SHARE_MEMORY, pParent)
{

}

CReadShareMemory::~CReadShareMemory()
{
}

void CReadShareMemory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReadShareMemory, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON1, &CReadShareMemory::OnReadShareMemory)
END_MESSAGE_MAP()


// CReadShareMemory message handlers


void CReadShareMemory::OnReadShareMemory()
{
	TCHAR lpszText[256] = _T("");
	GetSharedMem(lpszText, 255);
	SetDlgItemText(IDC_EDIT1, lpszText);
}
