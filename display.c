#include "display.h"

GLfloat pixelsize = 1;

GLfloat min_x = -1;
GLfloat max_x = 1;
GLfloat min_y = -1;
GLfloat max_y = 1;

int detail = 0;

void Display_InitGL()
{
  // Antialiasing
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glLineWidth(1.6f);
  glPointSize(3.0f);
  detail = 0;
}

// function to reset our viewport after a window resize
void Display_SetViewport(int width, int height, GLfloat dx, GLfloat dy, float zoom)
{
  glViewport(0, 0, (GLint) width, (GLint) height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  pixelsize = (max_y-min_y)/height;

  GLfloat a = (min_x + max_x) / 2 + dx - zoom * (pixelsize * width / 2);
  GLfloat b = (min_x + max_x) / 2 + dx + zoom * (pixelsize * width / 2);
  GLfloat c = (min_y + max_y) / 2 + dy - zoom * (max_y - min_y) / 2;
  GLfloat d = (min_y + max_y) / 2 + dy + zoom * (max_y - min_y) / 2;

  printf("%f\n", fabs(fabs(b) - fabs(a)));
  if (fabs(fabs(b) - fabs(a)) < 0.02) detail = 10;
  else detail = 0;

  glOrtho(a, b, c, d,-1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
