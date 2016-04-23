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
  if(w.aerialway!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.aeroway!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.amenity!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.barrier!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.boundary!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.building!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.craft!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.emergency!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.geological!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.highway!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.cycleway!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.busway!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.historic!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.landuse!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.leisure!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.man_made!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.military!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.natural!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.office!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.place!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.power!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.railway!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.brige!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.route!=0){
    r = Tess_Obj_Way(w.size,points,w);
  }else if(w.shop!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.sport!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.tourism!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.waterway!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else if(w.area!=0){
    r = Tess_Obj_Area(w.size,points,w);
  }else{
    Render_Default(w);
    //r = Tess_Obj(w.size,points,w);
    r = 0;
  }

  free(nodes);
  for(i=0;i<w.size;i++){
    free(points[i]);
  }
  free(points);
  return r;
}





GLuint Tess_Obj_Area(int c, GLdouble **points, way w)
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

  GLdouble pos;
  glNewList(id, GL_COMPILE);

  if(w.building!=0){
    BUILDING_COLOR;
    pos = BUILDING_DEPTH;
  }else if(w.natural!=0 && w.natural < 100){
    color_natural(w.natural);
    pos = NATURAL_DEPTH;
  }else if(w.waterway!=0){
    WATERWAY_COLOR;
    pos=WATERWAY_DEPTH;
  }

  int i;
  gluTessBeginPolygon(tess, 0);
  gluTessBeginContour(tess);
  for (i = 0; i < c-1; i++) {
    points[i][2]=pos;
    gluTessVertex(tess, points[i], points[i]);
  }
  gluTessEndContour(tess);
  gluTessEndPolygon(tess);

  gluDeleteTess(tess);

  glColor4f(0.0f,0.0f,0.0f, 0.5f);

  Draw_Lines(c, points,1.0f,pos);

  glEndList();

  return id;
}

