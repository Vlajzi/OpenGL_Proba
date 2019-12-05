#include "pch.h"
#include "Teapot.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void TeaPot::Teapot(long grid)
{
    float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
    long i, j, k, l;

    teaList = 1;
    glNewList(teaList, GL_COMPILE);
    glPushMatrix();
    glRotatef(270.0, 1.0, 0.0, 0.0);
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                for (l = 0; l < 3; l++) {
                    p[j][k][l] = cpData[patchData[i][j * 4 + k]][l];
                    q[j][k][l] = cpData[patchData[i][j * 4 + (3 - k)]][l];
                    if (l == 1) {
                        q[j][k][l] *= -1.0;
                    }
                    if (i < 6) {
                        r[j][k][l] = cpData[patchData[i][j * 4 + (3 - k)]][l];
                        if (l == 0) {
                            r[j][k][l] *= -1.0;
                        }
                        s[j][k][l] = cpData[patchData[i][j * 4 + k]][l];
                        if (l == 0) {
                            s[j][k][l] *= -1.0;
                        }
                        if (l == 1) {
                            s[j][k][l] *= -1.0;
                        }
                    }
                }
            }
        }
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &p[0][0][0]);
        glEnable(GL_MAP2_VERTEX_3);
        glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
        glEvalMesh2(GL_FILL, 0, grid, 0, grid);
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &q[0][0][0]);
        glEvalMesh2(GL_FILL, 0, grid, 0, grid);
        if (i < 6) {
            glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &r[0][0][0]);
            glEvalMesh2(GL_FILL, 0, grid, 0, grid);
            glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &s[0][0][0]);
            glEvalMesh2(GL_FILL, 0, grid, 0, grid);
        }
    }
    glDisable(GL_MAP2_VERTEX_3);
    glPopMatrix();
    glEndList();
}

void TeaPot::Init(void)
{
    float position[] = { 0.0, 3.0, 3.0, 0.0 };
    float local_view[] = { 0.0 };
    float ambient[] = { 0.1745, 0.01175, 0.01175 };
    float diffuse[] = { 0.61424, 0.04136, 0.04136 };
    float specular[] = { 0.727811, 0.626959, 0.626959 };

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    Teapot(14);
}

void TeaPot::Reshape(int w, int h)
{


    glViewport(0, 0, (GLint)w, (GLint)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6.0, 6.0, -6.0, 6.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TeaPot::SpecialKey(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        rotX -= 20.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        rotX += 20.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        rotY -= 20.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        rotY += 20.0;
        glutPostRedisplay();
        break;
    }
}

void TeaPot::Draw(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(rotY, 0.0, 1.0, 0.0);
    glRotatef(rotX, 1.0, 0.0, 0.0);

    glCallList(teaList);

    glPopMatrix();

    if (doubleBuffer) {
        glutSwapBuffers();
    }
    else {
        glFlush();
    }
}

void TeaPot::Args(int argc, char** argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-sb") == 0) {
            doubleBuffer = GL_FALSE;
        }
        else if (strcmp(argv[i], "-db") == 0) {
            doubleBuffer = GL_TRUE;
        }
    }
}

void TeaPot::Min()
{

}

void TeaPot::Key(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
    }
}
