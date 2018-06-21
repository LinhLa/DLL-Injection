// DialogTab6.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab6.h"
#include "afxdialogex.h"
#include "Util.h"

// CDialogTab6 dialog

IMPLEMENT_DYNAMIC(CDialogTab6, CDialogEx)

CDialogTab6::CDialogTab6(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB6, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB6, this);
}

CDialogTab6::~CDialogTab6()
{
}

void CDialogTab6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab6, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab6 message handlers


void CDialogTab6::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	
	CDialogEx::PostNcDestroy();
}
