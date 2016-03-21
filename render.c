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
    if(w.highway!=0){
      Render_Highway(w);
    }else if(w.building!=0){
      //Render_Building(w);
      Render_Default(w);
    }else{
      Render_Default(w);
    }
  }
  //Draw_Line(min_x, min_y, max_x, max_y, 10); BIG PINK DIAGONAL LINE

  glPopMatrix();

  // Render
  SDL_RenderPresent(renderer);
}

void Render_Default(way w){
  glColor3f(0.0f,0.0f,0.0f);
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

void Render_Highway(way w){
  GLfloat size = 1.0f;
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
    GLfloat *points = malloc(w.size*2*sizeof(GLfloat));
    int i=0;
    while(i<w.size){
      nodes[i]=getNode(list->ref);
      points[i*2]=nodes[i]->x;
      points[(i*2)+1]=nodes[i]->y;
      list = list->next;
      i = i+1;
    }
    Draw_Lines(w.size,points,size);
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
