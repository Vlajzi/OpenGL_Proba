
// OpenGL_Proba.h : main header file for the OpenGL_Proba application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGLProbaApp:
// See OpenGL_Proba.cpp for the implementation of this class
//

class COpenGLProbaApp : public CWinApp
{
public:
	COpenGLProbaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLProbaApp theApp;
