#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

struct st_node{
  float lat;
  float lon;
};

typedef struct st_node node;

extern node* nodes;

extern int sizeNodes;

xmlNodePtr getNode(xmlNodePtr cur, char* name);

void getNodes(xmlNodePtr cur);
