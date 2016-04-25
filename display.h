/**
* \file display.h
* \brief Initialise SDL et OpenGL
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 25 avril 2016
*
* Permet d'initialiser OpenGL et de définir/placer la caméra pour le rendu.
*
*/

#ifndef __DISPLAY_H__
#define __DISPLAY_H__extern float detail;



#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_opengl.h>

#define DEBUG 0

extern double pixelsize;

/**
* \brief Niveau de détail
*/
extern int detail;

/**
* \brief Valeur correspondant au minlon
*/
extern float min_x;
/**
* \brief Valeur correspondant au maxlon
*/
extern float max_x;
/**
* \brief Valeur correspondant au minlat
*/
extern float min_y;
/**
* \brief Valeur correspondant au maxlat
*/
extern float max_y;

/**
* \fn void Display_InitGL()
* \brief Initialise OpenGL et active certains modes de rendu.
* \return void
*/
void Display_InitGL();

/**
* \fn void Display_SetViewport(int width, int height, float dx, float dy, float zoom);
* \brief Place la caméra (proportions, position, zoom).
* \param width la largeur de la fenêtre accessible pour le dessin.
* \param height la hauteur de la fenêtre accessible pour le dessin.
* \param dx le décalage en x de la caméra.
* \param dy le décalage en y de la caméra.
* \param zoom le facteur de zoom.
* \return void
*/
void Display_SetViewport(int width, int height, float dx, float dy, float zoom);

#endif
