
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef CALLBACK
#define CALLBACK
#endif

void CALLBACK beginCallback(GLenum which);

void CALLBACK errorCallback(GLenum errorCode);

void CALLBACK endCallback(void);

void CALLBACK vertexCallback(GLvoid *vertex);

void CALLBACK combineCallback(GLdouble coords[3],GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut );

void testdrawing(void);
