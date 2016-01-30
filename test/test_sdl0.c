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

  // The window is open: could enter program loop here (see SDL_PollEvent())
  SDL_Delay(4000);  // Pause execution for 4000 milliseconds, for example

  // Close and destroy the window
  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();
  return 0;
}
