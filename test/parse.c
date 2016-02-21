#include "parse.h"


node* nodes = 0;
int sizeNodes = 100;

float minlat = 39.7492900;
float maxlat = 39.7525610;
float minlon = -104.9737800;
float maxlon = -104.9693810;
float midlon = 0;

float minx = -1;
float maxx = 1;
float miny = -1;
float maxy = 1;

xmlNodePtr getNode(xmlNodePtr cur, char* name){
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

void getNodes(xmlNodePtr cur){
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
      nodes[i]=n;
      i++;
    }
    cur=cur->next;
  }
  sizeNodes=i;
}

/*int main(int argc, char **argv) {
    if (argc != 2)
        return(1);

    LIBXML_TEST_VERSION

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(argv[1]);
    if(doc==NULL){
      fprintf(stderr,"Erreur parse\n");
      return 1;
    }

    cur = xmlDocGetRootElement(doc);

    if(cur == NULL){
      fprintf(stderr,"Erreur tree\n");
      return 2;
    }
    printf("root %s\n",cur->name);
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
      if(xmlStrcmp(cur->name,(const xmlChar *)"bounds")==0){
        printf("=====> %s\n", cur->name);
        parseNode(doc,cur);
      }
      cur=cur->next;
    }



    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();
    return(0);
}*/
