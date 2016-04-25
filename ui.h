/**
* \file ui.h
* \brief Manage the gui
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 04 25 2016
*
* Main running loop.
*
*/


#ifndef __UI_H__
#define __UI_H__


#include "display.h"
#include "render.h"

/**
* \fn int Display_Application(int argc, char* argv[])
* \brief Main loop.
* \param argc number of argurments.
* \param *argv[] argurments list.
* \return int exit code
*/
int Display_Application(int argc, char* argv[]);

#endif
