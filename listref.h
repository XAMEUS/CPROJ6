#ifndef __LISTREF_H__
#define __LISTREF_H__


#include <stdlib.h>


typedef struct st_listref listref;

struct st_listref{
  listref *next;
  long ref;
};

listref *listref_create(long ref);

listref *listref_append(listref *list, long ref);

#endif
