#include "listref.h"

listref *listref_create(long ref){
  listref *element = malloc(sizeof(listref));
  if(element){
    element->ref=ref;
    element->next=NULL;
  }
  return element;
}

listref *listref_append(listref *list, long ref){
  listref **plist = &list;
      while (*plist)
         plist = &(*plist)->next;
      *plist = listref_create(ref);
      if (*plist)
         return list;
      else
         return NULL;
}
