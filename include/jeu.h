/*!
 * \file jeu.h
 * \brief Fonctions liée aux cellules
 * \version 3.0
 * \date 31 mars 2020
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
 * \brief Compte le nombre de voisins vivants de la cellule avec des bords cycliques (i,j)
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [in] g Grille dans laquelle (i,j) et ses voisins
 * \return Nombre de voisins vivants
*/
int compte_voisins_vivants_cyclique (int i, int j, grille g);

/*!
 * \brief Compte le nombre de voisins vivants de la cellule (i,j) avec des bords non cycliques
 * \param [in] i Ligne de la cellule
 * \param [in] j Colonne de la cellule
 * \param [in] g Grille dans laquelle (i,j) et ses voisins
 * \return Nombre de voisins vivants
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/*!
 * \brief Fait évoluer la grille g d'un pas de temps
 * \param [in] g Pointeur sur la grille à évoluer
 * \param [out] gc Pointeur sur la grille évoluée
 * \param [in] timer Nombre d'étapes dans l'évolution
 * \param [in] compte_voisins_vivants Pointeur sur une fonction qui compte les voisants vivants d'une cellule en fonction de la demande de l'utilisateur (cylique ou non)
 * \param [in] aging Evolution différent en fonction de si le vieillisement est activé ou désactivé
*/
void evolue (grille *g, grille *gc, int *timer, int (*compte_voisins_vivants) (int, int, grille), int aging);

#endif
