// 赤本のp107から引用したテンプレート
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

void checkMatrix(GLdouble *matrix, char *comment)
{
  printf("-----------------------\n");
  printf("<%s>\n", comment);
  for (int i = 0; i < 16; i++)
  {
    printf("%4g ", matrix[i]);
    if ((i + 1) % 4 == 0)
    {
      printf("\n");
    }
  }
  printf("-----------------------\n");
}

void init(void)
{
  glClearColor(0.0, 0.0, 1.0, 1.0);
  glShadeModel(GL_FLAT);
}

void display(void)
{
  printf("display関数実行\n");

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glutWireCube(1.0);
  glFlush();
}
void resize(int w, int h)
{
  printf("resize関数実行\n");

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop();
  return 0;
}
