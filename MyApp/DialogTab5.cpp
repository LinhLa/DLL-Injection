// DialogTab5.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab5.h"
#include "afxdialogex.h"
#include "Util.h"

// CDialogTab5 dialog

IMPLEMENT_DYNAMIC(CDialogTab5, CDialogEx)

CDialogTab5::CDialogTab5(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB5, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB5, this);
}

CDialogTab5::~CDialogTab5()
{
}

void CDialogTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab5, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab5 message handlers


void CDialogTab5::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialogEx::PostNcDestroy();
}
