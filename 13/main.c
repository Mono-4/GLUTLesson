// dでdisplayで実行
//dを実行し続けると、乗算され続ける
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
  GLdouble camera[3] = {0.0, 5.0, 5.0};
  GLdouble look[3] = {0.0, 0.0, 0.0};
  GLdouble up[3] = {0.0, 1.0, 0.0};
  printf("display関数実行\n");
  // 背景消去
  glClear(GL_COLOR_BUFFER_BIT);

  glTranslated(1.0, 0.0, 0.0);
  checkAllMatrix(2);

  gluLookAt(camera[0], camera[1], camera[2], look[0], look[1], look[2], up[0], up[1], up[2]);
  guideAxis(); //色を濃くしている
  glutWireCube(2);

  glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'q':
    exit(0);
  case 'd':
    // printf("aaaa\n");
    display();
  default:
    break;
  }
}
void resize(int w, int h)
{
  printf("resize関数実行\n");
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  gluPerspective(30.0, TEXHEIGHT / TEXHEIGHT, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutInitWindowSize(TEXWIDTH, TEXHEIGHT);
  glutKeyboardFunc(keyboard);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop();
  return 0;
}
