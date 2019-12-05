#include "pch.h"

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;


	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0)
	{
		return false;
	}

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult)
	{
		return false;
	}

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc)
	{
		return false;
	}

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//-------------------------------
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//-------------------------------
	wglMakeCurrent(NULL, NULL);
	

}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::Reshape(CDC* pDC,int w,int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
	{
		h = 1;
		w = 0;
	}
	gluPerspective(120, (GLsizei)w / (GLsizei)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	//----------------------------------
	gluLookAt(0, 0, 10, 0, 0, 5, 0, 1, 0);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	glClear(GL_COLOR_BUFFER_BIT);

	//glLoadIdentity();
	glLineWidth(2.0);
	glPointSize(10);
	glBegin(GL_POINTS);

	

	float x1, y1;
	x1 = 0;
	glColor3f(1.0, 0.0, 0.0);
		
		glVertex3f(0, 0, 5);
	

	
	glEnd();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}
