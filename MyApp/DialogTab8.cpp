// DialogTab8.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab8.h"
#include "afxdialogex.h"
#include "Util.h"

// CDialogTab8 dialog

IMPLEMENT_DYNAMIC(CDialogTab8, CDialogEx)

CDialogTab8::CDialogTab8(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB8, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB8, this);
}

CDialogTab8::~CDialogTab8()
{
}

void CDialogTab8::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab8, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab8 message handlers


void CDialogTab8::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialogEx::PostNcDestroy();
}
