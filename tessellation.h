/**
* \file tessellation.h
* \brief Tessellation managing
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* Uses glu.
*
*/

#ifndef __TESSELLATION_H__
#define __TESSELLATION_H__

#include "display.h"
#include <GL/glu.h>

#ifndef CALLBACK
#define CALLBACK
#endif

/**
* \fn GLuint Tess_Obj(int c, GLdouble **points)
* \brief Tesselate un polygone.
* \param c nombre de points.
* \param **points liste des points.
* \return GLuint la liste à afficher avec gluTessCallback.
*/
GLuint Tess_Obj(int c, GLdouble ** points);

void tessCallback(GLUtesselator * tess);

GLuint Tess_InOut(int inc, GLdouble ** in, int outc, GLdouble ** out);

#endif
