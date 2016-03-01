#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <math.h>
#include "listref.h"

struct st_node{
  float lat;
  float lon;
  float x;
  float y;
  int id;
};

typedef struct st_node node;


struct st_way{
  listref *nodesref;
};

typedef struct st_way way;

extern node* nodes;
extern int sizeNodes;

extern way* ways;
extern int sizeWays;

extern float minlat;
extern float maxlat;
extern float minlon;
extern float maxlon;

extern float minx;
extern float maxx;
extern float miny;
extern float maxy;

xmlNodePtr xmlGetNode(xmlNodePtr cur, char* name);

void xmlGetNodes(xmlNodePtr cur);

way xmlGetWay(xmlNodePtr cur);

void xmlGetWays(xmlNodePtr cur);

void initBounds(xmlNodePtr bounds);

int initNodesBounds(char *filename);
