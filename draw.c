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
  wx = wx / length * size * pixelsize;
  wy = wy / length * size * pixelsize;

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
      /*if (vx < 0) {
        length = sqrt(vx * vx + vy * vy);
        vx = vx / length;
        vy = vy / length;
        printf("INF\n");
        wx = ux - vx;
        wy = uy - vy;
        length = sqrt(wx * wx + wy * wy);
        wx = wx / length;
        wy = wy / length;
        GLdouble teta = acos((ux * vx + uy * vy) / (sqrt(ux*ux+uy*uy)*sqrt(vx*vx+vy*vy)));
        printf("%lf %lf\n", teta, teta * 180 / PI);
        if (teta < PI) {
          //glColor3f(0.5, 0.5, 0.5);
          wx = -wx;
          wy = -wy;
        }
      } else { */
        //glColor3f(0, 0.8, 0.5);
        length = sqrt(vx * vx + vy * vy);
        vx = vx / length;
        vy = vy / length;
        wx = -uy;
        wy = ux;
        length = sqrt(wx * wx + wy * wy);
        wx = wx / length;
        wy = wy / length;


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
    GLdouble cx0 = x0 + wx + ux;
    GLdouble cy0 = y0 + wy + uy;
    GLdouble dx0 = x0 - wx + ux;
    GLdouble dy0 = y0 - wy + uy;
    glVertex3f(cx0, cy0, 0);
    glVertex3f(dx0, dy0, 0);
  glEnd();
}

void Draw_Lines_old(int n, GLdouble* points, GLdouble size)
{
  int i = 0;
  GLdouble x0 = *points;
  points++;
  GLdouble y0 = *points;
  points++;

  GLdouble x1 = *points;
  points++;
  GLdouble y1 = *points;
  points++;

  i++;

  GLdouble vx = x1 - x0;
  GLdouble vy = y1 - y0;
  GLdouble wx = -vy;
  GLdouble wy = vx;
  GLdouble length = sqrt(vx * vx + vy * vy);
  wx = wx / length * size * pixelsize;
  wy = wy / length * size * pixelsize;

  GLdouble ax0 = x0 + wx;
  GLdouble ay0 = y0 + wy;
  GLdouble bx0 = x0 - wx;
  GLdouble by0 = y0 - wy;
  GLdouble cx0 = x0 + wx + vx;
  GLdouble cy0 = y0 + wy + vy;
  GLdouble dx0 = x0 - wx + vx;
  GLdouble dy0 = y0 - wy + vy;

  glBegin(GL_TRIANGLE_STRIP);
    while (i < n)
    {
      glVertex3f(ax0, ay0, 0);
      glVertex3f(bx0, by0, 0);
      i++;
      if (i < n)
      {
        GLdouble x2 = *points;
        points++;
        GLdouble y2 = *points;
        points++;

        vx = x2 - x1;
        vy = y2 - y1;
        wx = -vy;
        wy = vx;
        length = sqrt(vx * vx + vy * vy);
        wx = wx / length * size * pixelsize;
        wy = wy / length * size * pixelsize;

        GLdouble ax1 = x1 + wx;
        GLdouble ay1 = y1 + wy;
        GLdouble bx1 = x1 - wx;
        GLdouble by1 = y1 - wy;
        GLdouble cx1 = x1 + wx + vx;
        GLdouble cy1 = y1 + wy + vy;
        GLdouble dx1 = x1 - wx + vx;
        GLdouble dy1 = y1 - wy + vy;
        if (dist(x0, y0, cx0, cy0) > dist(x0, y0, ax1, ay1))
        {
          GLdouble tmp = cx0; cx0 = ax1; ax1 = tmp;
          tmp = cy0; cy0 = ay1; ay1 = tmp;
        }
        else if (dist(x0, y0, dx0, dy0) > dist(x0, y0, bx1, by1))
        {
          GLdouble tmp = dx0; dx0 = bx1; bx1 = tmp;
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
