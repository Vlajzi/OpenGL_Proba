
// OpenGL_ProbaView.cpp : implementation of the COpenGLProbaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL_Proba.h"
#endif

#include "OpenGL_ProbaDoc.h"
#include "OpenGL_ProbaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void Rotate(float &a, bool dir);
// COpenGLProbaView

IMPLEMENT_DYNCREATE(COpenGLProbaView, CView)

BEGIN_MESSAGE_MAP(COpenGLProbaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLProbaView construction/destruction

COpenGLProbaView::COpenGLProbaView() noexcept
{


}

COpenGLProbaView::~COpenGLProbaView()
{
}

BOOL COpenGLProbaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLProbaView drawing

void COpenGLProbaView::OnDraw(CDC* pDC)
{
	COpenGLProbaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_gLRenderer.DrawScene(pDC);

	// TODO: add draw code for native data here
}


// COpenGLProbaView printing

BOOL COpenGLProbaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLProbaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLProbaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGLProbaView diagnostics

#ifdef _DEBUG
void COpenGLProbaView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLProbaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLProbaDoc* COpenGLProbaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLProbaDoc)));
	return (COpenGLProbaDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLProbaView message handlers


void COpenGLProbaView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_gLRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

//dodato

int COpenGLProbaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_gLRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


BOOL COpenGLProbaView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}




void COpenGLProbaView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_gLRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


void COpenGLProbaView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_gLRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void COpenGLProbaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 'A':Rotate(m_gLRenderer.angleY, true); break;
	case 'D':Rotate(m_gLRenderer.angleY, false); break;
	case 'W':Rotate(m_gLRenderer.angleX, true); break;
	case 'S':Rotate(m_gLRenderer.angleX, false); break;
	case 'Q':Rotate(m_gLRenderer.angleZ, true); break;
	case 'E':Rotate(m_gLRenderer.angleZ, false); break;
	default:
		break;
	}
	
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void Rotate(float &a, bool dir)
{
	float angle = 360;
	float ch = 10;
	if (dir)
	{
		angle = -angle;
		ch = -ch;
	}

	if (a == angle)
	{
		a = 0;
	}
	else
	{
		a += ch;
	}
}

