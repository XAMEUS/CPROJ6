#include "display.h"

GLfloat pixelsize = 1;

GLfloat min_x = -1;
GLfloat max_x = 1;
GLfloat min_y = -1;
GLfloat max_y = 1;

void Display_InitGL()
{
  // Antialiasing
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glLineWidth(1.6f);
  glPointSize(3.0f);
}

// function to reset our viewport after a window resize
void Display_SetViewport(int width, int height, GLfloat dx, GLfloat dy, float zoom)
{
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  pixelsize = (max_y-min_y)/height;
  glOrtho(
    (min_x + max_x) / 2 + dx - zoom * (pixelsize * width / 2),
    (min_x + max_x) / 2 + dx + zoom * (pixelsize * width / 2),
    (min_y + max_y) / 2 + dy - zoom * (max_y - min_y) / 2,
    (min_y + max_y) / 2 + dy + zoom * (max_y - min_y) / 2,
    -1.0,
    1.0
  );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
