#ifndef __PARSE_H__
#define __PARSE_H__


#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <math.h>
#include <glib.h>
#include "osm.h"

extern GHashTable* nodes_hashtable;

extern way* ways;
extern GHashTable* ways_hashtable;
extern int sizeWays;

extern relation* relations;
extern int sizeRelations;

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

relation xmlGetRelation(xmlNodePtr cur);

void xmlGetRelations(xmlNodePtr cur);

void initBounds(xmlNodePtr bounds);

int initNodesBounds(char *filename);

#endif