GLuint Tess_Obj_Way(int c, GLdouble **points,way w)
{
  GLuint id = glGenLists(1);
  if(!id)
  {
    fprintf(stderr, "failed to create a list, return 0\n");
    return id;
  }
  GLdouble size = 1.0f;
  GLdouble pos = 1.0f;
  glNewList(id, GL_COMPILE);

  /*
  if(w.barrier!=0){
    BARRIER_COLOR;
    size=BARRIER_SIZE;

  }else if (w.boundary!=0){
    switch(w.boundary){
      case BOUNDARY_ADMINISTRATIVE:
      BOUNDARY_ADMINISTRATIVE_COLOR;
      size = BOUNDARY_ADMINISTRATIVE_SIZE;
      break;

      case BOUNDARY_HISTORIC:
      BOUNDARY_HISTORIC_COLOR;
      size = BOUNDARY_HISTORIC_SIZE;
      break;

      case BOUNDARY_MARITIME:
      BOUNDARY_MARITIME_COLOR;
      size = BOUNDARY_MARITIME_SIZE;
      break;

      case BOUNDARY_NATIONAL_PARK:
      BOUNDARY_NATIONAL_PARK_COLOR;
      size = BOUNDARY_NATIONAL_PARK_SIZE;
      break;

      case BOUNDARY_POLITICAL:
      BOUNDARY_POLITICAL_COLOR;
      size = BOUNDARY_POLITICAL_SIZE;
      break;

      case BOUNDARY_POSTAL_CODE:
      BOUNDARY_POSTAL_CODE_COLOR;
      size = BOUNDARY_POSTAL_CODE_SIZE;
      break;

      case BOUNDARY_RELIGIOUS_ADMISTRATION:
      BOUNDARY_RELIGIOUS_ADMISTRATION_COLOR;
      size = BOUNDARY_RELIGIOUS_ADMISTRATION_SIZE;
      break;

      case BOUNDARY_PROTECCTED_AREA:
      BOUNDARY_PROTECCTED_AREA_COLOR;
      size = BOUNDARY_PROTECCTED_AREA_SIZE;
      break;
    }


  }else if (w.cycleway!=0){
    CYCLEWAY_COLOR;
    size=CYCLEWAY_SIZE;

  }else if (w.busway!=0){
    CYCLEWAY_COLOR;
    size=CYCLEWAY_SIZE;


  }else if (w.route!=0){
    ROUTE_COLOR;
    size=ROUTE_SIZE;

  }else if (w.railway!=0){
    RAILWAY_COLOR;
    size=RAILWAY_SIZE;

  }else */
  if (w.highway!=0){
    switch(w.highway){
      case HIGHWAY_MOTORWAY:
      HIGHWAY_MOTORWAY_COLOR;
      size = HIGHWAY_MOTORWAY_SIZE;
      pos = HIGHWAY_MOTORWAY_DEPTH;
      break;
      case HIGHWAY_TRUNK:
      HIGHWAY_TRUNK_COLOR;
      size = HIGHWAY_TRUNK_SIZE;
      pos = HIGHWAY_TRUNK_DEPTH;
      break;
      case HIGHWAY_PRIMARY:
      HIGHWAY_PRIMARY_COLOR;
      size = HIGHWAY_PRIMARY_SIZE;
      pos = HIGHWAY_PRIMARY_DEPTH;
      break;
      case HIGHWAY_SECONDARY:
      HIGHWAY_SECONDARY_COLOR;
      size = HIGHWAY_SECONDARY_SIZE;
      pos = HIGHWAY_SECONDARY_DEPTH;
      break;
      case HIGHWAY_TERTIARY:
      HIGHWAY_TERTIARY_COLOR;
      size = HIGHWAY_TERTIARY_SIZE;
      pos = HIGHWAY_TERTIARY_DEPTH;
      break;
      case HIGHWAY_UNCLASSIFIED:
      HIGHWAY_UNCLASSIFIED_COLOR;
      size = HIGHWAY_UNCLASSIFIED_SIZE;
      pos = HIGHWAY_UNCLASSIFIED_DEPTH;
      break;
      case HIGHWAY_RESIDENTIAL:
      HIGHWAY_RESIDENTIAL_COLOR;
      size = HIGHWAY_RESIDENTIAL_SIZE;
      pos = HIGHWAY_RESIDENTIAL_DEPTH;
      break;
      case HIGHWAY_SERVICE:
      HIGHWAY_SERVICE_COLOR;
      size = HIGHWAY_SERVICE_SIZE;
      pos = HIGHWAY_SERVICE_DEPTH;
      break;
      case HIGHWAY_MOTORWAY_LINK:
      HIGHWAY_MOTORWAY_LINK_COLOR;
      size = HIGHWAY_MOTORWAY_LINK_SIZE;
      pos = HIGHWAY_MOTORWAY_LINK_DEPTH;
      break;
      case HIGHWAY_TRUNK_LINK:
      HIGHWAY_TRUNK_LINK_COLOR;
      size = HIGHWAY_TRUNK_LINK_SIZE;
      pos = HIGHWAY_DEPTH;
      break;
      case HIGHWAY_PRIMARY_LINK:
      HIGHWAY_PRIMARY_LINK_COLOR;
      size = HIGHWAY_PRIMARY_LINK_SIZE;
      pos = HIGHWAY_PRIMARY_LINK_DEPTH;
      break;
      case HIGHWAY_SECONDARY_LINK:
      HIGHWAY_SECONDARY_LINK_COLOR;
      size = HIGHWAY_SECONDARY_LINK_SIZE;
      pos = HIGHWAY_SECONDARY_LINK_DEPTH;
      break;
      case HIGHWAY_TERTIARY_LINK:
      HIGHWAY_TERTIARY_LINK_COLOR;
      size = HIGHWAY_TERTIARY_LINK_SIZE;
      pos = HIGHWAY_TERTIARY_LINK_DEPTH;
      break;
      case HIGHWAY_LIVING_STREET:
      HIGHWAY_LIVING_STREET_COLOR;
      size = HIGHWAY_LIVING_STREET_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
      case HIGHWAY_PEDESTRIAN:
      HIGHWAY_PEDESTRIAN_COLOR;
      size = HIGHWAY_PEDESTRIAN_SIZE;
      pos = HIGHWAY_PEDESTRIAN_DEPTH;
      break;
    }
  }else if(w.natural!=0 && w.natural>=100 && w.natural<=200){
      color_natural(w.natural);
      size = 5.0f;
      pos = WATERWAY_DEPTH;
  }

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);
  Draw_Lines(c, points, size, pos);
  glDisable(GL_POLYGON_OFFSET_FILL);
  if (DEBUG)
  {
    glColor4f(0.5f, 0.9f, 0.5f, 0.8f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Draw_Lines(c, points, size, pos);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glEndList();

  // printf("creating Tess_Obj: %d\n", id);

  return id;
}
