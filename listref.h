#include <stdlib.h>

typedef struct st_listref listref;

struct st_listref{
  listref *next;
  int ref;
};

listref *listref_create(int ref);

listref *listref_append(listref *list, int ref);
