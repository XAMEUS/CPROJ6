#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[])
{

  SDL_Window *window; // Declare a pointer, main window

  // Initialize SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "XYW - SDL2",            // window title
    SDL_WINDOWPOS_UNDEFINED, // initial x position
    SDL_WINDOWPOS_UNDEFINED, // initial y position
    640,                     // width, in pixels
    480,                     // height, in pixels
    SDL_WINDOW_OPENGL        // flags
  );

  // Check that the window was successfully created
  if (window == NULL)
  {
    // In the case that the window could not be made...
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    return 1;
  }

  // Get displayModes from screen 0
  int modeNumber = SDL_GetNumDisplayModes(0);
  // Check the modeNumber
  if (modeNumber < 0)
  {
    fprintf(stderr, "SDL_GetNumDisplayModes failed: %s\n", SDL_GetError());
    return 1;
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
      return 1;
    }
    fprintf(stdout, "displayMode %d : %dx%dx%d\n", i, displayMode.w, displayMode.h, displayMode.refresh_rate);
  }

  fprintf(stdout, "Press the 'F' key to switch fullscreen.\n");
  fprintf(stdout, "Press the [x] button to close the window.\n");
  int fullscreen = 0;
  SDL_Event event;
  int quit = 0;
  while (!quit)
  {
    while (SDL_PollEvent(&event)) // User's actions
    {
      switch(event.type)
      {
        case SDL_QUIT: // Close button
        quit = 1;
        break;
        case SDL_KEYUP: // Key release
        if ( event.key.keysym.sym == SDLK_f ) // F key
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
  }

  // The window is open: could enter program loop here (see SDL_PollEvent())
  SDL_Delay(0);  // Pause execution for 3000 milliseconds, for example

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();
  return 0;
}
