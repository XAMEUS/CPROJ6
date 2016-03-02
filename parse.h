#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <math.h>
#include "osm.h"

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

node *getNode(long ref);

xmlNodePtr xmlGetNode(xmlNodePtr cur, char* name);

void xmlGetNodes(xmlNodePtr cur);

way xmlGetWay(xmlNodePtr cur);

void xmlGetWays(xmlNodePtr cur);

void initBounds(xmlNodePtr bounds);

int initNodesBounds(char *filename);
