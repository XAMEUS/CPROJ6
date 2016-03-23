#include "ui.h"
#include "load.h"

int Display_Application(int argc, char* argv[])
{

  SDL_Window *window; // Declare a pointer, main window
  int width = 640;
  int height = 480;
  GLfloat dx = 0;
  GLfloat dy = 0;
  GLfloat zoom = 1.0;

  initNodesBounds(argv[1]);

  min_x = minx;
  max_x = maxx;
  min_y = miny;
  max_y = maxy;

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

  int i;
  for(i=0;i<sizeWays;i++){
    ways[i].glist=tessellate(ways[i]);
  }

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
          if (event.key.keysym.sym == SDLK_s)
          {
            if (showFrame) showFrame = 0;
            else showFrame = 1;
          }
          if (event.key.keysym.sym == SDLK_p)
          {
            projection = !projection;
            if(projection){
              min_x = minx;
              max_x = maxx;
              min_y = miny;
              max_y = maxy;
            }else{
              min_x = minlon;
              max_x = maxlon;
              min_y = minlat;
              max_y = maxlat;
            }
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
