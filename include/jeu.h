/*!
 * \file jeu.h
 * \brief Fonctions liée aux cellules
 * \version 1.0
 * \date 17 fevrier 2020
*/

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/*!
 * \brief Modulo
 * \param [in] i 1ere opérande
 * \param [in] m 2eme opérande
 * \return Valeur du modulo
*/
static inline int modulo(int i, int m) {return (i+m)%m;}

/*!
 * \brief Compte le nombre de voisins vivants de la cellule (i,j)
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [in] g Grille dans laquelle (i,j) et ses voisins
 * \return Nombre de voisins vivants
*/
int compte_voisins_vivants (int i, int j, grille g);

/*!
 * \brief Fait évoluer la grille g d'un pas de temps
 * \param [in] g Pointeur sur la grille à évoluer
 * \param [out] gc Pointeur sur la grille évoluée
*/
void evolue (grille *g, grille *gc);

#endif
