#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>

extern float pixelsize;

extern float min_x;
extern float max_x;
extern float min_y;
extern float max_y;

void Display_InitGL();
void Display_SetViewport(int width, int height, float dx, float dy, float zoom);
