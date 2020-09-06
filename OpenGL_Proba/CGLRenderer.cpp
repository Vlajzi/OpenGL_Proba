#include "pch.h"




CGLRenderer::CGLRenderer()
{
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	
	linel = 0.04;
	light_position[0] = 2.0;
	light_position[1] = 2.0;
	light_position[2] = 2.0;
	light_position[3] = 1.0;


	
}

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
	pfd.cStencilBits = 32;
	pfd.cAccumBits = 32;
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	texZid = LoadTexture("res/clean-blue-wall-texture-background.jpg");
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
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
	glLoadIdentity();
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
	{
		h = 1;
	}
	gluPerspective(10, (GLsizei)w / (GLsizei)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	
	//----------------------------------
	//gluLookAt(5, 5, 5, 0, 0, 0, 0, 0, 0);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{

	wglMakeCurrent(pDC->m_hDC, m_hrc);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, -0.3, -12);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bool shadows = true;
	if(shadows)
	{
	
		glClear(GL_STENCIL_BUFFER_BIT);
		
	}

	bool light = true;
	if (light)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_NORMALIZE);
	}
	glEnable(GL_LIGHT0);
	float light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	float light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	//float light_position[] = { 2.0, 2.0, 2.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//start


	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glStencilMask(0xFF);

	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//glDepthMask(GL_FALSE);
	std::vector<Point> temena;

	temena.push_back({ -1,1 });
	temena.push_back({ 1,1 });
	temena.push_back({ 1,-1 });
	temena.push_back({ -1,-1 });

	//object
	DrawObject({ 1,0,0 }, {0,0,1}, { 1,1,1 });

	DrawFlore({ 1,1,1 });
	/*glRotatef(-90,1,0,0);
	glTranslatef(0, 1, 1);*/
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texZid);

	DrawWall({ 1,1,1 }, -90, 0);
	DrawWall({ 1,1,1 }, 90, 1);
	DrawWall({ 1,1,1 }, -90, 2);
	
	/*glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilMask(0x1);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glDepthMask(GL_FALSE);

	StetColorMaterial(0, 1, 0);
	glTranslatef(0.90, 1,0);
	glRotatef(-90, 0, 0, 1);
	DrawPoilgon2D(temena, 0.1);
	glPopMatrix();
	glPushMatrix();


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.001, 0);
	myShadowMatrix(test, light_position);
	glRotatef(-90, 0, 0, 1);
	glEnable(GL_STENCIL_TEST);
	//shadwos
	
	DrawObject(data, { 1,1,1 }, false);
	glDisable(GL_STENCIL_TEST);

	////////
	glTranslatef(-0.90, 1, 0);
	glRotatef(90, 0, 0, 1);
	DrawPoilgon2D(temena, 0.1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 1, -1.1);
	glRotatef(90, 1, 0, 0);
	DrawPoilgon2D(temena, 0.1);
	glPopMatrix();*/
	/*float* gh1 = (float*)malloc(sizeof(float)*400*3);
	glReadPixels(30, 30, 400, 1, GL_STENCIL_INDEX, GL_FLOAT, gh1);*/


	/*glStencilFunc(GL_EQUAL , 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glDepthMask(GL_TRUE);
	glPopMatrix();
	glPushMatrix();
	

	glScalef(1, -1, 1);
	DrawObject({ 1,1,0 }, { 0.5,0.3,0 });
	glDisable(GL_STENCIL_TEST);


	glPopMatrix();
	glTranslatef(0, 0.001, 0);
	float test[4] = {0,2,0,0};
	myShadowMatrix(test,light_position);

	glEnable(GL_STENCIL_TEST);
	//shadwos
	Colorf data = {0*0.2,1*0.2,0*0.2};
	DrawObject(data, { 1,1,1 }, false);
	glDisable(GL_STENCIL_TEST);
	*/
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
	//free(gh1);
}

void CGLRenderer::DrawTest(CDC* pDC)
{

	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, -0.3, -12);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texZid);
	//glNormal3f(-1, vt, temena[0].y);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0,1);

	//glNormal3f(temena[1].x, vt, temena[1].y);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0,1);

	//glNormal3f(temena[2].x, vt, temena[2].y);
	glTexCoord2f(1, 1);
	glVertex3f(1, 0,-1);

	//glNormal3f(temena[3].x, vt, temena[3].y);
	glTexCoord2f(0, 1);
	glVertex3f(-1,0,-1);
	glEnd();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}



