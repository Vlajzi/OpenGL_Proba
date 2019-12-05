#include "pch.h"
#include "CGLView.h"
#include "OpenGL_ProbaDoc.h"




BEGIN_MESSAGE_MAP(CGLView, CView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()





bool CGLView::OnEraseBkgn(CDC* pDC)
{
	return true;
}

int CGLView::OnCreate(LPCREATESTRUCT bCreateStruct)
{

	if (CView::OnCreate(bCreateStruct) == -1)
	{
		return -1;
	}
	CDC* pDC = GetDC();
	m_gLRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void CGLView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_gLRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

void CGLView::OnDraw(CDC* pDC)
{

	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_gLRenderer.DrawScene(pDC);
}

void CGLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_gLRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}

void CGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_gLRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}
