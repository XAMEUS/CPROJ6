#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>
#include "parse.h"

static float rotAngle = 0.0;

static float minlat = 39.7492900;
static float maxlat = 39.7525610;
static float minlon = -104.9737800;
static float maxlon = -104.9693810;

static float pixelsize = 1;

void initNodesBounds(char *filename){
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

  xmlNodePtr bounds = getNode(cur->xmlChildrenNode, "bounds");
  if(bounds == NULL){
    fprintf(stderr,"Erreur bounds\n");
    return 2;
  }
  cur = xmlDocGetRootElement(doc);

  SDL_Window *window; // Declare a pointer, main window
  int width = 640;
  int height = 480;
  float dx = 0;
  float dy = 0;
  float zoom = 1.0;
  minlat = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"minlat"));
  maxlat = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"maxlat"));
  minlon = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"minlon"));
  maxlon = atof((const char*)xmlGetProp(bounds,(const xmlChar*)"maxlon"));

  getNodes(cur);
}

void Display_InitGL()
{
  // Antialiasing
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glLineWidth(1.6f);
}

void Display_Frame() {

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glRotatef(-rotAngle, 0.0, 0.0, 0.1);
  glBegin(GL_POINTS);
    int i;
    for(i=0;i<sizeNodes;i++){
      glVertex2f(nodes[i].lon,nodes[i].lat);
    }
  glEnd();
  glPopMatrix();

}

void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom)
{
  // Set the background
  glClearColor(0.f, 0.f, 0.f, 0.0f);
  // Clear The Screen And The Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Display_Frame();

  // Render
  SDL_RenderPresent(renderer);
}

// function to reset our viewport after a window resize
void Display_SetViewport(int width, int height, float dx, float dy, float minlat, float minlon, float maxlat, float maxlon, float zoom)
{
  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (width <= height) {
    pixelsize = (maxlon-minlon)/width;
    glOrtho(
      (minlon + maxlon) / 2 + dx - zoom * (maxlon - minlon) / 2,
      (minlon + maxlon) / 2 + dx + zoom * (maxlon - minlon) / 2,
      (minlat + maxlat) / 2 + dy - zoom * (pixelsize * height / 2),
      (minlat + maxlat) / 2 + dy + zoom * (pixelsize * height / 2),
      -1.0,
      1.0
    );
  }
  else {
    pixelsize = (maxlat-minlat)/height;
    glOrtho(
      (minlon + maxlon) / 2 + dx - zoom * (pixelsize * width / 2),
      (minlon + maxlon) / 2 + dx + zoom * (pixelsize * width / 2),
      (minlat + maxlat) / 2 + dy - zoom * (maxlat - minlat) / 2,
      (minlat + maxlat) / 2 + dy + zoom * (maxlat - minlat) / 2,
      -1.0,
      1.0
    );
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char* argv[])
{

  SDL_Window *window; // Declare a pointer, main window
  int width = 640;
  int height = 480;
  float dx = 0;
  float dy = 0;

  float zoom = 1.0;

  initNodesBounds(argv[1]);

  // Initialize SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "SDL2 - OpenGL",            // window title
    SDL_WINDOWPOS_UNDEFINED,    // initial x position
    SDL_WINDOWPOS_UNDEFINED,    // initial y position
    width,                      // width, in pixels
    height,                     // height, in pixels
    SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE        // flags
  );

  // Check that the window was successfully created
  if (window == NULL)
  {
    // In the case that the window could not be made...
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "Press the 'F' key to switch fullscreen.\n");
  fprintf(stdout, "Press the 'R' key to reset the view.\n");
  fprintf(stdout, "Press the [x] button to close the window.\n");

  SDL_Renderer* displayRenderer = NULL;
  SDL_RendererInfo displayRendererInfo;
  displayRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
  if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
    (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
    fprintf(stderr, "We have no render surface and not accelerated.\n");
  }

  Display_InitGL();

  Display_SetViewport(
    width, height,
    dx,
    dy,
    minlat,
    minlon,
    maxlat,
    maxlon,
    zoom
  );

  int fullscreen = 0;
  int drag = 0;
  int xcursor = 0;
  int ycursor = 0;
  SDL_Event event;
  int quit = 0;
  time_t t = time(NULL);
  time_t ctime = time(NULL);
  int frames = 0;
  while (!quit)
  {
    Display_SetViewport(
      width, height,
      dx,
      dy,
      minlat,
      minlon,
      maxlat,
      maxlon,
      zoom
    );
    Display_Render(displayRenderer, width, height, dx, dy, zoom);
    while (SDL_PollEvent(&event)) // User's actions
    {
      switch(event.type)
      {
        case SDL_QUIT: // Close button
          quit = 1;
          break;
        case SDL_KEYUP: // Key release
          if (event.key.keysym.sym == SDLK_f) // F key
          {
            if (fullscreen == 0)
            {
              fullscreen = 1;
              SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
            }
            else if (fullscreen == 1)
            {
              fullscreen = 0;
              SDL_SetWindowFullscreen(window, 0);
            }
          }
          if (event.key.keysym.sym == SDLK_r)
          {
            zoom = 1.0;
            dx = 0.0;
            dy = 0.0;
          }
          break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
              width = event.window.data1;
              height = event.window.data2;
              break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              width = event.window.data1;
              height = event.window.data2;
              break;
            default:
              // printf("Window %d got unknown event %d\n", event.window.windowID, event.window.event);
              break;
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT)
            drag = 1;
          break;
        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT)
            drag = 0;
          break;
        case SDL_MOUSEMOTION:
          xcursor = event.motion.x;
          ycursor = event.motion.y;
          if (drag != 0) {
            dx -= pixelsize * event.motion.xrel * zoom;
            dy += pixelsize * event.motion.yrel * zoom;
          }
          break;
        case SDL_MOUSEWHEEL:
          if (zoom > 0.01) {
            dx = dx + 0.01 * pixelsize * event.wheel.y * (xcursor - width / 2);
            dy = dy - 0.01 * pixelsize * event.wheel.y * (ycursor - height / 2);
          }
          if (event.wheel.y > 0 && zoom > 0.01)
            zoom -= 0.01;
          else if (event.wheel.y < 0)
            zoom += 0.01;
          break;
        default:
          //printf("unknown event");
          break;
      }
    }
    frames++;
    ctime = time(NULL);
    if (t != ctime) {
      t = ctime;
      fprintf(stdout, "%d fps\n", frames);
      frames = 0;
    }
  }

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();

  return EXIT_SUCCESS;
}
