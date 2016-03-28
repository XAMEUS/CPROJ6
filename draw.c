#include "draw.h"

GLfloat dist(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1);

GLfloat dist(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1)
{
  GLfloat vx = x1 - x0;
  GLfloat vy = y1 - y0;
  return sqrt(vx * vx + vy * vy);
}

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

//TODO : Fix points orders
void Draw_Lines(int n, GLfloat* points, GLfloat size)
{
  int i = 0;
  GLfloat x0 = *points;
  points++;
  GLfloat y0 = *points;
  points++;

  GLfloat x1 = *points;
  points++;
  GLfloat y1 = *points;
  points++;

  i++; i++;

  GLfloat ux = x1 - x0;
  GLfloat uy = y1 - y0;
  GLfloat length = sqrt(ux * ux + uy * uy);
  ux = ux / length;
  uy = uy / length;
  GLfloat wx = -uy;
  GLfloat wy = ux;
  length = sqrt(wx * wx + wy * wy);
  wx = wx / length * size * pixelsize;
  wy = wy / length * size * pixelsize;

  GLfloat ax0 = x0 + wx;
  GLfloat ay0 = y0 + wy;
  GLfloat bx0 = x0 - wx;
  GLfloat by0 = y0 - wy;
  glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(ax0, ay0, 0);
    glVertex3f(bx0, by0, 0);
    while (i < n)
    {
      GLfloat x2 = *points;
      points++;
      GLfloat y2 = *points;
      points++;

      GLfloat vx = x2 - x1;
      GLfloat vy = y2 - y1;
      //glColor3f(0.6,0.8,0.6);
      if ((vx > 0.00000001) || (vy > 0.00000001)) {
        //glColor3f(0.5, 0.1, 0);
        length = sqrt(vx * vx + vy * vy);
        vx = vx / length;
        vy = vy / length;
        printf("INF\n");
        wx = ux - vx;
        wy = uy - vy;
        length = sqrt(wx * wx + wy * wy);
        wx = wx / length;
        wy = wy / length;
      } else {
        //glColor3f(0, 0.6, 0);
        length = sqrt(vx * vx + vy * vy);
        vx = vx / length;
        vy = vy / length;
        wx = -uy;
        wy = ux;
        length = sqrt(wx * wx + wy * wy);
        wx = wx / length;
        wy = wy / length;
      }

      glVertex3f(x1 + wx * size * pixelsize, y1 + wy * size * pixelsize, 0);
      glVertex3f(x1 - wx * size * pixelsize, y1 - wy * size * pixelsize, 0);

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
    wx = wx / length * size * pixelsize;
    wy = wy / length * size * pixelsize;
    GLfloat cx0 = x0 + wx + ux;
    GLfloat cy0 = y0 + wy + uy;
    GLfloat dx0 = x0 - wx + ux;
    GLfloat dy0 = y0 - wy + uy;
    glVertex3f(dx0, dy0, 0);
    glVertex3f(cx0, cy0, 0);
  glEnd();
}

void Draw_Lines_old(int n, GLfloat* points, GLfloat size)
{
  int i = 0;
  GLfloat x0 = *points;
  points++;
  GLfloat y0 = *points;
  points++;

  GLfloat x1 = *points;
  points++;
  GLfloat y1 = *points;
  points++;

  i++;

  GLfloat vx = x1 - x0;
  GLfloat vy = y1 - y0;
  GLfloat wx = -vy;
  GLfloat wy = vx;
  GLfloat length = sqrt(vx * vx + vy * vy);
  wx = wx / length * size * pixelsize;
  wy = wy / length * size * pixelsize;

  GLfloat ax0 = x0 + wx;
  GLfloat ay0 = y0 + wy;
  GLfloat bx0 = x0 - wx;
  GLfloat by0 = y0 - wy;
  GLfloat cx0 = x0 + wx + vx;
  GLfloat cy0 = y0 + wy + vy;
  GLfloat dx0 = x0 - wx + vx;
  GLfloat dy0 = y0 - wy + vy;

  glBegin(GL_TRIANGLE_STRIP);
    while (i < n)
    {
      glVertex3f(ax0, ay0, 0);
      glVertex3f(bx0, by0, 0);
      i++;
      if (i < n)
      {
        GLfloat x2 = *points;
        points++;
        GLfloat y2 = *points;
        points++;

        vx = x2 - x1;
        vy = y2 - y1;
        wx = -vy;
        wy = vx;
        length = sqrt(vx * vx + vy * vy);
        wx = wx / length * size * pixelsize;
        wy = wy / length * size * pixelsize;

        GLfloat ax1 = x1 + wx;
        GLfloat ay1 = y1 + wy;
        GLfloat bx1 = x1 - wx;
        GLfloat by1 = y1 - wy;
        GLfloat cx1 = x1 + wx + vx;
        GLfloat cy1 = y1 + wy + vy;
        GLfloat dx1 = x1 - wx + vx;
        GLfloat dy1 = y1 - wy + vy;
        if (dist(x0, y0, cx0, cy0) > dist(x0, y0, ax1, ay1))
        {
          GLfloat tmp = cx0; cx0 = ax1; ax1 = tmp;
          tmp = cy0; cy0 = ay1; ay1 = tmp;
        }
        else if (dist(x0, y0, dx0, dy0) > dist(x0, y0, bx1, by1))
        {
          GLfloat tmp = dx0; dx0 = bx1; bx1 = tmp;
          tmp = dy0; dy0 = by1; by1 = tmp;
        }
        glVertex3f(cx0, cy0, 0);
        glVertex3f(dx0, dy0, 0);
        x0 = x1;
        y0 = y1;
        x1 = x2;
        y1 = y2;
        ax0 = ax1;
        ay0 = ay1;
        bx0 = bx1;
        by0 = by1;
        cx0 = cx1;
        cy0 = cy1;
        dx0 = dx1;
        dy0 = dy1;
      }
    }
    glVertex3f(cx0, cy0, 0);
    glVertex3f(dx0, dy0, 0);
  glEnd();

}
