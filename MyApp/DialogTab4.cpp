// DialogTab4.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab4.h"
#include "afxdialogex.h"


// CDialogTab4 dialog

IMPLEMENT_DYNAMIC(CDialogTab4, CDialogEx)

CDialogTab4::CDialogTab4(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB4, pParent)
{

}

CDialogTab4::~CDialogTab4()
{
}

void CDialogTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab4, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab4 message handlers


void CDialogTab4::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialogEx::PostNcDestroy();
}
