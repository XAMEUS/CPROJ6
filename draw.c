#include "draw.h"

void Draw_Line(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat size)
{
  GLfloat vx = x1 - x0;
  GLfloat vy = y1 - y0;
  GLfloat wx = -vy;
  GLfloat wy = vx;
  GLfloat length = sqrt(vx * vx + vy * vy);
  wx = wx / length * size * pixelsize;
  wy = wy / length * size * pixelsize;
  glBegin(GL_QUADS);
    glVertex3f(x0 + wx, y0 + wy, 0);
    glVertex3f(x0 - wx, y0 - wy, 0);
    glVertex3f(x0 - wx + vx, y0 - wy + vy, 0);
    glVertex3f(x0 + wx + vx, y0 + wy + vy, 0);
  glEnd();
}
