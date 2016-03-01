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
  node *n = malloc(sizeof(node));
  for(i=0;i<sizeWays;i++){
    glBegin(GL_LINES);
      listref *list = ways[i].nodesref;
      while(list){
        n = getNode(list->ref);
        glVertex2f(n->x,n->y);
        list = list->next;
      }
      glEnd();
  }
  /*
  glBegin(GL_POINTS);
    if(projection){
      for(i=0;i<sizeNodes;i++){
        glVertex2f(nodes[i].x,nodes[i].y);
      }
    }
    else{
      for(i=0;i<sizeNodes;i++){
        glVertex2f(nodes[i].lon,nodes[i].lat);
      }
    }
  glEnd();
  */
  //Draw_Line(min_x, min_y, max_x, max_y, 10); BIG PINK DIAGONAL LINE

  glPopMatrix();

  // Render
  SDL_RenderPresent(renderer);
}