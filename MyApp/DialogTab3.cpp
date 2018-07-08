// DialogTab3.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab3.h"
#include "afxdialogex.h"
#include "Util.h"

// CDialogTab3 dialog

IMPLEMENT_DYNAMIC(CDialogTab3, CDialogEx)

CDialogTab3::CDialogTab3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB3, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB3, this);
}

CDialogTab3::~CDialogTab3()
{
}

void CDialogTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab3, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab3 message handlers


void CDialogTab3::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
}
