#include "listref.h"

listref *listref_create(long ref, int type, int role)
{
	listref *element = malloc(sizeof(listref));
	if (element) {
		element->ref = ref;
		element->type = type;
		element->role = role;
		element->next = NULL;
	}
	return element;
}

listref *listref_append(listref * list, long ref, int type, int role)
{
	listref **plist = &list;
	while (*plist)
		plist = &(*plist)->next;
	*plist = listref_create(ref, type, role);
	if (*plist)
		return list;
	else
		return NULL;
}
