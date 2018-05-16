
// CMyAppView.cpp : implementation of the CCMyAppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CMyApp.h"
#endif

#include "CMyAppDoc.h"
#include "CMyAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMyAppView

IMPLEMENT_DYNCREATE(CCMyAppView, CView)

BEGIN_MESSAGE_MAP(CCMyAppView, CView)
END_MESSAGE_MAP()

// CCMyAppView construction/destruction

CCMyAppView::CCMyAppView()
{
	// TODO: add construction code here

}

CCMyAppView::~CCMyAppView()
{
}

BOOL CCMyAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCMyAppView drawing

void CCMyAppView::OnDraw(CDC* /*pDC*/)
{
	CCMyAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCMyAppView diagnostics

#ifdef _DEBUG
void CCMyAppView::AssertValid() const
{
	CView::AssertValid();
}

void CCMyAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCMyAppDoc* CCMyAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCMyAppDoc)));
	return (CCMyAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CCMyAppView message handlers
