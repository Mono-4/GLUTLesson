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

void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POLYGON);
  glColor3d(1.0, 0.0, 0.0);
  glVertex2d(-0.9, -0.9);
  glVertex2d(0.9, -0.9);
  glVertex2d(0.9, 0.9);
  glEnd();
  glFlush();
}
void resize(int w, int h)
{
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void init(void)
{
  glClearColor(0.0, 0.0, 1.0, 1.0);
}
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}