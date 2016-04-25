/**
* \file display.h
* \brief Initializes SDL et OpenGL
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* Initializes OpenGL and set up the camer.
*
*/

#ifndef __DISPLAY_H__
#define __DISPLAY_H__extern float detail;



#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>
#include <png.h>


#define DEBUG 0

extern double pixelsize;

extern int screenshoot;

/**
* \brief LoD, Level of details
*/
extern int detail;

/**
* \brief minlon value
*/
extern float min_x;
/**
* \brief maxlon value
*/
extern float max_x;
/**
* \brief minlat value
*/
extern float min_y;
/**
* \brief maxlat value
*/
extern float max_y;

/**
* \fn void Display_InitGL()
* \brief Initializes OpenGL and enable options.
* \return void
*/
void Display_InitGL();

/**
* \fn void Display_SetViewport(int width, int height, float dx, float dy, float zoom);
* \brief Sets up the camera (proportion, position, zoom).
* \param width width of the window available for drawing.
* \param height height of the window available for drawing.
* \param dx x camera translation.
* \param dy y camera translation.
* \param zoom zoom factor.
* \return void
*/
void Display_SetViewport(int width, int height, float dx, float dy, float zoom);

/**
* \fn void screenshot_png(const char *filename, unsigned int width, unsigned int height, GLubyte **pixels, png_byte **png_bytes, png_byte ***png_rows)
* \brief Takes a screenshoot (png format).
*/
void screenshot_png(const char *filename, unsigned int width, unsigned int height, GLubyte **pixels, png_byte **png_bytes, png_byte ***png_rows);

#endif
