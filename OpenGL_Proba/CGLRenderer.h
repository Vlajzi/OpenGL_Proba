#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>

#define X 0
#define Y 1
#define Z 2
#define W 3



typedef struct color3f
{
	float r;
	float g;
	float b;
}Colorf;



typedef struct point
{
	float x;
	float y;


}Point;

class CGLRenderer
{
  
	


protected:
	HGLRC m_hrc;
	
	//TeaPot tp;
public:

	float angleX = 0;
	float angleY = 0;
	float angleZ = 0;
	float linel;


	CGLRenderer();
	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void DestroyScene(CDC* pDC);
	void Reshape(CDC* pDC,int w,int h);
	void DrawScene(CDC* pDC);
	void DrawTest(CDC* pDC);
	void DrawCube(float size, Colorf boja, int det);
	void StetColorMaterial(float r, float g, float b, bool emisija = false, float re = 0.2f, float ge = 0.6f, float be = 0.2f);
	void DrawCoun(float x, float y, float z, Colorf Boja, int fine = 20);
	void DrawPoilgon2D(std::vector<Point>, float y, float poz1 = 0, float poz2 = 0);
	std::vector<Point> OdrediPoligon(float size, int n);
	void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);
};