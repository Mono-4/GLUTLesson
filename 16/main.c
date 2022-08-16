// くぅオータニオンで回転
// https://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20040321
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
#include <math.h>
#include <GLUT/glut.h>

/* 表示図形のディスプレイリスト番号 */
static GLuint cube;

/* 物体の色 */
static GLfloat red[] = {0.8, 0.2, 0.2, 1.0};

/* 光源の位置 */
static GLfloat pos[] = {3.0, 4.0, 5.0, 1.0};

/* 視点の位置 */

/* ドラッグ開始位置 */
static int cx, cy;

/* マウスの絶対位置→ウィンドウ内での相対位置の換算係数 */
static double sx, sy;

/* マウスの相対位置→回転角の換算係数 */
#define SCALE (2.0 * 3.14159265358979323846)

/* 回転の初期値 (クォータニオン) */
static double cq[4] = {1.0, 0.0, 0.0, 0.0};

/* ドラッグ中の回転 (クォータニオン) */
static double tq[4];

/* 回転の変換行列 */
static double rt[16];

/*
** クォータニオンの積 r <- p x q
*/
void qmul(double r[], const double p[], const double q[])
{
  r[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
  r[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
  r[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
  r[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
}

/*
** 回転の変換行列 r <- クォータニオン q
// くぅオータニオンqから回転行列を作成
*/
void qrot(double r[], double q[])
{
  double x2 = q[1] * q[1] * 2.0;
  double y2 = q[2] * q[2] * 2.0;
  double z2 = q[3] * q[3] * 2.0;
  double xy = q[1] * q[2] * 2.0;
  double yz = q[2] * q[3] * 2.0;
  double zx = q[3] * q[1] * 2.0;
  double xw = q[1] * q[0] * 2.0;
  double yw = q[2] * q[0] * 2.0;
  double zw = q[3] * q[0] * 2.0;

  r[0] = 1.0 - y2 - z2;
  r[1] = xy + zw;
  r[2] = zx - yw;
  r[4] = xy - zw;
  r[5] = 1.0 - z2 - x2;
  r[6] = yz + xw;
  r[8] = zx + yw;
  r[9] = yz - xw;
  r[10] = 1.0 - x2 - y2;
  r[3] = r[7] = r[11] = r[12] = r[13] = r[14] = 0.0;
  r[15] = 1.0;
}

void display(void) //おわった
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 視点の移動 */
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  /* 回転 */
  // 回転行列をかける
  glMultMatrixd(rt);

  glCallList(cube);

  glutSwapBuffers();
}

void resize(int w, int h) //考えなくて良い
{
  /* マウスポインタ位置のウィンドウ内の相対的位置への換算用 */
  sx = 1.0 / (double)w;
  sy = 1.0 / (double)h;

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
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    switch (state)
    {
    case GLUT_DOWN:
      /* ドラッグ開始点を記録 */
      cx = x;
      cy = y;
      /* アニメーション開始 */
      glutIdleFunc(idle);
      break;
    case GLUT_UP:
      /* アニメーション終了 */
      glutIdleFunc(0);
      /* 回転の保存 */
      cq[0] = tq[0];
      cq[1] = tq[1];
      cq[2] = tq[2];
      cq[3] = tq[3];
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void motion(int x, int y)
{
  double dx, dy, a;

  /* マウスポインタの位置のドラッグ開始位置からの変位 */
  dx = (x - cx) * sx;
  dy = (y - cy) * sy;

  /* マウスポインタの位置のドラッグ開始位置からの距離 */
  a = sqrt(dx * dx + dy * dy);

  if (a != 0.0)
  {
    /* マウスのドラッグに伴う回転のクォータニオン dq を求める */
    double ar = a * SCALE * 0.5;
    double as = sin(ar) / a;
    double dq[4] = {cos(ar), dy * as, dx * as, 0.0};

    /* 回転の初期値 cq に dq を掛けて回転を合成 */
    qmul(tq, dq, cq);

    /* クォータニオンから回転の変換行列を求める */
    qrot(rt, tq);
  }
}



void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /* 回転行列の初期化 */
  qrot(rt, cq);
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
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  init();
  scene();
  glutMainLoop();
  return 0;
}
