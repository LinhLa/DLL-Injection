
// CMyAppView.h : interface of the CCMyAppView class
//

#pragma once


class CCMyAppView : public CView
{
protected: // create from serialization only
	CCMyAppView();
	DECLARE_DYNCREATE(CCMyAppView)

// Attributes
public:
	CCMyAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CCMyAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CMyAppView.cpp
inline CCMyAppDoc* CCMyAppView::GetDocument() const
   { return reinterpret_cast<CCMyAppDoc*>(m_pDocument); }
#endif

