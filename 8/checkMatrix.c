//Matrixやmodeをチェックする関数
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
  printf("\n<%s>\n", comment);
  for (int i = 0; i < 16; i++)
  {
    printf("%4g ", matrix[i]);
    if ((i + 1) % 4 == 0)
    {
      printf("\n");
    }
  }
  printf("\n");
}

void checkAllMatrix()
{
  GLint viewport[4];
  GLdouble modelview[16]; /* モデルビュー変換行列の保存用 */
  GLdouble projection[16];

  // 行列取得
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetIntegerv(GL_VIEWPORT, viewport);
  //  初期行列チェック
  checkMatrix(projection, "pro");
  checkMatrix(modelview, "mode");
  printf("position:(%d,%d), size: (%d,%d)\n", viewport[0], viewport[1], viewport[2], viewport[3]);
}

void checkMode()
{
  GLint mode;
  printf("\n");
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  if (mode == 5888)
  {
    printf("[MODELVIEWモード]\n");
  }
  else if (mode == 5889)
  {
    printf("[PROJECTIONモード]\n");
  }
  else
  {
    printf("[モードを特定できませんでした]\n");
  }
  printf("\n");
}
