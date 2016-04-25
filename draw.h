/**
* \file draw.h
* \brief Drawing functions.
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* Basic drawing.
*
*/

#include "display.h"
#include "tessellation.h"
#include <math.h>

/**
* \brief Pi (constant).
*/
#define PI 3.14159265

/**
* \fn void Draw_Line(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1, GLdouble size, GLdouble depth)
* \brief Draws a line
* \param x0 the x position x of the first point.
* \param y0 the y position en y of the first point.
* \param x1 the x position en x of the second point.
* \param y1 the y position en y of the secondpoint.
* \param size line width.
* \param depth z.
* \return void
*/
void Draw_Line(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1, GLdouble size, GLdouble depth);


/**
* \fn void Draw_Circle(GLdouble x, GLdouble y, GLdouble size, GLdouble depth)
* \brief Draws a circle with origin (x, y).
* \param x0 the x position x of the center.
* \param y0 the y position en y of the center.
* \param size radius.
* \param depth z.
* \return void
*/
void Draw_Circle(GLdouble x, GLdouble y, GLdouble size, GLdouble depth);


/**
* \fn Draw_Lines(int n, GLdouble **points, GLdouble size, GLdouble depth)
* \brief Draw lines.
* \param n number of points.
* \param **points list of points.
* \param size width.
* \param depth z.
* \return void
*/
void Draw_Lines(int n, GLdouble **points, GLdouble size, GLdouble depth);

/**
* \fn void Draw_Lines_old(int n, GLdouble **points, GLdouble size)
* \deprecated Fonction dépréciée, ne plus utiliser !
* \brief old
* \param n number of points.
* \param **points list of points.
* \param size width.
* \return void
*/
void Draw_Lines_old(int n, GLdouble **points, GLdouble size);
