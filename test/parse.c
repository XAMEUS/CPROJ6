#include "parse.h"

node* nodes = 0;
int sizeNodes = 100;

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
