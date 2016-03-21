#include "tessellation.h"

void CALLBACK beginCallback(GLenum which)
{
   glBegin(which);
}

void CALLBACK errorCallback(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf(stderr, "Tessellation Error: %s\n", (char *) estring);
   exit(0);
}

void CALLBACK endCallback(void)
{
   glEnd();
}

void CALLBACK vertexCallback(GLvoid *vertex)
{
   const GLdouble *pointer;

   pointer = (GLdouble *) vertex;
   glColor3dv(pointer+3);
   glVertex3dv(pointer);
}

void CALLBACK combineCallback(GLdouble coords[3],
                     GLdouble *vertex_data[4],
                     GLfloat weight[4], GLdouble **dataOut )
{
   GLdouble *vertex;
   int i;

   vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));

   vertex[0] = coords[0];
   vertex[1] = coords[1];
   vertex[2] = coords[2];
   for (i = 3; i < 6; i++)
      vertex[i] = weight[0] * vertex_data[0][i]
                  + weight[1] * vertex_data[1][i]
                  + weight[2] * vertex_data[2][i]
                  + weight[3] * vertex_data[3][i];
   *dataOut = vertex;
}

void testdrawing(void)
{
   GLUtesselator *tobj;
   GLdouble rect[4][3] = {{50.0, 50.0, 0.0},
                          {200.0, 50.0, 0.0},
                          {200.0, 200.0, 0.0},
                          {50.0, 200.0, 0.0}};
   GLdouble tri[3][3] = {{75.0, 75.0, 0.0},
                         {125.0, 175.0, 0.0},
                         {175.0, 75.0, 0.0}};
   GLdouble star[5][6] = {{250.0, 50.0, 0.0, 1.0, 0.0, 1.0},
                          {325.0, 200.0, 0.0, 1.0, 1.0, 0.0},
                          {400.0, 50.0, 0.0, 0.0, 1.0, 1.0},
                          {250.0, 150.0, 0.0, 1.0, 0.0, 0.0},
                          {400.0, 150.0, 0.0, 0.0, 1.0, 0.0}};

   glClearColor(0.0, 0.0, 0.0, 0.0);


   tobj = gluNewTess();
   gluTessCallback(tobj, GLU_TESS_VERTEX,
                   (GLvoid (CALLBACK*) ()) &glVertex3dv);
   gluTessCallback(tobj, GLU_TESS_BEGIN,
                   (GLvoid (CALLBACK*) ()) &beginCallback);
   gluTessCallback(tobj, GLU_TESS_END,
                   (GLvoid (CALLBACK*) ()) &endCallback);
   gluTessCallback(tobj, GLU_TESS_ERROR,
                   (GLvoid (CALLBACK*) ()) &errorCallback);

   /*  rectangle with triangular hole inside  */
   glShadeModel(GL_FLAT);
   gluTessBeginPolygon(tobj, NULL);
      gluTessBeginContour(tobj);
         gluTessVertex(tobj, rect[0], rect[0]);
         gluTessVertex(tobj, rect[1], rect[1]);
         gluTessVertex(tobj, rect[2], rect[2]);
         gluTessVertex(tobj, rect[3], rect[3]);
      gluTessEndContour(tobj);
      gluTessBeginContour(tobj);
         gluTessVertex(tobj, tri[0], tri[0]);
         gluTessVertex(tobj, tri[1], tri[1]);
         gluTessVertex(tobj, tri[2], tri[2]);
      gluTessEndContour(tobj);
   gluTessEndPolygon(tobj);
   glEndList();

   gluTessCallback(tobj, GLU_TESS_VERTEX,
                   (GLvoid (CALLBACK*) ()) &vertexCallback);
   gluTessCallback(tobj, GLU_TESS_BEGIN,
                   (GLvoid (CALLBACK*) ()) &beginCallback);
   gluTessCallback(tobj, GLU_TESS_END,
                   (GLvoid (CALLBACK*) ()) &endCallback);
   gluTessCallback(tobj, GLU_TESS_ERROR,
                   (GLvoid (CALLBACK*) ()) &errorCallback);
   gluTessCallback(tobj, GLU_TESS_COMBINE,
                   (GLvoid (CALLBACK*) ()) &combineCallback);

   /*  smooth shaded, self-intersecting star  */
   glShadeModel(GL_SMOOTH);
   gluTessProperty(tobj, GLU_TESS_WINDING_RULE,
                   GLU_TESS_WINDING_POSITIVE);
   gluTessBeginPolygon(tobj, NULL);
      gluTessBeginContour(tobj);
         gluTessVertex(tobj, star[0], star[0]);
         gluTessVertex(tobj, star[1], star[1]);
         gluTessVertex(tobj, star[2], star[2]);
         gluTessVertex(tobj, star[3], star[3]);
         gluTessVertex(tobj, star[4], star[4]);
      gluTessEndContour(tobj);
   gluTessEndPolygon(tobj);
   glEndList();
   gluDeleteTess(tobj);
}
