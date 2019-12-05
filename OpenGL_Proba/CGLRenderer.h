#pragma once


class CGLRenderer
{
  
	


protected:
	HGLRC m_hrc;
	
	//TeaPot tp;
public:

	float angleX = 0;
	float angleY = 0;
	float angleZ = 0;

	CGLRenderer();
	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void DestroyScene(CDC* pDC);
	void Reshape(CDC* pDC,int w,int h);
	void DrawScene(CDC* pDC);

};