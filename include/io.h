/*!
 * \file io.h
 * \brief Entrées et sorties du programme
 * \version 4.0
 * \date 31 mars 2020
*/

#ifndef __IO_H
#define __IO_H
#endif

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#if CAIRO

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo.h>
#include <cairo-xlib.h>

#define SIZEX 760
#define SIZEY 760

/*!
 * \brief Création d'une surface Cairo avec X11
 * \param[in] x Largeur de la surface
 * \param[in] y Hauteur de la surface
 */
extern cairo_surface_t *cairo_create_x11_surface(int x, int y);

/*!
 * \brief Destruction d'une surface Cairo avec X11
 */
extern void cairo_close_x11_surface();

/*!
 * \brief Affichage d'un trait horizontal (MODE=CAIRO)
 * \param[in] c Nombre de cellules du trait
 * \param[in] height Hauteur du trait
 * \param[in] line Hauteur de la ligne
 */
void affiche_trait (int c, int height, float line);

/*!
 * \brief Affichage d'une ligne de la grille (MODE=CAIRO)
 * \param[in] c Nombre de cellules de la ligne
 * \param[in] ligne Tableau qui indique l'état de chaque cellule (vivante ou morte)
 * \param[in] aging Indique si le vieillissement est activé ou désactivé
 * \param[in] height  Hauteur du trait
 * \param[in] line Hauteur de la ligne
 */
void affiche_ligne (int c, int* ligne, int aging, int height, float line);

/*!
 * \brief Effacement de la grille (MODE=CAIRO)
 */
void efface_grille ();

#else

/*!
 * \brief Affichage d'un trait horizontal
 * \param [in] c Nombre de cellules dans la colonne
 */
void affiche_trait (int c);

/*!
 * \brief Affichage d'une ligne de la grille
 * \param [in] c Nombre de la cellules dans la ligne
 * \param [in] ligne Tableau qui indique si chaque cellule est morte
 * \param [in] aging Si true, alors affiche l'age de la cellule, sinon 0
 */
void affiche_ligne (int c, int* ligne, int aging);

/*!
 * \brief Effacement d'une grille
 * \param [in] g Grille à effacer
 */
void efface_grille (grille g);

#endif

/*!
 * \brief Affichage d'une grille
 * \param [in] g Grille
 * \param [in] timer Indique le nombre d'étapes
 * \param [in] cycle Indique le mode cycle demandé
 * \param [in] aging Indique le mode vieillisement demandé
*/
void affiche_grille (grille g, int timer, int cycle, int aging);

/*!
 * \brief Debute le jeu
 * \param [in,out] g Pointeur sur la grille principale
 * \param [in,out] gc Pointeur sur une seconde grille de même paramètres
*/
void debut_jeu(grille *g, grille *gc);
