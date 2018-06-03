// DialogTab1.cpp : implementation file
//

#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab1.h"
#include "afxdialogex.h"


// CDialogTab1 dialog

IMPLEMENT_DYNAMIC(CDialogTab1, CDialogEx)

CDialogTab1::CDialogTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB1, pParent)
{

}

CDialogTab1::~CDialogTab1()
{
}

void CDialogTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab1, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab1 message handlers

void CDialogTab1::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CDialogTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	return TRUE;
}
