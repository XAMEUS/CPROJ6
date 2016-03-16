#include "render.h"
#include "draw.h"

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
      glColor3f(1.0f,0.0f,0.0f);
      size = HIGHWAY_MOTORWAY_SIZE;
      break;
    case HIGHWAY_TRUNK:
      glColor3f(1.0f,0.5f,0.5f);
      size = HIGHWAY_TRUNK_SIZE;
      break;
    case HIGHWAY_PRIMARY:
      glColor3f(1.0f,1.0f,0.0f);
      size = HIGHWAY_PRIMARY_SIZE;
      break;
    case HIGHWAY_SECONDARY:
      glColor3f(1.0f,0.0f,1.0f);
      size = HIGHWAY_SECONDARY_SIZE;
      break;
    case HIGHWAY_TERTIARY:
      glColor3f(0.0f,1.0f,0.0f);
      size = HIGHWAY_TERTIARY_SIZE;
      break;
    case HIGHWAY_UNCLASSIFIED:
      glColor3f(0.0f,1.0f,1.0f);
      size = HIGHWAY_UNCLASSIFIED_SIZE;
      break;
    case HIGHWAY_RESIDENTIAL:
      glColor3f(0.0f,0.5f,0.5f);
      size = HIGHWAY_RESIDENTIAL_SIZE;
      break;
    case HIGHWAY_SERVICE:
      glColor3f(0.5f,0.5f,0.5f);
      size = HIGHWAY_SERVICE_SIZE;
      break;
  }
    node *current = NULL;
    node *next = NULL;
    listref *list = w.nodesref;
    if(list){
      current = getNode(list->ref);
      list = list->next;
    }
    while(list){
      next = getNode(list->ref);
      if(current && next)
      Draw_Line(current->x,current->y,next->x,next->y,size);
      current = next;
      list = list->next;
    }
}
