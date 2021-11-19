/*!
 * \file io.h
 * \brief Entrées et sorties du programme
 * \version 1.0
 * \date 8 mars 2020
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
 * \param [in] aging Si true, alors affiche l'age de la cellule, sinon 0
 */
void affiche_ligne (int c, int* ligne, int aging);

/*!
 * \brief Affichage d'une grille
 * \param [in] g Grille
 * \param [in] timer Indique le nombre d'étapes
 * \param [in] cycle Indique le mode cycle demandé
 * \param [in] aging Indique le mode vieillisement demandé
*/
void affiche_grille (grille g, int timer, int cycle, int aging);

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
