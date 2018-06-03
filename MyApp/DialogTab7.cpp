// DialogTab7.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab7.h"
#include "afxdialogex.h"


// CDialogTab7 dialog

IMPLEMENT_DYNAMIC(CDialogTab7, CDialogEx)

CDialogTab7::CDialogTab7(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB7, pParent)
{

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
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialogEx::PostNcDestroy();
}
