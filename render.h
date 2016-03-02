#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>
#include "parse.h"
#include "display.h"

#define HIGHWAY_MOTORWAY_SIZE 10.0f
#define HIGHWAY_TRUNK_SIZE 8.0f
#define HIGHWAY_PRIMARY_SIZE 5.0f
#define HIGHWAY_SECONDARY_SIZE 4.0f
#define HIGHWAY_TERTIARY_SIZE 3.0f
#define HIGHWAY_UNCLASSIFIED_SIZE 2.0f
#define HIGHWAY_RESIDENTIAL_SIZE 2.0f
#define HIGHWAY_SERVICE_SIZE 1.0f

extern int showFrame;
extern int projection;

void Display_Frame();
void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom);

void Render_Default(way w);

void Render_Highway(way w);
