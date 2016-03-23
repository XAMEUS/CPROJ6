#include "load.h"
#include "draw.h"
#include <GL/glu.h>
#include "tessellation.h"
#include "render.h"



GLuint tessellate(way w){
  listref *list = w.nodesref;
  node **nodes = malloc(w.size*sizeof(node*));
  GLdouble **points = malloc(w.size*sizeof(GLdouble*));
  int i=0;
  while(i<w.size){
    nodes[i]=getNode(list->ref);
    points[i] = malloc(3*sizeof(GLdouble));
    points[i][0]=nodes[i]->x;
    points[i][1]=nodes[i]->y;
    points[i][2]=0;
    list = list->next;
    i = i+1;
  }

  GLuint r;
  if(w.highway!=0){
    r = Tess_Obj_Highway(w.size,points,w);
  }else if(w.building!=0){
    r = Tess_Obj_Building(w.size,points);
  }else{
    Render_Default(w);
    //r = Tess_Obj(w.size,points);
    r = 0;
  }

  free(nodes);
  for(i=0;i<w.size;i++){
    free(points[i]);
  }
  free(points);
  return r;
}





GLuint Tess_Obj_Building(int c, GLdouble **points)
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
  glColor3f(0.5f,0.5f,0.5f);
  gluTessBeginPolygon(tess, 0);
    gluTessBeginContour(tess);
      for (i = 0; i < c-1; i++)
        gluTessVertex(tess, points[i], points[i]);
    gluTessEndContour(tess);
  gluTessEndPolygon(tess);
  glEndList();

  gluDeleteTess(tess);

  printf("creating Tess_Obj: %d\n", id);

  return id;
}

GLuint Tess_Obj_Highway(int c, GLdouble **points,way w)
{
  GLuint id = glGenLists(1);
  if(!id)
  {
    fprintf(stderr, "failed to create a list, return 0\n");
    return id;
  }

  GLfloat* tmp = malloc(2*c*sizeof(GLfloat));

  int i;
  for(i=0;i<c;i++){
    tmp[i*2]=points[i][0];
    tmp[(i*2)+1]=points[i][1];
  }


  glNewList(id, GL_COMPILE);
  GLfloat size = 1.0f;
  switch(w.highway){
    case HIGHWAY_MOTORWAY:
      HIGHWAY_MOTORWAY_COLOR;
      size = HIGHWAY_MOTORWAY_SIZE;
      break;
    case HIGHWAY_TRUNK:
      HIGHWAY_TRUNK_COLOR;
      size = HIGHWAY_TRUNK_SIZE;
      break;
    case HIGHWAY_PRIMARY:
      HIGHWAY_PRIMARY_COLOR;
      size = HIGHWAY_PRIMARY_SIZE;
      break;
    case HIGHWAY_SECONDARY:
      HIGHWAY_SECONDARY_COLOR;
      size = HIGHWAY_SECONDARY_SIZE;
      break;
    case HIGHWAY_TERTIARY:
      HIGHWAY_TERTIARY_COLOR;
      size = HIGHWAY_TERTIARY_SIZE;
      break;
    case HIGHWAY_UNCLASSIFIED:
      HIGHWAY_UNCLASSIFIED_COLOR;
      size = HIGHWAY_UNCLASSIFIED_SIZE;
      break;
    case HIGHWAY_RESIDENTIAL:
      HIGHWAY_RESIDENTIAL_COLOR;
      size = HIGHWAY_RESIDENTIAL_SIZE;
      break;
    case HIGHWAY_SERVICE:
      HIGHWAY_SERVICE_COLOR;
      size = HIGHWAY_SERVICE_SIZE;
      break;
  }
  Draw_Lines(c,tmp,size);
  glEndList();


  printf("creating Tess_Obj: %d\n", id);

  return id;
}
