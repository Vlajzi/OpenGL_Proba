// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here


#include "framework.h"
#include "CGLRenderer.h"

//OpenGL------------
#include "OpenGL/glew.h"
#include <gl/GL.h>
#include<gl/GLU.h>
#pragma comment (lib,"OpenGL32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"OpenGL/glaux.lib")
#pragma comment (lib,"OpenGL/glew32.lib")
#pragma comment (lib,"OpenGL/freeglut.lib")
#include "OpenGL/glaux.h"
#include "OpenGL/freeglut.h"



#include "Terrain.h"
#endif //PCH_H
