/**
* \file load.h
* \brief Loading routines
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* Loading system, tessellating objects.
*
*/


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


GLuint Tess_Obj_Way(int c, GLdouble **points,way w);
GLuint Tess_Obj_Area(int c, GLdouble **points,way w);

#endif