void CGLRenderer::DrawCube(float size, Colorf boja, int det,bool svetlo)
{
	if (svetlo)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
	float side = size / 2;
	StetColorMaterial(boja.r, boja.g, boja.b);
	float poz = -size / 2;
	float stpd = size / det;
	float stp = size / det;
	float hg = 0;
	glBegin(GL_QUADS);
	for (int i = 0; i < det; i++)
	{
		for (int j = 0; j < det; j++)
		{


			glNormal3f(-1, 0, 0);
			glVertex3f(side, hg, poz);
			glVertex3f(side, hg + stp, poz);
			glVertex3f(side, hg + stp, poz + stp);
			glVertex3f(side, hg, poz + stp);

			glNormal3f(0, 0, -1);
			glVertex3f(poz, hg, side);
			glVertex3f(poz, hg + stp, side);
			glVertex3f(poz + stp, hg + stp, side);
			glVertex3f(poz + stp, hg, side);

			glNormal3f(1, 0, 0);
			glVertex3f(-side, hg, poz);
			glVertex3f(-side, hg + stp, poz);
			glVertex3f(-side, hg + stp, poz + stp);
			glVertex3f(-side, hg, poz + stp);

			glNormal3f(0, 0, 1);
			glVertex3f(poz, hg, -side);
			glVertex3f(poz, hg + stp, -side);
			glVertex3f(poz + stp, hg + stp, -side);
			glVertex3f(poz + stp, hg, -side);

			poz += stp;

		}
		poz = -side;
		hg += stp;
	}

	poz = -size / 2;
	side = -size / 2;
	hg = side;
	for (int i = 0; i < det; i++)
	{
		for (int j = 0; j < det; j++)
		{
			glNormal3f(0, 1, 0);
			glVertex3f(hg, 0, side);
			glVertex3f(hg, 0, side + stp);
			glVertex3f(hg + stp, 0, side + stp);
			glVertex3f(hg + stp, 0, side);


			side += stp;
		}
		side = poz;
		hg += stp;
	}

	glEnd();

	glEnable(GL_LIGHTING);
}



void CGLRenderer::StetColorMaterial(float r, float g, float b, bool emisija, float re, float ge, float be)
{
	glColor3f(r, g, b);
	float glColor[4] = { r, g, b,1.0 };
	float glWhite[4] = { 1.0, 1.0, 1.0,1.0 };
	float em[4] = { re,ge,be,1.0 };
	float emb[4] = { 0,0,0,1.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat*)glColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glWhite);
	if (emisija)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, em);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, emb);
	}
	glMaterialf(GL_FRONT, GL_SHININESS, 60);
}


