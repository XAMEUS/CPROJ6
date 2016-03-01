#include "listref.h"

listref *listref_create(int ref){
  listref *element = malloc(sizeof(listref));
  element->ref=ref;
  element->next=NULL;
  return element;
}

listref *listref_append(listref *list, int ref){
  listref **plist = &list;
  while (*plist)
    plist = &(*plist)->next;
  *plist = listref_create(ref);
   return list;
}
