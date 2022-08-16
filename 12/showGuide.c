// Matrixやmodeをチェックする関数
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#if defined(WIN32)
//#  pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include "glut.h"
#include "glext.h"
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
#elif defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#endif

// 軸の描画 (0,0,0)が原点
void guideAxis(void)
{
  GLdouble axis[][3] =
      {
          {0.0, 0.0, 0.0},
          {10.0, 0.0, 0.0},
          {0.0, 10.0, 0.0},
          {0.0, 0.0, 10.0}};
  GLdouble color[][3] =
      {
          {1.0, 0.0, 0.0},
          {0.0, 1.0, 0.0},
          {0.0, 0.0, 1.0}};
  printf("axis\n");

  glBegin(GL_LINES);
  for (int i = 0; i < 3; i++)
  {
    glColor3dv(color[i]);
    glVertex3dv(axis[0]);
    glVertex3dv(axis[i + 1]);
  }
  glColor3d(1.0, 1.0, 1.0);
  glEnd();
}

// XZ平面の描画
void guidePlane(void)
{
  const GLdouble xsize = 10.0;
  const GLdouble zsize = 10.0;
  printf("plane\n");
  glBegin(GL_LINES);
  glColor3d(0.5, 0.5, 0.5);
  for (GLdouble x = -xsize; x <= xsize; x += 1)
  {
    glVertex3d(x, 0.0, -zsize);
    glVertex3d(x, 0.0, zsize);
  }
  for (GLdouble z = -zsize; z <= zsize; z += 1)
  {
    glVertex3d(-xsize, 0.0, z);
    glVertex3d(xsize, 0.0, z);
  }
  glEnd();
}

void guidePoint(GLdouble *color)
{
  glColor3dv(color);
  glPointSize(10.0);
  glBegin(GL_POINTS);
  glVertex3d(0.0, 0.0, 0.0);
  glEnd();
  glColor3d(1.0, 1.0, 1.0);
}