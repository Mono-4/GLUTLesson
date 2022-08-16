// trackballの実装

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
#include <math.h>

#include "checkmatrix.h"
#include "showguide.h"
#include "trackball.h"

/* 表示図形のディスプレイリスト番号 */
static GLuint cube;

/* 物体の色 */
static GLfloat red[] = {0.8, 0.2, 0.2, 1.0};

/* 光源の位置 */
static GLfloat pos[] = {3.0, 4.0, 5.0, 1.0};

void display(void) //おわった
{
  printf("aa\n");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 視点の移動 */
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  /* 回転 */
  // 回転行列をかける
  glMultMatrixd(trackballRotation());

  glCallList(cube);

  glutSwapBuffers();
}

void resize(int w, int h) //考えなくて良い
{

  trackballRegion(w, h);
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 透視変換行列の指定 */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void idle(void) //考えなくて良い
{
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  printf("motio");

  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    switch (state)
    {
    case GLUT_DOWN:

      trackballStart(x, y);
      break;
    case GLUT_UP:
      trackballStop(x, y);
      break;
    default:
      break;
    }
  }
}

void motion(int x, int y)
{
  printf("motioaa");

  trackballMotion(x, y);
}

void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // trackballInit();
  //
}

void scene(void) //考えなくて良い
{
  /* 表示図形をディスプレイリストに登録 */
  cube = glGenLists(1);

  /* 立方体 */
  glNewList(cube, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(2.0);
  glEndList();
}

int main(int argc, char *argv[])
{
  printf("aab\n");
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutIdleFunc(idle);
  init();
  scene();
  glutMainLoop();
  return 0;
}
