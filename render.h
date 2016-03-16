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

#define HIGHWAY_MOTORWAY_COLOR glColor3f(1.0f,0.0f,0.0f)
#define HIGHWAY_TRUNK_COLOR glColor3f(1.0f,0.5f,0.5f)
#define HIGHWAY_PRIMARY_COLOR glColor3f(1.0f,1.0f,0.0f)
#define HIGHWAY_SECONDARY_COLOR glColor3f(1.0f,0.0f,1.0f)
#define HIGHWAY_TERTIARY_COLOR glColor3f(0.0f,1.0f,0.0f)
#define HIGHWAY_UNCLASSIFIED_COLOR glColor3f(0.0f,1.0f,1.0f)
#define HIGHWAY_RESIDENTIAL_COLOR glColor3f(0.0f,0.5f,0.5f)
#define HIGHWAY_SERVICE_COLOR glColor3f(0.5f,0.5f,0.5f)

extern int showFrame;
extern int projection;

void Display_Frame();
void Display_Render(SDL_Renderer* renderer, int width, int height, float dx, float dy, float zoom);

void Render_Default(way w);

void Render_Highway(way w);
void Render_Highway_test(way w);
