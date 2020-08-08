#include "pch.h"




CGLRenderer::CGLRenderer()
{
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	
	linel = 0.04;
	
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
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
	glTranslated(0, 0, -10);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);
	glDepthMask(GL_TRUE);
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
	float light_position[] = { 1.0, 1.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_STENCIL_TEST);

	DrawCoun(0.2, 0.5, 0, {1,0,0});
	
	std::vector<Point> temena;

	glTranslatef(0, -0.1, 0);

	temena.push_back({-0.25,0.25});
	temena.push_back({ 0.25,0.25 });
	temena.push_back({ 0.25,-0.25 });
	temena.push_back({ -0.25,-0.25 });


	glStencilFunc(GL_ALWAYS, 3, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.7, 0.0, 0.0, 0.3);
	glColor4f(1.0, 1.0, 1.0, 0.3);

	StetColorMaterial(0, 1, 0);
	DrawPoilgon2D(temena,0.1);
	glDisable(GL_BLEND);

	glStencilFunc(GL_LESS, 2, 0xffffffff);  /* draw if ==1 */
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glDisable(GL_STENCIL_TEST);


	//prvo pod pa onda trougao;

	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawTest(CDC* pDC)
{
	int velicina = 12;
	Terrain ten(velicina, 1.5);
	for (int i = 0; i < velicina * velicina; i++)
	{
		ten.points[i] = 0;

	}

	/*ten.points[14] = 0.1f;
	ten.points[15] = 0.2f;
	ten.points[16] = 0.3f;
	ten.points[17] = 0.4f;
	ten.points[velicina + 14] = 0.1f;
	ten.points[velicina + 15] = 0.2f;
	ten.points[velicina + 16] = 0.3f;
	ten.points[velicina + 17] = 0.4f;*/

	ten.points[17] = 0.1f;
	ten.points[velicina + 17] = 0.2f;
	ten.points[velicina + 16] = 0.1f;
	ten.points[velicina + 18] = 0.1f;
	ten.points[2 * velicina + 17] = 0.1f;

	//ten.points[11] = 0.7f;

	wglMakeCurrent(pDC->m_hDC, m_hrc);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -20);
	glTranslatef(-0.5, 0, 0);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);

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
	float light_position[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::vector<Point3f> tmp = ten.genPoints();
	std::vector<Point3f> boja = ten.genColor();

	float glColor[4] = { 1.0,0.0,0.0,1.0 };
	float glWhite[4] = { 1.0,1.0,1.0,1.0 };
	float color[4] = { 1.0,0.0,0.0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);
	for (int j = 0; j < velicina - 1; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		int poz = j * velicina * 2;
		for (int i = 0; i < velicina * 2; i++)
		{
			float boj[4] = { boja[poz + i].x, boja[poz + i].y, boja[poz + i].z ,1.0 };
			glMaterialfv(GL_FRONT, GL_AMBIENT, boj);
			boj[3] = 0.5;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, boj);
			//glColor3f(boja[poz+i].x, boja[poz+i].y, boja[poz+i].z);
			glVertex3f(tmp[poz + i].x, tmp[poz + i].y, tmp[poz + i].z);
			glNormal3f(tmp[poz + i].x, 1 - tmp[poz + i].y, tmp[poz + i].z);
		}

		glEnd();
	}

	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}



void CGLRenderer::DrawCube(float size, Colorf boja, int det)
{

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


void CGLRenderer::DrawCoun(float x, float y, float z, Colorf Boja, int fine)
{
	int n = fine;
	std::vector<Point> temena = OdrediPoligon(x, n);
	glColor3f(Boja.r, Boja.g, Boja.b);

	float glColor[4] = { Boja.r,Boja.g,Boja.b,1.0 };
	float glWhite[4] = { 1.0,1.0,1.0,1.0 };
	//float glColorDif[4] = { Boja.r*0.8,Boja.g*0.8,Boja.b*0.8,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, glColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);


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

	StetColorMaterial(0, 4, 0);
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

}


void CGLRenderer::DrawPoilgon2D(std::vector<Point> temena, float y, float poz1, float poz2)
{
	glBegin(GL_TRIANGLE_FAN);
	float vt = 1;
	if (y <= 0)
	{
		vt = -1;
	}

	float angle = (2 * M_PI / (float)temena.size());

	float d = 1.f / 16.f;
	float r = 1.5 * d;
	poz1 = 10 * d;
	poz2 = 1.5 * d;
	glNormal3f(0, vt, 0);
	glTexCoord2f(10 * d, 1.5 * d);
	glVertex3f(0, y, 0);
	for (int i = 0; i < temena.size(); i++)
	{
		glNormal3f(temena[i].x, vt, temena[i].y);
		glTexCoord2f(poz1 + r * cos(i * angle), poz2 + r * sin(i * angle));
		glVertex3f(temena[i].x, y, temena[i].y);
	}

	glNormal3f(temena[0].x, vt, temena[0].y);
	glTexCoord2f(10 * d + r * cos(0), 1.5 * d + r * sin(0));
	glVertex3f(temena[0].x, y, temena[0].y);

	glEnd();

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


void CGLRenderer::shadowMatrix(GLfloat shadowMat[4][4],GLfloat groundplane[4],GLfloat lightpos[4])
{
	GLfloat dot;

	/* Find dot product between light position vector and ground plane normal. */
	dot = groundplane[X] * lightpos[X] +
		groundplane[Y] * lightpos[Y] +
		groundplane[Z] * lightpos[Z] +
		groundplane[W] * lightpos[W];

	shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
	shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
	shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
	shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

	shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
	shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
	shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
	shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

	shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
	shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
	shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
	shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

	shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
	shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
	shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
	shadowMat[3][3] = dot - lightpos[W] * groundplane[W];

}