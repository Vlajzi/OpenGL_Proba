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
	float light_position[4];
	float angleX = 0;
	float angleY = 0;
	float angleZ = 0;
	float linel;
	UINT  texZid;

	CGLRenderer();
	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void DestroyScene(CDC* pDC);
	void Reshape(CDC* pDC,int w,int h);
	void DrawScene(CDC* pDC);
	void DrawTest(CDC* pDC);
	void DrawCube(float size, Colorf boja, int det, bool svetlo);
	void StetColorMaterial(float r, float g, float b, bool emisija = false, float re = 0.2f, float ge = 0.6f, float be = 0.2f);
	void DrawCoun(float x, float y, float z, Colorf Boja, bool materijal = true, bool linije = false,int fine = 20);
	void DrawPoilgon2D(std::vector<Point>, float y, bool tekstura = false, float poz1 = 0, float poz2 = 0);
	void DrawPoilgon2D_2(std::vector<Point>, float y, bool tekstura = false, float poz1 = 0, float poz2 = 0);
	std::vector<Point> OdrediPoligon(float size, int n);
	//void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);
	static void myShadowMatrix(float ground[4], float light[4]);
	void DrawProba(CDC* pDC);
	void DrawObject(Colorf boja, Colorf boja2,Colorf mix, bool svetlo = true);
	void DrawFlore(Colorf boja);
	void DrawWall(Colorf boja, int angle, int side);
	void DrawSphere(float radius, Colorf Boja, bool svetlo,bool emisija = false, int sector = 32, int stack = 16);
	UINT LoadTexture(char* fileName);
};