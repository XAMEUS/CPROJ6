#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>
#include "parse.h"
#include "display.h"

extern int showFrame;
extern int projection;

void Display_Frame();
void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom);
