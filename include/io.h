/*!
 * \file io.h
 * \brief Entrées et sorties du programme
 * \version 1.0
 * \date 17 fevrier 2020
*/
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/*!
 * \brief Affichage d'un trait horizontal
 * \param [in] c Nombre de cellules dans la colonne
 */
void affiche_trait (int c);

/*!
 * \brief Affichage d'une ligne de la grille
 * \param [in] c Nombre de la cellules dans la ligne
 * \param [in] ligne Tableau qui indique si chaque cellule est morte
 */
void affiche_ligne (int c, int* ligne);

/*!
 * \brief Affichage d'une grille
 * \param [in] g Grille
*/
void affiche_grille (grille g);

/*!
 * \brief Effacement d'une grille
 * \param [in] g Grille à effacer
 */
void efface_grille (grille g);

/*!
 * \brief Debute le jeu
 * \param [in,out] g Pointeur sur la grille principale
 * \param [in,out] gc Pointeur sur une seconde grille de même paramètres
*/
void debut_jeu(grille *g, grille *gc);

#endif
