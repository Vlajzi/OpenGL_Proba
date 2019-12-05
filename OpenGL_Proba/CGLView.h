#pragma once
#include "pch.h"

class CGLView: public CView
{
protected:
	CGLRenderer m_gLRenderer;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg bool OnEraseBkgn(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT bCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType,int cx,int cy);

public:
	void OnDraw(CDC* pDC);
	void OnInitialUpdate();

};