void CGLRenderer::DrawCoun(float x, float y, float z, Colorf Boja,bool materijal, bool linije,int fine)
{
	glDisable(GL_TEXTURE_2D);
	int n = fine;
	std::vector<Point> temena = OdrediPoligon(x, n);
	glColor3f(Boja.r, Boja.g, Boja.b);

	float glColor[4] = { Boja.r,Boja.g,Boja.b,1.0 };
	if (materijal)
	{

		float glWhite[4] = { 1.0,1.0,1.0,1.0 };
		//float glColorDif[4] = { Boja.r*0.8,Boja.g*0.8,Boja.b*0.8,1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, glColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, glColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, glWhite);
		glMaterialf(GL_FRONT, GL_SHININESS, 60);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
	


	glBegin(GL_TRIANGLES);

	float lng = sqrt(temena[0].x * temena[0].x + temena[0].y * temena[0].y);
	float alfa = atan(lng / y);
	float ost = sin(alfa);
	for (int i = 0; i < n - 1; i++)
	{

		glNormal3f(temena[i].x / lng, ost, temena[i].y / lng);
		glVertex3f(temena[i].x, 0, temena[i].y);
		i++;
		glNormal3f(temena[i].x / lng, ost, temena[i].y / lng);
		glVertex3f(temena[i].x, 0, temena[i].y);
		i--;
		//glNormal3f(temena[i].x - (temena[i].x + temena[i + 1].x) / 2, ost, (temena[i].y + (temena[i].y - temena[i + 1].y) / 2));
		glVertex3f(0, y, 0);
	}

	glNormal3f(temena[n - 1].x / lng, ost, temena[n - 1].y / lng);
	glVertex3f(temena[n - 1].x, 0, temena[n - 1].y);
	glNormal3f(temena[0].x / lng, ost, temena[0].y / lng);
	glVertex3f(temena[0].x, 0, temena[0].y);
	glVertex3f(0, y, 0);
	glEnd();
	StetColorMaterial(Boja.r, Boja.g, Boja.b);
	DrawPoilgon2D(temena, 0.0);

	if (linije)
	{
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		float norm[3];
		for (int i = 0; i < n; i++)
		{
			norm[0] = linel * temena[i].x / lng;
			norm[1] = linel * ost;
			norm[2] = linel * temena[i].y / lng;

			//float prv = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);

			glVertex3f(temena[i].x, 0, temena[i].y);
			glVertex3f(temena[i].x + norm[0], norm[1], temena[i].y + norm[2]);
			glVertex3f(0, y, 0);
			glVertex3f(norm[0], y + norm[1], norm[2]);

		}
		glEnd();
		glEnable(GL_LIGHTING);

	}
	glEnable(GL_LIGHTING);
}


void CGLRenderer::DrawPoilgon2D(std::vector<Point> temena, float y,bool tekstura, float poz1, float poz2)
{
	GLboolean test = false;
	glGetBooleanv(GL_TEXTURE_2D, &test);
	if (!tekstura)
	{
		glDisable(GL_TEXTURE_2D);
		
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
	}
	glBegin(GL_TRIANGLE_FAN);
	float vt = 1;
	if (y <= 0)
	{
		vt = -1;
	}

	float angle = (2 * M_PI / (float)temena.size());

	float d = 1.f / 2.f;
	float r = 1.f;
	poz1 = 10 * d;
	poz2 = 1.5 * d;
	glNormal3f(0, vt, 0);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0, y, 0);
	for (int i = 0; i < temena.size(); i++)
	{

		glNormal3f(temena[i].x, vt, temena[i].y);
		glTexCoord2f(1, 0);
		glVertex3f(temena[i].x, y, temena[i].y);
	}

	glNormal3f(temena[0].x, vt, temena[0].y);
	glTexCoord2f(-1, 1);
	glVertex3f(temena[0].x, y, temena[0].y);

	glEnd();
	if (test)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);

	}
}

void CGLRenderer::DrawPoilgon2D_2(std::vector<Point> temena, float y, bool tekstura, float poz1, float poz2)
{
	GLboolean test = false;
	glGetBooleanv(GL_TEXTURE_2D, &test);
	if (!tekstura)
	{
		glDisable(GL_TEXTURE_2D);

	}
	else
	{
		glEnable(GL_TEXTURE_2D);
	}
	if (!tekstura)
	{
		glDisable(GL_TEXTURE_2D);

	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->texZid);
	}
	glBegin(GL_QUADS);
	float vt = 1;
	if (y <= 0)
	{
		vt = -1;
	}

	float angle = (2 * M_PI / (float)temena.size());

	float d = 1.f / 2.f;
	float r = 1.f;
	poz1 = 10 * d;
	poz2 = 1.5 * d;
	/*glNormal3f(0, vt, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, y, 0);
	*/
	glNormal3f(temena[0].x, vt, temena[0].y);
	glTexCoord2f(0, 0);
	glVertex3f(temena[0].x, y, temena[0].y);
	
		glNormal3f(temena[1].x, vt, temena[1].y);
		glTexCoord2f(1, 0);
		glVertex3f(temena[1].x, y, temena[1].y);

		glNormal3f(temena[2].x, vt, temena[2].y);
		glTexCoord2f(1, 1);
		glVertex3f(temena[2].x, y, temena[2].y);

	glNormal3f(temena[3].x, vt, temena[3].y);
	glTexCoord2f(0, 1);
	glVertex3f(temena[3].x, y, temena[3].y);

	glEnd();
	if (test)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);

	}
}


std::vector<Point> CGLRenderer::OdrediPoligon(float size, int n)
{
	std::vector<Point> rez;

	float r = size / 2;


	for (int i = 0; i < n; i++)
	{
		float x = r * cos(2.0 * M_PI * i / (double)n);
		float y = r * sin(2.0 * M_PI * i / (double)n);
		rez.push_back({ x , y });
	}

	return rez;
}

