#include "display.h"
#include "tessellation.h"
#include <math.h>

#define PI 3.14159265

void Draw_Line(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1, GLdouble size);

void Draw_Circle(GLdouble x, GLdouble y, GLdouble size);

void Draw_Lines(int n, GLdouble **points, GLdouble size);

void Draw_Lines_old(int n, GLdouble **points, GLdouble size);
