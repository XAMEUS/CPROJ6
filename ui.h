/**
* \file ui.h
* \brief Gère l'interface graphique
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 25 avril 2016
*
* Contient la boucle principale d'éxécution.
*
*/


#ifndef __UI_H__
#define __UI_H__


#include "display.h"
#include "render.h"

/**
* \fn int Display_Application(int argc, char* argv[])
* \brief Boucle principale, main.
* \param argc nombre d'argurments.
* \param *argv[] les argurments.
* \return int exit code
*/
int Display_Application(int argc, char* argv[]);

#endif
