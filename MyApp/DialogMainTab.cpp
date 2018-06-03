// DialogMainTab.cpp : implementation file
//
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
	: CDialogEx(IDD_DIALOG_TAB_MAIN, pParent), m_DialogTab(8)
{
	m_DialogTab[SET1] = new CDialogTab1;
	m_DialogTab[SET2] = new CDialogTab2;
	m_DialogTab[SET3] = new CDialogTab3;
	m_DialogTab[SET4] = new CDialogTab4;
	m_DialogTab[SET5] = new CDialogTab5;
	m_DialogTab[SET6] = new CDialogTab6;
	m_DialogTab[SET7] = new CDialogTab7;
	m_DialogTab[SET8] = new CDialogTab8;
	
	m_MapModeToControl =
	{
		{
			IDC_BUTTON1,
			{
				{ SET1, IDD_DIALOG_TAB1 , _T("SET1") },
				{ SET2, IDD_DIALOG_TAB2 , _T("SET2") },
				{ SET3, IDD_DIALOG_TAB3 , _T("SET3") },
				{ SET4, IDD_DIALOG_TAB4 , _T("SET4") }
			}
		},
		{
			IDC_BUTTON2,
			{
				{ SET5, IDD_DIALOG_TAB5 , _T("SET5") },
				{ SET6, IDD_DIALOG_TAB6 , _T("SET6") },
				{ SET7, IDD_DIALOG_TAB7 , _T("SET7") },
				{ SET8, IDD_DIALOG_TAB8 , _T("SET8") }
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
}

BEGIN_MESSAGE_MAP(CDialogMainTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogMainTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogMainTab::OnBnClickedButton2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDialogMainTab::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CDialogMainTab::OnTcnSelchangingTab1)
END_MESSAGE_MAP()

void CDialogMainTab::InitDialogTab()
{
	CTabCtrl *pTabCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	for (auto &mode : m_MapModeToControl)
	{
		for (auto &tabItemInfo : mode.second)
		{
			((CDialogEx*)m_DialogTab[tabItemInfo.SettingGroup])->Create(tabItemInfo.dwIDC, pTabCtrl);
		}
	}
}

void CDialogMainTab::HideDialogTab()
{
	for (auto &dialog : m_DialogTab)
		dialog->ShowWindow(SW_HIDE);
}

void CDialogMainTab::ShowTab(DWORD Mode) 
{
	HideDialogTab();
	CTabCtrl *pTabCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	pTabCtrl->DeleteAllItems();

	DWORD tabID = 0;
	for(auto &tabItemInfo : m_MapModeToControl[Mode])
	{
		Util::InitItemTabControl(pTabCtrl, m_DialogTab[tabItemInfo.SettingGroup], tabID++, tabItemInfo.lpszTitle);
	}

	pTabCtrl->SetCurSel(0);
	m_DialogTab[TranslateDialogIndex(0)]->ShowWindow(SW_SHOW);
}

DWORD CDialogMainTab::TranslateDialogIndex(DWORD tabID)
{
	return m_MapModeToControl[m_ModeActive][tabID].SettingGroup;
}

BOOL CDialogMainTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitDialogTab();
	m_ModeActive = IDC_BUTTON1;
	ShowTab(IDC_BUTTON1);
	return TRUE;
}


void CDialogMainTab::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	m_ModeActive = IDC_BUTTON1;
	ShowTab(IDC_BUTTON1);
}

void CDialogMainTab::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	m_ModeActive = IDC_BUTTON2;
	ShowTab(IDC_BUTTON2);
}


void CDialogMainTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	DWORD tabIndex = ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetCurSel();
	m_DialogTab[TranslateDialogIndex(tabIndex)]->ShowWindow(SW_SHOW);
}


void CDialogMainTab::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	DWORD tabIndex = ((CTabCtrl*)GetDlgItem(IDC_TAB1))->GetCurSel();
	m_DialogTab[TranslateDialogIndex(tabIndex)]->ShowWindow(SW_HIDE);
}
