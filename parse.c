#include <string.h>
#include "parse.h"

GHashTable* nodes_hashtable = NULL;
GHashTable* ways_hashtable = NULL;
way* ways = NULL;
relation* relations = NULL;

int sizeWays = 100;
int sizeRelations = 100;

float minlat = 39.7492900;
float maxlat = 39.7525610;
float minlon = -104.9737800;
float maxlon = -104.9693810;
float midlon = 0;

float minx = -1;
float maxx = 1;
float miny = -1;
float maxy = 1;

/*
node *getNode(long ref){
  int i;
  for(i=0;i<sizeNodes;i++){
    if(nodes[i].id==ref)
      return &nodes[i];
  }
  printf("%ld\n",ref);
  return NULL;
}*/

node *getNode(long ref){
  node *n = NULL;
  n = g_hash_table_lookup(nodes_hashtable, &ref);
  return n;
}

xmlNodePtr xmlGetNode(xmlNodePtr cur, char* name){
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
/*
void xmlGetNodes(xmlNodePtr cur){
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
      n.id = atol((const char*)xmlGetProp(cur,(const xmlChar*)"id"));
      nodes[i]=n;
      i++;
    }
    cur=cur->next;
  }
  sizeNodes=i;
}*/

void xmlGetNodes(xmlNodePtr cur){
  nodes_hashtable = g_hash_table_new(g_int64_hash,g_int64_equal);
  cur = cur->xmlChildrenNode;
  node *n = NULL;
  while(cur != NULL){
    n = g_new(node,1);
    if(xmlStrcmp(cur->name,(const xmlChar *)"node")==0){
      n->lat = strtold((const char*)xmlGetProp(cur,(const xmlChar*)"lat"), NULL);
      n->lon = strtold((const char*)xmlGetProp(cur,(const xmlChar*)"lon"), NULL);
      n->x = n->lon;
      n->y = (((log(tan(M_PI/4+((((n->lat)/2)*M_PI)/180))))*180)/M_PI);
      n->id = atol((const char*)xmlGetProp(cur,(const xmlChar*)"id"));
      g_hash_table_insert(nodes_hashtable, &n->id, n);
    }
    cur=cur->next;
  }
}

way xmlGetWay(xmlNodePtr cur){
  way w;
  int n = 0;
  w.id = atol((const char*)xmlGetProp(cur,(const xmlChar*)"id"));
  cur = cur->xmlChildrenNode;
  w.nodesref = malloc(sizeof(listref));
  w.nodesref = NULL;
  w.aerialway=0;
    w.aeroway=0;
   w.amenity=0;
   w.barrier=0;
   w.building=0;
   w.boundary=0;
   w.craft=0;
   w.geological=0;
   w.emergency=0;
   w.highway=0;
   w.cycleway=0;
   w.busway=0;
   w.landuse=0;
   w.historic=0;
   w.leisure=0;
   w.man_made=0;
   w.military=0;
   w.natural=0;
   w.place =0;
   w.office=0;
   w.power=0;
   w.railway=0;
   w.brige=0;
   w.route=0;
   w.shop=0;
   w.tourism=0;
   w.sport=0;
   w.waterway=0;
   w.area=0;

  //printf("way %ld\n", w.id);
  while(cur!=NULL){
    if(xmlStrcmp(cur->name,(const xmlChar *)"nd")==0){
      //if (w.id == 63645087 || w.id == 63643868 || w.id == 78144300 || w.id == 41494697 || w.id == 41494698)
      //  printf("%ld\n", atol((const char*)xmlGetProp(cur,(const xmlChar*)"ref")));
      w.nodesref = listref_append(w.nodesref,atol((const char*)xmlGetProp(cur,(const xmlChar*)"ref")),REF_NODE,ROLE_NONE);
      n++;
    }

    if(xmlStrcmp(cur->name,(const xmlChar *)"tag")==0){
      char *k = (char*)xmlGetProp(cur,(const xmlChar*)"k");
      char *v = (char*)xmlGetProp(cur,(const xmlChar*)"v");


        if(strcmp(k,"aerialway")==0){
          w.aerialway=1;

        }else  if(strcmp(k,"aeroway")==0){
            w.aeroway=1;

        }else  if(strcmp(k,"amenity")==0){
          if(strcmp(v,"bar")==0 ||strcmp(v,"bbq")==0 || strcmp(v,"biergarten")==0 || strcmp(v,"cafe")==0 || strcmp(v,"drinking_water")==0 || strcmp(v,"fast_food")==0 || strcmp(v,"food_court")==0 || strcmp(v,"ice_cream")==0 || strcmp(v,"pub")==0 || strcmp(v,"restaurant")==0 ) {
            w.amenity=AMENITY_CONSOMMATION;
          } else if(strcmp(v,"college")==0 ||strcmp(v,"kindergarten")==0 || strcmp(v,"library")==0 || strcmp(v,"public_bookcase")==0 || strcmp(v,"school")==0 || strcmp(v,"music_school")==0 || strcmp(v,"driving_school")==0 || strcmp(v,"language_school")==0 || strcmp(v,"university")==0 ) {
            w.amenity=AMENITY_EDUCATION;
          } else if(strcmp(v,"bicycle_parking")==0 || strcmp(v,"bicycle_repair_station")==0 || strcmp(v,"bicycle_rental")==0 || strcmp(v,"boat_sharing")==0 || strcmp(v,"bus_station")==0 || strcmp(v,"car_rental")==0 || strcmp(v,"car_sharing")==0 || strcmp(v,"car_wash")==0
          || strcmp(v,"charging_station")==0 || strcmp(v,"ferry_terminal")==0 || strcmp(v,"fuel")==0 || strcmp(v,"grit_bin")==0 || strcmp(v,"motorcycle_parking")==0 || strcmp(v,"parking")==0 || strcmp(v,"parking_entrance")==0 || strcmp(v,"parking_space")==0 || strcmp(v,"parking_space")==0 ) {
            w.amenity=AMENITY_TRANSPORTS;
          } else if(strcmp(v,"atm")==0 ||strcmp(v,"bank")==0 || strcmp(v,"bureau_de_change")==0 ){
            w.amenity=AMENITY_ARGENTS;
          } else if(strcmp(v,"baby_hatch")==0 ||strcmp(v,"clinic")==0 || strcmp(v,"dentist")==0 || strcmp(v,"doctors")==0 || strcmp(v,"hospital")==0 || strcmp(v,"nursing_home")==0 || strcmp(v,"pharmacy")==0 || strcmp(v,"social_facility")==0 || strcmp(v,"veterinary")==0 || strcmp(v,"blood_donation")==0 ){
            w.amenity=AMENITY_SANTE;
          } else if(strcmp(v,"arts_centre")==0 ||strcmp(v,"brothel")==0 || strcmp(v,"casino")==0 || strcmp(v,"cinema")==0 || strcmp(v,"community_centre")==0 || strcmp(v,"fountain")==0 || strcmp(v,"gambling")==0 || strcmp(v,"nightclub")==0 || strcmp(v,"planetarium")==0 || strcmp(v,"social_centre")==0
          || strcmp(v,"stripclub")==0 || strcmp(v,"studio")==0 || strcmp(v,"swingerclub")==0 || strcmp(v,"theatre")==0)  {
            w.amenity=AMENITY_LOISIRS;
          }else
          w.amenity=AMENITY_AUTRES;


        }else  if(strcmp(k,"barrier")==0){
            w.barrier=1;

        }else  if(strcmp(k,"boundary")==0){
              w.boundary=1;

        }else if(strcmp(k, "building")==0){
              w.building=1;

        }else  if(strcmp(k,"craft")==0){
                w.craft=1;

        }else  if(strcmp(k,"emergency")==0){
                w.emergency=1;

        }else  if(strcmp(k,"geological")==0){
            if(strcmp(v,"moraine")==0){
              w.geological=GEOLOGICAL_MORAINE;
            }else if(strcmp(v,"outcrop")==0){
              w.geological=GEOLOGICAL_OUTCROP;
            }else if(strcmp(v,"palaeontological_site")==0){
              w.geological=GEOLOGICAL_PALAEONTOLOGICAL_SITE;
            }

        }else  if(strcmp(k,"highway")==0){
          if(strcmp(v,"motorway")==0){
          w.highway=HIGHWAY_MOTORWAY;
          }else if(strcmp(v,"trunk")==0){
          w.highway=HIGHWAY_TRUNK;
          }else if(strcmp(v,"primary")==0){
          w.highway=HIGHWAY_PRIMARY;
          }else if(strcmp(v,"secondary")==0){
          w.highway=HIGHWAY_SECONDARY;
          }else if(strcmp(v,"tertiary")==0){
          w.highway=HIGHWAY_TERTIARY;
          }else if(strcmp(v,"unclassified")==0){
          w.highway=HIGHWAY_UNCLASSIFIED;
          }else if(strcmp(v,"residential")==0){
          w.highway=HIGHWAY_RESIDENTIAL;
          }else if(strcmp(v,"service")==0){
          w.highway=HIGHWAY_SERVICE;
          }else if(strcmp(v,"motorway_link")==0){
          w.highway=HIGHWAY_MOTORWAY_LINK;
          }else if(strcmp(v,"trunk_link")==0){
          w.highway=HIGHWAY_TRUNK_LINK;
          }else if(strcmp(v,"primary_link")==0){
          w.highway=HIGHWAY_PRIMARY_LINK;
          }else if(strcmp(v,"secondary_link")==0){
          w.highway=HIGHWAY_SECONDARY_LINK;
          }else if(strcmp(v,"tertiary_link")==0){
          w.highway=HIGHWAY_TERTIARY_LINK;
          }else if(strcmp(v,"living_street")==0){
          w.highway=HIGHWAY_LIVING_STREET;
          }else if(strcmp(v,"pedestrian")==0){
          w.highway=HIGHWAY_PEDESTRIAN;
          }else if(strcmp(v,"track")==0){
          w.highway=HIGHWAY_TRACK;
          }else if(strcmp(v,"bus_guideway")==0){
          w.highway=HIGHWAY_BUS_GUIDEWAY;
          }else if(strcmp(v,"raceway")==0){
          w.highway=HIGHWAY_RACEWAY;
          }else if(strcmp(v,"road")==0){
          w.highway=HIGHWAY_ROAD;
          }else if(strcmp(v,"footway")==0){
          w.highway=HIGHWAY_FOOTWAY;
          }else if(strcmp(v,"bridleway")==0){
          w.highway=HIGHWAY_BRIDLEWAY;
          }else if(strcmp(v,"steps")==0){
          w.highway=HIGHWAY_STEPS;
          }else if(strcmp(v,"path")==0){
          w.highway=HIGHWAY_PATH;
          }else if(strcmp(v,"cycleway")==0){
          w.highway=HIGHWAY_CYCLEWAY;
          }else if(strcmp(v,"proposed")==0){
          w.highway=HIGHWAY_PROPOSED;
          }else if(strcmp(v,"construction")==0){
          w.highway=HIGHWAY_CONSTRUCTION;
          }else if(strcmp(v,"mini_roundabout")==0){
          w.highway=HIGHWAY_MINI_ROUNDABOUT;
          }else if(strcmp(v,"motorway_junction")==0){
          w.highway=HIGHWAY_MOTORWAY_JUNCTION;
          }else if(strcmp(v,"rest_area")==0){
          w.highway=HIGHWAY_REST_AREA;
          }else if(strcmp(v,"services")==0){
          w.highway=HIGHWAY_SERVICES;
          }else if(strcmp(v,"turning_circle")==0){
          w.highway=HIGHWAY_TURNING_CICLE;
          }

        }else if(strcmp(k,"cycleway")==0){
            w.cycleway=1;

        }else if(strcmp(k,"busway")==0){
            w.busway=1;

        }else if(strcmp(k,"historic")==0){
            w.historic=1;


     }else if(strcmp(k,"landuse")==0){
          if(strcmp(v,"allotments")==0){
            w.landuse=LANDUSE_ALLOTMENTS;
            }else if(strcmp(v,"basin")==0){
            w.landuse=LANDUSE_BASIN;
            }else if(strcmp(v,"brownfield")==0){
            w.landuse=LANDUSE_BROWNFIELD;
            }else if(strcmp(v,"cemetery")==0){
            w.landuse=LANDUSE_CEMTERY;
            }else if(strcmp(v,"commercial")==0){
            w.landuse=LANDUSE_COMMERCIAL;
            }else if(strcmp(v,"construction")==0){
            w.landuse=LANDUSE_CONSTRUCTION;
            }else if(strcmp(v,"farmland")==0){
            w.landuse=LANDUSE_FARMLAND;
            }else if(strcmp(v,"farmyad")==0){
            w.landuse=LANDUSE_FARMYARD;
            }else if(strcmp(v,"forest")==0){
            w.landuse=LANDUSE_FOREST;
            }else if(strcmp(v,"garages")==0){
            w.landuse=LANDUSE_GARAGES;
            }else if(strcmp(v,"grass")==0){
            w.landuse=LANDUSE_GRASS;
            }else if(strcmp(v,"greenfield")==0){
            w.landuse=LANDUSE_GREENFIELD;
            }else if(strcmp(v,"greenhouse_horiculture")==0){
            w.landuse=LANDUSE_GREENHOUSE_HORTICULTURE;
            }else if(strcmp(v,"indusrial")==0){
            w.landuse=LANDUSE_INDUSTRIAL;
            }else if(strcmp(v,"landfill")==0){
            w.landuse=LANDUSE_LANDFILL;
            }else if(strcmp(v,"meadow")==0){
            w.landuse=LANDUSE_MEADOW;
            }else if(strcmp(v,"military")==0){
            w.landuse=LANDUSE_MILITARY;
            }else if(strcmp(v,"orchard")==0){
            w.landuse=LANDUSE_ORCHARD;
            }else if(strcmp(v,"quarry")==0){
            w.landuse=LANDUSE_QUARRY;
            }else if(strcmp(v,"railway")==0){
            w.landuse=LANDUSE_RAILWWAY;
            }else if(strcmp(v,"recreation_ground")==0){
            w.landuse=LANDUSE_RECREATION_GROUND;
            }else if(strcmp(v,"reservoir")==0){
            w.landuse=LANDUSE_RESERVOIR;
            }else if(strcmp(v,"residential")==0){
            w.landuse=LANDUSE_RESIDENTIAL;
            }else if(strcmp(v,"retail")==0){
            w.landuse=LANDUSE_RETAIL;
            }else if(strcmp(v,"village_green")==0){
            w.landuse=LANDUSE_VILLAGE_GREEN;
            }else if(strcmp(v,"vineyard")==0){
            w.landuse=LANDUSE_VINEYARD;
              }


        }else if(strcmp(k,"leisure")==0){
                      if(strcmp(v,"adult_gaming_center")==0){
                        w.leisure=LEISURE_ADULT_GAMING_CENTRE;
                      }else if(strcmp(v,"amusement_arcade")==0){
                        w.leisure=LEISURE_AMUSEMENT_ARCADE;
                      }else if(strcmp(v,"beach_resort")==0){
                        w.leisure=LEISURE_BEACH_RESORT;
                      }else if(strcmp(v,"bandstand")==0){
                        w.leisure=LEISURE_BANDSTAND;
                      }else if(strcmp(v,"bird_hide")==0){
                        w.leisure=LEISURE_BIRD_HIDE;
                      }else if(strcmp(v,"dance")==0){
                        w.leisure=LEISURE_DANCE;
                      }else if(strcmp(v,"dog_park")==0){
                        w.leisure=LEISURE_DOG_PARK;
                      }else if(strcmp(v,"firepit")==0){
                        w.leisure=LEISURE_FIREPIT;
                      }else if(strcmp(v,"fishing")==0){
                        w.leisure=LEISURE_FISHING;
                      }else if(strcmp(v,"garden")==0){
                        w.leisure=LEISURE_GARDEN;
                      }else if(strcmp(v,"golf_course")==0){
                        w.leisure=LEISURE_GOLF_COURSE;
                      }else if(strcmp(v,"hackerspace")==0){
                        w.leisure=LEISURE_HACKERSPACE;
                      }else if(strcmp(v,"ice_rink")==0){
                        w.leisure=LEISURE_ICE_RINK;
                      }else if(strcmp(v,"marina")==0){
                        w.leisure=LEISURE_MARINA;
                      }else if(strcmp(v,"miniature_golf")==0){
                        w.leisure=LEISURE_MINIATURE_GOLF;
                      }else if(strcmp(v,"nature_reserve")==0){
                        w.leisure=LEISURE_NATURE_RESERVE;
                      }else if(strcmp(v,"park")==0){
                        w.leisure=LEISURE_PARK;
                      }else if(strcmp(v,"pitch")==0){
                        w.leisure=LEISURE_PITCH;
                      }else if(strcmp(v,"playground")==0){
                        w.leisure=LEISURE_PLAYGROUND;
                      }else if(strcmp(v,"slipway")==0){
                        w.leisure=LEISURE_SLIPWAY;
                      }else if(strcmp(v,"sports_centre")==0){
                        w.leisure=LEISURE_SPORT_CENTRE;
                      }else if(strcmp(v,"stadium")==0){
                        w.leisure=LEISURE_STADIUM;
                      }else if(strcmp(v,"summer_camp")==0){
                        w.leisure=LEISURE_SUMMER_CAMP;
                      }else if(strcmp(v,"swimming_area")==0){
                        w.leisure=LEISURE_SWIMMING_AREA;
                      }else if(strcmp(v,"swimming_pool")==0){
                        w.leisure=LEISURE_SWIMMING_POOL;
                      }else if(strcmp(v,"track")==0){
                        w.leisure=LEISURE_TRACK;
                      }else if(strcmp(v,"water_park")==0){
                        w.leisure=LEISURE_WATER_PARK;
                      }else if(strcmp(v,"wildlife_hide")==0){
                        w.leisure=LEISURE_WILDLIFE_HIDE;
                      }
                  }else if(strcmp(k,"man_made")==0){
                        w.man_made=1;

                  }else if(strcmp(k,"military")==0){
                          w.military=1;

                  }else if(strcmp(k,"natural")==0){
                              if(strcmp(v,"wood")==0){
                                w.natural=NATURAL_WOOD;
                              }else if(strcmp(v,"tree_row")==0){
                                w.natural=NATURAL_TREE_ROW;
                              }else if(strcmp(v,"tree_tree")==0){
                                w.natural=NATURAL_TREE;
                              }else if(strcmp(v,"scrub")==0){
                                w.natural=NATURAL_SCRUB;
                              }else if(strcmp(v,"heath")==0){
                                w.natural=NATURAL_HEATH;
                              }else if(strcmp(v,"grassland")==0){
                                w.natural=NATURAL_GRASSLAND;
                              }else if(strcmp(v,"fell")==0){
                                w.natural=NATURAL_FELL;
                              }else if(strcmp(v,"bare_rock")==0){
                                w.natural=NATURAL_BARE_ROCK;
                              }else if(strcmp(v,"scree")==0){
                                w.natural=NATURAL_SCREE;
                              }else if(strcmp(v,"shingle")==0){
                                w.natural=NATURAL_SHINGLE;
                              }else if(strcmp(v,"sand")==0){
                                w.natural=NATURAL_SAND;
                              }else if(strcmp(v,"mud")==0){
                                w.natural=NATURAL_MUD;
                              }else if(strcmp(v,"water")==0){
                                w.natural=NATURAL_WATER;
                              }else if(strcmp(v,"wetland")==0){
                                w.natural=NATURAL_SCRUB;
                              }else if(strcmp(v,"wetland")==0){
                                w.natural=NATURAL_WETLAND;
                              }else if(strcmp(v,"glacier")==0){
                                w.natural=NATURAL_GLACIER;
                              }else if(strcmp(v,"bay")==0){
                                w.natural=NATURAL_BAY;
                              }else if(strcmp(v,"beach")==0){
                                w.natural=NATURAL_BEACH;
                              }else if(strcmp(v,"coastline")==0){
                                w.natural=NATURAL_COASTLINE;
                              }else if(strcmp(v,"spring")==0){
                                w.natural=NATURAL_SPRING;
                              }else if(strcmp(v,"hot_spring")==0){
                                w.natural=NATURAL_HOT_SPRING;
                              }else if(strcmp(v,"geyser")==0){
                                w.natural=NATURAL_GEYSER;
                              }else if(strcmp(v,"land")==0){
                                w.natural=NATURAL_LAND;
                              }

                      }else if(strcmp(k,"office")==0){
                      w.office=1;

                  }else if(strcmp(k,"place")==0){
                      w.place=1;

                  }else if(strcmp(k,"power")==0){
                      w.power=1;

                  }else if(strcmp(k,"railway")==0){
                      w.railway=1;

                  }else if(strcmp(k,"brige")==0){
                      w.brige=1;

                    }else if(strcmp(k,"route")==0){
                        w.route=1;

                  }else if(strcmp(k,"shop")==0){
                      w.shop=1;

                  }else if(strcmp(k,"sport")==0){
                      w.sport=1;

                  }else if(strcmp(k,"tourism")==0){
                      w.tourism=1;

                  }else if(strcmp(k,"waterway")==0){
                        if(strcmp(v,"riverbank")==0){
                          w.waterway=1;
                    }

                  }else if(strcmp(k,"area")==0){
                        if(strcmp(v,"yes")==0){
                          if(strcmp(k,"highway")!=0){
                          w.area=1;
                          }
                        }






}
}

    cur=cur->next;
  }
  w.size=n;
  //printf("size : %d\n", w.size);
  //printf("----------\n\n");
  return w;

}

void xmlGetWays_array(xmlNodePtr cur){
  ways = malloc(sizeof(way)*100);
  cur = cur->xmlChildrenNode;
  int i = 0;
  while(cur != NULL){
    if(i==sizeWays){
      sizeWays*=2;
      ways = realloc(ways,sizeof(way)*sizeWays);
    }
    if(xmlStrcmp(cur->name,(const xmlChar *)"way")==0){
      ways[i]=xmlGetWay(cur);
      i++;
    }
    cur=cur->next;
  }
  sizeWays=i;
}

void xmlGetWays(xmlNodePtr cur){
  xmlGetWays_array(cur);
  ways_hashtable = g_hash_table_new(g_int64_hash,g_int64_equal);
  cur = cur->xmlChildrenNode;
  way *w = NULL;
  while(cur != NULL){
    w = g_new(way,1);
    if(xmlStrcmp(cur->name,(const xmlChar *)"way")==0){
      *w = xmlGetWay(cur);
      g_hash_table_insert(ways_hashtable, &w->id, w);
    }
    cur=cur->next;
  }
}

relation xmlGetRelation(xmlNodePtr cur){
  relation r;
  int n = 0;
  r.id = atol((const char*)xmlGetProp(cur,(const xmlChar*)"id"));
  cur = cur->xmlChildrenNode;
  r.member = malloc(sizeof(listref));
  r.member = NULL;
  while(cur!=NULL){
    if(xmlStrcmp(cur->name,(const xmlChar *)"member")==0){
      int role = ROLE_NONE;
      char *str_role = (char*)xmlGetProp(cur,(const xmlChar*)"role");
      if(strcmp(str_role,"inner")==0){
        role = ROLE_INNER;
      }else if(strcmp(str_role,"outer")==0){
        role = ROLE_OUTER;
      }else if(strcmp(str_role,"stop")==0){
        role = ROLE_STOP;
      }else if(strcmp(str_role,"forward")==0){
        role = ROLE_FORWARD;
      }else if(strcmp(str_role,"backward")==0){
        role = ROLE_BACKWARD;
      }else if(strcmp(str_role,"device")==0){
        role = ROLE_DEVICE;
      }else if(strcmp(str_role,"to")==0){
        role = ROLE_TO;
      }else if(strcmp(str_role,"from")==0){
        role = ROLE_FROM;
      }else if(strcmp(str_role,"station")==0){
        role = ROLE_STATION;
      }else if(strcmp(str_role,"entrance")==0){
        role = ROLE_ENTRANCE;
      }else if(strcmp(str_role,"sidestream")==0){
        role = ROLE_SIDESTREAM;
      }else if(strcmp(str_role,"TRIBUTARY")==0){
        role = ROLE_TRIBUTARY;
      }

      int type = REF_WAY;
      char *str_type = (char*)xmlGetProp(cur,(const xmlChar*)"type");
      if(strcmp(str_type,"node")==0){
        type = REF_NODE;
      }else if(strcmp(str_type,"relation")==0){
        type = REF_RELATION;
      }

      r.member = listref_append(r.member,atol((const char*)xmlGetProp(cur,(const xmlChar*)"ref")),type,role);
      n++;
    }

    if(xmlStrcmp(cur->name,(const xmlChar *)"tag")==0){
      char *k = (char*)xmlGetProp(cur,(const xmlChar*)"k");
      char *v = (char*)xmlGetProp(cur,(const xmlChar*)"v");
      if(strcmp(k,"type")==0){
        if(strcmp(v,"multipolygon")==0){
          r.type = RELATION_MULTIPOLYGON;
        }else if(strcmp(v,"waterway")==0){
          r.type = RELATION_WATERWAY;
        }else{
          r.type = RELATION_UNDEFINED;
        }
      }

    }

    cur=cur->next;
  }
  r.size=n;
  return r;

}

void xmlGetRelations(xmlNodePtr cur){
  relations = malloc(sizeof(relation)*100);
  cur = cur->xmlChildrenNode;
  int i = 0;
  while(cur != NULL){
    if(i==sizeRelations){
      sizeRelations*=2;
      relations = realloc(relations,sizeof(relation)*sizeRelations);
    }
    if(xmlStrcmp(cur->name,(const xmlChar *)"relation")==0){
      relations[i]=xmlGetRelation(cur);
      i++;
    }
    cur=cur->next;
  }
  sizeRelations=i;
}


int initNodesBounds(char *filename){
  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlParseFile(filename);
  if(doc==NULL){
    fprintf(stderr,"Erreur parse\n");
    return 1;
  }

  cur = xmlDocGetRootElement(doc);
  if(cur == NULL){
    fprintf(stderr,"Erreur tree\n");
    return 2;
  }

  xmlNodePtr bounds = xmlGetNode(cur->xmlChildrenNode, "bounds");
  if(bounds == NULL){
    fprintf(stderr,"Erreur bounds\n");
    return 2;
  }
  cur = xmlDocGetRootElement(doc);

  initBounds(bounds);

  xmlGetNodes(cur);

  xmlGetWays(cur);

  return 0;
}
