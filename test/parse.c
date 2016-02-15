#include "parse.h"

void parseNode( xmlDocPtr doc, xmlNodePtr cur){
  xmlAttr* attribute = cur->properties;
  xmlChar *val;
  while(attribute){
    val = xmlNodeListGetString(doc,attribute->children,1);
    printf("%s=%s\n",attribute->name,val);
    xmlFree(val);
    attribute = attribute->next;
  }
  xmlFree(attribute);
  return;
}

xmlNodePtr getNode(xmlDocPtr doc, xmlNodePtr cur, char* name){
  cur = cur->xmlChildrenNode;
  while(cur != NULL){
    printf("%s",cur->name);
    if(xmlStrcmp(cur->name,(const xmlChar *)name)==0){
        return cur;
    }
    cur=cur->next;
  }
  return cur;
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