void CGLRenderer::myShadowMatrix(float ground[4], float light[4])
{
	float  dot;
	float  shadowMat[4][4];

	dot = ground[0] * light[0] +
		ground[1] * light[1] +
		ground[2] * light[2] +
		ground[3] * light[3];

	shadowMat[0][0] = dot - light[0] * ground[0];
	shadowMat[1][0] = 0.0 - light[0] * ground[1];
	shadowMat[2][0] = 0.0 - light[0] * ground[2];
	shadowMat[3][0] = 0.0 - light[0] * ground[3];

	shadowMat[0][1] = 0.0 - light[1] * ground[0];
	shadowMat[1][1] = dot - light[1] * ground[1];
	shadowMat[2][1] = 0.0 - light[1] * ground[2];
	shadowMat[3][1] = 0.0 - light[1] * ground[3];

	shadowMat[0][2] = 0.0 - light[2] * ground[0];
	shadowMat[1][2] = 0.0 - light[2] * ground[1];
	shadowMat[2][2] = dot - light[2] * ground[2];
	shadowMat[3][2] = 0.0 - light[2] * ground[3];

	shadowMat[0][3] = 0.0 - light[3] * ground[0];
	shadowMat[1][3] = 0.0 - light[3] * ground[1];
	shadowMat[2][3] = 0.0 - light[3] * ground[2];
	shadowMat[3][3] = dot - light[3] * ground[3];

	glMultMatrixf((const GLfloat*)shadowMat);
}

void CGLRenderer::DrawProba(CDC* pDC)
{

	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*glTranslated(0, 0, -10);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//big blue square
	glColor3ub(0, 255, 255);
	glBegin(GL_POLYGON);
	glVertex3i(5, 5, 0);
	glVertex3i(-5, 5, 0);
	glVertex3i(-5, -5, 0);
	glVertex3i(5, -5, 0);
	glEnd();

	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glPushMatrix();
	/* transparent triangle */
	glScalef(0.5f, 0.5f, 0.0f);
	glColor4ub(0.0f, 0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3i(-4, -4, 0);
	glVertex3i(4, -4, 0);
	glVertex3i(0, 4, 0);
	glEnd();
	glPopMatrix();

	//	glStencilFunc(GL_EQUAL, 1, 1);
	//	glStencilOp(GL_INCR, GL_KEEP, GL_DECR);

	glStencilFunc(GL_EQUAL, 2, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	/* blue square */
	glColor3ub(0, 0, 200);
	glBegin(GL_POLYGON);
	glVertex3i(3, 3, 0);
	glVertex3i(-3, 3, 0);
	glVertex3i(-3, -3, 0);
	glVertex3i(3, -3, 0);
	glEnd();

	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
	
}

void CGLRenderer::DrawObject(Colorf boja, Colorf boja2,Colorf mix,bool svetlo )
{

	Colorf data;
	data.r = boja.r * mix.r;
	data.g = boja.g * mix.g;
	data.b = boja.b * mix.b;

	glPushMatrix();
	DrawCoun(0.2, 0.5, 0, data, svetlo);
	glTranslatef(0, 0.5, 0);
	glRotatef(33, 0, 0, 1);

	DrawCoun(0.2, 0.5, 0, data, svetlo);
	glTranslatef(0, -0.1, 0.4);
	glRotatef(-66, 0, 0, 1);
	DrawCoun(0.2, 0.5, 0, data, svetlo);
	glPopMatrix();
	glPushMatrix();
	data.r = boja2.r * mix.r;
	data.g = boja2.g * mix.g;
	data.b = boja2.b * mix.b;
	glTranslatef(-0.4, 0.4, 0.2);
	DrawSphere(0.14, data, svetlo);

	glPopMatrix();
}

void CGLRenderer::DrawFlore(Colorf boja)
{
	glPushMatrix();
	std::vector<Point> temena;

	glTranslatef(0, -0.1, 0);
	
	temena.push_back({ -1,1 });
	temena.push_back({ 1,1 });
	temena.push_back({ 1,-1 });
	temena.push_back({ -1,-1 });


	StetColorMaterial(0, 0.1, 0.9);
	//reflection
	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilMask(0x1);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glDepthMask(GL_FALSE);


	DrawPoilgon2D(temena, 0.1);//prvi sa refleksiom
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDepthMask(GL_TRUE);
	glPopMatrix();
	glPushMatrix();


	glScalef(1, -1, 1);
	DrawObject({ 1,0,1 }, { 0,0,1 }, { 0.5, 0.3, 0.3 });
	glDisable(GL_STENCIL_TEST);


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.001, 0);
	float test[4] = { 0,4,0,0 };
	myShadowMatrix(test, light_position);

	glEnable(GL_STENCIL_TEST);
	//shadwos
	Colorf data = { 1 * 0.0,1 * 0.0,1 * 0.0 };
	DrawObject(data, data, { 1,1,1 }, false);
	glDisable(GL_STENCIL_TEST);

	glPopMatrix();
}

void CGLRenderer::DrawWall(Colorf boja,int angle,int side)
{
	glPushMatrix();
	std::vector<Point> temena;

	glTranslatef(0, -0.1, 0);

	temena.push_back({ -1,1 });
	temena.push_back({ 1,1 });
	temena.push_back({ 1,-1 });
	temena.push_back({ -1,-1 });


	StetColorMaterial(1, 1, 1);

	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glDepthMask(GL_FALSE);

	switch (side)
	{
	case 0:glRotatef(angle, 1, 0, 0);
		glTranslatef(0, 0.9, 1.1); break;
	case 1:glRotatef(angle, 0, 0, 1);
		glTranslatef(1.1, 0.9, 0); break;
	case 2:glRotatef(angle, 0, 0, 1);
		glTranslatef(-1.1, 0.9, 0); break;
	default:glRotatef(angle, 1, 0, 0);
		glTranslatef(0, 0.9, -1.1); break;
	}

	
	DrawPoilgon2D_2(temena, 0.1,true);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glDepthMask(GL_TRUE);

	glDisable(GL_STENCIL_TEST);


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.001, 0);
	float test[4];
	switch (side)//fiksno
	{
	case 0:test[0] = 0;
		   test[1] = 0;
		   test[2] = 2;
		   test[3] = 2;
		   break;//zadnji
	case 1:test[0] = 2;
		test[1] = 0;
		test[2] = 0;
		test[3] = 2;
		break;
	case 2:test[0] = -2;
		test[1] = 0;
		test[2] = 0;
		test[3] = 2;
		break;
	default:test[0] = 0;
		test[1] = 0;
		test[2] = 2;
		test[3] = 2;
		break;
	}
	myShadowMatrix(test, light_position);
	
	glEnable(GL_STENCIL_TEST);
	//shadwos
	Colorf data = { 1 * 0.0,1 * 0.0,1 * 0.0 };
	DrawObject(data, data, { 1,1,1 }, false);
	glDisable(GL_STENCIL_TEST);

	glPopMatrix();
}

