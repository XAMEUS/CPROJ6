#ifndef __TESSELLATION_H__
#define __TESSELLATION_H__


#include "display.h"
#include <GL/glu.h>

#ifndef CALLBACK
#define CALLBACK
#endif

GLuint Tess_Obj(int c, GLdouble **points);

void tessCallback(GLUtesselator *tess);

void CALLBACK tessBeginCB(GLenum which) ;

void CALLBACK tessEndCB();

/**
* \fn void tessVertexCB(const GLvoid *data)
* \brief draw a vertex.
*/
void CALLBACK tessVertexCB(const GLvoid *data);

void CALLBACK tessVertexCB2(const GLvoid *data);

/**
* \fn void tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData)
* \brief Combine callback is used to create a new vertex where edges intersect.
         In this function, copy the vertex data into local array and compute the
         color of the vertex. And send it back to tessellator, so tessellator pass it
         to vertex callback function.
  \param newVertex the intersect point which tessellator creates for us.
  \param neighborVertex[4] 4 neighbor vertices to cause intersection (given from 3rd param of gluTessVertex()
  \param neighborWeight[4] 4 interpolation weights of 4 neighbor vertices
  \param outData the vertex data to return to tessellator
*/
void CALLBACK tessCombineCB(const GLdouble newVertex[3], const GLdouble *neighborVertex[4],
                            const GLfloat neighborWeight[4], GLdouble **outData);


GLuint Tess_InOut(int inc, GLdouble** in, int outc, GLdouble** out);

#endif
