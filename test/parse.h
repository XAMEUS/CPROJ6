#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <math.h>

struct st_node{
  float lat;
  float lon;
  float x;
  float y;
};

typedef struct st_node node;

extern node* nodes;

extern float minlat;
extern float maxlat;
extern float minlon;
extern float maxlon;

extern float minx;
extern float maxx;
extern float miny;
extern float maxy;

extern int sizeNodes;

xmlNodePtr getNode(xmlNodePtr cur, char* name);

void getNodes(xmlNodePtr cur);

void initBounds(xmlNodePtr bounds);

int initNodesBounds(char *filename);