void CGLRenderer::DrawSphere(float radius, Colorf Boja, bool svetlo, bool emisija , int sector , int stack )
{
	if (svetlo)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
	float x, y, z;

	float angleF = M_PI / stack;
	float angleS = 2 * M_PI / sector;
	float pozS = 0;
	float pozL = 0;


	float* vert = (float*)malloc(sizeof(float) * 15000);
	int* lm = (int*)malloc(sizeof(int) * 5000);


	int cnt = 0;
	int cnt2 = 0;

	for (int i = 0; i <= stack / 2; i++)
	{

		float xn = radius * cos(pozL);
		float sf = radius * sin(pozL);

		pozL += angleF;

		float xnn = radius * cos(pozL);
		float sfn = radius * sin(pozL);

		for (int j = 0; j <= sector; j++)//sa trouglovima
		{

			x = xn * cos(pozS);
			y = xn * sin(pozS);
			z = sf;


			vert[cnt++] = x;
			vert[cnt++] = z;
			vert[cnt++] = y;
			lm[cnt2] = cnt2;
			cnt2++;
			pozS += angleS;

			x = xnn * cos(pozS);
			y = xnn * sin(pozS);
			z = sfn;


			vert[cnt++] = x;
			vert[cnt++] = z;
			vert[cnt++] = y;
			lm[cnt2] = cnt2;
			lm[cnt2] = cnt2;
			cnt2++;


		}



		pozS = 0;
	}

	int n = cnt;
	for (int i = 0; i < n; i += 3)
	{
		vert[cnt++] = vert[i];
		vert[cnt++] = -vert[i + 1];
		vert[cnt++] = vert[i + 2];
		lm[cnt2] = cnt2;
		cnt2++;
	}





	glBegin(GL_TRIANGLE_STRIP);
	StetColorMaterial(Boja.r, Boja.g, Boja.b, emisija);



	for (int i = 0; i < cnt; i += 3)
	{
		glNormal3f(vert[i] / radius, vert[i + 1] / radius, vert[i + 2] / radius);
		glVertex3f(vert[i], vert[i + 1], vert[i + 2]);
		//glVertex3f(vx[i], vy[i], vz[i]);
	}



	glEnd();



	free(vert);
	free(lm);

	glEnable(GL_LIGHTING);
}



UINT CGLRenderer::LoadTexture(char* fileName)
{
	UINT texID;
	DImage img;
	img.Load(CString(fileName));

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(),
		GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.Width(), img.Height(), 0,
	GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());*/
	return texID;
}



