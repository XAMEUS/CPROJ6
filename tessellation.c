#include "tessellation.h"

// store newly created vertices (x, y, z, r, g, b)  by combine callback
GLdouble vertices[64][6];
// array index, incremented inside combine callback
int vertexIndex = 0;

//================================================================================
// GLU_TESS CALLBACKS
//================================================================================

#ifndef CALLBACK
#define CALLBACK
#endif

void CALLBACK tessBeginCB(GLenum which)
{
  glBegin(which);
}

void CALLBACK tessEndCB()
{
  glEnd();
}

/**
* \fn void tessVertexCB(const GLvoid *data)
* \brief draw a vertex.
*/
void CALLBACK tessVertexCB(const GLvoid *data)
{
  const GLdouble *ptr = (const GLdouble*) data;
  glVertex3dv(ptr);
}

/**
* \fn void tessVertexCB2(const GLvoid *data)
* \brief draw a vertex with color.
*/
void CALLBACK tessVertexCB2(const GLvoid *data)
{
  const GLdouble *ptr = (const GLdouble*) data;
  glColor3dv(ptr+3);
  glVertex3dv(ptr);
}

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
                            const GLfloat neighborWeight[4], GLdouble **outData)
{
  // copy new intersect vertex to local array
  // Because newVertex is temporal and cannot be hold by tessellator until next
  // vertex callback called, it must be copied to the safe place in the app.
  // Once gluTessEndPolygon() called, then you can safly deallocate the array.
  vertices[vertexIndex][0] = newVertex[0];
  vertices[vertexIndex][1] = newVertex[1];
  vertices[vertexIndex][2] = newVertex[2];

  // compute vertex color with given weights and colors of 4 neighbors
  // the neighborVertex[4] must hold required info, in this case, color.
  // neighborVertex was actually the third param of gluTessVertex() and is
  // passed into here to compute the color of the intersect vertex.
  vertices[vertexIndex][3] = neighborWeight[0] * neighborVertex[0][3] +   // red
                             neighborWeight[1] * neighborVertex[1][3] +
                             neighborWeight[2] * neighborVertex[2][3] +
                             neighborWeight[3] * neighborVertex[3][3];
  vertices[vertexIndex][4] = neighborWeight[0] * neighborVertex[0][4] +   // green
                             neighborWeight[1] * neighborVertex[1][4] +
                             neighborWeight[2] * neighborVertex[2][4] +
                             neighborWeight[3] * neighborVertex[3][4];
  vertices[vertexIndex][5] = neighborWeight[0] * neighborVertex[0][5] +   // blue
                             neighborWeight[1] * neighborVertex[1][5] +
                             neighborWeight[2] * neighborVertex[2][5] +
                             neighborWeight[3] * neighborVertex[3][5];


  // return output data (vertex coords and others)
  *outData = vertices[vertexIndex];   // assign the address of new intersect vertex

  ++vertexIndex;  // increase index for next vertex
}

void CALLBACK tessErrorCB(GLenum errorCode)
{
  const GLubyte *errorStr;

  errorStr = gluErrorString(errorCode);
  printf("[ERROR]: %s", errorStr);
}

void tessCallback(GLUtesselator *tess)
{
  // register callback functions
  gluTessCallback(tess, GLU_TESS_BEGIN,
                  (GLvoid (CALLBACK*) ()) &tessBeginCB);
  gluTessCallback(tess, GLU_TESS_END,
                  (GLvoid (CALLBACK*) ()) &tessEndCB);
  gluTessCallback(tess, GLU_TESS_ERROR,
                  (GLvoid (CALLBACK*) ()) &tessErrorCB);
  gluTessCallback(tess, GLU_TESS_VERTEX,
                  (GLvoid (CALLBACK*) ()) &tessVertexCB);
  gluTessCallback(tess, GLU_TESS_COMBINE,
                  (GLvoid (CALLBACK*) ()) &tessCombineCB);
}

GLuint Tess_Obj(int c, GLdouble **points)
{
  GLuint id = glGenLists(1);
  if(!id)
  {
    fprintf(stderr, "failed to create a list, return 0\n");
    return id;
  }

  GLUtesselator *tess = gluNewTess();
  if(!tess)
  {
    fprintf(stderr, "failed to create tessellation object, return 0\n");
    return 0;
  };

  tessCallback(tess);

  // tessellate and compile a concave quad into display list
  // gluTessVertex() takes 3 params: tess object, pointer to vertex coords,
  // and pointer to vertex data to be passed to vertex callback.
  // The second param is used only to perform tessellation, and the third
  // param is the actual vertex data to draw. It is usually same as the second
  // param, but It can be more than vertex coord, for example, color, normal
  // and UV coords which are needed for actual drawing.
  // Here, we are looking at only vertex coods, so the 2nd and 3rd params are
  // pointing same address.

  glNewList(id, GL_COMPILE);

  int i;
  gluTessBeginPolygon(tess, 0);
    gluTessBeginContour(tess);
      for (i = 0; i < c; i++)
        gluTessVertex(tess, points[i], points[i]);
    gluTessEndContour(tess);
  gluTessEndPolygon(tess);
  glEndList();

  gluDeleteTess(tess);

  printf("creating Tess_Obj: %d\n", id);

  return id;
}
