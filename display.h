#ifndef __DISPLAY_H__
#define __DISPLAY_H__extern float detail;



#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>

#define DEBUG 1

extern float pixelsize;

extern int detail;

extern float min_x;
extern float max_x;
extern float min_y;
extern float max_y;

void Display_InitGL();
void Display_SetViewport(int width, int height, float dx, float dy, float zoom);

#endif
