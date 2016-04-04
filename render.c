#include "render.h"
#include "draw.h"
#include <GL/glu.h>
#include "tessellation.h"

int showFrame = 0;
int projection = 1;

void Display_Frame()
{
  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glBegin(GL_LINES);
    glVertex2f(min_x, (max_y-min_y)/2 + min_y);
    glVertex2f(max_x, (max_y-min_y)/2 + min_y);
  glEnd();
  glPopMatrix();

  glColor3f(0.0, 0.0, 1.0);
  glPushMatrix();
  glBegin(GL_LINES);
    glVertex2f((max_x-min_x)/2 + min_x, min_y);
    glVertex2f((max_x-min_x)/2 + min_x, max_y);
  glEnd();
  glPopMatrix();
}

void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom)
{
  // Set the background
  glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
  // Clear The Screen And The Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (showFrame) Display_Frame();

  // Draw points
  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();

  int i;

   for(i=0;i<sizeWays;i++){
      way w = ways[i];
       if(w.waterway!=0){
        WATERWAY;
        Render_Glist(w.glist);
        //Render_Default(w);
      }
  }
  for(i=0;i<sizeWays;i++){
    way w = ways[i];
    if(w.landuse!=0){
      color_landuse(w.landuse);
      Render_Glist(w.glist);
      Render_Default(w);

    }else if(w.natural!=0){
      color_natural(w.natural);
      Render_Glist(w.glist);
      Render_Default(w);
    }
    /*else if(w.leisure!=0){
        color_leisure(w.leisure);
        Render_Glist(w.glist);
        Render_Default(w);
      }
*/
  }
  for(i=0;i<sizeWays;i++){
    way w = ways[i];
    if(w.highway!=0){
      Render_Glist(w.glist);
      if (detail == 10) Render_Border(w);
    }else if(w.building!=0){
      BUILDING;
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.0, 1.0);
      Render_Glist(w.glist);
      glDisable(GL_POLYGON_OFFSET_FILL);
      if (DEBUG)
      {
        glColor4f(0.5f, 0.9f, 0.5f, 0.8f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        Render_Glist(w.glist);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
      glEndList();
      if (detail == 10) Render_Border(w);
  /*  }else if(w.leisure!=0){
      color_leisure(w.leisure);
      Render_Glist(w.glist);
      Render_Default(w);
*/
  /*  }else if(w.area!=0){
      AREA;
      Render_Glist(w.glist);
      Render_Default(w);
    */
  /*  }else if(w.natural!=0){
      color_natural(w.natural);
      Render_Glist(w.glist);
      Render_Default(w);
      */
    }else{
      Render_Default(w);
    }
  }
  //Draw_Line(min_x, min_y, max_x, max_y, 10); BIG PINK DIAGONAL LINE

  glPopMatrix();

  // Render
  SDL_RenderPresent(renderer);
}

void Render_Border(way w)
{
  glColor4f(0.0f,0.0f,0.0f, 0.5f);
  glBegin(GL_LINE_STRIP);
    node *current = NULL;
    node *next = NULL;
    listref *list = w.nodesref;
    if(list){
      current = getNode(list->ref);
      list = list->next;
    }
    while(list){
      next = getNode(list->ref);
      if(current)
        glVertex2f(current->x,current->y);
      current = next;
      list = list->next;
    }
    if(current)
      glVertex2f(current->x,current->y);
  glEnd();
}

void Render_Glist(GLuint i){
  glCallList(i);
}

void Render_Default(way w){
  glColor3f(1.0f,0.0f,1.0f);
  glBegin(GL_LINE_STRIP);
    node *current = NULL;
    node *next = NULL;
    listref *list = w.nodesref;
    if(list){
      current = getNode(list->ref);
      list = list->next;
    }
    while(list){
      next = getNode(list->ref);
      if(current)
        glVertex2f(current->x,current->y);
      current = next;
      list = list->next;
    }
    if(current)
      glVertex2f(current->x,current->y);
  glEnd();
}

void color_natural(int n){
  switch(n){
    case NATURAL_WOOD :
      NATURAL_WOOD_COLOR;
      break;
    case NATURAL_TREE_ROW :
      NATURAL_TREE_ROW_COLOR;
      break;
    case NATURAL_TREE :
      NATURAL_TREE_COLOR;
      break;
    case NATURAL_SCRUB :
      NATURAL_SCRUB_COLOR;
      break;
    case NATURAL_HEATH :
      NATURAL_HEATH_COLOR;
      break;
    case NATURAL_GRASSLAND :
      NATURAL_GRASSLAND_COLOR;
      break;
    case NATURAL_FELL :
      NATURAL_FELL_COLOR;
      break;
    case NATURAL_BARE_ROCK :
      NATURAL_BARE_ROCK_COLOR;
      break;
    case NATURAL_SCREE :
      NATURAL_SCREE_COLOR;
      break;
    case NATURAL_SHINGLE :
      NATURAL_SHINGLE_COLOR;
      break;
    case NATURAL_SAND :
      NATURAL_SAND_COLOR;
      break;
    case NATURAL_MUD :
      NATURAL_MUD_COLOR;
      break;
    case NATURAL_WATER :
      NATURAL_WATER_COLOR;
      break;
    case NATURAL_WETLAND :
      NATURAL_WETLAND_COLOR;
      break;
    case NATURAL_GLACIER :
      NATURAL_GLACIER_COLOR;
      break;
    case NATURAL_BAY :
      NATURAL_BAY_COLOR;
      break;
    case NATURAL_BEACH :
      NATURAL_BEACH_COLOR;
      break;
    case NATURAL_COASTLINE :
      NATURAL_COASTLINE_COLOR;
      break;
    case NATURAL_SPRING :
      NATURAL_SPRING_COLOR;
      break;
    case NATURAL_HOT_SPRING :
      NATURAL_HOT_SPRING_COLOR;
      break;
    case NATURAL_GEYSER :
      NATURAL_GEYSER_COLOR;
      break;
  }

}

void color_landuse (int n){
  switch(n){
    case LANDUSE_ALLOTMENTS :
      LANDUSE_ALLOTMENTS_COLOR;
      break;
    case LANDUSE_BASIN :
      LANDUSE_BASIN_COLOR;
      break;
    case LANDUSE_BROWNFIELD :
      LANDUSE_BROWNFIELD_COLOR;
      break;
    case LANDUSE_CEMTERY :
      LANDUSE_CEMTERY_COLOR;
      break;
    case LANDUSE_COMMERCIAL :
      LANDUSE_COMMERCIAL_COLOR;
      break;
    case LANDUSE_CONSTRUCTION :
      LANDUSE_CONSTRUCTION_COLOR;
      break;
    case LANDUSE_FARMLAND :
      LANDUSE_FARMLAND_COLOR;
      break;
    case LANDUSE_FARMYARD :
      LANDUSE_FARMYARD_COLOR;
      break;
    case LANDUSE_FOREST :
      LANDUSE_FOREST_COLOR;
      break;
    case LANDUSE_GARAGES :
      LANDUSE_GARAGES_COLOR;
      break;
    case LANDUSE_GRASS :
      LANDUSE_GRASS_COLOR;
      break;
    case LANDUSE_GREENFIELD :
      LANDUSE_GREENFIELD_COLOR;
      break;
    case LANDUSE_GREENHOUSE_HORTICULTURE :
      LANDUSE_GREENHOUSE_HORTICULTURE_COLOR;
      break;
    case LANDUSE_INDUSTRIAL :
      LANDUSE_INDUSTRIAL_COLOR;
      break;
    case LANDUSE_LANDFILL :
      LANDUSE_LANDFILL_COLOR;
      break;
    case LANDUSE_MEADOW :
      LANDUSE_MEADOW_COLOR;
      break;
    case LANDUSE_MILITARY :
      LANDUSE_MILITARY_COLOR;
      break;
    case LANDUSE_ORCHARD :
      LANDUSE_ORCHARD_COLOR;
      break;
    case LANDUSE_QUARRY :
      LANDUSE_QUARRY_COLOR;
      break;
    case LANDUSE_RAILWWAY :
      LANDUSE_RAILWWAY_COLOR;
      break;
    case LANDUSE_RECREATION_GROUND :
      LANDUSE_RECREATION_GROUND_COLOR;
      break;
    case LANDUSE_RESERVOIR :
      LANDUSE_RESERVOIR_COLOR;
      break;
    case LANDUSE_RESIDENTIAL :
      LANDUSE_RESIDENTIAL_COLOR;
      break;
    case LANDUSE_RETAIL :
      LANDUSE_RETAIL_COLOR;
      break;
    case LANDUSE_VILLAGE_GREEN :
      LANDUSE_VILLAGE_GREEN_COLOR;
      break;
    case LANDUSE_VINEYARD :
      LANDUSE_VINEYARD_COLOR;
      break;

  }
}

void color_leisure (int n){

    switch(n){
      case LEISURE_ADULT_GAMING_CENTRE:
        LEISURE_ADULT_GAMING_CENTRE_COLOR;
        break;
      case LEISURE_AMUSEMENT_ARCADE:
        LEISURE_AMUSEMENT_ARCADE_COLOR;
        break;
      case LEISURE_BEACH_RESORT :
        LEISURE_BEACH_RESORT_COLOR;
        break;
      case LEISURE_BANDSTAND:
        LEISURE_BANDSTAND_COLOR;
        break;
      case LEISURE_BIRD_HIDE :
        LEISURE_BIRD_HIDE_COLOR;
        break;
      case LEISURE_DANCE:
        LEISURE_DANCE_COLOR;
        break;
      case LEISURE_DOG_PARK:
        LEISURE_DOG_PARK_COLOR;
        break;
      case LEISURE_FIREPIT:
        LEISURE_FIREPIT_COLOR;
        break;
      case LEISURE_FISHING :
        LEISURE_FISHING_COLOR;
        break;
      case LEISURE_GARDEN:
        LEISURE_GARDEN_COLOR;
        break;
      case LEISURE_GOLF_COURSE:
        LEISURE_GOLF_COURSE_COLOR;
        break;
      case LEISURE_HACKERSPACE:
        LEISURE_HACKERSPACE_COLOR;
        break;
      case LEISURE_ICE_RINK :
        LEISURE_ICE_RINK_COLOR;
        break;
      case LEISURE_MARINA:
        LEISURE_MARINA_COLOR;
        break;
      case LEISURE_MINIATURE_GOLF:
        LEISURE_MINIATURE_GOLF_COLOR;
        break;
      case LEISURE_NATURE_RESERVE :
        LEISURE_NATURE_RESERVE_COLOR;
        break;
      case LEISURE_PARK:
        LEISURE_PARK_COLOR;
        break;
      case LEISURE_PITCH:
        LEISURE_PITCH_COLOR;
        break;
      case LEISURE_PLAYGROUND:
        LEISURE_PLAYGROUND_COLOR;
        break;
      case LEISURE_SLIPWAY:
        LEISURE_SLIPWAY_COLOR;
        break;
      case LEISURE_SPORT_CENTRE:
        LEISURE_SPORT_CENTRE_COLOR;
        break;
      case LEISURE_STADIUM:
        LEISURE_STADIUM_COLOR;
        break;
      case LEISURE_SUMMER_CAMP :
        LEISURE_SUMMER_CAMP_COLOR;
        break;
      case LEISURE_SWIMMING_AREA:
        LEISURE_SWIMMING_AREA_COLOR;
        break;
      case LEISURE_SWIMMING_POOL:
        LEISURE_SWIMMING_POOL_COLOR;
        break;
      case LEISURE_TRACK:
        LEISURE_TRACK_COLOR;
        break;
      case LEISURE_WATER_PARK:
        LEISURE_WATER_PARK_COLOR;
        break;
        case LEISURE_WILDLIFE_HIDE:
          LEISURE_WILDLIFE_HIDE_COLOR;
          break;

  }
}




void Render_Highway(way w){
  GLdouble size = 1.0f;
  switch(w.highway){
    case HIGHWAY_MOTORWAY:
      HIGHWAY_MOTORWAY_COLOR;
      size = HIGHWAY_MOTORWAY_SIZE;
      break;
    case HIGHWAY_TRUNK:
      HIGHWAY_TRUNK_COLOR;
      size = HIGHWAY_TRUNK_SIZE;
      break;
    case HIGHWAY_PRIMARY:
      HIGHWAY_PRIMARY_COLOR;
      size = HIGHWAY_PRIMARY_SIZE;
      break;
    case HIGHWAY_SECONDARY:
      HIGHWAY_SECONDARY_COLOR;
      size = HIGHWAY_SECONDARY_SIZE;
      break;
    case HIGHWAY_TERTIARY:
      HIGHWAY_TERTIARY_COLOR;
      size = HIGHWAY_TERTIARY_SIZE;
      break;
    case HIGHWAY_UNCLASSIFIED:
      HIGHWAY_UNCLASSIFIED_COLOR;
      size = HIGHWAY_UNCLASSIFIED_SIZE;
      break;
    case HIGHWAY_RESIDENTIAL:
      HIGHWAY_RESIDENTIAL_COLOR;
      size = HIGHWAY_RESIDENTIAL_SIZE;
      break;
    case HIGHWAY_SERVICE:
      HIGHWAY_SERVICE_COLOR;
      size = HIGHWAY_SERVICE_SIZE;
      break;
  }
    listref *list = w.nodesref;
    node **nodes = malloc(w.size*sizeof(node*));
    GLdouble **points = malloc(w.size*sizeof(GLdouble*));
    int i=0;
    while(i<w.size){
      nodes[i]=getNode(list->ref);
      points[i] = malloc(3*sizeof(GLdouble));
      points[i][0]=nodes[i]->x;
      points[i][1]=nodes[i]->y;
      points[i][2]=0;
      list = list->next;
      i = i+1;
    }
    Draw_Lines(w.size, points, size);
    free(nodes);
    free(points);

}

void Render_Building(way w){

  listref *list = w.nodesref;
  node **nodes = malloc(w.size*sizeof(node*));
  GLdouble **points = malloc(w.size*sizeof(GLdouble*));
  int i=0;
  while(i<w.size){
    nodes[i]=getNode(list->ref);
    points[i] = malloc(3*sizeof(GLdouble));
    points[i][0]=nodes[i]->x;
    points[i][1]=nodes[i]->y;
    points[i][2]=0;
    list = list->next;
    i = i+1;
  }

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(0.5f,0.5f,0.5f);

  free(nodes);
  for(i=0;i<w.size;i++){
    free(points[i]);
  }
  free(points);
}
