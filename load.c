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
  if(w.hidden==0){
    if(w.area!=0){
      r = Tess_Obj_Area(w.size,points,w);
    }else if(w.highway!=0){
      r = Tess_Obj_Way(w.size,points,w);
    }else if(w.railway!=0){
      r = Tess_Obj_Way(w.size,points,w);
    }else if(w.building!=0){
      r = Tess_Obj_Area(w.size,points,w);
    }else if(w.natural!=0 && w.natural<100){
      r = Tess_Obj_Area(w.size,points,w);
    }else if(w.natural!=0 && w.natural>100 && w.natural<200){
      r = Tess_Obj_Way(w.size,points,w);
    }else if(w.inner!=0){
      r = Tess_Obj_Area(w.size,points,w);
    }else if(w.leisure!=0 && w.leisure<100){
      r = Tess_Obj_Area(w.size,points,w);
    }else if(w.leisure!=0 && w.leisure>100 && w.leisure<200){
      r = Tess_Obj_Way(w.size,points,w);
    }else if(w.waterway!=0 && w.waterway<100){
      r = Tess_Obj_Area(w.size,points,w);
    }else if(w.waterway!=0 && w.waterway>100 && w.waterway<200){
      r = Tess_Obj_Way(w.size,points,w);
    }
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
  int border = 0;
  glNewList(id, GL_COMPILE);

  if(w.highway==HIGHWAY_PEDESTRIAN){
    HIGHWAY_PEDESTRIAN_COLOR;
    pos=-4.9f;
    border =2;
  }else if(w.building!=0){
    BUILDING_COLOR;
    pos = BUILDING_DEPTH;
    border = 1;
  }else if(w.natural!=0){
    color_natural(w.natural);
    pos = NATURAL_DEPTH;
  }else if(w.waterway!=0){
    WATERWAY_COLOR;
    pos=WATERWAY_DEPTH;
  }else if(w.leisure!=0){
    color_leisure(w.leisure);
    pos=LEISURE_DEPTH;
  }else if(w.landuse!=0){
    color_landuse(w.landuse);
    pos=LEISURE_DEPTH;
  }else if(w.inner!=0){
    border=1;
    glColor3f(0.80f, 0.85f, 0.81f);
    if(w.inner>1){
      pos=BUILDING_DEPTH+0.1f;
    }else{
      pos=BACKGROUND_DEPTH;
    }
  }else if(w.bridge){
    BRIDGE_COLOR;
    pos=BRIDGE_DEPTH;
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

  if(border){
    glColor3f(0.3f,0.2f,0.2f);
    if(border == 2){
      glColor3f(0.0f,0.0f,0.0f);
    }
    Draw_Lines(c, points,1.0f,pos);
  }

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

  int border=1;
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
      case HIGHWAY_TRACK:
      HIGHWAY_TRACK_COLOR;
      size=HIGHWAY_TRACK_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
      case HIGHWAY_ROAD:
      HIGHWAY_ROAD_COLOR;
      size=HIGHWAY_ROAD_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
      case HIGHWAY_FOOTWAY:
      HIGHWAY_FOOTWAY_COLOR;
      size=HIGHWAY_FOOTWAY_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
      case HIGHWAY_BRIDLEWAY:
      HIGHWAY_BRIDLEWAY_COLOR;
      size=HIGHWAY_BRIDLEWAY_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
      case HIGHWAY_STEPS:
      HIGHWAY_STEPS_COLOR;
      size=HIGHWAY_STEPS_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
      case HIGHWAY_PATH:
      HIGHWAY_PATH_COLOR;
      size=HIGHWAY_PATH_SIZE;
      pos = HIGHWAY_LIVING_STREET_DEPTH;
      break;
    }
  }else if(w.natural!=0){
      color_natural(w.natural);
      size = 1.0f;
      if(w.natural==NATURAL_COASTLINE){
        size = 10.0f;
      }
      border = 0;
      pos = NATURAL_DEPTH;
  }else if(w.leisure!=0){
      color_leisure(w.leisure);
      size = 1.0f;
      border = 0;
      pos = LEISURE_DEPTH;
  }else if(w.waterway!=0){
      WATERWAY_COLOR;
      pos=WATERWAY_DEPTH;
      border=0;
      switch(w.highway){
          case WATERWAY_RIVER:
          size = WATERWAY_RIVER_SIZE;
          break;
          case WATERWAY_STREAM:
          size = WATERWAY_STREAM_SIZE;
          break;
          case WATERWAY_CANAL:
          size = WATERWAY_CANAL_SIZE;
          break;
          case WATERWAY_DRAIN:
          size = WATERWAY_DRAIN_SIZE;
          break;
          case WATERWAY_DITCH:
          size = WATERWAY_DITCH_SIZE;
          break;
      }
  }else if(w.railway!=0){
    RAILWAY_COLOR;
    size = RAILWAY_SIZE;
    pos=RAILWAY_DEPTH;
  }else if(w.bridge!=0){
    BRIDGE_COLOR;
    pos=BRIDGE_DEPTH;
  }

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);
  Draw_Lines(c, points, size, pos);
  if(border){
    glColor3f(0.0f,0.0f,0.0f);
    Draw_Lines(c,points, size+0.75f, pos-1.0f);
  }
  glDisable(GL_POLYGON_OFFSET_FILL);
  if (DEBUG)
  {
    glColor4f(0.5f, 0.9f, 0.5f, 0.8f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Draw_Lines(c, points, size, pos);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glEndList();

  return id;
}
