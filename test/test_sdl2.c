#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void render(SDL_Renderer* renderer)
{
  // Set render color ( background will be rendered in this color )
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  // Clear window
  SDL_RenderClear(renderer);
  // Render
  SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{

  SDL_Window *window; // Declare a pointer, main window

  // Initialize SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Get displayModes from screen 0
  int modeNumber = SDL_GetNumDisplayModes(0);
  // Check the modeNumber
  if (modeNumber < 0)
  {
    fprintf(stderr, "SDL_GetNumDisplayModes failed: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "displayModes: %d\n", modeNumber);

  int i;
  SDL_DisplayMode displayMode;
  // Print each displayMode
  for ( i = 0 ; i < modeNumber ; i++ )
  {
    // Try to get the displayMode
    if (SDL_GetDisplayMode(0, i, &displayMode))
    {
      fprintf(stderr,"SDL_GetDisplayMode failed: %s\n",SDL_GetError());
      exit(EXIT_FAILURE);
    }
    fprintf(stdout, "displayMode %d : %dx%dx%d\n", i, displayMode.w, displayMode.h, displayMode.refresh_rate);
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "SDL2 - 2D Accelerated Rendering",            // window title
    SDL_WINDOWPOS_UNDEFINED, // initial x position
    SDL_WINDOWPOS_UNDEFINED, // initial y position
    640,                     // width, in pixels
    480,                     // height, in pixels
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
  fprintf(stdout, "Press the [x] button to close the window.\n");

  SDL_Renderer* renderer = NULL;
  renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

  int fullscreen = 0;
  SDL_Event event;
  int quit = 0;
  time_t t = time(NULL);
  time_t ctime = time(NULL);
  int frames = 0;
  while (!quit)
  {
    render(renderer);
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
        break;
      }
    }
    frames++;
    ctime = time(NULL);
    if (t != ctime) {
      t = ctime;
      printf("%d fps\n", frames);
      frames = 0;
    }
  }

  // The window is open: could enter program loop here (see SDL_PollEvent())
  SDL_Delay(0);  // Pause execution for 3000 milliseconds, for example

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();

  return EXIT_SUCCESS;
}
