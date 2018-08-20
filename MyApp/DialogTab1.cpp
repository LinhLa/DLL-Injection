#include "stdafx.h"
#include "MyApp.h"
#include "DialogTab1.h"
#include "afxdialogex.h"
#include "Util.h"


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()


void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar < _T('0') || nChar > _T('9'))
	{
		//Discard character not number
		return;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

IMPLEMENT_DYNAMIC(CDialogTab1, CDialogEx)

CDialogTab1::CDialogTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB1, pParent)
{
	MyAppFactory::GetInstance()->Add(IDD_DIALOG_TAB1, this);
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
}

CDialogTab1::~CDialogTab1()
{
	MyAppFactory::GetInstance()->Remove(IDD_DIALOG_TAB1);
}

void CDialogTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_CEdit);
}


BEGIN_MESSAGE_MAP(CDialogTab1, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CDialogTab1::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogTab1::OnBnClickedNum1)
END_MESSAGE_MAP()


// CDialogTab1 message handlers

void CDialogTab1::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
}


BOOL CDialogTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_CEdit.SetFocus();
	return TRUE;
}


void CDialogTab1::OnEnChangeEdit1()
{

}


BOOL CDialogTab1::PreTranslateMessage(MSG* pMsg)
{
	if (m_hAccel != NULL)
	{
		if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
			return TRUE;
	}

	CWnd *pWnd = CWnd::GetFocus();
	if (pWnd && pWnd->m_hWnd == m_CEdit.m_hWnd)
	{
		DWORD keyCode = pMsg->wParam;
		if (pMsg->message == WM_KEYDOWN &&
			(keyCode == _T('/') || keyCode == _T('\\'))
			&&
			!(::GetKeyState(VK_SHIFT) & 0x8000)
			)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogTab1::OnBnClickedNum1()
{
	m_CEdit.PostMessageW(WM_KEYDOWN, _T('1'), 0);
}
