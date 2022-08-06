// Resizeからdisplayへの流れの確認

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

void display(void)
{
  GLint viewport[4];
  GLdouble modelview[16]; /* モデルビュー変換行列の保存用 */
  GLdouble projection[16];
  GLint mode = 0;

  printf("display関数実行\n");

  // 行列取得
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetIntegerv(GL_VIEWPORT, viewport);
  //  初期行列チェック
  printf("\ndisplay=========================================\n");
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  printf("初期モード　%d\n", mode);
  checkMatrix(projection, "pro2");
  checkMatrix(modelview, "mode2");
  printf("position:(%d,%d), size: (%d,%d)\n", viewport[0], viewport[1], viewport[2], viewport[3]);

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
  printf("resize関数実行\n");
  GLint viewport[4];
  GLdouble modelview[16]; /* モデルビュー変換行列の保存用 */
  GLdouble projection[16];
  GLint mode = 0;
  GLdouble p[16] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
  GLdouble m[16] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};

  int s = 3;

  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
  glViewport(0, 0, w, h);

  //値を出鱈目にする
  // glMatrixMode(GL_PROJECTION);
  // glLoadMatrixd(p);
  // glMatrixMode(GL_MODELVIEW);
  // glLoadMatrixd(m);
  switch (s)
  {
  case 1:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    break;
  case 2:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    break;
  case 3:
    break;
  }

  // 行列取得
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetIntegerv(GL_VIEWPORT, viewport);
  //  初期行列チェック
  printf("\nresize=========================================\n");
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  printf("初期モード　%d\n", mode);
  checkMatrix(projection, "pro2");
  checkMatrix(modelview, "mode2");
  printf("position:(%d,%d), size: (%d,%d)\n", viewport[0], viewport[1], viewport[2], viewport[3]);
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
