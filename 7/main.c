// 赤本のp107から引用したテンプレート.
// GLlookatの実験
// GLlookAtとglTranslateはその時のモードによる
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
  GLint viewport[4];
  GLdouble modelview[16]; /* モデルビュー変換行列の保存用 */
  GLdouble projection[16];
  GLint mode = 0;

  printf("display関数実行\n");

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);
  // 初期化
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //　モードチェンジ
  if (1)
  {
    glMatrixMode(GL_MODELVIEW);
  }
  else
  {
    glMatrixMode(GL_PROJECTION);
  }

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

  // gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslated(1.0, 1.0, 1.0);

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
  // glMatrixMode(GL_MODELVIEW);
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
