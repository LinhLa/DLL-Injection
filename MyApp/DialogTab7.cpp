// DialogTab7.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab7.h"
#include "afxdialogex.h"
#include "Util.h"

// CDialogTab7 dialog

IMPLEMENT_DYNAMIC(CDialogTab7, CDialogEx)

CDialogTab7::CDialogTab7(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB7, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB7, this);
}

CDialogTab7::~CDialogTab7()
{
}

void CDialogTab7::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab7, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab7 message handlers


void CDialogTab7::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
}
