/**
* \file draw.h
* \brief Routines de dessin.
* \author Perrachon Quentin, Gourgoulhon Maxime, Boufedji Belkacem
* \version 0.9
* \date 25 avril 2016
*
* Routines permettant de dessiner divers forme élémentaires.
*
*/

#include "display.h"
#include "tessellation.h"
#include <math.h>

/**
* \brief Pi approximation (constante).
*/
#define PI 3.14159265

/**
* \fn void Draw_Line(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1, GLdouble size, GLdouble depth)
* \brief Dessine une ligne entre deux points d'une épaisseur donnée.
* \param x0 la position en x du premier point.
* \param y0 la position en y du premier point.
* \param x1 la position en x du deuxième point.
* \param y1 la position en y du deuxième point.
* \param size l'epaisseur du trait.
* \param depth z.
* \return void
*/
void Draw_Line(GLdouble x0, GLdouble y0, GLdouble x1, GLdouble y1, GLdouble size, GLdouble depth);


/**
* \fn void Draw_Circle(GLdouble x, GLdouble y, GLdouble size, GLdouble depth)
* \brief Dessine un cercle de centre (x, y) et de rayon size.
* \param x la position en x du centre du cercle.
* \param y la position en y du centre du cercle.
* \param size rayon du cercle.
* \param depth z.
* \return void
*/
void Draw_Circle(GLdouble x, GLdouble y, GLdouble size, GLdouble depth);


/**
* \fn Draw_Lines(int n, GLdouble **points, GLdouble size, GLdouble depth)
* \brief Dessine des lignes suivant une liste de points.
* \param n taille de la liste.
* \param **points liste de points.
* \param size l'epaisseur des lignes.
* \param depth z.
* \return void
*/
void Draw_Lines(int n, GLdouble **points, GLdouble size, GLdouble depth);

/**
* \fn void Draw_Lines_old(int n, GLdouble **points, GLdouble size)
* \deprecated Fonction dépréciée, ne plus utiliser !
* \brief Dessine des lignes suivant une liste de points, utilisant l'ancienne méthode.
* \param n taille de la liste.
* \param **points liste de points.
* \param size l'epaisseur des lignes.
* \return void
*/
void Draw_Lines_old(int n, GLdouble **points, GLdouble size);
