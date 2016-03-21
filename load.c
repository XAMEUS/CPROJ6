#include "load.h"
#include "draw.h"
#include <GL/glu.h>
#include "tessellation.h"

int showFrame = 0;
int projection = 1;



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

  Gluint r = tessObj(w.size,points); // IF ELSE POUR CHAQUE TYPE DE WAY

  free(nodes);
  for(i=0;i<w.size;i++){
    free(points[i]);
  }
  free(points);
  return r;
}
