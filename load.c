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
  }else if(w.landuse!=0){
    r = Tess_Obj_Building(w.size,points);
   }else if(w.area!=0){
   r = Tess_Obj_Building(w.size,points);
 }else if(w.leisure!=0){
   r = Tess_Obj_Building(w.size,points);
 }else if(w.natural!=0){
   r = Tess_Obj_Building(w.size,points);
  }else if(w.waterway!=0){
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
  gluTessBeginPolygon(tess, 0);
    gluTessBeginContour(tess);
      for (i = 0; i < c-1; i++)
        gluTessVertex(tess, points[i], points[i]);
    gluTessEndContour(tess);
  gluTessEndPolygon(tess);

  gluDeleteTess(tess);

  printf("creating Tess_Obj: %d\n", id);

  glEndList();

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

  glNewList(id, GL_COMPILE);

  GLdouble size = 1.0f;
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
    case HIGHWAY_MOTORWAY_LINK:
      HIGHWAY_MOTORWAY_LINK_COLOR;
      size = HIGHWAY_MOTORWAY_LINK_SIZE;
      break;
    case HIGHWAY_TRUNK_LINK:
      HIGHWAY_TRUNK_LINK_COLOR;
      size = HIGHWAY_TRUNK_LINK_SIZE;
      break;
    case HIGHWAY_PRIMARY_LINK:
      HIGHWAY_PRIMARY_LINK_COLOR;
      size = HIGHWAY_PRIMARY_LINK_SIZE;
      break;
    case HIGHWAY_SECONDARY_LINK:
      HIGHWAY_SECONDARY_LINK_COLOR;
      size = HIGHWAY_SECONDARY_LINK_SIZE;
      break;
    case HIGHWAY_TERTIARY_LINK:
      HIGHWAY_TERTIARY_LINK_COLOR;
      size = HIGHWAY_TERTIARY_LINK_SIZE;
      break;
    case HIGHWAY_LIVING_STREET:
      HIGHWAY_LIVING_STREET_COLOR;
      size = HIGHWAY_LIVING_STREET_SIZE;
      break;
    case HIGHWAY_PEDESTRIAN:
      HIGHWAY_PEDESTRIAN_COLOR;
      size = HIGHWAY_PEDESTRIAN_SIZE;
      break;
    case HIGHWAY_TRACK:
      HIGHWAY_TRACK_COLOR;
      size = HIGHWAY_TRACK_SIZE;
      break;
      case HIGHWAY_BUS_GUIDEWAY:
        HIGHWAY_BUS_GUIDEWAY_COLOR;
        size = HIGHWAY_BUS_GUIDEWAY_SIZE;
        break;
      case HIGHWAY_RACEWAY:
        HIGHWAY_RACEWAY_COLOR;
        size = HIGHWAY_RACEWAY_SIZE;
        break;
      case HIGHWAY_ROAD:
        HIGHWAY_ROAD_COLOR;
        size = HIGHWAY_ROAD_SIZE;
        break;
      case HIGHWAY_FOOTWAY:
        HIGHWAY_FOOTWAY_COLOR;
        size = HIGHWAY_FOOTWAY_SIZE;
        break;
      case HIGHWAY_BRIDLEWAY:
        HIGHWAY_STEPS_COLOR;
        size = HIGHWAY_PATH_SIZE;
        break;
      case HIGHWAY_CYCLEWAY:
        HIGHWAY_CYCLEWAY_COLOR;
        size = HIGHWAY_CYCLEWAY_SIZE;
        break;
      case HIGHWAY_PROPOSED:
        HIGHWAY_PROPOSED_COLOR;
        size = HIGHWAY_PROPOSED_SIZE;
        break;
      case HIGHWAY_MINI_ROUNDABOUT:
        HIGHWAY_MINI_ROUNDABOUT_COLOR;
        size = HIGHWAY_CONSTRUCTION_SIZE;
        break;
      case HIGHWAY_CONSTRUCTION:
        HIGHWAY_CONSTRUCTION_COLOR;
        size = HIGHWAY_CONSTRUCTION_SIZE;
        break;
      case HIGHWAY_REST_AREA:
        HIGHWAY_REST_AREA_COLOR;
        size = HIGHWAY_REST_AREA_SIZE;
        break;
      case HIGHWAY_SERVICES:
        HIGHWAY_SERVICES_COLOR;
        size = HIGHWAY_SERVICES_SIZE;
        break;
      case HIGHWAY_TURNING_CICLE:
        HIGHWAY_TURNING_CICLE_COLOR;
        size = HIGHWAY_TURNING_CICLE_SIZE;
        break;
  }

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);
  Draw_Lines(c, points, size, 0.1);
  glDisable(GL_POLYGON_OFFSET_FILL);
  if (DEBUG)
  {
    glColor4f(0.5f, 0.9f, 0.5f, 0.8f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Draw_Lines(c, points, size, 0.5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glEndList();

  printf("creating Tess_Obj: %d\n", id);

  return id;
}
