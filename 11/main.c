//軸を追加
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

#include "checkMatrix.h"
#include "showGuide.h"

#define TEXWIDTH 512
#define TEXHEIGHT 512
void init(void)
{
  printf("init関数実行\n");
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_FLAT);
}

void display(void)
{
  GLdouble camera[3] = {0.0, 5.0, -5.0};
  GLdouble look[3] = {0.0, 0.0, 0.0};
  GLdouble up[3] = {0.0, 1.0, 0.0};
  printf("display関数実行\n");
  int a[3] = {0, 0, 1};
  // ====
  if (a[0])
  {
    printf("1\n");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, TEXHEIGHT / TEXHEIGHT, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
  }
  // =====

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, -2.0);

  // モデルビュー
  glTranslated(1.0, 0.0, 0.0);
  gluLookAt(camera[0], camera[1], camera[2], look[0], look[1], look[2], up[0], up[1], up[2]);
  if (a[1])
  {
    printf("2\n");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, TEXHEIGHT / TEXHEIGHT, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
  }
  // 描画
  guidePlane();
  guideAxis();
  glutWireCube(2);
  if (a[2])
  {
    printf("3\n");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, TEXHEIGHT / TEXHEIGHT, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
  }
  glFlush();
}
void resize(int w, int h)
{
  printf("resize関数実行\n");
  glViewport(0, 0, w, h);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutInitWindowSize(TEXWIDTH, TEXHEIGHT);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop();
  return 0;
}
