#ifndef __OSM_H__
#define __OSM_H__

#include "listref.h"
#include <GL/glu.h>

#define HIGHWAY_MOTORWAY 1
#define HIGHWAY_TRUNK 2
#define HIGHWAY_PRIMARY 3
#define HIGHWAY_SECONDARY 4
#define HIGHWAY_TERTIARY 5
#define HIGHWAY_UNCLASSIFIED 6
#define HIGHWAY_RESIDENTIAL 7
#define HIGHWAY_SERVICE 8


struct st_node{
  float lat;
  float lon;
  float x;
  float y;
  long id;
};

typedef struct st_node node;


struct st_way{
  listref *nodesref;
  int highway;
  int building;
  long id;
  int size;
  GLuint glist;
};

typedef struct st_way way;

#endif
