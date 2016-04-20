#include "draw.h"

GLdouble dist(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1);

GLdouble dist(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1)
{
  GLdouble vx = x1 - x0;
  GLdouble vy = y1 - y0;
  return sqrt(vx * vx + vy * vy);
}

void Draw_Line(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1, GLdouble size)
{
  GLdouble vx = x1 - x0;
  GLdouble vy = y1 - y0;
  GLdouble wx = -vy;
  GLdouble wy = vx;
  GLdouble length = sqrt(vx * vx + vy * vy);
  wx = wx / length * size * 0.00001;
  wy = wy / length * size * 0.00001;
  glBegin(GL_QUADS);
    glVertex3f(x0 + wx, y0 + wy, 0);
    glVertex3f(x0 - wx, y0 - wy, 0);
    glVertex3f(x0 - wx + vx, y0 - wy + vy, 0);
    glVertex3f(x0 + wx + vx, y0 + wy + vy, 0);
  glEnd();
}

void Draw_Lines(int n, GLdouble **points, GLdouble size)
{
  int i = 0;
  GLdouble x0 = points[0][0];
  GLdouble y0 = points[0][1];

  GLdouble x1 = points[1][0];
  GLdouble y1 = points[1][1];

  i++; i++;

  GLdouble ux = x1 - x0;
  GLdouble uy = y1 - y0;
  GLdouble length = sqrt(ux * ux + uy * uy);
  ux = ux / length;
  uy = uy / length;
  GLdouble wx = -uy;
  GLdouble wy = ux;
  length = sqrt(wx * wx + wy * wy);
  wx = wx / length * size * 0.00001;
  wy = wy / length * size * 0.00001;

  GLdouble ax0 = x0 + wx;
  GLdouble ay0 = y0 + wy;
  GLdouble bx0 = x0 - wx;
  GLdouble by0 = y0 - wy;
  glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(ax0, ay0, 0);
    glVertex3f(bx0, by0, 0);
    while (i < n)
    {
      GLdouble x2 = points[i][0];
      GLdouble y2 = points[i][1];

      GLdouble vx = x2 - x1;
      GLdouble vy = y2 - y1;
      length = sqrt(vx * vx + vy * vy);
      vx = vx / length;
      vy = vy / length;
      wx = ux - vx;
      wy = uy - vy;
      if (fabs(wx) > 0.01 || fabs(wy) > 0.01) {
        length = sqrt(wx * wx + wy * wy);
        wx = wx / length;
        wy = wy / length;
        GLdouble angle = atan2(-uy, -ux) - atan2(vy, vx);
        if (angle < 0) angle += 2 * PI;
        if (angle < PI) {
          wx = -wx;
          wy = -wy;
        }
      } else {
        wx = -uy;
        wy = ux;
        length = sqrt(wx * wx + wy * wy);
        wx = wx / length;
        wy = wy / length;
      }

      glVertex3f(x1 + wx * size * 0.00001, y1 + wy * size * 0.00001, 0);
      glVertex3f(x1 - wx * size * 0.00001, y1 - wy * size * 0.00001, 0);

      ux = vx;
      uy = vy;
      x0 = x1;
      y0 = y1;
      x1 = x2;
      y1 = y2;
      i++;
    }
    ux = x1 - x0;
    uy = y1 - y0;
    wx = -uy;
    wy = ux;
    length = sqrt(wx * wx + wy * wy);
    wx = wx / length * size * 0.00001;
    wy = wy / length * size * 0.00001;
    GLdouble cx0 = x0 + wx + ux;
    GLdouble cy0 = y0 + wy + uy;
    GLdouble dx0 = x0 - wx + ux;
    GLdouble dy0 = y0 - wy + uy;
    glVertex3f(cx0, cy0, 0);
    glVertex3f(dx0, dy0, 0);
  glEnd();
}
