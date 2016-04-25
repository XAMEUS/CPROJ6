#include "draw.h"
#include "load.h"
#include <GL/glu.h>

int width = 640;
int height = 480;

#define size 4

void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom);

void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom)
{
  // Set the background
  glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
  // Clear The Screen And The Depth Buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLdouble quad1[size][2] = { {500,100}, {400,200}, {300,350}, {150,400}};
  //GLdouble quad1[4][2] = { {500,350}, {350,400}, {200,350}, {150,200} };
  GLdouble *rows1[size] = { quad1[0], quad1[1], quad1[2], quad1[3]};
  GLdouble **data1 = rows1;

  GLdouble ux = quad1[1][0] - quad1[0][0];
  GLdouble uy = quad1[1][1] - quad1[0][1];
  GLdouble vx = quad1[2][0] - quad1[1][0];
  GLdouble vy = quad1[2][1] - quad1[1][1];
  GLdouble wx = quad1[3][0] - quad1[2][0];
  GLdouble wy = quad1[3][1] - quad1[2][1];
  GLdouble length = sqrt(ux * ux + uy * uy);
  ux = ux / length;
  uy = uy / length;
  length = sqrt(vx * vx + vy * vy);
  vx = vx / length;
  vy = vy / length;
  printf("u: (%lf, %lf)\n", ux, uy);
  printf("v: (%lf, %lf)\n", vx, vy);
  printf("w: (%lf, %lf)\n", wx, wy);
  printf("%lf\n", atan2(-uy, -ux) - atan2(vy, vx));
  printf("%lf\n", atan2(-vy, -vx) - atan2(wy, wx));

  glColor3f(0.9, 0.9, 0.2);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);
  Draw_Lines(size, data1, 20, 0);
  glDisable(GL_POLYGON_OFFSET_FILL);

  glColor3f (0.9, 0.1, 0.1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  Draw_Lines(size, data1, 20, 0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glPopMatrix();

  // Render
  SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{

  SDL_Window *window; // Declare a pointer, main window
  GLfloat dx = 0;
  GLfloat dy = 0;
  GLfloat zoom = 1.0;
  min_x = 0;
  max_x = width;
  min_y = 0;
  max_y = height;

  // Initialize SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "Drawing - OpenGL",            // window title
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
  Display_Render(displayRenderer, width, height, dx, dy, zoom);
  while (!quit)
  {
    Display_SetViewport(
      width, height,
      dx,
      dy,
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
          if (event.key.keysym.sym == SDLK_KP_PLUS) {
            if (zoom > 0.1) {
              dx = dx + 0.1 * pixelsize * (xcursor - width / 2);
              dy = dy - 0.1 * pixelsize * (ycursor - height / 2);
            }
            if (zoom > 0.1)
              zoom -= 0.1;
          }
          if (event.key.keysym.sym == SDLK_KP_MINUS) {
            dx = dx - 0.1 * pixelsize * (xcursor - width / 2);
            dy = dy + 0.1 * pixelsize * (ycursor - height / 2);
            zoom += 0.1;
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
          if (zoom > 0.03) {
            dx = dx + 0.03 * pixelsize * event.wheel.y * (xcursor - width / 2);
            dy = dy - 0.03 * pixelsize * event.wheel.y * (ycursor - height / 2);
          }
          if (event.wheel.y > 0 && zoom > 0.01)
            zoom -= 0.03;
          else if (event.wheel.y < 0)
            zoom += 0.03;
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
