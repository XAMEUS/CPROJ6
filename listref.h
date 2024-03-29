/**
* \file listref.h
* \brief LinkedList
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* LinkedList tools
*
*/

#ifndef __LISTREF_H__
#define __LISTREF_H__

#include <stdlib.h>

#define REF_NODE 0
#define REF_WAY 1
#define REF_RELATION 2

#define ROLE_NONE 0
#define ROLE_INNER 1
#define ROLE_OUTER 2
#define ROLE_STOP 3
#define ROLE_FORWARD 4
#define ROLE_BACKWARD 5
#define ROLE_DEVICE 6
#define ROLE_TO 7
#define ROLE_FROM 8
#define ROLE_STATION 9
#define ROLE_ENTRANCE 10
#define ROLE_SIDESTREAM 11
#define ROLE_TRIBUTARY 12

typedef struct st_listref listref;

/**
* \struct st_listref
* \brief LinkedList.
*/
struct st_listref {
	int type;
	listref *next;
	long ref;
	int role;
};

/**
* \fn listref *listref_create(long ref, int type, int role)
* \brief Create a list.
*/
listref *listref_create(long ref, int type, int role);

/**
* \fn listref *listref_append(listref *list, long ref, int type, int role)
* \brief Add a element to a list.
*/
listref *listref_append(listref * list, long ref, int type, int role);

#endif
