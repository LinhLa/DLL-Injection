#pragma once
#include "stdafx.h"
#include "MyApp.h"

#include "DialogMainTab.h"
#include "DialogTab1.h"
#include "DialogTab2.h"
#include "DialogTab3.h"
#include "DialogTab4.h"
#include "DialogTab5.h"
#include "DialogTab6.h"
#include "DialogTab7.h"
#include "DialogTab8.h"
#include "afxdialogex.h"
#include "Util.h"

// CDialogMainTab dialog


IMPLEMENT_DYNAMIC(CDialogMainTab, CDialogEx)

CDialogMainTab::CDialogMainTab(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_DIALOG_TAB_MAIN, pParent), Util::GroupTabHandler<CDialogMainTab, CDialogEx>(&m_CTabCtrl, 8)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB_MAIN, this);

	m_DialogTab[FLOW1] = new CDialogTab1;
	m_DialogTab[FLOW2] = new CDialogTab2;
	m_DialogTab[FLOW3] = new CDialogTab3;
	m_DialogTab[FLOW4] = new CDialogTab4;
	m_DialogTab[CHE1] = new CDialogTab5;
	m_DialogTab[CHE2] = new CDialogTab6;
	m_DialogTab[CHE3] = new CDialogTab7;
	m_DialogTab[CHE4] = new CDialogTab8;

	m_MapModeToControl = std::map<Util::GroupID, std::vector<TAB_ITEM>>
	{
		{
			FLOW,
			{
				{ m_DialogTab[FLOW1], IDD_DIALOG_TAB1, _T("FLOW1") },
				{ m_DialogTab[FLOW2], IDD_DIALOG_TAB2, _T("FLOW2") },
				{ m_DialogTab[FLOW3], IDD_DIALOG_TAB3, _T("FLOW3") },
				{ m_DialogTab[FLOW4], IDD_DIALOG_TAB4, _T("FLOW4") }
			}
		},
		{
			CHE,
			{
				{ m_DialogTab[CHE1], IDD_DIALOG_TAB5, _T("CHE1") },
				{ m_DialogTab[CHE2], IDD_DIALOG_TAB6, _T("CHE2") },
				{ m_DialogTab[CHE3], IDD_DIALOG_TAB7, _T("CHE3") },
				{ m_DialogTab[CHE4], IDD_DIALOG_TAB8, _T("CHE4") }
			}
		}
	};
}

CDialogMainTab::~CDialogMainTab()
{
}

void CDialogMainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_CTabCtrl);
}

BEGIN_MESSAGE_MAP(CDialogMainTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogMainTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogMainTab::OnBnClickedButton2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDialogMainTab::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CDialogMainTab::OnTcnSelchangingTab1)
END_MESSAGE_MAP()

BOOL CDialogMainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitDialogTab();
	SwitchGroupTab(FLOW);
	return TRUE;
}


void CDialogMainTab::OnBnClickedButton1()
{
	// Flow Mode
	SwitchGroupTab(FLOW);
}

void CDialogMainTab::OnBnClickedButton2()
{
	// CHE Mode
	SwitchGroupTab(CHE);
}


void CDialogMainTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Even after change tab item --> show selected tab dialog
	*pResult = 0;
	GetDialogFromCurrentTab()->ShowWindow(SW_SHOW);
}


void CDialogMainTab::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Even during chagne tab item --> hide current tab dialog
	*pResult = 0;
	GetDialogFromCurrentTab()->ShowWindow(SW_HIDE);
}
