/**
* \file osm.h
* \brief OpenStreetMap objects
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* Define OpenStreetMap objects.
*
*/

#ifndef __OSM_H__
#define __OSM_H__

#include "listref.h"
#include <GL/glu.h>

#define AMENITY_CONSOMMATION 1
#define AMENITY_EDUCATION 2
#define AMENITY_TRANSPORTS 3
#define AMENITY_ARGENTS 4
#define AMENITY_SANTE 5
#define AMENITY_LOISIRS 6
#define AMENITY_AUTRES 7

#define BOUNDARY_ADMINISTRATIVE 1
#define BOUNDARY_HISTORIC 2
#define BOUNDARY_MARITIME 3
#define BOUNDARY_NATIONAL_PARK 4
#define BOUNDARY_POLITICAL 5
#define BOUNDARY_POSTAL_CODE 6
#define BOUNDARY_RELIGIOUS_ADMISTRATION 7
#define BOUNDARY_PROTECCTED_AREA 8

#define GEOLOGICAL_MORAINE 1
#define GEOLOGICAL_OUTCROP 2
#define GEOLOGICAL_PALAEONTOLOGICAL_SITE 3

#define HIGHWAY_MOTORWAY 1
#define HIGHWAY_TRUNK 2
#define HIGHWAY_PRIMARY 3
#define HIGHWAY_SECONDARY 4
#define HIGHWAY_TERTIARY 5
#define HIGHWAY_UNCLASSIFIED 6
#define HIGHWAY_RESIDENTIAL 7
#define HIGHWAY_SERVICE 8
#define HIGHWAY_MOTORWAY_LINK 9
#define HIGHWAY_TRUNK_LINK 10
#define HIGHWAY_PRIMARY_LINK 11
#define HIGHWAY_SECONDARY_LINK 12
#define HIGHWAY_TERTIARY_LINK 13
#define HIGHWAY_LIVING_STREET 14
#define HIGHWAY_PEDESTRIAN 15
#define HIGHWAY_TRACK 16
#define HIGHWAY_BUS_GUIDEWAY 17
#define HIGHWAY_RACEWAY 18
#define HIGHWAY_ROAD 19
#define HIGHWAY_FOOTWAY 20
#define HIGHWAY_BRIDLEWAY 21
#define HIGHWAY_STEPS 22
#define HIGHWAY_PATH 23
#define HIGHWAY_CYCLEWAY 24
#define HIGHWAY_PROPOSED 25
#define HIGHWAY_CONSTRUCTION 26
#define HIGHWAY_MINI_ROUNDABOUT 27
#define HIGHWAY_MOTORWAY_JUNCTION 28
#define HIGHWAY_REST_AREA 29
#define HIGHWAY_SERVICES 30
#define HIGHWAY_TURNING_CICLE 31

#define LEISURE_ADULT_GAMING_CENTRE 1
#define LEISURE_AMUSEMENT_ARCADE 2
#define LEISURE_BEACH_RESORT 3
#define LEISURE_BANDSTAND 4
#define LEISURE_BIRD_HIDE 5
#define LEISURE_DANCE 6
#define LEISURE_DOG_PARK 7
#define LEISURE_FIREPIT 8
#define LEISURE_FISHING 9
#define LEISURE_GARDEN 10
#define LEISURE_GOLF_COURSE 11
#define LEISURE_HACKERSPACE 12
#define LEISURE_ICE_RINK 13
#define LEISURE_MARINA 14
#define LEISURE_MINIATURE_GOLF 15
#define LEISURE_NATURE_RESERVE 16
#define LEISURE_PARK 17
#define LEISURE_PITCH 18
#define LEISURE_PLAYGROUND 19
#define LEISURE_SLIPWAY 120
#define LEISURE_SPORT_CENTRE 21
#define LEISURE_STADIUM 22
#define LEISURE_SUMMER_CAMP 23
#define LEISURE_SWIMMING_AREA 24
#define LEISURE_SWIMMING_POOL 25
#define LEISURE_TRACK 26
#define LEISURE_WATER_PARK 27
#define LEISURE_WILDLIFE_HIDE 28

#define NATURAL_WOOD 1
#define NATURAL_TREE_ROW 102
#define NATURAL_TREE 203
#define NATURAL_SCRUB 4
#define NATURAL_HEATH 5
#define NATURAL_GRASSLAND 6
#define NATURAL_FELL 7
#define NATURAL_BARE_ROCK 8
#define NATURAL_SCREE 9
#define NATURAL_SHINGLE 10
#define NATURAL_SAND 11
#define NATURAL_MUD 12
#define NATURAL_WATER 13
#define NATURAL_WETLAND 14
#define NATURAL_GLACIER 15
#define NATURAL_BAY 16
#define NATURAL_BEACH 17
#define NATURAL_COASTLINE 118
#define NATURAL_SPRING 219
#define NATURAL_HOT_SPRING 220
#define NATURAL_GEYSER 221
#define NATURAL_LAND 222

#define LANDUSE_ALLOTMENTS 1
#define LANDUSE_BASIN 2
#define LANDUSE_BROWNFIELD 3
#define LANDUSE_CEMTERY 4
#define LANDUSE_COMMERCIAL 5
#define LANDUSE_CONSTRUCTION 6
#define LANDUSE_FARMLAND 7
#define LANDUSE_FARMYARD 8
#define LANDUSE_FOREST 9
#define LANDUSE_GARAGES 10
#define LANDUSE_GRASS 11
#define LANDUSE_GREENFIELD 12
#define LANDUSE_GREENHOUSE_HORTICULTURE 13
#define LANDUSE_INDUSTRIAL 14
#define LANDUSE_LANDFILL 15
#define LANDUSE_MEADOW 16
#define LANDUSE_MILITARY 17
#define LANDUSE_ORCHARD 18
#define LANDUSE_QUARRY 19
#define LANDUSE_RAILWWAY 20
#define LANDUSE_RECREATION_GROUND 21
#define LANDUSE_RESERVOIR 22
#define LANDUSE_RESIDENTIAL 23
#define LANDUSE_RETAIL 24
#define LANDUSE_VILLAGE_GREEN 25
#define LANDUSE_VINEYARD 26

#define WATERWAY_RIVER 101
#define WATERWAY_RIVERBANK 2
#define WATERWAY_STREAM 103
#define WATERWAY_CANAL 104
#define WATERWAY_DRAIN 105
#define WATERWAY_DITCH 106
#define WATERWAY_DOCK 7

#define RELATION_UNDEFINED 0
#define RELATION_MULTIPOLYGON 1
#define RELATION_ROUTE 2
#define RELATION_BOUNDARY 3
#define RELATION_RESTRICTION 4
#define RELATION_ROUTE_MASTER 5
#define RELATION_WATERWAY 6

struct st_node {
	long double lat;
	long double lon;
	double x;
	double y;
	long id;
};

typedef struct st_node node;

struct st_way {
	listref *nodesref;

	int hidden;
	int inner;
	int aerialway;
	int aeroway;
	int amenity;
	int barrier;
	int boundary;
	int building;
	int craft;
	int emergency;
	int geological;
	int highway;
	int cycleway;
	int busway;
	int historic;
	int landuse;
	int leisure;
	int man_made;
	int military;
	int natural;
	int office;
	int place;
	int power;
	int railway;
	int bridge;
	int route;
	int shop;
	int sport;
	int tourism;
	int waterway;
	int area;

	long id;
	int size;
	GLuint glist;
};

typedef struct st_way way;

struct st_relation {
	listref *member;
	int type;
	long id;
	int size;
};

typedef struct st_relation relation;

#endif
