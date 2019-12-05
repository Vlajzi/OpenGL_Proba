
// OpenGL_ProbaView.h : interface of the COpenGLProbaView class
//

#pragma once


class COpenGLProbaView : public CView
{
protected: // create from serialization only
	COpenGLProbaView() noexcept;
	DECLARE_DYNCREATE(COpenGLProbaView)

// Attributes
public:
	CGLRenderer m_gLRenderer;
	//TeaPot test;
	COpenGLProbaDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~COpenGLProbaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in OpenGL_ProbaView.cpp
inline COpenGLProbaDoc* COpenGLProbaView::GetDocument() const
   { return reinterpret_cast<COpenGLProbaDoc*>(m_pDocument); }
#endif

