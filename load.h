#ifndef __LOAD_H__
#define __LOAD_H__

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>
#include "parse.h"
#include "display.h"

GLuint tessellate(way w);


GLuint Tess_Obj_Highway(int c, GLdouble **points,way w);
GLuint Tess_Obj_Building(int c, GLdouble **points);

#endif
