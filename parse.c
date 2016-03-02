#include <string.h>
#include "parse.h"


node* nodes = NULL;
way* ways = NULL;

int sizeNodes = 100;
int sizeWays = 100;

float minlat = 39.7492900;
float maxlat = 39.7525610;
float minlon = -104.9737800;
float maxlon = -104.9693810;
float midlon = 0;

float minx = -1;
float maxx = 1;
float miny = -1;
float maxy = 1;

node *getNode(int ref){
  int i;
  for(i=0;i<sizeNodes;i++){
    if(nodes[i].id==ref)
      return &nodes[i];
  }
  return NULL;
}

xmlNodePtr xmlGetNode(xmlNodePtr cur, char* name){
  while(cur != NULL){
    printf("%s",cur->name);
    if(xmlStrcmp(cur->name,(const xmlChar *)name)==0){
        return cur;
    }
    cur=cur->next;
  }
  return cur;
}

void initBounds(xmlNodePtr bounds){
    minlat = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"minlat"));
    maxlat = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"maxlat"));
    minlon = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"minlon"));
    maxlon = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"maxlon"));
    midlon = ((maxlon-minlon)/2)+minlon;
    minx = minlon;
    maxx = maxlon;
    miny = (((log(tan(M_PI/4+((((minlat)/2)*M_PI)/180))))*180)/M_PI);
    maxy = (((log(tan(M_PI/4+((((maxlat)/2)*M_PI)/180))))*180)/M_PI);
}

void xmlGetNodes(xmlNodePtr cur){
  nodes = malloc(sizeof(node)*100);
  cur = cur->xmlChildrenNode;
  int i = 0;
  node n;
  while(cur != NULL){
    if(i==sizeNodes){
      sizeNodes*=2;
      nodes = realloc(nodes,sizeof(node)*sizeNodes);
    }
    if(xmlStrcmp(cur->name,(const xmlChar *)"node")==0){
      n.lat = atof((const char*)xmlGetProp(cur,(const xmlChar*)"lat"));
      n.lon = atof((const char*)xmlGetProp(cur,(const xmlChar*)"lon"));
      n.x = n.lon;
      n.y = (((log(tan(M_PI/4+((((n.lat)/2)*M_PI)/180))))*180)/M_PI);
      n.id = atol((const char*)xmlGetProp(cur,(const xmlChar*)"id"));
      nodes[i]=n;
      i++;
    }
    cur=cur->next;
  }
  sizeNodes=i;
}

way xmlGetWay(xmlNodePtr cur){
  way w;
  cur = cur->xmlChildrenNode;
  w.nodesref = malloc(sizeof(listref));
  w.nodesref = NULL;
  w.highway = 0;
  while(cur!=NULL){
    if(xmlStrcmp(cur->name,(const xmlChar *)"nd")==0){
      w.nodesref = listref_append(w.nodesref,atol((const char*)xmlGetProp(cur,(const xmlChar*)"ref")));
    }
    if(xmlStrcmp(cur->name,(const xmlChar *)"tag")==0){
      char *k = (char*)xmlGetProp(cur,(const xmlChar*)"k");
      char *v = (char*)xmlGetProp(cur,(const xmlChar*)"v");
      if(strcmp(k,"highway")==0){
        if(strcmp(v,"motorway")==0){
          w.highway=HIGHWAY_MOTORWAY;
        }else if(strcmp(v,"trunk")==0){
          w.highway=HIGHWAY_TRUNK;
        }else if(strcmp(v,"primary")==0){
          w.highway=HIGHWAY_PRIMARY;
        }else if(strcmp(v,"secondary")==0){
          w.highway=HIGHWAY_SECONDARY;
        }else if(strcmp(v,"tertiary")==0){
          w.highway=HIGHWAY_TERTIARY;
        }else if(strcmp(v,"unclassified")==0){
          w.highway=HIGHWAY_UNCLASSIFIED;
        }else if(strcmp(v,"residential")==0){
          w.highway=HIGHWAY_RESIDENTIAL;
        }else if(strcmp(v,"service")==0){
          w.highway=HIGHWAY_SERVICE;
        }
      }else{

      }
    }
    cur=cur->next;
  }
  return w;

}

void xmlGetWays(xmlNodePtr cur){
  ways = malloc(sizeof(way)*100);
  cur = cur->xmlChildrenNode;
  int i = 0;
  while(cur != NULL){
    if(i==sizeWays){
      sizeWays*=2;
      ways = realloc(ways,sizeof(way)*sizeWays);
    }
    if(xmlStrcmp(cur->name,(const xmlChar *)"way")==0){
      ways[i]=xmlGetWay(cur);
      i++;
    }
    cur=cur->next;
  }
  sizeWays=i;
}



int initNodesBounds(char *filename){
  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseFile(filename);
  if(doc==NULL){
    fprintf(stderr,"Erreur parse\n");
    return 1;
  }

  cur = xmlDocGetRootElement(doc);
  if(cur == NULL){
    fprintf(stderr,"Erreur tree\n");
    return 2;
  }

  xmlNodePtr bounds = xmlGetNode(cur->xmlChildrenNode, "bounds");
  if(bounds == NULL){
    fprintf(stderr,"Erreur bounds\n");
    return 2;
  }
  cur = xmlDocGetRootElement(doc);

  initBounds(bounds);

  xmlGetNodes(cur);

  xmlGetWays(cur);

  return 0;
}
